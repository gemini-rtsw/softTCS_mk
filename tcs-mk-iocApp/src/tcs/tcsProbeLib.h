/*
*   FILENAME
*   tcsProbeLib.h
*
*   DESCRIPTION
*   This file is the header for tcsProbeLib.c. It contains all the forward
*   declarations for the publically available routines in that library.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsProbeLib.h,v $
 * Revision 1.10  2010/06/08 15:01:13  cjm
 * Extra port parameters to 2 routines
 *
 * Revision 1.9  2010/06/03 15:36:10  cjm
 * Add tcsProbeGetGSAOIConfig
 *
 * Revision 1.8  2009/12/01 13:38:00  cjm
 * Add GetTcs2Odgw and GetTelescope routines
 *
 * Revision 1.7  2008/05/01 15:18:43  cjm
 * Routines to set and get rotary table limits, posns etc.
 *
 * Revision 1.6  2007/12/18 10:13:08  cjm
 * Add headers for functions needed by guiders
 *
 * Revision 1.5  2006/11/23 15:03:49  cjm
 * Add new routines Get/SetAOConfig
 *
 * Revision 1.4  2002/11/18 20:35:31  cjm
 * Add routine SetOiwfsZoff
 *
 * Revision 1.3  2001/10/05 09:14:05  cjm
 * Add declarations of routines to transform oiwfs coordinates
 *
 * Revision 1.2  2000/11/23 16:14:26  cjm
 * Add prototype for tcsProbeGetAoFold
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.4  1998/10/26 13:21:20  tcs
 * Add routines tcsProbeGetZoff and tcsProbeSetZoff
 *
 * Revision 1.3  1998/09/05 03:28:17  tcs
 * Add new routines SetRaddii, CheckRadii and SetRLimits
 *
 * Revision 1.2  1997/06/02 09:58:28  tcs
 * Add slew CAD
 *
 * Revision 1.1  1997/02/10 17:10:55  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1996/12/12 15:53:34  cjm
 * Updates in preparation for better probe handling
 *
 * Revision 1.1  1996/10/31 09:16:26  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#ifndef TCSPROBELIBH
#define TCSPROBELIBH

int  tcsProbeCheckRadii (int probe, double rmin, double rmax, char *mess);
int  tcsProbeGetAoFold (void) ;
int  tcsProbeGetAOConfig(void);
void tcsProbeSetAOConfig(int flag);
long  tcsProbeGetGSAOIConfig(void);
void tcsProbeInit (void) ;
void tcsProbeGetDefaults (int probe, double *xdef, double *ydef,
                          double *zdef ) ;
void tcsProbeGetTcs2Odgw(int port, int window, double coeffs[6]);
int tcsProbeGetTelescope(void);
void tcsProbeGetZoff (int probe, double *offset) ;
void tcsProbeSetCoeffs (double *coeffs) ;
void tcsProbeSetDefaults (int probe, double xdef, double ydef ,
                          double zdef ) ;
void tcsProbeSetDefaultFlag (int probe, int useDefault) ;
int tcsProbeGetDefaultFlag (int probe) ;
void tcsProbeSetChop (int probe, int ichop) ;
int tcsProbeGetChop (int probe) ;
void tcsProbeOiwfs2Tcs(double ox, double oy, double *tx, double *ty) ;
void tcsProbeSetAOMLimits (int probe, double xmin, double xmax,
                           double rmin, double rmax ) ;
void tcsProbeSetFollowFlag (int probe, long flag); 
void tcsProbeSetXYZLimits (int probe, double xmin, double xmax,
                           double ymin, double ymax,
                           double zmin, double zmax ) ;
void tcsProbeSetRadii (double rmin1, double rmax1, double rmin2, double rmax2);
void tcsProbeSetRLimits (int probe, double rmin, double rmax) ;
void tcsProbeSetRTLimits (double p1RTMin, double p1RTMax, double p2RTMin,
                          double p2RTMax);
void tcsProbeSetRTPosns (double p1RTPosn, double p2RTPosn);
void tcsProbeSetRZLimits  (int probe, double rmin, double rmax,
                           double zmin, double zmax ) ;
void tcsProbeSetOiwfsZoff (double zoff) ;
int tcsGetGsaoiPort();
void tcsProbeGetFollowFlag (int probe, long *flag);
void tcsProbeGetLimits (int probe, LIMITTYPE *limitType, 
                        double *xmin, double *xmax,
                        double *ymin, double *ymax,
                        double *zmin, double *zmax,
                        double *rmin, double *rmax) ;
void tcsProbeGetRTLimits (double *p1RTMin, double *p1RTMax, double *p2RTMin,
                          double *p2RTMax);
void tcsProbeGetRTPosns (double *p1RTPosn, double *p2RTPosn);
void tcsProbeSetZoff (int probe, double offset);
void tcsProbeTcs2Oiwfs(double xt, double yt, double *ox, double *oy) ;
void tcsProbeTcs2Aom(int gi, double xt, double yt, double *ox, double *oy) ;
void tcsProbeTcs2Odgw(int port, int gi, double xt, double yt, double *ox, double *oy) ;
void tcsProbeOdgw2Tcs(int port, int gi, double ox, double oy, double *xt, double *yt) ;
void tcsProbeAom2Tcs(int gi, double ox, double oy, double *xt, double *yt) ;

#endif
