/*
*   FILENAME
*   tcsAoMechCommands.c
*
*   FUNCTION NAME(S)
*
*   tcsCADaoMechOnOff    - Implement Altair commands with ON/OFF choice
*   tcsCADaoPrepareCm    - Implement the Altair prepareCm command
*   tcsCADaoMove         - Implement the Altair move command
*   tcsCADaoCentreWfs    - Implement the Altair centreWfs command
*   tcsCADaoCorrect      - Implement the Altair correct command
*   tcsCADaoFlexFile     - Set flexure and NCP file names
*   tcsCADaoGimOffsets   - Set/Clear Altair's gimbal offsets
*   tcsCADaoLgsIris      - Open/close the LGS iris
*   tcsCADaoLgsttfSource - Use PWFS1 or OIWFS for LGS TTF 
*   tcsCADaoNDFilter     - Insert/remove the LGS or NGS ND filter
*   tcsCADaoMoveAStar    - Implement the Altair moveAStar command
*   tcsCADaoDeployAdc    - Implement the Altair deployAdc command
*   tcsCADaoBeamSplitter - Implement the Altair aoBeamSplitter command
*   tcsCADaoCalMode      - Implement the Altair aoCalMode command
*   tcsCADaoShutter      - Implement the Altair Entry/Exit Shutter commands
*   tcsCADaoMoveAdc      - Implement the Altair aoMoveAdc command
*   tcsCADaoOiwfsSource  - Implement the Altair aoOiwfsSource command
*   tcsCADaoSFOLoop      - Implement control of the SFO loop
*   tcsCADaoStats        - Implement the Altair stats command
*   tcsCADaoTTGSLoop     - Implement control of the STRAP loop
*
*/
/* *INDENT-OFF* */
/*
 * $Log $
 *
 */
/* *INDENT-ON* */


#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include  <string.h>
#include  <math.h>

#include  <dbDefs.h>
#include  <dbEvent.h>
#include  <genSubRecord.h>
#include  <cadRecord.h>
#include  <subRecord.h>
#include  <dbCommon.h>
#include  <recSup.h>
#include  <cad.h>
#include  "tcsConstants.h"
#include  "tcsDecode.h"
#include  "tcsCadSupport.h"
#include  "tcsInterlocks.h"
#include  "tcsConfig.h"
#include  "tcsPointing.h"


#define ZDMAX 73.0          /* Maximum operational ZD for Gemini telescope */
#define CASS_ANG_MIN   0.0  /* Cassegrain rotator angle range */
#define CASS_ANG_MAX 360.0
#define AOWFS_XMIN  -37.2   /* AO WFS X/Y probe position limits */
#define AOWFS_XMAX   37.2
#define AOWFS_YMIN  -37.2
#define AOWFS_YMAX   37.2
#define AOGIM_XMIN  -10000.0   /* AO Gimbal offset limits          */
#define AOGIM_XMAX   10000.0   /* These are currently dummy values */ 
#define AOGIM_YMIN  -10000.0   /* as placeholders.                 */
#define AOGIM_YMAX   10000.0 
#define AOGIM_ZMIN  -10000.0   
#define AOGIM_ZMAX   10000.0 

/*+
 *   Function name:
 *   tcsCADaoMechOnOff
 *
 *   Purpose:
 *   Implements Altair commands in the TCS which have 1
 *   parameter only, with the choice of ON or OFF as valid input
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoMechOnOff (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Choice string (ON or OFF)
 *
 *   EPICS output paramters:
 *      vala => Choice string (ON or OFF)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoMechOnOff (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  int code ;              /* Index of state */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "Missing value");
       break ;
     } 
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoGimOffsets
 *
 *   Purpose:
 *   Set the gimbal offsets in Altair's database
 *
 *   Description:
 *   The code here is standard for a CAD. The parameters are validated
 *   and if any are null they are set to zero. The validated demands
 *   are then output for use by EPICS. The difference with this command
 *   starts at that point. There is no command in Altair to set the 
 *   gimbal offsets but rather the TCS has to write directly into
 *   specific Altair records. There can never therefore be a busy/idle
 *   response and the TCs has no way of knowing whehter the parameters
 *   have been accepted.
 *
 *   Invocation:
 *   tcsCADaoGimOffsets (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => Gimbal X offset 
 *   b => Gimbal Y offset 
 *   c => Gimbal Z offset 
 *
 *   Epics output parameters:
 *
 *   vala => Gimbal X offset 
 *   valb => Gimbal Y offset 
 *   valc => Gimbal Z offset 
 *
 *   Function value:
 *   (<)  status (long)  Return status
 * 
 *-
 */

long tcsCADaoGimOffsets (struct cadRecord *pcad) 
{
   int status;
   static double offX = 0.0;
   static double offY = 0.0;
   static double offZ = 0.0;  

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode X offset */
     if (!tcsDcLen(pcad->a)) {
       offX = 0.0;
     } else {
       if (tcsDcDouble ("Offset X: ", pcad->a, &offX, pcad))
         break;
       if (offX < AOGIM_XMIN || offX > AOGIM_XMAX) {
         tcsCsAppendMessage (pcad, "X offset out of range") ;
         break ;
       }
     }
	
/* Decode Y offset */
     if (!tcsDcLen(pcad->b)) {
       offY = 0.0;
     } else {
       if (tcsDcDouble ("Offset Y: ", pcad->b, &offY, pcad))
         break;
       if (offY < AOGIM_YMIN || offY > AOGIM_YMAX) {
         tcsCsAppendMessage (pcad, "Y offset out of range") ;
         break ;
       }
     }
	
/* Decode Z offset */
     if (!tcsDcLen(pcad->c)) {
       offZ = 0.0;
     } else {
       if (tcsDcDouble ("Offset Z: ", pcad->c, &offZ, pcad))
         break;
       if (offZ < AOGIM_ZMIN || offZ > AOGIM_ZMAX) {
         tcsCsAppendMessage (pcad, "Z offset out of range") ;
         break ;
       }
     }
	
     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem */
    *(double *)pcad->vala = offX;
    *(double *)pcad->valb = offY;
    *(double *)pcad->valc = offZ;
    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoLgsIris 
 *
 *   Purpose:
 *   Command the LGS iris to open or close
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoLgsIris (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Iris position (OPEN, CLOSE or percentage)
 *
 *   EPICS output paramters:
 *      vala => Shutter position (open, close or percentage)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoLgsIris (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"OPEN", "CLOSE", NULL} ;
  static int bs ;         /* Index of specified position */
  double dval ;
  static char ins[MAX_STRING_SIZE];

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     /* Altair only seems really happy with all lower case strings */
     tcsDcLc((char *)pcad->a, MAX_STRING_SIZE, ins);
     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No iris position given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) {

/* Note that if we pass an invalid double representation then dval will
*  be set to 0.0. Unfortunately errno will still be 0 in this case so
*  we can't trap it
*/
       dval = strtod(pcad->a, NULL);
       if (dval < 0.0 || dval > 100.0) {
         tcsCsAppendMessage (pcad, " Iris position out of range");
         break ;
       }
       if (dval == 0.0) {
         strcpy(ins, "close");
       }
       if (dval == 100.0) {
         strcpy(ins, "open");
       }
     }

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, ins, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoNDFilter 
 *
 *   Purpose:
 *   Insert or remove the ND filter from the LGS or NGS beam
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoNDFilter (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Filter position (In or Out)
 *
 *   EPICS output paramters:
 *      vala => Filter position (In or Out)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoNDFilter (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"IN", "OUT", NULL} ;
  int bs ;                /* Index of specified position */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No filter position given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break; 

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoPrepareCm
 *
 *   Purpose:
 *   Implement the Altair prepareCm (prepare control matrix)
 *   command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. Only fields A & B are mandatory
 *
 *   Invocation:
 *   tcsCADaoPrepareCm (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => Guide X position  (mm.)
 *   b => Guide Y position  (mm.)
 *   c => Seeing (optional) (metres)
 *   d => Guide Object estimated magnitude (optional)
 *   e => Aloft windspeed (optional m/s)
 *   f => 0/1 Field lens in use (1) or not in use (0)
 *
 *   Epics output parameters:
 *
 *   vala => Guide X position (mm.)
 *   valb => Guide Y position (mm.)
 *   valc => Seeing (optional) (metres)
 *   vald => Guide Object estimated magnitude (optional)
 *   vale => Aloft windspeed (optional m/s)
 *   vale => Field lens status (0/1)
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   25-Feb-02 PBT  Initial version
 *-
 */

long tcsCADaoPrepareCm (struct cadRecord *pcad) 
{
   int status;
   static double guideX, guideY, seeing, mag, wspeed ;  /* Requested values */
   static long useFlens = 0;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode Guide X position */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No Guide X pos given");
       break ;
     } 
     if (tcsDcDouble ("Guide X: ", pcad->a, &guideX, pcad))
       break;
     if (guideX < AOWFS_XMIN || guideX > AOWFS_XMAX) {
         tcsCsAppendMessage (pcad, "X pos out of range") ;
         break ;
     }
	
/* Decode Guide Y position */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No Guide Y pos given");
       break ;
     } 
     if (tcsDcDouble ("Guide Y: ", pcad->b, &guideY, pcad))
       break;
     if (guideY < AOWFS_YMIN || guideY > AOWFS_YMAX) {
         tcsCsAppendMessage (pcad, "Y pos out of range") ;
         break ;
     }
/* Decode Seeing value */
     if (tcsDcLen(pcad->c)) {
       if (tcsDcDouble ("Seeing: ",  pcad->c, &seeing, pcad))
         break;
       if (seeing <= 0.0 || seeing > 1.0) {
           tcsCsAppendMessage (pcad, "Seeing value out of range") ;
           break ;
       }
     }
/* Decode guide object mag.  */
     if (tcsDcLen(pcad->d)) {
       if (tcsDcDouble ("Magnitude: ", pcad->d, &mag, pcad))
         break;
       if (mag < -2.0 || mag > 20.0) {
           tcsCsAppendMessage (pcad, "Magnitude out of range") ;
           break ;
       }
     }

/* Decode aloft windspeed  */
     if (tcsDcLen(pcad->e)) {
       if (tcsDcDouble ("Windspeed: ", pcad->e, &wspeed, pcad))
         break;
       if (wspeed < 0.0 ) {
           tcsCsAppendMessage (pcad, "Windspeed out of range") ;
           break ;
       }
     }

/* Decode use of field lens */
     if (tcsDcLen(pcad->f)) {
       if (tcsDcLong ("Use Flens: ", pcad->f, &useFlens, pcad))
         break;
       if (useFlens < 0 || useFlens > 1) {
         tcsCsAppendMessage (pcad, "Use Flens must be 0 or 1") ;
         break ;
       }
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
/* N.B. we reverse x and y as Altair has a different coordinate frame */
    strncpy(pcad->vala, pcad->b, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
    strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
    strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoMove
 *
 *   Purpose:
 *   Implement the Altair Move WFS probe
 *   command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. 
 *
 *   Invocation:
 *   tcsCADaoMove (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => Guide X position (mm.)
 *   b => Guide Y position (mm.)
 *   c => Guide Z position (mm.)
 *   d => Cass Rotator Angle (degs.)
 *   e => Zenith distance (degs.)
 *   f => Sodium altitude (km.)
 *
 *   Epics output parameters:
 *
 *   vala => Guide X position (mm.)
 *   valb => Guide Y position (mm.)
 *   valc => Guide Z position (mm.)
 *   vald => Cass Rotator Angle (degs.)
 *   vale => Zenith distance (degs.)
 *   valf => Sodium altitude (km.) 
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   25-Feb-02 PBT  Initial version
 *-
 */

long tcsCADaoMove (struct cadRecord *pcad) 
{
   int status;
   static double guideX, guideY, guideZ, cassAng, zd, sodiumAlt ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode Guide X position */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No Guide X pos given");
       break ;
     }     
     if (tcsDcDouble ("Guide X: ", pcad->a, &guideX, pcad))
       break;
     if (guideX < AOWFS_XMIN || guideX > AOWFS_XMAX) {
         tcsCsAppendMessage (pcad, "X pos out of range") ;
         break ;
     }
	
/* Decode Guide Y position */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No Guide Y pos given");
       break ;
     }     
     if (tcsDcDouble ("Guide Y: ", pcad->b, &guideY, pcad))
       break;
     if (guideY < AOWFS_YMIN || guideY > AOWFS_YMAX) {
         tcsCsAppendMessage (pcad, "Y pos out of range") ;
         break ;
     }
/* Decode Guide Z position */
     if (!tcsDcLen(pcad->c)) {
       tcsCsAppendMessage (pcad, "No Guide Z pos given");
       break ;
     } 
     if (tcsDcDouble ("Guide Z: ", pcad->c, &guideZ, pcad))
       break;
     if (guideZ < -1.0 || guideZ > 1.0) {
         tcsCsAppendMessage (pcad, "Z pos out of range") ;
         break ;
     }
/* Decode Cassegrain angle value */
     if (tcsDcLen(pcad->d)) {
       if (tcsDcDouble ("Cass Angle: ",  pcad->d, &cassAng, pcad))
           break;
       if (cassAng < CASS_ANG_MIN || cassAng > CASS_ANG_MAX) {
           tcsCsAppendMessage (pcad, "Cass angle out of range") ;
           break ;
       }
     }
/* Decode Zenith distance value */
     if (tcsDcLen(pcad->e)) {
       if (tcsDcDouble ("Zenith distance: ",  pcad->e, &zd, pcad))
           break;
       if (zd < 0.0 || zd > ZDMAX) {
           tcsCsAppendMessage (pcad, "ZD out of range") ;
           break ;
       }
     }
/* Decode Sodium altitude value */
     if (tcsDcLen(pcad->f)) {
       if (tcsDcDouble ("Sodium altitude: ",  pcad->f, &sodiumAlt, pcad))
           break;
       if (sodiumAlt < 85.0 || sodiumAlt > 100.0) {
           tcsCsAppendMessage (pcad, "Sodium Alt out of range") ;
           break ;
       }
     }
     
     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
    strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
    strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoCentreWfs
 *
 *   Purpose:
 *   Implement the Altair centre WFS probe
 *   command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. 
 *
 *   Invocation:
 *   tcsCADaoCentreWfs (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a =>  WFS offsets flag : 1 or 0
 *
 *   Epics output parameters:
 *
 *   vala =>  WFS offsets flag
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   25-Feb-02 PBT  Initial version
 *-
 */

long tcsCADaoCentreWfs (struct cadRecord *pcad) 
{
   int status;
   static long offsetFlag ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode offset flag */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No offset flag given");
       break ;
     }  
     if (tcsDcLong ("Offset flag: ", pcad->a, &offsetFlag, pcad))
       break;
     if (offsetFlag < 0 || offsetFlag > 1) {
         tcsCsAppendMessage (pcad, "Offset flag invalid") ;
         break ;
     }
     
     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoCorrect
 *
 *   Purpose:
 *   Implement the Altair AO loop correcting
 *   control command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. 
 *
 *   Invocation:
 *   tcsCADaoCorrect (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => Close servo loop: ON or OFF
 *   b => Control matrix ID (optional)
 *   c => Override with last used control matrix
 *
 *   Epics output parameters:
 *
 *   vala => Close servo loop: ON or OFF
 *   valb => Control matrix ID
 *   valc => Override with last used control matrix
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   25-Feb-02 PBT  Initial version
 *-
 */

long tcsCADaoCorrect (struct cadRecord *pcad) 
{
   int status, code;
   static long matrixID, overrideFlag;
   static char controlMatId[MAX_STRING_SIZE] ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode close servo loop status  */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No servo loop demand");
       break ;
     }  
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;
	
/* Decode control matrix ID (optional) */
     strncpy(controlMatId, pcad->b, MAX_STRING_SIZE) ;
     if (tcsDcLen(pcad->b)) {
       if (tcsDcLong ("Matrix ID: ", pcad->b, &matrixID, pcad))
         break;
       if (matrixID < 0) {
         tcsCsAppendMessage (pcad, "Invalid matrix ID") ;
         break ;
       }
     } else {
/* A matrix ID of 0 is the same as a NULL demand */
       strcpy(controlMatId, "0") ;
     }
/* Decode override flag */
     if (!tcsDcLen(pcad->c)) {
       tcsCsAppendMessage (pcad, "No override flag");
       break ;
     }  
     if (tcsDcLong ("Override flag: ", pcad->c, &overrideFlag, pcad))
       break;
     if (overrideFlag < 0 || overrideFlag > 1) {
         tcsCsAppendMessage (pcad, "Invalid flag (C)") ;
         break ;
     }
     
     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, controlMatId, MAX_STRING_SIZE) ;
    strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoFlexFile
 *
 *   Purpose:
 *   Set the flexure and NCP file names in Altair
 *
 *   Description:
 *   This routine passes the file names that contain the flexure and
 *   non common path corrections to Altair. No checks are done on the 
 *   validity or existence of the files, that is done by Altair
 *
 *   Invocation:
 *   tcsCADaoFlexFile (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *   a => NCP filename 
 *   b => Flexure filename 
 *
 *   Epics output parameters:
 *   vala => NCP filename 
 *   valb => Flexure filename 
 *
 *   Function value:
 *   Return status
 *-
 */

long tcsCADaoFlexFile (struct cadRecord *pcad) 
{
   int status;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT;
     
     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoMoveAStar
 *
 *   Purpose:
 *   Implement the Altair move artifical star calibration
 *   unit (moveAStar) command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. 
 *
 *   Invocation:
 *   tcsCADaoMoveAStar (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => Position of artifical star calibration unit
 *   b => Probe X position (mm.)
 *   c => Probe Y position (mm.)
 *   d => Probe Z position (mm.)
 *
 *   Epics output parameters:
 *   vala => Position of artifical star calibration unit
 *   valb => Probe X position (mm.)
 *   valc => Probe Y position (mm.)
 *   vald => Probe Z position (mm.)
 *
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   25-Feb-02 PBT  Initial version
 *-
 */

long tcsCADaoMoveAStar (struct cadRecord *pcad) 
{
   int status;
   static char *bsopts[] = {"ASTAR", "FLOOD", "PARK", "FLENS",
                            "LGS", "NGS", NULL} ; /* Position names */
   int bs ;          /* Index of selected position */
   static double probeX, probeY, probeZ ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;
/* Decode position name */   
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No position given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;
     
     if (bs == 1)     /* Probe positions needed only for ASTAR (=1) */
     {
/* Decode Probe X position */
       if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No probe X pos given");
         break ;
       }  
       if (tcsDcDouble ("Probe X: ", pcad->b, &probeX, pcad))
         break;
       if (probeX < AOWFS_XMIN || probeX > AOWFS_XMAX) {
           tcsCsAppendMessage (pcad, "X pos out of range") ;
           break ;
       }
/* Decode probe Y position */
       if (!tcsDcLen(pcad->c)) {
         tcsCsAppendMessage (pcad, "No probe Y pos given");
         break ;
       }  
       if (tcsDcDouble ("Probe Y: ", pcad->c, &probeY, pcad))
         break;
       if (probeY < AOWFS_YMIN || probeY > AOWFS_YMAX) {
           tcsCsAppendMessage (pcad, "Y pos out of range") ;
           break ;
       }
/* Decode probe Y position */
       if (!tcsDcLen(pcad->d)) {
         tcsCsAppendMessage (pcad, "No probe Z pos given");
         break ;
       }  
       if (tcsDcDouble ("Probe Z: ", pcad->d, &probeZ, pcad))
         break;
       if (probeZ < 0.0 || probeZ > 100.0) {
           tcsCsAppendMessage (pcad, "Z pos out of range") ;
           break ;
       }
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Copy over the parameters for the subsystem CAD */
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;

    status = CAD_ACCEPT;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADaoDeployAdc 
 *
 *   Purpose:
 *   Implements the deployAdc command in the TCS
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoDeployAdc (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Science ADC position (IN or OUT)
 *
 *   EPICS output paramters:
 *      vala => Science ADC position (IN or OUT)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoDeployAdc (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"IN", "OUT", NULL} ;
  int bs ;                /* Index of specified position */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No ADC position given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   tcsCADaoBeamSplitter 
 *
 *   Purpose:
 *   Implements the selectBs command in the TCS
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoBeamSplitter (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Which beam splitter (IJHK or LM)
 *
 *   EPICS output paramters:
 *      vala => demand beam splitter 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoBeamSplitter (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *bsopts[] = {"IJHK", "LM", NULL} ;
  int bs ;                /* Index of selected beam splitter */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No beam splitter specified");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoCalMode 
 *
 *   Purpose:
 *   Implements the command that selects the AO calibration method
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoCalMode (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *   a => Artificial light source status (ON or OFF)
 *   b => Visual intensity of NGS (%age)
 *   c => Visual intensity of flood source (%age)
 *   d => Visual intensity of LGS source (%age)
 *
 *   EPICS output paramters:
 *   vala => Artificial light source status (ON or OFF)
 *   valb => Visual intensity of NGS (%age)
 *   valc => Visual intensity of flood source (%age)
 *   vald => Visual intensity of LGS source (%age)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoCalMode (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  int code ;              /* Index  */
  long ngsIntens, floodIntens, lgsIntens;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
/* Decode artifical star status flag (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No ON or OFF given");
       break ;
     }  
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;
/* Decode visual intensity of NGS */
     if (code == 1)    /* Calibration source(s) ON */
     {
       if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No NGS intens. given");
         break ;
       }  
       if (tcsDcLong ("NGS intensity: ", pcad->b, &ngsIntens, pcad))
         break;
       if (ngsIntens < 0 || ngsIntens > 100) {
           tcsCsAppendMessage (pcad, "NGS intensity invalid") ;
           break ;
       }
/* Decode visual intensity of Flood source */
       if (!tcsDcLen(pcad->c)) {
         tcsCsAppendMessage (pcad, "No Flood intens. given");
         break ;
       }  
       if (tcsDcLong ("Flood intensity: ", pcad->c, &floodIntens, pcad))
         break;
       if (floodIntens < 0 || floodIntens > 100) {
           tcsCsAppendMessage (pcad, "Flood intensity invalid") ;
           break ;
       }
/* Decode visual intensity of NGS */
       if (!tcsDcLen(pcad->d)) {
         tcsCsAppendMessage (pcad, "No LGS intens. given");
         break ;
       }  
       if (tcsDcLong ("LGS intensity: ", pcad->d, &lgsIntens, pcad))
         break;
       if (lgsIntens < 0 || lgsIntens > 100) {
           tcsCsAppendMessage (pcad, "LGS intensity invalid") ;
           break ;
       }
     }
     
     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
     strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE) ;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoShutter 
 *
 *   Purpose:
 *   Implements the Entry & Exit Shutter commands in the TCS
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoShutter (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Shutter position (OPEN or CLOSE)
 *
 *   EPICS output paramters:
 *      vala => Shutter position (OPEN or CLOSE)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoShutter (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"OPEN", "CLOSE", NULL} ;
  static int bs ;         /* Index of specified position */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No shutter position given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

/* Altair will only accept upper case so use bsopts */
     strncpy (pcad->vala, bsopts[bs], MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}


/*
 *   Function name:
 *   tcsCADaoMoveAdc
 *
 *   Purpose:
 *   Implement the aoMoveAdc command in the TCS
 *
 *   Description:
 *   The routine simply validates its inputs then performs the necessary
 *   unit conversions before outputting the data.
 *
 *   Invocation:
 *   tcsCADaoMoveAdc (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Cassegrain rotator angle (0->360 degs)
 *   b => Zenith distance (0->60 degs)
 *   c => central wavelength (nm)
 *   d => Adjust ADC during exposure (ON or OFF)
 *
 *   EPICS output parameters :
 *   vala => Cassegarin rotator angle 
 *   valb => Zenith distance 
 *   valc => central wavelength 
 *   vald => Adjust ADC during exposure 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcdouble        (tcsDecode)      Validate an input double 
 *   tcsCsAppendMessage (tcsCadSupport)  Append string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked     (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm  (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoMoveAdc (struct cadRecord *pcad)
 
{
  long status ;                            /* Return status */
  int code ;                               /* Index  */
  double parangle, zd, cenwave ;           /* Input parameter values */
 
/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
    status = CAD_ACCEPT ;

    switch (pcad->dir)
    {
 
     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* First check the Cassegrain rotator angle */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No rotator angle given");
       break ;
     }
     if (tcsDcDouble ("Rotator angle: ", pcad->a, &parangle, pcad)) break ;
     if (parangle < CASS_ANG_MIN || parangle > CASS_ANG_MAX )
     {
       tcsCsAppendMessage (pcad, "Rotator angle out of range") ;
       break ;
     }
/* Then check the zenith distance */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No zenith distance given");
       break ;
     }
     if (tcsDcDouble ("Zenith distance: ", pcad->b, &zd, pcad)) break ;
     if (zd < 0.0 || zd > ZDMAX )
     {
       tcsCsAppendMessage (pcad, "Zenith distance out of range") ;
       break ;
     }
  
/* Then check the requested central wavelength */
     if (!tcsDcLen(pcad->c)) {
       tcsCsAppendMessage (pcad, "No central wavelength given");
       break ;
     }
     if (tcsDcDouble ("wavelength: ", pcad->c, &cenwave, pcad)) break ;
 
/* Then check the adjust ADC flag value (ON or OFF)  */
     if (!tcsDcLen(pcad->d)) {
       tcsCsAppendMessage (pcad, "No ADC adjust status given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->d, &code, pcad)) break ;
 
     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

     break ;

     case menuDirectiveSTART :
 
       strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
       strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
       strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE);
       strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE);
       break;
 
     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;
   }
 
   return status ;
}


/*+
 *   Function name:
 *   tcsCADaoOiwfsSource 
 *
 *   Purpose:
 *   Implements the command that selects which OIWFS source to use 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoOiwfsSource (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Use OIWFS? either ON or OFF
 *      b => Bandwidth of low pass filter applied
 *
 *   EPICS output paramters:  
 *      vala => Use OIWFS?
 *      valb => Bandwidth of low pass filter applied
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDouble        (tcsDecode)      Validate an input double
 *   tcsDcLong          (tcsDecode)      Validate an input long
 *   tcsDcString        (tcsDecode)      Validate an input string
 *   tcsCsAppendMessage (tcsCadSupport)  Add string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked     (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm  (tcsConfig)      Mark record as part of a configuration
 *
 *
 *-
 */

long tcsCADaoOiwfsSource (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  int code ;              /* Index of selected OIWFS state */
  long bandwidth ;        /* Bandwidth of low pass filter applied */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
/* Decode (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No OIWFS ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;

/* Decode bandwidth */
     if (code == 1)  /* Switch ON */
     {
	 if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No bandwidth given");
         break ;
       }
/* During commissioning it was found that a value of -1 for bandwidth
*  meant use the default calculated by the AO system.
*/
       if (tcsDcLong ("bandwidth : ", pcad->b, &bandwidth, pcad)) break ;
       if (bandwidth != -1) {
         if (bandwidth > 500 || bandwidth < 0) {
           tcsCsAppendMessage (pcad, "bandwidth out of range ");
           break ;
         }
       }
     }

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoLgsttfSource 
 *
 *   Purpose:
 *   Implements the command that sets whether or not to use PWFS1 or OIWFS for
 *   LGS TTF 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsCADaoLgsttfSource (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Use PWFS1? either ON or OFF
 *      b => Use OIWFS? either ON or OFF
 *
 *   EPICS output paramters:  
 *      vala => Use PWFS1? either ON or OFF
 *      valb => Use OIWFS? either ON or OFF
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDouble        (tcsDecode)      Validate an input double
 *   tcsDcLong          (tcsDecode)      Validate an input long
 *   tcsDcString        (tcsDecode)      Validate an input string
 *   tcsCsAppendMessage (tcsCadSupport)  Add string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked     (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm  (tcsConfig)      Mark record as part of a configuration
 *
 *
 *-
 */

long tcsCADaoLgsttfSource (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static int code1, code2 ;       /* Index of selected state */
  static struct ICAD_FIELD modestruct ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
/* Decode (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No PWFS1 ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->a, &code1, pcad)) break ;

     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No OIWFS ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->b, &code2, pcad)) break ;
     /* Both can't be on at the same time */
     if ((code1 == 1)&&(code2 == 1)) /* Switched ON */
     {
       tcsCsAppendMessage (pcad, "Select only 1 source");
       break;
     }

/* Set the data in the configuration block and mark this command as part
   of a configuration */
     if (tcsConfigMarkComm (pcad->name, pcad->mess)) break ;
     modestruct.val = code1 ;
     modestruct.field = 'A' ;
     strncpy(modestruct.instring, pcad->a, MAX_STRING_SIZE);

     tcsConfigSetP1LGSMode (&modestruct);

     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     tcsSetP1LGSMode(code1);
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADaoSFOLoop 
 *
 *   Purpose:
 *   Open or close the loop for the SFO
 *
 *   Description:
 *   The SFO provides slow focus adjustments from a NGS. This command
 *   opens or closes the loop to the LGS zoom corrector.
 *
 *   Invocation:
 *   tcsCADaoSFOLoop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Loop demand (OPEN, CLOSE)
 *
 *   EPICS output paramters:
 *      vala => loop demand 0 = Open, 1 = Close 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoSFOLoop (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"OPEN", "CLOSE", NULL} ;
  static int bs ;         /* Index of specified position */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No demand given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break; 

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     *(long *)pcad->vala = bs ;

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*
 *   Function name:
 *   tcsCADaoStats
 *
 *   Purpose:
 *   Implement the Altair stats command in the TCS
 *
 *   Description:
 *   The routine simply validates its inputs then performs the necessary
 *   unit conversions before outputting the data.
 *
 *   Invocation:
 *   tcsCADaoStats (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => DHS file name
 *   b => Desired number of samples 
 *   c => Desired sample rate
 *   d => Desired trigger times
 *
 *   EPICS output parameters :
 *   vala => DHS file name
 *   valb => Desired number of samples 
 *   valc => Desired sample rate
 *   vald => Desired trigger times
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcdouble        (tcsDecode)      Validate an input double 
 *   tcsCsAppendMessage (tcsCadSupport)  Append string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked     (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm  (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoStats (struct cadRecord *pcad)
 
{
  long status ;                            /* Return status */
  double sampleRate, triggerTime ;         /* Input parameter values */
  long numSamp;
 
/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
    status = CAD_ACCEPT ;

    switch (pcad->dir)
    {
 
     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* First check the DHS file name */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No DHS filename given");
       break ;
     }
/* Then check the number of samples */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No number of samples given");
       break ;
     }
     if (tcsDcLong ("Number of samples: ", pcad->b, &numSamp, pcad)) break ;
     if (numSamp < 1 )
     {
       tcsCsAppendMessage (pcad, "Number of samples out of range") ;
       break ;
     }
  
/* Then check the requested sample rate */
     if (!tcsDcLen(pcad->c)) {
       tcsCsAppendMessage (pcad, "No sample rate given");
       break ;
     }
     if (tcsDcDouble ("sample rate: ", pcad->c, &sampleRate, pcad)) break ;
     if (sampleRate < 0.0 )
     {
       tcsCsAppendMessage (pcad, "sample rate invalid") ;
       break ;
     }
 
/* Then check the trigger time, if supplied */
     if (tcsDcLen(pcad->d)) {
       if (tcsDcDouble ("sample rate: ", pcad->d, &triggerTime, pcad)) break ;
       if (triggerTime < 0.0 )
       {
         tcsCsAppendMessage (pcad, "Trigger time invalid") ;
         break ;
       }
     }
  
     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

     break ;

     case menuDirectiveSTART :
 
       strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
       strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
       strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE);
       strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE);
       break;
 
     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;
   }
 
   return status ;
}

/*+
 *   Function name:
 *   tcsCADaoTTGSLoop 
 *
 *   Purpose:
 *   Open or close the loop for the tip/tilt NGS 
 *
 *   Description:
 *   The STRAP WFS provides tip/tilt guide signals from a NGS when
 *   the LGS is operating. This command closes the STRAP loop.
 *
 *   Invocation:
 *   tcsCADaoTTGSLoop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Loop demand (OPEN, CLOSE)
 *
 *   EPICS output paramters:
 *      vala => loop demand 0 = Open, 1 = Close 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADaoTTGSLoop (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  static char *bsopts[] = {"OPEN", "CLOSE", NULL} ;
  static int bs ;         /* Index of specified position */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No demand given");
       break ;
     }  
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break; 

     status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
     if (status)
       status = CAD_REJECT ;
     else
       status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     sprintf(pcad->vala, "%d", bs);

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

epicsRegisterFunction(tcsCADaoMoveAdc);
epicsRegisterFunction(tcsCADaoMove);
epicsRegisterFunction(tcsCADaoDeployAdc);
epicsRegisterFunction(tcsCADaoPrepareCm);
epicsRegisterFunction(tcsCADaoCorrect);
epicsRegisterFunction(tcsCADaoSFOLoop);
epicsRegisterFunction(tcsCADaoBeamSplitter);
epicsRegisterFunction(tcsCADaoCentreWfs);
epicsRegisterFunction(tcsCADaoLgsttfSource);
epicsRegisterFunction(tcsCADaoLgsIris);
epicsRegisterFunction(tcsCADaoOiwfsSource);
epicsRegisterFunction(tcsCADaoGimOffsets);
epicsRegisterFunction(tcsCADaoCalMode);
epicsRegisterFunction(tcsCADaoFlexFile);
epicsRegisterFunction(tcsCADaoMechOnOff);
epicsRegisterFunction(tcsCADaoShutter);
epicsRegisterFunction(tcsCADaoNDFilter);
epicsRegisterFunction(tcsCADaoTTGSLoop);
epicsRegisterFunction(tcsCADaoMoveAStar);
epicsRegisterFunction(tcsCADaoStats);
