/*
   *   FILENAME
   *   tcsAgsSimulation.c
   *
   *   This module holds the routines that are used in the MCS Simulation 
   *
   *   FUNCTION NAME(S)
   *   gemAb2xy     - convert probe angles to x and y
   *   gemXy2ab     - convert x and y to probe angles
   *   tcsAgInitCAD - initialise variables for the A & G simulator
   *   tcsAgMoveCAD - implement the A & G move command
   *   tcsAgsAo       - generate simulated WFS data
   *   tcsAgsSimulate - simulate the movement of the mount
   *   tcsAgsComplete - signal completion of a move command
   *   tcsAgsOiwfsCoeffs - provide oiwfs transformation coefficients
   *   tcsAgsSetCalParms - set calibration parameters
   *   tcsAgsStop - stop subsystem
   *   tcsGenericCAD - general purpose CAD routine
   *   tcsAgParkCAD - park mechanism
   *   tcsAGoiwfsSelCAD - simulate the oiwfsSel command in the A&G sequencer
   *   tcsOidetSigInitCAD - implement the OIWFS detsigInit command
   *   tcsOidetSigModeAo - set Ao observing mode parameters
   *   tcsOidetSigModeSeq - sequence closed loop command
   *   tcsOidetSigModeSeqDark - sequence dark command
   *   tcsOiobserveCAD - implement the OIWFS observe command
   *   tcsP1detSigModeAo - set Ao observing mode parameters
   *   tcsP1detSigModeSeq - sequence closed loop command
   *   tcsP1detSigModeSeqDark - sequence dark command
   *   tcsP1detSigInitCAD - implement the PWFS1 detsigInit command
   *   tcsP1observeCAD - implement the PWFS1 observe command
   *   tcsP2detSigModeAo - set Ao observing mode parameters
   *   tcsP2detSigModeSeq - sequence closed loop command
   *   tcsP2detSigModeSeqDark - sequence dark command
   *   tcsP2detSigInitCAD - implement the PWFS1 detsigInit command
   *   tcsP2observeCAD - implement the PWFS2 observe command
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsAgsSimulation.c,v $
 * Revision 1.32  2013/10/31 13:27:07  cjm
 * Increase number of Zernikes from OIWFS to 19
 *
 * Revision 1.31  2011/05/25 19:20:11  gemvx
 * Changed NIRS for GNIRS in OI selection DM screens.
 *
 * Revision 1.30  2010/02/01 15:00:21  ajf
 * Split-up the schematic, "agSimWfsData.sch", which puts out the individual WFS Zernike
 * terms into AO records.
 * This contained wires which crossed ports on a record. This is not allowed in "tdct"
 * and leads to a wiring confusion.
 * Modify "tcsAgsSimulation.c", to include an extra "genSub" routine which is used to
 * put out the individual Zernike terms. This is required for the newly designed schematic
 * "agWfsExpectedZernikes.sch".
 *
 * Revision 1.29  2008/05/01 15:24:42  cjm
 * Add code to support fetching of A&G CalParms
 *
 * Revision 1.28  2006/11/24 10:30:22  cjm
 * Improved simulation of AO fold, HW arm and science fold
 *
 * Revision 1.27  2006/11/13 13:11:15  cjm
 * Update table parameters and set error terms
 *
 * Revision 1.26  2006/04/21 12:47:17  cjm
 * Rework guiding to support sky simulator
 *
 * Revision 1.25  2005/12/13 08:48:46  cjm
 * Extend valid OIWFS names and modify guide simulator
 *
 * Revision 1.24  2005/11/18 16:55:29  cjm
 * Fix typo in simulator for P1 & P2
 *
 * Revision 1.23  2005/11/17 15:34:37  cjm
 * Implement closed loop control for probe guiding
 *
 * Revision 1.22  2005/11/16 15:24:51  cjm
 * First pass at generating artificial WFS data
 *
 * Revision 1.21  2004/03/24 14:52:38  cjm
 * Support detSigModeAo commands and use the aoTime when generating simulated zernikes
 *
 * Revision 1.20  2003/10/17 16:34:33  gemvx
 * Add code to handle extra wfs cads
 *
 * Revision 1.19  2003/06/24 11:30:20  cjm
 * Calculate the minimum radius the probes can reach
 *
 * Revision 1.18  2002/11/22 00:11:52  cjm
 * Provide simulation of transform coeffs for OIWFS
 *
 * Revision 1.17  2002/02/19 17:16:03  ajf
 * Make the A&G simulator the same as the real A&G with regard to
 * setting the "followS" record. This difference was causing problems
 * for the higher level TCL software.
 *
 * Revision 1.16  2001/11/06 13:36:27  cjm
 * Fix typo that was setting wrong variable when setting no. of Zernikes for oiwfs
 *
 * Revision 1.15  2001/10/05 09:04:21  cjm
 * New routine tcsAgsOiwfsCoeffs
 *
 * Revision 1.14  2001/09/10 15:04:44  cjm
 * add code to support oiwfsSel command
 *
 * Revision 1.13  2001/09/02 15:06:21  cjm
 * Fix typo that put data on C not VALC
 *
 * Revision 1.12  2001/05/25 07:21:48  cjm
 * Correct typo in include file name andremove final trace of mosub record
 *
 * Revision 1.11  2001/05/17 14:50:37  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.10  2001/05/06 00:05:44  cjm
 * Change probe simulations to work in table and arm angles rather than x and y
 *
 * Revision 1.9  2000/04/13 08:25:56  dlt
 * Add probe in position flags
 *
 * Revision 1.8  1999/11/27 02:52:22  cjm
 * Remove startMeasure & stopMeasure commands and add new observe commands to match latest WFS implementation
 *
 * Revision 1.7  1999/10/14 11:26:20  cjm
 * Fix output message for tolerance command
 *
 * Revision 1.6  1999/06/16 21:26:47  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.5  1999/02/02 04:39:50  cjm
 * Added a routine to handle the stopMeasure command and enhanced the subroutine that generates aO data
 *
 * Revision 1.4  1999/01/21 20:52:14  cjm
 * Allow QUIRC as valid science fold position
 *
 * Revision 1.3  1999/01/15 19:48:46  cjm
 * Modify for new peek command (formerly observe) and new startMeasure and calibrate parameters
 *
 * Revision 1.2  1999/01/05 16:58:42  epics
 * Implement changes to make startMeasure match the latest changes to the TCS/A&G ICD
 *
 * Revision 1.1.1.1  1998/11/08 00:21:09  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.22  1998/09/05 03:24:41  tcs
 * Remove redundant routine tcsAgDatumVals
 *
 * Revision 1.21  1998/08/10 10:10:32  dlt
 * Write fold mirror states to outputs
 *
 * Revision 1.20  1998/07/28 08:44:51  tcs
 * Only handle one set of probe demands not one for each chop state
 *
 * Revision 1.19  1998/01/08 16:39:33  cjm
 * Better error checking in startMeasure command
 *
 * Revision 1.18  1997/12/16 08:11:00  cjm
 * Add support for maintaining measuring status
 *
 * Revision 1.17  1997/12/11 15:21:29  pbt
 * Amended routines for WFS data handling
 *
 * Revision 1.16  1997/12/10 17:34:57  pbt
 * Add routines for WFS data handling genSub records
 *
 * Revision 1.15  1997/12/09 12:10:37  pbt
 * Add STOP directive handling to observe routine
 *
 * Revision 1.14  1997/12/08 17:50:52  pbt
 * Added routines for WFS processing
 *
 * Revision 1.13  1997/12/02 15:35:09  pbt
 * Add routine for setOrient
 *
 * Revision 1.12  1997/11/20 15:26:11  pbt
 * Add output of VALA in Beam Direction command routines
 *
 * Revision 1.11  1997/11/20 12:33:55  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.10  1997/11/18 15:19:18  pbt
 * Add datum status string handling
 *
 * Revision 1.9  1997/11/14 16:19:55  pbt
 * Changes with new simulated A&G commands and records
 *
 * Revision 1.8  1997/11/03 08:48:16  cjm
 * Initialise probe demand velocities to 0
 *
 * Revision 1.7  1997/10/24 16:16:52  pbt
 * Changes to A&G simulation - set CAR status correctly
 *
 * Revision 1.6  1997/09/24 16:31:18  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.5  1997/09/23 11:33:48  tcs
 * Correct probe index range
 *
 * Revision 1.4  1997/09/19 16:31:26  pbt
 * Added A&G Beam Direction command handling
 *
 * Revision 1.3  1997/04/16 15:57:19  pbt
 * Use symbol CAD_REJECT consistently
 *
 * Revision 1.2  1997/03/05 10:06:32  tcs
 * Update servo parameters
 *
 * Revision 1.1  1997/02/10 17:10:14  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.16  1997/01/20 09:06:37  cjm
 * Add servo control of z probe motion
 *
 * Revision 1.15  1997/01/09 21:38:47  cjm
 * Follow the specified chop state and bug fixes
 *
 * Revision 1.14  1996/12/11 11:47:57  tcs
 * cosmetic improvements
 *
 * Revision 1.13  1996/12/10 17:58:24  pbt
 * Simulator CADs now set followS value via output VALA field
 *
 * Revision 1.12  1996/12/06 15:16:23  pbt
 * Changed accleration and in position servo parameters
 *
 * Revision 1.11  1996/11/28 08:09:03  cjm
 * Fix triggering of activeC and trackid
 *
 * Revision 1.10  1996/11/27 14:47:47  pbt
 * Added servo simulation for X and Y probe positions
 *
 * Revision 1.9  1996/11/25 12:35:45  pbt
 * Changed simulation to use GenSub record
 *
 * Revision 1.8  1996/11/12 18:05:33  pbt
 * Various updates : STOP command and MOVE command default parameters
 *
 * Revision 1.7  1996/10/25 09:17:41  cjm
 * Move derotation of probes from A&G to TCS
 *
 * Revision 1.6  1996/07/30 09:49:39  tcs
 * Correct guide probe positions for non-perp
 *
 * Revision 1.5  1996/07/25 08:13:05  tcs
 * allow FOLLOW with no parameter
 *
 * Revision 1.4  1996/07/23 14:59:16  tcs
 * tidy up routine names and add header to include files
 *
 * Revision 1.3  1996/07/23 10:03:39  tcs
 * Add TEST & PARK plus generic CAD mechanism
 *
 * Revision 1.2  1996/07/22 11:39:00  tcs
 * fix MOVE command
 *
 * Revision 1.1  1996/07/19 13:40:44  tcs
 * A & G simulator
 *
 * Revision 1.12  1996/07/12 14:51:37  tcs
 * improved servo algorithm
 *
 * Revision 1.11  1996/07/09 13:18:04  tcs
 * revised track id logic and enhanced simulators
 *
 * Revision 1.10  1996/07/08 14:29:35  tcs
 * Implement track identifier scheme
 *
 * Revision 1.9  1996/06/24 14:22:51  tcs
 * generate azimuth and rotator angles in range -270/+270
 *
 * Revision 1.8  1996/06/21 13:50:17  tcs
 * elevation limit and MOVE logic changes
 *
 * Revision 1.7  1996/06/17 07:29:39  cjm
 * Tidy up, add control of error term etc.
 *
 */
/* *INDENT-ON* */



#include <string.h>
#include <epicsStdioRedirect.h>
#include <math.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>
#include <dbCommon.h>
#include <recSup.h>

#include "tcsAgs.h"
#include "tcsConstants.h"
#include "slalib.h"
#include "tcsServo.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "timeLib.h"
#include "tcsRandom.h"

/* Guide probe limits (mm) */
#define MAXX 500.0
#define MAXY 500.0
#define MAXZ 50.0

/* Data for x,y to table and arm angle */
#define M1TOFPLANE 18335.5393

static double heights[] = {1995.0, 1610.0, 0.0} ;     /* mm above focal plane */
static double probeLen[] = {391.04, 397.79, 0.0} ;    /* mm */
static double bearRadius[] = {396.91, 397.48, 0.0} ;  /* mm */
static double xyscale[] = {1.0, -1.0, 1.0} ;          /* scale factor for x,y */

/* Guide probe states */
static int StateProbe[3];

/* probe position (3 guide probes ) X and Y are angles (degs) for P1 and
*  P2 anf mm for the OIWFS
*/

static double x[3];
static double y[3];
static double z[3];

/* Demand position from MOVE command (3 guide probes). Note that the target
*  positions are in degrees for probe 1 and 2 for x and y but mm for
*  the OIWFS.
*/

static double xtarget[3];
static double ytarget[3];
static double ztarget[3];

/* Target position in focal plane (mm for all probes) */
static double xftarget[3];
static double yftarget[3];

/* Parameters set by the start/stop measure command. These are used when 
*  generating artificial Zernike data.
*/

static double agP1AoInterval = 60.0;    /* PWFS1 coadd time (secs) */
static double agP2AoInterval = 60.0;    /* PWFS2 coadd time (secs) */
static double agOiwfsAoInterval = 60.0; /* OIWFS coadd time (secs) */
static int agP1Measuring ;      /* TRUE when PWFS1 is in use */
static int agP2Measuring ;      /* TRUE when PWFS2 is in use */
static int agOiwfsMeasuring ;   /* TRUE when OIWFS is in use */
static int agP1NumZern = 10;    /* Number of Zernike terms */
static int agP2NumZern = 5;     /* Number of Zernikes measured by PWFS2 */
/* Set this to the maximum number of terms possible. This might not be 
*  true for all OIWFS but for this simulation it is the best choice
*/
static int agOiwfsNumZern = 19;  /* Number of Zernikes measured by OIWFS */ 

/* Default transformation coefficients for OIWFS */
static double tcs2oiwfs[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
static int currentOiwfs = 0 ;
                                  
/*+
 *   Function name:
 *   tcsAgInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the A&G control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the A&G control system.
 *
 *   Invocation:
 *   tcsAgInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure
 *
 *   Prior requirements:
 *   None
 *
 *-
 */

void tcsAgInit(void)
{
    static int first = TRUE;
    int i;

    if (first)
        first = FALSE;
    for (i = 0; i < 3; i++) {
        StateProbe[i] = STOPPED;
    }
}

/*+
 *   Function name:
 *   tcsAgFollowCAD
 *
 *   Purpose:
 *   Implement the follow CAD record in the A & G  simulator
 *
 *   Description:
 *   This function implements the follow CAD record in the A&G simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. Since all the 
 *   data is being transmitted to separate records the function of this
 *   routine is simply to set some internal flags that signal the internal
 *   state of the simulator to other pieces of code.
 *
 *   Invocation:
 *   tcsAgFollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */

long tcsAgFollowCAD(struct cadRecord *pcad)
{
  static long iprobe;
  long status ;

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;

  switch (pcad->dir) {
  case menuDirectivePRESET:
    if (tcsDcLong ("probe: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 3) {
      tcsCsAppendMessage (pcad, "number out of range") ;
      break ;
    }
    iprobe-- ;
    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART:
    StateProbe[iprobe] = FOLLOWING;
    strcpy(pcad->vala, "ON");
    status = CAD_ACCEPT ;
    break;          

  case menuDirectiveSTOP:
    if (tcsDcLong ("probe: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 3) {
      tcsCsAppendMessage (pcad, "number out of range") ;
      break ;
    }
    iprobe--;
    StateProbe[iprobe] = STOPPED;
    strcpy(pcad->vala, "OFF");
    break ;

  default:
      break;
  }

  return status ;
}

/*+
 *   Function name:
 *   tcsAgMoveCAD
 *
 *   Purpose:
 *   Implement the Move CAD record in the A & G  simulator
 *
 *   Description:
 *   This function implements the move CAD record in the A&G simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. 
 *
 *   Epics inputs :
 *
 *   a => X position
 *   b => Y position
 *   c => Z position 
 *   d => probe number
 *
 *   Invocation:
 *   tcsAgMoveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<) status  (long)  return status, 0 = OK
 *
 *-
 */

long tcsAgMoveCAD(struct cadRecord *pcad)
{
  static double xin, yin, zin;
  static long iprobe ;                      /* Probe number 1 to 3 initially */
  int ret ;
  long status ;
  static double a1, a2, b1, b2 ;            /* Angles of probes (rads) */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;
    
  switch (pcad->dir) {
    case menuDirectivePRESET:
      if (tcsDcLong("Probe: ", pcad->d, &iprobe, pcad) ) break ;
      if (iprobe < 1 || iprobe > 3) {
        tcsCsAppendMessage (pcad, "number out of range") ;
        break ;
      } 

      iprobe-- ;

      if (tcsDcDouble("x: ", pcad->a, &xin, pcad) ) break ;
      if (xin < -MAXX || xin > MAXX) {
        tcsCsAppendMessage (pcad, "out of range") ;
        break ;
      }
      if (tcsDcDouble("y: ", pcad->b, &yin, pcad) ) break ;
      if (yin < -MAXY || yin > MAXY) {
        tcsCsAppendMessage (pcad, "out of range") ;
        break ;
      }
      if (tcsDcDouble("z: ", pcad->c, &zin, pcad) ) break ;

      if (iprobe < 2 ) {
        ret = gemXy2ab (xin*xyscale[iprobe], yin*xyscale[iprobe],
                  M1TOFPLANE, heights[iprobe], 
                  bearRadius[iprobe], probeLen[iprobe], &a1, &b1, &a2, &b2) ; 
        if (ret == -2) {
          tcsCsAppendMessage (pcad, "can't reach position") ;
          break ;
        } else if ( ret != 0) {
          tcsCsAppendMessage (pcad, "error computing angles") ;
          break ;
        }
      }
      status = CAD_ACCEPT ;
      break ;

    case menuDirectiveSTART:
      xftarget[iprobe] = xin;
      yftarget[iprobe] = yin;
      ztarget[iprobe] = zin;
      if (iprobe < 2) {
        xtarget[iprobe] = a2 * R2D ;
        ytarget[iprobe] = b2 * R2D ;
      } else {
        xtarget[iprobe] = xin ;
        ytarget[iprobe] = yin ;
      }
      StateProbe[iprobe] = MOVING;
      strcpy(pcad->vala, "OFF");         /* Set follow mode off  */
      status = CAD_ACCEPT ;

      break;                

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */

    case menuDirectiveSTOP:
      if (tcsDcLong("Probe: ", pcad->d, &iprobe, pcad) ) break ;
      if (iprobe < 1 || iprobe > 3) {
        tcsCsAppendMessage (pcad, "number out of range") ;
        break ;
      } 

      strcpy(pcad->vala, "OFF");
      break;

    default:
        break;
    }

    return status ;

}

/*+
 *   Function name:
 *   tcsAGfocusSelCAD
 *
 *   Purpose:
 *   Implement the Move focus CAD record in the A & G  simulator
 *
 *   Description:
 *   This function implements the move CAD record in the A&G simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. 
 *
 *   Inputs :
 *
 *   a => focus position (mm)
 *
 *   Invocation:
 *    tcsAGfocusSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<) status  (long)  return status, 0 = OK
 *
 *-
 */

long tcsAGfocusSelCAD(struct cadRecord *pcad)
{
    double zin;
    int nitem, zNitem, iprobe;

/* The CAD directive is field  DIR */
    switch (pcad->dir) {
    case menuDirectiveSTART:
    case menuDirectivePRESET:
        strcpy(pcad->mess, "Move: arguments are valid");
        nitem = sscanf(pcad->d, "%d ", &iprobe);
        if (nitem != 1) {
            strcpy(pcad->mess, "Move: probe number is invalid");
            return CAD_REJECT;
        } else if (iprobe < 1 || iprobe > 3) {
            strcpy(pcad->mess, "Follow: probe number out of range");
            return CAD_REJECT;
        } else {
            iprobe--;
            zNitem = sscanf(pcad->a, "%lf ", &zin);
            if (zNitem < 1) {
                zin = z[iprobe];
            } else if (zin < -MAXZ || zin > MAXZ) {
                strcpy(pcad->mess, "focusSel: z out of range");
                return CAD_REJECT;
            }
/* Set MOVE target for Z. Get X,Y values from current positions */
            ztarget[iprobe] = zin;
            xtarget[iprobe] = x[iprobe];
            ytarget[iprobe] = y[iprobe];
            if (pcad->dir == menuDirectiveSTART) {
                StateProbe[iprobe] = MOVING;
            }
            strcpy(pcad->vala, "OFF");
            strcpy(pcad->mess, "Command accepted");

        }
        return 0;
        break;                  /* End PmenuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
    case menuDirectiveSTOP:
        strcpy(pcad->mess, "Move: argument is valid");
        nitem = sscanf(pcad->d, "%d ", &iprobe);
        if (nitem != 1) {
            strcpy(pcad->mess, "Move: probe number is invalid");
            return CAD_REJECT;
        } else if (iprobe < 1 || iprobe > 3) {
            strcpy(pcad->mess, "Move: probe number out of range");
            return CAD_REJECT;
        }
        StateProbe[--iprobe] = STOPPED;

/* Output acceptance message */
        strcpy(pcad->vala, "OFF");
        strcpy(pcad->mess, "Command accepted");
        return 0;
        break;

    default:
        return 0;
        break;
    }
}

/*+
 *   Function name:
 *   tcsAGoiwfsSelCAD
 *
 *   Purpose:
 *   Implement the oiwfsSel command in the A&G simulator
 *
 *   Description:
 *   This is a minimal simulation of the command that simply checks the
 *   incoming parameters for validity and then outputs them on the 
 *   output links.
 *
 *   Invocation:
 *    tcsAGoiwfsSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<) status  (long)  return status, 0 = OK
 *
 *   Epics Inputs :
 *   a => Demand OIWFS  
 *   b => Where to send the data
 *
 *   Epics outputs:
 *   vala => selected OIWFS
 *   valb => selected system to process the data
 *-
 */

long tcsAGoiwfsSelCAD(struct cadRecord *pcad)
{
  long status ;           /* Return status */
  static char *oiwfsNames[] = {"NONE", "GMOS", "NIRI", "GNIRS", "F2", "NIFS",
                               "BHROS", "NICI", "SPARE", NULL} ;
  static char *outNames[] = {"NONE", "WFS", "AO"} ;
  static int oiwfsIndex ;
  static int outIndex ;

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

/* The CAD directive is field  DIR */
    switch (pcad->dir) {

    case menuDirectivePRESET:

      status = CAD_REJECT ;

/* If no instrument is specified then default to "NONE" */
      if (!tcsDcLen(pcad->a)) {
        oiwfsIndex = 0 ;
      } else {
        if (tcsDcString (oiwfsNames, " ", pcad->a, &oiwfsIndex, pcad)) break ;
      }

      if (oiwfsIndex != 0) {
        if (tcsDcString (outNames, " ", pcad->b, &outIndex, pcad)) break ;
        if (outIndex == 0) {
          tcsCsAppendMessage(pcad, "Must select a processing system") ;
          break ;
        }
      }

    status = CAD_ACCEPT ;
    break;             

    case menuDirectiveSTART:

      currentOiwfs = oiwfsIndex ;
      strcpy(pcad->vala, pcad->a) ;
      strcpy(pcad->valb, pcad->b) ;
      break ;

    case menuDirectiveSTOP:
    break;

    case menuDirectiveCLEAR:
    break;

    default:
    break;
    }

    return status ;
}


/*+
 *   Function name:
 *   tcsAgsSimulate
 *
 *   Purpose:
 *   Simulates behaviour of the A & G without any hardware
 *
 *   Description:
 *   This routine is linked to the tcsAgsSimulate record and performs the main
 *   simulation of the A & G. Prior to the initial release of
 *   the A&G, the TCS sent demands for all three chop states. This has
 *   now been changed to send only one set of demands.
 *   Also, this simulation originally worked in x and y. It was later found 
 *   that a more realistic simulation was required that was more similar
 *   to the real rotary table/probe mechanisms in the A&G. Due to this, 
 *   the naming of the variables in this routine can be confusing. For P1
 *   and P2 x variables refer to rotary table angle and y variables contain
 *   probe arm angles.
 *   
 *
 *   Inputs :
 *
 *   b => probe number
 *   d => default startup x position (mm or degs)
 *   f => default startup y position (mm or degs)
 *   h => default startup z position (mm)
 *   l => maximum probe velocity
 *   n => X and Y position tolerances
 *   o => Z position tolerance
 *   j => Input demand array from TCS:
 *    Element 0  = Time now
 *    Element 1  = Target time
 *    Element 2  = Track identifier
 *    Element 3  = Demanded X position 
 *    Element 4  = Demanded Y position 
 *    Element 5  = Demanded Z position 
 *
 *   Outputs :
 * 
 *   vala => time at which positions apply
 *   valb => current x (mm)
 *   valc => current y (mm)
 *   vald => current z (mm)
 *   vale => x error (mm)
 *   valf => y error (mm)
 *   valg => z error (mm)
 *   valh => X and Y tolerance (mm)
 *   vali => Z tolerance (mm)
 *   valh => status
 *   vali => trackid
 *   valj => disable or enable following processing chain
 *   valk => in position flag
 *   vall => RT angle
 *   valm => PA angle
 *   valn => Quality of stream of input demands
 *
 *   Invocation:
 *   tcsAgsSimulate(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Deficiencies:
 *   The calculations assume the record is being scanned at 20Hz (through a
 *   constant DT). It should fetch the scan rate from the .SCAN field
 *
 *-
 */

long tcsAgsSimulate(struct genSubRecord *pgsub)
{
    static int count[3] =
    {0, 0, 0};

    static int first[3] =
    {TRUE, TRUE, TRUE};
    static int substat[3];      /* subsystem status */
    static double trackid[3];   /* current track id */

    int iprobe;                 /* probe number */
    double now;                 /* current time */
    unsigned long arraySize;    /* number of elements in inout demand array */
    double AGSdemand[12];       /* demand data array from kernel */
    double xdemand ;            /* Follow x demand */
    double ydemand ;            /* Follow y demand */
    double zdemand ;            /* Follow z demand */
    double xft, yft ;           /* Targets in mm for probe 1 and 2 */
    double rtangle ;            /* Rotary table position */
    double pangle ;             /* Probe arm angle */
    double xnow, ynow, znow;    /* X,Y,Z servo demands */
    double xdemandv, ydemandv;  /* X,Y demand velocity */
    double zdemandv;            /* Z demand velocity */
    double newtrack;            /* track id of demand */
    int newstat;                /* new subsystem status */
    int stateProbe[3];          /* local copy of probe states */
    int linkSelect;             /* Mask for downstream processing */
    double a1, a2, b1, b2 ;     /* Table and probe angles (rads) */
    int ret ;                   /* return status */
    double xfplane, yfplane ;   /* Probe position in focal plane (mm) */
    double xferr, yferr ;       /* x,y errors in focal plane */
    char arrayS[20] ;           /* State of incoming data */

    double fscale ;             /* Focal plane scaling factor for probes */
    double minRad ;             /* Minimum radius probes can reach (mm) */

    double tappl;               /* time for which demands are correct */
    static int inPositionX[3];         /* X now in position flag */
    static int inPositionY[3];         /* Y now in position flag */
    static int inPositionZ[3];         /* Z now in position flag */
    static int inPosition[3] =    {FALSE, FALSE, FALSE };   /* X, Y and Z all in position */
    static double tlast[3];     /* Time at last entry */
    static double xlast[3];     /* Previous X demands */
    static double ylast[3];     /* Previous Y demands */
    static double zlast[3];     /* Previous Z demands */
    static double xvel[3];      /* Current X probe velocity */
    static double yvel[3];      /* Current Y probe velocity */
    static double zvel[3];      /* Current Z probe velocity */
    static double xerr[3];      /* Current X position error */
    static double yerr[3];      /* Current Y position error */
    static double zerr[3];      /* Current Z position error */

    static struct ServoState servoStateX[3];
    static struct ServoState servoStateY[3];
    static struct ServoState servoStateZ[3];
    static struct ServoConfig servoConfigX[3];
    static struct ServoConfig servoConfigY[3];
    static struct ServoConfig servoConfigZ[3];

    count[0]++;
    count[1]++;
    count[2]++;

/*  Get probe number and current chop state */
    iprobe = floor(*(double *) pgsub->b);
    iprobe--;

/*   Get a local copy of the probe state as the global values may get changed
   from elsewhere */
    stateProbe[iprobe] = StateProbe[iprobe];

    if (first[iprobe]) {

/* Set servo initial values */
        servoConfigZ[iprobe].dvmax = 12.5;
        servoConfigZ[iprobe].gs = 4.0;
        servoConfigZ[iprobe].gp = 1.0;
        servoConfigZ[iprobe].gi = 0.1;
        servoConfigZ[iprobe].pi = 1.0;
        servoConfigZ[iprobe].tok = 0.5;
        servoStateZ[iprobe].pdtold = *(double *) pgsub->h;
        servoConfigZ[iprobe].noise = 0.0;
        timeNow(&(servoStateZ[iprobe].told));
        servoStateZ[iprobe].told -= 0.05;
        servoStateZ[iprobe].tout = servoStateZ[iprobe].told;
        servoStateZ[iprobe].vd = 0.0;
        servoStateZ[iprobe].accum = 0.0;
        z[iprobe] = servoStateZ[iprobe].pdtold;
        zvel[iprobe] = 0.0;
        servoConfigX[iprobe].dvmax = 12.5;
        servoConfigX[iprobe].gs = 4.0;
        servoConfigX[iprobe].gp = 1.0;
        servoConfigX[iprobe].gi = 0.1;
        servoConfigX[iprobe].pi = 1.0;
        servoConfigX[iprobe].tok = 0.5;
        servoStateX[iprobe].pdtold = *(double *) pgsub->d;
        servoConfigX[iprobe].noise = 0.0;
        timeNow(&(servoStateX[iprobe].told));
        servoStateX[iprobe].told -= 0.05;
        servoStateX[iprobe].tout = servoStateX[iprobe].told;
        servoStateX[iprobe].vd = 0.0;
        servoStateX[iprobe].accum = 0.0;
        x[iprobe] = servoStateX[iprobe].pdtold;
        xvel[iprobe] = 0.0;
        servoConfigY[iprobe].dvmax = 12.5;
        servoConfigY[iprobe].gs = 1.0;
        servoConfigY[iprobe].gp = 1.5;
        servoConfigY[iprobe].gi = 0.7;
        servoConfigY[iprobe].pi = 0.5;
        servoConfigY[iprobe].tok = 0.5;
        servoStateY[iprobe].pdtold = *(double *) pgsub->f;
        servoConfigY[iprobe].noise = 0.0;
        timeNow(&(servoStateY[iprobe].told));
        servoStateY[iprobe].told -= 0.05;
        servoStateY[iprobe].tout = servoStateY[iprobe].told;
        servoStateY[iprobe].vd = 0.0;
        servoStateY[iprobe].accum = 0.0;
        y[iprobe] = servoStateY[iprobe].pdtold;
        yvel[iprobe] = 0.0;

        newstat = menuCarstatesIDLE;
        substat[iprobe] = -1;
        trackid[iprobe] = 0.0;
        first[iprobe] = FALSE;
    }
/* fetch latest velocities & tolerances */
    servoConfigX[iprobe].vtmax = *(double *) pgsub->l;
    servoConfigY[iprobe].vtmax = *(double *) pgsub->l;
    servoConfigZ[iprobe].vtmax = *(double *) pgsub->l;
    servoConfigX[iprobe].pok   = *(double *) pgsub->n;
    servoConfigY[iprobe].pok   = *(double *) pgsub->n;
    servoConfigZ[iprobe].pok   = *(double *) pgsub->p;

/* Get demand data array */
    arraySize = pgsub->noj;
    memcpy(AGSdemand, pgsub->j, arraySize * sizeof(double));
    tappl = AGSdemand[1];
    newtrack = AGSdemand[2];
    xdemand  = AGSdemand[3] ;
    ydemand  = AGSdemand[4] ;
    zdemand  = AGSdemand[5] ;

    strcpy(arrayS, "GOOD") ;

/* For probe 1 and 2 convert the incoming x y demands to rotary table angle
*  and probe arm angle.
*/
   if (iprobe < 2) {
     ret = gemXy2ab (xdemand*xyscale[iprobe], ydemand*xyscale[iprobe],
                     M1TOFPLANE, heights[iprobe],
                     bearRadius[iprobe], probeLen[iprobe], &a1, &b1, &a2, &b2);
     if (ret != 0) {
       xdemand = xlast[0] ;
       ydemand = ylast[0] ;
       strcpy(arrayS, "BAD") ;
     } else {
       xdemand = a2 * R2D ;
       ydemand = b2 * R2D ;
     }
   }

/* send demands to servo. Currently no servo for Z movement */
    timeNow(&now);

/* Initialise demand velocities to 0.0. This was found to be neccesary if
*  the optimiser was used. Without it the probes would exhibit ocillatory
*  behaviour.
*/
    xdemandv = 0.0;
    ydemandv = 0.0;
    zdemandv = 0.0;

    if (stateProbe[iprobe] == MOVING) {
      xnow = xtarget[iprobe] ;
      xft  = xftarget[iprobe] ;
      inPositionX[iprobe] = tcsServo(now, xnow, 0, &servoConfigX[iprobe],
                        &servoStateX[iprobe], &x[iprobe], &xvel[iprobe]);
      xerr[iprobe] = xnow - x[iprobe];

      ynow = ytarget[iprobe] ;
      yft  = yftarget[iprobe] ;
      inPositionY[iprobe] = tcsServo(now, ynow, 0, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
      yerr[iprobe] = ynow - y[iprobe];

      znow = ztarget[iprobe] ;
      inPositionZ[iprobe] = tcsServo(now, znow, 0, &servoConfigZ[iprobe],
                        &servoStateZ[iprobe], &z[iprobe], &zvel[iprobe]);
      zerr[iprobe] = znow - z[iprobe];

    } else if (stateProbe[iprobe] == FOLLOWING) {
        if (tappl > tlast[iprobe]) {
            xdemandv = (xdemand - xlast[iprobe]) / (tappl - tlast[iprobe]);
            ydemandv = (ydemand - ylast[iprobe]) / (tappl - tlast[iprobe]);
            zdemandv = (zdemand - zlast[iprobe]) / (tappl - tlast[iprobe]);
        }
        xnow = xdemand + xdemandv * (now - tappl);
        xft  = AGSdemand[3] ;
   
        inPositionX[iprobe] = tcsServo(tappl, xnow, 0, &servoConfigX[iprobe],
                               &servoStateX[iprobe],
                               &x[iprobe], &xvel[iprobe]);
        xerr[iprobe] = xnow - x[iprobe];

        ynow = ydemand + ydemandv * (now - tappl);
        yft  = AGSdemand[4] ;
        inPositionY[iprobe] = tcsServo(tappl, ynow, 0, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
        yerr[iprobe] = ynow - y[iprobe];

        znow = zdemand + zdemandv * (now - tappl);
        inPositionZ[iprobe] = tcsServo(tappl, znow, 0, &servoConfigZ[iprobe],
                        &servoStateZ[iprobe], &z[iprobe], &zvel[iprobe]);
        zerr[iprobe] = znow - z[iprobe];

    } else {
        inPositionX[iprobe] = tcsServo(now, x[iprobe], 1, &servoConfigX[iprobe],
                        &servoStateX[iprobe], &x[iprobe], &xvel[iprobe]);
        xerr[iprobe] = 0.0;
        inPositionY[iprobe] = tcsServo(now, y[iprobe], 1, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
        yerr[iprobe] = 0.0;
        inPositionZ[iprobe] = tcsServo(now, z[iprobe], 1, &servoConfigZ[iprobe],
                        &servoStateZ[iprobe], &z[iprobe], &zvel[iprobe]);
        zerr[iprobe] = 0.0;
        xft = yft = 0.0; /* Not used for STOPPEd state but prevents warnings */
    }

    inPosition[iprobe] = inPositionX[iprobe] && inPositionY[iprobe] && inPositionZ[iprobe] ;

/* Round values to nearest micron */
    x[iprobe] = (floor(((1000.0 * x[iprobe])) + 0.5)) / 1000.0;
    y[iprobe] = (floor(((1000.0 * y[iprobe])) + 0.5)) / 1000.0;
    z[iprobe] = (floor(((1000.0 * z[iprobe])) + 0.5)) / 1000.0;

/* Initialise the link selection field. The bits in this field 
   are as follows :
     Bit 0 = Process completion record
     Bit 1 = Process CAR record
     Bit 2 = Process trackId record */
    linkSelect = 0;

/* Determine new subsystem state. To be 'all in position', 
   X, Y and Z must be in position 10x in successive calls */     

        if (inPosition[iprobe]) 
          {
          newstat = menuCarstatesIDLE;
 /* If not following, set to STOPPED */
          if (stateProbe[iprobe] == MOVING || stateProbe[iprobe] == STOPPING)
             {
              StateProbe[iprobe] = STOPPED ;
              linkSelect += 1;     /* Trigger record 'complete' */
             }
 /* If not following, set to STOPPED */
          } 
        else
/* Not in position */
          newstat = menuCarstatesBUSY;


/* Set the link selection field and update the subsystem state */

    if (newstat != substat[iprobe]) {
        substat[iprobe] = newstat;
        linkSelect += 2;           /* Trigger update of CAR record */
    }
    if (newtrack != trackid[iprobe]) {
        trackid[iprobe] = newtrack;
        inPosition[iprobe] = FALSE;
        linkSelect += 4;           /* Trigger update of trackId record */
    }

/* save demands */
    tlast[iprobe] = tappl;
    xlast[iprobe] = xdemand;
    ylast[iprobe] = ydemand;
    zlast[iprobe] = zdemand;

/* For probes 1 and 2 we must convert the rotary table and probe arm angles
*  back to x and y
*/
   if (iprobe < 2 ) {
     rtangle = x[iprobe] ;
     pangle  = y[iprobe] ;
     ret = gemAb2xy (x[iprobe]*D2R, y[iprobe]*D2R, M1TOFPLANE, heights[iprobe],
                     bearRadius[iprobe], probeLen[iprobe], &xfplane, 
                     &yfplane) ;
     xfplane /= xyscale[iprobe] ;
     yfplane /= xyscale[iprobe] ;
     if (stateProbe[iprobe] == STOPPED) {
       xferr = yferr = 0.0;
     } else {
       xferr = xft - xfplane ;
       yferr = yft - yfplane ;
     }
   } else {
     rtangle = 0.0 ;
     pangle  = 0.0 ;
     xfplane = x[iprobe] ;
     yfplane = y[iprobe] ;
     xferr   = xerr[iprobe] ;
     yferr   = yerr[iprobe] ;
   }

/* Although this is excessive, calculate the minimum radius a probe can
*  reach. The calculation for the OIWFS will always give 0.0
*/
   fscale = M1TOFPLANE / (M1TOFPLANE - heights[iprobe]) ;
   minRad = (bearRadius[iprobe] - probeLen[iprobe]) * fscale ;
   if (minRad < 0.0) minRad = -minRad ;

/* now output the results */
    *(double *) pgsub->vala = tappl;
    *(double *) pgsub->valb = xfplane;
    *(double *) pgsub->valc = yfplane;
    *(double *) pgsub->vald = z[iprobe];
    *(double *) pgsub->vale = xferr;
    *(double *) pgsub->valf = yferr;
    *(double *) pgsub->valg = zerr[iprobe];
    *(double *) pgsub->valh = substat[iprobe];
    *(double *) pgsub->vali = trackid[iprobe];
    *(long *) pgsub->valj = linkSelect;
    *(long *) pgsub->valk = inPosition[iprobe];
    *(double *) pgsub->vall = rtangle ;
    *(double *) pgsub->valm = pangle ;
    strcpy (pgsub->valn, arrayS) ;
    *(double *) pgsub->valo = minRad ;

    return 0;
}

/*+
 *   Function name:
 *   tcsAgsComplete
 *
 *   Purpose:
 *   Signal complete of a move command
 *
 *   Description:
 *   Signals completion of a move command by writing IDLE to the appropriate
 *   CAR record.
 *
 *   Invocation:
 *   tcsAgsComplete(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub    (genSubRecord *) pointer to genSub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAgsComplete(genSubRecord *psub)
{

/* output values for CAR Message and State fields */
    strcpy(psub->valb, "Stopped");
    *(double *)psub->vala = menuCarstatesIDLE;
    return 0;
}

/*+
 *   Function name:
 *   tcsAgsOiwfsCoeffs
 *
 *   Purpose:
 *   Output transformation coefficients to EPICS
 *
 *   Description:
 *   Write the appropriate transformation coefficients to VALJ.
 *   A set of parameters can be input in user coordinates e.g. orientation
 *   xscale etc. and these are transformed into a set of 6 affine
 *   coefficients that can be passed to the TCS
 *
 *   Invocation:
 *   tcsAgsOiwfsCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (genSubRecord *) pointer to genSub structure
 *
 *   Epics inputs:
 *  
 *   a => relative orientation (degs)
 *   b => non-perpendicularity (degs)
 *   c => x scale ;
 *   d => y scale ;
 *   e => x zero point ;
 *   f => y zero point ;
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAgsOiwfsCoeffs(genSubRecord *pgsub)
{

  double orient ;             /* Relative orientation (rads) */
  double nonperp ;            /* Non perpendicularity (degs) */
  double xscale, yscale ;     /* Scales in x and y */
  double xzero, yzero ;       /* Zero points in x and y */

  double costh, sinth ;       /* cos/sine of orientation */
  double cosp2, sinp2 ;       /* cos/sine of non-perp semi-angle */
  double Acoeff, Bcoeff ;
  double Ccoeff, Dcoeff ;     /* Intermediate variables */

  double localo2t[6] ;        /* Local copy of oiwfs to tcs params */
  double localt2o[6] ;        /* Local copy of tcs to oiwfs params */

  int jstat ;                 /* Status from inversion */
  int i ;                     /* Loop counter */

/* Read in all user data. Note there is no check on the validity. This is
*  assumed done at the EPICS level.
*/
  orient = *(double *)pgsub->a * D2R ;
  nonperp = *(double *)pgsub->b * D2R ;
  xscale  = *(double *)pgsub->c ;
  yscale  = *(double *)pgsub->d ;
  xzero   = *(double *)pgsub->e ;
  yzero   = *(double *)pgsub->f ;

/* Convert these numbers into the corresponding affine connection coeffs */
  costh = cos(orient) ;
  sinth = sin(orient) ;
  cosp2 = cos(nonperp/2) ;
  sinp2 = sin(nonperp/2) ;
  Acoeff = costh * cosp2 + sinth * sinp2 ;
  Bcoeff = costh * sinp2 + sinth * cosp2 ;
  Ccoeff = costh * sinp2 - sinth * cosp2 ;
  Dcoeff = costh * cosp2 - sinth * sinp2 ;

  localo2t[1] = Acoeff * xscale ;
  localo2t[2] = Bcoeff * yscale ;
  localo2t[0] = localo2t[1] * xzero + localo2t[2] * yzero ;
  localo2t[4] = Ccoeff * xscale ;
  localo2t[5] = Dcoeff * yscale ;
  localo2t[3] = localo2t[4] * xzero + localo2t[5] * yzero ;

  if (xscale < 0.0) {
    localo2t[2] = -localo2t[2] ;
    localo2t[4] = -localo2t[4] ;
  }

/* Invert the transformation */
  slaInvf (localo2t, localt2o, &jstat) ;

/* If inversion was successful then we have a valid set of coefficients to
*  transform OIWFS coords to TCS and vice versa so store these away for
*  later use
*/

  if (jstat == 0) {
    for (i = 0; i < 6 ; i++) {
      tcs2oiwfs[i] = localt2o[i] ;
    }
  }

  memcpy (pgsub->valj, tcs2oiwfs, 6 * sizeof(double)) ;

  return 0;
}

/*+
 *   Function name:
 *   tcsAgsSetCalParms
 *
 *   Purpose:
 *   Save calibration parameters in same manner as the real A&G
 *
 *   Description:
 *   This routine simply provides a mechanism's calibration parameters in
 *   the same form as that provided by the real A&G. This makes interfacing
 *   to this simualtor the same as interfacing to the real A&G.
 *
 *   Invocation:
 *   tcsAgsSetCalParms(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (genSubRecord *) pointer to genSub structure
 *
 *   Epics inputs:
 *  
 *   b => Rotary table upper limit (degs)
 *   d => Rotary Table lower limit (degs) ;
 *
 *   Epics outputs:
 *   vall => Rotary table upper limit
 *   valm => Rotary table lower limit
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAgsSetCalParms(genSubRecord *pgsub)
{

/* Just copy inputs to outputs */
  *(double *)pgsub->vall = *(double *)pgsub->b;
  *(double *)pgsub->valm = *(double *)pgsub->d;

  return 0;
}

/*+
 *   Function name:
 *   tcsAgStopCAD
 *
 *   Purpose:
 *   CAD to stop specified A&G probe
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAgStopCAD
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
 *-
 */

long tcsAgStopCAD(struct cadRecord *pcad)
{
    int nitem ;
    int iprobe = 0;

/* CAD directive is in field DIR */
    switch (pcad->dir) 
    {
    case menuDirectiveSTART:
    case menuDirectivePRESET:
        strcpy(pcad->mess, "Stop: argument is valid");
        nitem = sscanf(pcad->a, "%d ", &iprobe);
        if (nitem < 1 || iprobe < 0 || iprobe > 3) 
            {
              strcpy(pcad->mess, "Stop: probe number out of range");
              return CAD_REJECT;
            } 
        if (pcad->dir == menuDirectiveSTART)
          {
          if (iprobe == 0) 
             {
              StateProbe[0] = STOPPED ;
              StateProbe[1] = STOPPED ;
              StateProbe[2] = STOPPED ;
             } 
             else 
              StateProbe[--iprobe] = STOPPED ;
          }

/* Output acceptance message */
       strcpy(pcad->mess, "Command accepted");
       strncpy(pcad->vala, "OFF", 3);
       return CAD_ACCEPT;
       break;              /* End menuDirectiveSTART or menuDirectivePRESET */

       case menuDirectiveMARK:
       case menuDirectiveCLEAR:
       case menuDirectiveSTOP:
       break;

       default:
       strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
       return CAD_REJECT;
       break;
    }

    return CAD_ACCEPT ;
}


/*+
 *   Function name:
 *   tcsAgStop
 *
 *   Purpose:
 *   gensub to stop all A&G probes
 *
 *   Invocation:
 *   tcsAgStop
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to pgsub structure
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

long tcsAgStop(struct genSubRecord *pgsub)
{
    StateProbe[0] = STOPPED;
    StateProbe[1] = STOPPED;
    StateProbe[2] = STOPPED;
    strncpy(pgsub->vala, "OFF", 3);
    strncpy(pgsub->valb, "OFF", 3);
    strncpy(pgsub->valc, "OFF", 3);
    return (0);
}



/*+
 *   Function name:
 *   tcsAGaoSelCAD
 *
 *   Purpose:
 *   Emulate the A&G aoSel command
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G aoSel command.
 *
 *   Invocation:
 *   tcsAGaoSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *   a => AO Fold position : In | Out
 *   c => Current AO fold position
 *
 *   EPICS output parameters:
 *   vala => AO fold position In | Out 
 *   vald => AO fold position In | Out | undefined
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAGaoSelCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char ustring[MAX_STRING_SIZE] ; /* Buffer for upper case strings */
  char cpos[MAX_STRING_SIZE];     /* Buffer for current position */
  static char dem[MAX_STRING_SIZE];     /* Demand position */

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

/* Check the requested AO fold position demand */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ((strncmp(ustring,"IN",2) != 0) && (strncmp(ustring,"OUT",3) !=0)) {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "A&G AO fold : invalid position") ;
       return status ;
     } else {
       tcsDcUc (pcad->c, MAX_STRING_SIZE, cpos) ;
       strcpy(dem, pcad->a);
       if (strncmp(ustring, cpos, 2)) {
         strcpy(dem, "undefined");
       }
     }
     break;

     case menuDirectiveSTART:
/* Copy input to output */
       strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE);
       strncpy(pcad->vald, dem, MAX_STRING_SIZE);
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

/*+
 *   Function name:
 *   tcsAGhwSelCAD
 *
 *   Purpose:
 *   Emulate the A&G hwSel command, to select the HRWFS position
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G hwSel command.
 *
 *   Invocation:
 *   tcsAGhwSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS inputs :
 *   a => HRWFS probe position : In | Out
 *   c => Current HRWFS probe position
 *
 *   EPICS outputs:
 *   vala =>  Deamnd position In | Out
 *   vald =>  Current position In | Out | undefined
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAGhwSelCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char ustring[MAX_STRING_SIZE] ; /* Buffer for upper case strings */
  char cpos[MAX_STRING_SIZE];     /* Buffer for current position */
  static char dem[MAX_STRING_SIZE];     /* Demand position */

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

/* Check the requested HRWFS position demand */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ((strncmp(ustring,"IN",2) != 0) && (strncmp(ustring,"OUT",3) !=0)) {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "A&G HRWFS move : invalid position") ;
       return status ;
     } else {
       tcsDcUc (pcad->c, MAX_STRING_SIZE, cpos) ;
       strcpy(dem, pcad->a);
       if (strncmp(ustring, cpos, 2)) {
         strcpy(dem, "undefined");
       }
     }
     break;

     case menuDirectiveSTART:
/* Copy input to output */
       strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE);
       strncpy(pcad->vald, dem, MAX_STRING_SIZE);
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


/*+
 *   Function name:
 *   tcsAGsfSelCAD
 *
 *   Purpose:
 *   Emulate the A&G sfSel command, to select the Science Fold position
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G sfSel command.
 *
 *   Invocation:
 *   tcsAGsfSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Science Fold position : 0 -> 11, or name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGsfSelCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  long sfPos ;            /* Science fold demanded position */
  int  sfIndex ;          /* Index to SF position */
  char cadname[MAX_STRING_SIZE];           /* Name of CAD record */
  char prefix[MAX_STRING_SIZE];            /* Name of CAD record */
  static char *insnames[] = {"GCAL2GMOS5", "GMOS5", "GCAL2NIRIF6P3",
                             "GCAL2NIRIF14P3", "GCAL2NIRIF32P3", "NIRIF6P3",
                             "NIRIF14P3", "NIRIF32P3", "AO2NIRIF32P3",
                             "AO2NIRIF14P3", "AO2AC", "AO2HR", 
                             "GCAL2MICHELLE1", "AO2NIFS1", "GCAL2NIFS1", NULL} ;

/* Fetch name of CAD for use in messages */

    strcpy (cadname, strchr(pcad->name, ':') + 1) ;
    strcpy (prefix, cadname) ;
    strcat (prefix, ": ");

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;
/* Check the requested SF position demand. Due to changes to the interface
*  names and numbers are allowed
*/

     if (tcsDcLong (prefix, pcad->a, &sfPos, pcad)) {
       if (tcsDcString (insnames, "port: ", pcad->a, &sfIndex, pcad))
         break ;
     } else {
       if (sfPos < 0 || sfPos > 11)
       {
         strcpy (pcad->mess, "A&G Science Fold move: invalid position") ;
         return status ;
       }
     }
     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:
/* Copy input to output */
       strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE);
       strcpy (pcad->vald, "undefined");
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


/*+
 *   Function name:
 *   tcsAGfilterSelCAD
 *
 *   Purpose:
 *   Emulate the A&G filterSel command
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G filterSel command.
 *
 *   Invocation:
 *   tcsAGfilterSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Filter name
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGfilterSelCAD (struct cadRecord *pcad)

{

    long status ;           /* Return status */

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART:

/* Check the requested filter name */

     if (strlen(pcad->a) == 0)
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "A&G filter : filter name missing") ;
       return status ;
     }
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
 *   tcsAGfldstopSelCAD
 *
 *   Purpose:
 *   Emulate the A&G fldstopSel command
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G fldstopSel command.
 *
 *   Invocation:
 *   tcsAGfldstopSelCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Filter name
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGfldstopSelCAD (struct cadRecord *pcad)

{

    long status ;           /* Return status */

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART:

/* Check the requested fldstop name */

     if (strlen(pcad->a) == 0)
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "A&G fldstop : fldstop name missing") ;
       return status ;
     }
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


/*
 *   Function name:
 *   tcsAGtoleranceCAD
 *
 *   Purpose:
 *   Emulate the AG tolerance command
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G probe tolerance command.
 *
 *   Invocation:
 *   tcsAGtoleranceCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => X/Y position radial tolerance
 *   b => Z position (focus) tolerance
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGtoleranceCAD (struct cadRecord *pcad)

{
  double xyPosTol = 0;
  double zPosTol = 0;
  long status ;           /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {
     case menuDirectivePRESET :
     case menuDirectiveSTART :

      status = CAD_REJECT ;
/* At least can check that the tolerances are positive numbers */
     if (tcsDcDouble ("A&G probe:", pcad->a, &xyPosTol, pcad)) break ;
     if (xyPosTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "Probe R tolerance : must be positive") ;
       return status ;
     }
     if (tcsDcDouble ("A&G probe:", pcad->b, &zPosTol, pcad)) break ;
     if (zPosTol < 0 )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "Probe Z tolerance : must be positive") ;
       return status ;
     }
     status = CAD_ACCEPT ;
     if (pcad->dir == menuDirectiveSTART)
/* Output tolerance values */
       {
       * (double *) pcad->vala = xyPosTol ;
       * (double *) pcad->valb  = zPosTol ;
       }
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
 *   tcsAGsetOrientCAD
 *
 *   Purpose:
 *   Emulate the A&G setOrient command, to select orientation for the
 *   table & probe arms
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G set Orient command.
 *
 *   Invocation:
 *   tcsAGsetOrientCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Choice of table orientation : CCW | CW | X
 *   b => Choice of probe arm orientation : CCW | CW | X
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGsetOrientCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char ustring[MAX_STRING_SIZE] ; /* Buffer for upper case strings */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

/* Check the choice of table orientation */

     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"CCW", 3) != 0) && (strncmp(ustring,"CW", 2) !=0) &&
        (strncmp(ustring,"X", 1) != 0) )
     {
       status = CAD_REJECT ;
       tcsCsAppendMessage (pcad, "Invalid table orientation") ;
       break ;
     }
/* Check the choice of probe arm orientation */

     tcsDcUc (pcad->b, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"CCW", 3) != 0) && (strncmp(ustring,"CW", 2) !=0) &&
        (strncmp(ustring,"X", 1) != 0) )
     {
       status = CAD_REJECT ;
       tcsCsAppendMessage (pcad, "Invalid probe orientation") ;
       break ;
     }
     break;

     case menuDirectiveSTART:
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
 *   tcsP1detSigModeAoCAD
 *
 *   Purpose:
 *   Emulate the PWFS1 detSigModeAo command
 *
 *   Description:
 *   Used to set the time over which the WFS will coadd frames before
 *   fitting the data and generating a new set of Zernike corrections.
 *   The number of sub apertures that are turned off is not currently
 *   used.
 *
 *   Invocation:
 *   tcsP1detSigModeAoCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => AO coadd time (secs)
 *   b => No. of sub apertures switched off 
 *
 *   EPICS output parameters :
 *   vala => AO coadd time (secs)
 *   valb => No. of sub apertures switched off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP1detSigModeAoCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static double aoTime ;       /* AO coad time (secs) */
  static long numSubApps ;     /* Number of sub apertures turned off */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT ;

     if (!tcsDcLen(pcad->a)) {
       aoTime = agP1AoInterval ;
     } else {
       if (tcsDcDouble("aoTime :", pcad->a, &aoTime, pcad)) break;
     }

     if (!tcsDcLen(pcad->b)) {
       numSubApps = 0 ;
     } else {
       if (tcsDcLong("subApps :", pcad->b, &numSubApps, pcad)) break;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:
      agP1AoInterval = aoTime ;
      *(double *)pcad->vala = agP1AoInterval ;
      *(long *)pcad->valb = numSubApps ;
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP1detSigModeSeqDarkCAD
 *
 *   Purpose:
 *   Emulate the PWFS1 detSigModeSeqDark command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsP1detSigModeSeqDarkCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   c =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valc => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP1detSigModeSeqDarkCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valc, pcad->c);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP1detSigInitCAD
 *
 *   Purpose:
 *   Emulate the PWFS1 detSigInit command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsP1detSigInitCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   b =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valb => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP1detSigInitCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valb, pcad->b);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP1detSigModeSeqCAD
 *
 *   Purpose:
 *   Emulate the PWFS1 detSigModeSeq command. 
 *
 *   Description:
 *   Basic implementation of sequence closed loop command
 *
 *   Invocation:
 *   tcsP1detSigModeSeqCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Time to global guide (secs) 
 *   i => Period to average frmaes (secs)
 *   p => Write focus to SCS
 *   s => Rms multiplier
 *
 *   EPICS output parameters :
 *   vala => Time to global guide (secs) 
 *   valb => Period to average frmaes (secs)
 *   valc => Write focus to SCS
 *   vald => Rms multiplier
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP1detSigModeSeqCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static double globalTime ;   /* Time to global guide (secs) */
  static double frameTime ;    /* period to average frames */
  static long writeFocus ;     /* Flag to write focus values */
  static double rmsMultiplier; /* rms multiplier */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
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
     if (!tcsDcLen(pcad->i)) {
       tcsCsAppendMessage (pcad, "frame time not given") ;
       break ;
     }
     if (tcsDcDouble("Frame time: ", pcad->i, &frameTime, pcad)) break ;
     
     if (frameTime < 0.005) {
       tcsCsAppendMessage (pcad, "Frame time out of range") ;
       break ;
     }

/* Check the focus flag */
     if (!tcsDcLen(pcad->p)) {
       tcsCsAppendMessage (pcad, "focus flag not given") ;
       break ;
     }
     if (tcsDcLong("Focus flag: ", pcad->p, &writeFocus, pcad)) break ;
     
     if (writeFocus < 0 || writeFocus > 1) {
       tcsCsAppendMessage (pcad, "Focus flag out of range") ;
       break ;
     }

/* Finally check the rms multiplier */
     if (!tcsDcLen(pcad->s)) {
       tcsCsAppendMessage (pcad, "rms multiplier missing") ;
       break ;
     }
     if (tcsDcDouble("rms: ", pcad->s, &rmsMultiplier, pcad)) break ;
     
     if (rmsMultiplier < 0.0) {
       tcsCsAppendMessage (pcad, "rms out of range") ;
       break ;
     }
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       agP1AoInterval = frameTime ;
       *(double *)pcad->vala = globalTime  ;
       *(double *)pcad->valb = frameTime ;
       *(long *)pcad->valc = writeFocus ;
       *(double *)pcad->vald = rmsMultiplier ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP1observeCAD
 *
 *   Purpose:
 *   Emulate the PWFS1 observe command, to start the continuous measurement
 *   of WFS data
 *
 *   Description:
 *   This routine provides a minimal emulation of the PWFS1 observe command.
 *   Prior to the split of the WFS into separate IOCs, this command was
 *   called startMeasure. 
 *
 *   Invocation:
 *   tcsP1observeCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => No. of exposures, -1 = continuous 
 *   b => Exposure time (secs) 
 *   c => Output option, default = 0 (0 = NONE, 1 = DHS, 2 = FILE) 
 *   d => DHS label when output option is DHS (default = NONE) 
 *   e => DHS output, default = 2 (0 = PERM, 1 = TEMP, 2 = QL) 
 *   f => Data path, default = .
 *   g => File name when output option = FILE
 *   h => Simulation file when running in simulation mode (default = NONE) 
 *
 *   EPICS output parameters :
 *   vala => No. of exposures 
 *   valb => Exposure time (secs) 
 *   valc => measuring state (1 = measuring) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   Deficiencies:
 *   The routine just toggles the measuring flag to on when it gets a start
 *   directive and toggles it to off when the stop directive comes in. This
 *   is fine for continuous measurements but is not correct for a finite
 *   number of frames. 
 * 
 *
 *-
 */
long tcsP1observeCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static long nexp ;           /* No. of exposures */
  static double expTime ;      /* Exposure time */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage(pcad, "No. of exposures not given") ;
       break ;
     }
     if (tcsDcLong("Exposures: :", pcad->a, &nexp, pcad)) break;

     if (nexp < -1) {
       tcsCsAppendMessage (pcad, "No. of exposures invalid") ;
       break ;
     }

/* Check the exposure time */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "Exposure time not given") ;
       break ;
     }
     if (tcsDcDouble("Exp. time: ", pcad->b, &expTime, pcad)) break ;
     
     if (expTime < 0.005 || expTime > 10000.0) {
       tcsCsAppendMessage (pcad, "Exposure time out of range") ;
       break ;
     }

/* Don't bother with the remaining inputs for this simulation */ 
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       agP1Measuring = 1 ;
       *(long *)pcad->vala = nexp  ;
       *(double *)pcad->valb = expTime ;
       *(long *)pcad->valc = agP1Measuring ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
     case menuDirectiveSTOP:
      agP1Measuring = 0 ;
      *(long *)pcad->valc = agP1Measuring ;
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
 *   tcsP2detSigInitCAD
 *
 *   Purpose:
 *   Emulate the PWFS2 detSigInit command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsP2detSigInitCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   b =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valb => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP2detSigInitCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valb, pcad->b);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP2detSigModeAoCAD
 *
 *   Purpose:
 *   Emulate the PWFS2 detSigModeAo command
 *
 *   Description:
 *   Used to set the time over which the WFS will coadd frames before
 *   fitting the data and generating a new set of Zernike corrections.
 *   The number of sub apertures that are turned off is not currently
 *   used.
 *
 *   Invocation:
 *   tcsP2detSigModeAoCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => AO coadd time (secs)
 *   b => No. of sub apertures switched off 
 *
 *   EPICS output parameters :
 *   vala => AO coadd time (secs)
 *   valb => No. of sub apertures switched off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP2detSigModeAoCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static double aoTime ;       /* AO coad time (secs) */
  static long numSubApps ;     /* Number of sub apertures turned off */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT ;

     if (!tcsDcLen(pcad->a)) {
       aoTime = agP2AoInterval ;
     } else {
       if (tcsDcDouble("aoTime :", pcad->a, &aoTime, pcad)) break;
     }

     if (!tcsDcLen(pcad->b)) {
       numSubApps = 0 ;
     } else {
       if (tcsDcLong("subApps :", pcad->b, &numSubApps, pcad)) break;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:
      agP1AoInterval = aoTime ;
      *(double *)pcad->vala = agP2AoInterval ;
      *(long *)pcad->valb = numSubApps ;
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP2detSigModeSeqCAD
 *
 *   Purpose:
 *   Emulate the PWFS2 detSigModeSeq command. 
 *
 *   Description:
 *   Basic implementation of sequence closed loop command
 *
 *   Invocation:
 *   tcsP2detSigModeSeqCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Time to global guide (secs) 
 *   i => Period to average frmaes (secs)
 *   p => Write focus to SCS
 *   s => Rms multiplier
 *
 *   EPICS output parameters :
 *   vala => Time to global guide (secs) 
 *   valb => Period to average frmaes (secs)
 *   valc => Write focus to SCS
 *   vald => Rms multiplier
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP2detSigModeSeqCAD (struct cadRecord *pcad)

{

  long status ;                  /* Return status */
  static double globalTime ;     /* Time to global guide (secs) */
  static double frameTime ;      /* period to average frames */
  static long writeFocus ;       /* Flag to write focus values */
  static double rmsMultiplier ;  /* rms multiplier */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
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
     if (!tcsDcLen(pcad->i)) {
       tcsCsAppendMessage (pcad, "frame time not given") ;
       break ;
     }
     if (tcsDcDouble("Frame time: ", pcad->i, &frameTime, pcad)) break ;
     
     if (frameTime < 0.005) {
       tcsCsAppendMessage (pcad, "Frame time out of range") ;
       break ;
     }

/* Check the focus flag */
     if (!tcsDcLen(pcad->p)) {
       tcsCsAppendMessage (pcad, "focus flag not given") ;
       break ;
     }
     if (tcsDcLong("Focus flag: ", pcad->p, &writeFocus, pcad)) break ;
     
     if (writeFocus < 0 || writeFocus > 1) {
       tcsCsAppendMessage (pcad, "Focus flag out of range") ;
       break ;
     }

/* Finally check the rms multiplier */
     if (!tcsDcLen(pcad->s)) {
       tcsCsAppendMessage (pcad, "rms multiplier missing") ;
       break ;
     }
     if (tcsDcDouble("rms: ", pcad->s, &rmsMultiplier, pcad)) break ;
     
     if (rmsMultiplier < 0.0) {
       tcsCsAppendMessage (pcad, "rms out of range") ;
       break ;
     }
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       agP2AoInterval = frameTime ;
       *(double *)pcad->vala = globalTime  ;
       *(double *)pcad->valb = frameTime ;
       *(long *)pcad->valc = writeFocus ;
       *(double *)pcad->vald = rmsMultiplier ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP2detSigModeSeqDarkCAD
 *
 *   Purpose:
 *   Emulate the PWFS2 detSigModeSeqDark command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsP2detSigModeSeqDarkCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   c =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valc => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsP2detSigModeSeqDarkCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valc, pcad->c);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsP2observeCAD
 *
 *   Purpose:
 *   Emulate the PWFS2 observe command, to start the continuous measurement
 *   of WFS data
 *
 *   Description:
 *   This routine provides a minimal emulation of the PWFS2 observe command.
 *   Prior to the split of the WFS into separate IOCs, this command was
 *   called startMeasure. 
 *
 *   Invocation:
 *   tcsP2observeCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => No. of exposures, -1 = continuous 
 *   b => Exposure time (secs) 
 *   c => Output option, default = 0 (0 = NONE, 1 = DHS, 2 = FILE) 
 *   d => DHS label when output option is DHS (default = NONE) 
 *   e => DHS output, default = 2 (0 = PERM, 1 = TEMP, 2 = QL) 
 *   f => Data path, default = .
 *   g => File name when output option = FILE
 *   h => Simulation file when running in simulation mode (default = NONE) 
 *
 *   EPICS output parameters :
 *   vala => No. of exposures 
 *   valb => Exposure time (secs) 
 *   valc => measuring state (1 = measuring) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   Deficiencies:
 *   The routine just toggles the measuring flag to on when it gets a start
 *   directive and toggles it to off when the stop directive comes in. This
 *   is fine for continuous measurements but is not correct for a finite
 *   number of frames. 
 *-
 */
long tcsP2observeCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static long nexp ;           /* No. of exposures */
  static double expTime ;      /* Exposure time */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage(pcad, "No. of exposures not given") ;
       break ;
     }
     if (tcsDcLong("Exposures: :", pcad->a, &nexp, pcad)) break;

     if (nexp < -1) {
       tcsCsAppendMessage (pcad, "No. of exposures invalid") ;
       break ;
     }

/* Check the exposure time */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "Exposure time not given") ;
       break ;
     }
     if (tcsDcDouble("Exp. time: ", pcad->b, &expTime, pcad)) break ;
     
     if (expTime < 0.005 || expTime > 10000.0) {
       tcsCsAppendMessage (pcad, "Exposure time out of range") ;
       break ;
     }

/* Don't bother with the remaining inputs for this simulation */ 
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       agP2Measuring = 1 ;
       *(long *)pcad->vala = nexp  ;
       *(double *)pcad->valb = expTime ;
       *(long *)pcad->valc = agP2Measuring ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
     case menuDirectiveSTOP:
      agP2Measuring = 0 ;
      *(long *)pcad->valc = agP2Measuring ;
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
 *   tcsOidetSigInitCAD
 *
 *   Purpose:
 *   Emulate the OIWFS detSigInit command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsOidetSigInitCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   b =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valb => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsOidetSigInitCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valb, pcad->b);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsOidetSigModeSeqDarkCAD
 *
 *   Purpose:
 *   Emulate the OIWFS detSigModeSeqDark command
 *
 *   Description:
 *   A dummy routine that does nothing as it accepts any string as
 *   the name of the dark file to write.
 *
 *   Invocation:
 *   tcsOidetSigModeSeqDarkCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   c =>  Sky/dark file name
 *
 *   EPICS output parameters :
 *   valc => Sky/dark file name 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsOidetSigModeSeqDarkCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     break;

     case menuDirectiveSTART:
     strcpy (pcad->valc, pcad->c);
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsOidetSigModeAoCAD
 *
 *   Purpose:
 *   Emulate the OIWFS detSigModeAo command
 *
 *   Description:
 *   Used to set the time over which the WFS will coadd frames before
 *   fitting the data and generating a new set of Zernike corrections.
 *   The number of sub apertures that are turned off is not currently
 *   used.
 *
 *   Invocation:
 *   tcsOidetSigModeAoCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => AO coadd time (secs)
 *   b => No. of sub apertures switched off 
 *
 *   EPICS output parameters :
 *   vala => AO coadd time (secs)
 *   valb => No. of sub apertures switched off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsOidetSigModeAoCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static double aoTime ;       /* AO coad time (secs) */
  static long numSubApps ;     /* Number of sub apertures turned off */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT ;

     if (!tcsDcLen(pcad->a)) {
       aoTime = agOiwfsAoInterval ;
     } else {
       if (tcsDcDouble("aoTime :", pcad->a, &aoTime, pcad)) break;
     }

     if (!tcsDcLen(pcad->b)) {
       numSubApps = 0 ;
     } else {
       if (tcsDcLong("subApps :", pcad->b, &numSubApps, pcad)) break;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:
      agOiwfsAoInterval = aoTime ;
      *(double *)pcad->vala = agOiwfsAoInterval ;
      *(long *)pcad->valb = numSubApps ;
     break;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsOidetSigModeSeqCAD
 *
 *   Purpose:
 *   Emulate the OIWFS detSigModeSeq command. 
 *
 *   Description:
 *   Basic implementation of sequence closed loop command
 *
 *   Invocation:
 *   tcsOidetSigModeSeqCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Time to global guide (secs) 
 *   i => Period to average frmaes (secs)
 *   p => Write focus to SCS
 *   s => Rms multiplier
 *
 *   EPICS output parameters :
 *   vala => Time to global guide (secs) 
 *   valb => Period to average frmaes (secs)
 *   valc => Write focus to SCS
 *   vald => Rms multiplier
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */
long tcsOidetSigModeSeqCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  double globalTime ;          /* Time to global guide (secs) */
  double frameTime ;           /* period to average frames */
  long writeFocus ;            /* Flag to write focus values */
  double rmsMultiplier ;       /* rms multiplier */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
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
     if (!tcsDcLen(pcad->i)) {
       tcsCsAppendMessage (pcad, "frame time not given") ;
       break ;
     }
     if (tcsDcDouble("Frame time: ", pcad->i, &frameTime, pcad)) break ;
     
     if (frameTime < 0.005) {
       tcsCsAppendMessage (pcad, "Frame time out of range") ;
       break ;
     }

/* Check the focus flag */
     if (!tcsDcLen(pcad->p)) {
       tcsCsAppendMessage (pcad, "focus flag not given") ;
       break ;
     }
     if (tcsDcLong("Focus flag: ", pcad->p, &writeFocus, pcad)) break ;
     
     if (writeFocus < 0 || writeFocus > 1) {
       tcsCsAppendMessage (pcad, "Focus flag out of range") ;
       break ;
     }

/* Finally check the rms multiplier */
     if (!tcsDcLen(pcad->s)) {
       tcsCsAppendMessage (pcad, "rms multiplier missing") ;
       break ;
     }
     if (tcsDcDouble("rms: ", pcad->s, &rmsMultiplier, pcad)) break ;
     
     if (rmsMultiplier < 0.0) {
       tcsCsAppendMessage (pcad, "rms out of range") ;
       break ;
     }
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       *(double *)pcad->vala = globalTime  ;
       *(double *)pcad->valb = frameTime ;
       *(long *)pcad->valc = writeFocus ;
       *(double *)pcad->vald = rmsMultiplier ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
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
 *   tcsOiobserveCAD
 *
 *   Purpose:
 *   Emulate the OIWFS observe command, to start the continuous measurement
 *   of WFS data
 *
 *   Description:
 *   This routine provides a minimal emulation of the OIWFS observe command.
 *   Prior to the split of the WFS into separate IOCs, this command was
 *   called startMeasure. 
 *
 *   Invocation:
 *   tcsOiobserveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => No. of exposures, -1 = continuous 
 *   b => Exposure time (secs) 
 *   c => Output option, default = 0 (0 = NONE, 1 = DHS, 2 = FILE) 
 *   d => DHS label when output option is DHS (default = NONE) 
 *   e => DHS output, default = 2 (0 = PERM, 1 = TEMP, 2 = QL) 
 *   f => Data path, default = .
 *   g => File name when output option = FILE
 *   h => Simulation file when running in simulation mode (default = NONE) 
 *
 *   EPICS output parameters :
 *   vala => No. of exposures 
 *   valb => Exposure time (secs) 
 *   valc => measuring state (1 = measuring) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   Deficiencies:
 *   The routine just toggles the measuring flag to on when it gets a start
 *   directive and toggles it to off when the stop directive comes in. This
 *   is fine for continuous measurements but is not correct for a finite
 *   number of frames. 
 *-
 */
long tcsOiobserveCAD (struct cadRecord *pcad)

{

  long status ;                /* Return status */
  static long nexp ;           /* No. of exposures */
  static double expTime ;      /* Exposure time */

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the number of exposures */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage(pcad, "No. of exposures not given") ;
       break ;
     }
     if (tcsDcLong("Exposures: :", pcad->a, &nexp, pcad)) break;

     if (nexp < -1) {
       tcsCsAppendMessage (pcad, "No. of exposures invalid") ;
       break ;
     }

/* Check the exposure time */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "Exposure time not given") ;
       break ;
     }
     if (tcsDcDouble("Exp. time: ", pcad->b, &expTime, pcad)) break ;
     
     if (expTime < 0.005 || expTime > 10000.0) {
       tcsCsAppendMessage (pcad, "Exposure time out of range") ;
       break ;
     }

/* Don't bother with the remaining inputs for this simulation */ 
     status = CAD_ACCEPT ;

     break;

     case menuDirectiveSTART:

       agOiwfsMeasuring = 1 ;
       *(long *)pcad->vala = nexp  ;
       *(double *)pcad->valb = expTime ;
       *(long *)pcad->valc = agOiwfsMeasuring ;
       break ;
  
     case menuDirectiveMARK:
     break ;
     case menuDirectiveCLEAR:
     break ;
     case menuDirectiveSTOP:
      agOiwfsMeasuring = 0 ;
      *(long *)pcad->valc = agOiwfsMeasuring ;
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
 *   tcsAGpeekCAD
 *
 *   Purpose:
 *   Emulate the A&G peek command, to make one-off WFS observations
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G peek command.
 *
 *   Invocation:
 *   tcsAGobserveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => WFS selection bit mask. 0 = PWFS1, 1=PWFS2, 2=OIWFS.
 *   b => Number of exposures, -1 means continuous
 *   c => Whether raw uncalibrated data are to be transmitted 
 *   d => Use DHS?
 *   e => PWFS1 data label
 *   f => PWFS2 data label
 *   g => OIWFS data label
 *   h => Path for datafiles
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGpeekCAD (struct cadRecord *pcad)

{
  long status ;           /* Return status */
  long wfsMask, nexp, dhs;       /* variables for input conversions */
  long ifRaw ;            /* Whether raw data is to be transmitted */
  char label[MAX_STRING_SIZE];

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check WFS mask */
     if (tcsDcLong("WFS mask:", pcad->a, &wfsMask, pcad)) break;

/* Check number of exposures */
     if (tcsDcLong("no. of exposures: ", pcad->b, &nexp, pcad)) break;
     if (nexp < -1 || nexp == 0)
     {
       tcsCsAppendMessage (pcad, "no. of exposures invalid") ;
       break ;
     }

/* Check if raw uncalibrated data is to be transmitted */
     if (tcsDcLong ("if-raw: ", pcad->c, &ifRaw, pcad)) break;
     if (ifRaw != 0 && ifRaw != 1)
     {
       tcsCsAppendMessage (pcad, "if-raw must be 0 or 1") ;
       break ;
     }

/* Check DHS flag */
     if (tcsDcLong ("DHS flag:", pcad->d, &dhs, pcad)) break;
     if (dhs != 1 && dhs !=0)
     {
       tcsCsAppendMessage (pcad, "DHS flag invalid") ;
       break ;
     }

/* Remaining fields are simply labels */
     strncpy(label, pcad->e, MAX_STRING_SIZE);
     if (strlen(label) == 0 &&  (wfsMask & 0x0001))
     {
       tcsCsAppendMessage (pcad, "PWFS1 data label blank") ;
       break ;
     }       
     strncpy(label, pcad->f, MAX_STRING_SIZE);
     if (strlen(label) == 0 && (wfsMask & 0x0002))
     {
       tcsCsAppendMessage (pcad, "PWFS2 data label blank") ;
       break ;
     }
     strncpy(label, pcad->g, MAX_STRING_SIZE);
     if (strlen(label) == 0 && (wfsMask & 0x0004))
     {
       tcsCsAppendMessage (pcad, "OIWFS data label blank") ;
       break ;
     } 

/* Don't bother to check path name i.e. parameter h */

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTOP:
       epicsPrintf("A&G WFS peek : STOP received\n");
       status = CAD_ACCEPT ;     
     break;

     case menuDirectiveSTART:
     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
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
 *   tcsAGcalibrateCAD
 *
 *   Purpose:
 *   Emulate the A&G  command, to calibrate wavefront sensors
 *
 *   Description:
 *   This routine provides a minimal emulation of the A&G calibrate command.
 *
 *   Invocation:
 *   tcsAGcalibrateCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => WFS name PWFS1 | PWFS2 | OIWFS.
 *   b => Path for data files
 *   c => Name of dark calibration file
 *   d => Name of pixel sensitivity file 
 *   e => Name of control matrix file
 *   f => Name of spot centres file
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAGcalibrateCAD (struct cadRecord *pcad)
{
  long status ;           /* Return status */
  char ustring[MAX_STRING_SIZE];

/* Set message prefix */
    tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     status = CAD_REJECT;

/* Check the WFS name */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"PWFS1", 5) != 0) && (strncmp(ustring,"PWFS2", 5) !=0) &&
        (strncmp(ustring,"OIWFS", 5) != 0) )
     {
       tcsCsAppendMessage (pcad, "Invalid wfs name") ;
       break ;
     }

/* The other parameters are not worth checking for this simulation */

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART:
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
 *   tcsAgGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the A & G
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAgTestCAD(pcad)
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

long tcsAgGenericCAD(struct cadRecord *pcad)
{
    int status;                 /* return status */
    char command[29];           /* command name */
    int i, j;                   /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
    for (i = 0, j = 0; i < 29; i++, j++) {
        command[j] = pcad->name[i];
        if (!(pcad->name[i]))
            break;
        if (command[j] == ':')
            j = -1;
    }

    switch (pcad->dir) {
    case menuDirectiveSTART:

        /* write output message (n.b. no more that 28 characters) */
        sprintf(pcad->mess, "A & G: %.13s started", command);

        /* If its a STOP command, output the following flag value (zero) */
        if (strncmp(command, "stop", 4) == 0)
            strcpy(pcad->vala, "OFF");
        else
        {
/* Copy over the parameters to the output fields */

         strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
         strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
        }

        status = CAD_ACCEPT;
        break;

    default:
        status = 0;
        break;
    }
    return (status);
}


/*+
 *   Function name:
 *   tcsAgParkCAD
 *
 *   Purpose:
 *   Implement a Park command for the A & G
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAgParkCAD(pcad)
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

long tcsAgParkCAD(struct cadRecord *pcad)
{
    int status;                 /* return status */
    char command[29];           /* command name */
    int i, j;                   /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
    for (i = 0, j = 0; i < 29; i++, j++) {
        command[j] = pcad->name[i];
        if (!(pcad->name[i]))
            break;
        if (command[j] == ':')
            j = -1;
    }

    switch (pcad->dir) {
    case menuDirectiveSTART:

        /* write output message (n.b. no more that 28 characters) */
        sprintf(pcad->mess, "A & G: %.13s started", command);

        /* Write new mechanism position to vala */
        strcpy(pcad->vala, "park-pos.") ;
        strcpy(pcad->vald, "undefined") ;

        status = CAD_ACCEPT;
        break;

    default:
        status = 0;
        break;
    }
    return (status);
}


/*+
 *   Function name:
 *   tcsAgsTtfZero
 *
 *   Purpose:
 *   Simulated genSub record receiving data from the TCS.
 *   In this case the data is the expected Zernikes at the
 *   position of the WFS, to be used for guiding purposes.
 *
 *   Description:
 *   Simulation simply reads in the data as supplied by the TCS
 *
 *   Invocation:
 *   tcsAgsTtfZero(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   a => probe number
 *   j => Array of 8 (double) data items from the TCS
 *
 *   EPICS output fields :
 *
 *   vala..valc => Z1..Z3 
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
long tcsAgsTtfZero (struct genSubRecord *pgsub)
{
#define ARRMAX1 32

    static int count = 0;
    static int first = TRUE;
    int iprobe;               /* Probe number */
    unsigned long arraySize;  /* Number of array items in field J */
    double ttfdata[ARRMAX1];

    count++ ;
/*  Get probe number */
    iprobe = floor(*(double *) pgsub->a);
    if (iprobe <1 || iprobe > 3)
      {
      iprobe = 1;
      if (first) epicsPrintf("tcsAgsTtfZero : invalid probe number, assuming 1\n");
      }

/* Read in the data array */
    arraySize = pgsub->noj;
    if (arraySize > ARRMAX1)
      {
      arraySize = 8;
      if (first) epicsPrintf("tcsAgsTtfZero : invalid field J array size\n");
      }
    memcpy(ttfdata, pgsub->j, arraySize * sizeof(double));

/* Write out Zernike terms */
    *(double *)pgsub->vala =  ttfdata[5];
    *(double *)pgsub->valb =  ttfdata[6];
    *(double *)pgsub->valc =  ttfdata[7];
    first = FALSE;
    return 0;
}


/*+
 *   Function name:
 *   tcsAgsAoZero1
 *
 *   Purpose:
 *   Simulated genSub record receiving data from the TCS.
 *   In this case the data is the expected Zernikes at the
 *   position of the WFS, to be used for adaptive optics purposes
 *
 *   Description:
 *   Simulation simply reads in the data as supplied by the TCS
 *
 *   Invocation:
 *   tcsAgsAoZero1(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   b => probe number
 *   j => Array of 24 (double) data items from the TCS
 *
 *   EPICS output fields :
 *
 *   vala..valj => Z1..Z10
 *   valt => Array of 24 (double) data items from the TCS
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
long tcsAgsAoZero1 (struct genSubRecord *pgsub)
{
#define ARRMAX2 32

    static int count = 0;
    static int first = TRUE;
    int iprobe;               /* Probe number */
    unsigned long arraySize;  /* Number of array items in field J */
    double aodata[ARRMAX2];

    count++ ;
/*  Get probe number */
    iprobe = floor(*(double *) pgsub->b);
    if (iprobe <1 || iprobe > 3)
      {
      iprobe = 1;
      if (first) epicsPrintf("tcsAgsAoZero1 : invalid probe number, assuming 1\n");
      }

/* Read in the data array */
    arraySize = pgsub->noj;
    if (arraySize > ARRMAX2)
      {
      arraySize = 24;
      if (first) epicsPrintf("tcsAgsAoZero1 : invalid field J array size\n");
      }
    memcpy(aodata, pgsub->j, arraySize * sizeof(double));

/* Write out Zernike terms */
    *(double *)pgsub->vala =  aodata[5];
    *(double *)pgsub->valb =  aodata[6];
    *(double *)pgsub->valc =  aodata[7];
    *(double *)pgsub->vald =  aodata[8];
    *(double *)pgsub->vale =  aodata[9];
    *(double *)pgsub->valf =  aodata[10];
    *(double *)pgsub->valg =  aodata[11];
    *(double *)pgsub->valh =  aodata[12];
    *(double *)pgsub->vali =  aodata[13];
    *(double *)pgsub->valj =  aodata[14];
    memcpy(pgsub->valt, pgsub->j, arraySize * sizeof(double));

    first = FALSE;
    return 0;
}


/*+
 *   Function name:
 *   tcsAgsAoZero2
 *
 *   Purpose:
 *   Simulated genSub record receiving data from the TCS.
 *   In this case the data is the expected Zernikes at the
 *   position of the WFS, to be used for adaptive optics purposes
 *
 *   Description:
 *   Simulation simply reads in the data as supplied by the TCS
 *
 *   Invocation:
 *   tcsAgsAoZero2(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   b => probe number
 *   j => Array of 24 (double) data items from "tcsAgsAoZero1"
 *
 *   EPICS output fields :
 *
 *   vala..valj => Z11..Z19
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
long tcsAgsAoZero2 (struct genSubRecord *pgsub)
{
#define ARRMAX2 32

    static int count = 0;
    static int first = TRUE;
    int iprobe;               /* Probe number */
    unsigned long arraySize;  /* Number of array items in field J */
    double aodata[ARRMAX2];

    count++ ;
/*  Get probe number */
    iprobe = floor(*(double *) pgsub->b);
    if (iprobe <1 || iprobe > 3)
      {
      iprobe = 1;
      if (first) epicsPrintf("tcsAgsAoZero2 : invalid probe number, assuming 1\n");
      }

/* Read in the data array */
    arraySize = pgsub->noj;
    if (arraySize > ARRMAX2)
      {
      arraySize = 24;
      if (first) epicsPrintf("tcsAgsAoZero2 : invalid field J array size\n");
      }
    memcpy(aodata, pgsub->j, arraySize * sizeof(double));

/* Write out Zernike terms */
    *(double *)pgsub->valk =  aodata[15];
    *(double *)pgsub->vall =  aodata[16];
    *(double *)pgsub->valm =  aodata[17];
    *(double *)pgsub->valn =  aodata[18];
    *(double *)pgsub->valo =  aodata[19];
    *(double *)pgsub->valp =  aodata[20];
    *(double *)pgsub->valq =  aodata[21];
    *(double *)pgsub->valr =  aodata[22];
    *(double *)pgsub->vals =  aodata[23];

    first = FALSE;
    return 0;
}


/*+
 *   Function name:
 *   tcsAgsTtf
 *
 *   Purpose:
 *   Simulated genSub record sending WFS data to the TCS.
 *   In this case the data is the time-averaged tip/tilt/focus data
 *
 *   Description:
 *   Simulation simply copies over the data sent to this record
 *   by the optics simulator.
 *   Note that output data array is declared static so that it retains 
 *   values between invocations. This ensures that we don't get
 *   spurious uninitialized data on the output links.
 *
 *   Invocation:
 *   tcsAgsTtf(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   a => probe number
 *   d => Simulated focus Z3
 *   e => Sigma on Zernikes
 *   f => Data from PWFS1
 *   g => Data from PWFS2 
 *   h => Data from OIWFS
 *
 *   EPICS output fields :
 * 
 *   valj => Array of 8 (double) data items for TCS
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   1. If the mean value is zero then the sigma is also set to zero. This
 *      is deliberate so that the case when there is no signal can be tested.
 *   2. The error on the estimate is equal to the error on the mean. This
 *      shouldn't be a problem as these error estimates aren't used anywhere.
 *   3. The routine resets its idea of the base position of the probe each
 *      time an integration is started. It should do this each time a new
 *      probe target is given but that would require more information
 *      from the TCS
 *-
 */
long tcsAgsTtf (struct genSubRecord *pgsub)
{
#define ARRMAX3 32

    static int first = TRUE;
    int iprobe;                      /* Probe number */
    unsigned long outArraySize;      /* Number of array items in field J/VALJ */
    static double ttfP1data[ARRMAX3];
    static double ttfP2data[ARRMAX3];
    static double ttfOidata[ARRMAX3];
    double Zmean[3] ;                /* Mean Zernikes values */
    double Zerr ;                    /* Standard error */
    double sigma ;
    double temp ;

/*  Get probe number */
    iprobe = floor(*(double *) pgsub->a);
    if (iprobe <1 || iprobe > 3) {
      iprobe = 1;
      if (first) epicsPrintf("tcsAgsTtf : invalid probe number, assuming 1\n");
    }

/* Get mean Zernike terms plus error */
    Zmean[2] = *(double *)pgsub->d ;
    Zerr     = *(double *)pgsub->e ;

/* Check each probe to see if we need to generate data. In order to keep
*  the same signs and gains in the TCS it has been found that the raw
*  data has to be swapped, scaled by a factor of about 20 and then the
*  sign changed on the "x" component
*/
    if (iprobe == 1) {
      if (agP1Measuring) {
        memcpy(ttfP1data, pgsub->f, 8*sizeof(double));
        temp = ttfP1data[2]*0.05;
        ttfP1data[2] = -ttfP1data[3]*0.05;
        ttfP1data[3] = temp;
        sigma = (double)tcsGresid((float)Zerr);
        ttfP1data[4] = Zmean[2] + sigma ;
      } 

/* Output data array to TCS on VALJ */
      outArraySize = pgsub->novj;
      if (outArraySize > ARRMAX3) {
        if (first) epicsPrintf("tcsAgsTtf : invalid field VALJ array size\n");
      } 
      memcpy(pgsub->valj, ttfP1data, outArraySize * sizeof(double));
    }

    if (iprobe == 2) {
      if (agP2Measuring) {
        memcpy(ttfP2data, pgsub->g, 8*sizeof(double));
        temp = ttfP2data[2]*0.05;
        ttfP2data[2] = -ttfP2data[3]*0.05;
        ttfP2data[3] = temp;
        sigma = (double)tcsGresid((float)Zerr);
        ttfP2data[4] = Zmean[2] + sigma ;
      } 

/* Output data array to TCS on VALJ */
      outArraySize = pgsub->novj;
      if (outArraySize > ARRMAX3) {
        if (first) epicsPrintf("tcsAgsTtf : invalid field VALJ array size\n");
      } 
      memcpy(pgsub->valj, ttfP2data, outArraySize * sizeof(double));
    }

    if (iprobe == 3) {
      if (agOiwfsMeasuring) {
        memcpy(ttfOidata, pgsub->h, 8*sizeof(double));
        temp = ttfOidata[2]*0.05;
        ttfOidata[2] = -ttfOidata[3]*0.05;
        ttfOidata[3] = temp;
        sigma = (double)tcsGresid((float)Zerr);
        ttfOidata[4] = Zmean[2] + sigma ;
      } 

/* Output data array to TCS on VALJ */
      outArraySize = pgsub->novj;
      if (outArraySize > ARRMAX3) {
        if (first) epicsPrintf("tcsAgsTtf : invalid field VALJ array size\n");
      } 
      memcpy(pgsub->valj, ttfOidata, outArraySize * sizeof(double));
    }

    first = FALSE;
    return 0;

}

/*+
 *   Function name:
 *   tcsAgsAo
 *
 *   Purpose:
 *   Simulated genSub record sending WFS data to the TCS.
 *   In this case the data is the active optics data from the WFS.
 *
 *   Description:
 *   Simulation generates dummy WFS data which is then placed in
 *   correct array for collection by TCS. The simulation simply
 *   takes the input Zernike demands and adds a scaled error
 *   signal to them.
 *
 *   Invocation:
 *   tcsAgsAo(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   a => probe number
 *   b => Simulated tip Z1 (mm)
 *   c => Simulated tilt Z2 (mm)
 *   d => Simulated focus Z3 (mm)
 *   e => Simulated astigmatism Z4/Z5 (mm)
 *   f => Simulated coma Z6/Z7 (mm)
 *   g => Simulated spherical Z8 (mm)
 *   h => Simulated trefoil Z9/Z10 (mm)
 *   i => Simulated Z11/Z12 (mm)
 *   j => Simulated Z13/Z14 (mm)
 *   k => Simulated Z15 (mm)
 *   l => Simulated Z16/Z17 (mm)
 *   m => Simulated Z18/Z19 (mm)
 *   n => Sigma on Zernikes
 *
 *   EPICS output fields :
 * 
 *   valj => Array of 40 (double) data items for TCS
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
long tcsAgsAo (struct genSubRecord *pgsub)
{
#define ARRMAX4 40

    static int generatingP1 = 0 ; /* Set true if generating PWFS1 data */
    static int generatingP2 = 0 ; /* Set true if generating PWFS2 data */
    static int generatingOi = 0 ; /* Set TRUE of generating OIWFS data */
    static double timeStartP1 ;   /* Time at which PWFS1 data was started */
    static double timeStartP2 ;   /* Time at which PWFS2 data was started */
    static double timeStartOi ;   /* Time at which OIWFS data was started */
    static int first = TRUE;
    int iprobe;                   /* Probe number */
    unsigned long outArraySize;   /* Number of array items in field VALJ */
    static double aoP1data[ARRMAX4];  /* Output data */
    static double aoP2data[ARRMAX4];
    static double aoOidata[ARRMAX4];
    double Zmean[19] ;            /* Mean Zernike terms */
    double Zerr ;                 /* Standard error */
    double tnow ;                 /* Current time */
    double sigma ;                /* Current error on 1 mm Zernike */
    int i ;                       /* Loop counter */

/*  Get probe number */
    iprobe = floor(*(double *) pgsub->a);
    if (iprobe <1 || iprobe > 3) {
      iprobe = 1;
      if (first) epicsPrintf("tcsAgsAo : invalid probe number, assuming 1\n");
      }

/* Get mean Zernike terms plus error */

     Zmean[0] = *(double *)pgsub->b ;
     Zmean[1] = *(double *)pgsub->c ;
     Zmean[2] = *(double *)pgsub->d ;
     Zmean[3] = *(double *)pgsub->e ;
     Zmean[4] = Zmean[3] ;
     Zmean[5] = *(double *)pgsub->f ;
     Zmean[6] = Zmean[5] ;
     Zmean[7] = *(double *)pgsub->g ;  /* Spherical */
     Zmean[8] = *(double *)pgsub->h ;  /* Trefoil */
     Zmean[9] = Zmean[8] ;
     Zmean[10] = *(double *)pgsub->i ;
     Zmean[11] = Zmean[10] ;
     Zmean[12] = *(double *)pgsub->j ;
     Zmean[13] = Zmean[12] ;
     Zmean[14] = *(double *)pgsub->k ;
     Zmean[15] = *(double *)pgsub->l ;
     Zmean[16] = Zmean[15] ;
     Zmean[17] = *(double *)pgsub->m ;
     Zmean[18] = Zmean[17] ;
     Zerr      = *(double *)pgsub->n ;

/* Check each probe to see if we need to generate data */
    if (iprobe == 1) {
      if (agP1Measuring && !generatingP1) {
        timeNow (&timeStartP1) ;
        generatingP1 = TRUE ;
      }
      if (generatingP1 && !agP1Measuring)
        generatingP1 = FALSE ;
      if (generatingP1 ) {
        timeNow (&tnow) ;
        if (tnow - timeStartP1 > agP1AoInterval) {
/* Generate the neccessary Zernikes  and update the data array */
          aoP1data[0] = tnow ;
          aoP1data[1] = (double)agP1NumZern ;
          sigma = (double)tcsGresid((float)Zerr) ;
          for (i = 2 ; i < 40 ; i++ )
            aoP1data[i] = 0.0 ;
          for (i = 0 ; i < agP1NumZern ; i++ ) {
            if (Zmean[i] != 0.0) 
              aoP1data[21 + i] = sigma ;
            aoP1data[2 +i] = Zmean[i] + aoP1data[21+i] ;  
          }
          timeStartP1 = tnow ;
        }
      }

/* Output data to EPICS record */
      outArraySize = pgsub->novj;
      memcpy (pgsub->valj, aoP1data, outArraySize * sizeof (double)) ;
    }

    if (iprobe == 2) {
      if (agP2Measuring && !generatingP2) {
        timeNow (&timeStartP2) ;
        generatingP2 = TRUE ;
      }
      if (generatingP2 && !agP2Measuring)
        generatingP2 = FALSE ;
      if (generatingP2 ) {
        timeNow (&tnow) ;
        if (tnow - timeStartP2 > agP2AoInterval ) {
/* Generate the neccessary Zernikes  and update the data array */
          aoP2data[0] = tnow ;
          aoP2data[1] = (double)agP2NumZern ;
          sigma = (double)tcsGresid((float)Zerr) ;
          for (i = 2 ; i < 40 ; i++ )
            aoP2data[i] = 0.0 ;
          for (i = 0 ; i < agP2NumZern ; i++ ) {
            if (Zmean[i] != 0.0) 
              aoP2data[21 + i] = sigma ;
            aoP2data[2 + i] = Zmean[i] + aoP2data[21+i] ;  
          }
          timeStartP2 = tnow ;
        }
      }

/* Output data to EPICS record */
      outArraySize = pgsub->novj;
      memcpy (pgsub->valj, aoP2data, outArraySize * sizeof (double)) ;
    }

    if (iprobe == 3) {
      if (agOiwfsMeasuring && !generatingOi) {
        timeNow (&timeStartOi) ;
        generatingOi = TRUE ;
      }
      if (generatingOi && !agOiwfsMeasuring)
        generatingOi = FALSE ;
      if (generatingOi ) {
        timeNow (&tnow) ;
        if (tnow - timeStartOi > agOiwfsAoInterval) {
/* Generate the neccessary Zernikes  and update the data array */
          aoOidata[0] = tnow ;
          aoOidata[1] = (double)agOiwfsNumZern ;       
          sigma = (double)tcsGresid((float)Zerr) ;
          for (i = 2 ; i < 40 ; i++ )
            aoOidata[i] = 0.0 ;
          for (i = 0 ; i < agOiwfsNumZern ; i++ ) {
            if (Zmean[i] != 0.0) 
              aoOidata[21 + i] = sigma ;
            aoOidata[2 +i] = Zmean[i] + aoOidata[21+i] ;  
          }
          timeStartOi = tnow ;
        }
      }

/* Output data to EPICS record */
      outArraySize = pgsub->novj;
      memcpy (pgsub->valj, aoOidata, outArraySize * sizeof (double)) ;
    }

    first = FALSE;
    return 0;

}


int gemAb2xy ( double a, double b, double d, double h, double rp, double ra,
               double *x, double *y )
/*
**  - - - - - - - - -
**   g e m A b 2 x y
**  - - - - - - - - -
**
**  Probe rotator and arm angles a,b to focal-plane coordinates.
**
**  Given (arguments):
**     a       double    rotary table angle a (radians)
**     b       double    arm angle b (radians)
**     d       double    distance from focal plane to M1 image in M2
**     h       double    distance of probe above focal plane (Note 1)
**     rp      double    rotary-table axis to pivot (Note 1)
**     ra      double    pivot to pick-off (Note 1)
**
**  Returned (arguments):
**     x       double*   focal-plane x-coordinate
**     y       double*   focal-plane y-coordinate
**
**  Returned (function value):
**             int       0 = OK
**                      -1 = illegal argument
**
**  Called:  slaDrange
**
**  Notes:
**
**  1  Beware:  the way the geometrical parameters are defined here may
**     not match that presented on drawings and in other descriptions.
**
**     The choice is complicated by the tilt of the pivot axis, so that
**     the axis of the mechanical probe sweeps out a cone rather than a
**     plane.  The definitions here are concerned only with the pick-off
**     point (where the central ray intersects the probe's 45 deg entrance
**     mirror) and the plane in which this point moves as the arm rotates
**     (for any given rotary-table orientation):  the mechanical details,
**     shape, and apparent axis of the actual probe are not involved.
**     This plane intersects the rotary-table axis at a point which lies
**     h length units (mm, say) above the focal plane.  The distance, in
**     the plane, from this point to where the plane intersects the pivot
**     axis is rp mm.  The distance from the center of the circle to the
**     pick-off point is ra mm.  Only if rp and ra are equal will the
**     pick-off point be able to reach the rotary-table axis.
**
**     The nominal probe length of 400 mm refers to a point on the rotary
**     table that is considered to be the location of the pivot but which
**     in fact lies some distance below the probe.  The corresponding rp
**     and ra values are therefore slightly less (by about 3 mm) than the
**     nominal 400 mm.
**
**  2  The focal-plane x,y coordinates are exactly that:  where the
**     guidestar image is predicted to be.  The projection geometry and
**     all line-of-sight effects (including differential refraction and
**     atmospheric dispersion) are encapsulated within the x,y coordinates.
**
**  3  If the rotary-table axis does not pass through the focal-plane
**     origin, corrections must be applied to the x,y delivered by this
**     routine to align the position to focal-plane coordinates.  The
**     geometry is then no longer rigorous;  the algorithm assumes that
**     the rotary-table axis is coincident with the optical axis, and that
**     the optical axis defines the origin for the focal-plane x,y
**     coordinate system.
**
**  4  The height, h, of the probe above the focal plane is the distance
**     along from the x,y origin to the place where the plane swept out
**     by the pick-off point crosses the optical axis.  n.b. The axis of
**     the rotary table is presumed coincident with the telescope's
**     optical axis.
**
**  5  The angles a and b increase anti-clockwise as seen from M2.  The
**     zero point for a is when the pivot is on the minus y-axis.  The
**     zero point for b is when the probe is on the optical axis (or at
**     its closest approach).
**
**  6  The mechanical zero-point errors for the two angles a and b must
**     be dealt with outside this routine.
**
**  7  The "illegal argument" status value is returned whenever:
**
**        the focal-plane to M1-image-in-M2 distance is zero or less
**        the height is negative, or more than the former
**        rp is zero or less
**        ra is zero or less
**
**  8  The geometry is defined by three lines and two planes.  The three
**     lines, which intersect at the centre of the image of M1 reflected
**     in M2, are:
**
**       .  The line through the rotator axis in the focal plane.
**
**       .  The line through the guidestar image.
**
**       .  The pivot axis.
**
**     The two planes are:
**
**       .  The focal plane.
**
**       .  The plane of the circle swept out by the pick-off point.
**
**     The following labels will be used:
**
**       C  The point at which the three lines intersect.
**
**       A  Where the rotator axis passes through the focal plane
**          (i.e. the x,y origin).
**
**       P  Where the pivot axis passes through the focal plane.
**
**       S  The guidestar image, at [x,y] in the focal plane (when
**          not intercepted by the probe).
**
**       D  Where the probe plane intersects the line CA.
**
**       E  Where the probe plane intersects the line CP (i.e. the
**          pivot).
**
**       F  Where the probe plane crosses the line CS.
**
**     In the ideal case, where line CA is the optical axis and
**     rp = ra, point F is where the guidestar image is picked off
**     by the probe and point D is where the probe would pick off
**     an on-axis star.
**
**     We know the following:
**
**       .  Angles CED, CAP, CAS and CEF are right angles.
**
**       .  AC = d;  AD = h;  hence CD = d-h.
**
**       .  DE = rp;  EF = ra.
**
**       .  AS^2 = x^2+y^2
**
**  Latest revision:   3 February 2001
**
**  Copyright 2001 P.T.Wallace/CCLRC/Gemini.  All rights reserved.
*/

{
   double def, ac2, cd, cd2, de2, ef2, ce2, cf2, s2dce, cp2,
          ap2, df2, cdcf, as2, as, cs2, c2ecf, ps2, w, v, pas;



/* Validation. */
   if ( d <= 0.0 ||
        h < 0.0 ||
        h >= d ||
        rp <= 0.0 ||
        ra <= 0.0 ) return -1;

/* Preparation. */
   def = slaDrange(b);
   ac2 = d*d;
   cd = d-h;
   cd2 = cd*cd;
   de2 = rp*rp;
   ef2 = ra*ra;

/* Triangle CDE: determine CE. */
   ce2 = cd2-de2;

/* Triangle CEF: determine CF. */
   cf2 = ce2+ef2;

/* Triangle CDE: determine sin^2 of angle DCE. */
   s2dce = de2/cd2;

/* Triangle ACP: determine CP and AP. */
   cp2 = ac2/(1.0-s2dce);
   ap2 = cp2-ac2;

/* Triangle CDF: determine DF. */
   df2 = ef2+de2-2.0*sqrt(ef2*de2)*cos(def);

/* Triangle CDF: determine cos of angle DCF=ACS. */
   cdcf = (cd2+cf2-df2)/(2.0*sqrt(cd2*cf2));

/* Triangle ACS: determine AS. */
   w = cdcf*cdcf;
   as2 = ac2*(1.0-w)/w;
   as = sqrt(as2);

/* Triangle PCS: determine CS. */
   cs2 = ac2/(cdcf*cdcf);

/* Triangle CEF: determine cos^2 of angle ECF=PCS. */
   c2ecf = ce2/(ef2+ce2);

/* Triangle CPS: determine PS. */
   ps2 = cs2+cp2-2.0*sqrt(cs2*cp2*c2ecf);

/* Triangle APS: determine angle PAS. */
   w = as2+ap2-ps2;
   v = 4.0*as2*ap2-w*w;
   pas = w != 0.0 ? atan2( v > 0.0 ? sqrt(v) : 0.0, w ) : 0.0;
   if ( def > 0.0 ) pas = -pas;

/* Return the solution. */
   w = pas+a;
   *x = -as*sin(w);
   *y = as*cos(w);

/* OK exit. */
   return 0;
}


int gemXy2ab ( double x, double y, double d, double h, double rp, double ra,
               double *a1, double *b1, double *a2, double *b2 )
/*
**  - - - - - - - - -
**   g e m X y 2 a b
**  - - - - - - - - -
**
**  Focal-plane coordinates x,y to probe rotator and arm angles a,b.
**
**  Given (arguments):
**     x       double    focal-plane x-coordinate
**     y       double    focal-plane y-coordinate
**     d       double    separation between focal plane and M1 image in M2
**     h       double    distance of probe above focal plane when on-axis
**     rp      double    separation between optical axis and pivot axis
**     ra      double    radius of arm rotation about pivot axis
**
**  Returned (arguments):
**     a1      double*   turntable angle a, solution 1 (radians)
**     b1      double*   arm angle b, solution 1 (radians)
**     a2      double*   turntable angle a, solution 2 (radians)
**     b2      double*   arm angle b, solution 2 (radians)
**
**  Returned (function value):
**             int      +1 = a indeterminate
**                       0 = OK
**                      -1 = illegal argument
**                      -2 = impossible to reach the position
**
**  Called:  slaDrange
**
**  Notes:
**
**  1  The focal-plane x,y coordinates are exactly that:  where the
**     guidestar image is predicted to be.  The projection geometry and
**     all line-of-sight effects (including differential refraction and
**     atmospheric dispersion) are encapsulated within the x,y coordinates.
**
**  2  The height, h, of the probe above the focal plane is the distance
**     along from the x,y origin to the place where the disc swept out
**     by the probe arm crosses the optical axis.
**
**  3  The distance from the optical avis to the pivot, rp, is along a
**     line at right angles to the pivot axis.
**
**  4  The arm radius, ra, should ideally be equal to rp, otherwise
**     guidestar images near the optical axis can never be centred on the
**     WFS.
**
**  5  The angles a and b increase anti-clockwise as seen from M2.  The
**     zero point for a is when the pivot is on the minus y-axis.  The
**     zero point for b is when the probe is on the optical axis (or at
**     its closest approach).
**
**  6  The "illegal argument" status value is returned whenever:
**
**        the focal-plane to M1-image-in-M2 distance is zero or less
**        the height is negative, or more than the former
**        rp is zero or less
**        ra is zero or less
**
**     The "impossible" status value can only occur when the probe length
**     and pivot radius are different, and the demanded position is closer
**     to the optical axis than that difference.
**
**     The returned argments are undefined under the above circumstances.
**
**     The "indeterminate" status value occurs in the degenerate case when
**     the probe length and pivot radius are the same (as they should be)
**     and the demanded position is on the optical axis.  Zero is returned
**     for all the angles.
**
**  7  The geometry is defined by three lines and two planes.  The three
**     lines, which intersect at the centre of the image of M1 reflected
**     in M2, are:
**
**       .  The line through the rotator axis in the focal plane.
**
**       .  The line through the guidestar image.
**
**       .  The pivot axis.
**
**     The two planes are:
**
**       .  The focal plane.
**
**       .  The disc swept out by the probe.
**
**     The following labels will be used:
**
**       C  The point at which the three lines intersect.
**
**       A  Where the rotator axis passes through the focal plane
**          (i.e. the x,y origin).
**
**       P  Where the pivot axis passes through the focal plane.
**
**       S  The guidestar image, at [x,y] in the focal plane (when
**          not intercepted by the probe).
**
**       D  Where the probe plane intersects the line CA.
**
**       E  Where the probe plane intersects the line CP (i.e. the
**          pivot).
**
**       F  Where the probe plane crosses the line CS.
**
**     In the ideal case, where line CA is the optical axis and
**     rp = ra, point F is where the guidestar image is picked off
**     by the probe and point D is where the probe would pick off
**     an on-axis star.
**
**     We know the following:
**
**       .  Angles CED, CAP, CAS and CEF are right angles.
**
**       .  AC = d;  AD = h;  hence CD = d-h.
**
**       .  DE = rp;  EF = ra.
**
**       .  AS^2 = x^2+y^2
**
**  Latest revision:   3 February 2001
**
**  Copyright 2001 P.T.Wallace/CCLRC/Gemini.  All rights reserved.
*/

{
   double as2, w, ac2, cd, cd2, de2, ef2, ce2, cf2, cs2, df2,
          s2dce, b, ps2, cp2, ap2, pas, t;


/* Validation. */
   if ( d <= 0.0 ||
        h < 0.0 ||
        h >= d ||
        rp <= 0.0 ||
        ra <= 0.0 ) return -1;

/* Dispose of "indeterminate" case. */
   if ( ra == rp && x == 0.0 && y == 0.0 ) {
      *a1 = 0.0;
      *b1 = 0.0;
      *a2 = 0.0;
      *b2 = 0.0;
      return 1;
   }

/* Preparation. */
   as2 = x*x+y*y;
   ac2 = d*d;
   cd = d-h;
   cd2 = cd*cd;
   de2 = rp*rp;
   ef2 = ra*ra;

/* Triangle CDE: determine CE. */
   ce2 = cd2-de2;

/* Triangle CEF: determine CF. */
   cf2 = ce2+ef2;

/* Triangle ACS: determine CS. */
   cs2 = as2+ac2;

/* Triangle CDF: determine DF. */
   df2 = cf2+cd2-2.0*sqrt(cf2*cd2*ac2/cs2);

/* Triangle DEF: determine angle DEF (=-b), rejecting if impossible. */
   w = (ef2+de2-df2)/(2.0*ra*rp);
   if ( w > 1.0 ) return -2;
   b = atan2(sqrt(1.0-w*w),w);

/* Triangle CDE: determine sin^2 of angle DCE. */
   s2dce = de2/cd2;

/* Triangle CAP: determine CP. */
   cp2 = ac2/(1.0-s2dce);

/* Triangle CEF: determine cos^2 of angle ECF (=beta). */
   w = ce2/(ef2+ce2);

/* Triangle CPS: determine PS. */
   ps2 = cs2+cp2-2.0*sqrt(cs2*cp2*w);

/* Triangle CAP: determine AP. */
   ap2 = ac2*de2/ce2;

/* Triangle APS: determine angle PAS. */
   w = (as2+ap2-ps2)/(2.0*sqrt(as2*ap2));
   pas = fabs(w) < 1.0 ? atan2(sqrt(1.0-w*w),w) : 0.0;

/* Angle between +y axis and AS (=t). */
   t = as2 != 0.0 ? atan2(-x,y) : 0.0;

/* Return the two solutions. */
   *a1 = slaDrange ( t + pas );
   *b1 = slaDrange ( b );
   *a2 = slaDrange ( t - pas );
   *b2 = slaDrange ( -b );

/* OK exit. */
   return 0;
}
epicsRegisterFunction(tcsOiobserveCAD);
epicsRegisterFunction(tcsAgGenericCAD);
epicsRegisterFunction(tcsAGfldstopSelCAD);
epicsRegisterFunction(tcsAgFollowCAD);
epicsRegisterFunction(tcsAgsTtfZero);
epicsRegisterFunction(tcsOidetSigModeAoCAD);
epicsRegisterFunction(tcsAgsSetCalParms);
epicsRegisterFunction(tcsAGfilterSelCAD);
epicsRegisterFunction(tcsAGsetOrientCAD);
epicsRegisterFunction(tcsAGsfSelCAD);
epicsRegisterFunction(tcsP1observeCAD);
epicsRegisterFunction(tcsAgParkCAD);
epicsRegisterFunction(tcsP2observeCAD);
epicsRegisterFunction(tcsOidetSigModeSeqDarkCAD);
epicsRegisterFunction(tcsP2detSigModeAoCAD);
epicsRegisterFunction(tcsAGhwSelCAD);
epicsRegisterFunction(tcsAGtoleranceCAD);
epicsRegisterFunction(tcsP1detSigModeSeqCAD);
epicsRegisterFunction(tcsP2detSigModeSeqDarkCAD);
epicsRegisterFunction(tcsAgStopCAD);
epicsRegisterFunction(tcsAgsSimulate);
epicsRegisterFunction(tcsAgsTtf);
epicsRegisterFunction(tcsOidetSigInitCAD);
epicsRegisterFunction(tcsP2detSigModeSeqCAD);
epicsRegisterFunction(tcsAgsOiwfsCoeffs);
epicsRegisterFunction(tcsAGfocusSelCAD);
epicsRegisterFunction(tcsP2detSigInitCAD);
epicsRegisterFunction(tcsOidetSigModeSeqCAD);
epicsRegisterFunction(tcsAGoiwfsSelCAD);
epicsRegisterFunction(tcsP1detSigModeAoCAD);
epicsRegisterFunction(tcsAgsAo);
epicsRegisterFunction(tcsP1detSigInitCAD);
epicsRegisterFunction(tcsAgsAoZero1);
epicsRegisterFunction(tcsP1detSigModeSeqDarkCAD);
epicsRegisterFunction(tcsAgsAoZero2);
epicsRegisterFunction(tcsAgMoveCAD);
epicsRegisterFunction(tcsAGaoSelCAD);
epicsRegisterFunction(tcsAgStop);
