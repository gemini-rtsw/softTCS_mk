/*
*   FILENAME
*   tcsAos.h
*
*   DESCRIPTION
*   Routine definitions for the GSAOI simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsGsaoi.h,v $
 * Revision 1.1  2007/12/18 10:06:36  cjm
 * Initial header file for basic GSAOI simulation
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSGSAOI_H
#define TCSGSAOI_H

#include <dbDefs.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <genSubRecord.h>

long tcsGsaoiGenericCAD (struct cadRecord *pcad) ;
void tcsGsaoiInit(void);

#endif
