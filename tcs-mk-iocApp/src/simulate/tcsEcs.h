/*
*   FILENAME
*   tcsEcs.h
*
*   DESCRIPTION
*   Routine definitions for the Enclosure simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEcs.h,v $
 * Revision 1.2  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1997/10/02 10:42:18  pbt
 * Added extra #include to avoid compilation warnings
 *
 * Revision 1.2  1997/09/24 16:32:48  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.1  1997/02/10 17:10:33  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/07/23 14:59:17  tcs
 * tidy up routine names and add header to include files
 *
 */
/* *INDENT-ON* */

#ifndef ECS_H
#define ECS_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsEcInit (void ) ;

long tcsEcGenericCAD (struct cadRecord *pcad) ;

long tcsEcMoveCAD (struct cadRecord *pcad) ;

long tcsEcFollowCAD (struct cadRecord *pcad) ;

long tcsEcSimulate (genSubRecord *psub) ;

long tcsEcStop (struct genSubRecord *pgsub) ;

long tcsEcComplete (genSubRecord *psub) ;

#endif
