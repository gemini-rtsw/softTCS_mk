/*
*   FILENAME
*   tcsAos.h
*
*   DESCRIPTION
*   Routine definitions for the AOM simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsAom.h,v $
 * Revision 1.1  2007/12/18 10:05:18  cjm
 * Initial AOM simulator header file
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSAOM_H
#define TCSAOM_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

long tcsAomGenericCAD (struct cadRecord *pcad) ;
void tcsAomInit(void);

#endif
