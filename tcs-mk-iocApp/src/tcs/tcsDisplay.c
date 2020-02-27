/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsDisplay.c
*
*   Code to output TCS status items for display purposes;
*   these routines handle items which are only available in
*   global memory rather than EPICS fields or where
*   special computation is required before display is possible
*
*   FUNCTION NAME(S)
*   tcsCalcNaRange    - compute range to sodium layer
*   tcsCheckTime      - input an MJD and generate UTC and LST
*   tcsDisplayAirmass - compute zenith distance and airmass
*   tcsDisplayTime - compute local time and LAST as strings for display
*   tcsDisplayRADec - output demand positions in appropriate units
*   tcsDisplayEqx - output formatted equinox
*   tcsLimitDisplay - display limit error
*
*/
/*
 * $Log: tcsDisplay.c,v $
 * Revision 1.15  2015/06/12 12:36:29  cjm
 * Ensure zenith distance is always positive
 *
 * Revision 1.14  2013/05/20 12:20:52  cjm
 * Add routine tcsDisplayTelescopeRADec
 *
 * Revision 1.13  2013/05/09 22:31:11  gemvx
 * calculate currentRA and currentDec using non-timestamped MCS PMAC position data (REL-1252)
 *
 * Revision 1.12  2011/04/27 12:24:06  cjm
 * Add diagnostic routine tcsCheckTime
 *
 * Revision 1.11  2002/10/02 08:18:36  cjm
 * Add routine to compute range to Na layer
 *
 * Revision 1.10  2002/05/12 23:28:36  cjm
 * Add calculation of parallactice angle
 *
 * Revision 1.9  2001/05/18 10:40:28  cjm
 * Replace mosub record with gensub
 *
 * Revision 1.8  2001/01/15 11:38:01  dlt
 * Additional argument to tcsGetTrack
 *
 * Revision 1.7  2000/08/07 07:56:41  cjm
 * Change format of date and time strings
 *
 * Revision 1.6  2000/05/09 08:08:00  cjm
 * Calculate HA of sourceA in tcsDisplayTime
 *
 * Revision 1.5  1999/06/29 05:00:06  cjm
 * Modify to cope with new MCS data array of timestamp, position and velocity for each axis
 *
 * Revision 1.4  1999/02/08 10:28:40  cjm
 * Rotator positions now in degs. rather than rads. and changes to accommodate genSub rahter than a mosub record
 *
 * Revision 1.3  1998/12/07 11:24:33  epics
 * Add leading zero to RA
 *
 * Revision 1.2  1998/11/19 21:22:38  cjm
 * Modify to cope with inputs from mount in degs. rather than rads.
 *
 * Revision 1.1.1.1  1998/11/08 00:21:04  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.6  1998/05/18 13:22:19  tcs
 * remove leading spaces from time display
 *
 * Revision 1.5  1998/04/22 12:55:21  tcs
 * Format angles with colons
 *
 * Revision 1.4  1997/09/24 07:14:45  cjm
 * New routine tcsDisplayAirmass
 *
 * Revision 1.3  1997/06/09 15:54:59  tcs
 * Create tcsDisplay.h
 *
 * Revision 1.2  1997/05/16 12:21:37  tcs
 * make consistent use of frame/wavel/eqx
 *
 * Revision 1.1  1997/02/10 17:10:32  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.14  1997/01/03 11:18:47  tcs
 * change AZEL_MOUNT to AZEL_MNT
 *
 * Revision 1.13  1996/12/20 16:14:26  tcs
 * improve formatting of equinox
 *
 * Revision 1.12  1996/12/13 11:25:13  tcs
 * cosmetic improvements
 *
 * Revision 1.11  1996/12/13 10:07:48  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.10  1996/11/08 11:57:26  tcs
 * add display of frame and equinox
 *
 * Revision 1.9  1996/11/04 08:14:44  cjm
 * Ensure strings don't over run their buffers
 *
 * Revision 1.8  1996/10/24 14:55:56  cjm
 * Restore RA/Dec Az/El labelling
 *
 * Revision 1.7  1996/08/23 13:06:39  cjm
 * Generate Az/RA strings for display
 *
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>

#include "slalib.h"
#include "timeLib.h"
#include "tcsConstants.h"
#include "tcsPointing.h"
#include "tcsDisplay.h"
#include "astLib.h"
/* *INDENT-OFF* */


/*+
 *   Function name:
 *   tcsCalcNaRange
 *
 *   Purpose:
 *   Compute range to sodium layer for laser guide star systems
 *
 *   Description:
 *   The range to the Na layer is computed based on a simple spherical
 *   model of the atmosphere, the height of the observatory above sea-level
 *   and the altitude of the Na layer.
 *
 *   Epics inputs:
 *
 *   a => height of sodium layer (km)
 *   b => demand mount elevation (degs)
 *   c => Height of observatory above sea-level (m) 
 *
 *   Epics outputs:
 *
 *   vala => range to Na layer (km) 
 *
 *   Invocation:
 *   tcsCalcNaRange (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsCalcNaRange (struct genSubRecord *pgsub)

{
  static double re = 6378.14 ;      /* Earth radius (km) */
  double elRad ;                    /* Demand elevation (rads) */
  double sinel ;                    /* Sine of elevation */
  double h ;                        /* Observatory altitude (km) */
  double H ;                        /* Height of Na layer (km) */
  double range ;                    /* range to Na layer (km) */

/* fetch input parameters */

  elRad = *(double *) pgsub->b * D2R ;
  h     = *(double *) pgsub->c / 1000.0 ;  /* Height (km) */
  H     = *(double *) pgsub->a - h;        /*  Na height above telescope */
  sinel = sin(elRad) ;

  range = sqrt((h+re)*(h+re)*sinel*sinel + H*(H + 2.0*h + 2.0*re)) - 
          (h + re)*sinel ;
  if (range < 0.0) range = 0.0 ;

/* Output on EPICS links */

  *(double *)pgsub->vala = range ;

  return 0;
}

/*+
 *   Function name:
 *   tcsDisplayAirmass
 *
 *   Purpose:
 *   Produce airmass and zenith distance for potential display
 *
 *   Description:
 *   The routine pulls in the current mount azimuth and elevation. The azimuth
 *   is simply converted to degrees. The elevation is converted to a 
 *   zenith distance and this is used to compute the current relative 
 *   airmass.
 *
 *   Epics inputs:
 *
 *   a => current mount azimuth (degs)
 *   b => current mount elevation (degs)
 *
 *   Epics outputs:
 *
 *   vala => current mount azimuth (degs)
 *   valb => current mount zenith distance (degs)
 *   valc => current airmass
 *
 *   Invocation:
 *   tcsDisplayAirmass (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   slaAirmas      (slalib)           Computes relative airmass
 *
 *-
 */

long tcsDisplayAirmass (struct genSubRecord *pgsub)

{
  double elDeg ;                    /* Current elevation (degs) */
  double zdRad ;                    /* current zenith distance (rads) */
  double zdDeg ;                    /* current zenith distance (degs) */
  double airmass ;                  /* current relative airmass */

/* Fetch input elevation */

  elDeg = *(double *) pgsub->b ;

/* convert elevation to zenith distance */

  zdRad = D90 - elDeg * D2R ;
  if (zdRad < 0.0) zdRad = -zdRad;

/* Compute airmass at this zenith distance */

  airmass = slaAirmas (zdRad) ;

/* Convert output angles to degrees */

  zdDeg = R2D * zdRad ;

/* Output on EPICS links */

  *(double *)pgsub->vala = *(double *)pgsub->a ;
  *(double *)pgsub->valb = zdDeg ;
  *(double *)pgsub->valc = airmass;

  return 0;
}

/*+
 *   Function name:
 *   tcsCheckTime
 *
 *   Purpose:
 *   Calculates UTC and LST for a given input MJD for test purposes
 *
 *   Description:
 *   Writing an MJD on the TAI time scale to input J will compute the
 *   equivalent UTC and LST to msecs for comparison with external
 *   programs. 
 *
 *   Epics inputs:
 *   j => TAI expressed as an MJD 
 *
 *   Epics outputs:
 *   vala => UTC as formatted string 
 *   valb => LST as formatted string
 *
 *   Invocation:
 *   tcsCheckTime(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) gensub record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   timeNow        (timelib)         Get current time
 *   timeThenD      (timelib)         Compute UTC from current time
 *   timeThenC      (timelib)         Compute UTC from current time
 *   timeThenT      (timelib)         Compute LAST from current time
 *
 *-
 */
/* *INDENT-ON* */

long tcsCheckTime(struct genSubRecord *pgsub)
{
    double mjdtai;              /* TAI */
    double tai ;                /* TAI as a raw time */
    int ymdhmsf[7];             /* year, month, day, hours, mins, secs, frac */
    int hmsf[4];                /* hours, mins, secs, frac */

/* Fetch TAI */
    mjdtai = *(double *)pgsub->j;
    tai = timeTai2raw(mjdtai) ;

/* Date as string output */
    timeThenC(tai, UTC, 3, ymdhmsf);
    sprintf(pgsub->vala, "%2.2d:%2.2d:%2.2d.%3.3d", ymdhmsf[3], 
            ymdhmsf[4], ymdhmsf[5], ymdhmsf[6]);

/* LST string output */
    timeThenT(tai, LAST, 3, hmsf);
    sprintf(pgsub->valb, "%2.2d:%2.2d:%2.2d.%3.3d", hmsf[0], hmsf[1], 
            hmsf[2], hmsf[3]);

    return 0;
}
/*+
 *   Function name:
 *   tcsDisplayTime
 *
 *   Purpose:
 *   Provides local time and LAST as strings for display
 *
 *   Description:
 *   This function reads the current time as a UTC then adds the time zone
 *   offset to provide local time. This local time is then formatted as a 
 *   string for display. A similar operation is performed to generate LAST.
 *   Other information provided is the HA of source A as well as its 
 *   parallactic angle.
 *
 *   Epics inputs:
 *   a => Telescope mean latitude (degs)
 *   b => local time zone offset (hours)
 *
 *   Epics outputs:
 *   vala => local time (days)
 *   valb => MJD on UTC timescale 
 *   valc => Current UTC date as a formatted string as per FITS standard
 *   vald => LAST as a formatted string
 *   vale => HA of source A (hours)
 *   valf => HA of source A formatted as a string
 *   valg => Current UTC data as formatted string e.g. 2000 Aug 3
 *   valh => Parallactic angle of source A (degs)
 *
 *   Invocation:
 *   tcsDisplayTime(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) gensub record structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   timeNow        (timelib)         Get current time
 *   timeThenD      (timelib)         Compute UTC from current time
 *   timeThenC      (timelib)         Compute UTC from current time
 *   timeThenT      (timelib)         Compute LAST from current time
 *
 *-
 */
/* *INDENT-ON* */

long tcsDisplayTime(struct genSubRecord *pgsub)
{
    double tai;                 /* TAI */
    double utc;                 /* UTC */
    double last ;               /* LAST */
    static char *months[] =
    {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    double tzone;               /* time zone in days -ve to West +ve to East */
    double ltime;               /* temporary holding place for time */
    int ymdhmsf[7];             /* year, month, day, hours, mins, secs, frac */
    int hmsf[4];                /* hours, mins, secs, frac */
    double x, y ;               /* Pointing origins of source */
    double ra, dec ;            /* RA/Dec of target (rads) */
    double ha ;                 /* HA of source A */
    struct EPOCH ep ;           /* Equinox of target */
    char hasign ;               /* sign of HA */
    double pa ;                 /* Parallactic angle (rads) */
    double az, azd, azdd ;      /* Azimuth and its time derivatives */
    double el, eld, eldd ;      /* Elevation and its time derivatives */
    double pad, padd ;          /* Time derivatives of parallactic angle */
    double tlatm ;              /* Mean latitude (rads) */
    int status;

/* Fetch required global data */
    status = timeNow(&tai);
    if (!status) {
        timeThenD(tai, UTC, &utc);

/* UTC output on VALB */
        *(double *)pgsub->valb = utc;

/* Time zone value input at INPB */
        tzone = *(double *)pgsub->b / 24.0;
        ltime = utc + tzone;

/* Local time output on VALA */
        *(double *)pgsub->vala = ltime;

/* Date as string output */
        timeThenC(tai, UTC, 4, ymdhmsf);
        sprintf(pgsub->valc, "%4d-%2.2d-%2.2d", ymdhmsf[0], ymdhmsf[1],
                ymdhmsf[2]);
        sprintf(pgsub->valg, "%2d %s %2d", ymdhmsf[0], months[ymdhmsf[1] - 1],
                ymdhmsf[2]);

/* LST string output */
        timeThenT(tai, LAST, 1, hmsf);
        sprintf(pgsub->vald, "%2.2d:%2.2d:%2.2d.%d", hmsf[0], hmsf[1], hmsf[2],
                hmsf[3]);

/* HA of source A */
        timeThenR(tai, LAST, &last) ;
        tcsGetPO (SOURCE_A, &x, &y) ;
/* The epoch shouldn't be used but just in case set it to something sensible */
        ep.type = 'J' ;
        ep.year = 2000.0 ;
        astXy2s (x, y, APPT, ep, 0.5, 0, &ra, &dec) ;
        ra = slaDranrm (ra) ;
        ha = slaDrange (last - ra) ;
        slaDr2tf (2, ha, &hasign, hmsf) ;
        sprintf (pgsub->valf, "%c%2.2d:%2.2d:%2.2d.%2.2d", hasign, hmsf[0], 
                 hmsf[1], hmsf[2], hmsf[3]) ;
        *(double *)pgsub->vale = ha * 12.0 / PI ;

/* And finally the parallactic angle */
       tlatm = *(double *)pgsub->a * D2R ;
       slaAltaz (ha, dec, tlatm, &az, &azd, &azdd, &el, &eld, &eldd,
                 &pa, &pad, &padd) ;
       *(double *)pgsub->valh = pa * R2D; 
 
    }
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDisplayRADec
 *
 *   Purpose:
 *   Generate demand and current positions suitable for display
 *
 *   Description:
 *   This routine is used to generate demand and current positions of the
 *   telescope suitable for display. A complication is that if the 
 *   coordinate system is mount or topocentric az/el then the value
 *   to be displayed needs to be in degrees minutes and seconds whereas
 *   other coordinate frames e.g. FK5 need the display to be in hours,
 *   minutes and seconds. It is for this reason that the first angular
 *   coordinate is converted here whereas the second is passed directly
 *   to the appropriate SIR record and converted there.
 *   Appropriate display strings (RA or Az, Dec or El) are also output
 *
 *   Input and output EPICS fields used are
 *   a => timestamp for the positions
 *   b => input azimuth (degs)
 *   c => input elevation (degs)
 *   d => Timestamp, position angle and velocity of rotator
 *   e => Timestamp, position and velocity for az and el
 *   f => Use Timestamped positions?  (1: yes, 0: no)
 *   vala => total demand position (RA or Azimuth) (degs)
 *   valb => total demand position (Dec or Elevation) (degs)
 *   valc => current position (RA or Azimuth) (degs)
 *   vald => current position (Dec or Elevation) (degs)
 *   valg => vala as a formatted string
 *   valh => valc as a formatted string
 *   vali => RA or Az string
 *   valj => Dec or El string
 *
 *   Invocation:
 *   tcsDisplayRADec (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   tcsGetFrame    (tcsPointing)      Fetch code for co-ordinate system
 *   tcsGetCoord    (tcsPointing)      Fetch current demand position
 *   tcsGetTrack    (tcsPointing)      Fetch current position
 *
 *-
 */
/* *INDENT-ON* */

long tcsDisplayRADec(struct genSubRecord *pgsub)
{
    double ctarau, ctarbu;      /* Copy of demand ra, Dec */
    double tappl, az, el;       /* Current time, azimuth, elevation */
    double tauraui, tarbui;     /* Computed current RA Dec */
    double rpa;                 /* Rotator position angle */
    double rpat;                /* Time for rotator position angle */
    double rpav;                /* Rotator velocity */
    FRAMETYPE frame;            /* Coordinate system code */
    double eqx;                 /* Equinox */
    double wavel;               /* Wavelength */
    int hmsf[4];                /* Hrs mins, secs and fraction as integers */
    char sign;                  /* + or - */
    double crArray[3] ;         /* Time, position & velocity for Cass. Rot. */
    double mcArray[6] ;         /* Time stamped positions for Mount */
    long  useTimestamps;        /* Select whether or not to use timestamped positions */

/* Fetch required global data */
    tcsGetCoord(&ctarau, &ctarbu);
    tcsGetFrame(MOUNT, &frame, &eqx, &wavel);

    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        slaDr2af(2, ctarau, &sign, hmsf);
        sign = hmsf[0] + hmsf[1] + hmsf[2] ? sign : '+';
        sprintf(pgsub->valg, "%c%02d:%02d:%02d.%02d", sign, hmsf[0], hmsf[1],
                hmsf[2], hmsf[3]);
    } else {
        ctarau = slaDranrm(ctarau);
        slaDr2tf(3, ctarau, &sign, hmsf);
        if (hmsf[0] == 24)
            hmsf[0] = 0;
        sprintf(pgsub->valg, "%02d:%02d:%02d.%03d", hmsf[0], hmsf[1], hmsf[2],
                hmsf[3]);
    }

/* Output demand RA/Dec as VALA and VALB  */
    *(double *)pgsub->vala = ctarau * R2D;
    *(double *)pgsub->valb = ctarbu * R2D;

/* AWE:  It turns out that the arrays of timestamped positions are not being reliably output my the mcs.
   As a result, the currentRA and currentDec calculations generated here have not been usable for many years.
   Until this is fixed in the MCS, this will allow the current positions to be calculated. */

   useTimestamps = *(long *)pgsub->f;

   if (useTimestamps) {
     /* Get current time, current az/el from the timestamped array on input E*/
     memcpy (mcArray, pgsub->e, 6*sizeof(double)) ;
     tappl = mcArray[0] ;
     az    = mcArray[1] * D2R ;
     el    = mcArray[4] * D2R ;
   } else {
     /* Get current time, current az/el from inputs A, B and C */
     tappl = *(double *)pgsub->a;
     az = *(double *)pgsub->b * D2R ;
     el = *(double *)pgsub->c * D2R ;
   }

    memcpy (crArray, pgsub->d, 3 * sizeof(double)) ;
    rpat = crArray[0];
    rpa  = crArray[1];
    rpav = crArray[2];

/* Correct the rotator angle to the time of the mount position */
    rpa += (tappl - rpat) * rpav;

/* Convert to current RA/Dec. Output current RA/Dec as VALC, VALD */
    tcsGetTrack(az, el, rpa * D2R, tappl, &tauraui, &tarbui);
    *(double *)pgsub->valc = tauraui * R2D;
    *(double *)pgsub->vald = tarbui * R2D;

/* Output current Az or RA as a formatted string */
    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        slaDr2af(2, tauraui, &sign, hmsf);
        sign = hmsf[0] + hmsf[1] + hmsf[2] ? sign : '+';
        sprintf(pgsub->valh, "%c%02d:%02d:%02d.%02d", sign, hmsf[0], hmsf[1],
                hmsf[2], hmsf[3]);
    } else {
        tauraui = slaDranrm(tauraui);
        slaDr2tf(3, tauraui, &sign, hmsf);
        if (hmsf[0] == 24)
            hmsf[0] = 0;
        sprintf(pgsub->valh, "%02d:%02d:%02d.%03d", hmsf[0], hmsf[1], hmsf[2],
                hmsf[3]);
    }

/* Output strings for display */
    if (frame == AZEL_MNT || frame == AZEL_TOPO) {
        strcpy(pgsub->vali, "Az");
        strcpy(pgsub->valj, "El");
    } else {
        strcpy(pgsub->vali, "RA");
        strcpy(pgsub->valj, "Dec");
    }
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDisplayTelescopeRADec
 *
 *   Purpose:
 *   Generate current telescope position suitable for display
 *
 *   Description:
 *   Output the current telescope RA & Dec. The telescope RA & Dec
 *   is defined as the RA & Dec of the rotator center. 
 *
 *   EPICS outputs:
 *   vala => current position (RA) (degs)
 *   valb => current position (Dec) (degs)
 *
 *   Invocation:
 *   tcsDisplayTelescopeRADec (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */
/* *INDENT-ON* */

long tcsDisplayTelescopeRADec(struct genSubRecord *pgsub)
{
    double telra;                /* Telescope RA (degs) */
    double teldec ;              /* Telescope Dec (degs) */

/* Fetch required data */
    tcsGetTelescopeRADec(&telra, &teldec);

/* Output RA/Dec as VALA and VALB  */
    *(double *)pgsub->vala = telra ;
    *(double *)pgsub->valb = teldec ;

    return 0;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsDisplayEqx
 *
 *   Purpose:
 *   Generate an equinox suitable for display
 *
 *   Description:
 *   This routine formats an equinox as a string suitable for display.
 *
 *   Input and output EPICS fields used are
 *   a => Coordinate system
 *   b => equinox
 *   str1 => equinox as a formatted string
 *
 *   Invocation:
 *   tcsDisplayRADec (psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     ( genSubRecord * ) Pointer to genSub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *-
 */
/* *INDENT-ON* */

long tcsDisplayEqx( genSubRecord *psub )
{
    FRAMETYPE frame;
    double eqx;

    frame = *(double *)psub->a;
    eqx   = *(double *)psub->b;

    switch (frame) {
    case FK5:
        sprintf(psub->vala, "J%.1f", eqx);
        break;

    case FK4:
        sprintf(psub->vala, "B%.1f", eqx);
        break;

    default:
	strncpy(psub->vala, "\0", 1);
        break;
    }
    return 0;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsLimitDisplay
 *
 *   Purpose:
 *   Displays details of the limit error
 *
 *   Description:
 *   This routine is called to provide a formatted string that describes
 *   the type of limit that has been reached, the current elevation limit
 *   and if appropriate the time until the source rises
 *
 *   Invocation:
 *   tcsLimitDisplay( limerror, ellimit, timetorise, errstring)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    limerror (int)      Error code
 *      (>)    ellimit  (double)   Elevation limit in radians
 *      (>)    timetorise (double) Time before source rises (rads)
 *      (<)    errstring (char *)  Formatted error string
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   slaDr2tf       (slalib)    Converts time (rads) to hmsf as integers
 *
 *-
 */
/* *INDENT-ON* */

void tcsLimitDisplay(int limerror, double ellimit, double timetorise,
                     char *errstring)
{
    char sign;
    int hmsf[4];                /* Time to rise in hrs, mins, secs, frac */

    if (limerror == BELOW_EL_LIMIT)
        sprintf(errstring, "Demand is below limit of %.1f degs",
                ellimit * R2D);
    else if (limerror == NEVER_RISES)
        sprintf(errstring, "Source never rises above %.1f degs",
                ellimit * R2D);
    else if (limerror == BELOW_HORIZON) {
        slaDr2tf(1, timetorise, &sign, hmsf);
        sprintf(errstring, "Source does not rise for %dh %dm %ds", hmsf[0],
                hmsf[1], hmsf[2]);
    }
}
epicsRegisterFunction(tcsCheckTime);
epicsRegisterFunction(tcsDisplayTelescopeRADec);
epicsRegisterFunction(tcsCalcNaRange);
epicsRegisterFunction(tcsDisplayTime);
epicsRegisterFunction(tcsDisplayAirmass);
epicsRegisterFunction(tcsDisplayEqx);
epicsRegisterFunction(tcsDisplayRADec);
