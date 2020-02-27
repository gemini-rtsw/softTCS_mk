/*
*   FILENAME
*   tcsEcsLib.c
*
*   FUNCTION NAME(S)
*   tcsEcsCalcPosns      - compute enclosure and shutter positions 
*   tcsEcsCalcSlit       - compute edges of slit
*   tcsEcsCheckParams    - check user and default parameters for consistency
*   tcsEcsClearSlewFlag  - return slew flag and clear it
*   tcsEcsDump           - dump ECS parameters to screen
*   tcsEcsEffectiveSlitPosns - compute effective slit positions 
*   tcsEcsEnableDome     - set flag to enable automatic moves
*   tcsEcsEnableShtrs    - set flag to enable automatic moves
*   tcsEcsGetEnableFlags - fetch flags that determine if dome/shtrs are enabled
*   tcsEcsGetEncMode     - fetch operating mode of enclosure
*   tcsEcsGetIssueMoves  - retrieve flag to control issue of move or follow
*   tcsEcsGetParamDefs   - retrieve defaults for enclosure positioning
*   tcsEcsGetPosnDefs    - retrieve default positions for enclosure & shutters
*   tcsEcsGetShutLimits  - retrieve the enclosure shutter limits
*   tcsEcsGetUserParams  - retrieve user defined enclosure parameters
*   tcsEcsHaDec2AzEl     - convert an HA and dec to Azimuth & elevation
*   tcsEcsLimitTime      - compute time to next limit
*   tcsEcsLimitType      - check if current target is in an enclosure limit
*   tcsEcsPrintLimit     - wrapper for testing tcsEcsCalcLimit
*   tcsEcsPrintVign      - wrapper for testing tcsEcsVignette
*   tcsEcsSetIssueMoves  - toggle issue moves flag
*   tcsEcsSetParamDefs   - set default parameters for enclosure positioning
*   tcsEcsSetPosnDefs    - set default positions for enclosure & shutters
*   tcsEcsSetSlewFlag    - set slew flag to TRUE
*   tcsEcsSetShutLimits  - set the enclosure shutter limits
*   tcsEcsSetUserParams  - set users requested shutter parameters
*   tcsEcsShowFlags      - make enable flags available to EPICS
*   tcsEcsUpdateDefs     - update default parameters for ECS positioning
*   tcsEcsVignette       - calculate vignetting of mirror by enclosure
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEcsLib.c,v $
 * Revision 1.6  2014/09/18 15:03:35  cjm
 * Add new routine tcsEcsEffectivePosns
 *
 * Revision 1.5  2003/01/27 13:09:27  cjm
 * Fix logic of parameter checking
 *
 * Revision 1.4  2003/01/20 13:32:46  cjm
 * Bug fix for shutter vignette calculation
 *
 * Revision 1.3  2001/05/05 23:59:58  cjm
 * Ensure elTopfrac and elBotfrac are initialised
 *
 * Revision 1.2  1998/11/16 18:38:59  cjm
 * Pass shtrMode to tcsEcsCheckParams so that the slit height is not checked when the mode is fully open
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.12  1998/10/14 11:30:13  tcs
 * Fix problems with positioning shutters for some targets
 *
 * Revision 1.11  1998/09/16 01:05:31  tcs
 * Fix typos in tcsEcsCalcSlit
 *
 * Revision 1.10  1998/06/08 09:57:20  tcs
 * Fix bug in vignette fraction calculation
 *
 * Revision 1.9  1998/03/23 14:37:33  cjm
 * Add code for computing times to limits
 *
 * Revision 1.8  1997/11/18 08:26:26  cjm
 * Rename entranceAp to beamDiameter
 *
 * Revision 1.7  1997/11/05 16:45:23  cjm
 * Add tcsEcsVignette routine
 *
 * Revision 1.6  1997/10/10 07:18:31  cjm
 * Add tcsEcsShowFlags
 *
 * Revision 1.5  1997/10/01 15:25:42  cjm
 * Use correct units when clipping shutter demands
 *
 * Revision 1.4  1997/09/16 11:06:31  cjm
 * Added extra routines to support Basic mode
 *
 * Revision 1.3  1997/07/25 16:47:07  cjm
 * Add tcsEcsgetParamDefs
 *
 * Revision 1.2  1997/07/23 13:31:18  cjm
 * new routines tcsEcsDump, EnableShtrs and EnableDome
 *
 * Revision 1.1  1997/07/15 13:41:32  cjm
 * Initial version
 *
 * Revision 1.1  1997/02/10 17:10:37  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1996/10/24 16:11:08  tcs
 * Pointing origin offset commands
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <math.h>
#include <epicsStdioRedirect.h>
#include <epicsMutex.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "slamac.h"
#include "slalib.h"

#include <genSubRecord.h>

#include "tcsConstants.h"
#include "tcsEcsLib.h"
#include "tcsLimits.h"

static ENCLIMIT tcsEcsLimitType (double x, double y, double ylim,
                                double xLower, double xUpper) ;

epicsMutexId ecsSemId ;                 /* Semaphore to protect slew flag */

static double ecsMinBotShtr = 0.5;       /* Min elevation of bottom shutter */
static double ecsMaxBotShtr = 60.0;      /* Max elevation of bottom shutter */
static double ecsMinTopShtr = 0.5;       /* Min elevation of top shutter */
static double ecsMaxTopShtr = 106.5;     /* Max elevation of top shutter */

static double ecsDefDomePos = 90.0;      /* Default dome azimuth position */
static double ecsDefTopShtr = 15.0;      /* Default top shutter elevation */
static double ecsDefBotShtr = 15.0;      /* Default bottom shutter elevation */

static double ecsEncRadius  = 17000.0;   /* Enclosure radius (mm) */
static double ecsSlitWidth  = 9320.0;    /* Slit width (mm) */
static double ecsBeamDiameter = 7909.0;  /* Beam diameter at M1 (mm) */
static double ecsMinScatWidth = 500.0;   /* Min. scatter adjustment (mm) */
static double ecsMinSlitHeight = 9320.0; /* Min. slit height (mm) */
static double ecsSlitHeight = 9320.0;    /* Slit height (mm) */
static double ecsFieldRadius = 8.0;      /* Field radius (arcmin) */

static SHUTTERMODE ecsShutMode = FULLYOPEN;  /* Startup shutter mode */
static ENCMODE ecsEncMode = BASIC;       /* Enclosure operating mode */

static int ecsDomeEnabled = FALSE;    /* Dome disabled on startup */
static int ecsShtrsEnabled = FALSE;  /* Shutters disabled on startup */
static int ecsIssueMoves = TRUE;     /* Issue move rather than follow */

static double ecsPosnEffWidth ;     /* Effective positioning slit width (mm) */
static double ecsPosnEffHeight ;    /* effective positioning slit height (mm) */
static double ecsVignEffWidth ;     /* Effective vignette slit width (mm) */
static double ecsVignEffHeight;     /* Effective vignette slit height (mm) */

static int ecsSlewFlag = FALSE;          /* True if slew command issued */


/*+
 *   Function name:
 *   tcsEcsCalcPosns
 *
 *   Purpose:
 *   Compute enclosure position for maximum viewing time 
 *
 *   Description:
 *   In minimum vibration and minimum scatter modes, the TCS must position
 *   the dome and shutters such as to maximise the time before they must
 *   be moved again. This routine calculates the optimum position to
 *   achieve this aim. The routine is given the start and end points of
 *   the track of the source across the sky then positions the dome and
 *   shutters so that the maximum length of this track falls within the 
 *   enclosure aperture. The end point of the track will either be the same 
 *   as the start point (for cicumpolar objects) or more usually the point
 *   at which the target drops below the lower elevation limit. The major 
 *   complications involve handling the reversals in azimuth and/or elevation
 *   that occur as well as those targets whose tracks start close to the 
 *   zenith where the dome azimuth is completely arbitrary.
 *
 *   Invocation:
 *   tcsEcsCalcPosns (startHA, startDec, endHA, elLim, clat, slat, &domeAz,
 *                    &elTopShtr, &elBotShtr, &elTopVShtr, &elBotVShtr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   startHA    (double)   Observed HA of start of track (rads)
 *      (>)   startDec   (double)   Observed Dec of start of track (rads)
 *      (>)   endHA      (double)   Observed HA of end of track (rads)
 *      (>)   elLim      (double)   Elevation lower limit (rads)
 *      (>)   clat       (double)   Cos of site latitude
 *      (>)   slat       (double)   Sin of site latitude 
 *      (<)   domeAz     (double *) Dome azimuth (rads)
 *      (<)   elTopShtr  (double *) Top shutter elevation (rads)
 *      (<)   elBotShtr  (double *) Bottom shutter elevation (rads)
 *      (<)   elTopVShtr (double *) Top virtual shutter elevation (rads)
 *      (<)   elBotVShtr (double *) Bottom virtual shutter elevation (rads)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   (>)   ecsPosnEffWidth  (double)   Effective slit width (mm)
 *   (>)   ecsEncRadius     (double)   Enclosure radius (mm)
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   The function relies on global data describing the dimensions of the 
 *   slit aperture. It would be better to pass all data into the routine
 *   via parameters rather than rely on this.
 *
 *-
 */

void tcsEcsCalcPosns (double startHA, double startDec, double endHA,
                      double elLim, double clat, double slat,
                      double *domeAz, double *elTopShtr,
                      double *elBotShtr, double *elTopVShtr, 
                      double *elBotVShtr) 
{
   double rlim ;          /* Radius of "don't care" region at zenith (rads) */
   double az0 ;           /* Observed azimuth at start of track (rads) */
   double el0 ;           /* Observed elevation at start of track (rads) */
   double x0, y0, z0 ;    /* Cartesian components of start az/el */
   double cdec, sdec ;    /* Cos/sin of declination */
   double rr ;            /* cos elevation squared */
   double r ;             /* cos elevation */
   double exitEl;         /* Elevation on exit from zenith region */
   double exitHA ;        /* HA on exit from zenith region */
   int    domeAzSolved ;  /* True once the dome azimuth is found */
   int    domeElSolved ;  /* True once shutter elevations are found */
   double haRev ;         /* HA at which azimuth reverses direction */
   double x1, y1, z1 ;    /* Cartesian components of az and el */
   double x0p, y0p ;      /* Cartesian components in enclosure frame */
   double x1p, y1p ;      /* Cartesian components in enclosure frame */
   double deltaHA ;       /* HA step (rads) */
   double az1, el1 ;      /* Azimuth & elevation of target */
   double dx, dy ;        /* delta x,y for a deltaHA time step */
   double angle ;         /* Angle between slit edges and target path (rads) */
   double factor ;        /* Factor to scale angle between target & dome */
   double cosAzEnc ;      /* Cos of enclosure azimuth */
   double sinAzEnc ;      /* sin of enclosure azimuth */
   double ymax ;          /* Max y component for circumpolar objects */
   double AA ;            /* angle (rads) between dome and target direction */
   double elMin ;         /* Minimum elevation for target (rads) */
   double elMax ;         /* Maximum elevation of target (rads) */
   int    dbgLevel ;      /* Debug level */

/* Initialise data */
   domeAzSolved = FALSE ;
   domeElSolved = FALSE ;
   dbgLevel = DBG_NONE ;

/* Compute radius of region at zenith where there is no solution for the 
*  dome azimuth
*/
  rlim = ecsPosnEffWidth / (2.0 * ecsEncRadius) ;

/* Compute observed az/el at start of track as well as the cartesian
*  vector components.
*/
  tcsEcsHaDec2AzEl (startHA, startDec, clat, slat, &az0, &el0, &x0, &y0, &z0) ;
  rr   = x0 * x0 + y0 * y0 ;
  r    = sqrt (rr) ;
  cdec = cos(startDec) ;
  sdec = sin(startDec) ;

/* A dome azimuth is now computed such that a long track will be possible
*  before the dome has to be repositioned. A couple of special cases
*  are handled first.
*/

/* Is start position within the region around the zenith where it doesn't
*  matter what azimuth the dome is set to ? If it is then set the dome azimuth
*  to the source azimuth on exit from this region.
*/
  if (r <= rlim) {

/* For sources that are rising we need to ensure that the shutter edges
*  are positioned to take account of the fact the source is over the pole
*  at the starting enclosure azimuth.
*/
    if (startHA < 0.0) el0 = PI - el0 ; 
    tcsEcsCalcSlit (el0, elLim, SETTING, elTopShtr, elBotShtr,
                    elTopVShtr, elBotVShtr); 

/* Compute HA on exit from zenith region */
    exitEl = acos(rlim) ;
    tcsLimEl (cdec, sdec, exitEl, clat, slat, &exitHA) ;
    tcsEcsHaDec2AzEl (exitHA, startDec, clat, slat, &az0, &el0, &x0, &y0, &z0) ;
    *domeAz = az0 ;
    domeAzSolved = TRUE ;
    domeElSolved = TRUE ;

    DBGMSG (DBG_MIN, "tcsEcsCalcLimit: Dome az indeterminate at start HA") ;
  } 

  if (startHA == endHA) {

/* Pick off circumpolar objects that fit completely within the 
*  enclosure opening.
*/

    haRev = -acos (slat * cdec / (clat * sdec)) ;
    ymax = - sin(haRev) * cdec ;
    if (ymax < rlim) {
      *domeAz = (slat >= 0.0) ? 0.0 : PI ;
      domeAzSolved = TRUE ;
    }

   tcsEcsHaDec2AzEl (0.0, startDec, clat, slat, &az1, &elMax,
                      &x1, &y1, &z1) ;
   tcsEcsHaDec2AzEl (PI, startDec, clat, slat, &az1, &elMin,
                      &x1, &y1, &z1) ;
   tcsEcsCalcSlit ((elMin + elMax)/2.0, elLim, CENTRED, elTopShtr, elBotShtr,
                   elTopVShtr, elBotVShtr) ;
   if ((elMax < *elTopVShtr) && (elMin > *elBotVShtr))  domeElSolved = TRUE ;

   DBGMSG (DBG_MIN, "tcsEcsCalcLimit: Target is circumpolar");
  } 

/* Now handle the main bulk of targets.
*  The dome and target are first positioned so that the target is right on
*  the slit edge. The angle between the target track and slit is then
*  calculated. Depending on this angle the enclosure is then backed off
*  to place the target more centrally in the aperture.
*/

  if (!domeAzSolved) {
    deltaHA = 1.0 * S2R ;          /* One second time step */
    AA = asin (rlim / cos(el0)) ;

    tcsEcsHaDec2AzEl (startHA + deltaHA, startDec, clat, slat, &az1, &el1,
                      &x1, &y1, &z1) ;
    dy = y0 - y1 ;
    *domeAz = (dy < 0.0) ? az0 + AA : az0 - AA ;
    cosAzEnc = cos (*domeAz) ;
    sinAzEnc = sin (*domeAz) ;

    y0p = y0 * cosAzEnc - x0 * sinAzEnc ;
    x0p = y0 * sinAzEnc + x0 * cosAzEnc ;

    y1p = y1 * cosAzEnc - x1 * sinAzEnc ;
    x1p = y1 * sinAzEnc + x1 * cosAzEnc ;

    dy = y0p - y1p ;
    dx = x0p - x1p ;

    angle = (dx == 0.0 && dy == 0.0) ? 0.0 : atan2 (dy, dx) ;
    if (angle < 0.0) angle = -angle ;
    if (angle > PI/2.0) angle = PI - angle ;
    factor = 1.0 + ( angle - DPIBY2) / DPIBY2 ;

    *domeAz = (dy < 0.0) ? az0 + factor * AA : az0 - factor * AA ;
    domeAzSolved = TRUE ;

    DBGMSGREAL (DBG_MIN, "tcsEcsCalcLimit: Dome az (degs)", *domeAz/D2R);
    DBGMSGREAL (DBG_FULL, "tcsEcsCalcLimit: AA (degs)", AA/D2R) ;
    DBGMSGREAL (DBG_FULL, "tcsEcsCalcLimit: az0 (degs)", az0/D2R);
    DBGMSGREAL (DBG_FULL, "tcsEcsCalcLimit: angle (degs)", angle/D2R);
    DBGMSGREAL (DBG_FULL, "tcsEcsCalcLimit: factor      ", factor); 

  }
    
  if (!domeElSolved) {

    if (startHA < 0.0) {           /* Source is rising */
      tcsEcsHaDec2AzEl ( 0.0, startDec, clat, slat, &az1, &elMax, &x1,
                         &y1, &z1) ;  
      tcsEcsCalcSlit (el0, elLim, RISING, elTopShtr, elBotShtr, elTopVShtr,
                      elBotVShtr) ;
      if (elMax < *elTopVShtr) 
        tcsEcsCalcSlit (elMax, elLim, SETTING, elTopShtr, elBotShtr,
                        elTopVShtr, elBotVShtr);

     } else {                      /* Source is setting */
      
      tcsEcsHaDec2AzEl ( PI, startDec, clat, slat, &az1, &elMin, &x1,
                         &y1, &z1) ;  
      if (elMin < elLim) elMin = elLim ;
      tcsEcsCalcSlit (el0, elLim, SETTING, elTopShtr, elBotShtr, elTopVShtr,
                      elBotVShtr) ;
      if (elMin > *elTopVShtr)
        tcsEcsCalcSlit (elMin, elLim, RISING, elTopShtr, elBotShtr,
                        elTopVShtr, elBotVShtr) ;
     }
 
     domeElSolved = TRUE ;

  }


}

/*+
 *   Function name:
 *   tcsEcsCalcSlit
 *
 *   Purpose:
 *   Calculate demands for upper and lower shutters
 *   based on the mount elevation demand and enclosure operating mode.
 *
 *   Description:
 *   Based on the current mount demand elevation, the TCS must calculate
 *   the positions of the lower edge of the top shutter and the upper
 *   edge of the bottom shutter for sending to the ECS. This routine 
 *   performs this calculation taking account of the current shutter
 *   operating mode, the shutter operating limits and the enclosure 
 *   operating mode. If the enclosure mode is MinVibration or
 *   MinScatter it is also neccesary to know whether the current target
 *   is rising or setting.
 *   As well as returning the elevation demands of the physical shutter,
 *   the routine returns the elevations of a "virtual" shutter. These
 *   elevations are those at which a new move command will sent to the
 *   ECS for certain enclosure operating modes.
 *
 *   Invocation:
 *   tcsEcsCalcSlit (el, ellimit, sourceMode, &elTopShtr, &elBotShtr, 
 *                   &elTopVShtr, &elBotVShtr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  el       (double)  Current mount elevation demand (rads)
 *      (>)  ellimit  (double)  Mount elevation lower limit (rads)
 *      (>)  sourceMode (SOURCEMODE) CENTRED, RISING or SETTING
 *      (<)  elTopShtr (double *) Top shutter demand (rads)
 *      (<)  elBotShtr (double *) Bottom shutter demand (rads)
 *      (<)  elTopVShtr (double *) Elevation of top virtual shutter (rads)
 *      (<)  elBotVShtr (double *) Elevation of bottom virtual shutter (rads)
 *
 *   Function value:
 *   None.
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

void tcsEcsCalcSlit (double el, double ellimit, SOURCEMODE sourceMode, 
                     double *elTopShtr,
                     double *elBotShtr, double *elTopVShtr, 
                     double *elBotVShtr)

{
  double openArc ;          /* Size of slit opening (rads) */
  double ds ;               /* Offset of real and virtual slit (rads) */
  double rlim ;             /* Effective half width of slit */
  double cosEl ;            /* Cos of target elevation */
  double el2 ;              /* Cos**2 of corrected elevation */
  double elp ;              /* corrected elevation (rads) */
  double del ;              /* Elevation adjustment (rads) */

/* Set up some useful variables */

  openArc = asin (ecsPosnEffHeight/ecsEncRadius) ;
  ds      = asin ((ecsSlitHeight - ecsPosnEffHeight)/(2.0*ecsEncRadius)) ;

 
  if (ecsShutMode == FULLYOPEN) {
    *elBotVShtr = ellimit + ds;
    *elBotShtr  = ecsMinBotShtr * D2R ;
    *elTopShtr  = ecsMaxTopShtr * D2R;
    *elTopVShtr = *elTopShtr - ds ;
  } else {                            /* This section handles tracking mode */
    
/* Compute a correction to the shutter elevation to take account of the 
*  rotation between the target azimuth and the enclosure azimuth. This
*  rotation means that the edges of the shutters are not tangent to
*  lines of constant elevation.
*/
    rlim    = ecsPosnEffWidth / (2.0 * ecsEncRadius) ;
    cosEl   = cos(el) ;
    if (cosEl > rlim) {
      el2 = cosEl * cosEl - rlim * rlim ;
      cosEl = sqrt(el2) ;
      elp   = acos(cosEl) ;
    } else {
      elp = DPIBY2 ;
    }
    del   = elp - el ;

/* First handle the case where the source is to be centred in the slit */

    if (sourceMode == CENTRED) {

      *elBotVShtr = el - openArc / 2.0 ;

/* Since the bottom shutter has a limited range of travel, make sure
 * the virtual shutter limit is achievable 
*/
      if (*elBotVShtr > ecsMaxBotShtr*D2R + ds) 
        *elBotVShtr = ecsMaxBotShtr*D2R + ds ;

      if (*elBotVShtr < ellimit)
        *elBotVShtr = ellimit ;

/* Now do same for the top virtual shutter */

      *elTopVShtr = el + openArc/2.0 ;

      if (*elTopVShtr > ecsMaxTopShtr*D2R - ds)
        *elTopVShtr = ecsMaxTopShtr*D2R - ds ;

    } else if (sourceMode == RISING) {

/* This section will calculate the demands when the enclosure is in
 * MinVibration or MinScatter mode and the target is rising
*/
      *elBotVShtr = el - del ;
      
      if (*elBotVShtr > ecsMaxBotShtr*D2R + ds) 
        *elBotVShtr = ecsMaxBotShtr*D2R + ds ;

      if (*elBotVShtr < ellimit)
        *elBotVShtr = ellimit ;

      *elTopVShtr = el - del + openArc ;

      if (*elTopVShtr > ecsMaxTopShtr*D2R - ds)
        *elTopVShtr = ecsMaxTopShtr*D2R - ds ;

    } else {                             /* The source is setting */

/* This section will calculate the demands when the enclosure is in
 * MinVibration or MinScatter mode and the target is setting. 
*/
      *elTopVShtr = el + del ;
      *elBotVShtr = *elTopVShtr - openArc ;

      if (*elBotVShtr > ecsMaxBotShtr*D2R + ds) 
        *elBotVShtr = ecsMaxBotShtr*D2R + ds ;

      if (*elBotVShtr < ellimit)
        *elBotVShtr = ellimit ;
    }

/* Now set the positions of the physical slit */

    *elTopShtr = *elTopVShtr + ds ;
    *elBotShtr = *elBotVShtr - ds ;

/* Due to method of calculating the virtual shutter edges, the physical
*  edges generated above should always be valid but check and clip just 
*  in case.
*/
    if (*elTopShtr > ecsMaxTopShtr*D2R)
      *elTopShtr = ecsMaxTopShtr*D2R ;

    if (*elTopShtr < ecsMinTopShtr*D2R)
      *elTopShtr = ecsMinTopShtr*D2R ;

    if (*elBotShtr > ecsMaxBotShtr*D2R) 
      *elBotShtr = ecsMaxBotShtr*D2R ;

    if (*elBotShtr < ecsMinBotShtr*D2R)
      *elBotShtr = ecsMinBotShtr*D2R ;

  }                                   /* End of tracking mode calculations */

    

}

/*+
 *   Function name:
 *   tcsEcsCheckParams
 *
 *   Purpose:
 *   Check user and default parameters for consistency
 *
 *   Description:
 *   Positioning of the dome and shutters requires a combination of 
 *   quasi-static data and user defined parameters. Both sets of data
 *   are modifiable via either a user command or the TCS engineering screens.
 *   To ensure that the data supplied is consistent, this routine is
 *   called and checked for a non-zero return. The main checks done are
 *   to ensure that the resultant effective width and height of the
 *   enclosure aperture are greater than zero. Range checking of the
 *   data will have been accomplished by the EPICS input records used.
 *
 *   Invocation:
 *   status = tcsEcsCheckParams (encMode, shtrMode, slitHeight, slitWidth, 
 *                               encRadius, beamDiameter, minScatWidth, 
 *                               fieldRadius, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  encMode (ENCMODE) BASIC, MINVIBRATION or MINSCATTER
 *      (>)  shtrMode (SHUTTERMODE) TRACKING or FULLYOPEN
 *      (>)  slitHeight (double) Physical slit height (mm)
 *      (>)  slitWidth (double) Physical slit width (mm)
 *      (>)  encRadius (double) Enclosure radius (mm)
 *      (>)  beamDiameter (double) Beam diameter on M1 (mm)
 *      (>)  minScatWidth (double) Adjustment for minimum scatter
 *      (>)  fieldRadius (double) Focal plane field radius (arcmin)
 *      (<)  mess       (char *)  Return message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *-
 */

int tcsEcsCheckParams (ENCMODE encMode, SHUTTERMODE shtrMode,
                       double slitHeight, double slitWidth,
                       double encRadius, double beamDiameter, 
                       double minScatWidth, double fieldRadius, char *mess)
{
  int status;             /* return status */
  double effWidth;        /* effective width of slit (mm) */
  double effHeight;       /* effective height of slit (mm) */
  double fieldAdj;        /* adjustment to slit size (mm) due to field */

  status = 0;
  strcpy (mess, " ");

  fieldAdj = 2.0 * fieldRadius * encRadius * DD2R / 60.0; 

/* If slitHeight is greater than the enclosure radius then you should be
*  operating in the fullyOpen mode.
*/

  if (shtrMode != FULLYOPEN) {
    if (slitHeight >= encRadius) {
      status = -1;
      strcpy (mess, "Slit height greater than dome radius");
      return status;
    }

    if (slitHeight < ecsMinSlitHeight) {
      status = -1 ;
      sprintf (mess, "Slit height < %.1f", ecsMinSlitHeight) ;
      return status ;
    }
  }

/* Compute the effective Width and height of the enclosure aperture 
*  dependent on the operating mode
*/

  if ((encMode == BASIC) || (encMode == MINVIBRATION)) {
   effWidth = slitWidth - beamDiameter - fieldAdj ;
   effHeight = slitHeight - beamDiameter - fieldAdj ;
  } else {
   effWidth = slitWidth - beamDiameter - fieldAdj - minScatWidth;
   effHeight = slitHeight - beamDiameter - fieldAdj - minScatWidth;
  }

  if (effWidth <= 0.0) {
   status = -1;
   strcpy (mess, "Effective slit width < 0.0");
   return status;
  }

  if (shtrMode != FULLYOPEN) {
    if (effHeight <= 0.0) {
      status = -1;
      strcpy (mess, "Effective slit height < 0.0") ;
      return status ;   
    }
  }

  return status;

}


/*+
 *   Function name:
 *   tcsEcsClearSlewFlag
 *
 *   Purpose:
 *   Clears the slew flag and returns is previous setting
 *
 *   Description:
 *   The algorithms for minimum scatter and minimum vibration need to know
 *   if the slew command has been given as part of a configuration. If it
 *   has then they know to do a full recalculation of the best position
 *   of the shutters and dome. This routine clears the slew flag if it
 *   is set and returns the current value to the calling application.
 *
 *   Invocation:
 *   slewIssued = tcsEcsClearSlewFlag()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   None
 *
 *   Function value:
 *   (<)  slewIssued  (int)  TRUE or FALSE 
 * 
 *   External functions:
 *   semMCreate     (semLib)     Create mutex semaphore
 *
 *-
 */

int tcsEcsClearSlewFlag (void)

{

  int currentFlag ;           /* Current slew flag */

/* Create the semaphore if it doesn't already exist */
  if (!ecsSemId) {
     ecsSemId = epicsMutexMustCreate();			   
  }

    epicsMutexLock(ecsSemId) ;
    currentFlag = ecsSlewFlag ;
    ecsSlewFlag = FALSE ;
    epicsMutexUnlock(ecsSemId) ;

  return currentFlag ;
}

/*+
 *   Function name:
 *   tcsEcsDump
 *
 *   Purpose:
 *   Dump ECS parameters to screen
 *
 *   Description:
 *   This is a diagnostic routine to print out the internally held parameters
 *   that control the positioning of the dome and shutters.
 *
 *   Invocation:
 *   tcsEcsDump()
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsEcsDump (void)

{
  char mode[40];

  printf ("\nEnclosure positioning parameters\n\n");

  if (ecsDomeEnabled)
    printf ("Commands from TCS to dome :     Enabled\n");
  else
    printf ("Commands from TCS to dome :     Disabled\n");

  if (ecsShtrsEnabled)
    printf ("Commands from TCS to shutters : Enabled\n");
  else
    printf ("Commands from TCS to shutters : Disabled\n");

  if (ecsIssueMoves)
    printf ("Commands issued will be moves\n");
  else
    printf ("Commands issued will be follows\n");

  printf("\n");

  switch (ecsShutMode) {
    case FULLYOPEN: 
        strcpy (mode, "Fully Open");
        break ;
    case TRACKING:
        strcpy (mode, "Tracking");
        break ;
    default:
        strcpy (mode, "Undefined");
  }

  printf ("Shutter operating mode:       %s\n", mode);

  switch (ecsEncMode) {
    case BASIC:
        strcpy (mode, "basic");
        break;
    case MINVIBRATION:
        strcpy (mode, "Minimum vibration");
        break ;
    case MINSCATTER:
        strcpy (mode, "Minimum scatter");
        break ;
    default:
        strcpy (mode, "Undefined");
  }

  printf ("Enclosure operating mode:     %s\n", mode);

  printf ("\n");

  printf ("Shutter limits: Bottom shutter %.1f to %.1f\n", ecsMinBotShtr,
          ecsMaxBotShtr);
  printf ("                Top shutter    %.1f to %.1f\n", ecsMinTopShtr,
          ecsMaxTopShtr);

  printf ("\n");

  printf ("Enclosure radius (mm)          :   %.1f\n", ecsEncRadius);
  printf ("Slit width (mm)                :   %.1f\n", ecsSlitWidth);
  printf ("Beam diameter at M1 (mm)       :   %.1f\n", ecsBeamDiameter);
  printf ("Adjustment for min scatter (mm):   %.1f\n", ecsMinScatWidth);
  printf ("Minimum slit height (mm)       :   %.1f\n", ecsMinSlitHeight);
  printf ("Current slit height (mm)       :   %.1f\n", ecsSlitHeight);
  printf ("Field radius (arcmin)          :   %.1f\n", ecsFieldRadius);
  printf ("\n");
  printf ("Effective slit width (mm)      :   %.1f\n", ecsPosnEffWidth);
  printf ("Effective slit height (mm)     :   %.1f\n", ecsPosnEffHeight);

}


/*+
 *   Function name:
 *   tcsEcsEnableDome
 *
 *   Purpose:
 *   Toggle flag to enable/disable automatic moves being sent to dome
 *
 *   Description:
 *   This routine is expected to be called by the follow and carouselMode
 *   commands once the input parameters to those commands have been
 *   checked and accepted. The parameter passed will be set to TRUE. This
 *   will cause the TCS to issue follow or move commands to the ECS when
 *   slewing to a new target i.e. the dome will follow the target. 
 *   The low-level engineering commands move_dome and park_dome call this
 *   routine with the parameter set to FALSE. 
 *
 *   Invocation:
 *   tcsEcsEnableDome (state)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  state  (int)  TRUE or FALSE
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsEcsEnableDome (int state) 

{
  ecsDomeEnabled = state ;
}

/*+
 *   Function name:
 *   tcsEcsEnableShtrs
 *
 *   Purpose:
 *   Toggle flag to enable/disable automatic moves being sent to shutters 
 *
 *   Description:
 *   This routine is expected to be called by the follow and carouselMode
 *   commands once the input parameters to those commands have been
 *   checked and accepted. The parameter passed will be set to TRUE. This
 *   will cause the TCS to issue follow or move commands to the ECS when
 *   slewing to a new target i.e. the shutters will open. 
 *   The low-level engineering commands move_shtrs and park_shtrs call this
 *   routine with the parameter set to FALSE. 
 *
 *   Invocation:
 *   tcsEcsEnableShtrs (state)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  state  (int)  TRUE or FALSE
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsEcsEnableShtrs (int state) 

{
  ecsShtrsEnabled = state ;
}

/*+
 *   Function name:
 *   tcsEcsGetEnableFlags 
 *
 *   Purpose:
 *   Fetch flags that indicate whehter dome and shutters are enabled
 *
 *   Description:
 *   This routine simply returns to the caller the state of the flags that
 *   determine whether the dome and shutters are enabled within the TCS.
 *   If the flags are set to false then no commands to drive the 
 *   mechanisms will be sent to the ECS.
 *
 *   Invocation:
 *   tcsEcsGetEnableFlags (&enabledDome, &enabledShtrs)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)   enabledDome  (int *) TRUE if dome is enabled
 *      (<)   enabledShtrs (int *) TRUE if shutters are enabled 
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsGetEnableFlags (int *enabledDome, int *enabledShtrs)

{

  *enabledDome = ecsDomeEnabled ;
  *enabledShtrs = ecsShtrsEnabled ;

}


/*+
 *   Function name:
 *   tcsEcsGetEncMode 
 *
 *   Purpose:
 *   Fetch enclosure operating mode
 *
 *   Description:
 *   Make the enclosure operating mode available to the calling routine
 *
 *   Invocation:
 *   tcsEcsGetEncMode (&encMode)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    encMode  (ENCMODE *) BASIC, MINVIBRATION or MINSCATTER
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsGetEncMode (ENCMODE *encMode)

{

  *encMode = ecsEncMode ;

}


/*+
 *   Function name:
 *   tcsEcsGetIssueMoves 
 *
 *   Purpose:
 *   Fetch the value of the flag ecsIssueMoves
 *   that controls whether Move or Follow commands should be sent to the ECS
 *
 *   Description:
 *   Simply copy the ecsIssueMoves flag from storage.
 *
 *   Invocation:
 *   tcsEcsGetIssueMoves (&issueMoves)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    issueMoves  (int *) 1 = Issue move commands, 0 = issue Follow
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsGetIssueMoves (int *issueMoves)

{

  *issueMoves = ecsIssueMoves ;

}

/*+
 *   Function name:
 *   tcsEcsGetParamDefs
 *
 *   Purpose:
 *   Get parameter defaults for the dome and shutter operating modes
 *
 *   Description:
 *   This routine is used to fetch the quasi-static parameters that are
 *   used to position the dome and shutters. These parameters are likely
 *   to be fixed at the time of commissioning but may differ between
 *   GemNorth and GemSouth
 *
 *   Invocation:
 *   tcsEcsGetParamDefs (&encRadius, &slitWidth, &beamDiameter, &minScatWidth,
 *                       &minSlitHeight, &fieldRadius)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)  encRadius (double *) Enclosure radius (mm)
 *      (<)  slitWidth (double *) Physical slit width (mm)
 *      (<)  beamDiameter (double *) Beam diameter at M1 (mm)
 *      (<)  minScatWidth (double *) Adjustment for minimum scatter
 *      (<)  minSlitHeight (double *) Minimum slit height in tracking mode
 *      (<)  fieldRadius (double*) Focal plane field radius (arcmin)
 *
 *   Function value:
 *   None.
 *
 *-
 */


void tcsEcsGetParamDefs (double *encRadius, double *slitWidth, 
                         double *beamDiameter, double *minScatWidth,
                         double *minSlitHeight, double *fieldRadius)

{
  *encRadius = ecsEncRadius;
  *slitWidth = ecsSlitWidth ;
  *beamDiameter = ecsBeamDiameter;
  *minScatWidth = ecsMinScatWidth;
  *minSlitHeight = ecsMinSlitHeight;
  *fieldRadius = ecsFieldRadius;

}

/*+
 *   Function name:
 *   tcsEcsGetPosnDefs
 *
 *   Purpose:
 *   Fetch current default positions of the dome and shutters
 *
 *   Description:
 *   Simply fetch the current defaults from storage. If a call to 
 *   tcsEcsSetPosnDefs has not been made previously then the defaults
 *   will be those set when the routine was loaded.
 *
 *   Invocation:
 *   tcsEcsGetPosnDefs (&domePos, &botShtrPos, &topShtrPos)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)  domePos (double *) Dome azimuth position (degs)
 *      (<)  botShtrPos (double *) Bottom shutter elevation (degs)
 *      (<)  topShtrPos (double *) Top shutter elevation (degs)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsGetPosnDefs (double *domePos, double *botShtrPos, 
                        double *topShtrPos)

{
  *domePos = ecsDefDomePos ;
  *botShtrPos = ecsDefBotShtr;
  *topShtrPos = ecsDefTopShtr;
}


/*+
 *   Function name:
 *   tcsEcsGetShutLimits
 *
 *   Purpose:
 *   Fetch the current shutter elevation limits
 *
 *   Description:
 *   This simple routine fetches the current enclosure shutter limits from 
 *   local storage in order to make them available to other functions. If
 *   tcsEcsSetShutLimits has not been called prior to this routine then 
 *   the values retrieved are default values.
 *
 *   Invocation:
 *   tcsEcsGetShutLimits (&minBotShtr, &maxBotShtr, &minTopShtr, &maxTopShtr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)   minBotShtr (double *) Min. elevation of bottom shutter (degs)
 *      (<)   maxBotShtr (double *) Max. elevation of bottom shutter (degs)
 *      (<)   minTopShtr (double *) Min. elevation of top shutter (degs)
 *      (<)   maxTopShtr (double *) Max. elevation of top shutter (degs)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsGetShutLimits (double *minBotShtr, double *maxBotShtr,
                          double *minTopShtr, double *maxTopShtr)

{
  *minBotShtr = ecsMinBotShtr;
  *maxBotShtr = ecsMaxBotShtr;
  *minTopShtr = ecsMinTopShtr;
  *maxTopShtr = ecsMaxTopShtr;
}


/*+
 *   Function name:
 *   tcsEcsGetUserParams
 *
 *   Purpose:
 *   Fetch user defined enclosure operating parameters
 *
 *   Description:
 *   This routine simply retrieves the parameters previously set by the user
 *   for control of the dome and shutters.
 *
 *   Invocation:
 *   tcsEcsGetUserParams (&encMode, &slitMode, &slitHeight)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<) encMode (ENCMODE *) Basic, MinVibration or MinScatter
 *      (<) slitMode (SHUTTERMODE *) FullyOpen or Tracking
 *      (<) slitHeight (double *)  Slit height in tracking mode
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsEcsGetUserParams (ENCMODE *encMode, SHUTTERMODE *slitMode, 
                          double *slitHeight)

{
  *encMode = ecsEncMode;
  *slitMode = ecsShutMode ;
  *slitHeight = ecsSlitHeight;
}	

/*+
 *   Function name:
 *   tcsEcsEffectiveSlitPosns
 *
 *   Purpose:
 *   Return the effecto slit edges i.e. the positions vignetting starts at 
 *
 *   Description:
 *   From the current actual slit edges compute the effective edges
 *   allowing for both the main beam diameter and the field radius
 *
 *   Invocation:
 *   tcsEcsEffectiveSlitPosns (currTopShtr, currBotShtr, &vTopShtr, &vBotShtr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>) currTopShtr (double) Current top shutter position (rads)
 *      (>) currBotShtr (double) Current bottom shutter position (rads)
 *      (<) vTopShtr (double *) Effective top shutter position (rads)
 *      (<) vBotShtr (double *) Effective bottom shutter position (rads)
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsEcsEffectiveSlitPosns (double currTopShtr, double currBotShtr, 
                          double *vTopShtr, double *vBotShtr)

{
  double ds;

  ds = asin ((ecsSlitHeight - ecsPosnEffHeight)/(2.0*ecsEncRadius)) ;

  *vTopShtr = currTopShtr - ds ;
  *vBotShtr = currBotShtr + ds ;
}	


/*+
 *   Function name:
 *   tcsEcsHaDec2AzEl
 *
 *   Purpose:
 *   Converts from HA and Dec to Azimuth and Elevation
 *
 *   Description:
 *   Applies standard spherical trigonometry formulae to convert from
 *   an input HA and Dec to azimuth and elevation. Azimuth and elevation
 *   are returned both as spherical and cartesian components. 
 *
 *   Invocation:
 *   tcsEcsHaDec2AzEl (ha, dec, clat, slat, &az, &el, &x, &y, &z)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   ha    (double)    HA (rads)
 *      (>)   dec   (double)    declination (rads)
 *      (>)   clat  (double)    Cos of latitude
 *      (>)   slat  (double)    Sin of latitude
 *      (<)   az    (double *)  Azimuth (rads)
 *      (<)   el    (double *)  Elevation (rads)
 *      (<)   x     (double *)  X component of az/el
 *      (<)   y     (double *)  Y component of az/el
 *      (<)   z     (double *)  Z component of az/el
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsEcsHaDec2AzEl (double ha, double dec, double clat, double slat,
                       double *az, double *el, double *x, double *y,
                       double *z )
{

  double cdec, sdec ;          /* Cos/Sin of declination */
  double cha, sha ;            /* Cos/sin of HA */

  cdec = cos(dec) ;
  sdec = sin(dec) ;
  cha  = cos(ha) ;
  sha  = sin(ha) ;

  *x = -cha * cdec * slat + sdec * clat ;
  *y = -sha * cdec ;
  *z = cha * cdec * clat + sdec * slat ;

  *az = slaDranrm ( (*x == 0.0 && *y == 0.0) ? 0.0 : atan2 (*y, *x)) ;
  *el = atan2 (*z , sqrt (*x * *x + *y * *y) ) ;

  return ;

}


/*+
 *   Function name:
 *   tcsEcsLimitTime 
 *
 *   Purpose:
 *   Return the time and type of the next enclosure limit
 *
 *   Description:
 *   Given a starting position and the orientation of the enclosure, the
 *   routine evaluates the position of the target at increasing times into
 *   the future. When the target is found to have hit a limit defined 
 *   by the edges of the slit and shutters, the type of limit and time
 *   taken to reach it are returned to the caller. 
 *
 *   Invocation:
 *   tcsEcsLimitTime (startHA, startDec, domeAz, elTopVShtr, elBotVShtr,
 *                    dHA, clat, slat, &limitType, &timeToLimit)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>) startHA    (double)  Start HA of track (rads)
 *      (>) startDec   (double)  Start declination of track (rads)
 *      (>) domeAz     (double)  Dome azimuth (rads)
 *      (>) elTopVShtr (double)  Elevation of edge of top shutter (rads)
 *      (>) elBotVShtr (double)  Elevation of edge of bottom shutter (rads)
 *      (>) dHA        (double)  Time step (rads)
 *      (>) clat       (double)  Cosine of site latitude 
 *      (>) slat       (double)  Sin of site latitude
 *      (<) limitType  (ENCLIMIT *) Enclosure limit type
 *      (<) timeToLimit (double *)  Time to limit (UT secs)
 *
 *   Function value:
 *   None
 * 
 *   External variables:
 *   (>)   ecsPosnEffWidth  (double)   Effective slit width (mm)
 *   (>)   ecsEncRadius     (double)   Enclosure radius (mm)
 *-
 */

void tcsEcsLimitTime (double startHA, double startDec, double domeAz,
                      double elTopVShtr, double elBotVShtr,
                      double dHA, double clat, double slat, 
                      ENCLIMIT *limitType, double *timeToLimit )

{
 double xUpper ;             /* X coord of edge of top shutter */
 double xLower ;             /* X coord of edge of lower shutter */
 double cosAzEnc, sinAzEnc ; /* Cos/Sin of dome azimuth */
 int finished ;              /* Flag for termination of while loop */
 double az;                  /* Azimuth (rads) of target */
 double el;                  /* Elevation (rads) of target */
 double x0, y0, z0;          /* Cartesian components of start position */
 double x, y, z ;            /* Cartesian components of current position */
 double x0p, y0p ;           /* x,y in rotated enclosure frame */
 double xp, yp ;             /* x,y in rotated enclosure frame */
 double ha ;                 /* current HA (rads) */
 double ylim;                /* Y coord of dome leading edge */
 int    maxSteps ;           /* Maximum number of steps before aborting */
 int nsteps ;                /* no. of steps so far */
 int dbgLevel ;

/* Initialse return data */
 *timeToLimit = 0.0 ;
 *limitType = INVALID ;

/* Initialise other variables */
 xUpper = cos (elTopVShtr) ;
 xLower = cos (elBotVShtr) ;
 cosAzEnc = cos (domeAz) ;
 sinAzEnc = sin (domeAz) ;
 finished = FALSE ;
 ha       = startHA ;
 ylim     = ecsPosnEffWidth / (2.0 * ecsEncRadius) ;
 maxSteps = PI2/dHA  + 10;
 nsteps   = 0 ;
 dbgLevel = DBG_NONE ;

/* Fetch x,y components of starting position */
 tcsEcsHaDec2AzEl (startHA, startDec, clat, slat, &az, &el, &x0, &y0, &z0) ;
 
/* Rotate into frame of enclosure */
 y0p = y0 * cosAzEnc - x0 * sinAzEnc ;
 x0p = y0 * sinAzEnc + x0 * cosAzEnc ;

/* If we are in a limit already then simply return, if not then step along
*  the track of the target until the first limit is hit.
*/

 *limitType = tcsEcsLimitType (x0p, y0p, ylim, xLower, xUpper) ;
 if (*limitType > NOLIMIT) {
   return ;
 } else {
   while (!finished) {

     tcsEcsHaDec2AzEl (ha, startDec, clat, slat, &az, &el, &x, &y, &z) ;
     yp = y * cosAzEnc - x * sinAzEnc ;
     xp = y * sinAzEnc + x * cosAzEnc ;
     *limitType = tcsEcsLimitType (xp, yp, ylim, xLower, xUpper) ;

     switch (*limitType) {
 
      case TOPSHTR :
           ha += dHA * (xp - xUpper)/ (x0p - xp) ;
           *timeToLimit = (ha - startHA) / UTST / S2R ;
           finished = TRUE ;
           break ;

      case BOTSHTR :
           ha += dHA * (xp - xLower) / (x0p - xp) ;
           *timeToLimit = (ha - startHA) / UTST / S2R;
           finished = TRUE ;
           break ;

      case LEADEDGE :
           ha += dHA * (yp - ylim) / (y0p - yp) ; 
           *timeToLimit = (ha - startHA) / UTST / S2R ;
           finished = TRUE ;
           break ;

      case TRAILEDGE :
           ha += dHA * (yp + ylim) / (y0p - yp) ;
           *timeToLimit = (ha - startHA) / UTST / S2R;
           finished = TRUE ;
           break ;

      default :
           x0p = xp ;
           y0p = yp ;
           ha += dHA ;
           nsteps++ ;
           *timeToLimit = (ha - startHA) / UTST / S2R ;
           if (*timeToLimit > 86400.0) {
             finished = TRUE ;
             *limitType = NOLIMIT ;
             *timeToLimit = 86400.0 ;
           }
           if (nsteps > maxSteps) {
             finished = TRUE ;
             *limitType = INVALID ;
             DBGMSG (DBG_NONE, "tcsEcsLimitTime: Error - did not converge") ;
           }

     }

   }                            /* end while */
 }

}

/*+
 *   Function name:
 *   tcsEcsLimitType
 *
 *   Purpose:
 *   Checks whether the current target position is in an enclosure limit
 *
 *   Description:
 *   This routine checks to see whether the current target position has
 *   exceeded the limits set by the leading and trailing edges of the 
 *   dome or by the edges of the top and bottom shutter.
 *
 *   Invocation:
 *   limitType = tcsEcsLimitType (x, y, ylim, xLower, xUpper)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   x      (double)  X component of target position
 *      (>)   y      (double)  Y component of target position
 *      (>)   ylim   (double)  Y limit of slit edge
 *      (>)   xLower (double)  X limit of lower shutter
 *      (>)   xUpper (double)  X limit of upper shutter
 *
 *   Function value:
 *   (<)  limitType (ENCLIMIT) Type of limit
 * 
 *-
 */

ENCLIMIT tcsEcsLimitType (double x, double y, double ylim, double xLower,
                         double xUpper)
{

  if (y >= ylim) 
    return LEADEDGE ;
  else if ( y <= -ylim) 
    return TRAILEDGE ;
  else if (x <= xUpper) 
    return TOPSHTR ;
  else if (x >= xLower) 
    return BOTSHTR ;
  else
    return NOLIMIT ;
 
}


/*+
 *   Function name:
 *   tcsEcsPrintLimit
 *
 *   Purpose:
 *   A wrapper for tcsEcsCalcLimit for test and debug purposes
 *
 *   Description:
 *   This routine simply acts as a wrapper for tcsEcsCalcLimit and
 *   tcsEcsLimitTime. It provides
 *   default values for some of the inputs and prints a summary in 
 *   user units of the return data. 
 *
 *   Invocation:
 *   tcsEcsPrintLimit (ha, dec)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    ha       (double)   Hour angle of target (hours)
 *      (>)    dec      (double)   Declination of target (degs)
 *      (>)    dt       (double)   Time step (secs)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   The routine tcsEcsSetParamDefs should have been called as this sets
 *   up the enclosure slit width and height data. In practice this means
 *   the CAD record carouselMode should have been executed. 
 *
 *   Deficiencies:
 *   The site latitude is hard coded for Gemini North. It would be better
 *   to fetch this from the TCS internal database.
 *-
 */

void tcsEcsPrintLimit (double ha, double dec, double dt)
{

  double cdec, sdec ;              /* Cosine and sine of declination */
  double lat = 19.826667 * D2R ;   /* Site latitude 19 49 36 */
  double ellim = 15.0 * D2R ;      /* Elevation limit (degs) */
  double slat, clat ;              /* Cos/sine of latitude */
  double startHA ;                 /* HA at start of track (rads) */
  double endHA ;                   /* HA at end of track (rads) */
  ENCLIMIT encLimit ;              /* Enclosure limit type */
  double timeToGo ;                /* Time to limit (UT secs) */
  double azDome ;                  /* Dome azimuth (rads) */
  double elTopShtr ;               /* Top shutter position (rads) */
  double elBotShtr ;               /* Bottom shutter position (rads) */
  double elTopVShtr ;              /* Top virtual shutter position (rads) */
  double elBotVShtr ;              /* Bottom virtual shutter position (rads) */
  double startDec ;                /* Input declination (rads) */
  int    limitStatus ;             /* Status from tcsLimEl */
  double dHA ;                     /* Time step (rads) */

/* Set up default inputs */

  slat = sin (lat) ;
  clat = cos (lat) ;

  cdec = cos(dec * D2R) ;
  sdec = sin(dec * D2R) ;

  startDec = dec * D2R ;
  startHA = ha * 3600.0 * S2R ;

  dHA = dt * S2R ;
 
/* Check user data for validity */
  limitStatus = tcsLimEl (cdec, sdec, ellim, clat, slat, &endHA) ;

  if (limitStatus == -1) {
    printf ("The target you have specified never rises\n") ;
    return ;
  } else if (limitStatus == 1) {
    endHA = startHA ;
  } else {
    if (startHA < -endHA) {
      startHA = -endHA ;
      printf ("Starting HA adjusted to time target rises\n");
    }
  }


/* Call routines and print results */

  tcsEcsCalcPosns (startHA, startDec, endHA, ellim, clat, slat, &azDome,
                   &elTopShtr, &elBotShtr, &elTopVShtr, &elBotVShtr ) ;
  tcsEcsLimitTime (startHA, startDec, azDome, elTopVShtr, elBotVShtr, dHA,
                  clat, slat, &encLimit, &timeToGo) ;

  printf ("Dome azimuth demand  %10.2f (degs)\n", azDome / D2R );
  printf ("Top shutter  demand  %10.2f (degs)\n", elTopShtr/D2R );
  printf ("Bottom shutter demand %10.2f (degs)\n\n", elBotShtr/D2R );
  printf ("Top virtual shutter demand  %10.2f (degs)\n", elTopVShtr/D2R );
  printf ("Bottom virtual shutter demand %10.2f (degs)\n\n", elBotVShtr/D2R );

  switch  (encLimit) {

    case INVALID :

       printf ("Warning - no valid limit was found\n") ;
       break ;

    case NOLIMIT :

       printf ("Target never hits a limit\n") ;
       break ;

    case TOPSHTR :

       printf (" Target hits top shutter after %10.1f secs\n", timeToGo);
       break ;
    
    case BOTSHTR :

       printf (" Target hits bottom shutter after %10.1f secs\n", timeToGo);
       break ;
    
    case LEADEDGE :
       printf (" Target hits leading slit edge after %10.1f secs\n", timeToGo);
       break ;
    
    case TRAILEDGE :

       printf (" Target hits trailing slit edge after %10.1f secs\n", timeToGo);
       break ;

     default :

       printf ("Error - unknown limit type\n");
       break ;

    }
    
  
}


/*+
 *   Function name:
 *   tcsEcsPrintVign
 *
 *   Purpose:
 *   Wrapper for testing tcsEcsVignette
 *
 *   Description:
 *   Take user input in degrees and call tcsEcsVignette. Print the 
 *   resulting vignette fraction.
 *
 *   Invocation:
 *   tcsEcsPrintVign (az, el, azDome, elTopShtr, elBotShtr )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   az      (int)  Target azimith (degs)
 *      (>)   el      (int)  Target elevation (degs)
 *      (>)   azDome  (int)  Dome azimuth (degs)
 *      (>)   elTopShtr (int) Elevation of top shutter (degs)
 *      (>)   elBotShtr (int) Elevation of bottom shutter (degs)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Arguments are passed as ints because with the powerPC you can't pass
 *   floats or doubles from the command line. This is a known bug in
 *   VxWorks.
 *
 *-
 */

void tcsEcsPrintVign (int az, int el, int azDome, int elTopShtr,
                      int elBotShtr)
{
  double vfrac ;      /* fractional vignetting */
  double azRad ;
  double elRad ;
  double azDomeRad, elTopShtrRad, elBotShtrRad ;

  azRad = az * D2R ;
  elRad = el * D2R ;
  azDomeRad = azDome *D2R ;
  elTopShtrRad = elTopShtr * D2R ;
  elBotShtrRad = elBotShtr * D2R ;

  tcsEcsVignette (azRad, elRad, azDomeRad, elTopShtrRad, elBotShtrRad,
                  &vfrac ) ;

  printf ("Vignette fraction is %6.2f\n", vfrac) ;
  printf ("Telescope az, el (degs)  %d %d\n", az, el);
  printf ("Dome azimith (degs) %d\n", azDome) ;
  printf ("Dome Limits top, bottom (degs) %d %d\n", elTopShtr, elBotShtr);

}


/*+
 *   Function name:
 *   tcsEcsSetIssueMoves
 *
 *   Purpose:
 *   Set whether to issue moves or follows to the ECS
 *
 *   Description:
 *   The TCS can control the ECS either by issuing a follow command and
 *   a continuous stream of data or by issuing periodic move commands.
 *   This routine sets the flag that determines which option will be used.
 *   The flag will be set to TRUE by the carouselMode command and FALSE
 *   by the follow command. At present it is expected that the follow
 *   command will not be used for the ECS. 
 *
 *   Invocation:
 *   tcsEcsSetIssueMoves (state)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    state     (int)     TRUE or FALSE
 *
 *   Function value:
 *   None.
 * 
 *-
 */


void tcsEcsSetIssueMoves (int state )

{
  ecsIssueMoves = state;
}

/*+
 *   Function name:
 *   tcsEcsSetParamDefs
 *
 *   Purpose:
 *   Set parameter defaults for the dome and shutter operating modes
 *
 *   Description:
 *   This routine is used to store the quasi-static parameters that are
 *   used to position the dome and shutters. These parameters are likely
 *   to be fixed at the time of commissioning but may differ between
 *   GemNorth and GemSouth. Note that different effective widths are 
 *   calculated for positioning the enclosure as compared to calculating
 *   the vignette fraction. This is to give a safety margin.
 *
 *   Invocation:
 *   tcsEcsSetParamDefs (encRadius, slitWidth, beamDiameter, minScatWidth,
 *                       minSlitHeight, fieldRadius)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  encRadius (double) Enclosure radius (mm)
 *      (>)  slitWidth (double) Physical slit width (mm)
 *      (>)  beamDiameter (double) Beam diameter at M1 (mm)
 *      (>)  minScatWidth (double) Adjustment for minimum scatter
 *      (>)  minSlitHeight (double) Minimum slit height in tracking mode
 *      (>)  fieldRadius (double) Focal plane field radius (arcmin)
 *
 *   Function value:
 *   None.
 *
 *   Prior requirements:
 *   To ensure consistent data, the function tcsEcsCheckParams must be
 *   called prior to this routine and return with a zero value.
 *
 *-
 */


void tcsEcsSetParamDefs (double encRadius, double slitWidth, 
                         double beamDiameter, double minScatWidth,
                         double minSlitHeight, double fieldRadius)

{
  double fieldAdj;      /* adjustment to slit size due to field of view */

  ecsEncRadius = encRadius;
  ecsSlitWidth = slitWidth ;
  ecsBeamDiameter = beamDiameter;
  ecsMinScatWidth = minScatWidth;
  ecsMinSlitHeight = minSlitHeight;
  ecsFieldRadius = fieldRadius;

/* derived parameters */

  fieldAdj = 2.0 * ecsFieldRadius * ecsEncRadius * DD2R / 60.0;

  if ((ecsEncMode == BASIC) || (ecsEncMode == MINVIBRATION))
  {
   ecsPosnEffWidth = ecsSlitWidth - ecsBeamDiameter - 2.0 * fieldAdj ;
   ecsPosnEffHeight = ecsSlitHeight - ecsBeamDiameter - 2.0 * fieldAdj ;
   ecsVignEffWidth = ecsPosnEffWidth + fieldAdj ;
   ecsVignEffHeight = ecsPosnEffHeight + fieldAdj ;
  }
  else
  {
   ecsPosnEffWidth = ecsSlitWidth - ecsBeamDiameter - 2.0 * fieldAdj - ecsMinScatWidth;
   ecsPosnEffHeight = ecsSlitHeight - ecsBeamDiameter - 2.0 * fieldAdj - ecsMinScatWidth;
   ecsVignEffWidth = ecsPosnEffWidth + fieldAdj ;
   ecsVignEffHeight = ecsPosnEffHeight + fieldAdj ;
  }

}

/*+
 *   Function name:
 *   tcsEcsSetPosnDefs
 *
 *   Purpose:
 *   Set a default position to which the TCS will drive the ECS
 *
 *   Description:
 *   This routine is called whenever it is required to set a default 
 *   position to which to drive the ECS. In particular, this routine is
 *   called at startup to ensure the TCS will drive the enclosure and
 *   shutters to their current positions.
 *
 *   Invocation:
 *   status = tcsEcsSetPosnDefs (domePos, botShtrPos, topShtrPos, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  domePos  (double)    Default dome azimuth (degs)
 *      (>)  botShtrPos (double)  Default bottom shutter elevation (degs)
 *      (>)  topShtrPos (double)  Default top shutter elevation (degs)
 *      (<)  mess       (char *)  Error message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK, -1 = error
 * 
 *-
 */

int tcsEcsSetPosnDefs (double domePos, double botShtrPos, double topShtrPos,
                       char *mess)

{
  int status ;
   
  status = 0;
  strcpy(mess, " ");

  if (( domePos >= 0.0) && (domePos <= 360.0))
  {
   ecsDefDomePos = domePos ;
  }
  else
  {
    strcpy(mess, "Invalid dome azimuth");
    status = -1;
  }

  if ((botShtrPos >= ecsMinBotShtr) && (botShtrPos <= ecsMaxBotShtr))
  {
   ecsDefBotShtr = botShtrPos;
  }
  else
  {
   strcpy (mess, "Invalid bottom shutter elevation");
   status = -1;
  }

  if ((topShtrPos >= ecsMinTopShtr) && (topShtrPos <= ecsMaxTopShtr))
  {
   ecsDefTopShtr = topShtrPos;
  }
  else
  {
   strcpy (mess, "Invalid top shutter elevation");
   status = -1;
  }

  return status;

}


/*+
 *   Function name:
 *   tcsEcsSetSlewFlag
 *
 *   Purpose:
 *   Set flag to show a slew is part of the current configuration
 *
 *   Description:
 *   This routine stores a flag to indicate that a slew command is part of
 *   the current configuration. This flag is read and cleared by the 
 *   tcsEcsClearSlewFlag routine which is called from tcsDriveECS
 *
 *   Invocation:
 *   tcsEcsSetSlewFlag
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *    None
 *
 *   Function value:
 *    None
 * 
 *   External functions:
 *   semGive        (semLib)    Give a semaphore
 *   semTake        (semLib)    Take a semaphore 
 *
 *   Prior requirements:
 *   tcsEcsClearSlewFlag which creates the semaphore if it doesn't already
 *   exist must be called before this routine.
 *
 *
 *-
 */

void tcsEcsSetSlewFlag (void) 
{

/* Create the semaphore if it doesn't already exist */
    if (!ecsSemId) {
       ecsSemId = epicsMutexMustCreate();			   
    }
   
    epicsMutexLock(ecsSemId) ;
    ecsSlewFlag = TRUE ;
    epicsMutexUnlock(ecsSemId) ;
}

/*+
 *   Function name:
 *   tcsEcsSetShutLimits
 *
 *   Purpose:
 *   Set the current shutter elevation limits
 *
 *   Description:
 *   This routine sets the current limits for both the top and bottom 
 *   enclosure shutters. Simple checks are done on the data to ensure that
 *   the maximum limit is greater than the minimum limit.
 *
 *   Invocation:
 *   status = tcsEcsSetShutLimits (minBot, maxBot, minTop, maxTop, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   minBot (double) Min. elevation of bottom shutter
 *      (>)   maxBot (double) Max. elevation of bottom shutter
 *      (>)   minTop (double) Min. elevation of top shutter
 *      (>)   maxTop (double) Max. elevation of top shutter
 *      (<)   mess   (char *) Error message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK ,-1 = error
 * 
 *-
 */

int tcsEcsSetShutLimits (double minBot, double maxBot, double minTop,
                         double maxTop, char *mess)

{
  int status ;                     /* Return status */
  
  strcpy(mess, " ");
  status = 0;

  if (minBot < maxBot)
  {
    ecsMinBotShtr = minBot;
    ecsMaxBotShtr = maxBot;
  }
  else
  {
    strcpy (mess, "Invalid lower shutter limits");
    status = -1;
  }

  if (minTop < maxTop)
  {
   ecsMinTopShtr = minTop;
   ecsMaxTopShtr = maxTop;
  }
  else
  {
    strcpy (mess, "Invalid top shutter limits");
    status = -1;
  }

  return status ;

}


/*+
 *   Function name:
 *   tcsEcsSetUserParams
 *
 *   Purpose:
 *   Store user defined parameters controlling the dome and shutter operating
 *   modes
 *
 *   Description:
 *   This routine simple stores the user definable parameters that control
 *   the dome and shutter operating modes. The slitHeight parameter is
 *   not used when the slitMode parameter is set to FullyOpen.
 *
 *   Invocation:
 *   tcsEcsSetUserParams (encMode, slitMode, slitHeight)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>) encMode (ENCMODE) BASIC, MINVIBRATION or MINSCATTER
 *      (>) slitMode (SHUTTERMODE) FULLYOPEN or TRACKING
 *      (>) slitHeight (double)   Slit height (mm)
 *
 *   Function value:
 *   None.
 * 
 *   Prior requirements:
 *   To ensure consistent data, the routine tcsEcsCheckParams should be
 *   called prior to this routine. Only if a return value of 0 is
 *   obtained should this routine then be called.
 *
 *-
 */


void tcsEcsSetUserParams (ENCMODE encMode, SHUTTERMODE slitMode, 
                          double slitHeight)
{
   double fieldAdj ;          /* Adjustment to slit due to field of view */

   ecsEncMode = encMode ;
   ecsShutMode = slitMode;
   ecsSlitHeight = slitHeight;

/* derived parameters */

  fieldAdj = 2.0 * ecsFieldRadius * ecsEncRadius * DD2R / 60.0;

  if ((ecsEncMode == BASIC) || (ecsEncMode == MINVIBRATION))
  {
   ecsPosnEffWidth = ecsSlitWidth - ecsBeamDiameter - 2.0 * fieldAdj ;
   ecsPosnEffHeight = ecsSlitHeight - ecsBeamDiameter - 2.0 * fieldAdj ;
   ecsVignEffWidth = ecsPosnEffWidth + fieldAdj ;
   ecsVignEffHeight = ecsPosnEffHeight + fieldAdj ;
  }
  else
  {
   ecsPosnEffWidth = ecsSlitWidth - ecsBeamDiameter - 2.0 * fieldAdj - ecsMinScatWidth;
   ecsPosnEffHeight = ecsSlitHeight - ecsBeamDiameter - 2.0 * fieldAdj - ecsMinScatWidth;
   ecsVignEffWidth = ecsPosnEffWidth + fieldAdj ;
   ecsVignEffHeight = ecsPosnEffHeight + fieldAdj ;
  }
}

/*+
 *   Function name:
 *   tcsEcsShowFlags
 *
 *   Purpose:
 *   Make enable/disable flags available to EPICS
 *
 *   Description:
 *   This record makes the enable/disable flags for the dome and shutters
 *   available on EPICS outputs. 
 *
 *   Invocation:
 *   tcsEcsShowFlags (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics output parameters:
 *
 *   vala => Dome enable/disable flag 
 *   valb => Shutters enable/disable flag
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsEcsShowFlags (struct genSubRecord *pgsub)

{
  int domeEnabled ;
  int shtrsEnabled ;

  tcsEcsGetEnableFlags (&domeEnabled, &shtrsEnabled) ;

  *(long *)pgsub->vala = domeEnabled ;
  *(long *)pgsub->valb = shtrsEnabled ;

  return 0;

}


/*+
 *   Function name:
 *   tcsEcsUpdateDefs
 *
 *   Purpose:
 *   Update the default parameters used in enclosure positioning
 *
 *   Description:
 *   This routine is attached to the updateEcsDefs EPICS routine. Whenever
 *   that record is processed this routine is called and the default 
 *   parameters used in the positioning of the dome and shutters are
 *   updated. These parameters are essentially fixed once they have been
 *   established at commissioning time but by allowing access through 
 *   EPICS records they are easily modifiable without requiring a 
 *   recompilaton. It may also be necessary to have slightly different
 *   values between GemNorth and GemSouth.
 *
 *   Invocation:
 *   tcsEcsUpdateDefs (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics input parameters:
 *
 *   a => Enclosure radius (mm)
 *   b => Slit width (mm)
 *   c => Beam diameter at M1 (mm)
 *   d => Adjustment for minimum scatter mode of operation (mm)
 *   e => Minimum slit height when tracking shutters (mm)
 *   f => Field radius (arcmin)
 *
 *   Epics output parameters:
 *
 *   vala => return message
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsEcsUpdateDefs (struct genSubRecord *pgsub)

{

  double encRadius ;           /* Enclosure radius (mm) */
  double slitWidth ;           /* Slit width (mm) */
  double beamDiameter ;        /* Beam diameter at M1 (mm) */
  double minScatWidth;         /* Adjustment for minimum scatter */
  double minSlitHeight;        /* Minimum slit height (mm) */
  double fieldRadius;          /* Radius of accessible field (arcmin) */

  ENCMODE encMode;             /* Enclosure operating mode */
  SHUTTERMODE slitMode;        /* Shutter operating mode */
  double slitHeight;           /* Slit height in tracking mode */

  char mess[40];               /* return message */

/* Access the latest data on the input links. Range checking is imposed
*  by the EPICS records that feed the gensub record to which this 
*  subroutine is attached
*/

  encRadius = *(double *)pgsub->a;
  slitWidth = *(double *)pgsub->b;
  beamDiameter = *(double *)pgsub->c;
  minScatWidth = *(double *)pgsub->d;
  minSlitHeight = *(double *)pgsub->e;
  fieldRadius = *(double *)pgsub->f;

/* Fetch the current user specified parameters */

  tcsEcsGetUserParams (&encMode, &slitMode, &slitHeight) ;

/* Check that the data is consistent */

  if (!tcsEcsCheckParams (encMode, slitMode, slitHeight, slitWidth, encRadius, 
      beamDiameter, minScatWidth, fieldRadius, mess) )
  {
    tcsEcsSetParamDefs (encRadius, slitWidth, beamDiameter, minScatWidth,
       minSlitHeight, fieldRadius) ;
  }

/* Output the returned message */

  strcpy (pgsub->vala, mess);

  return 0;

}


/*+
 *   Function name:
 *   tcsEcsVignette
 *
 *   Purpose:
 *   Calculates the percentage vignetting of the mirror by the enclosure
 *
 *   Description:
 *   The routine is passed the current azimuth and elevation of the mount
 *   together with the azimuth of the dome and elevations of the shutters.
 *   It then calculates how much, if any, of the entrance aperture of the 
 *   telescope is occluded by the enclosure. The fraction calculated is
 *   not exact but will be a good approximation to the true value.
 *
 *   Invocation:
 *   tcsEcsVignette (az, el, azDome, elTopShtr, elBotShtr, &vfrac)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  az    (double)  Current mount azimuth (rads)
 *      (>)  el    (double)  Current mount elevation (rads)
 *      (>)  azDome (double) Current dome azimuth (rads)
 *      (>)  elTopShtr (double) Current elevation of top shutter (rads)
 *      (>)  elBotShtr (double) Current elevation of bottom shutter (rads)
 *      (<)  vfrac  (double *)  Fraction of mirror vignetted
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   slaDcs2c       (slalib)      Trnasforms spherical to cartesian coords
 *
 *   Deficiencies:
 *   The calculation of the vignette fraction is not exact. It only 
 *   approximates the overlap fraction when both a shutter and dome 
 *   edge are contributing to the vignetting. Also, the calculation of
 *   the edge of the mirror is approximate. This means it is possible 
 *   at certain elevations and relative azimuths to claim 100% vignetting
 *   when in fact a small percentage of the mirror is clear. Conversely,
 *   it is also possible to claim 0% vignetting when in fact a small
 *   percentage is obscured. Due to the approximations used, this latter
 *   case is less common than the former. 
 *
 *-
 */

void tcsEcsVignette (double az, double el, double azDome, 
                     double elTopShtr, double elBotShtr, double *vfrac)

{
  double vec[3] ;       /* Cartesian vector for mount position */
  double cosAzDome ;
  double sinAzDome ;
  double xm, ym ;       /* Cartesian coords of mount in enclosure frame */
  double y1 ;           /* Coord of one edge of mirror */
  double y2 ;           /* Coord of other edge of mirror */
  double halfAp ;       /* Half width of entrance aperture (dimensionless) */
  double halfWidth ;    /* Half width of enclosure aperture (dimensionless) */
  double dy ;           /* Separation of mirror centre and slit edge */
  double dymod ;        /* modulus of dy */
  double theta ;        
  double apAdj ;        /* Adjustment to entrance aperture for field radius */
  double beamDiameter ; /* Beam diameter adjusted for field radius */
  double elTopfrac ;    /* Fractional vignetting by top shutter */
  double elBotfrac ;    /* Fractional vignetting by bottom shutter */
  double ymin, ymax ;   /* min/max of shutter edge */
  double dx ;           /* Temporary variable */
  double dxmod;         /* Modulus of dx */
  double elUpper ;      /* Elevation of top of mirror (rads) */
  double elLower ;      /* Elevation of bottom of mirror (rads) */

  
/* Convert mount az/el to cartesians using a right handed frame */

  slaDcs2c (az, el, vec);
  vec[0] = -vec[0];

/* Rotate x, y components into frame oriented with the dome */

  sinAzDome = sin (azDome) ;
  cosAzDome = cos (azDome) ;

  xm = vec[0] * cosAzDome - vec[1] * sinAzDome ;
  ym = vec[1] * cosAzDome + vec[0] * sinAzDome ;

/* Calculate edge of mirror in this frame */

  apAdj = 2.0 * ecsFieldRadius * ecsEncRadius * DD2R / 60.0;
  beamDiameter = ecsBeamDiameter + apAdj ;
  halfAp = beamDiameter / (2.0 * ecsEncRadius) ;
  y1 = ym + halfAp ;
  y2 = ym - halfAp ;

/* Estimate vignette fraction due to slit edges */

  halfWidth = ecsSlitWidth / (2.0 * ecsEncRadius) ;

  if ( (y2 >= halfWidth ) || (y1 <= -halfWidth)) {
    *vfrac = 1.0 ;
    return ;
  } else if ( (y1 < halfWidth) && (y1 > -halfWidth) &&
              (y2 < halfWidth) && (y2 > -halfWidth) ) {
    *vfrac = 0.0 ;
  } else if ( (y1 < halfWidth) && (y1 > -halfWidth)) {
    
    dy = halfWidth + ym ;
    dymod = dy ;
    if (dy < 0.0) dymod = -dy ;

    theta = acos (dymod/halfAp) ;
    *vfrac = (theta - sin (2.0 * theta)/2.0) / PI ;

/* Check to see if more than 50% vignetted and adjust fraction accordingly */

    if (dy < 0.0) *vfrac = 1 - *vfrac ;

  } else if ((y2 < halfWidth) && (y2 > -halfWidth)) {

/* This is the case where only y2 lies within the dome edges */

    dy = halfWidth - ym ; 
    dymod = dy;
    if (dy < 0.0) dymod = -dy ;

    theta = acos (dymod/halfAp) ;
    *vfrac = (theta - sin (2.0 * theta)/2.0) / PI ;

/* Check to see if more than 50% vignetted and adjust fraction accordingly */

    if (dy < 0.0) *vfrac = 1 - *vfrac ;

  } else {
 
    printf ("tcsEcsVignette: Invalid y limits %f %f %f\n", y1, y2, 
             halfWidth);
    *vfrac = 1.0 ;
    return ;
  }

/* Now calculate the vignette fraction due to the top and bottom shutters.
*  If the entrance aperture is already vignetted by the slit edges then
*  allowance must be made for any potential overlap.
*/

  elTopfrac = 0.0 ;
  elBotfrac = 0.0 ;

  if (*vfrac < 1.0) {

/* Calculate x position of top and bottom of the entrance aperature in the
*  frame of the enclosure.
*/
   elUpper = el + halfAp;
   elLower = el - halfAp;

/* Handle the case of the top shutter first */

   if (elLower >= elTopShtr) {  
     *vfrac = 1.0 ;
     return ;
   } else if (elUpper <= elTopShtr) {
     elTopfrac = 0.0 ;
   } else if ( (elLower < elTopShtr) && (elUpper > elTopShtr)) {
     dx = el - elTopShtr ;
     dxmod = dx ;
     if (dx < 0.0) dxmod = -dx ;
     
     theta = acos (dxmod/halfAp) ;
     elTopfrac = (theta - sin (2.0 * theta)/2.0) / PI ;

/* Check for more than 50% vignette */

     if (dx > 0.0) elTopfrac = 1.0 - elTopfrac ;

/* If there is already some vignetting due to the slit edges then adjust
*  the vignette fraction due to the top shutter to correct for any 
*  overlap 
*/
     if (*vfrac > 0.0) {

       ymin = ym - halfAp * sin (theta) ;
       ymax = ym + halfAp * sin (theta) ;

       if ((halfWidth > ymin) && (halfWidth < ymax) )
         elTopfrac = elTopfrac * (halfWidth - ymin) / (ymax - ymin) ;

       if ((-halfWidth > ymin) && (-halfWidth < ymax) )
         elTopfrac = elTopfrac * (ymax + halfWidth) / (ymax - ymin) ;
     } 

   } else {

     *vfrac = 1.0 ;
     printf ("tcsEcsVignette: Invalid el limits %f %f %f\n",
               elUpper, elLower, elTopShtr) ;
     return ;
   }

/* Now handle the bottom shutter similarly */

   if (elUpper <= elBotShtr) {
     *vfrac = 1.0 ;
     return ;
   } else if (elLower >= elBotShtr) {
     elBotfrac = 0.0 ;
   } else if ( (elUpper > elBotShtr) && (elLower < elBotShtr)) {
     dx = el - elBotShtr ;
     dxmod = dx ;
     if (dx < 0.0) dxmod = -dx ;

     theta = acos (dxmod/halfAp) ;
     elBotfrac = (theta - sin (2.0 * theta)/2.0) / PI ;

/* Check for more than 50% vignette */

     if (dx < 0.0) elBotfrac = 1.0 - elBotfrac ;

/* If there is already some vignetting due to the slit edges then adjust
*  the vignette fraction due to the bottom shutter to correct for any 
*  overlap 
*/
     if (*vfrac > 0.0) {

       ymin = ym - halfAp * sin (theta) ;
       ymax = ym + halfAp * sin (theta) ;

       if ((halfWidth > ymin) && (halfWidth < ymax) )
         elBotfrac = elBotfrac * (halfWidth - ymin) / (ymax - ymin) ;

       if ((-halfWidth > ymin) && (-halfWidth < ymax) )
         elBotfrac = elBotfrac * (ymax + halfWidth) / (ymax - ymin) ;

     } 


   } else {

     *vfrac = 1.0 ;
     printf ("tcsEcsVignette: Invalid el limits %f %f %f\n",
              elUpper, elLower, elBotShtr) ;
     return ;
   }
     


  }

/* Finally add together all the vignette fractions. To allow for possible
*  rounding errors clip the fraction at 1.0
*/

  *vfrac = *vfrac + elTopfrac + elBotfrac ;
  if (*vfrac > 1.0) *vfrac = 1.0 ;

}
epicsRegisterFunction(tcsEcsShowFlags);
epicsRegisterFunction(tcsEcsUpdateDefs);
