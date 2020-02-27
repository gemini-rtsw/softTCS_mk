/*
*   FILENAME
*   tcsOptics.c
*
*   FUNCTION NAME(S)
*   tcsOpticsAoAv          - update m1AoAveraging flag
*   tcsOpticsApplyDist     - apply optical distortion correction
*   tcsOpticsAverageAo     - average Ao data for PCS
*   tcsOpticsCalcM1Moving  - generate the m1Moving flag to control averaging
*   tcsOpticsCalcM1ValidFlags - check if saved models are valid
*   tcsOpticsCheckAoModel  - checks model parameters for validity
*   tcsOpticsCheckChopLimits - checks that throw and frequency are compatible
*   tcsOpticsCheckTiltLimits - checks that tilt and focus are compatible
*   tcsOpticsDisplayAo     - display aO Zernikes sent to M1 
*   tcsOpticsDump          - print out internal variables for debug purposes
*   tcsOpticsGetAoAverage  - fetch flag that controls aO data averaging
*   tcsOpticsGetAoIntTime  - fetch aO integration time
*   tcsOpticsGetChopLimits - fetch chop limits
*   tcsOpticsGetDistCoeff  - fetch optical distortion coefficient
*   tcsOpticsGetM1ModelType  - fetch which M1 model to be restored
*   tcsOpticsGetM1ModelValid  - fetch flag to say model is valid
*   tcsOpticsFigureTotals  - copy total figure offsets from M1
*   tcsOpticsGetFl         - fetch effective focal length
*   tcsOpticsGetFshift     - fetch offset of focal plane from nominal
*   tcsOpticsGetM1Guide    - fetch M1 guide parameters
*   tcsOpticsGetM2Fplane   - fetch separation of M2 & focal plane
*   tcsOpticsGetM2XY       - fetch X, Y translation demands of M2
*   tcsOpticsGetM2ZTilt    - fetch Z translation and X,Y tilt demands of M2
*   tcsOpticsGetProbeScale - return scale factor for probe arm positions
*   tcsOpticsGetTiltLimits - fetch tilt and focus limits
*   tcsOpticsGetTTF        - fetch Tip/Tilt/Focus Zernikes for a probe
*   tcsOpticsGetZernikes   - fetch Zernikes 4 to 19 
*   tcsOpticsHrwfsData     - copy HRWFS zernikes for tuning M1
*   tcsOpticsInit          - initialise Optics library routines
*   tcsOpticsM1CalcFig     - calculate M1 figure corrections
*   tcsOpticsM1ClearModel  - clear zero and restore flags for m1 model
*   tcsOpticsM1Figure      - send figure command to M1
*   tcsOpticsM1FileStatus  - status of M1 restore file
*   tcsOpticsM1Offsets     - fetch M1 offsets from the subsystem
*   tcsOpticsM1ModelInit   - has decision been made on how to init model
*   tcsOpticsM1ModelValid  - check if a valid M1 model is available to restore
*   tcsOpticsM1Restore     - restore M1 model
*   tcsOpticsM1SetInit     - set the flag to init the open loop model
*   tcsOpticsM1ShowCoeffs  - make current in use coefficients visible to EPICS
*   tcsOpticsM1StoreCoeffs - store coefficients of M1 open loop optics model
*   tcsOpticsM2ClearComa   - zero the error corrections due to coma
*   tcsOpticsM2Coma        - store coma correction terms
*   tcsOpticsM2ModelTilt   - generate model corrections to X,Y tilts
*   tcsOpticsM2ModelXY     - generate model corrections to X,Y translation
*   tcsOpticsM2ModelZ      - generate model corrections to Z translation
*   tcsOpticsM2Move        - send repeated move commands to M2
*   tcsOpticsM2ThermalTilt - generate thermal corrections to X,Y tilts
*   tcsOpticsM2ThermalXY   - generate thermal corrections to X,Y translation
*   tcsOpticsM2ThermalZ    - generate thermal corrections to Z translation
*   tcsOpticsM2Tilt        - generate X,Y tilts for M2
*   tcsOpticsM2XY          - generate X,Y demands for M2
*   tcsOpticsM2XYErr       - show translation corrections for M2
*   tcsOpticsM2Z           - generate Z demands for M2
*   tcsOpticsM2ZFilter     - filter Z error corrections from M2
*   tcsOpticsM2ZServo      - absorb m2 error corrections into TCS
*   tcsOpticsM2ZValues     - focus data for M2
*   tcsOpticsPlaneXYZ      - correct probe positions back to flat focal plane
*   tcsOpticsProbeXYZ      - provide corrected probe positions
*   tcsOpticsRemoveDist    - remove optical distortion from focal plane
*   tcsOpticsScaleThrow    - scale between sky and M2 units
*   tcsOpticsSensor1Temp   - process sensor data for M2 thermal model
*   tcsOpticsSensor2Temp   - process sensor data for M2 thermal model
*   tcsOpticsSetAoExpTime  - set aO exposure time
*   tcsOpticsSetAoFrames   - set number of frames to coadd for aO data
*   tcsOpticsSetComaCoeffs - set coefficients of coma correction model 
*   tcsOpticsSetChopLimits - set chop limit parameters
*   tcsOpticsSetColl       - set collimation corrections for optics
*   tcsOpticsSetFocusFlag  - set flag to control focus temperature corrections
*   tcsOpticsSetM1Guide    - set guide configuration parameters for M1
*   tcsOpticsSetM1Zero     - set flag to zero M1 model on startup
*   tcsOpticsSetM1Restore  - set flag to restore M1 model on startup
*   tcsOpticsSetM2DzIns    - set instrument focus offset for model
*   tcsOpticsSetM2DzUser   - Set user focus offset for model
*   tcsOpticsSetM2Guide    - Set guide modes for M2
*   tcsOpticsSetM2Nom      - set nominal position for M2 coma tilt model
*   tcsOpticsSetM2XYOff    - Set X,Y offsets for M2
*   tcsOpticsSetM2XYRot    - Set XY translations for a given rotation
*   tcsOpticsSetM2ZError   - set error correction term in M2 model
*   tcsOpticsSetPointFlag  - set flag that controls optics pointing adjustments
*   tcsOpticsSetTelScales  - set telescope optics scales
*   tcsOpticsSetTiltLimits - set tilt/focus limits
*   tcsOpticsSetZCoeffs    - set matrix coefficients to compute Zernikes
*   tcsOpticsSetTopEnd     - set top end that is currently in use
*   tcsOpticsTrussReset    - reset truss temperature calculation
*   tcsOpticsTrussTemp     - compute overall truss temperature
*   tcsOpticsXpYpToXY      - rotate x', y' to x,y
*   tcsOpticsXYToXpYp      - rotate x,y to x', y'
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsOptics.c,v $
 * Revision 1.50  2013/10/15 12:25:33  cjm
 * Support new status items m1RestoredFile, m1RestoredTime and m1ModelName
 *
 * Revision 1.49  2013/09/11 15:42:30  cjm
 * Add support for GPI M1 model
 *
 * Revision 1.48  2012/11/06 10:01:00  cjm
 * Don't pass pgsub->name to strtok as it gets modified
 *
 * Revision 1.47  2012/10/04 15:38:00  cjm
 * provide access to flags that say if M1 model file is valid
 *
 * Revision 1.46  2012/10/04 13:32:08  cjm
 * Updates to support save/restore of AO specific M1 models
 *
 * Revision 1.45  2011/05/03 14:44:53  cjm
 * Implement median filter on temperature data
 *
 * Revision 1.44  2010/06/01 08:06:45  cjm
 * Fix typo
 *
 * Revision 1.43  2009/12/01 13:45:31  cjm
 * Add support for GAOS as source of M1 data
 *
 * Revision 1.42  2009/10/30 17:19:42  cjm
 * Allow for Zernikes from GeMS system
 *
 * Revision 1.41  2009/08/19 09:39:00  cjm
 * reversion to r1.39, r1.40 changes removed
 *
 * Revision 1.39  2008/10/07 12:24:31  cjm
 * Output M2 scale optics scale factor in dump routine
 *
 * Revision 1.38  2005/12/20 14:59:10  cjm
 * Implement selectable focus models in ProbeXYZ
 *
 * Revision 1.37  2005/06/30 14:26:57  cjm
 * New style check for presence of M1 truss records
 *
 * Revision 1.36  2004/05/28 14:19:37  cjm
 * Allow extra flag to turn on/off open loop model during closed loop operation
 *
 * Revision 1.35  2004/05/27 15:07:40  cjm
 * Apply open loop corrections for P2 and OIWFS during closed loop except for astigmatism
 *
 * Revision 1.34  2004/03/24 14:50:24  cjm
 * Turn off open loop model when closed loop guiding
 *
 * Revision 1.33  2003/11/10 14:37:55  gemvx
 * Provide means to reset truss temperature calculations
 *
 * Revision 1.32  2003/07/15 09:22:21  cjm
 * Restore coma corrections and add sin term to M2 model
 *
 * Revision 1.31  2003/07/09 10:51:08  cjm
 * Add new functions to save/restore/init M1 optics model
 *
 * Revision 1.30  2002/11/18 20:33:53  cjm
 * Add code to support focus offsets of instrument
 *
 * Revision 1.29  2002/10/04 14:26:09  cjm
 * Add code to handle ao data from Altair
 *
 * Revision 1.28  2002/08/02 15:29:57  cjm
 * Add code to support HRWFS as a source of ao data
 *
 * Revision 1.27  2002/02/22 10:46:15  cjm
 * Changes to support thermal adjustments to M2 focus
 *
 * Revision 1.26  2002/02/19 17:23:11  ajf
 * Fixed major problem where the optical data semaphore was never being
 * created. This may have been leading to many of the TCS crashes that
 * have been reported. Also fixed the "scan6" task crash. It was possible
 * for some optical data not to have been initialised before first being
 * used. This lead to a divide by 0 error.
 *
 * Revision 1.25  2001/09/10 15:09:01  cjm
 * add explanation of current Zernike model
 *
 * Revision 1.24  2001/09/02 15:10:05  cjm
 * Support new format m1GuideConfig command
 *
 * Revision 1.23  2001/05/17 15:16:04  cjm
 * Use menuDirectiveSTART instead of CAD_START
 *
 * Revision 1.22  2001/04/06 16:19:28  cjm
 * Set new coefficients in CheckAoModel
 *
 * Revision 1.21  2001/03/12 15:24:25  cjm
 * Add tcsOpticsCheckAoModel to permit an empirical off axis astigmatism model to be used
 *
 * Revision 1.20  2000/10/11 05:33:55  cjm
 * Add routine to set aO averaging flag
 *
 * Revision 1.19  2000/02/16 06:19:17  dlt
 * Add sin(1.7*el) to focus model
 *
 * Revision 1.18  2000/02/07 21:08:49  cjm
 * Implement cos(el) dependence of X coma
 *
 * Revision 1.17  2000/01/29 23:51:52  cjm
 * Remove scaling in M2Coma, WFS now returns coma in mm of shift of M2
 *
 * Revision 1.16  2000/01/26 05:59:24  cjm
 * Add routines M2ClearComa, M2Coma and M2XYErr to support closed loop coma corrections
 *
 * Revision 1.15  1999/12/16 16:33:05  cjm
 * Change fourth parameter of SetM1Guide to be a number of frames to average rahter than an integration time
 *
 * Revision 1.14  1999/12/14 09:43:28  cjm
 * Output START directive to figure command as a double not a string
 *
 * Revision 1.13  1999/11/28 02:20:37  cjm
 * Fix bug that all outputs were not initialised if the number of Zernikes to correct was less than the maximum
 *
 * Revision 1.12  1999/11/27 03:00:54  cjm
 * Remove SetAoIntTime routine and add new routines SetAoExpTime and SetAoFrames
 *
 * Revision 1.11  1999/11/20 03:45:11  cjm
 * Add routine CalcM1Moving and take account of state of M1 when averaging the data from P1
 *
 * Revision 1.10  1999/06/29 05:01:06  cjm
 * Fix zero / zero bug when calculating corrections for on axis guide stars
 *
 * Revision 1.9  1999/03/22 22:01:40  dlt
 * Initialize flCurrent and deltaZ
 *
 * Revision 1.8  1999/03/14 22:01:48  dlt
 * Change M2 axis moved for coma correction
 *
 * Revision 1.7  1999/03/12 09:42:18  cjm
 * Add headers for SetComaCoeffs and SetM2Nom
 *
 * Revision 1.6  1999/03/11 00:05:27  cjm
 * Add many new routines to handle M1 open loop optics corrections
 *
 * Revision 1.5  1999/03/01 09:23:00  cjm
 * Add tcsOpticsFigureTotals
 *
 * Revision 1.4  1999/02/27 05:32:20  cjm
 * Add routine to return probe scale factors
 *
 * Revision 1.3  1999/02/02 04:43:14  cjm
 * Add routines tcsOpticsM1Figure and tcsOpticsAverageAo
 *
 * Revision 1.2  1999/01/05 16:49:30  epics
 * Add routines to handle averaging and manipulation of the aO data from the PWFS
 *
 * Revision 1.1.1.1  1998/11/08 00:21:06  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.12  1998/02/10 08:31:52  cjm
 * Move tcsOpticsSimulate to separate file and rewrite
 *
 * Revision 1.11  1998/01/14 20:58:40  cjm
 * Add routines for optical distortion & probe corrections
 *
 * Revision 1.10  1997/12/12 08:22:27  cjm
 * Use M1 actual positions for sky simulator
 *
 * Revision 1.9  1997/12/09 08:22:55  cjm
 * Add tcsOpticsSetColl to set ca,ce
 *
 * Revision 1.8  1997/12/08 10:04:00  cjm
 * Added support for generating expected Zernikes
 *
 * Revision 1.7  1997/12/01 09:08:30  cjm
 * Add routines to initialise Zernike terms
 *
 * Revision 1.6  1997/11/18 15:34:03  cjm
 * Add M2ZServo routine for absorbing focus errors
 *
 * Revision 1.5  1997/11/18 08:30:23  cjm
 * Add support for fast focus guide errors
 *
 * Revision 1.4  1997/11/10 15:44:41  cjm
 * Add support for M1 displacements
 *
 * Revision 1.3  1997/04/03 14:33:43  cjm
 * Fix bug in chop throw scale
 *
 * Revision 1.2  1997/03/24 15:16:39  cjm
 * Add new routines to check M2 limits
 *
 * Revision 1.1  1997/02/10 17:10:48  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1997/01/20 09:07:52  cjm
 * Add tcsOpticsM2DzUser routine
 *
 * Revision 1.3  1997/01/17 18:18:39  cjm
 * Correct x,y probe positions and generate focus demand
 *
 * Revision 1.2  1997/01/16 10:44:40  cjm
 * Add support for tip/tilt/focus models of M2
 *
 * Revision 1.1  1997/01/14 16:30:50  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <iocsh.h> 
#include <math.h>
#include <time.h>
#include <epicsMutex.h>
#include <sys/stat.h>

#include <dbDefs.h>
#include <alarm.h>
#include <genSubRecord.h>
#include <subRecord.h>

#include "tcsConstants.h"
#include "tcsPointing.h"
#include "tcsProbeLib.h"
#include "tcsDecode.h"
#include "tcsOptics.h"
#include "tcsRandom.h"
#include "timeLib.h"
#include "cad.h"

/* define the maximum number of Zernikes to compute as well as the number
*  of terms that could contribute to each one.
*/

#define MAXZERNIKES 19
#define MAXENTRIES 11
#define MAXZERNCOEFFS 14

/* Define constants to refer to the various sources of AO data */
#define PWFS1_AO_SOURCE 0
#define PWFS2_AO_SOURCE 1
#define OIWFS_AO_SOURCE 2
#define HRWFS_AO_SOURCE 3
#define ALTAIR_AO_SOURCE 4
#define GEMS_AO_SOURCE 5
#define GAOS_AO_SOURCE 6

static double flDefs[NUMTOPENDS] = {128000.0, 48000.0, 14400.0};
static double m2CurvDefs[NUMTOPENDS] = {-1.0/4193.0685, -1.0/12131.868, 0.0};
static double m2SepDefs[NUMTOPENDS] = {12539.326, 10155.00, 0.0};
static double optDistDefs[NUMTOPENDS] = {40.632, 0.0, 0.0};
static double imageCurvDefs[NUMTOPENDS] = {1/1926.087, 1/4537.0, 0.0};
static double m2CofGDefs[NUMTOPENDS] = {51.0, 0.0, 0.0} ;
static double m1Curvature = -1.0/28800; /* Nominal curvature of M1 */
static double backFocus = 4000.0;       /* Back focal distance */
static double pwfs1FplaneSep = 1995.0;  /* Height of pwfs1 above focal plane */
static double pwfs2FplaneSep = 1610.0;  /* Height of pwfs2 above focal plane */

static TOPEND topEnd;              /* Current top end in use */
static double flNominal;           /* Current nominal focal length (mm) */
static double flCurrent;           /* Current focal length (mm) */
static double m2Separation;        /* M1 to M2 separation */
static double optDistCoeff;        /* Optical distortion coeff */
static double m2Curvature;         /* Curvature of M2 */
static double imageCurvature;      /* Curvature of image plane */
static double deltaZ;              /* Shift in Z due to M1 & M2 (mm) */
static double m2Mag;               /* Magnification due to M2 */
static double m2CofG ;             /* Position of M2 C of G (mm) */

/* Matrix to compute Zernike terms */
static double zMatrix[MAXZERNIKES][MAXENTRIES] ;
static double m1XUserOffset;       /* User offset to X (mm) */
static double m1YUserOffset;       /* User offset to Y (mm) */
static double m1ZUserOffset;       /* User offset to Z (mm) */
static double m1XRotUserOffset;    /* User offset to X rotation (rads) */
static double m1YRotUserOffset;    /* User offset to Y rotation (rads) */
static double m1ZRotUserOffset;    /* User offset to Z rotation (rads) */
static double m2XRotOffset[3];     /* X offset due to rotation about C of G */
static double m2YRotOffset[3];     /* Y offset due to rotation about C of G */

/* Coefficients for open loop model of Zernike corrections for M1 */
static double m1ZernCoeffs[MAXZERNCOEFFS][3] ;    /* Current model */
static double m1NewZernCoeffs[MAXZERNCOEFFS][3] ; /* New potential model */
static double m1LastFigure[MAXZERNCOEFFS] ;       /* Last figure model */
static double m1SavedModel[MAXZERNCOEFFS] ;       /* Saved model */
static double m1CurrentIncr[MAXZERNCOEFFS] ;      /* Latest model increments */
static double m1TotalFigure[MAXZERNCOEFFS] ;      /* Total model */
static int m1OpenLoopInit    = TRUE  ;            /* Init open loop model */
static int m1ZeroModel       = 0;                 /* Zero model on init */
static int m1RestoreModel    = 0;                 /* Restore model on init */
static int m1RestoreModelType = 0;                /* Which model to restore */
static int m1SaveModelType = 0;                   /* Which model to save */
static char m1RestoreFile[MAX_STRING_SIZE];       /* Last restored file */
static char m1RestoreTime[MAX_STRING_SIZE];       /* Time of last restore */
static int m1AOModelValid ;                       /* Is AO model valid */
static int m1ModelValid ;                         /* Is non-AO model valid */
static int m1GPIModelValid ;                      /* Is GPI model valid */

/* Coefficients of empirical model to correct for offaxis astigmatism */
static double astig0[7] =  {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0} ;  
static double astig45[7] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0} ; 

/* Coefficients etc. for corrections for coma via tilt */
static double m2ComaTiltCoeffs[3] ;  /* Coefficients */
static double m2NominalPosn[5] ;     /* Nominal demanded position of M2 */
static double m2ComaTilt ;           /* Current coma tilt (arcsec) */

/* Guide parameters for M1 */
static double latestAoZtoM1[MAXZERNIKES] ; /* aO Zernike demands to M1 */
static double latestZtoM1[MAXZERNCOEFFS] ; /* Total Zernike demands to M1 */
static M1WEIGHT m1AoWeight = NOWEIGHTS; /* Weighting scheme for combining aO data */
static long m1AoFrames = 1;        /* No. of WFS frames to average */
static int p1AoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int p2AoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int oiAoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int hrAoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int aoAoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int gsAoAveraging = FALSE ; /* Flag for controlling aO averaging */
static int currM1AoSource = PWFS1_AO_SOURCE ;  /* usually data is from P1 */
static int prevM1AoSource = PWFS1_AO_SOURCE ;
static int pwfs1Measuring = 0 ;    /* Is P1 integrating ? */
static int pwfs2Measuring = 0 ;    /* Is P2 integrating */
static int oiwfsMeasuring = 0 ;    /* Is OIWFS integrating */
static int hrwfsMeasuring = 0 ;    /* Is HRWFS integrating */
static int altairMeasuring = 0;    /* Is Altair integrating */
static int gemsMeasuring = 0;      /* Is GeMS integrating */
static double aoExpTime  = 0.1 ;   /* aO data exposure time */
static int    aoNumFrames = 1 ;    /* Num of aO frames to coadd */

static double m2XNominal;          /* Nominal X position of M2 (mm) */
static double m2XUserOffset;       /* User offset to X (mm) */
static double m2XTempCorr;         /* Current temp. correction to X (mm) */
static double m2XModelCorr;        /* Current model correction to X (mm) */
static double m2XErrorCorr;        /* Current error correction to X (mm) */
static double m2XDemand;           /* Total X demand */
static double m2ZTempRef;          /* Reference temperature for model */

static double m2YNominal;          /* Nominal Y position of M2 (mm) */
static double m2YUserOffset;       /* User offset to Y (mm) */
static double m2YTempCorr;         /* Current temp. correction to Y (mm) */
static double m2YModelCorr;        /* Current model correction to Y (mm) */
static double m2YErrorCorr;        /* Current error correction to Y (mm) */
static double m2YDemand;           /* Total Y demand */

static int m2XYTempEnable = TRUE;  /* Enable/disable temperature corrections */
static int m2XYModelEnable = TRUE; /* Enable/disable model corrections */

static double m2ZNominal;          /* Nominal Z position of M2 (mm) */
static double m2ZUserOffset;       /* User offset to Z (mm) */
static double m2ZInsOffset ;       /* Instrument offset to Z (mm) */
static double m2ZTempCorr;         /* Current temp. correction to Z (mm) */
static double m2ZModelCorr;        /* Current model correction to Z (mm) */
static double m2ZErrorCorr;        /* Current error correction to Z (mm) */
static double m2ZDemand;           /* Total Z demand */

static int m2ZTempEnable = TRUE;   /* Enable/disable temperature corrections */
static int m2ZModelEnable = TRUE;  /* Enable/disable model corrections */

static double m2XTiltNominal;      /* Nominal X position of M2 (rads) */
static double m2XTiltTempCorr;     /* Current temp. correction to X (rads) */
static double m2XTiltModelCorr;    /* Current model correction to X (rads) */
static double m2XTiltErrorCorr;    /* Current error correction to X (rads) */
static double m2XTiltUser[3];      /* User defined tilt (rads) */
static double m2XTiltDemand;       /* Total X demand */

static double m2YTiltNominal;      /* Nominal Y position of M2 (rads) */
static double m2YTiltTempCorr;     /* Current temp. correction to Y (rads) */
static double m2YTiltModelCorr;    /* Current model correction to Y (rads) */
static double m2YTiltErrorCorr;    /* Current error correction to Y (rads) */
static double m2YTiltUser[3];      /* User defined tilt (rads) */
static double m2YTiltDemand;       /* Total Y demand */

static int m2TiltTempEnable = TRUE; /* Enable/disable temperature corrections */
static int m2TiltModelEnable = TRUE; /* Enable/disable model corrections */

/* M2 Guide mode flags */
static int m2AbsorbFocus = FALSE;  /* Enable/disable absorb focus errors */
static int m2ComaCorrect = FALSE;  /* Enable/disable coma corrections */

/* M2 limit data. The chop throw data are in M2 units */
 
static double m2MaxChopFreq ;      /* Maximum chop frequency (Hz) */
static double m2BreakChopFreq;     /* Chop frequency at break (Hz) */
static double m2MinChopFreq ;      /* Minimum chop frequency (Hx) */
static double m2MaxChopFreqThrow ; /* Maximum permitted throw (rads) */
static double m2BreakChopFreqThrow ; /* Chop throw at break (rads) */
static double m2MinChopFreqThrow ; /* Chop throw at min. freq (rads) */

static double m2MinTilt ;          /* Minimum Tilt (arcsec) */
static double m2MaxTilt ;          /* Maximum Tilt (arcsec) */
static double m2MinTiltZ;          /* Maximum Z at minimum tilt (mm) */
static double m2MaxTiltZ;          /* Maximum Z at maximum tilt (mm) */
 
static int optPointAdj ;           /* 1 = adjust pointing for optics shifts */
static double caOptics ;           /* ca due to tilts/translations of M1 & M2 */
static double ceOptics ;           /* ce due to tilts/translations of M1 & M2 */

epicsMutexId opticsSemId;          /* Mutex for optics model */

/* Flags used in truss temperature calculation */
static int waitForFirstConnect1 = TRUE ;
static int waitForFirstConnect2 = TRUE ;

/* Function prototypes for internal routines */

static void tcsOpticsM2Coma (double z5, double z6 ) ;

static void tcsOpticsM2ModelXY (double xcoeff1, double xcoeff2, 
                                double ycoeff1, double ycoeff2,
                                double *xcorr, double *ycorr);

static void tcsOpticsM2ThermalXY (double tempDef, double xcoeff, 
                                  double ycoeff, double *xcorr, double *ycorr);

static void tcsOpticsM2ModelZ (double zcoeff1, double zcoeff2, double *zcorr) ;

static void tcsOpticsM2ThermalZ (double ttemp, double tempDef, double zcoeff, 
                                 double *zcorr);

static void tcsOpticsM2ModelTilt (double xcoeff, double ycoeff,
                                double *xcorr, double *ycorr);

static void tcsOpticsM2ThermalTilt (double tempDef, double xcoeff, 
                                  double ycoeff, double *xcorr, double *ycorr);

/*+
 *   Function name:
 *   tcsOpticsMedian
 *
 *   Purpose:
 *   Find the median of an array of data
 *
 *   Description:
 *   Find the median of an array of data by a simple sort in place.
 *   For efficiency reasons this shouldn't be used for arrays greater than
 *   about 20 elements. The array passed in is modified such that the 
 *   elements are arranged in order. The median value returned is the
 *   n/2 element of the sorted array.
 *
 *   Invocation:
 *   tcsOpticsMedian(n, data)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   n        (int)        Number if elements in the array
 *      (!)   data     (double [])  Pointer to data array 
 *
 *   Function value:
 *   (<)  median  (double) Median value of the array 
 *
 *-
 */

double tcsOpticsMedian(int n, double data[]) {

  int i, j;
  double val ;

  for (j = 1; j < n; j++) {
    val = data[j];
    i = j - 1;
    while (i > -1 && data[i] > val) {
      data[i+1] = data[i];
      i--;
    }
    data[i+1] = val ;
  }

  return data[n/2] ;

}

/*+
 *   Function name:
 *   tcsOpticsAoAv
 *
 *   Purpose:
 *   Update the AoAveraging flags
 *
 *   Description:
 *   This routine is called periodically to check which WFS are integrating.
 *   The flags that tell the TCS whether it can potentially average
 *   the aO data from the WFS are then updated accordingly.
 *
 *   Invocation:
 *   tcsOpticsAoAv(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   psub     (struct subRecord *)  Pointer to subroutine record 
 *
 *   Epics inputs:
 *   a => flag to show if PWFS1 is integrating
 *   b => flag to show if PWFS2 is integrating
 *   c => flag to show if OIWFS is integrating
 *   d => flag to show if HRWFS is integrating
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *   Deficiencies:
 *   This routine used to be called tcsOpticsAoAverage but the name had
 *   to be abbreviated to fit the constraints of the subroutine record.
 *   The SNAM field can only be 16 characters long.
 * 
 *-
 */

long tcsOpticsAoAv (struct subRecord *psub) 
{
  pwfs1Measuring = psub->a ;
  pwfs2Measuring = psub->b ;
  oiwfsMeasuring = psub->c ;
  hrwfsMeasuring = psub->d ;
  return 0 ;
}


/*+
 *   Function name:
 *   tcsOpticsApplyDist
 *
 *   Purpose:
 *   Applies an optical distortion correction to an position in focal plane.
 *
 *   Description:
 *   The RC design of the Gemini optics results in an almost linear focal
 *   plane scale. This routine calculates the very small departure from
 *   linearity. In the F/16 configuration, the distortion is approx 0.1 arcsec
 *   8 arcmin from the optic axis. The non-linearity is modelled by an
 *   r**3 dependence.
 *
 *   Invocation:
 *   tcsOpticsApplyDist (x, y, &xd, &yd)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     x       (double)   Nominal X position in focal plane (rads)
 *      (>)     y       (double)   Nominal Y position in focal plane (rads)
 *      (<)     xd      (double *) Corrected X position (rads)
 *      (<)     yd      (double *) Corrected Y position (rads)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   tcsOpticsSetTopEnd must have been called to set an appropriate value
 *   for the distortion coefficient.
 *-
 */

void tcsOpticsApplyDist( double x, double y, double *xd, double *yd)
{
  double r0sq ;          /* Square of radial distance from optics centre */
  double scale ;         /* Scale factor to apply to input coords */

  r0sq = x * x + y * y ;
  scale = 1 + optDistCoeff * r0sq ;

  *xd = x * scale ;
  *yd = y * scale ;
 
}

/*+
 *   Function name:
 *   tcsOpticsAverageAo
 *
 *   Purpose:
 *   Average Ao data from PWFS1, PWFS2, OIWFS or HRWFS before sending to PCS
 *
 *   Description:
 *   This routine is triggered into action when the wfsStartMeasure command is
 *   issued and switched off when the wfsStopMeasure command is given. It
 *   pulls in the aO data from the relevant WFS and averages and
 *   combines it in accordance with the parameters set by the m1GuideConfig
 *   command. Note that this happens whether or not the data is actually
 *   being sent to the PCS. When the data has been averaged for long 
 *   enough a flag is set to indicate to the downstream code that new
 *   Zernike corrections are available. Data that is received when the M1
 *   actuators are moving is discarded. The only data of interest is that
 *   when the mirror has settled.
 *   For PWFS2 and the OIWFS the only corrections available are astigmatism.
 *   Note that this routine used to work out when it was time to send data
 *   to M1 by an update interval (in secs). This has been changed 
 *   temporarily (?) to use a simple number of frames. This is due to not
 *   currently having access to the WFS integration time and a very large
 *   and uncertain time delay between the WFS measuring the data and it
 *   being sent to the TCS.
 *
 *   Invocation:
 *   tcsOpticsAverageAo(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *      b => Zernike terms and their errors for PWFS1
 *      d => Zernike terms and their errors for PWFS2
 *      f => Zernike terms and their errors for OIWFS 
 *      h => Zernike terms and their errors for HRWFS 
 *      j => Zernike terms and their errors for Altair 
 *      l => Flag to indicate if M1 is moving
 *      n => Zernike terms and their errors for GeMS
 *
 *   Epics outputs:
 *      vala => data ready flag, 1 if there is new data for M1
 *      valb => current estimate of Z1 (Zemax convention)
 *      valt => current estimate of Z19
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   At the moment there is no check that the oiwfs in use hasn't been
 *   changed. Potentially we could continue to use say GMOS's OIWFS
 *   even though we are now using NIRI. This would only happen if the
 *   GMOS OIWFS integrations weren't stopped however.
 *
 *-
 */

long tcsOpticsAverageAo (struct genSubRecord *pgsub)
{
 
  static int reInit = TRUE ;          /* Flag to re-initialise data arrays */
  static double wfsSumZ[MAXZERNIKES]; /* Summed Zernike terms for WFS */
  static double wfsWeightsZ[MAXZERNIKES]; /* Summed weights for WFS */
  double wfsZ[MAXZERNIKES] ;       /* Current Zernike corrections from WFS */
  double currentZtoM1[MAXZERNIKES]; /* Current Zernike estimate for M1 */
  double wfsData[40] ;               /* Data from WFS */
  static int wfsNumCoeffs ;        /* Number of Zernikes supplied for WFS */
  static double wfsPrevTime ;      /* Time of last ao data sample */
  static int firstSample = TRUE ; /* Flag to indicate this is first sample */
  static double timeStart ;       /* Time of start of first sample */
  int i ;                         /* Loop counter */
  int dataReady ;                 /* Flag to indicate data is ready for M1 */
  long m1Moving ;                 /* Flag to show if M1 is moving */
  static int numFrames = 0 ;      /* Number of frames averaged so far */

/* Initialise dataReady flag. This must be output every time this routine is
*  called. It will be set to 1 whenever there is data available for M1 and
*  reset to 0 on the next call to this routine
*/
  dataReady = 0 ;
  
  m1Moving = *(long *)pgsub->l ;
 
/* Check if it is time to re-initialise the data arrays. The arrays must
*  be initialised if a) the current WFS has been changed by the user b) if
*  a particular WFS has been being used for AO data and is now no longer
*  integrating. 
*/

  if (currM1AoSource != prevM1AoSource) {
    reInit = TRUE ;
    prevM1AoSource = currM1AoSource ;

/* If the source of data has changed then reset all the AoAveraging flags
*  The currently selected source will get reset later if it is integrating
*/
    p1AoAveraging = FALSE ;
    p2AoAveraging = FALSE ;
    oiAoAveraging = FALSE ;
    hrAoAveraging = FALSE ;
    aoAoAveraging = FALSE ;
    gsAoAveraging = FALSE ;
  }

  if (!pwfs1Measuring && p1AoAveraging) {
    p1AoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (!pwfs2Measuring && p2AoAveraging) {
    p2AoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (!oiwfsMeasuring && oiAoAveraging ) {
    oiAoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (!hrwfsMeasuring && hrAoAveraging ) {
    hrAoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (!altairMeasuring && aoAoAveraging ) {
    aoAoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (!gemsMeasuring && gsAoAveraging ) {
    gsAoAveraging = FALSE ;
    reInit = TRUE ;
  }

  if (reInit) {
    for (i = 0 ; i < MAXZERNIKES ; i++ ) {
       wfsSumZ[i] = 0.0 ;
       wfsWeightsZ[i] = 0.0 ;
       latestAoZtoM1[i] = 0.0 ;
    }
    reInit = FALSE ;
    firstSample = TRUE ;
    timeNow (&timeStart) ;
    wfsPrevTime = timeStart ;
    numFrames = 0 ;
  }

/* Check if a WFS has come on line and is currently selected to be used to
*  provide M1 zernike data. Remember to turn off the other WFS.
*/
   if (pwfs1Measuring && currM1AoSource == PWFS1_AO_SOURCE) {
     hrAoAveraging = FALSE ;
     p1AoAveraging = TRUE ;
     p2AoAveraging = FALSE ;
     oiAoAveraging = FALSE ;
     aoAoAveraging = FALSE ;
     gsAoAveraging = FALSE ;
   } else if (pwfs2Measuring && currM1AoSource == PWFS2_AO_SOURCE) {
     hrAoAveraging = FALSE ;
     p2AoAveraging = TRUE ;
     p1AoAveraging = FALSE ;
     oiAoAveraging = FALSE ;
     aoAoAveraging = FALSE ;
     gsAoAveraging = FALSE ;
   } else if (hrwfsMeasuring && currM1AoSource == HRWFS_AO_SOURCE) {
     hrAoAveraging = TRUE ;
     oiAoAveraging = FALSE ;
     p1AoAveraging = FALSE ;
     p2AoAveraging = FALSE ;
     aoAoAveraging = FALSE ;
     gsAoAveraging = FALSE ;
   } else if (oiwfsMeasuring && currM1AoSource == OIWFS_AO_SOURCE) {
     hrAoAveraging = FALSE ;
     oiAoAveraging = TRUE ;
     p1AoAveraging = FALSE ;
     p2AoAveraging = FALSE ;
     aoAoAveraging = FALSE ;
     gsAoAveraging = FALSE ;
   } else if (altairMeasuring && currM1AoSource == ALTAIR_AO_SOURCE) {
     hrAoAveraging = FALSE ;
     oiAoAveraging = FALSE ;
     p1AoAveraging = FALSE ;
     p2AoAveraging = FALSE ;
     aoAoAveraging = TRUE ;
     gsAoAveraging = FALSE ;
   } else if (gemsMeasuring && currM1AoSource == GEMS_AO_SOURCE) {
     hrAoAveraging = FALSE ;
     oiAoAveraging = FALSE ;
     p1AoAveraging = FALSE ;
     p2AoAveraging = FALSE ;
     aoAoAveraging = FALSE ;
     gsAoAveraging = TRUE ;
   }

/* If averaging is turned on, read the data from the A&G and if it is new
*  add it into the accumulators after checking for validity
*/

   if (p1AoAveraging || p2AoAveraging || oiAoAveraging || hrAoAveraging ||
       aoAoAveraging || gsAoAveraging) {

/* Fetch data from A&G */
     if (currM1AoSource == PWFS1_AO_SOURCE) {
       memcpy(wfsData, pgsub->b, 40 * sizeof(double)) ;
     } else if (currM1AoSource == PWFS2_AO_SOURCE) {
       memcpy(wfsData, pgsub->d, 40 * sizeof(double)) ;
     } else if (currM1AoSource == OIWFS_AO_SOURCE) {
       memcpy(wfsData, pgsub->f, 40 * sizeof(double)) ;
     } else if (currM1AoSource == HRWFS_AO_SOURCE) {
       memcpy(wfsData, pgsub->h, 40 * sizeof(double)) ;
     } else if (currM1AoSource == ALTAIR_AO_SOURCE) {
       memcpy(wfsData, pgsub->j, 40 * sizeof(double)) ;
     } else if (currM1AoSource == GEMS_AO_SOURCE) {
       memcpy(wfsData, pgsub->n, 40 * sizeof(double)) ;
     }

     if (firstSample ) {
/* Check that the data read from the A&G is not out of date */
      if (wfsData[0] > timeStart) {
        firstSample = FALSE ;
        wfsPrevTime = timeStart ;
        timeStart = wfsData[0] ;
        wfsNumCoeffs = (int)floor(wfsData[1]) ;
      } else {                    /* Data is still out of date so just exit */
        *(long *)pgsub->vala = dataReady ;
        return 0 ;
      }
     }

/* Add in data if it is new. If it isn't then nothing needs to be done and
*  we just exit at the end of this routine
*/
     if (wfsPrevTime != wfsData[0] && !m1Moving) {
       numFrames++ ;
       for (i = 0 ; i < wfsNumCoeffs ; i++ ) {
          if (m1AoWeight == NOWEIGHTS) {
            wfsData[21+i] = 1.0 ;
            wfsData[21+i] = 1.0 ;
          } else {
            if (wfsData[21+i] != 0.0) {
              wfsData[21+i] = 1.0/(wfsData[21+i] * wfsData[21+i]) ;
            }
          }      
          wfsSumZ[i] += wfsData[2+i] * wfsData[21+i] ;
          wfsWeightsZ[i] += wfsData[21+i] ;

/* Form the latest Zernike estimate */
         if (wfsWeightsZ[i] != 0.0)
           wfsZ[i] = wfsSumZ[i] / wfsWeightsZ[i] ;
         else
           wfsZ[i] = 0.0 ;
         
         currentZtoM1[i] = wfsZ[i] ;

       }      /* end for loop */

/* Make sure all output data has been initialised */
       if (wfsNumCoeffs < MAXZERNIKES) {
         for (i = wfsNumCoeffs; i < MAXZERNIKES; i++ ) {
            currentZtoM1[i] = 0.0 ;
         }
       }

/* Output the current best estimate of the corrections to be applied to M1 */
       *(double *)pgsub->valb = currentZtoM1[0] ;  /* tip */
       *(double *)pgsub->valc = currentZtoM1[1] ;  /* tilt */ 
       *(double *)pgsub->vald = currentZtoM1[2] ;  /* focus */ 
       *(double *)pgsub->vale = currentZtoM1[3] ;  /* astigmatism */ 
       *(double *)pgsub->valf = currentZtoM1[4] ;  /* astigmatism */ 
       *(double *)pgsub->valg = currentZtoM1[5] ;  /* coma */ 
       *(double *)pgsub->valh = currentZtoM1[6] ;  /* coma */ 
       *(double *)pgsub->vali = currentZtoM1[7] ;  /* spherical */ 
       *(double *)pgsub->valj = currentZtoM1[8] ;  /* trefoil */ 
       *(double *)pgsub->valk = currentZtoM1[9] ;  /* trefoil */ 
       *(double *)pgsub->vall = currentZtoM1[10] ;  
       *(double *)pgsub->valm = currentZtoM1[11] ;  
       *(double *)pgsub->valn = currentZtoM1[12] ;  
       *(double *)pgsub->valo = currentZtoM1[13] ;  
       *(double *)pgsub->valp = currentZtoM1[14] ;  
       *(double *)pgsub->valq = currentZtoM1[15] ;  
       *(double *)pgsub->valr = currentZtoM1[16] ;  
       *(double *)pgsub->vals = currentZtoM1[17] ;  
       *(double *)pgsub->valt = currentZtoM1[18] ;  
       
/* Check to see if it is time to flag that new data is available */

/* Comment out the next line temporarily */
/*
       if (wfsData[0] - timeStart + aoExpTime*aoNumFrames > m1AoInterval ) {
*/
       if (numFrames == m1AoFrames) {
         for (i = 0 ; i < wfsNumCoeffs ; i++ ) {
           latestAoZtoM1[i] = currentZtoM1[i] ;
         } 
         tcsOpticsM2Coma (currentZtoM1[5], currentZtoM1[6]) ;
         dataReady = 1 ;

/* Reset start time for next integration period to be the time of the latest
*  data from the A&G
*/
         timeStart = wfsData[0] ;
         firstSample = TRUE ;
         numFrames = 0 ;

/* Reset arrays ready for next set of averages */
         for (i = 0; i < MAXZERNIKES ; i++ ) {
           wfsSumZ[i] = 0.0 ;
           wfsWeightsZ[i] = 0.0 ;
         }    
       }
 
       wfsPrevTime = wfsData[0] ;

     }           /* End of code executed when there is new data */
     
   }             /* End of code executed when data is being averaged */

   *(long *)pgsub->vala = dataReady ;

   return 0 ;
}


/*+
 *   Function name:
 *   tcsOpticsCalcM1Moving
 *
 *   Purpose:
 *   Generate the m1Moving flag to control the averaging of aO data
 *
 *   Description:
 *   If the M1 actuators are moving then we need to indicate this to
 *   other software components. Rather than using a simple test that if
 *   the number of actuators moving is greater than n then set m1Moving to
 *   TRUE otherwise set m1Moving FALSE, a deadband is used to prevent the
 *   flag toggling backwards and forwards too often. The deadband limits etc.
 *   are read from EPICS records to allow them to be controlled from the
 *   user interface. 
 *   If the PCS isn't loaded we expect to read the number of moving actuators
 *   as 0 and so will always set the m1Moving flag to FALSE in this 
 *   situation.
 *
 *   Invocation:
 *   tcsOpticsCalcM1Moving(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     pgsub   (struct genSubRecord *)  Pointer to gensub
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *
 *   a => Lower limit to deadband
 *   b => Upper limit to deadband
 *   c => Centre of deadband
 *   d => Number of actuators moving in M1
 *
 *   Epics outputs:
 *   vala => Flag to show M1 moving (= 1) or not (= 0)
 *   valb => Currently used lower limit 
 *   valc => Currently used upper limit 
 *   vald => Currently used centre limit
 *   vale => Message to show if M1 is stabilised or not
 *
 *-
 */

long tcsOpticsCalcM1Moving (struct genSubRecord *pgsub) 
{

  int lowLimit ;           /* Deadband lower limit */
  int highLimit ;          /* Deadband high limit */
  int centreLimit ;        /* Deadband centre */
  int numMoving ;          /* Number of actuators moving in M1 */
  int m1Moving ;           /* Flag to show M1 moving */
  static int prevNumMoving = 0 ; /* No. of actuators moving previously */
  char mess[40] ;          /* Message to go with flag */

  m1Moving = FALSE ;

/* Fetch all EPICS inputs */
  lowLimit = *(long *)pgsub->a ;
  highLimit = *(long *)pgsub->b ;
  centreLimit = *(long *)pgsub->c ;
  numMoving = *(long *)pgsub->d ;

/* Check the inputs for validity */
  if (lowLimit > highLimit) {
    lowLimit = highLimit ;
    centreLimit = lowLimit ;
  } else if (centreLimit > highLimit || centreLimit < lowLimit) {
    centreLimit = (lowLimit + highLimit) / 2 ;
  }

/* Now set the M1 moving flag. Once the number of actuators has moved into
*  the deadband area and croseed the threshold of centreLimit, the flag
*  does not change value until it exists from teh deadband area 
*/
  if (numMoving < lowLimit ) {
    prevNumMoving = numMoving ;
    m1Moving = FALSE ;
  } else if (numMoving > highLimit) {
    prevNumMoving = numMoving ;
    m1Moving = TRUE ;
  } else {                          /* We're in the deadband area */
    if (numMoving > centreLimit && prevNumMoving < lowLimit) {
      m1Moving = TRUE ;
    } else if (numMoving < centreLimit && prevNumMoving > highLimit) {
      m1Moving = FALSE ;
    }
  }

  *(long *)pgsub->vala = m1Moving ;
  if (m1Moving)
    strcpy (mess, "M1 not settled");
  else
    strcpy (mess, "M1 settled");

/* the following are for possible diagnostic purposes */
  *(long *)pgsub->valb = lowLimit ;
  *(long *)pgsub->valc = highLimit ;
  *(long *)pgsub->vald = centreLimit ;
  strcpy (pgsub->vale, mess );

  return 0 ;
    
}

/*+
 *   Function name:
 *   tcsOpticsM1FileStatus
 *
 *   Purpose:
 *   Provide status for the restored m1 models
 *
 *   Description:
 *   On first execution, initialize data. On subsequent calls just
 *   report the data that has been set elsewhere
 *
 *   Invocation:
 *   tcsOpticsM1FileStatus(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     pgsub   (struct genSubRecord *)  Pointer to gensub
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics outputs:
 *   vala => M1 model name e.g. non-AO, AO or GPI 
 *   valb => File name from which the last model was restored
 *   valc => Date and time of last file restore or zero invocation 
 *
 *-
 */

long tcsOpticsM1FileStatus (struct genSubRecord *pgsub) 
{
  static int first = 1 ;

  char *fileTypes[] = {"non-AO",
                       "AO",
                       "GPI"};

  char fileType[MAX_STRING_SIZE];
  double tai ;
  int ymdhmsf[7];

  if (first) {
    strcpy(m1RestoreFile, "None");
    timeNow(&tai);
    timeThenC(tai, UTC, 4, ymdhmsf);
    sprintf(m1RestoreTime, "%4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
            ymdhmsf[0], ymdhmsf[1], ymdhmsf[2], ymdhmsf[3], ymdhmsf[4],
            ymdhmsf[5]);
    first = 0; 
  }
  
  strcpy(fileType, fileTypes[m1SaveModelType]);

/* Now output the results */
  strcpy(pgsub->vala, fileType);
  strcpy(pgsub->valb, m1RestoreFile);
  strcpy(pgsub->valc, m1RestoreTime);

  return 0 ;
    
}

/*+
 *   Function name:
 *   tcsOpticsCalcM1ValidFlags
 *
 *   Purpose:
 *   Generate validity flags for saved M1 models
 *
 *   Description:
 *   This routine computes the values of the validity flags for the
 *   two M1 models that the TCS regularly saves. A reason for the 
 *   value of the flag is also produced.
 *
 *   Invocation:
 *   tcsOpticsCalcM1ValidFlags(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     pgsub   (struct genSubRecord *)  Pointer to gensub
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *
 *   a => Maximum age a file can be and still be valid 
 *
 *   Epics outputs:
 *   vala => Flag to show if saved AO model is valid (= 1) or not (= 0)
 *   valb => Reason for validity flag 
 *   valc => Flag to show if saved non-AO model is valid (= 1) or not (= 0)
 *   vald => Reason for validity flag 
 *
 *-
 */

long tcsOpticsCalcM1ValidFlags (struct genSubRecord *pgsub) 
{
  double maxage ;            /* Maximum allowed age (hours) */
  long   maxagesecs;         /* Maximum age in seconds */
  char messGPI[40] ;         /* Message to go with flag */
  char messAO[40] ;          /* Message to go with flag */
  char mess[40] ;            /* Message to go with flag */
  char fileAO[40];           /* Name of AO file */
  char filenonAO[40];        /* Name of non AO file */
  char fileGPI[40];          /* Name of GPI file */
  char *prefix ;
  char recname[40] ;

/* Fetch all EPICS inputs */
  maxage = *(double *)pgsub->a ;

/* Default to 24 hrs if an invalid age is provided */
  if (maxage <= 0.0) maxage = 24.0;

  maxagesecs = (long)(maxage*3600.0) ;

/* Now get record name prefix so we can construct the names of the 
 * files to look for 
 */
  strcpy(recname, pgsub->name);
  prefix = strtok(recname, ":");

  strcpy(fileGPI, "./data/");
  strcat(fileGPI, prefix);
  strcat(fileGPI, "M1RestoreGPI.pv"); 

  strcpy(fileAO, "./data/");
  strcat(fileAO, prefix);
  strcat(fileAO, "M1RestoreAO.pv"); 

  strcpy(filenonAO, "./data/");
  strcat(filenonAO, prefix);
  strcat(filenonAO, "M1Restore.pv"); 

/* Check that file is valid */
  m1GPIModelValid = tcsOpticsM1ModelValid(fileGPI, maxagesecs, messGPI);
  m1AOModelValid = tcsOpticsM1ModelValid(fileAO, maxagesecs, messAO);
  m1ModelValid   = tcsOpticsM1ModelValid(filenonAO, maxagesecs, mess);
  
/* Now output the results */
  *(long *)pgsub->vala = m1AOModelValid ;
  strcpy (pgsub->valb, messAO );
  *(long *)pgsub->valc = m1ModelValid ;
  strcpy (pgsub->vald, mess );
  *(long *)pgsub->vale = m1GPIModelValid ;
  strcpy (pgsub->valf, messGPI );

  return 0 ;
    
}

/*+
 *   Function name:
 *   tcsOpticsCheckAoModel
 *
 *   Purpose:
 *   Check aO model parameters for validity and update if OK
 *
 *   Description:
 *   The users input data for the empirical model that corrects for 
 *   off axis astigmatism is checked for validity. If the parameters
 *   fall within the allowed range then the data is stored in the 
 *   internal database for use by other software.
 *
 *   Invocation:
 *   tcsOpticsCheckAoModel (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     pgsub   (struct genSubRecord *)  Pointer to gensub
 *
 *   Epics inputs:
 *   a => Zero point for 0 astig (microns)
 *   b => Scale factor for 0 astig
 *   c => Phase angle for 0 astig (degrees)
 *   d => Zero point for 45 astig (microns)
 *   e => Scale factor for 45 astig
 *   f => Phase angle for 45 astig (degrees)
 *   g => Amplitude of cos 2t term (microns)
 *   h => Phase of cos 2t term (degs)
 *   i => Amplitude of cos t term (microns)
 *   j => Phase of cos t term (degs)
 *   k => Amplitude of cos 2t term for 45 astig (microns)
 *   l => Phase of cos 2t term for 45 astig (degs)
 *   m => Amplitude of cos t term for 45 astig (microns)
 *   n => Phase of cos t term  for 45 astig (degs)
 *
 *   Epics outputs:
 *   vala => Current zero point for 0 astig (microns)
 *   valb => Current scale factor for 0 astig
 *   valc => CurrenT phase angle for 0 astig (degrees)
 *   vald => Current zero point for 45 astig (microns)
 *   vale => CurrenT scale factor for 45 astig
 *   valf => Current phase angle for 45 astig (degrees)
 *   valg => current amplitude of cos 2t term (microns)
 *   valh => Phase of cos 2t term (degs)
 *   vali => Amplitude of cos t term (microns)
 *   valj => Phase of cos t term (degs)
 *   valk => Amplitude of cos 2t term for 45 astig (microns)
 *   vall => Phase of cos 2t term for 45 astig (degs)
 *   valm => Amplitude of cos t term for 45 astig (microns)
 *   valn => Phase of cos t term  for 45 astig (degs)
 *   valo => Possible error message
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *-
 */

#define MAXASTIGZERO 20.0
#define MINASTIGZERO -20.0
#define MAXASTIGSCALE 5.0
#define MINASTIGSCALE 0.0
#define MAXASTIGPHASE 360.0
#define MINASTIGPHASE -360.0

long tcsOpticsCheckAoModel (struct genSubRecord *pgsub) 
{
  double ast0Zero, ast0Scale, ast0Phase ;
  double ast45Zero, ast45Scale, ast45Phase ;
  double ast0A2, ast0A3, ast0P2, ast0P3 ;
  double ast45A2, ast45A3, ast45P2, ast45P3 ;
  char mess[MAX_STRING_SIZE] ;
  int dataValid ;

  strcpy(mess, " ") ;
  dataValid = 1 ;

/* Fetch all data from the input links */
  ast0Zero = *(double *)pgsub->a ;
  ast0Scale = *(double *)pgsub->b ;
  ast0Phase = *(double *)pgsub->c ;
  ast45Zero = *(double *)pgsub->d ;
  ast45Scale = *(double *)pgsub->e ;
  ast45Phase = *(double *)pgsub->f ;
  ast0A2     = *(double *)pgsub->g ;
  ast0P2     = *(double *)pgsub->h ;
  ast0A3     = *(double *)pgsub->i ;
  ast0P3     = *(double *)pgsub->j ;
  ast45A2    = *(double *)pgsub->k ;
  ast45P2    = *(double *)pgsub->l ;
  ast45A3    = *(double *)pgsub->m ;
  ast45P3    = *(double *)pgsub->n ;

  if (ast0Zero < MINASTIGZERO || ast0Zero > MAXASTIGZERO) {
    strcpy(mess, "Zero point for 0 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast45Zero < MINASTIGZERO || ast45Zero > MAXASTIGZERO) {
    strcpy(mess, "Zero point for 45 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast0Scale < MINASTIGSCALE || ast0Scale > MAXASTIGSCALE) {
    strcpy(mess, "Scale for 0 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast45Scale < MINASTIGSCALE || ast45Scale > MAXASTIGSCALE) {
    strcpy(mess, "Scale for 45 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast0Phase < MINASTIGPHASE || ast0Phase > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 0 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast45Phase < MINASTIGPHASE || ast45Phase > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 45 astig out of range") ; 
    dataValid = 0 ;
  } else if (ast0P2 < MINASTIGPHASE || ast0P2 > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 0 astig p2 out of range") ; 
    dataValid = 0 ;
  } else if (ast0P3 < MINASTIGPHASE || ast0P3 > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 0 astig p3 out of range") ; 
    dataValid = 0 ;
  } else if (ast45P2 < MINASTIGPHASE || ast45P2 > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 45 astig p2 out of range") ; 
    dataValid = 0 ;
  } else if (ast45P3 < MINASTIGPHASE || ast45P3 > MAXASTIGPHASE) {
    strcpy(mess, "Phase for 45 astig p3 out of range") ; 
    dataValid = 0 ;
  }
    
/* Store data for later use */
  if ((dataValid) &&(opticsSemId)) {
     epicsMutexLock(opticsSemId);
     astig0[0] = ast0Zero / 1000.0 ;
     astig0[1] = ast0Scale ;
     astig0[2] = ast0Phase * D2R ;
     astig0[3] = ast0A2 / 1000.0 ;
     astig0[4] = ast0P2 * D2R ;
     astig0[5] = ast0A3 / 1000.0 ;
     astig0[6] = ast0P3 * D2R ;
     astig45[0] = ast45Zero / 1000.0 ;
     astig45[1] = ast45Scale ;
     astig45[2] = ast45Phase * D2R ;
     astig45[3] = ast45A2 / 1000.0 ;
     astig45[4] = ast45P2 * D2R ;
     astig45[5] = ast45A3 / 1000.0 ;
     astig45[6] = ast45P3 * D2R ;
     epicsMutexUnlock(opticsSemId);

/* Write current data to links */
    *(double *)pgsub->vala = ast0Zero ;
    *(double *)pgsub->valb = ast0Scale ;
    *(double *)pgsub->valc = ast0Phase ;
    *(double *)pgsub->vald = ast45Zero ;
    *(double *)pgsub->vale = ast45Scale ;
    *(double *)pgsub->valf = ast45Phase ;
    *(double *)pgsub->valg = ast0A2 ;
    *(double *)pgsub->valh = ast0P2 ;
    *(double *)pgsub->vali = ast0A3 ;
    *(double *)pgsub->valj = ast0P3 ;

/* N.B. for the type of gensub symbol we are using it doesn't seem possible
*  to change the type of the outputs from VALK onwards. They have to be
*  strings. So, do the conversion to a string type here. This shouldn't
*  matter as these are only for display
*/
    sprintf (pgsub->valk, "%.2f", ast45A2) ;
    sprintf (pgsub->vall, "%.2f", ast45P2) ;
    sprintf (pgsub->valm, "%.2f", ast45A3) ;
    sprintf (pgsub->valn, "%.2f", ast45P3) ;
  }

  strcpy (pgsub->valo, mess) ;

  return 0 ;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsOpticsCheckChopLimits
 *
 *   Purpose:
 *   This routine checks that the chop throw and frequency are compatible
 *
 *   Description:
 *   The parameters throw and frequency that are acceptable by M2 are
 *   not independent of each other above a certain break frequency. 
 *   This routine checks that the values specified by the user are
 *   compatible. The routine assumes a linear relationship between throw
 *   and frequency both above and below the break. In practice it is
 *   expected that the throw is independent of frequency below the break
 *   but that is not assumed in this routine, only that the relationship
 *   is linear.
 *   The routine returns the throw limit (in arcsec on the sky) for the
 *   specified chop frequency as well as the maximum frequency for the 
 *   specified throw. 
 *
 *   Invocation:
 *   tcsOpticsCheckChopLimits (chopMode, freq, throw, &freqLimit,
 *                             &throwLimit, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  chopMode  (int)     2posn, 3posn or triangle
 *      (>)  freq      (double)  Requested frequency (Hz)
 *      (>)  throw     (double)  Requested throw (arcsec on sky)
 *      (<)  freqLimit (double *) Allowed max. freq for specified throw (Hz)
 *      (<)  throwLimit (double *) Allowed max. throw for given freq. (arcsec)
 *      (<)  mess      (char *)  Message
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */

int tcsOpticsCheckChopLimits (int chopMode, double freq, double throw,
        double *freqLimit, double *throwLimit, char *mess)

{
  double freqScale ;     /* Scale factor to handle 2 and 3 position chop */
  double minThrow ;      /* Local copy of minimum throw */
  double breakThrow;     /* Local copy of throw at break frequency */
  double maxThrow;       /* Local copy of throw at max. freq */
  double minFreq;        /* Local copy of minimum frequency */
  double breakFreq;      /* Local copy of break frequency */
  double maxFreq ;       /* Local copy of maximum frequency */
  double throw0;         /* Throw at "minimum" frequency */
  double freq0;          /* "minimum" frequency */
  double slope;          /* slope of throw/frequency relationship */
  double m2Throw ;       /* Required M2 throw (rads) */
  int status;            /* return status */
  double chopLimit;     /* Chop limit in M2 units */
  double throwScale;     /* Converts between user and M2 units */

  if (chopMode == THREEPOSN)
    freqScale = 0.5 ;
  else
    freqScale = 1.0;

/* Fetch local copies of global data */

  if (!opticsSemId) return 0;
  epicsMutexLock(opticsSemId);
   
  minFreq = m2MinChopFreq * freqScale;
  breakFreq = m2BreakChopFreq * freqScale;
  maxFreq = m2MaxChopFreq * freqScale;
  minThrow = m2MinChopFreqThrow;
  breakThrow = m2BreakChopFreqThrow;
  maxThrow = m2MaxChopFreqThrow;
  epicsMutexUnlock(opticsSemId);
  
  if (freq <= breakFreq)
  {
   slope = (minThrow - breakThrow)/ (minFreq - breakFreq);
   freq0 = minFreq;
   throw0 = minThrow;
  }
  else
  {
   slope = (breakThrow - maxThrow) / (breakFreq - maxFreq) ;
   freq0 = breakFreq ;
   throw0 = breakThrow;
  }

/* Convert user throw (arcsec on sky) into M2 units (radians) */

  m2Throw = tcsOpticsScaleThrow(throw * AS2R) ;
  throwScale = m2Throw / throw ;

/* Check for compatibility. The first checks are to ensure the maximum limits
 * are exceded. This should already have been done but repeat just in case.
*/

  if (freq > maxFreq) {
   *freqLimit = maxFreq;
   *throwLimit = maxThrow / throwScale ;
   sprintf(mess, "Max chop frequency %.1f (Hz) exceeded", *freqLimit);
   status = 1;
  } else if (m2Throw > minThrow) {
   *throwLimit = minThrow  / throwScale;
   *freqLimit = maxFreq;
   sprintf (mess, "Max chop throw %.1f (arcsec) exceeded", *throwLimit);
   status = 1;
  } else {
   chopLimit = slope * (freq - freq0) + throw0;
   *throwLimit = chopLimit / throwScale ;
   if (m2Throw > chopLimit)
   {
    sprintf (mess, "Max. chop %.1f (arcsec) at %.1f (Hz)", *throwLimit, freq);
    if (slope != 0.0) 
     *freqLimit = (m2Throw - throw0)/slope + freq0;
    else
     *freqLimit = freq0; 
    status = 1;
   } else {
    *freqLimit = freq;
    strcpy(mess, " ");
    status = 0;
   }
  }

  return status ;

}


/*+
 *   Function name:
 *   tcsOpticsCheckTiltLimits
 *
 *   Purpose:
 *   Checks that tilt and focus demands are compatible
 *
 *   Description:
 *   M2 limits for focus and tilt are not independent. The purpose of this
 *   routine is to check that the specified focus and tilt demands 
 *   are compatible. The routine assumes a linear relationship between
 *   focus and tilt up to the maximum tilt.
 *
 *   Invocation:
 *   status = tcsOpticsCheckTiltLimits (tilt, focus, &tiltLim, &zLimit,
 *                                     mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (code) <name>   <C type>   <parameter description>
 *      (>)   tilt   (double)  Tilt demand (arcsec on sky)
 *      (>)   zDemand  (double)  demand Z position (mm)
 *      (<)   tiltLim (double *) Tilt limit for this focus (arcsec on sky)
 *      (<)   zLimit (double *) Z limit for the demand tilt (mm)
 *      (<)   mess   (char *)  Return message 
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   Prior requirements:
 *   Tilt and focus limits should already have been set up via a call to
 *   tcsOpticsSetTiltLimits
 *
 *-
 */

int tcsOpticsCheckTiltLimits (double tilt, double zDemand, double *tiltLim,
                              double *zLim, char *mess)

{
 double tiltScale;         /* Converts user demands (arcsec) to M2 units */
 double slope ;            /* slope of tilt-focus relationship */
 double minTilt;           /* Minimum tilt of M2 (rads) */
 double maxTilt;           /* Maximum tilt of M2 (rads) */
 double minTiltZ;          /* Maximum Z corresponding to minimum tilt (mm) */
 double maxTiltZ;          /* Maximum Z corresponding to maximum tilt (mm) */
 double tilt0;     
 double tiltZ0;
 int status;               /* return status */
 double zLimit;            /* Z limit for given tilt */
 double m2Tilt ;           /* Tilt of M2 (rads) for given user tilt */

 if (! opticsSemId)return 0;
 
 epicsMutexLock(opticsSemId);
 minTilt = m2MinTilt ;
 maxTilt = m2MaxTilt;
 minTiltZ = m2MinTiltZ;
 maxTiltZ = m2MaxTiltZ;
 epicsMutexUnlock(opticsSemId);

 slope = (minTiltZ - maxTiltZ) / (minTilt - maxTilt);
 tilt0 = minTilt;
 tiltZ0 = minTiltZ;

/* Convert user demanded tilt into (positive) M2 units */

 m2Tilt = tcsOpticsScaleThrow(tilt);
 tiltScale = m2Tilt / tilt ;
 if (m2Tilt < 0.0) m2Tilt = -m2Tilt;
 if (zDemand  < 0.0 ) zDemand = -zDemand;

/* Check for compatibility. The first checks are to see if the maximum 
 * allowed values are exceeded.
*/

 if (m2Tilt > maxTilt)
 {
  *tiltLim = maxTilt / tiltScale ;
  *zLim    = minTiltZ;
  strcpy (mess, "Maximum tilt exceeded");
  status = 1 ;
 }
 else if (zDemand > minTiltZ)
 {
  *tiltLim = maxTilt / tiltScale ;
  *zLim = minTiltZ;
  strcpy (mess , "Maximum Z exceeded");
  status = 1;
 }
 else
 {
  zLimit = slope * (m2Tilt - tilt0) + tiltZ0;
  *zLim = zLimit;
  if (zDemand > zLimit) 
  {
   strcpy (mess, "Maximum Z exceeded");
   if (slope != 0.0)
    *tiltLim = ((zDemand - tiltZ0) / slope + tilt0)/ tiltScale;
   else
    *tiltLim = maxTilt / tiltScale ;
   status = 1;
  }
  else
  {
    *tiltLim = m2Tilt / tiltScale ;
    strcpy (mess, " ");
    status = 0;
  }
 }

 return status;

}


/*+
 *   Function name:
 *   tcsOpticsDisplayAo
 *
 *   Purpose:
 *   Puts aO data on EPICS outputs for display
 *
 *   Description:
 *   This routine simply outputs the aO data that is about to be sent to
 *   the PCS so that it can be displayed. It then copies the data into
 *   the array that will be used to send the data to the PCS.
 *
 *   Invocation:
 *   tcsOpticsDisplayAo(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics outputs:
 *   vala => Z4 (Zemax convention)
 *   valb => Z5
 *   valc => Z8
 *   vald => Z9
 *   vale => Z10
 *   valf => Z11
 *   valg => Z12
 *   valh => Z13
 *   vali => Z14
 *   valj => Z15
 *   valk => Z16
 *   vall => Z17
 *   valm => Z18
 *   valn => Z19
 *-
 */

long tcsOpticsDisplayAo (struct genSubRecord *pgsub)
{
    int i;      /* Loop counter */

    *(double *)pgsub->vala = latestAoZtoM1[3] ;
    *(double *)pgsub->valb = latestAoZtoM1[4] ;
    *(double *)pgsub->valc = latestAoZtoM1[7] ;
    *(double *)pgsub->vald = latestAoZtoM1[8] ;
    *(double *)pgsub->vale = latestAoZtoM1[9] ;
    *(double *)pgsub->valf = latestAoZtoM1[10] ;
    *(double *)pgsub->valg = latestAoZtoM1[11] ;
    *(double *)pgsub->valh = latestAoZtoM1[12] ;
    *(double *)pgsub->vali = latestAoZtoM1[13] ;
    *(double *)pgsub->valj = latestAoZtoM1[14] ;
    *(double *)pgsub->valk = latestAoZtoM1[15] ;
    *(double *)pgsub->vall = latestAoZtoM1[16] ;
    *(double *)pgsub->valm = latestAoZtoM1[17] ;
    *(double *)pgsub->valn = latestAoZtoM1[18] ;

/* Add data to array to be sent to M1. This is protected by a semaphore so
*  that the open loop model corrections don't get scrambled. Note also
*  that only some of the aO corrections are sent on to M1. We don't send
*  tip/tilt/focus or coma.
*/  
    if (opticsSemId) {
        epicsMutexLock(opticsSemId);
        latestZtoM1[0] += latestAoZtoM1[3] ;
        latestZtoM1[1] += latestAoZtoM1[4] ;
        for ( i = 2; i < MAXZERNCOEFFS; i++ ) {
          latestZtoM1[i] += latestAoZtoM1[5+i] ;
        }
        epicsMutexUnlock(opticsSemId);
     } 
  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsDump
 *
 *   Purpose:
 *   Prints out internal variables for diagnostic purposes
 *
 *   Description:
 *   Simply prints out internal variables to check that they hold the values
 *   expected.
 *
 *   Invocation:
 *   tcsOpticsDump()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   None
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsDump (void)

{
   int i,j ;          /*Loop counters */

   printf ("Optical collimation corrections flag %d\n", optPointAdj);
   printf ("Absorb focus errors flag = %d\n", m2AbsorbFocus);
   printf ("Comma correction flag    = %d\n\n", m2ComaCorrect);
   printf ("Currently selected source of ao data %d\n\n", currM1AoSource) ;
   printf ("PWFS1 currently integrating %d\n", pwfs1Measuring) ;
   printf ("PWFS2 currently integrating %d\n", pwfs2Measuring) ;
   printf ("OIWFS currently integrating %d\n", oiwfsMeasuring) ;
   printf ("Altair currently integrating %d\n", altairMeasuring) ;
   printf ("GeMS currently integrating %d\n", gemsMeasuring) ;
   printf ("HRWFS currently integrating %d\n\n", hrwfsMeasuring) ;
   printf ("PWFS1 currently averaging data for M1 = %d\n", p1AoAveraging);
   printf ("PWFS2 currently averaging data for M1 = %d\n", p2AoAveraging);
   printf ("OIWFS currently averaging data for M1 = %d\n", oiAoAveraging);
   printf ("Altair currently averaging data for M1 = %d\n", aoAoAveraging);
   printf ("GemS currently averaging data for M1 = %d\n", gsAoAveraging);
   printf ("HRWFS currently averaging data for M1 = %d\n\n", hrAoAveraging);
   printf ("Model components for M1 and M2\n\n");
   printf ("                        M1       M2\n\n");
   printf ("X user offset (mm)  %f     %f\n", m1XUserOffset, m2XUserOffset);
   printf ("Y user offset (mm)  %f     %f\n", m1YUserOffset, m2YUserOffset);
   printf ("Z user offset (mm)  %f     %f\n", m1ZUserOffset, m2ZUserOffset);
   printf ("Z ins  offset (mm)         %f\n", m2ZInsOffset) ;
   printf ("X offset about CG (A)            %f\n", m2XRotOffset[0]);
   printf ("X offset about CG (B)            %f\n", m2XRotOffset[1]);
   printf ("X offset about CG (C)            %f\n", m2XRotOffset[2]);
   printf ("Y offset about CG (A)            %f\n", m2YRotOffset[0]);
   printf ("Y offset about CG (B)            %f\n", m2YRotOffset[1]);
   printf ("Y offset about CG (C)            %f\n", m2YRotOffset[2]);
   printf ("                                 %f\n", m2XTiltUser[0]/AS2R);
   printf ("X rotation (arcsec) %f     %f\n", m1XRotUserOffset/AS2R,
                                              m2XTiltUser[1]/AS2R);
   printf ("                                 %f\n", m2XTiltUser[2]/AS2R);
   printf ("                                 %f\n", m2YTiltUser[0]/AS2R);
   printf ("Y rotation (arcsec) %f     %f\n", m1YRotUserOffset/AS2R,
                                              m2YTiltUser[1]/AS2R);
   printf ("                                 %f\n", m2YTiltUser[2]/AS2R);
   printf ("Z rotation (arcsec) %f\n", m1ZRotUserOffset);
   printf ("Model error correction (mm) %f\n", m2ZErrorCorr);
   printf ("\n");
   printf ("M2 optics scale factor %f\n", tcsOpticsScaleThrow(1.0));
   printf ("Zernike conversion coefficients\n");
   for ( j = 0 ; j < MAXZERNIKES ; j++ ) {
    for ( i = 0 ; i < MAXENTRIES ; i++) 
      printf ("%f ", zMatrix[j][i]) ;
    printf ("\n") ;
   }
}


/*+
 *   Function name:
 *   tcsOpticsGetAoAverage
 *
 *   Purpose:
 *   Fetch flags that control aO data averaging
 *
 *   Description:
 *   Simply fetch the current value of the flags that control whether aO
 *   data from the WFS should be averaged
 *
 *   Invocation:
 *   flag = tcsOpticsGetAoAverage()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  flag (int)  TRUE or FALSE
 * 
 *-
 */

int tcsOpticsGetAoAverage (void)
{
  if (p1AoAveraging || p2AoAveraging || oiAoAveraging)
    return TRUE ;
  else
    return FALSE ;
}

/*+
 *   Function name:
 *   tcsOpticsGetAoIntTime
 *
 *   Purpose:
 *   Fetch the current value of the integration time for aO data
 *
 *   Description:
 *   Simply return the value of the integration time from storage.
 *
 *   Invocation:
 *   tcsOpticsGetAoIntTime(&IntTime)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    intTime (double)  Integration time (secs)
 *
 *   Function value:
 *   None
 *-
 */

void tcsOpticsGetAoIntTime (double *intTime)
{

  *intTime = aoExpTime * aoNumFrames ;

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsOpticsGetChopLimits
 *
 *   Purpose:
 *   Fetch chop limits for TCS database
 *
 *   Description:
 *   This routine retrieves the current chop limits from the internal
 *   database where they are stored in M2 units and converts them into
 *   user units i.e. arcsec on sky.
 *
 *   Invocation:
 *   tcsOpticsGetChopLimits (&maxThrow, &minChopFreq, &maxChopFreq )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (<)    maxThrow (double *) Max chop throw on sky (arcsec)
 *      (<)    minChopFreq (double *) Minimum chop frequency (Hz)
 *      (<)    maxChopfreq (double *) Maximum chop frequency (Hz)
 *
 *   Function value:
 *   None.
 *
 *   External functions:
 *   tcsOpticsGetFl       (tcsOptics) Fetch current focal length
 *   tcsOpticsGetM2Fplane (tcsOptics) Fetch M2 to focal plane separation
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */

void tcsOpticsGetChopLimits(double *maxThrow, double *minChopFreq,
                      double *maxChopFreq)
{
    double throwScale ;     /* Converts sky units to M2 units */

/* Compute the current scaling factor by inputing a unit offset on the sky */
    throwScale = tcsOpticsScaleThrow (1.0) ;

  if (opticsSemId) {

    epicsMutexLock(opticsSemId);

/* N.B. the maximum throw is available at the lowest frequencies. Hence
 * the use of the variable m2MinChopFreqThrow in the expression below
*/

    *maxThrow = m2MinChopFreqThrow / ( AS2R * throwScale);
    *minChopFreq = m2MinChopFreq;
    *maxChopFreq = m2MaxChopFreq;

    epicsMutexUnlock(opticsSemId);
  }
}


/*+
 *   Function name:
 *   tcsOpticsGetTiltLimits 
 *
 *   Purpose:
 *   Fetch tilt and focus limits from internal store
 *
 *   Description:
 *   This routine fetchs the current tilt and focus limits from internal
 *   storage. The values returned are in user units i.e. the tilt limit
 *   is in arcsec on the sky. Since the focus and tilt limits are not
 *   independent of each other this routine returns the maximum allowed
 *   values. 
 *
 *   Invocation:
 *   tcsOpticsGetTiltLimits (&maxTilt, &maxZ)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    maxTilt  (double *)  Maximum tilt in arcsec on sky
 *      (<)    maxZ     (double *)  Maximum allowed Z (mm)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   tcsOpticsSetTiltLimits must have been called before calling this
 *   routine for the first time.
 *
 *   Deficiencies:
 *   The routine assumes that the limits are symmetric about the origin i.e.
 *   a tilt must lie between -maxTilt and +maxTilt and a focus demand 
 *   between -maxZ and +maxZ
 *
 *-
 */

void tcsOpticsGetTiltLimits (double *maxTilt, double *maxZ)

{
  double tiltScale ;

/* Compute tilt scale by inputting a unit tilt on the sky */
  tiltScale = tcsOpticsScaleThrow (1.0) ;

  *maxZ = m2MinTiltZ;
  *maxTilt =  m2MaxTilt / ( tiltScale * AS2R);

}



/*+
 *   Function name:
 *   tcsOpticsGetDistCoeff
 *
 *   Purpose:
 *   Provides a copy of the optical distortion coefficient
 *
 *   Description:
 *   The optical distortion coefficient is set on the basis of the current
 *   top end. The correction coefficent should be multiplied by the
 *   cube of the angular displacement (in rads) and then by the effective
 *   focal length to give the displacement in the image plane. 
 *   A positive coefficient indicates that the object will be displaced
 *   outwards compared to the paraxial position.
 *
 *   Invocation:
 *   tcsOpticsGetDistCoeff (&coeff)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    coeff    (double *) Optical distortion coefficient
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsGetDistCoeff(double *coeff)

{

  *coeff = optDistCoeff;

}

/*+
 *   Function name:
 *   tcsOpticsGetM1ModelType
 *
 *   Purpose:
 *   Returns the internally stored M1 model type that is to be restored
 *
 *   Description:
 *   This routine is used to return the internal M1 model type. This 
 *   parameter determines which file of saved model data is to be 
 *   reloaded via a restore operation. The TCS maintains three types of
 *   model data, one is for AO, another for non-AO and the the other for 
 *   GPI
 *
 *   Invocation:
 *   model = tcsOpticsGetM1ModelType ()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  model  (int)  0 = non-AO, 1 = AO, 2 = GPI 
 *-
 */

int tcsOpticsGetM1ModelType(void)

{

  return m1RestoreModelType;

}

/*+
 *   Function name:
 *   tcsOpticsGetM1SaveType
 *
 *   Purpose:
 *   Returns the internally stored M1 model type that is to be saved 
 *
 *   Description:
 *   This routine is used to return the internal M1 model type. This 
 *   parameter determines which file the M1 model data is to be 
 *   saved to. The TCS maintains three types of
 *   model data, one is for AO, another for non-AO and the the other for 
 *   GPI
 *
 *   Invocation:
 *   model = tcsOpticsGetM1SaveType ()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *   (<)  model  (int)  0 = non-AO, 1 = AO, 2 = GPI 
 *-
 */

int tcsOpticsGetM1SaveType(void)

{

  return m1SaveModelType;

}

/*+
 *   Function name:
 *   tcsOpticsGetM1ModelValid
 *
 *   Purpose:
 *   Returns the valid flag for the specifiedd model 
 *
 *   Description:
 *   Simply return the validity flag for the specified model. If the
 *   model number is out of range return zero i.e. invalid
 *
 *   Invocation:
 *   valid = tcsOpticsGetM1ModelValid (model)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   (<)  model  (int)  0 = non-AO, 1 = AO 2 = GPI
 *
 *   Function value:
 *   (<)  valid  (int)  0 = invalid, 1 = valid 
 *-
 */

int tcsOpticsGetM1ModelValid(int model)

{
  int valid = 0;

  if (model == 0 ) {
    valid = m1ModelValid ;
  } else if (model == 1) {
    valid = m1AOModelValid ;
  } else if (model == 2) {
    valid = m1GPIModelValid ;
  }

  return valid ;
}


/*+
 *   Function name:
 *   tcsOpticsFigureTotals
 *
 *   Purpose:
 *   Copy total figure offsets from M1 to output fields of a gensub
 *
 *   Description:
 *   This routine simply copies the various Zernike offsets that have 
 *   been applied to M1 to output fields for display by the TCS.
 *   It also stores them internally in case they are needed during
 *   a restore operation.
 *
 *   Invocation:
 *   tcsOpticsFigureTotals (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsFigureTotals (struct genSubRecord *pgsub) 
{

  m1TotalFigure[0] = *(double *)pgsub->vala = *(double *)pgsub->a ;
  m1TotalFigure[1] = *(double *)pgsub->valb = *(double *)pgsub->b ;
  m1TotalFigure[2] = *(double *)pgsub->valc = *(double *)pgsub->c ;
  m1TotalFigure[3] = *(double *)pgsub->vald = *(double *)pgsub->d ;
  m1TotalFigure[4] = *(double *)pgsub->vale = *(double *)pgsub->e ;
  m1TotalFigure[5] = *(double *)pgsub->valf = *(double *)pgsub->f ;
  m1TotalFigure[6] = *(double *)pgsub->valg = *(double *)pgsub->g ;
  m1TotalFigure[7] = *(double *)pgsub->valh = *(double *)pgsub->h ;
  m1TotalFigure[8] = *(double *)pgsub->vali = *(double *)pgsub->i ;
  m1TotalFigure[9] = *(double *)pgsub->valj = *(double *)pgsub->j ;
  m1TotalFigure[10] = *(double *)pgsub->valk = *(double *)pgsub->k ;
  m1TotalFigure[11] = *(double *)pgsub->vall = *(double *)pgsub->l ;
  m1TotalFigure[12] = *(double *)pgsub->valm = *(double *)pgsub->m ;
  m1TotalFigure[13] = *(double *)pgsub->valn = *(double *)pgsub->n ;

  return 0;
}

/*+
 *   Function name:
 *   tcsOpticsGetFl
 *
 *   Purpose:
 *   Provide a copy of the current effective focal length
 *
 *   Description:
 *   Simply copy the current effective focal length
 *
 *   Invocation:
 *   tcsOpticsGetFl (&focalLength)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    focalLength (double *) focal length (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsGetFl (double *focalLength)
{

 *focalLength = flCurrent;

}

/*+
 *   Function name:
 *   tcsOpticsGetFshift
 *
 *   Purpose:
 *   Fetch the current offset of the focal plane from nominal
 *
 *   Description:
 *   Use the current offset of the M1 and M2 separation to compute the
 *   shift in the focal plane.
 *
 *   Invocation:
 *   tcsOpticsGetFshift (&shift)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    shift (double *) focal plane shift (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsGetFshift (double *shift)
{

 *shift = deltaZ * (m2Mag * m2Mag + 1.0) ;

}

/*+
 *   Function name:
 *   tcsOpticsGetM2Fplane
 *
 *   Purpose:
 *   Makes available the M2 to Focal plane separation 
 *
 *   Description:
 *   This routine is used to return the current value of the separation
 *   between M2 and the focal plane. This is used when calculating the
 *   scaling between user tip/tilt demands and physical demands to M2
 *
 *   Invocation:
 *   tcsOpticsGetM2Fplane (&m2FplaneSep)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    m2FplaneSep  (double *)  Separation of M2 and focal plane (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock        (semLib)           Give a semaphore
 *   epicsMutexLock          (semLib)           Take a semaphore
 *
 *-
 */

void tcsOpticsGetM2Fplane (double *m2FplaneSep)

{

  if (opticsSemId) {
    epicsMutexLock(opticsSemId);
    *m2FplaneSep = m2Separation + deltaZ + backFocus ;
    epicsMutexUnlock(opticsSemId);
  }
}

/*+
 *   Function name:
 *   tcsOpticsGetM2XY
 *
 *   Purpose:
 *   Makes available the current total M2 X,Y translation demands
 *
 *   Description:
 *   This routine simply copies the current total M2 X,Y translation demands
 *   to make them available to other software compoments.
 *
 *   Invocation:
 *   tcsOpticsGetM2XY (&m2Xposn, &m2Yposn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    m2Xposn  (double *)  Total X position demand (mm)
 *      (<)    m2Yposn  (double *)  Total Y position demand (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock        (semLib)           Give a semaphore
 *   epicsMutexLock          (semLib)           Take a semaphore
 *
 *-
 */

void tcsOpticsGetM2XY (double *m2Xposn, double *m2Yposn)

{

  if (opticsSemId) {
    epicsMutexLock(opticsSemId);
    *m2Xposn = m2XDemand;
    *m2Yposn = m2YDemand;
    epicsMutexUnlock(opticsSemId);
  }
}

/*+
 *   Function name:
 *   tcsOpticsGetM2ZTilt
 *
 *   Purpose:
 *   Copy the current total M2 Z translation and X,Y tilt demands
 *
 *   Description:
 *   This routine simply copies the current total M2 Z translation 
 *   and X,Y tilt demands 
 *   to make them available to other software compoments.
 *
 *   Invocation:
 *   tcsOpticsGetM2ZTilt (&m2Zposn, &m2XtiltPosn, &m2YtiltPosn)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    m2Zposn      (double *)  Total Z position demand (mm)
 *      (<)    m2XtiltPosn  (double *)  Total X tilt demand (rads)
 *      (<)    m2YtiltPosn  (double *)  Total Y tilt demand (rads)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexUnlock        (semLib)           Give a semaphore
 *   epicsMutexLock          (semLib)           Take a semaphore
 *
 *-
 */

void tcsOpticsGetM2ZTilt (double *m2Zposn, double *m2XtiltPosn,
                          double *m2YtiltPosn)

{

  if (opticsSemId) {
    epicsMutexLock(opticsSemId);
    *m2XtiltPosn = m2XTiltDemand;
    *m2YtiltPosn = m2YTiltDemand;
    *m2Zposn     = m2ZDemand;
    epicsMutexUnlock(opticsSemId);
  }
}


/*+
 *   Function name:
 *   tcsOpticsGetProbeScale
 *
 *   Purpose:
 *   Calculates and returns the scale factor for the probe arm positions
 *   to allow for the fact they lie above the focal plane.
 *
 *   Description:
 *   The two PWFS move in planes that lie some way above the focal plane
 *   of the telescope. When positioning the ends of the probes, they 
 *   must therefore be put closer to the optic axis than they would be
 *   if they were moving in the focal plane. The routine calculates the
 *   scale factor by which the focal plane demand must be multiplied to
 *   get the desired position at the appropriate height above the focal
 *   plane. With the release of V4-0 of the A&G this approximate
 *   method has been replaced with a proper calculation within the A&G
 *   and this routine is thus redundant. 
 *  
 *   Invocation:
 *   tcsOpticsGetProbeScale (&p1Scale, &p2Scale)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    p1Scale  (double)   Scale factor for PWFS1
 *      (<)    p2Scale  (double)   Scale factor for PWFS2
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *   The routine doesn't take account of changes to the M2 to focal plane
 *   separation or the heights of the WFS above the focal plane that occur
 *   when M1 and M2 are moved.
 * 
 *-
 */

void tcsOpticsGetProbeScale (double *p1Scale, double *p2Scale)
{
   *p1Scale = 1.0 - pwfs1FplaneSep / (m2Separation + backFocus) ;
   *p2Scale = 1.0 - pwfs2FplaneSep / (m2Separation + backFocus) ;
}

/*+
 *   Function name:
 *   tcsOpticsGetTTF
 *
 *   Purpose:
 *   Fetch tip/tilt/focus Zernikes for a given probe and chop state
 *
 *   Description:
 *   The TCS must supply the A&G system with the expected tip/tilt/focus
 *   values its wave front sensors should see expressed as Zernike
 *   coefficients. This routine calculates these data based on the 
 *   position of the probe in the focal plane. Currently Zernike terms
 *   1 and 2 that represent tilt in x and y respectively are set to zero.
 *   This is done because the probe is always positioned such that the 
 *   target star is centred on the WFS. For Z3 (the focus term) this 
 *   isn't done. For PWFS 1 and 2, the probes will have been positioned
 *   in z to take out the gross focal plane curvature as well as any
 *   focus shift due to z displacements of M1 or M2. Only the residual
 *   term due to a tilt of the focal plane will be calculated here.
 *   For the OIWFS there is no z movement available so the full focus
 *   term is computed.
 *
 *   Invocation:
 *   tcsOpticsGetTTF (probe, ichop, x, y, pa, ttf)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    probe   (int  )     Probe  
 *      (>)    ichop   (int)       chop state
 *      (>)    x       (double)    Probe position in x (mm)
 *      (>)    y       (double)    Probe position in y (mm)
 *      (>)    pa      (double)    Position angle (rads)
 *      (<)    ttf     (double[3]) Zernike terms Z1, Z2 and Z3 (mm)
 *
 *   Function value:
 *   None.
 * 
 *   Deficiencies:
 *   It is somewhat inconsistent that PWFS1 and PWFS2 are positioned in
 *   z to take out all the position (in focal plane) independent focus
 *   term but not the position dependent parts. In x and y the probes are
 *   always positioned to ensure Z1 and Z2 are zero. 
 *
 *-
 */

void tcsOpticsGetTTF (int probe, int ichop, double x, double y, 
                      double pa, double ttf[3])

{
  double xoff, yoff ;           /* Offset from nominal optical centre (rads) */
  static int count = 0 ;        /* Loop counter */
  static int i = 0;             /* Loop counter */


/* Convert guide target position from rotator frame into standard x,y frame.
 */ 

  tcsOpticsXYToXpYp (x/flCurrent, y/flCurrent, pa, &xoff, &yoff);

/* Set Z1 and Z2 to 0.0 for all probes */

 ttf[0] = 0.0 ;
 ttf[1] = 0.0 ;

/* Compute Z3 for the probe given the field position. Note that the oiwfs
 * has an additional term due to any z offset of M1 or M2. For the PWFS
 * this is taken out by the z movement of the probe 
 */

 ttf[2] = zMatrix[2][1]*m1XUserOffset*xoff +
          zMatrix[2][2]*m1YUserOffset*yoff +
          zMatrix[2][4]*m1XRotUserOffset*yoff +
          zMatrix[2][5]*m1YRotUserOffset*xoff +
          zMatrix[2][6]*(m2XUserOffset + m2XRotOffset[ichop])*xoff +
          zMatrix[2][7]*(m2YUserOffset + m2YRotOffset[ichop])*yoff +
          zMatrix[2][9]*m2XTiltUser[ichop]*yoff +
          zMatrix[2][10]*m2YTiltUser[ichop]*xoff ;

/* Add in the contribution for the OIWFS if there are displacements of
 * M1 and M2
 */

 if (probe == 2) {
   ttf[2] = ttf[2] + zMatrix[2][3]*m1ZUserOffset +
                     zMatrix[2][8]*m2ZUserOffset ;
 }
 
/* Output some debug information */

 count++ ;
 if (count%600 == 0) i = 1 ;
 if (i > 0 ) {
/*
   printf ("probe, chop, x,y,t,t,f = %d %d %f %f %f %f %f\n",
            probe, ichop, xoff/AS2R, yoff/AS2R, ttf[0], ttf[1], ttf[2]);
*/
   i++ ;
   if (i > 3) i = 0 ;
 } 

}


/*+
 *   Function name:
 *   tcsOpticsGetZernikes
 *
 *   Purpose:
 *   Compute Z4 to Z19 for a given probe at a specified x,y in focal plane
 *
 *   Description:
 *   The TCS must provide each WFS with the expected Zernike coefficients
 *   that it should see. These Zernike terms depend on the position
 *   in the focal plane as well as the translations and tilts of M1 and
 *   M2. The Zernikes are computed using a matrix of coefficients that 
 *   have been predetermined offline using Zemax. The low order terms
 *   for tilt in x and y as well as focus are computed in a companion
 *   routine tcsOpticsGetTTF.
 *
 *   Invocation:
 *   tcsOpticsGetZernikes (probe, ichop, x, y, pa, zernikes)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     probe   (int)      Identifier for probe O, 1 or 2
 *      (>)     ichop   (int)      Chop state 0, 1 or 2
 *      (>)     x       (double)   Probe x coord in rotator frame (mm)
 *      (>)     y       (double)   Probe y coord in rotator frame (mm)
 *      (>)     pa      (double)   Rotation angle to ISS frame (rads)
 *      (<)     zernike[16] (double) Zernikes terms (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsGetZernikes (int probe, int ichop, double x, double y,
                           double pa, double zernike[16])
{

  double xoff, yoff;            /* Offsets in ISS frame (rads) */
  int i ;                       /* loop counter */
  double rsq ;                  /* Square of separation */
  double theta ;                /* Direction */

/* Rotate x,y probe position to offsets in ISS frame */

  tcsOpticsXYToXpYp (x/flCurrent, y/flCurrent, pa, &xoff, &yoff) ;

/* Precompute certain terms */ 
  rsq  = xoff*xoff + yoff*yoff ;
  theta = 0.0 ;
  if (rsq != 0.0)
    theta = atan2(yoff, xoff) ;

/* Z4 (astigmatism in X) */

/* For time being comment out the simple theoretical fit and use an empirical
*  one instead.
*  N.B. after the complex model was put in it was discovered that most of
*  the astigmatism variation was in the WFS themselves. The only problem with
*  the theoretical model was that it gave the "wrong" sign as defined by the
*  WFS. The model currently therefore has astig0[1] set to 1.0 and 
*  astig0[2] set to 180 degs. All other coefficients are 0. Similar 
*  considerations apply to the 45 astigmatism.

  zernike[0] = zMatrix[3][0]*(xoff*xoff - yoff*yoff) +
*/
  zernike[0] = astig0[1] * zMatrix[3][0] * rsq * cos(2.0*theta + astig0[2]) +
               astig0[3] * cos(2.0*theta + astig0[4]) +
               astig0[5] * cos(theta + astig0[6]) +
               astig0[0] +
               zMatrix[3][1]*m1XUserOffset*xoff +
               zMatrix[3][2]*m1YUserOffset*yoff +
               zMatrix[3][3]*m1ZUserOffset +
               zMatrix[3][4]*m1XRotUserOffset*yoff +
               zMatrix[3][5]*m1YRotUserOffset*xoff +
               zMatrix[3][6]*(m2XUserOffset + m2XRotOffset[ichop])*xoff +
               zMatrix[3][7]*(m2YUserOffset + m2YRotOffset[ichop])*yoff +
               zMatrix[3][8]*m2ZUserOffset + 
               zMatrix[3][9]*m2XTiltUser[ichop]*yoff +
               zMatrix[3][10]*m2YTiltUser[ichop]*xoff ;

/* Z5 (astigmatism in Y) */
/*
  As for 0 astigmatism, allow for an empirical fit
  zernike[1] = zMatrix[4][0]*2.0*xoff*yoff +
*/
  zernike[1] = astig45[1] * zMatrix[4][0] * rsq * sin(2.0*theta + astig45[2]) +
               astig45[3] * sin(2.0*theta + astig45[4]) +
               astig45[5] * sin(theta + astig45[6]) +
               astig45[0] +
               zMatrix[4][1]*m1XUserOffset*yoff +
               zMatrix[4][2]*m1YUserOffset*xoff +
               zMatrix[4][3]*m1ZUserOffset +
               zMatrix[4][4]*m1XRotUserOffset*xoff +
               zMatrix[4][5]*m1YRotUserOffset*yoff +
               zMatrix[4][6]*(m2XUserOffset + m2XRotOffset[ichop])*yoff +
               zMatrix[4][7]*(m2YUserOffset + m2YRotOffset[ichop])*xoff +
               zMatrix[4][8]*m2ZUserOffset + 
               zMatrix[4][9]*m2XTiltUser[ichop]*xoff +
               zMatrix[4][10]*m2YTiltUser[ichop]*yoff ;

/* Z6 (Coma in X) */
  zernike[2] = zMatrix[5][1]*m1XUserOffset +
               zMatrix[5][2]*m1YUserOffset +
               zMatrix[5][3]*m1ZUserOffset +
               zMatrix[5][4]*m1XRotUserOffset +
               zMatrix[5][5]*m1YRotUserOffset +
               zMatrix[5][6]*(m2XUserOffset + m2XRotOffset[ichop]) +
               zMatrix[5][7]*(m2YUserOffset + m2YRotOffset[ichop]) +
               zMatrix[5][8]*m2ZUserOffset +
               zMatrix[5][9]*m2XTiltUser[ichop] +
               zMatrix[5][10]*m2YTiltUser[ichop] ;

/* Z7 (Coma in Y) */
  zernike[3] = zMatrix[6][1]*m1XUserOffset +
               zMatrix[6][2]*m1YUserOffset +
               zMatrix[6][3]*m1ZUserOffset +
               zMatrix[6][4]*m1XRotUserOffset +
               zMatrix[6][5]*m1YRotUserOffset +
               zMatrix[6][6]*(m2XUserOffset + m2XRotOffset[ichop]) +
               zMatrix[6][7]*(m2YUserOffset + m2YRotOffset[ichop]) +
               zMatrix[6][8]*m2ZUserOffset +
               zMatrix[6][9]*m2XTiltUser[ichop] +
               zMatrix[6][10]*m2YTiltUser[ichop] ;

/* Z8 (Spherical) */
  zernike[4] = zMatrix[7][1]*m1XUserOffset +
               zMatrix[7][2]*m1YUserOffset +
               zMatrix[7][3]*m1ZUserOffset +
               zMatrix[7][4]*m1XRotUserOffset +
               zMatrix[7][5]*m1YRotUserOffset +
               zMatrix[7][6]*(m2XUserOffset + m2XRotOffset[ichop]) +
               zMatrix[7][7]*(m2YUserOffset + m2YRotOffset[ichop]) +
               zMatrix[7][8]*m2ZUserOffset +
               zMatrix[7][9]*m2XTiltUser[ichop] +
               zMatrix[7][10]*m2YTiltUser[ichop] ;

/* Set all others to zero */

  for (i = 5 ; i < 16 ; i++) {
    zernike[i] = 0.0;
  }

}

/*+
 *   Function name:
 *   tcsOpticsHrwfsData
 *
 *   Purpose:
 *   Copy data provided by tcsReadHrwfs sequence program
 *
 *   Description:
 *   This routine simply copies data supplied by the tcsReadHrwfs sequence
 *   program from its input to its output. This then provides the same
 *   interface to the downstream code as the PWFS's and the OIWFS.
 *   It also generates a "measuring" flag for the HRWFS. This is set
 *   whenever the data source is HRWFS and the guiding is on
 *
 *   Invocation:
 *   tcsOpticsHrwfsData (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Whether m1 figure corrections are enabled or not
 *   b => Counter from data file
 *   j => array of Zernike corrections
 *
 *   Epics outputs:
 *   vala => HRWFS measuring flag
 *   valj => array of Zernike corrections
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsHrwfsData (struct genSubRecord *pgsub)
{
  long m1On ;
  static long hrwfsActive = 0;
  long counter ;
  static long currCounter = 0 ;
  static int firstTime = 1 ;

  m1On = *(long *)pgsub->a ;
  counter = *(long *)pgsub->b;
 
  if (m1On && (currM1AoSource == HRWFS_AO_SOURCE)) {
    if (firstTime) {
      currCounter = counter ;
      firstTime   = 0 ;
    } else {
      if ((currCounter != counter) && !hrwfsActive) {
        hrwfsActive = 1 ;
      }
    } 
    
  } else {
    hrwfsActive = 0 ;
    firstTime = 1 ;
  }

  *(long *)pgsub->vala = hrwfsActive ;
  memcpy (pgsub->valj, pgsub->j, 40 * sizeof(double)) ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsM1CalcFig
 *
 *   Purpose:
 *   Calculates the open loop corrections to the M1 figure
 *
 *   Description:
 *   Each time this routine is called, it calculates the offset correction
 *   to be sent to M1 for each Zernike. The offsets are calculated from
 *   a three coefficient model. The logic for whether this routine is called
 *   or not is contained in the EPICS database.
 *
 *   Invocation:
 *   tcsOpticsM1CalcFig (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *   a => Flag to use open and closed loop corrections
 *   b => Flag for closed loop guiding 
 *-
 */

long tcsOpticsM1CalcFig (struct genSubRecord *pgsub)
{

  int i ;                        /* loop counter */
  double model[MAXZERNCOEFFS] ;  /* Latest model for current elevation */
  double el ;                    /* demand elevation (rads) */
  double az ;                    /* demand azimuth (rads) */
  double cosEl, sinEl ;          /* Cos & sin of current elevation */
  long m1GuideOn ;               /* Flag to show if M1 is closed loop */
  long useOpenLoop = 0;          /* Flag for test purposes */

/* Re-initialise the M1 model on the basis of whether we have zeroed the
*  PCS figure or whether we are restoring the last model saved to disk.
*  This routine will never get called unless one of m1RestoreModel or
*  m1ZeroModel have been set. This is done by the m1ZeroSet and m1RestoreModel
*  commands respectively.
*/
  if (!opticsSemId) return 0;

  if (m1OpenLoopInit) {
   if (m1RestoreModel) { 
     for (i=0; i < MAXZERNCOEFFS ; i++ ) {
       m1LastFigure[i] = m1SavedModel[i] ;
     }
   } else {
     for (i=0; i < MAXZERNCOEFFS ; i++ ) {
       m1LastFigure[i] = 0.0 ;
     }
   }
   m1OpenLoopInit = FALSE ;
     
  }

/* Compute new corrections for each Zernike term */
  tcsGetMountAzEl (&az, &el) ;
  cosEl = cos(el) ;
  sinEl = sin(el) ;

  for (i = 0 ; i < MAXZERNCOEFFS ; i++ ) {
    model[i] = m1ZernCoeffs[i][0]*cosEl + m1ZernCoeffs[i][1]*sinEl + 
               m1ZernCoeffs[i][2] ;
    m1CurrentIncr[i] = model[i] - m1LastFigure[i] ;
    m1LastFigure[i]  = model[i] ;
  }
  
/* If we are running closed loop then the WFS will have taken out any
*  open loop correction so we don't need to do anything else unless
*  we are using P2 or the OIWFS as these only measure astigmatism.
*  For P2 and OIWFS we use the open loop for everything but astigmatism. 
*/
  m1GuideOn = *(long *)pgsub->b ;

/* The following flag is for engineering tests. If it is set on then we
*  continue to apply the open loop corrections even when in closed loop.
*  This mimics the previous way the software worked except that the
*  updates are synchronous with the closed loop corrections whereas
*  in earlier versions they were asynchronous
*/
  useOpenLoop = *(long *)pgsub->a ;

  if (!m1GuideOn) {

/* Output the latest increments for display purposes */
    *(double *)pgsub->vala = m1CurrentIncr[0] ;
    *(double *)pgsub->valb = m1CurrentIncr[1] ;
    *(double *)pgsub->valc = m1CurrentIncr[2] ;
    *(double *)pgsub->vald = m1CurrentIncr[3] ;
    *(double *)pgsub->vale = m1CurrentIncr[4] ;
    *(double *)pgsub->valf = m1CurrentIncr[5] ;
    *(double *)pgsub->valg = m1CurrentIncr[6] ;
    *(double *)pgsub->valh = m1CurrentIncr[7] ;
    *(double *)pgsub->vali = m1CurrentIncr[8] ;
    *(double *)pgsub->valj = m1CurrentIncr[9] ;
    *(double *)pgsub->valk = m1CurrentIncr[10] ;
    *(double *)pgsub->vall = m1CurrentIncr[11] ;
    *(double *)pgsub->valm = m1CurrentIncr[12] ;
    *(double *)pgsub->valn = m1CurrentIncr[13] ;

/* Add model increments to any other corrections being sent e.g. from the
*  WFS.
*/
      epicsMutexLock(opticsSemId);
      for (i = 0; i < MAXZERNCOEFFS; i++) {
        latestZtoM1[i] += m1CurrentIncr[i] ;
      }
      epicsMutexUnlock(opticsSemId);

  } else {                      /* Close loop guiding */
   if (currM1AoSource == PWFS2_AO_SOURCE || currM1AoSource == OIWFS_AO_SOURCE) {     
     *(double *)pgsub->valc = m1CurrentIncr[2] ;
     *(double *)pgsub->vald = m1CurrentIncr[3] ;
     *(double *)pgsub->vale = m1CurrentIncr[4] ;
     *(double *)pgsub->valf = m1CurrentIncr[5] ;
     *(double *)pgsub->valg = m1CurrentIncr[6] ;
     *(double *)pgsub->valh = m1CurrentIncr[7] ;
     *(double *)pgsub->vali = m1CurrentIncr[8] ;
     *(double *)pgsub->valj = m1CurrentIncr[9] ;
     *(double *)pgsub->valk = m1CurrentIncr[10] ;
     *(double *)pgsub->vall = m1CurrentIncr[11] ;
     *(double *)pgsub->valm = m1CurrentIncr[12] ;
     *(double *)pgsub->valn = m1CurrentIncr[13] ;

       epicsMutexLock(opticsSemId);
       for (i = 2; i < MAXZERNCOEFFS; i++) {
         latestZtoM1[i] += m1CurrentIncr[i] ;
       }
      epicsMutexUnlock(opticsSemId);

     if (useOpenLoop) {
       *(double *)pgsub->vala = m1CurrentIncr[0] ;
       *(double *)pgsub->valb = m1CurrentIncr[1] ;
         epicsMutexLock(opticsSemId);
         for (i = 0; i < 2; i++) {
           latestZtoM1[i] += m1CurrentIncr[i] ;
         }
         epicsMutexUnlock(opticsSemId);
     }
   } else {                    /* P1, Altair, HRWFS */
     if (useOpenLoop) {
       *(double *)pgsub->vala = m1CurrentIncr[0] ;
       *(double *)pgsub->valb = m1CurrentIncr[1] ;
       *(double *)pgsub->valc = m1CurrentIncr[2] ;
       *(double *)pgsub->vald = m1CurrentIncr[3] ;
       *(double *)pgsub->vale = m1CurrentIncr[4] ;
       *(double *)pgsub->valf = m1CurrentIncr[5] ;
       *(double *)pgsub->valg = m1CurrentIncr[6] ;
       *(double *)pgsub->valh = m1CurrentIncr[7] ;
       *(double *)pgsub->vali = m1CurrentIncr[8] ;
       *(double *)pgsub->valj = m1CurrentIncr[9] ;
       *(double *)pgsub->valk = m1CurrentIncr[10] ;
       *(double *)pgsub->vall = m1CurrentIncr[11] ;
       *(double *)pgsub->valm = m1CurrentIncr[12] ;
       *(double *)pgsub->valn = m1CurrentIncr[13] ;

         epicsMutexLock(opticsSemId);
         for (i = 0; i < MAXZERNCOEFFS; i++) {
           latestZtoM1[i] += m1CurrentIncr[i] ;
         }
         epicsMutexUnlock(opticsSemId);
     }
   }
  }

  return 0 ;

}


/*+
 *   Function name:
 *   tcsOpticsM1Figure
 *
 *   Purpose:
 *   Drives the M1 figure command with the latest Zernike corrections
 *
 *   Description:
 *   The tcsOpticsAverageAo & tcsOpticsM1CalcFig routines generate
 *   Zernike corrections from the open loop model and the data supplied
 *   by the A&G. When it is time to output a command to M1
 *   a flag is set that triggers this routine. The latest Zernike 
 *   corrections are fetched and output on the EPICS links.
 *
 *   Invocation:
 *   tcsOpticsM1Figure(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics outputs:
 *   vala => Z4 (Zemax convention)
 *   valb => Z5
 *   valc => Z8
 *   vald => Z9
 *   vale => Z10
 *   valf => Z11
 *   valg => Z12
 *   valh => Z13
 *   vali => Z14
 *   valj => Z15
 *   valk => Z16
 *   vall => Z17
 *   valm => Z18
 *   valn => Z19
 *   valo => Start directive 
 *-
 */

long tcsOpticsM1Figure (struct genSubRecord *pgsub)
{
   int i ;         /* loop counter */

/* To make sure that the array of data isn't changed whilst it is being
*  output protect the updates by a semaphore.
*/
  if (opticsSemId) {
        epicsMutexLock(opticsSemId);
    *(double *)pgsub->vala = latestZtoM1[0] ;
    *(double *)pgsub->valb = latestZtoM1[1] ;
    *(double *)pgsub->valc = latestZtoM1[2] ;
    *(double *)pgsub->vald = latestZtoM1[3] ;
    *(double *)pgsub->vale = latestZtoM1[4] ;
    *(double *)pgsub->valf = latestZtoM1[5] ;
    *(double *)pgsub->valg = latestZtoM1[6] ;
    *(double *)pgsub->valh = latestZtoM1[7] ;
    *(double *)pgsub->vali = latestZtoM1[8] ;
    *(double *)pgsub->valj = latestZtoM1[9] ;
    *(double *)pgsub->valk = latestZtoM1[10] ;
    *(double *)pgsub->vall = latestZtoM1[11] ;
    *(double *)pgsub->valm = latestZtoM1[12] ;
    *(double *)pgsub->valn = latestZtoM1[13] ;
    *(double *)pgsub->valo = menuDirectiveSTART ;
    for (i = 0; i < MAXZERNCOEFFS; i++ ) {
       latestZtoM1[i] = 0.0 ;
    }
    epicsMutexUnlock(opticsSemId);
  }
  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsM1Restore
 *
 *   Purpose:
 *   Restores M1 optics model after a reboot of the TCS or PCS
 *
 *   Description:
 *   Corrections are fetched and output on the EPICS links.
 *
 *   Invocation:
 *   tcsOpticsM1Restore(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Epics inputs:
 *      a..n => Total Zernike corrections
 *      o    => Last stored elevation (degrees)
 *      p    => M2 x coma correction
 *      q    => M2 y coma correction
 *-
 */

long tcsOpticsM1Restore (struct genSubRecord *pgsub)
{

  int i ;                 /* Loop counter */
  double el ;             /* Restored elevation (rads) */
  double cosEl, sinEl ;   /* Cos & Sin of elevation */
  double comax, comay ;   /* X & Y coma corrections */

/* Firstly compute what the open loop model corrections were for the 
*  restored data and save these for later use
*/
  el = *(double *)pgsub->o * D2R ;
  cosEl = cos(el) ;
  sinEl = sin(el) ;

  for (i = 0 ; i < MAXZERNCOEFFS ; i++ ) {
    m1SavedModel[i] = m1ZernCoeffs[i][0]*cosEl + m1ZernCoeffs[i][1]*sinEl + 
                      m1ZernCoeffs[i][2] ;
  }

/* Now compute the differences between the totals now and the totals as
*  saved
*/
  latestZtoM1[0]  += *(double *)pgsub->a - m1TotalFigure[0] ;
  latestZtoM1[1]  += *(double *)pgsub->b - m1TotalFigure[1] ;
  latestZtoM1[2]  += *(double *)pgsub->c - m1TotalFigure[2] ;
  latestZtoM1[3]  += *(double *)pgsub->d - m1TotalFigure[3] ;
  latestZtoM1[4]  += *(double *)pgsub->e - m1TotalFigure[4] ;
  latestZtoM1[5]  += *(double *)pgsub->f - m1TotalFigure[5] ;
  latestZtoM1[6]  += *(double *)pgsub->g - m1TotalFigure[6] ;
  latestZtoM1[7]  += *(double *)pgsub->h - m1TotalFigure[7] ;
  latestZtoM1[8]  += *(double *)pgsub->i - m1TotalFigure[8] ;
  latestZtoM1[9]  += *(double *)pgsub->j - m1TotalFigure[9] ;
  latestZtoM1[10] += *(double *)pgsub->k - m1TotalFigure[10] ;
  latestZtoM1[11] += *(double *)pgsub->l - m1TotalFigure[11] ;
  latestZtoM1[12] += *(double *)pgsub->m - m1TotalFigure[12] ;
  latestZtoM1[13] += *(double *)pgsub->n - m1TotalFigure[13] ;
  
/* Zero and then restore the coma adjustments. Note that we unconditionally
*  restore the coma corrections whether or not the coma loop is closed 
*  (which is why we don't call tcsOpticsM2Coma(comax, comay)). This is
*  to bring the system as close as possible back to the state it was in 
*  prior to the reboot of the TCS or PCS.
*/
  comax = *(double *)pgsub->p ;
  comay = *(double *)pgsub->q ;
  tcsOpticsM2ClearComa();
  m2XErrorCorr += comax ;
  m2YErrorCorr += comay ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsInit
 *
 *   Purpose:
 *   Performs any initialisation needed by the optics library
 *
 *   Description:
 *   At present just create the semaphore that protects the optics data
 *
 *   Invocation:
 *   tcsOpticsInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   None
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   semMCreate     (semLib)           Create Mutex semaphore 
 *
 *-
 */

void tcsOpticsInit(void)

{
 static int first = TRUE; 
 static int dbgLevel = DBG_NONE;      /* Initialise debug level */

 if (first)
 {
   opticsSemId = epicsMutexMustCreate ();
   if (opticsSemId)
   {
     tcsOpticsSetTelScales(0.0);
     first = FALSE;
   }
   else
     DBGMSG (DBG_NONE, "tcsOpticsInit: Failed to create semaphore");
 }

}

/*+
 *   Function name:
 *   tcsOpticsM1ModelInit
 *
 *   Purpose:
 *   Check if a decision has been made how to initialise the M1 model
 *
 *   Description:
 *   Check the zero and restore flags to see if either are set
 *
 *   Invocation:
 *   value = tcsOpticsM1ModelInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      (<)  value  (int)  1 = decision made, 0 = no decision 
 * 
 *-
 */

int tcsOpticsM1ModelInit (void)
{

  return m1ZeroModel || m1RestoreModel;

}

/*+
 *   Function name:
 *   tcsOpticsM1ModelValid
 *
 *   Purpose:
 *   Check if a file of M1 data is valid i.e. not too old
 *
 *   Description:
 *   The TCS maintains data files of the current state of the corrections
 *   sent to the M1 mirror. It maintains separate files for AO observations
 *   (currently Altair at Gemini North and GeMS at Gemini South) and
 *   non-AO observations. Due to the time it can take to tune the mirror
 *   these files can be restored if the TCS is shut down or a switch is
 *   made from AO to non-AO modes. These files are only valid for a 
 *   configurable period of time. If deemed too old gthen they are not valid. 
 *   This routine checks if the file exists and if so that it is not too
 *   old. If it meets these criteria it is considered valid.
 *
 *   Invocation:
 *   valid = tcsOpticsM1ModelValid(filename, age, reason)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    filename    (char *)  Filename to check
 *      (>)    age         (long)   Maximum age (secs)
 *      (<)    reason      (char *)  Reason for validity flag setting
 *
 *   Function value:
 *      (<)  valid  (int)  1 = valid, 0 = not valid
 * 
 *-
 */

int tcsOpticsM1ModelValid (char *filename, long age, char *reason)
{
  struct stat filestat;
  int valid = 0;
  time_t tnow ;

  /* Fetch file status */
  if (!stat(filename, &filestat)) { 
    tnow = time(&tnow);
    if (tnow - filestat.st_mtime < age) {
      valid = 1;
      strcpy(reason, "File Ok");
    } else {
      strcpy(reason, "File out of date") ;
    }
  } else {
    strcpy(reason, "File not found");
  }

  return valid;

}

/*+
 *   Function name:
 *   tcsOpticsSetM1Restore
 *
 *   Purpose:
 *   Set flag to select which M1 model to restore on startup
 *
 *   Description:
 *   Simply set internal flags for use later
 *
 *   Invocation:
 *   tcsOpticsSetM1Restore(model)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *     (>)   model   (int)  non-AO model (=0), AO model (=1), GPI (=2)
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsOpticsSetM1Restore (int model)
{

  double tai;
  int ymdhmsf[7];

  char *fileNames[] = {"./data/M1Restore.pv",
                       "./data/M1RestoreAO.pv",
                       "./data/M1RestoreGPI.pv"};
  m1ZeroModel = 0 ;
  m1RestoreModel = 1 ;

  m1RestoreModelType = model ;
  /* Automatically start saving to the same file as you have restored */
  m1SaveModelType = model ;

  strcpy(m1RestoreFile, fileNames[m1RestoreModelType]);

  timeNow(&tai);
  timeThenC(tai, UTC, 4, ymdhmsf);
  sprintf(m1RestoreTime, "%4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
          ymdhmsf[0], ymdhmsf[1], ymdhmsf[2], ymdhmsf[3], ymdhmsf[4],
          ymdhmsf[5]);

  tcsOpticsM1SetInit() ;

}

/*+
 *   Function name:
 *   tcsOpticsSetM1Save
 *
 *   Purpose:
 *   Set the model that is currently being saved
 *
 *   Description:
 *   Sets the file type being saved
 *
 *   Invocation:
 *   tcsOpticsSetM1Save(model)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *     (>)   model   (int)  non-AO model (=0), AO model (=1), GPI (=2)
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsOpticsSetM1Save (int model)
{

  /* We just change where we are saving to, we don't need to change
   * either the last restored file name nor the time 
   */

  m1SaveModelType = model ;

}

/*+
 *   Function name:
 *   tcsOpticsSetM1Zero
 *
 *   Purpose:
 *   Set flag to zero M1 model on startup
 *
 *   Description:
 *   Simply set internal flag for use later
 *
 *   Invocation:
 *   tcsOpticsSetM1Zero()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsOpticsSetM1Zero (void)
{

  double tai;
  int ymdhmsf[7];

  m1ZeroModel = 1 ;
  m1RestoreModel = 0 ;
  strcpy(m1RestoreFile, "None");

  timeNow(&tai);
  timeThenC(tai, UTC, 4, ymdhmsf);
  sprintf(m1RestoreTime, "%4d-%2.2d-%2.2d %2.2d:%2.2d:%2.2d", 
          ymdhmsf[0], ymdhmsf[1], ymdhmsf[2], ymdhmsf[3], ymdhmsf[4],
          ymdhmsf[5]);

  tcsOpticsM1SetInit() ;

}

/*+
 *   Function name:
 *   tcsOpticsM1ClearModel
 *
 *   Purpose:
 *   Clear the flags that show the zero or restore commands have been issued.
 *
 *   Description:
 *   This routine is called when the TCS detects that the PCS has been 
 *   rebooted. It clears flags that show that the m1ZeroSet or m1ModelRestore
 *   commands have been issued. This then forces one of these commands
 *   to be issued by the user when the PCS comes back on line. 
 *
 *   Invocation:
 *   tcsOpticsM1ClearModel()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsOpticsM1ClearModel (void)
{

  m1ZeroModel = 0 ;
  m1RestoreModel = 0 ;
  tcsOpticsM1SetInit() ;

}


/*+
 *   Function name:
 *   tcsOpticsM1SetInit
 *
 *   Purpose:
 *   Set flag to initialise the M1 open loop figure corrections
 *
 *   Description:
 *   Simply set the init flag to TRUE
 *
 *   Invocation:
 *   tcsOpticsM1SetInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsOpticsM1SetInit (void)
{

  m1OpenLoopInit = TRUE ;

}

/*+
 *   Function name:
 *   tcsOpticsM1Offsets
 *
 *   Purpose:
 *   Fetch M1 offsets from the subsystem and store for later use
 *
 *   Description:
 *   The routine is attached to a genSub record that is scanned at 1 Hz. It
 *   pulls in the total offsets of M1 from its nominal position, converts
 *   the rotations to radians and stores the data for later use.
 *   Copies of the data (in units of arcsec) are output for access by EPICS 
 *
 *   Invocation:
 *   tcsOpticsM1Offsets (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 * 
 *   a => X offset (mm)
 *   b => Y offset (mm)
 *   c => Z offset 9mm)
 *   d => X rotation (millirads)
 *   e => Y rotation (millrads)
 *   f => Z rotation (millirads)
 *
 *   Epics outputs:
 *
 *   vala => X offset (mm)
 *   valb => Y offset (mm)
 *   valc => Z offset (mm)
 *   vald => X rotation (arcsec)
 *   vale => Y rotation (arcsec)
 *   valf => Z rotation (arcsec)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   There are no checks on the validity of the data read from the EPICS
 *   input links. This is assumed to be validated by the M1 control system.
 *
 *-
 */

long tcsOpticsM1Offsets (struct genSubRecord *pgsub) 
{

/* just copy the position offsets directly into the global variables */

  m1XUserOffset = *(double *)pgsub->a ;
  m1YUserOffset = *(double *)pgsub->b ;
  m1ZUserOffset = *(double *)pgsub->c ;

/* Copy the rotation offsets into global variables after scaling */

  m1XRotUserOffset = *(double *)pgsub->d / 1000.0 ;
  m1YRotUserOffset = *(double *)pgsub->e / 1000.0 ;
  m1ZRotUserOffset = *(double *)pgsub->f / 1000.0 ;

/* Output the data after scaling the rotations to arcsec */

  *(double *)pgsub->vala = m1XUserOffset ;
  *(double *)pgsub->valb = m1YUserOffset ;
  *(double *)pgsub->valc = m1ZUserOffset ;
  *(double *)pgsub->vald = m1XRotUserOffset / AS2R ;
  *(double *)pgsub->vale = m1YRotUserOffset / AS2R ;
  *(double *)pgsub->valf = m1ZRotUserOffset / AS2R ;

  return 0;
}


/*+
 *   Function name:
 *   tcsOpticsM1ShowCoeffs
 *
 *   Purpose:
 *   Makes current M1 figure coefficients visible to EPICS
 *
 *   Description:
 *   The data describing the current open loop optics model for M1 is
 *   simply copied to the output links of the gensub record to make
 *   them visible to EPICS.
 *
 *   Invocation:
 *   tcsOpticsM1ShowCoeffs (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   t => index to coefficients
 *
 *   Epics outputs:
 *
 *   vala => Coefficient of Z4
 *   valb => Coefficient of Z5
 *   valc => Coefficient of Z8
 *   vald => Coefficient of Z9
 *   vale => Coefficient of Z10
 *   valf => Coefficient of Z11
 *   valg => Coefficient of Z12
 *   valh => Coefficient of Z13
 *   vali => Coefficient of Z14
 *   valj => Coefficient of Z15
 *   valk => Coefficient of Z16
 *   vall => Coefficient of Z17
 *   valm => Coefficient of Z18
 *   valn => Coefficient of Z19
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsM1ShowCoeffs (struct genSubRecord *pgsub) 
{
  int arrayIndex ;

  arrayIndex = *(double *)pgsub->t ;

  *(double *)pgsub->vala = m1ZernCoeffs[0][arrayIndex];
  *(double *)pgsub->valb = m1ZernCoeffs[1][arrayIndex];
  *(double *)pgsub->valc = m1ZernCoeffs[2][arrayIndex];
  *(double *)pgsub->vald = m1ZernCoeffs[3][arrayIndex];
  *(double *)pgsub->vale = m1ZernCoeffs[4][arrayIndex];
  *(double *)pgsub->valf = m1ZernCoeffs[5][arrayIndex];
  *(double *)pgsub->valg = m1ZernCoeffs[6][arrayIndex];
  *(double *)pgsub->valh = m1ZernCoeffs[7][arrayIndex];
  *(double *)pgsub->vali = m1ZernCoeffs[8][arrayIndex];
  *(double *)pgsub->valj = m1ZernCoeffs[9][arrayIndex];
  *(double *)pgsub->valk = m1ZernCoeffs[10][arrayIndex];
  *(double *)pgsub->vall = m1ZernCoeffs[11][arrayIndex];
  *(double *)pgsub->valm = m1ZernCoeffs[12][arrayIndex];
  *(double *)pgsub->valn = m1ZernCoeffs[13][arrayIndex];
 
  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsM1StoreCoeffs
 *
 *   Purpose:
 *   Read in and store coefficients for the M1 open loop figure corrections
 *
 *   Description:
 *   This routine simply reads in and stores the coefficients of the M1 
 *   open loop figure model. The model for each Zernike term can have three
 *   coefficients. The number of the coefficient is read in and an internal
 *   array updated for later use. 
 *
 *   Invocation:
 *   tcsOpticsM1StoreCoeffs (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs :
 *
 *   a => Coefficient for Z4
 *   b => Coefficient for Z5
 *   c => Coefficient for Z8
 *   d => Coefficient for Z9
 *   e => Coefficient for Z10
 *   f => Coefficient for Z11
 *   g => Coefficient for Z12
 *   h => Coefficient for Z13
 *   i => Coefficient for Z14
 *   j => Coefficient for Z15
 *   k => Coefficient for Z16
 *   l => Coefficient for Z17
 *   m => Coefficient for Z18
 *   n => Coefficient for Z19
 *   u => index of coefficient to load
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsM1StoreCoeffs (struct genSubRecord *pgsub)
{
  long arrayIndex ;
  int i,j ;                    /* loop indices */

/* fetch index to see which set of coefficients to update */
  arrayIndex = *(double *)pgsub->u ;

/* Now fetch each coefficient and store in the appropriate array location */
  m1NewZernCoeffs[0][arrayIndex]  = *(double *)pgsub->a ;
  m1NewZernCoeffs[1][arrayIndex]  = *(double *)pgsub->b ;
  m1NewZernCoeffs[2][arrayIndex]  = *(double *)pgsub->c ;
  m1NewZernCoeffs[3][arrayIndex]  = *(double *)pgsub->d ;
  m1NewZernCoeffs[4][arrayIndex]  = *(double *)pgsub->e ;
  m1NewZernCoeffs[5][arrayIndex]  = *(double *)pgsub->f ;
  m1NewZernCoeffs[6][arrayIndex]  = *(double *)pgsub->g ;
  m1NewZernCoeffs[7][arrayIndex]  = *(double *)pgsub->h ;
  m1NewZernCoeffs[8][arrayIndex]  = *(double *)pgsub->i ;
  m1NewZernCoeffs[9][arrayIndex]  = *(double *)pgsub->j ;
  m1NewZernCoeffs[10][arrayIndex] = *(double *)pgsub->k ;
  m1NewZernCoeffs[11][arrayIndex] = *(double *)pgsub->l ;
  m1NewZernCoeffs[12][arrayIndex] = *(double *)pgsub->m ;
  m1NewZernCoeffs[13][arrayIndex] = *(double *)pgsub->n ;
  
/* If this is the last index then copy the data from the temporary array
*  to the permanent location.
*/
  if (arrayIndex == 2 ) {
    if (opticsSemId) {
       epicsMutexLock(opticsSemId);
        for (i = 0; i < MAXZERNCOEFFS; i++) {
          for (j = 0; j < 3; j++) {
            m1ZernCoeffs[i][j] = m1NewZernCoeffs[i][j] ;
          }
        }
      epicsMutexUnlock(opticsSemId);
      }
    else{
        printf("DBG1 Failed to create semaphore opticsSemId\n");
        }
   }

  return 0 ;
}


/*+
 *   Function name:
 *   tcsOpticsM2ClearComa
 *
 *   Purpose:
 *   Zero the translation corrections for coma
 *
 *   Description:
 *   This routine simply sets the corrections that have been calculated to
 *   compensate for coma to zero. When closed loop active optics is running
 *   the TCS adjusts the position of M2 by moving in X and Y to compensate
 *   for any coma error. Normally when closed loop corrections are stopped
 *   you want to maintain the corrected position of M2 so that the image
 *   quality doesn't instantly degrade. For test and commissioning purposes
 *   or if the corrections applied are incorrect for some reason then a
 *   means of setting these corrections to zero is required. This routine
 *   permits this to be done and is normally called from the zeroComaCorr
 *   command. 
 *
 *   Invocation:
 *   tcsOpticsM2ClearComa()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *   None
 *
 *   Function value:
 *   None
 *
 *-
 */

void tcsOpticsM2ClearComa (void)
{
  m2XErrorCorr = 0.0 ;
  m2YErrorCorr = 0.0 ;
}

/*+
 *   Function name:
 *   tcsOpticsM2Coma
 *
 *   Purpose:
 *   Compute mirror translations to correct for the measured coma
 *
 *   Description:
 *   Originally this routine was written to take measured coma corrections
 *   in microns of wavefront error and convert these to corresponding
 *   lateral shifts in M2. However, the interaction matrix used by the
 *   WFS to generate coma values from the spot pattern is calibrated by
 *   using known M2 translations in mm. This means the WFS now return
 *   mirror shifts directly in mm and no conversion is required. Any
 *   new corrections are simply summed.
 *
 *   Invocation:
 *   tcsOpticsM2Coma (z5, z6)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    z5   (double)  X translation due to coma 
 *      (>)    z6   (double)  Y translation due to coma 
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *   It is assumed that M2 moves fast enough that the full correction can be
 *   applied immediately. It may be that a proper PI servo is needed in the
 *   future. 
 * 
 *-
 */

void tcsOpticsM2Coma (double z5, double z6)
{
  if (m2ComaCorrect) {
    m2XErrorCorr += z5 ;
    m2YErrorCorr += z6 ;
  }
}

/*+
 *   Function name:
 *   tcsOpticsM2ModelTilt
 *
 *   Purpose:
 *   Generate model corrections to X,Y tilts of M2
 *
 *   Description:
 *   This routine is a place holder at the moment as the true model (if any)
 *   for the tilts of M2 as a function of elevation is unknown. The 
 *   "model" implemented here allows both the X and Y tilts to depend
 *   on the cosine of the elevation. In practice once the code has been
 *   tested, this routine will always be presented with coefficients
 *   that are set to zero.
 *
 *   Invocation:
 *   tcsOpticsM2ModelTilt (xcoeff, ycoeff, &xcorr, &ycorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    xcoeff   (double)   Coefficient for X model displacement
 *      (>)    ycoeff   (double)   Coefficient for Y model displacent
 *      (<)    xcorr    (double *) X model correction (rad)
 *      (<)    ycorr    (double *) Y model correction (rad)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsGetMountAzEl (tcsPointing)    Return demand mount az and el
 *
 *   Deficiencies:
 *   Only an estimated model is currently implemented.
 *
 *-
 */

void tcsOpticsM2ModelTilt (double xcoeff, double ycoeff, 
                         double *xcorr, double *ycorr)
{
   double elevation;      /* current demand elevation */
   double azimuth;        /* current demand azimuth */

   tcsGetMountAzEl (&azimuth, &elevation);
   *xcorr = xcoeff * cos(elevation);
   *ycorr = ycoeff * cos(elevation);
 
}

/*+
 *   Function name:
 *   tcsOpticsM2ModelXY
 *
 *   Purpose:
 *   Generate model corrections to X,Y translation of M2
 *
 *   Description:
 *   This routine is really a place holder at the current time in that the 
 *   model that it implements is very crude. The true model may be more
 *   complex and hence need more parmaters to be passed to it. The 
 *   determination of this model must await commissioning. The model for
 *   the displacement in Y provides a 1.4mm correction at the horizon
 *   varying as cosine of the elevation. This maximum sag is based on
 *   FEA analysis. 
 *
 *   Invocation:
 *   tcsOpticsM2ModelXY (xcoeff1, xcoeff2, ycoeff1, ycoeff2, &xcorr, &ycorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    xcoeff1   (double)   Coefficient for X model displacement
 *      (>)    xcoeff2   (double)   Coefficient for X model displacement
 *      (>)    ycoeff1   (double)   Coefficient for Y model displacent
 *      (>)    ycoeff2   (double)   Coefficient for Y model displacent
 *      (<)    xcorr    (double *) X model correction (mm)
 *      (<)    ycorr    (double *) Y model correction (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsGetMountAzEl (tcsPointing)    Return demand mount az and el
 *
 *   Deficiencies:
 *   Only an estimated model is currently implemented.
 *
 *-
 */

void tcsOpticsM2ModelXY (double xcoeff1, double xcoeff2, 
                         double ycoeff1, double ycoeff2, 
                         double *xcorr, double *ycorr)
{
   double elevation;      /* current demand elevation */
   double azimuth;        /* current demand azimuth */

   tcsGetMountAzEl (&azimuth, &elevation);
   *ycorr = ycoeff1 * cos(elevation) + ycoeff2 * sin(elevation);
   *xcorr = xcoeff1 * cos(elevation) + xcoeff2 * sin(elevation);
 
}

/*+
 *   Function name:
 *   tcsOpticsM2ModelZ
 *
 *   Purpose:
 *   Generate model corrections to Z (focus) translation of M2
 *
 *   Description:
 *   This routine is a place holder for the true model (if any) that will
 *   describe the movement of z as a function of elevation.
 *
 *   Invocation:
 *   tcsOpticsM2ModelZ (zcoeff1, zcoeff2, &zcorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    zcoeff   (double)   Coefficient for Z model displacement
 *      (<)    zcorr    (double *) Z model correction (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsGetMountAzEl (tcsPointing)    Return demand mount az and el
 *
 *   Deficiencies:
 *   Only an estimated model is currently implemented.
 *
 *-
 */

void tcsOpticsM2ModelZ (double zcoeff1, double zcoeff2, double *zcorr) 
{
   double elevation;      /* current demand elevation */
   double azimuth;        /* current demand azimuth */

   tcsGetMountAzEl (&azimuth, &elevation);
   *zcorr = zcoeff1 * cos(elevation) + zcoeff2 * sin( 1.7 * elevation);
 
}


/*+
 *   Function name:
 *   tcsOpticsM2Move
 *
 *   Purpose:
 *   Compute desired position of M2 and issue move command
 *
 *   Description:
 *   This routine is intended to provide a stop gap method of correcting 
 *   coma by tilting M2. This is necessary as it is not possible to translate
 *   M2. Each time the record is processed it grabs the current nominal
 *   demands and then adds a model correction (if the model is enabled).
 *   The logic for whether the routine is called or not is controlled by
 *   EPICS
 *
 *   Invocation:
 *   tcsOpticsM2Move (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub  (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   a => model corrections on or off
 *
 *   Epics outputs:
 *
 *   vala => x tilt Beam A
 *   valb => y tilt Beam A
 *   valc => x tilt Beam B
 *   vald => y tilt Beam B
 *   vale => x tilt Beam C
 *   valf => y tilt Beam C
 *   valg => x position (microns)
 *   valh => y position (microns)
 *   vali => z position (microns)
 *   valj => Start directive
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsOpticsM2Move (struct genSubRecord *pgsub)

{

  int modelOn ;              /* Flag to show if model is on */
  double nomPosn[5] ;        /* Nominal position for M2 */
  double coeffs[3] ;         /* Model coefficients */
  double cosEl, sinEl ;      /* Cos & sin of elevation */
  double currAz, currEl ;    /* Current az/el (rads) */
  int i ;                    /* Loop counter */
  double comaTilt ;          /* Tilt correction (arcsec) */

/* Fetch flag to see if model corrections should be on */
  modelOn = *(long *)pgsub->a ;

/* Fetch current model coefficients and nominal demands */
    if (opticsSemId) {
       epicsMutexLock(opticsSemId);
       for (i = 0; i < 3 ; i++ ) 
         coeffs[i] = m2ComaTiltCoeffs[i] ;
       for (i = 0; i < 5 ; i++ )
         nomPosn[i] = m2NominalPosn[i] ;
       epicsMutexUnlock(opticsSemId);
    } else {
        printf("DBG2 Failed to create semaphore opticsSemId\n");
        return 0;
    }

/* Grab current elevation */
  tcsGetMountAzEl(&currAz, &currEl) ;

/* Compute model if necessary */
  if (modelOn) {
    cosEl = cos(currEl) ;
    sinEl = sin(currEl) ;
    comaTilt = coeffs[0]*cosEl + coeffs[1]*sinEl + coeffs[2] ;
  } else {
    comaTilt = 0.0 ;
  }

/* Save coma tilt correction for use by pointing adjustment code */
  m2ComaTilt = comaTilt ;

/* Now output demands */
  *(double *)pgsub->vala = nomPosn[0] + comaTilt ;
  *(double *)pgsub->valb = nomPosn[1] ;
  *(double *)pgsub->valc = nomPosn[0] + comaTilt ;
  *(double *)pgsub->vald = nomPosn[1] ;
  *(double *)pgsub->vale = nomPosn[0] + comaTilt ;
  *(double *)pgsub->valf = nomPosn[1] ;
  *(double *)pgsub->valg = nomPosn[2] ;
  *(double *)pgsub->valh = nomPosn[3] ;
  *(double *)pgsub->vali = nomPosn[4] ;
  strcpy (pgsub->valj, "START") ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsM2ThermalTilt
 *
 *   Purpose:
 *   Computes thermal contribution to tilts of M2
 *
 *   Description:
 *   This routine is currently a placeholder as the true thermal model of
 *   the X,Y tilts of M2 is unknown. It may turn out to be 
 *   unnecessary. The "model" implemented here is simply a linear one
 *   It is probable that the temperature coefficients will generally be
 *   set to zero once it has been verified that a non-zero correction 
 *   can be handled consistently throughout the TCS code.
 *
 *   Invocation:
 *   tcsOpticsM2ThermalTilt (tempRef, xcoeff, ycoeff, &xcorr, &ycorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tempRef  (double)   Reference temperature (deg. C)
 *      (>)    xcoeff   (double)   Slope of temp. correction (rad/C)
 *      (>)    ycoeff   (double)   Slope of temp correction (rad/C)
 *      (<)    xcorr    (double *) X temperature correction (rad)
 *      (<)    ycorr    (double *) Y temperature correction (rad)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Deficiencies:
 *   The model implemented here will need to be replaced by one derived 
 *   from calibrations of the real telescope. Also, the temperature used
 *   for the corrections is that used in the TCS refraction model. This is
 *   not necessarily the correct one to use.
 *
 *-
 */

void tcsOpticsM2ThermalTilt (double tempRef, double xcoeff, double ycoeff,
                           double *xcorr, double *ycorr)
{
  double tempTel;         /* Temperature of telescope */

/* Fetch current temperature */

  tcsGetTemperature(&tempTel);

  *xcorr = xcoeff * (tempRef - tempTel);
  *ycorr = ycoeff * (tempRef - tempTel);

}

/*+
 *   Function name:
 *   tcsOpticsM2ThermalXY
 *
 *   Purpose:
 *   Computes thermal contribution to X,Y position of M2
 *
 *   Description:
 *   This routine is currently a placeholder as the true thermal model of
 *   the X,Y translation of M2 is unknown. It may turn out to be 
 *   unnecessary. The "model" implemented here is simply a linear one
 *   It is probable that the temperature coefficients will generally be
 *   set to zero once it has been verified that a non-zero correction 
 *   can be handled consistently throughout the TCS code.
 *
 *   Invocation:
 *   tcsOpticsM2ThermalXY (tempRef, xcoeff, ycoeff, &xcorr, &ycorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tempRef  (double)   Reference temperature (deg. C)
 *      (>)    xcoeff   (double)   Slope of temp. correction (mm/C)
 *      (>)    ycoeff   (double)   Slope of temp correction (mm/C)
 *      (<)    xcorr    (double *) X temperature correction (mm)
 *      (<)    ycorr    (double *) Y temperature correction (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   Deficiencies:
 *   The model implemented here will need to be replaced by one derived 
 *   from calibrations of the real telescope. Also, the temperature used
 *   for the corrections is that used in the TCS refraction model. This is
 *   not necessarily the correct one to use.
 *
 *-
 */

void tcsOpticsM2ThermalXY (double tempRef, double xcoeff, double ycoeff,
                           double *xcorr, double *ycorr)
{
  double tempTel;         /* Temperature of telescope */

/* Fetch current temperature */

  tcsGetTemperature(&tempTel);

  *xcorr = xcoeff * (tempRef - tempTel);
  *ycorr = ycoeff * (tempRef - tempTel);

}

/*+
 *   Function name:
 *   tcsOpticsM2ThermalZ
 *
 *   Purpose:
 *   Computes thermal contribution to Z (focus) position of M2
 *
 *   Description:
 *   The model implemented here is a simple linear one. It should be
 *   considered as a placeholder until the true relationship has been
 *   calibrated at commissioning. For test purposes the coefficient
 *   describing the expansion was set to 0.138 mm/deg C which is the 
 *   expansion of steel multiplied by the primary to secondary separation.
 *
 *   Invocation:
 *   tcsOpticsM2ThermalZ (ttemp, tempRef, zcoeff, &zcorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    ttemp    (double)   Telescope truss temperature (deg. C)
 *      (>)    tempRef  (double)   Reference temperature (deg. C)
 *      (>)    zcoeff   (double)   Slope of temp. correction (mm/C)
 *      (<)    zcorr    (double *) Z temperature correction (mm)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   The model implemented here will need to be replaced by one derived 
 *   from calibrations of the real telescope. Also, the temperature used
 *   for the corrections is that used in the TCS refraction model. This is
 *   not necessarily the correct one to use.
 *
 *-
 */

void tcsOpticsM2ThermalZ (double ttemp, double tempRef, double zcoeff,
                          double *zcorr)
{
  *zcorr = zcoeff * (tempRef - ttemp);

}

/*+
 *   Function name:
 *   tcsOpticsM2XY
 *
 *   Purpose:
 *   Generate X, Y translations for M2
 *
 *   Description:
 *   This routine is called periodically by EPICS with the purpose of 
 *   generating demand X and Y translations for M2. The total translation
 *   in each axis is the sum of a zero point, a thermal contribution,
 *   a model contribution, any user offset and the current DC error
 *   term from the WFS. This routine will generate new thermal and model
 *   contributions based on the current temperature and elevation.
 *
 *   Invocation:
 *   tcsOpticsM2XY (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => Nominal X position
 *   b => Nominal Y position
 *   c => Thermal model reference temperature
 *   d => Thermal model X coefficient (mm/C)
 *   e => Thermal model Y coefficient (mm/C)
 *   f => Model X coefficient 1 (mm)
 *   g => Model Y coefficient 1 (mm)
 *   h => Current X position (microns)
 *   i => Current Y position (microns)
 *   j => Model X coefficient 2 (mm)
 *   k => Model Y coefficient 2 (mm)
 *
 *   Epics outputs:
 *
 *   vala => X temperature correction (mm)
 *   valb => Y temperature correction (mm)
 *   valc => X Model correction (mm)
 *   vald => Y Model correction (mm)
 *   vale => X total correction (mm)
 *   valf => Y total correction (mm)
 *   valg => X Nominal position (mm)
 *   valh => Y Nominal position (mm)
 *   vali => Current X position (mm)
 *   valj => Current Y position (mm)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsM2XY (struct genSubRecord *pgsub)

{
 double userOffset[2];       /* local copy of user offsets */
 double nominal[2];          /* local values of nominal X,Y positions */
 double tempCorr[2];         /* local values of temperature corrections */
 double errorCorr[2];        /* local values of error correction */
 double modelCorr[2];        /* local values of model correction */
 double tcsDemand[2];        /* local copy of total X, Y demand */
 double tempCoeff[2];        /* X,Y temperature coefficients */
 double modelCoeff[4];       /* X,Y model coefficients */
 double tempDefault;         /* Reference temperature for model */
 int i;                      /* loop counter */

/* First read in inputs from all the EPICS links into the appropriate
 * local variables
*/

 if (! opticsSemId){
        printf("DBG3 Failed to create semaphore opticsSemId\n");
     return 0;
 }

 nominal[0] = *(double *)pgsub->a;
 nominal[1] = *(double *)pgsub->b;
 tempDefault = *(double *)pgsub->c;
 tempCoeff[0] = *(double *)pgsub->d;
 tempCoeff[1] = *(double *)pgsub->e;
 modelCoeff[0] = *(double *)pgsub->f;
 modelCoeff[1] = *(double *)pgsub->j;
 modelCoeff[2] = *(double *)pgsub->g;
 modelCoeff[3] = *(double *)pgsub->k;

/* Generate the current thermal corrections to the X, Y positions */

 tcsOpticsM2ThermalXY (tempDefault, tempCoeff[0], tempCoeff[1], &tempCorr[0],
                       &tempCorr[1]);

/* Generate the current model corrections to the X, Y positions */

 tcsOpticsM2ModelXY (modelCoeff[0], modelCoeff[1], modelCoeff[2],
                     modelCoeff[3], &modelCorr[0], &modelCorr[1]);

/* Now lock the database to grab consistent user and error corrections */

 epicsMutexLock(opticsSemId);

 errorCorr[0] = m2XErrorCorr;
 errorCorr[1] = m2YErrorCorr;
 userOffset[0] = m2XUserOffset;
 userOffset[1] = m2YUserOffset;

 epicsMutexUnlock(opticsSemId);

/* Form the total demand in X and Y */

  for (i = 0 ; i < 2 ; i++)
  {
   tcsDemand[i] = 0.0;
   tcsDemand[i] += errorCorr[i];
   tcsDemand[i] += userOffset[i];
   tcsDemand[i] += nominal[i];
   if (m2XYTempEnable)
     tcsDemand[i] += tempCorr[i];
   if (m2XYModelEnable)
     tcsDemand[i] += modelCorr[i];
  }

/* Now write the new data back into the database */

    epicsMutexLock(opticsSemId);
    m2XTempCorr = tempCorr[0];
    m2YTempCorr = tempCorr[1];
    m2XModelCorr = modelCorr[0];
    m2YModelCorr = modelCorr[1];
    m2XDemand = tcsDemand[0];
    m2YDemand = tcsDemand[1];
    m2XNominal   = nominal[0];
    m2YNominal   = nominal[1];
    epicsMutexUnlock(opticsSemId);

/* Output the data onto the EPICS links */

   *(double *)pgsub->vala = tempCorr[0];
   *(double *)pgsub->valb = tempCorr[1];
   *(double *)pgsub->valc = modelCorr[0];
   *(double *)pgsub->vald = modelCorr[1];
   *(double *)pgsub->vale = tcsDemand[0];
   *(double *)pgsub->valf = tcsDemand[1];
   *(double *)pgsub->valg = nominal[0];
   *(double *)pgsub->valh = nominal[1];
   *(double *)pgsub->vali = *(double *)pgsub->h / 1000.0;
   *(double *)pgsub->valj = *(double *)pgsub->i / 1000.0;


   return 0;

}


/*+
 *   Function name:
 *   tcsOpticsM2XYErr
 *
 *   Purpose:
 *   Exports M2 translation corrections to EPICS
 *
 *   Description:
 *   This routine smply writes some internal data to its EPICS outputs.
 *   The routine only exists as there are not enough output ports on
 *   M2XY.
 *
 *   Invocation:
 *   tcsOpticsM2XYErr(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub  (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsM2XYErr (struct genSubRecord *pgsub)
{

  *(double *)pgsub->vala = m2XErrorCorr ;
  *(double *)pgsub->valb = m2YErrorCorr ;
  return 0 ;
}

/*+
 *   Function name:
 *   tcsOpticsM2Tilt
 *
 *   Purpose:
 *   Generate X, Y tilts for M2
 *
 *   Description:
 *   This routine is called periodically by EPICS with the purpose of 
 *   generating demand X and Y tilts for M2. The total tilt
 *   in each axis is the sum of a zero point, a thermal contribution,
 *   a model contribution and the current DC error
 *   term from the WFS. This routine will generate new thermal and model
 *   contributions based on the current temperature and elevation.
 *
 *   Invocation:
 *   tcsOpticsM2Tilt (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => Nominal X tilt (rads)
 *   b => Nominal Y tilt (rads)
 *   c => Thermal model reference temperature
 *   d => Thermal model X coefficient (rads/C)
 *   e => Thermal model Y coefficient (rads/C)
 *   f => Model X coefficient (rads)
 *   g => Model Y coefficient (rads)
 *
 *   Epics outputs:
 *
 *   vala => X temperature correction (rads)
 *   valb => Y temperature correction (rads)
 *   valc => X Model correction (rads)
 *   vald => Y Model correction (rads)
 *   vale => X total correction (rads)
 *   valf => Y total correction (rads)
 *   valg => X Nominal position (rads)
 *   valh => Y Nominal position (rads)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsOpticsM2Tilt (struct genSubRecord *pgsub)

{
 double nominal[2];          /* local values of nominal X,Y positions */
 double tempCorr[2];         /* local values of temperature corrections */
 double errorCorr[2];        /* local values of error correction */
 double modelCorr[2];        /* local values of model correction */
 double tcsDemand[2];        /* local copy of total X, Y demand */
 double tempCoeff[2];        /* X,Y temperature coefficients */
 double modelCoeff[2];       /* X,Y model coefficients */
 double tempDefault;         /* Reference temperature for model */
 int i;                      /* loop counter */

/* First read in inputs from all the EPICS links into the appropriate
 * local variables
*/

 nominal[0] = *(double *)pgsub->a;
 nominal[1] = *(double *)pgsub->b;
 tempDefault = *(double *)pgsub->c;
 tempCoeff[0] = *(double *)pgsub->d;
 tempCoeff[1] = *(double *)pgsub->e;
 modelCoeff[0] = *(double *)pgsub->f;
 modelCoeff[1] = *(double *)pgsub->g;

/* Generate the current thermal corrections to the X, Y positions */

 if (! opticsSemId){
        printf("DBG4 Failed to create semaphore opticsSemId\n");
     return 0;
 }

 tcsOpticsM2ThermalTilt (tempDefault, tempCoeff[0], tempCoeff[1], &tempCorr[0],
                       &tempCorr[1]);

/* Generate the current model corrections to the X, Y positions */

 tcsOpticsM2ModelTilt (modelCoeff[0], modelCoeff[1], &modelCorr[0],
                     &modelCorr[1]);

/* Now lock the database to grab consistent error corrections */

 epicsMutexLock(opticsSemId);

 errorCorr[0] = m2XTiltErrorCorr;
 errorCorr[1] = m2YTiltErrorCorr;

 epicsMutexUnlock(opticsSemId);

/* Form the total demand in X and Y */

  for (i = 0 ; i < 2 ; i++)
  {
   tcsDemand[i] = 0.0;
   tcsDemand[i] += errorCorr[i];
   tcsDemand[i] += nominal[i];
   if (m2TiltTempEnable)
     tcsDemand[i] += tempCorr[i];
   if (m2TiltModelEnable)
     tcsDemand[i] += modelCorr[i];
  }

/* Now write the new data back into the database */

    epicsMutexLock(opticsSemId);
    m2XTiltTempCorr = tempCorr[0];
    m2YTiltTempCorr = tempCorr[1];
    m2XTiltModelCorr = modelCorr[0];
    m2YTiltModelCorr = modelCorr[1];
    m2XTiltDemand = tcsDemand[0];
    m2YTiltDemand = tcsDemand[1];
    m2XTiltNominal   = nominal[0];
    m2YTiltNominal   = nominal[1];
    epicsMutexUnlock(opticsSemId);

/* Output the data onto the EPICS links */

   *(double *)pgsub->vala = tempCorr[0];
   *(double *)pgsub->valb = tempCorr[1];
   *(double *)pgsub->valc = modelCorr[0];
   *(double *)pgsub->vald = modelCorr[1];
   *(double *)pgsub->vale = tcsDemand[0];
   *(double *)pgsub->valf = tcsDemand[1];
   *(double *)pgsub->valg = nominal[0];
   *(double *)pgsub->valh = nominal[1];


   return 0;

}

/*+
 *   Function name:
 *   tcsOpticsM2Z
 *
 *   Purpose:
 *   Generate Z (focus) translation for M2
 *
 *   Description:
 *   This routine is called periodically by EPICS with the purpose of 
 *   generating demand Z (focus) translations for M2. The total translation
 *   is the sum of a zero point, a thermal contribution,
 *   a model contribution, any user offset and the current DC error
 *   term from the WFS. This routine will generate new thermal and model
 *   contributions based on the current temperature and elevation.
 *   The sign convention for z is such that if M2 is moved towards M1 
 *   away from its nominal position then deltaZ is negative resulting in
 *   an increased focal length.
 *
 *   Invocation:
 *   tcsOpticsM2Z (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => Nominal Z position
 *   b => Thermal model reference temperature
 *   c => Thermal model Z coefficient (mm/C)
 *   d => Model Z coefficient (mm)
 *   e => Current Z Position (microns)
 *   f => Current focus guide correction from M2 (microns)
 *   g => Second Z model coefficient
 *   h => truss temperature (deg C)
 *
 *   Epics outputs:
 *
 *   vala => Z temperature correction (mm)
 *   valb => Z Model correction (mm)
 *   valc => Z total correction (mm)
 *   vald => Z Nominal position (mm)
 *   vale => Current focal length (mm)
 *   valf => Current z position (mm)
 *   valg => Smoothed focus guide correction (mm)
 *   valh => M2 scale factor
 *   vali => M2 Magnification
 *   valj => Flag showing if temp. corrections to focus are enabled
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   The sampling interval and break frequency that control the filtering
 *   of the Z focus error are hard coded.
 *
 *-
 */

long tcsOpticsM2Z (struct genSubRecord *pgsub)

{
 double userOffset;       /* local copy of user offset */
 double insOffset ;       /* local copy of instrument offset */
 double m1UserOffset ;    /* local copy of M1 Z user offset */
 double nominal;          /* local value of nominal Z position */
 double tempCorr;         /* local value of temperature correction */
 double errorCorr;        /* local value of error correction */
 double modelCorr;        /* local value of model correction */
 double tcsDemand;        /* local copy of total Z demand */
 double tempCoeff;        /* Z temperature coefficient */
 double modelCoeff1;      /* Z model coefficient 1 */
 double modelCoeff2;      /* Z model coefficient 2 */
 double tempDefault;      /* Reference temperature for model */
 double dz;               /* Offset from nominal */
 double fl;               /* Local value of focal length */
 double zError ;          /* Current value of M2 focus error (mm) */
 double zErrorSmooth;     /* Smoothed value of zError (mm) */
 double m2Scale ;         /* Sky tilt * m2Scale = tilt of M2 */
 double ttemp ;           /* Truss temperature (deg C) */
 static double dt = 0.05; /* Sampling interval (secs) */
 static double kp = 0.05 ; /* Proportional gain */
 static double ki = 0.5;  /* Integral gain */

/* First read in inputs from all the EPICS links into the appropriate
 * local variables
*/
 if (! opticsSemId){
        printf("DBG5 Failed to create semaphore opticsSemId\n");
     return 0;
 }

 nominal = *(double *)pgsub->a;
 tempDefault = *(double *)pgsub->b;
 tempCoeff = *(double *)pgsub->c;
 modelCoeff1= *(double *)pgsub->d;
 modelCoeff2= *(double *)pgsub->g;
 ttemp      = *(double *)pgsub->h ;

/* Generate the current thermal correction to the Z position */

 tcsOpticsM2ThermalZ (ttemp, tempDefault, tempCoeff, &tempCorr);

/* Generate the current model correction to the Z position */

 tcsOpticsM2ModelZ (modelCoeff1, modelCoeff2, &modelCorr);

/* Generate the current error correction to the Z position */
 if (m2AbsorbFocus) {
   zError = *(double *)pgsub->f/1000.0;
   zErrorSmooth = zError ;
   errorCorr = tcsOpticsM2ZServo (kp, ki, dt, zErrorSmooth);
  } else {
   errorCorr = m2ZErrorCorr ;
  }


/* Now lock the database to grab consistent user corrections */

 epicsMutexLock(opticsSemId);

 userOffset = m2ZUserOffset;
 insOffset  = m2ZInsOffset ;
 m1UserOffset = m1ZUserOffset ;

 epicsMutexUnlock(opticsSemId);

/* Form the total demand in Z as well as the offset from the nominal
 * position
 */

  tcsDemand = 0.0;
  dz = 0.0;

  tcsDemand += errorCorr;
  tcsDemand += userOffset;
  tcsDemand += insOffset ;
  tcsDemand += nominal;
  dz        += userOffset;
  dz        += insOffset;
  dz        -= m1UserOffset;

/* If temperature corrections are not enabled then don't add this 
*  correction to the demand to M2. A similar  
*  argument applies to the model correction.
*/

  if (m2ZTempEnable)
     tcsDemand += tempCorr;

   if (m2ZModelEnable)
     tcsDemand += modelCorr;

/* Set up image scales and focal length */

   tcsOpticsSetTelScales (dz) ;
   tcsOpticsGetFl(&fl) ;
   m2Scale = tcsOpticsScaleThrow (1.0) ;

/* Now write the new data back into the database */

    epicsMutexLock(opticsSemId);
    m2ZTempCorr = tempCorr;
    m2ZModelCorr = modelCorr;
    m2ZErrorCorr = errorCorr;
    m2ZDemand = tcsDemand;
    m2ZNominal   = nominal;
    m2ZTempRef = tempDefault;
    flCurrent = fl;
    deltaZ    = dz;
    epicsMutexUnlock(opticsSemId);

/* Output the data onto the EPICS links */

   *(double *)pgsub->vala = tempCorr;
   *(double *)pgsub->valb = modelCorr;
   *(double *)pgsub->valc = tcsDemand;
   *(double *)pgsub->vald = nominal;
   *(double *)pgsub->vale = fl;
   *(double *)pgsub->valf = *(double *)pgsub->e / 1000.0;
   *(double *)pgsub->valg = errorCorr;
   *(double *)pgsub->valh = m2Scale ;
   *(double *)pgsub->vali = m2Mag ;
   *(long *)pgsub->valj   = m2ZTempEnable ;


   return 0;

}

/*+
 *   Function name:
 *   tcsOpticsM2ZValues
 *
 *   Purpose:
 *   Makes internal focus data available to EPICS
 *
 *   Description:
 *   Currently just copy some internal data to EPICS output links. This
 *   routine was only added because other genSub records had run out
 *   of links.
 *
 *   Invocation:
 *   tcsOpticsM2ZValues(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsOpticsM2ZValues (struct genSubRecord *pgsub)
{

  *(double *)pgsub->vala = m2ZInsOffset ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsM2ZFilter
 *
 *   Purpose:
 *   Filters out high frequency components of the M2 focus error
 *
 *   Description:
 *   This routine implements a simple low pass filter. The break frequency
 *   at which the gain is 3dB is specified in Hz.
 *
 *   Invocation:
 *   output = tcsOpticsM2ZFilter(dt, freq0, input)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     dt    (double)   Sampling interval (secs)
 *      (>)     freq0 (double)   Frequency (Hz) at which gain is 3dB
 *      (>)     input (double)   Input signal
 *
 *   Function value:
 *   (<)  output  (double) Output signal (mm) 
 * 
 *-
 */

double tcsOpticsM2ZFilter (double dt, double freq0, double input)
{
  static int first = TRUE ;
  static double lastOutput ;       /* Last value output */
  static double lastInput ;        /* Last value input */
  double output ;
  double k ;                       /* Break frequency (rads/s) */
  double a, b ;                    /* Filter constants */

  if (first) {
    lastOutput = 0.0;
    lastInput  = 0.0;
    first = FALSE;
  }

  k = freq0 * 2.0 * PI ;
  a = (k * dt - 2.0) / (k * dt + 2.0) ;
  b = k * dt / (k * dt + 2.0) ;

  output =  -a * lastOutput + b * (input + lastInput) ;
  lastOutput = output ;
  lastInput = input ;

  return output ;
}


/*+
 *   Function name:
 *   tcsOpticsM2ZServo
 *
 *   Purpose:
 *   Implements a slow servo loop to absorb m2 focus offsets into the TCS
 *
 *   Description:
 *   This routine implements a slow servo algorithm so that any DC terms in
 *   the focus corrections being applied by the WFS to M2 can be absorbed
 *   into the model used by the TCS.
 *
 *   Invocation:
 *   output = tcsOpticsM2ZServo (kp, ki, dt, input)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     kp   (double)  Proportional gain
 *      (>)     ki   (double)  Integral gain
 *      (>)     dt   (double)  Time interval (secs)
 *      (>)     input (double) Input data
 *
 *   Function value:
 *   (<)  output  (double) Output value 
 * 
 *-
 */

double tcsOpticsM2ZServo (double kp, double ki, double dt, double input)
{

 static int first = 0 ;
 static double lastOutput ;
 static double lastInt ;
 double en ;                   /* Error */
 double in ;                   /* Integral term */
 double output ;

 if (first) {
   lastOutput = 0.0;
   lastInt = 0.0;
   first = FALSE ;
 }

/* Evaluate the new output */

 en = input  ;
 in = ki * en * dt + lastInt ;
 
 output = in + en * kp ; 

 lastOutput = output ;
 lastInt = in ;

 return output ;

}


/*+
 *   Function name:
 *   tcsOpticsPlaneXYZ
 *
 *   Purpose:
 *   Convert a probe X,Y position into an x,y in the focal plane.
 *
 *   Description:
 *   The positioning of the PWFS probes must be corrected to allow for
 *   the curved focal plane and the constraint that keeps the WFS
 *   pointing towards the exit pupil. In order to convert a probe position
 *   into an x,y that can be used to geenrate an RA,Dec these corrections
 *   must be removed. This routine removes these corrections and thus
 *   is the inverse of tcsOpticsProbeXYZ. This routine is only relevant for
 *   the PWFS and always sets the z position to zero.
 *   Note that x,y's returned by this routine are not corrected for optical
 *   distortion.
 *
 *   Invocation:
 *   tcsOpticsPlaneXYZ (&x, &y, &z)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   x    (double *)  X position in focal plane (mm)
 *      (!)   y    (double *)  Y position in focal plane (mm)
 *      (!)   z    (double *)  Z position in focal plane (mm)
 *
 *   Function value:
 *   None
 * 
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsOpticsPlaneXYZ (double *x, double *y, double *z)
{
  int itopEnd;           /* Index to current top end */
  double curvExitPupil;  /* Curvature of exit pupil distance (mm -1) */
  double r2 ;            /* Target distance from optic axis (mm) */
  double r1 ;            /* Target distance corrected for exit pupil (mm) */
  double r0 ;            /* Target distance corrected for focus (mm) */
  double bFocus ;        /* Back focal distance (mm) */
  double mag ;           /* Magnification of M2 */
  double dz ;            /* Shift in M2/M1 separation (mm) */
  double m2Sep;          /* M1/M2 separation (mm) */
  double fPlaneShift;    /* Shift in focal plane (mm) */
   
/* Fetch local copies of global data */
    if (! opticsSemId){
        printf("DBG6 Failed to create semaphore opticsSemId\n");
        return;
    }

    epicsMutexLock(opticsSemId);
    bFocus = backFocus ;
    itopEnd = (int)topEnd ;
    mag = m2Mag ;
    dz  = deltaZ ;
    m2Sep = m2Separation ;
    epicsMutexUnlock(opticsSemId);

/* Correct for curvature of exit pupil constraint */

  r2 = sqrt (*x * *x + *y * *y) ;
  curvExitPupil = 1.0 / (m2SepDefs[itopEnd] + bFocus) ;
  r1 = r2 * ( 1.0 + curvExitPupil * curvExitPupil * r2 * r2 / 2.0) ; 

/* Correct for any shift in focal plane */

  fPlaneShift = (mag * mag + 1) * dz ;
  r0 = r1 - fPlaneShift * r1 / (m2Sep + bFocus) ;

/* Scale input x, y */

  *x = *x * r0 / r2 ;
  *y = *y * r0 / r2 ;
  *z = 0.0 ;

}

/*+
 *   Function name:
 *   tcsOpticsProbeXYZ
 *
 *   Purpose:
 *   Generates corrected PWFS probe positions given a nominal X and Y
 *
 *   Description:
 *   This routine will generate corrected X, Y probe positions as well as
 *   the required Z focus position given the uncorrected probe positions as
 *   input. The input X, Y are the paraxial positions corrected for
 *   optical distortion. The X, Y positions 
 *   are corrected both for the curved image surface as well as the fact 
 *   the probes move on an arc pointing at the exit pupil. The focal 
 *   position allows for the curved image surface, the non planar movement
 *   of the probes and any adjustment due to changes in the overall 
 *   telescope focus. 
 *
 *   Invocation:
 *   tcsOpticsProbeXYZ (focusModel, &xcorr, &ycorr, &zcorr)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     focusModel (int)   Index to focus model 0, 1 or 2
 *      (!)     xcorr   (double *) Corrected x position (mm)
 *      (!)     ycorr   (double *) Corrected y position (mm)
 *      (!)     zcorr   (double *) Required z position (mm)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   The routine does not handle the OIWFS. These are expected to operate
 *   in a different optical environment with a flat focal plane and hence
 *   have no z focus capability.  
 *
 *-
 */

void tcsOpticsProbeXYZ (int focusModel, double *xcorr, double *ycorr, 
                        double *zcorr)

{
 double r0;        /* Original probe radial position*/
 double u;         /* Angle of ray at the exit pupil (rads) */
 double m22Fplane; /* Separation of m2 and focal plane */
 double dd;        /* local copy of deltaZ */
 double m2Sep;     /* local copy of M2 to M1 separation */
 double bFocus;    /* Local copy of back focal distance */
 double mag;       /* local copy of M2 magnification */
 double drFocusShift; /* dr due to telescope focus shift */
 double fPlaneShift;  /* shift of focal plane due to telescope focus change */
 double imageCurv; /* local copy of image plane curvature */
 double r1;        /* radial position after correction for focal plane shift */
 double r2;        /* radial position adjusted for exit pupil curvature */
 double dzImageCurv; /* Focus adjustment due to image plane curvature */
 double dzExitPupil; /* Focus adjustment due to exit pupil curvature */
 int itopEnd;        /* Top end index */
 double curvExitPupil; /* Curvature of exit pupil distance */
 double x,y ;        /* Initial values of x & y */
 static int count = 0; /* Counter for debug messages */
 int    dbgLevel;    /* Debug level */

   count++;
   dbgLevel = DBG_NONE ; 

/* First get local copies of the data protected by semaphores */

    if (! opticsSemId){
        printf("DBG7 Failed to create semaphore opticsSemId\n");
        return;
    }
    epicsMutexLock(opticsSemId);

    m2Sep = m2Separation;
    dd    = deltaZ;
    bFocus = backFocus;
    mag    = m2Mag;
    imageCurv = imageCurvature;
    itopEnd = (int)topEnd;

    epicsMutexUnlock(opticsSemId);

/* The following code can be considered temporary until and if the focus
*  model is moved into the A&G. Three focus models are provided. 
*  0 - the old model. This is wrong as it treats the probe as tracing out
*      a spherical surface
*  1 - the new model. Correctly treats the probe as moving on a tilted but
*      flat plane
*  2 - no model. This is for when the model is moved into the A&G
*/

  if (focusModel == 1) {
    
    x = *xcorr ;
    y = *ycorr ;
    r0 = sqrt (x * x + y * y);
    
    dzImageCurv = 0.5 * r0 * r0 * imageCurv ;
    fPlaneShift =  (mag * mag + 1) * dd;
    dzExitPupil = r0 * tan (1.37 * D2R) ;

  } else if (focusModel == 2) {            /* Apply no corrections */

    dzImageCurv = 0.0;
    dzExitPupil = 0.0;
    fPlaneShift =  (mag * mag + 1) * dd;
 
  } else {                                 /* Currently default to old model */

/* Compute the angle that the ray makes at the exit pupil */
    x = *xcorr;
    y = *ycorr;
    r0 = sqrt ( x * x + y * y);
    m22Fplane = m2Sep + bFocus - mag * mag * dd;
    u = r0/m22Fplane;

/* Compute the focal plane shift due to any changes in telescope focus and
 * from this the radial displacement needed to compensate
 */

    fPlaneShift =  (mag * mag + 1) * dd;
    drFocusShift = fPlaneShift * u ;
    r1 = r0 + drFocusShift;

/* Compute the radial displacement and then the focus displacement due to
 * the motion of the probes along the curved path whose tangent points at
 * the exit pupil.
*/

    curvExitPupil = 1.0/(m2SepDefs[itopEnd] + bFocus);
    r2 = r1 * ( 1.0 - curvExitPupil * curvExitPupil * r1 * r1 / 2.0 );
    dzExitPupil = curvExitPupil * r2 * r2 / 2.0;

/* Compute the focus shift due to the image plane curvature */

    dzImageCurv = imageCurv * r2 * r2 /( 1.0 + sqrt(1 - imageCurv * imageCurv *
                  r2 * r2)) ;

/* Finally return the corrected x,y and z position of the probe */

    if (r0 < 1.e-10) {
      *xcorr = x ;
      *ycorr = y ;
    } else {
      *xcorr = x * r2 / r0 ;
      *ycorr = y * r2 / r0 ;
    }
 
    if (count%300 == 1) {
      DBGMSGREAL (DBG_MIN, "Input radius ", r0);
      DBGMSGREAL (DBG_MIN, "Corrected radius ", r2);
      DBGMSGREAL (DBG_MIN, "Dz (Image plane curvature)", dzImageCurv);
      DBGMSGREAL (DBG_MIN, "Dz (exit pupil curvature)", dzExitPupil);
      DBGMSGREAL (DBG_MIN, "Dz (focal plane shift)", fPlaneShift);
    }

  }

  *zcorr = dzImageCurv - dzExitPupil + fPlaneShift ;

}


/*+
 *   Function name:
 *   tcsOpticsRemoveDist
 *
 *   Purpose:
 *   Remove optical distortion effects from a focal plane position
 *
 *   Description:
 *   The focal plane scale of the Gemini telescopes is almost but not 
 *   quite linear. In the F/16 configuration the distortion at 8 arcmin
 *   is about 0.1 arcsec and follows an r**3 dependence. Measured probe
 *   positions should therefore be corrected for this effect before 
 *   converting to an RA/Dec. This routine performs this correction and
 *   is the inverse of tcsOpticsApplyDist.
 *
 *   Invocation:
 *   tcsOpticsRemoveDist(xd, yd, &x, &y)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  xd    (double)  X position in focal plane (rads)
 *      (>)  yd    (double)  Y position in focal plane (rads)
 *      (<)  x     (double *) X position with optical distortion removed (rads)
 *      (<)  y     (double *) Y position with optical distortion removed (rads)
 *
 *   Function value:
 *   None.
 * 
 *   Prior requirements:
 *   tcsOpticsSetTopEnd must have been called to set a value for the optical
 *   distortion coefficient
 *
 *-
 */

void tcsOpticsRemoveDist (double xd, double yd, double *x, double *y)
{
  double scale ;           /* Scale factor to convert xd, yd to x,y */
  double rdsq ;            /* Squared distance from optic axis */

  rdsq = xd * xd + yd * yd;
  scale = 1 - optDistCoeff * rdsq ;

  *x = xd * scale ;
  *y = yd * scale ;

}


/*+
 *   Function name:
 *   tcsOpticsScaleThrow
 *
 *   Purpose:
 *   Scales a given tilt on sky to equivalent tilt of M2
 *
 *   Description:
 *   Given an angular offset on the sky, this routine returns the 
 *   equivalent tilt of M2 required to achieve that offset. The scaling
 *   takes into account that M2 tilts about its centre of gravity.
 *   Such a tilt causes a small lateral displacement of M2 which in 
 *   turn acts to offset the shift induced by the rotation. The net effect
 *   is that M2 has to be tilted slightly more than would be the case if
 *   it could tilt about its vertex. 
 *   Since the overall effect is just a scaling, the input can be supplied 
 *   in any angular units. The return result will be in the same units
 *   as the input.
 *
 *   Invocation:
 *   m2Tilt = tcsOpticsScaleThrow (skyTilt)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    skyTilt  (double)  Angular offset on sky (angular units)
 *
 *   Function value:
 *   (<)  m2Tilt  (double)  Tilt of M2 in same units as input
 * 
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

double tcsOpticsScaleThrow (double skyTilt)
{
  double fl ;               /* Current focal length */
  double cg ;               /* offset of C of G from mirror vertex */
  double tiltScale ;        /* Converts tilts about vertex */
  double transScale ;       /* Converts translations to image shifts */

/* Grab self consistent values for data */

    if (! opticsSemId){
        printf("DBG8 Failed to create semaphore opticsSemId\n");
        return 0;
    }
    epicsMutexLock(opticsSemId);
    fl = flCurrent ;
    cg = m2CofG;
    tiltScale = zMatrix[1][9] ; 
    transScale = zMatrix[1][7];
    epicsMutexUnlock(opticsSemId);

/* return scaled offset */

  return skyTilt * fl / (tiltScale + transScale * cg) ; 
}


/*+
 *   Function name:
 *   tcsOpticsSensor1Temp
 *
 *   Purpose:
 *   Process the raw data from truss temperature sensor 1
 *
 *   Description:
 *   The PCS provides a number sensors attached to the telescope truss that
 *   measure its temperature. These temperatures can be used to correct the
 *   telescope focus for thermal expansion effects. This routine reads
 *   the PCS sensors every 12s and forms a 1 minute running mean to be fed to
 *   the focus model. The routine protects against loss of the sensor signal
 *   and large unphysical steps in temperature such as might happen if a
 *   sensor failed.
 *
 *   Invocation:
 *   tcsOpticsSensor1Temp(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Default temperature if no connection to sensors
 *   b => Sensor temperature
 *   c => Permitted temperature step
 *   d => Severity of input temperature
 *
 *   Epics outputs:
 *   vala => Smoothed output temperature
 *   valb => Health message
 *   valc => Health 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   The routine can't detect a whole string of bad data samples on 
 *   initialisation
 *
 *-
 */

#define NREADINGS 5
#define NFILTER 3

long tcsOpticsSensor1Temp (struct genSubRecord *pgsub)
{
  static double sum = 0.0 ;           /* Sum of data samples */
  static double vals[NREADINGS] ;     /* Last 5 data samples */
  static double rawvals[NFILTER] ;    /* Last NFILTER raw data values */
  double tvals[NFILTER] ;             /* Temporary array of raw values */
  static int ind = 0 ;                /* Index to oldest data sample */
  static int rind = 0 ;               /* Index to oldest raw data sample */
  static int newInd = NREADINGS - 1 ; /* Index to newest data sample */
  static int rnewInd = NFILTER - 1 ;  /* Index to oldest raw data sample */

  int connected;                      /* Flag to show if currently connected */
  double newValue ;                   /* lastest temperature */
  int i ;                             /* loop index */
  double limitStep ;                  /* Maximum step allowed in samples */
  double tempStep ;                   /* current step in temperature */
  double outTemp ;                    /* New smoothed temperature */
  long health ;                       /* Health of sensor reading */
  char mess[MAX_STRING_SIZE] ;        /* Message */
  static int badCount = NREADINGS ;   /* No. of bad samples */

/* Initialise health and message */
  health = GOODHEALTH ;
  strcpy(mess, " ");

/* Use severity level to see if PCS system is up and running. Since GEM8.5
*  this link can't be connected directly to the record in M1. If it was
*  then the genSub would be invalid and this code would never run  */
  if (*(long *)pgsub->d == NO_ALARM) 
    connected = TRUE ;
  else
    connected = FALSE ;

  limitStep = *(double *)pgsub->c ;

  if (waitForFirstConnect1) {

    if (connected) {
      waitForFirstConnect1 = FALSE ;
      newValue = *(double *)pgsub->b ;
      badCount = 0 ;
    } else {
      newValue = *(double *)pgsub->a ;
      health = BADHEALTH ;
      strcpy(mess, "No connection to sensors");
    }

    sum = 0.0;
    for (i = 0; i < NREADINGS; i++) {
      vals[i] = newValue ;
      sum += newValue ;
    }
    for (i = 0; i < NFILTER; i++) {
      rawvals[i] = newValue ;
    }

  } else {

/* Check if we have become disconnected from the PCS records */
    if (connected) {
      newValue = *(double *)pgsub->b ;

/* Now median filter the raw data so that we eliminate any single data
 * point spikes
 */
      rawvals[rind] = newValue ;
      rnewInd = rind ;
      rind++ ;
      rind = rind % NFILTER ;
      for (i = 0 ; i < NFILTER ; i++) {
        tvals[i] = rawvals[i];
      }
      newValue = tcsOpticsMedian(NFILTER, tvals);
    } else {
/* Simply use the last value read */
      newValue = vals[newInd] ;
      badCount++ ;
      if (badCount > NREADINGS)
        health = BADHEALTH ;
      else 
        health = WARNHEALTH ;
      strcpy(mess, "Disconnected from sensors") ;
    } 

  }

/* Now form the new data value */
  if (newValue > 25.0 || newValue < -25.0) {
    badCount++ ;
    strcpy (mess, "Temp exceeds +/-25 C") ;
    if (badCount > NREADINGS)
      health = BADHEALTH ;
    else
      health = WARNHEALTH ;
    newValue = vals[newInd] ;
  } else {
    tempStep = newValue - vals[newInd] ;
    if (tempStep < 0.0) tempStep = -tempStep ;

/* Ignore check on steps in data values if limitStep is zero. This is done
*  for two reasons. First a limitStep of zero is not sensible as it will cause
*  all data to be discarded unless the the input is exactly constant.
*  Secondly, limitStep can be zero until the record is first initialised.
*  It might be that this routine has run several times by then
*/
    if (limitStep > 0.0) {
      if (tempStep > limitStep) {
        badCount++ ;
        sprintf (mess, "Temp jump %f", tempStep);
        if (badCount > NREADINGS) 
          health = BADHEALTH ;
        else 
          health = WARNHEALTH ;
        newValue = vals[newInd] ;
      } else {
        badCount = 0 ;
      }
    } else {
      badCount = 0 ;
    }
  }

  sum = sum - vals[ind] + newValue ;
  outTemp = sum / NREADINGS ;
  vals[ind] = newValue ;
  newInd = ind ;
  ind++ ;
  ind = ind % NREADINGS ;

/* Output data */
  *(double *)pgsub->vala = outTemp ;
  strcpy(pgsub->valb, mess) ;
  *(long *)pgsub->valc = health ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsSensor2Temp
 *
 *   Purpose:
 *   Process the raw data from truss temperature sensor 2
 *
 *   Description:
 *   The PCS provides a number sensors attached to the telescope truss that
 *   measure its temperature. These temperatures can be used to correct the
 *   telescope focus for thermal expansion effects. This routine reads
 *   the PCS sensors every 12s and forms a 1 minute running mean to be fed to
 *   the focus model. The routine protects against loss of the sensor signal
 *   and large unphysical steps in temperature such as might happen if a
 *   sensor failed.
 *
 *   Invocation:
 *   tcsOpticsSensor2Temp(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => Default temperature if no connection to sensors
 *   b => Sensor temperature
 *   c => Permitted temperature step
 *   d => Severity of input temperature
 *
 *   Epics outputs:
 *   vala => Smoothed output temperature
 *   valb => Health message
 *   valc => Health 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   The routine can't detect a whole string of bad data samples on 
 *   initialisation
 *
 *-
 */

long tcsOpticsSensor2Temp (struct genSubRecord *pgsub)
{
  static double sum = 0.0 ;           /* Sum of data samples */
  static double vals[NREADINGS] ;     /* Last 5 data samples */
  static double rawvals[NFILTER];     /* Last NFILTER raw data values */
  double tvals[NFILTER] ;             /* Temporary array of raw values */
  static int ind = 0 ;                /* Index to oldest data sample */
  static int rind = 0 ;               /* Index to oldest raw data sample */
  static int newInd = NREADINGS - 1 ; /* Index to newest data sample */
  static int rnewInd = NFILTER - 1 ;  /* Index to newest raw data sample */

  int connected;                      /* Flag to show if currently connected */
  double newValue ;                   /* lastest temperature */
  int i ;                             /* loop index */
  double limitStep ;                  /* Maximum step allowed in samples */
  double tempStep ;                   /* current step in temperature */
  double outTemp ;                    /* New smoothed temperature */
  long health ;                       /* Health of sensor reading */
  char mess[MAX_STRING_SIZE] ;        /* Message */
  static int badCount = NREADINGS ;   /* No. of bad samples */

/* Initialise health and message */
  health = GOODHEALTH ;
  strcpy(mess, " ");

/* Use severity level to see if PCS system is up and running */
  if (*(long *)pgsub->d == NO_ALARM) 
    connected = TRUE ;
  else
    connected = FALSE ;

  limitStep = *(double *)pgsub->c ;

  if (waitForFirstConnect2) {

    if (connected) {
      waitForFirstConnect2 = FALSE ;
      newValue = *(double *)pgsub->b ;
      badCount = 0 ;
    } else {
      newValue = *(double *)pgsub->a ;
      health = BADHEALTH ;
      strcpy(mess, "No connection to sensors");
    }

    sum = 0.0;
    for (i = 0; i < NREADINGS; i++) {
      vals[i] = newValue ;
      sum += newValue ;
    }
    for (i = 0; i < NFILTER; i++) {
      rawvals[i] = newValue ;
    }

  } else {

/* Check if we have become disconnected from the PCS records */
    if (connected) {
      newValue = *(double *)pgsub->b ;

/* Now median filter the raw data so that we eliminate any single data
 * point spikes
 */
      rawvals[rind] = newValue ;
      rnewInd = rind ;
      rind++ ;
      rind = rind % NFILTER ;
      for (i = 0 ; i < NFILTER ; i++) {
        tvals[i] = rawvals[i];
      }
      newValue = tcsOpticsMedian(NFILTER, tvals);
    } else {
/* Simply use the last value read */
      newValue = vals[newInd] ;
      badCount++ ;
      if (badCount > NREADINGS)
        health = BADHEALTH ;
      else 
        health = WARNHEALTH ;
      strcpy(mess, "Disconnected from sensors") ;
    } 

  }

/* Now form the new data value */
  if (newValue > 25.0 || newValue < -25.0) {
    badCount++ ;
    strcpy (mess, "Temp exceeds +/-25 C") ;
    if (badCount > NREADINGS)
      health = BADHEALTH ;
    else
      health = WARNHEALTH ;
    newValue = vals[newInd] ;
  } else {
    tempStep = newValue - vals[newInd] ;
    if (tempStep < 0.0) tempStep = -tempStep ;

/* Ignore check on steps in data values if limitStep is zero. This is done
*  for two reasons. First a limitStep of zero is not sensible as it will cause
*  all data to be discarded unless the the input is exactly constant.
*  Secondly, limitStep can be zero until the record is first initialised.
*  It might be that this routine has run several times by then
*/
    if (limitStep > 0.0) {
      if (tempStep > limitStep) {
        badCount++ ;
        sprintf (mess, "Temp jump %f", tempStep);
        if (badCount > NREADINGS) 
          health = BADHEALTH ;
        else 
          health = WARNHEALTH ;
        newValue = vals[newInd] ;
      } else {
        badCount = 0 ;
      }
    } else {
      badCount = 0 ;
    }
  }

  sum = sum - vals[ind] + newValue ;
  outTemp = sum / NREADINGS ;
  vals[ind] = newValue ;
  newInd = ind ;
  ind++ ;
  ind = ind % NREADINGS ;

/* Output data */
  *(double *)pgsub->vala = outTemp ;
  strcpy(pgsub->valb, mess) ;
  *(long *)pgsub->valc = health ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsSetAoExpTime
 *
 *   Purpose:
 *   Set aO data exposure time 
 *
 *   Description:
 *   The exposure time used by the A&G to generate aO data is stored
 *   for future use.
 *
 *   Invocation:
 *   tcsOpticsSetAoExpTime (expTime)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  intTime    (double)  Exposure time (secs) 
 *
 *   Function value:
 *   None
 * 
 *-
 */


void tcsOpticsSetAoExpTime (double expTime )

{
   aoExpTime = expTime ;
}

/*+
 *   Function name:
 *   tcsOpticsSetAoFrames
 *
 *   Purpose:
 *   Set number of frames to coadd when generating aO data 
 *
 *   Description:
 *   The number of frames that will be used by PWFS1 to coadd before
 *   generating the aO data is stored for future use.
 *
 *   Invocation:
 *   tcsOpticsSetAoFrames (numFrames)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  numFrames    (int)  Number of frames to coadd 
 *
 *   Function value:
 *   None
 * 
 *-
 */


void tcsOpticsSetAoFrames (int numFrames )

{
   aoNumFrames = numFrames ;
}


/*+
 *   Function name:
 *   tcsOpticsSetComaCoeffs
 *
 *   Purpose:
 *   Sets the coefficients of the coma correction model for M2
 *
 *   Description:
 *   Simply stores the coefficients for later use
 *
 *   Invocation:
 *   tcsOpticsSetComaCoeffs (a, b, c)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    a     (double)  A coefficient of model
 *      (>)    b     (double)  B coefficient of model
 *      (>)    c     (double)  C coefficient of model
 *
 *   Function value:
 *    None
 * 
 *-
 */

void tcsOpticsSetComaCoeffs (double a, double b, double c) 
{

/* Set coefficients in the library. Protect by semaphore to prevent the
*  code that uses these coefficients from getting a mixture of the new
*  and old numbers.
*/

 if (opticsSemId) {
    epicsMutexLock(opticsSemId);
    m2ComaTiltCoeffs[0] = a ;
    m2ComaTiltCoeffs[1] = b ;
    m2ComaTiltCoeffs[2] = c ;
    epicsMutexUnlock(opticsSemId);
 }
 else{
        printf("DBG9 Failed to create semaphore opticsSemId\n");
 }
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsOpticsSetChopLimits
 *
 *   Purpose:
 *   Set chop limits in internal database
 *
 *   Description:
 *   This routine is used to set the current M2 chop limits in the TCS
 *   internal database. The chop throw given is in terms of the physical
 *   throw of M2. 
 *   The chop limits are a function of chop
 *   frequency hence the need for the parameter breakChopfreq.
 *
 *   Invocation:
 *   tcsOpticsSetChopLimits (minChopFreq, breakChopFreq, maxChopFreq,
 *                     minChopFreqThrow, breakChopFreqThrow, maxChopFreqThrow )
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (>)   minChopFreq (double) Minimum chop frequency (Hz)
 *      (>)   breakChopFreq (double) Chop frequency at break (Hz)
 *      (>)   maxChopFreq (double) Maximum chop frequency (Hz)
 *      (>)   minChopFreqThrow (double) Throw at min. frequency (arcsec)
 *      (>)   breakChopFreqThrow (double) Throw at break frequency (arcsec)
 *      (>)   maxChopFreqThrow  (double)  Throw at maximum frequency (arcsec)
 *
 *   Function value:
 *   None.
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
/* *INDENT-ON* */


void tcsOpticsSetChopLimits(double minChopFreq, double breakChopFreq,
                      double maxChopFreq, double minChopFreqThrow,
                      double breakChopFreqThrow, double maxChopFreqThrow)
{

/* simply copy the frequency parameters into their corresponding global
 * counterparts */

 if (opticsSemId) {
    epicsMutexLock(opticsSemId);

    m2MaxChopFreq = maxChopFreq;
    m2BreakChopFreq = breakChopFreq ;
    m2MinChopFreq = minChopFreq;

/* Convert the throws into radians */

    m2MaxChopFreqThrow = maxChopFreqThrow * AS2R;
    m2BreakChopFreqThrow = breakChopFreqThrow * AS2R;
    m2MinChopFreqThrow = minChopFreqThrow * AS2R;

    epicsMutexUnlock(opticsSemId);
 }
 else{
        printf("DBG10 Failed to create semaphore opticsSemId\n");
 }
}


/*+
 *   Function name:
 *   tcsOpticsSetM2Guide
 *
 *   Purpose:
 *   Set flags to control how the TCS handles guide errors through M2
 *
 *   Description:
 *   This routine is used to configure the way in which the TCS handles
 *   guide errors through M2. If the absorbFocus flag is set to TRUE then
 *   the TCS off loads any low frequency terms from the focus corrections
 *   being applied to M2 by modifying the open loop demands that it is
 *   applying. If the comaCorrect flag is set then any coma term measured 
 *   by the WFS is corrected by modifying the X,Y demands to M2.
 *
 *   Invocation:
 *   tcsOpticsSetM2Guide (absorbFocus, comaCorrect)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    absorbFocus (int)  enable/disable absorption of focus errors
 *      (>)    comaCorrect (int)  enable/disable coma corrections
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsSetM2Guide (int absorbFocus, int comaCorrect)

{

  m2AbsorbFocus = absorbFocus ;
  m2ComaCorrect = comaCorrect ;

}


/*+
 *   Function name:
 *   tcsOpticsSetM2Nom
 *
 *   Purpose:
 *   Stores nominal M2 position for use by coma correction model
 *
 *   Description:
 *   Simply store the incoming data for later use. 
 *
 *   Invocation:
 *   tcsOpticsSetM2Nom (xTilt, yTilt, x, y, z) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  xTilt  (double)  X tilt (arcsec)
 *      (>)  yTilt  (double)  Y tilt (arcsec)
 *      (>)  x      (double)  x position (microns)
 *      (>)  y      (double)  y position (microns)
 *      (>)  z      (double)  focus (microns)
 *
 *   Function value:
 *    None
 * 
 *-
 */

void tcsOpticsSetM2Nom (double xTilt, double yTilt, double x, double y,
                        double z) 
{
 if (opticsSemId) {
     epicsMutexLock(opticsSemId);
     m2NominalPosn[0] = xTilt ;
     m2NominalPosn[1] = yTilt ;
     m2NominalPosn[2] = x ;
     m2NominalPosn[3] = y ;
     m2NominalPosn[4] = z ;
     epicsMutexUnlock(opticsSemId);
 }
 else{
        printf("DBG11 Failed to create semaphore opticsSemId\n");
 }
}


/*+
 *   Function name:
 *   tcsOpticsSetM2XYOff
 *
 *   Purpose:
 *   Set X Y offsets of M2 for later use
 *
 *   Description:
 *   This routine is expected to be called from the start directive of
 *   the m2XYOffset CAD. It simply stores the user specified X,Y offsets
 *   for later use.
 *
 *   Invocation:
 *   tcsOpticsSetM2XYOff (xoff, yoff)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    xoff     (double)  X offset (mm)
 *      (>)    yoff     (double)  Y offset (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsSetM2XYOff (double xoff, double yoff) 

{
  m2XUserOffset = xoff ;
  m2YUserOffset = yoff ;
}

/*+
 *   Function name:
 *   tcsOpticsSetTelScales 
 *
 *   Purpose:
 *   Set scaling factors for optics 
 *
 *   Description:
 *   The optics models are based on a nominal optical layout for the 
 *   telescope. If the primary to secondary separation is changed then
 *   the various scalings relating M1 amd M2 tip/tilt/translation to
 *   image movement also change. This routine recalculates the scalings
 *   based on the offset between the nominal layout and the actual layout.
 *
 *   Invocation:
 *   tcsOpticsSetTelScales (dz)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   dz      (double)  Offset in mm between nominal M1/M2 separation
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void tcsOpticsSetTelScales ( double dz)
{

  double fl ;               /* Overall focal length (mm) */
  double separation ;       /* Distance from M2 to focal plane (mm) */

/* Recalculate the focal length and separation between M2 and the focal
*  plane 
*/

  separation = m2Separation + dz + backFocus ;
  fl = flNominal - 4.0 * flNominal * flNominal *
                         m2Curvature * m1Curvature * dz ;

/* Calculate matrix coefficients that convert tilts and translations of
*  M1 and M2 into translations of image. The coefficients are scaled
*  so that if displacements are given in mm and rotations in radians then
*  the output displacements are also in mm. 
*/

  zMatrix[0][1] = - 2 * fl * m1Curvature ;    /* Translation of M1 in x */
  zMatrix[0][5] = 2 * fl ;                    /* Rotation of M1 about y */
  zMatrix[1][2] = zMatrix[0][1] ;             /* Translation of M1 in y */
  zMatrix[1][4] = -zMatrix[0][5];             /* Rotation of M1 about x */
  
  zMatrix[0][6] = -zMatrix[0][1] + 1.0;       /* Translation of M2 in x */
  zMatrix[0][10] = - 2.0 * separation ;       /* Rotation of M2 about y */
  zMatrix[1][7] = zMatrix[0][6] ;             /* Translation of M2 in y */
  zMatrix[1][9] = -zMatrix[0][10];            /* Rotation of M2 about x */

/* Store updated data back into global database */

 if (opticsSemId) {
    epicsMutexLock(opticsSemId);

    deltaZ = dz ;
    flCurrent = fl ;

    epicsMutexUnlock(opticsSemId);
  }
 else{
        printf("DBG12 Failed to create semaphore opticsSemId\n");
 }
}

/*+
 *   Function name:
 *   tcsOpticsSetTiltLimits
 *
 *   Purpose:
 *   Sets the limits used in the tilt-focus relationship for M2
 *
 *   Description:
 *   This routine is called whenever it is required to set or reset the
 *   limits used in the tilt-focus relationship. There is a 
 *   dependency between the maximum tilt allowed and the Z (focus) 
 *   position of M2 for some ranges of Z. In practice M2 will always
 *   be operated in the region where tilt and focus are independent.
 *   The tilt limit inputs to this routine are in M2's frame i.e they
 *   are the physical limits that M2 can reach. Tilts on the sky which
 *   are what the user is interested in are approximately a factor 4
 *   smaller.
 *
 *   Invocation:
 *   tcsOpticsSetTiltLimits (minTilt, maxTilt, minTiltZ, maxTiltZ)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   minTilt  (double)  Tilt minimum (arcsec)
 *      (>)   maxTilt  (double)  Tilt maximum (arcsec)
 *      (>)   minTiltZ (double)  Maximum Z at minimum tilt (mm)
 *      (>)   maxTiltZ (double)  Maximum Z at maximum tilt (mm)
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   epicsMutexLock          (semLib)           Take a semaphore
 *   epicsMutexUnlock        (semLib)           Give a semaphore
 *
 *-
 */

void tcsOpticsSetTiltLimits (double minTilt, double maxTilt, double minTiltZ,
           double maxTiltZ)
{
 if (opticsSemId) {
   epicsMutexLock(opticsSemId);

   m2MinTilt = minTilt * AS2R;
   m2MaxTilt = maxTilt * AS2R;
   m2MinTiltZ = minTiltZ;
   m2MaxTiltZ = maxTiltZ;

   epicsMutexUnlock(opticsSemId);
 }
 else{
        printf("DB13 Failed to create semaphore opticsSemId\n");
 }
}


/*+
 *   Function name:
 *   tcsOpticsSetColl
 *
 *   Purpose:
 *   Set collimation corrections due to movements of optics
 *
 *   Description:
 *   The TCS maintains open loop models that keep M1 and M2 in alignment.
 *   There are two situations when this does not apply 1) the secondary
 *   is chopping and 2) it is required for test purposes to misalign
 *   the system.  If the system is deliberately misaligned this will cause
 *   an image shift. This routine calculates the equivalent collimation
 *   corrections and makes them available to EPICS. Two sets of collimation
 *   corrections are output. The first set is for the kernel pointing loops.
 *   These will be set to zero if the flag to correct for optical collimation
 *   corrections is set to FALSE. The second set is for the TCS sky 
 *   simulator. These are always equal to the current collimation correction.
 *  
 *
 *   Invocation:
 *   tcsOpticsSetColl (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics input parameters:
 *    a => array of positions and rotations of M1
 *
 *   Epics output parameters:
 *
 *   vala => Horizontal collimation, caOptics (arcsec)
 *   valb => Vertical collimation, ceOptics (arcsec)
 *   valc => Horizontal collimation for sky simulator (arcsec)
 *   vald => Vertical collimation for sky simulator (arcsec)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   This record pulls in data that is only available from the m1 simulator
 *   in order to provide information for the sky simulator. It would be 
 *   better if this were done in a separate record.
 *
 *-
 */

long tcsOpticsSetColl (struct genSubRecord *pgsub)
{
  double xoff, yoff ;       /*Image shifts in x & y (mm) */
  double m1Posns[6] ;       /* Current M1 positions in mm and rads */

/* Fetch input data from m1 simulator */
  memcpy (m1Posns, pgsub->a, 6 * sizeof(double)) ;

/* Compute image shifts in focal plane. Note the offset due to tilting M2
*  is NOT included. Such offsets are generally outside the bandwidth that
*  the telescope can correct for
*/
  xoff = zMatrix[0][1] * m1XUserOffset +
         zMatrix[0][5] * m1YRotUserOffset +
         zMatrix[0][6] * m2XUserOffset ; 
  yoff = zMatrix[1][2] * m1YUserOffset +
         zMatrix[1][4] * m1XRotUserOffset +
         zMatrix[1][7] * m2YUserOffset  ;

  caOptics = xoff/flCurrent ;
  ceOptics = yoff/flCurrent ;

/* This step should be done properly, using the ZMatrix terms above. However
*  for the moment as its not clear how long this code will be used we've
*  just added the correction here
*  The correction allows for the tilt of the secondary to correct coma
*  If the telescope tilts the wrong way then change the sign below
*/
  ceOptics += m2ComaTilt*2.0*(m2Separation + backFocus)*AS2R/flCurrent ;

  if (optPointAdj) {
    *(double *)pgsub->vala = caOptics/AS2R ;
    *(double *)pgsub->valb = ceOptics/AS2R ;
  } else {
    *(double *)pgsub->vala = 0.0 ;
    *(double *)pgsub->valb = 0.0 ;
  }

/* Compute the collimation corrections that the sky should see. These depend
*  on the current positions of the optics NOT the demand positions. These
*  data are for simulation purposes only
*/

  xoff = zMatrix[0][1] * m1Posns[0] +
         zMatrix[0][5] * m1Posns[4] +
         zMatrix[0][6] * m2XUserOffset ; 
  yoff = zMatrix[1][2] * m1Posns[1] +
         zMatrix[1][4] * m1Posns[3] +
         zMatrix[1][7] * m2YUserOffset  ;

  caOptics = xoff/flCurrent ;
  ceOptics = yoff/flCurrent ;

  *(double *)pgsub->valc = caOptics/AS2R ;
  *(double *)pgsub->vald = ceOptics/AS2R ;

  return 0 ;
}


/*+
 *   Function name:
 *   tcsOpticsSetFocusFlag
 *
 *   Purpose:
 *   Set flag that controls focus temperature adjustments
 *
 *   Description:
 *   This routine simply sets the flag that controls whether the 
 *   adjustments that are computed to the focus to compensate for the
 *   changing truss temperature are applied or not.
 *
 *   Invocation:
 *   tcsOpticsSetFocusFlag (flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    flag     (int)      0 = Off, 1 = On
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsOpticsSetFocusFlag (int flag) 
{
   m2ZTempEnable = flag ;
}


/*+
 *   Function name:
 *   tcsOpticsSetM1Guide
 *
 *   Purpose:
 *   Stores parameters relating to M1 Guiding
 *
 *   Description:
 *   The parameters relating to M1 guiding i.e. the application of aO 
 *   data to the mirror are simply stored for future use.
 *   The altair "measuring" flag is also set here. This is simply for
 *   convenience to match the interfacce used by the other WFS. In practice
 *   because of changes elsewhere these "measuring" flags are redundant.
 *   At some point they should all be done away with and the AverageAo
 *   routine rewritten.
 *
 *   Invocation:
 *   tcsOpticsSetM1Guide (weightScheme, pwfs1Weight, pwfs2Weight, numFrames)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   weightScheme  (M1WEIGHT)  NOWEIGHTS or ERRORS
 *      (>)   wfsSource     (int)       Source of WFS data 
 *      (>)   numFrames     (long)      Number of frames to average 
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsSetM1Guide (M1WEIGHT weightScheme, int wfsSource,
                          long numFrames )
{
  int telindex ;

  m1AoWeight = weightScheme ;
  currM1AoSource = wfsSource ; 
  m1AoFrames    = numFrames ; 

  if (currM1AoSource == ALTAIR_AO_SOURCE ){
    altairMeasuring = TRUE ;
  }
  if (currM1AoSource == GEMS_AO_SOURCE ){
    gemsMeasuring = TRUE ;
  }

  telindex = tcsProbeGetTelescope();
  if (telindex == 0 && currM1AoSource == GAOS_AO_SOURCE) {
    currM1AoSource = ALTAIR_AO_SOURCE;
    altairMeasuring = TRUE ;
  }

  if (telindex == 1 && currM1AoSource == GAOS_AO_SOURCE) {
    currM1AoSource = GEMS_AO_SOURCE;
    gemsMeasuring = TRUE ;
  }

}

/*+
 *   Function name:
 *   tcsOpticsSetM2DzIns
 *
 *   Purpose:
 *   Set the instrument's focus offset for use by the optics model
 *
 *   Description:
 *   This routine simply copies the instrument's focus offset request into the 
 *   optic's model. Note the offset supplied is the shift in the focal
 *   plane whereas the number stored is the corresponding shift in M2.
 *
 *   Invocation:
 *   tcsOpticsSetM2DzIns (dzIns)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    dzIns   (double)   Instrument focus offset (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsSetM2DzIns (double dzIns)

{

  m2ZInsOffset = dzIns/(m2Mag * m2Mag + 1.0);

}

/*+
 *   Function name:
 *   tcsOpticsSetM2DzUser
 *
 *   Purpose:
 *   Set the user's focus offset for use by the optics model
 *
 *   Description:
 *   This routine simply copies the user's focus offset request into the 
 *   optic's model.
 *
 *   Invocation:
 *   tcsOpticsSetM2DzUser (dzUser)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    dzUser   (double)   User focus offset (mm)
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsSetM2DzUser (double dzUser)

{

  m2ZUserOffset = dzUser;

}


/*+
 *   Function name:
 *   tcsOpticsSetTopEnd
 *
 *   Purpose:
 *   Set current top end for the optics model
 *
 *   Description:
 *   The routine checks that the string passed to it corresponds to one
 *   of the top ends that are supported. If it is the topend index is set 
 *   appropriately. If not then the system defaults to F16 and a warning
 *   message is issued. Various internal data values are then initialised
 *   with the appropriate topend values.
 *
 *   Invocation:
 *   tcsOpticsSetTopEnd(topEndString)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    topEndString   (char *)   String specifying top end 
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsDcUc        (tcsDecode)        Convert string to upper case
 *   epicsMutexLock        (semLib)           Take a semaphore
 *   epicsMutexUnlock        (semLib)           Give a semaphore
 *-
 */

void tcsOpticsSetTopEnd(char *topEndString)

{
  char ucTopEnd[MAX_STRING_SIZE];     /* Upper case version of topend */
  int dbgLevel;                       /* Local debug level */
  int itopEnd;                        /* top end index */

  dbgLevel = DBG_NONE;

  tcsDcUc(topEndString, MAX_STRING_SIZE, ucTopEnd);

  if (!strcmp(ucTopEnd, "F16"))
    topEnd = F16;
  else if (!strcmp(ucTopEnd, "F6"))
    topEnd = F6;
  else if (!strcmp(ucTopEnd, "PRIME"))
    topEnd = PRIME;
  else
  {
   topEnd = F16;
   DBGMSG(DBG_NONE, "tcsOpticsSetTopEnd: unknown topend, defaulting to F16");
  }

  itopEnd = (int)topEnd;

 if (opticsSemId) {
   epicsMutexLock(opticsSemId);
   flNominal = flDefs[itopEnd];
   flCurrent = flNominal;
   deltaZ = 0.0;
   m2Separation = m2SepDefs[itopEnd];
   optDistCoeff = optDistDefs[itopEnd];
   m2Curvature  = m2CurvDefs[itopEnd];
   imageCurvature = imageCurvDefs[itopEnd];
   m2Mag = flNominal/flDefs[(int)PRIME];
   m2CofG = m2CofGDefs[itopEnd];
   epicsMutexUnlock(opticsSemId);
 }
 else{
        printf("DBG14 Failed to create semaphore opticsSemId\n");
 }
 printf("DBG tcsOpticsSetTopEnd flCurrent=%lf \n", flCurrent);  
}

/*+
 *   Function name:
 *   tcsOpticsTrussReset
 *
 *   Purpose:
 *   Reset the truss temperatures calculation 
 *
 *   Description:
 *   This routine is used to reset the truss temperature calculation 
 *   following a problem with the truss sensors. The calculations
 *   are restarted as if the TCS had just been booted. This is needed
 *   as sometimes the hardware returns data which looks perfectly
 *   valid e.g. zeroes but then switches to correct numbers say 6.5
 *   for example. The temperature calculation throws away the valid
 *   data as it thinks there has been a large and unphysical change
 *   in temperature.
 *   The reset is achieved by simply setting the wait for the first
 *   connection flags.
 *
 *   Invocation:
 *   tcsOpticsTrussReset(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *-
 */

long tcsOpticsTrussReset (struct genSubRecord *pgsub)
{

  waitForFirstConnect1 = TRUE ; 
  waitForFirstConnect2 = TRUE ; 
  return 0 ;

}

/*+
 *   Function name:
 *   tcsOpticsTrussTemp
 *
 *   Purpose:
 *   Average the truss temperature sensor readings
 *
 *   Description:
 *   There are currently two sensors on the telescope truss which monitor
 *   its temperature. This routine takes these two temperatures and
 *   averages them taking into account their validity based on their
 *   health values.
 *
 *   Invocation:
 *   tcsOpticsTrussTemp(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 *
 *   Epics inputs:
 *   a   =>  Temperature of sensor 1
 *   b   =>  Health message of sensor 1
 *   c   =>  Health status of sensor 1
 *   d   =>  Temperature of sensor 2
 *   e   =>  Health message of sensor 2
 *   f   =>  Health status of sensor 2
 *   g   =>  Permitted difference between sensor 1 and 2 (deg C)
 *
 *   Epics outputs:
 *   vala => Average truss temperature
 *   valb => Health message
 *   valc => Health status GOOD, WARNING or BAD
 * 
 *
 *-
 */

long tcsOpticsTrussTemp (struct genSubRecord *pgsub)
{
  char *hstrings[] = {"GOOD", "WARNING", "BAD"} ;
  double t1, t2  ;               /* Temperatures 1 and 2 (deg C) */
  long   health1, health2 ;      /* Health values of sensor 1 and 2 */
  char mess1[MAX_STRING_SIZE] ;  /* Health message of sensor 1 */
  char mess2[MAX_STRING_SIZE] ;  /* Health message of sensor 2 */

  double tout ;                  /* New temperature */
  long health ;                  /* Health of truss temperature */
  char mess[MAX_STRING_SIZE] ;   /* Health message */

  double diff ;                  /* Allowed temperature difference */
  double dt ;                    /* Difference in sensor temperature */

/* Read and initialise data */
  health = GOODHEALTH ;
  strcpy(mess, " ") ;
  t1 = *(double *)pgsub->a ;
  strcpy(mess1, pgsub->b) ;
  health1 = *(long *)pgsub->c ;
  t2 = *(double *)pgsub->d ;
  strcpy(mess2, pgsub->e) ;
  health2 = *(long *)pgsub->f ;
  diff = *(double *)pgsub->g ;

  dt = t1 - t2 ;
  if (dt < 0.0) dt = -dt ;

/* If diff is set to zero then take this as meaning don't bother what the 
*  difference between the sensors is. A diff of zero isn't sensible so it
*  is either an error or the record hasn't yet been initialised.
*/
  if (diff > 0.0) {
    if (dt > diff) {
      if (health1 < health2) {
        tout = t1 ;
      } else if (health1 > health2) {
        tout = t2 ;
      } else {
/* Can't chose between them so just average anyway */
        tout = (t1 + t2)/2.0 ;
      }

    } else {
      tout = (t1 + t2)/2.0 ;
    }
  } else {
    tout = (t1 + t2) /2.0 ;
  }
  
/* Now compute overall health */
  if (health1 < health2) {
    health = health2 ;
    strcpy(mess, mess2) ;
  } else if (health1 > health2) {
    health = health1 ;
    strcpy(mess, mess1) ;
  } else {
    health = health1 ;
    strcpy(mess, mess1) ;
  }
  
/* Write output */
  *(double *)pgsub->vala = tout ;
  strcpy(pgsub->valb, mess) ;
  strcpy(pgsub->valc, hstrings[health]) ;
  
  return 0 ;

}


/*+
 *   Function name:
 *   tcsOpticsSetM2XYRot
 *
 *   Purpose:
 *   Set up translations that result from a rotation about C of G.
 *
 *   Description:
 *   M2 can only be tilted about its C of G. For the F/16 top end this
 *   C of G is about 51 mm behind the mirror vertex. A given tilt
 *   of M2 is therefore accompanied by a translation of the vertex. This
 *   translation needs to be accounted for when computing the Zernike
 *   terms a WFS is expecting to see.
 *
 *   Invocation:
 *   tcsOpticsSetM2XYRot (ichop, xrot, yrot)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    ichop    (int)      Chop state
 *      (>)    xrot     (double)   Requested chop endpoint in x (rads)
 *      (>)    yrot     (double)   Requested chop endpoint in y (rads)
 *
 *   Function value:
 *   None
 * 
 *   Deficiencies:
 *   Fails silently if ichop is not 0, 1 or 2
 *
 *-
 */

void tcsOpticsSetM2XYRot (int ichop, double xrot, double yrot)
{

  if (ichop < 3 && ichop > -1) {
    m2XTiltUser[ichop] = yrot ; /* Rotate about y to get displacement in x */
    m2YTiltUser[ichop] = -xrot ;  /* Rotate about x to get displacement in y */
    m2XRotOffset[ichop] = -m2CofG * m2YTiltUser[ichop] ;
    m2YRotOffset[ichop] = m2CofG * m2XTiltUser[ichop] ;
  }
}



/*+
 *   Function name:
 *   tcsOpticsSetM2ZError
 *
 *   Purpose:
 *   Set error term in M2 Z position demand
 *
 *   Description:
 *   Stores a value for the error term used in the model that generates
 *   the demand M2 z position. This routine is most often used to 
 *   zero the error term.
 *
 *   Invocation:
 *   tcsOpticsSetM2ZError (zError)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    zError   (double)   Error term (mm)
 *
 *   Function value:
 *   None
 *-
 */

void tcsOpticsSetM2ZError (double zError)
{

  m2ZErrorCorr = zError ;

}


/*+
 *   Function name:
 *   tcsOpticsSetPointFlag
 *
 *   Purpose:
 *   Set flag that controls optics pointing adjustments
 *
 *   Description:
 *   For test purposes a user may want to offset the telescope optics
 *   away from their nominal positions. If this is done there will be
 *   associated image shifts. The user also has the option of adjusting
 *   the telscope pointing at the same time to compensate for these
 *   image shifts. This routine sets the flag that controls whether or
 *   not such pointing adjustments should be made.
 *
 *   Invocation:
 *   tcsOpticsSetPointFlag (flag)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    flag     (int)      0 = Off, 1 = On
 *
 *   Function value:
 *   None.
 * 
 *-
 */

void tcsOpticsSetPointFlag (int flag) 
{
   optPointAdj = flag ;

}

/*+
 *   Function name:
 *   tcsOpticsSetZCoeffs
 *
 *   Purpose:
 *   Set up the matrix coefficients used to calculate Zernike terms
 *
 *   Description:
 *   When this routine is triggered, it will read in the number of Zernike
 *   terms for which coefficients are being provided. It will then read
 *   in each set of coefficients in turn, checking that the correct number
 *   of elements has been provided. The data will then be stored in 
 *   the appropriate location in an internal matrix. Once all terms are
 *   read, the coefficients to calculate the shifts in the focal plane
 *   i.e. Z1 and Z2 will be computed to complete the matrix. 
 *
 *   Invocation:
 *   tcsOpticsSetZCoeffs (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => number of Zernike terms for which coeffs are provided
 *   b => coefficients for Z3 
 *   c => coefficients for Z4 etc.
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Currently only handles coefficients for Zernike terms up to Z8.
 *
 *-
 */

long tcsOpticsSetZCoeffs (struct genSubRecord *pgsub)
{

  int nZernikes ;              /* Number of coefficients */
  int nelems ;                 /* Number of elements */
  int i ;                      /* index */
  int count ;                  /* Count of number of Zernikes read */
  static int dbgLevel = DBG_NONE; /* Debug level */
  double *zEntry ;             /* Pointer to Zernike coeff. */
  double *zval ;               /* Pointer to coefficient value */

/* Read in number of Zernikes for which coeffs. are provided */

  nZernikes = *(long *)pgsub->a;

  if ((nZernikes < 1 ) || (nZernikes > MAXZERNIKES - 2)) {
    DBGMSG (DBG_NONE, "Invalid no. of Zernikes specified") ;
    return -1 ;
  }

/* At present we only expect to specify data up to Z8. Issue a warning
*  if more are given as currently they will be ignored.
*/
 
  if (nZernikes > 6) {
    DBGMSG (DBG_NONE, "Ignoring coefficients for Z9 and higher") ;
  }
  
/* For each input, check number of elements is correct and then read and
 * store data 
*/

  zEntry = &zMatrix[2][0] ;
  count = 0;

  nelems = (int)pgsub->nob ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z3");
    return -1 ;
  } else {
    zval = (double *)pgsub->b ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  nelems = (int)pgsub->noc ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z4");
    return -1 ;
  } else {
    zval = (double *)pgsub->c ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  nelems = (int)pgsub->nod ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z5");
    return -1 ;
  } else {
    zval = (double *)pgsub->d ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  nelems = (int)pgsub->noe ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z6");
    return -1 ;
  } else {
    zval = (double *)pgsub->e ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  nelems = (int)pgsub->nof ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z7");
    return -1 ;
  } else {
    zval = (double *)pgsub->f ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  nelems = (int)pgsub->nog ;
  if (nelems != MAXENTRIES) {
    DBGMSG (DBG_NONE, "Insufficient entries for Z8");
    return -1 ;
  } else {
    zval = (double *)pgsub->g ; 
    for (i = 0; i < nelems ; i++ )
       *zEntry++ = *zval++ ;
    count++ ;
    if (count == nZernikes) return 0 ;
  }

  return 0 ;
 
}

/*+
 *   Function name:
 *   tcsOpticsXpYpToXY
 *
 *   Purpose:
 *   Transform x,y components from one frame to another
 *
 *   Description:
 *   This routine is used to transform the x,y components of a vector from
 *   one frame to another that is rotated relative to it by an angle pa.
 *   The input primed frame has y' upwards and x' to the right. The angle pa
 *   is then measured from y' being positive for a clockwise rotation.
 *
 *   Invocation:
 *   tcsOpticsXpYpToXY(xp, yp, pa, &x, &y)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     xp      (double)   X component (arbitrary units)
 *      (>)     yp      (double)   Y component (arbitrary units)
 *      (>)     pa      (double)   Rotation angle (rads)
 *      (<)     x       (double *) X component in rotated frame
 *      (<)     y       (double *) Y component in rotated frame
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsXpYpToXY (double xp, double yp, double pa, double *x,
                        double *y)
{
  double cospa, sinpa ;      /* Cos and sin of rotation angle */

  cospa = cos(pa) ;
  sinpa = sin(pa) ;

  *x = xp * cospa - yp * sinpa ;
  *y = xp * sinpa + yp * cospa ;

}


/*+
 *   Function name:
 *   tcsOpticsXYToXpYp
 *
 *   Purpose:
 *   Transform x,y components from one frame to another
 *
 *   Description:
 *   This routine is used to transform the x,y components of a vector from
 *   one frame to another that is rotated relative to it by an angle pa.
 *   The output primed frame has y' upwards and x' to the right. The angle pa
 *   is then measured from y' being positive for a clockwise rotation.
 *   This routine is the inverse of tcsOpticsXpYpToXY
 *
 *   Invocation:
 *   tcsOpticsXYToXpYp(x, y, pa, &xp, &yp)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)     x       (double)   X component (arbitrary units)
 *      (>)     y       (double)   Y component (arbitrary units)
 *      (>)     pa      (double)   Rotation angle (rads)
 *      (<)     xp      (double *) X component in rotated frame
 *      (<)     yp      (double *) Y component in rotated frame
 *
 *   Function value:
 *   None
 * 
 *-
 */

void tcsOpticsXYToXpYp (double x, double y, double pa, double *xp,
                        double *yp)
{
  double cospa, sinpa ;      /* Cos and sin of rotation angle */

  cospa = cos(pa) ;
  sinpa = sin(pa) ;

  *xp = x * cospa + y * sinpa ;
  *yp = -x * sinpa + y * cospa ;

}

epicsRegisterFunction(tcsOpticsTrussReset);
epicsRegisterFunction(tcsOpticsFigureTotals);
epicsRegisterFunction(tcsOpticsAverageAo);
epicsRegisterFunction(tcsOpticsTrussTemp);
epicsRegisterFunction(tcsOpticsM2Z);
epicsRegisterFunction(tcsOpticsCalcM1ValidFlags);
epicsRegisterFunction(tcsOpticsSensor1Temp);
epicsRegisterFunction(tcsOpticsSensor2Temp);
epicsRegisterFunction(tcsOpticsCalcM1Moving);
epicsRegisterFunction(tcsOpticsM2ZValues);
epicsRegisterFunction(tcsOpticsM1FileStatus);
epicsRegisterFunction(tcsOpticsSetZCoeffs);
epicsRegisterFunction(tcsOpticsM2Move);
epicsRegisterFunction(tcsOpticsM2XY);
epicsRegisterFunction(tcsOpticsAoAv);
epicsRegisterFunction(tcsOpticsM1Offsets);
epicsRegisterFunction(tcsOpticsSetColl);
epicsRegisterFunction(tcsOpticsDisplayAo);
epicsRegisterFunction(tcsOpticsM1ShowCoeffs);
epicsRegisterFunction(tcsOpticsHrwfsData);
epicsRegisterFunction(tcsOpticsM1Restore);
epicsRegisterFunction(tcsOpticsM2XYErr);
epicsRegisterFunction(tcsOpticsM1StoreCoeffs);
epicsRegisterFunction(tcsOpticsCheckAoModel);
epicsRegisterFunction(tcsOpticsM1CalcFig);
epicsRegisterFunction(tcsOpticsM2Tilt);
epicsRegisterFunction(tcsOpticsM1Figure);

static const iocshFuncDef tcsOpticsInitFuncDef =
         {"tcsOpticsInit"};
	 
static void tcsOpticsInitCallFunc(const iocshArgBuf *args)
{
   tcsOpticsInit();
}

static void registerTcsOpticsInitCommands(void)
{
      iocshRegister(&tcsOpticsInitFuncDef, tcsOpticsInitCallFunc);
}
epicsExportRegistrar(registerTcsOpticsInitCommands);
