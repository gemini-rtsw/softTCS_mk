/*
*   FILENAME
*   tcsOpticsSimulation
*
*   FUNCTION NAME(S)
*   tcsOpticsSimulate - generate simulated optics data i.e. Zernikes
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsOpticsSimulation.c,v $
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1998/02/10 08:33:34  cjm
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

#include <dbDefs.h>
#include <genSubRecord.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include "tcsRandom.h"


/*+
 *   Function name:
 *   tcsOpticsSimulate
 *
 *   Purpose:
 *   Generate artificial optics corrections for testing purposes
 *
 *   Description:
 *   This routine is intended for test and simulation purposes to allow the
 *   generation of optics model corrections when wave front sensors aren't
 *   available. The following model is used for generating focus corrections.
 *   User specified values are pulled in for the nominal position and 
 *   thermal coefficients of M2 as well as a random error term. The 
 *   difference between what this model predicts and the standard TCS model 
 *   is then used to output a position error directly to the M2 internal
 *   simulator. When the guide loop is closed this error is gradually fed
 *   back into the demand M2 position as well as being used in this 
 *   simulation to modify the error being sent to M2. The end result is that
 *   this routine sends a zero error. 
 *
 *   Invocation:
 *   tcsOpticsSimulate (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => Simulated nominal position of M2 (mm)
 *   b => Simulated thermal expansion coefficient for M2 (mm/deg C)
 *   c => Standard deviation of focal length variation (mm)
 *   d => Current temperature (deg C)
 *   e => Nominal position of M2 (mm)
 *   f => Current temperature correction for M2 (mm)
 *   g => Reference temperature for M2 focus adjustment (deg C)
 *   h => M2 magnification
 *   i => M2 error correction
 *
 *   Epics outputs:
 *   
 *   vala => simulated error for M2 simulator (microns)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Deficiencies:
 *   Currently only deals with simulating focus errors
 *   Should be loaded as a separate file to allow running in another IOC
 *
 *-
 */

long tcsOpticsSimulate (struct genSubRecord *pgsub)
{

  double simM2ZNominal;       /* Nominal Z posn. used by simulator */
  double simM2ZTempCoeff;     /* Temp coeff (mm/deg C) used by simulator */
  double simM2FlError;        /* error on focus position */
  double currTemp;            /* Current temperature (deg C) */
  double zDiff ;              /* Difference between simulated and true posn */
  double zNominal ;           /* Nominal Z position (mm) */
  double zTempCorr ;          /* Thermal correction to Z posn. (mm) */
  double zTempRef ;           /* Reference temperature for model (deg C) */
  double m2Magnification ;    /* Nominal M2 magnification */
  double zErrorCorr ;         /* Z error correction (mm) */

/* Access the users input values for the simulation */

  simM2ZNominal = *(double *)pgsub->a;
  simM2ZTempCoeff = *(double *)pgsub->b ;
  simM2FlError = *(double *)pgsub->c ;

/* Access the data currently held by the TCS to model the Z position of M2 */

  currTemp = *(double *)pgsub->d ;
  zNominal = *(double *)pgsub->e ;
  zTempCorr = *(double *)pgsub->f ;
  zTempRef = *(double *)pgsub->g ;
  m2Magnification = *(double *)pgsub->h ;
  zErrorCorr = *(double *)pgsub->i ;

/* Calculate the difference between the standard model and the users model */

  zDiff = zNominal + zTempCorr 
          - simM2ZNominal - simM2ZTempCoeff * (zTempRef - currTemp) ;

/* Generate a random error and add to zDiff */

  zDiff += (double)tcsGresid((float)simM2FlError)/
           (m2Magnification * m2Magnification + 1);

/* Add on any feed back term */

  zDiff -= zErrorCorr ;

/* Output result for use by EPICS */

  *(double *)pgsub->vala = zDiff * 1000.0; 

  return 0 ;

}
epicsRegisterFunction(tcsOpticsSimulate);


