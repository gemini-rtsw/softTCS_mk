/*
*   FILENAME
*   tcsLimits.h
*
*   DESCRIPTION
*   Routine definitions for tcs limit checking routines
*
*/
/* *INDENT-OFF* */
/*
 * $Log:
 */
/* *INDENT-ON* */

#ifndef TCSLIMITS_H
#define TCSLIMITS_H

#include "tcsConstants.h"

int tcsLimits (FRAMETYPE frame, double ellimit, double ra, double dec,
                double lat, double st, double *timetorise);
void tcsLimAzel2Hadec( double x, double y, double z, double clat, double slat,
   double *ha, double *dec);
int tcsLimEl( double cdec, double sdec, double el, double clat, double slat, 
   double *ha);
int tcsLimAz( double cdec, double sdec, double al, double clat, double slat,
   double ha[2]);
int tcsLimPa( double cdec, double sdec, double pl, double clat, double slat,
   double ha[2]);

#endif
