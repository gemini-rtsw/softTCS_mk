/*
*   FILENAME
*   tcsConfig.h
*
*   DESCRIPTION
*   This header file contains all the definitions, forward declarations
*   and typedefs for tcsConfig.c. All code that checks and 
*   validates a configuration from the OCS is maintained in this module.
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsConfig.h,v $
 * Revision 1.10  2012/05/08 09:43:56  cjm
 * Add SetAOConfiguration and SetP1LGSMode
 *
 * Revision 1.9  2010/11/29 14:12:25  cjm
 * Add new routine tcsConfigForceCheck
 *
 * Revision 1.8  2009/12/01 13:42:01  cjm
 * Add SetOdgwParams
 *
 * Revision 1.7  2007/12/18 10:22:17  cjm
 * Add declaration of tcsConfigSetVgconfig
 *
 * Revision 1.6  2007/01/09 11:55:33  cjm
 * New call parameters for Get and SetOrbit
 *
 * Revision 1.5  2005/12/23 14:53:28  cjm
 * Aff new routine ResetRates
 *
 * Revision 1.4  2005/10/20 15:14:34  cjm
 * tcsConfigGetPlanet now expects arrays
 *
 * Revision 1.3  2003/04/10 10:21:09  dlt
 * Store chop mode in kernel
 *
 * Revision 1.2  2001/05/17 15:18:25  cjm
 * Remove references to subCad record
 *
 * Revision 1.1.1.1  1998/11/08 00:21:04  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.17  1997/11/19 16:05:42  tcs
 * implement slew parameters
 *
 * Revision 1.16  1997/11/19 10:11:15  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.15  1997/11/13 13:23:34  tcs
 * Revised guide star scheme
 *
 * Revision 1.14  1997/11/05 11:43:00  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.13  1997/10/31 14:44:55  tcs
 * Add instrument angle to rotator structure
 *
 * Revision 1.12  1997/09/12 12:58:22  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.11  1997/09/11 16:13:28  tcs
 * Add clipAtLimits support
 *
 * Revision 1.10  1997/06/26 10:10:11  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.9  1997/06/25 12:57:17  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.8  1997/06/11 15:14:18  tcs
 * Implement wavelength CADs
 *
 * Revision 1.7  1997/06/09 15:57:41  tcs
 * rewrite config checking with astlib
 *
 * Revision 1.6  1997/06/02 09:58:24  tcs
 * Add slew CAD
 *
 * Revision 1.5  1997/05/16 12:19:48  tcs
 * Change TCB to arrays
 *
 * Revision 1.4  1997/05/15 14:15:07  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.3  1997/05/07 10:26:41  tcs
 * Implement target to current filter
 *
 * Revision 1.2  1997/04/03 14:31:52  cjm
 * New headers for modified tcsConfig.c
 *
 * Revision 1.1  1997/02/10 17:10:24  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1997/01/24 14:25:13  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.3  1997/01/23 10:46:40  tcs
 * kernel support for relative chopping
 *
 * Revision 1.2  1996/12/13 09:51:09  cjm
 * Correct type for cosys in tcsConfigGetSysconfig
 *
 * Revision 1.1  1996/12/12 16:57:06  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.21  1996/12/06 14:10:35  tcs
 * revise rotator data
 *
 * Revision 1.20  1996/12/05 13:12:11  tcs
 * rename initial state to catch up
 *
 * Revision 1.19  1996/12/03 16:55:23  tcs
 * New filter parameter names
 *
 * Revision 1.18  1996/12/02 11:04:59  tcs
 * Add rotator parameters to GetSysConfig
 *
 * Revision 1.17  1996/11/26 15:27:10  tcs
 * Add filter access routines
 *
 * Revision 1.16  1996/11/13 14:38:52  tcs
 * Add rotator CAD
 *
 * Revision 1.15  1996/11/06 14:14:56  tcs
 * add pm argument to GetTarget and remove GetFrame
 *
 * Revision 1.14  1996/10/24 16:11:06  tcs
 * Pointing origin offset commands
 *
 * Revision 1.13  1996/10/24 12:10:40  tcs
 * add pointing origin commands
 *
 * Revision 1.12  1996/10/24 07:09:38  cjm
 * Redefine tcsConfigEndPreset
 *
 * Revision 1.11  1996/10/23 12:11:05  tcs
 * Add coordinate type to GetOffset
 *
 * Revision 1.10  1996/10/22 15:59:43  tcs
 * Add configuration offset commands
 *
 * Revision 1.9  1996/10/08 14:01:34  tcs
 * Add CADs for all 13 VTs & remove guide1 and target
 *
 * Revision 1.8  1996/10/07 07:10:49  cjm
 * Support 13 VTs for both preset and current targets
 *
 * Revision 1.7  1996/10/04 08:08:06  cjm
 * Support tcbdefn command and new telescope types
 *
 * Revision 1.6  1996/09/30 17:01:03  pbt
 * Alterations to tcsConfig save and load routines
 *
 * Revision 1.5  1996/09/05 16:02:50  pbt
 * Added definitions of new tcsConfig routines
 *
 * Revision 1.4  1996/07/25 12:51:10  cjm
 * Modifications to support data passing via TCBs
 *
 * Revision 1.3  1996/07/24 07:39:03  cjm
 * Additional routines to build and manipulate TCBs
 *
 * Revision 1.2  1996/07/19 15:34:46  cjm
 * Modifications for handling of configurations
 *
 * Revision 1.1  1996/07/15 07:40:37  cjm
 * Initial version
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSCONFIGH
#define TCSCONFIGH

#include "tcsTcb.h"

TCBDEFN tcsConfigActiveTCB ( void ) ;

long tcsConfigBegin ( cadRecord *pcad );

long tcsConfigEnd ( cadRecord *pcad );

void tcsConfigForceCheck() ;

void tcsConfigGetOffset (TCBDEFN tcbDefn, TELESCOPE telescope, int offsetNum,
                         OFFCOORD *coord, double *dtheta1, double *dtheta2) ;

void tcsConfigGetPo (TCBDEFN tcbDefn, TELESCOPE telescope, 
                     double *x, double *y) ;

void tcsConfigGetPFilt (TCBDEFN tcbDefn, double *weightA,
                        double *weightB, double *weightC, double *weightNod,
                        double *bw, double *maxv, double *grab, int *sc) ;

void tcsConfigGetTFilt (TCBDEFN tcbDefn, double *bw, 
                        double *maxv, double *grab, int *sc) ;

void tcsConfigGetPoOffset (TCBDEFN tcbDefn, TELESCOPE telescope, int offsetNum,
                     double *x, double *y) ;

void tcsConfigGetChop (TCBDEFN tcbDefn, int, int*, FRAMETYPE*, double*,
                       double*, double*, int*) ;

void tcsConfigGetGuide (TCBDEFN tcbDefn, int, int[3][3]) ;

void tcsConfigGetGuideIndex(int gindex, int *pindex) ;

void tcsConfigGetWavel (TCBDEFN tcbDefn, TELESCOPE telescope, double *wavel) ;

void tcsConfigGetTrack (TCBDEFN tcbDefn, TELESCOPE telescope,
                        FRAMETYPE *frame, struct EPOCH *eqx,
                        double *theta1, double *theta2,
                        double *dtheta1, double *dtheta2, double *t0) ;

void tcsConfigGetDiffTrack (TCBDEFN tcbDefn, TELESCOPE telescope,
                         FRAMETYPE *frame, struct EPOCH *eqx,
                         double *zerotime, double *diffRA, double *diffDec) ;

void tcsConfigGetSysconfig (TCBDEFN tcbDefn, int *azwrap, int *rotwrap, 
                            double *ipa, FRAMETYPE *r_frame, double *r_eqx, 
                            double *iaa, int *chopmode) ;

void tcsConfigGetPlanet(TCBDEFN tcbDefn, PLANET planet[], int override_rates[]);

void tcsConfigGetOrbit(TCBDEFN tcbDefn, int jform[], double epoch[],
   double orbinc[], double anode[], double perih[], double aorq[], 
   double e[], double aorl[], double dm[]) ;

void tcsConfigGetReftime (TCBDEFN tcbDefn, double *reftime) ;

int tcsConfigMarkSeqComm (char *name, char *errmsg) ;

int tcsConfigMarkComm (char *name, char *errmsg) ;

void tcsConfigPrintTCB (TCBDEFN tcbDefn) ;

void tcsConfigResetRates (int i, double tt, double dtheta1, double dtheta2);

long tcsConfigSeqCheck ( cadRecord *pcad );

void tcsConfigSetAOConfiguration (struct ICAD_FIELD *pAOConfig);

void tcsConfigSetP1LGSMode (struct ICAD_FIELD *pMode);

void tcsConfigSetChopParams (struct DCAD_FIELD *pChopFreq,
                             struct ICAD_FIELD *pChopMode) ;

void tcsConfigSetRelChopParams (int chopNum,
                             struct DCAD_FIELD *pChopThrow, 
                             struct DCAD_FIELD *pChopPA,
                             struct FRAMECAD_FIELD *pChopFrame,
                             struct EPOCHCAD_FIELD *pChopEquinox,
                             int pari) ;

void tcsConfigSetOdgwParams(void);
void tcsConfigSetPo ( TELESCOPE telescope, struct IMAGEPOS *imagepos) ;

void tcsConfigSetPoOffset ( TELESCOPE telescope, int offsetNum,
                            struct IMAGEPOS *imagepos) ;

void tcsConfigSetOffset (TELESCOPE telescope, int offsetNum, 
                         struct OFFBASE *offbase ) ;

void tcsConfigSetPFilt ( struct POINTFILTER *pfilt) ;

void tcsConfigSetTFilt ( struct TARGETFILTER *tfilt) ;

void tcsConfigSetPresetTime ( double time ) ;

void tcsConfigSetTarget (TELESCOPE telescope, struct TARGET *target) ;

void tcsConfigSetVgconfig (int gindex, struct VGCONFIG *vgconfig);

void tcsConfigSetWavel (TELESCOPE telescope, struct WAVEL *wavel) ;

void tcsConfigSetDiffTrack (TELESCOPE telescope, struct DIFFTRACK *difftrack) ;

void tcsConfigUpdateDiffTrack (TELESCOPE telescope, double tt, int zero) ;

void tcsConfigSetTrack (TELESCOPE telescope, struct TRACK *track) ;

void tcsConfigSetWrap (WRAP wrap, struct ICAD_FIELD *wrapval) ;

void tcsConfigSetGuide (int nguide, struct GUIDE *guide) ;

void tcsConfigSetClipAtLimit (struct ICAD_FIELD *flag) ;

void tcsConfigSetSlew (struct SLEW *slew) ;

void tcsConfigSetRot (struct ROT *rot) ;

void tcsConfigSetPlanet (struct PLANET *planet) ;

void tcsConfigSetOrbit (struct ORBIT *orbit, TELESCOPE tel) ;

void tcsConfigSetTels (char *tels, int *status) ;

void tcsConfigSetTCBDefn (TCBDEFN tcbDefn) ;

int tcsConfigSaveTcb(TCBDEFN tcbDefn, char *filename, char *comment, char *errmess) ;

int tcsConfigLoadTcb(TCBDEFN tcbDefn, char *filename, char *errmess) ;
                            
void tcsConfigSetAllTargetFields(const char *top, TCBDEFN tcbDefn);

#endif
