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
* seq &tcsReadHrwfs
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
 * The DC publishes a frame counter, the low-order Zernikes (one record each)
 * and the recentre pointing offsets.
 */
int    hrCounter ;
assign hrCounter to "{hrtop}dc:aoCounter" ;
monitor hrCounter ;

double hrZern1 ;
assign hrZern1 to "{hrtop}dc:aoZern1" ;
monitor hrZern1 ;
double hrZern2 ;
assign hrZern2 to "{hrtop}dc:aoZern2" ;
monitor hrZern2 ;
double hrZern3 ;
assign hrZern3 to "{hrtop}dc:aoZern3" ;
monitor hrZern3 ;
double hrZern4 ;
assign hrZern4 to "{hrtop}dc:aoZern4" ;
monitor hrZern4 ;
double hrZern5 ;
assign hrZern5 to "{hrtop}dc:aoZern5" ;
monitor hrZern5 ;
double hrZern6 ;
assign hrZern6 to "{hrtop}dc:aoZern6" ;
monitor hrZern6 ;
double hrZern7 ;
assign hrZern7 to "{hrtop}dc:aoZern7" ;
monitor hrZern7 ;
double hrZern8 ;
assign hrZern8 to "{hrtop}dc:aoZern8" ;
monitor hrZern8 ;
double hrZern9 ;
assign hrZern9 to "{hrtop}dc:aoZern9" ;
monitor hrZern9 ;
double hrZern10 ;
assign hrZern10 to "{hrtop}dc:aoZern10" ;
monitor hrZern10 ;
double hrZern11 ;
assign hrZern11 to "{hrtop}dc:aoZern11" ;
monitor hrZern11 ;
double hrZern12 ;
assign hrZern12 to "{hrtop}dc:aoZern12" ;
monitor hrZern12 ;
double hrZern13 ;
assign hrZern13 to "{hrtop}dc:aoZern13" ;
monitor hrZern13 ;
double hrZern14 ;
assign hrZern14 to "{hrtop}dc:aoZern14" ;
monitor hrZern14 ;
double hrZern15 ;
assign hrZern15 to "{hrtop}dc:aoZern15" ;
monitor hrZern15 ;
double hrZern16 ;
assign hrZern16 to "{hrtop}dc:aoZern16" ;
monitor hrZern16 ;
double hrZern17 ;
assign hrZern17 to "{hrtop}dc:aoZern17" ;
monitor hrZern17 ;
double hrZern18 ;
assign hrZern18 to "{hrtop}dc:aoZern18" ;
monitor hrZern18 ;
double hrZern19 ;
assign hrZern19 to "{hrtop}dc:aoZern19" ;
monitor hrZern19 ;

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
         pvGet(hrZern1) ;
         pvGet(hrZern2) ;
         pvGet(hrZern3) ;
         pvGet(hrZern4) ;
         pvGet(hrZern5) ;
         pvGet(hrZern6) ;
         pvGet(hrZern7) ;
         pvGet(hrZern8) ;
         pvGet(hrZern9) ;
         pvGet(hrZern10) ;
         pvGet(hrZern11) ;
         pvGet(hrZern12) ;
         pvGet(hrZern13) ;
         pvGet(hrZern14) ;
         pvGet(hrZern15) ;
         pvGet(hrZern16) ;
         pvGet(hrZern17) ;
         pvGet(hrZern18) ;
         pvGet(hrZern19) ;
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
         numz = 19 ;
         zerns[0] = tai ;
         zerns[1] = numz ;
         zerns[2] = hrZern1 ;
         zerns[3] = hrZern2 ;
         zerns[4] = hrZern3 ;
         zerns[5] = hrZern4 ;
         zerns[6] = hrZern5 ;
         zerns[7] = hrZern6 ;
         zerns[8] = hrZern7 ;
         zerns[9] = hrZern8 ;
         zerns[10] = hrZern9 ;
         zerns[11] = hrZern10 ;
         zerns[12] = hrZern11 ;
         zerns[13] = hrZern12 ;
         zerns[14] = hrZern13 ;
         zerns[15] = hrZern14 ;
         zerns[16] = hrZern15 ;
         zerns[17] = hrZern16 ;
         zerns[18] = hrZern17 ;
         zerns[19] = hrZern18 ;
         zerns[20] = hrZern19 ;
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
