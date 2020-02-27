/*
*   FILENAME
*   tcsInterlocks.h
*
*   DESCRIPTION
*   This is the header file for tcsInterlocks.c
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsInterlocks.h,v $
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:10:42  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/09/27 07:18:31  cjm
 * Initial version
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSINTERLOCKSH
#define TCSINTERLOCKSH

long tcsInterlock (struct subRecord *psub) ;
long tcsUpdateState (struct subRecord *psub) ;
int  tcsInterlocked (char *message) ;

#endif
