/*
*   FILENAME
*   tcsAos.h
*
*   DESCRIPTION
*   Routine definitions for the GAOS simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsAos.h,v $
 * Revision 1.2  2001/05/17 14:38:43  cjm
 * Replace mosub references with genSub
 *
 * Revision 1.1.1.1  1998/11/08 00:21:09  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/10/31 12:33:29  pbt
 * Simulation code for Gemini AO system
 *
 */
/* *INDENT-ON* */

#ifndef AOS_H
#define AOS_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

void tcsAoInit (void ) ;

long tcsAoGenericCAD (struct cadRecord *pcad) ;

long tcsAoMoveCAD (struct cadRecord *pcad) ;

long tcsAoFollowCAD (struct cadRecord *pcad) ;

long tcsAoStop (struct genSubRecord *psub) ;

long tcsAoComplete (genSubRecord *psub) ;

#endif
