/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsCotran.c
*
*   FUNCTION NAME(S)
*   tcsCtOffToSph - Converts an offset to spherical coordinates
*   tcsCtSphToOff - Converts an offset to input form
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */



#include <string.h>
#include <slalib.h>
#include "tcsConstants.h"
#include "tcsCotran.h"
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - - - -
**   t c s C t O f f T o S p h
**  - - - - - - - - - - - - - -
**
**  Transform an offset from its data-entry form to its tracking form.
**
**  Given:
**    frame     FRAMETYPE  source frame
**    p0        double[2]  reference position (radians)
**    coord     OFFCOORD   offset coordinate type
**    dtheta1   double     offset in RA or azimuth
**    dtheta1   double     offset in Dec or elevation
**
**  Returned (arguments):
**    tar_ob    double[2]  offset in spherical coordinates (radians)
**
**  Returned (function value):
**              int      0 = OK
**
**  Called:
**
**  Notes:
**
**    1  The units of theta1 and theta2 depend on both the source frame
**       and the offset coordinates: if the coordinate frame is AZEL_MNT 
**       or AZEL_TOPO then theta1 & theta2 are in degrees otherwise theta2
**       is in arcsec and theta1 is either in arcsec (coord is TANGENT_PLANE)
**       or seconds of time (coord in RADEC).
**
**
**  D.L.Terrett   23 October 1996
**
**  Copyright RAL 1996.  All rights reserved.
*/
/* *INDENT-ON* */

int tcsCtOffToSph(FRAMETYPE frame, double p0[], OFFCOORD coord,
                  double dtheta1, double dtheta2, double tar_ob[])
{
    double theta1;
    double theta2;

/*  Convert offsets to radians */
    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        dtheta1 *= D2R;
        dtheta2 *= D2R;
    } else {
        if (coord == RADEC)
            dtheta1 *= S2R;
        else
            dtheta1 *= AS2R;
        dtheta2 *= AS2R;
    }

/* Convert from tangent plane to spherical */
    if (coord == TANPLANE) {
        slaDtp2s(dtheta1, dtheta2, p0[0], p0[1], &theta1, &theta2);
        tar_ob[0] = theta1 - p0[0];
        tar_ob[1] = theta2 - p0[1];
    } else {
        tar_ob[0] = dtheta1;
        tar_ob[1] = dtheta2;
    }

    return 0;
}
/* *INDENT-OFF* */
/*
**  - - - - - - - - - - - - - -
**   t c s C t O f f T o S p h
**  - - - - - - - - - - - - - -
**
**  Transform an offset from its tracking form to its data-entry form.
**
**  Given:
**    frame     FRAMETYPE  source frame
**    p0        double[2]  reference position (radians)
**    coord     OFFCOORD   offset coordinate type
**    tar_ob    double[2]  offset in spherical coordinates (radians)
**
**  Returned (arguments):
**    dtheta1   double     offset in RA or azimuth
**    dtheta1   double     offset in Dec or elevation
**
**  Returned (function value):
**              int      0 = OK
**
**  Called:
**
**  Notes:
**
**    1  The units of theta1 and theta2 depend on both the source frame
**       and the offset coordinates: if the coordinate frame is AZEL_MNT 
**       or AZEL_TOPO then theta1 & theta2 are in degrees otherwise theta2
**       is in arcsec and theta1 is either in arcsec (coord is TANGENT_PLANE)
**       or seconds of time (coord in RADEC).
**
**
**  D.L.Terrett   5 December 1996
**
**  Copyright RAL 1996.  All rights reserved.
*/
/* *INDENT-ON* */

int tcsCtSphToOff(FRAMETYPE frame, double p0[], OFFCOORD coord,
                  double tar_ob[], double *dtheta1, double *dtheta2)
{
    double theta1;
    double theta2;
    int j;

/* Convert from spherical to tangent plane */
    if (coord == TANPLANE) {
        theta1 = tar_ob[0] + p0[0];
        theta2 = tar_ob[1] + p0[1];
        slaDs2tp(theta1, theta2, p0[0], p0[1], dtheta1, dtheta2, &j);
    } else {
        *dtheta1 = tar_ob[0];
        *dtheta2 = tar_ob[1];
    }

/*  Convert offsets to input units */
    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        *dtheta1 /= D2R;
        *dtheta2 /= D2R;
    } else {
        if (coord == RADEC)
            *dtheta1 /= S2R;
        else
            *dtheta1 /= AS2R;
        *dtheta2 /= AS2R;
    }

    return 0;
}
