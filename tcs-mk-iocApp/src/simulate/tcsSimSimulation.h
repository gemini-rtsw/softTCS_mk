/*
*   FILENAME
*   tcsSimSimulation.h
*
*   DESCRIPTION
*   This file is the header for tcsSimSimulation.c which contains non
*   subsystem specific routines used by the TCS internal simulations.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSimSimulation.h,v $
 * Revision 1.1.1.1  1998/11/08 00:21:11  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:11:22  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/05/22 22:13:22  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#ifndef TCSSIMSIMULATIONH
#define TCSSIMSIMULATIONH

long tcsSimLog (struct sirRecord *psir) ;

long tcsSimNullInit ( struct subRecord *psub) ;

#endif
