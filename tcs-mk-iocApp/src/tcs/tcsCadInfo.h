/*
*   FILENAME
*   tcsCadInfo.h
*
*   DESCRIPTION
*   Definitions of constants and data structures used
*   to hold TCS CAD command data. Also prototypes for functions
*   to initialize and display this data.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsCadInfo.h,v $
 * Revision 1.3  2013/10/31 13:30:28  cjm
 * Increase CAD record limit
 *
 * Revision 1.2  2002/02/27 13:53:18  ptaylor
 * Max number of CADs raised from 300 to 400
 *
 * Revision 1.1.1.1  1998/11/08 00:21:03  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.6  1998/01/26 10:10:03  pbt
 * Increase MAXCAD to 300 (now have 251 CAD records)
 *
 * Revision 1.5  1998/01/21 17:25:50  pbt
 * Provide return values (for errors) from Cad/Car search routines
 *
 * Revision 1.4  1997/11/04 10:35:25  pbt
 * Increased MAXCAD to cope with 250 CAD records - should this suffice?
 *
 * Revision 1.3  1997/09/17 09:47:09  pbt
 * Add routine to check for empty configuration
 *
 * Revision 1.2  1997/06/02 09:58:20  tcs
 * Add slew CAD
 *
 * Revision 1.1  1997/02/10 17:10:15  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.10  1997/01/17 12:37:55  pbt
 * ReadCadInfo no longer uses file tcsSubCad.data
 *
 * Revision 1.9  1996/10/25 15:22:39  pbt
 * Increased max number of CAD records value to 200 - should suffice?
 *
 * Revision 1.8  1996/07/25 13:40:40  pbt
 * Added definition of tcsGetCad function
 *
 * Revision 1.7  1996/07/24 07:34:52  cjm
 * Add tcsCadInfoGetMarked
 *
 * Revision 1.6  1996/07/16 11:03:51  pbt
 * tcsCommandData and related structure definitions are now local to
 * tcsReadCadInfo module. New proto for tcsGetSubCad added.
 *
 * Revision 1.5  1996/07/15 07:32:48  cjm
 * Add configpart to tcsCommand structure
 *
 * Revision 1.4  1996/07/12 14:38:06  pbt
 * Changed prototype for tcsFindCadnames
 *
 * Revision 1.3  1996/07/12 09:16:00  pbt
 * *** empty log message ***
 *
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSCADINFO
#define TCSCADINFO

#define MAXCAD 500


/* Prototypes of functions to initialize and display the CAD data */

void tcsPrintCadInfo();
int tcsConfigEmpty();
int tcsCadIndex(char *cname);
int tcsSnameIndex(char *sname);
int tcsReadCadInfo(char *top);
void tcsCadInfoClearMarks (void) ;
int  tcsCadInfoSetMarked( char *recname) ;
int  tcsCadInfoIsMarked (char *recname) ;
char *tcsGetSubCad(int index, int *first, char **ptr) ;
char *tcsGetCad(int *ncad, int *first);

#endif

