/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsSkySimulation.c
*
*   FUNCTION NAME(S)
*   tcsSkyGetProbe - Gets guide probe x/y positions.
*   tcsSkySimulate - Writes simulated sky data
*   tcsSkyGetStars - Reads catalogue of stars
*   tcsSkyGenStars - Fakes catalogue of stars
*   tcsSkyDisplayCat - Writes catalogue info to output links
*
*/
/*
 * $Log: tcsSkySimulation.c,v $
 * Revision 1.7  2006/04/21 12:58:44  cjm
 * Major rework to restore and extend functionality
 *
 * Revision 1.6  2001/04/17 15:58:50  cjm
 * Add defaults to setting of guide star separation
 *
 * Revision 1.5  1999/03/24 03:30:07  dlt
 * Change sub to gensub
 *
 * Revision 1.4  1999/03/22 22:11:41  dlt
 * Rotator inputs now in degrees & and scale WFS probe positions
 *
 * Revision 1.3  1998/11/19 21:13:35  cjm
 * MCS now supplies positions etc. in degress rather than rads.
 *
 * Revision 1.2  1998/11/14 00:15:32  dlt
 * Add IA and IE
 *
 * Revision 1.1.1.1  1998/11/08 00:21:11  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.17  1998/02/10 08:32:43  cjm
 * Pull in m2Scale via EPICS rather than by subroutine
 *
 * Revision 1.16  1998/01/13 17:07:20  tcs
 * Initialise number of stars to zero
 *
 * Revision 1.15  1998/01/08 16:41:35  cjm
 * Respond to measuring state of WFS
 *
 */
/* *INDENT-ON* */

#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <string.h>
#include <genSubRecord.h>
#include <slalib.h>
#include "slamac.h"
#include <timeLib.h>
#include <astLib.h>
#include "tcsConstants.h"
#include "tcsRandom.h"

#define MAX_STARS 20
#define MAX_LINE_LEN 256

double Pwfs1x = 0.0;         /* PWFS1 x position */
double Pwfs1y = 0.0;         /* PWFS1 x position */
double Pwfs2x = 0.0;         /* PWFS2 x position */
double Pwfs2y = 0.0;         /* PWFS2 x position */
double Oiwfsx = 0.0;         /* OIWFS x position */
double Oiwfsy = 0.0;         /* OIWFS x position */
int Nstars = 0;              /* Number of stars in database */
struct star {
     double ra;
     double dec;
     double mag;
     double wavel;
} StarData[MAX_STARS];       /* Star data */
double Ca, Ce;               /* Collimation corrections */
double Dca = 0.0, Dce = 0.0; /* Collimation correction adjustments */
double GuideX = 0.0;         /* Net guiding correction (x arcsec) */
double GuideY = 0.0;         /* Net guiding correction (y arcsec) */
double Dx = 0.0 ;            /* Seeing adjustments to star positions (") */
double Dy = 0.0 ;            /* Seeing adjustments to star positions (") */

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSkyGetProbe
 *
 *   Purpose:
 *   Fetches the guide probe x/y positions.
 *
 *   Description:
 *   The x/y positions of the guide probes and OIWFS are read from the
 *   input links and stored in the sky simulation global memory and
 *   CA and CE are updated to simulate the telescope drifting. Any
 *   collimation corrections due to tilts or translations of M1 or
 *   translations of M2 are also allowed for.
 *
 *   Invocation:
 *   tcsSkyGetProbe( pgsub );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *)  pointer to genSubRecord structure
 *
 *   Epics inputs:
 *
 *   a => X position of PWFS1 (mm)
 *   b => Y position of PWFS1 (mm)
 *   c => X position of PWFS2 (mm)
 *   d => Y position of PWFS2 (mm)
 *   e => X position of OIWFS (mm)
 *   f => Y position of OIWFS (mm)
 *   g => Base ca (arcsec)
 *   h => base ce (arcsec)
 *   i => Mount oscillation amplitude ce (arcsec)
 *   j => Optics ca (arcsec)
 *   k => Optics ce (arcsec)
 *   l => Rms seeing amplitude (arcsecs)
 *   m => Sampling time (s) for new direction
 *   n => Period of mount oscillations (secs)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External variables:
 *   (<)   Pwfs1x    (double)    PWFS1 x position
 *   (<)   Pwfs1y    (double)    PWFS1 y position
 *   (<)   Pwfs2x    (double)    PWFS2 x position
 *   (<)   Pwfs2y    (double)    PWFS2 y position
 *   (<)   Oiwfsx    (double)    OIWFS x position
 *   (<)   Oiwfsy    (double)    OIWFS y position
 *   (<)   Ca        (double)    CA
 *   (<)   Ce        (double)    CE
 *   (<)   Dca       (double)    CA adjustment
 *   (<)   Dce       (double)    CE adjustment
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *   There is no attempt to extrapolate the probe positions to the same 
 *   time as the rest of the data in global memory because the probes are
 *   assumed to move relatively slowly.
 *
 *-
 */
/* *INDENT-ON* */

long tcsSkyGetProbe( struct genSubRecord *pgsub )
{
    double ca_base;              /* Base value of CA (arcsec) */
    double ce_base;              /* Base value of CE (arcsec) */
    double oscamp ;              /* Mount oscillation amplitude (arcsec) */
    double oscperiod ;           /* Mount oscillation period (secs) */
    static double oscphase ;     /* Oscillation phase (rads) */
    double caOpt ;               /* Optics model contribution to CA (arcsec) */
    double ceOpt ;               /* Optics model contribution to CE (arcsec) */
    static int first = 1 ;       /* Flag for first call of this routine */
    static double prevDx ;       /* Previous x seeing offset (arcsec) */
    static double prevDy ;       /* Previous y seeing offset (arcsec) */
    static double nextDx ;       /* Next x seeing offset (arcsec) */
    static double nextDy ;       /* Next y seeing offset (arcsec) */
    static int dirCount ;
    double seeing ;              /* Rms seeing (arcsecs) */

    seeing = *(double *)pgsub->l;

/* Initialize time dependent data */
    if (first) {
      prevDx = (double)tcsGresid((float)seeing);
      prevDy = (double)tcsGresid((float)seeing);
      nextDx = (double)tcsGresid((float)seeing);
      nextDy = (double)tcsGresid((float)seeing);
      oscphase = 0.0;
      first = 0 ;
    }


/* Check if its time to resample the seeing. Note we assume we are processing
*  once every 0.2s. We should really check this
*/
    dirCount++ ;
    dirCount = dirCount % (int)(*(double *)pgsub->m/0.2);
    if (!dirCount) {
      prevDx = nextDx ;
      prevDy = nextDy ;
      nextDx = (double)tcsGresid((float)seeing);
      nextDy = (double)tcsGresid((float)seeing);
    }

    if (*(double *)pgsub->m > 0.0) {
      Dx = prevDx + (nextDx - prevDx) * dirCount * 0.2 / *(double *)pgsub->m ;
      Dy = prevDy + (nextDy - prevDy) * dirCount * 0.2 / *(double *)pgsub->m ;
    } else {
      Dx = 0.0;
      Dy = 0.0;
    }

    Pwfs1x = *(double *)pgsub->a;
    Pwfs1y = *(double *)pgsub->b;
    Pwfs2x = *(double *)pgsub->c;
    Pwfs2y = *(double *)pgsub->d;
    Oiwfsx = *(double *)pgsub->e;
    Oiwfsy = *(double *)pgsub->f;

/* Initial values of CA & CE  */
    ca_base = *(double *)pgsub->g;
    ce_base = *(double *)pgsub->h;

/* Mount oscillation amplitude (only affects ce) */
    oscamp = *(double *)pgsub->i;
    oscperiod = *(double *)pgsub->n ;
    if (oscperiod > 0.0) {
      oscphase += 0.2*D2PI/oscperiod ; 
      if (oscphase > D2PI) oscphase -= D2PI ;
    } else {
      oscphase = 0.0;
    }

    Dca = 0.0;
    Dce = oscamp*sin(oscphase);

/* ca/ce due to optics */
    caOpt = *(double *)pgsub->j;
    ceOpt = *(double *)pgsub->k;

/* Compute new CA & CE */
    Ca = (ca_base + Dca + caOpt) * AS2R;
    Ce = (ce_base + Dce + ceOpt) * AS2R;

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSkySimulate
 *
 *   Purpose:
 *   Write simulate sky data to output link
 *
 *   Description:
 *   Write the data necessary to plot a simulated view of the sky and
 *   other paraphernalia in the focal plane (in the coordinate frame of
 *   the rotator).
 *
 *   Epics inputs:
 *
 *   a => M2 scale factor
 *   b => time stamp
 *   c => mount azimuth (degs)
 *   d => mount elevation (degs)
 *   e => tube flexure (arcsec)
 *   f => rotator position time stamp
 *   g => rotator position (degs)
 *   h => rotator velocity (degs/s)
 *   i => m2 x tilt (arcsec)
 *   j => m2 y tilt (arcsec)
 *   k => PWFS1 measuring state (0/1)
 *   l => PWFS2 measuring state (0/1)
 *   m => OIWFS measuring state (0/1)
 *   n => NICI measuring state (0/1)
 *   o => Data array for converting az/el to mount etc. 
 *   q => Open loop M2 scan demand
 *   r => Open loop M2 scan demand
 *
 *   Epics outputs:
 *
 *   The output array contains the following data:
 *   [0]  Rotator position angle
 *   [1]  Bearing of North from y axis
 *   [2]  M2 tip/tilt x
 *   [3]  M2 tip/tilt y
 *   [4]  mount pointing origin x
 *   [5]  mount pointing origin y
 *   [6]  source chop state A pointing origin x
 *   [7]  source chop state A pointing origin y
 *   [8]  source chop state B pointing origin x
 *   [9]  source chop state B pointing origin y
 *   [10] source chop state C pointing origin x
 *   [11] source chop state C pointing origin y
 *   [12] PWFS1 x
 *   [13] PWFS1 y
 *   [14] PWFS2 x
 *   [15] PWFS2 y
 *   [16] OIWFS x
 *   [17] OIWFS y
 *   [17+2*n]   Star n x
 *   [17+2*n+1] Star n y
 *
 *   valb => X guide error
 *   valc => Y guide error
 *   vald => PWFS1 guide data
 *   vale => PWFS2 guide data
 *   valf => OIWFS guide data
 *   valg => NICI guide data 
 *
 *   Invocation:
 *   tcsSkySimulate( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  pointer to subRecord structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   astGetpo      (astlib)     Gets current pointing origins
 *   astGetCtx     (astlib)     Get current context
 *   astCts2tr     (astlib)     Get transformation from context
 *   astInvtr      (astlib)     Invert transformation
 *   astS2xyq      (astlib)     Convert spherical coordinate to x/y
 *   slaDcmpf      (slalib)     Compute bearing
 *
 *   External variables:
 *   (>)   Ca          (double)    CA
 *   (>)   Ce          (double)    CE
 *   (>)   Pwfs1x      (double)    PWFS1 x position
 *   (>)   Pwfs1y      (double)    PWFS1 y position
 *   (>)   Pwfs2x      (double)    PWFS2 x position
 *   (>)   Pwfs2y      (double)    PWFS2 y position
 *   (>)   Oiwfsx      (double)    OIWFS x position
 *   (>)   Oiwfsy      (double)    OIWFS y position
 *   (>)   StarData    (double)    Star catalogue
 *   (!)   GuideX    (double)    Guiding correction (x)
 *   (!)   GuideY    (double)    Guiding correction (y)
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsSkySimulate( struct genSubRecord *pgsub)
{
    struct PO po;                 /* pointing origin structure */
    double *valap = pgsub->vala;  /* pointer to vala array of pgsub */
    double *vnp = pgsub->o ;      /* Pointer to o array of pgsub */
    struct WCS_CTX ctx;           /* world coordinate context */
    struct EPOCH eqx;             /* equinox of positions */
    struct WCS wcs;               /* x/y to spherical transformation */
    int wfs;                      /* active wave front sensor */
    double x,y;                   /* focal plane x/y */
    int i, j;                     /* loop index */
    double time;                  /* ast context timestamp */
    double bearing;               /* bearing of North from y axis */
    double xz, yz, xs, ys, perp;  /* not used */
    double spa, cpa;              /* sine and cosine of rotator angle */
    double az, el;                /* Az/El of telescope */
    double ie;                    /* Index error */
    double timeStamp;             /* Timestamp of mount Az/El */
    double rma;                   /* Rotator position angle */
    double rmav;                  /* Rotator velocity */
    double rmat;                  /* Rotator position timestamp */
    double dx, dy;                /* Guide star offset */
    double m2Scale;               /* Convert sky to m2 units */
    long p1Measuring ;            /* PWFS1 active flag */
    long p2Measuring ;            /* PWFS2 active flag */
    long oiMeasuring ;            /* OIWFS active flag */
    long niciMeasuring;           /* NICI active flag */
    double xtilt, ytilt ;         /* Open loop M2 demands */
    double ia_net ;               /* Total index error in azimuth */
    double vd ;                   /* Vertical deflection */
    double ae2mt[3][3] ;          /* Az/el to mount matrix */
    double xf, yf, zf;
    double x0, y0, z0 ;
    double z ;
    double r;
    double cvd ;                  /* Cos of vertical deflection */
    double f ;
    double rsq ;                  /* Squared error */
    double p1rsq, p2rsq, oirsq ;  /* Squared WFS error */
    double p1Data[8] ;            /* PWFS1 guiding data */
    double p2Data[8] ;            /* PWFS2 guiding data */
    double oiData[8] ;            /* OIWFS guiding data */
    double niciData[8] ;          /* NICI guiding data */

/* Check if there is an active WFS. For this simulation, when there are
 * multiple active WFS, the order of precedence is PWFS1, PWFS2, OIWFS
 */
    p1Measuring = *(long *)pgsub->k ;
    p2Measuring = *(long *)pgsub->l ;
    oiMeasuring = *(long *)pgsub->m ;
    niciMeasuring = *(long *)pgsub->n;
    wfs = 0;
    if (oiMeasuring) wfs = 3 ;
    if (p2Measuring) wfs = 2 ;
    if (p1Measuring) wfs = 1 ;

/* Fetch open loop M2 model */
    xtilt = *(double *)pgsub->q;
    ytilt = *(double *)pgsub->r;

/* Get the latest world coordinate context */
    astGetctx( &ctx );

/* Get the Az/el to mount matrix and subsidiary information */
   for (i = 0; i < 3; i++) {
     for (j = 0; j < 3; j++) {
       ae2mt[i][j] = *vnp++;
     }
   }
   ia_net = *vnp++;
   ie     = *vnp++;
   vd     = *vnp++;

/* Set equinox to J2000 */
    eqx.year = 2000.0;
    eqx.type = 'J';

/* Fetch M2 scaling parameter */
    m2Scale = *(double *)pgsub->a ;

/* Update the sidereal time in the ast context to match the time stamp of
   the mount Az/El. */
    timeStamp = *(double *)pgsub->b;
    timeThenR(timeStamp, LAST, &ctx.aoprms[13]);

/* Replace Az/El in ast context with actual mount position adjusted for
   tube flexture and index errors. */
    az = *(double *)pgsub->c*DD2R;
    el = *(double *)pgsub->d*DD2R;
    az -= ia_net;
    el += ie ;
    xf = -cos(el)*cos(az);
    yf = cos(el)*sin(az);
    zf = sin(el);

/* Rotate to az/el */
    x = ae2mt[0][0]*xf + ae2mt[1][0]*yf + ae2mt[2][0]*zf;
    y = ae2mt[0][1]*xf + ae2mt[1][1]*yf + ae2mt[2][1]*zf;
    z = ae2mt[0][2]*xf + ae2mt[1][2]*yf + ae2mt[2][2]*zf;

/* Remove vertical deflection */
    if ( (r = sqrt(x*x + y*y) ) > 0.0) {
      cvd = 1.0 - vd*vd / 2.0;
      f = cvd + vd * z / r ;
      x *= f;
      y *= f;
      z = z * cvd - vd*r ;
    }

/* Rotate back to mount */
    x0 = ae2mt[0][0]*x + ae2mt[0][1]*y + ae2mt[0][2]*z;
    y0 = ae2mt[1][0]*x + ae2mt[1][1]*y + ae2mt[1][2]*z;
    z0 = ae2mt[2][0]*x + ae2mt[2][1]*y + ae2mt[2][2]*z;

/* Finally, update context */
    ctx.ab0[0] = (x0 == 0.0 && y0 == 0.0) ? 0.0 : atan2(y0, -x0);
    ctx.ab0[1] = atan2( zf, sqrt(x0*x0+y0*y0));

/* Replace the rotator position angle in the ast context with the actual
   rotator position extrapolated to the mount timestamp. */
    rmat = *(double *)pgsub->f;
    rma = *(double *)pgsub->g*DD2R;
    rmav = *(double *)pgsub->h*DD2R;
    ctx.tel.rma = rma + rmav * ( timeStamp - rmat );

/* Replace CA & CE in ast context with "drifting" values */
    ctx.tel.ca += Ca;
    ctx.tel.ce += Ce;

/* Replace chop A tip/tilt with actual values from M2 */
    ctx.m2xy[0][0] = (*(double *)pgsub->i - xtilt) / m2Scale * AS2R;
    ctx.m2xy[0][1] = (*(double *)pgsub->j - ytilt) / m2Scale * AS2R;

/* Compute WCS transformation for FK5 */
    astCtx2tr( ctx, FK5, eqx, 0.55, 0, &wcs, &time);

/* Invert the transformation */
    astInvtr( wcs, &wcs);

/* Calculate bearing of North from y axis */
    slaDcmpf(wcs.coeffs, &xz, &yz, &xs, &ys, &perp, &bearing);

/* Output rotator position angles wrt y axis and North */
    *valap++ = ctx.tel.rma;
    *valap++ = bearing;

/* Output M2 tip/tilt */
    spa = sin( ctx.tel.rma );
    cpa = cos( ctx.tel.rma );
    x = - ctx.m2xy[0][0] * ctx.tel.fl;
    y = - ctx.m2xy[0][1] * ctx.tel.fl;
    *valap++ = x * cpa - y * spa;
    *valap++ = x * spa + y * cpa;

/* Output pointing origins */
    astGetpo( &po );
    *valap++ = po.mx;
    *valap++ = po.my;
    *valap++ = po.ax;
    *valap++ = po.ay;
    *valap++ = po.bx;
    *valap++ = po.by;
    *valap++ = po.cx;
    *valap++ = po.cy;

/* Output guide probe positions */
    *valap++ = Pwfs1x;
    *valap++ = Pwfs1y;
    *valap++ = Pwfs2x;
    *valap++ = Pwfs2y;
    *valap++ = Oiwfsx;
    *valap++ = Oiwfsy;

/* For each Star */
    *(double *) pgsub->valb = 0.0;
    *(double *) pgsub->valc = 0.0;
    p1rsq = p2rsq = oirsq = 1000000.0;
    for (i = 0; i< 8; i++) {
      p1Data[i] = 0.0;
      p2Data[i] = 0.0;
      oiData[i] = 0.0;
      niciData[i] = 0.0;
    }
    p1Data[0] = p2Data[0] = oiData[0] = niciData[0] = timeStamp;
    p1Data[1] = p2Data[1] = oiData[1] = niciData[1] = 3.0;

    for ( i = 0; i < Nstars; i++) {

/* Compute x/y in the focal plane */
        if ( astS2xyq( StarData[i].ra, StarData[i].dec, wcs, &x, &y) ) {
            x = 1000.0;
            y = 1000.0;
        } else {
            x += Dx/(AS2R*ctx.tel.fl);
            y += Dy/(AS2R*ctx.tel.fl);
        }

/* Check for star adjacent to the active guide probe */
        if ( wfs ) {
            switch (wfs) {
            case 1:
                dx = Pwfs1x - x;
                dy = Pwfs1y - y;
                break;
            case 2:
                dx = Pwfs2x - x;
                dy = Pwfs2y - y;
                break;
            case 3:
                dx = Oiwfsx - x;
                dy = Oiwfsy - y;
                break;
            default :
                dx = 0.0 ;
                dy = 0.0 ;
                break ;
            }
            if ( ( dx < 5.0 && dx > -5.0 ) && ( dy < 5.0 && dy > -5.0 ) ) {

/* Update guide star displacement in M2 coordinates */
               dx = - dx / ctx.tel.fl * m2Scale / AS2R;
               dy = - dy / ctx.tel.fl * m2Scale / AS2R;
               GuideX = dx * cpa + dy * spa;
               GuideY =  - dx * spa + dy * cpa;

/* Output guiding corrections */
               *(double *) pgsub->valb = GuideX;
               *(double *) pgsub->valc = GuideY;
            }
        }

/* Generate guiding data for all active probes. This may eventually 
*  replace the code above 
*/
       if (p1Measuring) {
         dx = Pwfs1x - x;
         dy = Pwfs1y - y;
         rsq = dx*dx + dy*dy ;
         if (rsq < p1rsq && rsq < 25.0) {
           dx = - dx / ctx.tel.fl * m2Scale / AS2R;
           dy = - dy / ctx.tel.fl * m2Scale / AS2R;
           p1Data[2] = dx * cpa + dy * spa;
           p1Data[3] =  - dx * spa + dy * cpa;
           p1rsq = rsq ;
         }
       }
           
       if (p2Measuring) {
         dx = Pwfs2x - x;
         dy = Pwfs2y - y;
         rsq = dx*dx + dy*dy ;
         if (rsq < p2rsq && rsq < 25.0) {
           dx = - dx / ctx.tel.fl * m2Scale / AS2R;
           dy = - dy / ctx.tel.fl * m2Scale / AS2R;
           p2Data[2] = dx * cpa + dy * spa;
           p2Data[3] =  - dx * spa + dy * cpa;
           p2rsq = rsq ;
         }
       }
           
/* Handle NICI and OIWFS together as probe control is the same for both
*  although the data comes out on different links.
*/
       if (oiMeasuring || niciMeasuring) {
         dx = Oiwfsx - x;
         dy = Oiwfsy - y;
         rsq = dx*dx + dy*dy ;
         if (rsq < oirsq && rsq < 25.0) {
           dx = - dx / ctx.tel.fl * m2Scale / AS2R;
           dy = - dy / ctx.tel.fl * m2Scale / AS2R;
           if (oiMeasuring) {
             oiData[2] = dx * cpa + dy * spa;
             oiData[3] =  - dx * spa + dy * cpa;
           }
           if (niciMeasuring) {
             niciData[2] = dx * cpa + dy * spa;
             niciData[3] =  - dx * spa + dy * cpa;
           }
           oirsq = rsq ;
         }
       }
           
/* Output star x/y */
        *valap++ = x;
        *valap++ = y;
    }

/* Output guiding data */
    memcpy(pgsub->vald, p1Data, 8 * sizeof(double));
    memcpy(pgsub->vale, p2Data, 8 * sizeof(double));
    memcpy(pgsub->valf, oiData, 8 * sizeof(double));
    memcpy(pgsub->valg, niciData, 8 * sizeof(double));

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSkyGetStars
 *
 *   Purpose:
 *   Reads a catalogue of stars into global memory
 *
 *   Description:
 *   A file name is read from the input links and the contents of the
 *   file loaded into the global memory. Depending on the format of the
 *   file, the data is either treated as containing absolute RA, Decs 
 *   (the default) or relative RA, Decs. The advantage of relative 
 *   RA, Decs is that you don't have to keep generating or finding new
 *   catalogues every time you slew to a new target. Whether the 
 *   catalogue is treated as relative or absolute depends on the 
 *   presence of the word "Offsets" before the first star position.
 *
 *   Invocation:
 *   tcsSkyGetStars( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct pgsubRecord *)  pointer to subRecord structure
 *
 *   Epics inputs:
 *   a =>  RA of science target (degs)
 *   b =>  Dec of science target (degs)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External variables:
 *   (<)   StarData    (struct stars)     Star positions
 *   (<>   Nstars      (int)              Number of stars in catalogue
 *   (<)   Dca       (double)    CA adjustment
 *   (<)   Dce       (double)    CE adjustment
 *   (<)   GuideX    (double)    Guiding correction (x)
 *   (<)   GuideY    (double)    Guiding correction (y)
 *
 *-
 */
/* *INDENT-ON* */

long tcsSkyGetStars( struct genSubRecord *pgsub)
{
    FILE *file;
    char line[MAX_LINE_LEN];
    int nstrt;
    int j;
    double ra0, dec0 ;       /* RA/Dec of science target */
    int offsetline ;         /* Flag set if last line contained "offsets" */
    int nc ;                 /* No. of characters in line */
    int relative = 0 ;       /* Flag for relative/absolute positions */

/* Fetch RA Dec of science target. Only used for relative positions */
    ra0 = *(double *)pgsub->a * D2R;
    dec0 = *(double *)pgsub->b * D2R;

/* Open the input file */
    file = fopen( (char*)pgsub->j, "r");
    if ( file ) {

/* Clear the database */
        Nstars = 0;

/* Read in the stars a line at a time */
        while ( fgets( line, MAX_LINE_LEN, file) && Nstars < MAX_STARS ) {

            offsetline = 0;
            nc = strlen(line);

/* Skip empty lines and comments (assumes terminated by newline) */
            if (nc > 1 && line[0] != '#') { 

/* Are the positions absolute or relative ? */
              if (Nstars == 0 ) {
                if (!strncmp(line, "Offsets", 7) || 
                    !strncmp(line, "offsets", 7) ) {
                  offsetline = 1;
                  relative = 1;
                }
              }

/* Decode the star */
              if (!offsetline) {
                printf ("%s", line);
                nstrt = 1;
                slaDafin( line, &nstrt, &StarData[Nstars].ra, &j);
                if (j) {
                  printf("Star cat error: line %d, bad RA\n", Nstars);
                  break;
                }
                if (relative) { 
                  StarData[Nstars].ra = StarData[Nstars].ra*15.0 + ra0;
                  if (StarData[Nstars].ra > D2PI)
                    StarData[Nstars].ra -= D2PI ;
                  if (StarData[Nstars].ra < 0.0)
                    StarData[Nstars].ra += D2PI;
                } else {
                  StarData[Nstars].ra *= 15.0;
                }
                slaDafin( line, &nstrt, &StarData[Nstars].dec, &j);
                if (j) {
                  printf("Star cat error: line %d, bad Dec\n", Nstars);
                  break;
                }
                if (relative) {
                  StarData[Nstars].dec += dec0 ;
                  if (StarData[Nstars].dec > DPIBY2) {
                    StarData[Nstars].dec = DPI - StarData[Nstars].dec;
                    if (StarData[Nstars].ra > DPI)
                      StarData[Nstars].ra -= DPI;
                    else
                      StarData[Nstars].ra += DPI;
                  }
                  if (StarData[Nstars].dec < -DPIBY2) {
                    StarData[Nstars].dec = -DPI - StarData[Nstars].dec;
                    if (StarData[Nstars].ra > DPI)
                      StarData[Nstars].ra -= DPI;
                    else
                      StarData[Nstars].ra += DPI;
                  }
                }
                  
                StarData[Nstars].mag = 18.0;
                slaDfltin( line, &nstrt, &StarData[Nstars].mag, &j);
                if (j > 1) {
                  printf("Star cat error: line %d, bad magnitude\n", Nstars);
                  break;
                }
                StarData[Nstars].wavel = 0.55;
                slaDfltin( line, &nstrt, &StarData[Nstars].wavel, &j);
                if (j > 1) {
                  printf("Star cat error: line %d, bad wavelength\n", Nstars);
                  break;
                }

/* Increment the star count */
                Nstars++;
              }
           }
        }

/* Close the file */
        fclose( file );

    } else {
      printf("Failed to open/find catalgue file\n");
    }

/* Zero the collimation drifts */
    Dca = Dce = 0.0;

/* Zero the guiding corrections */
    GuideX = GuideY = 0.0;

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSkyDisplayCat
 *
 *   Purpose:
 *   Writes star catalogue information to output links
 *
 *   Description:
 *
 *   Invocation:
 *   tcsSkyDisplayCat( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct pgsubRecord *)  pointer to subRecord structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *
 *   External variables:
 *   (>)   StarData    (struct starxs)    Star positions
 *   (>)   Nstars      (int)              Number of stars in catalogue
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsSkyDisplayCat( struct genSubRecord *pgsub)
{
    double *valbp = pgsub->valb;  /* pointer to valb array of pgsub */
    double *valcp = pgsub->valc;  /* pointer to valc array of pgsub */
    int j;

/* Write the number of stars loaded to output link */
    *(long *)pgsub->vala = Nstars;

    for ( j = 0; j < Nstars; j++ ) {

    /* magnitude */
        *valbp++ = StarData[j].mag;

    /* wavelength */
        *valcp++ = StarData[j].wavel;
    }


    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsSkyGenStars
 *
 *   Purpose:
 *   Generates a catalogue of stars
 *
 *   Description:
 *
 *   Invocation:
 *   tcsSkyGenStars( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct pgsubRecord *)  pointer to subRecord structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *
 *   External variables:
 *   (<)   StarData    (struct starxs)    Star positions
 *   (<>   Nstars      (int)              Number of stars in catalogue
 *   (<)   Dca       (double)    CA adjustment
 *   (<)   Dce       (double)    CE adjustment
 *   (<)   GuideX    (double)    Guiding correction (x)
 *   (<)   GuideY    (double)    Guiding correction (y)
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsSkyGenStars( struct genSubRecord *pgsub)
{

#define FIELD  (1200.0 * DAS2R)

    double xi, eta;
    char c;
    int hmsf[4], dmsf[4];
    int i;
    double tai;
    double sep;

    StarData[0].ra = *(double*)pgsub->a * D2R;
    StarData[0].dec = *(double*)pgsub->b * D2R;
    Nstars = *(long*)pgsub->c;
    Nstars = ( Nstars <= 0 || Nstars > 20 ) ? 20 : Nstars;
    StarData[0].mag = 18.0;

    timeNow(&tai);
    srand((int)tai);
    for ( i = 1; i < Nstars; i++ ) {
        xi = (double)rand() * FIELD / RAND_MAX - FIELD / 2.0;
        eta = (double)rand() * FIELD / RAND_MAX - FIELD / 2.0;
        xi *= (double)rand() / RAND_MAX;
        eta *= (double)rand() / RAND_MAX;
        slaDtp2s( xi, eta, StarData[0].ra, StarData[0].dec, 
                  &StarData[i].ra, &StarData[i].dec);
        if ( i < 5 ) StarData[i].mag = 19.0;
        else if ( i < 10 ) StarData[i].mag = 20.0;
        else if ( i < 15 ) StarData[i].mag = 21.0;
        else StarData[i].mag = 22.0;
        StarData[i].wavel = 0.55;
    }
    for ( i = 0; i < Nstars; i++ ) {
        slaDr2tf(1, StarData[i].ra, &c, hmsf);
        if (hmsf[0] == 24) {
           hmsf[1] = 0;
           hmsf[2] = 0;
           hmsf[3] = 0;
        }
        if (c == '-') hmsf[0] = 24 - hmsf[0];
        slaDr2af(1, StarData[i].dec, &c, dmsf);
        sep = slaDsep(StarData[0].ra, StarData[0].dec, StarData[i].ra,
           StarData[i].dec);
        printf("%2d %2d %2d.%1d %c%2d %2d %2d.%1d (%d)\n", hmsf[0], hmsf[1],
               hmsf[2], hmsf[3], c, dmsf[0], dmsf[1], dmsf[2], dmsf[3],
               (int)(sep/AS2R));
    }

/* Zero the collimation drifts */
    Dca = Dce = 0.0;

/* Zero the guiding corrections */
    GuideX = GuideY = 0.0;

    return 0;
}
epicsRegisterFunction(tcsSkyGenStars);
epicsRegisterFunction(tcsSkySimulate);
epicsRegisterFunction(tcsSkyDisplayCat);
epicsRegisterFunction(tcsSkyGetStars);
epicsRegisterFunction(tcsSkyGetProbe);
