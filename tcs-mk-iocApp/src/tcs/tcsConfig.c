/*
   *   FILENAME
   *   tcsConfig.c
   *
   *   FUNCTION NAME(S)
   *   tcsConfigActiveTCB   - returns active TCB
   *   tcsConfigBegin       - routine attached to configBegin record
   *   tcsConfigBeginPreset - called at the start of a APPLY PRESET
   *   tcsConfigBeginStart  - called at the start of an APPLY START
   *   tcsConfigEnd         - routine attached to configEnd record
   *   tcsConfigEndPreset   - called at the end of an APPLY PRESET
   *   tcsConfigEndStart    - called at the end of an APPLY START
   *   tcsConfigForceCheck  - force a check of the configuration
   *   tcsConfigGetOffset   - fetches offset data from TCB
   *   tcsConfigGetPo       - fetches pointing origin data from TCB
   *   tcsConfigGetPoOffset - fetches pointing origin offset data from TCB
   *   tcsConfigGetPFilt    - fetches pointing filter data from TCB
   *   tcsConfigGetTFilt    - fetches target filter data from TCB
   *   tcsConfigGetChop     - fetches chop data from TCB
   *   tcsConfigGetWavel    - fetches wavelength data from TCB
   *   tcsConfigGetTrack    - fetches tracking frame data from TCB
   *   tcsConfigGetDiffTrack - fetches differential tracking data from TCB
   *   tcsConfigGetSysconfig - fetches system config (wrap data) from TCB
   *   tcsConfigGetPlanet   - fetches planet data from TCB
   *   tcsConfigGetOrbit    - fetches orbit data from a TCB
   *   tcsConfigGuideAzEl   - generate mount az/el for guide targets
   *   tcsConfigGetGuideIndex - fetch index of physical guider
   *   tcsConfigInitTCB     - initialises a TCB
   *   tcsConfigPrintTCB    - print a TCB to the screen
   *   tcsConfigMarkComm    - set flag to show command is part of a config
   *   tcsConfigMarkSeqComm - set flag to show sequence command is part of a config
   *   tcsConfigM2Scan       - check if tip/tilt is in a limit
   *   tcsConfigResetRates  - reset differential track rates in TCB
   *   tcsConfigSeqCheck    - checks sequence commands for consistency
   *   tcsConfigSetAOConfiguration - set AO configuration
   *   tcsConfigSetChopParams - set chop parameters
   *   tcsConfigSetOdgwParams - set ODGW parameters
   *   tcsConfigSetOffset   - set offset data into a TCB
   *   tcsConfigSetP1LGSMode - set P1 + LGS observing mode
   *   tcsConfigSetPoOffset - set pointing origin offset data into a TCB
   *   tcsConfigSetPFilt    - set pointing filter data into a TCB
   *   tcsConfigSetTFilt    - set target filter data into a TCB
   *   tcsConfigSetRelChopParams - set relative chop parameters
   *   tcsConfigSetTarget   - set target data into a TCB
   *   tcsConfigSetVgconfig - set the virtual guider configuration
   *   tcsConfigSetWavel   -  set effective wavelegth target data into a TCB
   *   tcsConfigSetDiffTrack - set differential tracking data into a TCB
   *   tcsConfigUpdateDiffTrack - update diff tracking and position in a TCB
   *   tcsConfigSetTrack    - set tracking frame data into a TCB
   *   tcsConfigSetWrap     - set wrap data into a TCB
   *   tcsConfigSetGuide    - set guide config data into a TCB
   *   tcsConfigSetClipAtLimit  - set clip at limit flag in a TCB
   *   tcsConfigSetSlew     - set slew reset data in a TCB
   *   tcsConfigSetRot      - set rotator configuration data into a TCB
   *   tcsConfigSetPlanet   - set planet data into a TCB
   *   tcsConfigSetOrbit    - set orbit data into a TCB
   *   tcsConfigSetTels     - set telescope names in configuration
   *   tcsConfigSetTCBDefn  - sets definition of TCB, current or preset
   *   tcsConfigSetFilePrefix - Set the file name prefix for save/load
   *   tcsConfigSaveTcb     - save TCB data into a file
   *   tcsConfigLoadTcb     - load TCB data from a file
   *   tcsConfigPutTargetFields     - Set all the input EPICS fields in a target CAD 
   *   tcsConfigSetAllTargetFields  - Set all the input EPICS fields in all the target CADs
   *   tcsConfigZeroPm      - zero a proper motion structure
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsConfig.c,v $
 * Revision 1.42  2014/02/08 02:10:21  gemvx
 * REL-1630 implement aoLgsTTFSource command and simulators
 *
 * Revision 1.41  2013/07/22 16:25:57  cjm
 * Remove spurious print statement
 *
 * Revision 1.40  2013/05/02 14:41:25  cjm
 * Move clearoffset and clearPoOffset to different if clause to ensure they are checked for being marked
 *
 * Revision 1.39  2012/06/01 15:53:34  cjm
 * Only set sc to one shot if sc is open
 *
 * Revision 1.38  2012/05/17 11:49:40  cjm
 * Improve configuration checking when switching between P2 and Altair
 *
 * Revision 1.37  2012/05/08 09:44:50  cjm
 * Add SetAOConfiguration and SetP1LGSMode support
 *
 * Revision 1.36  2011/05/06 08:15:05  cjm
 * Add diagnostics for OIWFS x/y exceeded
 *
 * Revision 1.35  2011/01/26 15:14:49  cjm
 * Handle targetAdjust, poAdjust and incrOffsets
 *
 * Revision 1.34  2010/12/20 12:43:15  cjm
 * Check on index before setting ODGW center
 *
 * Revision 1.33  2010/11/29 14:13:22  cjm
 * New routine tcsConfigForceCheck plus change logic of triggering an ODGW setup
 *
 * Revision 1.32  2010/06/08 15:06:41  cjm
 * Add GSAOI port number in call to tcsProbeTcs2Odgw
 *
 * Revision 1.31  2010/05/27 07:35:11  cjm
 * Make config checking smarter when configuring which physical guider to use
 *
 * Revision 1.30  2010/01/22 11:32:51  cjm
 * Turn off act flags if GemS guiders can't reach position
 *
 * Revision 1.29  2010/01/22 09:17:52  cjm
 * Clear active flags for guiders not in use
 *
 * Revision 1.28  2009/12/01 13:44:18  cjm
 * Check ODGW configurations and trigger setup command
 *
 * Revision 1.27  2009/05/20 10:33:12  cjm
 * Recompute OTMs if rotator command is given
 *
 * Revision 1.26  2007/12/19 10:42:19  cjm
 * Remove old comments
 *
 * Revision 1.25  2007/12/18 10:22:54  cjm
 * Extensive changes to handle new guiders
 *
 * Revision 1.24  2007/01/09 14:04:08  cjm
 * Enhance config checking for new orbit commands
 *
 * Revision 1.23  2006/11/24 10:23:13  cjm
 * Use new GetAOConfig routine rather than GetAoFold
 *
 * Revision 1.22  2005/12/23 14:59:34  cjm
 * New routine ResetRates and fetch rates from ephemeris files
 *
 * Revision 1.21  2005/12/14 16:47:02  cjm
 * use new call sequence for tcsEphemerisTarget
 *
 * Revision 1.20  2005/12/13 08:26:25  cjm
 * Fix bug that caused incorrect track rates to be displayed
 *
 * Revision 1.19  2005/10/21 15:39:15  cjm
 * Handle health from tcsEphemerisTarget
 *
 * Revision 1.18  2005/10/20 15:17:24  cjm
 * Allow targets to be specified by ephemeris files
 *
 * Revision 1.17  2004/04/08 10:56:22  cjm
 * Default to nod A / chop A if guide target specified and nothing is configured
 *
 * Revision 1.16  2003/04/30 12:31:41  dlt
 * Revise interaction between slew and filter CADs
 *
 * Revision 1.15  2003/04/10 10:21:09  dlt
 * Store chop mode in kernel
 *
 * Revision 1.14  2003/04/09 10:11:14  dlt
 * Skip chop throw check when chopping mode is NONE
 *
 * Revision 1.13  2003/04/07 15:08:41  dlt
 * Remove duplicate and buggy M2 throw check
 *
 * Revision 1.12  2003/01/13 16:04:16  dlt
 * Implement one-shot filters when slewing
 *
 * Revision 1.11  2003/01/10 10:54:43  dlt
 * Implement chop reset slew flag
 *
 * Revision 1.10  2002/05/09 20:51:51  cjm
 * Add Dave's fix to set the pointing offset slew flag to zero
 *
 * Revision 1.9  2002/04/17 10:28:54  cjm
 * Add clode to clear pointing origin offsets
 *
 * Revision 1.8  2001/10/05 09:09:07  cjm
 * Check limits in oiwfs frame
 *
 * Revision 1.7  2001/05/18 10:39:21  cjm
 * Remove references to subcad records
 *
 * Revision 1.6  2000/12/05 13:46:50  dlt
 * Add flag to zero guide star offsets
 *
 * Revision 1.5  2000/11/23 16:13:15  cjm
 * Fetch ao fold position to dtermine whether to use AO limits or P2 limits
 *
 * Revision 1.4  2000/09/12 08:22:44  cjm
 * Better error messages when probe can't reach demand
 *
 * Revision 1.3  1999/03/22 22:00:12  dlt
 * Fix uninitialised proper motion structure
 *
 * Revision 1.2  1999/03/17 00:42:24  dlt
 * Correct sign of diff track rates in config checking
 *
 * Revision 1.1.1.1  1998/11/08 00:21:04  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.35  1998/09/13 20:59:49  tcs
 * Add WFS name to x/y exceeded error messages
 *
 * Revision 1.34  1998/06/29 09:32:58  dlt
 * Check slew filter flags when driving mount position
 *
 * Revision 1.33  1998/02/16 09:48:59  tcs
 * Revised applyC logic
 *
 * Revision 1.32  1998/01/21 15:34:15  tcs
 * Make slew command disable chopping
 *
 * Revision 1.31  1998/01/08 15:18:43  tcs
 * Change source CAD names
 *
 * Revision 1.30  1997/11/21 14:59:19  cjm
 * add diagnostics to test software timing requirements
 *
 * Revision 1.29  1997/11/19 16:05:40  tcs
 * implement slew parameters
 *
 * Revision 1.28  1997/11/19 10:11:14  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.27  1997/11/17 13:30:47  tcs
 * Fix bug in mount estimate
 *
 * Revision 1.26  1997/11/14 15:59:37  tcs
 * Revised astRot arguments
 *
 * Revision 1.25  1997/11/13 13:23:32  tcs
 * Revised guide star scheme
 *
 * Revision 1.24  1997/11/05 11:36:34  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.23  1997/10/31 14:44:57  tcs
 * Add instrument angle to rotator structure
 *
 * Revision 1.22  1997/10/02 08:47:31  tcs
 * Copy wavelength on slew
 *
 * Revision 1.21  1997/09/25 13:01:50  tcs
 * Leave low elevation refraction problem to astlib
 *
 * Revision 1.20  1997/09/23 11:35:47  tcs
 * Remove redundant if (slew)
 *
 * Revision 1.19  1997/09/23 09:37:23  tcs
 * Correct fetching of pointing origin offsets
 *
 * Revision 1.18  1997/09/17 09:47:53  pbt
 * Add check for empty configuration, to set applyC IDLE
 *
 * Revision 1.17  1997/09/12 12:58:20  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.16  1997/09/11 16:13:26  tcs
 * Add clipAtLimits support
 *
 * Revision 1.15  1997/08/12 10:19:40  tcs
 * Reset local pointing model on slew
 *
 * Revision 1.14  1997/06/26 10:10:09  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.13  1997/06/25 12:57:13  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.12  1997/06/23 14:45:03  tcs
 * detect inaccessible region
 *
 * Revision 1.11  1997/06/11 15:14:16  tcs
 * Implement wavelength CADs
 *
 * Revision 1.10  1997/06/09 15:57:42  tcs
 * rewrite config checking with astlib
 *
 * Revision 1.9  1997/06/02 09:58:22  tcs
 * Add slew CAD
 *
 * Revision 1.8  1997/05/16 12:19:46  tcs
 * Change TCB to arrays
 *
 * Revision 1.7  1997/05/15 14:15:05  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.6  1997/05/07 10:26:40  tcs
 * Implement target to current filter
 *
 * Revision 1.5  1997/04/22 15:17:58  tcs
 * remove tf from tel structure
 *
 * Revision 1.4  1997/04/07 13:56:03  pbt
 * Changes for compatability with new Gemini EPICS version RGO4
 *
 * Revision 1.3  1997/04/03 14:31:24  cjm
 * Check for chop throw/freq conmsistency
 *
 * Revision 1.2  1997/03/24 15:15:15  cjm
 * Use new limit check routines for M2
 *
 * Revision 1.1  1997/02/10 17:10:22  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.51  1997/02/05 11:02:06  tcs
 * Correct printing of filter parameters
 *
 * Revision 1.50  1997/01/31 14:17:10  tcs
 * Zero all offsets on new source A
 *
 * Revision 1.49  1997/01/30 15:25:42  tcs
 * Add chop parameters to PrintTCB
 *
 * Revision 1.48  1997/01/28 10:36:26  tcs
 * corrections to differential tracking
 *
 * Revision 1.47  1997/01/24 14:25:10  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.46  1997/01/23 10:46:37  tcs
 * kernel support for relative chopping
 *
 * Revision 1.45  1997/01/21 08:15:20  cjm
 * Use cartesian cords in tcsConfigProbeInLimit
 *
 * Revision 1.44  1997/01/13 14:30:29  cjm
 * define chop targets correctly when given throw & PA
 *
 * Revision 1.43  1997/01/10 15:17:01  tcs
 * CocoR moved to astlib
 *
 * Revision 1.42  1997/01/09 21:39:45  cjm
 * No longer set defaults for probe chop states
 *
 * Revision 1.41  1997/01/08 09:38:04  cjm
 * Code for checking M2 and probe limits
 *
 * Revision 1.40  1997/01/03 11:15:05  tcs
 * change Coco to CocoR and AZEL_MOUNT to AZEL_MNT
 *
 * Revision 1.39  1996/12/20 15:08:19  pbt
 * Uses save/load file path prefix to select file destination
 *
 * Revision 1.38  1996/12/13 15:07:45  tcs
 * remove zerotime argument from tcsCtCoco
 *
 * Revision 1.37  1996/12/13 10:07:46  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.36  1996/12/13 09:50:24  cjm
 * Rotator command now causes OTMs to be recalculated
 *
 * Revision 1.35  1996/12/12 16:57:03  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.34  1996/12/12 15:53:29  cjm
 * Updates in preparation for better probe handling
 *
 * Revision 1.33  1996/12/09 08:16:55  cjm
 * Fetch filters (tcsInitTCB) and use target A for limit checking
 *
 * Revision 1.32  1996/12/06 14:10:33  tcs
 * revise rotator data
 *
 * Revision 1.31  1996/12/06 09:46:32  tcs
 *  Correct copying of offsets from kernel to TCB
 *
 * Revision 1.30  1996/12/05 13:12:09  tcs
 * rename initial state to catch up
 *
 * Revision 1.29  1996/12/04 10:21:24  cjm
 * For general fix to mount target problem
 *
 * Revision 1.28  1996/12/04 10:00:46  cjm
 * Fix calculation of Mount target
 *
 * Revision 1.27  1996/12/03 16:55:21  tcs
 * New filter parameter names
 *
 * Revision 1.26  1996/12/02 11:04:57  tcs
 * Add rotator parameters to GetSysConfig
 *
 * Revision 1.25  1996/11/26 15:27:08  tcs
 * Add filter access routines
 *
 * Revision 1.24  1996/11/13 14:38:50  tcs
 * Add rotator CAD
 *
 * Revision 1.23  1996/11/08 10:04:50  cjm
 * Fix bug to prevent alwyas checking configuration
 *
 * Revision 1.22  1996/11/07 16:20:10  tcs
 * return correct tracking frame and equinox from GetTarget
 *
 * Revision 1.21  1996/11/06 14:14:58  tcs
 * add pm argument to GetTarget and remove GetFrame
 *
 * Revision 1.20  1996/11/04 08:14:03  cjm
 * Add check for mount limits
 *
 * Revision 1.19  1996/10/24 16:11:04  tcs
 * Pointing origin offset commands
 *
 * Revision 1.18  1996/10/24 12:10:38  tcs
 * add pointing origin commands
 *
 * Revision 1.17  1996/10/24 07:07:14  cjm
 * Upgrade tcsConfigEndPreset
 *
 * Revision 1.16  1996/10/23 12:11:06  tcs
 * Add coordinate type to GetOffset
 *
 * Revision 1.15  1996/10/22 15:59:41  tcs
 * Add configuration offset commands
 *
 * Revision 1.14  1996/10/08 14:01:31  tcs
 * Add CADs for all 13 VTs & remove guide1 and target
 *
 * Revision 1.13  1996/10/07 07:10:47  cjm
 * Support 13 VTs for both preset and current targets
 *
 * Revision 1.12  1996/10/04 08:08:04  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.11  1996/09/30 17:01:01  pbt
 * Alterations to tcsConfig save and load routines
 *
 * Revision 1.10  1996/09/27 07:16:51  cjm
 * Check interlocks before triggering commands
 *
 * Revision 1.9  1996/09/05 16:01:51  pbt
 * Uses modified target data including instring and field fields. Supports
 * setting anf getting ofdwrap data values.
 *
 * Revision 1.8  1996/08/01 15:00:57  tcs
 * comment out debugging output
 *
 * Revision 1.7  1996/07/31 07:26:40  cjm
 * Addition of guide1 command
 *
 * Revision 1.6  1996/07/26 07:46:33  cjm
 * Fix link to configFan
 *
 * Revision 1.5  1996/07/25 12:51:08  cjm
 * Modifications to support data passing via TCBs
 *
 * Revision 1.4  1996/07/24 07:38:46  cjm
 * Additional routines to build and manipulate TCBs
 *
 * Revision 1.3  1996/07/19 15:34:44  cjm
 * Modifications for handling of configurations
 *
 * Revision 1.1  1996/07/15 07:39:58  cjm
 * Initial version
 *
 *
 */
/* *INDENT-ON* */




#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <string.h>
#include <iocsh.h> 
#include <epicsStdlib.h>
#include <math.h>
#include <epicsTypes.h>
#include <genSubRecord.h>
#include <subRecord.h>
#include <db_access.h>
#include <cadef.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuDirective.h>
#include "tcsCadInfo.h"
#include "tcsCadSupport.h"
#include "tcsConstants.h"
#include "tcsTcb.h"
#include "tcsConfig.h"
#include "tcsChannelAccess.h"
#include "tcsGuide.h"
#include "tcsPointing.h"
#include "tcsDisplay.h"
#include "tcsLimits.h"
#include "tcsOptics.h"
#include "tcsCadInfo.h"
#include "timeLib.h"
#include "tcsInterlocks.h"
#include "slalib.h"
#include "tcsCotran.h"
#include "tcsProbeLib.h"
#include "tcsCadInfo.h"
#include "tcsEphemeris.h"

static char firstSeqCommName[MAX_STRING_SIZE];  /* Name of first sequence
                                                   command in configuration */

static char telnames[MAX_STRING_SIZE];  /* Names of telescopes */

static char saveFilePrefix[MAX_STRING_SIZE] = "";       /* File path prefix for save/load file location */

static int firstSeqCommMarked;  /* Flag to show a sequence comamnd 
                                   has been marked                  */

static int recalcOTMs;          /* TRUE if OTMs need recalculating */

static struct TCB currentTCB;   /* The TCB currently being filled out */
static struct TCB presetTCB;    /* The TCB for the preset */
static struct TCB kernelTCB;    /* The TCB that holds the kernel preset data */

static TCBDEFN activeTCB = CURRENT;     /* Default TCB */


/* A structure to define the data handled with the save & load commands */
struct SAVEDATA {
    char savetime[21];          /* String representing time data was saved */
    char comment[MAX_STRING_SIZE];      /* Comment */
    struct TCB savedtcb;        /* The TCB data being saved */
};

static void tcsConfigBeginPreset(void);
static void tcsConfigBeginStart(void);
static long tcsConfigEndPreset( cadRecord *pcad );
static void tcsConfigEndStart(void);
static void tcsConfigInitTCB(TCBDEFN tcbDefn, struct TCB *tcb);
static int tcsConfigM2Scan( struct TCB *pTCB, struct WCS_CTX *ctx, char *mess);

/*+
 *   Function name:
 *   tcsConfigSetChopParams
 *
 *   Purpose:
 *   Set and store chop parameters for later use
 *
 *   Description:
 *   This routine stores the user's input chop parameters for later use. At
 *   present some of this data is stored in the TCB. Other data is 
 *   stored in separate structures until a decison is made on whether or
 *   not is should go in the TCB.
 *
 *   Invocation:
 *   tcsConfigSetChopParams (&chopFreq, &chopMode) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   pChopFreq  (struct DCAD_FIELD *) Structure for chop freq.
 *      (>)   pChopMode  (struct ICAD_FIELD *) Structure for chop mode
 *
 *   Function value:
 *   None
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
 *   Need to decide whether all this data goes into the TCB or not
 *
 *-
 */

void tcsConfigSetChopParams(struct DCAD_FIELD *pChopFreq,
                            struct ICAD_FIELD *pChopMode)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

/* Set the needsCheck flag as the chop frequency is dependent on the chop 
*  throw 
*/

    pTCB->sysconfig.needsCheck = TRUE;

/* Store the data in the TCB */
    pTCB->sysconfig.chopmode = *pChopMode;
    pTCB->sysconfig.chopfreq = *pChopFreq;

}


/*+
 *   Function name:
 *   tcsConfigSetRelChopParams
 *
 *   Purpose:
 *   Set and store relative chop parameters for later use
 *
 *   Description:
 *   This routine stores the user's input chop parameters for later use. At
 *   present some of this data is stored in the TCB. Other data is 
 *   stored in separate structures until a decison is made on whether or
 *   not is should go in the TCB.
 *
 *   Invocation:
 *   tcsConfigSetRelChopParams (chopNum &chopThrow, &chopPA, 
 *                           &chopFrame, &chopEquinox, &chopWavel)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   chopNum    (int)                 Chop number
 *      (>)   pChopThrow (struct DCAD_FIELD *) Structure for chop throw
 *      (>)   pChopPA    (struct DCAD_FIELD *) Structure for chop PA
 *      (>)   pChopFrame (struct FRAMECAD_FIELD *) Structure for chop frame
 *      (>)   pChopEquinox (struct EPOCHCAD_FIELD *) Structure for equinox
 *      (>)   pari (int) Position angle relative to instrument
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Need to decide whether all this data goes into the TCB or not
 *
 *-
 */

void tcsConfigSetRelChopParams(int chopNum,
                            struct DCAD_FIELD *pChopThrow,
                            struct DCAD_FIELD *pChopPA,
                            struct FRAMECAD_FIELD *pChopFrame,
                            struct EPOCHCAD_FIELD *pChopEquinox,
                            int pari)
                            
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

/* Set needsCheck to true as there is a relationship between chop frequency
*  and throw that must be validated.
*/
    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->chop[chopNum-1].frame = *pChopFrame;
    pTCB->chop[chopNum-1].throw = *pChopThrow;
    pTCB->chop[chopNum-1].pa = *pChopPA;
    pTCB->chop[chopNum-1].eqx = *pChopEquinox;
    pTCB->chop[chopNum-1].pari = pari;
}

/*+
 *   Function name:
 *   tcsConfigActiveTCB
 *
 *   Purpose:
 *   Returns the active TCB
 *
 *   Description:
 *
 *   Invocation:
 *   tcsConfigActiveTCB ( )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *
 *   Function value:
 *     The active TCB
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *-
 */

TCBDEFN tcsConfigActiveTCB(void)
{
    return activeTCB;
}

/*+
 *   Function name:
 *   tcsConfigSetOdgwParams
 *
 *   Purpose:
 *   Stores the parameters of the ODGW setup command in a TCB
 *
 *   Description:
 *   In practice this routine currently does not actually store the data.
 *   It us simply used to trigger a check of the current configuration.
 *
 *   Invocation:
 *   tcsConfigSetOdgwParams () 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *     None
 * 
 *-
 */

void tcsConfigSetOdgwParams(void)
{

    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

}

/*+
 *   Function name:
 *   tcsConfigSetAOConfiguration
 *
 *   Purpose:
 *   Store the AO configuration in the configuration part (non-target 
 *   specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the mode parameters passed to it and 
 *   copies them to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetAOConfiguration(&aostruct)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  aostruct (struct ICAD_FIELD*)      Mode value, 0 or 1 
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetAOConfiguration(struct ICAD_FIELD *aostruct)
{
   if (activeTCB == CURRENT) {
        currentTCB.sysconfig.AOconfig = *aostruct;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        presetTCB.sysconfig.AOconfig = *aostruct;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetP1LGSMode
 *
 *   Purpose:
 *   Store the P1 + LGS mode in the configuration part (non-target 
 *   specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the mode parameters passed to it and 
 *   copies them to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetP1LGSMode(&modestruct)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  modestruct (struct ICAD_FIELD*)      Mode value, 0 or 1 
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetP1LGSMode(struct ICAD_FIELD *modestruct)
{
    if (activeTCB == CURRENT) {
        currentTCB.sysconfig.p1LGSMode = *modestruct;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        presetTCB.sysconfig.p1LGSMode = *modestruct;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetOffset
 *
 *   Purpose:
 *   Stores the parameters of a new offset in a TCB
 *
 *   Description:
 *   This routine simply takes the input data passed to it and stores it
 *   in an appropriate place in the active Telescope Control Block (TCB)
 *
 *   Invocation:
 *   tcsConfigSetOffset (tel, offsetNum, &offbase ) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)    offsetNum (int)  The number of the offset
 *      (>)    offbase   (struct OFFBASE*) 
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   There is no warning that the offset number lies outside the expected range
 *   If the number is out of range the routine fails silently and does nothing.
 *-
 */

void tcsConfigSetOffset(TELESCOPE tel, int offsetNum,
                        struct OFFBASE *offbase)
{

    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    if (offsetNum >= 0 && offsetNum < 3) {
        pTCB->ob[offsetNum][tel] = *offbase;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetPoOffset
 *
 *   Purpose:
 *   Stores the parameters of a new pointing origin offset in a TCB
 *
 *   Description:
 *   This routine simply takes the input data passed to it and stores it
 *   in an appropriate place in the active Telescope Control Block (TCB)
 *
 *   Invocation:
 *   tcsConfigSetPoOffset (tel, offsetNum, &imagepos ) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)    offsetNum (int)  The number of the offset
 *      (>)    imagepos   (struct IMAGEPOS*) 
 *
 *   Function value:
 *     None
 * 
 *   Deficiencies:
 *   There is no warning that the offset number or telescope index
 *   lies outside the expected range. If the number is out of range 
 *   the routine fails silently and does nothing.
 *-
 */

void tcsConfigSetPoOffset(TELESCOPE tel, int offsetNum,
                          struct IMAGEPOS *imagepos)
{

    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    if (offsetNum >= 0 && offsetNum < 3) {
      if (tel < PWFS1) {
        pTCB->porob[offsetNum][tel] = *imagepos;
      }
    }
}

/*+
 *   Function name:
 *   tcsConfigSetPo
 *
 *   Purpose:
 *   Stores the parameters of a new pointing origin in a TCB
 *
 *   Description:
 *   This routine simply takes the input data passed to it and stores it
 *   in an appropriate place in the active Telescope Control Block (TCB)
 *
 *   Invocation:
 *   tcsConfigSetPo (tel, &po ) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)    po        (struct IMAGEPOS*)
 *
 *   Function value:
 *     None
 * 
 *   Deficiencies:
 *-
 */

void tcsConfigSetPo(TELESCOPE tel, struct IMAGEPOS *po)
{

    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    if (tel < PWFS1) {
      pTCB->por[tel] = *po;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetPFilt
 *
 *   Purpose:
 *   Stores the parameters of a new pointing filter in a TCB
 *
 *   Description:
 *   This routine simply takes the input data passed to it and stores it
 *   in an appropriate place in the active Telescope Control Block (TCB)
 *
 *   Invocation:
 *   tcsConfigSetPFilt ( &filt ) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    filt      (struct POINTFILTER*)
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *-
 */

void tcsConfigSetPFilt(struct POINTFILTER *filt)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->pf2 = *filt;
}

/*+
 *   Function name:
 *   tcsConfigSetTFilt
 *
 *   Purpose:
 *   Stores the parameters of a new target filter in a TCB
 *
 *   Description:
 *   This routine simply takes the input data passed to it and stores it
 *   in an appropriate place in the active Telescope Control Block (TCB)
 *
 *   Invocation:
 *   tcsConfigSetTFilt ( &filt ) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    filt      (struct POINTFILTER*)
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *-
 */

void tcsConfigSetTFilt(struct TARGETFILTER *filt)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->tf1 = *filt;
}

/*+
 *   Function name:
 *   tcsConfigSetTarget
 *
 *   Purpose:
 *   Store the parameters of a new target in a TCB.
 *
 *   Description:
 *   The routine simply takes the input target data structure passed to it and 
 *   copies it in the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetTarget(tel, &target)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)  target    (TARGET *)  Pointer to target structure for this telescope
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetTarget(TELESCOPE tel, struct TARGET *target)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->target[tel] = *target;
}

/*+
 *   Function name:
 *   tcsConfigGetGuideIndex
 *
 *   Purpose:
 *   Fetch the index of the guider attached to this virtual guider
 *
 *   Description:
 *   Each of the generic virtual guiders g1 to g4 can be linked to one
 *   or more of the 7  physical guiders TTGS1, TTGS2, TTGS3, ODGW1, ODGW2,
 *   ODGW3 or ODGW4. The guider "NONE" is a special case when there is no
 *   link yet established. This routine gets the index of the physical guider
 *   for the specified generic guider 
 *
 *   Invocation:
 *   tcsConfigGetGuideIndex(gindex, &pindex)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  gindex   (int)    Guider index (0 - 3) 
 *      (<)  pindex   (int *)  Physical guide index (0 - 7) 
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetGuideIndex(int gindex, int *pindex)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    if (gindex >=0 && gindex < 4) {
      *pindex = pTCB->vgconfig[gindex].destination ;
    } else {
      *pindex = 0;
    }
}
/*+
 *   Function name:
 *   tcsConfigSetVgconfig
 *
 *   Purpose:
 *   Store the guider configuration parameters in a TCB.
 *
 *   Description:
 *   Each of the generic virtual guiders g1 to g4 can be linked to one
 *   or more of the 7  physical guiders TTGS1, TTGS2, TTGS3, ODGW1, ODGW2,
 *   ODGW3 or ODGW4. This routine sets the indices that identify which
 *   of the seven are actually in use.
 *
 *   Invocation:
 *   tcsConfigSetVgconfig(gindex, &vgconfig)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  gindex   (int) Guider index (0 - 3) 
 *      (>)  vgconfig (VGCONFIG *)  Pointer to config structure for guider 
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetVgconfig(int gindex, struct VGCONFIG *vgconfig)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    if (gindex >=0 && gindex < 4) {
      pTCB->vgconfig[gindex] = *vgconfig;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetWavel
 *
 *   Purpose:
 *   Store the parameters of a new effective wavelength in a TCB.
 *
 *   Description:
 *   The routine simply takes the input target data structure passed to it and 
 *   copies it in the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetWavel(tel, &wavel)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)  wavel     (TARGET *)  Pointer to wavel structure for this telescope
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetWavel(TELESCOPE tel, struct WAVEL *wavel)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->wavel[tel] = *wavel;
}

/*+
 *   Function name:
 *   tcsConfigSetDiffTrack
 *
 *   Purpose:
 *   Store the parameters of a new differential tracking in a TCB.
 *
 *   Description:
 *   The routine takes the input target data structure passed to it and 
 *   copies it in the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetDiffTrack(tel, &difftrack)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)  difftrack (DIFFTRACK *)  Pointer to difftrack structure for this telescope
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetDiffTrack(TELESCOPE tel, struct DIFFTRACK *difftrack)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->difftrack[tel] = *difftrack;
}


/*+
 *   Function name:
 *   tcsConfigResetRates
 *
 *   Purpose:
 *   Reset differential track rates without triggering a check
 *
 *   Description:
 *   The differential track rates of the specified telescope are reset
 *   to new values. Currently the only reason for doing this is that
 *   the TCB track rates are displayed. When tracking a non sidereal
 *   object this means changes in the track rates will get displayed.
 *   Alternatively the kernel track rates could be displayed but these
 *   are in the tracking frame not the users input frame.
 *
 *   Invocation:
 *   tcsConfigResetRates(i, tt, dtheta1, dtheta2)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    i       (int)    Index to telescope
 *      (>)    tt      (double) Reference time MJD on TT timescale
 *      (>)    dtheta1 (double) Track rate rads/day
 *      (>)    dtheta2 (double) Track rate in rads/day
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsConfigResetRates(int i, double tt, double dtheta1, double dtheta2)
{
  struct TCB *pTCB;

  if (activeTCB == CURRENT)
      pTCB = &currentTCB;
  else
      pTCB = &presetTCB;

  if (i < MOUNT || i > G4) {
    return ;
  } else {
    pTCB->difftrack[i].t0.val = tt;
    pTCB->difftrack[i].dtheta1.val = dtheta1;
    pTCB->difftrack[i].dtheta2.val = dtheta2;
  }

}

/*+
 *   Function name:
 *   tcsConfigUpdateDiffTrack
 *
 *   Purpose:
 *   Update the differential tracking zero time in a TCB.
 *
 *   Description:
 *   The target position in the currently active TCB is adjusted to
 *   match the new zero time and optionally the track rates set to zero
 *   in the target frame.
 *
 *   Invocation:
 *   tcsConfigUpdateDiffTrack(tel, tt, zero)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)  tt        (double)  New zero time
 *      (>)  zero      (double)  TRUE to set the track rates to zero
 *
 *   Function value:
 *      None
 * 
 *   Deficiencies:
 *   Updating the target position only works correctly if the target and
 *   differential tracking frames are the same.
 *
 *-
 */

void tcsConfigUpdateDiffTrack(TELESCOPE tel, double tt, int zero)
{
    struct TCB *pTCB;
    double dt;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    dt = tt - pTCB->difftrack[tel].t0.val;
    if (zero) {
       pTCB->difftrack[tel].dtheta1.val = 0.0;
       pTCB->difftrack[tel].dtheta2.val = 0.0;
       pTCB->difftrack[tel].frame.val = pTCB->target[tel].frame.val;
       pTCB->difftrack[tel].eqx.val = pTCB->target[tel].eqx.val;
    } else {
       pTCB->target[tel].theta1.val += pTCB->difftrack[tel].dtheta1.val * dt;
       pTCB->target[tel].theta2.val += pTCB->difftrack[tel].dtheta2.val * dt;
    }
    pTCB->difftrack[tel].t0.val = tt;
}

/*+
 *   Function name:
 *   tcsConfigSetTrack
 *
 *   Purpose:
 *   Store the parameters of a new tracking frame in a TCB.
 *
 *   Description:
 *   The routine simply takes the input track data structure passed to it and 
 *   copies it in the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetTrack(tel, &track)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (>)  target    (TRACK *)  Pointer to track structure for this telescope
 *
 *   Function value:
 *      None
 * 
 *
 *-
 */

void tcsConfigSetTrack(TELESCOPE tel, struct TRACK *track)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    pTCB->track[tel] = *track;
}

/*+
 *   Function name:
 *   tcsConfigSetWrap
 *
 *   Purpose:
 *   Store the wrap parameters in the configuration part (non-target 
 *   specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the input wrap parameter values passed to it and 
 *   copies them to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetWrap(wrap, wrapval)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  wrap    (WRAP)      Which wrap, AZIMUTH or ROTATOR
 *      (>)  wrapval (struct ICAD_FIELD*)      Wrap value, -1/0/+1 
 *
 *   Function value:
 *      None
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

void tcsConfigSetWrap(WRAP wrap, struct ICAD_FIELD *wrapval)
{
    if (activeTCB == CURRENT) {
        if (wrap == AZIMUTH)
            currentTCB.sysconfig.azwrap = *wrapval;
        if (wrap == ROTATOR)
            currentTCB.sysconfig.rotwrap = *wrapval;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        if (wrap == AZIMUTH)
            presetTCB.sysconfig.azwrap = *wrapval;
        if (wrap == ROTATOR)
            presetTCB.sysconfig.rotwrap = *wrapval;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetGuide
 *
 *   Purpose:
 *   Store the parameters of a guide configuration tracking frame in a TCB.
 *
 *   Description:
 *   The routine simply takes the input guide data structure passed to it and 
 *   copies it in the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetGuide(nguide, &guide)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  nguide    (int)      Guide probe number
 *      (>)  guide     (GUIDE *)  Pointer to guide structure
 *
 *   Function value:
 *      None
 * 
 *   Deficiencies:
 *   Fails silently if nguide is out of range
 *
 *-
 */

void tcsConfigSetGuide(int nguide, struct GUIDE *guide)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

    if (nguide >= 0 && nguide < 7) {
      pTCB->guide[nguide] = *guide;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetClipAtLimit
 *
 *   Purpose:
 *   Store the check limits flag in the configuration part (non-target 
 *   specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the input flag parameter values passed to it and 
 *   copies them to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetClipAtLimit(flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  flag (struct ICAD_FIELD*)      Flag value
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetClipAtLimit( struct ICAD_FIELD *flag)
{
    if (activeTCB == CURRENT) {
        currentTCB.sysconfig.clipAtLimit = *flag;
    }
    if (activeTCB == PRESET) {
        presetTCB.sysconfig.clipAtLimit = *flag;
    }
}


/*+
 *   Function name:
 *   tcsConfigSetSlew
 *
 *   Purpose:
 *   Store the slew reset data in a TCB.
 *
 *   Description:
 *   The routine simply takes the input slew structure passed to it and 
 *   copies it to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetSlew(slew)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  slew (struct SLEW*)      Slew structure
 *
 *   Function value:
 *      None
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

void tcsConfigSetSlew( struct SLEW *slew)
{
    if (activeTCB == CURRENT) {
        currentTCB.slew = *slew;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        presetTCB.slew = *slew;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}

/*+
 *   Function name:
 *   tcsConfigSetRot
 *
 *   Purpose:
 *   Store the rotator configuration in the configuration part 
 *   (non-target specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the structure passed to it and 
 *   copies it to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetRot( &rot )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  rot  (struct ROT*)      Rotator configuration
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetRot(struct ROT *rot)
{
    if (activeTCB == CURRENT) {
        currentTCB.sysconfig.rot = *rot;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        presetTCB.sysconfig.rot = *rot;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}
/*+
 *   Function name:
 *   tcsConfigSetPlanet
 *
 *   Purpose:
 *   Store the planet data in the configuration part 
 *   (non-target specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the input planet name value passed to it and 
 *   copies it to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *   Note that we currently always assume the target virtual telescope is
 *   SOURCE_A. The CAD commands that would allow specifying a planet for
 *   other virtual telescops are not yet implemented.
 *
 *   Invocation:
 *   tcsConfigSetPlanet( &planet )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  planet  (struct PLANET*)      Planet name structure
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetPlanet(struct PLANET *planet)
{
    if (activeTCB == CURRENT) {
        currentTCB.planet[SOURCE_A] = *planet;
        currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
        presetTCB.planet[SOURCE_A] = *planet;
        presetTCB.sysconfig.needsCheck = TRUE;
    }
}
/*+
 *   Function name:
 *   tcsConfigSetOrbit
 *
 *   Purpose:
 *   Store the orbit data in the configuration part 
 *   (non-target specific data) of a TCB.
 *
 *   Description:
 *   The routine simply takes the input orbit data passed to it and 
 *   copies it to the appropriate place in the currently active
 *   Telescope Control Block (TCB).
 *
 *   Invocation:
 *   tcsConfigSetOrbit( &orbit, tel )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  orbit  (struct ORBIT*)      Orbit structure
 *      (>)  tel    TELESCOPE            Virtual telescope identifier 
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigSetOrbit(struct ORBIT *orbit, TELESCOPE tel)
{
    if (activeTCB == CURRENT) {
      currentTCB.orbit[tel] = *orbit ;
      currentTCB.sysconfig.needsCheck = TRUE;
    }
    if (activeTCB == PRESET) {
      presetTCB.orbit[tel] = *orbit;
      presetTCB.sysconfig.needsCheck = TRUE;
    }
}

/*+
 *   Function name:
 *   tcsConfigGetOffset
 *
 *   Purpose:
 *   Fetch the offsets of a specified telescope from a TCB
 *
 *   Description:
 *   Simply return the data for the specified telescope from the TCB
 *
 *   Invocation:
 *   tcsConfigGetOffset(tcbDefn, tel, offnum, &coord, &dtheta1, &dtheta2 )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel       (TELESCOPE) Type specifying the telescope
 *      (>)  offnum    (int )    The offset number
 *      (<)  coord     (OFFCOORD *) The offset coordinate system
 *      (<)  dtheta1   (double *) The offset in the first axis
 *      (<)  dtheta2   (double *) The offset in the second axis
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   1. No check that offnum is in correct range, defaults to 0 silently
 *
 *-
 */

void tcsConfigGetOffset(TCBDEFN tcbDefn, TELESCOPE tel, int offnum,
                      OFFCOORD * coord, double *dtheta1, double *dtheta2)
{
    struct TCB *pTCB;

    if (offnum < 0 || offnum > 2)
        offnum = 0;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    *coord = pTCB->ob[offnum][tel].coord.val;
    *dtheta1 = pTCB->ob[offnum][tel].dtheta1.val;
    *dtheta2 = pTCB->ob[offnum][tel].dtheta2.val;
}

/*+
 *   Function name:
 *   tcsConfigGetPoOffset
 *
 *   Purpose:
 *   Fetch the pointing origin offsets of a specified telescope from a TCB
 *
 *   Description:
 *   Simply return the data for the specified telescope from the TCB
 *
 *   Invocation:
 *   tcsConfigGetPoOffset(tcbDefn, tel, offnum, &x, &y )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel       (TELESCOPE) Type specifying the telescope
 *      (>)  offnum    (int )    The offset number
 *      (<)  x         (double *) The offset in the first axis
 *      (<)  y         (double *) The offset in the second axis
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   1. No check that offnum is in correct range, defaults to 0 silently
 *
 *-
 */

void tcsConfigGetPoOffset(TCBDEFN tcbDefn, TELESCOPE tel, int offnum,
                          double *x, double *y)
{
    struct TCB *pTCB;

    if (offnum < 0 || offnum > 2)
        offnum = 0;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    if (tel < PWFS1) {
      *x = pTCB->porob[offnum][tel].x.val;
      *y = pTCB->porob[offnum][tel].y.val;
    } else {
      *x = 0.0;
      *y = 0.0;
    }
}

/*+
 *   Function name:
 *   tcsConfigGetPFilt
 *
 *   Purpose:
 *   Fetch the pointing filter parameters from a TCB
 *
 *   Description:
 *   Simply return the data for the specified telescope from the TCB
 *
 *   Invocation:
 *   tcsConfigGetPFilt(tcbDefn, &weightA, &weightB, &weightC, &weightNod, 
 *   &bw, &maxv, &grab, &sc )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (<)  weightA  (double *) The weight for source A
 *      (<)  weightB  (double *) The weight for source B
 *      (<)  weightC  (double *) The weight for source C
 *      (<)  weightNod (double *) The weight for nod state
 *      (<)  bw       (double *) The bandwidth
 *      (<)  maxv     (double *) The minimum discrepancy
 *      (<)  grab     (double *) The grab parameter
 *      (<)  sc       (int *)    The short circuit parameter
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *
 *-
 */

void tcsConfigGetPFilt(TCBDEFN tcbDefn, double *weightA,
                       double *weightB, double *weightC, double *weightNod,
                       double *bw, double *maxv, double *grab, int *sc)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

     *weightA = pTCB->pf2.weightA.val;
     *weightB = pTCB->pf2.weightB.val;
     *weightC = pTCB->pf2.weightC.val;
     *weightNod = pTCB->pf2.weightNod.val;
     *bw = pTCB->pf2.bw.val;
     *maxv = pTCB->pf2.maxv.val;
     *grab = pTCB->pf2.grab.val;
     *sc = pTCB->pf2.sc.val;
}

/*+
 *   Function name:
 *   tcsConfigGetTFilt
 *
 *   Purpose:
 *   Fetch the target filter parameters from a TCB
 *
 *   Description:
 *   Simply return the data for the specified telescope from the TCB
 *
 *   Invocation:
 *   tcsConfigGetTFilt(tcbDefn, &bw, &maxv &grab, &sc )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (<)  bw       (double *) The bandwidth
 *      (<)  maxv     (double *) The minimum discrepancy
 *      (<)  grab     (double *) The grab parameter
 *      (<)  sc       (int *)    The short circuit parameter
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *
 *-
 */

void tcsConfigGetTFilt(TCBDEFN tcbDefn, double *bw,
                       double *maxv, double *grab, int *sc)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

     *bw = pTCB->tf1.bw.val;
     *maxv = pTCB->tf1.maxv.val;
     *grab = pTCB->tf1.grab.val;
     *sc = pTCB->tf1.sc.val;
}

/*+
 *   Function name:
 *   tcsConfigGetChop
 *
 *   Purpose:
 *   Fetch the chop parameters from a TCB
 *
 *   Description:
 *   Simply return the data for the specified chop from the TCB
 *
 *   Invocation:
 *   tcsConfigGetChop(tcbDefn, chopnum, &mode, &frame, &eqx, &throw &pa, &pari)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  chopnum  (int )     The chop number
 *      (<)  mode     (int *)    The chop mode
 *      (<)  frame    (FRAMETYPE *) The chop frame
 *      (<)  eqx      (double *) The chop equinox
 *      (<)  throw    (double *) The chop throw
 *      (<)  pa       (double *) The chop position angle
 *      (<)  pari     (int *)    Angle relaive to IPA
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   1. No check that chopnum is in correct range, defaults to 1 silently
 *
 *-
 */

void tcsConfigGetChop(TCBDEFN tcbDefn, int chopnum, int *mode,
                      FRAMETYPE *frame, double *eqx, double *throw, 
                      double *pa, int *pari)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    *mode = pTCB->chop[chopnum-1].mode.val;
    *frame = pTCB->chop[chopnum-1].frame.val;
    if (currentTCB.chop[chopnum-1].frame.val == FK5) {
        *eqx = slaEpco('J', currentTCB.chop[chopnum-1].eqx.val.type,
                         currentTCB.chop[chopnum-1].eqx.val.year);
    } else if (currentTCB.chop[chopnum-1].frame.val == FK4) {
        *eqx = slaEpco('B', currentTCB.chop[chopnum-1].eqx.val.type,
                         currentTCB.chop[chopnum-1].eqx.val.year);
    } else {
        *eqx = currentTCB.chop[chopnum-1].eqx.val.year;
    }
    *throw = pTCB->chop[chopnum-1].throw.val;
    *pa = pTCB->chop[chopnum-1].pa.val;
    *pari = pTCB->chop[chopnum-1].pari;
}

/*+
 *   Function name:
 *   tcsConfigGetGuide
 *
 *   Purpose:
 *   Fetch the guide parameters from a TCB
 *
 *   Description:
 *   Simply return the data for the specified guide star from the TCB
 *
 *   Invocation:
 *   tcsConfigGetGuide(tcbDefn, guidenum, &act)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  guidenum (int )     The guider number
 *      (<)  act      (int [3][3])    The active flags
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   1. No check that chopnum is in correct range, defaults to 1 silently
 *
 *-
 */

void tcsConfigGetGuide(TCBDEFN tcbDefn, int guidenum, int act[3][3])
{
    struct TCB *pTCB;
    int inod, ichop;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    for ( inod = 0; inod < 3; inod++ ) {
        for ( ichop = 0; ichop < 3; ichop++ ) {
            act[inod][ichop] = pTCB->guide[guidenum].act[inod][ichop].val;
        }
    }
}

/*+
 *   Function name:
 *   tcsConfigGetPo
 *
 *   Purpose:
 *   Fetch the pointing origin of a specified telescope from a TCB
 *
 *   Description:
 *   Simply return the data for the specified telescope from the TCB
 *
 *   Invocation:
 *   tcsConfigGetPo(tcbDefn, tel, &x, &y )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel       (TELESCOPE) Type specifying the telescope
 *      (<)  x         (double *) The pointing origin in the first axis
 *      (<)  y         (double *) The pointing origin in the second axis
 *
 *   Function value:
 *     None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   1. No check that offnum is in correct range, defaults to 0 silently
 *
 *-
 */

void tcsConfigGetPo(TCBDEFN tcbDefn, TELESCOPE tel,
                    double *x, double *y)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    if (tel < PWFS1) {
      *x = pTCB->por[tel].x.val;
      *y = pTCB->por[tel].y.val;
    } else {
      *x = 0.0;
      *y = 0.0;
    }
}

/*+
 *   Function name:
 *   tcsConfigGetWavel
 *
 *   Purpose:
 *   Fetch the parameters of a new target from a  TCB.
 *
 *   Description:
 *   This routine simply returns the data for a specified target and TCB
 *
 *   Invocation:
 *   tcsConfigGetWavel( tcbDefn, tel, &wavel)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn   (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel       (TELESCOPE) Enumerated type specifying telescope
 *      (<)  wavel     (double *)   Wavelength (microns)
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetWavel(TCBDEFN tcbDefn, TELESCOPE tel, double *wavel)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    *wavel = pTCB->wavel[tel].wavel.val;
}

/*+
 *   Function name:
 *   tcsConfigGetTrack
 *
 *   Purpose:
 *   Fetch the parameters of a new target from a  TCB.
 *
 *   Description:
 *   This routine simply returns the data for a specified target and TCB
 *
 *   Invocation:
 *   tcsConfigGetTrack( tcbDefn, tel, &frame, &teqx, &theta1, &theta2,
 *       &dtheta1, &dtheta2, &t0)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel      (TELESCOPE) Enumerated type specifying telescope
 *      (<)  frame    (FRAMETYPE * )     Code for tracking coordinate frame
 *      (<)  eqx      (struct EPOCH *)   Equinox of tracking frame
 *      (<)  theta1   (double *)   RA or Azimuth
 *      (<)  theta2   (double *)   Dec or El
 *      (<)  dtheta1  (double *)   Differential rate in theta1
 *      (<)  dtheta2  (double *)   Differential rate in theta2
 *      (<)  t0       (double *)   Zero time for differential rate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetTrack(TCBDEFN tcbDefn, TELESCOPE tel,
                        FRAMETYPE * frame, struct EPOCH *eqx,
                        double *theta1, double *theta2, double *dtheta1,
                        double *dtheta2, double *t0)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    *frame = pTCB->track[tel].frame.val;
    *eqx = pTCB->track[tel].eqx.val;
    *theta1 = pTCB->track[tel].theta1;
    *theta2 = pTCB->track[tel].theta2;
    *dtheta1 = pTCB->track[tel].dtheta1;
    *dtheta2 = pTCB->track[tel].dtheta2;
    *t0 = pTCB->track[tel].t0;
}

/*+
 *   Function name:
 *   tcsConfigGetDiffTrack
 *
 *   Purpose:
 *   Fetch the parameters of differential tracking from a  TCB.
 *
 *   Description:
 *   This routine simply returns the data for a specified target and TCB
 *
 *   Invocation:
 *   tcsConfigGetDiffTrack( tcbDefn, tel, &zeroTime, &frame, 
 *                       &eqx, &dtheta1, &dtheta2 )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)  tel      (TELESCOPE) Enumerated type specifying telescope
 *      (<)  zeroTime (struct EPOCH *)   Start time for differential tracking
 *      (<)  frame    (FRAMETYPE * )     Code for coordinate frame
 *      (<)  eqx      (struct EPOCH *)   Equinox of frame
 *      (<)  dtheta1  (double *)   Differential track rate RA or Az
 *      (<)  dtheta2  (double *)   Differential track rate Dec or Elevation
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetDiffTrack(TCBDEFN tcbDefn, TELESCOPE tel,
                        FRAMETYPE *frame, struct EPOCH *eqx,
                        double *zeroTime, double *dtheta1, double *dtheta2)
{
    struct TCB *pTCB;

    if (tcbDefn == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    *frame = pTCB->difftrack[tel].frame.val;
    eqx->year = pTCB->difftrack[tel].eqx.val.year;
    eqx->type = pTCB->difftrack[tel].eqx.val.type;
    *zeroTime = pTCB->difftrack[tel].t0.val;
    *dtheta1 = pTCB->difftrack[tel].dtheta1.val;
    *dtheta2 = pTCB->difftrack[tel].dtheta2.val;
}

/*+
 *   Function name:
 *   tcsConfigGetSysconfig
 *
 *   Purpose:
 *   Fetch the non-target specific data from a TCB.
 *
 *   Description:
 *   This routine fetches target independent data from a 'sysconfig' data 
 *   structure for a specified TCB
 *
 *   Invocation:
 *   tcsConfigGetSysConfig( tcbDefn, &azwrap, &rotwrap, &ipa, &r_frame, &r_eqx, ia, &chopmode);
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (<)  azwrap   (int *)    Pointer to azimuth wrap value
 *      (<)  rotwrap  (int *)    Pointer to rotator wrap value
 *      (<)  ipa      (double *) Pointer to instrument position angle
 *      (<)  r_frame  (FRAMETYPE *)    Pointer to frame of position angle
 *      (<)  r_eqx    (double *) Pointer to equinox of frame
 *      (<)  ia       (double *) Pointer to instrument alignment
 *      (<)  chopmode (int *)    Pointer to chop mode
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetSysconfig(TCBDEFN tcbDefn, int *azwrap, 
         int *rotwrap, double *ipa, FRAMETYPE * r_frame, double *r_eqx, 
         double *ia, int *chopmode)
{
    if (tcbDefn == CURRENT) {
        *azwrap = currentTCB.sysconfig.azwrap.val;
        *rotwrap = currentTCB.sysconfig.rotwrap.val;
        *ipa = currentTCB.sysconfig.rot.ipa.val;
        *r_frame = currentTCB.sysconfig.rot.frame.val;
        if (currentTCB.sysconfig.rot.frame.val == FK5) {
            *r_eqx = slaEpco('J', currentTCB.sysconfig.rot.eqx.val.type,
                             currentTCB.sysconfig.rot.eqx.val.year);
        } else if (currentTCB.sysconfig.rot.frame.val == FK4) {
            *r_eqx = slaEpco('B', currentTCB.sysconfig.rot.eqx.val.type,
                             currentTCB.sysconfig.rot.eqx.val.year);
        } else {
            *r_eqx = currentTCB.sysconfig.rot.eqx.val.year;
        }
        *ia = currentTCB.sysconfig.rot.iaa.val;
        *chopmode = currentTCB.sysconfig.chopmode.val;
    }
    if (tcbDefn == PRESET) {
        *azwrap = presetTCB.sysconfig.azwrap.val;
        *rotwrap = presetTCB.sysconfig.rotwrap.val;
        *ipa = presetTCB.sysconfig.rot.ipa.val;
        *r_frame = presetTCB.sysconfig.rot.frame.val;
        if (presetTCB.sysconfig.rot.frame.val == FK5) {
            *r_eqx = slaEpco('J', presetTCB.sysconfig.rot.eqx.val.type,
                             presetTCB.sysconfig.rot.eqx.val.year);
        } else if (presetTCB.sysconfig.rot.frame.val == FK4) {
            *r_eqx = slaEpco('B', presetTCB.sysconfig.rot.eqx.val.type,
                             presetTCB.sysconfig.rot.eqx.val.year);
        } else {
            *r_eqx = presetTCB.sysconfig.rot.eqx.val.year;
        }
        *ia = presetTCB.sysconfig.rot.iaa.val;
        *chopmode = presetTCB.sysconfig.chopmode.val;
    }
}

/*+
 *   Function name:
 *   tcsConfigGetPlanet
 *
 *   Purpose:
 *   Fetch the planet data from a TCB.
 *
 *   Description:
 *   This routine fetches planet data from a 'planet' data 
 *   structure for a specified TCB. It will be used by the pointing code to 
 *   decide how to handle the different virtual telescopes. The routine
 *   sets the flags based on both the ephemeris flag in the target structure
 *   and the planet structure. This is historical as at one time only
 *   the planet structure was relevant.
 *
 *   Invocation:
 *   tcsConfigGetSysPlanet( tcbDefn, &planet, &override_rates)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn          (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (<)  planet[]         (PLANET *) Pointer to planet codes
 *      (<)  override_rates[] (int*) Override rates flags
 *
 *   Function value:
 *      None
 * 
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsConfigGetPlanet(TCBDEFN tcbDefn, PLANET *planet, int *override_rates) 
{
    int i ;                

    if (tcbDefn == CURRENT) {
      for ( i = 0; i < 11; i++) {
        if (currentTCB.target[i].ephemeris) {
          planet[i] = EPHEMERIS;
          override_rates[i] = 1 ;
        } else {
          planet[i] = NO_PLANET ;
          override_rates[i] = 0 ;
        }
        planet[i] = currentTCB.planet[i].code.val;
        override_rates[i] = currentTCB.planet[i].override_rates;
      }
    }
    if (tcbDefn == PRESET) {
      for ( i = 0; i < 11; i++) {
        if (presetTCB.target[i].ephemeris) {
          planet[i] = EPHEMERIS;
          override_rates[i] = 1 ;
        } else {
          planet[i] = NO_PLANET ;
          override_rates[i] = 0 ;
        }
        planet[i] = presetTCB.planet[i].code.val;
        override_rates[i] = presetTCB.planet[i].override_rates;
      }
    }
}

/*+
 *   Function name:
 *   tcsConfigGetOrbit
 *
 *   Purpose:
 *   Fetch the orbit data from a TCB.
 *
 *   Description:
 *   This routine fetches orbit data from a 'orbit' data 
 *   structure for a specified TCB
 *
 *   Invocation:
 *   tcsConfigGetOrbit( tcbDefn, epoch, jform, orbinc, anode, perih, 
 *                         aorq, e, aorl, dm)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)   Enumerated type, CURRENT or PRESET
 *      (<)  jform[]  (int*)      Element set code
 *      (<)  epoch[]  (double*)   Epoch of elements
 *      (<)  orbinc[] (double*)   Orbital inclination
 *      (<)  anode[]  (double*)   Longitude of ascending node
 *      (<)  perih[]  (double*)   Longitude or argument of perihelion
 *      (<)  aorq[]   (double*)   Mean or perihelion distance
 *      (<)  e[]      (double*)   Eccentricity
 *      (<)  aorl[]   (double*)   Mean anomoly or longitude
 *      (<)  dm[]     (double*)   Daily motion
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetOrbit(TCBDEFN tcbDefn, int *jform, 
   double *epoch, double *orbinc, double *anode, double *perih, double *aorq,
   double *e, double *aorl, double *dm) 
{
    int i ;                        /* Loop index */

    if (tcbDefn == CURRENT) {
       for (i = 0; i < 11; i++) {
         jform[i] = currentTCB.orbit[i].jform.val;
         epoch[i] = currentTCB.orbit[i].epoch.val;
         orbinc[i] = currentTCB.orbit[i].orbinc.val;
         anode[i] = currentTCB.orbit[i].anode.val;
         perih[i] = currentTCB.orbit[i].perih.val;
         aorq[i] = currentTCB.orbit[i].aorq.val;
         e[i] = currentTCB.orbit[i].e.val;
         aorl[i] = currentTCB.orbit[i].aorl.val;
         dm[i] = currentTCB.orbit[i].dm.val;
       }
    }
    if (tcbDefn == PRESET) {
       for (i = 0; i < 11; i++) {
         jform[i] = presetTCB.orbit[i].jform.val;
         epoch[i] = presetTCB.orbit[i].epoch.val;
         orbinc[i] = presetTCB.orbit[i].orbinc.val;
         anode[i] = presetTCB.orbit[i].anode.val;
         perih[i] = presetTCB.orbit[i].perih.val;
         aorq[i] = presetTCB.orbit[i].aorq.val;
         e[i] = presetTCB.orbit[i].e.val;
         aorl[i] = presetTCB.orbit[i].aorl.val;
         dm[i] = presetTCB.orbit[i].dm.val;
       }
    }
}

/*+
 *   Function name:
 *   tcsConfigGetReftime
 *
 *   Purpose:
 *   Fetch the the reference time from a TCB. 
 *
 *   Description:
 *   This routine fetches reference time from a 'sysconfig' data structure 
 *   for a specified TCB
 *
 *   Invocation:
 *   tcsConfigGetReftime( tcbDefn, &reftime)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tcbDefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (<)  reftime  (int *)    Pointer to reference time
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsConfigGetReftime(TCBDEFN tcbDefn, double *reftime)
{
    if (tcbDefn == CURRENT) {
        *reftime = currentTCB.sysconfig.reftime;
    }
    if (tcbDefn == PRESET) {
        *reftime = presetTCB.sysconfig.reftime;
    }
}

/*+
 *   Function name:
 *   tcsConfigBegin
 *
 *   Purpose:
 *   Begin a new TCS configuration.
 *
 *   Description:
 *   This routine is called as soon as a new configuration is started by
 *   the OCS or by an engineering screen. It is tied to a cad record
 *   which is in turn the first record triggered by the top level Apply
 *   record. It will get called the top level Apply both when preset and
 *   start are issued. Any code that needs to be executed before preset
 *   or start is issued to any commands should be executed from this
 *   routine.
 *
 *   Invocation:
 *   tcsConfigBegin (pcad) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (cadRecord *)  Pointer to cad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsConfigBegin( cadRecord *pcad )
{

    static int dbgLevel = DBG_NONE ;  /* Set debug level */
    long status;                      /* return status */
    double tnow ;                     /* Raw time now */


/* Check for interlocks */

    if (tcsInterlocked(pcad->mess))
        status = CAD_REJECT;
    else {
        status = CAD_ACCEPT;
        switch (pcad->dir) {
        case menuDirectivePRESET:

/* Since this is the first user routine that will be called by the TCS
*  when a command is issued. Provide a time stamp if the debug level is
*  set to the correct value. These diagnostics are used in ST02000 and 
*  ST02003. 
*/
            (void) timeNow(&tnow) ;
            DBGMSGREAL (DBG_FULL, "tcsConfigBegin: preset at ", tnow) ;
            tcsConfigBeginPreset();
            break;

        case menuDirectiveSTART:
            (void) timeNow(&tnow) ;
            DBGMSGREAL (DBG_FULL, "tcsConfigBegin: start at ", tnow) ;
            tcsConfigBeginStart();
            break;

        default:
            break;
        }
    }

    return status;

}


/*+
 *   Function name:
 *   tcsConfigEnd
 *
 *   Purpose:
 *   End a new TCS configuration and tidy up.
 *
 *   Description:
 *   This routine is called once a new configuration has been started by
 *   the OCS or by an engineering screen. It is tied to a cad record
 *   which is in turn the last record triggered by the top level Apply
 *   record. It will get called by the top level Apply both when preset and
 *   start are issued. Any code that needs to be executed after preset
 *   or start is issued to any commands should be executed from this
 *   routine.
 *   In particular, the routine at present writes a mask value to a
 *   fanout record which in turn triggers processing in the kernel
 *
 *   Invocation:
 *   tcsConfigEnd (pcad) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (cadRecord *)  Pointer to cad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics outputs:
 *   vala => Mask for triggerring kernel behaviour
 *   valb => Mask for triggerring SAD updates
 *   valc => Trigger for GSAOI setup command.
 *-
 */

long tcsConfigEnd( cadRecord *pcad )
{

    long status;             /* return status */
    long outmask;            /* mask for triggering links on a fanout record */
    long sadmask;            /* mask for triggering links on a fanout record */
    long gsaoimask ;         /* Mask for triggering GSAOI submit */
    static int dbgLevel = DBG_NONE ; /* Debug level */
    double tnow ;            /* Raw time now */

    status = CAD_ACCEPT;

    switch (pcad->dir) {
    case menuDirectivePRESET:

        if (!firstSeqCommMarked)
            status = tcsConfigEndPreset(pcad);

        break;

    case menuDirectiveSTART:
        /*
         * Originally outmask and sadmask were used for triggering different
         * types of downstream activity. To avoid large changes to the
         * schematic there is now no real difference between them.
         */
        outmask = 0;
        sadmask = 0;
        gsaoimask = 0;
        /* The gsaoimask needs to be set irrespective of whether needsCheck
         * is true or false when certain commands are marked. In fact it
         * should be possible to put all the checks for gsaoimask here but
         * for time being (so we don't accidentally break anything else)
         * just check for the "adjust" commands which are issued from 
         * handsets and bypass the configuration checking
         */
        if (tcsGuideAnyOdgwFollowing()) {
          if (tcsCadInfoIsMarked("targetAdjust")  ||
            tcsCadInfoIsMarked("incrOffset")    ||
            tcsCadInfoIsMarked("poAdjust") ||
            tcsCadInfoIsMarked("clearOffset") ||
            tcsCadInfoIsMarked("clearPoOffset") ) gsaoimask = 7 ;
        }
        if (currentTCB.sysconfig.needsCheck == FALSE) {
            outmask = 0;
            sadmask = 0;
        } else {
            if (activeTCB == CURRENT) {
                if (recalcOTMs == TRUE)
                    outmask = 1;                  /* processes ak:source */
                else
                    outmask = 2;                  /* processes ak:newConfig */
                if (tcsCadInfoIsMarked("slew")) outmask += 4;
                if (currentTCB.slew.lpm.val) outmask += 8;
                if (tcsCadInfoIsMarked("g1orbit")) outmask +=16;
                if (tcsCadInfoIsMarked("g2orbit")) outmask +=32;
                if (tcsCadInfoIsMarked("planet") || 
                                     tcsCadInfoIsMarked("orbit")) sadmask += 1;
                if (tcsCadInfoIsMarked("pwfs1orbit")) sadmask += 2;
                if (tcsCadInfoIsMarked("pwfs2orbit")) sadmask += 4;
                if (tcsCadInfoIsMarked("oiwfsorbit")) sadmask += 8;
                if (tcsCadInfoIsMarked("g3orbit")) outmask +=16;
                if (tcsCadInfoIsMarked("g4orbit")) outmask +=32;
                
                /* New method of checking to see if a dataODGW command is
                 * needed to be sent to the GSAOI to set the window
                 * parameters.
                 */
                if (tcsCadInfoIsMarked("gsaoiodgwSetup") ||
                    tcsCadInfoIsMarked("odgw1Park") ||
                    tcsCadInfoIsMarked("odgw2Park") ||
                    tcsCadInfoIsMarked("odgw3Park") ||
                    tcsCadInfoIsMarked("odgw4Park") ||
                    tcsCadInfoIsMarked("odgw1Move") ||
                    tcsCadInfoIsMarked("odgw2Move") ||
                    tcsCadInfoIsMarked("odgw3Move") ||
                    tcsCadInfoIsMarked("odgw4Move") ) {
                     gsaoimask = 7;
                } else if ((tcsCadInfoIsMarked("odgw1Follow") ||
                    tcsCadInfoIsMarked("odgw2Follow") ||
                    tcsCadInfoIsMarked("odgw3Follow") ||
                    tcsCadInfoIsMarked("odgw4Follow")) &&
                    tcsGuideAnyOdgwFollowing() ) {
                      gsaoimask = 7;
                } else  {
                   if (tcsGuideAnyOdgwFollowing()) {
                     if (tcsCadInfoIsMarked("guiderConfig") ||
                         tcsCadInfoIsMarked("g1")           ||
                         tcsCadInfoIsMarked("g2")           ||
                         tcsCadInfoIsMarked("g3")           ||
                         tcsCadInfoIsMarked("g4")           ||
                         tcsCadInfoIsMarked("offsetG1A")    ||
                         tcsCadInfoIsMarked("offsetG1B")    ||
                         tcsCadInfoIsMarked("offsetG1C")    ||
                         tcsCadInfoIsMarked("offsetG2A")    ||
                         tcsCadInfoIsMarked("offsetG2B")    ||
                         tcsCadInfoIsMarked("offsetG2C")    ||
                         tcsCadInfoIsMarked("offsetG3A")    ||
                         tcsCadInfoIsMarked("offsetG3B")    ||
                         tcsCadInfoIsMarked("offsetG3C")    ||
                         tcsCadInfoIsMarked("offsetG4A")    ||
                         tcsCadInfoIsMarked("offsetG4B")    ||
                         tcsCadInfoIsMarked("offsetG4C") )  gsaoimask = 7; 
                     if (tcsCadInfoIsMarked("poriginM")        ||
                         tcsCadInfoIsMarked("poriginA")        ||
                         tcsCadInfoIsMarked("poriginB")        ||
                         tcsCadInfoIsMarked("poriginC")        ||
                         tcsCadInfoIsMarked("offsetMount")     ||
                         tcsCadInfoIsMarked("offsetSourceA")   ||
                         tcsCadInfoIsMarked("offsetSourceA1")  ||
                         tcsCadInfoIsMarked("offsetSourceA2")  ||
                         tcsCadInfoIsMarked("offsetSourceB")   ||
                         tcsCadInfoIsMarked("offsetSourceB1")  ||
                         tcsCadInfoIsMarked("offsetSourceB2")  ||
                         tcsCadInfoIsMarked("offsetSourceC")   ||
                         tcsCadInfoIsMarked("offsetSourceC1")  ||
                         tcsCadInfoIsMarked("offsetSourceC2") ) gsaoimask = 7; 
                     if (tcsCadInfoIsMarked("offsetPoM")     ||
                         tcsCadInfoIsMarked("offsetPoA")     ||
                         tcsCadInfoIsMarked("offsetPoA1")    ||
                         tcsCadInfoIsMarked("offsetPoA2")    ||
                         tcsCadInfoIsMarked("offsetPoB")     ||
                         tcsCadInfoIsMarked("offsetPoB1")    ||
                         tcsCadInfoIsMarked("offsetPoB2")    ||
                         tcsCadInfoIsMarked("offsetPoC")     ||
                         tcsCadInfoIsMarked("offsetPoC1")    ||
                         tcsCadInfoIsMarked("offsetPoB2") ) gsaoimask = 7; 
                   }
                }
            } else {
                outmask = 0;
                sadmask = 0;
                gsaoimask = 0;
                kernelTCB = presetTCB;
            }
        }
        *(long *) pcad->vala = outmask;
        *(long *) pcad->valb = sadmask;
        *(long *) pcad->valc = gsaoimask;
        tcsConfigEndStart();

/* Since this is the last user routine that will be called by the TCS
*  when a command is issued, provide a time stamp if the debug level is
*  set to the correct value. These diagnostices are used in ST02000. 
*/
    (void) timeNow(&tnow) ;
    DBGMSGREAL (DBG_FULL, "tcsConfigEnd: completed at ", tnow) ;

        break;

    default:
        break;

    }

    return status;

}


/*+
 *   Function name:
 *   tcsConfigBeginPreset
 *
 *   Purpose:
 *   Initialise a new TCS configuration.
 *
 *   Description:
 *   This routine will initialise a new TCS configuration. It does this
 *   by creating a copy of the current TCS configuration and clearing
 *   and initialising some flags.
 *
 *   Invocation:
 *   tcsConfigBeginPreset()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsConfigBeginPreset(void)
{
    static int first = TRUE;

    firstSeqCommMarked = FALSE;
    strcpy(firstSeqCommName, " ");
    strcpy(telnames, " ");
    tcsCadInfoClearMarks();

    tcsConfigInitTCB(CURRENT, &currentTCB);

/* Perform a one time initialisation of the kernelTCB the first time this
   *  routine is called. Do this by filling it in as if it were the 
   *  currentTCB. This will initialise it with the startup data of the
   *  astrometric kernel.
   *  Set the clipAtLimit flags to TRUE.
 */

    if (first) {
        first = FALSE;
        tcsConfigInitTCB(CURRENT, &kernelTCB);
        currentTCB.sysconfig.clipAtLimit.val = 1;
        presetTCB.sysconfig.clipAtLimit.val = 1;
        kernelTCB.sysconfig.clipAtLimit.val = 1;
    }

    tcsConfigInitTCB(PRESET, &presetTCB);
}

/*+
 *   Function name:
 *   tcsConfigBeginStart
 *
 *   Purpose:
 *   Perform any actions needed prior to issuing start to commands.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsConfigBeginStart()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsConfigBeginStart(void)
{
}


/*+
 *   Function name:
 *   tcsConfigEndPreset
 *
 *   Purpose:
 *   Check a TCS configuration.
 * 
 *   Description:
 *   Once all the presets have been issued to a set of commands, a 
 *   Telescope Control Block (TCB) will have been built that contains
 *   all the data that the user wishes to apply to the telescope. It
 *   is the purpose of this routine to check that the TCB is valid.
 *   If a new target has been set for any for the virtual telescopes
 *   then a full recalculation of the OTMs is requested immediately. For any
 *   other input the data is passed directly into the kernel and the
 *   OTMs are recalculated on the next reschedule. 
 *
 *   Invocation:
 *   status = tcsConfigEndPreset(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (cadRecord *) Pointer to cad record
 *
 *   Function value:
 *   (<)  status  (long)   Return status, 0 = OK
 * 
 *   External functions:
 *   slaDfltin      (slalib)          Decode string to double 
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   1. Needs to distinguish between PRESET and CURRENT configurations
 *-
 */

long tcsConfigEndPreset( cadRecord *pcad )
{

    long status;                /* Return status from function */
    struct TCB *pTCB;           /* Pointer to TCB structure */
    double elLimit;             /* Elevation limit (rads) */
    double timeToRise;          /* Time until source rises */
    int nstrt;                  /* Pointer for slalib call */
    int istat;                  /* Temporary status variable */
    int i, j, k ;               /* Loop index */
    TELESCOPE tel;              /* Virtual telescope */
    struct TELP telParams;      /* Telescope parameters */
    double aoprms[15];          /* Apparent to observed array */
    struct PMPXRV pm;           /* Proper motion structure */
    struct PMPXRV pm0;          /* Zero proper motion structure */
    struct EPOCH epochref;      /* Epoch at  reference time */
    struct EPOCH epoch0;        /* Epoch at t0 */
    double ttref;               /* TT at reference time */
    double utcref ;             /* UTC at reference time */
    double tdbref;              /* TDB at reference time */
    double refa, refb;          /* Refraction constants */
    double mtheta[2];           /* Estimated mount theta */
    double rtheta[2];           /* Estimated mount theta in rotator frame */
    double gtheta[2];           /* Estimated guide theta */
    double stheta[3][2];        /* Source thetas */
    double x, y, z;             /* Cartesian coordinates */
    double xu, yu, zu;          /* Cartesian coordinates */
    double xp, yp;              /* Pointing origin */
    double xpu, ypu;            /* Pointing origin */
    double w;                   /* Weight */
    double dt;                  /* Time difference */
    int src;                    /* source (A,B or C) */
    double ob[2];               /* Offsets from base */
    struct WCS_CTX ctx;         /* WCS context */
    struct WCS wcs;             /* WCS transformation */
    double az, el;              /* Esimated mount az/el */
    int limError;               /* Limit error code */
    double time;                /* Time from WCS */
    int probe;                  /* Guide probe number */
    int ichop;                  /* Chop state */
    int inod ;                  /* Nod state */
    double xmin, xmax;          /* Guide probe limits */
    double ymin, ymax;          /* Guide probe limits */
    double zmin, zmax;          /* Guide probe limits */
    double rmin, rmax;          /* Guide probe limits */
    double radval;              /* Probe radius */
    double r;
    LIMITTYPE limitType;
    double sinb, cosb;
    double theta1;              /* Scratch theta1 */
    double theta2;              /* Scratch theta2 */
    double theta01, theta02 ;   /* Base positions */
    double diam;                /* Planet diameter (not used) */
    double tlong;               /* Observatory true longitude */
    double tlat;                /* Observatory true latitude */
    double hm;                  /* Observatory height */
    int gsaoiport;              /* GSAOI port number */
    int probeIndex ;            /* Index for probe limits */
    int telIndex ;              /* Index for tnames */
    double ox, oy ;             /* probe demands in oiwfs frame */
    char* tnames[] = { "Mount", "Source A", "Source B", "Source C",
                          "PWFS 1", "PWFS 2", "OIWFS", "Altair", "G1", 
                          "G2", "G3", "G4"};
    char* targetCads[] = {"mount", "sourceA", "sourceB", "sourceC",
                          "pwfs1", "pwfs2", "oiwfs", "g1", "g2", "g3", "g4"};
    char* planetCads[] = {"mountplanet", "planet", "sourceBplanet", 
                          "sourceCplanet", "pwfs1planet", "pwfs2planet",
                          "oiwfsplanet", "g1planet", "g2planet", "g3planet",
                          "g4planet"};
    char* orbitCads[]  = {"mountorbit", "orbit", "sourceBorbit", 
                          "sourceCorbit", "pwfs1orbit", "pwfs2orbit",
                          "oiwfsorbit", "g1orbit", "g2orbit", "g3orbit", 
                          "g4orbit"};
    char* difTrCads[]  = {"difTrMount", "difTrSourceA", "difTrSourceB", 
                          "difTrSourceC", "difTrPwfs1", "difTrPwfs2",
                          "difTrOiwfs", "difTrG1", "difTrG2", "difTrG3",
                          "difTrG4"};
    struct GUIDE guide ;        /* Current guide configuration */
    int nodchopset ;            /* Flag for nod/chop parameters */
    char hlth[8] ;              /* Ephemeris health */
    char mess[80] ;             /* Message */
    double dra1, dra2 ;         /* RA track rates from ephemeris */
    double ddec1, ddec2 ;       /* Dec track rates from ephemeris */
    char tbuff[80];             /* Temporary buffer for string data */
    int odgwguiding[4] ;        /* Guiding flags for ODGW */
    double xorig = 0.0, yorig = 0.0;  /* Original values of x, y for diagnostics */
    int p1LGSMode ;             /* Bypass some checks if set to 1 */
    int configuredForAO ;       /* Set if Altair is in use */

    status = CAD_ACCEPT;

    if (activeTCB == CURRENT) {
        pTCB = &currentTCB;
    } else {
        pTCB = &presetTCB;
    }

/* If there is nothing to check just return */

    if (pTCB->sysconfig.needsCheck == FALSE)
        return status;

/* Get the P1 + LGS mode */
    p1LGSMode = pTCB->sysconfig.p1LGSMode.val ;

/* Get the AO configuration */
   configuredForAO = pTCB->sysconfig.AOconfig.val ;

/* Get the reference time as TT and UTC and epoch */
    timeThenD(pTCB->sysconfig.reftime, TT, &ttref);
    timeThenD(pTCB->sysconfig.reftime, UTC, &utcref);
    epochref.year = slaEpj( ttref );
    epochref.type = 'J';

/* Get observatory position */
    tcsGetObs( &tlong, &tlat, &hm);

/* Set chop mode to relative if the slew reset flag is set or chopRelative 
   is marked and set the throws to zero if chopRelative isn't marked. */
    if (pTCB->slew.chop.val || tcsCadInfoIsMarked("chopRelative")) {
        pTCB->chop[0].mode.val = 1;
        pTCB->chop[1].mode.val = 1;
        if ( ! tcsCadInfoIsMarked("chopRelative") ) {
           pTCB->chop[0].throw.val = 0.0;
           pTCB->chop[1].throw.val = 0.0;
        }
    }

/* If the slewing flags are set and the corresponding CADs aren't marked
   set the source, mount, guide and pointing origin offsets and differential 
   track rates to zero */
    if ( pTCB->slew.soff.val ) {
       if ( !tcsCadInfoIsMarked("offsetSourceA") ) {
           pTCB->ob[0][SOURCE_A].dtheta1.val = 0.0;
           pTCB->ob[0][SOURCE_A].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceA1") ) {
           pTCB->ob[1][SOURCE_A].dtheta1.val = 0.0;
           pTCB->ob[1][SOURCE_A].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceA2") ) {
           pTCB->ob[2][SOURCE_A].dtheta1.val = 0.0;
           pTCB->ob[2][SOURCE_A].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceB") ) {
           pTCB->ob[0][SOURCE_B].dtheta1.val = 0.0;
           pTCB->ob[0][SOURCE_B].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceB1") ) {
           pTCB->ob[1][SOURCE_B].dtheta1.val = 0.0;
           pTCB->ob[1][SOURCE_B].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceB2") ) {
           pTCB->ob[2][SOURCE_B].dtheta1.val = 0.0;
           pTCB->ob[2][SOURCE_B].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceC") ) {
           pTCB->ob[0][SOURCE_C].dtheta1.val = 0.0;
           pTCB->ob[0][SOURCE_C].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceC1") ) {
           pTCB->ob[1][SOURCE_C].dtheta1.val = 0.0;
           pTCB->ob[1][SOURCE_C].dtheta2.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetSourceC2") ) {
           pTCB->ob[2][SOURCE_C].dtheta1.val = 0.0;
           pTCB->ob[2][SOURCE_C].dtheta2.val = 0.0;
       }
    }
    if ( pTCB->slew.pooff.val ) {
       if ( !tcsCadInfoIsMarked("offsetPoA") ) {
           pTCB->porob[0][MOUNT].x.val = 0.0;
           pTCB->porob[0][MOUNT].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoA") ) {
           pTCB->porob[0][SOURCE_A].x.val = 0.0;
           pTCB->porob[0][SOURCE_A].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoA1") ) {
           pTCB->porob[1][SOURCE_A].x.val = 0.0;
           pTCB->porob[1][SOURCE_A].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoA2") ) {
           pTCB->porob[2][SOURCE_A].x.val = 0.0;
           pTCB->porob[2][SOURCE_A].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoB") ) {
           pTCB->porob[0][SOURCE_B].x.val = 0.0;
           pTCB->porob[0][SOURCE_B].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoB1") ) {
           pTCB->porob[1][SOURCE_B].x.val = 0.0;
           pTCB->porob[1][SOURCE_B].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoB2") ) {
           pTCB->porob[2][SOURCE_B].x.val = 0.0;
           pTCB->porob[2][SOURCE_B].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoC") ) {
           pTCB->porob[0][SOURCE_C].x.val = 0.0;
           pTCB->porob[0][SOURCE_C].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoC1") ) {
           pTCB->porob[1][SOURCE_C].x.val = 0.0;
           pTCB->porob[1][SOURCE_C].y.val = 0.0;
       }
       if ( !tcsCadInfoIsMarked("offsetPoC2") ) {
           pTCB->porob[2][SOURCE_C].x.val = 0.0;
           pTCB->porob[2][SOURCE_C].y.val = 0.0;
       }
    }
    if ( pTCB->slew.sdt.val ) {
       if ( !tcsCadInfoIsMarked("difTrSourceA") ) {
          pTCB->difftrack[SOURCE_A].dtheta1.val = 0.0;
          pTCB->difftrack[SOURCE_A].dtheta2.val = 0.0;
          pTCB->difftrack[SOURCE_A].frame.val = pTCB->target[SOURCE_A].frame.val;
          pTCB->difftrack[SOURCE_A].eqx.val = pTCB->target[SOURCE_A].eqx.val;
          pTCB->difftrack[SOURCE_A].eqx.val = pTCB->target[SOURCE_A].eqx.val;
          pTCB->difftrack[SOURCE_A].t0.val = ttref;
       }
       if ( !tcsCadInfoIsMarked("difTrSourceB") ) {
          pTCB->difftrack[SOURCE_B].dtheta1.val = 0.0;
          pTCB->difftrack[SOURCE_B].dtheta2.val = 0.0;
          pTCB->difftrack[SOURCE_B].frame.val = pTCB->target[SOURCE_B].frame.val;
          pTCB->difftrack[SOURCE_B].eqx.val = pTCB->target[SOURCE_B].eqx.val;
          pTCB->difftrack[SOURCE_B].eqx.val = pTCB->target[SOURCE_B].eqx.val;
          pTCB->difftrack[SOURCE_B].t0.val = ttref;
       }
       if ( !tcsCadInfoIsMarked("difTrSourceC") ) {
          pTCB->difftrack[SOURCE_C].dtheta1.val = 0.0;
          pTCB->difftrack[SOURCE_C].dtheta2.val = 0.0;
          pTCB->difftrack[SOURCE_C].frame.val = pTCB->target[SOURCE_C].frame.val;
          pTCB->difftrack[SOURCE_C].eqx.val = pTCB->target[SOURCE_C].eqx.val;
          pTCB->difftrack[SOURCE_C].eqx.val = pTCB->target[SOURCE_C].eqx.val;
          pTCB->difftrack[SOURCE_C].t0.val = ttref;
       }
    }
    if ( pTCB->slew.moff.val && !tcsCadInfoIsMarked("offsetMount") ) {
       pTCB->ob[0][MOUNT].dtheta1.val = 0.0;
       pTCB->ob[0][MOUNT].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.mdt.val && !tcsCadInfoIsMarked("difTrMount") ) {
       pTCB->difftrack[MOUNT].dtheta1.val = 0.0;
       pTCB->difftrack[MOUNT].dtheta2.val = 0.0;
       pTCB->difftrack[MOUNT].frame.val = pTCB->target[MOUNT].frame.val;
       pTCB->difftrack[MOUNT].eqx.val = pTCB->target[MOUNT].eqx.val;
       pTCB->difftrack[MOUNT].eqx.val = pTCB->target[MOUNT].eqx.val;
       pTCB->difftrack[MOUNT].t0.val = ttref;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs1A") ) {
       pTCB->ob[0][PWFS1].dtheta1.val = 0.0;
       pTCB->ob[0][PWFS1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs1B") ) {
       pTCB->ob[1][PWFS1].dtheta1.val = 0.0;
       pTCB->ob[1][PWFS1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs1C") ) {
       pTCB->ob[2][PWFS1].dtheta1.val = 0.0;
       pTCB->ob[2][PWFS1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs2A") ) {
       pTCB->ob[0][PWFS2].dtheta1.val = 0.0;
       pTCB->ob[0][PWFS2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs2B") ) {
       pTCB->ob[1][PWFS2].dtheta1.val = 0.0;
       pTCB->ob[1][PWFS2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetPwfs2C") ) {
       pTCB->ob[2][PWFS2].dtheta1.val = 0.0;
       pTCB->ob[2][PWFS2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetOiwfsA") ) {
       pTCB->ob[0][OIWFS].dtheta1.val = 0.0;
       pTCB->ob[0][OIWFS].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetOiwfsB") ) {
       pTCB->ob[1][OIWFS].dtheta1.val = 0.0;
       pTCB->ob[1][OIWFS].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetOiwfsC") ) {
       pTCB->ob[2][OIWFS].dtheta1.val = 0.0;
       pTCB->ob[2][OIWFS].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG1A") ) {
       pTCB->ob[0][G1].dtheta1.val = 0.0;
       pTCB->ob[0][G1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG1B") ) {
       pTCB->ob[1][G1].dtheta1.val = 0.0;
       pTCB->ob[1][G1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG1C") ) {
       pTCB->ob[2][G1].dtheta1.val = 0.0;
       pTCB->ob[2][G1].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG2A") ) {
       pTCB->ob[0][G2].dtheta1.val = 0.0;
       pTCB->ob[0][G2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG2B") ) {
       pTCB->ob[1][G2].dtheta1.val = 0.0;
       pTCB->ob[1][G2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG2C") ) {
       pTCB->ob[2][G2].dtheta1.val = 0.0;
       pTCB->ob[2][G2].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG3A") ) {
       pTCB->ob[0][G3].dtheta1.val = 0.0;
       pTCB->ob[0][G3].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG3B") ) {
       pTCB->ob[1][G3].dtheta1.val = 0.0;
       pTCB->ob[1][G3].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG3C") ) {
       pTCB->ob[2][G3].dtheta1.val = 0.0;
       pTCB->ob[2][G3].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG4A") ) {
       pTCB->ob[0][G4].dtheta1.val = 0.0;
       pTCB->ob[0][G4].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG4B") ) {
       pTCB->ob[1][G4].dtheta1.val = 0.0;
       pTCB->ob[1][G4].dtheta2.val = 0.0;
    }
    if ( pTCB->slew.goff.val && !tcsCadInfoIsMarked("offsetG4C") ) {
       pTCB->ob[2][G4].dtheta1.val = 0.0;
       pTCB->ob[2][G4].dtheta2.val = 0.0;
    }

/* If the filter CADs are not marked then set the filter short circuit
   to "closed" if the corresponding slew flag is set. */
    if ( !tcsCadInfoIsMarked("filter1") ) {
       if ( pTCB->slew.sc1.val ) {
          pTCB->tf1.sc.val = 1;
       }
    }
    if ( !tcsCadInfoIsMarked("filter2") ) {
       if ( pTCB->slew.sc2.val ) {
          pTCB->pf2.sc.val = 1;
       }
    }

/* if the slew CAD is marked then, if the filter short circuit flag is set 
   to "open", then the flag is set to "one shot for this configuration only" 
   so that the system slews briskly but the filters settings are restored
   once the slew has started. Also, if the configuration contains BOTH a
   science target and an Altair target then set to one shot. We
   only want to filter if just the target is changed */
    if ( pTCB->tf1.sc.val == 0 && tcsCadInfoIsMarked("slew") ) {
       pTCB->tf1.sc.val = 3;
    }
    if ( pTCB->pf2.sc.val == 0 && tcsCadInfoIsMarked("slew") ) {
       pTCB->pf2.sc.val = 3;
    }
    if ( pTCB->tf1.sc.val == 0 && 
         tcsCadInfoIsMarked("sourceA") && tcsCadInfoIsMarked("pwfs2")) {
       pTCB->tf1.sc.val = 3;
       if ( pTCB->pf2.sc.val == 0) pTCB->pf2.sc.val = 3;
    }

/* Now loop through each virtual telescope to set up and verify that the
*  target from the planet, orbit or source commands is set up correctly.
*  Originally this code only applied to sourceA but was subsequently
*  extended to handle an ephemeris specification for the guide targets
*  and subsequently orbits and planets as well. Currently the mount,
*  sourceB and sourceC telescopes don't support independent specifications
*  of orbit, planet or ephemerides.
*/
   for (tel = MOUNT; tel <= G4; tel++) {
    
     if (tel !=MOUNT || tel != SOURCE_B || tel != SOURCE_C) {

/* If source has been marked then check if the target has been
*  specified via an ephemeris and then set the planet to none */
      if (tcsCadInfoIsMarked(targetCads[tel])) {
        if (pTCB->target[tel].ephemeris) {
          pTCB->planet[tel].code.val = EPHEMERIS;
          pTCB->planet[tel].override_rates = TRUE;
        } else {
          pTCB->planet[tel].code.val = NO_PLANET;
        }

/* Check that source hasn't been mixed with planet or orbit */
        if (tcsCadInfoIsMarked(planetCads[tel])) {
            status = CAD_REJECT;
            sprintf(mess,"%s & %s specified", planetCads[tel], targetCads[tel]);
            tcsCsSetMessage(pcad, mess);
            return status ;
        }
        if (tcsCadInfoIsMarked(orbitCads[tel])) {
            status = CAD_REJECT;
            sprintf(mess,"%s & %s specified", targetCads[tel], orbitCads[tel]);
            tcsCsSetMessage(pcad, mess);
            return status ;
        }
      } else if (tcsCadInfoIsMarked(planetCads[tel])) {

/* Else if planet is marked then check that orbit isn't as well */
        if (tcsCadInfoIsMarked(orbitCads[tel])) {
            status = CAD_REJECT;
            sprintf(mess,"%s & %s specified", planetCads[tel], orbitCads[tel]);
            tcsCsSetMessage(pcad, mess);
            return status ;
        }
        pTCB->planet[tel].override_rates = TRUE;
      } else if (tcsCadInfoIsMarked(orbitCads[tel])) {

/* Else if orbit is marked set the planet code to ORBIT */
        pTCB->planet[tel].code.val = ORBIT;
        pTCB->planet[tel].override_rates = TRUE;
      }

/* If Source differential tracking has been specified then set the 
   override rates flag to disable updating of the rates from the orbital
   elements */
      if (tcsCadInfoIsMarked(difTrCads[tel])) {
        if (!pTCB->target[tel].ephemeris) {
          pTCB->planet[tel].override_rates = FALSE;
        }
      }

/* If planet, orbit or ephemeris is set then generate source and, 
 * if the cad hasn't been marked, a differential track rate */
      if (pTCB->planet[tel].code.val == ORBIT) {
        slaPlante( ttref, tlong, tlat, pTCB->orbit[tel].jform.val,
           pTCB->orbit[tel].epoch.val, pTCB->orbit[tel].orbinc.val,
           pTCB->orbit[tel].anode.val, pTCB->orbit[tel].perih.val,
           pTCB->orbit[tel].aorq.val, pTCB->orbit[tel].e.val,
           pTCB->orbit[tel].aorl.val, pTCB->orbit[tel].dm.val,
           &pTCB->target[tel].theta1.val, 
           &pTCB->target[tel].theta2.val, &r, &istat);
        if (istat) {
            status = CAD_REJECT;
            strcpy (pcad->mess, "orbit does not compute");
            return status ;
        }
        pTCB->target[tel].frame.val = APPT;

        if (pTCB->planet[tel].override_rates) {
            dt = 1.0 / 24.0 / 60.0;
            slaPlante( ttref + dt, tlong, tlat, pTCB->orbit[SOURCE_A].jform.val,
              pTCB->orbit[tel].epoch.val, pTCB->orbit[tel].orbinc.val,
              pTCB->orbit[tel].anode.val, pTCB->orbit[tel].perih.val,
              pTCB->orbit[tel].aorq.val, pTCB->orbit[tel].e.val,
              pTCB->orbit[tel].aorl.val, pTCB->orbit[tel].dm.val,
              &theta1, &theta2, &r, &istat);
            if (istat) {
                status = CAD_REJECT;
                strcpy (pcad->mess, "orbit does not compute");
                return status ;
            }
            pTCB->difftrack[tel].frame.val = APPT;
            pTCB->difftrack[tel].t0.val = ttref;
            pTCB->difftrack[tel].dtheta1.val = 
                (theta1 - pTCB->target[tel].theta1.val) / dt;
            pTCB->difftrack[tel].dtheta2.val = 
                (theta2 - pTCB->target[tel].theta2.val) / dt;
        }

      } else if (pTCB->planet[tel].code.val == EPHEMERIS) {

/* Set up the differential track rates. 
 * The rates used here which will eventually get displayed are the raw values
 * from the ephemeris files. The previous method of getting the position
 * at two differnt times can lead to apparent jumps in the track rates 
 * when crossing data point boundaries. These apparent changes are due
 * solely to the precison with which the positions are tabulated. E.g
 * if the data is tabulated every minute then the derived track rates
 * are only accurate to 0.09"/hr in RA and 0.06"/hr in dec.
 * Note that the ephemeris table is in UTC. For consistency with the rest 
 * of the TCS it would have been better if this were TT but we have stuck 
 * with the JPL ephemeris choice.
 */
        if (pTCB->planet[tel].override_rates) {
            dt = 1.0 / 24.0 / 60.0;
            istat = tcsEphemerisTarget(utcref, tel, APPT, &theta01, 
                                       &theta02, &dra1, &ddec1, hlth, 
                                       pcad->mess);
            istat = tcsEphemerisTarget(utcref+dt, tel, APPT, &theta1, 
                                       &theta2, &dra2, &ddec2, hlth, 
                                       pcad->mess);
            pTCB->difftrack[tel].frame.val = APPT;
            pTCB->difftrack[tel].t0.val = ttref;
            pTCB->difftrack[tel].dtheta1.val = dra1;
            pTCB->difftrack[tel].dtheta2.val = ddec1;
        }
 
      } else if (pTCB->planet[tel].code.val != NO_PLANET) {
        timeThenD(pTCB->sysconfig.reftime, TDB, &tdbref);
        slaRdplan( tdbref, (int)pTCB->planet[tel].code.val, tlong, tlat, 
           &pTCB->target[tel].theta1.val, 
           &pTCB->target[tel].theta2.val, &diam);
        pTCB->target[tel].frame.val = APPT;

        if (pTCB->planet[tel].override_rates) {
            if (pTCB->planet[tel].code.val == MOON)
              dt = 1.0 / 24.0 / 60.0 / 6.0;
            else dt = 1.0 / 24.0 / 60.0;
            slaRdplan( tdbref + dt, (int)pTCB->planet[tel].code.val, 
               tlong, tlat, &theta1, &theta2, &diam);
            pTCB->difftrack[tel].frame.val = APPT;
            pTCB->difftrack[tel].t0.val = ttref;
            pTCB->difftrack[tel].dtheta1.val = 
                (theta1 - pTCB->target[tel].theta1.val) / dt;
            pTCB->difftrack[tel].dtheta2.val = 
                (theta2 - pTCB->target[tel].theta2.val) / dt;
        }
      }
    }
  }

/* If targets B or C have been set this implies absolute chopping.
 */
    if (tcsCadInfoIsMarked("sourceB")) pTCB->chop[0].mode.val = 0;
    if (tcsCadInfoIsMarked("sourceC")) pTCB->chop[1].mode.val = 0;

/* Check that relative chopping has not been mixed with absolute B or C 
   targets */
    if (tcsCadInfoIsMarked("chopRelative") && !pTCB->chop[0].mode.val) {
        status = CAD_REJECT;
        strcpy (pcad->mess, "Relative & absolute chopping specified");
        return status ;
    }


/* If slewing disable any guide stars not explicitly enabled as part of the
   configuration */
    if (pTCB->slew.guide.val) {
       if ( !tcsCadInfoIsMarked("configPwfs1") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[0].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configPwfs2") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[1].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configOiwfs") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[2].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configG1") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[3].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configG2") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[4].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configG3") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[5].act[i][j].val = 0;
          }
       }
       if ( !tcsCadInfoIsMarked("configG4") ) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[6].act[i][j].val = 0;
          }
       }
    }

/* Default to nod A / chop A if there is no nod/chop state set but a guide
*  target has been given. Note the exception however for Altair
*/
    if (tcsCadInfoIsMarked("pwfs1") && !tcsCadInfoIsMarked("configPwfs1")) {
      nodchopset = FALSE ;
      tcsGetGuide(0, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[0].act[0][0].val = 1;
    }

/* If the pwfs2 virtual telescope is currently in use for Altair and we
 * are in P1+LGS node then we don't set a default nod/chop state. 
*/
    if (tcsCadInfoIsMarked("pwfs2") && !tcsCadInfoIsMarked("configPwfs2")) {
      nodchopset = FALSE ;
      tcsGetGuide(1, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[1].act[0][0].val = 1;

    }

/* Reject if nod/chop state is part of config and trying to turn the 
 * state to on and we're configured for AO and in P1 + LGS mode
 */
    if (tcsCadInfoIsMarked("configPwfs2") && configuredForAO && p1LGSMode) {
      nodchopset = FALSE ;
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (pTCB->guide[1].act[inod][ichop].val) 
            nodchopset = TRUE;
        }
      }
      if (nodchopset) {
        status = CAD_REJECT ;
        strncpy(pcad->mess, "Can not set nod/chop in P1+LGS mode", 
                MAX_STRING_SIZE);
        return status ;
      }
    }

/* Explicitly disable nod/chop states for Altair if the aoLgsttfSource
   command is part of the configuration and is set on. Note that
   if we are not configured for AO by this time then we effectively
   turn off the nod/chop states for PWFS2 but presumeably if
   we set aoLgsp1Source then we will configure for AO later
*/
    if (tcsCadInfoIsMarked("aoLgsttfSource") && p1LGSMode) {
        for (inod = 0; inod < 3; inod++) {
          for (ichop = 0; ichop < 3; ichop++) {
            pTCB->guide[1].act[inod][ichop].val = 0;
          } 
        }
    }

/* Make sure all the nod/chop flags are off if using Altair in P1+LGS mode*/
    if (configuredForAO && p1LGSMode) {
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          pTCB->guide[1].act[inod][ichop].val = 0;
        } 
      }
    } 

    if (tcsCadInfoIsMarked("oiwfs") && !tcsCadInfoIsMarked("configOiwfs")) {
      nodchopset = FALSE ;
      tcsGetGuide(2, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[2].act[0][0].val = 1;
    }

    if (tcsCadInfoIsMarked("g1") && !tcsCadInfoIsMarked("configG1")) {
      nodchopset = FALSE ;
      tcsGetGuide(3, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[3].act[0][0].val = 1;
    } 

    if (tcsCadInfoIsMarked("g2") && !tcsCadInfoIsMarked("configG2")) {
      nodchopset = FALSE ;
      tcsGetGuide(4, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[4].act[0][0].val = 1;
    }

    if (tcsCadInfoIsMarked("g3") && !tcsCadInfoIsMarked("configG3")) {
      nodchopset = FALSE ;
      tcsGetGuide(5, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[5].act[0][0].val = 1;
    }

    if (tcsCadInfoIsMarked("g4") && !tcsCadInfoIsMarked("configG4")) {
      nodchopset = FALSE ;
      tcsGetGuide(6, &guide);
      for (inod = 0; inod < 3; inod++) {
        for (ichop = 0; ichop < 3; ichop++) {
          if (guide.act[inod][ichop].val)
            nodchopset = TRUE;
        }
      }
      if (!nodchopset)
        pTCB->guide[6].act[0][0].val = 1;
    } 

/* If guiderConfig is marked then we need to check which of the
 * generic guiders is actually being used. 
 */
   if (tcsCadInfoIsMarked("guiderConfig") && !tcsCadInfoIsMarked("configG1")) {
     probeIndex = pTCB->vgconfig[0].destination;
     if (probeIndex == 0) {
       for ( i = 0; i < 3; i++) {
         for ( j = 0; j < 3; j++) pTCB->guide[3].act[i][j].val = 0;
       }
     } else {
       nodchopset = FALSE ;
       tcsGetGuide(3, &guide);
       for (inod = 0; inod < 3; inod++) {
         for (ichop = 0; ichop < 3; ichop++) {
           if (guide.act[inod][ichop].val)
             nodchopset = TRUE;
         }
       }
       if (!nodchopset)
         pTCB->guide[3].act[0][0].val = 1;
     }
   }

   if (tcsCadInfoIsMarked("guiderConfig") && !tcsCadInfoIsMarked("configG2")) {
     probeIndex = pTCB->vgconfig[1].destination;
     if (probeIndex == 0) {
       for ( i = 0; i < 3; i++) {
         for ( j = 0; j < 3; j++) pTCB->guide[4].act[i][j].val = 0;
       }
     } else {
       nodchopset = FALSE ;
       tcsGetGuide(4, &guide);
       for (inod = 0; inod < 3; inod++) {
         for (ichop = 0; ichop < 3; ichop++) {
           if (guide.act[inod][ichop].val)
             nodchopset = TRUE;
         }
       }
       if (!nodchopset)
         pTCB->guide[4].act[0][0].val = 1;
     }
   }

   if (tcsCadInfoIsMarked("guiderConfig") && !tcsCadInfoIsMarked("configG3")) {
     probeIndex = pTCB->vgconfig[2].destination;
     if (probeIndex == 0) {
       for ( i = 0; i < 3; i++) {
         for ( j = 0; j < 3; j++) pTCB->guide[5].act[i][j].val = 0;
       }
     } else {
       nodchopset = FALSE ;
       tcsGetGuide(5, &guide);
       for (inod = 0; inod < 3; inod++) {
         for (ichop = 0; ichop < 3; ichop++) {
           if (guide.act[inod][ichop].val)
             nodchopset = TRUE;
         }
       }
       if (!nodchopset)
         pTCB->guide[5].act[0][0].val = 1;
     }
   }

   if (tcsCadInfoIsMarked("guiderConfig") && !tcsCadInfoIsMarked("configG4")) {
     probeIndex = pTCB->vgconfig[3].destination;
     if (probeIndex == 0) {
       for ( i = 0; i < 3; i++) {
         for ( j = 0; j < 3; j++) pTCB->guide[6].act[i][j].val = 0;
       }
     } else {
       nodchopset = FALSE ;
       tcsGetGuide(6, &guide);
       for (inod = 0; inod < 3; inod++) {
         for (ichop = 0; ichop < 3; ichop++) {
           if (guide.act[inod][ichop].val)
             nodchopset = TRUE;
         }
       }
       if (!nodchopset)
         pTCB->guide[6].act[0][0].val = 1;
     }
   }

   if (tcsCadInfoIsMarked("guiderConfig")) {
     for (k = 0; k < 4; k++) {
       probeIndex = pTCB->vgconfig[k].destination;
       if (probeIndex == 0) {
          for ( i = 0; i < 3; i++) {
             for ( j = 0; j < 3; j++) pTCB->guide[k+3].act[i][j].val = 0;
          }
       }
     }
   }
/* Update the position and rates in the tracking frame */

/* Zero proper motion structure */
    pm0.pm = 0;
    pm0.pmRA = 0.0;
    pm0.pmDec = 0.0;
    pm0.px = 0.0;
    pm0.rv = 0.0;

/* Fill in a telescope structure */
    tcsGetTelParams(MOUNT, &telParams);

/* Apparent to observed place array */
    tcsGetAoprms( aoprms);
    timeThenR(pTCB->sysconfig.reftime, LAST, &aoprms[13]);

/* Save refraction constants at reference wavelength */
    refa = aoprms[10];
    refb = aoprms[11];

    for ( tel = MOUNT; tel <= G4; tel++ ) {

/* Proper motion structure */
        pm.pm = pTCB->target[tel].pm;
        pm.pmRA = pTCB->target[tel].pmRA.val;
        pm.pmDec = pTCB->target[tel].pmDec.val;
        pm.px = pTCB->target[tel].parallax.val;
        pm.rv = pTCB->target[tel].rv.val;

/* Target to differential tracking frame at t0 of rates */
        astCoco( pTCB->target[tel].theta1.val, pTCB->target[tel].theta2.val,
             pm, pTCB->target[tel].frame.val, pTCB->target[tel].eqx.val,
             pTCB->target[tel].epoch.val, pTCB->difftrack[tel].frame.val,
             pTCB->difftrack[tel].eqx.val, pTCB->difftrack[tel].t0.val, 
             aoprms, telParams, &theta1, &theta2);

/* If the differential rate frame is different from the tracking frame
   then adjust the position to the reference time */
        if ( pTCB->difftrack[tel].frame.val != pTCB->track[tel].frame.val ||
          pTCB->difftrack[tel].eqx.val.year != pTCB->track[tel].eqx.val.year ||
          pTCB->difftrack[tel].eqx.val.type != pTCB->track[tel].eqx.val.type) {
            dt = ttref - pTCB->difftrack[tel].t0.val;
            theta1 += pTCB->difftrack[tel].dtheta1.val * dt;
            theta2 += pTCB->difftrack[tel].dtheta2.val * dt;
            pTCB->difftrack[tel].t0.val = ttref;
        }

/* Epoch at t0 */
        epoch0.year = slaEpj( pTCB->difftrack[tel].t0.val );
        epoch0.type = 'J';

/* Position and rate to tracking frame at reference epoch */
        astCocoR(theta1, theta2, pm0, 
             pTCB->difftrack[tel].dtheta1.val/86400.0,
             pTCB->difftrack[tel].dtheta2.val/86400.0,
             pTCB->difftrack[tel].frame.val, pTCB->difftrack[tel].eqx.val, 
             epoch0, 
             pTCB->track[tel].frame.val, pTCB->track[tel].eqx.val, 
             ttref, aoprms, telParams,
             &pTCB->track[tel].theta1, &pTCB->track[tel].theta2, 
             &pTCB->track[tel].dtheta1, &pTCB->track[tel].dtheta2);

/* Convert track rates from radians per second to radians per day */
             pTCB->track[tel].dtheta1 *= 86400.0;
             pTCB->track[tel].dtheta2 *= 86400.0;

/* Zero time for rates in tracking frame */
             pTCB->track[tel].t0 = pTCB->difftrack[tel].t0.val;
    }

/* Epoch at reference time  */
    epoch0.year = slaEpj( ttref );
    epoch0.type = 'J';

/* Get net source targets */
    for (src = 0; src < 3; src++) {

/* Virtual telescope for this source */
        switch (src) {
        case 0:
           tel = SOURCE_A;
           break;
        case 1:
           tel = SOURCE_B;
           break;
        case 2:
           tel = SOURCE_C;
           break;
        }

        if ( src != 0 && pTCB->chop[src-1].mode.val == 1) {

/* Relative chopping so target is derived from source A and the chop
   throw */

/* Source A to frame of throw */
            astCoco(stheta[0][0], stheta[0][1], pm0, 
                pTCB->track[SOURCE_A].frame.val, 
                pTCB->track[SOURCE_A].eqx.val, 
                epoch0, 
                pTCB->chop[src-1].frame.val, pTCB->chop[src-1].eqx.val, 
                ttref, aoprms, telParams,
                &theta1, &theta2);

/* Apply throw */
                r = tan(pTCB->chop[src-1].throw.val);
                slaDtp2s(r*sin(pTCB->chop[src-1].pa.val),
                    r*cos(pTCB->chop[src-1].pa.val), theta1, theta2,
                    &theta1, &theta2);

/* To source tracking frame */
            astCoco(theta1, theta2, pm0,
                pTCB->chop[src-1].frame.val, pTCB->chop[src-1].eqx.val, 
                epoch0, 
                pTCB->track[tel].frame.val, pTCB->track[tel].eqx.val, 
                ttref, aoprms, telParams,
                &stheta[src][0], &stheta[src][1]);

        } else {

/* Source position at reference time */
            dt = ttref - pTCB->track[tel].t0;
            stheta[src][0] = pTCB->track[tel].theta1 +
                pTCB->track[tel].dtheta1 * dt;
            stheta[src][1] = pTCB->track[tel].theta2 +
                pTCB->track[tel].dtheta2 * dt;
        }

/* Add the offsets from base */
        for ( i = 0; i < 3; i++ ) {
            tcsCtOffToSph( pTCB->track[tel].frame.val, stheta[src],
                pTCB->ob[i][tel].coord.val, pTCB->ob[i][tel].dtheta1.val,
                pTCB->ob[i][tel].dtheta2.val, ob);
            stheta[src][0] += ob[0];
            stheta[src][1] += ob[1];
        }
    }

/* For the remaining configuration checks we need an estimate of where 
   the mount is going to be and what the mount pointing origin is which 
   depend on the filter 2 settings. */

/* By default use the mount target and pointing origin */
    mtheta[0] = pTCB->track[MOUNT].theta1;
    mtheta[1] = pTCB->track[MOUNT].theta2;
    xp = pTCB->por[MOUNT].x.val;
    yp = pTCB->por[MOUNT].y.val;

/* If the short circuit flag is set and the weights are non-zero or the
   short circuit filter 2 flag is set in the slew parameters then 
   assume that the filter is short circuit */

    if ((pTCB->pf2.sc.val && ( pTCB->pf2.weightA.val + pTCB->pf2.weightB.val +
        pTCB->pf2.weightC.val != 0.0)) || pTCB->slew.sc2.val ) {

/* Transform each source target to XYZ in the mount tracking frame and take
   the weighted average */
        x = y = z = 0.0;
        xp = yp = 0.0;

        for (src = 0; src < 3; src++) {

/* Virtual telescope for this source */
            switch (src) {
            case 0:
               tel = SOURCE_A;
               break;
            case 1:
               tel = SOURCE_B;
               break;
            case 2:
               tel = SOURCE_C;
               break;
            }

/* Source to mount tracking frame */
            astCoco(stheta[src][0], stheta[src][1], pm0, 
                pTCB->track[tel].frame.val, pTCB->track[tel].eqx.val, 
                epoch0, 
                pTCB->track[MOUNT].frame.val, pTCB->track[MOUNT].eqx.val, 
                ttref, aoprms, telParams, &theta1, &theta2);

/* To cartesian */
            cosb = cos(theta2);
            xu = cos(theta1) * cosb;
            yu = sin(theta1) * cosb;
            zu = sin(theta2);
            if (pTCB->track[MOUNT].frame.val == AZEL_TOPO) xu = -xu;

/* Net pointing origin for this virtual telescope */
            xpu = pTCB->por[tel].x.val;
            ypu = pTCB->por[tel].y.val;
            for ( i = 0; i < 3; i++) {
               xpu += pTCB->porob[i][tel].x.val;
               ypu += pTCB->porob[i][tel].y.val;
            }

/* Normalised input vector */
            switch (src) {
            case 0:
                x += pTCB->pf2.weightA.val * xu;
                y += pTCB->pf2.weightA.val * yu;
                z += pTCB->pf2.weightA.val * zu;
                xp += pTCB->pf2.weightA.val * xpu;
                yp += pTCB->pf2.weightA.val * ypu;
                break;
            case 1:
                x += pTCB->pf2.weightB.val * xu;
                y += pTCB->pf2.weightB.val * yu;
                z += pTCB->pf2.weightB.val * zu;
                xp += pTCB->pf2.weightB.val * xpu;
                yp += pTCB->pf2.weightB.val * ypu;
                break;
            case 2:
                x += pTCB->pf2.weightC.val * xu;
                y += pTCB->pf2.weightC.val * yu;
                z += pTCB->pf2.weightC.val * zu;
                xp += pTCB->pf2.weightC.val * xpu;
                yp += pTCB->pf2.weightC.val * ypu;
                break;
            }
        }

/* Form the normalised vector */
        w = x * x + y * y + z * z;
        if (w != 0.0) {
            w = sqrt ( w );
            x /= w;
            y /= w;
            z /= w;

/* Convert back to spherical */
            mtheta[0] = slaDranrm(atan2(y, 
                pTCB->track[MOUNT].frame.val == AZEL_TOPO ? -x : x )); 
            mtheta[1] = atan2 (z, sqrt( x * x + y * y ));
        }
    }

/* Apply mount differential tracking */
    dt = ttref - pTCB->track[MOUNT].t0;
    mtheta[0] += pTCB->track[MOUNT].dtheta1 * dt;
    mtheta[1] += pTCB->track[MOUNT].dtheta2 * dt;

/* Apply mount offsets from base */
    tcsCtOffToSph( pTCB->track[MOUNT].frame.val, mtheta, 
        pTCB->ob[0][MOUNT].coord.val, pTCB->ob[0][MOUNT].dtheta1.val,
        pTCB->ob[0][MOUNT].dtheta2.val, ob);
    mtheta[0] += ob[0];
    mtheta[1] += ob[1];

/* Apply mount pointing origin offsets */
    xp += pTCB->porob[0][MOUNT].x.val;
    yp += pTCB->porob[0][MOUNT].y.val;

/* Convert mount position to rotator tracking frame */
    astCoco(mtheta[0], mtheta[1], pm0, 
        pTCB->track[MOUNT].frame.val, pTCB->track[MOUNT].eqx.val, 
        epoch0, 
        pTCB->sysconfig.rot.frame.val, pTCB->sysconfig.rot.eqx.val, 
        ttref, aoprms, telParams, &rtheta[0], &rtheta[1]);

/* Get telescope context */
    astGetctx( &ctx );

/* Set tip/tilts to zero */
    for ( i = 0; i < 3; i++)
       for ( j = 0; j < 2; j++ ) ctx.m2xy[i][j] = 0.0;

/* Set time to reference time */
    ctx.time = pTCB->sysconfig.reftime;

/* Update pointing origin and refraction constants */
    telParams.pox = xp;
    telParams.poy = yp;
    slaAtmdsp(aoprms[5], aoprms[6], aoprms[7], aoprms[8], aoprms[10],
         aoprms[11], pTCB->wavel[MOUNT].wavel.val, aoprms + 10, aoprms + 11);

/* Predict rotator position angle */
    istat = astRot( pTCB->sysconfig.rot.frame.val, 
       pTCB->sysconfig.rot.eqx.val, rtheta[0], rtheta[1], ttref, aoprms,
       telParams, pTCB->sysconfig.rot.iaa.val,  pTCB->sysconfig.rot.ipa.val, 
       &telParams.rma);
    if (istat) telParams.rma = 0.0;

/* Predict mount Az/El */
    istat = astCoco( mtheta[0], mtheta[1], pm0, pTCB->track[MOUNT].frame.val,
        pTCB->track[MOUNT].eqx.val, epoch0, AZEL_MNT, epoch0, ttref, aoprms,
        telParams, &az, &el);
    if( istat ) {
        strcpy(pcad->mess, "Position inaccessible-too near zenith");
        return CAD_REJECT;
    }

/* Save az/el and modified telescope parameters in wcs context */
    ctx.ab0[0] = az;
    ctx.ab0[1] = el;
    ctx.tel = telParams;
    
/* Check estimate against the elevation limit if limit checking is enabled */
    nstrt = 1;
    slaDfltin(pcad->a, &nstrt, &elLimit, &istat);
    if (istat > 0) {
        strcpy(pcad->mess, "tcsConfigEndPreset: Bad elevation limit");
        return CAD_REJECT;
    }
    if ( el < elLimit && pTCB->sysconfig.clipAtLimit.val ) {
        limError = tcsLimits(pTCB->track[MOUNT].frame.val, elLimit, mtheta[0], 
            mtheta[1], tlat, aoprms[13], &timeToRise);
        tcsLimitDisplay(limError, elLimit, timeToRise, pcad->mess);
        return CAD_REJECT;
    }

/* Generate tip tilt values for each of the three source targets */
     for (src = 0; src < 3; src++) {

/* Virtual telescope for this source */
         switch (src) {
         case 0:
             tel = SOURCE_A;
             break;
         case 1:
             tel = SOURCE_B;
             break;
         case 2:
             tel = SOURCE_C;
             break;
         }

/* Convert WCS context to sky to x/y transformation */
         astCtx2tr( ctx, pTCB->track[tel].frame.val, 
             pTCB->track[tel].eqx.val, pTCB->wavel[tel].wavel.val, 
             src, &wcs, &time);
         astInvtr( wcs, &wcs);

/* Get x/y for source target */
         astS2xyq( stheta[src][0], stheta[src][1], wcs, &x, &y);

/* Adjust for pointing origin position */
         x -= pTCB->por[tel].x.val;
         y -= pTCB->por[tel].y.val;
         for ( i = 0; i < 3; i++) {
            x -= pTCB->porob[i][tel].x.val;
            y -= pTCB->porob[i][tel].y.val;
         }

/* Convert to tip/tilt in unrotated x/y and store in WCS context in radians */
         x /= telParams.fl;
         y /= telParams.fl;
         cosb = cos( - telParams.rma );
         sinb = sin( - telParams.rma );
         ctx.m2xy[src][0] = x * cosb - y * sinb;
         ctx.m2xy[src][1] = y * cosb + x * sinb;
    }

/* Check that tip/tilts are within allowed range */
    if (tcsConfigM2Scan (pTCB, &ctx, pcad->mess)) return CAD_REJECT;

/* For each active guide probe get the x/y position for the active chop
   states (the check is done for the telescope in the nod A position only */

    for (i = 0; i < 4; i++) {
      odgwguiding[i] = 0;
    }

    for ( probe = 0; probe < 7; probe++ ) {
       switch (probe) {
       case 0:
          tel = PWFS1;
          break;
       case 1:
          tel = PWFS2;
          break;
       case 2:
          tel = OIWFS;
          break;
       case 3:
          tel = G1;
          break;
       case 4:
          tel = G2;
          break;
       case 5:
          tel = G3;
          break;
       case 6:
          tel = G4;
          break;
       }
       for ( ichop = 0; ichop < 3; ichop ++ ) {
          if ( pTCB->guide[probe].act[0][ichop].val ||
               pTCB->guide[probe].act[1][ichop].val ||
               pTCB->guide[probe].act[2][ichop].val) {
             switch ( ichop ) {
             case 0:
                ctx.tel.pox = pTCB->por[SOURCE_A].x.val;
                ctx.tel.poy = pTCB->por[SOURCE_A].y.val;
                break;
             case 1:
                ctx.tel.pox = pTCB->por[SOURCE_B].x.val;
                ctx.tel.poy = pTCB->por[SOURCE_B].y.val;
                break;
             case 2:
                ctx.tel.pox = pTCB->por[SOURCE_C].x.val;
                ctx.tel.poy = pTCB->por[SOURCE_C].y.val;
                break;
             }

/* Convert WCS context to sky to x/y transformation */
             astCtx2tr( ctx, pTCB->track[tel].frame.val, 
                pTCB->track[tel].eqx.val, pTCB->wavel[tel].wavel.val, 
                ichop, &wcs, &time);
                astInvtr( wcs, &wcs);

/* Apply differential tracking */
             dt = ttref - pTCB->track[tel].t0;
             gtheta[0] = pTCB->track[tel].theta1 + pTCB->track[tel].dtheta1 *
                         dt;
             gtheta[1] = pTCB->track[tel].theta2 + pTCB->track[tel].dtheta2 *
                         dt;

/* Apply offsets from base */
             tcsCtOffToSph( pTCB->track[tel].frame.val, gtheta, 
                 pTCB->ob[ichop][tel].coord.val, 
                 pTCB->ob[ichop][tel].dtheta1.val,
                 pTCB->ob[ichop][tel].dtheta2.val, ob);
             gtheta[0] += ob[0];
             gtheta[1] += ob[1];

/* Get guide probe x/y */
             astS2xyq( gtheta[0], gtheta[1], wcs, &x, &y);

/* Check against limits. Must check whether P2 or Altair is in use */
             if (tel == PWFS2 && configuredForAO) {
               probeIndex = 3;
               telIndex = 7 ;
             } else {

/* For the generic guiders we need to look up where their output is going to
 * so we can extract the correct limits
 */
               telIndex = tel ;
               if (probe > 2) {
                 probeIndex = pTCB->vgconfig[probe-3].destination;
                 telIndex += 1;
                 if (probeIndex != 0) {
                   probeIndex += 3;
                 }
               } else {
                 probeIndex = probe ;
               }
             }
             if (probeIndex != 0) {
               tcsProbeGetLimits(probeIndex, &limitType, &xmin, &xmax,  
                  &ymin, &ymax, &zmin, &zmax, &rmin, &rmax);
               if ( limitType == XY ) {

/* For the OIWFS and ODGW the limits are in its frame of reference so we must 
*  transform the tcs demand to the same frame
*/
                  if (probeIndex ==2) {
                    xorig = x ;
                    yorig = y ;
                    tcsProbeTcs2Oiwfs(x, y, &ox, &oy) ;
                    x = ox ;
                    y = oy ;
                  } 
                  if (probeIndex > 6) {
                    gsaoiport = tcsGetGsaoiPort();
                    tcsProbeTcs2Odgw(gsaoiport, probeIndex - 7, x, y, &ox, &oy);
                    /*
                    printf("x,y %f %f, px, py %f %f\n", x, y, ox, oy);
                    */
                    x = ox ;
                    y = oy ; 
                  }
                  if ( x < xmin || x > xmax || y < ymin || y > ymax ) {
                     printf("Guide star out of range\n") ;
                     printf("Guide RA/Dec : %f %f\n", gtheta[0]*R2D/15.0, 
                           gtheta[1]*R2D);
                     printf("Probe index 2: x, y, ox, oy %f %f %f %f\n", 
                            xorig, yorig, ox, oy);
                     printf ("probeIndex = %d\n", probeIndex);
                     printf ("telIndex = %d\n", telIndex);
                     printf ("xmin etc %f %f %f %f\n", xmin, xmax, ymin, ymax);
                     sprintf(tbuff,"%6.1f, %6.1f", x, y);
                     tcsCsSetMessageN(pcad, tnames[telIndex], " => ", tbuff,
                                  " x/y exceeded", (char *)NULL);
                     /* We can't get to the target so for the generic guiders
                      * we reset the act flags to 0. 
                      */
                     if (probe > 2) {
                       for ( i = 0; i < 3; i++) {
                         for ( j = 0; j < 3; j++) {
                           pTCB->guide[probe].act[i][j].val = 0;
                         }
                       }
                     }
                     return CAD_REJECT;
                  } else {
/* For the ODGW we must store the demand positions ready to be sent with
 * the next dataODGW command to the GSAOI
 */
                     if (probeIndex > 6) {
                       tcsGuideSetODGWCenter(probeIndex - 7, x, y);
                       odgwguiding[probeIndex - 7] = 1;
                     }
                  }
               } else if ( limitType == RADIAL ) {
                  radval = sqrt ( x * x + y * y );
                  if (probeIndex > 3 && probeIndex < 7) {

/* Handle the AOM probes here. They are a combination of both radial and
 * XY limits.
 */
                    if (radval > rmax) {
                      strcpy(pcad->mess, "probe ");
                      strcat(pcad->mess, tnames[telIndex]);
                      strcat(pcad->mess, " r > rmax");
                      return CAD_REJECT;
                    }
                    if (probeIndex == 4 ) {         /* AOM TTG 1 */
                      if (x > xmax ) { 
                        strcpy(pcad->mess, "probe ");
                        strcat(pcad->mess, tnames[telIndex]);
                        strcat(pcad->mess, " x > xmax");
                        return CAD_REJECT;
                      }
                    }
                    if (probeIndex == 5 ) {         /* AOM TTG 2 */
                      if (x < xmin ) { 
                        strcpy(pcad->mess, "probe ");
                        strcat(pcad->mess, tnames[telIndex]);
                        strcat(pcad->mess, " x < xmin");
                        return CAD_REJECT;
                      }
                    }
                  } else {                    /* Handle other radial probes */
                    if ( radval > rmax || radval < rmin ) {
                      strcpy(pcad->mess, "probe ");
                      strcat(pcad->mess, tnames[telIndex]);
                      if (radval < rmin) {
                        strcat(pcad->mess, " r < rmin");
                      } else {
                        strcat(pcad->mess, " r > rmax");
                      }
                      return CAD_REJECT;
                   }
                 }
               }
             }
          }
       }
    }

/* Now set any ODGW guiding flags */
    for (i = 0; i < 4; i++) {
      tcsSetODGWGuiding(i, odgwguiding[i]);
    }


/* OTMs always recalculated if slewing or if any target or tracking 
   frame CAD has been marked */
    if (tcsCadInfoIsMarked("slew") || tcsCadInfoIsMarked("rotator") ||
        tcsCadInfoIsMarked("mount") || tcsCadInfoIsMarked("trackMount") ||
        tcsCadInfoIsMarked("sourceA") || tcsCadInfoIsMarked("trackSourceA") ||
        tcsCadInfoIsMarked("sourceB") || tcsCadInfoIsMarked("trackSourceB") ||
        tcsCadInfoIsMarked("sourceC") || tcsCadInfoIsMarked("trackSourceC") ||
        tcsCadInfoIsMarked("pwfs1") || tcsCadInfoIsMarked("trackPwfs1") ||
        tcsCadInfoIsMarked("pwfs2") || tcsCadInfoIsMarked("trackPwfs2") ||
        tcsCadInfoIsMarked("oiwfs") || tcsCadInfoIsMarked("trackOiwfs") ||
        tcsCadInfoIsMarked("g1")    || tcsCadInfoIsMarked("trackG1")    ||
        tcsCadInfoIsMarked("g2")    || tcsCadInfoIsMarked("trackG2")    ||
        tcsCadInfoIsMarked("g3")    || tcsCadInfoIsMarked("trackG3")    ||
        tcsCadInfoIsMarked("g4")    || tcsCadInfoIsMarked("trackG4")) 
        recalcOTMs = TRUE;

    return status;
}

/*+
 *   Function name:
 *   tcsConfigEndStart
 *
 *   Purpose:
 *   Perform any actions needed after issuing start to commands.
 *
 *   Description:
 *
 *   Invocation:
 *   tcsConfigEndStart()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsConfigEndStart(void)
{
}

/*+
 *   Function name:
 *   tcsConfigForceCheck
 *
 *   Purpose:
 *   Force a check on the current configuration
 *
 *   Description:
 *   This routine sets the needsCheck flag to true in the current 
 *   TCB. This was introduced as there are some commands that if set
 *   need to checked just to see if they are in conflict with other
 *   commands but there is no data that needs to be checked.
 *
 *   Invocation:
 *   tcsConfigForceCheck()
 *
 *-
 */

void tcsConfigForceCheck(void)
{
    struct TCB *pTCB;

    if (activeTCB == CURRENT)
        pTCB = &currentTCB;
    else
        pTCB = &presetTCB;

    pTCB->sysconfig.needsCheck = TRUE;

}


/*+
 *   Function name:
 *   tcsConfigSeqCheck
 *
 *   Purpose:
 *   Check sequence commands for consistency.
 *
 *   Description:
 *   Once all the sequence commands have been preset, this routine is invoked
 *   to make sure that those commands that have been issued are consistent.
 *   At present this is done prior to checking the TCS configuration and the
 *   criterion used is that there must only be one sequence command in
 *   a configuration. In principle some sequence commands could be issued
 *   in parallel but at present this is not required. The commands that
 *   potentially could be issued in parallel are
 *
 *   1. observe, pause, continue, stop, abort or endobserve with guide or
 *      endguide
 *   2. stop, abort or endobserve with park
 *
 *   Invocation:
 *   tcsConfigSeqCheck(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad    (struct cadRecord *)  Pointer to cad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
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

long tcsConfigSeqCheck( cadRecord *pcad )
{
    long status;                /* return status */

    status = CAD_ACCEPT;

    switch (pcad->dir) {
    case menuDirectivePRESET:
        break;

    default:
        break;

    }

    return status;


}


/*+
 *   Function name:
 *   tcsConfigMarkSeqComm
 *
 *   Purpose:
 *   Set flag to show a sequence command is part of a configuration
 *
 *   Description:
 *   Each CAD record in the TCS that implements an OCS sequence command
 *   calls this routine when it receives the preset directive. It checks
 *   if this is the first sequence command in the configuration and if
 *   so sets the flag firstSeqCommMarked to TRUE. If another sequence
 *   command has already been marked as part of this configuration then
 *   an error status is set and an appropriate message returned. Currently
 *   it is an error to include more than one ocs sequence command in a  
 *   configuration.
 *
 *   Invocation:
 *   tcsConfigSeqMarkSeqComm (recname, errmsg)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    fullname (char *)   Name of CAD record
 *      (<)    errmsg   (char *)   Error message or empty string
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 = Error
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

int tcsConfigMarkSeqComm(char *fullname, char *errmsg)
{

    int status;                 /* return status */
    char recname[MAX_STRING_SIZE];      /* CAD record name stripped of prefix */
    char suffix[MAX_STRING_SIZE];       /* CAD name following last ":" */
    int ncad;                   /* Index for the CAD record */

/* Initialise return values */

    status = 0;
    strcpy(errmsg, "OK");       /* Ignored if status is 0 */

/* Extract the command name from the full record name */

    strcpy(recname, fullname);
    if (strrchr(recname, ':') != NULL) {
        strcpy(suffix, strrchr(recname, ':') + 1);
        strcpy(recname, suffix);
    }
/* Mark the record as part of a configuration */

    ncad = tcsCadInfoSetMarked(recname);

    if (ncad < 0) {
        status = ncad;
        sprintf(errmsg, "%s not in database", recname);
        return (status);
    }
/* Check if this is only sequence command in the configuration */

    if (!firstSeqCommMarked) {
        firstSeqCommMarked = TRUE;
        strcpy(firstSeqCommName, recname);
    } else {

/* Make sure this is actually a different command and not the same one
   *  being preset more than once
 */

        if (strcmp(firstSeqCommName, recname) != 0) {
            sprintf(errmsg, "%s and %s are incompatible", firstSeqCommName, recname);
            status = -1;
        }
    }

    return (status);

}

/*+
 *   Function name:
 *   tcsConfigMarkComm
 *
 *   Purpose:
 *   Set flag to show a command is part of a configuration
 *
 *   Description:
 *   Each CAD record in the TCS that implements a command (other than
 *   a sequence command, those should call tcsConfigMarkSeqComm)
 *   calls this routine when it receives the preset directive. The
 *   routine marks this record as part of a configuration and then 
 *   checks if any OCS sequence commands have been preset as well. If 
 *   it finds that they have it will flag an error.
 *
 *   Invocation:
 *   tcsConfigSeqMarkComm (fullname, errmsg)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    fullname (char *)   Name of CAD record
 *      (<)    errmsg   (char *)   Error message or empty string
 *
 *   Function value:
 *   (<)  status  (int) Index to CAD record or -1 
 * 
 *   External functions:
 *   strcpy         (ansiString)       copy a string
 *   strrchr        (ansiString)       find last occurence of character
 *   sprintf        (fioLib)           write formatted string to buffer
 *
 *   External variables:
 *   (>)   firstSeqCommMarked  (int) TRUE if a sequence command is issued
 *
 *-
 */

int tcsConfigMarkComm(char *fullname, char *errmsg)
{

    int status;                 /* return status */
    char recname[MAX_STRING_SIZE];      /* CAD record name stripped of prefix */
    char suffix[MAX_STRING_SIZE];       /* CAD name following last ":" */
    int ncad;                   /* Index for the CAD record */

/* Initialise return values */

    status = 0;
    strcpy(errmsg, "OK");       /* Ignored if status is 0 */

/* Extract the command name from the full record name */

    strcpy(recname, fullname);
    if (strrchr(recname, ':') != NULL) {
        strcpy(suffix, strrchr(recname, ':') + 1);
        strcpy(recname, suffix);
    }
/* Mark the record as part of a configuration */

    ncad = tcsCadInfoSetMarked(recname);

    if (ncad < 0) {
        status = ncad;
        sprintf(errmsg, "%s not in database", recname);
        return (status);
    }
/* Check if any sequence commands are  in the configuration */

    if (firstSeqCommMarked) {
        sprintf(errmsg, "%s and %s are incompatible", firstSeqCommName, recname);
        status = -1;
    }
    return (status);

}

/*+
 *   Function name:
 *   tcsConfigInitTCB
 *
 *   Purpose:
 *   Initialise a Telescope Control Block.
 *
 *   Description:
 *   This routine is called at the start of a Preset operation. Its function
 *   is to fill out a Telescope Control Block (TCB) with default data.
 *   The default data is obtained from the global database that the 
 *   astrometric kernel is operating on. As subsequent CAD records are
 *   successfully preset, the new data over writes the initial default
 *   data that is loaded by this routine.
 *
 *   Invocation:
 *   tcsConfigInitTCB(tcbDefn, ptcb)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tcbDefn  (TCBDEFN)  An enumerated type, CURRENT or PRESET
 *      (!)    ptcb      (struct TCB *) Pointer to a TCB
 *
 *   Function value:
 *      None
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

void tcsConfigInitTCB(TCBDEFN tcbDefn, struct TCB *tcb)
{
    int i;                      /* loop index */
    TELESCOPE tel;
    int status;                 /* status return */

    status = 0;
    tcb->sysconfig.needsCheck = FALSE;
    recalcOTMs = FALSE;

    if (tcbDefn == CURRENT) {

/* Get a reference time for all time dependent calculations */
        timeNow( &tcb->sysconfig.reftime );

/* Check if we are in the special p1LGSMode where we need to bypass
 * some of the normal checks 
 */
        tcb->sysconfig.p1LGSMode.val = tcsGetP1LGSMode();
 
/* Check if we are configured for AO */
        tcb->sysconfig.AOconfig.val = tcsProbeGetAOConfig();
 
/* Fill in all the targets */

        for ( tel = MOUNT; tel <= G4; tel++ ) {
           tcsGetTarget(tel, tcb);
        }

/* Add in all the pointing origins and offsets */

        tcsGetImagePos(MOUNT, 0, &tcb->por[MOUNT], &status);
        tcsGetImagePos(MOUNT, 1, &tcb->porob[MOUNT][0], &status);
        tcsGetImagePos(SOURCE_A, 0, &tcb->por[SOURCE_A], &status);
        for (i = 0; i < 3; i++)
            tcsGetImagePos(SOURCE_A, i + 1, &tcb->porob[i][SOURCE_A], &status);
        tcsGetImagePos(SOURCE_B, 0, &tcb->por[SOURCE_B], &status);
        for (i = 0; i < 3; i++)
            tcsGetImagePos(SOURCE_B, i + 1, &tcb->porob[i][SOURCE_B], &status);
        tcsGetImagePos(SOURCE_C, 0, &tcb->por[SOURCE_C], &status);
        for (i = 0; i < 3; i++)
            tcsGetImagePos(SOURCE_C, i + 1, &tcb->porob[i][SOURCE_C], &status);

/* Fill in all the offsets */

        for ( tel = MOUNT; tel <= G4; tel++ ) {
           tcsGetBaseOffset(tel, 0, &tcb->ob[0][tel], &status);
        }
        for (i = 0; i < 3; i++) {
            tcsGetBaseOffset(SOURCE_A, i, &tcb->ob[i][SOURCE_A], &status);
            tcsGetBaseOffset(SOURCE_B, i, &tcb->ob[i][SOURCE_B], &status);
            tcsGetBaseOffset(SOURCE_C, i, &tcb->ob[i][SOURCE_C], &status);
            tcsGetBaseOffset(PWFS1, i, &tcb->ob[i][PWFS1], &status);
            tcsGetBaseOffset(PWFS2, i, &tcb->ob[i][PWFS2], &status);
            tcsGetBaseOffset(OIWFS, i, &tcb->ob[i][OIWFS], &status);
            tcsGetBaseOffset(G1, i, &tcb->ob[i][G1], &status);
            tcsGetBaseOffset(G2, i, &tcb->ob[i][G2], &status);
            tcsGetBaseOffset(G3, i, &tcb->ob[i][G3], &status);
            tcsGetBaseOffset(G4, i, &tcb->ob[i][G4], &status);
        }

/* Fill in the rotator configuration */

        tcsGetRotConfig(&tcb->sysconfig.rot);

/* Fetch the filters */

        tcsGetTFilt(&tcb->tf1);
        tcsGetPFilt(&tcb->pf2);

/* Fetch the chop parameters */
        tcsGetChop(1, &tcb->chop[0]);
        tcsGetChop(2, &tcb->chop[1]);

/* Fetch the planet and orbit parameters */
        for ( tel = MOUNT; tel <= G4; tel++ ) {
          tcsGetPlanet(tel, tcb);
          tcsGetOrbit(tel, &tcb->orbit[tel]);
        }

/* Get Chop Mode. */
        tcsGetChopMode( &tcb->sysconfig );

/* Set the Slew reset flags to false */
        tcb->slew.chop.val = 0;
        tcb->slew.nod.val = 0;
        tcb->slew.soff.val = 0;
        tcb->slew.sdt.val = 0;
        tcb->slew.moff.val = 0;
        tcb->slew.mdt.val = 0;
        tcb->slew.sc1.val = 0;
        tcb->slew.sc2.val = 0;
        tcb->slew.lpm.val = 0;
        tcb->slew.guide.val = 0;
        tcb->slew.goff.val = 0;
        tcb->slew.pooff.val = 0;

    } else {                    /* Fill out Preset TCB */
        *tcb = kernelTCB;
    }

}


/*+
 *   Function name:
 *   tcsConfigPrintTCB
 *
 *   Purpose:
 *   Diagnostic to print contents of a TCB to the screen
 *
 *   Description:
 *   This routine simply outputs the full contents of a TCB to the screen
 *   for diagnostic purposes.
 *
 *   Invocation:
 *   tcsConfigPrintTCB(tcbDefn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tcbDefn  (TCBDEFN) Either CURRENT or PRESET
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *   It is neccesary for the user to know that CURRENT maps to 0 and 
 *   PRESET to 1 when executing from the command line. The enumerated
 *   type is not available directly
 *
 *-
 */

void tcsConfigPrintTCB(TCBDEFN tcbDefn)
{
    struct TCB *pTCB;

    char *frames[] =
    {"Mount Az/El", "Topo Az/El ", " Apparent  ",
     "    FK5    ", "    FK4    "};

    if (tcbDefn == CURRENT) {
        pTCB = &currentTCB;
        printf("                  CURRENT Telescope Control Block\n\n");
    } else {
        pTCB = &presetTCB;
        printf("                   PRESET Telescope Control Block\n\n");
    }

    if (pTCB->sysconfig.p1LGSMode.val) {
      printf("P1+LGS mode is enabled\n");
    } else {
      printf("P1+LGS mode is disabled\n");
    }
    printf("\n");

    printf("              Mount         Source A        Source B        Source C\n");
    printf("Name       %s        %s        %s        %s\n", pTCB->target[MOUNT].name.val,
           pTCB->target[SOURCE_A].name.val,
           pTCB->target[SOURCE_C].name.val,
           pTCB->target[SOURCE_C].name.val);
    printf("RA/Az      %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].theta1.val * R2D, 
           pTCB->target[SOURCE_A].theta1.val * R2D,
           pTCB->target[SOURCE_B].theta1.val * R2D, 
           pTCB->target[SOURCE_C].theta1.val * R2D);
    printf("Dec/El     %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].theta2.val * R2D,
           pTCB->target[SOURCE_A].theta2.val * R2D,
           pTCB->target[SOURCE_B].theta2.val * R2D,
           pTCB->target[SOURCE_C].theta2.val * R2D);
    printf("Frame      %s     %s    %s    %s \n",
           frames[pTCB->target[MOUNT].frame.val],
           frames[pTCB->target[SOURCE_A].frame.val],
           frames[pTCB->target[SOURCE_B].frame.val], 
           frames[pTCB->target[SOURCE_C].frame.val]);
    printf("Equinox   %c%10.5f    %c%10.5f   %c%10.5f     %c%10.5f\n",
           pTCB->target[MOUNT].eqx.val.type,
           pTCB->target[MOUNT].eqx.val.year,
           pTCB->target[SOURCE_A].eqx.val.type, 
           pTCB->target[SOURCE_A].eqx.val.year,
           pTCB->target[SOURCE_B].eqx.val.type,
           pTCB->target[SOURCE_B].eqx.val.year,
           pTCB->target[SOURCE_C].eqx.val.type,
           pTCB->target[SOURCE_C].eqx.val.year);
    printf("Epoch     %c%10.5f    %c%10.5f   %c%10.5f     %c%10.5f\n",
           pTCB->target[MOUNT].epoch.val.type, 
           pTCB->target[MOUNT].epoch.val.year,
           pTCB->target[SOURCE_A].epoch.val.type,
           pTCB->target[SOURCE_A].epoch.val.year,
           pTCB->target[SOURCE_B].epoch.val.type,
           pTCB->target[SOURCE_B].epoch.val.year,
           pTCB->target[SOURCE_C].epoch.val.type,
           pTCB->target[SOURCE_C].epoch.val.year);
    printf("Parallax   %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].parallax.val,
           pTCB->target[SOURCE_A].parallax.val,
           pTCB->target[SOURCE_B].parallax.val,
           pTCB->target[SOURCE_C].parallax.val);
    printf("PM RA      %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].pmRA.val,
           pTCB->target[SOURCE_A].pmRA.val,
           pTCB->target[SOURCE_B].pmRA.val,
           pTCB->target[SOURCE_C].pmRA.val);
    printf("PM Dec     %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].pmDec.val,
           pTCB->target[SOURCE_A].pmDec.val,
           pTCB->target[SOURCE_B].pmDec.val,
           pTCB->target[SOURCE_C].pmDec.val);
    printf("RV         %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->target[MOUNT].rv.val,
           pTCB->target[SOURCE_A].rv.val,
           pTCB->target[SOURCE_B].rv.val,
           pTCB->target[SOURCE_C].rv.val);
    printf("Wavelength %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->wavel[MOUNT].wavel.val,
           pTCB->wavel[SOURCE_A].wavel.val,
           pTCB->wavel[SOURCE_B].wavel.val,
           pTCB->wavel[SOURCE_C].wavel.val);
    printf("Epoch0    %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->difftrack[MOUNT].t0.val,
           pTCB->difftrack[SOURCE_A].t0.val,
           pTCB->difftrack[SOURCE_B].t0.val,
           pTCB->difftrack[SOURCE_C].t0.val);
    printf("Diff RA    %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->difftrack[MOUNT].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_A].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_B].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_C].dtheta1.val / AS2R / 86400);
    printf("Diff Dec   %10.5f     %10.5f    %10.5f      %10.5f\n",
           pTCB->difftrack[MOUNT].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_A].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_B].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[SOURCE_C].dtheta2.val / AS2R / 86400);
    printf("Tracking   %s     %s    %s    %s \n",
           frames[pTCB->track[MOUNT].frame.val],
           frames[pTCB->track[SOURCE_A].frame.val],
           frames[pTCB->track[SOURCE_B].frame.val],
           frames[pTCB->track[SOURCE_C].frame.val]);
    printf("frame     %c%10.5f    %c%10.5f   %c%10.5f     %c%10.5f\n",
           pTCB->track[MOUNT].eqx.val.type,
           pTCB->track[MOUNT].eqx.val.year,
           pTCB->track[SOURCE_A].eqx.val.type,
           pTCB->track[SOURCE_A].eqx.val.year,
           pTCB->track[SOURCE_B].eqx.val.type,
           pTCB->track[SOURCE_B].eqx.val.year,
           pTCB->track[SOURCE_C].eqx.val.type,
           pTCB->track[SOURCE_C].eqx.val.year);

    printf("\n             PWFS1         PWFS2            OIWFS     \n");
    printf("Name      %s         %s        %s   \n", pTCB->target[PWFS1].name.val,
           pTCB->target[PWFS2].name.val,
           pTCB->target[OIWFS].name.val);
    printf("RA/Az      %10.5f     %10.5f    %10.5f  \n",
           pTCB->target[PWFS1].theta1.val * R2D,
           pTCB->target[PWFS2].theta1.val * R2D,
           pTCB->target[OIWFS].theta1.val * R2D);
    printf("Dec/El     %10.5f     %10.5f    %10.5f\n",
           pTCB->target[PWFS1].theta2.val * R2D,
           pTCB->target[PWFS2].theta2.val * R2D,
           pTCB->target[OIWFS].theta2.val * R2D);
    printf("Frame      %s     %s    %s  \n",
           frames[pTCB->target[PWFS1].frame.val],
           frames[pTCB->target[PWFS2].frame.val],
           frames[pTCB->target[OIWFS].frame.val]);
    printf("Equinox   %c%10.5f    %c%10.5f   %c%10.5f\n",
           pTCB->target[PWFS1].eqx.val.type,
           pTCB->target[PWFS1].eqx.val.year,
           pTCB->target[PWFS2].eqx.val.type,
           pTCB->target[PWFS2].eqx.val.year,
           pTCB->target[OIWFS].eqx.val.type,
           pTCB->target[OIWFS].eqx.val.year);
    printf("Epoch     %c%10.5f    %c%10.5f   %c%10.5f \n",
           pTCB->target[PWFS1].epoch.val.type,
           pTCB->target[PWFS1].epoch.val.year,
           pTCB->target[PWFS2].epoch.val.type,
           pTCB->target[PWFS2].epoch.val.year,
           pTCB->target[OIWFS].epoch.val.type,
           pTCB->target[OIWFS].epoch.val.year);
    printf("Parallax   %10.5f     %10.5f    %10.5f \n",
           pTCB->target[PWFS1].parallax.val,
           pTCB->target[PWFS2].parallax.val,
           pTCB->target[OIWFS].parallax.val);
    printf("PM RA      %10.5f     %10.5f    %10.5f  \n",
           pTCB->target[PWFS1].pmRA.val,
           pTCB->target[PWFS2].pmRA.val,
           pTCB->target[OIWFS].pmRA.val);
    printf("PM Dec     %10.5f     %10.5f    %10.5f \n",
           pTCB->target[PWFS1].pmDec.val,
           pTCB->target[PWFS2].pmDec.val,
           pTCB->target[OIWFS].pmDec.val);
    printf("RV         %10.5f     %10.5f    %10.5f \n",
           pTCB->target[PWFS1].rv.val,
           pTCB->target[PWFS2].rv.val,
           pTCB->target[OIWFS].rv.val);
    printf("Wavelength %10.5f     %10.5f    %10.5f \n",
           pTCB->wavel[PWFS1].wavel.val,
           pTCB->wavel[PWFS2].wavel.val,
           pTCB->wavel[OIWFS].wavel.val);
    printf("Epoch0    %10.5f     %10.5f    %10.5f  \n",
           pTCB->difftrack[PWFS1].t0.val,
           pTCB->difftrack[PWFS2].t0.val,
           pTCB->difftrack[OIWFS].t0.val);
    printf("Diff RA    %10.5f     %10.5f    %10.5f \n",
           pTCB->difftrack[PWFS1].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[PWFS2].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[OIWFS].dtheta1.val / AS2R / 86400);
    printf("Diff Dec   %10.5f     %10.5f    %10.5f \n",
           pTCB->difftrack[PWFS1].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[PWFS2].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[OIWFS].dtheta2.val / AS2R / 86400);
    printf("Tracking   %s     %s    %s \n",
        frames[pTCB->track[PWFS1].frame.val],
           frames[pTCB->track[PWFS2].frame.val],
           frames[pTCB->track[OIWFS].frame.val]);
    printf("frame     %c%10.5f    %c%10.5f   %c%10.5f\n",
           pTCB->track[PWFS1].eqx.val.type,
           pTCB->track[PWFS1].eqx.val.year,
           pTCB->track[PWFS2].eqx.val.type,
           pTCB->track[PWFS2].eqx.val.year,
           pTCB->track[OIWFS].eqx.val.type,
           pTCB->track[OIWFS].eqx.val.year);

    printf("\n              G1             G2            G3           G4\n");
    printf("Name      %s         %s        %s      %s\n", 
           pTCB->target[G1].name.val,
           pTCB->target[G2].name.val,
           pTCB->target[G3].name.val,
           pTCB->target[G4].name.val);
    printf("RA/Az      %10.5f     %10.5f    %10.5f    %10.5f  \n",
           pTCB->target[G1].theta1.val * R2D,
           pTCB->target[G2].theta1.val * R2D,
           pTCB->target[G3].theta1.val * R2D,
           pTCB->target[G4].theta1.val * R2D);
    printf("Dec/El     %10.5f     %10.5f    %10.5f    %10.5f\n",
           pTCB->target[G1].theta2.val * R2D,
           pTCB->target[G2].theta2.val * R2D,
           pTCB->target[G3].theta2.val * R2D,
           pTCB->target[G4].theta2.val * R2D);
    printf("Frame      %s     %s    %s    %s\n",
           frames[pTCB->target[G1].frame.val],
           frames[pTCB->target[G2].frame.val],
           frames[pTCB->target[G3].frame.val],
           frames[pTCB->target[G4].frame.val]);
    printf("Equinox   %c%10.5f    %c%10.5f   %c%10.5f   %c%10.5f\n",
           pTCB->target[G1].eqx.val.type,
           pTCB->target[G1].eqx.val.year,
           pTCB->target[G2].eqx.val.type,
           pTCB->target[G2].eqx.val.year,
           pTCB->target[G3].eqx.val.type,
           pTCB->target[G3].eqx.val.year,
           pTCB->target[G4].eqx.val.type,
           pTCB->target[G4].eqx.val.year);
    printf("Epoch     %c%10.5f    %c%10.5f   %c%10.5f   %c%10.5f \n",
           pTCB->target[G1].epoch.val.type,
           pTCB->target[G1].epoch.val.year,
           pTCB->target[G2].epoch.val.type,
           pTCB->target[G2].epoch.val.year,
           pTCB->target[G3].epoch.val.type,
           pTCB->target[G3].epoch.val.year,
           pTCB->target[G4].epoch.val.type,
           pTCB->target[G4].epoch.val.year);
    printf("Parallax   %10.5f     %10.5f    %10.5f    %10.5f \n",
           pTCB->target[G1].parallax.val,
           pTCB->target[G2].parallax.val,
           pTCB->target[G3].parallax.val,
           pTCB->target[G4].parallax.val);
    printf("PM RA      %10.5f     %10.5f    %10.5f    %10.5f  \n",
           pTCB->target[G1].pmRA.val,
           pTCB->target[G2].pmRA.val,
           pTCB->target[G3].pmRA.val,
           pTCB->target[G4].pmRA.val);
    printf("PM Dec     %10.5f     %10.5f    %10.5f    %10.5f\n",
           pTCB->target[G1].pmDec.val,
           pTCB->target[G2].pmDec.val,
           pTCB->target[G3].pmDec.val,
           pTCB->target[G4].pmDec.val);
    printf("RV         %10.5f     %10.5f    %10.5f    %10.5f\n",
           pTCB->target[G1].rv.val,
           pTCB->target[G2].rv.val,
           pTCB->target[G3].rv.val,
           pTCB->target[G4].rv.val);
    printf("Wavelength %10.5f     %10.5f    %10.5f    %10.5f\n",
           pTCB->wavel[G1].wavel.val,
           pTCB->wavel[G2].wavel.val,
           pTCB->wavel[G3].wavel.val,
           pTCB->wavel[G4].wavel.val);
    printf("Epoch0    %10.5f     %10.5f    %10.5f    %10.5f\n",
           pTCB->difftrack[G1].t0.val,
           pTCB->difftrack[G2].t0.val,
           pTCB->difftrack[G3].t0.val,
           pTCB->difftrack[G4].t0.val);
    printf("Diff RA    %10.5f     %10.5f    %10.5f   %10.5f\n",
           pTCB->difftrack[G1].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[G2].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[G3].dtheta1.val / AS2R / 86400,
           pTCB->difftrack[G4].dtheta1.val / AS2R / 86400);
    printf("Diff Dec   %10.5f     %10.5f    %10.5f   %10.5f\n",
           pTCB->difftrack[G1].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[G2].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[G3].dtheta2.val / AS2R / 86400,
           pTCB->difftrack[G4].dtheta2.val / AS2R / 86400);
    printf("Tracking   %s     %s    %s   %s\n",
        frames[pTCB->track[G1].frame.val],
           frames[pTCB->track[G2].frame.val],
           frames[pTCB->track[G3].frame.val],
           frames[pTCB->track[G4].frame.val]);
    printf("frame     %c%10.5f    %c%10.5f   %c%10.5f   %c%10.5f\n",
           pTCB->track[G1].eqx.val.type,
           pTCB->track[G1].eqx.val.year,
           pTCB->track[G2].eqx.val.type,
           pTCB->track[G2].eqx.val.year,
           pTCB->track[G3].eqx.val.type,
           pTCB->track[G3].eqx.val.year,
           pTCB->track[G4].eqx.val.type,
           pTCB->track[G4].eqx.val.year);


    printf("\n              P.O.           Base Offset         Offset\n");
    printf("Mount    %10.5f        %10.5f        %10.5f\n",
           pTCB->por[MOUNT].x.val,
           pTCB->porob[0][MOUNT].x.val,
           pTCB->ob[0][MOUNT].dtheta1.val);
    printf("         %10.5f        %10.5f        %10.5f\n",
           pTCB->por[MOUNT].y.val,
           pTCB->porob[0][MOUNT].y.val,
           pTCB->ob[0][MOUNT].dtheta2.val);
    printf("Source A %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_A].x.val,
           pTCB->porob[0][SOURCE_A].x.val,
           pTCB->ob[0][SOURCE_A].dtheta1.val);
    printf("         %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_A].y.val,
           pTCB->porob[0][SOURCE_A].y.val,
           pTCB->ob[0][SOURCE_A].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_A].x.val,
           pTCB->ob[1][SOURCE_A].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_A].y.val,
           pTCB->ob[1][SOURCE_A].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_A].x.val,
           pTCB->ob[2][SOURCE_A].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_A].y.val,
           pTCB->ob[2][SOURCE_A].dtheta2.val);
    printf("Source B %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_B].x.val,
           pTCB->porob[0][SOURCE_B].x.val,
           pTCB->ob[0][SOURCE_B].dtheta1.val);
    printf("         %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_B].y.val,
           pTCB->porob[0][SOURCE_B].y.val,
           pTCB->ob[0][SOURCE_B].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_B].x.val,
           pTCB->ob[1][SOURCE_B].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_B].y.val,
           pTCB->ob[1][SOURCE_B].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_B].x.val,
           pTCB->ob[2][SOURCE_B].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_B].y.val,
           pTCB->ob[2][SOURCE_B].dtheta2.val);
    printf("Source C %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_C].x.val,
           pTCB->porob[0][SOURCE_C].x.val,
           pTCB->ob[0][SOURCE_C].dtheta1.val);
    printf("         %10.5f        %10.5f        %10.5f\n",
           pTCB->por[SOURCE_C].y.val,
           pTCB->porob[0][SOURCE_C].y.val,
           pTCB->ob[0][SOURCE_C].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_C].x.val,
           pTCB->ob[1][SOURCE_C].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[1][SOURCE_C].y.val,
           pTCB->ob[1][SOURCE_C].dtheta2.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_C].x.val,
           pTCB->ob[2][SOURCE_C].dtheta1.val);
    printf("                       %10.5f        %10.5f\n",
           pTCB->porob[2][SOURCE_C].y.val,
           pTCB->ob[2][SOURCE_C].dtheta2.val);

    printf("\nFilter 1 sc          bw           maxv            grab\n");
    printf("           %1d      %10.5f   %10.5f      %10.5f\n",
           pTCB->tf1.sc.val, pTCB->tf1.bw.val,
           pTCB->tf1.maxv.val / AS2R, pTCB->tf1.grab.val / AS2R);

    printf("\nFilter 2   Weight A         Weight B        Weight C\n");
    printf("         %10.5f       %10.5f        %10.5f\n",
           pTCB->pf2.weightA.val, pTCB->pf2.weightB.val,
           pTCB->pf2.weightC.val);
    printf("           sc          bw           maxv            grab\n");
    printf("           %1d      %10.5f   %10.5f      %10.5f\n",
           pTCB->pf2.sc.val, pTCB->pf2.bw.val,
           pTCB->pf2.maxv.val / AS2R, pTCB->pf2.grab.val / AS2R);
    printf("\n\nDesired position angle %10.5f frame %d equinox %c%10.5f\n",
           pTCB->sysconfig.rot.ipa.val, pTCB->sysconfig.rot.frame.val,
           pTCB->sysconfig.rot.eqx.val.type,
           pTCB->sysconfig.rot.eqx.val.year);
    printf("        Frame   Equinox      throw     pa\n");
    printf("Chop B   %1d  %c%10.5f %10.5f %10.5f\n", pTCB->chop[0].frame.val,
            pTCB->chop[0].eqx.val.type, pTCB->chop[0].eqx.val.year,
            pTCB->chop[0].throw.val, pTCB->chop[0].pa.val);
    printf("Chop C   %1d  %c%10.5f %10.5f %10.5f\n", pTCB->chop[1].frame.val,
            pTCB->chop[1].eqx.val.type, pTCB->chop[1].eqx.val.year,
            pTCB->chop[1].throw.val, pTCB->chop[1].pa.val);
}



/*+
 *   Function name:
 *   tcsConfigSetTels
 *
 *   Purpose:
 *   Set and check the list of telescopes given with the mount target.
 *
 *   Description:
 *   This function is called from the subroutine attached to the CAD 
 *   record that processes the mount target. Its purpose is to allow
 *   the user to specify which of the virtual telescopes they want the
 *   target parameters to apply to. The list of telescopes can be any
 *   combination of S, A or B with + signs in between e.g. A+B would
 *   indicate the target parameters should apply not only to the mount
 *   but also to chop states A & B. If an empty or null string is
 *   passed then it is assumed that the target parameters will apply to
 *   the mount, the source (i.e. M2) as well as chop states A and B.
 *
 *   Invocation:
 *   tcsConfigSetTels(tels, &status)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tels    (char *)    List of telescopes
 *      (!)    status  (int *)     Return status
 *
 *   Function value:
 *     None
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

void tcsConfigSetTels(char *tels, int *status)
{

    if (*status != 0)
        return;

/* This is only a dummy at present, just copy the data */

    strcpy(telnames, tels);

}

/*+
 *   Function name:
 *   tcsConfigSetTCBDefn
 *
 *   Purpose:
 *   Set the TCB that is being acted on
 *
 *   Description:
 *   The TCS has the concept of a current configuration and a preset
 *   configuration. The current configuration is the one the telescope
 *   is set to. The preset configuration will typically be that for the
 *   next target that the observer wants to observe. This routine sets
 *   configuration that is currently being acted on.
 *
 *   Invocation:
 *   tcsConfigSetTCBDefn (tcbdefn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    tcbdefn  (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *
 *-
 */


void tcsConfigSetTCBDefn(TCBDEFN tcbDefn)
{

    activeTCB = tcbDefn;

}


/*+
 *   Function name:
 *   tcsConfigSetFilePrefix
 *
 *   Purpose:
 *   Set the file path prefix for save/load file names.
 *
 *   Description:
 *   Set the static string holding the prefix.
 *
 *   Invocation:
 *   tcsConfigSetFilePrefix(prefix)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    prefix    (char *)   File path prefix for save/load file names.
 *
 *   Function value:
 *   none
 *
 *-
 */

void tcsConfigSetFilePrefix(char *prefix)
{
    strncpy(saveFilePrefix, prefix, MAX_STRING_SIZE);
}

/*+
 *   Function name:
 *   tcsConfigSaveTcb
 *
 *   Purpose:
 *   Write the contents of the specified TCB (CURRENT OR PRESET) into
 *   the named file
 *
 *   Description:
 *
 *   Invocation:
 *   tcsConfigSaveTcb(tcbDefn, file, comment, errmess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tcbDefn   (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)    filename  (char *)   Name of file in which to save data     
 *      (>)    comment   (char *)   User comment for this configuration
 *      (<)    errmess   (char *)   Error message returned via CAD error field
 *
 *   Function value:
 *     Returned integer status
 * 
 *   External functions:
 *   malloc       (memPartLib)     allocate a block of memory
 *   free         (memPartLib)     free a block of memory
 *   fopen        (ansiStdio)      open a file specified by name
 *   fwrite       (ansiStdio)      write from a specified array
 *   ferror       (ansiStdio)      test error indicator for file pointer
 *   fclose       (ansiStdio)      close a stream
 *   strncpy      (ansiString)     copy characters
 *   sprintf      (fioLib)         write formatted string to a buffer 
 *   printf       (fioLib)         write formatted string to output stream
 *   timeNowC     (timeLib)        fetch current time
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   fopen can fail but still return OK. For example if the user doesn't
 *   have permission to write to the directory where the file is to be
 *   placed fopen apparently completes normally although in fact it
 *   hasn't created the file. 
 *
 *-
 */

int tcsConfigSaveTcb(TCBDEFN tcbDefn, char *filename, char *comment, char *errmess)
{

    FILE *savefile;             /* File in which to save TCB data */
    int i, status;
    char fullfn[80];            /* Filename including path name prefix */
    int nwrite;                 /* Number of items actually written by fwrite */
    int utctime[7];             /* Current UTC time y, m, d, h, m, s, .ss */
    struct SAVEDATA *savedData; /* pointer to area for data being saved */

    strncpy(errmess, "save : completed OK", MAX_STRING_SIZE - 1);
    if (tcbDefn != CURRENT && tcbDefn != PRESET) {
        sprintf(errmess, "save : TCB must be CURRENT or PRESET");
        return (1);
    }
/* Allocate memory for the data to be saved */
    savedData = (struct SAVEDATA *) malloc(sizeof(struct SAVEDATA));
    if (savedData == NULL) {
        sprintf(errmess, "save: failed to allocate memory");
        return (1);
    }
/* Set up the data to be saved : time, comment and appropriate TCB */
    status = timeNowC(UTC, 2, utctime);         /* Get current time (UTC) */
    if (status != 0) {
        for (i = 0; i < 7; i++)
            utctime[i] = 0;
    }                           /* Set time on error */
    sprintf(savedData->savetime, "%4d%02d%02d %02d:%02d:%02d.%02d%c", utctime[0],
            utctime[1], utctime[2], utctime[3], utctime[4], utctime[5], utctime[6], '\0');
    strcpy(savedData->comment, comment);
    if (tcbDefn == CURRENT)
        savedData->savedtcb = currentTCB;
    else if (tcbDefn == PRESET)
        savedData->savedtcb = presetTCB;

/* Add in prefix for filename if not null */
    if (strlen(saveFilePrefix) > 0) {
        strcpy(fullfn, saveFilePrefix);
        strcat(fullfn, filename);
    } else
        strcpy(fullfn, filename);

    if ((savefile = fopen(fullfn, "w")) != NULL) {
/* Now write out the data to the file */
        nwrite = fwrite(savedData, sizeof(struct SAVEDATA), 1, savefile);
        if (nwrite != 1 || ferror(savefile) != 0) {
            sprintf(errmess, "save : Error %d during write to file %s\n", ferror(savefile), fullfn);
            fclose(savefile);
            free(savedData);
            return (1);
        }
    } else {
        sprintf(errmess, "save : Error %d opening file %s\n", ferror(savefile), fullfn);
        fclose(savefile);
        free(savedData);
        return (1);
    }

    printf("save : data written to file %s OK.\n", fullfn);
    fclose(savefile);
    free(savedData);
    return (0);
}


/*+
 *   Function name:
 *   tcsConfigLoadTcb
 *
 *   Purpose:
 *   Read the contents of the specified TCB (CURRENT OR PRESET) from
 *   the named file
 *
 *   Description:
 *
 *   Invocation:
 *   tcsConfigLoadTcb(tcbDefn, file, errmess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tcbDefn   (TCBDEFN)  Enumerated type, CURRENT or PRESET
 *      (>)    file      (char *)   Name of file from which to load data  
 *      (<)    errmess   (char *)   Error message returned via CAD error field   
 *
 *   Function value:
 *     Returned integer status
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

int tcsConfigLoadTcb(TCBDEFN tcbDefn, char *filename, char *errmess)
{

    FILE *loadfile;             /* File from which to load TCB data */
    char fullfn[80];            /* Filename including path name prefix */
    int nread;
    struct SAVEDATA *loadedData;

    strcpy(errmess, "load : completed OK");

    if (tcbDefn != CURRENT && tcbDefn != PRESET) {
        sprintf(errmess, "load : Error - TCB must be CURRENT or PRESET");
        return (1);
    }
/* Allocate area to load data into */
    loadedData = (struct SAVEDATA *) malloc(sizeof(struct SAVEDATA));
    if (loadedData == NULL) {
        sprintf(errmess, "load: failed to allocate memory");
        return (1);
    }

/* Add in prefix for filename if not null */
    if (strlen(saveFilePrefix) > 0) {
        strcpy(fullfn, saveFilePrefix);
        strcat(fullfn, filename);
    } else
        strcpy(fullfn, filename);

    if ((loadfile = fopen(fullfn, "r")) != NULL) {
        nread = fread(loadedData, sizeof(struct SAVEDATA), 1, loadfile);        /* Read the time */
        if (nread != 1 || ferror(loadfile) != 0) {
            sprintf(errmess, "load : Error %d during read from file %s\n", ferror(loadfile), fullfn);
            fclose(loadfile);
            free(loadedData);
            return (1);
        }
    } else {
        sprintf(errmess, "load : Error %d, failed to open file %s\n", ferror(loadfile), fullfn);
        fclose(loadfile);
        free(loadedData);
        return (1);
    }

    if (tcbDefn == CURRENT)
        currentTCB = loadedData->savedtcb;
    else if (tcbDefn == PRESET)
        presetTCB = loadedData->savedtcb;
    printf("load : data had been saved on %s\n", loadedData->savetime);
    printf("load : comment with save was %s\n", loadedData->comment);

    printf("load : data read from file %s OK.\n", fullfn);

    fclose(loadfile);
    free(loadedData);
    return (0);
}


/*+
 *   Function name:
 *   tcsConfigPutTargetFields
 *
 *   Purpose:
 *   Using Channel Access, set each input field in the CAD record 
 *   corresponding to the target definition for a specified virtual telescope.
 *
 *   Description:
 *   For each field of the CAD record corresponding for the specified target
 *   use tcsPutCadField to set the value which was stored in the 'instring' 
 *   field of the target data structure.
 *
 *   Invocation:
 *   tcsConfigPutTargetFields(top, target)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    top       (char *)     The top database name prefix string 
 *      (>)    tel       (TELESCOPE)  Name of virtual telescope data to be set
 *      (>)    pTCB      (TCB *)      Pointer to configuation block
 *
 *   Function value:
 *     None
 * 
 *   External functions:
 *   tcsPutCadField        tcsChannelAccess      Set a CAD input field
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
static void tcsConfigPutTargetFields(const char *top, TELESCOPE tel, 
                                     struct TCB *pTCB)
{

/* Set each CAD input field value using CA Put */
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].theta1.field,
       pTCB->target[tel].theta1.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].theta2.field, 
       pTCB->target[tel].theta2.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].name.field, 
       pTCB->target[tel].name.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].frame.field, 
       pTCB->target[tel].frame.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].eqx.field, 
       pTCB->target[tel].eqx.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].epoch.field, 
       pTCB->target[tel].epoch.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].parallax.field, 
       pTCB->target[tel].parallax.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].pmRA.field, 
       pTCB->target[tel].pmRA.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].pmDec.field, 
       pTCB->target[tel].pmDec.instring);
    tcsPutCadField(top, pTCB->target[tel].cadname,
       pTCB->target[tel].rv.field, 
       pTCB->target[tel].rv.instring);
    tcsPutCadField(top, pTCB->wavel[tel].cadname,
       pTCB->wavel[tel].wavel.field, 
       pTCB->wavel[tel].wavel.instring);
    tcsPutCadField(top, pTCB->track[tel].cadname,
       pTCB->track[tel].frame.field, 
       pTCB->track[tel].frame.instring);
    tcsPutCadField(top, pTCB->track[tel].cadname,
       pTCB->track[tel].eqx.field, 
       pTCB->track[tel].eqx.instring);
    tcsPutCadField(top, pTCB->difftrack[tel].cadname,
       pTCB->difftrack[tel].frame.field, 
       pTCB->difftrack[tel].frame.instring);
    tcsPutCadField(top, pTCB->difftrack[tel].cadname,
       pTCB->difftrack[tel].eqx.field, 
       pTCB->difftrack[tel].eqx.instring);
    tcsPutCadField(top, pTCB->difftrack[tel].cadname,
       pTCB->difftrack[tel].t0.field, 
       pTCB->difftrack[tel].t0.instring);
    tcsPutCadField(top, pTCB->difftrack[tel].cadname,
       pTCB->difftrack[tel].dtheta1.field, 
       pTCB->difftrack[tel].dtheta1.instring);
    tcsPutCadField(top, pTCB->difftrack[tel].cadname,
       pTCB->difftrack[tel].dtheta2.field, 
       pTCB->difftrack[tel].dtheta2.instring);
}

/*+
 *   Function name:
 *   tcsConfigSetAllTargetFields
 *
 *   Purpose:
 *   Set the input fields for the CAD records that define
 *   all virtual telescopes
 *   
 *   Description:
 *   For each virtual telescope in turn, set all
 *   the input fields with a call to tcsConfigPutTargetFields 
 *
 *   Invocation:
 *   csConfigSetAllTargetFields(top, tcbDefn)
 *
 *   Parameters: (">" input, "!" modified, "<" output) 
 *      (>)    top       (char *)   The top database name prefix string 
 *      (>)    tcbDefn   (TCBDEFN)  TCB to be set : CURRENT or PRESET
 *
 *   Function value:
 *     None
 * 
 *   External functions:
 *   tcsConfigPutTargetFields   Set all the CAD input fields for the specified target
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
void tcsConfigSetAllTargetFields(const char *top, TCBDEFN tcbDefn)
{
    TELESCOPE tel;

    if (tcbDefn == CURRENT) {
        for ( tel = MOUNT; tel <= OIWFS; tel++ )
           tcsConfigPutTargetFields(top, tel, &currentTCB);
    } else if (tcbDefn == PRESET) {
        for ( tel = MOUNT; tel <= OIWFS; tel++ )
           tcsConfigPutTargetFields(top, tel, &presetTCB);
    }
}

/*+
 *   Function name:
 *   tcsConfigM2Scan
 *
 *   Purpose:
 *   Check tip/tilt values for M2
 *
 *   Description:
 *   The M2 tip/tilt values in the WCS context are compared with the 
 *   current allowed maximum value and if it is greater than this
 *   maximum an error is returned. The scan tip/tilts are then differenced
 *   to yield chop throws and these are checked for compatibility with
 *   the requested chop frequency and mode.  This last check is to trap
 *   illegal data when absolute chopping. It does not trap illegal data
 *   when relative chopping.
 *
 *   Invocation:
 *   status = tcsConfigM2Scan (&TCB, &ctx, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>) pTCB         (struct TCB *) Pointer to TCB structure
 *      (>) ctx          (struct WCS_CTX *) Pointer to WCS context
 *      (<) mess          (char *) Return error message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, 1 = Error
 * 
 *   External functions:
 *   tcsOpticsGetTiltLimits   (tcsOptics) Fetch current tilt limits
 *   tcsOpticsCheckChopLimits (tcsOptics) Check chop throw/freq parameters
 *
 *   Deficiencies:
 *   The maximum tilt limit is used rather than also checking the current
 *   Z displacement as well.
 *
 *-
 */

int tcsConfigM2Scan( struct TCB *pTCB, struct WCS_CTX *ctx, char *errMess)
{
    int dbgLevel;               /* Debug level */
    int status;                 /* return status */
    int i;                      /* Loop index */
    int posn;                   /* Number of chop positions in use */
    double maxTilt;             /* Max tilt (arcsec) */
    double currTilt[3];         /* Current tilt demand */
    double currThrow;           /* Current chop throw (arcsec) */
    double freqLimit;           /* Frequency limit for given throw */
    double throwLimit;          /* Throw limit for given frequency */
    double maxZ;                /* Maximum allowed Z (focus) value */
    char mess[80];              /* debug message */
    char *chopNames[] =
    {"A", "B", "C"};

/* Initialise return data */

    status = 0;
    strcpy(errMess, " ");
    dbgLevel = DBG_NONE;

/* Set number of chop position used for the selected mode. */
    switch ( pTCB->sysconfig.chopmode.val ) {
       case NOCHOP:
          posn = 1;
          break;
       case TWOPOSN:
          posn = 2;
          break;
       default:
          posn = 3;
          break;
    }

    for (i = 0; i < posn; i++) {
        tcsOpticsGetTiltLimits(&maxTilt, &maxZ);
        sprintf(mess, "tcsConfigM2Scan: chop %s x,y scan %f %f",
                chopNames[i], ctx->m2xy[i][0] / AS2R, ctx->m2xy[i][1] / AS2R);
        currTilt[i] = sqrt (ctx->m2xy[i][0] * ctx->m2xy[i][0] +
                         ctx->m2xy[i][1] * ctx->m2xy[i][1]) / AS2R ;
        if (currTilt[i] > maxTilt) {
            status = 1;
            strcpy(errMess, "tcsConfigM2Scan: M2 tilt exceeded");
            DBGMSG(DBG_FULL, mess);
            return status;
        }
 
        DBGMSG(DBG_FULL, mess);

    }

/* Calculate chop throw. This is either the difference of the B & C scan
*  demands (for three position chopping) or the difference of the A & B
*  scan demands (for two position chopping )
*/
    if ( posn > 1 ) {
      if ( posn == 3 )
        currThrow = currTilt[1] - currTilt[2];
      else
        currThrow = currTilt[1] - currTilt[0];

      if (currThrow < 0.0) currThrow = -currThrow;

/* Check limits */

      if (tcsOpticsCheckChopLimits (pTCB->sysconfig.chopmode.val,
                                    pTCB->sysconfig.chopfreq.val,
                                    currThrow, &freqLimit, &throwLimit,
                                    errMess)) {
        printf ("Limit check failed in M2Scan\n") ;
        status = 1;
      }
    }

    return status;
}
epicsRegisterFunction(tcsConfigBegin);
epicsRegisterFunction(tcsConfigEnd);
epicsRegisterFunction(tcsConfigSeqCheck);


static const iocshArg tcsSaveFilePrefixArg0 = {"saveFilePrefix", iocshArgString };

static const iocshArg *tcsSaveFilePrefixArgs[] = { &tcsSaveFilePrefixArg0 };

static const iocshFuncDef tcsSaveFilePrefixFuncDef =
         {"tcsConfigSetFilePrefix", 1, tcsSaveFilePrefixArgs};

	 
static void tcsSaveFilePrefixCallFunc(const iocshArgBuf *args)
{
   tcsConfigSetFilePrefix(args[0].sval);
}

static void registerTcsSaveFilePrefixCommands(void)
{
      iocshRegister(&tcsSaveFilePrefixFuncDef, tcsSaveFilePrefixCallFunc);
}
epicsExportRegistrar(registerTcsSaveFilePrefixCommands);
