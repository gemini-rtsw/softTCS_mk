/*
*   FILENAME
*   tcsInPosition.h
*
*   DESCRIPTION
*   This include file contains the status values and associated messages
*   for reporting the reasons for the tcs being "out of position".
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsInPosition.h,v $
 * Revision 1.2  2007/12/18 10:12:13  cjm
 * Add macros for in position reasons for new guiders
 *
 * Revision 1.1  2001/10/24 22:53:39  dlt
 * Display reason for inPosition false
 *
 *
 */
/* *INDENT-ON* */

/*
 * TODO 
 * add reasons for the generic guiders
 */
#ifndef TCSINPOSITION_H
#define TCSINPOSITION_H

#define IPR_INPOSITION 0
#define IPR_TARFILT   1
#define IPR_ZENITH    2
#define IPR_ELLOW     3
#define IPR_ELHIGH    4
#define IPR_AZLOW     5
#define IPR_AZHIGH    6
#define IPR_ROTLOW    7
#define IPR_ROTHIGH   8
#define IPR_M2XMAX    9
#define IPR_M2YMAX   10
#define IPR_WFSXMIN  11
#define IPR_WFSXMAX  12
#define IPR_WFSYMIN  13
#define IPR_WFSYMAX  14
#define IPR_WFSRMIN  15
#define IPR_WFSRMAX  16
#define IPR_WFSZMIN  17
#define IPR_WFSZMAX  18
/* Skip 16 numbers for to allow for 3 wave-front sensors. */
#define IPR_AOXMIN   35
#define IPR_AOXMAX   36
#define IPR_AOYMIN   37
#define IPR_AOYMAX   38
#define IPR_AOZMIN   39
#define IPR_AOZMAX   40
#define IPR_NGS1XMIN 41
#define IPR_NGS1XMAX 42
#define IPR_NGS1RMIN 43
#define IPR_NGS1RMAX 44
#define IPR_NGS2XMIN 45
#define IPR_NGS2XMAX 46
#define IPR_NGS2RMIN 47
#define IPR_NGS2RMAX 48
#define IPR_NGS3XMIN 49
#define IPR_NGS3XMAX 50 
#define IPR_NGS3RMIN 51 
#define IPR_NGS3RMAX 52
#define IPR_ODGW1XMIN 53 
#define IPR_ODGW1XMAX 54 
#define IPR_ODGW1YMIN 55 
#define IPR_ODGW1YMAX 56 
#define IPR_ODGW2XMIN 57 
#define IPR_ODGW2XMAX 58 
#define IPR_ODGW2YMIN 59 
#define IPR_ODGW2YMAX 60 
#define IPR_ODGW3XMIN 61 
#define IPR_ODGW3XMAX 62 
#define IPR_ODGW3YMIN 63 
#define IPR_ODGW3YMAX 64 
#define IPR_ODGW4XMIN 65 
#define IPR_ODGW4XMAX 66 
#define IPR_ODGW4YMIN 67 
#define IPR_ODGW4YMAX 68 


char* iprreasons[] = {
   "",
   "Target filter in progress",
   "Target too close to zenith",
   "Elevation at low limit",
   "Elevation at high limit",
   "Azimuth at low limit",
   "Azimuth at high limit",
   "Rotator at low limit",
   "Rotator at high limit",
   "M2 maximum X tilt",
   "M2 maximum Y tilt",
   "PWFS1 at minimum X limit",
   "PWFS1 at maximum X limit",
   "PWFS1 at minimum Y limit",
   "PWFS1 at maximum Y limit",
   "PWFS1 at minimum radius",
   "PWFS1 at maximum radius",
   "PWFS1 at minimum Z limit",
   "PWFS1 at maximum Z limit",
   "PWFS2 at minimum X limit",
   "PWFS2 at maximum X limit",
   "PWFS2 at minimum Y limit",
   "PWFS2 at maximum Y limit",
   "PWFS2 at minimum radius",
   "PWFS2 at maximum radius",
   "PWFS2 at minimum Z limit",
   "PWFS2 at maximum Z limit",
   "OIWFS at minimum X limit",
   "OIWFS at maximum X limit",
   "OIWFS at minimum Y limit",
   "OIWFS at maximum Y limit",
   "OIWFS at minimum radius",
   "OIWFS at maximum radius",
   "OIWFS at minimum Z limit",
   "OIWFS at maximum Z limit",
   "AO at minimum X limit",
   "AO at maximum X limit",
   "AO at minimum Y limit",
   "AO at maximum Y limit",
   "AO at minimum Z limit",
   "AO at maximum Z limit",
   "AOM NGS1 at min. X limit",
   "AOM NGS1 at max. X limit",
   "AOM NGS1 at min. radius",
   "AOM NGS1 at max. radius",
   "AOM NGS2 at min. X limit",
   "AOM NGS2 at max. X limit",
   "AOM NGS2 at min. radius",
   "AOM NGS2 at max. radius",
   "AOM NGS3 at min. X limit",
   "AOM NGS3 at max. X limit",
   "AOM NGS3 at min. radius",
   "AOM NGS3 at max. radius",
   "ODGW1 at minimum X limit",
   "ODGW1 at maximum X limit",
   "ODGW1 at minimum Y limit",
   "ODGW1 at maximum Y limit",
   "ODGW2 at minimum X limit",
   "ODGW2 at maximum X limit",
   "ODGW2 at minimum Y limit",
   "ODGW2 at maximum Y limit",
   "ODGW3 at minimum X limit",
   "ODGW3 at maximum X limit",
   "ODGW3 at minimum Y limit",
   "ODGW3 at maximum Y limit",
   "ODGW4 at minimum X limit",
   "ODGW4 at maximum X limit",
   "ODGW4 at minimum Y limit",
   "ODGW4 at maximum Y limit"
};

#endif
