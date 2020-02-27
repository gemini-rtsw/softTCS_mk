/*
*   FILENAME
*   tcsMcs.h
*
*   DESCRIPTION
*   Routine definitions for the Mount simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsMcs.h,v $
 * Revision 1.2  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1997/10/02 10:42:20  pbt
 * Added extra #include to avoid compilation warnings
 *
 * Revision 1.2  1997/09/24 16:32:50  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.1  1997/02/10 17:10:45  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.3  1996/07/23 14:59:20  tcs
 * tidy up routine names and add header to include files
 *
 */
/* *INDENT-ON* */

#ifndef MCS_H
#define MCS_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsMcInit (void ) ;

long tcsMcGenericCAD (struct cadRecord *pcad) ;

long tcsMcMoveCAD (struct cadRecord *pcad) ;

long tcsMcFollowCAD (struct cadRecord *pcad) ;

long tcsMcSimulate (genSubRecord *psub) ;

long tcsMcStop (struct genSubRecord *pgsub) ;

long tcsMcComplete (genSubRecord *psub) ;

#endif
