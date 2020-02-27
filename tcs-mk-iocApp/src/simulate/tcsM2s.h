/*
*   FILENAME
*   tcsM2s.h
*
*   DESCRIPTION
*   Routine definitions for the M2 G simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsM2s.h,v $
 * Revision 1.2  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1997/10/02 10:42:19  pbt
 * Added extra #include to avoid compilation warnings
 *
 * Revision 1.2  1997/09/24 16:32:49  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.1  1997/02/10 17:10:43  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/07/23 14:59:19  tcs
 * tidy up routine names and add header to include files
 *
 */
/* *INDENT-ON* */

#ifndef M2S_H
#define M2S_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsM2Init (void ) ;

long tcsM2GenericCAD (struct cadRecord *pcad) ;

long tcsM2MoveCAD (struct cadRecord *pcad) ;

long tcsM2FollowCAD (struct cadRecord *pcad) ;

long tcsM2Simulate (genSubRecord *psub) ;

long tcsM2Stop (struct genSubRecord *pgsub) ;

long tcsM2Complete (genSubRecord *psub) ;

#endif
