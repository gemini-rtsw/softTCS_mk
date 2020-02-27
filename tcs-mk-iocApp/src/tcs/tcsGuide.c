/*
*   FILENAME
*   tcsGuide.c
*
*   FUNCTION NAME(S)
*   tcsDriveGsaoiOdgwSetup1 - setup ODGW window specific parameters
*   tcsDriveGsaoiOdgwSetup2 - setup ODGW common parameters
*   tcsGetRotCorr - fetch the total rotator correction
*   tcsGuide - Extracts tip/tilt from WFS data.
*   tcsGuideDump - print internal parameters to screen
*   tcsGuideGetOdgwGuideState - fetch guiding state of an ODGW
*   tcsGuideAnyOdgwFollowing - is any ODGW following  
*   tcsGuideGetOdgwFollowing - fetch following state of an ODGW 
*   tcsGuideGetOdgwFollowState - fetch following state of an ODGW for EPICS
*   tcsGuideGetOdgwParkStates - fetch park state of an ODGW for EPICS
*   tcsGuideGGFollowStates - compute and export follow state of generic guiders
*   tcsGuideInitOdgwPosns  - set startup positions for ODGW
*   tcsGuideMoveOdgw - move ODGW to a fixed position
*   tcsGuideOdgwInPosition - compute inPosition flag based on window center
*   tcsGuideParkOdgw - park the specified ODGW
*   tcsGuideSetOdgwFollowState - set follow state for ODGW
*   tcsGuideSetODGWCenter - set center of window in backing store
*   tcsRotatorGuide - compute latest rotator guide correction
*   tcsSetODGWCorner - set corner of specified ODGW
*   tcsSetODGWGuidePeriod  - set guide period for the specified ODGW
*   tcsSetODGWGuiding - set guiding flag for the specified ODGW
*   tcsSetupODGW - seup common parameters for ODGWs
*   tcsSetRotatorGuideMode - set rotator guiding on or off
*   tcsZeroRotCorr - set rotator guide correction back to zero
*/
/* *INDENT-OFF* */
/*
 * $Log $
 */
/* *INDENT-ON* */

#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <genSubRecord.h>
#include <recSup.h>
#include <string.h>
#include <epicsStdioRedirect.h>
#include "tcsConstants.h"
#include "tcsGuide.h"

static double Rotcorr ;  /* Rotator correction (rads) */
static int Rotguiding ;  /* Whether or not we are guiding the rotator */

/* Data for ODGW */
#define CHIPXSIZE 2048
#define CHIPYSIZE 2048
#define DEADBAND 4

/* The following definitions assume the GSAOI defines its pixels starting
 * from 1. These are the initial values of the centers and lower left
 * corners of the ODGW windows
 */
static int setupODGWx[4] = {CHIPXSIZE - DEADBAND - 64 + 1, 
                            DEADBAND + 1, 
                            DEADBAND + 1 , 
                            CHIPXSIZE - DEADBAND - 64 + 1} ;  
static int setupODGWy[4] = {DEADBAND+1,
                            DEADBAND+1,
                            CHIPYSIZE - DEADBAND - 64 + 1,
                            CHIPYSIZE - DEADBAND - 64 + 1} ;         
static int setupODGWxc[4] = {CHIPXSIZE - DEADBAND -32 + 1, 
                             DEADBAND+1+32, 
                             DEADBAND+1+32,
                             CHIPXSIZE - DEADBAND -32 + 1};
static int setupODGWyc[4] = {DEADBAND+1+32,
                             DEADBAND+1+32,
                             CHIPYSIZE - DEADBAND -32 + 1,
                             CHIPYSIZE - DEADBAND -32 + 1};
static int parkODGWxc[4] = {CHIPXSIZE - DEADBAND -32 + 1, 
                            DEADBAND+1+32, 
                            DEADBAND+1+32,
                            CHIPXSIZE - DEADBAND -32 + 1};
static int parkODGWyc[4] = {DEADBAND+1+32,
                            DEADBAND+1+32,
                            CHIPYSIZE - DEADBAND -32 + 1,
                            CHIPYSIZE - DEADBAND -32 + 1};
/* These next two arrays have been setup to meet the requirements of the
* "ODGW Guide wrapper" document. They hold the values that will be sent
* to the GSAOI if follow mode is invoked, they are initialized to the
* default park positions
*/
static double storeODGWxc[4] = {CHIPXSIZE - DEADBAND -32 + 1, 
                                DEADBAND+1+32, 
                                DEADBAND+1+32,
                                CHIPXSIZE - DEADBAND -32 + 1};
static double storeODGWyc[4] = {DEADBAND+1+32,
                                DEADBAND+1+32,
                                CHIPYSIZE - DEADBAND -32 + 1,
                                CHIPYSIZE - DEADBAND -32 + 1};

static int setupODGWguiding[4] ;
static int setupODGWFollowing[4] ;
static int setupODGWParked[4] ;     /* Not parked at initialization */

static double setupODGWperiod[4]= {0.1, 0.1, 0.1, 0.1} ;  /* Assume  seconds */
static int setupWindowSize = 32 ;            /* Assume a 32 pixel window */
static int setupSaveIndex = 0;
static int setupGuiderIndex = 0;
static int setupDisplayIndex = 1;
static double setupDisplayRate = 1.0;   /* Assume 1 Hz */
 
/*+
 *   Function name:
 *   tcsDriveGsaoiOdgwSetup1
 *
 *   Purpose:
 *   Set the GSAOI ODGW window specific parameters
 *
 *   Description:
 *   This routine sets the window specific paramters (in particular
 *   the coordinates of the guide box) plus the other parameters
 *   needed by the dataODGW command in the GSAOI. The rather odd name
 *   of this routine is due to the fact it used to be part of
 *   the driver for the GSAOI setup command that needed 22 
 *   parameters. That command was removed and replaced by the
 *   seqODGW and dataODGW commands which take some but not all
 *   of the old setup parameters plus introduce some new ones.
 *
 *   Epics Outputs :
 *    vala => Window size e.g. 8x8 
 *    valb => Save permanent copy (Yes | No)
 *    valc => The X ordinate of the center of ODGW 1
 *    vald => The Y ordinate of the center of ODGW 1
 *    vale => The X ordinate of the center of ODGW 2
 *    valf => The Y ordinate of the center of ODGW 2
 *    valg => The X ordinate of the center of ODGW 3
 *    valh => The Y ordinate of the center of ODGW 3
 *    vali => The X ordinate of the center of ODGW 4
 *    valj => The Y ordinate of the center of ODGW 4
 *    valk => Guider output (MCAO | DUMMY)
 *    vall => Display ODGW (Yes | No )
 *    valm -> Rate to display ODGW (Hz)
 *    valn => Start directive to the dataODGW CAD record
 * 
 *   Invocation:
 *   tcsDriveGsaoiOdgwSetup1(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsDriveGsaoiOdgwSetup1 (struct genSubRecord *pgsub) 

{
    int window ;

    sprintf(pgsub->vala, "%dx%d", setupWindowSize, setupWindowSize);
/* It seems GSAOI expects 1 or 0 not YES or NO JL 02/12/10 */
    if (setupSaveIndex) {
      strcpy(pgsub->valb, "1");
    } else {
      strcpy(pgsub->valb, "0");
    }

/* Generate the values to be sent with the setup command using the most
 * recently stored demands from the kernel.
 */
    for (window = 0; window < 4; window++) {
      if (setupODGWFollowing[window] ) {
        tcsSetODGWCorner(window, storeODGWxc[window], storeODGWyc[window]);
      }
    }

    sprintf(pgsub->valc, "%d", setupODGWxc[0]);
    sprintf(pgsub->vald, "%d", setupODGWyc[0]);

    sprintf(pgsub->vale, "%d", setupODGWxc[1]);
    sprintf(pgsub->valf, "%d", setupODGWyc[1]);

    sprintf(pgsub->valg, "%d", setupODGWxc[2]);
    sprintf(pgsub->valh, "%d", setupODGWyc[2]);

    sprintf(pgsub->vali, "%d", setupODGWxc[3]);
    sprintf(pgsub->valj, "%d", setupODGWyc[3]);

    if (setupGuiderIndex) {
      strcpy(pgsub->valk, "Dummy");
    } else {
      strcpy(pgsub->valk, "MCAO");
    }

/* It seems GSAOI expects 1 or 0 not YES or NO JL 02/12/10 */
    if (setupDisplayIndex) {
      strcpy(pgsub->vall, "1");
    } else {
      strcpy(pgsub->vall, "0");
    }

    sprintf(pgsub->valm, "%f", setupDisplayRate);

    strcpy(pgsub->valn, "START");

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGetRotCorr
 *
 *   Purpose:
 *   Returns the current total rotator correction for use by the pointing 
 *   code.
 *
 *   Description:
 *   Simply return the currently stored correction.
 * 
 *   Invocation:
 *   corr = tcsGetRotCorr()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      (<)   rotcorr (double)   Correction to rotator angle (rads)
 * 
 *-
 */

double tcsGetRotCorr(void) 
{
  return Rotcorr ;
}

/*+
 *   Function name:
 *   tcsGuide
 *
 *   Purpose:
 *   Split the incoming guide signal into separate components
 *
 *   Description:
 *   The relevant elements from the array sent by the WFS are 
 *   extracted and output as individual values. For the OIWFS the
 *   output numbers are scaled. This is a provided as a work round
 *   in case there are issues with signs etc. from different OIWFS.
 *   It is hoped that both the tip and tilt scale factors can in fact
 *   be set to 1.0
 *   If the OIWFS is NICI then we must read the data direct from it 
 *   as its data isn't processed or passed through the OIWFS detector
 *   controller.
 *
 *   Epics Inputs :
 *    a => PWFS1 guide data
 *    b => PWFS2 guide data
 *    c => OIWFS guide data
 *    d => NICI guide data
 *    e => Z1 scale factor for OIWFS or NICI
 *    f => Z2 scale factor for OIWFS or NICI
 *    g => Name of OIWFS
 *    h => Sign factor
 *
 *   Epics Outputs :
 *    vala => PWFS1 "x" error
 *    valb => PWFS1 "y" error
 *    valc => PWFS2 "x" error
 *    vald => PWFS2 "y" error
 *    vale => OIWFS "x" error
 *    valf => OIWFS "y" error
 * 
 *   Invocation:
 *   tcsGuide(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsGuide (struct genSubRecord *pgsub) 

{
/* Fetch sign factor. This is +1 if the error signal is going to the same
*  probe the signal is being measured from or -1 otherwise
*/
    double sign = *(double *)pgsub->h;

    double oiZ1scale = *(double *)pgsub->e;
    double oiZ2scale = *(double *)pgsub->f;

    *(double *)pgsub->vala = sign * ((double *)pgsub->a)[2];
    *(double *)pgsub->valb = sign * ((double *)pgsub->a)[3];
    *(double *)pgsub->valc = sign * ((double *)pgsub->b)[2];
    *(double *)pgsub->vald = sign * ((double *)pgsub->b)[3];
    if (!strncmp(pgsub->g, "NICI", 4)) {
      *(double *)pgsub->vale = sign * ((double *)pgsub->d)[2]*oiZ1scale;
      *(double *)pgsub->valf = sign * ((double *)pgsub->d)[3]*oiZ2scale;
    } else {
      *(double *)pgsub->vale = sign * ((double *)pgsub->c)[2]*oiZ1scale;
      *(double *)pgsub->valf = sign * ((double *)pgsub->c)[3]*oiZ2scale;
    }
    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideDump
 *
 *   Purpose:
 *   Print internal data to screen for diagnostics
 *
 *   Description:
 *   Print internal data to screen
 * 
 *   Invocation:
 *   tcsGuidedump()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideDump(void) 
{
   int i ;

   for (i = 0; i < 4; i++) {
     printf("Window %d:  Following = %d\n", i+1, setupODGWFollowing[i]) ; 
     printf("Window %d:  Parked    = %d\n", i+1, setupODGWParked[i]) ; 
     printf("Window %d:  x center  = %d\n", i+1, setupODGWxc[i]) ; 
     printf("Window %d:  y center  = %d\n", i+1, setupODGWyc[i]) ; 
   }

}

/*+
 *   Function name:
 *   tcsGuideGetOdgwGuideState
 *
 *   Purpose:
 *   Fetch the ODGW guide state for export to EPICS
 *
 *   Description:
 *   Simply return the ODGW status flag to EPICS. If the demand 
 *   input is out of range then simply return 0 i.e. guiding
 *   is off. The flag returned here is the equivalent of the 
 *   following state for a mechanical guide probe.
 *
 *   Epics Inputs :
 *    a => No. of ODGW (0 - 3)
 *
 *   Epics Outputs :
 *    vala =>  Guiding/Following state (0 | 1)
 * 
 *   Invocation:
 *   tcsGuideGetOdgwGuideState(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *
 *-
 */

long tcsGuideGetOdgwGuideState (struct genSubRecord *pgsub) 

{
    long following ;
    long flag = *(long *)pgsub->a;

    if (flag < 0 || flag > 3) {
     following = 0;
    } else {
      following = setupODGWguiding[flag];
    }

    *(long *)pgsub->vala = following;

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideGetOdgwFollowState
 *
 *   Purpose:
 *   Fetch the ODGW follow state for export to EPICS
 *
 *   Description:
 *   Simply return the ODGW status flag to EPICS. If the demand 
 *   input is out of range then simply return 0 i.e.following 
 *   is off. The flag returned here is the equivalent of the 
 *   following state for a mechanical guide probe eve though
 *   for the ODGW there is no concept of following. It is 
 *   done this way as their is a hiigh level requirement that the
 *   interface to the ODGW is similar to the other guiders.
 *
 *   Epics Inputs :
 *    a => No. of ODGW (0 - 3)
 *
 *   Epics Outputs :
 *    vala =>  Following state (0 | 1)
 * 
 *   Invocation:
 *   tcsGuideGetOdgwFollowState(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *
 *-
 */

long tcsGuideGetOdgwFollowState (struct genSubRecord *pgsub) 

{
    long following ;
    long flag = *(long *)pgsub->a;

    if (flag < 0 || flag > 3) {
     following = 0;
    } else {
      following = setupODGWFollowing[flag];
    }

    *(long *)pgsub->vala = following;

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideGetOdgwParkStates
 *
 *   Purpose:
 *   Fetch the ODGW park states for export to EPICS
 *
 *   Description:
 *   This routine simply returns the park flags and text strings
 *   as called for in the "ODGW Guide Wrapper" document to EPICS. 
 *   Note that these park flags are no longer set explicitly by the 
 *   TCS but instead computed from the read back ODGW positions in routine 
 *   tcsGuideOdgwInPosition.
 *
 *   Epics Outputs :
 *    vala =>  Park state for ODGW1 (0 | 1)
 *    valb =>  Status string for ODGW1 (Parked | Not Parked)
 *    valc =>  Park state for ODGW2 (0 | 1)
 *    vald =>  Status string for ODGW2 (Parked | Not Parked)
 *    vale =>  Park state for ODGW3 (0 | 1)
 *    valf =>  Status string for ODGW3 (Parked | Not Parked)
 *    valg =>  Park state for ODGW4 (0 | 1)
 *    valh =>  Status string for ODGW4 (Parked | Not Parked)
 * 
 *   Invocation:
 *   tcsGuideGetOdgwParkStates(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsGuideGetOdgwParkStates (struct genSubRecord *pgsub) 

{

    *(long *)pgsub->vala = setupODGWParked[0];
    *(long *)pgsub->valc = setupODGWParked[1];
    *(long *)pgsub->vale = setupODGWParked[2];
    *(long *)pgsub->valg = setupODGWParked[3];

    if (setupODGWParked[0]) {
      strcpy(pgsub->valb, "Parked");
    } else {
      strcpy(pgsub->valb, "Not Parked");
    }

    if (setupODGWParked[1]) {
      strcpy(pgsub->vald, "Parked");
    } else {
      strcpy(pgsub->vald, "Not Parked");
    }

    if (setupODGWParked[2]) {
      strcpy(pgsub->valf, "Parked");
    } else {
      strcpy(pgsub->valf, "Not Parked");
    }

    if (setupODGWParked[3]) {
      strcpy(pgsub->valh, "Parked");
    } else {
      strcpy(pgsub->valh, "Not Parked");
    }

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideAnyOdgwFollowing
 *
 *   Purpose:
 *   Check if any ODGW is following
 *
 *   Description:
 *   Return true (= 1) if any of the ODGW are following. This is needed
 *   by the configuration checking to decide if new window parameters
 *   need to be sent to the GSAOI.
 *
 *   Invocation:
 *   following = tcsGuideAnyOdgwFollowing()
 *
 *   Function value:
 *   Following status flag
 * 
 *-
 */

int tcsGuideAnyOdgwFollowing (void) 

{
    int sum ;
    int i ;
    
    sum = 0;
    for (i = 0; i < 4; i++) {
      sum += setupODGWFollowing[i] ;
    }
    if (sum > 0) {
      return 1 ;
    } else {
      return 0 ;
    }
}

/*+
 *   Function name:
 *   tcsGuideGetOdgwFollowing
 *
 *   Purpose:
 *   Fetch the ODGW follow state 
 *
 *   Description:
 *   Simply return the ODGW following status. If the demand 
 *   input is out of range then simply return 0 i.e.following 
 *   is off. The flag returned here is the equivalent of the 
 *   following state for a mechanical guide probe even though
 *   for the ODGW there is no concept of following. It is 
 *   done this way as their is a high level requirement that the
 *   interface to the ODGW is similar to the other guiders.
 *
 *   Invocation:
 *   following = tcsGuideGetOdgwFollowing(window)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window     (int) Window number 0 - 3 
 *
 *   Function value:
 *   Following status flag
 * 
 *-
 */

int tcsGuideGetOdgwFollowing (int window) 

{
    if (window < 0 || window > 3) {
     return 0;
    } else {
      return setupODGWFollowing[window];
    }
}

/*+
 *   Function name:
 *   tcsGuideGGFollowStates
 *
 *   Purpose:
 *   Compute and export the following status of the generic guiders.
 *
 *   Description:
 *   A generic guider can be connected to any one of up to 7 
 *   physical guiders. This routine checks to see which if any
 *   physical guider is in use and then sets the generic guider
 *   following status to that of the current physical guider.
 *
 *   Epics Inputs :
 *    a => Index of physical guider for generic guider 1 (0 - 7) 
 *    b => Index of physical guider for generic guider 2 (0 - 7) 
 *    c => Index of physical guider for generic guider 3 (0 - 7) 
 *    d => Index of physical guider for generic guider 4 (0 - 7) 
 *    e => Following state of TTGS1
 *    f => Following state of TTGS2
 *    g => Following state of TTGS3
 *
 *   Epics Outputs :
 *    vala =>  Guiding/Following state of generic guider 1 (0 | 1)
 *    valb =>  Guiding/Following state of generic guider 2 (0 | 1)
 *    valc =>  Guiding/Following state of generic guider 3 (0 | 1)
 *    vald =>  Guiding/Following state of generic guider 4 (0 | 1)
 * 
 *   Invocation:
 *   tcsGuideGGFollowStates(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *
 *-
 */

long tcsGuideGGFollowStates (struct genSubRecord *pgsub) 

{
    long gg1Follow = 0;
    long gg2Follow = 0;
    long gg3Follow = 0;
    long gg4Follow = 0;
    long ngsFollow[3] ;

    long gg1PhyIndex = *(long *)pgsub->a;
    long gg2PhyIndex = *(long *)pgsub->b;
    long gg3PhyIndex = *(long *)pgsub->c;
    long gg4PhyIndex = *(long *)pgsub->d;
    ngsFollow[0]     = *(long *)pgsub->e;
    ngsFollow[1]     = *(long *)pgsub->f;
    ngsFollow[2]     = *(long *)pgsub->g;

    if (gg1PhyIndex > 3) {
      gg1Follow = setupODGWFollowing[gg1PhyIndex-4];
    } else if (gg1PhyIndex > 0) {
      gg1Follow = ngsFollow[gg1PhyIndex-1];
    }

    if (gg2PhyIndex > 3) {
      gg2Follow = setupODGWFollowing[gg2PhyIndex-4];
    } else if (gg2PhyIndex > 0) {
      gg2Follow = ngsFollow[gg2PhyIndex-1];
    }

    if (gg3PhyIndex > 3) {
      gg3Follow = setupODGWFollowing[gg3PhyIndex-4];
    } else if (gg3PhyIndex > 0) {
      gg3Follow = ngsFollow[gg3PhyIndex-1];
    }

    if (gg4PhyIndex > 3) {
      gg4Follow = setupODGWFollowing[gg4PhyIndex-4];
    } else if (gg4PhyIndex > 0) {
      gg4Follow = ngsFollow[gg4PhyIndex-1];
    }

    *(long *)pgsub->vala = gg1Follow ;
    *(long *)pgsub->valb = gg2Follow ;
    *(long *)pgsub->valc = gg3Follow ;
    *(long *)pgsub->vald = gg4Follow ;

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideOdgwInPosition
 *
 *   Purpose:
 *   Computes the in position and parked status of a specified ODGW
 *
 *   Description:
 *   Compare the values of the guide window center read from the
 *   GSAOI with the values sent by the TCS. if the values are
 *   the same, then set in position to true ( = 1) if not set it
 *   to false ( = 0). If the positions correspond to the park positions
 *   then set the parked state to true (= 1) or false (= 0).
 *
 *   Epics Inputs :
 *    a => Number of ODGW (1 - 4) 
 *    b => x coordinate of center as read from GSAOI
 *    c => y coordinate of center as read from GSAOI
 *
 *   Epics Outputs :
 *    vala =>  In position state of ODGW 
 * 
 *   Invocation:
 *   tcsGuideOdgwInPosition(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *
 *-
 */

long tcsGuideOdgwInPosition (struct genSubRecord *pgsub) 

{
    long inPosition = 0;

    long window = *(long *)pgsub->a - 1;
    double xcg  = *(double *)pgsub->b ;
    double ycg  = *(double *)pgsub->c;

/* Compare value sent by TCS with value read back from GSAOI. 
*  Note that although the values are read in as doubles,
*  there is no fractional part. 
*/
    if (window > -1 && window < 4) {
      if (((int)xcg == setupODGWxc[window]) && 
          ((int)ycg == setupODGWyc[window])) {
        inPosition = 1;
      } else {
        inPosition = 0;
      }

      if (((int)xcg == parkODGWxc[window]) && 
          ((int)ycg == parkODGWyc[window])) {
         setupODGWParked[window] = 1;
      } else {
         setupODGWParked[window] = 0;
      }
    }

    *(long *)pgsub->vala = inPosition ;

    return 0 ;  
}

/*+
 *   Function name:
 *   tcsGuideMoveOdgw
 *
 *   Purpose:
 *   Set the internal store so the specified ODGW can be moved
 *
 *   Description:
 *   This routine copies the demand positions into the setup arrays
 *   so that next time the window parameters are sent to the GSAOI
 *   they will contain the move positions rather than target positions.
 * 
 *   Invocation:
 *   tcsGuideParkOdgw(window, x, y)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)    Index of window 0 - 3
 *      (>)    x        (long)   Center x pixel of window 
 *      (>)    y        (long)   Center y pixel of window 
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideMoveOdgw(int window, long ix, long iy) 
{
   if (window < 0 || window > 3) return ;

   setupODGWxc[window] = ix;
   setupODGWyc[window] = iy;
}

/*+
 *   Function name:
 *   tcsGuideParkOdgw
 *
 *   Purpose:
 *   Configure the internal store so that the specified ODGW can be parked
 *
 *   Description:
 *   This routine copies the park positions into the setup arrays
 *   so that next time the window parameters are sent to the GSAOI
 *   they will contain the park positions rather than target positions.
 * 
 *   Invocation:
 *   tcsGuideParkOdgw(window)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)   Index of window 0 - 3
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideParkOdgw(int window) 
{
   if (window < 0 || window > 3) return ;

   setupODGWxc[window] = parkODGWxc[window];
   setupODGWyc[window] = parkODGWyc[window];
}

/*+
 *   Function name:
 *   tcsGuideSetOdgwFollowState
 *
 *   Purpose:
 *   Set the following flag of the specified ODGW
 *
 *   Description:
 *   Simply set the following flag to true (=1) or false (=0). 
 *   If the window number is invalid do nothing.
 * 
 *   Invocation:
 *   tcsGuideSetOdgwFollowState(window, guiding)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)   Index of window 0 - 3
 *      (>)    following  (int)   Following state 0 or 1
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideSetOdgwFollowState(int window, int following) 
{
   if (window < 0 || window > 3) return ;

   if (following > 0) {
     setupODGWFollowing[window] = 1 ;
   } else {
     setupODGWFollowing[window] = 0 ;
   }

}

/*+
 *   Function name:
 *   tcsRotatorGuide
 *
 *   Purpose:
 *   Integrate the incoming rotator guide signal so it can be
 *   applied to the rotator demands generated by the kernel.
 *
 *   Description:
 *   Read the incoming data nad check that the data is new.
 *   If it is then multiply by the supplied gain and add it to
 *   the current correction.
 *
 *   Epics Inputs :
 *    a => Rotator guide data
 *    b => Integrator gain 
 *
 *   Epics Outputs :
 *    vala => Current rotator correction (degs) 
 *    valb => Total rotator guide correction (degs)
 * 
 *   Invocation:
 *   tcsRotatorGuide(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *
 *-
 */

long tcsRotatorGuide (struct genSubRecord *pgsub) 

{

  long status = 0 ;
  static double id = -1.0;
  double newid ;
  double newrotcorr ;       /* Newly received rotator correction (degs) */
  double rotgain ;          /* Gain to be applied to rotator demands */


  newid = ((double *)pgsub->a)[1];
  newrotcorr = ((double *)pgsub->a)[2];
  rotgain = *(double *)pgsub->b ;

/* Check if new data has arrived and we are rotator guiding. If so, 
 * integrate the new data with teh current correction
 */

  if (newid != id && Rotguiding) {
   
    Rotcorr += newrotcorr*rotgain*D2R;
    id = newid;

  }

  *(double *)pgsub->vala = newrotcorr;
  *(double *)pgsub->valb = Rotcorr * R2D ;

  return status ;

}


/*+
 *   Function name:
 *   tcsSetODGWCorner
 *
 *   Purpose:
 *   Set center of specified ODGW
 *
 *   Description:
 *   Sets the top left hand corner of the specified ODGW given the
 *   position of the target. When this routine is called it
 *   should already have been verified that the target does 
 *   indeed lie on the chip but we check anyway and set the 
 *   corner of the window to the top left hand corner of the chip. If the
 *   window index is out of range then the routine does nothing.
 *   The name of this routine is historical. Originally the TCS was
 *   required to send the lower left corner of the guide window. This
 *   was later changed to the center.
 * 
 *   Invocation:
 *   tcsSetODGWCorner(window, xc, yc)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)      Index of window 0 - 3
 *      (>)    xc       (double)   X ordinate of target (pixels)
 *      (>)    yc       (double)   Y ordinate of target (pixels)
 *
 *   Function value:
 *      None
 *-
 */

void tcsSetODGWCorner(int window, double xc, double yc) 
{

   int x0, y0 ;   /* ODGW corner */
   int x1, y1 ;   /* Upper right corner */

   if (window < 0 || window > 3) return ;

   x0 = (int)(xc + 0.5) - setupWindowSize / 2 + 1 ;
   if (x0 <= DEADBAND) x0 = DEADBAND + 1 ;

   y0 = (int)(yc + 0.5) - setupWindowSize / 2 + 1;
   if (y0 <= DEADBAND) y0 = DEADBAND + 1 ;

/* Now check that the ODGW is fully on the chip */
   x1 = x0 + setupWindowSize - 1;
   y1 = y0 + setupWindowSize - 1;
   if (x1 > CHIPXSIZE - DEADBAND) {
     x0 = CHIPXSIZE - DEADBAND - setupWindowSize + 1;
   }
   if (y1 > CHIPYSIZE - DEADBAND) {
     y0 = CHIPYSIZE - DEADBAND - setupWindowSize + 1;
   }
   
   setupODGWx[window] = x0 ;
   setupODGWy[window] = y0 ;
   setupODGWxc[window] = x0 + setupWindowSize/2 - 1;
   setupODGWyc[window] = y0 + setupWindowSize/2 - 1;
}

/*+
 *   Function name:
 *   tcsGuideSetODGWCenter
 *
 *   Purpose:
 *   Set center of specified ODGW
 *
 *   Description:
 *   This routine sets the center of the ODGW window in the backing store.
 * 
 *   Invocation:
 *   tcsGuideSetODGWCenter(window, xc, yc)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)      Index of window 0 - 3
 *      (>)    xc       (double)   X ordinate of target (pixels)
 *      (>)    yc       (double)   Y ordinate of target (pixels)
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideSetODGWCenter(int window, double xc, double yc) 
{
   if (window < 0 || window > 3) {
     printf("tcsGuideSetODGWCenter: window = %d is invalid\n", window) ;
   } else {
     storeODGWxc[window] = xc ;
     storeODGWyc[window] = yc ;
   }
}

/*+
 *   Function name:
 *   tcsGuideInitOdgwPosns
 *
 *   Purpose:
 *   Set default values for ODGW centers in internal storage
 *
 *   Description:
 *   This routine is called by the startup sequence program. It sets
 *   the default positions in the internal storage arrays to the current
 *   values of the ODGW centers as read from the GSAOI. In this way if a 
 *   single ODGW is parked for example then the demands to the other
 *   windows will be their current positions and not some arbitrary
 *   TCS defaults. This is necessary as you can't set an individual
 *   ODGW but must send data for all of them.
 * 
 *   Invocation:
 *   tcsGuideInitOdgwPosns(window, xc, yc)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)      Index of window 0 - 3
 *      (>)    xc       (double)   X ordinate of target (pixels)
 *      (>)    yc       (double)   Y ordinate of target (pixels)
 *
 *   Function value:
 *      None
 *-
 */

void tcsGuideInitOdgwPosns(int window, double xc, double yc) 
{
   storeODGWxc[window] = xc ;
   storeODGWyc[window] = yc ;
   tcsSetODGWCorner(window, xc, yc);

}

/*+
 *   Function name:
 *   tcsSetODGWGuidePeriod
 *
 *   Purpose:
 *   Set the guiding period of the specified ODGW
 *
 *   Description:
 *   Set the period between samples for the specified guide
 *   window. If the window number or the period are invalid
 *   then do nothing. 
 * 
 * 
 *   Invocation:
 *   tcsSetODGWGuidePeriod(window, period)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)   Index of window 0 - 3
 *      (>)    period   (double)   Guide period (secs)
 *
 *   Function value:
 *      None
 *-
 */

void tcsSetODGWGuidePeriod(int window, double period) 
{
   if (window < 0 || window > 3) return ;

   if (period >= 0.0) setupODGWperiod[window] = period; 

}

/*+
 *   Function name:
 *   tcsSetODGWGuiding
 *
 *   Purpose:
 *   Set the guiding flag of the specified ODGW
 *
 *   Description:
 *   Simply set the guiding flag to true (=1) or false (=0)
 *   If the window number is invalid do nothing.
 * 
 *   Invocation:
 *   tcsSetODGWGuiding(window, guiding)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    window   (int)   Index of window 0 - 3
 *      (>)    guiding  (int)   Guiding state 0 or 1
 *
 *   Function value:
 *      None
 *-
 */

void tcsSetODGWGuiding(int window, int guiding) 
{
   if (window < 0 || window > 3) return ;

   if (guiding > 0) {
     setupODGWguiding[window] = 1 ;
   } else {
     setupODGWguiding[window] = 0 ;
   }

}

/*+
 *   Function name:
 *   tcsSetupODGW
 *
 *   Purpose:
 *   Set up the common parameters for the ODGW
 *
 *   Description:
 *   Setup of the ODGW's for GSAOI involves a large number of 
 *   parameters. Separate routines are provided to set up the 
 *   window specific parameters and this routine stores the
 *   parameters that are common to all windows.
 * 
 *   Invocation:
 *   tcsSetupODGW(windowSize, saveIndex, guiderIndex, displayIndex, 
 *                displayRate)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    windowSize (int)     Size of window (pixels) 
 *      (>)    saveIndex  (int)     Whether to save a permanent copy (0 or 1)
 *      (>)    guiderIndex  (int)   Index to select guider output 
 *      (>)    displayIndex (int)   Whether to display data or not
 *      (>)    displayRate  (double) Display rate (Hz) 
 *
 *   Function value:
 *      None
 *-
 */

void tcsSetupODGW(int windowSize, int saveIndex, int guiderIndex, 
		  int displayIndex, double displayRate) 
{

  int i ;

  setupWindowSize = windowSize ;
  setupSaveIndex  = saveIndex ;
  setupGuiderIndex = guiderIndex ;
  setupDisplayIndex = displayIndex ;
  setupDisplayRate = displayRate ;

/* In case the windowSize has been changed, reset the window corners */

  for (i = 0; i < 4; i++ ) {
    tcsSetODGWCorner(i, (double)setupODGWxc[i], (double)setupODGWyc[i]);
  }

}

/*+
 *   Function name:
 *   tcsSetRotatorGuideMode
 *
 *   Purpose:
 *   Sets the flag that says whether incoming rotator guide signals
 *   should be used or ignored. This routiee is expected to be called
 *   from the rotGuideMode command.
 *
 *   Description:
 *   Assume any value > zero means turn guiding on and any value
 *   <= 0 means turn it off.
 * 
 *   Invocation:
 *   tcsSetRotatorGuideMode(state)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *     (>)  state  (int)   Requested quide state
 *
 *   Function value:
 *     None
 * 
 *-
 */

void tcsSetRotatorGuideMode(int state) 
{
  if (state > 0) {
    Rotguiding = 1;
  } else {
    Rotguiding = 0;
  }
}

/*+
 *   Function name:
 *   tcsZeroRotCorr
 *
 *   Purpose:
 *   Sets the accumulated rotator guider correction back to zero. This is
 *   expected to be called from the zeroRotGuide command.
 *
 *   Description:
 *   Simply set the internal rottcorr variable back to zero.
 * 
 *   Invocation:
 *   tcsZeroRotCorr()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsZeroRotCorr(void) 
{
  Rotcorr = 0.0;
}

epicsRegisterFunction(tcsGuideGGFollowStates);
epicsRegisterFunction(tcsGuideGetOdgwParkStates);
epicsRegisterFunction(tcsDriveGsaoiOdgwSetup1);
epicsRegisterFunction(tcsGuideOdgwInPosition);
epicsRegisterFunction(tcsRotatorGuide);
epicsRegisterFunction(tcsGuideGetOdgwFollowState);
epicsRegisterFunction(tcsGuide);
