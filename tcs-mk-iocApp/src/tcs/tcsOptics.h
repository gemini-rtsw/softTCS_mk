/*
*   FILENAME
*   tcsOptics.h
*
*   DESCRIPTION
*   Header file for code to support Gemini Optics models
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsOptics.h,v $
 * Revision 1.18  2013/10/15 12:25:33  cjm
 * Support new status items m1RestoredFile, m1RestoredTime and m1ModelName
 *
 * Revision 1.17  2012/10/04 15:38:00  cjm
 * provide access to flags that say if M1 model file is valid
 *
 * Revision 1.16  2012/10/04 13:31:13  cjm
 * Add nGetM1ModelType, M1ModelValid update setM1Restore
 *
 * Revision 1.15  2009/08/19 09:39:53  cjm
 * Reversion to r1.13, r1.14 changes removed
 *
 * Revision 1.13  2005/12/20 14:58:24  cjm
 * Pass focusModel parameter to ProbeXYZ call
 *
 * Revision 1.12  2003/07/09 10:49:40  cjm
 * Add definitions of new functions related to M1 optics model
 *
 * Revision 1.11  2002/11/18 20:32:29  cjm
 * Add routines GetFshift and SetM2DzIns
 *
 * Revision 1.10  2002/02/22 10:44:17  cjm
 * Add declaration of SetFocusFlag
 *
 * Revision 1.9  2001/09/02 15:12:02  cjm
 * New declaration for SetM1Guide
 *
 * Revision 1.8  2000/01/26 06:00:05  cjm
 * Add routines M2ClearComa and M2XYErr
 *
 * Revision 1.7  1999/12/16 16:33:06  cjm
 * Change fourth parameter of SetM1Guide to be a number of frames to average rahter than an integration time
 *
 * Revision 1.6  1999/11/27 03:00:07  cjm
 * Remove SetAoIntTime routine and add new routines SetAoExpTime and SetAoFrames
 *
 * Revision 1.5  1999/03/12 09:42:28  cjm
 * Add headers for SetComaCoeffs and SetM2Nom
 *
 * Revision 1.4  1999/03/11 00:06:12  cjm
 * Add routine tcsOpticsM1SetInit
 *
 * Revision 1.3  1999/02/27 05:33:19  cjm
 * Add tcsOpticsGetProbeScale
 *
 * Revision 1.2  1999/01/05 16:52:46  epics
 * Add routines GetAoAverage, GetAoIntTime, GetM1Guide, SetAoIntTime, SetAoAverage, SetM1Guide
 *
 * Revision 1.1.1.1  1998/11/08 00:21:06  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.7  1998/01/14 20:58:42  cjm
 * Add routines for optical distortion & probe corrections
 *
 * Revision 1.6  1997/12/08 10:04:23  cjm
 * Added support for generating expected Zernikes
 *
 * Revision 1.5  1997/12/01 09:09:15  cjm
 * Add ScaleThrow and SetTelScales routines
 *
 * Revision 1.4  1997/11/18 15:35:01  cjm
 * Add declaration of tcsOpticsM2ZServo
 *
 * Revision 1.3  1997/11/18 08:31:18  cjm
 * Add routines SetM2Guide, SetM2ZError & M2ZFilter
 *
 * Revision 1.2  1997/03/24 15:16:14  cjm
 * Store M2 limit parameters
 *
 * Revision 1.1  1997/02/10 17:10:49  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1997/01/20 09:07:53  cjm
 * Add tcsOpticsM2DzUser routine
 *
 * Revision 1.3  1997/01/17 18:18:41  cjm
 * Correct x,y probe positions and generate focus demand
 *
 * Revision 1.2  1997/01/16 10:44:41  cjm
 * Add support for tip/tilt/focus models of M2
 *
 * Revision 1.1  1997/01/14 16:30:59  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#ifndef TCSOPTICSH 
#define TCSOPTICSH 

void tcsOpticsApplyDist (double x, double y, double *xd, double *yd);
int  tcsOpticsCheckChopLimits (int chopMode, double freq, double throw,
           double *freqLimit, double *throwLimit, char *mess);
int  tcsOpticsCheckTiltLimits (double tilt, double zDemand, 
           double *tiltLim, double *zLim, char *mess);
int  tcsOpticsGetAoAverage (void) ;
void tcsOpticsGetAoIntTime (double *intTime) ;
void tcsOpticsGetChopLimits (double *maxThrow, double *minChopFreq,
                       double *maxChopFreq ) ;
void tcsOpticsGetDistCoeff (double *coeff) ;
void tcsOpticsGetFl (double *focalLength);
void tcsOpticsGetFshift (double *shift) ;
void tcsOpticsGetM1Guide (M1WEIGHT *weightType, double *p1Weight, 
                          double *p2Weight, double *updateInt);
int tcsOpticsGetM1ModelType (void);
int tcsOpticsGetM1SaveType (void);
int tcsOpticsGetM1ModelValid (int model);
void tcsOpticsM2ClearComa (void) ;
void tcsOpticsGetM2Fplane ( double *m2FplaneSep) ;
void tcsOpticsGetM2XY (double *m2Xposn, double *m2Yposn);
void tcsOpticsGetM2ZTilt (double *m2Zposn, double *m2XtiltPosn,
                          double *m2YtiltPosn);
void tcsOpticsGetProbeScale (double *p1Scale, double *p2Scale) ;
void tcsOpticsGetTiltLimits (double *maxTilt, double *maxZ);
void tcsOpticsGetTTF (int probe, int ichop, double x, double y, double pa,
                      double ttf[3] );
void tcsOpticsGetZernikes (int probe, int ichop, double x, double y, double pa,
                      double zernikes[16] );
void tcsOpticsInit (void);
void tcsOpticsM1ClearModel (void) ;
void tcsOpticsM1SetInit (void) ;
int  tcsOpticsM1ModelInit (void) ;
int  tcsOpticsM1ModelValid (char *filename, long age, char *reason);
long tcsOpticsM2Tilt (struct genSubRecord *pgsub);
long tcsOpticsM2XY (struct genSubRecord *pgsub);
long tcsOpticsM2XYErr (struct genSubRecord *pgsub);
long tcsOpticsM2Z (struct genSubRecord *pgsub);
double tcsOpticsM2ZFilter (double dt, double freq0, double input);
double tcsOpticsM2ZServo (double kp, double ki, double dt, double input);
void tcsOpticsPlaneXYZ (double *x, double *y, double *z) ;
void tcsOpticsProbeXYZ (int focusModel, double *xcorr, double *ycorr, 
                        double *zcorr);
void tcsOpticsRemoveDist(double xd, double yd, double *x, double *y);
double tcsOpticsScaleThrow (double skyThrow) ;
void tcsOpticsSetAoExpTime( double expTime) ;
void tcsOpticsSetAoFrames (int numFrames) ;
void tcsOpticsSetComaCoeffs (double a, double b, double c) ;
void tcsOpticsSetChopLimits (double minChopFreq, double breakChopFreq,
                       double maxChopFreq, double minChopFreqThrow,
                       double breakChopFreqThrow, double maxChopFreqThrow);
void tcsOpticsSetFocusFlag (int flag);
void tcsOpticsSetM1Guide (M1WEIGHT weightType, int wfsSource, 
                          long numFrames);
void tcsOpticsSetM1Zero (void) ;
void tcsOpticsSetM1Restore (int model) ;
void tcsOpticsSetM1Save (int model) ;
void tcsOpticsSetM2Nom (double xTilt, double yTilt, double x, double y,
                        double z) ;
void tcsOpticsSetM2XYOff (double xoff, double yoff);
void tcsOpticsSetM2XYRot (int ichop, double xrot, double yrot);
void tcsOpticsSetTelScales (double dz) ;
void tcsOpticsSetTiltLimits (double minTilt, double maxTilt, 
                             double minTiltZ, double maxTiltZ);
void tcsOpticsSetM2DzIns (double dzIns);
void tcsOpticsSetM2DzUser (double dzUser);
void tcsOpticsSetM2Guide (int absorbFocus, int comaCorrect);
void tcsOpticsSetM2ZError (double zError);
void tcsOpticsSetPointFlag (int flag);
void tcsOpticsSetTopEnd (char *topEndString);
void tcsOpticsXpYpToXY (double xp, double yp, double pa,
                               double *x, double *y);
void tcsOpticsXYToXpYp (double x, double y, double pa,
                               double *xp, double *yp);

#endif
