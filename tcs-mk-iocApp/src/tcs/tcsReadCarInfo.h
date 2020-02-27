/*
*   FILENAME
*   tcsCarInfo.h
*
*   DESCRIPTION
*   Definitions of constants and data structures used
*   to hold TCS CAR record data. Also prototypes for functions
*   to initialize and display this data.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsReadCarInfo.h,v $
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.2  1998/01/21 17:25:52  pbt
 * Provide return values (for errors) from Cad/Car search routines
 *
 * Revision 1.1  1997/02/10 17:11:00  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1997/01/10 14:30:39  pbt
 * New routines/sequence program to combine CAR values into softC record
 *
 */
/* *INDENT-ON* */

#ifndef TCSCARINFO
#define TCSCARINFO

#define MAXCAR 200


/* Prototypes of functions to initialize and display the CAR data */

void tcsPrintCarInfo();
int tcsReadCarInfo(char *top);
char *tcsGetCar(int ncar);

#endif

