/*
*   FILENAME
*   tcsProbeLib.c
*
*   FUNCTION NAME(S)
*   tcsProbeAom2Tcs        - transform AOM coords to TCS coords
*   tcsProbeCheckRadii     - check user's limits against physical limits
*   tcsProbeDefaultTcs2Odgw - generate some default transformation coefficeints
*   tcsProbeDump           - print details of internal variables
*   tcsProbeGetAOConfig    - fetch state of AO fold
*   tcsProbeGetAoFold      - fetch state of AO fold
*   tcsProbeGetChop        - fetch chop state that a probe is following
*   tcsProbeGetDefaultFlag - get useDefaults falg for a probe
*   tcsProbeGetDefaults    - fetch probe defaults in X, Y and Z
*   tcsProbeGetFollowFlag  - fetch probe follow status
*   tcsProbeGetLimits      - fetch all user probe limits
*   tcsProbeGetRTLimits    - fetch probe rotary table limits
*   tcsProbeGetRTPosns     - fetch probe rotary table angles
*   tcsProbeGetTcs2Odgw    - fetch TCS to ODGW transformation parameters
*   tcsProbeGetTelescope   - return telescope index
*   tcsProbeGetZoff        - fetch z offset for a probe
*   tcsProbeInit           - initialise the semaphore used to guard the data
*   tcsProbeOdgwCoeffs     - export ODGW transformation coeffs to EPICS
*   tcsProbeOdgw2Tcs       - transform ODGW coords to TCS coords
*   tcsProbeOiwfs2Tcs      - transform OIWFS coords to TCS coords
*   tcsProbeRTPosns        - gensub routine to set rotary table posns
*   tcsProbeSetAOConfig    - save AO Configuration state 
*   tcsProbeSetAoFold      - save state of AO fold
*   tcsProbeSetCoeffs      - set transformation coefficients
*   tcsProbeSetDefaultFlag - set useDefaults flag for a probe
*   tcsProbeSetDefaults    - set probe defaults in X, Y and Z
*   tcsProbeSetFollowFlag  - set flag to say if probe is following
*   tcsProbeSetOffsets     - set focus and probe offsets
*   tcsProbeSetRadii       - set physical limits for a probe
*   tcsProbeSetRLimits     - set radial limits for a probe
*   tcsProbeSetRTLimits    - set rotary table limits for P1 and P2
*   tcsProbeSetRTPosns     - set probe rotary table angles in store
*   tcsProbeSetRZLimits    - set radial and Z limits for a probe
*   tcsProbeSetTcs2Odgw    - set the TCS to ODGW transformation parameters
*   tcsProbeSetTelescope   - set index for site
*   tcsProbeSetXYZLimits   - set X Y and Z limits for a probe
*   tcsProbeSetZoff        - set z offset for a probe
*   tcsProbeStoreOdgwCoeffs - store ODGW transform coefficients.
*   tcsProbeTcs2Aom        - transform TCS coords to AOM frame
*   tcsProbeTcs2Oiwfs      - transform TCS coordinates to OIWFS frame 
*   tcsProbeTcs2Odgw       - transform TCS coords to GSAOI frame
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsProbeLib.c,v $
 * Revision 1.26  2013/07/02 13:57:36  gemvx
 * REL-1302: Fixed bug where TCS was saving M1 figure to the wrong file if AO fold position was park-pos instead of OUT.
 *
 * Revision 1.25  2013/05/14 08:36:54  cjm
 * Fix multiple taking of semaphore
 *
 * Revision 1.24  2013/05/05 12:12:06  gemvx
 * ----------------------------------------------------------------------
 * Committing in .
 * Modified Files: All related to REL-466.
 * 	capfast/tcs/tcsReadAg.sch: Added gensub to set the PWFS2 RT limits
 * 	according to the RT prefered orientation.
 * 	capfast/tcs/tcsReadWfs.sch: Added p2RTorient record.
 * 	src/tcs/tcsProbeLib.c: Added setRTCurrentLimits routine.
 * ----------------------------------------------------------------------
 *
 * Revision 1.23  2011/04/19 18:09:00  gemvx
 * Updated ODGW transformation coefficients.
 *
 * Revision 1.22  2010/11/29 14:10:54  cjm
 * Pass GSAOI focus offsets to AOM not M2
 *
 * Revision 1.21  2010/08/26 09:55:12  cjm
 * Make port checking for GSAOi case independent
 *
 * Revision 1.20  2010/06/08 15:41:29  cjm
 * Changes for 3 GSAOI port transform coeffs. Array tcs2odgw now 3 dims. Add gensub routines tcsModifyOdgwCoeffs, tcsFindGsaoiPort. Added tcsGetGsaoiPort().
 *
 * Revision 1.19  2010/06/04 09:54:42  cjm
 * Output the usingGSAOI flag
 *
 * Revision 1.18  2010/06/03 15:40:49  cjm
 * Add support for GSAOI filter offsets
 *
 * Revision 1.17  2010/06/01 08:07:54  cjm
 * Add flag to say whether GSAOI is in use or not
 *
 * Revision 1.16  2010/04/13 16:06:24  cjm
 * Update the default GSAOI image scale
 *
 * Revision 1.15  2010/02/22 15:23:04  gemvx
 * Last coefficient for ODGW was not been copied to coefficients array.
 *
 * Revision 1.14  2010/01/20 15:52:34  cjm
 * Fix default ODGW transformation and ensure values in config file over ride them
 *
 * Revision 1.13  2009/12/01 13:39:33  cjm
 * Add routines for setting, getting and manipulating ODGW coefficients
 *
 * Revision 1.12  2008/05/01 15:19:25  cjm
 * Routines to set and get rotary table limits, posns etc.
 *
 * Revision 1.11  2007/12/18 10:15:16  cjm
 * Many changes to handle new guiders
 *
 * Revision 1.10  2006/11/24 10:28:01  cjm
 * New routines Set and Get AOConfig
 *
 * Revision 1.9  2004/07/12 10:39:52  cjm
 * Output AO fold position
 *
 * Revision 1.8  2002/11/18 20:37:22  cjm
 * Add code to support instruments that are not confocal with their OIWFS
 *
 * Revision 1.7  2001/10/05 09:14:45  cjm
 * add routines to transform oiwfs coordinates
 *
 * Revision 1.6  2001/05/06 00:01:20  cjm
 * Include stdio.h
 *
 * Revision 1.5  2000/11/23 16:17:40  cjm
 * add routines to get and set AO fold position
 *
 * Revision 1.4  2000/08/18 16:06:30  cjm
 * Update library to accommodate Altair probe
 *
 * Revision 1.3  2000/03/25 01:06:06  cjm
 * Add routine tcsProbeDump to show internal data of the probe library
 *
 * Revision 1.2  1999/03/22 22:06:07  dlt
 * Add missing strings.h and remove stuff about rcsid - it doesn't work on the power PC
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.5  1998/10/26 13:20:11  tcs
 * Add code to set and get focus offsets for probes
 *
 * Revision 1.4  1998/09/05 03:28:02  tcs
 * Add new routines SetRaddii, CheckRadii and SetRLimits
 *
 * Revision 1.3  1997/11/13 13:25:19  tcs
 * Revised guide star scheme
 *
 * Revision 1.2  1997/06/02 09:58:27  tcs
 * Add slew CAD
 *
 * Revision 1.1  1997/02/10 17:10:54  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1997/01/20 14:36:36  cjm
 * Correct typo that generated wrong ymin for pwfs2 and oiwfs
 *
 * Revision 1.3  1996/12/12 15:53:32  cjm
 * Updates in preparation for better probe handling
 *
 * Revision 1.2  1996/11/08 10:05:31  cjm
 * Include math.h
 *
 * Revision 1.1  1996/10/31 09:16:10  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#include <epicsMutex.h>
#include <math.h>
#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>


#include "slalib.h"
#include "slamac.h"
#include "tcsConstants.h"
#include "tcsProbeLib.h"
#include "tcsDecode.h"
#include "genSubRecord.h"
#include "tcsOptics.h"
#include "tcsPointing.h"

epicsMutexId tcsProbeSemId; /*Mutex semaphore to guard data */

static int init = FALSE ;       /* Flag to indicate initialisation */

struct PROBELIMIT {
       LIMITTYPE limitType ;  /* Type of limit X,Y or Radial */
       double xmin ;          /* Minimum X value (mm) */
       double xmax ;          /* Maximum X value (mm) */
       double ymin ;          /* Minimum Y value (mm) */
       double ymax ;          /* Maximum Y value (mm) */
       double zmin ;          /* Minimum Z value (mm) */
       double zmax ;          /* Maximum Z value (mm) */
       double rmin ;          /* Minimum R value (mm) */
       double rmax ;          /* Maximum R value (mm) */
       double xdef ;          /* X default value (mm) */
       double ydef ;          /* Y default value (mm) */
       double zdef ;          /* Z default value (mm) */
       } ;

static struct PROBELIMIT pwfs1Limit ;
static struct PROBELIMIT pwfs2Limit ;
static struct PROBELIMIT oiwfsLimit ;
static struct PROBELIMIT aowfsLimit ;
static struct PROBELIMIT aomLimit[3];
static struct PROBELIMIT odgwLimit[4];

/* Physical radial limits of PWFS1 and PWFS2 */

static double pwfs1Rmin = 0.0 ;
static double pwfs1Rmax = 300.0;
static double pwfs2Rmin = 0.0 ;
static double pwfs2Rmax = 300.0 ;

/* Limits pf probe rotator table motion (degs) */
static double pwfs1RTmin = -200.0 ;
static double pwfs1RTmax = 200.0 ;
static double pwfs2RTmin = -200.0 ;
static double pwfs2RTmax = 200.0 ;

/* Follow status and current rotary table angle. These are only here as
*  we ran out of links on the EPICS records. This would have meant a
*  major restructuring when adding the code for computing probe time
*  to limits.
*/
static long pwfs1FollowStat = 0;
static long pwfs2FollowStat = 0;
static double pwfs1RTPosn ;
static double pwfs2RTPosn ;             /* Rotary table angle (degs) */

/* Total offsets from nominal probe positions */
static double pwfs1Zoff = 0.0;
static double pwfs2Zoff = 0.0;
static double oiwfsZoff = 0.0;
static double aowfsZoff = 0.0;

/* Focus offset as specified by instrument */
static double oiwfsInsZoff = 0.0 ;

/* Focus offset as specified by User */
static double oiwfsUserZoff = 0.0;

/* Position of AO fold. On startup set to 0 ( = OUT) */
static int aoFoldPosition = 0 ;
static int configuredForAO = 0;

/* Transformation coefficents for OIWFS coordinates */
static double tcs2oiwfs[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
static double oiwfs2tcs[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;

/* Transformation coefficients for AOM guiders */
static double tcs2aom[3][6] = {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                               {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                               {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};
static double aom2tcs[3][6] = {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                               {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                               {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}};

/* GSAOI port handling */
static int gsaoiport[3] = {1,3,5}; /* GSAOI can be on Port 1, 3 or 5 */
static int gsaoiCurrentPort;       /* Current port number of GSAOI */

/* Transformation coefficients for the ODGW guiders. 
   3 ports x 4 windows x 6 coeffs             */
static double tcs2odgw[3][4][6] = {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
                                   {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
                                   {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}};
static double odgw2tcs[3][4][6] = {{{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
                                   {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}},
                                   {{0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0},
                                   {0.0, 1.0, 0.0, 0.0, 0.0, 1.0}}};

/* Not perhaps the obvious place but here we store whether we are
 * configured for Gemini North or South. It is put here as a lot
 * the differences between the two sites involve probe control.
 * Gemini North => 0
 * Gemini South => 1
 */
static int telIndex = 0;
                               
/* Flag to say if GSAOI is in use */
static long usingGSAOI = 0;

/*+
 *   Function name:
 *   tcsProbeDefaultTcs2Odgw
 *
 *   Purpose:
 *   Generate some default transformation coefficients for the ODGW
 *
 *   Description:
 *   This routine generates some default TCS -> ODGW transformation
 *   coefficients (and their inverse) based on the expected 
 *   geometry of the detector. These can be used until a proper
 *   calibration is done at which time the coefficients can be
 *   stored in the configuration files and set via the routine
 *   tcsProbeSetTcs2Odgw.
 *
 *   Invocation:
 *   tcsProbeDefaultTcs2Odgw()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   None
 * 
 *   Deficiences:
 *   Everything is currently hard coded but as these defaults should
 *   only be in use temporarily this is probably not a problem.
 *-
 */

void tcsProbeDefaultTcs2Odgw(void)
{
   double pixsize = 18.0 ;    /* Pixels are 18 microns */ 
   double gap    = 3000.0 ;   /* Gap between detectors is 3000 microns */

   double delta ;             /* Half gap in pixels */
   double X0 ;                /* Offset of TCS from array origin (pixels) */
   double Y0 ;

   int k, j, i ;                    /* loop indices */
   int jstat;                 /* Status of slaInvf */

   double origins[4][2] ;     /* Array of origins of detectors (pixels) */
   double imagescale ;        /* Transform TCS mm to GSAOI pixels */

/* For each detector set up the origin relative to the array centre.
 * Note we assume the origin of each detector is the bottom left hand
 * corner with y increasing upwards. This may not be correct as the
 * GSAOI documentation is ambiguous sometimes referring to the y origin
 * as being at the top with y increasing downwards.
 */
   delta = gap / (pixsize * 2.0) ;

   origins[0][0] = delta ;
   origins[0][1] = -delta - 2048.0 ;
   origins[1][0] = -delta - 2048.0 ;
   origins[1][1] = -delta - 2048.0 ;
   origins[2][0] = -delta - 2048.0 ;
   origins[2][1] = delta ;
   origins[3][0] = delta ;
   origins[3][1] = delta ;

/* Now allow for the offset between the array origin and the TCS origin.
 * Y is again assumed to increase downwards.
 */
   X0 = 0.0;
   Y0 = 0.0;

   for (i = 0; i < 4; i++) {
     origins[i][0] -= X0;
     origins[i][1] -= Y0;
   }

/* Image scale is set as follows:
 * GSAOI pixel size is 18 microns
 * GSAOI image scale claimed as 0.02 arcsec/pixel (= 1.111 arcsec/mm)
 * TCS image scale = 1.611 arcsecs/pixel
 * 
 * so, tcs(mm) * 1.611/0.02 gives GSAOI pixels.
 */
 imagescale = 1.611/0.02 ;
 
/* Generate the transforms. We currently assume the axes are aligned
 * i.e. no rotation. flips etc. BUT GSAOI x axis increase to the right
 * whereas TCS x axis increase to the left hence the sign change in the
 * xscaling (tcs2odgw[i][1])
 *
 * Three GSAOI ports with port index = 0, 1, 2
 */
     for (i = 0; i < 4; i++) {
       tcs2odgw[0][i][0] = -origins[i][0] ;
       tcs2odgw[0][i][1] = -imagescale ;
       tcs2odgw[0][i][2] = 0.0 ;
       tcs2odgw[0][i][3] = -origins[i][1] ;
       tcs2odgw[0][i][4] = 0.0 ;
       tcs2odgw[0][i][5] = imagescale ;
       
       tcs2odgw[1][i][0] = -origins[i][0] ;
       tcs2odgw[1][i][1] = 0.0 ;
       tcs2odgw[1][i][2] = -imagescale ;
       tcs2odgw[1][i][3] = -origins[i][1] ;
       tcs2odgw[1][i][4] = -imagescale ;
       tcs2odgw[1][i][5] = 0.0 ;
       
       tcs2odgw[2][i][0] = -origins[i][0] ;
       tcs2odgw[2][i][1] = 0.0 ;
       tcs2odgw[2][i][2] = imagescale ;
       tcs2odgw[2][i][3] = -origins[i][1] ;
       tcs2odgw[2][i][4] = -imagescale ;
       tcs2odgw[2][i][5] = 0.0 ;      
     }

/*
  for (j = 0; j < 3; j++) {
     for (i = 0; i < 4; i++) {
         for (k = 0; k < 6; k++) {
           printf("tcsProbeDefaultTcs2Odgw: tcs2odgw[%1d][%1d][%1d] = %8.4f\n",
                   j, i, k, tcs2odgw[j][i][k]);
         }
     }
   }
*/

/* Generate the inverse tranformation */
   for (j = 0; j < 3; j++) {   /* Three possible GSAOI ports */
     for (i = 0; i < 4; i++) {
       slaInvf(tcs2odgw[j][i], odgw2tcs[j][i], &jstat);
/* If the inverse failed - it shouldn't - just put out a message.
 * the array tcs2odgw will be the identity matrix.
 */
       if (jstat != 0) {
          printf ("tcsProbeDefaultTcs2Odgw: Port %d Window %d - Failed to invert matrix\n",
                   gsaoiport[j], i);
          for (k = 0; k < 6; k++)
            printf ("tcs2odgw[%1d][%1d][%1d] = %8.4f\n",
                     j, i, k, tcs2odgw[j][i][k]);
          }
     }
   }

}


/*+
 *   Function name:
 *   tcsProbeDump
 *
 *   Purpose:
 *   Print out details of probeLib internal variables
 *
 *   Description:
 *   This routine simply fetches the data for the specified probe and
 *   writes it to the screen for diagnostic purposes.
 *
 *   Invocation:
 *   tcsProbeDump(probe)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   probe   (int)  Probe number 0, 1 or 2
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsProbeDump (int probe)
{
 double xdef, ydef, zdef ;              /* Default position of probe (mm) */
 LIMITTYPE limType ;                    /* Type of limit */
 double xmin, xmax ;                    /* X probe limits (mm) */
 double ymin, ymax ;                    /* Y probe limits (mm) */
 double zmin, zmax ;                    /* Z probe limits (mm) */
 double rmin, rmax ;                    /* Radial probe limits (mm) */
 int j;                                 /* Loop index */

 if (probe > 10 || probe < 0) {
   printf ("Probe number must be in range 0 to 10\n") ;
 } else {
   tcsProbeGetDefaults(probe, &xdef, &ydef, &zdef) ;
   tcsProbeGetLimits (probe, &limType, &xmin, &xmax, &ymin, &ymax, &zmin, 
                      &zmax, &rmin, &rmax) ;
   if (probe == 0) {
    printf ("\n            PWFS1\n\n") ;
    printf("Physical radial limits:   %.2f %.2f\n", pwfs1Rmin, pwfs1Rmax);
    printf("Rotary table limits   :   %.2f %.2f\n", pwfs1RTmin, pwfs1RTmax);
   } else if (probe == 1) {
    printf ("\n            PWFS2\n\n") ;
    printf("Physical radial limits:   %.2f %.2f\n", pwfs2Rmin, pwfs2Rmax);
    printf("Rotary table limits   :   %.2f %.2f\n", pwfs1RTmin, pwfs1RTmax);
   } else if (probe == 2) {
    printf ("\n            OIWFS\n\n") ;
   } else if (probe == 3) {
    printf ("\n            AOWFS (Altair)\n\n") ;
   } else if (probe > 3 && probe < 7) {
    printf ("\n            TTGS%d (Canopus)\n\n", probe-3);
   } else {
    printf ("\n            ODGW%d (GSAOI)\n\n", probe-6);
   }
   if (probe < 4) {
     printf ("Current default demands : %.2f %.2f %.2f\n", xdef, ydef, zdef);
   } else {
     printf ("Current default demands : %.2f %.2f \n", xdef, ydef);
   }
   if (probe == 4 || probe == 5) {
     printf("R(min), R(max):           %.2f %.2f\n", rmin, rmax) ;
     printf("X(min), X(max):           %.2f %.2f\n", xmin, xmax) ;
   } else {
     if (limType == XY) { 
       printf("X(min), X(max):           %.2f %.2f\n", xmin, xmax) ;
       printf("Y(min), Y(max):           %.2f %.2f\n", ymin, ymax) ;
     } else {
       printf("R(min), R(max):           %.2f %.2f\n", rmin, rmax) ;
     }
   }
   if (probe < 4) {
     printf("Z(min), Z(max):           %.2f %.2f\n", zmin, zmax) ;
   }

   if (probe == 2) {
     printf ("Offset of WFS and Instrument focal planes %.2f\n", oiwfsInsZoff);
     printf ("Total probe focus offset %.2f\n", oiwfsZoff);
     if (limType == XY ) {
       printf ("Coordinate transformation coefficients for OIWFS\n");
       printf ("%f %f %f %f %f %f\n", tcs2oiwfs[0], tcs2oiwfs[1], tcs2oiwfs[2],
               tcs2oiwfs[3], tcs2oiwfs[4], tcs2oiwfs[5]) ;
     }
   }
   if (probe >= 4 && probe <= 6) {
     printf ("Coordinate transformation coefficients for TTGS %d\n", probe-3);
     printf ("%f %f %f %f %f %f\n", tcs2aom[probe-4][0], tcs2aom[probe-4][1], 
	     tcs2aom[probe-4][2],   tcs2aom[probe-4][3], tcs2aom[probe-4][4],
	     tcs2aom[probe-4][5]) ;
   }
   if (probe >= 7 && probe <= 10) {
     if (usingGSAOI) {
       printf("Currently configured for GSAOI\n");
     } else {
       printf("Not currently configured for GSAOI\n");
     }
     printf ("Coordinate transformation coefficients for ODGW %d\n", probe-6);

     for (j = 0; j < 3; j++)   /* Three possible GSAOI ports */
     {
       printf (" TCS -> GSAOI\n");
       printf ("Coordinate transformation coefficients for ODGW %d, Port %d\n", probe-6, gsaoiport[j]);
       printf ("%f + %f  * xt + %f * yt\n", tcs2odgw[j][probe-7][0], 
                tcs2odgw[j][probe-7][1], tcs2odgw[j][probe-7][2]) ;
       printf ("%f + %f * xt + %f * yt\n", tcs2odgw[j][probe-7][3], 
                tcs2odgw[j][probe-7][4], tcs2odgw[j][probe-7][5]) ;
     }
   }
   
 } 
}


/*+
 *   Function name:
 *   tcsProbeGetGSAOIConfig
 *
 *   Purpose:
 *   Fetch state of GSAOI configuration.
 *
 *   Description:
 *   This routine simply returns the state of the GSAOI configuration which 
 *   has been stored previously by the routine tcsProbeSetOffsets. The state 
 *   is either 1 which means it is configured or 0 which means it is not.
 *
 *   Invocation:
 *   state = tcsProbeGetGSAOIConfig() 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  state  (long)  Either 1 ( = configured) or 0 (= not configured) 
 * 
 *-
 */

long tcsProbeGetGSAOIConfig(void)
{

  return usingGSAOI ;

}
/*+
 *   Function name:
 *   tcsProbeGetAOConfig
 *
 *   Purpose:
 *   Fetch state of AO configuration.
 *
 *   Description:
 *   This routine simply returns the state of the AO configuration which 
 *   has been stored previously by the routine tcsProbeSetAOConfig. The state 
 *   is either 1 which means it is configured or 0 which means it is not.
 *
 *   Invocation:
 *   state = tcsProbeGetAOConfig() 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  state  (int)  Either 1 ( = configured) or 0 (= not configured) 
 * 
 *-
 */

int tcsProbeGetAOConfig(void)
{

  return configuredForAO ;

}

/*+
 *   Function name:
 *   tcsProbeGetAoFold
 *
 *   Purpose:
 *   Fetch state of AO fold i.e. whether it is deployed or not.
 *
 *   Description:
 *   This routine simply returns the state of the AO fold which has been
 *   stored previously by the routine tcsProbeSetAoFold. The state is
 *   1 which means it is in or deployed,  0 which means it is out, 
 *   2 which means it is moving or 3 if the state is unknown.
 *
 *   Invocation:
 *   state = tcsProbeGetAoFold() 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  state  (int)  1 ( = in), 0 (= out), moving (= 2) or unkown (= 3) 
 * 
 *-
 */

int tcsProbeGetAoFold(void)
{

  return aoFoldPosition ;

}


/*+
 *   Function name:
 *   tcsProbeGetTelescope
 *
 *   Purpose:
 *   Fetch telescope index.
 *
 *   Description:
 *   Simply return the telescope index. 0 indicates Gemini North and 1 
 *   is Gemini South.
 *
 *   Invocation:
 *   index = tcsProbeGetTelescope() 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  index  (int)  Either 1 ( = South) or 0 (= North) 
 * 
 *-
 */

int tcsProbeGetTelescope(void)
{

  return telIndex ;

}

/*+
 *   Function name:
 *   tcsProbeInit
 *
 *   Purpose:
 *   Initialise library of routines that access probe limits and defaults
 *
 *   Description:
 *   Simply create a mutex semaphore to guard the data used by the tcsProbe
 *   routines and set a flag to indicate this has been done. This routine
 *   need not be called explicitly as the routines in tcsProbeLib each
 *   check if this routine has been called and if not call it themselves.
 *   Added initialization of default transformation coefficients for the 
 *   ODGW.
 *
 *   Invocation:
 *   tcsProbeInit ()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   semMCreate     (semLib)      Create a mutex semaphore
 *
 *   Deficiencies:
 *   Does not check to see if mutex was created successfully
 *
 *-
 */

void tcsProbeInit (void)

{
  if (!init)
  {

   tcsProbeSemId = epicsMutexMustCreate(); /*Mutex semaphore to guard data */

   init = TRUE ;
   tcsProbeDefaultTcs2Odgw();
  }

}

/*+
 *   Function name:
 *   tcsProbeAom2Tcs
 *
 *   Purpose:
 *   Transforms AOM coordinates into the frame of the TCS 
 *
 *   Description:
 *   Use the stored transformation coefficients to convert AOM coords
 *   into the TCS frame
 *
 *   Invocation:
 *   tcsProbeAom2Tcs (gi, ox, oy, &tx, &ty)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    gi   (int)        ODGW index
 *      (>)    ox   (double)     OIWFS x coordinate
 *      (>)    oy   (double)     OIWFS y coordinate
 *      (<)    tx   (double *)   TCS x coordinate
 *      (<)    ty   (double *)   TCS y coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsProbeAom2Tcs (int gi, double ox, double oy, double *tx, double *ty)
{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
  if (gi > -1 && gi < 3) {
    epicsMutexLock(tcsProbeSemId);

    *tx = aom2tcs[gi][0] + aom2tcs[gi][1] * ox + aom2tcs[gi][2] * oy ;
    *ty = aom2tcs[gi][3] + aom2tcs[gi][4] * ox + aom2tcs[gi][5] * oy ;

    epicsMutexUnlock(tcsProbeSemId);
  } else {
    *tx = ox ;
    *ty = oy ;
  }
}

/*+
 *   Function name:
 *   tcsProbeOdgwCoeffs
 *
 *   Purpose:
 *   Export the ODGW transformation coefficients to EPICS.
 *
 *   Description:
 *   Fetch the ODGW window number then fetch the relevant coefficients
 *   and passs then to EPICS. An identity trasnform is provided if
 *   the window number is invalid.
 *
 *   Invocation:
 *   tcsProbeOdgwCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => GSAOI port number (1, 3 or 5)
 *   b => Window number (0 - 3)
 *
 *   Epics outputs:
 *   vala => Coefficient a
 *   valb => Coefficient b
 *   valc => Coefficient c
 *   vald => Coefficient d
 *   vale => Coefficient e
 *   valf => Coefficient f

 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeOdgwCoeffs (struct genSubRecord *pgsub)
{
  long port, winindex ;
  double coeffs[6];

  port = *(long *)pgsub->a ;
  winindex = *(long *)pgsub->b ;

  tcsProbeGetTcs2Odgw((int)port, (int)winindex, coeffs);

  *(double *)pgsub->vala = coeffs[0];
  *(double *)pgsub->valb = coeffs[1];
  *(double *)pgsub->valc = coeffs[2];
  *(double *)pgsub->vald = coeffs[3];
  *(double *)pgsub->vale = coeffs[4];
  *(double *)pgsub->valf = coeffs[5];

  return 0 ;

}

/*+
 *   Function name:
 *   tcsProbeOdgw2Tcs
 *
 *   Purpose:
 *   Transforms ODGW coordinates into the frame of the TCS 
 *
 *   Description:
 *   Use the stored transformation coefficients to convert ODGW coords
 *   into the TCS frame
 *
 *   Invocation:
 *   tcsProbeOdgw2Tcs (port, gi, ox, oy, &tx, &ty)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    port (int)        GSAOI port number (1,3 or 5)
 *      (>)    gi   (int)        ODGW index
 *      (>)    ox   (double)     OIWFS x coordinate
 *      (>)    oy   (double)     OIWFS y coordinate
 *      (<)    tx   (double *)   TCS x coordinate
 *      (<)    ty   (double *)   TCS y coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsProbeOdgw2Tcs (int port, int gi, double ox, double oy, double *tx, double *ty)
{
   int j ;              /* Loop index */
   int iport ;          /* GSAOI port index: 0=1, 1=3, 2=5 */

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

   iport = 0;           /* default port index */
   for (j = 0; j < 3; j++) if (port == gsaoiport[j]) iport = j;
   
/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
  if (gi > -1 && gi < 4) {
    epicsMutexLock(tcsProbeSemId);

    *tx = odgw2tcs[iport][gi][0] + odgw2tcs[iport][gi][1] * ox + odgw2tcs[iport][gi][2] * oy ;
    *ty = odgw2tcs[iport][gi][3] + odgw2tcs[iport][gi][4] * ox + odgw2tcs[iport][gi][5] * oy ;

    epicsMutexUnlock(tcsProbeSemId);
  } else {
    *tx = ox ;
    *ty = oy ;
  }
}

/*+
 *   Function name:
 *   tcsProbeOiwfs2Tcs
 *
 *   Purpose:
 *   Transforms OIWFS coordinates into the frame of the TCS 
 *
 *   Description:
 *   Use the stored transformation coefficients to convert OIWFS coords
 *   into the TCS frame
 *
 *   Invocation:
 *   tcsProbeOiwfs2Tcs (ox, oy, &tx, &ty)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    ox   (double)     OIWFS x coordinate
 *      (>)    oy   (double)     OIWFS y coordinate
 *      (<)    tx   (double *)   TCS x coordinate
 *      (<)    ty   (double *)   TCS y coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsProbeOiwfs2Tcs (double ox, double oy, double *tx, double *ty)
{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
  epicsMutexLock(tcsProbeSemId);

  *tx = oiwfs2tcs[0] + oiwfs2tcs[1] * ox + oiwfs2tcs[2] * oy ;
  *ty = oiwfs2tcs[3] + oiwfs2tcs[4] * ox + oiwfs2tcs[5] * oy ;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   tcsProbeRTPosns
 *
 *   Purpose:
 *   Store the current probe rotary table angles 
 *
 *   Description:
 *   Fetch the current rotary table angles from EPICS and store them for 
 *   later use.
 *
 *   Invocation:
 *   tcsProbeRTPosns(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => P1 rotary table position (degs) 
 *   b => P2 rotary table position (degs) 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeRTPosns (struct genSubRecord *pgsub)
{
  double p1RTPosn ;
  double p2RTPosn ;

  p1RTPosn = *(double *)pgsub->a ;
  p2RTPosn = *(double *)pgsub->b ;

  tcsProbeSetRTPosns(p1RTPosn, p2RTPosn);

  return 0 ;

}
/*+
 *   Function name:
 *   tcsProbeSetAOConfig
 *
 *   Purpose:
 *   Read in the state of the AO fold and store it internally
 *
 *   Description:
 *   This routine simply stores the AO configuration state as specified by
 *   the user via the configureForAO command. 
 *   In earlier versions of the TCS the AO configuration was deduced from
 *   the position of the AO fold. If it was in then AO was assumed in use.
 *   This caused problems in that the AO virtual guider is shared with P2.
 *   Until the AO fold was fully in this would mean that the P2 probe limits
 *   would be used. This could cause incorrect rejection of configurations
 *   during slews. 
 *   If not configured for AO then the inPosition, CAR and health status
 *   from the AO system are not used in the overall TCS equivalent status
 *
 *   Invocation:
 *   tcsProbeSetAOConfig(flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   flag  (int)   1 = Configured for AO
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsProbeSetAOConfig (int flag)
{

  if (flag > 0) {
    configuredForAO = 1;
  } else {
    configuredForAO = 0;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetAoFold
 *
 *   Purpose:
 *   Read in the state of the AO fold and store it internally
 *
 *   Description:
 *   The current position of the AO fold is read, verified and converted
 *   to an index. Note that the A&G name for the AO fold position is 
 *   either in/out or undefined. It is necessary to look at the CAR 
 *   record to tell if it is moving. Even this is not fully reliable as
 *   the CAR could get stuck on BUSY.
 *
 *   Invocation:
 *   tcsProbeSetAoFold(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => AO fold position as a string
 *   b => AO Fold CAR status
 *
 *   Epics outputs:
 *   vala => AO fold position 1 = in , 0 = out, 2 = moving , 3 = unknown
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeSetAoFold (struct genSubRecord *pgsub)
{
  int aoFoldPos = 0 ;
  char aoFold[10] ;
  char aoCar[10];

  tcsDcUc ((char *)pgsub->a, 10, aoFold) ;
  tcsDcUc ((char *)pgsub->b, 10, aoCar) ;

  if (!strncmp(aoFold, "IN", 2)) {
    aoFoldPos = 1 ;
  } else if (!strncmp(aoFold, "UNDEFINED", 9)) {
    if (!strncmp(aoCar, "MOVING", 6)) {
      aoFoldPos = 2 ;
    } else {
      aoFoldPos = 3 ;
    }
  } else if (!strncmp(aoFold, "OUT", 3)) {
    aoFoldPos = 0 ;
  } else {                                  /* Should never happen */
    aoFoldPos = 3 ;
  }

  aoFoldPosition = aoFoldPos ;

  *(long *)pgsub->vala = aoFoldPosition ;

  return 0 ;

}


/*+
 *   Function name:
 *   tcsProbeSetCoeffs
 *
 *   Purpose:
 *   Set OIWFS probe transformation coefficients
 *
 *   Description:
 *   The coefficients that define the transformation between the TCS frame
 *   of reference and the OIWFS frame of reference are stored for use by
 *   other software components. At the same time, the inverse transformation
 *   is also computed and saved.
 *
 *   Invocation:
 *   tcsProbeSetCoeffs(coeffs)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  coeffs[6]   (double)  array of transformation coefficients
 *
 *   Function value:
 *     None
 * 
 *-
 */

void tcsProbeSetCoeffs (double *coeffs) 
{

  int jstat ;
  int i ;
  double invCoeffs[6] ;

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Invert the transform */
  slaInvf (coeffs, invCoeffs, &jstat) ;

/* If the inversion is successful then store both sets of coefficients */
  if (!jstat) {
    epicsMutexLock(tcsProbeSemId);
    for (i = 0; i < 6 ; i++) {
      tcs2oiwfs[i] = coeffs[i] ;
      oiwfs2tcs[i] = invCoeffs[i] ;
    }
    epicsMutexUnlock(tcsProbeSemId);
  }

}

/*+
 *   Function name:
 *   tcsProbeSetDefaults
 *
 *   Purpose:
 *   Sets the default X, Y and Z position for the specified probe
 *
 *   Description:
 *   This routine will be called at initialisation time (tcsSeqInit.st) 
 *   in order to set the default positions to those reported by the A&G subsystem. 
 *   Subsequently they will be updated with the current demand positions
 *   whenever the probe is following a stream of demands.
 *
 *   Invocation:
 *   tcsProbeSetDefaults (probe, xdef, ydef, zdef)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Guide probe (0-10)
 *      (>)    xdef    (double)    X default (mm)
 *      (>)    ydef    (double)    Y default (mm)
 *      (>)    zdef    (double)    Z default (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeSetDefaults (int probe, double xdef, double ydef, double zdef ) 

{
/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Store the data in the relevant structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    pwfs1Limit.xdef = xdef ;
    pwfs1Limit.ydef = ydef ;
    pwfs1Limit.zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    pwfs2Limit.xdef = xdef ;
    pwfs2Limit.ydef = ydef ;
    pwfs2Limit.zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    oiwfsLimit.xdef = xdef ;
    oiwfsLimit.ydef = ydef ;
    oiwfsLimit.zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 3:
    epicsMutexLock(tcsProbeSemId);
    aowfsLimit.xdef = xdef ;
    aowfsLimit.ydef = ydef ;
    aowfsLimit.zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 4: case 5: case 6:
    epicsMutexLock(tcsProbeSemId);
    aomLimit[probe-4].xdef = xdef ;
    aomLimit[probe-4].ydef = ydef ;
    aomLimit[probe-4].zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 7: case 8: case 9: case 10:
    epicsMutexLock(tcsProbeSemId);
    odgwLimit[probe-7].xdef = xdef ;
    odgwLimit[probe-7].ydef = ydef ;
    odgwLimit[probe-7].zdef = zdef ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetFollowFlag
 *
 *   Purpose:
 *   Sets the following status for the specified probe
 *
 *   Description:
 *   Set the follow status flag. This routine was introduced due to running
 *   out of links on some EPICS records. The data is therefore passed via 
 *   code rather than EPICS links
 *
 *   Invocation:
 *   tcsProbeSetFollowFlag (probe, flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Guide probe (0-1)
 *      (>)    flag    (long)      Follow status (1 = following)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no feedback if an invalid probe is given. The routine just
 *   ignores the data
 *
 *-
 */

void tcsProbeSetFollowFlag (int probe, long flag ) 

{

  switch (probe) {
  case 0:
    if (flag !=0) {
      pwfs1FollowStat = 1 ;
    } else {
      pwfs1FollowStat = 0 ;
    }
    break;
  case 1:
    if (flag !=0) {
      pwfs2FollowStat = 1 ;
    } else {
      pwfs2FollowStat = 0 ;
    }
    break;
  default:
    break;
  }
}


/*+
 *   Function name:
 *   tcsProbeSetOffsets
 *
 *   Purpose:
 *   Store current probe and focus offsets 
 *
 *   Description:
 *   The A&G provides focal plane offsets and probe focus offsets for
 *   the currently selected instrument. This routine reads these offsets
 *   and on the basis of whether the AO fold is deployed or not stores
 *   them for use by the telescope and probe focus models.
 *   The routine was later modified to provide an over ride if GSAOI
 *   was in use. GSAOI does not provide its offsets through the A&G.
 *   Eventually it is hoped that this over ride will be set automatically.
 *   Originally the image shifts in x and y were given in mm. This was changed
 *   to arcsecs from V1.19 of the science requirements document.
 *   Also it was pointed out the focus offset from GSAOI does not go to
 *   M2. It is now passed out of the routine so it can go to the AOM.
 *
 *   Invocation:
 *   tcsProbeSetOffsets(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *      a => Focus offset supplied by instrument when Altair not used
 *      b => Focus offset supplied by instrumetn when Altair is used
 *      c => OIWFS probe offset to be applied
 *      d => GSAOI focus offset
 *      e => Flag to say if GSAOI is in use
 *      f => GSAOI x offset (arcsecs)
 *      g => GSAOI y oddset (arcsecs)
 *
 *   Epics outputs:
 *      vala => Flag to say if GSAOI is in use
 *      valb => GSAOI focus offset for AOM Zoom corrector
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeSetOffsets (struct genSubRecord *pgsub)
{

  double dzNoAltair ;
  double dzAltair ;
  double dzProbe ;
  double dzGSAOI ;
  double dxGSAOI ;
  double dyGSAOI ;
  double coeffs[6] ;
  int i ;
  double flcurrent ;          /* Current focal length (mm) */

  for (i = 0; i < 6; i++) {
    coeffs[i] = 0.0;
  }
  coeffs[1] = 1.0;
  coeffs[5] = 1.0;

/* Fetch data from input links */
  dzNoAltair = *(double *)pgsub->a ;
  dzAltair   = *(double *)pgsub->b ;
  dzProbe    = *(double *)pgsub->c ;
  dzGSAOI    = *(double *)pgsub->d ;
  usingGSAOI   = *(long *)pgsub->e ;
  dxGSAOI    = *(double *)pgsub->f ;
  dyGSAOI    = *(double *)pgsub->g ;

/* Check if we are using GSAOI */
  if (usingGSAOI > 0 ) {

/* GSAOI in use so store the distortion coeffs. Since the filters introduce 
 * a linear shift just set the zero points
 */
    tcsOpticsGetFl(&flcurrent) ;
    coeffs[0] = dxGSAOI * DAS2R * flcurrent ;
    coeffs[3] = dyGSAOI * DAS2R * flcurrent ;
    tcsSetGSAOIDistortion(coeffs);
    tcsProbeSetOiwfsZoff (0.0) ;
    *(double *)pgsub->valb = dzGSAOI ;
  } else {
/* Store the data */
    tcsProbeSetOiwfsZoff (dzProbe) ;

    /* save to AO M1 model file if AO fold is IN */
    if (aoFoldPosition == 1)
      tcsOpticsSetM2DzIns(dzAltair) ;
    else
      tcsOpticsSetM2DzIns(dzNoAltair) ;
  }

  *(long *)pgsub->vala = usingGSAOI ;

  return 0;

}

/*+
 *   Function name:
 *   tcsProbeSetTcs2Odgw
 *
 *   Purpose:
 *   Set values of transformation coefficients for the ODGW
 *
 *   Description:
 *   This routine simply stores the values for the transformation
 *   coefficients of the ODGW. If an invalid window number is
 *   given then nothing is done. A warning is printed if the 
 *   inverse does not exist.
 *
 *   Invocation:
 *   tcsProbeSetTcs2Odgw (port, window, coeffs)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    port     (int)         GSAOI port number (1,3 or 5)
 *      (>)    window   (int)         Window number (0-3)
 *      (>)    coeffs   (double *)    Coefficient array
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsProbeSetTcs2Odgw (int port, int window, double coeffs[6]) 

{
   int jstat ;          /* Status from slaInvf */
   int i, j, k ;        /* Loop counters */
   int iport ;          /* GSAOI port index: 0=1, 1=3, 2=5 */

   iport = 0;           /* default port index */
   for (j = 0; j < 3; j++) if (port == gsaoiport[j]) iport = j;

   if (window < 0 || window > 3) return ;

   for ( i = 0; i < 6; i++) {
     tcs2odgw[iport][window][i] = coeffs[i] ;
   }

   slaInvf (tcs2odgw[iport][window], odgw2tcs[iport][window], &jstat);

   if (jstat) {
     printf ("tcsProbeSetTcs2Odgw: Port %d Window %d - failed to invert matrix\n", port, window) ;
     for (k = 0; k < 6; k++)
       printf ("tcs2odgw[%1d][%1d][%1d] = %8.4f\n",
                iport, window, k, tcs2odgw[iport][window][k]);
   }

   
}



/*+
 *   Function name:
 *   tcsProbeSetTelescope
 *
 *   Purpose:
 *   Parse the telescope name and set the telescope index
 *
 *   Description:
 *   Check if the string is Gemini-North or Gemini-South and set
 *   the index appropriately. No favouritism implied but if the name
 *   can't be interpreted default to Gemini-North
 *
 *   Invocation:
 *   tcsProbeSetTelescope(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Telescope name string
 *
 *   Epics outputs:
 *   a => Telescope name string
 *   b => Telescope index
 *   c => Diagnsotic message
 * 
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeSetTelescope (struct genSubRecord *pgsub)
{

  char utelname[80];
  static char *telOpts[] = {"GEMINI-NORTH", "NORTH", 
                            "GEMINI-SOUTH", "SOUTH", NULL};
  int n, ls, i ;
  int index ;

  n = 80 - 1;
  if (( ls = tcsDcLen(pgsub->a) ) > n) ls = n;
  tcsDcUc(pgsub->a, ls + 1, utelname);

  index = -1 ;
  for (i = 0; telOpts[i]; i++) {
   if ( !strcmp (utelname, telOpts[i])) {
     index = i ;
     break ;
   }
  }
      
  if (index < 0) {
    strcpy(pgsub->valc, "Error: defaulting to Gemini North");
    index = 0 ;
  } else {
    strcpy(pgsub->valc, "") ;
  }

  if (index < 2) {
    telIndex = 0 ;
    strcpy(pgsub->vala, "Gemini-North");
  } else {
    telIndex = 1 ;
    strcpy(pgsub->vala, "Gemini-South");
  }
  *(long *)pgsub->valb = telIndex;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsProbeGetDefaults
 *
 *   Purpose:
 *   Fetches the default X, Y and Z position for the specified probe
 *
 *   Description:
 *   This routine will be used to fetch the current default probe 
 *   positions for the specified probe. 
 *   It is expected that this routine will be called by the routine 
 *   driving the WFS probes to set the probes to a valid demand when
 *   they are not following a stream of demands.
 *
 *   Invocation:
 *   tcsProbeGetDefaults (probe, &xdef, &ydef, &zdef)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)         Probe number (0-10)
 *      (<)    xdef    (double *)    X default (mm)
 *      (<)    ydef    (double *)    Y default (mm)
 *      (<)    zdef    (double *)    Z default (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   To ensure valid data is returned, tcsProbeSetDefaults should have been
 *   called prior to this routine.
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *-
 */

void tcsProbeGetDefaults (int probe, double *xdef, double *ydef,
                          double *zdef ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Check if probe is valid and if so restore the data from the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    *xdef = pwfs1Limit.xdef  ;
    *ydef = pwfs1Limit.ydef  ;
    *zdef = pwfs1Limit.zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    *xdef = pwfs2Limit.xdef  ;
    *ydef = pwfs2Limit.ydef  ;
    *zdef = pwfs2Limit.zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    *xdef = oiwfsLimit.xdef  ;
    *ydef = oiwfsLimit.ydef  ;
    *zdef = oiwfsLimit.zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 3:
    epicsMutexLock(tcsProbeSemId);
    *xdef = aowfsLimit.xdef  ;
    *ydef = aowfsLimit.ydef  ;
    *zdef = aowfsLimit.zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 4: case 5: case 6:
    epicsMutexLock(tcsProbeSemId);
    *xdef = aomLimit[probe-4].xdef  ;
    *ydef = aomLimit[probe-4].ydef  ;
    *zdef = aomLimit[probe-4].zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 7: case 8: case 9: case 10:
    epicsMutexLock(tcsProbeSemId);
    *xdef = odgwLimit[probe-7].xdef  ;
    *ydef = odgwLimit[probe-7].ydef  ;
    *zdef = odgwLimit[probe-7].zdef  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeGetFollowFlag
 *
 *   Purpose:
 *   Fetches the follow status for the specified probe
 *
 *   Description:
 *   Simply return the following status of the specified probe that had
 *   previously been stored with a tcsProbeSetFollowFlag call.
 *
 *   Invocation:
 *   tcsProbeGetFollowFlag (probe, &flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)         Probe number (0-10)
 *      (<)    flag    (long *)      Follow status (1 = following) 
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Return 0 with no indication of any problem if the probe is out of range
 *-
 */

void tcsProbeGetFollowFlag (int probe, long *flag)

{

/* Check if probe is valid and if so restore the data from the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    *flag = pwfs1FollowStat;
    break;
  case 1:
    *flag = pwfs2FollowStat;
    break;
  default:
    *flag = 0;
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetAOMLimits
 *
 *   Purpose:
 *   Set the limits for the AOM TT probes 1, 2 and 3
 *
 *   Description:
 *   Probes 1 and 2 of the AOM have limits that are a combination of 
 *   both radial and x. This routine stores these limits for later 
 *   use. AOM Probe 3 has purely radial limits. 
 *
 *   Invocation:
 *   tcsProbeSetAOMLimits (probe, xmin, xmax, rmin, rmax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Probe number (0-10)
 *      (>)    xmin    (double)    X lower limit (mm)
 *      (>)    xmax    (double)    X upper limit (mm)
 *      (>)    rmin    (double)    Radial lower limit (mm)
 *      (>)    rmax    (double)    Radial upper limit (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *   Does nothing sliently if called with an invalid probe number
 *-
 */

void tcsProbeSetAOMLimits (int probe, double xmin, double xmax,
                          double rmin, double rmax  ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;


/* Check if probe is valid and if so store the data in the relevant
*  structure. 
*/

  switch (probe) {
  case 4: case 5: case 6:

    epicsMutexLock(tcsProbeSemId);
    aomLimit[probe-4].xmin = xmin  ;
    aomLimit[probe-4].xmax = xmax  ;
    aomLimit[probe-4].ymin = -rmax  ;
    aomLimit[probe-4].ymax = rmax ;
    aomLimit[probe-4].zmin = 0.0 ;
    aomLimit[probe-4].zmax = 0.0 ;
    aomLimit[probe-4].rmin = rmin ;
    aomLimit[probe-4].rmax = rmax ;
    aomLimit[probe-4].limitType = RADIAL;
    epicsMutexUnlock(tcsProbeSemId);
    break;

  default:
/*  Do nothing if the probe index isn't in range */
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetXYZLimits
 *
 *   Purpose:
 *   Sets the X, Y and Z limit positions for the specified probe
 *
 *   Description:
 *   WFS probes controlled by the A&G can have two types of limits, XYZ
 *   limits when they are on an XY stage or RZ limits when they are on
 *   a rotary table. This routine sets these limits for the TCS for
 *   subsequent use when checking if a combination of target and
 *   guide star gives valid probe demands. The routine will set 
 *   default R limits even though these are not expected to be used.
 *
 *   Invocation:
 *   tcsProbeSetXYZLimits (probe, xmin, xmax, ymin, ymax, zmin, zmax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Probe number (0-10)
 *      (>)    xmin    (double)    X lower limit (mm)
 *      (>     xmax    (double)    X upper limit (mm)
 *      (>)    ymin    (double)    Y lower limit (mm)
 *      (>     ymax    (double)    Y upper limit (mm)
 *      (>)    zmin    (double)    Z lower limit (mm)
 *      (>     zmax    (double)    Z upper limit (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *-
 */

void tcsProbeSetXYZLimits (int probe, double xmin, double xmax,
                          double ymin, double ymax,
                          double zmin, double zmax  ) 

{
  double rmax ;         /* Maximum radius corresponding to xy limits */
  double r1,r2 ;        /* temporary  radial limit values */
  double rmin ;         /* Minimum radius */

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Set default radial limits */

  r1 = sqrt (xmax * xmax + ymax * ymax) ;
  r2 = sqrt (xmin * xmin + ymin * ymin) ;
  rmax = gmax(r1,r2) ;
  rmin = 0.0 ;

/* Check if probe is valid and if so store the data in the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    pwfs1Limit.xmin = xmin ;
    pwfs1Limit.xmax = xmax ;
    pwfs1Limit.ymin = ymin ;
    pwfs1Limit.ymax = ymax ;
    pwfs1Limit.zmin = zmin ;
    pwfs1Limit.zmax = zmax ;
    pwfs1Limit.rmin = rmin ;
    pwfs1Limit.rmax = rmax ;
    pwfs1Limit.limitType = XY ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    pwfs2Limit.xmin = xmin ;
    pwfs2Limit.xmax = xmax ;
    pwfs2Limit.ymin = ymin ;
    pwfs2Limit.ymax = ymax ;
    pwfs2Limit.zmin = zmin ;
    pwfs2Limit.zmax = zmax ;
    pwfs2Limit.rmin = rmin ;
    pwfs2Limit.rmax = rmax ;
    pwfs2Limit.limitType = XY ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    oiwfsLimit.xmin = xmin ;
    oiwfsLimit.xmax = xmax ;
    oiwfsLimit.ymin = ymin ;
    oiwfsLimit.ymax = ymax ;
    oiwfsLimit.zmin = zmin ;
    oiwfsLimit.zmax = zmax ;
    oiwfsLimit.rmin = rmin ;
    oiwfsLimit.rmax = rmax ;
    oiwfsLimit.limitType = XY ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 3:
    epicsMutexLock(tcsProbeSemId);
    aowfsLimit.xmin = xmin ;
    aowfsLimit.xmax = xmax ;
    aowfsLimit.ymin = ymin ;
    aowfsLimit.ymax = ymax ;
    aowfsLimit.zmin = zmin ;
    aowfsLimit.zmax = zmax ;
    aowfsLimit.rmin = rmin ;
    aowfsLimit.rmax = rmax ;
    aowfsLimit.limitType = XY ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 4: case 5: case 6:

/* The AOM guiders are not strictly radial (apart from probe 3)
 * so the TCS uses both the x limits as well as the radial
 * limits
 */
    epicsMutexLock(tcsProbeSemId);
    aomLimit[probe-4].xmin = xmin  ;
    aomLimit[probe-4].xmax = xmax  ;
    aomLimit[probe-4].ymin = ymin  ;
    aomLimit[probe-4].ymax = ymax ;
    aomLimit[probe-4].zmin = zmin ;
    aomLimit[probe-4].zmax = zmax ;
    aomLimit[probe-4].rmin = rmin ;
    aomLimit[probe-4].rmax = rmax ;
    aomLimit[probe-4].limitType = RADIAL;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 7: case 8: case 9: case 10:
    epicsMutexLock(tcsProbeSemId);
    odgwLimit[probe-7].xmin = xmin ;
    odgwLimit[probe-7].xmax = xmax ;
    odgwLimit[probe-7].ymin = ymin ;
    odgwLimit[probe-7].ymax = ymax ;
    odgwLimit[probe-7].zmin = zmin ;
    odgwLimit[probe-7].zmax = zmax ;
    odgwLimit[probe-7].rmin = rmin ;
    odgwLimit[probe-7].rmax = rmax ;
    odgwLimit[probe-7].limitType  = XY;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetRLimits
 *
 *   Purpose:
 *   Sets the users radial limit positions for the specified probe
 *
 *   Description:
 *   WFS probes controlled by the A&G can have two types of limits, XYZ
 *   limits when they are on an XY stage or RZ limits when they are on
 *   a rotary table. This routine sets the radial limits for the TCS for
 *   subsequent use when checking if a combination of target and
 *   guide star gives valid probe demands. Although this routine sets
 *   a radial limit, default XY limits are set as well.
 *   This call is expected to be used from the setProbeLimits CAD command.
 *
 *   Invocation:
 *   tcsProbeSetRLimits (probe, rmin, rmax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Probe number (0-2)
 *      (>)    rmin    (double)    R lower limit (mm)
 *      (>)    rmax    (double)    R upper limit (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeSetRLimits (int probe, double rmin, double rmax)

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Check if probe is valid and if so store the data in the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    pwfs1Limit.xmin = -rmax ;
    pwfs1Limit.xmax = rmax ;
    pwfs1Limit.ymin = -rmax ;
    pwfs1Limit.ymax = rmax ;
    pwfs1Limit.rmin = rmin ;
    pwfs1Limit.rmax = rmax ;
    pwfs1Limit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    pwfs2Limit.xmin = -rmax ;
    pwfs2Limit.xmax = rmax ;
    pwfs2Limit.ymin = -rmax ;
    pwfs2Limit.ymax = rmax ;
    pwfs2Limit.rmin = rmin ;
    pwfs2Limit.rmax = rmax ;
    pwfs2Limit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    oiwfsLimit.xmin = -rmax ;
    oiwfsLimit.xmax = rmax ;
    oiwfsLimit.ymin = -rmax ;
    oiwfsLimit.ymax = rmax ;
    oiwfsLimit.rmin = rmin ;
    oiwfsLimit.rmax = rmax ;
    oiwfsLimit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}


/*+
 *   Function name:
 *   tcsProbeGetRTLimits
 *
 *   Purpose:
 *   Returns the rotary table limits for the probes
 *
 *   Description:
 *   Return the probe rotary table limits for use for example to 
 *   compute the times at which these limits will be reached if the
 *   Cass Rotator is fixed.
 *
 *   Invocation:
 *   tcsProbeGetRTLimits (&p1RTMin, &p1RTMax, &p2RTMin, &p2RTMax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    p1RTMin (double)    P1 rotary table lower limit (degs)
 *      (<)    p1RTMax (double)    P1 rotary table upper limit (degs)
 *      (<)    p2RTMin (double)    P2 rotary table lower limit (degs)
 *      (<)    p2RTMax (double)    P2 rotary table upper limit (degs)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeGetRTLimits (double *p1RTMin, double *p1RTMax,
                          double *p2RTMin, double *p2RTMax ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

  epicsMutexLock(tcsProbeSemId);
  
  *p1RTMin = pwfs1RTmin ;
  *p1RTMax = pwfs1RTmax ;
  *p2RTMin = pwfs2RTmin ;
  *p2RTMax = pwfs2RTmax ;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   tcsProbeGetRTPosns
 *
 *   Purpose:
 *   Returns the rotary table positions for the probes
 *
 *   Description:
 *   Return the probe rotary table positions for use for example to 
 *   compute the times at which these limits will be reached if the
 *   Cass Rotator is fixed.
 *
 *   Invocation:
 *   tcsProbeGetRTPosns (&p1RTPosn, &p1RTPosn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    p1RTPosn (double)    P1 rotary table position (degs)
 *      (<)    p2RTPosn (double)    P2 rotary table position (degs)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeGetRTPosns (double *p1RTPosn, double *p2RTPosn)

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

  epicsMutexLock(tcsProbeSemId);
  
  *p1RTPosn = pwfs1RTPosn ;
  *p2RTPosn = pwfs2RTPosn ;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   tcsProbeGetTcs2Odgw
 *
 *   Purpose:
 *   Get values of transformation coefficients for the ODGW
 *
 *   Description:
 *   This routine simply retrieves the values for the transformation
 *   coefficients of the ODGW. If an invalid window number is
 *   given then the identity transform is returned.  
 *tcsProbeGetTcs2Odgw
 *   Invocation:
 *   tcsProbeGetTcs2Odgw (port, window, coeffs)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    port     (int)         GSAOI port number (1,3 or 5)
 *      (>)    window   (int)         Window number (0-3)
 *      (<)    coeffs   (double *)    Coefficient array
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsProbeGetTcs2Odgw (int port, int window, double coeffs[6]) 

{
   int i,j ;            /* Loop counters */
   int iport ;          /* GSAOI port index: 0=1, 1=3, 2=5 */

   iport = 0;           /* default port index */
   for (j = 0; j < 3; j++) if (port == gsaoiport[j]) iport = j;
   
   if (window < 0 || window > 3) {
     coeffs[0] = 0.0;
     coeffs[1] = 1.0;
     coeffs[2] = 0.0;
     coeffs[3] = 0.0;
     coeffs[4] = 0.0;
     coeffs[5] = 1.0;
   } else {
     for ( i = 0; i < 6; i++) {
       coeffs[i] = tcs2odgw[iport][window][i] ;
     }
   }
/* printf("tcsProbeGetTcs2Odgw: port = %d, iport = %d, window = %d\n", port, iport, window);
   printf("tcsProbeGetTcs2Odgw: coeffs = %8.4f %8.4f %8.4f %8.4f %8.4f %8.4f\n",
         coeffs[0], coeffs[1], coeffs[2], coeffs[3], coeffs[4], coeffs[5]);
*/
}       

/*+
 *   Function name:
 *   tcsProbeSetRTLimits
 *
 *   Purpose:
 *   Stores the rotary table limits for the probes
 *
 *   Description:
 *   Save the probe rotary table limits for later use for example to 
 *   compute the times at which these limits will be reached if the
 *   Cass Rotator is fixed.
 *
 *   Invocation:
 *   tcsProbeSetRTLimits (p1RTMin, p1RTMax, p2RTMin, p2RTMax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    p1RTMin (double)    P1 rotary table lower limit (degs)
 *      (>)    p1RTMax (double)    P1 rotary table upper limit (degs)
 *      (>)    p2RTMin (double)    P2 rotary table lower limit (degs)
 *      (>)    p2RTMax (double)    P2 rotary table upper limit (degs)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeSetRTLimits (double p1RTMin, double p1RTMax,
                          double p2RTMin, double p2RTMax ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

  epicsMutexLock(tcsProbeSemId);
  
  pwfs1RTmin = p1RTMin;
  pwfs1RTmax = p1RTMax;
  pwfs2RTmin = p2RTMin;
  pwfs2RTmax = p2RTMax;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   setRTCurrentLimits
 *
 *   Purpose:
 *   Set the PWFS2 rotary table limits acording to the preferred orientation.
 *
 *   Description:
 *   Save the probe rotary table limits for later use for example to 
 *   compute the times at which these limits will be reached if the
 *   Cass Rotator is fixed.
 *
 *   Invocation:
 *   setRTCurrentLimits(pgsub)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

long setRTCurrentLimits (struct genSubRecord *pgsub)

{
  long orientation;

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

  orientation = *(long *)pgsub->a;   /* Prefered P2 RT orientation, default 2 */

  switch (orientation) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    pwfs2RTmin = -218.0;
    pwfs2RTmax = 0.0;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    pwfs2RTmin = -180.0;
    pwfs2RTmax = 180.0;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  default:
    epicsMutexLock(tcsProbeSemId);
    pwfs2RTmin = -218.0;
    pwfs2RTmax = 218.0;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }

  return 0 ;
}

/*+
 *   Function name:
 *   tcsProbeSetRTPosns
 *
 *   Purpose:
 *   Stores the rotary table positions for the probes
 *
 *   Description:
 *   Save the probe rotary table positions for later use for example to 
 *   compute the times at which these limits will be reached if the
 *   Cass Rotator is fixed.
 *
 *   Invocation:
 *   tcsProbeSetRTPosns (p1RTPosn, p2RTPosn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    p1RTPosn (double)    P1 rotary table posn (degs)
 *      (>)    p2RTPosn (double)    P2 rotary table posn (degs)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeSetRTPosns (double p1RTPosn, double p2RTPosn)

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

  epicsMutexLock(tcsProbeSemId);
  
  pwfs1RTPosn = p1RTPosn;
  pwfs2RTPosn = p2RTPosn;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   tcsProbeSetRZLimits
 *
 *   Purpose:
 *   Sets the R and Z limit positions for the specified probe
 *
 *   Description:
 *   WFS probes controlled by the A&G can have two types of limits, XYZ
 *   limits when they are on an XY stage or RZ limits when they are on
 *   a rotary table. This routine sets these limits for the TCS for
 *   subsequent use when checking if a combination of target and
 *   guide star gives valid probe demands. Although this routine sets
 *   RZ limits, default XY limits are set as well.
 *
 *   Invocation:
 *   tcsProbeSetRZLimits (probe, rmin, rmax, zmin, zmax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)       Probe number (0-2)
 *      (>)    rmin    (double)    R lower limit (mm)
 *      (>)    rmax    (double)    R upper limit (mm)
 *      (>)    zmin    (double)    Z lower limit (mm)
 *      (>)    zmax    (double)    Z upper limit (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeSetRZLimits (int probe, double rmin, double rmax,
                          double zmin, double zmax  ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Check if probe is valid and if so store the data in the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    pwfs1Limit.xmin = -rmax ;
    pwfs1Limit.xmax = rmax ;
    pwfs1Limit.ymin = -rmax ;
    pwfs1Limit.ymax = rmax ;
    pwfs1Limit.zmin = zmin ;
    pwfs1Limit.zmax = zmax ;
    pwfs1Limit.rmin = rmin ;
    pwfs1Limit.rmax = rmax ;
    pwfs1Limit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    pwfs2Limit.xmin = -rmax ;
    pwfs2Limit.xmax = rmax ;
    pwfs2Limit.ymin = -rmax ;
    pwfs2Limit.ymax = rmax ;
    pwfs2Limit.zmin = zmin ;
    pwfs2Limit.zmax = zmax ;
    pwfs2Limit.rmin = rmin ;
    pwfs2Limit.rmax = rmax ;
    pwfs2Limit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    oiwfsLimit.xmin = -rmax ;
    oiwfsLimit.xmax = rmax ;
    oiwfsLimit.ymin = -rmax ;
    oiwfsLimit.ymax = rmax ;
    oiwfsLimit.zmin = zmin ;
    oiwfsLimit.zmax = zmax ;
    oiwfsLimit.rmin = rmin ;
    oiwfsLimit.rmax = rmax ;
    oiwfsLimit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 3:
    epicsMutexLock(tcsProbeSemId);
    aowfsLimit.xmin = -rmax ;
    aowfsLimit.xmax = rmax ;
    aowfsLimit.ymin = -rmax ;
    aowfsLimit.ymax = rmax ;
    aowfsLimit.zmin = zmin ;
    aowfsLimit.zmax = zmax ;
    aowfsLimit.rmin = rmin ;
    aowfsLimit.rmax = rmax ;
    aowfsLimit.limitType = RADIAL ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeGetLimits
 *
 *   Purpose:
 *   Fetches the current probe limits for the specified WFS probe
 *
 *   Description:
 *   This routine fetches the WFS probe limits for the specified probe
 *   Probe limits are returned for both XY and radial limits. Which limits
 *   should be used is determined by the limitType parameter. If the 
 *   limitType is RADIAL then the rmin, rmax values should be used. If 
 *   the limitType is XY then the xmin, xmax, ymin and ymax values should
 *   be used. The tcsProbeSetXYZLimits and tcsProbeSetRZLimits calls
 *   ensure that sensible values are set for all limits. 
 *
 *   Invocation:
 *   tcsProbeGetLimits (probe, &limitType, &xmin, &xmax, &ymin, &ymax,
 *                      &zmin, &zmax, &rmin, &rmax)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int)         Probe number (0-10)
 *      (<)    limitType (LIMITTYPE) Either XY or RADIAL
 *      (<)    xmin    (double *)  X Probe lower limit (mm)
 *      (<)    xmax    (double *)  X probe upper limit (mm)
 *      (<)    ymin    (double *)  Y Probe lower limit (mm)
 *      (<)    ymax    (double *)  Y probe upper limit (mm)
 *      (<)    zmin    (double *)  Z Probe lower limit (mm)
 *      (<)    zmax    (double *)  Z probe upper limit (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock(tcsProbeSemId)   Give a semaphore
 *   epicsMutexLock(tcsProbeSemId)     Take a semaphore
 *
 *   Prior requirements:
 *   To ensure valid data is returned, tcsProbeSetXYZLimits or
 *   tcsProbeSetRZLimits should have been called prior to calling this
 *   routine.
 *
 *   Deficiencies:
 *   There is no check on the status of the semLib calls
 *
 *-
 */

void tcsProbeGetLimits (int probe, LIMITTYPE *limitType,
                        double *xmin, double *xmax,
                        double *ymin, double *ymax,
                        double *zmin, double *zmax,
                        double *rmin, double *rmax ) 

{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Check if probe is valid and if so restore the data from the relevant
*  structure. 
*/

  switch (probe) {
  case 0:
    epicsMutexLock(tcsProbeSemId);
    *limitType = pwfs1Limit.limitType ;
    *xmin = pwfs1Limit.xmin  ;
    *xmax = pwfs1Limit.xmax  ;
    *ymin = pwfs1Limit.ymin  ;
    *ymax = pwfs1Limit.ymax  ;
    *zmin = pwfs1Limit.zmin  ;
    *zmax = pwfs1Limit.zmax  ;
    *rmin = pwfs1Limit.rmin  ;
    *rmax = pwfs1Limit.rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 1:
    epicsMutexLock(tcsProbeSemId);
    *limitType = pwfs2Limit.limitType ;
    *xmin = pwfs2Limit.xmin  ;
    *xmax = pwfs2Limit.xmax  ;
    *ymin = pwfs2Limit.ymin  ;
    *ymax = pwfs2Limit.ymax  ;
    *zmin = pwfs2Limit.zmin  ;
    *zmax = pwfs2Limit.zmax  ;
    *rmin = pwfs2Limit.rmin  ;
    *rmax = pwfs2Limit.rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 2:
    epicsMutexLock(tcsProbeSemId);
    *limitType = oiwfsLimit.limitType ;
    *xmin = oiwfsLimit.xmin  ;
    *xmax = oiwfsLimit.xmax  ;
    *ymin = oiwfsLimit.ymin  ;
    *ymax = oiwfsLimit.ymax  ;
    *zmin = oiwfsLimit.zmin  ;
    *zmax = oiwfsLimit.zmax  ;
    *rmin = oiwfsLimit.rmin  ;
    *rmax = oiwfsLimit.rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 3:
    epicsMutexLock(tcsProbeSemId);
    *limitType = aowfsLimit.limitType ;
    *xmin = aowfsLimit.xmin  ;
    *xmax = aowfsLimit.xmax  ;
    *ymin = aowfsLimit.ymin  ;
    *ymax = aowfsLimit.ymax  ;
    *zmin = aowfsLimit.zmin  ;
    *zmax = aowfsLimit.zmax  ;
    *rmin = aowfsLimit.rmin  ;
    *rmax = aowfsLimit.rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 4: case 5: case 6:
    epicsMutexLock(tcsProbeSemId);
    *limitType = aomLimit[probe-4].limitType ;
    *xmin = aomLimit[probe-4].xmin  ;
    *xmax = aomLimit[probe-4].xmax  ;
    *ymin = aomLimit[probe-4].ymin  ;
    *ymax = aomLimit[probe-4].ymax  ;
    *zmin = aomLimit[probe-4].zmin  ;
    *zmax = aomLimit[probe-4].zmax  ;
    *rmin = aomLimit[probe-4].rmin  ;
    *rmax = aomLimit[probe-4].rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  case 7: case 8: case 9: case 10:
    epicsMutexLock(tcsProbeSemId);
    *limitType = odgwLimit[probe-7].limitType ;
    *xmin = odgwLimit[probe-7].xmin  ;
    *xmax = odgwLimit[probe-7].xmax  ;
    *ymin = odgwLimit[probe-7].ymin  ;
    *ymax = odgwLimit[probe-7].ymax  ;
    *zmin = odgwLimit[probe-7].zmin  ;
    *zmax = odgwLimit[probe-7].zmax  ;
    *rmin = odgwLimit[probe-7].rmin  ;
    *rmax = odgwLimit[probe-7].rmax  ;
    epicsMutexUnlock(tcsProbeSemId);
    break;
  }
}

/*+
 *   Function name:
 *   tcsProbeSetRadii
 *
 *   Purpose:
 *   Set physical limits of PWFS1 and PWFS2
 *
 *   Description:
 *   This routine simply stores the physical limits for future use.
 *
 *   Invocation:
 *   tcsProbeSetRadii (rmin1, rmax1, rmin2, rmax2)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    rmin1    (double)  Min. radius for PWFS1 (mm)
 *      (>)    rmax1    (double)  Max. radius for PWFS1 (mm)
 *      (>)    rmin2    (double)  Min. radius for PWFS2 (mm)
 *      (>)    rmax2    (double)  Max. radius for PWFS2 (mm)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   No checks are done on the validity of the data passed. This is
 *   the responsibility of the system providing the data, in this case
 *   the A&G. 
 *-
 */

void tcsProbeSetRadii (double rmin1, double rmax1, double rmin2,
                       double rmax2 )
{

  pwfs1Rmin = rmin1 ;
  pwfs1Rmax = rmax1 ;
  pwfs2Rmin = rmin2 ;
  pwfs2Rmax = rmax2 ;

}

/*+
 *   Function name:
 *   tcsProbeCheckRadii 
 *
 *   Purpose:
 *   Check user specified radial limits for WFS against physical limits
 *
 *   Description:
 *   This routine is expected to be called from the CAD command 
 *   setProbeLimits. It checks that the radial limits provided by the user
 *   don't conflict with the physical limits maintained by the A&G.
 *
 *   Invocation:
 *   status = tcsProbeCheckRadii (probe, rmin, rmax, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe    (int)      Probe number 0 or 1
 *      (>)    rmin     (double)   Min. requested radius (mm)
 *      (>)    rmax     (double)   Max. requested radius (mm)
 *      (>)    mess     (char *)   Error/warning message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *-
 */

int tcsProbeCheckRadii (int probe, double rmin, double rmax, char *mess)
{

  int status ;                 /* return status */
  double pwfsRmin, pwfsRmax ;  /* Radial limits of selected PWFS */

  status = 0 ;
  strcpy (mess, " ") ;

  if (probe == 0) {
    pwfsRmin = pwfs1Rmin ;
    pwfsRmax = pwfs1Rmax ;
  } else if (probe == 1) {
    pwfsRmin = pwfs2Rmin ;
    pwfsRmax = pwfs2Rmax ;
  } else {
   status = 1 ;
   strcpy(mess, "Radial limits apply to PWFS1 or 2") ;
   return status;
  }

  if (rmin < pwfsRmin ) {
    status = 1 ;
    strcpy (mess, "Lower limit too small");
  } else if (rmax > pwfsRmax) {
    status = 1 ;
    strcpy (mess, "Upper limit too large") ;
  } 

  return status ;
    
}


/*+
 *   Function name:
 *   tcsProbeGetZoff
 *
 *   Purpose:
 *   Return current z (focus) offset for a specified probe. The probes are
 *   numbered as follows 0 = PWFS1, 1 = PWFS2, 2 = OIWFS and 3 = AOWFS
 *
 *   Description:
 *   Simply fetch current offset from storage
 *
 *   Invocation:
 *   tcsProbeGetZoff(probe, &offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe    (int)      Probe identifier 0, 1, 2 or 3 
 *      (<)    offset   (double *) Current offset (mm)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Fails silently returning an offset of 0.0 if the probe number is
 *   out of range
 *
 *-
 */

void tcsProbeGetZoff(int probe, double *offset)
{

  *offset = 0.0 ;

  if (probe == 0) {
    *offset = pwfs1Zoff ;
  } else if (probe == 1) {
    *offset = pwfs2Zoff ;
  } else if (probe == 2) {
    *offset = oiwfsZoff ;
  } else if (probe == 3) {
    *offset = aowfsZoff ;
  }

}


/*+
 *   Function name:
 *   tcsProbeSetZoff
 *
 *   Purpose:
 *   Set current z (focus) offset for a specified probe
 *
 *   Description:
 *   Simply set current offset in storage. For the OIWFS the total
 *   offset is made up of two parts. A user offset that can be specified
 *   here and an instrument offset that is set by SetOiwfsZoff. The
 *   instrument offset is fetched automatically from the A&G. Ideally 
 *   this instrument offset, which would be non-zero only if the instrument
 *   was not confocal with its OIWFS, would be handled internally by the 
 *   instrument. It would either use the probeOffset record if it had no
 *   z motion or adjust the TCS demand. 
 *
 *   Invocation:
 *   tcsProbeSetZoff(probe, offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe    (int)      Probe identifier 0, 1 or 2
 *      (>)    offset   (double )  Current offset (mm)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Fails silently without setting an offset if the probe number is
 *   out of range
 *
 *-
 */

void tcsProbeSetZoff(int probe, double offset)
{

  if (probe == 0) {
    pwfs1Zoff = offset ;
  } else if (probe == 1) {
    pwfs2Zoff = offset ;
  } else if (probe == 2) {
    oiwfsUserZoff = offset ;
    oiwfsZoff = oiwfsUserZoff + oiwfsInsZoff ;
  } else if (probe == 3) {
    aowfsZoff = offset ;
  }

}

/*+
 *   Function name:
 *   tcsProbeSetOiwfsZoff
 *
 *   Purpose:
 *   Set focus offset for an OIWFS
 *
 *   Description:
 *   This routine sets the focus offset for an OIWFS as specified by
 *   the instrument itself. This offset will allow for any offset 
 *   in the focal planes of the instrument itself and the OIWFS.
 *
 *   Invocation:
 *   tcsProbeSetOiwfsZoff(offset)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    offset   (double )  Current offset (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsProbeSetOiwfsZoff(double offset)
{

  oiwfsInsZoff = offset ;
  oiwfsZoff = oiwfsUserZoff + oiwfsInsZoff ;

}


/*+
 *   Function name:
 *   tcsProbeStoreOdgwCoeffs
 *
 *   Purpose:
 *   Store ODGW transformation coefficients for later use
 *
 *   Description:
 *   This routine is intended to be called at startup but can be called
 *   at any time the transformation coefficients need to be updated.
 *   At startup pvload will set the 3x4 sets of 6 parameters and then 
 *   trigger the record.
 *   
 *   Invocation:
 *   tcsProbeStoreOdgwCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => 6 transformation coefficients for Port 1, ODGW 0 
 *   b => 6 transformation coefficients for Port 1, ODGW 1 
 *   c => 6 transformation coefficients for Port 1, ODGW 2 
 *   d => 6 transformation coefficients for Port 1, ODGW 3 
 *   e => 6 transformation coefficients for Port 3, ODGW 0 
 *   f => 6 transformation coefficients for Port 3, ODGW 1 
 *   g => 6 transformation coefficients for Port 3, ODGW 2 
 *   h => 6 transformation coefficients for Port 3, ODGW 3 
 *   i => 6 transformation coefficients for Port 5, ODGW 0 
 *   (skip j as it triggers the gensub)
 *   k => 6 transformation coefficients for Port 5, ODGW 1 
 *   l => 6 transformation coefficients for Port 5, ODGW 2 
 *   m => 6 transformation coefficients for Port 5, ODGW 3 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsProbeStoreOdgwCoeffs (struct genSubRecord *pgsub)
{
  double coeffs[6];

  if (!init) {
    tcsProbeInit() ;
  }
  memcpy (coeffs, pgsub->a, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(1, 0, coeffs);

  memcpy (coeffs, pgsub->b, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(1, 1, coeffs);

  memcpy (coeffs, pgsub->c, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(1, 2, coeffs);

  memcpy (coeffs, pgsub->d, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(1, 3, coeffs);

  memcpy (coeffs, pgsub->e, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(3, 0, coeffs);

  memcpy (coeffs, pgsub->f, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(3, 1, coeffs);

  memcpy (coeffs, pgsub->g, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(3, 2, coeffs);

  memcpy (coeffs, pgsub->h, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(3, 3, coeffs);

  memcpy (coeffs, pgsub->i, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(5, 0, coeffs);
/* Skip j input as it triggers the gensub */
  memcpy (coeffs, pgsub->k, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(5, 1, coeffs);

  memcpy (coeffs, pgsub->l, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(5, 2, coeffs);

  memcpy (coeffs, pgsub->m, 6 * sizeof(double)) ;
  tcsProbeSetTcs2Odgw(5, 3, coeffs);

  return 0 ;

}

/*+
 *   Function name:
 *   tcsModifyOdgwCoeffs
 *
 *   Purpose:
 *   Read in a set of 6 ODGW transformation coefficients
 *   and update the transformation coefficient array by calling
 *   tcsProbeSetTcs2Odgw
 *   
 *   Invocation:
 *   tcsModifyOdgwCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => GSAOI port number (1, 3 or 5)
 *   b => Window number
 *   c => transform coefficient A
 *   d => transform coefficient B
 *   e => transform coefficient C
 *   f => transform coefficient D
 *   g => transform coefficient E   
 *   h => transform coefficient F
 *
 *   Epics output:
 *   vala => Array of 6 coefficients
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsModifyOdgwCoeffs (struct genSubRecord *pgsub)
{

  double coeffs[6];
  long port, window;

  port = *(long *)pgsub->a;   /* Port number, default 1 */
  if ((port != 1) && (port != 3) && (port !=5)) port = 1;
  window = *(long *)pgsub->b; /* Window number, default 0 */
  if (window < 0 || window > 3) window = 0;
  coeffs[0] = *(double *) pgsub->c;
  coeffs[1] = *(double *) pgsub->d;  
  coeffs[2] = *(double *) pgsub->e;  
  coeffs[3] = *(double *) pgsub->f;
  coeffs[4] = *(double *) pgsub->g;
  coeffs[5] = *(double *) pgsub->h;
  tcsProbeSetTcs2Odgw((int)port, (int)window, coeffs);

  return 0 ;
}


/*+
 *   Function name:
 *   tcsProbeTcs2Oiwfs
 *
 *   Purpose:
 *   Transforms TCS coordinates into the frame of the OIWFS
 *
 *   Description:
 *   A check is made to see if the OIWFS is controlled in x/y coordinates.
 *   If so the TCS x,y are converted to the OIWFS frame using the 
 *   transform coefficients provided from the A&G
 *
 *   Invocation:
 *   tcsProbeTcs2Oiwfs (tx, ty, &ox, &oy)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tx   (double)     TCS x coordinate
 *      (>)    ty   (double)     TCS y coordinate
 *      (<)    ox   (double *)   OIWFS x coordinate
 *      (<)    oy   (double *)   OIWFS y coordinate
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsProbeTcs2Oiwfs (double xt, double yt, double *ox, double *oy)
{

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
  epicsMutexLock(tcsProbeSemId);

  *ox = tcs2oiwfs[0] + tcs2oiwfs[1] * xt + tcs2oiwfs[2] * yt ;
  *oy = tcs2oiwfs[3] + tcs2oiwfs[4] * xt + tcs2oiwfs[5] * yt ;

  epicsMutexUnlock(tcsProbeSemId);
}

/*+
 *   Function name:
 *   tcsProbeTcs2Aom
 *
 *   Purpose:
 *   Transforms TCS coordinates into the frame of the AOM 
 *
 *   Description:
 *   The TCS x,y are converted to the AOM frame using the 
 *   transform coefficients provided from the system 
 *
 *   Invocation:
 *   tcsProbeTcs2Aom (gi, tx, ty, &ox, &oy)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    gi   (int)        Index to TT probe 0..2
 *      (>)    tx   (double)     TCS x coordinate
 *      (>)    ty   (double)     TCS y coordinate
 *      (<)    ox   (double *)   ODGW x coordinate
 *      (<)    oy   (double *)   ODGW y coordinate
 *
 *   Function value:
 *      None
 *
 *   Deficiencies :
 *   Fails silently if the index is outside the range 0 to 2
 * 
 *-
 */

void tcsProbeTcs2Aom (int gi, double xt, double yt, double *ox, double *oy)
{
 
/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
  if (gi > -1 && gi < 3) {
    epicsMutexLock(tcsProbeSemId);

    *ox = tcs2aom[gi][0] + tcs2aom[gi][1] * xt + tcs2aom[gi][2] * yt ;
    *oy = tcs2aom[gi][3] + tcs2aom[gi][4] * xt + tcs2aom[gi][5] * yt ;

    epicsMutexUnlock(tcsProbeSemId);
  } else {
    *ox = xt ;
    *oy = yt ;
  }
}
/*+
 *   Function name:
 *   tcsProbeTcs2Odgw
 *
 *   Purpose:
 *   Transforms TCS coordinates into the frame of the GSAOI 
 *
 *   Description:
 *   A check is made to see if the  GSAOI is controlled in x/y coordinates.
 *   If so the TCS x,y are converted to the GSAOI frame using the 
 *   transform coefficients provided from the detector 
 *
 *   Invocation:
 *   tcsProbeTcs2Odgw (port, gi, tx, ty, &ox, &oy)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    port (int)        GSAOI port number (1,3 or 5)
 *      (>)    gi   (int)        Index to ODGW 0..3
 *      (>)    tx   (double)     TCS x coordinate
 *      (>)    ty   (double)     TCS y coordinate
 *      (<)    ox   (double *)   ODGW x coordinate
 *      (<)    oy   (double *)   ODGW y coordinate
 *
 *   Function value:
 *      None
 *
 *   Deficiencies :
 *   Fails silently if the index is outside the range 0 to 3
 * 
 *-
 */

void tcsProbeTcs2Odgw (int port, int gi, double xt, double yt, double *ox, double *oy)
{

  double coeffs[6];

/* Use the probe semaphore just in case the coefficients are being
*  updated just as the conversion is being done
*/
   int j;               /* Loop index */
   int iport ;          /* GSAOI port index: 0=1, 1=3, 2=5 */

/* Check if library is initialised */

  if (!init)
    tcsProbeInit() ;

   iport = 0;           /* default port index */
   for (j = 0; j < 3; j++) if (port == gsaoiport[j]) iport = j;
   

/* Fetch distortion coefficients that need to be taken back out before 
 * computing where the star is. Note the assumption here is that inserting
 * a filter is a purely linear shift so we only need coeffs 0 and 3
 */
   tcsGetGSAOIDistortion(1, coeffs);

   if (gi > -1 && gi < 4) {
    epicsMutexLock(tcsProbeSemId);

/* For consistency, only correct the transformations if GSAOI is
 * in use. It could be argued that even if GSAOI doesn't have the
 * beam we should always use the corrected transformations as only
 * GSAOI is affected. However for consistency with ignoring the 
 * focus changes which we definitely must not apply if GSAOI doesn't
 * have the beam we ignore the image shifts as well.
 */
    if (usingGSAOI) {
      *ox = tcs2odgw[iport][gi][0] + tcs2odgw[iport][gi][1] * (xt - coeffs[0]) + 
              tcs2odgw[iport][gi][2] * yt ;
      *oy = tcs2odgw[iport][gi][3] + tcs2odgw[iport][gi][4] * xt + 
              tcs2odgw[iport][gi][5] * (yt - coeffs[3]) ;
    } else {
      *ox = tcs2odgw[iport][gi][0] + tcs2odgw[iport][gi][1] * xt + tcs2odgw[iport][gi][2] * yt ;
      *oy = tcs2odgw[iport][gi][3] + tcs2odgw[iport][gi][4] * xt + tcs2odgw[iport][gi][5] * yt ;
    }

    epicsMutexUnlock(tcsProbeSemId);

  } else {
    *ox = xt ;
    *oy = yt ;
  }
}

/*+
 *   Function name:
 *   tcsFindGsaoiPort
 *
 *   Purpose:
 *   Discover the current GSAOI port number 
 *
 *   Description:
 *   Search through AG records containing the names of instruments on
 *   ports 1, 3 and 5. When found one set to "GSAOI", set port number
 *   in local var and output on VALA. Default is port 1. The check
 *   for the string "GSAOI" is case independent.
 *   Note that if the A&G has been incorrectly configured with "GSAOI"
 *   on multiple ports then we'll take the first one.
 *
 *   Invocation:
 *   tcsFindGsaoiPort(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => (char) Instrument at AG port number 1 (ag:port:port1) 
 *   b => (char) Instrument at AG port number 3 (ag:port:port3) 
 *   c => (char) Instrument at AG port number 5 (ag:port:port5) 
 *
 *   Epics output:
 *   a => (long) Port number for GSAOI
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsFindGsaoiPort (struct genSubRecord *pgsub)
{
 long gsaoiport;
 char instname[MAX_STRING_SIZE];
 char ucInstname[MAX_STRING_SIZE];
   
  gsaoiport = 1;  /* Default */

  strncpy(instname, (char *)pgsub->a, MAX_STRING_SIZE);
  tcsDcUc(instname, MAX_STRING_SIZE, ucInstname);
  if (!strncmp(ucInstname, "GSAOI", 5)) {
    gsaoiport = 1;
  } else {
    strncpy(instname, (char *)pgsub->b, MAX_STRING_SIZE);
    tcsDcUc(instname, MAX_STRING_SIZE, ucInstname);
    if (!strncmp(ucInstname, "GSAOI", 5)) {
      gsaoiport = 3;
    } else {
      strncpy(instname, (char *)pgsub->c, MAX_STRING_SIZE);
      tcsDcUc(instname, MAX_STRING_SIZE, ucInstname);
      if (!strncmp(ucInstname, "GSAOI", 5)) gsaoiport = 5;
    }
  }

/* Store in  local static var  & output on vala */
  gsaoiCurrentPort = (int)gsaoiport;
  *(long *)pgsub->vala = gsaoiport;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsGetGsaoiPort
 *
 *   Purpose:
 *   Get the current GSAOI port number 
 *
 *   Description:
 *   Get the current GSAOI port number from local static variable
 *
 *   Invocation:
 *   tcsGetGsaoiPort()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  gsaoiport  (int)  Return port value.
 * 
 *-
 */
int tcsGetGsaoiPort ()
{
/* Return  local var */
  return gsaoiCurrentPort;
}
epicsRegisterFunction(tcsProbeSetAoFold);
epicsRegisterFunction(setRTCurrentLimits);
epicsRegisterFunction(tcsProbeSetTelescope);
epicsRegisterFunction(tcsProbeSetOffsets);
epicsRegisterFunction(tcsProbeRTPosns);
epicsRegisterFunction(tcsFindGsaoiPort);
epicsRegisterFunction(tcsProbeStoreOdgwCoeffs);
epicsRegisterFunction(tcsProbeOdgwCoeffs);
epicsRegisterFunction(tcsModifyOdgwCoeffs);
