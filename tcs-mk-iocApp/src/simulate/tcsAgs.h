/*
*   FILENAME
*   tcsAgs.h
*
*   DESCRIPTION
*   Routine definitions for the A & G simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsAgs.h,v $
 * Revision 1.3  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.2  2001/05/06 00:03:16  cjm
 * Add declarations of gemAb2xy and gemxy2ab
 *
 * Revision 1.1.1.1  1998/11/08 00:21:09  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1997/10/02 10:42:15  pbt
 * Added extra #include to avoid compilation warnings
 *
 * Revision 1.2  1997/09/24 16:32:47  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.1  1997/02/10 17:10:12  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/07/23 14:59:15  tcs
 * tidy up routine names and add header to include files
 *
 */
/* *INDENT-ON* */

#ifndef AGS_H
#define AGS_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsAgInit (void ) ;

long tcsAgGenericCAD (struct cadRecord *pcad) ;

long tcsAgMoveCAD (struct cadRecord *pcad) ;

long tcsAgFollowCAD (struct cadRecord *pcad) ;

long tcsAgSimulate (genSubRecord *psub) ;

long tcsAgStop (struct genSubRecord *psub) ;

long tcsAgComplete (genSubRecord *psub) ;

int gemAb2xy (double a, double b, double d, double h, double rp,
              double ra, double *x, double *y) ;
int gemXy2ab (double x, double y, double d, double h, double rp,
              double ra, double *a1, double *b1, double *a2,
              double *b2);

#endif
