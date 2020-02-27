/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsHandset.c
*
*   FUNCTION NAME(S)
*   tcsHsTarOffset - Connects handset to source offsets.
*   tcsHsPoOffset - Connects handset to pointing origin offsets.
*   tcsHsGuide - Connects handset to guideing.
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */

#include <registryFunction.h>
#include <epicsExport.h>
#include <math.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include "tcsConstants.h"
#include "timeLib.h"
#include "tcsPointing.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsHsTarOffset
 *
 *   Purpose:
 *   Connects software handset to source offsets.
 *
 *   Description:
 *   Each time the associated EPICS subroutine record is processed the
 *   source offsets are incremented by an amount specified by the EPICS
 *   process variables.
 *
 *   Invocation:
 *   tcsHsTarOffset( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *   tcsIncrOffset      (tcsPointing)     Increments offsets
 *   tcsGetCoord        (tcsPointing)     Gets current tracking coordinates
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsHsTarOffset(struct genSubRecord *pgsub)
{
    double delta;
    double delta1 = 0.0, delta2 = 0.0;
    TELESCOPE_M telmask;
    int tanp, dir;
    static int dbgLevel = DBG_NONE; /* Debug level */
    double tnow ;                   /* time now (raw time) */

/* Output diagnostic if debug level is correct.
 * N.B. these diagnostics are used for ST02003
 */
    (void)timeNow(&tnow);
    DBGMSGREAL (DBG_FULL, "tcsHsSrcOffset: started at ", tnow);

/*  Fetch values from input links */
    dir = *(long *)pgsub->a;                  /* Increment direction */
    delta = *(double *)pgsub->b;              /* Increment in theta (arcsec) */
    telmask = *(long *)pgsub->c;              /* Virtual telescope mask */
    tanp = *(long *)pgsub->d;                 /* True if delta is tangent plane */

/*  Convert increment to radians */
    delta *= AS2R;

/*  Set increments according to direction specified */
    switch (dir) {
    case 0:
       delta2 = delta;
       break;
    case 1:
       delta2 = -delta;
       break;
    case 2:
       delta1 = delta;
       break;
    case 3:
       delta1 = -delta;
       break;
    }

/*  Call kernel offset routine */
    tcsIncrOffsets( tanp, delta1, delta2, telmask, 0);

    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsHsPoOffset
 *
 *   Purpose:
 *   Connects software handset to pointing origin offsets.
 *
 *   Description:
 *   Each time the associated EPICS subroutine record is processed the
 *   pointing origin offsets are incremented by an amount specified by the 
 *   EPICS process variables.
 *
 *   Invocation:
 *   tcsHsPoOffset( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   tcsIncrPoOffset      tcsPointing     Increments offsets
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsHsPoOffset(struct genSubRecord *pgsub)
{
    double delta;
    double delta1 = 0.0, delta2 = 0.0;
    TELESCOPE_M telmask;
    int dir;

/*  Fetch values from input links */
    dir = *(long *)pgsub->a;                  /* Increment direction */
    delta = *(double *)pgsub->b;              /* Increment in theta (mm) */
    telmask = *(long *)pgsub->c;              /* Virtual telescope mask */

/*  Set increments according to direction specified */
    switch (dir) {
    case 0:
       delta2 = delta;
       break;
    case 1:
       delta2 = -delta;
       break;
    case 2:
       delta1 = delta;
       break;
    case 3:
       delta1 = -delta;
       break;
    }

/*  Call kernel offset routine */
    tcsIncrPoOffsets( delta1, delta2, telmask, 0);

    return 0;
}


/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsHsGuide
 *
 *   Purpose:
 *   Connects software handset to guiding.
 *
 *   Description:
 *   Each time the associated EPICS subroutine record is processed the
 *   guiding offsets are incremented by an amount specified by the EPICS
 *   process variables and the kernel track id set to a new value.
 *
 *   Invocation:
 *   tcsHsGuide( pgsub )
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) Pointer to subroutine record
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *
 *   External variables:
 *   none
 *
 *   Prior requirements:
 *
 *   Deficiencies:
 *
 *-
 */
/* *INDENT-ON* */

long tcsHsGuide(struct genSubRecord *pgsub)
{
    double delta;
    double delta1 = 0.0, delta2 = 0.0;
    int dir;

/*  Fetch values from input links */
    dir = *(long *)pgsub->a;                  /* Increment direction */
    delta = *(double *)pgsub->b;              /* Increment in theta (arcsec) */

/*  Set increments according to direction specified */
    switch (dir) {
    case 0:
       delta2 = delta;
       break;
    case 1:
       delta2 = -delta;
       break;
    case 2:
       delta1 = delta;
       break;
    case 3:
       delta1 = -delta;
       break;
    }

/* Write increments to output links */
    *(double *) pgsub->vala = delta1;
    *(double *) pgsub->valb = delta2;

/* Set track id */
    tcsSetTrackid();

    return 0;
}
epicsRegisterFunction(tcsHsPoOffset);
epicsRegisterFunction(tcsHsTarOffset);
epicsRegisterFunction(tcsHsGuide);
