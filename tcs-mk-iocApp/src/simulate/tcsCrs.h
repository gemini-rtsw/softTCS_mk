/*
*   FILENAME
*   tcsCrs.h
*
*   DESCRIPTION
*   Routine definitions for the Cass Rotator simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsCrs.h,v $
 * Revision 1.2  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.1.1.1  1998/11/08 00:21:09  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1997/10/02 10:42:17  pbt
 * Added extra #include to avoid compilation warnings
 *
 * Revision 1.2  1997/09/24 16:32:47  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.1  1997/02/10 17:10:28  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/07/23 14:56:26  tcs
 * make consistent use of cr for cass rotator
 *
 */
/* *INDENT-ON* */

#ifndef CRS_H
#define CRS_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsCrInit (void ) ;

long tcsCrGenericCAD (struct cadRecord *pcad) ;

long tcsCrMoveCAD (struct cadRecord *pcad) ;

long tcsCrFollowCAD (struct cadRecord *pcad) ;

long tcsCrSimulate (genSubRecord *psub) ;

long tcsCrStop (struct genSubRecord *pgsub) ;

long tcsCrComplete (genSubRecord *psub) ;

#endif
