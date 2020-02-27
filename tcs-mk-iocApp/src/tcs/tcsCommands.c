/*
 *   FILENAME
 *   tcsCommands.c
 *
 *   FUNCTION NAME(S)
 *   tcsCADabortAll     - stops movement in all telescope systems
 *   tcsCADairmassLimit - AirmassLimit CAD routine
 *   tcsCADazwrap       - azwrap CAD record subroutine
 *   tcsCADcarouselMode - set enclosure operating mode
 *   tcsCADclipAtLimit  - ClipAtLimits CAD routine
 *   tcsCADconfigureForAO - configure TCS for AO use
 *   tcsCADdebug        - set debug level in TCS and subsystems
 *   tcsCADfilter1      - Set source filter
 *   tcsCADfilter2      - Set pointing filter
 *   tcsCADfocusTempAdj - turn on/off temperature compensation of focus
 *   tcsCADfollow       - follow CAD
 *   tcsCADgenericCad   - CAD routine with no parameters
 *   tcsCADgsaoiodgwSetup - Setup parameters for ODGW
 *   tcsCADguiderConfig - configure generic virtual guiders
 *   tcsCADload         - load a configuration
 *   tcsCADmountGuideMode - set guide mode for mount
 *   tcsCADm1FigUpdates - set open loop figure corrections on/off
 *   tcsCADm1GuideMode  - set guide mode for M1
 *   tcsCADm1GuideConfig - set guide parameters for M1
 *   tcsCADm1ModelRestore - choose to restore M1 model from file on startup 
 *   tcsCADm2ComaCorr    - turn on/off coma corrections
 *   tcsCADm2NomPosn     - set nominal position for M2 coma tilt model
 *   tcsCADm2ComaModel   - set the coefficients of the M2 coma tilt model
 *   tcsCADm2GuidetcsMode  - m2GuideMode CAD routine
 *   tcsCADodgwDatum    - dummy command to "datum" the ODGW
 *   tcsCADodgwFollow   - set follow mode for the ODGW
 *   tcsCADodgwMove     - move the ODGW at a fixed position
 *   tcsCADodgwPark     - "park" the ODGW in the corners of the array
 *   tcsCADoiwfsSelect   - select a particular OIWFS
 *   tcsCADoptPointAdj - adjust pointing for optics movements
 *   tcsCADorbit        - Set orbital elements
 *   tcsCADplanet       - Set planet
 *   tcsCADpointParam   - Sets pointing model parameter
 *   tcsCADtimeParam    - Sets time sysytem parameter
 *   tcsCADprobeFocus   - apply a focus offset to a WFS probe
 *   tcsCADrotator      - rotator CAD subroutine
 *   tcsCADrotGuideConfig - configure rotator guide parameters
 *   tcsCADrotGuideMode - turn rotator guiding on or off
 *   tcsCADrotwrap      - rotwrap CAD record subroutine
 *   tcsCADsave         - save a configuration
 *   tcsCADsetProbeLimits - set radial limits for WFS probes
 *   tcsCADstopAll      - stops movement in major telescope systems
 *   tcsCADtcbdefn      - set the TCB to current or preset
 *   tcsCADunfollowAll  - stop all mechanisms following
 *   tcsCADstopGuideAll - stop all mechanisms following
 *   tcsCADwfsGuideMode - wfsGuideMode CAD routine
 *   tcsSetwrap         - Set azimuth/rotator wrap value
 *   tcsCADzeroComaCorr - set coma corrections to zero
 *   tcsCADzeroFocusGuide - zeroFocusGuide CAD routine
 *   tcsCADzeroRotGuide - zero the current rotator guide corrections
 *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsCommands.c,v $
 * Revision 1.62  2015/08/12 16:14:09  gemvx
 * Added command to stop guiding.
 *
 * Revision 1.61  2015/08/07 20:00:45  gemvx
 * Added parameter for brakes to stopAll and abortAll.
 *
 * Revision 1.60  2015/05/18 09:33:34  cjm
 * Add subroutines for unfollowAll, stopAll & abortAll
 *
 * Revision 1.59  2014/10/01 16:28:13  cjm
 * Add logging of some commands
 *
 * Revision 1.58  2013/10/15 12:23:56  cjm
 * Call SetM1save rather than SetM1Restore when setting file to save
 *
 * Revision 1.57  2013/09/11 15:41:00  cjm
 * Add code for m1ModelSave, update m1ModelRestore
 *
 * Revision 1.56  2012/10/04 15:37:07  cjm
 * Add check on modle restore that file is valid
 *
 * Revision 1.55  2012/10/04 13:32:07  cjm
 * Updates to support save/restore of AO specific M1 models
 *
 * Revision 1.54  2012/10/01 15:53:08  cjm
 * Fix bug that was causing filename to be ignored
 *
 * Revision 1.53  2012/05/08 09:42:52  cjm
 * Store AO configuration in TCB
 *
 * Revision 1.52  2012/03/11 02:29:50  gemvx
 * Fixed bug in tcsRotatorGuide, added new ODGW sizes.
 *
 * Revision 1.51  2011/01/26 16:04:37  gemvx
 * Made it compliant with GSAOI implementated interface for ODGW read mode and output parameters.
 *
 * Revision 1.50  2010/12/03 14:01:49  cjm
 * Fix some comments
 *
 * Revision 1.49  2010/11/29 14:14:42  cjm
 * New command to move, park and datum the ODGW
 *
 * Revision 1.48  2010/05/27 07:31:09  cjm
 * Add tcsCADodgwFollow
 *
 * Revision 1.47  2010/02/26 18:49:23  gemvx
 * Modified gsaoisetup to interface to latest GSAOI commands
 *
 * Revision 1.46  2009/12/01 13:35:50  cjm
 * Add gsaoiodgwSetup command
 *
 * Revision 1.45  2009/10/30 17:16:59  cjm
 * add new commands to control rotator guiding
 *
 * Revision 1.44  2009/08/19 09:38:24  cjm
 * Reversion to r1.42, r1.43 changes removed
 *
 * Revision 1.42  2008/10/07 12:25:06  cjm
 * Retain iaa in FIXED mode
 *
 * Revision 1.41  2008/05/01 15:21:39  cjm
 * Store follow state of peripheral guide probe
 *
 * Revision 1.40  2007/12/18 10:32:51  cjm
 * New commands for new guiders
 *
 * Revision 1.39  2007/11/13 12:47:29  gemvx
 *  changed so that NICI is properly configured in the pixed router (OIWFS selection)
 *
 * Revision 1.38  2007/01/09 14:03:14  cjm
 * Enhance the orbit command for guiders
 *
 * Revision 1.37  2006/11/24 10:19:58  cjm
 * New command configureForAO
 *
 * Revision 1.36  2006/04/21 10:51:13  cjm
 * Add oiwfsSelect and update wfsGuideMode
 *
 * Revision 1.35  2005/11/16 15:26:36  cjm
 * Allow OIWFS probe guiding in wfsGuideMode command
 *
 * Revision 1.34  2005/10/20 15:12:31  cjm
 * Add EPHEMERIS to switch statement to avoid compiler warnings
 *
 * Revision 1.33  2004/07/21 11:10:35  cjm
 * Allow range of -360 to +360 as per FR2953
 *
 * Revision 1.32  2003/07/09 10:53:45  cjm
 * Add code for m1Modelrestore command
 *
 * Revision 1.31  2003/02/13 11:02:01  cjm
 * Add test for file existence in m1GuideConfig
 *
 * Revision 1.30  2002/10/04 14:27:35  cjm
 * Add option to take ao data from Altair
 *
 * Revision 1.29  2002/08/02 15:29:57  cjm
 * Add code to support HRWFS as a source of ao data
 *
 * Revision 1.28  2002/06/06 07:55:59  cjm
 * Fix bug that orbit command wrote name to j not valj
 *
 * Revision 1.27  2002/02/22 10:45:19  cjm
 * Implement focusTempAdj command
 *
 * Revision 1.26  2002/02/20 15:50:14  dlt
 * Improve TT handling
 *
 * Revision 1.25  2001/09/02 15:08:13  cjm
 * Rework m1GuideConfig command
 *
 * Revision 1.24  2001/05/24 10:18:57  cjm
 * Remove subcad include and use new menuDirective constants
 *
 * Revision 1.23  2001/05/05 23:59:02  cjm
 * Reorganise to eliminate warnings
 *
 * Revision 1.22  2000/11/24 10:00:01  cjm
 * Set weights to zero when wfs guiding is switched off
 *
 * Revision 1.21  2000/07/19 00:09:39  dlt
 * Implement new pointing model implementation
 *
 * Revision 1.20  2000/04/20 09:49:28  dlt
 * Implement guiding of wfs probes
 *
 * Revision 1.19  2000/03/25 01:07:15  cjm
 * Rewrite setProbeLimits command to cope with change to two separate commands one for each probe
 *
 * Revision 1.18  2000/03/21 22:51:00  cjm
 * If mountGuideMode is being switched off don't check the remaining parameters
 *
 * Revision 1.17  2000/01/29 23:53:51  cjm
 * Add command zeroComaCorr
 *
 * Revision 1.16  2000/01/26 05:57:40  cjm
 * Rewrite CADfollow routine now that eacg subsystem has its own command to start/stop following
 *
 * Revision 1.15  1999/12/16 16:29:53  cjm
 * Change fourth parameter of m1GuideConfig from an update interval to a number of frames to average
 *
 * Revision 1.14  1999/06/16 21:27:28  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.13  1999/05/29 08:12:24  dlt
 * Move tf to genertic parameters
 *
 * Revision 1.12  1999/05/11 00:39:10  cjm
 * Allow for strings PAR0 to PAR19 in pointParam command
 *
 * Revision 1.11  1999/03/22 22:01:03  dlt
 * print longs with %ld and fix compiler warnings
 *
 * Revision 1.10  1999/03/16 01:02:48  dlt
 * Remove all but CA & CE from local pointing model
 *
 * Revision 1.9  1999/03/12 09:41:25  cjm
 * New CAD routines for m2ComaCorr, m2NomPosn and m2ComaModel
 *
 * Revision 1.8  1999/03/10 21:45:50  cjm
 * Add tcsCADM1FigUpdates routine
 *
 * Revision 1.7  1999/01/24 00:43:43  dlt
 * Implement guiding from A & G
 *
 * Revision 1.6  1999/01/05 16:45:32  epics
 * Add routines tcsCADm1GuideMode and tcsCADm1GuideConfig
 *
 * Revision 1.5  1998/12/07 11:22:53  epics
 * Use dmod macro in place of fmod
 *
 * Revision 1.4  1998/11/20 02:25:27  dlt
 * Implement timeParam CAD
 *
 * Revision 1.3  1998/11/16 18:35:43  cjm
 * Fix bug that slit height was checked even when shutter mode was fully open
 *
 * Revision 1.2  1998/11/14 00:15:57  dlt
 * Add IA and IE to pointing model
 *
 * Revision 1.1.1.1  1998/11/08 00:21:04  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.37  1998/10/26 13:17:20  tcs
 * Add code for tcsCADprobeFocus
 *
 * Revision 1.36  1998/09/05 03:26:31  tcs
 * Add code to support setProbeLimits command
 *
 * Revision 1.35  1998/06/08 09:55:55  tcs
 * Allow YES & NO for followS strings to accommodate SCS
 *
 * Revision 1.34  1998/01/13 11:52:11  tcs
 * Change names of CAD subroutines
 *
 * Revision 1.33  1998/01/12 16:23:12  tcs
 * Change CAD subroutine names to tcsCADxxxx
 *
 * Revision 1.32  1998/01/08 16:40:02  cjm
 * Add mountGuideMode command
 *
 * Revision 1.31  1997/12/08 10:01:58  cjm
 * Implement optPointAdj command
 *
 * Revision 1.30  1997/11/24 11:53:42  tcs
 * Correct type of rotator outputs
 *
 * Revision 1.29  1997/11/21 14:59:16  cjm
 * add diagnostics to test software timing requirements
 *
 * Revision 1.28  1997/11/20 12:35:41  pbt
 * Add call to tcsConfigMarkComm for *all* CADs
 *
 * Revision 1.27  1997/11/19 16:08:14  tcs
 * Fix typos
 *
 * Revision 1.26  1997/11/19 10:11:09  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.25  1997/11/18 08:28:01  cjm
 * Add commands m2guideMode and zeroFocusGuide
 *
 * Revision 1.24  1997/11/05 11:36:33  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.23  1997/10/31 14:45:25  tcs
 * Add instrument angle to rotator CAD
 *
 * Revision 1.22  1997/10/31 09:32:36  tcs
 * Revise filter defaults
 *
 * Revision 1.21  1997/10/09 15:47:17  tcs
 * add object name to planet and orbit CADs
 *
 * Revision 1.20  1997/10/09 12:51:08  tcs
 * Drive sad from kernel instead of CAD
 *
 * Revision 1.19  1997/10/03 15:56:11  pbt
 * Output long type values from tcsCarouselMode command
 *
 * Revision 1.18  1997/09/24 16:34:41  pbt
 * Added tcsFollowString routine to handle subsystem Follow status
 *
 * Revision 1.17  1997/09/24 07:15:31  cjm
 * Add extra outputs to airmass CAD
 *
 * Revision 1.16  1997/09/16 11:08:53  cjm
 * Ensure slit height is set even when fully open
 *
 * Revision 1.15  1997/09/12 12:58:18  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.14  1997/09/12 10:07:13  tcs
 * add tcs prefix to all cad routines
 *
 * Revision 1.13  1997/09/11 16:13:24  tcs
 * Add clipAtLimits support
 *
 * Revision 1.12  1997/09/10 16:55:43  tcs
 * Create routine for CADs with no parameters
 *
 * Revision 1.11  1997/09/08 14:00:58  tcs
 * Add airmassLimit CAD
 *
 * Revision 1.10  1997/09/05 16:41:44  cjm
 * Use correct routine to decode shutter modes
 *
 * Revision 1.9  1997/08/21 10:41:22  tcs
 * Add pointLog CAD
 *
 * Revision 1.8  1997/08/11 15:41:21  tcs
 * Add CAD for setting pointing parameters
 *
 * Revision 1.7  1997/07/25 16:43:54  cjm
 * Add tcsCarouselMode to support CAD coomand
 *
 * Revision 1.6  1997/07/23 13:33:18  cjm
 * Fix bug in debug command
 *
 * Revision 1.5  1997/06/25 12:57:09  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.4  1997/05/16 12:21:36  tcs
 * make consistent use of frame/wavel/eqx
 *
 * Revision 1.3  1997/05/07 10:26:38  tcs
 * Implement target to current filter
 *
 * Revision 1.2  1997/03/05 09:36:55  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:20  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.49  1997/02/05 11:00:45  tcs
 * Correct setting of CAD output links
 *
 * Revision 1.48  1997/01/24 14:25:07  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.47  1997/01/23 10:45:26  tcs
 * Change epoch type to char
 *
 * Revision 1.46  1996/12/13 13:24:49  tcs
 * replace tcsLibrary with tcsDecode routines
 *
 * Revision 1.45  1996/12/13 10:07:43  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.44  1996/12/12 16:57:00  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.43  1996/12/06 15:17:08  pbt
 * CAD subroutine and associated decode routine for CAD Follow
 *
 * Revision 1.42  1996/12/05 13:12:06  tcs
 * rename initial state to catch up
 *
 * Revision 1.41  1996/12/04 10:00:15  cjm
 * Fix bug in if statement in setfilter
 *
 * Revision 1.40  1996/12/03 16:55:19  tcs
 * New filter parameter names
 *
 * Revision 1.39  1996/12/02 11:13:36  tcs
 * Implement rotator tracking frame
 *
 * Revision 1.38  1996/11/29 08:28:46  cjm
 * Add support for debug command
 *
 * Revision 1.37  1996/11/28 08:10:51  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.36  1996/11/26 15:24:43  tcs
 * Add filter commands and remove source
 *
 * Revision 1.35  1996/11/13 14:38:48  tcs
 * Add rotator CAD
 *
 * Revision 1.34  1996/11/13 10:57:30  tcs
 * remove TCB parameter from wrap commands
 *
 * Revision 1.33  1996/10/22 15:59:39  tcs
 * Add configuration offset commands
 *
 * Revision 1.32  1996/10/08 14:01:29  tcs
 * Add CADs for all 13 VTs & remove guide1 and target
 *
 * Revision 1.31  1996/10/07 07:10:44  cjm
 * Support 13 VTs for both preset and current targets
 *
 * Revision 1.30  1996/10/04 08:07:59  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.29  1996/09/11 13:40:46  tcs
 * Change azimuth wrap limits to -180/+360
 *
 * Revision 1.28  1996/09/09 15:24:41  tcs
 * Change topo az limits to 0-360 plus derive az wrap flag from mount az
 *
 * Revision 1.27  1996/09/05 16:00:28  pbt
 * Added save,load, azwrap and rotwrap commands. Added setting of
 * CAD input field data for later use by LOAD etc.
 *
 * Revision 1.26  1996/08/02 08:38:51  tcs
 * fix equinox for sourceS and guide1
 *
 * Revision 1.25  1996/08/01 14:45:30  cjm
 * Improve range checking, remove diagnostics
 *
 * Revision 1.24  1996/08/01 13:12:28  tcs
 * revised offset code
 *
 * Revision 1.23  1996/08/01 08:02:14  tcs
 * correct use of epoch for proper motion
 *
 * Revision 1.22  1996/07/31 16:40:08  tcs
 * change units of differential tracking
 *
 * Revision 1.21  1996/07/31 07:26:38  cjm
 * Addition of guide1 command
 *
 * Revision 1.20  1996/07/26 07:45:47  cjm
 * Set guide targets to same as mount target
 *
 * Revision 1.19  1996/07/25 12:51:06  cjm
 * Modifications to support data passing via TCBs
 *
 * Revision 1.18  1996/07/24 07:36:32  cjm
 * Add targetS, rework source, offset and remove sequence commands
 *
 * Revision 1.17  1996/07/19 15:34:42  cjm
 * Modifications for handling of configurations
 *
 * Revision 1.16  1996/07/19 11:32:47  pbt
 * Added test and observe command (trivial) routines
 *
 * Revision 1.15  1996/07/18 14:49:51  pbt
 * Changed sequence command subroutine names to be the same as the the CAD records
 *
 * Revision 1.14  1996/07/17 16:19:10  cjm
 * Check for valid configuration in init & reset
 *
 * Revision 1.13  1996/07/17 14:29:46  pbt
 * Changed Source routine name : now called source
 *
 * Revision 1.12  1996/07/15 07:38:05  cjm
 * Check configuration when preset received
 *
 * Revision 1.11  1996/07/09 15:27:05  tcs
 * Implement azimuth and rotator wrap control
 *
 * Revision 1.10  1996/06/24 14:22:50  tcs
 * generate azimuth and rotator angles in range -270/+270
 *
 * Revision 1.9  1996/06/24 10:32:57  tcs
 * remove debug output
 *
 * Revision 1.8  1996/06/21 15:49:14  cjm
 * Add init and reset commands
 *
 * Revision 1.7  1996/06/21 13:50:14  tcs
 * elevation limit and MOVE logic changes
 *
 * Revision 1.6  1996/06/10 21:11:15  cjm
 * Use function templates and add code for reset and init
 *
 */
/* *INDENT-ON* */

#include <epicsStdlib.h>
#include <stdio.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <iocsh.h>
#include <epicsExport.h>
#include  <string.h>
#include  <dbDefs.h>
#include  <cadRecord.h>
#include  <genSubRecord.h>
#include  <subRecord.h>
#include  <cad.h>
#include  <epicsThread.h>
#include  "tcsConstants.h"
#include  "timeLib.h"
#include  "tcsConstants.h"
#include  "tcsCommands.h"
#include  "tcsConfig.h"
#include  "slalib.h"
#include  "slamac.h"
#include  "tcsPointing.h"
#include  "tcsInterlocks.h"
#include  "tcsDecode.h"
#include  "tcsCadSupport.h"
#include  "tcsEcsLib.h"
#include  "tcsOptics.h"
#include  "tcsProbeLib.h"
#include  "tcsGuide.h"
#include  "tcsLogSupport.h"


/*+
 *   Function name:
 *   tcsCADfocusTempAdj
 *
 *   Purpose:
 *   Control whether the focus is adjusted for temperature changes 
 *
 *   Description:
 *   This command somply turns on and off the model that adjusts the 
 *   secondary mirror position for temperature changes.
 *
 *   Invocation:
 *   tcsCADfocusTempAdj (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => On or Off 
 *
 *   EPICS output parameters:
 *      vala => On or Off 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetFocusFlag  (tcsOptics) Store flag 
 *
 *-
 */

long tcsCADfocusTempAdj (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int flag;        /* 0 = Off, 1 = On */

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
    if (tcsDcOnOff ("flag: ", pcad->a, &flag, pcad))
      break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    tcsOpticsSetFocusFlag (flag) ;
    
    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);

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
 *   tcsCADoptPointAdj
 *
 *   Purpose:
 *   Control whether pointing adjustments are made when optics are moved
 *
 *   Description:
 *   For test purposes it will sometimes be necessary to adjust the 
 *   optics i.e. M1 and M2 away from their best alignment position. When
 *   this is done the image will shift. This command controls whether
 *   or not compensating pointing adjustments are made so that the image 
 *   will remain on the pointing origin.
 *
 *   Invocation:
 *   tcsCADoptPointAdj (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Flag, On or Off 
 *
 *   EPICS output parameters:
 *      vala => On or Off 
 *      valb => 1 or 0
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetPointFlag  (tcsOptics) Store flag 
 *
 *-
 */

long tcsCADoptPointAdj (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int flag;        /* 0 = Off, 1 = On */

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
    if (tcsDcOnOff ("flag: ", pcad->a, &flag, pcad))
      break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    tcsOpticsSetPointFlag (flag) ;
    
    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
    *(long *)pcad->valb = flag ;

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
 *   tcsCADsetProbeLimits
 *
 *   Purpose:
 *   Set user limits for allowed radial range of PWFS's
 *
 *   Description:
 *   Physically the PWFS's can move fully to the centre of the field. They
 *   can also move into areas where there is partial vignetting. This 
 *   command allows a user to set radial limits such that the telescope
 *   will not try to drive the guide probes outside the limits set. The 
 *   limits are checked for validity as well as for consistency with the
 *   physical limits held by the A&G.
 *
 *   Invocation:
 *   tcsCADsetProbeLimits (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Requested lower radial limit for WFS (mm)
 *      b => Requested upper radial limit for WFS (mm)
 *
 *   EPICS output parameters:
 *      vala => Lower radial limit for WFS (mm) 
 *      valb => Upper radial limit for WFS (mm) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsProbeSetRLimits  (tcsProbeLib) Set user limits for probe movement
 *   tcsProbeCheckRadii  (tcsProbeLib) Check users radial limits. 
 *
 *-
 */

long tcsCADsetProbeLimits (struct cadRecord *pcad)

{

  long status ;           /* Return status */

  static double rmin1 ;   /* User requested min. radius for pwfs1 */
  static double rmax1 ;   /* User requested max. radius for pwfs1 */
  static int probe ;      /* Index to probe */

  char mess[80] ;         /* Message */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  if (!strcmp(tcsCsCadName(pcad), "pwfs1RLimits")) {
    probe = 0 ;
  } else if (!strcmp(tcsCsCadName(pcad), "pwfs2RLimits")) {
    probe = 1 ;
  } else {
    status = CAD_REJECT ;
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), 
                           "Unknown command", (char *) NULL ) ;
    return status ; 
  }

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

    status = CAD_REJECT ;
    if (tcsDcDouble ("rmin: ", pcad->a, &rmin1, pcad))
      break ;

    if (rmin1 < 0.0) {
      tcsCsAppendMessage (pcad, "min. radius < 0.0");
      break ;
    }

    if (tcsDcDouble ("rmax: ", pcad->b, &rmax1, pcad))
      break ;

    if (rmax1 < 0.0) {
      tcsCsAppendMessage (pcad, "max. radius < 0.0");
      break ;
    }

    if (rmin1 >= rmax1) {
      tcsCsAppendMessage (pcad, "min > max radius") ;
      break ;
    }

/* Now check the user limits against the physical probe limits */

   if (tcsProbeCheckRadii (probe, rmin1, rmax1, mess)) {
     tcsCsAppendMessage (pcad, mess) ;
     break ;
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    tcsProbeSetRLimits (probe, rmin1, rmax1) ; 
    
    *(double *)pcad->vala = rmin1 ;
    *(double *)pcad->valb = rmax1 ;

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
 *   tcsCADconfigureForAO
 *
 *   Purpose:
 *   Set up TCS for use with AO
 *
 *   Description:
 *   This command configures the TCS for use with or without AO. If
 *   not configured for AO the TCS does not use the health, inPosition
 *   or CAR status of the AO system when computing its own overall state
 *   and the virtual guider is set to control P2.
 *
 *   Invocation:
 *   tcsCADconfigureForAO (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Yes or No 
 *
 *   EPICS output parameters:
 *      vala => Yes or No
 *      valb => config flag (1 = configured for AO) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsProbeSetAOConfig  (tcsProbeLib) Store flag 
 *
 *-
 */

long tcsCADconfigureForAO (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int flag;        /* 0 = No, 1 = Yes */
  char *confignames[] = { "NO", "YES", NULL };
  static struct ICAD_FIELD aostruct;

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
    if (tcsDcString (confignames, "flag: ", pcad->a, &flag, pcad))
       break;

   if (tcsConfigMarkComm (pcad->name, pcad->mess)) break ;
   aostruct.val = flag;
   aostruct.field = 'A';
   strncpy(aostruct.instring, pcad->a, MAX_STRING_SIZE);
  
   tcsConfigSetAOConfiguration(&aostruct);

   status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    tcsProbeSetAOConfig (flag) ;
    
    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
    *(long *)pcad->valb = flag;

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
 *   tcsCADmountGuideMode
 *
 *   Purpose:
 *   Set guide mode for mount control system
 *
 *   Description:
 *   This routine implements the mountGuideMode command in the TCS. The
 *   routine checks the input parameters for validity and if valid, returns
 *   an OK status. If after this the command receives a START directive
 *   the parameters are sent to the EPICS outputs so that they are
 *   are available to the rest of the database.
 *
 *   Invocation:
 *   tcsCADmountGuideMode
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => absorb tip/tilt errors (On/Off) 
 *      b => guide source (SCS/AG)
 *      c => pwfs1 weight
 *      d => pwfs2 weight
 *
 *   EPICS output parameters:
 *      vala => absorb tip/tilt status (On/Off) 
 *      valb => guide source (SCS/AG)
 *      valc => normalized pwfs1 weight
 *      vald => normalized pwfs2 weight
 *      vale => scan mask, 3 = use M2 tip/tilt, 4 = use A&G, 0 = Off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADmountGuideMode (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int flag ;       /* 1 = enabled, 0 = disabled */
  char *sourcenames[] = { "SCS", "AG", NULL };
  static int source;
  static double pwfs1w, pwfs2w;
  double w;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

/* In the PRESET stage the CAD inputs must all be checked for validity. Note
*  that any values derived from the inputs which are also required at the
*  menuDirectiveSTART stage must be declared static.
*/

   case menuDirectivePRESET :

   status = CAD_REJECT ;
   if (tcsDcOnOff ("flag: ", pcad->a, &flag, pcad))
      break ;

/* Its only necessary to check the remaining parameters if we are
*  switching on the guide mode
*/
   if (flag) {
     if (tcsDcString (sourcenames, "source: ", pcad->b, &source, pcad))
        break;
     if (tcsDcDouble ("pwfs1 weight:", pcad->c, &pwfs1w, pcad))
        break;
     if ( pwfs1w < 0.0 ) {
        tcsCsAppendMessage(pcad, "weight 1 less than 0.0");
        break;
     }
     if ( pwfs2w < 0.0 ) {
        tcsCsAppendMessage(pcad, "weight 2 less than 0.0");
        break;
     }
     if (tcsDcDouble ("pwfs2 weight:", pcad->d, &pwfs2w, pcad))
        break;

/* Normalise wieghts. */
     if ( pwfs1w + pwfs2w == 0.0 ) {
        pwfs1w = pwfs2w = 0.5;
     } else {
        w = pwfs1w + pwfs2w;
        pwfs1w /= w;
        pwfs2w /= w;
     }
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
 
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    *(long *)pcad->vale = 0 ;
    if ( flag ) {
       if ( source == 0 ) {
          *(long *)pcad->vale = 3 ;
       } else if ( source == 1 ) {
          *(long *)pcad->vale = 4 ;
       }
      strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE);
      *(double *) pcad->valc = pwfs1w;
      *(double *) pcad->vald = pwfs2w;
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
 *   tcsCADcarouselMode
 *
 *   Purpose:
 *   Sets the operating mode for control of the enclosure
 *
 *   Description:
 *   This routine sets the operating mode that the TCS will use to control
 *   the enclosure dome and shutters. On the preset directive, all 
 *   parameters input to the CAD are validated. On the start directive
 *   the data is copied into memory to be used by the drive routines
 *   that are controlling the dome and shutters.
 *   The two parameters that control the sending of move commands to the 
 *   ECS are present to allow operation of the telescope without opening
 *   the shutters or moving the dome.
 *
 *   Invocation:
 *   tcsCADcarouselMode (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Positioning mode Simple, MinVibration or MinScatter
 *      b => Shutter mode FullyOpen or Tracking
 *      c => slit height (mm) only relevant in Tracking mode
 *      d => automatic move_dome commands On or Off
 *      e => automatic move_shtrs commands On or Off 
 *
 *   EPICS output parameters:
 *      vala => Positioning mode
 *      valb => Shutter mode
 *      valc => slit height (mm)
 *      vald => automatic move_dome commands
 *      vale => automatic move_shtrs comands 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsGetUserParams   (tcsEcsLib)  Fetch current ECS user parameters
 *   tcsEcsGetParamDefs    (tcsEcsLib)  Fetch current ECS parameters
 *   tcsEcsCheckParams     (tcsEcsLib)  Check ECS parameters for consistency
 *   tcsEcsSetIssueMoves   (tcsEcsLib)  Send moves or follows to ECS
 *   tcsEcsEnableShtrs     (tcsEcsLib)  Enable/disable driving shutters
 *   tcsEcsEnableDome      (tcsEcsLib)  Enable/disable driving dome
 *   tcsEcsSetUserParams   (tcsEcsLib)  Set ECS user parameters
 *   tcsDcEncMode          (tcsDecode)  Decode/validate enclosure mode
 *   tcsDcShtrMode         (tcsDecode)  Decode/validate shutter mode
 *   tcsDcDouble           (tcsDecode)  Decode/validate a string as a double
 *
 *-
 */

long tcsCADcarouselMode (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static int autoMoveDome;    /* Flag to control sending of moves to dome */
  static int autoMoveShtrs;   /* Flag to control sending of moves to shtrs */
  static double slitHeight;   /* Slit height in mm */
  static char encModeStr[20];  /* String representing the enclosure mode */
  static char shtrModeStr[20]; /* String describing shutter mode */
  static ENCMODE encMode;      /* Enclosure mode */
  static SHUTTERMODE shtrMode; /* Shutter mode */ 
  double encRadius ;           /* Enclosure radius */
  double entranceAp;           /* Entrance aperture (mm) */
  double slitWidth ;           /* Slit width (mm) */
  double minSlitHeight ;       /* Minimum slit height (mm) */
  double minScatWidth ;        /* Adjustment for minimum scatter (mm) */
  double fieldRadius ;         /* Field radius (arcmin) */
  ENCMODE currEncMode ;        /* Current enclosure mode */
  SHUTTERMODE currShtrMode;    /* Current shutter mode */
  char mess[40] ;              /* message string */

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

/* Pull in and validate the data on the CAD input fields */

     if (tcsDcEncMode ("Enc mode: ", pcad->a, &encMode, pcad))
       break ;

     switch (encMode) {

     case BASIC:
        strcpy(encModeStr, "Basic") ;
        break ;
     case MINVIBRATION:
        strcpy(encModeStr, "Minimum Vibration");
        break ;
     case MINSCATTER:
        strcpy (encModeStr, "Minimum Scatter");
        break ;
     }

     if (tcsDcShtrMode ("Shtr mode: ", pcad->b, &shtrMode, pcad)) 
       break ;

     switch (shtrMode) {

     case FULLYOPEN:
        strcpy (shtrModeStr, "Fully Open") ;
        break ;
     case TRACKING:
        strcpy (shtrModeStr, "Tracking") ;
        break ;
     }

/* Fetch current parameters defining the enclosure operating mode */

     tcsEcsGetParamDefs (&encRadius, &slitWidth, &entranceAp, &minScatWidth,
                         &minSlitHeight, &fieldRadius) ;
     tcsEcsGetUserParams (&currEncMode, &currShtrMode, &slitHeight );

/* Over ride the current slit height if shutter mode is tracking */

     if (shtrMode == TRACKING) {
       if (tcsDcDouble("height: ", pcad->c, &slitHeight, pcad))
           break ;
     }

/* Check new set of enclosure parameters for consistency */

     if (tcsEcsCheckParams (encMode, shtrMode, slitHeight, slitWidth, encRadius,
                            entranceAp, minScatWidth, fieldRadius, mess)) {
       tcsCsAppendMessage (pcad, mess);
       break ;
     }

     if (tcsDcOnOff ("Auto dome moves :", pcad->d, &autoMoveDome, pcad))
       break ;

     if (tcsDcOnOff ("Auto shtr moves: ", pcad->e, &autoMoveShtrs, pcad))
       break ;
     
     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

/* Set the flag that says we want to issue moves rather than follows to the 
*  ECS.
*/
 
      tcsEcsSetIssueMoves (TRUE) ;

/* Set the flags that determine whether automatic moves or follows are 
*  to be sent to the dome and shutters 
*/

      tcsEcsEnableShtrs (autoMoveShtrs) ;
      tcsEcsEnableDome (autoMoveDome );

/* Store the remaining user supplied data */

      tcsEcsSetUserParams (encMode, shtrMode, slitHeight) ;

/* Copy the validated input data to the output */

      strcpy (pcad->vala, encModeStr) ;
      strcpy (pcad->valb, shtrModeStr) ;
      strcpy (pcad->valc, pcad->c ) ;
      *(long *) pcad->vald = (long)autoMoveDome ;
      *(long *) pcad->vale = (long)autoMoveShtrs ;

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



/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADdebug
 *
 *   Purpose:
 *   Set debug level in TCS and subsystems
 *
 *   Description:
 *   This routine is tied to the debug CAD record. It simply checks the
 *   debug levels specified for the TCS and each of its subsystems and
 *   if they are valid, sets them to the requested values. 
 *
 *   Invocation:
 *   tcsCADdebug (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input fields :
 *
 *   a => TCS debug level
 *   b => MCS debug level
 *   c => CRS debug level
 *   d => ECS debug level
 *   e => A&G debug level
 *   f => M2  debug level
 *   g => PCS debug level
 *   h => AO  debug level
 *
 *   EPICS Output fields :
 *
 *   vala => TCS debug level
 *   valb => MCS debug level
 *   valc => CRS debug level
 *   vald => ECS debug level
 *   vale => A&G debug level
 *   valf => M2  debug level
 *   valg => PCS debug level
 *   valh => AO  debug level
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDebug      (tcsDecode)    Check for valid debug level 
 *
 *
 *-
 */
/* *INDENT-ON* */

long tcsCADdebug(struct cadRecord *pcad)
{

   long status;                 /* Return status */
   int debugLevel;              /* Code for debug level */
   static int tcsDebugLevel;    /* Code for TCS debug level */
   static int oldTcsDebugLevel = DBG_NONE;
   static char tcsLevel[MAX_STRING_SIZE];       /* TCS debug level */
   static char mcLevel[MAX_STRING_SIZE];        /* MC debug level */
   static char crLevel[MAX_STRING_SIZE];        /* CR debug level */
   static char m1Level[MAX_STRING_SIZE];        /* M1 debug level */
   static char m2Level[MAX_STRING_SIZE];        /* M2 debug level */
   static char aoLevel[MAX_STRING_SIZE];        /* AO debug level */
   static char agLevel[MAX_STRING_SIZE];        /* AG debug level */
   static char ecLevel[MAX_STRING_SIZE];        /* EC debug level */

/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Decode each input field. Valid strings are NONE, MIN or FULL */

      if (tcsDcDebug("TCS: ", pcad->a, &tcsDebugLevel, tcsLevel, pcad))
         break;

      if (tcsDcDebug("MC: ", pcad->b, &debugLevel, mcLevel, pcad))
         break;

      if (tcsDcDebug("CR: ", pcad->c, &debugLevel, crLevel, pcad))
         break;

      if (tcsDcDebug("EC: ", pcad->d, &debugLevel, ecLevel, pcad))
         break;

      if (tcsDcDebug("AG: ", pcad->e, &debugLevel, agLevel, pcad))
         break;

      if (tcsDcDebug("M2: ", pcad->f, &debugLevel, m2Level, pcad))
         break;

      if (tcsDcDebug("M1: ", pcad->g, &debugLevel, m1Level, pcad))
         break;

      if (tcsDcDebug("AO: ", pcad->h, &debugLevel, aoLevel, pcad))
         break;

      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated data to the output links */

      strcpy(pcad->vala, tcsLevel);
      strcpy(pcad->valb, mcLevel);
      strcpy(pcad->valc, crLevel);
      strcpy(pcad->vald, ecLevel);
      strcpy(pcad->vale, agLevel);
      strcpy(pcad->valf, m2Level);
      strcpy(pcad->valg, m1Level);
      strcpy(pcad->valh, aoLevel);

/* As an example of logging at different debug levels. Log the setting of
   *  the TCS debug level itself 
 */

      if (oldTcsDebugLevel != tcsDebugLevel) {
         epicsPrintf("TCS: debug level set to %s\n", tcsLevel);
         oldTcsDebugLevel = tcsDebugLevel;
      }
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;
   }


   return status;
}

/*+
 *   Function name:
 *   tcsCADm1GuideConfig
 *
 *   Purpose:
 *   Implements the m1GuideConfig command in the TCS
 *
 *   Description:
 *   This routine sets the parameters that control how guiding data from
 *   the A&G is manipulated before being passed on to M1. The user can
 *   elect to simply average the data over a period of time or form a 
 *   weighted mean where the weights are proportional to the reciprocal
 *   of the squared error estimates. 
 *   The routine validates the inputs and if Ok stores them for use by the
 *   routines that perform the averaging.
 *   The name Altair option is retained for historical reasons and backwards
 *   compatibility. Both Gemini North and South should specify GAOS
 *
 *   Invocation:
 *   tcsCADm1GuideConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Weighting scheme, "None" or "Errors" 
 *      b => Source for data "PWFS1", "PWFS2", "OIWFS", "HRWFS", "Altair" or
 *           "GeMS", "GAOS"
 *      c => No. of WFS frames to average 
 *      d => Filename (only relevant for HRWFS)
 *
 *   EPICS output parameters:
 *      vala => Weighting scheme, "None" or "Errors" 
 *      valb => Source for data "PWFS1", "PWFS2", "OIWFS", "HRWFS", "Altair",
 *             "GeMS", "GAOS" 
 *      valc => No. of WFS frames to average 
 *      vald => Filename for HRWFS data
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
 *-
 */

long tcsCADm1GuideConfig (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static long numAoFrames ;   /* Number of WFS frames to average */
  static int weightIndex ;    /* Index for weight scheme */
  static int wfsIndex ;       /* Index for WFS source */
  M1WEIGHT weightScheme ;     /* Type of weighting to apply to aO data */
  static char *weightOpts[] = {"NONE", "ERRORS", NULL} ;
  static char *wfsOpts[] = {"PWFS1", "PWFS2", "OIWFS", "HRWFS", "ALTAIR", 
                            "GEMS", "GAOS", NULL} ;
  FILE *fp ;

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

   if (tcsDcString (weightOpts, " ", pcad->a, &weightIndex, pcad)) break ;
   if (tcsDcString (wfsOpts, " ", pcad->b, &wfsIndex, pcad)) break ;

/* If the option is HRWFS then there must be a filename as well. The data
*  will be read by a background sequence program but check if file is
*  accessible. It is not ideal doing this here due to the time it might
*  take.
*/
   if (wfsIndex == 3  ) {
     if (!tcsDcLen(pcad->d)) {
       tcsCsAppendMessage (pcad, "No file specified");
       break ;
     } else {
       if ((fp = fopen (pcad->d, "r"))) {
         fclose (fp);
       } else {
         tcsCsAppendMessage (pcad, "File not accessible");
         break ;
       }
     }
   }

/* Altair and GeMS are deprecated but if given, map to GAOS */
   if (wfsIndex == 4 || wfsIndex == 5)  wfsIndex = 6 ;

/* make sure a number of frames is specified */

   if (!tcsDcLen(pcad->c)) {
     tcsCsAppendMessage (pcad, "no frames specified") ;
     break ;
   }
   if (tcsDcLong ("Num. frames:", pcad->c, &numAoFrames, pcad) ) break ;
   if (numAoFrames < 1) {
     tcsCsAppendMessage (pcad, "Number of frames < 1") ;
     break ;
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     if (weightIndex == 0) 
       weightScheme = NOWEIGHTS ;
     else
       weightScheme = ERRORS ;

     tcsOpticsSetM1Guide (weightScheme, wfsIndex, numAoFrames) ;
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
     *(long *)pcad->valc = numAoFrames ;
     strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE);

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
 *   tcsCADm1FigUpdates
 *
 *   Purpose:
 *   Implements the m1FigUpdates command in the TCS
 *
 *   Description:
 *   The routine first validates the input data and if OK sets the
 *   the flag that controls whether the  open loop corrections to the
 *   M1 figure are enabled or disabled.
 *
 *   Invocation:
 *   tcsCADm1FigUpdates (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Figure corrections on/off
 *
 *   EPICS output parameters:
 *      vala => Figure corrections on/off
 *      valb => Flag to show if corrections are on (=1) or off (=0) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm1FigUpdates (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static int applyCorr ;     /* Apply corrections 1 = on, 0 = off */

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

/* Trap null or empty input as an error rather than defaulting to Off */
    if (!tcsDcLen(pcad->a)) {
      tcsCsAppendMessage (pcad, "Null or blank input") ;
      break ;
    }

    if (tcsDcOnOff ("Corrections :", pcad->a, &applyCorr, pcad))
      break ;

/* Check if a decision has been made on how to initialise the corrections */
    if (applyCorr) {
      if (!tcsOpticsM1ModelInit()) {
        tcsCsAppendMessage (pcad, "Zero or restore model first") ;
        break ;
      }
    }
/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     *(long *)pcad->valb = applyCorr ;

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
 *   tcsCADm1GuideMode
 *
 *   Purpose:
 *   Implements the m1GuideMode command in the TCS
 *
 *   Description:
 *   The routine first validates the input data and if OK sets the
 *   the flag that controls whether the guide loop to the PCS is open
 *   or closed. Guiding here means whether higher order Zernike corrections
 *   are sent periodically to M1.
 *
 *   Invocation:
 *   tcsCADm1GuideMode (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Zernike corrections on/off
 *
 *   EPICS output parameters:
 *      vala => Zernike corrections on/off
 *      valb => Flag to show if corrections are on (=1) or off (=0) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm1GuideMode (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static int applyZernikes ; /* Flag to control absorption of focus errors */

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

   status = CAD_REJECT ;

/* Trap null or empty input as an error rather than defaulting to Off */
    if (!tcsDcLen(pcad->a)) {
      tcsCsAppendMessage (pcad, "Null or blank input") ;
      break ;
    }

    if (tcsDcOnOff ("Apply Zern :", pcad->a, &applyZernikes, pcad))
      break ;

    if (applyZernikes) {
      if (!tcsOpticsM1ModelInit()) {
        tcsCsAppendMessage (pcad, "Zero or restore model first") ;
        break ;
      }
    }
/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     *(long *)pcad->valb = applyZernikes ;

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
 *   tcsCADm1ModelRestore
 *
 *   Purpose:
 *   Choose to restore M1 optics model from file
 *
 *   Description:
 *   This command selects reloading the M1 optics model from file
 *   after a reboot of the TCS. It sets a flag that is used later
 *   when the open loop model is turned on as well as initiating a
 *   pvload of the data. Since pvload requires file access that can
 *   be slow, the loading is actually done from a sequencer file.
 *   Originally this command took no parameters. Subsequently there
 *   was a requirement (from GeMS) that different models be kept
 *   and restored for working with AO or without AO and later
 *   still that a separate model be maintained for GPI. For backwards
 *   compatibility, if no parameter is specified the state of the 
 *   AO fold will be queried to determine which model to load.
 *
 *   Invocation:
 *   tcsCADm1ModelRestore (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  Which model to restore (AO, non-AO or GPI)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm1ModelRestore (struct cadRecord *pcad)

{

  char *opts[] = { "NON-AO", "AO", "GPI", NULL };
  long status ;              /* Return status */
  static int choice ;        /* Index for chosen file */
  int foldposn ;             /* Index of fold position */

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

/* If which file to restore is not specified check where the AO fold
 * is and decide from that. If the AO fold position can't be found
 * then reject and make the user make a decision
 */
  if (tcsDcNotEmpty(pcad->a)) {
    if (tcsDcString (opts, "file: ", pcad->a, &choice, pcad))
      break;
  } else {
    foldposn = tcsProbeGetAoFold();
    if (foldposn == 0) {
      choice = 0 ;
    } else if (foldposn == 1) {
      choice = 1;
    } else {
      tcsCsAppendMessage (pcad, "Choose AO or non-AO");
      break ;
    }
  }

/* Now check if, for the selected model there is in fact a valid file
 * available
 */
  if (!tcsOpticsGetM1ModelValid(choice)) {
    tcsCsAppendMessage(pcad, "No valid file available");
    break ; 
  }

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     tcsOpticsSetM1Restore(choice) ;
     strcpy(pcad->vala, pcad->a);

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
 *   tcsCADm1ModelSave
 *
 *   Purpose:
 *   Set which M1 model is to be saved 
 *
 *   Description:
 *   Originally the m1 model to be saved was set by the state of the
 *   AO fold. If the fold was in then the M1 data was saved to a file
 *   reserved for AO whereas if the fold was out it was saved to a file
 *   reserved for non-AO work. The GPI does not fit into this scheme
 *   so this command was introduced to explicitly set the file the
 *   m1 data is to be saved to.
 *
 *   Invocation:
 *   tcsCADm1ModelSave (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  Which model to save (AO, non-AO or GPI)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm1ModelSave (struct cadRecord *pcad)

{

  char *opts[] = { "NON-AO", "AO", "GPI", NULL };
  long status ;              /* Return status */
  static int choice ;        /* Index for chosen file */

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

/* If which file to save is not specified reject the command 
 */
  if (tcsDcNotEmpty(pcad->a)) {
    if (tcsDcString (opts, "file: ", pcad->a, &choice, pcad))
      break;
  } else {
      tcsCsAppendMessage (pcad, "File not specified");
      break ;
  }

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     tcsOpticsSetM1Save(choice) ;
     strcpy(pcad->vala, pcad->a);

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
 *   tcsCADm2ComaModel 
 *
 *   Purpose:
 *   Load the coefficients of the coma tilt model
 *
 *   Description:
 *   This routine allows the user to set and modify the coefficients of
 *   the model that attempts to correct the coma of the telescope by 
 *   tilting the secondary mirror. This model is only expected to be
 *   used when the x/y stage is not operating.
 *
 *   Invocation:
 *   tcsCADm2ComaModel (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => A coefficient 
 *      b => B coefficient 
 *      c => C coefficient 
 *
 *   EPICS output parameters:
 *      vala => Current A coefficient 
 *      valb => Current B coefficient 
 *      valc => Current C coefficient 
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
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADm2ComaModel (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double a, b, c ; /* Input coefficients */

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

/* Pull in and validate the data on the CAD input fields */
   if (tcsDcDouble ("A coeff: ", pcad->a, &a, pcad)) break ;
   if (tcsDcDouble ("B coeff: ", pcad->b, &b, pcad)) break ;
   if (tcsDcDouble ("C coeff: ", pcad->c, &c, pcad)) break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
   {
     status = CAD_ACCEPT ;
   }

   break ;

   case menuDirectiveSTART :

/* Set data into model */
    tcsOpticsSetComaCoeffs (a, b, c) ;

    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
   
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
 *   tcsCADm2ComaCorr
 *
 *   Purpose:
 *   Implements the m2ComaCorr command in the TCS
 *
 *   Description:
 *   The routine first validates the input data and if OK sets the
 *   the flag that controls whether the model tilt corrections to the
 *   position of M2 are applied or not.
 *
 *   Invocation:
 *   tcsCADm2ComaCorr (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Tilt corrections on/off
 *
 *   EPICS output parameters:
 *      vala => Tilt corrections on/off
 *      valb => Flag to show if corrections are on (=1) or off (=0) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADm2ComaCorr (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static int applyCorr ;     /* Apply corrections 1 = on, 0 = off */

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

/* Trap null or empty input as an error rather than defaulting to Off */
    if (!tcsDcLen(pcad->a)) {
      tcsCsAppendMessage (pcad, "Null or blank input") ;
      break ;
    }

    if (tcsDcOnOff ("Corrections :", pcad->a, &applyCorr, pcad))
      break ;

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     *(long *)pcad->valb = applyCorr ;

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
 *   tcsCADm2NomPosn 
 *
 *   Purpose:
 *   Sets the nominal position to be used as a base for the coma model
 *
 *   Description:
 *   This routine reads and checks the data input by the user that is to be
 *   used as the nominal or base position for the coma correction model.
 *   Once verified the data is stored for use elsewhere. Departures from
 *   this base position can be used to automatically correct the pointing
 *   for the model tilt.
 *
 *   Invocation:
 *   tcsCADm2NomPosn (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => x tilt (arcsec) 
 *      b => y tilt (arcsec) 
 *      c => focus (microns)
 *      d => x posn (microns)
 *      e => y posn (microns)
 *
 *   EPICS output parameters:
 *      vala => demanded x tilt
 *      valb => demanded y tilt
 *      valc => demanded focus
 *      vald => demanded x posn
 *      vale => demanded y posn 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetM2Nom  (tcsOptics)  Set nominal position for M2 coma model
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADm2NomPosn (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double xTilt ;   /* Demanded x tilt (arcsec) */
  static double yTilt ;
  static double x, y, z ; 

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
     tcsCsAppendMessage (pcad, "No x tilt given") ;
     break ;
   }
   if (tcsDcDouble ("x tilt: ", pcad->a, &xTilt, pcad)) break ;

   if (!tcsDcLen(pcad->b)) {
     tcsCsAppendMessage (pcad, "No y tilt given") ;
     break ;
   }
   if (tcsDcDouble ("y tilt: ", pcad->b, &yTilt, pcad)) break ;

   if (!tcsDcLen(pcad->c)) {
     tcsCsAppendMessage (pcad, "No focus given") ;
     break ;
   }
   if (tcsDcDouble ("focus: ", pcad->c, &z, pcad)) break ;

   if (!tcsDcLen(pcad->d)) {
     tcsCsAppendMessage (pcad, "No x posn. given") ;
     break ;
   }
   if (tcsDcDouble ("x posn: " , pcad->d, &x, pcad)) break ;

   if (!tcsDcLen(pcad->e)) {
     tcsCsAppendMessage (pcad, "No y posn. given") ;
     break ;
   }
   if (tcsDcDouble ("y posn: " , pcad->e, &y, pcad)) break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
   {
     status = CAD_ACCEPT ;
   }

   break ;

   case menuDirectiveSTART :

/* Store data for later use and output on links for display */
     tcsOpticsSetM2Nom (xTilt, yTilt, x, y, z) ;
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
     strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE) ;
     strncpy (pcad->vale, pcad->e, MAX_STRING_SIZE) ;

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
 *   tcsCADm2GuideMode
 *
 *   Purpose:
 *   Implements the m2GuideMode command in the TCS
 *
 *   Description:
 *   The routine first validates the input data and if OK sets the
 *   the flags that control how focus and coma corrections are handled.
 *
 *   Invocation:
 *   tcsCADm2GuideMode (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => absorb focus corrections on/off
 *      b => apply coma corrections on/off
 *
 *   EPICS output parameters:
 *      vala => absorbing focus corrections on/off
 *      valb => applying coma corrections on/off
 *      valc => flag (0/1) to show if focus corrections are being absorbed
 *      vald => flag (0/1) to show if coma corrections are being applied
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetM2Guide (tcsOptics)   Store states of guide mode flags
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *-
 */

long tcsCADm2GuideMode (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static int absorbFocus ;   /* Flag to control absorption of focus errors */
  static int comaCorrect ;   /* Flag to control coma corrections */

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

   status = CAD_REJECT ;

    if (tcsDcOnOff ("Absorb focus :", pcad->a, &absorbFocus, pcad))
      break ;

    if (tcsDcOnOff ("Correct coma :", pcad->b, &comaCorrect, pcad))
      break ;

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

/* Store data for later use and copy inputs to outputs */

     tcsOpticsSetM2Guide (absorbFocus, comaCorrect) ;

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
     *(long *)pcad->valc = (long)absorbFocus ;
     *(long *)pcad->vald = (long)comaCorrect ;

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
 *   tcsCADodgwDatum
 *
 *   Purpose:
 *   Datum the ODGW 
 *
 *   Description:
 *   This is a complete dummy routine called for in the "ODGW Guide
 *   Wrapper" document so that a common interface can be presented
 *   to higher level systems. The real GSAOI ODGW have no concept
 *   of needing to be sent to a home position.
 *
 *   Invocation:
 *   tcsCADodgwDatum (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADodgwDatum (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  char cadname[40];          /* Name of CAD */
  static char *cadNames[] = {"ODGW1DATUM", "ODGW2DATUM", "ODGW3DATUM", 
                               "ODGW4DATUM", NULL}; 
  int odgwIndex ;
  
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT;

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
  
      status = CAD_REJECT ;

/* Check which ODGW we are called for */
      strcpy(cadname, tcsCsCadName(pcad)) ;
      if (tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ) 
         break;
      status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
      if (!status)
        status = CAD_ACCEPT ;

   case menuDirectiveSTART :
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
 *   tcsCADodgwFollow
 *
 *   Purpose:
 *   Set an ODGW into follow mode
 *
 *   Description:
 *   The ODGW windows of the GSAOI have no concept of following in the
 *   sense that a guide probe does. However there is a requirement that
 *   the ODGW present the higher level systems with a similar interface
 *   to that of the guide probes. In the case of the odgwFollow commands
 *   we just therefore set an internal flag in the TCS to say we are
 *   following but don't actually send anything to the GSAOI
 *
 *   Invocation:
 *   tcsCADodgwFollow (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => follow state demand (on | off)
 *
 *   EPICS output parameters:
 *      vala => Follow state 0 or 1 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADodgwFollow (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  char cadname[40];          /* Name of CAD */
  static char *cadNames[] = {"ODGW1FOLLOW", "ODGW2FOLLOW", "ODGW3FOLLOW", 
                               "ODGW4FOLLOW", NULL}; 
  int odgwIndex ;
  long followState ;
  
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT;

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
  
      status = CAD_REJECT ;

/* Decode the following state demand */
      if (tcsDcFollow("switch: ", pcad->a, &followState, pcad))
         break;

/* Check which ODGW we are called for */
      strcpy(cadname, tcsCsCadName(pcad)) ;
      if (tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ) 
         break;
      status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
      if (!status)
        status = CAD_ACCEPT ;

   case menuDirectiveSTART :

/* Decode again but now we know it is going to work. This is so
 * we don't need static variables as this routine can get called 
 * for different CAD's
 */
      tcsDcFollow("switch: ", pcad->a, &followState, pcad) ;
      tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ; 

/* Now set internal flags and write to EPICS outputs */
      tcsGuideSetOdgwFollowState(odgwIndex, followState);
      *(long *)pcad->vala = followState ;
      tcsConfigForceCheck() ;

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
 *   tcsCADodgwMove
 *
 *   Purpose:
 *   Send the ODGW to a fixed position 
 *
 *   Description:
 *   This command will set the center of the ODGW to s specified pixel.
 *   A check is made to ensure that the specified pixel is on the chip.
 *   If the ODGW was in follow mode then this is disabled.
 *
 *   Invocation:
 *   tcsCADodgwMove (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  The x coordinate of the window center (pixels)
 *      b =>  The y coordinate of the window center (pixels)
 *
 *   EPICS output parameters:
 *      vala =>  Validated x coordinate of the window center (pixels)
 *      valb =>  Validated y coordinate of the window center (pixels)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADodgwMove (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  char cadname[40];          /* Name of CAD */
  static char *cadNames[] = {"ODGW1MOVE", "ODGW2MOVE", "ODGW3MOVE", 
                               "ODGW4MOVE", NULL}; 
  int odgwIndex ;
  static long ix ;       /* Demanded x pixel coordinate */
  static long iy ;       /* Demanded y pixel coordinate */
  LIMITTYPE limitType ;  /* type of limit for for the ODGW */
  double xmin, xmax ;    /* Max and min x pixel limits for the ODGW */
  double ymin, ymax ;    /* Max and min y pixel limits for the ODGW */
  double zmin, zmax ;    /* Max and min focus limits for the ODGW */
  double rmin, rmax ;    /* Max and min radial limits for the ODGW */
  
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT;

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
  
      status = CAD_REJECT ;

/* Check which ODGW we are called for */
      strcpy(cadname, tcsCsCadName(pcad)) ;
      if (tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ) 
         break;

/* Decode the input demands and check for range */
      if (tcsDcLong("x center: ", pcad->a, &ix, pcad)) break ;
      if (tcsDcLong("y center: ", pcad->b, &iy, pcad)) break ;

      tcsProbeGetLimits(odgwIndex+7, &limitType, &xmin, &xmax, &ymin, &ymax,
                        &zmin, &zmax, &rmin, &rmax);
      if (ix > xmax || ix < xmin) {
        tcsCsAppendMessage(pcad, "x demand out of range") ;
        break;
      }

      if (iy > ymax || iy < ymin) {
        tcsCsAppendMessage(pcad, "y demand out of range") ;
        break;
      }

      status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
      if (!status)
        status = CAD_ACCEPT ;

   case menuDirectiveSTART :

/* Decode again but now we know it is going to work. This is so
 * we don't need static variables as this routine can get called 
 * for different CAD's
 */
      tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ; 

/* Setup the move position for this window and turn following off */
      tcsGuideSetOdgwFollowState(odgwIndex, 0);
      tcsGuideMoveOdgw(odgwIndex, ix, iy) ;
      tcsConfigForceCheck() ;

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
 *   tcsCADodgwPark
 *
 *   Purpose:
 *   Send the ODGW to its park position 
 *
 *   Description:
 *   The ODGW can't physically be parked but this command sets up the 
 *   center coordinates of the window such that the window is in the
 *   corner of the chip. This ensures the readout of the ODGW does
 *   not interfere with science data. Parking the ODGW will automatically
 *   disable following so that resetting the target for the ODGW via
 *   the guideConfigure command won't move the window to the target
 *   until following is re-started.
 *
 *   Invocation:
 *   tcsCADodgwPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      t =>  Dummy parameter to ensure the CAD is marked
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADodgwPark (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  char cadname[40];          /* Name of CAD */
  static char *cadNames[] = {"ODGW1PARK", "ODGW2PARK", "ODGW3PARK", 
                               "ODGW4PARK", NULL}; 
  int odgwIndex ;
  
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT;

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
  
      status = CAD_REJECT ;

/* Check which ODGW we are called for */
      strcpy(cadname, tcsCsCadName(pcad)) ;
      if (tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ) 
         break;
      status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
      if (!status)
        status = CAD_ACCEPT ;

   case menuDirectiveSTART :

/* Decode again but now we know it is going to work. This is so
 * we don't need static variables as this routine can get called 
 * for different CAD's
 */
      tcsDcString(cadNames, " ", cadname, &odgwIndex, pcad) ; 

/* Setup the park position for this window and turn following off */
      tcsGuideSetOdgwFollowState(odgwIndex, 0);
      tcsGuideParkOdgw(odgwIndex) ;
      tcsConfigForceCheck() ;

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
 *   tcsCADoiwfsSelect
 *
 *   Purpose:
 *   Select an OIWFS
 *
 *   Description:
 *   Currently the only function of this record is to trap the name NICI
 *   and convert it to None before passing it on to the A&G Sequencer. This
 *   is a temporary measure until such time as the sequencer is coded to
 *   handle NICI. Note that only the name NICI is checked for, all other
 *   names are passed on directly. This is done deliberately so that the TCS
 *   does not limit the possible instruments that might be in use.
 *
 *   N.B. The above temporary measure was removed May 07
 *
 *   Invocation:
 *   tcsCADoiwfsSelect (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Name of OIWFS to use 
 *      b => Destination of data 
 *
 *   EPICS output parameters:
 *      vala => Name of OIWFS sent to A&G Sequencer 
 *      valb => Destination of data
 *      valc => Name of WFS used by TCS
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADoiwfsSelect (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static char *outNames[] = {"WFS", "AO"} ;
//  static int oiwfsIndex ;
  static int outIndex ;
  static char instrument[40]; /* name of the selected instrument */
  
/* Set message prefix */
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT;

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
  
      status = CAD_REJECT ;

/* If no instrument is specified then default to "NONE" */
      if( !tcsDcLen(pcad->a) ) {
//        oiwfsIndex = 0;
        strcpy(instrument, "None");
      } else {
        strcpy (instrument, pcad->a);
      }

      if ( !tcsDcLen(pcad->b) ) {
        tcsCsAppendMessage(pcad, "Must select a processing system") ;
        break ;
      }
      if (tcsDcString(outNames, " ", pcad->b, &outIndex, pcad) ) 
         break;

      status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
      if (!status)
        status = CAD_ACCEPT ;

   case menuDirectiveSTART :

    strcpy (pcad->vala, instrument);
    strcpy (pcad->valb, pcad->b);
/* This is only needed whilst NICI is being converted to "None" */
    strcpy (pcad->valc, pcad->a) ;

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



/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADfollow
 *
 *   Purpose:
 *   Set whether a TCS subsystem should FOLLOW kernel demands or not
 *
 *   Description:
 *   This routine is tied to the follow CAD record. It simply checks the
 *   follow switch specified for the subsystem and if it is valid sets
 *   it to the requested value. The switch 
 *   for FOLLOW is either ON or OFF to start or stop the subsystem following
 *   the TCS kernel demands.
 *
 *   Invocation:
 *   tcsCADfollow (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input fields :
 *
 *   a => Subsystem follow switch
 *
 *   EPICS Output fields :
 *
 *   vala => Subsystem follow switch
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
/* *INDENT-ON* */

long tcsCADfollow(struct cadRecord *pcad)
{

   long status;                 /* Return status */
   static long subsysSwitch = 0;

/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Fetch name of cad for use in messages */

   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Decode input field. Valid strings are ON or OFF */

      if (tcsDcFollow("switch: ", pcad->a, &subsysSwitch, pcad))
         break;

      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated data to the output links */

      *(double *) pcad->vala = (double) subsysSwitch;
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;
   }
   return status;
}


/*+
 *   Function name:
 *   tcsCADunFollowAll
 *
 *   Purpose:
 *   Stop all subsystem mechanisms from following the TCS demand stream
 *
 *   Description:
 *   This is essential a null routine. All the work is done in the
 *   database. When the preset is received a link triggers "off" 
 *   parameters to be set in every TCS follow command. This will
 *   mark each command so that they are then triggered by the start
 *   directive when it arrives
 *
 *   Invocation:
 *   tcsCADunfollowAll (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     none 
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADunfollowAll (struct cadRecord *pcad)

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
 *   tcsCADabortAll
 *
 *   Purpose:
 *   Stop all movement in all telescope subsystems 
 *
 *   Description:
 *   This is essential a null routine. All the work is done in the
 *   database. When the preset is received a link marks each of the
 *   records unfollowAll and stopAll. For this to work
 *   it is essential that this CAD appears earlier in the sequence
 *   of CAD record than those other records.
 *
 *   Invocation:
 *   tcsCADabortAll (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Apply brakes (Yes|No) 
 *
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADabortAll (struct cadRecord *pcad)

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
     strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
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
 *   tcsCADstopAll
 *
 *   Purpose:
 *   Stop all movement in major telescope and enclosure subsystems 
 *
 *   Description:
 *   This is essential a null routine. All the work is done in the
 *   database. When the preset is received a link marks each of the
 *   records telstop, rotStop and enclosureStop. For this to work
 *   it is essential that this CAD appears earlier in the sequence
 *   of CAD record than those other records.
 *
 *   Invocation:
 *   tcsCADstopAll (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *   a -> apply brakes (Yes|No)
 * 
 *   EPICS input parameters:
 *      a => Apply brakes (Yes|No)
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADstopAll (struct cadRecord *pcad)

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
     strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
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
 *   tcsCADstopGuideAll
 *
 *   Purpose:
 *   Disable guidinng in M2, M1, mount, rotator and probes
 *
 *   Description:
 *   This is essential a null routine. All the work is done in the
 *   database. When the preset is received a link triggers "off" 
 *   parameters to be set in every TCS guide command. This will
 *   mark each command so that they are then triggered by the start
 *   directive when it arrives
 *
 *   Invocation:
 *   tcsCADunfollowAll (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     none 
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADstopGuideAll (struct cadRecord *pcad)

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

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADsave
 *
 *   Purpose:
 *   Save TCS configuration (TCB) data in a file
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - whether this command saves the CURRENT or PRESET target
 *   b -  The name of the file to save the data in
 *   c -  A comment string associated with this configuration
 *
 *   Invocation:
 *   tcsCADsave(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
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
/* *INDENT-ON* */

long tcsCADsave(struct cadRecord *pcad)
{
   int nptr;                    /* Pointer to input argument */
   static long tcbDefn;         /* Is this CURRENT or PRESET */
   int status;
   static char filename[MAX_STRING_SIZE];
   static char comment[MAX_STRING_SIZE];

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Which TCB is to be saved ? */

      nptr = 1;
      slaIntin(pcad->a, &nptr, &tcbDefn, &status);
      if (status == 0) {
         if (tcbDefn != CURRENT && tcbDefn != PRESET) {
            tcsCsAppendMessage(pcad, "invalid TCB definition");
            break;
         }
      } else {
         printf("save: invalid TCB definition, assuming CURRENT\n");
         tcbDefn = CURRENT;
      }

/* Get name of file for saved configuration */
      strncpy(filename, pcad->b, MAX_STRING_SIZE);

/* If null or blank name assume a default */
      if ((strlen(filename) == 0) || (strspn(filename, " ") ==
                                      strlen(filename))) {
         strcpy(filename, "savedTCB.dat");
      }

/* Get comment if present */
      strncpy(comment, pcad->c, MAX_STRING_SIZE);

      sprintf(pcad->a, "%ld", tcbDefn);
      sprintf(pcad->b, "%s", filename);

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* End of switch statement */

   return (status);

}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADload
 *
 *   Purpose:
 *   Load TCS configuration (TCB) data from a file
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - whether this command saves the CURRENT or PRESET target
 *   b - Name of file to load configuration from
 *
 *   Invocation:
 *   tcsCADload(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
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
/* *INDENT-ON* */

long tcsCADload(struct cadRecord *pcad)
{
   int nptr;                    /* Pointer to input argument */
   static long tcbDefn;         /* Is this CURRENT or PRESET */
   int status;
   static char filename[MAX_STRING_SIZE];

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Which TCB is to be saved ? */

      nptr = 1;
      slaIntin(pcad->a, &nptr, &tcbDefn, &status);
      if (status == 0) {
         if (tcbDefn != CURRENT && tcbDefn != PRESET) {
            tcsCsAppendMessage(pcad, "invalid TCB definition");
            break;
         }
      } else {
         printf("load: invalid TCB definition, assuming CURRENT\n");
         tcbDefn = CURRENT;
      }

/* Get name of file for loading configuration */
      strncpy(filename, pcad->b, MAX_STRING_SIZE);

/* If null or blank name assume a default */
      if ((strlen(filename) == 0) || (strspn(filename, " ") ==
                                      strlen(filename))) {
         strcpy(filename, "savedTCB.dat");
      }

      sprintf(pcad->a, "%ld", tcbDefn);
      sprintf(pcad->b, "%s", filename);

      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* End of switch statement */
   return (status);
}


/*+
 *   Function name:
 *   tcsCADprobeFocus 
 *
 *   Purpose:
 *   Set a focus offset for a WFS
 *
 *   Description:
 *   This routine allows a probe focus offset to be set for each WFS.
 *   The offset value specified is checked for validity and then stored
 *   for later use by the routine that drives the probe z position.
 *   The offset specified is absolute i.e. specifying an offset of say
 *   0.1 mm followed by another offset of 0.1 mm leaves the probe offset by 
 *   a total of 0.1 mm not 0.2 mm. The offsets that are set are only applied
 *   when continuous demands are being sent to the A&G. If a move 
 *   command is issued then by definition this is a move to an absolute 
 *   position. The command here is intended to be used to tweak the 
 *   focus setting of the probe for engineering or test purposes. 
 *
 *   Invocation:
 *   tcsCADprobeFocus (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  focus offset (mm)
 *
 *   EPICS output parameters:
 *      vala => current focus offset 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsCsCadName   (tcsCadSupport)    Fetch name of cad record
 *
 *-
 */

long tcsCADprobeFocus (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  char* cadname ;         /* Command name without prefix */
  static int  guide ;     /* Identifier for WFS */
  static double offset ;  /* Demand focus offset (mm) */
  LIMITTYPE limitType ;   /* Type of limit for probe */
  double xmin, xmax ;     /* X limits for probe */
  double ymin, ymax ;     /* Y limits for probe */
  double zmin, zmax ;     /* Z limits for probe (mm) */
  double rmin, rmax ;     /* Radial limits for probe (mm) */
  char message[80] ;      /* Output message */

  
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

/* Fetch name of cad in order to identify the probe */
     cadname = tcsCsCadName (pcad) ;
     if (!strcmp(cadname, "pwfs1Focus")) {
       guide = 0 ;
     } else if (!strcmp (cadname, "pwfs2Focus")) {
       guide = 1 ;
     } else if (!strcmp (cadname, "oiwfsFocus")) {
       guide = 2 ;
     } else {
       tcsCsAppendMessage (pcad, "cad record name unknown");
       break ;
     }    

/*  Check offset for validity and range */
     if (tcsDcDouble ("Offset: ", pcad->a, &offset, pcad)) break ;
     tcsProbeGetLimits (guide, &limitType, &xmin, &xmax, &ymin, &ymax,
                        &zmin, &zmax, &rmin, &rmax) ;

     if (offset < zmin || offset > zmax) {
       sprintf (message, "Offset > %.1f or < %.1f", zmax, zmin);
       tcsCsAppendMessage (pcad, message) ;
       break ;
     }

    status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
    if (status)
      status = CAD_REJECT ;
    else
      status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    tcsProbeSetZoff (guide, offset);
    *(double *)pcad->vala = offset ;

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


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADrotator
 *
 *   Purpose:
 *   Set the desired rotator position angle.
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   Epics inputs:
 *   a -> instrument position angle (eastwards from north or up).
 *   b -> rotator frame
 *   c -> equinox of frame
 *   d -> instrument alignment angle
 *
 *   Invocation:
 *   tcsCADrotator(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *
 *
 *   Function value:
 *   Return status
 * 
 *-
 */
/* *INDENT-ON* */

long tcsCADrotator(struct cadRecord *pcad)
{
   double ipa;                  /* Input instrument position angle */
   double iaa;                  /* Input instrument alignment */
   FRAMETYPE frame;             /* Rotator frame */
   double eqx;                  /* Equinox of frame */
   char eqtype;                 /* Type of Equinox (B or J) */
   static struct ROT rotstruct;
   static char *opts[] = {"FIXED", NULL};
   int optindex ;
   static int fixed = 0;
   int status;

/* Check for any interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Get ipa value */
      if (tcsDcDouble("instrument position angle: ", pcad->a, &ipa, pcad))
         break;

/* Is ipa value out of range? */
      if (ipa < -360.0 || ipa > 360.0) {
         tcsCsAppendMessage(pcad, "invalid instrument position angle");
         break;
      }
      if (ipa < 0.0) ipa += 360.0;

/* Rotator tracking frame and equinox */
      if (pcad->b[0]) {

/* A bit of a hack to handle the "FIXED" option that the operators require.
 * look for the string "fixed" first and handle it specially
 */
         if (!tcsDcString(opts, "frame: ", pcad->b, &optindex, pcad)) {
           fixed = 1 ; 
           frame = AZEL_TOPO ;
           eqtype = ' ';
           eqx = 0.0;
           ipa -= 180.0;
           if (ipa < 0.0) ipa += 360.0;
      
         } else {
           
           fixed = 0;

           if (tcsDcFrame("", pcad->b, &frame, pcad))
              break;

           if (frame == FK4 || frame == FK5) {
              if (pcad->c[0]) {
                 if (tcsDcEpoch("", pcad->c, &eqtype, &eqx, pcad))
                    break;
              } else {
                 if (frame == FK5) {
                    eqtype = 'J';
                    eqx = 2000.0;
                 } else if (frame == FK4) {
                    eqtype = 'B';
                    eqx = 1950.0;
                 }
              }
           } else {
              eqtype = ' ';
              eqx = 0.0;
           }
        }
      } else {                  /* frame is blank */

         if (pcad->c[0]) {
            if (tcsDcEpoch("", pcad->c, &eqtype, &eqx, pcad))
               break;
            frame = eqtype == 'B' ? FK4 : FK5;
         } else {
            frame = FK5;
            eqtype = 'J';
            eqx = 2000.0;
         }
      }

/* Get iaa value */
      if (tcsDcDouble("instrument alignment: ", pcad->d, &iaa, pcad))
         break;

/* Is iaa value out of range? */
      if (iaa < -360.0 || iaa > 360.0) {
         tcsCsAppendMessage(pcad, "invalid instrument alignment");
         break;
      }
      if (iaa < 0.0) iaa += 360.0;
      if (fixed) {
        ipa +=iaa ;
        if (ipa < 0.0) ipa += 360.0;
      }

/* Set the data in the configuration block and mark this command as part
   of a configuration */
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
      status = CAD_ACCEPT;

      rotstruct.ipa.val = ipa * D2R;
      rotstruct.ipa.field = 'A';
      strncpy(rotstruct.ipa.instring, pcad->a, MAX_STRING_SIZE);

      rotstruct.frame.field = 'B';
      strncpy(rotstruct.frame.instring, pcad->b, MAX_STRING_SIZE);
      rotstruct.frame.val = frame;

      rotstruct.eqx.field = 'C';
      strncpy(rotstruct.eqx.instring, pcad->e, MAX_STRING_SIZE);
      rotstruct.eqx.val.year = eqx;
      rotstruct.eqx.val.type = eqtype;

      rotstruct.iaa.val = iaa * D2R;
      rotstruct.iaa.field = 'D';
      strncpy(rotstruct.iaa.instring, pcad->d, MAX_STRING_SIZE);

      tcsConfigSetRot(&rotstruct);

      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      *(double *) pcad->vala = rotstruct.ipa.val / D2R;
      strcpy(pcad->valb, tcsCsFrame(rotstruct.frame.val));
      sprintf(pcad->valc, "%c%.14f", rotstruct.eqx.val.type,
              rotstruct.eqx.val.year);
      *(double *) pcad->vald = rotstruct.iaa.val / D2R;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* End of switch statement */

   return (status);

}

/*+
 *   Function name:
 *   tcsCADrotGuideConfig
 *
 *   Purpose:
 *   Sets the parameters that control rotator guiding
 *
 *   Description:
 *   This routine sets the parameters that control how rotator guiding
 *   is configured. Currently there is only one parameter that can be
 *   set and this is the gain. Incoming corrections are multiplied
 *   by the gain before being added to the current total correction.
 *   The range of the gain is -1 to +1 justin case the sign of the
 *   correction needs to be reversed.
 *
 *   Invocation:
 *   tcsCADrotGuideConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  demand gain
 *
 *   EPICS output parameters:
 *      vala => current gain 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADrotGuideConfig (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static double gain ;       /*  Gain demand */


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

   status = CAD_REJECT ;

   if (tcsDcDouble("gain: ", pcad->a, &gain, pcad)) break;

   if ( gain > 1.0 || gain < -1.0 ) {
     tcsCsAppendMessage( pcad, "gain out of range");
     break;
   }

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     *(double *)pcad->vala = gain ;

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
 *   tcsCADrotGuideMode
 *
 *   Purpose:
 *   Implements the rotGuideMode command in the TCS
 *
 *   Description:
 *   This command turns rotator guiding on or off. When on, the TCS 
 *   accepts adjustments to the rotator position from the GeMS guiding
 *   system.
 *
 *   Invocation:
 *   tcsCADrotGuideMode (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => guiding corrections on/off
 *
 *   EPICS output parameters:
 *      vala => applying guiding corrections on/off
 *      valb => flag (0/1) to show if guide corrections are being applied 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADrotGuideMode (struct cadRecord *pcad)

{

  long status ;              /* Return status */
  static int rotCorrect ;    /* Flag to control guide corrections */

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

   status = CAD_REJECT ;

    if (tcsDcOnOff ("Guide :", pcad->a, &rotCorrect, pcad))
      break ;

/* If the data is validated then mark this command as part of a configuration.
*  Most CADs should do this but there are a few exceptions e.g. debug
*/
   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

     tcsSetRotatorGuideMode (rotCorrect) ;

     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
     *(long *)pcad->valb = (long)rotCorrect ;

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


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSetwrap
 *
 *   Purpose:
 *   Set the required azimuth/rotator wrap value. This specifies the
 *   the azimuth/rotator wrap sector that should be in use. 
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - The wrap value code : +1, 0 or -1. The values mean :
 *   If set to 1 the mount drive demand angles are forced to the "positive" 
 *   wrap (ie an angle between 0 & +360 for azimuth or -270 &270 for the
 *   rotator); if set to -1 the demand is forced to the "negative" wrap 
 *   (-180/+180 or -270/+90). Zero means use current wrap.
 *
 *   Invocation:
 *   tcsSetwrap(adname, pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    wrapname  (char *)      Either rotwrap or azwrap
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *      (!)    wrapstruct (struct ICAD_FIELD) wrap structure
 *
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
/* *INDENT-ON* */

static long tcsSetwrap(char *wrapname, struct cadRecord *pcad,
                    struct ICAD_FIELD *wrapstruct)
{
   long wrapval;                /* Input requested wrap */
   WRAP wrap;
   int status;

/* Check for any interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Get wrap value */
      if (tcsDcLong("", pcad->a, &wrapval, pcad)) break;

/* Is wrap value out of range? */
      if (wrapval < -1 || wrapval > 1) {
         tcsCsAppendMessage(pcad, "invalid wrap value");
         break;
      }
      if (strcmp(wrapname, "azwrap") == 0) {
         wrap = AZIMUTH;
      } else if (strcmp(wrapname, "rotwrap") == 0) {
         wrap = ROTATOR;
      } else {
         tcsCsAppendMessage(pcad, "invalid wrap name") ;
         break ;
      }

/* Set the data in the configuration block and mark this command as part
   of a configuration */
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
      wrapstruct->val = wrapval;
      wrapstruct->field = 'B';
      strncpy(wrapstruct->instring, pcad->b, MAX_STRING_SIZE);

      tcsConfigSetWrap(wrap, wrapstruct);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      *(long *) pcad->valb = wrapstruct->val;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* End of switch statement */
   return (status);
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADazwrap
 *
 *   Purpose:
 *   Set the azimuth wrap flag
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - The wrap value code : +1, 0 or -1. The values mean :
 *   If set to 1 the mount drive demand angles are forced to the "positive" 
 *   wrap (ie an angle between 0 & +360) if set to -1 the demand is forced 
 *   to the "negative" wrap (-180/+180). Zero means use current wrap.
 *
 *   Invocation:
 *   tcsCADazwrap(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *
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
/* *INDENT-ON* */
long tcsCADazwrap(struct cadRecord *pcad)
{
   static struct ICAD_FIELD wrapstruct;
   return (tcsSetwrap("azwrap", pcad, &wrapstruct));
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADrotwrap
 *
 *   Purpose:
 *   Set the rotator wrap flag
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - The wrap value code : +1, 0 or -1. The values mean :
 *   If set to 1 the cwrotator mount drive demand angles are forced to the 
 *   "positive"  wrap (ie an angle between -90 & +270) if set to -1 the demand 
 *   is forced to the "negative" wrap (-270/+90). Zero means use current wrap.
 *
 *   Invocation:
 *   tcsCADrotwrap(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *
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
/* *INDENT-ON* */

long tcsCADrotwrap(struct cadRecord *pcad)
{
   static struct ICAD_FIELD wrapstruct;
   return (tcsSetwrap("rotwrap", pcad, &wrapstruct));
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADtcbdefn
 *
 *   Purpose:
 *   Controls whether configuration being set is the current or preset
 *
 *   Description:
 *   This routine is activated whenever the tcbdefn CAD is triggered. It
 *   checks that its input arguments are valid and if they are tags the
 *   configuration as being either "current" or "preset". If the 
 *   configuration is current it will eventually be applied to the telescope
 *   and cause it to move. If it is preset then it will apply to the 
 *   preset target which will normally be the next target the observer 
 *   wnats to observe.
 *
 *   Invocation:
 *   tcsCADtcbdefn(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
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
/* *INDENT-ON* */

long tcsCADtcbdefn(struct cadRecord *pcad)
{
   long status;                 /* return status */
   char utcbdefn[20];           /* upper case version of tcbdefn */
   static TCBDEFN outtcb;       /* TCB definition to be put on output links */

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* fetch and check input data */
      tcsDcUc(pcad->a, 20, utcbdefn);
      if (strcmp(utcbdefn, "CURRENT") && strcmp(utcbdefn, "PRESET")) {
         tcsCsAppendMessage(pcad, "invalid choice");
         break;
      }

/* Try and mark command to see if it is valid within the current configuration
 */
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

/* Store requested TCB definition in configuration for later use */
      if (strcmp(utcbdefn, "CURRENT") == 0) {
         tcsConfigSetTCBDefn(CURRENT);
         outtcb = CURRENT;
      } else {
         outtcb = PRESET;
         tcsConfigSetTCBDefn(PRESET);
      }

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy inputs to outputs */
      *(long *) pcad->vala = outtcb;
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* end switch statement */

   return (status);

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADfilter1
 *
 *   Purpose:
 *   Set filter 1 parameters
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - bandwidth
 *   b - maxv parameter
 *   c - grab parameter
 *   d - short circuit flag
 *
 *   Invocation:
 *   tcsCADfilter1(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADfilter1(struct cadRecord *pcad)
{
   static struct TARGETFILTER filter;
   static char *scopts[] = {"OPEN", "CLOSED", "ONE SHOT", NULL};
   int sc;
   double bw, maxv, grab;
   int status;
   char message[256];

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Bandwidth */
      if (!tcsDcLen(pcad->a)) {
         bw = 0.05;
      } else {
         if (tcsDcDouble("bandwidth: ", pcad->a, &bw, pcad)) break;
         if (bw < 0.0) {
            tcsCsAppendMessage(pcad, "bandwidth: negative");
            break;
         }
      }

/* Maxv */
      if (!tcsDcLen(pcad->b)) {
         maxv = 3e7;             /* 2pi rad in 0.05 sec */
      } else {
         if (tcsDcDouble("maxv: ", pcad->b, &maxv, pcad)) break;
      }

/* Grab */
      if (!tcsDcLen(pcad->c)) {
         grab = 1.0;
      } else {
         if (tcsDcDouble("grab: ", pcad->c, &grab, pcad)) break;
      }

/* Short circuit */
      if (!tcsDcLen(pcad->d)) {
         sc = 0;
      } else {
         if (tcsDcString(scopts, "short circuit: ", pcad->d, &sc, pcad)) break;
      }

/* Convert maxv and grab to radians */
      maxv *= AS2R;
      grab *= AS2R;

/* Load the data into the configuration block */
      strcpy(filter.cadname, tcsCsCadName(pcad));

      filter.bw.field = 'A';
      strncpy(filter.bw.instring, pcad->a, MAX_STRING_SIZE);
      filter.bw.val = bw;

      filter.maxv.field = 'B';
      strncpy(filter.maxv.instring, pcad->b, MAX_STRING_SIZE);
      filter.maxv.val = maxv;

      filter.grab.field = 'C';
      strncpy(filter.grab.instring, pcad->c, MAX_STRING_SIZE);
      filter.grab.val = grab;

      filter.sc.field = 'D';
      strncpy(filter.sc.instring, pcad->d, MAX_STRING_SIZE);
      filter.sc.val = sc;

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;
      tcsConfigSetTFilt(&filter);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      *(long *) pcad->vala = filter.bw.val;
      *(long *) pcad->valb = filter.maxv.val;
      *(long *) pcad->valc = filter.grab.val;
      *(long *) pcad->vald = filter.sc.val;

      sprintf(message, "%s : bw: %s maxv: %s grab: %s sc: %s", 
                     tcsCsCadName(pcad), pcad->a, pcad->b, pcad->c, pcad->d);
      tcsLogMessage(message);


      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADfilter2
 *
 *   Purpose:
 *   Set filter 2 parameters
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Weight for chop state A
 *   b - Weight for chop state B
 *   c - Weight for chop state C
 *   d - Weight for NOD state
 *   e - bandwidth
 *   f - maxv parameter
 *   g - grab parameter
 *   h - short circuit flag
 *
 *   Invocation:
 *   tcsCADfilter2(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADfilter2(struct cadRecord *pcad)
{
   static struct POINTFILTER filter;
   static char *scopts[] = {"OPEN", "CLOSED", "ONE SHOT", NULL};
   double weightA, weightB, weightC, weightNod;
   int sc;
   double bw, maxv, grab;
   int status;
   double tot;
   char message[256];

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Weights */
      if (tcsDcDouble("chop A weight: ", pcad->a, &weightA, pcad)) break;
      if (weightA < 0.0) {
         tcsCsAppendMessage(pcad, "negative chop state A weight");
         break;
      }
      if (tcsDcDouble("chop B weight: ", pcad->b, &weightB, pcad)) break;
      if (weightB < 0.0) {
         tcsCsAppendMessage(pcad, "negative chop state B weight");
         break;
      }
      if (tcsDcDouble("chop C weight: ", pcad->c, &weightC, pcad)) break;
      if (weightC < 0.0) {
         tcsCsAppendMessage(pcad, "negative chop state C weight");
         break;
      }
      if (tcsDcDouble("Nod weight: ", pcad->d, &weightNod, pcad)) break;
      if (weightNod < 0.0) {
         tcsCsAppendMessage(pcad, "negative Nod weight");
         break;
      }

/* Bandwidth */
      if (!tcsDcLen(pcad->e)) {
         bw = 0.05;
      } else {
         if (tcsDcDouble("bandwidth: ", pcad->e, &bw, pcad)) break;
         if (bw < 0.0) {
            tcsCsAppendMessage(pcad, "bandwidth: negative");
            break;
         }
      }

/* Maxv */
      if (!tcsDcLen(pcad->f)) {
         maxv = 3e7;             /* 2pi rad in 0.05 sec */
      } else {
         if (tcsDcDouble("maxv: ", pcad->f, &maxv, pcad)) break;
      }

/* Grab */
      if (!tcsDcLen(pcad->g)) {
         grab = 1.0;
      } else {
         if (tcsDcDouble("grab: ", pcad->g, &grab, pcad)) break;
      }

/* Short circuit */
      if (!tcsDcLen(pcad->h)) {
         sc = 0;
      } else {
         if (tcsDcString(scopts, "short circuit: ", pcad->h, &sc, pcad)) break;
      }

/* Normalise weights and disable filter (via bw) if they are 
   all zero */
      tot = weightA + weightB + weightC + weightNod;
      if (tot != 0.0) {
         weightA /= tot;
         weightB /= tot;
         weightC /= tot;
         weightNod /= tot;
      } else {
         weightA = weightB = weightC = weightNod = 1.0 / 4.0;
         bw = 0.0;
      }

/* Convert maxv and grab to radians */
      maxv *= AS2R;
      grab *= AS2R;

/* Load the data into the configuration block */
      strcpy(filter.cadname, tcsCsCadName(pcad));

      filter.weightA.field = 'A';
      strncpy(filter.weightA.instring, pcad->a, MAX_STRING_SIZE);
      filter.weightA.val = weightA;

      filter.weightB.field = 'B';
      strncpy(filter.weightB.instring, pcad->b, MAX_STRING_SIZE);
      filter.weightB.val = weightB;

      filter.weightC.field = 'C';
      strncpy(filter.weightC.instring, pcad->c, MAX_STRING_SIZE);
      filter.weightC.val = weightC;

      filter.weightNod.field = 'D';
      strncpy(filter.weightNod.instring, pcad->d, MAX_STRING_SIZE);
      filter.weightNod.val = weightNod;

      filter.bw.field = 'E';
      strncpy(filter.bw.instring, pcad->e, MAX_STRING_SIZE);
      filter.bw.val = bw;

      filter.maxv.field = 'F';
      strncpy(filter.maxv.instring, pcad->f, MAX_STRING_SIZE);
      filter.maxv.val = maxv;

      filter.grab.field = 'G';
      strncpy(filter.grab.instring, pcad->g, MAX_STRING_SIZE);
      filter.grab.val = grab;

      filter.sc.field = 'H';
      strncpy(filter.sc.instring, pcad->h, MAX_STRING_SIZE);
      filter.sc.val = sc;

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;
      tcsConfigSetPFilt(&filter);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      *(long *) pcad->vala = filter.weightA.val;
      *(long *) pcad->valb = filter.weightB.val;
      *(long *) pcad->valc = filter.weightC.val;
      *(long *) pcad->vald = filter.weightNod.val;
      *(long *) pcad->vale = filter.bw.val;
      *(long *) pcad->valf = filter.maxv.val;
      *(long *) pcad->valg = filter.grab.val;
      *(long *) pcad->valh = filter.sc.val;

      sprintf(message, "%s : A: %s B: %s C: %s Nod: %s bw: %s maxv: %s grab: %s sc: %s", 
                     tcsCsCadName(pcad), pcad->a, pcad->b, pcad->c, pcad->d,
                     pcad->e, pcad->f, pcad->g, pcad->h);
      tcsLogMessage(message);
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}

/*+
 *   Function name:
 *   tcsCADgsaoiodgwSetup
 *
 *   Purpose:
 *   Setup the non window specific ODGW parameters for the GSAOI.
 *
 *   Description:
 *   The setup of the ODGW windows for the GSAOI requires a large 
 *   number of parameters. Quite a few of these parameters 
 *   are dependent on the target and whether the ODGW for that 
 *   detector is in use e.g. the position of the window. This command 
 *   sets up all the other parameters for the guiding e.g. integration
 *   time, type of sampling etc. 
 *   Note that the first ten parameters will be sent directly to the 
 *   GSAOI command seqODGW when this record executes. The other parameters
 *   are stored and sent with the dataODGW command whenever the ODGW
 *   window parameters are set.
 *
 *   Epics inputs:
 *     a => Read method (DCS | Fowler)
 *     b => Number of resets
 *     c => Number of Fowler samples
 *     d => Exposure time (secs)
 *     e => Number of interleaved science rows
 *     f => Number of interleaved idle rows
 *     g => Exposure multiplier ODGW1 
 *     h => Exposure multiplier ODGW2 
 *     i => Exposure multiplier ODGW3 
 *     j => Exposure multiplier ODGW4 
 *     k => Window size (4, 8, 16, 32 or 64 pixels)
 *     l => Save permanent copy? (YES | NO)
 *     m => Guider output (MCAO | DUMMY)
 *     n => Display ODGW (YES | NO)
 *     o => Display Rate (Hz)
 *
 *   Epics outputs:
 *     vala => Read method (DCS | Fowler)
 *     valb => Number of resets
 *     valc => Number of Fowler samples
 *     vald => Exposure time (secs)
 *     vale => Number of interleaved science rows
 *     valf => Number of interleaved idle rows
 *     valg => Exposure multiplier ODGW1 
 *     valh => Exposure multiplier ODGW2 
 *     vali => Exposure multiplier ODGW3 
 *     valj => Exposure multiplier ODGW4 
 *     valk => Window size (4, 8, 16, 32 or 64 pixels)
 *     vall => Save permanent copy? (YES | NO)
 *     valm => Guider output (MCAO | DUMMY)
 *     valn => Display ODGW (YES | NO)
 *     valo => Display Rate (Hz)
 *
 *   Invocation:
 *   tcsCADgsaoiodgwSetup(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsCADgsaoiodgwSetup(struct cadRecord *pcad)
{
   static char *readopts[] = {"DCS", "FOWLER", NULL} ; 
   static int readIndex ;
   static long numResets ;
   static long noFowlerSamps ;
   static long noInterleavedScienceRows;
   static long noInterleavedIdleRows ;
   static double exposure ;
   static long odgw1Multiplier ;
   static long odgw2Multiplier ;
   static long odgw3Multiplier ;
   static long odgw4Multiplier ;
   static char *windowopts[] = {"2", "4", "6", "8", "10", "12", "16", "24", "32", "64", "128", NULL};
   static int windowIndex ;
   static char *saveopts[] = {"YES", "NO", NULL} ;
   static int saveIndex ;
   static char *guideropts[] = {"MCAO", "DUMMY", NULL};
   static int guiderIndex ;
   static char *displayopts[] = {"YES", "NO", NULL} ;
   static int displayIndex ;
   static double displayRate ;
   int windowSize ;                                  

   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* The first set of 10 parameters trigger the GSAOI seqODGW command
 * immediately. The second group of 5 are saved for sending with
 * the dataODGW when it is issued.
 */
      if (tcsDcString(readopts, "read: ", pcad->a, &readIndex, pcad)) break;

      if (tcsDcLong("extent: ", pcad->b, &numResets, pcad)) break;
      if ( numResets < 0 ) {
         tcsCsAppendMessage( pcad, "No. of resets < 0" );
         break;
      }

      if (tcsDcLong("samples: ", pcad->c, &noFowlerSamps, pcad)) break;
      if ( noFowlerSamps < 0 ) {
         tcsCsAppendMessage( pcad, "No. Fowler samples < 0" );
         break;
      }

      if (tcsDcDouble("Exposure: ", pcad->d, &exposure, pcad)) break;
      if ( exposure < 0.0 ) {
         tcsCsAppendMessage( pcad, "Exposure < 0.0" );
         break;
      }

      if (tcsDcLong("rows: ", pcad->e, &noInterleavedScienceRows, pcad)) break;
      if ( noInterleavedScienceRows < 0 ) {
         tcsCsAppendMessage( pcad, "No. interleaved science rows < 0" );
         break;
      }

      if (tcsDcLong("rows: ", pcad->f, &noInterleavedIdleRows, pcad)) break;
      if ( noInterleavedIdleRows < 0 ) {
         tcsCsAppendMessage( pcad, "No. interleaved idle rows < 0" );
         break;
      }

      if (tcsDcLong("ODGW1 multiplier: ", pcad->g, &odgw1Multiplier, pcad)) break;
      if ( odgw1Multiplier < 0 ) {
         tcsCsAppendMessage( pcad, "ODGW1 exposure multiplier < 0" );
         break;
      }

      if (tcsDcLong("ODGW2 multiplier: ", pcad->h, &odgw2Multiplier, pcad)) break;
      if ( odgw2Multiplier < 0 ) {
         tcsCsAppendMessage( pcad, "ODGW2 exposure multiplier < 0" );
         break;
      }

      if (tcsDcLong("ODGW3 multiplier: ", pcad->i, &odgw3Multiplier, pcad)) break;
      if ( odgw3Multiplier < 0 ) {
         tcsCsAppendMessage( pcad, "ODGW3 exposure multiplier < 0" );
         break;
      }

      if (tcsDcLong("ODGW4 multiplier: ", pcad->j, &odgw4Multiplier, pcad)) break;
      if ( odgw4Multiplier < 0 ) {
         tcsCsAppendMessage( pcad, "ODGW4 exposure multiplier < 0" );
         break;
      }

      if (tcsDcString(windowopts, "window: ", pcad->k, &windowIndex, pcad)) break;

      if (tcsDcString(saveopts, "save? : ", pcad->l, &saveIndex, pcad)) break;

      if (tcsDcString(guideropts, "guider : ", pcad->m, &guiderIndex, pcad)) break;

      if (tcsDcString(displayopts, "display : ", pcad->n, &displayIndex, pcad)) break;

      if (tcsDcDouble("Rate: ", pcad->o, &displayRate, pcad)) break;

      if ( displayRate < 0.0 ) {
         tcsCsAppendMessage( pcad, "Rate < 0.0" );
         break;
      }

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;

      tcsConfigSetOdgwParams();

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Update the data store. */
      tcsSetODGWGuidePeriod(0, exposure * odgw1Multiplier);
      tcsSetODGWGuidePeriod(1, exposure * odgw2Multiplier);
      tcsSetODGWGuidePeriod(2, exposure * odgw3Multiplier);
      tcsSetODGWGuidePeriod(3, exposure * odgw4Multiplier);
      windowSize = atoi(windowopts[windowIndex]);
      tcsSetupODGW(windowSize, saveIndex, guiderIndex, displayIndex,
                   displayRate);

      
/* Copy validated inputs argument to output CAD fields */
      /*      strcpy(pcad->vala, readopts[readIndex]);*/
      if ( readIndex == 0 ) {
	strcpy(pcad->vala, "0");
      } else if ( readIndex == 1 ) {
	strcpy(pcad->vala, "1");
      }
      strcpy(pcad->valb, pcad->b);
      strcpy(pcad->valc, pcad->c);
      strcpy(pcad->vald, pcad->d);
      strcpy(pcad->vale, pcad->e);
      strcpy(pcad->valf, pcad->f);
      strcpy(pcad->valg, pcad->g);
      strcpy(pcad->valh, pcad->h);
      strcpy(pcad->vali, pcad->i);
      strcpy(pcad->valj, pcad->j);
      strcpy(pcad->valk, pcad->k);
      strcpy(pcad->vall, saveopts[saveIndex]);
      strcpy(pcad->valm, guideropts[guiderIndex]);
      strcpy(pcad->valn, displayopts[displayIndex]);
      strcpy(pcad->valo, pcad->o);

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}
/*+
 *   Function name:
 *   tcsCADguiderConfig
 *
 *   Purpose:
 *   Configure the four generic virtual guiders. This defines the
 *   real guiders, either the AOM tip/tilt guiders or the On detector
 *   Guide Windows (ODGW) that the virtual guiders are connected to.
 *
 *   Description:
 *   The input parameters are verified and a check is made that 
 *   no physical guider is attached to more than one virtual
 *   guider. The verified data is then stored in the Telescope
 *   Configuration Block for use by the configuration checking.
 *   This command simply sets up the configuration, whether a 
 *   virtual guider is really part of the configuration depends
 *   on whether a target is set for g1, g2, g3 or g4. 
 *   Valid names for the output for each virtual guider are:
 *   None, TTGS1, TTGS2, TTGS3, ODGW1, ODGW2, ODGW3 or ODGW4
 *
 *   Epics inputs:
 *     a => Name of output for g1
 *     b => Name of output for g2
 *     c => Name of output for g3
 *     d => Name of output for g4
 *
 *   Epics outputs:
 *     vala => Name of output for g1
 *     valb => Name of output for g2
 *     valc => Name of output for g3
 *     vald => Name of output for g4
 *     vale => Index of output for g1
 *     valf => Index of output for g2
 *     valg => Index of output for g3
 *     valh => Index of output for g4
 *
 *   Invocation:
 *   tcsCADguiderConfig(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsCADguiderConfig(struct cadRecord *pcad)
{
   static struct VGCONFIG vgconfig;
   static char *vgopts[] = {"NONE", "TTGS1", "TTGS2", "TTGS3",
                            "ODGW1", "ODGW2", "ODGW3", "ODGW4", NULL};
   static int g1index ;            /* Output guider index */
   static int g2index ;            /* Output guider index */
   static int g3index ;            /* Output guider index */
   static int g4index ;            /* Output guider index */
   int status;
   char mess[MAX_STRING_SIZE];     /* Output message */

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* G1 */
      if (!tcsDcLen(pcad->a)) {
         g1index = 0;
      } else {
         if (tcsDcString(vgopts, "g1: ", pcad->a, &g1index, pcad)) break;
      }

/* G2 */
      if (!tcsDcLen(pcad->b)) {
         g2index = 0;
      } else {
         if (tcsDcString(vgopts, "g2: ", pcad->b, &g2index, pcad)) break;
      }

/* G3 */
      if (!tcsDcLen(pcad->c)) {
         g3index = 0;
      } else {
         if (tcsDcString(vgopts, "g3: ", pcad->c, &g3index, pcad)) break;
      }

/* G4 */
      if (!tcsDcLen(pcad->d)) {
         g4index = 0;
      } else {
         if (tcsDcString(vgopts, "g4: ", pcad->d, &g4index, pcad)) break;
      }

/* Check for duplicates (other than 0) */
      if (g1index != 0) {
        if (g1index == g2index || g1index == g3index || g1index == g4index) {
          strcpy(mess, "outputs are the same");
          tcsCsAppendMessage (pcad, mess);
          break ;
        }
      }
      if (g2index != 0) {
        if (g2index == g3index || g2index == g4index) {
          strcpy(mess, "outputs are the same");
          tcsCsAppendMessage (pcad, mess);
          break ;
        }
      }
      if (g3index != 0) {
        if (g3index == g4index) {
          strcpy(mess, "outputs are the same");
          tcsCsAppendMessage (pcad, mess);
          break ;
        }
      }

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;

/* Load the data into the configuration block */
      strcpy(vgconfig.cadname, tcsCsCadName(pcad));
      vgconfig.destination = g1index ;
      tcsConfigSetVgconfig(0, &vgconfig);
      vgconfig.destination = g2index ;
      tcsConfigSetVgconfig(1, &vgconfig);
      vgconfig.destination = g3index ;
      tcsConfigSetVgconfig(2, &vgconfig);
      vgconfig.destination = g4index ;
      tcsConfigSetVgconfig(3, &vgconfig);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      strcpy(pcad->vala, vgopts[g1index]);
      strcpy(pcad->valb, vgopts[g2index]);
      strcpy(pcad->valc, vgopts[g3index]);
      strcpy(pcad->vald, vgopts[g4index]);
      *(long *) pcad->vale = g1index;
      *(long *) pcad->valf = g2index;
      *(long *) pcad->valg = g3index;
      *(long *) pcad->valh = g4index;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADplanet
 *
 *   Purpose:
 *   Set planet parameters
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Planet name (or moon)
 *   b - Object name (for SAD)
 *
 *   Invocation:
 *   tcsCADplanet(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADplanet(struct cadRecord *pcad)
{
   static struct PLANET planet;
   static char sname[MAX_STRING_SIZE];
   PLANET code;
   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Planet */
      if (tcsDcPlanet("name: ", pcad->a, &code, pcad)) break;

/* Object name - default to the planet name */
      if (tcsDcLen(pcad->b)) {
         strncpy( sname, pcad->b, MAX_STRING_SIZE);
      } else {
         strncpy( sname, pcad->a, MAX_STRING_SIZE);
      }

/* Load the data into the configuration block */
      strcpy(planet.cadname, tcsCsCadName(pcad));

      planet.code.field = 'A';
      strncpy(planet.code.instring, pcad->a, MAX_STRING_SIZE);
      planet.code.val = code;

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;
      tcsConfigSetPlanet(&planet);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      switch(planet.code.val) {
      case MERCURY:
         strcpy(pcad->vala, "Mercury");
         break;
      case VENUS:
         strcpy(pcad->vala, "Venus");
         break;
      case MOON:
         strcpy(pcad->vala, "Moon");
         break;
      case MARS:
         strcpy(pcad->vala, "Mars");
         break;
      case JUPITER:
         strcpy(pcad->vala, "Jupiter");
         break;
      case SATURN:
         strcpy(pcad->vala, "Saturn");
         break;
      case URANUS:
         strcpy(pcad->vala, "Uranus");
         break;
      case NEPTUNE:
         strcpy(pcad->vala, "Neptune");
         break;
      case PLUTO:
         strcpy(pcad->vala, "Pluto");
         break;

/* This suppressed compiler warnings. */
      case EPHEMERIS:
      case ORBIT:
      case NO_PLANET:
         break;
      }
      strncpy(pcad->valb, sname, MAX_STRING_SIZE);

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADorbit
 *
 *   Purpose:
 *   Set orbit parameters
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Element set code
 *   b - Epoch (TT MJD) of elements
 *   c - Orbital inclination
 *   d - Longitude of ascending node
 *   e - Longitude or argument of perihelion
 *   f - Mean or perihelion distance
 *   g - Eccentricity
 *   h - Mean anomoly or longitude
 *   i - Daily motion
 *   j - Object name
 *
 *   Invocation:
 *   tcsCADorbit(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADorbit(struct cadRecord *pcad)
{
   static struct ORBIT sourceAorbit, pwfs1Orbit, pwfs2Orbit, oiwfsOrbit;
   static struct ORBIT mountOrbit, sourceBOrbit, sourceCOrbit ;
   static struct ORBIT g1Orbit, g2Orbit, g3Orbit, g4Orbit ;
   struct ORBIT *porbit ;
   TELESCOPE tel;
   long jform;
   double epoch, orbinc, anode, perih, aorq, e, aorl, dm;
   int status, j;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);
   if (!strncmp(tcsCsCadName(pcad), "pwfs1orbit", 10)) {
     porbit = &pwfs1Orbit;
     tel = PWFS1;
   } else if (!strncmp(tcsCsCadName(pcad), "pwfs2orbit", 10)) {
     porbit = &pwfs2Orbit ;
     tel = PWFS2 ;
   } else if (!strncmp(tcsCsCadName(pcad), "oiwfsorbit", 10)) {
     porbit = &oiwfsOrbit;
     tel = OIWFS ;
   } else if (!strncmp(tcsCsCadName(pcad), "mountorbit", 10)) {
     porbit = &mountOrbit ;
     tel = MOUNT; 
   } else if (!strncmp(tcsCsCadName(pcad), "sourceBorbit", 12)) {
     porbit = &sourceBOrbit;
     tel = SOURCE_B ;
   } else if (!strncmp(tcsCsCadName(pcad), "sourceCorbit", 12)) {
     porbit = &sourceCOrbit;
     tel = SOURCE_C ;
   } else if (!strncmp(tcsCsCadName(pcad), "g1orbit", 7)) {
     porbit = &g1Orbit;
     tel = G1 ;
   } else if (!strncmp(tcsCsCadName(pcad), "g2orbit", 7)) {
     porbit = &g2Orbit;
     tel = G2 ;
   } else if (!strncmp(tcsCsCadName(pcad), "g3orbit", 7)) {
     porbit = &g3Orbit;
     tel = G3 ;
   } else if (!strncmp(tcsCsCadName(pcad), "g4orbit", 7)) {
     porbit = &g4Orbit;
     tel = G4 ;
   } else {
     porbit = &sourceAorbit ;
     tel = SOURCE_A ;
   }

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Element set */
      if (tcsDcLong("element set: ", pcad->a, &jform, pcad)) break;
      if ( jform < 1 || jform > 3 ) {
         tcsCsAppendMessage( pcad, "element set not in range 1-3" );
         break;
      }

/* Epoch */
      j = tcsDcT0("epoch: ", pcad->b, &epoch, pcad);
      if ( j < 0 ) break;
      if ( j == 2 ) {
         tcsCsAppendMessage( pcad, "TT is blank" );
         break;
      } else if ( j == 1 ) {
         tcsCsAppendMessage( pcad, "TT less than one day" );
         break;
      }

/* Orbital inclination */
      if (tcsDcDouble("inclination: ", pcad->c, &orbinc, pcad)) break;
      if ( orbinc < -180.0 || orbinc > 180.0 ) {
         tcsCsAppendMessage( pcad, "inclination outside +/-180" );
         break;
      }

/* Longitude of ascending node */
      if (tcsDcDouble("ascending node: ", pcad->d, &anode, pcad)) break;
      if ( anode < 0.0 || anode > 360.0 ) {
         tcsCsAppendMessage( pcad, "ascending node outside 0-360" );
         break;
      }

/* Longitude or argument of perihelion */
      if (tcsDcDouble("perhelion: ", pcad->e, &perih, pcad)) break;
      if ( perih < 0.0 || perih > 360.0 ) {
         tcsCsAppendMessage( pcad, "perihelion outside 0-360" );
         break;
      }

/* Mean or perihelion distance */
      if (tcsDcDouble("mean/peri dist: ", pcad->f, &aorq, pcad)) break;
      if ( aorq < 0.0 || aorq > 1000.0 ) {
         tcsCsAppendMessage( pcad, "mean/peri dist outside 0-1000" );
         break;
      }

/* Eccentricity */
      if (tcsDcDouble("eccentricity: ", pcad->g, &e, pcad)) break;
      if ( e < 0.0 || e > 1.5 ) {
         tcsCsAppendMessage( pcad, "eccentricity outside 0-1.5" );
         break;
      }

/* Mean anomoly or longitude */
      if ( jform == 1 || jform == 2 ) {
         if (tcsDcDouble("mean anom/long: ", pcad->h, &aorl, pcad)) break;
         if ( aorl < 0.0 || aorl > 360.0 ) {
            tcsCsAppendMessage( pcad, "mean anom/long outside 0-360" );
            break;
         }
      } else {
         aorl = 0.0;
      }

/* Daily motion */
      if (jform == 1) {
         if (tcsDcDouble("daily motion: ", pcad->i, &dm, pcad)) break;
         if ( dm < 0.0 || dm > 10.0 ) {
            tcsCsAppendMessage( pcad, "daily motion outside 0-10" );
            break;
         }
      } else {
         dm = 0.0;
      }


/* Load the data into the configuration block */
      strcpy(porbit->cadname, tcsCsCadName(pcad));

      porbit->jform.field = 'A';
      strncpy(porbit->jform.instring, pcad->a, MAX_STRING_SIZE);
      porbit->jform.val = jform;

      porbit->epoch.field = 'B';
      strncpy(porbit->epoch.instring, pcad->b, MAX_STRING_SIZE);
      porbit->epoch.val = epoch;

      porbit->orbinc.field = 'C';
      strncpy(porbit->orbinc.instring, pcad->c, MAX_STRING_SIZE);
      porbit->orbinc.val = orbinc * D2R;

      porbit->anode.field = 'D';
      strncpy(porbit->anode.instring, pcad->d, MAX_STRING_SIZE);
      porbit->anode.val = anode * D2R;

      porbit->perih.field = 'E';
      strncpy(porbit->perih.instring, pcad->e, MAX_STRING_SIZE);
      porbit->perih.val = perih * D2R;

      porbit->aorq.field = 'F';
      strncpy(porbit->aorq.instring, pcad->f, MAX_STRING_SIZE);
      porbit->aorq.val = aorq;

      porbit->e.field = 'G';
      strncpy(porbit->e.instring, pcad->g, MAX_STRING_SIZE);
      porbit->e.val = e;

      porbit->aorl.field = 'H';
      strncpy(porbit->aorl.instring, pcad->h, MAX_STRING_SIZE);
      porbit->aorl.val = aorl * D2R;

      porbit->dm.field = 'I';
      strncpy(porbit->dm.instring, pcad->i, MAX_STRING_SIZE);
      porbit->dm.val = dm * D2R;

      if (tcsConfigMarkComm(pcad->name, pcad->mess))
         break;
      tcsConfigSetOrbit(porbit, tel);

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

   if (!strncmp(tcsCsCadName(pcad), "pwfs1orbit", 10)) {
     porbit = &pwfs1Orbit;
   } else if (!strncmp(tcsCsCadName(pcad), "pwfs2orbit", 10)) {
     porbit = &pwfs2Orbit ;
   } else if (!strncmp(tcsCsCadName(pcad), "oiwfsorbit", 10)) {
     porbit = &oiwfsOrbit;
   } else if (!strncmp(tcsCsCadName(pcad), "g1orbit", 7)) {
     porbit = &g1Orbit;
   } else if (!strncmp(tcsCsCadName(pcad), "g2orbit", 7)) {
     porbit = &g2Orbit;
   } else if (!strncmp(tcsCsCadName(pcad), "g3orbit", 7)) {
     porbit = &g3Orbit;
   } else if (!strncmp(tcsCsCadName(pcad), "g4orbit", 7)) {
     porbit = &g4Orbit;
   } else if (!strncmp(tcsCsCadName(pcad), "mountorbit", 10)) {
     porbit = &mountOrbit ;
   } else if (!strncmp(tcsCsCadName(pcad), "sourceBorbit", 12)) {
     porbit = &sourceBOrbit;
   } else if (!strncmp(tcsCsCadName(pcad), "sourceCorbit", 12)) {
     porbit = &sourceCOrbit;
   } else {
     porbit = &sourceAorbit ;
   }

/* Copy validated inputs argument to output CAD fields */
      *(long *) pcad->vala = (long) porbit->jform.val;
      *(double *) pcad->valb = (double) porbit->epoch.val/D2R;
      *(double *) pcad->valc = (double) porbit->orbinc.val/D2R;
      *(double *) pcad->vald = (double) porbit->anode.val/D2R;
      *(double *) pcad->vale = (double) porbit->perih.val/D2R;
      *(double *) pcad->valf = (double) porbit->aorq.val;
      *(double *) pcad->valg = (double) porbit->e.val;
      *(double *) pcad->valh = (double) porbit->aorl.val/D2R;
      *(double *) pcad->vali = (double) porbit->dm.val/D2R;
      strncpy( pcad->valj, pcad->j, MAX_STRING_SIZE);

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADpointParam
 *
 *   Purpose:
 *   Set pointing model parameter
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Parameter name
 *   b - Parameter set name (session or local)
 *   c - Parameter value
 *
 *   Invocation:
 *   tcsCADpointParam(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADpointParam(struct cadRecord *pcad)
{
   static int set, param;

/* The orders of these arrays must match the order of the links from the
   fan out records in tcsPointParams.sch. */
   static char *setnames[] = {"SESSION", "LOCAL", NULL};
   static char *parnames[] = {"CA", "CE", "IA",
                              "PAR0",  "PAR1",  "PAR2",  "PAR3",  "PAR4",
                              "PAR5",  "PAR6",  "PAR7",  "PAR8",  "PAR9",
                              "PAR10", "PAR11", "PAR12", "PAR13", "PAR14",
                              "PAR15", "PAR16", "PAR17", "PAR18", "PAR19",
                              "PAR20", "PAR21", "PAR22", "PAR23", "PAR24",
                              "PAR25", "PAR26", "PAR27", "PAR28", "PAR29",
                              NULL};
   static double value;
   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Parameter name */
      if (tcsDcString(parnames, "parameter name: ", pcad->a, &param, pcad)) 
         break;

/* Parameter set */
      if (tcsDcString(setnames, "parameter set: ", pcad->b, &set, pcad)) break;

/* Local is only valid for CA & CE */
      if ( set == 1 && param > 1 ) {
          tcsCsAppendMessage( pcad, "LOCAL not valid for ");
          tcsCsAppendMessage( pcad, pcad->a);
          break;
      }

/* Parameter value */
       if (tcsDcDouble("value: ", pcad->c, &value, pcad)) break;

       if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      strcpy(pcad->vala, parnames[param]);
      strcpy(pcad->valb, setnames[set]);
      *(double *) pcad->valc = (double)value;

/* Copy set and name indexes and value to output links */
      *(long *) pcad->vald = (long)(set + 1);
      *(long *) pcad->vale = (long)(param + 1);
      *(double *) pcad->valf = (double)value;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADtimeParam
 *
 *   Purpose:
 *   Set a time sysytem parameter
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Parameter name
 *   b - Parameter value
 *
 *   Invocation:
 *   tcsCADtimeParam(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADtimeParam(struct cadRecord *pcad)
{
   static int param;
   static char *parnames[] = {"XPM", "YPM", "DJMLS", "DELAT", "DELUT", NULL};
   static double value;
   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Parameter name */
      if (tcsDcString(parnames, "parameter name: ", pcad->a, &param, pcad)) 
         break;

/* Parameter value */
       if (tcsDcDouble("value: ", pcad->b, &value, pcad)) break;

/* Check for sane value. */
       if ( param <= 1 && fabs(value) > 1.0 ) {
          tcsCsAppendMessage( pcad, "polar motion out of range");
          break;
       }
       if ( param == 2 && value < 1.0 ) {
          tcsCsAppendMessage( pcad, "djmls out of range");
          break;
       }
       if ( param == 3 && ( value < 0.0 || value > 1000.0 ) ) {
          tcsCsAppendMessage( pcad, "TAI-UTC out of range");
          break;
       }
       if ( param == 3 && dmod(value, 1.0) != 0.0) {
           tcsCsAppendMessage( pcad, "TAI-UTC not integral");
          break;
       }
       if ( param == 4 && fabs(value) > 1.0) {
           tcsCsAppendMessage( pcad, "UT1-UTC out of range");
          break;
       }

       if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      strcpy(pcad->vala, parnames[param]);
      *(double *) pcad->valb = (double)value;

/* Copy name index and value to output links */
      *(long *) pcad->valc = (long)(param + 1);
      *(double *) pcad->vald = (double)value;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADgenericCad
 *
 *   Purpose:
 *   Implements a CAD record with no parameters
 *
 *   Description:
 *
 *   Method:
 *   This CAD has no input parameters
 *
 *   Invocation:
 *   tcsCADgenericCad(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADgenericCad(struct cadRecord *pcad)
{
   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
    
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
      break;

   case menuDirectiveSTART:
      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

   return (status);
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADairmassLimit
 *
 *   Purpose:
 *   Set airmass limit
 *
 *   Description:
 *
 *   Method:
 *   The user specified airmass limit is checked for validity. If the value
 *   is within range then the corresponding elevation is computed. This
 *   uses a linearised form of the slaAirmas routine. The airmass limit
 *   is output to each of the EPICS records that needs it.
 *
 *   Epics inputs:
 *
 *   a => Airmass limit
 *
 *   Epics outputs:
 *
 *   vala => airmass limit
 *
 *   Invocation:
 *   tcsCADairmassLimit(pcad)
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
 *   Deficiencies:
 *-
 */
/* *INDENT-ON* */

long tcsCADairmassLimit(struct cadRecord *pcad)
{
   static double value;
   static int dbgLevel = DBG_NONE ;
   double tnow ;                    /* Time now */
   int status;

/* Check for interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Copy name of CAD for messages */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {
   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Limit */
      if (tcsDcDouble("value: ", pcad->a, &value, pcad)) break;

/* Check for sane value */
      if ( value < 1.0 || value > 4.0 ) {
         tcsCsAppendMessage( pcad, "airmass out of range");
         break;
      }

      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;
      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      *(double *) pcad->vala = (double)value;

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                         /* End of switch statement */

/* Add a debug statement for ST02000 */

   (void)timeNow (&tnow) ;
   DBGMSGREAL (DBG_FULL, "tcsAirmassLimit: completed at ", tnow) ;
   return (status);
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADclipAtLimit
 *
 *   Purpose:
 *   Set ClipAtLimit flag
 *
 *   Description:
 *
 *   Method:
 *   The input links are assumed to have the following data:
 *
 *   a - Clip at limit flag (On|Off)
 *
 *   Invocation:
 *   tcsCADclipAtLimit(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *
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
/* *INDENT-ON* */

long tcsCADclipAtLimit(struct cadRecord *pcad)
{
   int flag;                  /* Input desired position angle */
   static struct ICAD_FIELD clipAtLimit;
   int status;

/* Check for any interlocks */
   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT;
   switch (pcad->dir) {

   case menuDirectivePRESET:
      status = CAD_REJECT;

/* Get flag value */
      if (tcsDcOnOff("flag: ", pcad->a, &flag, pcad))
         break;

/* Set the data in the configuration block and mark this command as part
   of a configuration */
      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;
      status = CAD_ACCEPT;

      clipAtLimit.val = flag;
      clipAtLimit.field = 'A';
      strncpy(clipAtLimit.instring, pcad->a, MAX_STRING_SIZE);

      tcsConfigSetClipAtLimit(&clipAtLimit);

      break;

   case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
      strcpy(pcad->vala, clipAtLimit.val ? "On" : "Off");

      break;

   case menuDirectiveMARK:
      break;

   case menuDirectiveSTOP:
      break;

   case menuDirectiveCLEAR:
      break;

   default:
      break;

   }                            /* End of switch statement */

   return (status);

}


/*+
 *   Function name:
 *   tcsFollowString
 *
 *   Purpose:
 *   Output binary value for subsystem Follow status
 *
 *   Description:
 *   The expected input value is the string "On". If this is the case then
 *   the value 1 is output. Some TCS subsystems (e.g. the SCS) use the
 *   values "NO" and "YES" for the values of followS. Although not strictly
 *   allowed, these values are tolerated.  
 *
 *   Invocation:
 *   tcsFollowString
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

long tcsFollowString (struct genSubRecord *pgsub)
{
   char fstring[MAX_STRING_SIZE] ;
   
   tcsDcUc (pgsub->a, MAX_STRING_SIZE, fstring);

/* value output is TRUE if input string was "On" */ 
   if ((strncmp(fstring, "ON", 2) == 0) || 
       (strncmp(fstring, "YES", 3)  == 0) )
     *(long *)pgsub->vala = 1 ;
   else
     *(long *)pgsub->vala = 0;
   return(0);
}

/*+
 *   Function name:
 *   tcsFollowStat
 *
 *   Purpose:
 *   Store the follow state of the peripheral probes
 *
 *   Description:
 *   This is a simple wrapper for the tcsProbeSetFollowFlag routine. It
 *   just stores the peripheral probe follow status. 
 *
 *   Invocation:
 *   tcsFollowStat
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Epics inputs:
 *   a = > probe number (0 or 1)
 *   b = > follwo status ( 0 or 1)
 *
 *   Prior requirements:
 *   None
 *
 *-
 */

long tcsFollowStat (struct genSubRecord *pgsub)
{
   long probe ;
   long following ;

   probe = *(long *)pgsub->a ;
   following = *(long *)pgsub->b ;
   tcsProbeSetFollowFlag(probe, following);

   return(0);
}


/*+
 *   Function name:
 *   tcsCADzeroFocusGuide
 *
 *   Purpose:
 *   Sets any DC focus error to zero
 *
 *   Description:
 *   DC focus errors measured by the WFS and sent to M2 can be off loaded 
 *   onto the TCS by issuing the m2GuideMode command. If at some later 
 *   time it is required to zero these errors then this command can be
 *   issued.
 *
 *   Invocation:
 *   tcsCADzeroFocusGuide (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     none 
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsSetM2ZError (tcsOptics)  Set error term in M2 Z demand
 *
 *-
 */

long tcsCADzeroFocusGuide (struct cadRecord *pcad)

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

    tcsOpticsSetM2ZError (0.0) ;

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
 *   tcsCADzeroRotGuide
 *
 *   Purpose:
 *   Clears any rotator guiding corrections by setting them to zero.
 *
 *   Description:
 *   Corrections to the rotator position can come from the GeMS system.
 *   This command is provided to set those corrections back to zero. This
 *   may be useful if the corrections have become contaminated with bad data
 *   or if they need to be reset immediately without waiting for them
 *   to integrate back to zero.
 *
 *   Invocation:
 *   tcsCADzeroRotGuide (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     none 
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADzeroRotGuide (struct cadRecord *pcad)

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

    tcsZeroRotCorr () ;

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
 *   tcsCADzeroComaCorr
 *
 *   Purpose:
 *   Set any translation offsets for Coma to zero
 *
 *   Description:
 *   Any coma errors measured by the WFS are converted to equivalent 
 *   translations of M2. These translation offsets can be set to zero
 *   with this command.
 *
 *   Invocation:
 *   tcsCADzeroComaCorr (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     none 
 *
 *   EPICS output parameters:
 *     none
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsOpticsM2ClearComa (tcsOptics) Zero corrections to M2 x,y transations 
 *
 *-
 */

long tcsCADzeroComaCorr (struct cadRecord *pcad)

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

    tcsOpticsM2ClearComa() ;

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
 *   tcsCADwfsGuideMode
 *
 *   Purpose:
 *   Set guide mode for the wfs probes
 *
 *   Description:
 *   This routine implements the wfsGuideMode command in the TCS. The
 *   routine sets up the two different types of probe guiding. In the 
 *   first type the error from the WFS is fed back to its own probe.
 *   This was the original type of probe guiding and is used to centre
 *   a guide star on the WFS. This is useful when the guide target doesn't
 *   fall exactly on the center of the WFS due to e.g. slightly inaccurate
 *   coordinates etc.
 *   In the second type of probe guiding, an error signal from an OIWFS is
 *   fed back to a peripheral PWFS. This is for use when both an OIWFS 
 *   and a PWFS are in use. These will be working in different bandwidth
 *   regimes for example and then the OIWFS wants to offload a DC signal.
 *   This might arise for example from differential flexure between the OIWFS
 *   and the PWFS. 
 *
 *   Invocation:
 *   tcsCADwfsGuideMode
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => absorb wfs errors (On/Off) 
 *      b => source of guide probe signal (PWFS1/PWFS2/OIWFS)
 *      c => destination of guide probe signal (PWFS1/PWFS2/OIWFS)
 *
 *   EPICS output parameters:
 *      vala => absorb wfs errors status (On/Off) 
 *      valb => source guide signal (PWFS1/PWFS2/OIWFS)
 *      valc => guide enable switch
 *      vald => probe number to guide (1..3)
 *      vale => normalized pwfs1 input weight
 *      valf => normalized pwfs2 input weight
 *      valg => normalized oiwfs input weight
 *      valh => destination guide signal (PWFS1/PWFS2/OIWFS)
 *      vali => sign +1 or -1
 *      valj => Flag (0/1) to show if P1 is probe guiding
 *      valk => Flag (0/1) to show if P2 is probe guiding
 *      vall => Flag (0/1) to show if OI is probe guiding
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */

long tcsCADwfsGuideMode (struct cadRecord *pcad)

{

/* TODO - enhance for generic guiders ? vald will become 1..7 */

  long status ;           /* Return status */
  static int flag ;       /* 1 = enabled, 0 = disabled */
  char *probenames[] = { "PWFS1", "PWFS2", "OIWFS", NULL };
  static int insignal;
  static int outsignal;
  static char outname[MAX_STRING_SIZE];
  double sign ;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

/* In the PRESET stage the CAD inputs must all be checked for validity. Note
*  that any values derived from the inputs which are also required at the
*  menuDirectiveSTART stage must be declared static.
*/

   case menuDirectivePRESET :

   status = CAD_REJECT ;
   if (tcsDcOnOff ("flag: ", pcad->a, &flag, pcad))
      break ;

/* Its only necessary to check the remaining parameters if we are
*  switching on the guide mode
*/
   if (flag) {
     if (tcsDcString (probenames, "in: ", pcad->b, &insignal, pcad))
        break;

/* For backwards compatibility when the output destination was always
*  the same as input source, if the C field isn't specfied then make
*  it the same as the B field
*/ 
     if (!tcsDcLen(pcad->c)) {
       outsignal = insignal;
       strcpy(outname, pcad->b);
     } else {
       if (tcsDcString (probenames, "out: ", pcad->c, &outsignal, pcad))
          break;
       strcpy(outname, pcad->c);
     }

/* Now check for valid combinations */
     if (insignal == outsignal || insignal == 2) {     /* Let these through */
     } else {
       tcsCsAppendMessage( pcad, "invalid in/out combination");
       break;
     }
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (!status)
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :
 
    strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
    if ( flag ) {
       *(long *)pcad->valc = 1 ;
       if ( insignal == 0 ) {
          *(long *)pcad->vald = outsignal + 1 ;
          *(double *)pcad->vale = 1.0;
          *(double *)pcad->valf = 0.0;
          *(double *)pcad->valg = 0.0;
       } else if ( insignal == 1 ) {
          *(long *)pcad->vald = outsignal + 1 ;
          *(double *)pcad->vale = 0.0;
          *(double *)pcad->valf = 1.0;
          *(double *)pcad->valg = 0.0;
       } else if ( insignal == 2 ) {
          *(long *)pcad->vald = outsignal + 1 ;
          *(double *)pcad->vale = 0.0;
          *(double *)pcad->valf = 0.0;
          *(double *)pcad->valg = 1.0;
       }
       if (insignal == outsignal) {
         sign = 1.0;
       } else {
         sign = -1.0;
       }
       if (outsignal == 0){
         *(double *)pcad->valj = 1.0;
         *(double *)pcad->valk = 0.0;
         *(double *)pcad->vall = 0.0;
       } else if (outsignal == 1) {
         *(double *)pcad->valj = 0.0;
         *(double *)pcad->valk = 1.0;
         *(double *)pcad->vall = 0.0;
       } else {
         *(double *)pcad->valj = 0.0;
         *(double *)pcad->valk = 0.0;
         *(double *)pcad->vall = 1.0;
       }
       *(double *)pcad->vali = sign ;  
       strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE);
       strncpy(pcad->valh, outname, MAX_STRING_SIZE);
    } else {
       *(long *)pcad->valc = 0 ;
       *(long *)pcad->vald = 0 ;
       *(double *)pcad->vale = 0.0 ;
       *(double *)pcad->valf = 0.0 ;
       *(double *)pcad->valg = 0.0 ;
       *(double *)pcad->valj = 0.0;
       *(double *)pcad->valk = 0.0;
       *(double *)pcad->vall = 0.0;
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

/* Function to set thread priorities on the fly */
void tcsThreadSetPriority(const char *tName, unsigned int priority)
{
    epicsThreadId id;
    int oldPrio;
    
    if (!(id = epicsThreadGetId(tName)))
    {
        printf("%s: Thread not found\n", tName);
        return;
    }
    else{
        oldPrio = epicsThreadGetPriority(id);
        epicsThreadSetPriority(id, priority);
        printf("Thread %s priority changed. Old: %d --> New: %d\n", tName, oldPrio, priority);
        return;
    }
}

static const iocshArg tspArg0 = {"Thread name", iocshArgString};
static const iocshArg tspArg1 = {"New Priority", iocshArgInt };

static const iocshArg *tspArgs[] = {&tspArg0, &tspArg1};

static const iocshFuncDef tcsThreadSetPriorityFuncDef = {"tcsThreadSetPriority", 2, tspArgs};

static void tcsThreadSetPriorityCallFunc(const iocshArgBuf *args)
{
    tcsThreadSetPriority(args[0].sval, args[1].ival);
}

static void registerTcsThreadSetPriorityCommands(void)
{
    iocshRegister(&tcsThreadSetPriorityFuncDef, tcsThreadSetPriorityCallFunc);
}

epicsExportRegistrar(registerTcsThreadSetPriorityCommands);

epicsRegisterFunction(tcsCADm2ComaCorr);
epicsRegisterFunction(tcsCADdebug);
epicsRegisterFunction(tcsCADmountGuideMode);
epicsRegisterFunction(tcsCADunfollowAll);
epicsRegisterFunction(tcsCADm2GuideMode);
epicsRegisterFunction(tcsCADm2ComaModel);
epicsRegisterFunction(tcsCADzeroRotGuide);
epicsRegisterFunction(tcsCADwfsGuideMode);
epicsRegisterFunction(tcsCADstopGuideAll);
epicsRegisterFunction(tcsCADm1GuideConfig);
epicsRegisterFunction(tcsCADfilter1);
epicsRegisterFunction(tcsCADfilter2);
epicsRegisterFunction(tcsCADm1ModelSave);
epicsRegisterFunction(tcsCADrotGuideConfig);
epicsRegisterFunction(tcsCADpointParam);
epicsRegisterFunction(tcsCADguiderConfig);
epicsRegisterFunction(tcsCADm2NomPosn);
epicsRegisterFunction(tcsCADazwrap);
epicsRegisterFunction(tcsCADgsaoiodgwSetup);
epicsRegisterFunction(tcsCADrotGuideMode);
epicsRegisterFunction(tcsCADtimeParam);
epicsRegisterFunction(tcsCADplanet);
epicsRegisterFunction(tcsCADzeroComaCorr);
epicsRegisterFunction(tcsCADstopAll);
epicsRegisterFunction(tcsCADoptPointAdj);
epicsRegisterFunction(tcsCADsave);
epicsRegisterFunction(tcsCADrotwrap);
epicsRegisterFunction(tcsCADtcbdefn);
epicsRegisterFunction(tcsCADm1FigUpdates);
epicsRegisterFunction(tcsCADoiwfsSelect);
epicsRegisterFunction(tcsCADzeroFocusGuide);
epicsRegisterFunction(tcsCADconfigureForAO);
epicsRegisterFunction(tcsCADload);
epicsRegisterFunction(tcsCADclipAtLimit);
epicsRegisterFunction(tcsCADfollow);
epicsRegisterFunction(tcsCADairmassLimit);
epicsRegisterFunction(tcsFollowStat);
epicsRegisterFunction(tcsCADgenericCad);
epicsRegisterFunction(tcsCADorbit);
epicsRegisterFunction(tcsCADrotator);
epicsRegisterFunction(tcsCADodgwDatum);
epicsRegisterFunction(tcsCADodgwFollow);
epicsRegisterFunction(tcsCADodgwPark);
epicsRegisterFunction(tcsCADcarouselMode);
epicsRegisterFunction(tcsCADprobeFocus);
epicsRegisterFunction(tcsCADfocusTempAdj);
epicsRegisterFunction(tcsCADabortAll);
epicsRegisterFunction(tcsCADsetProbeLimits);
epicsRegisterFunction(tcsCADm1ModelRestore);
epicsRegisterFunction(tcsCADm1GuideMode);
epicsRegisterFunction(tcsFollowString);
epicsRegisterFunction(tcsCADodgwMove);
