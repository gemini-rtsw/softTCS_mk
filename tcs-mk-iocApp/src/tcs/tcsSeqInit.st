/*
*   FILENAME
*   tcsSeqInit.stpp
*
*   FUNCTION NAME(S)
*   This file contains the main initialisation and monitoring sequence
*   for the TCS.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSeqInit.st,v $
 * Revision 1.25  2013/10/31 13:32:20  cjm
 * New A&G simulator prefix
 *
 * Revision 1.24  2013/10/15 12:34:01  cjm
 * Only save if open and closed loop M1 correctionsare available, use new routines to check file to save to
 *
 * Revision 1.23  2013/09/11 15:38:45  cjm
 * Add support for saving GPI M1 corrections
 *
 * Revision 1.22  2013/08/16 20:50:38  gemvx
 * Fixed bug where M1 figure was saved to AO file if AO position was park-pos.
 *
 * Revision 1.21  2012/10/04 13:32:08  cjm
 * Updates to support save/restore of AO specific M1 models
 *
 * Revision 1.20  2011/01/26 15:14:17  cjm
 * Leave fast loop passive and set scan on fastscan instead
 *
 * Revision 1.19  2010/11/29 14:08:24  cjm
 * Update chip limits and set initial ODGW positions
 *
 * Revision 1.18  2010/07/28 12:39:02  cjm
 * Trigger the slow loop at startup
 *
 * Revision 1.17  2010/05/27 07:32:00  cjm
 * Update variable names to reflect center not corner of ODGW
 *
 * Revision 1.16  2010/04/13 16:00:53  cjm
 * Use gsaoiState record in TCS - GSAOI state is a string
 *
 * Revision 1.15  2010/02/26 18:51:37  gemvx
 * use new names for GSAOI parameters
 *
 * Revision 1.14  2009/12/01 13:37:01  cjm
 * Add support for fetching and setting ODGW parameters
 *
 * Revision 1.13  2008/10/07 12:26:02  cjm
 * Change time limit scan to 0.2 seconds
 *
 * Revision 1.12  2008/05/01 15:17:26  cjm
 * Add code to retrieve the rotary table limits
 *
 * Revision 1.11  2007/12/18 10:11:34  cjm
 * Add state sets for aom and gsaoi
 *
 * Revision 1.10  2005/06/30 14:26:11  cjm
 * Fix bug causing infinite loop if M1 not present
 *
 * Revision 1.9  2005/05/09 22:39:43  gemvx
 * Define ao macro
 *
 * Revision 1.8  2003/07/09 10:47:56  cjm
 * Add control of save and restore of M1 optics model
 *
 * Revision 1.7  2003/04/03 13:59:00  cjm
 * Add code to check for faulty Rmax on startup
 *
 * Revision 1.6  2002/11/08 12:02:09  cjm
 * Set limits for Altair probe
 *
 * Revision 1.5  2002/09/24 16:08:28  cjm
 * Fix to get round lack of Altair limit records
 *
 * Revision 1.4  2002/04/17 13:13:30  cjm
 * Add default gp macro and full name of state record
 *
 * Revision 1.3  2001/10/05 09:16:56  cjm
 * Fetch and set oiwfs transformation coefficients
 *
 * Revision 1.2  2001/09/25 16:35:32  ptaylor
 * Add new state set to handle GPOL states; add GPOL handling in master ss
 *
 * Revision 1.1  2001/05/24 11:15:28  cjm
 * Renamed from tcsSeqInit.stpp
 *
 * Revision 1.10  2000/08/18 16:07:26  cjm
 * Add code for Altair
 *
 * Revision 1.9  2000/03/27 06:19:33  cjm
 * Rearrange pv calls to cope with fact that pvGet can faiilently if a channel isn't connected
 *
 * Revision 1.8  1999/03/24 00:37:46  dlt
 * Enable limits scan after starting kernel loops
 *
 * Revision 1.7  1999/03/01 09:22:05  cjm
 * Add further when clause for AO. This was needed to fix a bug that was only revealed by previous update. The result was the TCS got stuck in init
 *
 * Revision 1.6  1999/02/27 05:36:15  cjm
 * Commit bug fixes found by Andy & Dave
 *
 * Revision 1.5  1999/01/21 01:00:48  dlt
 * remove unused simulate flags and add missing AO cases
 *
 * Revision 1.4  1999/01/19 20:50:08  cjm
 * Set fast loop speed to 10 rahter than 20 hz
 *
 * Revision 1.3  1998/12/18 09:03:00  epics
 * Initialise scan rate of ECS drive record and disable enclosure following when the MCS is shut down
 *
 * Revision 1.2  1998/11/19 21:21:23  cjm
 * Connect to standard MCS record names rather than ports on a genSub record
 *
 * Revision 1.1.1.1  1998/11/08 00:21:08  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.28  1998/09/16 00:54:03  tcs
 * Set user limits for WFS probe positions
 *
 * Revision 1.27  1998/09/05 03:27:09  tcs
 * Add better handling of probe limits
 *
 * Revision 1.26  1998/05/19 13:53:15  cjm
 * Disable automoves on reboot of ECS
 *
 * Revision 1.25  1998/04/07 20:48:32  cjm
 * Change timeout period for ECS
 *
 * Revision 1.24  1998/04/01 15:34:43  cjm
 * Improved handling of ECS reboot
 *
 * Revision 1.23  1998/03/31 11:23:32  cjm
 * Changes to accommodate ECS gamma release of March 98
 *
 * Revision 1.22  1998/02/12 16:30:51  pbt
 * Trigger state sets init AFTER pvload; add setting of AO init flag
 *
 * Revision 1.21  1998/01/22 15:28:36  tcs
 * Correct EC timeout handling
 *
 * Revision 1.20  1998/01/21 17:27:43  pbt
 * Handle INIT actions failure
 *
 * Revision 1.19  1997/12/04 17:03:21  pbt
 * Changed oiwfs: to oi:
 *
 * Revision 1.18  1997/12/04 15:23:10  tcs
 * Change rpa to rma
 *
 * Revision 1.17  1997/12/01 16:32:01  pbt
 * Set simulator control initially True if simulation is on
 *
 * Revision 1.16  1997/11/17 14:45:06  pbt
 * New naming convention for A&G subsystem probe position records
 *
 * Revision 1.15  1997/11/13 13:25:20  tcs
 * Revised guide star scheme
 *
 * Revision 1.14  1997/11/04 10:35:59  pbt
 * Added aos, AO startup state set
 *
 * Revision 1.13  1997/10/21 16:52:03  pbt
 * Changed handling of TCS state and init CAR value. Added timeout printf's
 *
 * Revision 1.12  1997/10/02 14:23:09  pbt
 * Add set/unset dbLoading flag record
 *
 * Revision 1.11  1997/09/16 11:07:21  cjm
 * Update to agree with latest TCS/ECS ICD
 *
 * Revision 1.10  1997/07/23 13:26:50  cjm
 * Fetch and monitor ECS shutter limits
 *
 * Revision 1.9  1997/07/15 13:39:30  cjm
 * Add variables for ECs initialisation
 *
 * Revision 1.8  1997/07/10 12:34:53  tcs
 * Implement times to limits
 *
 * Revision 1.7  1997/07/02 15:47:23  pbt
 * Amended default subsystem prefixes : now in lowercase
 *
 * Revision 1.6  1997/06/26 10:10:15  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.5  1997/06/02 09:58:29  tcs
 * Add slew CAD
 *
 * Revision 1.4  1997/04/25 16:48:51  pbt
 * CHnaged name of Simulate record
 *
 * Revision 1.3  1997/04/22 15:18:28  tcs
 * Copy rpa to initrpa
 *
 * Revision 1.2  1997/03/24 15:18:21  cjm
 * Use new limit routines on M2 startup
 *
 * Revision 1.1  1997/02/10 17:11:10  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.24  1997/02/10 14:44:45  pbt
 * Changes to allow initialization (pvload etc) for INIT sequence command
 *
 * Revision 1.23  1997/01/17 12:36:39  pbt
 * Amended programs to handle redefined init & removed reset sequence commands
 *
 * Revision 1.22  1997/01/16 10:44:42  cjm
 * Add support for tip/tilt/focus models of M2
 *
 * Revision 1.21  1997/01/14 16:33:43  cjm
 * Initialise M2 open loop model
 *
 * Revision 1.20  1997/01/09 21:35:13  cjm
 * Make chop state A the default for all probes
 *
 * Revision 1.19  1997/01/08 09:36:37  cjm
 * set a default chop state for probe to follow
 *
 * Revision 1.18  1996/12/13 10:07:57  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.17  1996/12/12 15:53:35  cjm
 * Updates in preparation for better probe handling
 *
 * Revision 1.16  1996/12/04 09:16:27  tcs
 * scan medfasttrig instead of medfast
 *
 * Revision 1.15  1996/12/02 11:07:09  tcs
 * Add medium fast loop
 *
 * Revision 1.14  1996/12/02 08:09:10  cjm
 * Fixes for initial az, el and debug level
 *
 * Revision 1.13  1996/11/29 08:28:51  cjm
 * Add support for debug command
 *
 * Revision 1.12  1996/11/04 08:17:05  cjm
 * Handle initialisation of probe positions
 *
 * Revision 1.11  1996/10/21 13:47:54  cjm
 * Fetch initialisation data from SCS
 *
 * Revision 1.10  1996/09/26 10:24:02  tcs
 * Initialise Init & Reset event flags
 *
 * Revision 1.9  1996/07/25 12:49:17  cjm
 * replace state init by state initialising
 *
 * Revision 1.8  1996/07/23 18:02:27  pbt
 * Reacts to TCS reset/init CADs. Reboots on init when all subsystems IDLE
 *
 * Revision 1.7  1996/07/19 15:34:53  cjm
 * Modifications for handling of configurations
 *
 * Revision 1.6  1996/07/19 13:47:03  tcs
 * add new simulators
 *
 * Revision 1.5  1996/07/09 13:18:11  tcs
 * revised track id logic and enhanced simulators
 *
 * Revision 1.4  1996/07/08 14:29:40  tcs
 * Implement track identifier scheme
 *
 * Revision 1.3  1996/06/17 07:29:42  cjm
 * Tidy up, add control of error term etc.
 *
 * Revision 1.2  1996/06/13 13:40:53  cjm
 * Restart fast loop
 *
 * Revision 1.1  1996/06/13 13:07:34  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

/*+ 
* Module:
* tcsSeqInit.stpp
*
* Purpose:
* Initialise and monitor the TCS subsystems
*
* Description:
* The program consists of a master state set plus a state set for each
* subsystem. The subsystem state set assigns variables to channels 
* depending on whether the subsystem is being simulated internally by
* the TCS or whether it needs to connect to the real subsystem. It then 
* waits for a connection to the appropriate database and then waits
* for the subsystem to reach the RUNNING state. After this it monitors
* for disconnect events and for the setting of an event flag to
* indicate it should restart itself. Timeouts and transitions to the
* RUNNING state are signalled via event flags to the master state set.
* It is the job of the master state set to initialise the TCS itself.
* This involves pulling in data from the subsystems when they come
* on line and then starting its pointing loops. If subsystems 
* are not available it will use default parameters to start the pointing
* loops. This is so the TCS can be started even if all its subsystems
* are not ready. 
*
* Invocation:
* The program is normally started as follows
*
* seq &tcsSeqInit
*
* Macro substitution can be used if records are in non-standard databases.
* E.g. if the mount database is prefixed by MCtest: rather than the 
* normal MC: then the program should be started with
*
* seq &tcsSeqInit "mc=MCtest:"
*
*-
*/

program tcsSeqInit ("top=tcs:, mc=mc:, cr=cr:, ec=ec:, m2=m2:, ag=ag:, gp=gp:, m1=m1:, ao=ao:, aom=aom:, gsaoi=gsaoi:, CONF_FILES_DIR=/gem_sw/etc/rtconfig/tcs")

option -c ;                    /* allow start prior to all connections */

/* Put all include files here */

#include "tcsSeqConstants.h"
#include "tcsSeqMacros.h"
%%#include "tcsConstants.h"

%%#include <string.h>
%%#include "tcsPointing.h"
%%#include "tcsSeqCommands.h"
%%#include "menuCarstates.h"
%%#include "tcsProbeLib.h"
%%#include "tcsGuide.h"
%%#include "tcsEcsLib.h"
%%#include <genSubRecord.h>
%%#include "tcsOptics.h"
%%#include "timeLib.h"

/* Need these to avoid warnings - there is no header file we can include
*  for pvload and pvsave but it is unlikely the calling interface will
*  ever change
*/
%{
int pvload (char *file, char *subst, int flags) ;
int pvsave (char *file , char *subst, char *outFile, int flags);
}%

/* Local defines go here */

%{
#define MARK 0
#define INIT 1
#define START 3
#define MAXLOOPS 20
#define MAX_PATH 256
}%


/* Local variables */

int i ;                             /* Loop counter */
int initStat;                       /* INIT command CAR status */
float loopDelay ;                   /* Loop delay (seconds) */
float waitTime[MAXSUBSYS] ;         /* Seconds waiting for connections */
float timeOutPeriod[MAXSUBSYS] ;    /* Timeout (seconds) for each subsystem */
int intSimulate[MAXSUBSYS] ;        /* Internal Simulation flags */
int applState[MAXSUBSYS] ;          /* Subsystem application state */
int done[MAXSUBSYS]  ;              /* flags to show subsystems are "ready" */
int timedOut[MAXSUBSYS] ;           /* flags to show subsystems timed out */
int pstat ;                         /* Status of pvload */

int semInitialized = FALSE ;        /* Flag to show if semaphores have been initialized */
int firstInit ;                     /* Flag to show first init has been done */
int m1ModelType ;                   /* non-AO or AO model */
double gsaoiChipXmin ;              /* Minimum X (pixels) */
double gsaoiChipXmax ;
double gsaoiChipYmin ;
double gsaoiChipYmax ;
double odgw1Xpos ;                  /* Position of target in ODGW 1 */
double odgw1Ypos ;                  /* Position of target in ODGW 1 */
double odgw2Xpos ;                  /* Position of target in ODGW 1 */
double odgw2Ypos ;                  /* Position of target in ODGW 1 */
double odgw3Xpos ;                  /* Position of target in ODGW 1 */
double odgw3Ypos ;                  /* Position of target in ODGW 1 */
double odgw4Xpos ;                  /* Position of target in ODGW 1 */
double odgw4Ypos ;                  /* Position of target in ODGW 1 */
string tcsPrefix ;                  /* Prefix for TCS database names */
string tcsPrefixSub ;               /* Substution string for Prefix when pvsaving */
string tcsPrefNoColon ;             /* Prefix for files */
string mcPrefix ;                   /* Prefix for MC database names */
string crPrefix ;                   /* Prefix for CR database names */
string ecPrefix ;                   /* Prefix for EC database names */
string m1Prefix ;                   /* Prefix for PCS database */
string m2Prefix ;                   /* Prefix for M2 database names */
string agPrefix ;                   /* Prefix for AG database names */
string aoPrefix ;                   /* Prefix for AO database names */
string gpPrefix ;                   /* Prefix for GPOL database names */
string aomPrefix ;                  /* Prefix for AOM database names */
string gsaoiPrefix ;                /* Prefix for GSAOI database names */
string mcDbName ;                   /* Name of MC database records */
string crDbName ;                   /* Name of CR database records */
string ecDbName ;                   /* Name of EC database records */
string m1DbName ;                   /* Name of M1 database records */
string m2DbName ;                   /* Name of M2 database records */
string agDbName ;                   /* Name of AG database records */
string aoDbName ;                   /* Name of AO database records */
string gpDbName ;                   /* Name of GPOL database records */
string aomDbName ;                  /* Name of AOM database records */
string gsaoiDbName ;                /* Name of GSAOI database records */
char confFileSave[MAX_PATH];
char confFileRest[MAX_PATH];
string CONF_FILES_DIR;


/* Event flags */
evflag m1Restore ;

evflag mcTimeOut ;
evflag crTimeOut ;
evflag ecTimeOut ;
evflag m1TimeOut ;
evflag m2TimeOut ;
evflag agTimeOut ;
evflag aoTimeOut ;
evflag gpTimeOut ;
evflag aomTimeOut ;
evflag gsaoiTimeOut ;
evflag mcRunning ;
evflag crRunning ;
evflag ecRunning ;
evflag m1Running ;
evflag m2Running ;
evflag agRunning ;
evflag aoRunning ;
evflag gpRunning ;
evflag aomRunning ;
evflag gsaoiRunning ;
evflag mcSeqInit ;
evflag crSeqInit ;
evflag ecSeqInit ;
evflag m1SeqInit ;
evflag m2SeqInit ;
evflag agSeqInit ;
evflag aoSeqInit ;
evflag gpSeqInit ;
evflag aomSeqInit;
evflag gsaoiSeqInit ;

/* Simulator control flag */
string mcScanControl ;                 /* Simulator scan On/Off for MC */
string crScanControl ;                 /* Simulator scan On/Off for CR */
string ecScanControl ;                 /* Simulator scan On/Off for EC */
string m1ScanControl ;                 /* Simulator scan On/Off for M2 */
string m2ScanControl ;                 /* Simulator scan On/Off for M2 */
string agScanControl ;                 /* Simulator scan On/Off for AG */
string aoScanControl ;                 /* Simulator scan On/Off for AO */
string aomScanControl ;                /* Simulator scan On/Off for AOM */
string gsaoiScanControl ;              /* Simulator scan on/off for GSAOI */
assign mcScanControl to "" ;
assign crScanControl to "" ;
assign ecScanControl to "" ;
assign m1ScanControl to "" ;
assign m2ScanControl to "" ;
assign agScanControl to "" ;
assign aoScanControl to "" ;
assign aomScanControl to "" ;
assign gsaoiScanControl to "" ;


/* SNC assignments */

ASSVAR ( int, tcsName, "{top}name.PROC") ;
ASSVAR ( int, tcsState, "{top}state" ) ;
ASSVAR ( int, tcsInitCarIval, "{top}initC.IVAL" ) ;
ASSVAR ( string, tcsInitCarImss, "{top}initC.IMSS" ) ;
ASSVAR ( int, dbReloading, "{top}dbReloading" ) ;
ASSVAR ( int, go, "{top}ak:init" ) ;
ASSVAR ( int, goM, "{top}ak:mediuminit" ) ;
ASSVAR ( int, setEcsDefs, "{top}def:updateEcsDefs.PROC" );
ASSVAR ( int, goS, "{top}ak:slow.PROC" );
ASSVAR ( string, goM2XY, "{top}om:m2XYStartLoop" );
ASSVAR ( string, goM2Tilt, "{top}om:m2TiltStartLoop" );
ASSVAR ( string, slowScan, "{top}ak:slowtrig.SCAN" ) ;
ASSVAR ( string, limitsScan, "{top}limits:trig.SCAN" ) ;
ASSVAR ( string, solsysScan, "{top}ak:solsys.SCAN" ) ;
ASSVAR ( string, mediumScan, "{top}ak:mediumtrig.SCAN" ) ;
ASSVAR ( string, medFastScan, "{top}ak:medfasttrig.SCAN" ) ;
ASSVAR ( string, fastScan, "{top}ak:fastscan.SCAN" ) ;
ASSVAR ( string, ecsScan, "{top}drives:driveECS.SCAN" ) ;
ASSVAR ( string, RADecScan, "{top}display:DisplayRADec.SCAN" ) ;
ASSVAR ( string, limitsEnable, "{top}limits:times.DISA" ) ;
ASSVAR ( double, defrma, "{top}rmadef" ) ;
ASSVAR ( double, defAz, "{top}azdef" ) ;
ASSVAR ( double, defEl, "{top}eldef" ) ;
ASSVAR ( double, initAz, "{top}ak:initaz" ) ;
ASSVAR ( double, initEl, "{top}ak:initel" ) ;
ASSVAR ( double, initRma, "{top}ak:initrma") ;
ASSVAR ( double, initRmaF, "{top}ak:fast.B") ;
ASSVAR ( double, initRmaVel, "{top}ak:fast.C" ) ;
MONVAR ( int,    m1GuideOn, "{top}im:m1GuideOn" ) ;
MONVAR ( int,    m1FigUpdates, "{top}im:m1FigUpdatesFlag" ) ;
ASSVAR ( string, m1GuideModeA, "{top}m1GuideMode.A" ) ;
ASSVAR ( int,    m1GuideModeDIR, "{top}m1GuideMode.DIR" ) ;
ASSVAR ( string, m1FigUpdatesA, "{top}m1FigUpdates.A" ) ;
ASSVAR ( int,    m1FigUpdatesDIR, "{top}m1FigUpdates.DIR" ) ;
ASSVAR ( int,    m1ModelRestore, "{top}m1ModelRestore" ) ;
ASSVAR ( int,    m1CommSentC, "{top}m1CommSentC" );
ASSVAR ( string, m1CommSentMsg, "{top}m1CommSentC.IMSS" ) ;
MONVAR ( int,    m1RestoreTrigger, "{top}m1ModelRestorebusy" );
MONVAR ( double, pwfs1UserRmin, "{top}pwfs1Rmin" ) ; 
MONVAR ( double, pwfs1UserRmax, "{top}pwfs1Rmax" ) ; 
MONVAR ( double, pwfs2UserRmin, "{top}pwfs2Rmin" ) ; 
MONVAR ( double, pwfs2UserRmax, "{top}pwfs2Rmax" ) ; 
ASSVAR ( string, logrecord, "{top}logrecord" ) ;
/* The following assignments are temporary. If a command is added to
*  allow the user to set user limits on the patrol area of the OIWFS
*  then it will be neccessary to do something similar to what is
*  done for the PWFS
*/
ASSVAR (double, oiwfsUserRmin, "{top}sad:oiwfsRmin" ) ;
ASSVAR (double, oiwfsUserRmax, "{top}sad:oiwfsRmax" ) ;
ASSVAR (double, oiwfsUserXmin, "{top}sad:oiwfsXmin" ) ;
ASSVAR (double, oiwfsUserXmax, "{top}sad:oiwfsXmax" ) ;
ASSVAR (double, oiwfsUserYmin, "{top}sad:oiwfsYmin" ) ;
ASSVAR (double, oiwfsUserYmax, "{top}sad:oiwfsYmax" ) ;
ASSVAR (int,    oiwfsUserLimitType, "{top}sad:oiwfsLimitType" ) ;

/* As for the OIWFS, until we add a command to allow user limits
*  to be set for Altair etc., set the SAD limits directly from this sequence
*  program.
*/
ASSVAR (double, aoUserXmin, "{top}sad:aoXmin" ) ;
ASSVAR (double, aoUserXmax, "{top}sad:aoXmax" ) ;
ASSVAR (double, aoUserYmin, "{top}sad:aoYmin" ) ;
ASSVAR (double, aoUserYmax, "{top}sad:aoYmax" ) ;

ASSVAR (double, aomPr1UserXmin, "{top}sad:aomPr1Xmin" ) ;
ASSVAR (double, aomPr1UserXmax, "{top}sad:aomPr1Xmax" ) ;
ASSVAR (double, aomPr1UserRmin, "{top}sad:aomPr1Rmin" ) ;
ASSVAR (double, aomPr1UserRmax, "{top}sad:aomPr1Rmax" ) ;

ASSVAR (double, aomPr2UserXmin, "{top}sad:aomPr2Xmin" ) ;
ASSVAR (double, aomPr2UserXmax, "{top}sad:aomPr2Xmax" ) ;
ASSVAR (double, aomPr2UserRmin, "{top}sad:aomPr2Rmin" ) ;
ASSVAR (double, aomPr2UserRmax, "{top}sad:aomPr2Rmax" ) ;

ASSVAR (double, aomPr3UserXmin, "{top}sad:aomPr3Xmin" ) ;
ASSVAR (double, aomPr3UserXmax, "{top}sad:aomPr3Xmax" ) ;
ASSVAR (double, aomPr3UserRmin, "{top}sad:aomPr3Rmin" ) ;
ASSVAR (double, aomPr3UserRmax, "{top}sad:aomPr3Rmax" ) ;

/* default data for M2. Only used if the TCS can't connect to M2 */

ASSVAR ( double, defM2MinChopFreq, "{top}def:m2MinChopFreq" ) ;
ASSVAR ( double, defM2BreakChopFreq, "{top}def:m2BreakChopFreq" ) ;
ASSVAR ( double, defM2MaxChopFreq, "{top}def:m2MaxChopFreq" ) ;
ASSVAR ( double, defM2MinChopFreqThrow, "{top}def:m2MinChopFreqThrow" ) ;
ASSVAR ( double, defM2BreakChopFreqThrow, "{top}def:m2BreakChopFreqThrow" ) ;
ASSVAR ( double, defM2MaxChopFreqThrow, "{top}def:m2MaxChopFreqThrow" ) ;
ASSVAR ( double, defM2MinTilt, "{top}def:m2MinTilt" ) ;
ASSVAR ( double, defM2MaxTilt, "{top}def:m2MaxTilt" ) ;
ASSVAR ( double, defM2MinTiltZ, "{top}def:m2MinTiltZ" ) ;
ASSVAR ( double, defM2MaxTiltZ, "{top}def:m2MaxTiltZ" ) ;
ASSVAR ( string, defTopEnd, "{top}defTopEnd" ) ;

/* default data for the enclosure. Only used if TCS can't connect to ECS */

ASSVAR (double, defMinBotShtr, "{top}def:minBotShtr" ) ;
ASSVAR (double, defMaxBotShtr, "{top}def:maxBotShtr" ) ;
ASSVAR (double, defMinTopShtr, "{top}def:minTopShtr" ) ;
ASSVAR (double, defMaxTopShtr, "{top}def:maxTopShtr" ) ;
ASSVAR (double, defDomePos,    "{top}def:domePos" ) ;
ASSVAR (double, defBotShtrPos, "{top}def:botShtrPos" );
ASSVAR (double, defTopShtrPos, "{top}def:topShtrPos") ;

/* default data for the A&G. Only used if the TCS can't initially connect */

ASSVAR (double, defPwfs1Rmin, "{top}def:pwfs1Rmin") ;
ASSVAR (double, defPwfs1Rmax, "{top}def:pwfs1Rmax") ;
ASSVAR (double, defPwfs1Zmin, "{top}def:pwfs1Zmin") ;
ASSVAR (double, defPwfs1Zmax, "{top}def:pwfs1Zmax") ;
ASSVAR (double, defPwfs1Xposn, "{top}def:pwfs1Xposn") ;
ASSVAR (double, defPwfs1Yposn, "{top}def:pwfs1Yposn") ;
ASSVAR (double, defPwfs1Zposn, "{top}def:pwfs1Zposn") ;
ASSVAR (int,    defPwfs1LimitType, "{top}def:pwfs1LimitType") ;
ASSVAR (double, defPwfs1RTmin, "{top}def:pwfs1RTmin") ;
ASSVAR (double, defPwfs1RTmax, "{top}def:pwfs1RTmax") ;

ASSVAR (double, defPwfs2Rmin, "{top}def:pwfs2Rmin") ;
ASSVAR (double, defPwfs2Rmax, "{top}def:pwfs2Rmax") ;
ASSVAR (double, defPwfs2Zmin, "{top}def:pwfs2Zmin") ;
ASSVAR (double, defPwfs2Zmax, "{top}def:pwfs2Zmax") ;
ASSVAR (double, defPwfs2Xposn, "{top}def:pwfs2Xposn") ;
ASSVAR (double, defPwfs2Yposn, "{top}def:pwfs2Yposn") ;
ASSVAR (double, defPwfs2Zposn, "{top}def:pwfs2Zposn") ;
ASSVAR (int,    defPwfs2LimitType, "{top}def:pwfs2LimitType") ;
ASSVAR (double, defPwfs2RTmin, "{top}def:pwfs2RTmin") ;
ASSVAR (double, defPwfs2RTmax, "{top}def:pwfs2RTmax") ;

ASSVAR (double, defOiwfsXmin, "{top}def:oiwfsXmin") ;
ASSVAR (double, defOiwfsXmax, "{top}def:oiwfsXmax") ;
ASSVAR (double, defOiwfsYmin, "{top}def:oiwfsYmin") ;
ASSVAR (double, defOiwfsYmax, "{top}def:oiwfsYmax") ;
ASSVAR (double, defOiwfsZmin, "{top}def:oiwfsZmin") ;
ASSVAR (double, defOiwfsZmax, "{top}def:oiwfsZmax") ;
ASSVAR (double, defOiwfsRmin, "{top}def:oiwfsRmin") ;
ASSVAR (double, defOiwfsRmax, "{top}def:oiwfsRmax") ;
ASSVAR (double, defOiwfsXposn, "{top}def:oiwfsXposn") ;
ASSVAR (double, defOiwfsYposn, "{top}def:oiwfsYposn") ;
ASSVAR (double, defOiwfsZposn, "{top}def:oiwfsZposn") ;
ASSVAR (int,    defOiwfsLimitType, "{top}def:oiwfsLimitType") ;

/* Default data for Altair. Only used if TCS can't initially connect */

ASSVAR (double, defAowfsXmin, "{top}def:aowfsXmin") ;
ASSVAR (double, defAowfsXmax, "{top}def:aowfsXmax") ;
ASSVAR (double, defAowfsYmin, "{top}def:aowfsYmin") ;
ASSVAR (double, defAowfsYmax, "{top}def:aowfsYmax") ;
ASSVAR (double, defAowfsZmin, "{top}def:aowfsZmin") ;
ASSVAR (double, defAowfsZmax, "{top}def:aowfsZmax") ;
ASSVAR (double, defAowfsXposn, "{top}def:aowfsXposn") ;
ASSVAR (double, defAowfsYposn, "{top}def:aowfsYposn") ;
ASSVAR (double, defAowfsZposn, "{top}def:aowfsZposn") ;

/* Default data for Canopus. Only used if TCS can't initially connect */

ASSVAR (double, defAomngsPr1Xmin, "{top}def:aomngsPr1Xmin") ;
ASSVAR (double, defAomngsPr1Xmax, "{top}def:aomngsPr1Xmax") ;
ASSVAR (double, defAomngsPr1Rmin, "{top}def:aomngsPr1Rmin") ;
ASSVAR (double, defAomngsPr1Rmax, "{top}def:aomngsPr1Rmax") ;
ASSVAR (double, defAomngsPr2Xmin, "{top}def:aomngsPr2Xmin") ;
ASSVAR (double, defAomngsPr2Xmax, "{top}def:aomngsPr2Xmax") ;
ASSVAR (double, defAomngsPr2Rmin, "{top}def:aomngsPr2Rmin") ;
ASSVAR (double, defAomngsPr2Rmax, "{top}def:aomngsPr2Rmax") ;
ASSVAR (double, defAomngsPr3Xmin, "{top}def:aomngsPr3Xmin") ;
ASSVAR (double, defAomngsPr3Xmax, "{top}def:aomngsPr3Xmax") ;
ASSVAR (double, defAomngsPr3Rmin, "{top}def:aomngsPr3Rmin") ;
ASSVAR (double, defAomngsPr3Rmax, "{top}def:aomngsPr3Rmax") ;
ASSVAR (double, defAomngsPr1Xposn, "{top}def:aomngsPr1Xposn") ;
ASSVAR (double, defAomngsPr1Yposn, "{top}def:aomngsPr1Yposn") ;
ASSVAR (double, defAomngsPr2Xposn, "{top}def:aomngsPr2Xposn") ;
ASSVAR (double, defAomngsPr2Yposn, "{top}def:aomngsPr2Yposn") ;
ASSVAR (double, defAomngsPr3Xposn, "{top}def:aomngsPr3Xposn") ;
ASSVAR (double, defAomngsPr3Yposn, "{top}def:aomngsPr3Yposn") ;

/* Default data for GSAOI, only used if TCS can not connect */
ASSVAR (double, defodgw1Xcen, "{top}def:odgw1Xcen") ;
ASSVAR (double, defodgw1Ycen, "{top}def:odgw1Ycen") ;
ASSVAR (double, defodgw2Xcen, "{top}def:odgw2Xcen") ;
ASSVAR (double, defodgw2Ycen, "{top}def:odgw2Ycen") ;
ASSVAR (double, defodgw3Xcen, "{top}def:odgw3Xcen") ;
ASSVAR (double, defodgw3Ycen, "{top}def:odgw3Ycen") ;
ASSVAR (double, defodgw4Xcen, "{top}def:odgw4Xcen") ;
ASSVAR (double, defodgw4Ycen, "{top}def:odgw4Ycen") ;

/* Monitor the init TCS CAR record */
MONVAR ( int, tcsInitCar, "{top}initC.VAL" ) ;

/* The TCS REBOOT CAR value is monitored to know when to reboot */
MONVAR (int, tcsRebootCar, "{top}rebootC.VAL") ;

/* Monitor the debug level for printing messages
*  N.B. The name of the variable MUST be dbgLevel if the macros
*  are to be used
*/
MONVAR ( int, dbgLevel, "{top}debugLevel" ) ;

ASSNOVAR (double, currAz ) ; 
ASSNOVAR (double, currEl ) ;
ASSNOVAR (double, currRma) ;

/* parameters from M2 */
ASSNOVAR (double, m2MaxChopFreq ) ;
ASSNOVAR (double, m2BreakChopFreq ) ;
ASSNOVAR (double, m2MinChopFreq ) ;
ASSNOVAR (double, m2MaxChopFreqThrow ) ;
ASSNOVAR (double, m2BreakChopFreqThrow ) ;
ASSNOVAR (double, m2MinChopFreqThrow ) ;
ASSNOVAR (double, m2MinTilt) ;
ASSNOVAR (double, m2MaxTilt) ;
ASSNOVAR (double, m2MinTiltZ) ;
ASSNOVAR (double, m2MaxTiltZ) ;
ASSNOVAR (string, topEnd );

/* Parameters for A&G */

ASSNOVAR (double, pwfs1xPos) ;
ASSNOVAR (double, pwfs1yPos) ;
ASSNOVAR (double, pwfs1zPos) ;
ASSNOVAR (double, pwfs1Rmax) ;
ASSNOVAR (double, pwfs1Rmin) ;
ASSNOVAR (double, pwfs1Zmax) ;
ASSNOVAR (double, pwfs1Zmin) ;
ASSNOVAR (double, pwfs1RTmax) ;
ASSNOVAR (double, pwfs1RTmin) ;

ASSNOVAR (double, pwfs2xPos) ;
ASSNOVAR (double, pwfs2yPos) ;
ASSNOVAR (double, pwfs2zPos) ;
ASSNOVAR (double, pwfs2Rmax) ;
ASSNOVAR (double, pwfs2Rmin) ;
ASSNOVAR (double, pwfs2Zmax) ;
ASSNOVAR (double, pwfs2Zmin) ;
ASSNOVAR (double, pwfs2RTmax) ;
ASSNOVAR (double, pwfs2RTmin) ;

ASSNOVAR (double, oiwfsxPos) ;
ASSNOVAR (double, oiwfsyPos) ;
ASSNOVAR (double, oiwfszPos) ;
ASSNOVAR (int,    oiwfsLimitType) ;
ASSNOVAR (double, oiwfsXmax) ;
ASSNOVAR (double, oiwfsXmin) ;
ASSNOVAR (double, oiwfsYmax) ;
ASSNOVAR (double, oiwfsYmin) ;
ASSNOVAR (double, oiwfsZmax) ;
ASSNOVAR (double, oiwfsZmin) ;
ASSNOVAR (double, oiwfsRmax) ;
ASSNOVAR (double, oiwfsRmin) ;
double oiwfsCoeffs[6] ;
assign oiwfsCoeffs to "" ;

/* Parameters for Altair */
ASSNOVAR (double, aowfsXpos) ;
ASSNOVAR (double, aowfsYpos) ;
ASSNOVAR (double, aowfsZpos) ;
ASSNOVAR (double, aowfsXmax) ;
ASSNOVAR (double, aowfsXmin) ;
ASSNOVAR (double, aowfsYmax) ;
ASSNOVAR (double, aowfsYmin) ;
ASSNOVAR (double, aowfsZmax) ;
ASSNOVAR (double, aowfsZmin) ;

/* Parameters for AOM (Canopus) */
ASSNOVAR (double, aomngsPr1Xpos) ;
ASSNOVAR (double, aomngsPr1Ypos) ;
ASSNOVAR (double, aomngsPr1Xmax) ;
ASSNOVAR (double, aomngsPr1Xmin) ;
ASSNOVAR (double, aomngsPr1Rmax) ;
ASSNOVAR (double, aomngsPr2Xpos) ;
ASSNOVAR (double, aomngsPr2Ypos) ;
ASSNOVAR (double, aomngsPr2Xmax) ;
ASSNOVAR (double, aomngsPr2Xmin) ;
ASSNOVAR (double, aomngsPr2Rmax) ;
ASSNOVAR (double, aomngsPr3Xpos) ;
ASSNOVAR (double, aomngsPr3Ypos) ;
ASSNOVAR (double, aomngsPr3Xmax) ;
ASSNOVAR (double, aomngsPr3Xmin) ;
ASSNOVAR (double, aomngsPr3Rmax) ;

/* Parameters for GSAOI */
ASSNOVAR (double, odgw1Xcen) ;
ASSNOVAR (double, odgw1Ycen) ;
ASSNOVAR (double, odgw2Xcen) ;
ASSNOVAR (double, odgw2Ycen) ;
ASSNOVAR (double, odgw3Xcen) ;
ASSNOVAR (double, odgw3Ycen) ;
ASSNOVAR (double, odgw4Xcen) ;
ASSNOVAR (double, odgw4Ycen) ;
ASSNOVAR (double, odgwExtent) ;

/* Parameters for enclosure */

ASSNOVAR (double, minBotShtr) ;
ASSNOVAR (double, maxBotShtr) ;
ASSNOVAR (double, minTopShtr) ;
ASSNOVAR (double, maxTopShtr) ;
ASSNOVAR (double, domePosn) ;
ASSNOVAR (double, topShtrPosn) ;
ASSNOVAR (double, botShtrPosn) ;

/* Parameters for the PCS */
sync m1RestoreTrigger m1Restore ; 

assign intSimulate[MC] to "{top}mcIntSimulate" ;
assign intSimulate[M1] to "{top}m1IntSimulate" ;
assign intSimulate[M2] to "{top}m2IntSimulate" ;
assign intSimulate[CR] to "{top}crIntSimulate" ;
assign intSimulate[EC] to "{top}ecIntSimulate" ;
assign intSimulate[AG] to "{top}agIntSimulate" ;
assign intSimulate[AO] to "{top}aoIntSimulate" ;
assign intSimulate[WS] to "{top}wsIntSimulate" ;
assign intSimulate[GP] to "{top}gpIntSimulate" ;
assign intSimulate[AOM] to "{top}aomIntSimulate" ;
assign intSimulate[GSAOI] to "{top}gsaoiIntSimulate" ;

assign applState[MC] to "" ;
assign applState[M1] to "" ;
assign applState[M2] to "" ;
assign applState[CR] to "" ;
assign applState[EC] to "" ;
assign applState[AG] to "" ;
assign applState[AO] to "" ;
assign applState[WS] to "" ;
assign applState[GP] to "" ;
assign applState[AOM] to "" ;
assign applState[GSAOI] to "" ;

void setConfFileRest(string result, int modelType, string top, string dir, string pref) {
  if (modelType == 2) {
    if (!strcmp(top, "tcs:")) {
      snprintf (result, MAX_PATH, "%s/%s", dir, "tcsM1Restore.pv");
    } else {
      snprintf (result, MAX_PATH, "%s/%s%s", dir, pref, "M1RestoreGPI.pv");
    }
  } else if (modelType == 1) {
    snprintf (result, MAX_PATH, "%s/%s%s", dir, pref, "M1RestoreAO.pv");
  } else {
    snprintf (result, MAX_PATH, "%s/%s%s", dir, pref, "M1Restore.pv");
  }
}

/****************************************************************************/
/* The state set controlling the MCS
*/

ss mcs
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear (mcTimeOut) ;
    efClear (mcRunning) ;
    loopDelay = 1.0 ;
    waitTime[MC] = 0.0 ;                
    timeOutPeriod[MC] = 60.0 ;
    pvGet(intSimulate[MC]) ;
    if (intSimulate[MC])
    {
     snprintf (mcPrefix, 40, "%smc:", macValueGet("top"));
    }
    else
    {
     strcpy (mcPrefix, macValueGet("mc")) ;
    }

/* Now construct each database name and assign the relevant variable to it */

    if (intSimulate[MC])
    {
     snprintf (mcDbName, 40, "%ssimScanControl.VAL", mcPrefix);
     pvAssign(mcScanControl, mcDbName) ;
     strcpy(mcScanControl, "On");
     pvPut(mcScanControl);
    }
    snprintf (mcDbName, 40, "%sazCurrentPos", mcPrefix);
    pvAssign(currAz, mcDbName) ;
    snprintf (mcDbName, 40, "%selCurrentPos", mcPrefix);
    pvAssign(currEl, mcDbName) ;
    snprintf (mcDbName, 40, "%sstate", mcPrefix);
    pvAssign(applState[MC], mcDbName) ;
    pvMonitor(applState[MC]) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss mcs init -> connecting\n");
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[MC]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss mcs connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[MC]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(mcSeqInit))
   {
   }  state init

   when (pvConnected(applState[MC]))
   {
    waitTime[MC] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss mcs wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[MC] = waitTime[MC] + loopDelay ;
    if (waitTime[MC] > timeOutPeriod[MC])
    {
      efSet(mcTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
 * subsystem cannot reach the "Running" state before the time out period
*/

  state checkState
  {
   when (efTestAndClear(mcSeqInit))
   {
   }  state init

   when (applState[MC] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    efClear(mcTimeOut) ;
    efSet (mcRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss mcs checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[MC] = waitTime[MC] + loopDelay ;
    if (waitTime[MC] > timeOutPeriod[MC])
    {
      efSet(mcTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[MC]))
   {
     applState[MC] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[MC]))
   {
/* Make sure that the enclosure doesn't try following when there is no
 * mount position information 
*/
    tcsEcsEnableShtrs(FALSE) ;
    tcsEcsEnableDome (FALSE) ;
    applState[MC] = BOOTING ;
   } state init

   when (delay(1.0))
   {
   } state monitoring

   when (efTestAndClear(mcSeqInit))
   {
   }  state init
  }

}


/****************************************************************************/
/* The state set controlling the Cass Rotator
*/

ss crs
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(crTimeOut) ;
    efClear(crRunning) ;
    loopDelay = 1.0 ;
    waitTime[CR] = 0.0 ;                
    timeOutPeriod[CR] = 30.0 ;
    pvGet(intSimulate[CR]) ;
    if (intSimulate[CR])
    {
     snprintf(crPrefix, 40, "%scr:", macValueGet("top"));
    }
    else
    {
     strcpy (crPrefix, macValueGet("cr")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[CR])
    {
     snprintf (crDbName, 40, "%ssimScanControl.VAL", crPrefix);
     pvAssign(crScanControl, crDbName) ;
     strcpy(crScanControl, "On");
     pvPut(crScanControl);
    }
    snprintf (crDbName, 40, "%sfollowA.VALB", crPrefix);
    pvAssign(currRma, crDbName) ;
    snprintf (crDbName, 40, "%sstate", crPrefix);
    pvAssign(applState[CR],crDbName) ;
    pvMonitor(applState[CR]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[CR]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss crcs connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[CR]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(crSeqInit))
   {
   }  state init

   when (pvConnected(applState[CR]))
   {
    waitTime[CR] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss crcs wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[CR] = waitTime[CR] + loopDelay ;
    if (waitTime[CR] > timeOutPeriod[CR])
    {
      efSet(crTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(crSeqInit))
   {
   }  state init

   when (applState[CR] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    efClear(crTimeOut) ;
    efSet(crRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss crcs checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[CR] = waitTime[CR] + loopDelay ;
    if (waitTime[CR] > timeOutPeriod[CR])
    {
      efSet(crTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[CR]))
   {
     applState[CR] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[CR]))
   {
    applState[CR] = BOOTING ;
   } state init

   when (delay(1.0))
   {
   } state monitoring

   when (efTestAndClear(crSeqInit))
   {
   }  state init
  }

}

/****************************************************************************/
/* The state set controlling the enclosure
*/

ss ecs
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(ecTimeOut) ;
    efClear(ecRunning) ;
    loopDelay = 1.0 ;
    waitTime[EC] = 0.0 ;                
    timeOutPeriod[EC] = 20.0 ;
    pvGet(intSimulate[EC]) ;
    if (intSimulate[EC])
    {
     snprintf (ecPrefix, 40, "%sec:", macValueGet("top"));
    }
    else
    {
     strcpy (ecPrefix, macValueGet("ec")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[EC])
    {
     snprintf (ecDbName, 40, "%ssimScanControl.VAL", ecPrefix);
     pvAssign(ecScanControl, ecDbName) ;
     strcpy(ecScanControl, "On");
     pvPut(ecScanControl);
    }

    snprintf (ecDbName, 40, "%sbotShtrMin", ecPrefix);
    pvAssign(minBotShtr, ecDbName);
    pvMonitor(minBotShtr) ;

    snprintf (ecDbName, 40, "%sbotShtrMax", ecPrefix);
    pvAssign(maxBotShtr, ecDbName);
    pvMonitor(maxBotShtr) ;

    snprintf (ecDbName, 40, "%stopShtrMin", ecPrefix);
    pvAssign(minTopShtr, ecDbName);
    pvMonitor(minTopShtr) ;

    snprintf (ecDbName, 40, "%stopShtrMax", ecPrefix);
    pvAssign(maxTopShtr, ecDbName);
    pvMonitor(maxTopShtr) ;

    snprintf (ecDbName, 40, "%sdomePos", ecPrefix);
    pvAssign(domePosn, ecDbName);

    snprintf (ecDbName, 40, "%stopShtrPos", ecPrefix);
    pvAssign(topShtrPosn, ecDbName);

    snprintf (ecDbName, 40, "%sbotShtrPos", ecPrefix);
    pvAssign(botShtrPosn, ecDbName);

    snprintf (ecDbName, 40, "%sstate", ecPrefix);
    pvAssign(applState[EC],ecDbName) ;
    pvMonitor(applState[EC]) ;

   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[EC]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss ecs connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[EC]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(ecSeqInit))
   {
   }  state init

   when (pvConnected(applState[EC]))
   {
    waitTime[EC] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss ecs wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[EC] = waitTime[EC] + loopDelay ;
    if (waitTime[EC] > timeOutPeriod[EC])
    {
      efSet(ecTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(ecSeqInit))
   {
   }  state init

   when (applState[EC] == RUNNING && semInitialized == TRUE)
   {

    DBGMSG (DBG_NONE, "tcsSeqInit: ss ecs checkState -> monitoring\n");

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/

/* Set the shutter limit positions */

   pvGet(minBotShtr) ;
   pvGet(maxBotShtr) ;
   pvGet(minTopShtr) ;
   pvGet(maxTopShtr) ;
   if (tcsEcsSetShutLimits (minBotShtr, maxBotShtr, minTopShtr, maxTopShtr, 
                        logrecord)) 
   {
    pvPut (logrecord);
   }

/* Fetch and set the current shutter and dome positions */

   pvGet(domePosn) ;
   pvGet(botShtrPosn) ;
   pvGet(topShtrPosn) ;
  
   if (tcsEcsSetPosnDefs (domePosn, botShtrPosn, topShtrPosn, logrecord))
   {
    pvPut (logrecord) ;
   }

    efClear(ecTimeOut) ;
    efSet(ecRunning) ;
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[EC] = waitTime[EC] + loopDelay ;
    if (waitTime[EC] > timeOutPeriod[EC])
    {
      efSet(ecTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[EC]))
   {
     applState[EC] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[EC]))
   {
    applState[EC] = BOOTING ;
    tcsEcsEnableShtrs(FALSE);
    tcsEcsEnableDome(FALSE);
   } state init

   when (delay(1.0))
   {
     if (tcsEcsSetShutLimits (minBotShtr, maxBotShtr, minTopShtr, maxTopShtr, 
                        logrecord)) 
     {
      pvPut (logrecord);
     }
   } state monitoring

   when (efTestAndClear(ecSeqInit))
   {
   }  state init
  }

}

/****************************************************************************/
/* The state set controlling secondary mirror
*/

ss m2s
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(m2TimeOut) ;
    efClear(m2Running) ;
    loopDelay = 1.0 ;
    waitTime[M2] = 0.0 ;                
    timeOutPeriod[M2] = 60.0 ;
    pvGet(intSimulate[M2]) ;
    if (intSimulate[M2])
    {
     snprintf (m2Prefix, 40, "%sm2:", macValueGet("top"));
    }
    else
    {
     strcpy (m2Prefix, macValueGet("m2")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[M2])
    {
     snprintf (m2DbName, 40, "%ssimScanControl.VAL", m2Prefix);
     pvAssign(m2ScanControl, m2DbName) ;
     strcpy(m2ScanControl, "On");
     pvPut(m2ScanControl);
    }

/* Limits on throw and frequency of chop */

    snprintf (m2DbName, 40, "%smaxChopFreqThrow", m2Prefix);
    pvAssign (m2MaxChopFreqThrow, m2DbName) ;
    pvMonitor (m2MaxChopFreqThrow) ;

    snprintf (m2DbName, 40, "%sbreakChopFreqThrow", m2Prefix);
    pvAssign (m2BreakChopFreqThrow, m2DbName) ;
    pvMonitor (m2BreakChopFreqThrow) ;

    snprintf (m2DbName, 40, "%sminChopFreqThrow", m2Prefix);
    pvAssign (m2MinChopFreqThrow, m2DbName) ;
    pvMonitor (m2MinChopFreqThrow) ;

    snprintf (m2DbName, 40, "%smaxChopFreq", m2Prefix);
    pvAssign (m2MaxChopFreq, m2DbName) ;
    pvMonitor (m2MaxChopFreq) ;

    snprintf (m2DbName, 40, "%sbreakChopFreq", m2Prefix);
    pvAssign (m2BreakChopFreq, m2DbName) ;
    pvMonitor (m2BreakChopFreq) ;

    snprintf (m2DbName, 40, "%sminChopFreq", m2Prefix);
    pvAssign (m2MinChopFreq, m2DbName) ;
    pvMonitor (m2MinChopFreq) ;

/* Limits on Tilt and Focus */

    snprintf (m2DbName, 40, "%sminTilt", m2Prefix);
    pvAssign (m2MinTilt, m2DbName) ;
    pvMonitor (m2MinTilt) ;

    snprintf (m2DbName, 40, "%smaxTilt", m2Prefix);
    pvAssign (m2MaxTilt, m2DbName) ;
    pvMonitor (m2MaxTilt) ;

    snprintf (m2DbName, 40, "%sminTiltZ", m2Prefix);
    pvAssign (m2MinTiltZ, m2DbName) ;
    pvMonitor (m2MinTiltZ) ;

    snprintf (m2DbName, 40, "%smaxTiltZ", m2Prefix);
    pvAssign (m2MaxTiltZ, m2DbName) ;
    pvMonitor (m2MaxTiltZ) ;

/* top end */

    snprintf (m2DbName, 40, "%stopEnd", m2Prefix);
    pvAssign (topEnd, m2DbName);

    snprintf (m2DbName, 40, "%sstate", m2Prefix);
    pvAssign(applState[M2],m2DbName) ;
    pvMonitor(applState[M2]) ;

   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[M2]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss scs connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[M2]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(m2SeqInit))
   {
   }  state init

   when (pvConnected(applState[M2]))
   {
    waitTime[M2] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss scs wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[M2] = waitTime[M2] + loopDelay ;
    if (waitTime[M2] > timeOutPeriod[M2])
    {
      efSet(m2TimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(m2SeqInit))
   {
   }  state init

   when (applState[M2] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/

/* Set the chop limits */

    tcsOpticsSetChopLimits (m2MinChopFreq, m2BreakChopFreq, m2MaxChopFreq,
              m2MinChopFreqThrow, m2BreakChopFreqThrow, m2MaxChopFreqThrow) ;

/* set the tilt limits */

    tcsOpticsSetTiltLimits (m2MinTilt, m2MaxTilt, m2MinTiltZ, m2MaxTiltZ);

/* Fetch and set top end */

    pvGet(topEnd);
    tcsOpticsSetTopEnd (topEnd);
 
    efClear(m2TimeOut) ;
    efSet(m2Running) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss scs checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[M2] = waitTime[M2] + loopDelay ;
    if (waitTime[M2] > timeOutPeriod[M2])
    {
      efSet(m2TimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[M2]))
   {
     applState[M2] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[M2]))
   {
    applState[M2] = BOOTING ;
   } state init

   when (delay(1.0))
   {
/* Reset the chop limits on each loop. If any dynamic changes are made
 * to the m2 database due to mechanical problems etc. then this ensures that
 * the TCS always has the latest data.
*/
    tcsOpticsSetChopLimits (m2MinChopFreq, m2BreakChopFreq, m2MaxChopFreq,
        m2MinChopFreqThrow, m2BreakChopFreqThrow, m2MaxChopFreqThrow) ;
    tcsOpticsSetTiltLimits (m2MinTilt, m2MaxTilt, m2MinTiltZ, m2MaxTiltZ);
   } state monitoring

   when (efTestAndClear(m2SeqInit))
   {
   }  state init
  }

}
/****************************************************************************/
/* The state set controlling the A & G
*/

ss ags
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(agTimeOut) ;
    efClear(agRunning) ;
    loopDelay = 1.0 ;
    waitTime[AG] = 0.0 ;                
    timeOutPeriod[AG] = 60.0 ;
    pvGet(intSimulate[AG]) ;
    if (intSimulate[AG])
    {
     strcpy (agPrefix, "tag:") ;
    }
    else
    {
     strcpy (agPrefix, macValueGet("ag")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[AG])
    {
     snprintf (agDbName, 40, "%ssimScanControl.VAL", agPrefix);
     pvAssign(agScanControl, agDbName) ;
     strcpy(agScanControl, "On");
     pvPut(agScanControl);
    }

/* PWFS1 */

    snprintf (agDbName, 40, "%sp1:Rmin", agPrefix);
    pvAssign (pwfs1Rmin, agDbName ) ;
    pvMonitor (pwfs1Rmin) ;
    snprintf (agDbName, 40, "%sp1:Rmax", agPrefix);
    pvAssign (pwfs1Rmax, agDbName ) ;
    pvMonitor (pwfs1Rmax) ;
    snprintf (agDbName, 40, "%sp1:Zmin", agPrefix);
    pvAssign (pwfs1Zmin, agDbName ) ;
    pvMonitor (pwfs1Zmin) ;
    snprintf (agDbName, 40, "%sp1:Zmax", agPrefix);
    pvAssign (pwfs1Zmax, agDbName ) ;
    pvMonitor (pwfs1Zmax) ;
    snprintf (agDbName, 40, "%sp1:x", agPrefix);
    pvAssign (pwfs1xPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp1:y", agPrefix);
    pvAssign (pwfs1yPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp1:focusPos", agPrefix);
    pvAssign (pwfs1zPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp1:probeCalParm.L", agPrefix);
    pvAssign (pwfs1RTmax, agDbName ) ;
    snprintf (agDbName, 40, "%sp1:probeCalParm.M", agPrefix);
    pvAssign (pwfs1RTmin, agDbName ) ;

/* PWFS2 */

    snprintf (agDbName, 40, "%sp2:Rmin", agPrefix);
    pvAssign (pwfs2Rmin, agDbName ) ;
    pvMonitor (pwfs2Rmin) ;
    snprintf (agDbName, 40, "%sp2:Rmax", agPrefix);
    pvAssign (pwfs2Rmax, agDbName ) ;
    pvMonitor (pwfs2Rmax) ;
    snprintf (agDbName, 40, "%sp2:Zmin", agPrefix);
    pvAssign (pwfs2Zmin, agDbName ) ;
    pvMonitor (pwfs2Zmin) ;
    snprintf (agDbName, 40, "%sp2:Zmax", agPrefix);
    pvAssign (pwfs2Zmax, agDbName ) ;
    pvMonitor (pwfs2Zmax) ;
    snprintf (agDbName, 40, "%sp2:x", agPrefix);
    pvAssign (pwfs2xPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp2:y", agPrefix);
    pvAssign (pwfs2yPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp2:focusPos", agPrefix);
    pvAssign (pwfs2zPos, agDbName ) ;
    snprintf (agDbName, 40, "%sp2:probeCalParm.L", agPrefix);
    pvAssign (pwfs2RTmax, agDbName ) ;
    snprintf (agDbName, 40, "%sp2:probeCalParm.M", agPrefix);
    pvAssign (pwfs2RTmin, agDbName ) ;

/* OIWFS */

    snprintf (agDbName, 40, "%soi:Rmin", agPrefix);
    pvAssign (oiwfsRmin, agDbName ) ;
    pvMonitor (oiwfsRmin) ;
    snprintf (agDbName, 40, "%soi:Rmax", agPrefix);
    pvAssign (oiwfsRmax, agDbName ) ;
    pvMonitor (oiwfsRmax) ;
    snprintf (agDbName, 40, "%soi:Xmin", agPrefix);
    pvAssign (oiwfsXmin, agDbName ) ;
    snprintf (agDbName, 40, "%soi:Xmax", agPrefix);
    pvAssign (oiwfsXmax, agDbName ) ;
    snprintf (agDbName, 40, "%soi:Ymin", agPrefix);
    pvAssign (oiwfsYmin, agDbName ) ;
    snprintf (agDbName, 40, "%soi:Ymax", agPrefix);
    pvAssign (oiwfsYmax, agDbName ) ;
    snprintf (agDbName, 40, "%soi:Zmin", agPrefix);
    pvAssign (oiwfsZmin, agDbName ) ;
    snprintf (agDbName, 40, "%soi:Zmax", agPrefix);
    pvAssign (oiwfsZmax, agDbName ) ;
    snprintf (agDbName, 40, "%soi:LimitType", agPrefix);
    pvAssign (oiwfsLimitType, agDbName ) ;
    pvMonitor (oiwfsLimitType) ;
    snprintf (agDbName, 40, "%soi:x", agPrefix);
    pvAssign (oiwfsxPos, agDbName ) ;
    snprintf (agDbName, 40, "%soi:y", agPrefix);
    pvAssign (oiwfsyPos, agDbName ) ;
    snprintf (agDbName, 40, "%soi:focusPos", agPrefix);
    pvAssign (oiwfszPos, agDbName ) ;
    snprintf (agDbName, 40, "%soi:oiwfsCoeffs.VALJ", agPrefix);
    pvAssign (oiwfsCoeffs, agDbName ) ;

    snprintf (agDbName, 40, "%sstate", agPrefix);
    pvAssign(applState[AG],agDbName) ;
    pvMonitor(applState[AG]) ;

   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[AG]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss a&g connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[AG]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(agSeqInit))
   {
   }  state init

   when (pvConnected(applState[AG]))
   {
    waitTime[AG] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss a&g wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[AG] = waitTime[AG] + loopDelay ;
    if (waitTime[AG] > timeOutPeriod[AG])
    {
      efSet(agTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(agSeqInit))
   {
   }  state init

   when (applState[AG] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/

/* Set the limits and default positions of the probes */

    pvGet(oiwfsCoeffs) ;
    pvGet(pwfs1Rmin) ;
    pvGet(pwfs1Rmax) ;
    pvGet(pwfs2Rmin) ;
    pvGet(pwfs2Rmax) ;

    pvGet(pwfs1RTmin) ;
    pvGet(pwfs1RTmax) ;
    pvGet(pwfs2RTmin) ;
    pvGet(pwfs2RTmax) ;
    tcsProbeSetRTLimits (pwfs1RTmin, pwfs1RTmax, pwfs2RTmin, pwfs2RTmax);

/* This next section of code is to overcome an occasional problem when pvGet
 * returns zeroes for the probe limits. This is some sort of timing problem
 * which can disappear for months and then return. There should really be no
 * need to go through these hoops.
*/
    if (pwfs1Rmax == 0.0) {
      pwfs1Rmin = pwfs1UserRmin ;
      pwfs1Rmax = pwfs1UserRmax ;
    }
    if (pwfs2Rmax == 0.0) {
      pwfs2Rmin = pwfs2UserRmin ;
      pwfs2Rmax = pwfs2UserRmax ;
    }

    tcsProbeSetRadii (pwfs1Rmin, pwfs1Rmax, pwfs2Rmin, pwfs2Rmax);
    tcsProbeSetCoeffs(oiwfsCoeffs) ;

    if (pwfs1UserRmin < pwfs1Rmin) {
      pwfs1UserRmin = pwfs1Rmin ;
      pvPut(pwfs1UserRmin) ;
    }
    if (pwfs1UserRmax > pwfs1Rmax) {
      pwfs1UserRmax = pwfs1Rmax ;
      pvPut(pwfs1UserRmax) ;
    }
    if (pwfs2UserRmin < pwfs2Rmin) {
      pwfs2UserRmin = pwfs2Rmin ;
      pvPut(pwfs2UserRmin) ;
    }
    if (pwfs2UserRmax > pwfs2Rmax) {
      pwfs2UserRmax = pwfs2Rmax ;
      pvPut(pwfs2UserRmax) ;
    }
    tcsProbeSetRZLimits (0, pwfs1UserRmin, pwfs1UserRmax, pwfs1Zmin, 
                         pwfs1Zmax) ;
    pvGet(pwfs1xPos) ;
    pvGet(pwfs1yPos) ;
    pvGet(pwfs1zPos) ;
    tcsProbeSetDefaults (0, pwfs1xPos, pwfs1yPos, pwfs1zPos) ;

    tcsProbeSetRZLimits (1, pwfs2UserRmin, pwfs2UserRmax, pwfs2Zmin, 
                         pwfs2Zmax) ;
    pvGet(pwfs2xPos) ;
    pvGet(pwfs2yPos) ;
    pvGet(pwfs2zPos) ;
    tcsProbeSetDefaults (1, pwfs2xPos, pwfs2yPos, pwfs2zPos) ;

    if (oiwfsLimitType == XY) {
      pvGet(oiwfsXmin) ;
      pvGet(oiwfsXmax) ;
      pvGet(oiwfsYmin) ;
      pvGet(oiwfsYmax) ;
      pvGet(oiwfsZmin) ;
      pvGet(oiwfsZmax) ;
      tcsProbeSetXYZLimits (2, oiwfsXmin, oiwfsXmax,
                                     oiwfsYmin, oiwfsYmax,
                                     oiwfsZmin, oiwfsZmax) ;
      oiwfsUserXmin = oiwfsXmin ;
      oiwfsUserXmax = oiwfsXmax ;
      oiwfsUserYmin = oiwfsYmin ;
      oiwfsUserYmax = oiwfsYmax ;
      pvPut(oiwfsUserXmin) ;
      pvPut(oiwfsUserXmax) ;
      pvPut(oiwfsUserYmin) ;
      pvPut(oiwfsUserYmax) ;
    } else {
      tcsProbeSetRZLimits (2, oiwfsRmin, oiwfsRmax, oiwfsZmin, 
                           oiwfsZmax) ;
      oiwfsUserRmin = oiwfsRmin ;
      oiwfsUserRmax = oiwfsRmax ;
      pvPut(oiwfsUserRmin) ;
      pvPut(oiwfsUserRmax) ;
    }

    oiwfsUserLimitType = oiwfsLimitType ;
    pvPut(oiwfsUserLimitType) ;

    pvGet(oiwfsxPos) ;
    pvGet(oiwfsyPos) ;
    pvGet(oiwfszPos) ;
    tcsProbeSetDefaults (2, oiwfsxPos, oiwfsyPos, oiwfszPos) ;

    efClear(agTimeOut) ;
    efSet(agRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss a&g checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[AG] = waitTime[AG] + loopDelay ;
    if (waitTime[AG] > timeOutPeriod[AG])
    {
      efSet(agTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[AG]))
   {
     applState[AG] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[AG]))
   {
    applState[AG] = BOOTING ;
   } state init

   when (delay(1.0))
   {
/* Update the limits in case the subsystem database has been modified */
    if (pwfs1Rmax == 0.0) {
      pwfs1Rmin = pwfs1UserRmin ;
      pwfs1Rmax = pwfs1UserRmax ;
    }
    if (pwfs2Rmax == 0.0) {
      pwfs2Rmin = pwfs2UserRmin ;
      pwfs2Rmax = pwfs2UserRmax ;
    }
    tcsProbeSetRadii (pwfs1Rmin, pwfs1Rmax, pwfs2Rmin, pwfs2Rmax);
    pvGet(oiwfsCoeffs) ;
    tcsProbeSetCoeffs(oiwfsCoeffs) ;

    if (pwfs1UserRmin < pwfs1Rmin) {
      pwfs1UserRmin = pwfs1Rmin ;
      strcpy (logrecord, "Reset min. radius for PWFS1") ;
      pvPut(pwfs1UserRmin) ;
      pvPut(logrecord) ;
    }
    if (pwfs1UserRmax > pwfs1Rmax) {
      pwfs1UserRmax = pwfs1Rmax ;
      strcpy (logrecord, "Reset max. radius for PWFS1") ;
      pvPut(pwfs1UserRmax) ;
      pvPut(logrecord) ;
    }
    if (pwfs2UserRmin < pwfs2Rmin) {
      pwfs2UserRmin = pwfs2Rmin ;
      strcpy (logrecord, "Reset min. radius for PWFS2") ;
      pvPut(pwfs2UserRmin) ;
      pvPut(logrecord) ;
    }
    if (pwfs2UserRmax > pwfs2Rmax) {
      pwfs2UserRmax = pwfs2Rmax ;
      strcpy (logrecord, "Reset max. radius for PWFS2") ;
      pvPut(pwfs2UserRmax) ;
      pvPut(logrecord) ;
    }
    tcsProbeSetRZLimits (0, pwfs1UserRmin, pwfs1UserRmax, pwfs1Zmin, 
                         pwfs1Zmax) ;
    tcsProbeSetRZLimits (1, pwfs2UserRmin, pwfs2UserRmax, pwfs2Zmin, 
                         pwfs2Zmax) ;

    pvGet(pwfs1RTmin) ;
    pvGet(pwfs1RTmax) ;
    pvGet(pwfs2RTmin) ;
    pvGet(pwfs2RTmax) ;
    tcsProbeSetRTLimits (pwfs1RTmin, pwfs1RTmax, pwfs2RTmin, pwfs2RTmax);

    if (oiwfsLimitType == XY) {
      pvGet(oiwfsXmin) ;
      pvGet(oiwfsXmax) ;
      pvGet(oiwfsYmin) ;
      pvGet(oiwfsYmax) ;
      pvGet(oiwfsZmin) ;
      pvGet(oiwfsZmax) ;
      tcsProbeSetXYZLimits (2, oiwfsXmin, oiwfsXmax,
                                     oiwfsYmin, oiwfsYmax,
                                     oiwfsZmin, oiwfsZmax) ;
      oiwfsUserXmin = oiwfsXmin ;
      oiwfsUserXmax = oiwfsXmax ;
      oiwfsUserYmin = oiwfsYmin ;
      oiwfsUserYmax = oiwfsYmax ;
      pvPut(oiwfsUserXmin) ;
      pvPut(oiwfsUserXmax) ;
      pvPut(oiwfsUserYmin) ;
      pvPut(oiwfsUserYmax) ;
     } else {
      tcsProbeSetRZLimits (2, oiwfsRmin, oiwfsRmax, oiwfsZmin, 
                           oiwfsZmax) ;
      oiwfsUserRmin = oiwfsRmin ;
      oiwfsUserRmax = oiwfsRmax ;
      pvPut(oiwfsUserRmin) ;
      pvPut(oiwfsUserRmax) ;
     }

    oiwfsUserLimitType = oiwfsLimitType ;
    pvPut(oiwfsUserLimitType) ;

   } state monitoring

   when (efTestAndClear(agSeqInit))
   {
   }  state init
  }

}


/****************************************************************************/
/* The state set controlling the Altair Adaptive Optics subsystem
*/

ss aos
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(aoTimeOut) ;
    efClear(aoRunning) ;
    loopDelay = 1.0 ;
    waitTime[AO] = 0.0 ;                
    timeOutPeriod[AO] = 25.0 ;
    pvGet(intSimulate[AO]) ;
    if (intSimulate[AO])
    {
     snprintf (aoPrefix, 40, "%sao:", macValueGet("top"));
    }
    else
    {
     strcpy (aoPrefix, macValueGet("ao")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[AO])
    {
     snprintf (aoDbName, 40, "%ssimScanControl.VAL", aoPrefix);
     pvAssign(aoScanControl, aoDbName) ;
     strcpy(aoScanControl, "On");
     pvPut(aoScanControl);
    }
    snprintf (aoDbName, 40, "%swfsXMin", aoPrefix);
    pvAssign(aowfsXmin, aoDbName) ;
    pvMonitor(aowfsXmin) ;
    snprintf (aoDbName, 40, "%swfsXMax", aoPrefix);
    pvAssign(aowfsXmax, aoDbName) ;
    pvMonitor(aowfsXmax) ;
    snprintf (aoDbName, 40, "%swfsYMin", aoPrefix);
    pvAssign(aowfsYmin, aoDbName) ;
    pvMonitor(aowfsYmin) ;
    snprintf (aoDbName, 40, "%swfsYMax", aoPrefix);
    pvAssign(aowfsYmax, aoDbName) ;
    pvMonitor(aowfsYmax) ;
    snprintf (aoDbName, 40, "%swfsZMin", aoPrefix);
    pvAssign(aowfsZmin, aoDbName) ;
    pvMonitor(aowfsZmin) ;
    snprintf (aoDbName, 40, "%swfsZMax", aoPrefix);
    pvAssign(aowfsZmax, aoDbName) ;
    pvMonitor(aowfsZmax) ;
    snprintf (aoDbName, 40, "%swfsXPosition", aoPrefix);
    pvAssign(aowfsXpos, aoDbName) ;
    pvMonitor(aowfsXpos) ;
    snprintf (aoDbName, 40, "%swfsYPosition", aoPrefix);
    pvAssign(aowfsYpos, aoDbName) ;
    pvMonitor(aowfsYpos) ;
    snprintf (aoDbName, 40, "%swfsZPosition", aoPrefix);
    pvAssign(aowfsZpos, aoDbName) ;
    pvMonitor(aowfsZpos) ;
    snprintf (aoDbName, 40, "%sstate", aoPrefix);
    pvAssign(applState[AO],aoDbName) ;
    pvMonitor(applState[AO]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[AO]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aos connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[AO]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(aoSeqInit))
   {
   }  state init

   when (pvConnected(applState[AO]))
   {
    waitTime[AO] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aos wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[AO] = waitTime[AO] + loopDelay ;
    if (waitTime[AO] > timeOutPeriod[AO])
    {
      efSet(aoTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(aoSeqInit))
   {
   }  state init

   when (applState[AO] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    tcsProbeSetXYZLimits (3, aowfsXmin, aowfsXmax, 
                             aowfsYmin, aowfsYmax,
                             aowfsZmin, aowfsZmax) ;
    tcsProbeSetDefaults  (3, aowfsXpos, aowfsYpos, aowfsZpos) ;
/* Since there isn't yet a command to set user limits, just use the AO ones */
    aoUserXmin = aowfsXmin ;
    aoUserXmax = aowfsXmax ;
    aoUserYmin = aowfsYmin ;
    aoUserYmax = aowfsYmax ;
    pvPut(aoUserXmax) ;
    pvPut(aoUserXmin) ;
    pvPut(aoUserYmax) ;
    pvPut(aoUserYmin) ;
    efClear(aoTimeOut) ;
    efSet(aoRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aos checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[AO] = waitTime[AO] + loopDelay ;
    if (waitTime[AO] > timeOutPeriod[AO])
    {
      efSet(aoTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[AO]))
   {
     applState[AO] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[AO]))
   {
    applState[AO] = BOOTING ;
   } state init

   when (delay(1.0))
   {
    tcsProbeSetXYZLimits (3, aowfsXmin, aowfsXmax, 
                             aowfsYmin, aowfsYmax,
                             aowfsZmin, aowfsZmax) ;
    aoUserXmin = aowfsXmin ;
    aoUserXmax = aowfsXmax ;
    aoUserYmin = aowfsYmin ;
    aoUserYmax = aowfsYmax ;
    pvPut(aoUserXmax) ;
    pvPut(aoUserXmin) ;
    pvPut(aoUserYmax) ;
    pvPut(aoUserYmin) ;
   } state monitoring

   when (efTestAndClear(aoSeqInit))
   {
   }  state init
  }

}


/****************************************************************************/
/* The state set controlling the MCAO Adaptive Optics subsystem
*/

ss aom
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(aomTimeOut) ;
    efClear(aomRunning) ;
    loopDelay = 1.0 ;
    waitTime[AOM] = 0.0 ;                
    timeOutPeriod[AOM] = 25.0 ;
    pvGet(intSimulate[AOM]) ;
    if (intSimulate[AOM])
    {
     snprintf (aomPrefix, 40, "%saom:", macValueGet("top"));
    }
    else
    {
     strcpy (aomPrefix, macValueGet("aom")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[AOM])
    {
     snprintf (aomDbName, 40, "%ssimScanControl.VAL", aomPrefix);
     pvAssign(aomScanControl, aomDbName) ;
     strcpy(aomScanControl, "On");
     pvPut(aomScanControl);
    }
    snprintf (aomDbName, 40, "%sngsPr1XMin", aomPrefix);
    pvAssign(aomngsPr1Xmin, aomDbName) ;
    pvMonitor(aomngsPr1Xmin) ;
    snprintf (aomDbName, 40, "%sngsPr1XMax", aomPrefix);
    pvAssign(aomngsPr1Xmax, aomDbName) ;
    pvMonitor(aomngsPr1Xmax) ;
    snprintf (aomDbName, 40, "%sngsPr1Rmax", aomPrefix);
    pvAssign(aomngsPr1Rmax, aomDbName) ;
    pvMonitor(aomngsPr1Rmax) ;

    snprintf (aomDbName, 40, "%sngsPr2XMin", aomPrefix);
    pvAssign(aomngsPr2Xmin, aomDbName) ;
    pvMonitor(aomngsPr2Xmin) ;
    snprintf (aomDbName, 40, "%sngsPr2XMax", aomPrefix);
    pvAssign(aomngsPr2Xmax, aomDbName) ;
    pvMonitor(aomngsPr2Xmax) ;
    snprintf (aomDbName, 40, "%sngsPr2Rmax", aomPrefix);
    pvAssign(aomngsPr2Rmax, aomDbName) ;
    pvMonitor(aomngsPr2Rmax) ;

    snprintf (aomDbName, 40, "%sngsPr3XMin", aomPrefix);
    pvAssign(aomngsPr3Xmin, aomDbName) ;
    pvMonitor(aomngsPr3Xmin) ;
    snprintf (aomDbName, 40, "%sngsPr3XMax", aomPrefix);
    pvAssign(aomngsPr3Xmax, aomDbName) ;
    pvMonitor(aomngsPr3Xmax) ;
    snprintf (aomDbName, 40, "%sngsPr3Rmax", aomPrefix);
    pvAssign(aomngsPr3Rmax, aomDbName) ;
    pvMonitor(aomngsPr3Rmax) ;

    snprintf (aomDbName, 40, "%sngsPr1:X", aomPrefix);
    pvAssign(aomngsPr1Xpos, aomDbName) ;
    pvMonitor(aomngsPr1Xpos) ;
    snprintf (aomDbName, 40, "%sngsPr1:Y", aomPrefix);
    pvAssign(aomngsPr1Ypos, aomDbName) ;
    pvMonitor(aomngsPr1Ypos) ;
    snprintf (aomDbName, 40, "%sngsPr2:X", aomPrefix);
    pvAssign(aomngsPr2Xpos, aomDbName) ;
    pvMonitor(aomngsPr2Xpos) ;
    snprintf (aomDbName, 40, "%sngsPr2:Y", aomPrefix);
    pvAssign(aomngsPr2Ypos, aomDbName) ;
    pvMonitor(aomngsPr2Ypos) ;
    snprintf (aomDbName, 40, "%sngsPr3:X", aomPrefix);
    pvAssign(aomngsPr3Xpos, aomDbName) ;
    pvMonitor(aomngsPr3Xpos) ;
    snprintf (aomDbName, 40, "%sngsPr3:Y", aomPrefix);
    pvAssign(aomngsPr3Ypos, aomDbName) ;
    pvMonitor(aomngsPr3Ypos) ;

    snprintf (aomDbName, 40, "%sstate", aomPrefix);
    pvAssign(applState[AOM],aomDbName) ;
    pvMonitor(applState[AOM]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[AOM]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aom connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[AOM]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(aomSeqInit))
   {
   }  state init

   when (pvConnected(applState[AOM]))
   {
    waitTime[AOM] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aom wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[AOM] = waitTime[AOM] + loopDelay ;
    if (waitTime[AOM] > timeOutPeriod[AOM])
    {
      efSet(aomTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(aomSeqInit))
   {
   }  state init

   when (applState[AOM] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    tcsProbeSetAOMLimits (4, aomngsPr1Xmin, aomngsPr1Xmax, 0.0, aomngsPr1Rmax);
    tcsProbeSetDefaults  (4, aomngsPr1Xpos, aomngsPr1Ypos, 0.0) ;
    tcsProbeSetAOMLimits (5, aomngsPr2Xmin, aomngsPr2Xmax, 0.0, aomngsPr2Rmax);
    tcsProbeSetDefaults  (5, aomngsPr2Xpos, aomngsPr2Ypos, 0.0) ;
    tcsProbeSetAOMLimits (6, aomngsPr3Xmin, aomngsPr3Xmax, 0.0, aomngsPr3Rmax);
    tcsProbeSetDefaults  (6, aomngsPr3Xpos, aomngsPr3Ypos, 0.0) ;

/* Since there isn't yet a command to set user limits, just use the AOM ones */
    aomPr1UserXmin = aomngsPr1Xmin ;
    aomPr1UserXmax = aomngsPr1Xmax ;
    aomPr1UserRmin = 0.0 ;
    aomPr1UserRmax = aomngsPr1Rmax ;
    pvPut(aomPr1UserXmax) ;
    pvPut(aomPr1UserXmin) ;
    pvPut(aomPr1UserRmax) ;
    pvPut(aomPr1UserRmin) ;

    aomPr2UserXmin = aomngsPr2Xmin ;
    aomPr2UserXmax = aomngsPr2Xmax ;
    aomPr2UserRmin = 0.0 ;
    aomPr2UserRmax = aomngsPr2Rmax ;
    pvPut(aomPr2UserXmax) ;
    pvPut(aomPr2UserXmin) ;
    pvPut(aomPr2UserRmax) ;
    pvPut(aomPr2UserRmin) ;

    aomPr3UserXmin = aomngsPr3Xmin ;
    aomPr3UserXmax = aomngsPr3Xmax ;
    aomPr3UserRmin = 0.0 ;
    aomPr3UserRmax = aomngsPr3Rmax ;
    pvPut(aomPr3UserXmax) ;
    pvPut(aomPr3UserXmin) ;
    pvPut(aomPr3UserRmax) ;
    pvPut(aomPr3UserRmin) ;

    efClear(aomTimeOut) ;
    efSet(aomRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss aom checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[AOM] = waitTime[AOM] + loopDelay ;
    if (waitTime[AOM] > timeOutPeriod[AOM])
    {
      efSet(aomTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[AOM]))
   {
     applState[AOM] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[AOM]))
   {
    applState[AOM] = BOOTING ;
   } state init

   when (delay(1.0))
   {
    tcsProbeSetAOMLimits (4, aomngsPr1Xmin, aomngsPr1Xmax, 0.0, aomngsPr1Rmax);
    tcsProbeSetAOMLimits (5, aomngsPr2Xmin, aomngsPr2Xmax, 0.0, aomngsPr2Rmax);
    tcsProbeSetAOMLimits (6, aomngsPr3Xmin, aomngsPr3Xmax, 0.0, aomngsPr3Rmax);
    aomPr1UserXmin = aomngsPr1Xmin ;
    aomPr1UserXmax = aomngsPr1Xmax ;
    aomPr1UserRmin = 0.0 ;
    aomPr1UserRmax = aomngsPr1Rmax ;
    pvPut(aomPr1UserXmax) ;
    pvPut(aomPr1UserXmin) ;
    pvPut(aomPr1UserRmax) ;
    pvPut(aomPr1UserRmin) ;
    aomPr2UserXmin = aomngsPr2Xmin ;
    aomPr2UserXmax = aomngsPr2Xmax ;
    aomPr2UserRmin = 0.0 ;
    aomPr2UserRmax = aomngsPr2Rmax ;
    pvPut(aomPr2UserXmax) ;
    pvPut(aomPr2UserXmin) ;
    pvPut(aomPr2UserRmax) ;
    pvPut(aomPr2UserRmin) ;
    aomPr3UserXmin = aomngsPr3Xmin ;
    aomPr3UserXmax = aomngsPr3Xmax ;
    aomPr3UserRmin = 0.0 ;
    aomPr3UserRmax = aomngsPr3Rmax ;
    pvPut(aomPr3UserXmax) ;
    pvPut(aomPr3UserXmin) ;
    pvPut(aomPr3UserRmax) ;
    pvPut(aomPr3UserRmin) ;
   } state monitoring

   when (efTestAndClear(aomSeqInit))
   {
   }  state init
  }

}

/****************************************************************************/
/* The state set controlling the GSAOI ODGW (On detector Guide Window) 
*/

ss gsaoi 
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(gsaoiTimeOut) ;
    efClear(gsaoiRunning) ;
/* GSAOI counts pixels from 1 and there is a deadband of 4 */
    gsaoiChipXmin = 5.0 ;
    gsaoiChipXmax = 2048.0 - 4.0;
    gsaoiChipYmin = 5.0 ;
    gsaoiChipYmax = 2048.0 - 4.0;
    loopDelay = 1.0 ;
    waitTime[GSAOI] = 0.0 ;                
    timeOutPeriod[GSAOI] = 25.0 ;
    pvGet(intSimulate[GSAOI]) ;
    if (intSimulate[GSAOI])
    {
     strcpy(gsaoiPrefix, "tgsaoi:") ;
    }
    else
    {
     strcpy (gsaoiPrefix, macValueGet("gsaoi")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    if (intSimulate[GSAOI])
    {
     snprintf (gsaoiDbName, 40, "%ssimScanControl.VAL", gsaoiPrefix);
     pvAssign(gsaoiScanControl, gsaoiDbName) ;
     strcpy(gsaoiScanControl, "On");
     pvPut(gsaoiScanControl);
    }
    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winXo1", gsaoiPrefix);
    pvAssign(odgw1Xcen, gsaoiDbName) ;
    pvMonitor(odgw1Xcen) ;
    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winYo1", gsaoiPrefix);
    pvAssign(odgw1Ycen, gsaoiDbName) ;
    pvMonitor(odgw1Ycen) ;

    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winXo2", gsaoiPrefix);
    pvAssign(odgw2Xcen, gsaoiDbName) ;
    pvMonitor(odgw2Xcen) ;
    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winYo2", gsaoiPrefix);
    pvAssign(odgw2Ycen, gsaoiDbName) ;
    pvMonitor(odgw2Ycen) ;

    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winXo3", gsaoiPrefix);
    pvAssign(odgw3Xcen, gsaoiDbName) ;
    pvMonitor(odgw3Xcen) ;
    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winYo3", gsaoiPrefix);
    pvAssign(odgw3Ycen, gsaoiDbName) ;
    pvMonitor(odgw3Ycen) ;

    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winXo4", gsaoiPrefix);
    pvAssign(odgw4Xcen, gsaoiDbName) ;
    pvMonitor(odgw4Xcen) ;
    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winYo4", gsaoiPrefix);
    pvAssign(odgw4Ycen, gsaoiDbName) ;
    pvMonitor(odgw4Ycen) ;


    snprintf (gsaoiDbName, 40, "%ssad:dc:d_gdr_winSizeS", gsaoiPrefix);
    pvAssign(odgwExtent, gsaoiDbName) ;
    pvMonitor(odgwExtent) ;

/* Note we must use a tcs record here as GSAOI uses strings for
 * the states and we need an integer
 */
    snprintf (gsaoiDbName, 40, "%sgsaoiState", macValueGet("top"));
    pvAssign(applState[GSAOI], gsaoiDbName) ;
    pvMonitor(applState[GSAOI]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[GSAOI]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gsaoi connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[GSAOI]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(gsaoiSeqInit))
   {
   }  state init

   when (pvConnected(applState[GSAOI]))
   {
    waitTime[GSAOI] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gsaoi wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[GSAOI] = waitTime[GSAOI] + loopDelay ;
    if (waitTime[GSAOI] > timeOutPeriod[GSAOI])
    {
      efSet(gsaoiTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
*/

  state checkState
  {

   when (efTestAndClear(gsaoiSeqInit))
   {
   }  state init

   when (applState[GSAOI] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/

/* Note, previously the ODGW limits were used in the calls to 
 * tcsProbeSetXYZLimits. This was wrong. What we need are the chip 
 * limits. There does not seem to be a record in GSAOI to read these from
 * but they are pretty well fixed. There is a band of 4 pixels around the
 * edge that is not used for imaging.
 * Note also that as well as setting "probe" defaults we also set defaults
 * for the guide windows
 */ 
    
    tcsProbeSetXYZLimits (7, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    odgw1Xpos = odgw1Xcen ;
    odgw1Ypos = odgw1Ycen ;
    tcsProbeSetDefaults  (7, odgw1Xpos, odgw1Ypos, 0.0) ;
    tcsGuideInitOdgwPosns(0, odgw1Xpos, odgw1Ypos) ;
    tcsProbeSetXYZLimits (8, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    odgw2Xpos = odgw2Xcen  ;
    odgw2Ypos = odgw2Ycen  ;
    tcsProbeSetDefaults  (8, odgw2Xpos, odgw2Ypos, 0.0) ;
    tcsGuideInitOdgwPosns(1, odgw1Xpos, odgw1Ypos) ;
    tcsProbeSetXYZLimits (9, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    odgw3Xpos = odgw3Xcen  ;
    odgw3Ypos = odgw3Ycen  ;
    tcsProbeSetDefaults  (9, odgw3Xpos, odgw3Ypos, 0.0) ;
    tcsGuideInitOdgwPosns(2, odgw1Xpos, odgw1Ypos) ;
    tcsProbeSetXYZLimits (10, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    odgw4Xpos = odgw4Xcen  ;
    odgw4Ypos = odgw4Ycen  ;
    tcsProbeSetDefaults  (10, odgw4Xpos, odgw4Ypos, 0.0) ;
    tcsGuideInitOdgwPosns(3, odgw1Xpos, odgw1Ypos) ;


    efClear(gsaoiTimeOut) ;
    efSet(gsaoiRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gsaoi checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[GSAOI] = waitTime[GSAOI] + loopDelay ;
    if (waitTime[GSAOI] > timeOutPeriod[GSAOI])
    {
      efSet(gsaoiTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[GSAOI]))
   {
     applState[GSAOI] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[GSAOI]))
   {
    applState[GSAOI] = BOOTING ;
   } state init

   when (delay(1.0))
   {
    /* This is probably redundant - the chip limits will not change */
    tcsProbeSetXYZLimits (7, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    tcsProbeSetXYZLimits (8, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    tcsProbeSetXYZLimits (9, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
    tcsProbeSetXYZLimits (10, gsaoiChipXmin, gsaoiChipXmax, gsaoiChipYmin, 
                          gsaoiChipYmax, 0.0, 0.0);
   } state monitoring

   when (efTestAndClear(gsaoiSeqInit))
   {
   }  state init
  }

}


/****************************************************************************/
/* The state set controlling GPOL
*/

ss gpol
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(gpTimeOut) ;
    efClear(gpRunning) ;
    loopDelay = 1.0 ;
    waitTime[GP] = 0.0 ;                
    timeOutPeriod[GP] = 30.0 ;
    pvGet(intSimulate[GP]) ;
    if (intSimulate[GP])
    {
     snprintf (gpPrefix, 40, "%sgp:", macValueGet("top"));
    }
    else
    {
     strcpy (gpPrefix, macValueGet("gp")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    snprintf (gpDbName, 40, "%ssad:state", gpPrefix);
    pvAssign(applState[GP],gpDbName) ;
    pvMonitor(applState[GP]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[GP]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gpol connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[GP]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(gpSeqInit))
   {
   }  state init

   when (pvConnected(applState[GP]))
   {
    waitTime[GP] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gpol wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[GP] = waitTime[GP] + loopDelay ;
    if (waitTime[GP] > timeOutPeriod[GP])
    {
      efSet(gpTimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
 * subsystem cannot reach the "Running" state before the time out period
*/

  state checkState
  {

   when (efTestAndClear(gpSeqInit))
   {
   }  state init

   when (applState[GP] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    efClear(gpTimeOut) ;
    efSet(gpRunning) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss gpol checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[GP] = waitTime[GP] + loopDelay ;
    if (waitTime[GP] > timeOutPeriod[GP])
    {
      efSet(gpTimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[GP]))
   {
     applState[GP] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[GP]))
   {
    applState[GP] = BOOTING ;
   } state init

   when (delay(1.0))
   {
   } state monitoring

   when (efTestAndClear(gpSeqInit))
   {
   }  state init
  }

}


/****************************************************************************/
/* The state set controlling the PCS 
*/

ss m1s 
{

/* The init state is present to do any one time initialisation. 
 * The state will be executed at the following times
 * 1) when the state set is first loaded
 * 2) when an INIT or RESET has been received 
 * 3) When the subsystem disconnects
*/

  state init
  {
   when()
   {
    efClear(m1TimeOut) ;
    efClear(m1Running) ;
    efClear(m1Restore) ;
    loopDelay = 1.0 ;
    waitTime[M1] = 0.0 ;                
    timeOutPeriod[M1] = 30.0 ;
    pvGet(intSimulate[M1]) ;
    if (intSimulate[M1])
    {
     snprintf (m1Prefix, 40, "%sm1:", macValueGet("top"));
    }
    else
    {
     strcpy (m1Prefix, macValueGet("m1")) ;
    }

/* Now construct each database name and assign the relevant variable to it */
    snprintf (m1DbName, 40, "%sstate", m1Prefix);
    pvAssign(applState[M1],m1DbName) ;
    pvMonitor(applState[M1]) ;
   }  state connecting
  }

/* The connecting state is present to provide a means of waiting for a 
 * period of time for the needed connections to be made or, if the connections
 * are available to wait for the subsystem to reach the "Running" state
*/

  state connecting
  {
   when (pvConnected(applState[M1]))
   {
    DBGMSG (DBG_NONE, "tcsSeqInit: ss pcs connecting -> checkstate\n");
   } state checkState

   when (!pvConnected(applState[M1]))
   {
   } state waitConnect
  }

/* The state waitConnect waits indefinitely for the subsystem
 * (or subsystem simulation) to be booted. Once the timeout period is
 * exceeded, the timeout event flag is set to signal to any other state 
 * set that a timeout has occurred.
*/
 
  state waitConnect
  {
   when (efTestAndClear(m1SeqInit))
   {
   }  state init

   when (pvConnected(applState[M1]))
   {
    waitTime[M1] = 0.0 ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss pcs wait connect -> checkstate\n");
   } state checkState
 
   when (delay(loopDelay))
   {
    waitTime[M1] = waitTime[M1] + loopDelay ;
    if (waitTime[M1] > timeOutPeriod[M1])
    {
      efSet(m1TimeOut) ;
    } 
   }  state waitConnect
  }
 

/* The state checkState waits until the subsystem state changes to "Running"
 * It also reacts to disconnect events and sets the time out flag if the
 * subsystem cannot reach the "Running" state before the time out period
*/

  state checkState
  {

   when (efTestAndClear(m1SeqInit))
   {
   }  state init

   when (applState[M1] == RUNNING && semInitialized == TRUE)
   {

/* Any subsystem specific initialisation should go here.
 * Initialisation that depends on the state of a number of subsystems
 * should go in the initialisation phase of the master state set
*/
    efClear(m1TimeOut) ;
    efSet(m1Running) ;
    DBGMSG (DBG_NONE, "tcsSeqInit: ss mcs checkState -> monitoring\n");
   } state monitoring

   when (delay(loopDelay))
   {
    waitTime[M1] = waitTime[M1] + loopDelay ;
    if (waitTime[M1] > timeOutPeriod[M1])
    {
      efSet(m1TimeOut) ;
    }
   }  state checkState

   when (!pvConnected(applState[M1]))
   {
     applState[M1] = BOOTING ;
   }  state init

  }


/* The monitoring state is the state in which the sequence program should
 * be most of the time. It does any periodic housekeeping and monitors
 * for disconnect events as well as Init and Reset commands sent to the
 * TCS
*/

  state monitoring
  {
   when (!pvConnected(applState[M1]))
   {
/* Open loops and clear the initialisation flag so that when we reconnect a
*  decision has to be made about whether to zero or restore the M1 model
*/
    if (m1GuideOn) {
      strcpy(m1GuideModeA, "OFF");
      m1GuideModeDIR = 3 ;
      pvPut(m1GuideModeA) ;
      pvPut(m1GuideModeDIR);
    }
    if (m1FigUpdates) {
      strcpy (m1FigUpdatesA, "OFF") ;
      m1FigUpdatesDIR = 3 ;
      pvPut(m1FigUpdatesA);
      pvPut(m1FigUpdatesDIR);
    }
    tcsOpticsM1ClearModel();
    applState[M1] = BOOTING ;
   } state init

   when (delay(5.0))
   {
/* N.B. it is crucial that bit 2 is set in the flags or else you will
*  crash the sequencer. Bit 8 is also set so that you truncate the output 
*  file rather than appending to it.
*  There is also a problem with macro substitutions. Hence the need to
*  call different functions depending on the value of "top"
*/
     if (m1GuideOn && m1FigUpdates ) {
       m1ModelType = tcsOpticsGetM1SaveType();
       snprintf (confFileSave, MAX_PATH, "%s/%s", CONF_FILES_DIR, "tcsM1Model.save");
       setConfFileRest(confFileRest, m1ModelType, tcsPrefix, CONF_FILES_DIR, tcsPrefNoColon);
       pvsave(confFileSave, tcsPrefixSub, confFileRest, 10);
     }
   } state monitoring

   when (efTestAndClear(m1Restore))
   {
     m1ModelType = tcsOpticsGetM1ModelType();
     setConfFileRest(confFileRest, m1ModelType, tcsPrefix, CONF_FILES_DIR, tcsPrefNoColon);
     pstat = pvload(confFileRest, "", 2);
     if (pstat) {
       strcpy(m1CommSentMsg, "Failed to restore M1 model data");
       m1CommSentC = menuCarstatesERROR ;
       pvPut(m1CommSentMsg);
       pvPut(m1CommSentC);
     }
   } state monitoring

   when (efTestAndClear(m1SeqInit))
   {
   }  state init
  }

}


/***************************************************************************/
/* This section contains the code for the master state set. This is the 
*  state set that initialises the TCS application itself and controls the
*  state sets that monitor each TCS subsystem.
*/

ss master
{
 state init
 {
  when ()
  {
    firstInit = FALSE ;
    tcsState  = INITIALISING ;
    tcsName   = 1 ;
    go        = INIT ;
    goM       = MARK ;
    goS       = INIT;
    setEcsDefs = INIT ;
    strcpy (goM2XY, "enable");
    strcpy (goM2Tilt, "enable");
    strcpy (slowScan, "10 second") ;
    for ( i = 0 ; i < MAXSUBSYS ; i++ )
    {
      done[i] = FALSE ;
      timedOut[i] = FALSE ;
    }
    pvPut(tcsState) ;
    pvPut(tcsName);
    strcpy (tcsPrefix, macValueGet("top")) ;
    strcpy (CONF_FILES_DIR, macValueGet("CONF_FILES_DIR"));
    snprintf (tcsPrefixSub, 40, "prefix=%s", macValueGet("top")) ;
    snprintf (tcsPrefNoColon, strlen(tcsPrefix), "%s", tcsPrefix);

    // THE FOLLOWING WAS ABSORBED FROM THE "noclock" STATE, WHICH
    // BECAME IRRELEVANT SINCE WE ASSUME THE CLOCK IS ALWAYS IN SYNC

    // NOTE: The following two functions MAY fail.
    //       A proper state transition should take this
    //       into account and not mark semInitialized until
    //       after they return "OK". But the functions need
    //       to be modified first for proper re-entry.
    //tcsOpticsInit();
    semInitialized = TRUE;
    pvPut(goS);
    DBGMSG (DBG_NONE, "tcsSeqInit: ss master sem init -> initialising\n") ;
  } state initialising
 }

 state initialising
 {

/* This state waits for each subsystem to be flagged as either timed out
*  or for it to transition to the "Running" state. In either case the 
*  subsystem is marked "Done". 
*  Once all subsytems are marked "Done" the TCS moves to the "Running"
*  state.
*  N.B. Each when clause consists of a logical AND such that it will be 
*  executed once only. This prevents the state entering an infinite loop
*  and consuming all the CPU
*/

  when (!firstInit && done[MC] && done[CR] && done[EC] && done[M2] && 
     done[AG] && done[AO] && done[GP] && done[M1] && done[AOM])
  {
   pvGet(tcsInitCar);
/* Don't do anything if INIT is in ERROR state */
   if (tcsInitCar != menuCarstatesERROR)
    {
     strcpy (mediumScan, "5 second" ) ;
     strcpy (medFastScan, "1 second" ) ;
/* Limit scan doesn't really go at this rate. The capfast schematic limits
*  updates to 1 Hz. This value is really just the smallest time interval
*  you could go at.
*/
     strcpy (limitsScan, ".2 second" ) ;
     strcpy (solsysScan, "10 second" ) ;
     strcpy (fastScan, ".1 second" ) ;
     strcpy (ecsScan, ".5 second" ) ;
     strcpy (RADecScan, ".5 second" ) ;
     strcpy (limitsEnable, "0" ) ;
     tcsState = RUNNING ;
     pvPut(goM2XY) ;
     pvPut(goM2Tilt);
     pvPut(go) ;
     pvPut(goM) ;
     pvPut(slowScan) ;
     pvPut(mediumScan) ;
     pvPut(medFastScan) ;
     pvPut(fastScan) ;
     pvPut(solsysScan) ;
     pvPut(limitsScan) ;
     pvPut(ecsScan) ;
     pvPut(RADecScan) ;
     pvPut(limitsEnable) ;
     pvPut(setEcsDefs) ;
     tcsInitCarIval = menuCarstatesIDLE ;
     pvPut(tcsInitCarIval) ;
     pvPut(tcsState) ;
     firstInit = TRUE ;
     DBGMSG (DBG_NONE, "tcsSeqInit: ss master initialising -> monitoring (1st time)\n") ;
   }
  } state monitoring

/* This clause will only be executed on initialisations after the first */

  when (firstInit && done[MC] && done[CR] && done[EC] && done[M2] && done[AG]
    && done[AO] && done[GP] && done[M1] && done[AOM])
  {
   pvGet(tcsInitCar);
/* Don't do anything if INIT is in ERROR state */
   if (tcsInitCar != menuCarstatesERROR)
    {
     pvPut(setEcsDefs) ;
     tcsState = RUNNING ;
     tcsInitCarIval = menuCarstatesIDLE ;
     pvPut(tcsInitCarIval) ;
     pvPut(tcsState) ;
     DBGMSG (DBG_NONE, "tcsSeqInit: ss master initialising -> monitoring\n") ;
    }
  } state monitoring
    
  when (efTest(mcTimeOut) && !timedOut[MC])
  {
/* Subsystem timed out so fetch TCS internal default parameters for current
*  azimuth and elevation
*/
   pvGet(defAz) ;
   pvGet(defEl) ;
   initAz = defAz ;
   initEl = defEl ;
   pvPut(initAz) ;
   pvPut(initEl) ;
   done[MC] = TRUE ;
   timedOut[MC] = TRUE ;
   printf( "tcsSeqInit: mcTimeOut\n") ;
  } state initialising

  when (efTest(crTimeOut) && !timedOut[CR])
  {

/* This setting of the initial RPA may need modifying. The Fast loop
*  currently has an input link directly to the Cass simulator so that
*  it can pull in this value. It may be that this will over ride setting
*  a value directly this way
*/

   pvGet(defrma) ;
   initRma = defrma*R2D ;
   initRmaF = defrma ;
   initRmaVel = 0.0 ;
   pvPut (initRma) ;
   pvPut (initRmaF) ;
   pvPut (initRmaVel) ;
   done[CR] = TRUE ;
   timedOut[CR] = TRUE ;
   printf( "tcsSeqInit: crTimeOut\n") ;
  } state initialising

  when (efTest(mcRunning) && !done[MC])
  {
/* Everything has connected OK so fetch the current az and el to initialise
*  the pointing loops.
*/
   pvGet(currAz) ;
   pvGet(currEl) ;
   initAz = currAz ;
   initEl = currEl ;
   pvPut(initAz) ;
   pvPut(initEl) ;
   done[MC] = TRUE ;
   timedOut[MC] = FALSE ;
  } state initialising

  when (efTest(crRunning) && !done[CR])
  {

/* No need to copy current Rma as fast loop uses a direct input link.
*  This will have to change eventually as this wires the fast loop
*  directly to the simulator
*/
   pvGet(currRma) ;
   initRma = currRma*R2D ;
   pvPut(initRma) ;
   done[CR] = TRUE ;
   timedOut[CR] = FALSE ;
   DBGMSGREAL (DBG_FULL , "tcsSeqInit: initial Rma ", initRma) ;
  } state initialising

  when (efTest(ecRunning) && !done[EC])
  {
   done[EC] = TRUE ;
   timedOut[EC] = FALSE ;
  } state initialising

/* Handle case where ec has timed out and so must use TCS internal defaults */

  when (efTest(ecTimeOut) && !timedOut[EC])
  {
   pvGet(defMinBotShtr) ;
   pvGet(defMaxBotShtr) ;
   pvGet(defMinTopShtr) ;
   pvGet(defMaxTopShtr) ;
   pvGet(defDomePos) ;
   pvGet(defBotShtrPos) ;
   pvGet(defTopShtrPos) ;

   if (tcsEcsSetShutLimits (defMinBotShtr, defMaxBotShtr, defMinTopShtr,
                            defMaxTopShtr, logrecord))
   {
     pvPut (logrecord) ;
   }

   if (tcsEcsSetPosnDefs (defDomePos, defBotShtrPos, defTopShtrPos, logrecord))
   {
    pvPut (logrecord) ;
   }
   done[EC] = TRUE ;
   timedOut[EC] = TRUE ;
   DBGMSG (DBG_NONE, "tcsSeqInit: ecTimeOut\n") ;
  } state initialising


  when (efTest(m2Running) && !done[M2])
  {
   done[M2] = TRUE ;
   timedOut[M2] = FALSE ;
  } state initialising

/* Handle case where m2 has timed out so must use TCS internal default 
 * parameters 
*/

  when (efTest(m2TimeOut) && !timedOut[M2])
  {
   pvGet (defM2MaxChopFreqThrow) ;
   pvGet (defM2BreakChopFreqThrow);
   pvGet (defM2MinChopFreqThrow);
   pvGet (defM2MaxChopFreq) ;
   pvGet (defM2BreakChopFreq);
   pvGet (defM2MinChopFreq) ;
   pvGet (defM2MinTilt);
   pvGet (defM2MaxTilt);
   pvGet (defM2MinTiltZ);
   pvGet (defM2MaxTiltZ);
   pvGet (defTopEnd);
   tcsOpticsSetChopLimits (defM2MinChopFreq, defM2BreakChopFreq,
        defM2MaxChopFreq,
        defM2MinChopFreqThrow, defM2BreakChopFreqThrow,
        defM2MaxChopFreqThrow) ;
   tcsOpticsSetTiltLimits (defM2MinTilt, defM2MaxTilt, defM2MinTiltZ,
                           defM2MaxTiltZ);
   tcsOpticsSetTopEnd (defTopEnd);
   done[M2] = TRUE ;
   timedOut[M2] = TRUE ;
   printf( "tcsSeqInit: m2TimeOut\n") ;
  }  state initialising

  when (efTest(agRunning) && !done[AG])
  {
   done[AG] = TRUE ;
   timedOut[AG] = FALSE ;
  } state initialising

/* Handle case where A&G has timed out so initialise with TCS internal default
*  parameters.
*/

  when (efTest(agTimeOut) && !timedOut[AG])
  {
   pvGet(defPwfs1Xposn) ;
   pvGet(defPwfs1Yposn) ;
   pvGet(defPwfs1Zposn) ;
   tcsProbeSetDefaults (0, defPwfs1Xposn, defPwfs1Yposn, defPwfs1Zposn) ;

   pvGet(defPwfs1Rmin) ;
   pvGet(defPwfs1Rmax) ;
   pvGet(defPwfs1Zmin) ;
   pvGet(defPwfs1Zmax) ;

   pvGet(defPwfs2Xposn) ;
   pvGet(defPwfs2Yposn) ;
   pvGet(defPwfs2Zposn) ;
   tcsProbeSetDefaults (1, defPwfs2Xposn, defPwfs2Yposn, defPwfs2Zposn) ;

   pvGet(defPwfs2Rmin) ;
   pvGet(defPwfs2Rmax) ;
   pvGet(defPwfs2Zmin) ;
   pvGet(defPwfs2Zmax) ;

   tcsProbeSetRadii (defPwfs1Rmin, defPwfs1Rmax, defPwfs2Rmin, defPwfs2Rmax);
   tcsProbeSetRZLimits (0, pwfs1UserRmin, pwfs1UserRmax,
                                 defPwfs1Zmin, defPwfs1Zmax) ;
   tcsProbeSetRZLimits (1, pwfs2UserRmin, pwfs2UserRmax,
                                 defPwfs2Zmin, defPwfs2Zmax) ;

/* Set rotary table limits */
   pvGet(defPwfs1RTmin) ;
   pvGet(defPwfs1RTmax) ;
   pvGet(defPwfs2RTmin) ;
   pvGet(defPwfs2RTmax) ;
   tcsProbeSetRTLimits (defPwfs1RTmin, defPwfs1RTmax, defPwfs2RTmin,
                        defPwfs2RTmax);

   pvGet(defOiwfsXposn) ;
   pvGet(defOiwfsYposn) ;
   pvGet(defOiwfsZposn) ;
   tcsProbeSetDefaults (2, defOiwfsXposn, defOiwfsYposn, defOiwfsZposn) ;

   pvGet(defOiwfsLimitType) ;
   pvGet(defOiwfsZmin) ;
   pvGet(defOiwfsZmax) ;
   if (defOiwfsLimitType == XY )
   {
    pvGet(defOiwfsXmin) ;
    pvGet(defOiwfsXmax) ;
    pvGet(defOiwfsYmin) ;
    pvGet(defOiwfsYmax) ;
    tcsProbeSetXYZLimits (2, defOiwfsXmin, defOiwfsXmax,
                                   defOiwfsYmin, defOiwfsYmax,
                                   defOiwfsZmin, defOiwfsZmax) ;
   }
   else
   {
    pvGet(defOiwfsRmin) ;
    pvGet(defOiwfsRmax) ;
    tcsProbeSetRZLimits (2, defOiwfsRmin, defOiwfsRmax,
                                  defOiwfsZmin, defOiwfsZmax) ;
   }
   done[AG] = TRUE ;
   timedOut[AG] = TRUE ;
   printf( "tcsSeqInit: agTimeOut\n") ;
  }  state initialising 

  when (efTest(aomRunning) && !done[AOM])
  {
   done[AOM] = TRUE ;
   timedOut[AOM] = FALSE ;
  } state initialising

/* Handle case where AOM has timed out so initialise with TCS internal default
*  parameters.
*/

  when (efTest(aomTimeOut) && !timedOut[AOM])
  {
   pvGet(defAomngsPr1Xposn) ;
   pvGet(defAomngsPr1Yposn) ;
   tcsProbeSetDefaults (4, defAomngsPr1Xposn, defAomngsPr1Yposn, 0.0);

   pvGet(defAomngsPr2Xposn) ;
   pvGet(defAomngsPr2Yposn) ;
   tcsProbeSetDefaults (5, defAomngsPr2Xposn, defAomngsPr2Yposn, 0.0);

   pvGet(defAomngsPr3Xposn) ;
   pvGet(defAomngsPr3Yposn) ;
   tcsProbeSetDefaults (6, defAomngsPr3Xposn, defAomngsPr3Yposn, 0.0);

   pvGet(defAomngsPr1Xmin) ;
   pvGet(defAomngsPr1Xmax) ;
   pvGet(defAomngsPr1Rmin) ;
   pvGet(defAomngsPr1Rmax) ;
   tcsProbeSetAOMLimits (4, defAomngsPr1Xmin, defAomngsPr1Xmax,
                            defAomngsPr1Rmin, defAomngsPr1Rmax);

   pvGet(defAomngsPr2Xmin) ;
   pvGet(defAomngsPr2Xmax) ;
   pvGet(defAomngsPr2Rmin) ;
   pvGet(defAomngsPr2Rmax) ;
   tcsProbeSetAOMLimits (5, defAomngsPr2Xmin, defAomngsPr2Xmax,
                            defAomngsPr2Rmin, defAomngsPr2Rmax);

   pvGet(defAomngsPr3Xmin) ;
   pvGet(defAomngsPr3Xmax) ;
   pvGet(defAomngsPr3Rmin) ;
   pvGet(defAomngsPr3Rmax) ;
   tcsProbeSetAOMLimits (6, defAomngsPr3Xmin, defAomngsPr3Xmax,
                            defAomngsPr3Rmin, defAomngsPr3Rmax);

   done[AOM] = TRUE ;
   timedOut[AOM] = TRUE ;
   printf( "tcsSeqInit: aomTimeOut\n") ;
  }  state initialising 


  when (efTest(aoRunning) && !done[AO])
  {

/* This is a temporary fix until the names of the Altair limit records
*  are agreed on
*/
   pvGet(defAowfsZmin) ;
   pvGet(defAowfsZmax) ;
   pvGet(defAowfsXmin) ;
   pvGet(defAowfsXmax) ;
   pvGet(defAowfsYmin) ;
   pvGet(defAowfsYmax) ;
   tcsProbeSetXYZLimits (3, defAowfsXmin, defAowfsXmax,
                            defAowfsYmin, defAowfsYmax,
                            defAowfsZmin, defAowfsZmax) ;
   done[AO] = TRUE ;
   timedOut[AO] = FALSE ;
  } state initialising
  
/* Handle case where connection to Altair times out */

  when (efTest(aoTimeOut) && !timedOut[AO])
  {
   pvGet(defAowfsZmin) ;
   pvGet(defAowfsZmax) ;
   pvGet(defAowfsXmin) ;
   pvGet(defAowfsXmax) ;
   pvGet(defAowfsYmin) ;
   pvGet(defAowfsYmax) ;
   tcsProbeSetXYZLimits (3, defAowfsXmin, defAowfsXmax,
                            defAowfsYmin, defAowfsYmax,
                            defAowfsZmin, defAowfsZmax) ;
   done[AO] = TRUE ;
   timedOut[AO] = TRUE ;
   printf( "tcsSeqInit: aoTimeOut\n") ;
  } state initialising

  when (efTest(gpRunning) && !done[GP])
  {
   done[GP] = TRUE ;
   timedOut[GP] = FALSE ;
  } state initialising
  
  when (efTest(gpTimeOut) && !timedOut[GP])
  {
   done[GP] = TRUE ;
   timedOut[GP] = TRUE ;
   printf( "tcsSeqInit: gpTimeOut\n") ;
  } state initialising

  when (efTest(m1Running) && !done[M1])
  {
   done[M1] = TRUE ;
   timedOut[M1] = FALSE ;
  } state initialising
  
  when (efTest(m1TimeOut) && !timedOut[M1])
  {
   done[M1] = TRUE ;
   timedOut[M1] = TRUE ;
   printf( "tcsSeqInit: m1TimeOut\n") ;
  } state initialising

 } 

 state monitoring
 {

/* This state checks for disconnect events for each subsystem as well as
 * for transitions to the "Running" state. Transitions to the "Running"
 * state are expected if the subsystem had previously set its timeout
 * flag
*/

  when ((!pvConnected(applState[MC]) && !timedOut[MC])  ||
        (efTest(mcRunning) && timedOut[MC]))
  {
   done[MC] = FALSE ;
   timedOut[MC] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: mount event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[CR]) && !timedOut[CR])  ||
        (efTest(crRunning) && timedOut[CR]))
  {
   done[CR] = FALSE ;
   timedOut[CR] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: rotator event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[EC]) && !timedOut[EC])  ||
        (efTest(ecRunning) && timedOut[EC]))
  {
   tcsState = INITIALISING;
   done[EC] = FALSE ;
   timedOut[EC] = FALSE ;
   pvPut(tcsState);
   DBGMSG (DBG_MIN, "tcsSeqInit: enclosure event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[M2]) && !timedOut[M2])  ||
        (efTest(m2Running) && timedOut[M2]))
  {
   done[M2] = FALSE ;
   timedOut[M2] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: M2 event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[AG]) && !timedOut[AG])  ||
        (efTest(agRunning) && timedOut[AG]))
  {
   done[AG] = FALSE ;
   timedOut[AG] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: A&G event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[AO]) && !timedOut[AO])  ||
        (efTest(aoRunning) && timedOut[AO]))
  {
   done[AO] = FALSE ;
   timedOut[AO] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: AO event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[AOM]) && !timedOut[AOM])  ||
        (efTest(aomRunning) && timedOut[AOM]))
  {
   done[AOM] = FALSE ;
   timedOut[AOM] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: AOM event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[GP]) && !timedOut[GP])  ||
        (efTest(gpRunning) && timedOut[GP]))
  {
   done[GP] = FALSE ;
   timedOut[GP] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: GPOL event, monitoring -> initialising\n") ;
  } state initialising

  when ((!pvConnected(applState[M1]) && !timedOut[M1])  ||
        (efTest(m1Running) && timedOut[M1]))
  {
   done[M1] = FALSE ;
   timedOut[M1] = FALSE ;
   DBGMSG (DBG_MIN, "tcsSeqInit: PCS event, monitoring -> initialising\n") ;
  } state initialising

  when (tcsInitCar == menuCarstatesBUSY)
  {
   tcsState = INITIALISING ;
   pvPut(tcsState) ;
   dbReloading = 1 ;
   pvPut(dbReloading);
   initStat = tcsSeqInitActions(tcsPrefix) ;
   dbReloading = 0 ;
   pvPut(dbReloading);
   efSet(mcSeqInit) ;
   efSet(crSeqInit) ;
   efSet(ecSeqInit) ;
   efSet(m2SeqInit) ;
   efSet(agSeqInit) ;
   efSet(aoSeqInit) ;
   efSet(aomSeqInit) ;
   efSet(gpSeqInit) ;
/* Failure in tcsSeqInitActions? */
   if (initStat != 0)
   {
     tcsInitCarIval = menuCarstatesERROR;
     strcpy(tcsInitCarImss,"Error : INIT command failure");
     pvPut(tcsInitCarImss);
     pvPut(tcsInitCarIval);
   }
     
   DBGMSG (DBG_MIN, "tcsSeqInit: init event, monitoring -> init\n") ;
  } state init

/* Reboot sequence command issued : wait for IDLE, then REBOOT */
  when (tcsRebootCar == menuCarstatesBUSY)
  {} state WaitRebootIdle
 } 

 state WaitRebootIdle
 {
  when (tcsRebootCar == menuCarstatesIDLE)
  {
     DBGMSG (DBG_NONE, "tcsSeqInit: Reboot now...\n"); 
/*     reboot(BOOT_QUICK_AUTOBOOT); */
  } state init
 }

}
