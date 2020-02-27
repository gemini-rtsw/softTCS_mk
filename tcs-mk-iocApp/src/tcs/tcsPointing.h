/*
*   FILENAME
*   tcsPointing.h
*
*   DESCRIPTION
*   Routine definitions for tcs kernel
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsPointing.h,v $
 * Revision 1.13  2013/05/20 12:21:31  cjm
 * Add tcsG/etTelescopeRADec
 *
 * Revision 1.12  2012/05/08 09:45:38  cjm
 * Add set and get of P1LGSMode
 *
 * Revision 1.11  2010/06/03 15:35:01  cjm
 * Add Set/GetGSAOIDistortion
 *
 * Revision 1.10  2007/01/09 11:50:16  cjm
 * Pass virtual telescope to GetPlanet and GetOrbit
 *
 * Revision 1.9  2006/11/24 10:21:29  cjm
 * Add extra debug parameter to tcsFastLoop
 *
 * Revision 1.8  2005/10/21 15:41:47  cjm
 * Modified declaration for tcsSolsysLoop
 *
 * Revision 1.7  2003/04/10 10:21:09  dlt
 * Store chop mode in kernel
 *
 * Revision 1.6  2001/01/15 11:37:17  dlt
 * New handset interface
 *
 * Revision 1.5  2000/05/09 08:08:43  cjm
 * Add declaration of tcsGetPO
 *
 * Revision 1.4  2000/04/20 09:49:29  dlt
 * Implement guiding of wfs probes
 *
 * Revision 1.3  1999/01/22 03:18:26  dlt
 * Do tangent plane conversion in tcsIncrOffset
 *
 * Revision 1.2  1998/12/07 16:45:03  epics
 * Disable further 20Hz processing if fast loop does not run
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.18  1998/10/28 10:02:04  dlt
 * New routine for setting new trackid
 *
 * Revision 1.17  1997/12/09 08:24:41  cjm
 * Amend declaration of tcsFastLoop
 *
 * Revision 1.16  1997/11/19 16:05:42  tcs
 * implement slew parameters
 *
 * Revision 1.15  1997/11/13 13:23:39  tcs
 * Revised guide star scheme
 *
 * Revision 1.14  1997/10/31 14:46:27  tcs
 * Add instrument angle concept
 *
 * Revision 1.13  1997/09/23 11:39:27  tcs
 * Remove redundant declarations
 *
 * Revision 1.12  1997/09/23 09:38:04  tcs
 * Add support for absorbing & zeroing offsets
 *
 * Revision 1.11  1997/09/12 13:07:38  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.10  1997/08/13 10:24:40  tcs
 * Add guiding adjustments to ca/ce
 *
 * Revision 1.9  1997/06/26 10:10:14  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.8  1997/06/25 12:57:25  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.7  1997/06/11 15:14:22  tcs
 * Implement wavelength CADs
 *
 * Revision 1.6  1997/06/09 15:54:00  tcs
 * Move tcsLimits from tcsPointing
 *
 * Revision 1.5  1997/05/16 12:20:22  tcs
 * Change cosys to frame
 *
 * Revision 1.4  1997/05/15 14:15:11  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.3  1997/05/07 10:26:46  tcs
 * Implement target to current filter
 *
 * Revision 1.2  1997/03/24 15:17:46  cjm
 * Remove redundant header entries
 *
 * Revision 1.1  1997/02/10 17:10:53  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.7  1997/01/23 10:46:50  tcs
 * kernel support for relative chopping
 *
 * Revision 1.6  1997/01/14 17:37:04  pbt
 * Add tcsGetTrackid function
 *
 * Revision 1.5  1997/01/14 16:34:31  cjm
 * add new functions to fetch az,el and temperature
 *
 * Revision 1.4  1997/01/10 15:22:10  tcs
 * add nod support
 *
 * Revision 1.3  1996/12/20 14:43:09  tcs
 * remove guide probe flexture terms
 *
 * Revision 1.2  1996/12/18 11:17:38  tcs
 * cleanup plus offset routines
 *
 * Revision 1.1  1996/12/13 10:07:55  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.14  1996/12/09 08:14:52  cjm
 * Add tcsGetAoprms, tcsGetPfilt and tcsGetTelParams
 *
 * Revision 1.13  1996/12/06 09:46:30  tcs
 *  Correct copying of offsets from kernel to TCB
 *
 * Revision 1.12  1996/12/02 11:03:29  tcs
 * Add medium fast loop
 *
 * Revision 1.11  1996/10/21 13:45:19  cjm
 * Forward declarations for Set/Get ChopLimits
 *
 * Revision 1.10  1996/07/23 15:02:59  tcs
 * make consistent use of cr for cass rotator
 *
 */
/* *INDENT-ON* */

#ifndef TCSPOINTING_h
#define TCSPOINTING_H

#include "tcsConstants.h"
#include "tcsTcb.h"

void tcsGetFrame(TELESCOPE tel, FRAMETYPE *frame, double *eqx, double *wavel);

void tcsGetIaa( double *iaa);

void tcsGetMountAzEl(double *azimuth, double *elevation);

void tcsGetTemperature (double *temperature);

void tcsSetSimFlags (int McsSimulate, int CrsSimulate, int EcsSimulate,
                     int M2sSimulate, int AgsSimulate);


void tcsGetCoord (double *ra, double *dec);

void tcsGetObs (double *tlong, double *tlat, double *hm);

void tcsGetTarget(TELESCOPE telescope, struct TCB *pTCB) ;

void tcsGetImagePos (TELESCOPE telescope, int index, struct IMAGEPOS *pimpos,
                     int *status) ;

void tcsGetPO (TELESCOPE telescope, double *x, double *y) ;

void tcsGetTelescopeRADec (double *ra, double *dec) ;

void tcsGetTrackid (double *trackid) ;

void tcsSetTrackid (void) ;

void tcsGetAoprms (double *aoprms) ;

void tcsGetBaseOffset (TELESCOPE telescope, int index, struct OFFBASE *pob, 
                       int *status) ;

void tcsGetPFilt (struct POINTFILTER *pFilter) ;

void tcsGetTFilt (struct TARGETFILTER *tFilter) ;

void tcsGetChop (int chopNo, struct CHOP *pChop) ;

void tcsGetChopMode (struct SYSCONFIG *pSysConfig) ;

void tcsGetGuide (int guideNo, struct GUIDE *pGuide) ;

void tcsGetRotConfig ( struct ROT *rot) ;

void tcsGetPlanet(TELESCOPE tel, struct TCB *pTCB);

void tcsGetOrbit(TELESCOPE tel, struct ORBIT *orbit);

void tcsGetTelParams (TELESCOPE telescope, struct TELP *pTelParams) ;

void tcsGetTrack (double az, double el, double rpa, double tappl, 
                  double *taraui, double *tarbui);

int tcsGetP1LGSMode (void) ;


void tcsAbsorbOffsets (TELESCOPE_M, int ) ;

void tcsSetOffsets (TELESCOPE_M, int, double, double ) ;

void tcsSetP1LGSMode(int mode);

void tcsAbsorbPoOffsets (TELESCOPE_M, int ) ;

void tcsSetPoOffsets (TELESCOPE_M, int, double, double ) ;

void tcsSetGSAOIDistortion(double *coeffs);

void tcsGetGSAOIDistortion(int type, double *coeffs);

void tcsIncrOffsets (int, double, double, TELESCOPE_M, int ) ;

void tcsIncrPoOffsets (double, double, TELESCOPE_M, int ) ;

void tcsNod( int );

void tcsMediumLoop(void);
void tcsSolsysLoop(char *health, char *mess);
void tcsMedFastLoop(void);
int tcsFastLoop(double, double, double, double, double, double, double,
   long, double, double, long);

#endif
