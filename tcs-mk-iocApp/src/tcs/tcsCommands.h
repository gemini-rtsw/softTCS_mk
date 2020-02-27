/*
*   FILENAME
*   tcsCommands.h
*
*   DESCRIPTION
*   This file is the header for tcsCommands.c which contains the source
*   code for the TCS commands implemented via CAD records.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsCommands.h,v $
 * Revision 1.1.1.1  1998/11/08 00:21:04  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.4  1997/09/12 10:07:14  tcs
 * add tcs prefix to all cad routines
 *
 * Revision 1.3  1997/04/07 13:56:01  pbt
 * Changes for compatability with new Gemini EPICS version RGO4
 *
 * Revision 1.2  1997/04/03 14:33:13  cjm
 * Add tcsChopRel;ative and remove redundant headers
 *
 * Revision 1.1  1997/02/10 17:10:21  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.7  1996/11/28 08:10:53  cjm
 * Upgrades to add debug command and macros
 *
 * Revision 1.6  1996/10/21 13:46:10  cjm
 * Forward declarations for ChopConfig & TargetMFilter
 *
 * Revision 1.5  1996/10/04 08:08:01  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.4  1996/07/24 07:37:45  cjm
 * Add targetS, remove init and reset
 *
 * Revision 1.3  1996/06/21 15:50:10  cjm
 * Add definitions of accept & reject
 *
 * Revision 1.2  1996/06/10 21:10:09  cjm
 * Use template header file
 *
 */
/* *INDENT-ON* */

#ifndef TCSCOMMANDSH
#define TCSCOMMANDSH

/* put definitions here */

#define ARGS_OK 0
#define INV_COSYS 2
#define INV_MINS_SECS 2
#define INV_RA 3
#define INV_DEC 4
#define INV_ARGS 5

/* Put function prototypes here */

#endif 

void tcsThreadSetPriority(const char *tName, unsigned int priority);
