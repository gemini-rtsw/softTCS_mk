/*
*   FILENAME
*   tcsM2sSimulation.c
*
*   This module holds the routines that are used in the M2 Simulation
*
*   FUNCTION NAME(S)
*   tcsM2beamCAD    - implement beam command
*   tcsM2ChopConfig - implement chopConfig command
*   tcsM2ChopControl - implement chopControl command
*   tcsM2clearGuideFocusCAD - implement clearGuideFocus command
*   tcsM2clearTiltGuideCAD - implement clearTiltGuide command
*   tcsM2Dump        - print out internal M2 variables
*   tcsM2exposuretimeCAD - send WFS exposure time to M2
*   tcsM2GuideErrors - make guide errors available to EPICS
*   tcsM2guideCAD - implement the M2 guide command
*   tcsM2guideConfigCAD - implement the M2 guideConfig command
*   tcsM2guideConfigResetCAD - reset the guide configuration
*   tcsM2InitCAD - initialise variables for the M2 simulator
*   tcsM2MoveCAD - implement the M2 move command
*   tcsM2moveBaffleCAD - implement the M2 moveBaffle command
*   tcsM2parkCAD   - implement the M2 park command
*   tcsM2setController - minimal implementation of setController command
*   tcsM2sSimulate - simulate the movement of secondary mirror
*   tcsM2sComplete - signal completion of a move command
*   tcsM2sStop - stop M2 move
*   tcsM2sGenericCAD - general purpose CAD routine
*   tcsM2toleranceCAD - implement the M2 tolerance  command
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsM2sSimulation.c,v $
 * Revision 1.18  2006/04/21 12:53:35  cjm
 * New clearGuideTilt command and improve guiding simulation
 *
 * Revision 1.17  2003/11/10 14:40:08  gemvx
 * Provide simulations of new SCS commands
 *
 * Revision 1.16  2002/11/23 12:43:31  cjm
 * Add setController command
 *
 * Revision 1.15  2002/11/13 13:29:11  dlt
 * Implement reset in guideConfig
 *
 * Revision 1.14  2002/11/13 05:04:04  cjm
 * Add simulation for guideConfigProc record
 *
 * Revision 1.13  2001/09/10 15:05:55  cjm
 * add code to support clearGuideFocus command
 *
 * Revision 1.12  2001/05/17 14:50:38  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.11  2000/10/24 02:38:00  cjm
 * Output sync source and use tcsDcString
 *
 * Revision 1.10  2000/10/11 05:38:53  cjm
 * Use new names of baffle positions
 *
 * Revision 1.9  2000/07/12 07:28:35  dlt
 * Change chopControl output values to match real M2S
 *
 * Revision 1.8  2000/06/10 01:45:02  cjm
 * Output current chop beam from simulation
 *
 * Revision 1.7  2000/06/08 06:33:57  cjm
 * Output duty cycle for compatibility with SCS
 *
 * Revision 1.6  2000/05/09 08:14:58  cjm
 * Output chopping state from simulation routine rather than apply time of the positions
 *
 * Revision 1.5  2000/01/29 23:55:02  cjm
 * Output whether M2 is guiding
 *
 * Revision 1.4  1999/06/16 21:26:50  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.3  1999/05/24 03:58:14  cjm
 * Modify moveBaffle parameters in line with latest SCS implementation
 *
 * Revision 1.2  1999/01/15 19:45:14  cjm
 * Allow for receipt of focus and tilt scaling factors but don't do anything with them
 *
 * Revision 1.1.1.1  1998/11/08 00:21:11  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.20  1998/07/31 10:45:48  dlt
 * Write baffle positions to output links
 *
 * Revision 1.19  1998/07/09 08:36:43  tcs
 * Change name of CAd from beam to beamJog to match latest ICD
 *
 * Revision 1.18  1998/07/01 12:06:11  tcs
 * Add tcsM2parkCAD routine and use new sync source in chopConfig command
 *
 * Revision 1.17  1998/06/17 16:08:55  tcs
 * Support beam command and update move, guideConfig and guideControl
 *
 * Revision 1.16  1998/03/23 14:40:12  cjm
 * Use input J for continuous demands as per latest ICD
 *
 * Revision 1.15  1998/01/08 16:40:53  cjm
 * Handle guide errors via a servo
 *
 * Revision 1.14  1997/12/01 09:07:37  cjm
 * Check for correct status back from slaDftlin
 *
 * Revision 1.13  1997/11/20 12:34:00  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.12  1997/11/18 08:27:02  cjm
 * Add support for fast focus errors
 *
 * Revision 1.11  1997/09/24 16:32:44  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.10  1997/09/23 11:50:06  tcs
 * Remove redundant includes
 *
 * Revision 1.9  1997/09/23 09:43:58  pbt
 * Removed carOR routine
 *
 * Revision 1.8  1997/09/17 15:36:32  pbt
 * Correct bug in guideConfig routine
 *
 * Revision 1.7  1997/09/15 17:08:32  pbt
 * Implementation of extra M2 simulated commands
 *
 * Revision 1.6  1997/09/03 10:07:03  tcs
 * Change M2 units to tip/tilt
 *
 * Revision 1.5  1997/08/21 10:43:20  tcs
 * Feedback guiding signals to tcs
 *
 * Revision 1.4  1997/04/21 15:37:32  cjm
 * Trap string test as an invalid input to chopConfig
 *
 * Revision 1.3  1997/04/03 14:34:57  cjm
 * Mods to agree with TCS/SCS ICD
 *
 * Revision 1.2  1997/03/05 09:36:58  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:44  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.11  1997/01/13 09:01:37  cjm
 * Updates to support M2 open loop model
 *
 * Revision 1.10  1996/12/13 13:24:53  tcs
 * replace tcsLibrary with tcsDecode routines
 *
 * Revision 1.9  1996/12/10 17:58:29  pbt
 * Simulator CADs now set followS value via output VALA field
 *
 * Revision 1.8  1996/11/28 08:09:49  cjm
 * Fix triggering of activeC and trackid
 *
 * Revision 1.7  1996/11/25 12:35:46  pbt
 * Changed simulation to use GenSub record
 *
 * Revision 1.6  1996/11/12 18:05:35  pbt
 * Various updates : STOP command and MOVE command default parameters
 *
 * Revision 1.5  1996/11/05 11:07:20  cjm
 * Add chopConfig & chopControl and enhance simulation
 *
 * Revision 1.4  1996/07/23 15:40:15  tcs
 * Add file header comments
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>

#include "tcsM2s.h"
#include "tcsConstants.h"
#include "slalib.h"
#include "slamac.h" 
#include "tcsDecode.h"
#include "tcsCadSupport.h"

/* State of rotator */
static int StateM2;

/* Chop control and chop emulation parameters */
static int chopping = FALSE ;
static int freqTicks = 1 ;    
static int freqCounter = 0 ;
static int chopMode ;         /* whether 2posn 3posn or triangle chopping */
static int currentChopIndex = 0 ; 
static int defaultBeam = 0 ;  /* Default beam when not chopping */

/* Guiding parameters & state */
static int m2IsGuiding = 0 ;
static double xGuide = 0.0;    /* Guide error in arcsec */
static double yGuide = 0.0;    /* Guide error in arcsec */
static double zGuide = 0.0;    /* Focus error in microns */
static double lastIntX = 0.0 ;  /* Integral of x guide error */
static double lastIntY = 0.0 ;  /* Integral of y guide error */
static int guideConfigReset = 0; /* Flag to reset guide config */
static int guideConfigSetup = 0; /* Flag to indicate a new guide config */

/* Demand position from move command */
static double xTiltTarget[3];        /* Arcsec in M2 frame */
static double yTiltTarget[3];        /* Arcsec in M2 frame */
static double xTarget;               /* microns */
static double yTarget;               /* microns */
static double zTarget;               /* microns */

/* Current (= demand) position for X and Y */
static double xTiltDemand[3];        /* Arcsec in M2 frame */
static double yTiltDemand[3];        /* Arcsec in M2 frame */
static double xDemand;               /* microns */
static double yDemand;               /* microns */
static double zDemand;               /* microns */


/*+
 *   Function name:
 *   tcsM2beamJogCAD 
 *
 *   Purpose:
 *   Switch default beam that M2 follows
 *
 *   Description:
 *   By default the SCS will always follow beam A. This command allows
 *   a different default beam to be specified. Note that unless chopping
 *   has been configured, the positions of beams A, B and C are all
 *   identical. 
 *
 *   Invocation:
 *   tcsM2beamJogCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => demanded defualt beam, A, B or C 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsM2beamJogCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *beamOpts[] = {"A", "B", "C", NULL} ;
  static int bs ;         /* Index of selected beam */

  status = CAD_ACCEPT ;
  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;
     if (tcsDcString (beamOpts, " ", pcad->a, &bs, pcad )) break ;
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     defaultBeam = bs ;

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
 *   tcsM2clearGuideFocusCAD 
 *
 *   Purpose:
 *   Set any mean DC focus correction to zero
 *
 *   Description:
 *   For this simple simulation just set zGuide to 0.0
 *
 *   Invocation:
 *   tcsM2clearGuideFocusCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsM2clearGuideFocusCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;
  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   break ;

   case menuDirectiveSTART :

     zGuide = 0.0 ;

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
 *   tcsM2clearTiltGuideCAD 
 *
 *   Purpose:
 *   Set any mean DC tilt correction to zero
 *
 *   Description:
 *   For this simple simulation just set the errors and integral terms to
 *   zero. We don't try and protect the variables by semaphores nor
 *   do we worry about whehter we are guiding or not. 
 *
 *   Invocation:
 *   tcsM2clearTiltGuideCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsM2clearTiltGuideCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;
  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   break ;

   case menuDirectiveSTART :

     xGuide = 0.0 ;
     yGuide = 0.0 ;
     lastIntX = 0.0;
     lastIntY = 0.0;

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
 *   tcsM2exposuretimeCAD
 *
 *   Purpose:
 *   Emulate the M2 exposuretime command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS exposureTime command.
 *
 *   Invocation:
 *   tcsM2exposuretimeCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => WFS exposure time (secs)  
 *   b => WFS  
 *
 *   EPICS output parameters:
 *   vala => Exposure time (secs) 
 *   valb => WFS source
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsM2exposuretimeCAD (struct cadRecord *pcad)

{
  static char *sourceOpts[] = {"PWFS1", "PWFS2", "OIWFS", NULL } ; 
  static double expTime ;
  static int wfsnum = 0;

  long status ;           /* Return status */
  char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
  char prefix[MAX_STRING_SIZE];            /* Name of CAD record */

/* Fetch name of CAD for use in messages */

    strcpy (cadname, strchr(pcad->name, ':') + 1) ;
    strcpy (prefix, cadname) ;
    strcat (prefix, ": ");

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;
/* First check the exposure time */
     if (tcsDcDouble (prefix, pcad->a, &expTime, pcad)) break ;
     if (expTime < 0.005 ) {
       strcpy (pcad->mess, "M2 exposure time < 0.005") ;
       return status ;
     }

/* Check the requested WFS type */
     if (tcsDcString (sourceOpts, prefix, pcad->b, &wfsnum, pcad)) break ;

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:

      *(double *)pcad->vala   = expTime ;
      strcpy( pcad->valb, pcad->b ) ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsM2Init
 *
 *   Purpose:
 *   Initialise the TCS internal simulation of M2
 *
 *   Description:
 *   This routine is called from a sequence program every time that the M2
 *   simulator executes the INIT command. It can be used to reset any 
 *   internal variables that may have been modified since the system
 *   was booted.
 *
 *   Invocation:
 *   tcsM2Init()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   None
 * 
 *-
 */


void tcsM2Init (void )
{
   static int first = TRUE;

/* Place any initialisations that should only happen once within the 
 * if (first) clause.
*/

   if (first) first = FALSE;

/* Set the M2 state back to stopped */

   StateM2 = STOPPED;

/* Set the guiding parameters back to 0.0 */

  xGuide = 0.0;
  yGuide = 0.0;
  zGuide = 0.0;
  lastIntX = 0.0;
  lastIntY = 0.0;
}


/*+
 *   Function name:
 *   tcsM2ChopConfig
 *
 *   Purpose:
 *   Emulate the M2 chopConfig command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS chopConfig command.
 *   The only parameters of interest are the type of chop and the 
 *   frequency.
 *
 *   Invocation:
 *   tcsM2ChopConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => chop mode, "2posn", "3posn" or "triangular"
 *   b => sync source, "SCS" or "ICSn" where n = 0,1,2,3,4 
 *   c => chop frequency (Hz)
 *   d => duty cycle (%)
 *
 *   EPICS output parameters :
 *
 *   vala => chop mode (as a string)
 *   valb => sync source (as an integer)
 *   valc => chop frequency (Hz)
 *   vald => duty cycle (%)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   slaDfltin      (slalib)    Convert string input to double 
 *   dnint          (slamac)    Nearest int as a double
 *
 *-
 */

long tcsM2ChopConfig (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  int nptr ;              /* Pointer for slaDfltin */
  int decodeStatus ;      /* Status for slaDfltin */
  static int inputChopMode ; /* Input chop mode */
  static double inputChopFreq ; /* Input chop frequency (Hz) */
  static double inputDutyCycle ;
  static int syncIndex ;
  char ustring[MAX_STRING_SIZE] ; /* Buffer for upper case strings */
  char *syncOpts[] = {"SCS","ICS0","ICS1","ICS2","ICS3","ICS4"} ;

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* First check the requested chop mode */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if (strncmp(ustring,"2",1) == 0)
       inputChopMode = TWOPOSN ;
     else if (strncmp(ustring,"3",1) == 0)
       inputChopMode = THREEPOSN ;
     else if (strncmp(ustring,"T",1) == 0)
       inputChopMode = TRIANGLE ;
     else {
       strcpy (pcad->mess, "Mode must be 2posn, 3posn or triangle") ;
       return status ;
     }

/* Check the sync source */

     if (tcsDcString (syncOpts, "sync :", pcad->b, &syncIndex, pcad))
       break ;

/* Read the frequency */

     nptr = 1 ;
     slaDfltin (pcad->c, &nptr, &inputChopFreq, &decodeStatus) ;
     if (decodeStatus > 0)
     {
      strcpy (pcad->mess, "Chop frequency invalid or null") ;
      return status ;
     }

     if (tcsDcDouble ("Duty cycle", pcad->d, &inputDutyCycle, pcad)) 
       break ;

     status = CAD_ACCEPT ;

     break ;

     case menuDirectiveSTART :

/* Copy inputs to outputs and set the frequency switch parameter */

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     *(long *)pcad->valb = syncIndex ;
     *(double *)pcad->valc = inputChopFreq ;
     *(double *)pcad->vald = inputDutyCycle ;

     if (inputChopFreq != 0.0)
     {
      if (inputChopMode == THREEPOSN)
        freqTicks = (int)dnint (20.0/(4.0 * inputChopFreq)) ;
      else
        freqTicks = (int)dnint (20.0/(2.0 * inputChopFreq)) ;
     }
     if (freqTicks < 1) freqTicks = 1 ;
     chopMode = inputChopMode ;

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
 *   tcsM2ChopControl
 *
 *   Purpose:
 *   Emulate the SCS chopControl command
 *
 *   Description:
 *   This routine emulates the chopControl command of the SCS. It is only
 *   interested in the first parameter to the command i.e. whether to
 *   turn chopping on or off
 *
 *   Invocation:
 *   tcsM2ChopControl (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input parameters :
 *   
 *   a => chop control "On" or "Off"
 *
 *   EPICS Output parameters :
 *
 *   vala => chop control "YES" or "NO"
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsM2ChopControl (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char cadname[MAX_STRING_SIZE] ;  /* Name of cad record */
  char prefix[MAX_STRING_SIZE] ;   /* prefix for message */
  int prelen ;                     /* Base length of prefix */
  static int inputChopControl ;    /* 0 = Off, 1 = On */

/* Fetch name of cad for use in messages */

  strcpy (cadname, strrchr(pcad->name, ':') + 1 ) ;
  strcpy (prefix, cadname) ;
  strcat (prefix, ": ") ;
  prelen = strlen (prefix) ;

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* The only input of interest for the simulation is the first */

     prefix[prelen] = '\0' ;
     strcat (prefix, "Control: ") ;
     if (tcsDcOnOff (prefix, pcad->a, &inputChopControl, pcad)) break ;

     status = CAD_ACCEPT ;
     break ;

     case menuDirectiveSTART :

     if (inputChopControl == 0 )
     { 
      chopping = FALSE ;
      strcpy (pcad->vala, "NO") ;
     }
     else
     {
      chopping = TRUE ;
      freqCounter = 0 ;
      currentChopIndex = 0 ;
      strcpy (pcad->vala, "YES") ;
     }
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
 *   tcsM2Dump
 *
 *   Purpose:
 *   Diagnostic routine to print out values of internal variables
 *
 *   Description:
 *   This is a debug/diagnoses routine that is used to check that internal
 *   variables really do contain the values expected.
 *
 *   Invocation:
 *   tcsM2Dump
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *     None
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsM2Dump (void)

{

  printf("M2 guiding flag = %d\n", m2IsGuiding) ;
  printf("M2 chopping flag = %d\n", chopping);

}

/*+
 *   Function name:
 *   tcsM2FollowCAD
 *
 *   Purpose:
 *   Implements the follow command for the M2 simulator
 *
 *   Description:
 *   Simply sets a flag dependent on the directive to tell the simulator
 *   what state it should enter.
 *
 *   Invocation:
 *   tcsM2FollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad   (struct cadRecord *pcad) Pointer to CAD record structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */


long tcsM2FollowCAD (struct cadRecord *pcad)
{

/* CAD directive is in field DIR */

   switch (pcad->dir)
   {
   case menuDirectiveSTART:
      StateM2 = FOLLOWING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"On");
      return 0;
      break;  /* End menuDirectiveSTART */

/* The STOP CAD directive simply sets the axis 
      state flags to STOPPED   */

    case menuDirectiveSTOP:
      StateM2 = STOPPED;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"Off");
      return 0;

   default :
      return 0;
      break;
   }
}


/*+
 *   Function name:
 *   tcsM2GuideErrors
 *
 *   Purpose:
 *   Output guide errors to EPICS variables
 *
 *   Description:
 *   This routine simply copies the current guide errors to EPICS variables.
 *   It was introduced only because all available outputs from tcsM2sSimulate
 *   were already allocated.
 *
 *   Invocation:
 *   tcsM2GuideErrors (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub record 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsM2GuideErrors (struct genSubRecord *pgsub) 
{

/* Copy guide errors to outputs */

  *(double *)pgsub->vala = xGuide ;
  *(double *)pgsub->valb = yGuide ;
  *(double *)pgsub->valc = zGuide;

  return 0;
}

/*+
 *   Function name:
 *   tcsM2MoveCAD
 *
 *   Purpose:
 *   Implements the MOVE CAD record in the TCS simulation of M2
 *
 *   Description:
 *   Read and verify the input on the EPICS links then set the state of the
 *   simulator to MOVING. The input data is then copied to locations 
 *   accessible by the M2 simulator.
 *
 *   Invocation:
 *   tcsM2MoveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad   (struct cadRecord *pcad) Pointer to CAD record structure
 *
 *   Epics inputs:
 *    
 *   a => Ax tilt (arcsec)
 *   b => Ay tilt (arcsec)
 *   c => Bx tilt (arcsec)
 *   d => Bx tilt (arcsec)
 *   e => Cy tilt (arcsec)
 *   f => Cy tilt (arcsec)
 *   g => x position (microns)
 *   h => y position (microns)
 *   i => z position (microns)
 *
 *   Epics outputs:
 *  
 *   vala => Following state is Off
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDouble    (tcsDecode)        Decode an input string as a double
 *
 *   Deficiencies:
 *   Does not check for out of range input, only invalid input
 *
 *-
 */


long tcsM2MoveCAD (struct cadRecord *pcad)
{
   double xTiltA, yTiltA;                   /* Input x,y Tilts (arcsec) */
   double xTiltB, yTiltB;                   /* Input x,y Tilts (arcsec) */
   double xTiltC, yTiltC;                   /* Input x,y Tilts (arcsec) */
   double x,y,z;                            /* Input x,y & z  (microns) */
   long status;                             /* Return status */
   int prelen;                              /* Base length of prefix */
   char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
   char prefix[MAX_STRING_SIZE];            /* prefix for messages */

/* Fetch name of CAD for use in messages */

   strcpy (cadname, strchr(pcad->name, ':') + 1) ;
   strcpy (prefix, cadname) ;
   strcat (prefix, ": ");
   prelen = strlen(prefix);

   status = CAD_ACCEPT;

/* CAD directive is in field DIR */

   switch (pcad->dir)
   {
   case menuDirectivePRESET:

      status = CAD_REJECT;

      if (tcsDcDouble (prefix, pcad->a, &xTiltA, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->b, &yTiltA, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->c, &xTiltB, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->d, &yTiltB, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->e, &xTiltC, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->f, &yTiltC, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->g, &x, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->h, &y, pcad))
         break ;
      if (tcsDcDouble (prefix, pcad->i, &z, pcad))
         break ;

      xTiltTarget[0] = xTiltA;
      yTiltTarget[0] = yTiltA;
      xTiltTarget[1] = xTiltB;
      xTiltTarget[1] = xTiltB;
      yTiltTarget[2] = yTiltC;
      yTiltTarget[2] = yTiltC;
      xTarget        = x;
      yTarget        = y;
      zTarget        = z;
      status = CAD_ACCEPT;

      break; 

   case menuDirectiveSTART:

      StateM2 = MOVING;
      strcpy (pcad->vala, "Off") ;
      break ;

/* The STOP CAD directive simply sets the axis 
   state flags to STOPPED   */

   case menuDirectiveSTOP:
      StateM2 = STOPPED;

   default :
      break;
   }

   return status;
}

/*+
 *   Function name:
 *   tcsM2guideCAD
 *
 *   Purpose:
 *   Emulate the M2 guide command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS guide command.
 *
 *   Invocation:
 *   tcsM2guideCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => guiding "On" or "Off"
 *
 *   EPICS output parameters :
 *  
 *   vala => guide state, 0 = Off, 1 = On
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsM2guideCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char ustring[MAX_STRING_SIZE] ; /* Buffer for upper case strings */
  static int guideMode ;

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

/* First check the requested guide mode */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"ON",2) != 0) && (strncmp(ustring,"OFF",3) !=0) )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 Guide mode must be On or Off") ;
       return status ;
     }
     if ( (strncmp (ustring, "ON",2) == 0) )
       guideMode = 1 ;
     else
       guideMode = 0;

     break;

     case menuDirectiveSTART:
  
     m2IsGuiding = guideMode;
     *(long *)pcad->vala = (long)guideMode ;
     break ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsM2guideConfigCAD
 *
 *   Purpose:
 *   Emulate the M2 guideConfig command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS guideConfig command.
 *
 *   Invocation:
 *   tcsM2guideConfigCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => WFS type 
 *   b => Sample frequency (Hz)
 *   c => Filter type (0->4)
 *   d => Filter edge frequency 1 (Hz)
 *   e => Filter edge frequency 2 (Hz)
 *   f => not used
 *   g => Beam A Weight (-2 -> 100)
 *   h => Beam B Weight (-2 -> 100)
 *   i => Beam C Weight (-2 -> 100)
 *   j => reset guide processing "On" or "Off" 
 *
 *   EPICS output parameters:
 *   vala => Filter type 
 *   valb => WFS source
 *   valc => Beam A weight
 *   vald => Beam B weight
 *   vale => Reset
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsM2guideConfigCAD (struct cadRecord *pcad)

{
  static char *sourceOpts[] = {"PWFS1", "PWFS2", "OIWFS", "GAOS", "GYRO",
                                NULL } ;
  static char *filterOpts[] = {"OFF", "RAW", "LOWPASS", "HIGHPASS", "BANDPASS",
                              "BANDSTOP", NULL} ;
  static int wfsnum = 0;
  double ssfreq = 0;
  static int filter = 0;
  double fefreq1 = 0;
  double fefreq2 = 0;
  static double weightA = 0;
  static double weightB = 0;
  static double weightC = 0;
  long status ;           /* Return status */
  char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
  char prefix[MAX_STRING_SIZE];            /* Name of CAD record */
  static char ustring[MAX_STRING_SIZE];

/* Fetch name of CAD for use in messages */

    strcpy (cadname, strchr(pcad->name, ':') + 1) ;
    strcpy (prefix, cadname) ;
    strcat (prefix, ": ");

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* First check the requested WFS type */
     if (tcsDcString (sourceOpts, prefix, pcad->a, &wfsnum, pcad)) break ;

/* Then check the requested sample frequency */
     if (tcsDcDouble (prefix, pcad->b, &ssfreq, pcad)) break ;
     if (ssfreq < 0 || ssfreq > 200.0) {
       strcpy (pcad->mess, "M2 guideConfig. freq. out of range") ;
       return status ;
     }

/* Then check the specified filter type */
     if (tcsDcString (filterOpts, prefix, pcad->c, &filter, pcad)) break ;
     if (filter > 1 ) {

/* Then check the requested filter edge frequency 1 */
     if (tcsDcDouble (prefix, pcad->d, &fefreq1, pcad)) break ;
       if (fefreq1 < 0 || fefreq1 > ssfreq/2.)
       {
         strcpy (pcad->mess, "M2 guideConfig. Edge freq. 1 invalid") ;
         return status ;
       }

/* Then check the requested filter edge frequency 2 */
       if (tcsDcDouble (prefix, pcad->e, &fefreq2, pcad)) break ;
       if (fefreq2 < fefreq1 || fefreq2 > ssfreq/2.) {
         strcpy (pcad->mess, "M2 guideConfig. Edge freq. 2 invalid") ;
         return status ;
       }
     }

/* Then check the specified beam weights */
     if (tcsDcDouble (prefix, pcad->g, &weightA, pcad)) break ;
     if (weightA < -2.0 || weightA > 100.0)
     {
       strcpy (pcad->mess, "M2 guideConfig. Beam weight A invalid") ;
       return status ;
     }
     if (tcsDcDouble (prefix, pcad->h, &weightB, pcad)) break ;
     if (weightB < -2.0 || weightB > 100.0)
     {
       strcpy (pcad->mess, "M2 guideConfig. Beam weight B invalid") ;
       return status ;
     }

     if (tcsDcDouble (prefix, pcad->i, &weightC, pcad)) break ;
     if (weightC < -2.0 || weightC > 100.0)
     {
       strcpy (pcad->mess, "M2 guideConfig. Beam weight C invalid") ;
       return status ;
     }

/* Then check the requested reset mode */

     tcsDcUc (pcad->j, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"ON",2) != 0) && (strncmp(ustring,"OFF",3) !=0) )
     {
       strcpy (pcad->mess, "M2 Guide reset mode must be On or Off") ;
       return status ;
     } 

/* This setting of the reset flag can be removed when the latest SCS is
*  released. For the time being this allows the old command to work
* as before 
*/
     if ( strncmp(ustring, "ON", 2) == 0) {
       guideConfigReset = 1 ;
     } else {
       guideConfigSetup = 1 ;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:

      *(long *)pcad->vala   = filter ;
      *(long *)pcad->valb   = wfsnum ;
      *(double *)pcad->valc = weightA ;
      *(double *)pcad->vald = weightB ;
      strcpy( pcad->vale, ustring ) ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsM2guideConfigResetCAD
 *
 *   Purpose:
 *   Emulate the M2 guideConfigReset command
 *
 *   Description:
 *   The functionality of this command used to be provided through field
 *   J of the guideConfig command. This caused difficulties in use and
 *   so the reset was moved to this new command.
 *
 *   Invocation:
 *   tcsM2guideConfigResetCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => reset guide processing "On" or "Off" 
 *
 *   EPICS output parameters:
 *   vala => Reset
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsM2guideConfigResetCAD (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
  char prefix[MAX_STRING_SIZE];            /* Name of CAD record */
  static char ustring[MAX_STRING_SIZE];

/* Fetch name of CAD for use in messages */

    strcpy (cadname, strchr(pcad->name, ':') + 1) ;
    strcpy (prefix, cadname) ;
    strcat (prefix, ": ");

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* Then check the requested reset mode */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"ON",2) != 0) && (strncmp(ustring,"OFF",3) !=0) )
     {
       strcpy (pcad->mess, "M2 Guide reset mode must be On or Off") ;
       return status ;
     }
     if ( strncmp(ustring, "ON", 2) == 0) {
       guideConfigReset = 1;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:

      strcpy( pcad->vala, ustring ) ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsGuideConfig
 *
 *   Purpose:
 *   Emulates the SCS guideConfig routine
 *
 *   Description:
 *   This routine emulates the SCS guideConfig routine so that this 
 *   simulator provides the same interface to the TCS as the real SCS.
 *   It provides the guideConfig status strings so that they can be
 *   displayed by the TCS
 *
 *   Invocation:
 *   tcsGuideConfig(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsGuideConfig (struct genSubRecord *pgsub)
{

 char *filterOpts[] = {"OFF", "RAW", "LOWPASS", "HIGHPASS", "BANDPASS",
                              "BANDSTOP", NULL} ;
 long filterType ;
 long wfsnum ;
 double weightA, weightB ;       
 char filterString[MAX_STRING_SIZE];
 char aString[10], bString[10], cString[10] ;

 filterType = *(long *)pgsub->a ;
 wfsnum     = *(long *)pgsub->b ;
 weightA    = *(double *)pgsub->c ;
 weightB    = *(double *)pgsub->d ;

/* Reset */
 if ( guideConfigReset ) {
     strcpy (pgsub->vala, "OFF") ;
     strcpy (pgsub->valb, "OFF") ;
     strcpy (pgsub->valc, "OFF") ;
     strcpy (pgsub->vald, "OFF") ;
     guideConfigReset = 0 ;
 } else if (guideConfigSetup) {

   guideConfigSetup = 0 ;

/* Always set weightC to OFF */
    strncpy (cString, "C-OFF  ", 9);

    if (filterType == 0) {
      sprintf (filterString, "%.8s", filterOpts[filterType]);
    } else {
     if(weightA < -1)
         strncpy(aString, "A-OFF  ", 9);
     else if(weightA < 0)
         strncpy(aString, "A-AUTO ", 9);
     else
         sprintf(aString, "A-%4.1f ", weightA);
   
     if(weightB < -1)
         strncpy(bString, "B-OFF  ", 9);
     else if(weightB < 0)
         strncpy(bString, "B-AUTO ", 9);
     else
         sprintf(bString, "B-%4.1f ", weightB);
   
     sprintf (filterString, "%.8s %s %s %s", filterOpts[filterType], aString,
                   bString, cString);
   
   
    }
   
    switch (wfsnum)
    {
      case 0 :
        strncpy (pgsub->vala, filterString, MAX_STRING_SIZE - 1) ;
        break ;
   
      case 1 :
        strncpy (pgsub->valb, filterString, MAX_STRING_SIZE - 1) ;
        break ;
   
      case 2 :
        strncpy (pgsub->valc, filterString, MAX_STRING_SIZE - 1) ;
        break ;
   
      case 3 :
        strncpy (pgsub->vald, filterString, MAX_STRING_SIZE - 1) ;
        break ;

      default :
        break ;
    }
 }
 
 return 0 ;

}


/*
 *   Function name:
 *   tcsM2toleranceCAD
 *
 *   Purpose:
 *   Emulate the M2 tolerance command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS tolerance command.
 *
 *   Invocation:
 *   tcsM2toleranceCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => X tilt tolerance
 *   b => Y tilt tolerance
 *   c => Z pos tolerance
 *   d => X pos tolerance
 *   e => Y pos tolerance
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsM2toleranceCAD (struct cadRecord *pcad)

{
  double xTiltTol = 0;
  double yTiltTol = 0;
  double xPosTol = 0;
  double yPosTol = 0;
  double zPosTol = 0;
  long status ;           /* Return status */
  char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
  char prefix[MAX_STRING_SIZE];            /* Name of CAD record */

/* Fetch name of CAD for use in messages */

    strcpy (cadname, strchr(pcad->name, ':') + 1) ;
    strcpy (prefix, cadname) ;
    strcat (prefix, ": ");

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {
     case menuDirectivePRESET :
     case menuDirectiveSTART :

      status = CAD_REJECT ;
/* At least can check that the tolerances are positive numbers */
     if (tcsDcDouble (prefix, pcad->a, &xTiltTol, pcad)) break ;
     if (xTiltTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 tolerance. Tol must be positive") ;
       return status ;
     }
     if (tcsDcDouble (prefix, pcad->b, &yTiltTol, pcad)) break ;
     if (yTiltTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 tolerance. Tol must be positive") ;
       return status ;
     }
     if (tcsDcDouble (prefix, pcad->c, &zPosTol, pcad)) break ;
     if (zPosTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 tolerance. Tol must be positive") ;
       return status ;
     }
     if (tcsDcDouble (prefix, pcad->d, &xPosTol, pcad)) break ;
     if (xPosTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 tolerance. Tol must be positive") ;
       return status ;
     }
     if (tcsDcDouble (prefix, pcad->e, &yPosTol, pcad)) break ;
     if (yPosTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "M2 tolerance. Tol must be positive") ;
       return status ;
     }
     status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}


/*+
 *   Function name:
 *   tcsM2moveBaffleCAD
 *
 *   Purpose:
 *   Emulate the M2 moveBaffle command
 *
 *   Description:
 *   This routine provides a minimal emulation of the SCS moveBaffle command.
 *
 *   Invocation:
 *   tcsM2moveBaffleCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => deployable baffle :  "retracted" | "near ir" | "visible" | "extended"
 *   b => central baffle : "closed" | "open"
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsM2moveBaffleCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char *centralOpts[] = {"OPEN", "CLOSED", NULL} ;
  char *deployOpts[]  = {"RETRACTED", "NEAR IR", "VISIBLE", "EXTENDED", NULL};
  static int  deployIndex ;
  static int  cenIndex ;

/* set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL);

  status = CAD_ACCEPT ;
  switch (pcad->dir) 
  {
   case menuDirectivePRESET :

     status = CAD_REJECT;

/* First check the requested deployable baffle demand */
     if (tcsDcString(deployOpts, " ", pcad->a, &deployIndex, pcad)) break ;
     if (tcsDcString(centralOpts, " ", pcad->b, &cenIndex, pcad)) break ;

     status = CAD_ACCEPT ;

   case menuDirectiveSTART:

/* Write the baffle positions to the output links */
     strcpy ( pcad->vala, deployOpts[deployIndex] );
     strcpy ( pcad->valb, centralOpts[cenIndex] );
     break;


   case menuDirectiveMARK:
   case menuDirectiveCLEAR:
   case menuDirectiveSTOP:
     break;

   default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}


/*+
 *   Function name:
 *   tcsM2parkCAD 
 *
 *   Purpose:
 *   Implement the SCS park command in the TCS internal simulator
 *
 *   Description:
 *   This routine simply takes in the default park positions for the
 *   Lockheed tip/tilt system and the XY stage and sends them on to
 *   the move command.
 *
 *   Invocation:
 *   tcsM2parkCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Default X tilt (arcsec)
 *      b => Default Y tilt (arcsec)
 *      c => Default X position (mm)
 *      d => Default Y position (mm)
 *      e => Default Z position (mm) 
 *
 *   EPICS output paramters:
 *      vala => X tilt park position for Beam A (arcsec)
 *      valb => Y tilt park position for Beam A (arcsec)
 *      valc => X tilt park position for Beam B (arcsec)
 *      vald => Y tilt park position for Beam B (arcsec)
 *      vale => X tilt park position for Beam C (arcsec)
 *      valf => Y tilt park position for Beam C (arcsec)
 *      valg => X park position (microns)
 *      valh => Y park position (microns)
 *      vali => Z park position (microns)
 * 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsM2parkCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double xpark, ypark, zpark ;   /* Park positions (mm) */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
  
   if (tcsDcDouble (" ", pcad->c, &xpark, pcad))
     xpark = 0.0;

   if (tcsDcDouble (" ", pcad->d, &ypark, pcad))
     ypark = 0.0 ;

   if (tcsDcDouble (" ", pcad->e, &zpark, pcad))
     zpark = 0.0;

   break ;

   case menuDirectiveSTART :

/* For tilt demands just copy inputs to outputs */
   strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   strncpy (pcad->valc, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->vald, pcad->b, MAX_STRING_SIZE) ;
   strncpy (pcad->vale, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->valf, pcad->b, MAX_STRING_SIZE) ;

/* Position demands must be scaled by 1000.0 */

   sprintf (pcad->valg, "%.1f", xpark*1000.0) ;
   sprintf (pcad->valh, "%.1f", ypark*1000.0) ;
   sprintf (pcad->vali, "%.1f", zpark*1000.0) ;

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
 *   tcsM2setController 
 *
 *   Purpose:
 *   Minimal implementation of setController command
 *
 *   Description:
 *   This simulation simply reads in the inputs without checking them
 *   and writes them to the outputs. Only the 9 parameters sent by
 *   the TCS are read.
 *
 *   Invocation:
 *   tcsM2setController (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => P term for X tilt 
 *      b => I term for X tilt 
 *      c => D term for X tilt 
 *      f => P term for focus 
 *      g => I term for focus 
 *      h => D term for focus 
 *      m => P term for Y tilt 
 *      n => I term for Y tilt 
 *      o => D term for Y tilt 
 *
 *   EPICS output parameters:
 *      vala => P term for X tilt 
 *      valb => I term for X tilt 
 *      valc => D term for X tilt 
 *      valf => P term for focus 
 *      valg => I term for focus 
 *      valh => D term for focus 
 *      valm => P term for Y tilt 
 *      valn => I term for Y tilt 
 *      valo => D term for Y tilt 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsM2setController (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
  
   break ;

   case menuDirectiveSTART :

/* Just copy inputs to outputs */
   strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
   strncpy (pcad->valf, pcad->f, MAX_STRING_SIZE) ;
   strncpy (pcad->valg, pcad->g, MAX_STRING_SIZE) ;
   strncpy (pcad->valh, pcad->h, MAX_STRING_SIZE) ;
   strncpy (pcad->valm, pcad->m, MAX_STRING_SIZE) ;
   strncpy (pcad->valn, pcad->n, MAX_STRING_SIZE) ;
   strncpy (pcad->valo, pcad->o, MAX_STRING_SIZE) ;

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
 *   tcsM2sSimulate
 *
 *   Purpose:
 *   Perform simulation of M2 including chopping
 *
 *   Description:
 *   This routine performs a simple simulation of M2. If M2 is stopped then
 *   the output is constant. If M2 is active then the output is just the 
 *   demand. If M2 is chopping then the output changes at approximately
 *   the correct frequency between the different chop states.
 *
 *   Invocation:
 *   tcsM2sSimulate (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to genSub record 
 *
 *   EPICS input parameters :
 *
 *   j => demand data array from TCS consisting of 
 *        the 14 type double data items as follows 
 *
 *    Time sent
 *    Time to be applied
 *    Track ID
 *    Chop A X tilt
 *    Chop A Y Tilt
 *    Chop B X tilt
 *    Chop B Y Tilt
 *    Chop C X tilt
 *    Chop C Y Tilt
 *    X position (micron)
 *    Y position (microns)
 *    Z focus (microns)
 *    tiltScale 
 *    focusScale
 * 
 *
 *    a => Selected WFS
 *    b => Default X Tilt (arcsec)
 *    c => Default Y Tilt (arcsec)
 *    d => Default X position (mm)
 *    e => Default Y position (mm)
 *    f => Default Z position (mm)
 *    g => PWFS1 guide signals 
 *    h => PWFS2 guide signals 
 *    i => OIWFS guide signals 
 *
 *
 *   EPICS outputs :
 *
 *   vala => Chopping (YES | NO) 
 *   valb => current xTilt (arcsec, M2 units)
 *   valc => current yTilt (arcsec, M2 units)
 *   vald => current x (microns)
 *   vale => current y (microns)
 *   valf => current z (microns)
 *   valg => Current chop beam (0 | 1 | 2)
 *   valh => status
 *   vali => trackid
 *   valj => disable or enable following processing chain
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */


long tcsM2sSimulate (struct genSubRecord *pgsub) 
{
   static int count = 0 ;
   static int first = TRUE;
   static int substat;        /* subsystem status */
   static double trackid;     /* current track id */
   unsigned long arraySize ;  /* number of elements in input demand array */
   double M2Sdemand[14] ;     /* Demand data array from the TCS */
   int i;                     /* Loop counter */
   long wfsnum;               /* Selected WFS index */

   double newtrack;           /* track id of demand */
   int newstat;               /* new subsystem status */
   int stateM2;               /* local copy of rotator state */
   int linkSelect;            /* Selects links for processing downstream */

   static double tappl;      /* time for which demands are correct */

   static int chopBeam[] = {0, 1, 0, 2} ;

   static double dt = 0.05;        /* Time step (secs) */
   static double kp = 0.05;        /* Proportional gain */
   static double ki = 0.5;         /* Integral gain */

   double intX , intY ;            /* Integrals of X & Y guide errors */

   long outBeam ;                  /* Output beam */
   double guideData[8] ;           /* Guide data */

   count++;

/* Get a local copy of M2 state as the global value may get changed
   from elsewhere */

   stateM2 = StateM2;

/* Read in input demand array data from kernel */
      arraySize = pgsub->noj ;
      memcpy(M2Sdemand, pgsub->j, arraySize * sizeof(double)) ;

/* Fetch guiding correction. For this simulation, the guiding corrections
 * are supplied in the correct units so we don't need to use the tilt and
 * focus scaling factors
 */

      wfsnum = *(long *)pgsub->a ;
      if (wfsnum == 1) {
        memcpy(guideData, pgsub->h, 8*sizeof(double));
      } else if (wfsnum == 2) {
        memcpy(guideData, pgsub->i, 8*sizeof(double));
      } else {
/* Default to using PWFS1 data for time being */
        memcpy(guideData, pgsub->g, 8*sizeof(double));
      }

      if (m2IsGuiding) {
        intX = guideData[2] * ki * dt + lastIntX;
        intY = guideData[3] * ki * dt + lastIntY;
        xGuide = intX + guideData[2] * kp ;
        yGuide = intY + guideData[3] * kp ;
        zGuide = guideData[4];
        lastIntX = intX ;
        lastIntY = intY ;
      } 

      tappl      = M2Sdemand[1] ;
      newtrack   = M2Sdemand[2] ;
      xTiltDemand[0] = M2Sdemand[3] + xGuide;
      yTiltDemand[0] = M2Sdemand[4] + yGuide;
      xTiltDemand[1] = M2Sdemand[5] + xGuide;
      yTiltDemand[1] = M2Sdemand[6] + yGuide;
      xTiltDemand[2] = M2Sdemand[7] + xGuide;
      yTiltDemand[2] = M2Sdemand[8] + yGuide;
      xDemand        = M2Sdemand[9];
      yDemand        = M2Sdemand[10];
      zDemand        = M2Sdemand[11] + zGuide ;
 
      if (first)            /* Initialise servo simulator */
      {
         xTiltDemand[0] = *(double *)pgsub->b;
         yTiltDemand[0] = *(double *)pgsub->c;
         xTiltDemand[1] = *(double *)pgsub->b;
         yTiltDemand[1] = *(double *)pgsub->c;
         xTiltDemand[2] = *(double *)pgsub->b;
         yTiltDemand[2] = *(double *)pgsub->c;
         xDemand        = *(double *)pgsub->d * 1000.0;
         yDemand        = *(double *)pgsub->e * 1000.0;
         zDemand        = *(double *)pgsub->f * 1000.0;
         substat = -1;
         newstat = menuCarstatesIDLE;
         trackid = 0.0;
         first = FALSE;
      }

      if ( stateM2 == STOPPED || stateM2 == MOVING )
      {
        for (i = 0; i < 3; i++)
        {
         xTiltDemand[i] = xTiltTarget[i];
         yTiltDemand[i] = yTiltTarget[i];
        }
        xDemand = xTarget;
        yDemand = yTarget;
        zDemand = zTarget;
      }

/* Set the link selection field and update the subsystem state */

      linkSelect = 0;
      newstat = menuCarstatesIDLE;
      if ( stateM2 == MOVING ) 
      {
         StateM2 = STOPPED;
         linkSelect += 1;
      }
      if (newstat != substat)
      {
         substat = newstat;
         linkSelect += 2;
      }
      if (newtrack != trackid)
      {
         trackid = newtrack;
         linkSelect +=4;
      } 
   
/* now output the results */

      outBeam = 0 ;
      if (chopping) {
       strcpy (pgsub->vala, "YES") ;
       if (chopMode == TWOPOSN || chopMode == TRIANGLE) {
        if (freqCounter == freqTicks) {
         currentChopIndex = currentChopIndex ? 0 : 1 ;
         outBeam = currentChopIndex ;
         freqCounter = 0 ;
        }
        else
         freqCounter++ ;

       } else {                 /* Three position chopping */
        if (freqCounter == freqTicks) {
         currentChopIndex++ ;
         if (currentChopIndex > 3)
           currentChopIndex = 0 ;
         freqCounter = 0 ;
        }
        else
         freqCounter++ ;
       }
        outBeam = chopBeam[currentChopIndex] ;
        *(double *)pgsub->valb = xTiltDemand[outBeam];
        *(double *)pgsub->valc = yTiltDemand[outBeam];

      } else {                /* No chopping */
        strcpy( pgsub->vala, "NO") ;
        outBeam = defaultBeam ;
        *(double *)pgsub->valb = xTiltDemand[defaultBeam];
        *(double *)pgsub->valc = yTiltDemand[defaultBeam];
      }

      *(double *)pgsub->vald = xDemand ;
      *(double *)pgsub->vale = yDemand ;
      *(double *)pgsub->valf = zDemand ;
      *(long *)pgsub->valg   = outBeam ;
      *(double *)pgsub->valh = substat;
      *(double *)pgsub->vali = trackid;
      *(long *)pgsub->valj   = linkSelect;

   return 0;
}
  
/* Routine to signal action completion of the MOVE command */

long tcsM2sComplete (genSubRecord *psub)
{

/* output values */

   strcpy(psub->valb, "Stopped");
   *(double *)psub->vala = menuCarstatesIDLE;
   return 0;
}

/*+
 *   Function name:
 *   tcsM2Stop
 *
 *   Purpose:
 *   Stops the mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsM2Stop
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *-
 */

long tcsM2Stop (struct genSubRecord *pgsub)
{
   StateM2 = STOPPED;
   strncpy(pgsub->vala, "Off", 3);
   return(0);
}


/*+
 *   Function name:
 *   tcsM2GenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the M2
 *
 *   Description:
 *
 *   Invocation:
 *   tcsM2TestCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   Only responds to the START directive
 *
 *-
 */

long tcsM2GenericCAD (struct cadRecord *pcad)
{
   int status;                /* return status */
   char command[29];          /* command name */
   int i, j;                  /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
   for ( i = 0, j = 0; i < 29; i++, j++ )
   {
      command[j] = pcad->name[i];
      if ( !(pcad->name[i]) ) break;
      if ( command[j] == ':' ) j = -1;
   }

   switch(pcad->dir)
   {
   case menuDirectiveSTART:

   /* write output message (n.b. no more that 28 characters) */
      sprintf(pcad->mess, "M2: %.16s started", command);
 /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"Off");
      else
      {
/* Copy over the parameters to the output fields */

       strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
       strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
       strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
       strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
       strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
       strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
       }
      status = CAD_ACCEPT;
      break;

   default:
      status = 0;
      break;
   }
   return(status);
}
epicsRegisterFunction(tcsM2beamJogCAD);
epicsRegisterFunction(tcsM2GenericCAD);
epicsRegisterFunction(tcsM2guideConfigCAD);
epicsRegisterFunction(tcsM2setController);
epicsRegisterFunction(tcsM2sSimulate);
epicsRegisterFunction(tcsGuideConfig);
epicsRegisterFunction(tcsM2Stop);
epicsRegisterFunction(tcsM2ChopConfig);
epicsRegisterFunction(tcsM2guideConfigResetCAD);
epicsRegisterFunction(tcsM2clearGuideFocusCAD);
epicsRegisterFunction(tcsM2clearTiltGuideCAD);
epicsRegisterFunction(tcsM2moveBaffleCAD);
epicsRegisterFunction(tcsM2sComplete);
epicsRegisterFunction(tcsM2ChopControl);
epicsRegisterFunction(tcsM2MoveCAD);
epicsRegisterFunction(tcsM2exposuretimeCAD);
epicsRegisterFunction(tcsM2guideCAD);
epicsRegisterFunction(tcsM2FollowCAD);
epicsRegisterFunction(tcsM2parkCAD);
epicsRegisterFunction(tcsM2toleranceCAD);
epicsRegisterFunction(tcsM2GuideErrors);
