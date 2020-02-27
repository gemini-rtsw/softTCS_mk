/*
*   FILENAME
*   tcsGlobal.h
*
*   DESCRIPTION
*   This include file contains the global parameters used by the 
*   Gemini Telescope Control Systems
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsGlobal.h,v $
 * Revision 1.15  2010/06/03 15:34:01  cjm
 * Add arrays to store distortion coefficients
 *
 * Revision 1.14  2007/12/18 10:17:53  cjm
 * Add new variables and expand arrays to handle new guiders
 *
 * Revision 1.13  2007/01/09 11:46:04  cjm
 * Dimension planet code variables O_jform etc.
 *
 * Revision 1.12  2005/10/20 15:13:22  cjm
 * Make P_code and P_override rates into arrays
 *
 * Revision 1.11  2003/04/10 10:21:09  dlt
 * Store chop mode in kernel
 *
 * Revision 1.10  2002/11/08 12:03:11  cjm
 * Add arrays for altair distortion coefficients
 *
 * Revision 1.9  2002/10/22 20:37:45  dlt
 * Implement filter 1 for pointing origins and fix filter flag resetting
 *
 * Revision 1.8  2001/10/24 22:53:39  dlt
 * Display reason for inPosition false
 *
 * Revision 1.7  2000/07/20 03:00:52  dlt
 * Upgrade to latest tptlib
 *
 * Revision 1.6  2000/07/19 00:09:39  dlt
 * Implement new pointing model implementation
 *
 * Revision 1.5  1999/05/29 08:12:26  dlt
 * Move tf to genertic parameters
 *
 * Revision 1.4  1999/01/21 01:00:05  dlt
 * remove unused simulate flags
 *
 * Revision 1.3  1998/12/18 19:49:06  dlt
 * Complete implementation of otm calculation after slew
 *
 * Revision 1.2  1998/11/14 00:15:58  dlt
 * Add IA and IE to pointing model
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.21  1998/02/16 16:57:59  tcs
 * implement internal in position flag
 *
 * Revision 1.20  1997/11/19 10:11:17  tcs
 * Change filter catchup to short circuit
 *
 * Revision 1.19  1997/11/14 15:59:39  tcs
 * Revised astRot arguments
 *
 * Revision 1.18  1997/11/13 13:23:36  tcs
 * Revised guide star scheme
 *
 * Revision 1.17  1997/11/05 11:43:01  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.16  1997/10/31 14:46:27  tcs
 * Add instrument angle concept
 *
 * Revision 1.15  1997/10/15 15:29:31  tcs
 * Add user offset to pa used for pa calculation
 *
 * Revision 1.14  1997/10/09 09:53:08  tcs
 * Add current focal length
 *
 * Revision 1.13  1997/10/03 15:06:30  tcs
 * Add scratch debug items to global data
 *
 * Revision 1.12  1997/09/23 11:37:03  tcs
 * Make all variables static
 *
 * Revision 1.11  1997/09/12 12:58:23  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.10  1997/08/13 10:24:37  tcs
 * Add guiding adjustments to ca/ce
 *
 * Revision 1.9  1997/06/26 10:10:12  tcs
 * Update orbits at 0.1Hz
 *
 * Revision 1.8  1997/06/25 12:57:21  tcs
 * Implement planet, moon and orbit data entry
 *
 * Revision 1.7  1997/06/11 15:14:19  tcs
 * Implement wavelength CADs
 *
 * Revision 1.6  1997/05/16 12:21:01  tcs
 * Change cosys to frame
 *
 * Revision 1.5  1997/05/07 10:26:43  tcs
 * Implement target to current filter
 *
 * Revision 1.4  1997/04/28 14:06:08  tcs
 * Add default values for MCS and RCS
 *
 * Revision 1.3  1997/04/16 11:55:42  tcs
 * Move tube flexure to telescope specific pointing model routines
 *
 * Revision 1.2  1997/03/24 15:15:45  cjm
 * Move M2 limit parameters to tcsOptics.h
 *
 * Revision 1.1  1997/02/10 17:10:39  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.36  1997/02/05 11:04:06  tcs
 * Change filter catchup comments
 *
 * Revision 1.35  1997/01/28 10:36:22  tcs
 * corrections to differential tracking
 *
 * Revision 1.34  1997/01/23 10:46:43  tcs
 * kernel support for relative chopping
 *
 * Revision 1.33  1997/01/17 18:16:16  cjm
 * Remove variable Fl (focal length)
 *
 * Revision 1.32  1997/01/10 15:20:50  tcs
 * add tropospheric lapse rate
 *
 * Revision 1.31  1997/01/03 11:20:29  tcs
 * add pre-collimation mount az/el
 *
 * Revision 1.30  1996/12/20 14:43:04  tcs
 * remove guide probe flexture terms
 *
 * Revision 1.29  1996/12/18 11:17:32  tcs
 * cleanup plus offset routines
 *
 * Revision 1.28  1996/12/06 14:09:59  tcs
 * Move all rotator calculations to fast loop
 *
 * Revision 1.27  1996/12/05 13:13:37  tcs
 * implement filter catchup
 *
 * Revision 1.26  1996/12/03 16:55:25  tcs
 * New filter parameter names
 *
 * Revision 1.25  1996/12/03 11:32:12  tcs
 * interpolate rotator zero point
 *
 * Revision 1.24  1996/12/02 11:11:57  tcs
 * Add rotator position and frame etc.
 *
 * Revision 1.23  1996/11/26 15:25:00  tcs
 * Add filter weights
 *
 * Revision 1.22  1996/11/13 14:38:55  tcs
 * Add rotator CAD
 *
 * Revision 1.21  1996/11/07 16:17:27  tcs
 * add daz to aoprms array
 *
 * Revision 1.20  1996/11/06 14:30:27  tcs
 * Add axis tilts and remove Active flags
 *
 * Revision 1.19  1996/11/04 11:40:17  tcs
 * Add observed to apparent parameters
 *
 * Revision 1.18  1996/10/21 13:46:35  cjm
 * Global parameters for chop limits
 *
 * Revision 1.17  1996/09/25 07:38:02  tcs
 * Change chop states to ABC (comments only)
 *
 * Revision 1.16  1996/09/11 13:40:52  tcs
 * Change azimuth wrap limits to -180/+360
 *
 * Revision 1.15  1996/09/06 11:40:59  tcs
 * Improved wrap handling + Al/El coordinate handedness fixed
 *
 * Revision 1.14  1996/07/24 15:29:18  tcs
 * clear up cosys confusion
 *
 * Revision 1.13  1996/07/23 15:13:45  tcs
 * Add header comments
 *
 */
/* *INDENT-ON* */

#ifndef TCSGLOBAL_H
#define TCSGLOBAL_H

#include <epicsMutex.h>
#include "tptlib.h"

/* Set by the secondary initialisation process */
static double Del;       /* probe-vector spacing (rad) for OTM generation */
static double Hm;        /* site elevation, metres above sea-level */
static double Sst,Cst;   /* functions of LAST (updated by Fast Loop) */

/* Operational pointing model */
#define MAXTRM  30            /* maximum number of terms in model */
#define NTROOM 100            /* maximum number of terms in repertoire */
static int Model[MAXTRM]; /* term numbers for current model (0=end) */
static double Coeffv[MAXTRM]; /* coefficient values */
static int Nterml;       /* # local terms */
static int Ntermx;       /* # terms implemented explicitly (loc+std) */
static int Nterms;       /* # terms avail. currently (loc+std+gen) */
static char Coeffn[NTROOM][9]; /* coeff. names (local, standard, generic) */
static char Coform[NTROOM][9]; /* format of generic term */
static double Ae2nm[3][3]; /* rotation matrix. [Az.El] to nominal mount */

/* Basic pointing model coefficients (radians mostly) */
static double An;        /* azimuth axis tilt N */
static double Aw;        /* azimuth axis tilt W */
static double Ia;        /* index error in azimuth */
static double Ie;        /* index error in elevation */
static double Vd;        /* vertical deflection */
static double Pnpae;     /* Az/El nonperpendicularity NPAE */
static double Ca;        /* azimuth collimation correction CA */
static double Ae2mt[3][3]; /* rotation matrix, [Az,El] to mount */
static double Aux[3];    /* auxiliary readings */

/* Adjustments to base model */ 
static double Ia_delta;  /* index error in azimuth */
static double Ca_delta;  /* azimuth collimation correction */
static double Ce_delta;  /* elevationcollimation correction */

/* Set by the slow loop process */
static double Tick0;     /* raw clock time at reference epoch */
static double St0;       /* LAST at reference epoch (radians) */
static double Tt0;       /* TT at reference epoch (MJD) */
static double Tdbj;      /* TDB Julian Epoch */
static double Amprms[21];   /* target-independent MAP parameters */
static double Aoprms[15];   /* target-independent AOP parameters */
static double Temp;      /* ambient temperature (deg K) */
static double Press;     /* pressure (mB) */
static double Humid;     /* relative humidity (0-1) */
static double Tlr;       /* tropospheric lapse rate */
static double Wavelr;    /* reference wavelength (micrometres) */
static double Tlong,     /* telescope true       */
              Tlat,      /*  longitude, latitude */
              Slat,Clat; /*  and functions       */
static double Daz;       /* azimuth correction for polar motion */
static double Ukm,Vkm;   /* distance from spin axis and equator (km)   */
static double Refa,Refb; /* tan and tan^3 refraction constants */
static double Diurab;    /* diurnal aberration (radians) */

static double Trackid;          /* tracking identifier */

/* Set by the fast loop */
static double Tick;      /* TAI at next tick (clock) */
static double Tt;        /* TT at next tick */
static double St;        /* LAST at next tick */
static double Az,El;     /* demand Az/El (N=0, E=90, radians) */
static double Paim;      /* P.A. of y-axis for rotator angle zero */
static double Rma;       /* Predicted mechanical angle of rotator at next tick */
static double Pa;        /* Ideal rotator position angle */
static double Rm;        /* cos of elevation */
static double X0;        /* pre-collimation mount az/el */
static double Y0;
static double Z0;
static double Fl;        /* Focal length (at last tick) */
static double Ca_net;    /* Net horizontal collimation CA */
static double Ce_net;    /* Net vertical collimation CE */
static double Ia_net;    /* Net azimuth index error */


/* Mount and Cass rotator positions to be used in the absence of valid
   data from the fast loop */
static double AzDef;
static double ElDef;
static double RmaDef;

/* Flags to show whether the fast loop values should be sent to the 
   subsystems */
static int McsActive;
static int RcsActive;

epicsMutexId TcsSemId;  /* Mutex semaphore to control access to data */

/* Flag to control the azimuth axis wrap state. 
     -1 => use -180/+180
      0 => use +180/+360 closest to current demand
     +1 => use    0/+360
     +2 => use closest to current then clip to wrap limit
*/
static int AzWrap;

/* Flag to control the rotator axis wrap state. 
     -1 => use -270/+90
      0 => use -270/+270 closest to current demand
     +1 => use  -90/+270
     +2 => use closest to current then clip to wrap limit
*/
static int RotWrap;

static double Ipa;  /* Desired position angle of the instrument principle
                       direction */
static double Iaa;  /* Instrument alignment angle */
static double Sia;  /* Sine of instrument alignment */
static double Cia;  /* Cosine of instrument alignment */
static int Nod;     /* Current NOD state */

/* In position flag. Set to FALSE if and mechanism has reached a limit or
   zenith avoidance is in effect */
static int InPosition;

/* Numeric code for the reason that InPosition is false. */
static int InPosReason;

/*
**  +----------------------------------+
**  | Virtual-Telescope Configurations |
**  +----------------------------------+
**
**  Array indices obey these rules:
**
**  . Coordinates (spherical coordinates or x/y/z values) are
**    adjacent in memory, i.e. the index is the rightmost one.
**
**  . 3x3 matrices occupy continuous addresses in memory.
**
**  . The next most significant index is where there is a set of
**    offsets from base or a nod state (A, B and C).
**
**  . The most significant index of all (i.e. the leftmost if used)
**    is the chop state.  0, 1 and 2 correspond to chop states A, B
**    and C.
*/

/*
**  Target Contexts
**  ---------------
**
**  There are 11 target contexts, each consisting of:
**
**  . user coordinate system and (for mean RA/Dec) the equinox
**  . effective wavelength (except for the rotator which shares
**    the mount)
**
**  The target contexts apply to:
**
**  . mount, rotator, source chop states A, B and C, PWFS #1, PWFS #2, OIWFS
**    G1, G2, G3 and G4
*/

/* Mount */
   static FRAMETYPE M_frame;
   static double M_eqx, M_wavel;

/* Rotator */
   static FRAMETYPE R_frame;
   static double R_eqx;

/* Source */
   static FRAMETYPE S_frame[3];
   static double S_eqx[3], S_wavel[3];

/* PWFS #1 */
   static FRAMETYPE G1_frame;
   static double G1_eqx, G1_wavel;

/* PWFS #2 */
   static FRAMETYPE G2_frame;
   static double G2_eqx, G2_wavel;

/* OIWFS */
   static FRAMETYPE G3_frame;
   static double G3_eqx, G3_wavel;

/* Generic guider #1 */
   static FRAMETYPE GG1_frame;
   static double GG1_eqx, GG1_wavel;

/* Generic guider #2 */
   static FRAMETYPE GG2_frame;
   static double GG2_eqx, GG2_wavel;

/* Generic guider #3 */
   static FRAMETYPE GG3_frame;
   static double GG3_eqx, GG3_wavel;

/* Generic guider #4 */
   static FRAMETYPE GG4_frame;
   static double GG4_eqx, GG4_wavel;

/*
**  Targets
**  -------
**
**  There are 11 targets.  Each consists of:
**
**  . position at reference epoch (spherical coordinates, radians)
**  . differential rates (radians/day)
**  . reference epoch (TT MJD)
**  . offset(s) from base (radians)
**  . net target position(s)
**
**  The eleven targets correspond to the above 11 target contexts 
**  (mount source chop states A, B and C, PWFS #1, PWFS #2, OIWFS,
**  G1, G2, G3 and G4.
**
**  The three source positions filter into a current position and the position
**  used to compute the OTMs is stored separately in order to manage slews
**  without disturbing the filters.
**
**  The source targets have three offsets from base each.  The mount has
**  one offset from base and the seven guidestar targets have one offset 
**  from base for each chop state.
**
*/

/* Mount */
   static double M_tar_p0[2], M_tar_dt[2], M_tar_t0,
                 M_tar_ob[2],
                 M_tar_p[2];

/* Source, chop states A, B and C */
   static double S_tar_p0[3][2], S_tar_dt[3][2], S_tar_t0[3],
                 S_tar_ob[3][3][2],
                 S_tar_p[3][2],
                 S_tar_pc[3][2], S_tar_pt[3][2];

/* PWFS 1 */
   static double G1_tar_p0[2], G1_tar_dt[2], G1_tar_t0,
                 G1_tar_ob[3][2],
                 G1_tar_p[3][2];

/* PWFS 2 */
   static double G2_tar_p0[2], G2_tar_dt[2], G2_tar_t0,
                 G2_tar_ob[3][2],
                 G2_tar_p[3][2];

/* OIWFS */
   static double G3_tar_p0[2], G3_tar_dt[2], G3_tar_t0,
                 G3_tar_ob[3][2],
                 G3_tar_p[3][2];

/* Generic Guider 1 */
   static double GG1_tar_p0[2], GG1_tar_dt[2], GG1_tar_t0,
                 GG1_tar_ob[3][2],
                 GG1_tar_p[3][2];

/* Generic Guider 2 */
   static double GG2_tar_p0[2], GG2_tar_dt[2], GG2_tar_t0,
                 GG2_tar_ob[3][2],
                 GG2_tar_p[3][2];

/* Generic Guider 3 */
   static double GG3_tar_p0[2], GG3_tar_dt[2], GG3_tar_t0,
                 GG3_tar_ob[3][2],
                 GG3_tar_p[3][2];

/* Generic Guider 4 */
   static double GG4_tar_p0[2], GG4_tar_dt[2], GG4_tar_t0,
                 GG4_tar_ob[3][2],
                 GG4_tar_p[3][2];

/*
**  Pointing Origins
**  ----------------
**
**  There are 4 pointing origins (mount + source for chop states A,
**  B and C).  Each consists of:
**
**  . x,y position (mm)
**  . offset(s) from base (mm)
**  . net current x,y position
**
**  The source pointing-origins have three offsets from base each.  The
**  mount pointing-origin has one offset from base.
*/

/* Mount */
   static double M_por_p0[2],
                 M_por_ob[2],
                 M_por_p[2];

/* Source, chop states S, A and B */
   static double S_por_p0[3][2],
                 S_por_ob[3][3][2],
                 S_por_pc[3][2],
                 S_por_p[3][2];

/*
**  Chopping
**  --------
**
**  There are 2 chopping contexts, for chop states B and C
**  respectively.  Each consists of:
**
**  . user coordinate system and (for mean RA/Dec) the equinox
**
**  .  a flag indicating whether the target positions for the
**     three chop states are expressed directly through the source
**     contexts ("absolute" chopping) or in terms of throw distance
**     and orientation ("relative" chopping);
**
**  .  the chop throw and orientation expressed as offsets in
**     xi,eta (used for the "relative" case only).
*/
   static FRAMETYPE C_frame[2];
   static double C_eqx[2];
   static int C_mode[2];         /* 0 = absolute, else = relative to target A */
   static double C_xieta[2][2],  /* Throw in standard coordinates (~radians) */
                 C_xieta_f[2];   /* Length of unit vector + throw vector */

/*
**  Osculating Transformation Matrices
**  ----------------------------------
**
**  OTM #1 usually describes the transformation from the user frame
**  to apparent RA/Dec.  Usually, OTM #2 describes the transformation
**  from apparent -HA/Dec to mount Az/El;  however, the OTMs can also
**  be used to control the telescope in an Az/El frame.
**
**  Each OTM has a corresponding inverse, used for "upstream"
**  transformations.
**
**  One pair of OTMs is for the mount and one pair is for the
**  rotator.  The twenty four pairs are for the source, PWFS #1,
**  PWFS #2, OIWFS, G1, G2, G3 and G4 each for chop states A, B and C) and
**  there is one pair for relative chopping.
**
**  Between OTM #1 and OTM #2 there is a rotation about the z-axis.
**  For the usual case where the user frame is an RA/Dec, the
**  rotation angle is the local apparent sidereal time.  For the
**  case where the user frame is an Az/El, the rotation angle is
**  zero.
*/

/* Mount */
   static double M_otm1[3][3], M_otm1_i[3][3],
                 M_otm2[3][3], M_otm2_i[3][3];

/* Rotator */
   static double R_otm1[3][3], R_otm1_i[3][3],
                 R_otm2[3][3], R_otm2_i[3][3];

/* Source, chop states S, A and B */
   static double S_otm1[3][3][3], S_otm1_i[3][3][3],
                 S_otm2[3][3][3], S_otm2_i[3][3][3];

/* PWFS #1, chop states S, A and B */
   static double G1_otm1[3][3][3], G1_otm1_i[3][3][3],
                 G1_otm2[3][3][3], G1_otm2_i[3][3][3];

/* PWFS #2, chop states S, A and B */
   static double G2_otm1[3][3][3], G2_otm1_i[3][3][3],
                 G2_otm2[3][3][3], G2_otm2_i[3][3][3];

/* OIWFS, chop states S, A and B */
   static double G3_otm1[3][3][3], G3_otm1_i[3][3][3],
                 G3_otm2[3][3][3], G3_otm2_i[3][3][3];

/* Generic Guider #1, chop states S, A and B */
   static double GG1_otm1[3][3][3], GG1_otm1_i[3][3][3],
                 GG1_otm2[3][3][3], GG1_otm2_i[3][3][3];

/* Generic Guider #2, chop states S, A and B */
   static double GG2_otm1[3][3][3], GG2_otm1_i[3][3][3],
                 GG2_otm2[3][3][3], GG2_otm2_i[3][3][3];

/* Generic Guider #3, chop states S, A and B */
   static double GG3_otm1[3][3][3], GG3_otm1_i[3][3][3],
                 GG3_otm2[3][3][3], GG3_otm2_i[3][3][3];

/* Generic Guider #4, chop states S, A and B */
   static double GG4_otm1[3][3][3], GG4_otm1_i[3][3][3],
                 GG4_otm2[3][3][3], GG4_otm2_i[3][3][3];

/* Chop orientation and throw, chop states B and C */
   static double C_otm1[2][3][3], C_otm1_i[2][3][3],
                 C_otm2[2][3][3], C_otm2_i[2][3][3];

/*-----------------------------------------------------------------------*/

/*
** Filters
** -------
**
** The filters allow one quantity to feed into another to equalize the
** two.  The elimination of the discrepancy can occur instantaneously,
** gradually or not at all.  
**
**   The "bw" parameter stands for "bandwidth";  it controls the
**   extent to which the size of the discrepancy affects the speed
**   of equalization.  0.0 = open-circuit;  1.0 = immediate
**   equalization.
**
**   The "min" parameter is the minimum discrepancy recognized,
**   before equalization is forced.
**
**   The "max" parameter limits the speed of equalization to a
**   specified fixed value.
**
**   The "sc" stands for "short circuit"; it controls the starting point for 
**   the second quantity. 
**
**       0  => start at current value 
**      > 0 => start at filtered value, i.e. as if the filter was a short 
**                  circuit. 
**       2  => short circuit on first pass for each new configuration.
**       3  => short circuit on first pass only and for this configuration only
**      -2  => same as 2 after first pass
**
**
**   For the pointing filter the "w" parameters, one per chop state plus one
**   for the current NOD beam, are the weights that control what fraction of 
**   each of the sources - A, B or C - is fed into the mount.
**
** The parameters are in radians units.
*/

/* Filter 1:  science targets to current targets */
   static double F1_bw, F1_grab, F1_maxv;
   static int F1_sc;

/* Filter 2:  source to mount */
   static double F2_w[4], F2_bw, F2_grab, F2_maxv;
   static int F2_sc;

/*-----------------------------------------------------------------------*/

/*
** M2 tip/tilt
** -----------
**
** (3 chop states:  A, B, C)
**
*/
   static double M2_scan_x[3], M2_scan_y[3];

/*-----------------------------------------------------------------------*/

/*
** Guidestars
** ----------
**
** For 3 wavefront sensors (PWFS #1, PWFS #2, OIWFS)
** and 4 generic guiders (G1, G2 G3 and G4)
**
**   x/y coordinates, in millimetres, with respect to the rotator
**   axis for each of 3 chop states:
**
**   Active/inactive flag for 3 chop states for each of 3 nod states
**
*/
   static double G1_x[3], G1_y[3];
   static double G2_x[3], G2_y[3];
   static double G3_x[3], G3_y[3];
   static double GG1_x[3], GG1_y[3];
   static double GG2_x[3], GG2_y[3];
   static double GG3_x[3], GG3_y[3];
   static double GG4_x[3], GG4_y[3];
   static int G1_act[3][3];
   static int G2_act[3][3];
   static int G3_act[3][3];
   static int GG1_act[3][3];
   static int GG2_act[3][3];
   static int GG3_act[3][3];
   static int GG4_act[3][3];
/*
** Planets
** -------
**
** The planet code and a flag to indicate whether the differential rates
** should be updated by the Solar system loop.
*/
   static PLANET P_code[11];
   static int P_override_rates[11];

/*
** Orbital elements
** ----------------
**
** The planet code
*/
   static int O_jform[11];
   static double O_epoch[11];
   static double O_orbinc[11];
   static double O_anode[11];
   static double O_perih[11];
   static double O_aorq[11];
   static double O_e[11];
   static double O_aorl[11];
   static double O_dm[11];

   static double Debug1;
   static double Debug2;

/* Distortion coefficients to correct for any distortions by the AO systems */
   static double Ao2t[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
   static double T2ao[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;

/* Specific distortion ceofficients for Altair */
   static double Altair2t[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
   static double T2altair[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;

/* Specific distortion ceofficients for GSAOI */
   static double Gsaoi2t[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
   static double T2gsaoi[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;

/* Default distortion ceofficients */
   static double Default2t[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
   static double T2default[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;

   static double O_por[2] = {0.0, 0.0};

/* Chop mode - not used in the kernel but needed in the config checking code. */
   static int ChopMode;
#endif

