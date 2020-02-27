/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsLimits.c
*
*   FUNCTION NAME(S)
*   tcsLimits - Check source position against telescope limits
*   tcsLimAzel2Hadec - Converts Az/El to HA/Dec
*   tcsLimEl - Computes hour angle of elevation limit
*   tcsLimPa - Computes hour angle of position angle limit
*
*/
/*
 * $Log:
*/
/* *INDENT-ON* */


#include <slalib.h>
#include <astLib.h>
#include "tcsLimits.h"
#include "tcsConstants.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimits
 *
 *   Purpose:
 *   Checks limits before sending new source demands to Mount etc.
 *
 *   Description:
 *   At present only the simplest elevation limit is calculated to test the
 *   operation of the CAD/CAR records. The additional functionality of
 *   azimuth wrap, rotator and blind spot limits can easily be added later
 *
 *   Invocation:
 *   tcsLimits ( frame, ellimit, ra, dec, lat,  st, &ttr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)    frame    (FRAMETYPE) Coordinate frame
 *      (>)    ellimit  (double)    Elevation limit
 *      (>)    ra       (double)    RA
 *      (>)    dec      (double)    Dec
 *      (>)    lat      (double)    Telescope latitude
 *      (>)    st       (double)    Siderial time
 *      (<)    ttr      (double)    Time to rise
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
 *
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */


int tcsLimits(FRAMETYPE frame, double ellimit, double ra, double dec,
              double lat, double st, double *ttr)
{
    double maxarg = 0.99999999; /* Max. value of arg */
    double arg;                 /* argument of elevation limit formula */
    double ha;                  /* HA of source (rads) */
    double risetime;            /* HA source rises (rads) */
    double settime;             /* HA source sets (rads) */
    double ctimetorise;         /* Time to rise above elevation limit */
    int cLimitError;            /* Error code for limit */
    double dec_never_rises;
    double dec_never_sets;

/* First check co-ordinate system, then check if any limit is reached then
 * finally if the source is up at the moment
 */

    ctimetorise = 0.0;          /* Initialise to make sure it gets set */
    cLimitError = NO_LIMIT;

    /* source input was Az/El */
    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        if (dec < ellimit)
            cLimitError = BELOW_EL_LIMIT;
        else
            cLimitError = NO_LIMIT;
    } else {                    /* Source input was RA/Dec */
        dec_never_rises = lat + ellimit - PI / 2;
        dec_never_sets = PI / 2 + ellimit - lat;

        if (dec < dec_never_rises)
            cLimitError = NEVER_RISES;
        else if (dec > dec_never_sets)
            cLimitError = NO_LIMIT;
        else {
            arg = (sin(ellimit) - sin(dec) * sin(lat)) / (cos(dec) * cos(lat));
            if (arg < -maxarg)
                settime = PI;
            else if (arg > maxarg)
                settime = 0;
            else
                settime = acos(arg);
            risetime = -settime;
            ha = slaDrange(st - ra);
            if (ha > risetime && ha < settime)
                cLimitError = NO_LIMIT;
            else {
                cLimitError = BELOW_HORIZON;
                ctimetorise = (risetime - ha) / UTST;
                if (ctimetorise < 0.0)
                    ctimetorise = ctimetorise + PI2;
            }
        }
    }
/*  Return function value limit error and timetorise parameter */

    *ttr = ctimetorise;
    return cLimitError;
}

void tcsLimAzel2Hadec( double x0, double y0, double z0, 
   double clat, double slat, double *ha, double *dec)
{
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimAzel2Hadec
 *
 *   Purpose:
 *   Convert Az/El to hour angle and declination
 *
 *   Description:
 *   Converts an Az/El expressed as a vector into an hour angle and
 *   declination.
 *
 *   Invocation:
 *   tcsLimAzel2Hadec( x, y, z, &ha, &dec);
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    x0       (double)   X component of Az/El
 *      (>)    y0       (double)   Y component of Az/El
 *      (>)    z0       (double)   Z component of Az/El
 *      (>)    clat     (double)   cosine of latitude
 *      (>)    slat     (double)   sine of latitude
 *      (<)    ha       (double*)  Hour angle
 *      (<)    dec      (double*)  Declination
 *
 *   Function value:
 *      none
 * 
 *   External functions:
 *      none
 *
 *   External variables:
 *      none
 *
 *   Prior requirements:
 *      none
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

   double x1, y1, z1;

/* To HA/Dec cartesian */
   x1 = x0 * slat + z0 * clat;
   y1 = y0;
   z1 = - x0 * clat + z0 * slat;

/* To spherical */
   *ha =   - ( x1 == 0.0 && y1 == 0.0 ? 0.0 : atan2( y1, x1) );
   *dec = atan2( z1, sqrt( x1 * x1 + y1 * y1) );
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimEl
 *
 *   Purpose:
 *   Returns the hour angle at which a star at a given declination sets
 *
 *   Description:
 *   Deterimines whether a star reaches a given elevation, and if it does
 *   returns the hour angle at which the star sets.
 *
 *   Invocation:
 *   istat = tcsLimEl( cdec, sdec, el, clat, slat, &ha);
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    cdec     (double)   cosine declination of object
 *      (>)    sdec     (double)   sine declination of object
 *      (>)    el       (double)   elevation limit
 *      (>)    clat     (double)   cosine of latitude
 *      (>)    slat     (double)   sine of latitude
 *      (<)    ha       (double*)  hour angle of setting
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
 *                                     -1 = never rises
 *                                     +1 = never sets
 * 
 *   External functions:
 *   none
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *   none
 *
 *   Deficiencies:
 *   Fails if clat = 0 (a telescope on the equator)
 *
 *-
 */
/* *INDENT-ON* */

int tcsLimEl( double cdec, double sdec, double el, double clat, double slat, 
   double *ha)
{
   double gamma;

/* dec +/-90 are a special case to avoid divide by zero */
   if ( cdec == 0.0 ) {
      if ( sdec > 0.0 && slat > 0.0 ) return 1;
      else return -1;
   }

   gamma = ( sin( el ) - sdec * slat ) / ( cdec * clat );
   if ( gamma < -1.0 )
      return 1;             /* never sets */
   else if ( gamma > 1.0 ) 
      return -1;            /* never rises */
   else
      *ha = acos( gamma );
   return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimAz
 *
 *   Purpose:
 *   Returns the hour angle at which a star at a given declination reaches
 *   a given azimuth.
 *
 *   Description:
 *   Determines whether a star reaches a given azimuth, and if it does
 *   returns the hour angle at which it reaches it.
 *
 *   Invocation:
 *   istat = tcsLimAz( cdec, sdec, al, clat, slat, ha);
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    cdec     (double)   cosine declination of object
 *      (>)    sdec     (double)   sine declination of object
 *      (>)    al       (double)   azimuth limit
 *      (>)    clat     (double)   cosine of latitude
 *      (>)    slat     (double)   sine of latitude
 *      (<)    ha[2]    (double)   hour angles of setting
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Number of hour angles
 * 
 *   External functions:
 *   none
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *   none
 *
 *   Deficiencies:
 *   Fails if slat = 0 (a telescope at the N or S pole) and al = PI/2.
 *
 *-
 */
/* *INDENT-ON* */

int tcsLimAz( double cdec, double sdec, double al, double clat, double slat, 
   double ha[2])
{
   double a, b, t, h1, h2;
   double sal, cal, asinab;
   int i;

   sal = sin( al );
   cal = cos( al );
   a = sdec * sal * clat;
   b = cdec * sqrt( cal * cal + sal * sal * slat *slat );

   if ( fabs(a) > fabs(b) || b == 0.0 ) return 0;

   t = atan2( sal * slat, - cal);

   asinab = asin( a / b );
   h1 = slaDrange( asinab - t );
   h2 = slaDrange( PI - ( asinab + t ) );

   i = 0;
   if ( ( sal > 0.0 && h1 < 0.0 ) || ( sal < 0.0 && h1 > 0.0 ) ) ha[i++] = h1;
   if ( ( sal > 0.0 && h2 < 0.0 ) || ( sal < 0.0 && h2 > 0.0 ) ) ha[i++] = h2;

   return i;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimPa
 *
 *   Purpose:
 *   Returns the hour angle at which a star at a given declination reaches
 *   a given parallactic angle.
 *
 *   Description:
 *   Determines whether a star reaches a given parallactic angle, and if 
 *   it does returns the hour angle at which it reaches it.
 *
 *   Invocation:
 *   istat = tcsLimPa( cdec, sdec, ap, clat, slat, &ha);
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    cdec     (double)   cosine declination of object
 *      (>)    sdec     (double)   sine declination of object
 *      (>)    pl       (double)   parallactic angle limit
 *      (>)    clat     (double)   cosine of latitude
 *      (>)    slat     (double)   sine of latitude
 *      (<)    ha[2]    (double)   hour angle of setting
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Number of hour angles.
 * 
 *   External functions:
 *   none
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *   none
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

int tcsLimPa( double cdec, double sdec, double pl, double clat, double slat, 
   double ha[2])
{
   int i;
   double a, b, t, h1, h2;
   double spl, cpl, asinab;

   spl = sin( pl );
   cpl = cos( pl );
   a = slat * spl * cdec;
   b = clat * sqrt( cpl * cpl + spl * spl * sdec *sdec );

   if ( fabs(a) > fabs(b) || b == 0 ) return 0;

   t = atan2( spl * sdec, cpl);

   asinab = asin( a / b );
   h1 = slaDrange( asinab - t );
   h2 = slaDrange( PI - ( asinab + t ) );

   i = 0;
   if ( ( spl > 0.0 && h1 > 0.0 ) || ( spl < 0.0 && h1 < 0.0 ) ) ha[i++] = h1;
   if ( ( spl > 0.0 && h2 > 0.0 ) || ( spl < 0.0 && h2 < 0.0 ) ) ha[i++] = h2;

   return i;
}
