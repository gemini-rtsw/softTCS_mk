/*
*   FILENAME
*   tcsMechCommands.c
*
*   FUNCTION NAME(S)
*
*   tcsCADcarousel     - implement the carousel command
*   tcsCADcarouselPark - implement the carouselPark command
*   tcsCADcarouselStop - implement the carouselStop command
*   tcsCADdetSigInit   - send detSigInit command to WFS
*   tcsCADdetSigModeAo  - set parameters for AO mode
*   tcsCADdetSigModeSeq - sequence closed loop to WFS
*   tcsCADdetSigModeSeqDark - sequence dark to WFS
*   tcsCADecMechCads   - implement a general ECS mechanism command
*   tcsCADenclosurePark - implement the enclosurePark command
*   tcsCADenclosureStop - implement the enclosureStop command
*   tcsCADencThermal    - implement the encThermal command
*   tcsCADgpolPlateAngle - implement the gpolPlateAngle command
*   tcsCADgpolPlateDatum - implement the gpolPlateDatum command
*   tcsCADgpolPlateMove  - implement the gpolPlateMove command
*   tcsCADgpolPlateRotate - implement the gpolPlateRotate command
*   tcsCADgpolPlateSeq    - implement the gpolPlateSeq command
*   tcsCADm1Definition  - implement the m1definition command
*   tcsCADm1Btempset   - implements the m1tempset command
*   tcsCADm1Figure     - implement the m1Figure command
*   tcsCADm1ZeroSet       - implement the m1ZeroSet command
*   tcsCADm2Baffle        - move the M2 baffles 
*   tcsCADm2GuideControl - implements the m2GuideControl command
*   tcsCADm2Move       - implements the m2Move command
*   tcsCADmechCad      - implements general subsystem mechanism CAD from TCS
*   tcsCADmechCad20    - implements general subsystem mechanism CAD from TCS
*   tcsCADngsPark      - park the Canopus NGS probe
*   tcsCADwfsObserve   - start WFS integrating
*   tcsCADrotConfig    - configure the Cass encoders
*   tcsCADshutter      - implement the shutter command
*   tcsCADshutterPark  - implement the shutterPark command
*   tcsCADshutterStop  - implement the shutterStop command
*   tcsCADventgates    - implements the ventgates command
*   tcsCADventGatesPark - implements the ventGatesPark command
*   tcsCADventGatesStop - implements the ventGatesStop command
*   tcsCADwfsStartMeasure - implements the wfsStartMeasure command
*   tcsCADwfsStopMeasure  - implement the wfsStopMeasure command
*   tcsGpolPlates         - store the names of the GPOL plates
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsMechCommands.c,v $
 * Revision 1.23  2009/10/30 17:18:42  cjm
 * Commands for parking AOM probes
 *
 * Revision 1.22  2004/03/24 14:49:23  cjm
 * Add commands p1SigModeAo, p2SigModeAo
 *
 * Revision 1.21  2003/10/17 16:35:43  gemvx
 * Add code to handle new WFS commands
 *
 * Revision 1.20  2003/07/09 10:52:43  cjm
 * Change M1SetInit call to SetM1Zero
 *
 * Revision 1.19  2002/07/02 07:37:07  cjm
 * Add code for gpolPlateSeq command
 *
 * Revision 1.18  2002/05/10 19:56:35  cjm
 * Allow plate names in the gpolPlateMove command
 *
 * Revision 1.17  2002/04/16 15:49:08  cjm
 * Add routines to handle gpol commands
 *
 * Revision 1.16  2002/02/27 13:47:35  ptaylor
 * AO command handling moved to tcsAoCommands.c
 *
 * Revision 1.15  2001/09/02 15:13:10  cjm
 * Remove redundant comments
 *
 * Revision 1.14  2001/05/24 10:23:27  cjm
 * Use new menuDirective constants
 *
 * Revision 1.13  2000/10/11 05:33:02  cjm
 * Use revised names for baffle positions and remove start and stop of aO averaging from CAD commands
 *
 * Revision 1.12  2000/01/29 23:52:55  cjm
 * Remove wfsStartMeasure command it has been replaced by wfsStartObserve
 *
 * Revision 1.11  1999/11/27 03:39:04  cjm
 * Add wfsObserve CAD subroutine to replace the previous startMeasure command
 *
 * Revision 1.10  1999/06/16 21:27:30  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.9  1999/05/24 04:04:38  cjm
 * Add tcsCADm2Baffle subroutine
 *
 * Revision 1.8  1999/05/12 06:10:14  cjm
 * Allow carousel az demand of < 0.0
 *
 * Revision 1.7  1999/03/22 22:04:44  dlt
 * remove round (not implemented on power PC) and print longs with %ld
 *
 * Revision 1.6  1999/03/11 00:04:34  cjm
 * Add routine tcsCADm1ZeroSet
 *
 * Revision 1.5  1999/03/01 09:24:12  cjm
 * Add routine tcsCADm1Figure
 *
 * Revision 1.4  1999/02/02 04:42:04  cjm
 * Mkae aoExpTime static in wfsStartMeasure
 *
 * Revision 1.3  1999/01/05 16:56:09  epics
 * Add new routines tcsCADwfsStopMeasure and tcsCADwfsStartMeasure
 *
 * Revision 1.2  1998/12/18 09:00:44  epics
 * Change outputs for dome azimuth and shutter position to match latest capfast schematics
 *
 * Revision 1.1.1.1  1998/11/08 00:21:06  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.23  1998/06/17 16:07:31  tcs
 * Updated m2Move and m2GuideControl commands
 *
 * Revision 1.22  1998/05/19 13:51:43  cjm
 * Handle shutdown mode in encThermal command
 *
 * Revision 1.21  1998/03/31 11:23:16  cjm
 * Changes to accommodate ECS gamma release of March 98
 *
 * Revision 1.20  1998/03/25 17:10:46  cjm
 * Add support for aoCalMode, aoBeamSplitter, aoMoveAdc and aoOiwfsSource
 *
 * Revision 1.19  1998/02/12 11:34:41  cjm
 * Add routine tcsCADrotConfig
 *
 * Revision 1.18  1998/01/26 11:32:01  pbt
 * Add tcsCADenclosureDatum command
 *
 * Revision 1.17  1998/01/15 14:30:05  tcs
 * Change m2move to m2Move
 *
 * Revision 1.16  1998/01/13 11:52:13  tcs
 * Change names of CAD subroutines
 *
 * Revision 1.15  1997/12/12 08:21:31  cjm
 * Increase precision for M1 movements
 *
 * Revision 1.14  1997/12/09 08:21:56  cjm
 * Increase precision of outputs to M1 definition
 *
 * Revision 1.13  1997/11/20 12:35:44  pbt
 * Add call to tcsConfigMarkComm for *all* CADs
 *
 * Revision 1.12  1997/11/20 08:10:54  cjm
 * Upgrade m1Btempset routine to latest ICD
 *
 * Revision 1.11  1997/11/18 08:29:40  cjm
 * fix bugs and enhance m2move CAD subroutine
 *
 * Revision 1.10  1997/11/10 15:44:17  cjm
 * Add unit conversion to m1Definition command
 *
 * Revision 1.9  1997/10/06 14:23:44  cjm
 * new routine tcsEncThermal plus bug fixes to auto moves
 *
 * Revision 1.8  1997/09/24 07:16:33  cjm
 * Extra outputs for SIR items in carousel & shutter commands
 *
 * Revision 1.7  1997/09/23 11:37:47  tcs
 * Remove redundant includes
 *
 * Revision 1.6  1997/09/11 14:01:43  pbt
 * Modified tcsMechCad and tcsMechCad20 routines
 *
 * Revision 1.5  1997/07/23 13:27:56  cjm
 * Enhanced and extra routines for ECS mechanisms
 *
 * Revision 1.4  1997/06/23 15:35:21  pbt
 * Added routine tcsEcMechCads
 *
 * Revision 1.3  1997/06/04 16:56:38  pbt
 * Added routine for mechanism CAD 20 records
 *
 * Revision 1.2  1997/03/05 09:36:58  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:47  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/12/05 14:30:06  cjm
 * Bug fix to copying inputs to outputs
 *
 * Revision 1.1  1996/11/07 16:50:26  pbt
 * Mechanism control CAD subroutines
 *
 */
/* *INDENT-ON* */


#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include  <string.h>
#include  <math.h>
#include  <alarm.h>
#include  <caeventmask.h>

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
#include  "tcsEcsLib.h"
#include  "tcsOptics.h"
#include  "tcsConfig.h"

static char gpolUpperPlate[MAX_STRING_SIZE];
static char gpolMiddlePlate[MAX_STRING_SIZE];
static char gpolLowerPlate[MAX_STRING_SIZE];

typedef enum {PLATE_PARKED = 0,
              PLATE_INBEAM = 1,
              PLATE_MOVING = 2,
              PLATE_DISCONNECTED = 3,
              PLATE_BROKEN = 4,
              PLATE_INVALID = 5} PLATESTATE ;

static PLATESTATE gpolUpperPlateState = PLATE_PARKED ;
static PLATESTATE gpolMiddlePlateState = PLATE_PARKED ;
static PLATESTATE gpolLowerPlateState = PLATE_PARKED ;

/*+
 *   Function name:
 *   tcsCADcarousel
 *
 *   Purpose:
 *   Implement the TCS carousel command
 *
 *   Description:
 *   This command drives the dome to a specified azimuth. It is a low level
 *   command as normally the dome will be driven automatically as a 
 *   result of the target position specified. This command over rides
 *   these automatic demands and it will be neccessary to re-issue the 
 *   carouselMode command if automatic updates to the dome position are 
 *   required again. 
 *
 *   Invocation:
 *   tcsCADcarousel (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => demand azimuth 
 *
 *   EPICS output parameters:
 *      vala => demand dome azimuth 
 *      vald => demand azimuth for SAD
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableDome      (tcsEcsLib)    Enable/disable automatic moves 
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADcarousel (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double azDemand; /* Dome azimuth demand (degs) */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL) ;

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

      status = CAD_REJECT;

      if (tcsDcDouble ("azimuth: ", pcad->a, &azDemand, pcad))
        break;

      if (azDemand < -360.0 || azDemand > 360.0) {
        tcsCsAppendMessage (pcad, "Azimuth out of range") ;
        break ;
      }
      if (azDemand < 0.0) azDemand += 360.0 ;
  
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   status = CAD_ACCEPT;
   break ;

   case menuDirectiveSTART :
    
/* Disable the automatic sending of moves or follows when tracking a source */
 
      tcsEcsEnableDome(FALSE);

/* Trigger the ECS move_dome command */

      strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
      *(double *)pcad->vald = azDemand ;

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
 *   tcsCADcarouselPark
 *
 *   Purpose:
 *   Implement the carouselPark command
 *
 *   Description:
 *   The carouselPark command is a low level command to send just the dome
 *   to its park position. The first parameter to the command is a
 *   string that references one of a number of fixed park positions.
 *   If the string is set to "position" then a second parameter must be
 *   supplied that gives the azimuth at which the dome is to be parked.
 *
 *   Invocation:
 *   tcsCADcarouselPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Identifier for park position as a string
 *      b => Azimuth of dome (degs) if identifier is "Position"  
 *
 *   EPICS output paramters:
 *      vala => Identifier for park position as an index 
 *      valb => Azimuth of dome (degs) if identifier is "Position"
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString      (tcsDecode)      Decode a string 
 *   tcsEcsEnableDome (tcsEcsLib)      Enable/disable automatic moves
 *
 *   Deficiencies:
 *   The routine has been modified (March 98) to fit the latest ECS
 *   implementation. This now requires the TCS to map string names to
 *   an index and send the index rather than the string. It is imperative
 *   that the order and names of strings in parkopts matches the enumerated
 *   types in ecs.h.
 *-
 */

long tcsCADcarouselPark (struct cadRecord *pcad)

{

  long status ;                  /* Return status */
  static int ident ;             /* Index to string */
  double az ;                    /* Azimuth of park position (degs) */
  static char *parkopts[] = {"DEFAULT","POSITION","ACCESS1","ACCESS2","ACCESS3", NULL} ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT;

/* Pull in and validate the data on the CAD input fields */

     if(tcsDcString (parkopts, " ", pcad->a, &ident, pcad)) break ;

     if (strncmp (parkopts[ident], "POSITION", 8) == 0) {
       if (tcsDcDouble ("az: ", pcad->b, &az, pcad))
         break ;
       
       if ((az < 0.0) || (az > 360.0)) {
         tcsCsAppendMessage (pcad, "Dome az. out of range") ;
         break ;
       }
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Disable the automatic sending of moves or follows when tracking a source */

     tcsEcsEnableDome (FALSE);

/* Trigger the ECS park_dome command */

     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
     sprintf (pcad->valc, "%d", ident) ;
     *(long *)pcad->valh = pcad->dir;

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
 *   tcsCADcarouselStop
 *
 *   Purpose:
 *   Implements the carouselStop command in the TCS
 *
 *   Description:
 *   This is a simple routine to implement the TCS carouselStop command.
 *   There are no parameters, the routine simply sets the flag that 
 *   disables sending automatic moves & follows and then triggers the 
 *   ECS stop_dome command
 *
 *   Invocation:
 *   tcsCADcarouselStop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output paramters:
 *      vala => MARK directive to stop_dome 
 *      valb => START directive to stop_dome
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableDome  (tcsEcsLib)     Enable/disable automatic moves
 *
 *-
 */

long tcsCADcarouselStop (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
   break ;

   case menuDirectiveSTART :

/* Disable the automatic sending of moves or follows when tracking a source */

      tcsEcsEnableDome (FALSE) ;

/* Trigger the stop_dome command */

      *(long *)pcad->vala = menuDirectiveMARK;
      *(long *)pcad->valb = pcad->dir;

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
 *   tcsCADdetSigInit 
 *
 *   Purpose:
 *   Initialize the pwfs1, pwfs2 and oiwfs signal processing commands
 *
 *   Description:
 *   This routine initialises the signal processing modes of the WFS.
 *   Although the WFS has many parameters that are set at initialization
 *   at the TCS level the only one that can be set is the default file
 *   name for the dark/sky. If other parameters need to be changed then
 *   this must currently be done from the WFS engineering screens.
 *
 *   Invocation:
 *   tcsCADdetSigInit (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => filename of dark/sky 
 *
 *   EPICS output paramters:
 *      vala => file containing dark/sky 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADdetSigInit (struct cadRecord *pcad)

{

  long status ;             /* Return status */

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

/* Check that a filename has been given */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage(pcad, "No file specified");
     break ;
   }
      
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
 *   tcsCADdetSigModeAo 
 *
 *   Purpose:
 *   Set up AO mode parameters in the WFS
 *
 *   Description:
 *   This comamnd sets up the AO observing mode parameters in the
 *   apparopriate WFS. The parameters set are the AO coadd time
 *   and the number of sub apertures that are switched off. The
 *   TCS makes no use of this data but simply passes it on to the 
 *   WFS.
 *
 *   Invocation:
 *   tcsCADdetSigModeAo (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Interval over which to coadd data (secs)
 *      b => No. of subapertures to ignore 
 *
 *   EPICS output parameters:
 *      vala => Coadd interval (secs)
 *      valb => No. of subapertures
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADdetSigModeAo (struct cadRecord *pcad)
{
  long status ;             /* Return status */

  double aoTime ;           /* Coadd interval (secs) */
  long   numSubApps ;       /* Number of subapertures */

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
     tcsCsAppendMessage(pcad, "Coadd time missing") ;
     break ;
   }
   if (tcsDcDouble("aoTime: ", pcad->a, &aoTime, pcad)) break;

   if (aoTime < 0.005) {
     tcsCsAppendMessage (pcad, "time too short") ;
     break ;
   }

/* Check the number of sub frames */
   if (!tcsDcLen(pcad->b)) {
     tcsCsAppendMessage (pcad, "Sub apertures missing") ;
     break ;
   }
   if (tcsDcLong("sub apps: ", pcad->b, &numSubApps, pcad)) break ;

   if (numSubApps < 0 || numSubApps > 36) {
     tcsCsAppendMessage (pcad, "Subapps out of range") ;
     break ;
   }
 
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
    strcpy (pcad->vala, pcad->a) ;
    strcpy (pcad->valb, pcad->b) ;
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
 *   tcsCADdetSigModeSeq 
 *
 *   Purpose:
 *   Initiate sequence closed loop guiding in the WFS
 *
 *   Description:
 *   Sequence closed loop guiding is the main acquisition mode used
 *   by the guiders. This command provides the TCS interface to 
 *   the low level WFS commands. It only sets a small subset of
 *   the parameters that the WFS commands accept and assumes 
 *   that the default values for the other parameters are suitable.
 *   For low level engineering work it will be necessary to use the
 *   WFS comamnds directly.
 *
 *   Invocation:
 *   tcsCADdetSigModeSeq (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => period to global guide (secs)
 *      b => period to average frames (secs)
 *      c => Flag to write focus to SCS (0 or 1)
 *      d => Rms multiplier
 *
 *   EPICS output parameters:
 *      vala => period to global guide (secs)
 *      valb => period to average frames (secs)
 *      valc => Flag to write focus to SCS (0 or 1)
 *      vald => Rms multiplier
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADdetSigModeSeq (struct cadRecord *pcad)
{
  long status ;             /* Return status */

  double globalTime ;       /* Period to global guide (secs) */
  double frameTime ;        /* Period to average frames */
  long writeFocus ;         /* Flag to write focus values */
  double rmsMultiplier;     /* rms multiplier */

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
     tcsCsAppendMessage(pcad, "Global guide time missing") ;
     break ;
   }
   if (tcsDcDouble("Global guide: ", pcad->a, &globalTime, pcad)) break;

   if (globalTime < 0.0) {
     tcsCsAppendMessage (pcad, "time invalid") ;
     break ;
   }

/* Check the frame averaging time */
   if (!tcsDcLen(pcad->b)) {
     tcsCsAppendMessage (pcad, "frame time not given") ;
     break ;
   }
   if (tcsDcDouble("Frame time: ", pcad->b, &frameTime, pcad)) break ;

   if (frameTime < 0.005) {
     tcsCsAppendMessage (pcad, "Frame time out of range") ;
     break ;
   }
 
/* Check the focus flag */
   if (!tcsDcLen(pcad->c)) {
     tcsCsAppendMessage (pcad, "focus flag not given") ;
     break ;
   }
   if (tcsDcLong("Focus flag: ", pcad->c, &writeFocus, pcad)) break ;

   if (writeFocus < 0 || writeFocus > 1) {
     tcsCsAppendMessage (pcad, "Focus flag out of range") ;
     break ;
   }

/* Finally check the rms multiplier */
   if (!tcsDcLen(pcad->d)) {
     tcsCsAppendMessage (pcad, "rms multiplier missing") ;
     break ;
   }
   if (tcsDcDouble("rms: ", pcad->d, &rmsMultiplier, pcad)) break ;

   if (rmsMultiplier < 0.0) {
     tcsCsAppendMessage (pcad, "rms out of range") ;
     break ;
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
    strcpy (pcad->vala, pcad->a) ;
    strcpy (pcad->valb, pcad->b) ;
    strcpy (pcad->valc, pcad->c) ;
    strcpy (pcad->vald, pcad->d) ;
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
 *   tcsCADdetSigModeSeqDark 
 *
 *   Purpose:
 *   Take and store a dark/sky frame
 *
 *   Description:
 *   Issues a comamnd to the WFS to take a dark/sky frame. The only
 *   parameter settable from the TCS is the name of the file to 
 *   which the dark will be written. If lower level control is 
 *   needed then this must be done direct from the WFS. The routine
 *   assumes that the WFS already has defaults set up for all
 *   the other parameters.
 *
 *   Invocation:
 *   tcsCADdetSigModeSeqDark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => filename of dark/sky 
 *
 *   EPICS output paramters:
 *      vala => file containing dark/sky 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADdetSigModeSeqDark (struct cadRecord *pcad)

{

  long status ;             /* Return status */

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

/* Check that a filename has been given */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage(pcad, "No file specified");
     break ;
   }
      
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
 *   tcsCADencThermal
 *
 *   Purpose:
 *   Implements the encThermal command in the TCS
 *
 *   Description:
 *   This routine implements the TCS command encThermal. It simply checks
 *   the input parameters for validity and then passes them on to the
 *   enclosure control system.
 *
 *   Invocation:
 *   tcsCADencThermal (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Thermal control mode as a string
 *
 *   EPICS output paramters:
 *      vala => demand thermal control mode as an index 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsCsSetMessageN  (tcsCadSupport) Set message prefix
 *
 *
 *   Deficiencies:
 *   The latest ECS implementation requires an index number rather than a
 *   string for the control mode. The TCS must therefore retain the mapping
 *   between mode and index. It would be better to go back to strings. It
 *   is essential that the order of strings in thermal modes is the same
 *   as the enumerated types in ecs.h
 *
 *-
 */

long tcsCADencThermal (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char *thermalModes[] = { "PASSIVE", "ACTIVE", "SHUTDOWN", NULL} ;
  static int modeIndex ;         /* index of thermal mode */

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

/* Decode demand thermal mode */
     if (tcsDcString (thermalModes, "mode: ", pcad->a, &modeIndex, pcad)) 
       break;

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
      
   break ;

   case menuDirectiveSTART :

     sprintf (pcad->vala, "%d", modeIndex) ;

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
 *   tcsCADgpolPlateAngle
 *
 *   Purpose:
 *   Implement the gpolPlateAngle command in the TCS
 *
 *   Description:
 *   This command sets each of the specified plates to the demanded angle.
 *   GPOl itself requires angles in the range 0 to 360 but the TCS will
 *   accept -360 to +360 and map the negative numbers to the positive
 *   range. If the input field is null then no command is sent to
 *   the corresponding plate.
 *
 *   Invocation:
 *   tcsCADgpolPlateAngle (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Demand angle (degs) of the upper plate 
 *   b => Demand angle (degs) of the middle plate 
 *   c => Demand angle (degs) of the lower plate 
 *
 *   Epics outputs :
 *
 *   vale => Name of upper plate
 *   valf => Demand angle or period of the upper plate 
 *   valg => Name of middle plate
 *   valh => Demand angle or period of the middle plate 
 *   vali => Name of lower plate
 *   valj => Demand angle or period of the lower plate 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADgpolPlateAngle (struct cadRecord *pcad) 
{
   int status;
   static int moveUpper ;
   static int moveMiddle ;
   static int moveLower ;
   static double upAngle ;
   static double midAngle ;
   static double lowAngle ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode upper plate demand */
     if (tcsDcNotEmpty(pcad->a)) {
       if (tcsDcDouble ("upper : ", pcad->a, &upAngle, pcad))
         break;
       if ((upAngle < -360.0) || ( upAngle> 360.0)) {
         tcsCsAppendMessage (pcad, "upper: out of range") ;
         break ;
       }
       if (upAngle < 0.0) upAngle += 360.0 ;
       moveUpper = 1 ;
     } else {
       moveUpper = 0;
     }

/* Decode middle plate demand */
     if (tcsDcNotEmpty(pcad->b)) {
       if (tcsDcDouble ("middle : ", pcad->b, &midAngle, pcad))
         break;
       if ((midAngle < -360.0) || ( midAngle> 360.0)) {
         tcsCsAppendMessage (pcad, "middle: out of range") ;
         break ;
       }
       if (midAngle < 0.0) midAngle += 360.0 ;
       moveMiddle = 1 ;
     } else {
       moveMiddle = 0;
     }

/* Decode lower plate demand */
     if (tcsDcNotEmpty(pcad->c)) {
       if (tcsDcDouble ("lower : ", pcad->c, &lowAngle, pcad))
         break;
       if ((lowAngle < -360.0) || ( lowAngle> 360.0)) {
         tcsCsAppendMessage (pcad, "lower: out of range") ;
         break ;
       }
       if (lowAngle < 0.0) lowAngle += 360.0 ;
       moveLower = 1 ;
     } else {
       moveLower = 0;
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

    if (moveUpper) {
      strncpy(pcad->vale, gpolUpperPlate, MAX_STRING_SIZE);
      sprintf(pcad->valf,"%.2f", upAngle) ;
    } else {
      strncpy(pcad->vale, "", MAX_STRING_SIZE);
      strncpy(pcad->valf, "", MAX_STRING_SIZE);
    }
    if (moveMiddle) {
      strncpy(pcad->valg, gpolMiddlePlate, MAX_STRING_SIZE);
      sprintf(pcad->valh,"%.2f", midAngle) ;
    } else {
      strncpy(pcad->valg, "", MAX_STRING_SIZE);
      strncpy(pcad->valh, "", MAX_STRING_SIZE);
    }
    if (moveLower) {
      strncpy(pcad->vali, gpolLowerPlate, MAX_STRING_SIZE);
      sprintf(pcad->valj,"%.2f", lowAngle) ;
    } else {
      strncpy(pcad->vali, "", MAX_STRING_SIZE);
      strncpy(pcad->valj, "", MAX_STRING_SIZE);
    }
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
 *   tcsCADgpolPlateDatum
 *
 *   Purpose:
 *   Datum selected GPOL plates 
 *
 *   Description:
 *   This command will drive the specified GPOL plates to their home or
 *   datum positions. Only those plates specified are datumed.
 *
 *   Invocation:
 *   tcsCADgpolPlateDatum (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Datum request for upper plate 
 *   b => Datum request for middle plate 
 *   c => Datum request for lower plate 
 *
 *   Epics outputs :
 *
 *   vale => Name of upper plate to datum 
 *   valf => Name of middle plate to datum 
 *   valg => Name of lower plate to datum 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADgpolPlateDatum (struct cadRecord *pcad) 
{
   int status;

   static char *datumOpts[] = {"NO", "YES", NULL} ;
   int datum ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode upper carriage demand */
   if (tcsDcString (datumOpts, " ", pcad->a, &datum, pcad)) break ;

   if (datum) 
     strncpy(pcad->vale, gpolUpperPlate, MAX_STRING_SIZE) ;
   else
     strncpy(pcad->vale, "", MAX_STRING_SIZE);

/* Decode middle plate demand */
   if (tcsDcString (datumOpts, " ", pcad->b, &datum, pcad)) break ;

   if (datum) 
     strncpy(pcad->valf, gpolMiddlePlate, MAX_STRING_SIZE) ;
   else
     strncpy(pcad->valf, "", MAX_STRING_SIZE);

/* Decode lower plate demand */
   if (tcsDcString (datumOpts, " ", pcad->c, &datum, pcad)) break ;

   if (datum) 
     strncpy(pcad->valg, gpolLowerPlate, MAX_STRING_SIZE) ;
   else
     strncpy(pcad->valg, "", MAX_STRING_SIZE);


     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :


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
 *   tcsCADgpolPlateMove
 *
 *   Purpose:
 *   Move the GPOL plates in or out
 *
 *   Description:
 *   This command will drive the GPOL carriages either into the beam or out to
 *   their parked position. Due to the operation of the GPOL interface
 *   it checks the current state of the carriages and only drives them
 *   if a change is needed. At present no attempt is made to check
 *   whether the plates are in an error state, GPOL isn't loaded etc. The
 *   command is sent anyway.
 *
 *   Invocation:
 *   tcsCADgpolPlateMove (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Demand position of the upper carriage 
 *   b => Demand position of the middle carriage 
 *   c => Demand position of the lower carriage 
 *
 *   Epics outputs :
 *
 *   vala => flag to control if a platePark command is sent
 *   valb => flag to control if a plateBeam command is sent
 *   valc => Name of upper plate to park
 *   vald => Name of middle plate to park
 *   vale => Name of lower plate to park
 *   valf => Name of upper plate to insert 
 *   valg => Name of middle plate to insert 
 *   valh => Name of lower plate to insert 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADgpolPlateMove (struct cadRecord *pcad) 
{
   int status;

   static long issueBeam ; 
   static long issuePark ;
   static char *posnOpts[] = {"IN", "OUT", "PLATENAME", "INBEAM", "PARKED",
                               NULL} ;
   int posn ;
   char ucPlateName[MAX_STRING_SIZE];
   int ls ;                             /* Length of string */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;
   issueBeam = 0 ;
   issuePark = 0 ;

/* Decode upper carriage demand */

   ls = tcsDcLen(gpolUpperPlate);
   posnOpts[2] = tcsDcUc(gpolUpperPlate, ls + 1, ucPlateName) ;

   if (tcsDcString (posnOpts, " ", pcad->a, &posn, pcad)) break ;

/* Map alternative names to standard positions */
   if (posn == 2) posn = 0 ;
   if (posn > 2)  posn -= 3 ;

   if (posn == 0 && gpolUpperPlateState != PLATE_INBEAM) {
     issueBeam = 1 ;
     strncpy (pcad->valc, "", MAX_STRING_SIZE) ;
     strncpy (pcad->valf, gpolUpperPlate, MAX_STRING_SIZE) ;
   } else if (posn == 1 && gpolUpperPlateState != PLATE_PARKED) {
     issuePark = 1 ;
     strncpy (pcad->valc, gpolUpperPlate, MAX_STRING_SIZE) ;
     strncpy (pcad->valf, "", MAX_STRING_SIZE) ;
   }

/* Decode middle plate demand */

   ls = tcsDcLen(gpolMiddlePlate);
   posnOpts[2] = tcsDcUc(gpolMiddlePlate, ls + 1, ucPlateName) ;

   if (tcsDcString (posnOpts, " ", pcad->b, &posn, pcad)) break ;

   if (posn == 2) posn = 0 ;
   if (posn > 2)  posn -= 3 ;

   if (posn == 0 && gpolMiddlePlateState != PLATE_INBEAM) {
     issueBeam = 1 ;
     strncpy (pcad->vald, "", MAX_STRING_SIZE) ;
     strncpy (pcad->valg, gpolMiddlePlate, MAX_STRING_SIZE) ;
   } else if (posn == 1 && gpolMiddlePlateState != PLATE_PARKED) {
     issuePark = 1 ;
     strncpy (pcad->vald, gpolMiddlePlate, MAX_STRING_SIZE) ;
     strncpy (pcad->valg, "", MAX_STRING_SIZE) ;
   }

/* Decode lower plate demand */

   ls = tcsDcLen(gpolLowerPlate);
   posnOpts[2] = tcsDcUc(gpolLowerPlate, ls + 1, ucPlateName) ;

   if (tcsDcString (posnOpts, " ", pcad->c, &posn, pcad)) break ;

   if (posn == 2) posn = 0;
   if (posn > 2)  posn -= 3 ;

   if (posn == 0 && gpolLowerPlateState != PLATE_INBEAM) {
     issueBeam = 1 ;
     strncpy (pcad->vale, "", MAX_STRING_SIZE) ;
     strncpy (pcad->valh, gpolLowerPlate, MAX_STRING_SIZE) ;
   } else if (posn == 1 && gpolLowerPlateState != PLATE_PARKED) {
     issuePark = 1 ;
     strncpy (pcad->vale, gpolLowerPlate, MAX_STRING_SIZE) ;
     strncpy (pcad->valh, "", MAX_STRING_SIZE) ;
   }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

    *(long *)pcad->vala = issuePark ;
    *(long *)pcad->valb = issueBeam ;

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
 *   tcsCADgpolPlateRotate
 *
 *   Purpose:
 *   Implement the gpolPlateRotate command in the TCS
 *
 *   Description:
 *   This command sets each of the specified plates to the specified period.
 *   If the input field is null then no command is sent to
 *   the corresponding plate.
 *
 *   Invocation:
 *   tcsCADgpolPlateRotate (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Demand period (secs) of the upper plate 
 *   b => Demand period (secs) of the middle plate 
 *   c => Demand period (secs) of the lower plate 
 *
 *   Epics outputs :
 *
 *   vale => Name of upper plate
 *   valf => Demand period of the upper plate 
 *   valg => Name of middle plate
 *   valh => Demand period of the middle plate 
 *   vali => Name of lower plate
 *   valj => Demand period of the lower plate 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

#define PLATE_MAX_PERIOD 40.0
#define PLATE_MIN_PERIOD 4.0

long tcsCADgpolPlateRotate (struct cadRecord *pcad) 
{
   int status;
   static int moveUpper ;
   static int moveMiddle ;
   static int moveLower ;
   static double upPeriod ;
   static double midPeriod ;
   static double lowPeriod ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode upper plate demand */
     if (tcsDcNotEmpty(pcad->a)) {
       if (tcsDcDouble ("upper : ", pcad->a, &upPeriod, pcad))
         break;
       if ((upPeriod < PLATE_MIN_PERIOD) || ( upPeriod > PLATE_MAX_PERIOD)) {
         tcsCsAppendMessage (pcad, "upper: out of range") ;
         break ;
       }
       moveUpper = 1 ;
     } else {
       moveUpper = 0;
     }

/* Decode middle plate demand */
     if (tcsDcNotEmpty(pcad->b)) {
       if (tcsDcDouble ("middle : ", pcad->b, &midPeriod, pcad))
         break;
       if ((midPeriod < PLATE_MIN_PERIOD) || (midPeriod > PLATE_MAX_PERIOD)) {
         tcsCsAppendMessage (pcad, "middle: out of range") ;
         break ;
       }
       moveMiddle = 1 ;
     } else {
       moveMiddle = 0;
     }

/* Decode lower plate demand */
     if (tcsDcNotEmpty(pcad->c)) {
       if (tcsDcDouble ("lower : ", pcad->c, &lowPeriod, pcad))
         break;
       if ((lowPeriod < PLATE_MIN_PERIOD) || (lowPeriod > PLATE_MAX_PERIOD)) {
         tcsCsAppendMessage (pcad, "lower: out of range") ;
         break ;
       }
       moveLower = 1 ;
     } else {
       moveLower = 0;
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

    if (moveUpper) {
      strncpy(pcad->vale, gpolUpperPlate, MAX_STRING_SIZE);
      strncpy(pcad->valf, pcad->a, MAX_STRING_SIZE);
    } else {
      strncpy(pcad->vale, "", MAX_STRING_SIZE);
      strncpy(pcad->valf, "", MAX_STRING_SIZE);
    }
    if (moveMiddle) {
      strncpy(pcad->valg, gpolMiddlePlate, MAX_STRING_SIZE);
      strncpy(pcad->valh, pcad->b, MAX_STRING_SIZE);
    } else {
      strncpy(pcad->valg, "", MAX_STRING_SIZE);
      strncpy(pcad->valh, "", MAX_STRING_SIZE);
    }
    if (moveLower) {
      strncpy(pcad->vali, gpolLowerPlate, MAX_STRING_SIZE);
      strncpy(pcad->valj, pcad->c, MAX_STRING_SIZE);
    } else {
      strncpy(pcad->vali, "", MAX_STRING_SIZE);
      strncpy(pcad->valj, "", MAX_STRING_SIZE);
    }
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
 *   tcsCADgpolPlateSeq
 *
 *   Purpose:
 *   Move the GPOL plates via GPOL sequencer 
 *
 *   Description:
 *   This command drives the GPOL wave plates via the GPOL sequencer. It is
 *   an alternative to the gpolPlateMove and gpolPlateAngle commands but
 *   does not have the restriction that you can't move a plate in and one
 *   out in the same command. It also allows you to specify a particular
 *   angle at the same time as driving the plates.
 *
 *   Invocation:
 *   tcsCADgpolPlateSeq (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Demand position of the upper carriage 
 *   b => Demand angle of upper plate
 *   c => Demand position of the middle carriage 
 *   d => Demand angle of middle plate
 *   e => Demand position of the lower carriage 
 *   f => Demand angle of lower plate
 *
 *   Epics outputs :
 *
 *   vala => Demand position of the upper carriage 
 *   valb => Demand angle of upper plate
 *   valc => Demand position of the middle carriage 
 *   vald => Demand angle of middle plate
 *   vale => Demand position of the lower carriage 
 *   valf => Demand angle of lower plate
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADgpolPlateSeq (struct cadRecord *pcad) 
{
   int status;

   static char *posnOpts[] = {"IN", "OUT", "INBEAM", "PARKED",
                               NULL} ;
   int posn ;
   static int moveUpper ;
   static int moveMiddle ;
   static int moveLower ;
   static double upAngle ;
   static double midAngle ;
   static double lowAngle ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode upper carriage demand */

   if (pcad->a[0]) {
     if (tcsDcString (posnOpts, " ", pcad->a, &posn, pcad)) break ;

/* Map alternative names to standard positions */
     if (posn < 2)  posn += 2 ;
     strcpy (pcad->vala, posnOpts[posn]) ;

   } 
     
   if (tcsDcNotEmpty(pcad->b)) {
     if (tcsDcDouble ("upper : ", pcad->b, &upAngle, pcad))
       break;
     if ((upAngle < -360.0) || ( upAngle> 360.0)) {
       tcsCsAppendMessage (pcad, "upper: out of range") ;
       break ;
     }
     if (upAngle < 0.0) upAngle += 360.0 ;
     moveUpper = 1 ;
   } else {
     moveUpper = 0;
   }

/* Decode middle plate demand */

   if (pcad->c[0]) {
     if (tcsDcString (posnOpts, " ", pcad->c, &posn, pcad)) break ;

     if (posn < 2)  posn += 2 ;
     strcpy (pcad->valc, posnOpts[posn]) ;
   }

   if (tcsDcNotEmpty(pcad->d)) {
     if (tcsDcDouble ("middle : ", pcad->d, &midAngle, pcad))
       break;
     if ((midAngle < -360.0) || ( midAngle> 360.0)) {
       tcsCsAppendMessage (pcad, "middle: out of range") ;
       break ;
     }
     if (midAngle < 0.0) midAngle += 360.0 ;
     moveMiddle = 1 ;
   } else {
     moveMiddle = 0;
   }

/* Decode lower plate demand */
   if (pcad->e[0]) {
     if (tcsDcString (posnOpts, " ", pcad->e, &posn, pcad)) break ;

     if (posn < 2)  posn += 2 ;
     strcpy (pcad->vale, posnOpts[posn]) ;
   }

   if (tcsDcNotEmpty(pcad->f)) {
     if (tcsDcDouble ("lower: ", pcad->f, &lowAngle, pcad))
       break;
     if ((lowAngle < -360.0) || ( lowAngle> 360.0)) {
       tcsCsAppendMessage (pcad, "lower: out of range") ;
       break ;
     }
     if (lowAngle < 0.0) lowAngle += 360.0 ;
     moveLower = 1 ;
   } else {
     moveLower = 0;
   }

   if (tcsConfigMarkComm(pcad->name, pcad->mess))
     break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

    if (moveUpper) {
      sprintf(pcad->valb,"%.2f", upAngle) ;
    } else {
      strncpy(pcad->valb, "", MAX_STRING_SIZE);
    }
    if (moveMiddle) {
      sprintf(pcad->vald,"%.2f", midAngle) ;
    } else {
      strncpy(pcad->vald, "", MAX_STRING_SIZE);
    }
    if (moveLower) {
      sprintf(pcad->valf,"%.2f", lowAngle) ;
    } else {
      strncpy(pcad->valf, "", MAX_STRING_SIZE);
    }

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
 *   tcsCADngsPark 
 *
 *   Purpose:
 *   Park a Canopus NGS probe
 *
 *   Description:
 *   Executes the Canopus (AOM) probe control command with a value
 *   of PARK.
 *
 *   Invocation:
 *   tcsCADngsPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      t => Dummy parameter simply to mark the command 
 *
 *   EPICS output paramters:
 *      vala => PARK 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADngsPark (struct cadRecord *pcad)

{

  long status ;             /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    strncpy (pcad->vala, "PARK", MAX_STRING_SIZE) ;

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
 *   tcsCADm1Btempset
 *
 *   Purpose:
 *   Implement the m1Btempset command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. No range checking is done on the data. Once validated, the 
 *   inputs are copied to the outputs for onward transmission to M1. 
 *
 *   Invocation:
 *   tcsCADm1Btempset (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs :
 *   
 *   a => Bulk temperature demand (deg C)
 *   b => Offset to be applied when surface heating is on (deg C)
 *   c => Offset to be applied when surface heating is off (deg C)
 *   d => Offset to generate surface heating demand temperature (deg C)
 *
 *   Epics outputs :
 *
 *   vala => Bulk temperature demand (deg C)
 *   valb => Offset to be applied when surface heating is on (deg C)
 *   valc => Offset to be applied when surface heating is off (deg C)
 *   vald => Offset to generate surface heating demand temperature (deg C)
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsCADm1Btempset (struct cadRecord *pcad) 
{
   int status;
   double temp ;            /* Bulk temperature demand (deg C) */
   double tempOffset ;       /* Offset temperature demand (deg C) */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode target temperature */
     if (tcsDcDouble ("Bulk temp : ", pcad->a, &temp, pcad))
       break;

/* Decode offset temperatures */
     if (tcsDcDouble ("Offset temp : ", pcad->b, &tempOffset, pcad))
       break;

     if (tcsDcDouble ("Offset temp : ", pcad->c, &tempOffset, pcad))
       break;

     if (tcsDcDouble ("Offset temp : ", pcad->d, &tempOffset, pcad))
       break;

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

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
 *   tcsCADm1Definition
 *
 *   Purpose:
 *   Implement the m1Definition command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid 
 *   numbers. No range checking is done on the data. Those parameters
 *   that define rotations are converted from arcsec to millirads and
 *   sent on to the M1 control system.
 *
 *   Invocation:
 *   tcsCADm1Definition (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *   History:
 *   7-Nov-97 CJM  Initial version
 *-
 */

long tcsCADm1Definition (struct cadRecord *pcad) 
{
   int status;
   double dummy;   /* Temporary variable */
   static double xrot, yrot, zrot ;   /* Requested rotations */
   double factor ;                    /* Convert arcsec to millirads */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode X rotation */
     if (tcsDcDouble ("X rotn: ", pcad->a, &xrot, pcad))
       break;

/* Decode Y rotation */
     if (tcsDcDouble ("Y rotn: ", pcad->b, &yrot, pcad))
       break;

/* Decode Z rotation */
     if (tcsDcDouble ("Z rotn: ", pcad->c, &zrot, pcad))
       break;

/* Decode X displacement  */
     if (tcsDcDouble ("X offset: ", pcad->d, &dummy, pcad))
       break;

/* Decode Y displacement  */
     if (tcsDcDouble ("Y offset: ", pcad->e, &dummy, pcad))
       break;

/* Decode Z displacement  */
     if (tcsDcDouble ("Z offset: ", pcad->f, &dummy, pcad))
       break;

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Convert the rotations from arcsec to millirads */
     factor = AS2R * 1000.0 ;
     xrot *= factor ;
     yrot *= factor ;
     zrot *= factor;

/* Copy over the parameters for the subsystem CAD */

    sprintf (pcad->vala, "%f.15", xrot) ;
    sprintf (pcad->valb, "%f.15", yrot) ;
    sprintf (pcad->valc, "%f.15", zrot) ;
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
 *   tcsCADm1Figure 
 *
 *   Purpose:
 *   Implement the m1Figure command
 *
 *   Description:
 *   This routine implements the m1Figure command in the TCS. It does
 *   no checking of the input parameters but simplu passes them on to
 *   the M1 system. It implements "clear" in the same way as the PCS
 *   i.e. sets both its input and outputs to zero by calling
 *   db_post_events. This is done only because of the large number of
 *   input parameters and to match the PCS.
 *
 *   Invocation:
 *   tcsCADm1Figure (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Zernike coefficient Z4
 *
 *   EPICS output paramters:
 *      vala => Zernike coefficient Z4
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   Deficiencies:
 *   The routine uses the clear directive to reset its inputs
 *
 *-
 */

long tcsCADm1Figure (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char *cptr ;            /* Pointer to character strings */
  int i ;                 /* loop index */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;

   break ;

   case menuDirectiveSTART :

     strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
     strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
     strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
     strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
     strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
     strncpy(pcad->valh, pcad->h, MAX_STRING_SIZE) ;
     strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
     strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;
     strncpy(pcad->valk, pcad->k, MAX_STRING_SIZE) ;
     strncpy(pcad->vall, pcad->l, MAX_STRING_SIZE) ;
     strncpy(pcad->valm, pcad->m, MAX_STRING_SIZE) ;
     strncpy(pcad->valn, pcad->n, MAX_STRING_SIZE) ;

     break ;

   case menuDirectiveMARK :
     break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :

     cptr = pcad->a;
     for (i = 0; i < 14; i++, cptr +=MAX_STRING_SIZE) {
       strcpy (cptr, "0.0") ;
       db_post_events(pcad, cptr, DBE_VALUE);
     }
     strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
     strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
     strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
     strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
     strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
     strncpy(pcad->valh, pcad->h, MAX_STRING_SIZE) ;
     strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
     strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;
     strncpy(pcad->valk, pcad->k, MAX_STRING_SIZE) ;
     strncpy(pcad->vall, pcad->l, MAX_STRING_SIZE) ;
     strncpy(pcad->valm, pcad->m, MAX_STRING_SIZE) ;
     strncpy(pcad->valn, pcad->n, MAX_STRING_SIZE) ;
   break ;

  }

  return status ;
}


/*+
 *   Function name:
 *   tcsCADm2Baffle 
 *
 *   Purpose:
 *   Implement the m2Baffle command
 *
 *   Description:
 *   The routine checks the input parameters for the m2Baffle command then
 *   triggers the moveBaffle command in the SCS
 *
 *   Invocation:
 *   tcsCADm2Baffle (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Deployable baffle position 
 *      b => Central baffle position
 *
 *   EPICS output paramters:
 *      vala => Demanded M2 deployable baffle position 
 *      valb => Demanded M2 central baffle position
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm2Baffle (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int deployIndex ; /* Index to deployable baffle */
  static int cenIndex ;    /* Index to central baffle position */
  static char *deployOpts[] = {"RETRACTED", "NEAR IR", "VISIBLE", "EXTENDED", 
                                NULL } ;
  static char *centralOpts[] = {"CLOSED", "OPEN", NULL} ;

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

   if (tcsDcString (deployOpts, " ", pcad->a, &deployIndex, pcad)) break ;
   if (tcsDcString (centralOpts, " ", pcad->b, &cenIndex, pcad)) break ;

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
 *   tcsCADm2GuideControl 
 *
 *   Purpose:
 *   Implements the m2GuideControl command in the TCS
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links. The only input is the desired guiding state of
 *   M2 which is either "On" or "Off" (case is unimportant). If the 
 *   guiding state is set to On then M2 will respond to any valid guiding
 *   data sent on the synchro bus using the configuration set with the
 *   m2GuideConfig command.
 *
 *   Invocation:
 *   tcsCADm2GuideControl (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Desired guiding state of M2 "On" or "Off" 
 *
 *   EPICS output paramters:
 *      vala => demand guiding state "On" or "Off" 
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

long tcsCADm2GuideControl (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *gOpts[] = {"OFF", "ON", NULL} ;
  int gs ;                /* Index of selected guide state */

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
     if (tcsDcString (gOpts, " ", pcad->a, &gs, pcad)) break ;

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
 *   tcsCADm2Move
 *
 *   Purpose:
 *   Implement the m2Move command in the TCS
 *
 *   Description:
 *   The routine reads the Cad inputs and checks that they are valid. 
 *   The position demands are converted to microns
 *   before passing to the subsystem. If the tilts for the B and C
 *   tilts are null then the A beam demands are used instead.
 *
 *   Invocation:
 *   tcsCADm2Move (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics input parameters:
 *
 *   a => A beam X tilt (arcsec)
 *   b => A beam Y tilt (arcsec)
 *   c => B beam X tilt (arcsec)
 *   d => B beam Y tilt (arcsec)
 *   e => C beam X tilt (arcsec)
 *   f => C beam Y tilt (arcsec)
 *   g => X position (mm)
 *   h => Y position (mm)
 *   i => Z position (mm)
 *
 *   Epics output parameters:
 *
 *   vala => A beam X tilt (arcsec)
 *   valb => A beam Y tilt (arcsec)
 *   valc => B beam X tilt (arcsec)
 *   vald => B beam Y tilt (arcsec)
 *   vale => C beam X tilt (arcsec)
 *   valf => C beam Y tilt (arcsec)
 *   valg => X position (microns)
 *   valh => Y position (microns)
 *   vali => Z position (microns)
 *
 *   Function value:
 *   Return status
 *
 *   Deficiencies;
 *   The limits used to check the input data are hard coded. They should
 *   ideally be obtained from the SCS.
 *
 *   History:
 *   14-Nov-97 CJM  Initial version
 *-
 */

long tcsCADm2Move (struct cadRecord *pcad) 
{
   int status;
   static double xrotA, yrotA ;   /* Requested rotations */
   static double xrotB, yrotB ;   /* Requested rotations */
   static double xrotC, yrotC ;   /* Requested rotations */
   static double xpos, ypos, zpos ; /* Requested positions */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = CAD_REJECT;

/* Decode X rotation */
     if (pcad->a[0]) {
       if (tcsDcDouble ("X tilt A: ", pcad->a, &xrotA, pcad))
         break;
     } else {
       tcsCsAppendMessage (pcad, "Beam A X tilt mandatory");
       break ;
     }

/* Decode Y rotation */
     if (pcad->b[0]) {
       if (tcsDcDouble ("Y tilt A: ", pcad->b, &yrotA, pcad))
         break;
     } else {
       tcsCsAppendMessage (pcad, "Beam A Y tilt mandatory");
       break ;
     }

/* Decode X rotation */
     if (pcad->c[0]) {
       if (tcsDcDouble ("X tilt B: ", pcad->c, &xrotB, pcad))
         break;
     } else {
       xrotB = xrotA ;
       strncpy (pcad->c, pcad->a, MAX_STRING_SIZE) ;
     }

/* Decode Y rotation */
     if (pcad->d[0]) {
       if (tcsDcDouble ("Y tilt B: ", pcad->d, &yrotB, pcad))
         break;
     } else {
       yrotB = yrotA ;
       strncpy (pcad->d, pcad->b, MAX_STRING_SIZE) ;
     }

/* Decode X rotation */
     if (pcad->e[0]) {
       if (tcsDcDouble ("X tilt C: ", pcad->e, &xrotC, pcad))
         break;
     } else {
       xrotC = xrotA ;
       strncpy (pcad->e, pcad->a, MAX_STRING_SIZE) ;
     }

/* Decode Y rotation */
     if (pcad->f[0]) {
       if (tcsDcDouble ("Y tilt C: ", pcad->f, &yrotC, pcad))
         break;
     } else {
       yrotC = yrotA ;
       strncpy (pcad->f, pcad->b, MAX_STRING_SIZE);
     }

/* Decode X displacement  */
     if (pcad->g[0]) {
       if (tcsDcDouble ("X offset: ", pcad->g, &xpos, pcad))
         break;
       if (xpos < -M2XLIMIT || xpos > M2XLIMIT) {
         tcsCsAppendMessage (pcad, "X limit exceeded");
         break ;
       }
     } else {
       tcsCsAppendMessage (pcad, "X demand mandatory");
       break ;
     }

      
/* Decode Y displacement  */
     if (pcad->h[0]) {
       if (tcsDcDouble ("Y offset: ", pcad->h, &ypos, pcad))
         break;

       if (ypos < -M2YLIMIT || ypos > M2YLIMIT) {
         tcsCsAppendMessage (pcad, "Y limit exceeded");
         break ;
       }
     
     } else {
       tcsCsAppendMessage (pcad, "Y demand mandatory");
       break ;
     }
      
/* Decode Z displacement  */
     if (pcad->i[0]) {
       if (tcsDcDouble ("Z offset: ", pcad->i, &zpos, pcad))
         break;
     } else {
       tcsCsAppendMessage (pcad, "Z demand mandatory");
       break ;
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess))
       break;

   status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

/* Convert the positions to microns */

   xpos *= 1000.0;
   ypos *= 1000.0;
   zpos *= 1000.0;

/* Copy over the parameters for the subsystem CAD */

    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
    strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
    strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
    sprintf (pcad->valg, "%.2f", xpos) ;
    sprintf (pcad->valh, "%.2f", ypos) ;
    sprintf (pcad->vali, "%.2f", zpos) ;
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
 *   tcsCADmechCad
 *
 *   Purpose:
 *  
 *   Implements general subsystem mechanism CAD command from TCS
 *
 *   Description:
 *
 *    General puprose subroutine to implement a subsystem CAD being
 *    triggered from a TCS CAD> The input strings are simply copied
 *    to the output strings and a MARK & START directive is output to the
 *    subsystem CAD via STLK.
 *
 *   Invocation:
 *    tcsCADmechCad (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *
 *   History:
 *   4-Nov-96 PBT  Initial version
 *  10-Sep-97 PBT  Amended to change order of parameters/directive outputs
 *-
 */

long tcsCADmechCad (struct cadRecord *pcad) 
{
   int status;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_REJECT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

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
   status = CAD_ACCEPT;
   break ;

   case menuDirectiveSTOP : 
   status = CAD_ACCEPT;
   break ;

   case menuDirectiveCLEAR :
   status = CAD_ACCEPT;
   break ;

  }
  
  return(status) ;

}

/*+
 *   Function name:
 *   tcsCADenclosurePark
 *
 *   Purpose:
 *   Implements the enclosurePark command in the TCS
 *
 *   Description:
 *   This routine is almost null as there are no parameters to this command.
 *   It is only necessary to disable sending any automatic moves to the 
 *   dome and shutters
 *
 *   Invocation:
 *   tcsCADenclosurePark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableDome  (tcsEcsLib)     Enable/disable automatic moves
 *   tcsEcsEnableShtrs (tcsEcsLib)     Enable/disable automatic moves
 *-
 */

long tcsCADenclosurePark (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
   break ;

   case menuDirectiveSTART :

     tcsEcsEnableDome (FALSE) ;
     tcsEcsEnableShtrs (FALSE) ;

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
 *   tcsCADenclosureStop
 *
 *   Purpose:
 *   Implements the enclosureStop command in the TCS
 *
 *   Description:
 *   This routine is almost null as there are no parameters to this command.
 *   The real work is done by the capfast schematic to which this routine
 *   is attached. The purpose of the enclosureStop command is to provide
 *   a single command at the TCS level that can stop the dome, shutters
 *   and vent gates. This is achieved by fanning out the mark and
 *   start directives to the ECS commands stop_dome, stop_shtrs and
 *   stop_vgates. This occurs when the start link of the enclosureStop
 *   CAD to which this routine is tied is fired off.
 *
 *   Invocation:
 *   tcsCADenclosureStop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableDome  (tcsEcsLib)     Enable/disable automatic moves
 *   tcsEcsEnableShtrs (tcsEcsLib)     Enable/disable automatic moves
 *-
 */

long tcsCADenclosureStop (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Make sure that any automatic move commands to the enclosure are disabled */

     tcsEcsEnableDome (FALSE) ;
     tcsEcsEnableShtrs (FALSE) ;

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
 *   tcsCADenclosureDatum
 *
 *   Purpose:
 *   Implements the enclosureDatum command in the TCS
 *
 *   Description:
 *   This routine is almost null as there are no parameters to this command.
 *   It is similar to the enclosureStop command but in this case the
 *   capfast schematic simply triggers a datum command in the enclosure
 *   subsystem
 *
 *   Invocation:
 *   tcsCADenclosureDatum (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableDome  (tcsEcsLib)     Enable/disable automatic moves
 *   tcsEcsEnableShtrs (tcsEcsLib)     Enable/disable automatic moves
 *-
 */

long tcsCADenclosureDatum (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Make sure that any automatic move commands to the enclosure are disabled */

     tcsEcsEnableDome (FALSE) ;
     tcsEcsEnableShtrs (FALSE) ;

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
 *   tcsCADmechCad20
 *
 *   Purpose:
 *  
 *   Implements general subsystem mechanism CAD command from TCS
 *    for case with 20 CAD parameters
 *
 *   Description:
 *
 *    General purpose subroutine to implement a subsystem CAD being
 *    triggered from a TCS CAD. The input strings are simply copied
 *    to the output strings and a MARK & START directive is output to the
 *    subsystem CAD via STLK.
 *
 *   Invocation:
 *    tcsCADmechCad20 (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *
 *   History:
 *   2-Jun-97 PBT  Initial version, adapted from tcsMechCad
 *  10-Sep-97 PBT  Amended to change order of parameters/directive outputs
 *-
 */

long tcsCADmechCad20 (struct cadRecord *pcad) 
{
   int status;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
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
  strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
  strncpy(pcad->valh, pcad->h, MAX_STRING_SIZE) ;
  strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
  strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;
  strncpy(pcad->valk, pcad->k, MAX_STRING_SIZE) ;
  strncpy(pcad->vall, pcad->l, MAX_STRING_SIZE) ;
  strncpy(pcad->valm, pcad->m, MAX_STRING_SIZE) ;
  strncpy(pcad->valn, pcad->n, MAX_STRING_SIZE) ;
  strncpy(pcad->valo, pcad->o, MAX_STRING_SIZE) ;
  strncpy(pcad->valp, pcad->p, MAX_STRING_SIZE) ;
  strncpy(pcad->valq, pcad->q, MAX_STRING_SIZE) ;
  strncpy(pcad->valr, pcad->r, MAX_STRING_SIZE) ;
  strncpy(pcad->vals, pcad->s, MAX_STRING_SIZE) ;
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
 *   tcsCADwfsObserve 
 *
 *   Purpose:
 *   Implement the pwfs1, pwfs2 and oiwfs Observe commands
 *
 *   Description:
 *   Prior to the split of the WFS into separate crates the functionality
 *   of this command was implemented by wfsStartMeasure. The routine
 *   checks the input data for validity and then stores the exposure time.
 *   The checked data is then forwarded to the relevant WFS.
 *
 *   Invocation:
 *   tcsCADwfsObserve (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => No. of exposures (-1 = continuous)
 *      b => Exposure time (secs)
 *      c => Output option (None | DHS | File)
 *      d => DHS label 
 *      e => DHS output (Perm | Temp | QL)
 *      f => Path for datafiles
 *      g => Output file name
 *
 *   EPICS output paramters:
 *      vala => No. of exposures
 *      valb => Exposure time
 *      valc => Index to output option (0 | 1 | 2)
 *      vald => DHS label
 *      vale => Index to DHS output (0 | 1 | 2)
 *      valf => Path for datafiles
 *      valg => Output file name
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetAoExpTime  (tcsOptics) Save aO exposure time
 *
 *-
 */

long tcsCADwfsObserve (struct cadRecord *pcad)

{

  long status ;             /* Return status */
  double expTime ;          /* Exposure time (secs) */
  long numExp ;             /* Number of exposures */
  char *outOpts[] = {"NONE", "DHS", "FILE", NULL } ;
  char *dhsOpts[] = {"PERM", "TEMP", "QL", NULL} ;
  static int outIndex ;     /* Index to output option */
  static int dhsIndex ;     /* Index to dhs option */
  static char dhsLabel[MAX_STRING_SIZE] ;
  static char filePath[MAX_STRING_SIZE] ;
  static char fileName[MAX_STRING_SIZE] ;
  char *cadName ;           /* Name of cad record */

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

/* Number of exposures must be present */
   if (!tcsDcLen(pcad->a)) {
     tcsCsAppendMessage (pcad, "No. of exposures missing") ;
     break ;
   } else {
     if (tcsDcLong ("n-exp: ", pcad->a, &numExp, pcad))
       break ;
     if (numExp < -1 ) {
       tcsCsAppendMessage (pcad, "No. of exposures < -1") ;
       break ;
     } 
   }

/* Exposure time must be present */
   if (!tcsDcLen(pcad->b)) {
     tcsCsAppendMessage (pcad, "no exposure time") ;
     break ;
   } else {
    if (tcsDcDouble ("t-exp: ", pcad->b, &expTime, pcad)) break ;
    if (expTime < 0.005 || expTime > 10000.0) {
      tcsCsAppendMessage (pcad, "Exposure time out of range") ;
      break ;
    }
   }

/* Provide a default if the output option isn't specified */
   if (!tcsDcLen(pcad->c)) {
     outIndex = 0 ;
   } else {
     if (tcsDcString(outOpts, "output option: ", pcad->c, &outIndex, pcad))
       break ;
   }

/* Provide a default if a dhs label isn't specified */
   if (!tcsDcLen (pcad->d)) {
     strcpy(dhsLabel, "NONE" ) ;
   } else {
     strcpy(dhsLabel, pcad->d) ;
   }

/* Default output is to Quick Look tool if nothing is specified */
   if (!tcsDcLen (pcad->e)) {
     dhsIndex = 2 ;
   } else {
     if (tcsDcString(dhsOpts, "DHS output: ", pcad->e, &dhsIndex, pcad))
       break ;
   }
     
/* Provide a default path if none is specified */
   if (!tcsDcLen(pcad->f)) {
     strcpy(filePath, ".") ;
   } else {
     strcpy (filePath, pcad->f) ;
   }

/* Provide a default file name if none is specified */
   if (!tcsDcLen(pcad->g)) {
     strcpy (fileName, "pwfs1.fits") ;
   } else {
     strcpy (fileName, pcad->g) ;
   }
      
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

/* For PWFS1 store exposure time for later use */

    cadName = tcsCsCadName(pcad) ;
    if (!strcmp(cadName, "pwfs1Observe")) {
      tcsOpticsSetAoExpTime (expTime) ;
    }

    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    sprintf (pcad->valc, "%d", outIndex);
    strncpy (pcad->vald, dhsLabel, MAX_STRING_SIZE) ;
    sprintf (pcad->vale, "%d", dhsIndex);
    strncpy (pcad->valf, filePath, MAX_STRING_SIZE) ;
    strncpy (pcad->valg, fileName, MAX_STRING_SIZE) ;

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
 *   tcsCADrotConfig
 *
 *   Purpose:
 *   Configure the Cass rotator encoder system
 *
 *   Description:
 *   The Cass rotator encoder system can use a number of different algorithms
 *   to calculate the virtual encoder reading. This command sets the
 *   algorithm and the combination of read heads to use.
 *
 *   Invocation:
 *   tcsCADrotConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Demand algorithm 
 *      b => Demand head id
 *
 *   EPICS output paramters:
 *      vala => Algorithm
 *      valb => head id.
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcLong        (tcsDecode)        Decode an integer
 *   tcsDcString      (tcsDecode)        Match a string
 *   tcsCsSetMessageN (tcsCadSupport)    Define a message
 *
 */

long tcsCADrotConfig (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *algopts[] = {"FDE", "FULL", "N", "M&N", NULL};
  static long headId;     /* Head identifier */
  static int algIndex;    /* Index to demand algorithm */

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

/* Algorithm */
   if (tcsDcString (algopts, "algorithm : ", pcad->a, &algIndex, pcad)) break;

/* Head identifier */
   if (algIndex > 1) {
     if (!tcsDcLen (pcad->b)) {
       tcsCsAppendMessage (pcad, "no head identifier") ;
       break ;
     } else {
       if (tcsDcLong ("head id : ", pcad->b, &headId, pcad)) break ;
       if (headId < 1 || headId > 15) {
         tcsCsAppendMessage (pcad, "head ID < 1 or > 15");
         break ;
       }
     }
   }

   if (tcsConfigMarkComm (pcad->name, pcad->mess)) break ; 

   status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

   strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);

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
 *   tcsCADshutter
 *
 *   Purpose:
 *   Implement the TCS shutter command
 *
 *   Description:
 *   The shutter command is used to drive the enclosure shutters to
 *   specified elevations. It is a low level command as normally the 
 *   shutters will be driven automatically as a result of tracking
 *   a target. If this command is issued then it over rides these
 *   automatic demands and it will be neccessary to issue a new
 *   carouselMode command before automatic updates are re-instated.
 *
 *   Invocation:
 *   tcsCADshutter (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Top shutter elevation (degs)
 *      b => Bottom shutter elevation (degs) 
 *
 *   EPICS output paramters:
 *      vala => Top shutter elevation (degs)
 *      valb => Bottom shutter elevation (degs) 
 *      vald => Top shutter elevation (degs) for SAD
 *      vale => Bottom shutter elevation (degs) for SAD
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableShtrs   (tcsEcsLib) Enable/disable automatic moves
 *   tcsEcsGetShutLimits (tcsEcsLib) Fetch current shutter elevation limits
 *   tcsDcDouble         (tcsDecode) Decode a string as a double
 *   tcsCsSetMessageN    (tcsCadSupport) Set message prefix
 *
 *-
 */

long tcsCADshutter (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static double topShtrEl;     /* demand top shutter elevation */
  static double botShtrEl;     /* demand bottom shutter elevation */

  double minTopShtr;           /* Min. top shutter elevation */
  double maxTopShtr;           /* Max. top shutter elevation */
  double minBotShtr;           /* Min. bottom shutter elevation */
  double maxBotShtr;           /* Max. bottom shutter elevation */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL) ;  

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
 
      status = CAD_REJECT;

      if (tcsDcDouble ("top shtr: ", pcad->a, &topShtrEl, pcad))
        break ;

      if (tcsDcDouble ("bottom shtr: ", pcad->b, &botShtrEl, pcad))
        break;

      tcsEcsGetShutLimits (&minBotShtr, &maxBotShtr, &minTopShtr,
            &maxTopShtr) ;

      if ((topShtrEl < minTopShtr) || (topShtrEl > maxTopShtr)) {
        tcsCsAppendMessage (pcad, "top shutter out of range") ;
        break ;
      }

      if ((botShtrEl < minBotShtr) || (botShtrEl > maxBotShtr)) {
        tcsCsAppendMessage (pcad, "bottom shutter out of range") ;
        break ;
      }

      if (botShtrEl > topShtrEl) {
        tcsCsAppendMessage (pcad, "bottom shutter > top shutter") ;
        break ;
      }
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;


   break ;

   case menuDirectiveSTART :

/* Disable the automatic sending of moves or follows when tracking a source */

      tcsEcsEnableShtrs (FALSE);

/* Trigger the ECS move_shtrs command */

      strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
      strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
      *(double *)pcad->vald = topShtrEl ;
      *(double *)pcad->vale = botShtrEl ;

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
 *   tcsCADshutterPark
 *
 *   Purpose:
 *   Implements the shutterPark command in the TCS
 *
 *   Description:
 *   This is a simple routine to implement the TCS shutterPark command.
 *   There are no parameters so the routine disables automatic moves of
 *   the dome and shutters and then triggers the ECS park_shtrs command.
 *
 *   Invocation:
 *   tcsCADshutterPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output paramters:
 *      vala => MARK directive to park_shtrs
 *      valb => START directive to park_shtrs 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableShtrs  (tcsEcsLib)     Enable/disable automatic moves
 *
 *-
 */

long tcsCADshutterPark (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Disable the automatic sending of moves or follows when tracking a source */

      tcsEcsEnableShtrs (FALSE) ;

/* Trigger the park_shtrs command */

      *(long *)pcad->vala = menuDirectiveMARK;
      *(long *)pcad->valb = pcad->dir;

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
 *   tcsCADshutterStop
 *
 *   Purpose:
 *   Implements the shutterStop command in the TCS
 *
 *   Description:
 *   This is a simple routine to implement the TCS shutterStop command.
 *   There are no parameters, the routine sets the flag to prevent the sending
 *   of automatic moves and follows and then triggers the stop_shtrs
 *   command in the ECS
 *
 *   Invocation:
 *   tcsCADshutterStop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output paramters:
 *      vala => MARK directive to stop_shtrs
 *      valb => START directive to stop_shtrs 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsEnableShtrs  (tcsEcsLib)     Enable/disable automatic moves
 *
 *-
 */

long tcsCADshutterStop (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Disable the automatic sending of moves or follows when tracking a source */

      tcsEcsEnableShtrs (FALSE) ;

/* Trigger the stop_shtrs command */

      *(long *)pcad->vala = menuDirectiveMARK;
      *(long *)pcad->valb = pcad->dir;

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
 *   tcsCADventgates
 *
 *   Purpose:
 *   Implements the ventgates command to open/close the east/west vent gates
 *
 *   Description:
 *   This routine implements the command that controls the East and West
 *   vent gates. The parameters sent with the command and the fraction by
 *   which the gates should be opened i.e. a value of 0.0 means closed 
 *   whereas a value of 1.0 means fully open.
 *
 *   Invocation:
 *   tcsCADventgates (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => East gate fractional opening.
 *      b => West gate fractional opening.
 *
 *   EPICS output paramters:
 *      vala => East gate percentage opening
 *      valb => West gate percentage opening
 *      valh => Directive to move_vgates ECS command 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDouble    (tcsDecode)        Interpret a string as a double
 *
 *-
 */

long tcsCADventgates (struct cadRecord *pcad)

{

  long status ;             /* Return status */
  static double eastGate ;  /* East gate demand */
  static double westGate ;  /* West gate demand */

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

     if (tcsDcDouble ("East gate: ", pcad->a, &eastGate, pcad))
       break ;

     if ((eastGate < 0.0 ) || (eastGate > 1.0)) {
       tcsCsAppendMessage (pcad, "Out of range") ;
       break ;
     }

     if (tcsDcDouble ("West gate: ", pcad->b, &westGate, pcad))
       break ;

     if ((westGate < 0.0 ) || (westGate > 1.0)) {
       tcsCsAppendMessage (pcad, "Out of range") ;
       break ;
     }
     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

      sprintf (pcad->vala, "%6.1f", eastGate*100.0);
      sprintf (pcad->valb, "%6.1f", westGate*100.0);
      *(long *)pcad->valh = pcad->dir ;

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
 *   tcsCADventGatesPark
 *
 *   Purpose:
 *   Implements the ventGatesPark command in the TCS
 *
 *   Description:
 *   This is a simple routine to implement the TCS ventGatesPark command.
 *   Since there are no parameters to the command the routine only has
 *   to trigger suitable directives on the ECS park_vgates command.
 *
 *   Invocation:
 *   tcsCADventGatesPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output paramters:
 *      vala => MARK directive to park_vgates
 *      valb => START directive to park_vgates 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADventGatesPark (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Trigger the park_vgates command */

      *(long *)pcad->vala = menuDirectiveMARK;
      *(long *)pcad->valb = pcad->dir;

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
 *   tcsCADventGatesStop
 *
 *   Purpose:
 *   Implements the ventGatesStop command in the TCS
 *
 *   Description:
 *   This is a simple routine to implement the TCS ventGatesStop command.
 *   Since there are no parameters to the command the routine only has
 *   to trigger suitable directives on the ECS stop_vgates command.
 *
 *   Invocation:
 *   tcsCADventGatesStop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output paramters:
 *      vala => MARK directive to stop_vgates
 *      valb => START directive to stop_vgates 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADventGatesStop (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

   break ;

   case menuDirectiveSTART :

/* Trigger the stop_vgates command */

      *(long *)pcad->vala = menuDirectiveMARK;
      *(long *)pcad->valb = pcad->dir;

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
 *   tcsCADwfsStopObserve 
 *
 *   Purpose:
 *   Implement the stopObserve wfs commands in the TCS
 *
 *   Description:
 *   This command currently has no arguments so all it does is set 
 *   to off the flag that controls whether the incoming aO data from the
 *   A&G is averaged.
 *
 *   Invocation:
 *   tcsCADwfsStopObserve (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   EPICS output paramters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADwfsStopObserve (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char *cadName ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

/* In the PRESET stage the CAD inputs must all be checked for validity. Note
*  that any vlaues derived from the inputs which are also required at the
*  menuDirectiveSTART stage must be declared static.
*/

   case menuDirectivePRESET :

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;

   break ;

   case menuDirectiveSTART :

    cadName = tcsCsCadName(pcad) ;

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
 *   tcsCADm1ZeroSet
 *
 *   Purpose:
 *   Implement the m1ZeroSet command to zero the figure or demand offsets
 *
 *   Description:
 *   The inputs are checked for validity. If it is required to zero the
 *   figure then a flag is set to ensure that next time the open loop
 *   demands are sent, the full offset is output rather than the increment
 *   since the previous offset.
 *
 *   Invocation:
 *   tcsCADm1ZeroSet (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Figure or definition 
 *
 *   EPICS output paramters:
 *      vala => Figure or Definition 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsM1SetInit  (tcsOptics)   Set flag to initialise open loop model
 *   tcsDcString         (tcsDecode)   Check for a valid string
 *
 *-
 */

long tcsCADm1ZeroSet (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  int  optIndex ;         /* Index to option */
  static char *opts[] = {"FIGURE", "DEFINITION", NULL} ;

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
   if (tcsDcString (opts, " ", pcad->a, &optIndex, pcad)) break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
   
    tcsOpticsSetM1Zero() ;
    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE ) ;

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
 *   tcsGpolPlates
 *
 *   Purpose:
 *   Store the names and states of the plates as read from GPOL
 *
 *   Description:
 *   This routine will store the current names of the plates loaded in
 *   GPOL for use by the various GPOL CAD commands. It also generates
 *   a value for the state of the plate based on the values of the
 *   plate switches.
 *
 *   Invocation:
 *   tcsGpolPlates(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *    (!)  (pgsub)  (struct genSubRecord *) Pointer to gensub record structure
 *
 *   Epics inputs:
 *   a => Name of upper plate
 *   b => Name of middle plate
 *   c => Name of lower plate
 *   d => State of upper plate beam switch
 *   e => State of upper plate park switch
 *   f => State of middle plate beam switch
 *   g => State of middle plate park switch
 *   h => State of lower plate beam switch
 *   i => State of lowerplate park switch
 *
 *   Epics outputs:
 *   vala => State of upper plate
 *   valb => State of middle plate
 *   valc => State of lower plate
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsGpolPlates(struct genSubRecord *pgsub)
{

/* For the names, just copy whatever is read from GPOL */
  strncpy(gpolUpperPlate, pgsub->a, MAX_STRING_SIZE) ;
  strncpy(gpolMiddlePlate, pgsub->b, MAX_STRING_SIZE) ;
  strncpy(gpolLowerPlate, pgsub->c, MAX_STRING_SIZE) ;

/* For the switches check the severity (to make sure GPOL is connected)
*  then check that the states read are valid and finally that the
*  switch states are consistent
*/

  if (pgsub->sevr == NO_ALARM) {

/* Now we know we have valid strings, make sure they are consistent */
    if (!strcmp(pgsub->d, "OPEN") && !strcmp(pgsub->e, "OPEN")) {
      gpolUpperPlateState = PLATE_MOVING ;
    } else if (!strcmp(pgsub->d, "OPEN") && !strcmp(pgsub->e, "CLOSED")) {
      gpolUpperPlateState = PLATE_PARKED ;
    } else if (!strcmp(pgsub->d, "CLOSED") && !strcmp(pgsub->e, "CLOSED")) {
      gpolUpperPlateState = PLATE_BROKEN ;
    } else if (!strcmp(pgsub->d, "CLOSED") && !strcmp(pgsub->e, "OPEN")) {
      gpolUpperPlateState = PLATE_INBEAM ;
    } else {
      gpolUpperPlateState = PLATE_INVALID ;
    }

    if (!strcmp(pgsub->f, "OPEN") && !strcmp(pgsub->g, "OPEN")) {
      gpolMiddlePlateState = PLATE_MOVING ;
    } else if (!strcmp(pgsub->f, "OPEN") && !strcmp(pgsub->g, "CLOSED")) {
      gpolMiddlePlateState = PLATE_PARKED ;
    } else if (!strcmp(pgsub->f, "CLOSED") && !strcmp(pgsub->g, "CLOSED")) {
      gpolMiddlePlateState = PLATE_BROKEN ;
    } else if (!strcmp(pgsub->f, "CLOSED") && !strcmp(pgsub->g, "OPEN")) {
      gpolMiddlePlateState = PLATE_INBEAM ;
    } else {
      gpolMiddlePlateState = PLATE_INVALID ;
    }

    if (!strcmp(pgsub->h, "OPEN") && !strcmp(pgsub->i, "OPEN")) {
      gpolLowerPlateState = PLATE_MOVING ;
    } else if (!strcmp(pgsub->h, "OPEN") && !strcmp(pgsub->i, "CLOSED")) {
      gpolLowerPlateState = PLATE_PARKED ;
    } else if (!strcmp(pgsub->h, "CLOSED") && !strcmp(pgsub->i, "CLOSED")) {
      gpolLowerPlateState = PLATE_BROKEN ;
    } else if (!strcmp(pgsub->h, "CLOSED") && !strcmp(pgsub->i, "OPEN")) {
      gpolLowerPlateState = PLATE_INBEAM ;
    } else {
      gpolLowerPlateState = PLATE_INVALID ;
    }

  } else {

   gpolUpperPlateState  = PLATE_DISCONNECTED ;
   gpolMiddlePlateState = PLATE_DISCONNECTED ;
   gpolLowerPlateState  = PLATE_DISCONNECTED ;

  }
    
  *(long *)pgsub->vala = (long)gpolUpperPlateState ;
  *(long *)pgsub->valb = (long)gpolMiddlePlateState ;
  *(long *)pgsub->valc = (long)gpolLowerPlateState ;
  return 0 ;

}
epicsRegisterFunction(tcsCADencThermal);
epicsRegisterFunction(tcsCADshutter);
epicsRegisterFunction(tcsCADshutterPark);
epicsRegisterFunction(tcsCADm1Definition);
epicsRegisterFunction(tcsCADm2Move);
epicsRegisterFunction(tcsCADventgates);
epicsRegisterFunction(tcsCADrotConfig);
epicsRegisterFunction(tcsCADshutterStop);
epicsRegisterFunction(tcsCADcarouselStop);
epicsRegisterFunction(tcsCADm2Baffle);
epicsRegisterFunction(tcsCADm2GuideControl);
epicsRegisterFunction(tcsCADgpolPlateSeq);
epicsRegisterFunction(tcsCADventGatesPark);
epicsRegisterFunction(tcsCADventGatesStop);
epicsRegisterFunction(tcsCADcarouselPark);
epicsRegisterFunction(tcsCADcarousel);
epicsRegisterFunction(tcsCADenclosureDatum);
epicsRegisterFunction(tcsCADwfsStopObserve);
epicsRegisterFunction(tcsCADdetSigModeAo);
epicsRegisterFunction(tcsCADgpolPlateAngle);
epicsRegisterFunction(tcsCADm1ZeroSet);
epicsRegisterFunction(tcsCADgpolPlateDatum);
epicsRegisterFunction(tcsCADgpolPlateRotate);
epicsRegisterFunction(tcsCADdetSigInit);
epicsRegisterFunction(tcsCADdetSigModeSeqDark);
epicsRegisterFunction(tcsCADm1Btempset);
epicsRegisterFunction(tcsCADenclosureStop);
epicsRegisterFunction(tcsGpolPlates);
epicsRegisterFunction(tcsCADgpolPlateMove);
epicsRegisterFunction(tcsCADenclosurePark);
epicsRegisterFunction(tcsCADngsPark);
epicsRegisterFunction(tcsCADmechCad20);
epicsRegisterFunction(tcsCADwfsObserve);
epicsRegisterFunction(tcsCADm1Figure);
epicsRegisterFunction(tcsCADdetSigModeSeq);
epicsRegisterFunction(tcsCADmechCad);
