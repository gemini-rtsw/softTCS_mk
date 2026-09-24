/*
*   FILENAME
*   tcsReadHrwfs.st
*
*   FUNCTION NAME(S)
*   This file contains the polling task for reading the HRWFS Zernike data.
*
*/
/*  *INDENT-OFF* */
/* $Log: tcsReadHrwfs.st,v $
/* Revision 1.5  REL-845 - read HRWFS Zernikes over channel access
/*   instead of from a data file. The HRWFS DC now computes the Zernikes
/*   itself (aoHrwfsLib) and publishes them, a frame counter and the
/*   pointing offsets, so the file-based method is replaced.
/*
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
* Read the HRWFS Zernike data over channel access to tune M1.
*
* Description:
* A simple polling task that reads the Zernike coefficients, a frame counter
* and the pointing offsets published by the HRWFS detector controller
* (REL-845, aoHrwfsLib) over channel access. Each time the frame counter
* changes, the Zernikes are written into a database record for passing on to
* the PCS, and (if M1 guiding is on) the pointing offsets are applied to the
* telescope. This replaces the previous method of reading a data file.
*
* Invocation:
* The program is normally started as follows
*
* seq &tcsReadHrwfs
*
* Macro substitution can over ride the default record prefixes e.g.
* seq &tcsReadHrwfs "top=tc1:,hrtop=hrwfs:"
*
*-
*/

program tcsReadHrwfs ("top=tcs:,hrtop=hrwfs:")

%%#include <stdio.h>
%%#include <stdlib.h>
%%#include <string.h>
%%#include <math.h>
%%#include "timeLib.h"

#define PI    3.1415926535897932384626433832795
#define D2R   (PI/180.0)
#define R2D   (1.0/D2R)
#define NHRZERN 19            /* Number of Zernikes published by the HRWFS DC */

/* Local variables */
double tai ;
double xoff ;
double yoff ;
double mag ;
double dir ;
int    numz ;
long   oldCounter ;
int    i ;

/* TCS-side records populated for M1 tuning (unchanged) */
int   counter ;
assign counter to "{top}hr:dc:ao.B" ;
double zerns[40] ;
assign zerns to "{top}hr:dc:ao.J";

/*
 * HRWFS detector-controller records, read over channel access (REL-845).
 * The DC publishes a frame counter, the low-order Zernikes and the recentre
 * pointing offsets. hrZern is an array assigned across the 19 aoZern records.
 */
long   hrCounter ;
assign hrCounter to "{hrtop}dc:aoCounter" ;
monitor hrCounter ;

double hrZern[NHRZERN] ;
assign hrZern to {
   "{hrtop}dc:aoZern1",  "{hrtop}dc:aoZern2",  "{hrtop}dc:aoZern3",
   "{hrtop}dc:aoZern4",  "{hrtop}dc:aoZern5",  "{hrtop}dc:aoZern6",
   "{hrtop}dc:aoZern7",  "{hrtop}dc:aoZern8",  "{hrtop}dc:aoZern9",
   "{hrtop}dc:aoZern10", "{hrtop}dc:aoZern11", "{hrtop}dc:aoZern12",
   "{hrtop}dc:aoZern13", "{hrtop}dc:aoZern14", "{hrtop}dc:aoZern15",
   "{hrtop}dc:aoZern16", "{hrtop}dc:aoZern17", "{hrtop}dc:aoZern18",
   "{hrtop}dc:aoZern19" } ;
monitor hrZern ;

double hrOffX ;
assign hrOffX to "{hrtop}dc:aoOffX" ;
double hrOffY ;
assign hrOffY to "{hrtop}dc:aoOffY" ;

/* Records to offset the telescope (unchanged) */
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

ss readData {

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

       pvGet(hrCounter) ;
       pvGet(m1GuideOn) ;

/* Only update when the HRWFS DC reports a new processed frame. */
       if (hrCounter != oldCounter) {
         oldCounter = hrCounter ;

/* Refresh the Zernikes and the pointing offsets from the HRWFS DC. */
         pvGet(hrZern) ;
         pvGet(hrOffX) ;
         pvGet(hrOffY) ;

/* Apply the pointing offset to the telescope (if M1 guiding is on). */
         xoff = hrOffX ;
         yoff = hrOffY ;
         mag = sqrt(xoff * xoff + yoff * yoff) ;
         sprintf (size, "%.2f", mag) ;
         dir = atan2(-xoff, yoff) * R2D ;
         sprintf (angle, "%.2f", dir) ;
         if (m1GuideOn) {
           pvPut(frame) ;
           pvPut(angle) ;
           pvPut(size) ;
           pvPut(vt) ;
           pvPut(apply) ;
         }

/* Assemble the Zernike array: [time, numz, 19 Zernikes, 19 errors]. */
         timeNow(&tai);
         numz = NHRZERN ;
         zerns[0] = tai ;
         zerns[1] = numz ;
         for (i = 0 ; i < numz ; i++) {
           zerns[2 + i] = hrZern[i] ;
         }
/* Errors are not yet computed by the HRWFS DC - fill with zeroes. */
         for (i = 0 ; i < 19 ; i++) {
           zerns[21 + i] = 0.0 ;
         }

/* Put the counter first as the record only processes when the Zernikes
*  get written.
*/
         counter = hrCounter ;
         pvPut(counter) ;
         pvPut(zerns) ;
       }

     }  state poll

  }

}
