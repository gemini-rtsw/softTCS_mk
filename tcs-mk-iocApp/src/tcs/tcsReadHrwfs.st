/* 
*   FILENAME
*   tcsReadHrwfs.st
*
*   FUNCTION NAME(S)
*   This file contains the polling task for reading the HRWFS data file
*
*/
/*  *INDENT-OFF* */
/* $Log: tcsReadHrwfs.st,v $
/* Revision 1.4  2005/04/18 13:20:53  cjm
/* Include stdio.h to remove warnings
/*
/* Revision 1.3  2002/10/24 14:51:31  cjm
/* Change orientation of data sent by HRWFS
/*
/* Revision 1.2  2002/10/22 15:47:07  cjm
/* Support automatic centering
/*
/* Revision 1.1  2002/08/02 15:31:54  cjm
/* New sequence program to poll for HRWFS data in background
/*
 */
/*  *INDENT-ON* */

/*+
* Module:
* tcsReadHrwfs.st
*
* Purpose:
* Read the HRWFS data from a file to tune M1
*
* Description:
* The program consists of a simple polling task that reads a file containing
* the Zernike data from the HRWFS. Each time the data in the file is
* updated, it is written into a database record for passing on to the PCS.
* Following requests by users, the program was modified to support 
* automatic offsetting of the telescope based on additional data in the
* HRWFS data file.
*
* Invocation:
* The program is normally started as follows
*
* seq &tcsReadHrwfs
*
* Macro substitution can be used to over ride the default record prefixes e.g.
* seq &tcsReadHrwfs "top=tc1:"
*
*-
*/

program tcsReadHrwfs ("top=tcs:")

%%#include <stdio.h>
%%#include <stdlib.h>
%%#include <string.h>
%%#include <math.h>
%%#include "timeLib.h"

#define PI    3.1415926535897932384626433832795
#define D2R   (PI/180.0)
#define R2D   (1.0/D2R)

/* Local variables */
double tai ;
double xoff ;
double yoff ;
double mag ;
double dir ;
int    numz ;
int numitems ;
long   oldCounter ;
char   buf[40] ;
%%FILE   *fp ;
int    i ;

/* assign variables to records */
int   counter ;
assign counter to "{top}hr:dc:ao.B" ;
double zerns[40] ;
assign zerns to "{top}hr:dc:ao.J";
string fileName ;
assign fileName to "{top}m1GuideConfig.VALD" ;

/* Records to offset the telescope */
int   m1GuideOn ;
assign m1GuideOn to "{top}im:m1GuideOn" ;
string frame ;
assign frame to "{top}poAdjust.A" ;
string size ;
assign size to "{top}poAdjust.B" ;
string angle ;
assign angle to "{top}poAdjust.C" ;
string vt ;
assign vt to "{top}poAdjust.D" ;
string apply ;
assign apply to "{top}apply.DIR" ;

ss readFile {

  state init {

     when() { 
       oldCounter = 0 ;
       for (i = 0 ; i < 40 ; i++) {
          zerns[i] = 0.0 ;
       }
       timeNow(&tai);
       zerns[0] = tai ;
       strcpy (frame, "1") ;
       strcpy (vt, "1") ;
       strcpy (apply, "START") ;

     }  state poll
  }

  state poll {
    
     when (delay(1.0)) {
      
       pvGet(fileName) ;
       pvGet(m1GuideOn) ;
       if (fileName != NULL) {
         
         if ((fp = fopen (fileName, "r"))) {
           fgets(buf, 40, fp);
           counter = atoi(buf);

/* The if statement here will cause the zernikes to be updated the first time
*  this state set runs i.e. if there is an old file of HRWFS data lying
*  around these old values will get written into the database. This is not
*  a problem however as the code that writes these data to M1 will not be
*  active at this time so they'll never get sent to the PCS
*/
           if (counter != oldCounter) {
             oldCounter = counter ;
             fgets(buf, 40, fp) ;

/* Try and detect if this is a new style file with offsets or an old style
*  file without offsets
*/
             numitems = sscanf(buf, "%lf %lf", &xoff, &yoff) ;
             if ( numitems == 2) {
               mag = sqrt(xoff * xoff + yoff * yoff);
               sprintf (size, "%.2f", mag);
               dir = atan2(-xoff, yoff) * R2D ;
               sprintf (angle, "%.2f", dir);
               if (m1GuideOn) {
                 pvPut(frame) ;
                 pvPut(angle) ;
                 pvPut(size);
                 pvPut(vt) ;
                 pvPut(apply) ;
               }
               fgets(buf, 40, fp) ;
               numz = atoi(buf) ;
             } else {
               numz = atoi(buf) ;
             }
             timeNow(&tai);
             zerns[0] = tai ;
             zerns[1] = numz ;
/* fill in all the zernikes that have been measured */
             for (i = 0 ; i < numz ; i++) {
               fgets(buf, 40, fp) ;
               zerns[2+i] = atof(buf) ;
             }
/* If the maximum allowed haven't been measured, fill in the rest with zeroes */
             if (numz < 19 ) {
               for (i = 0; i < 19-numz ; i++) {
                 zerns[numz + 2 + i] = 0.0 ;
               }
             } 
/* Now fill in the errors */
             for (i = 0; i < numz; i++) {
                fgets(buf, 40, fp) ;
                zerns[21+i] = atof(buf);
             }
/* Again make sure those not measured are filled with zeroes */
             if (numz < 19) {
               for (i = 0; i < 19-numz ; i++) {
                 zerns[numz + 21 + i] = 0.0;
               }
              } 
           } 

/* Put the counter first as the record will only process when the Zernikes
*  get written
*/
           pvPut(counter) ;
           pvPut(zerns) ;
           fclose (fp) ;
         }

       }

     }  state poll

  }

}
