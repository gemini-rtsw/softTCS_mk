/*
   *   FILENAME
   *
   *   tcsAosSimulation.c
   *
   *   This module holds the routines that are used in the GAOS Simulation 
   *
   *   FUNCTION NAME(S)
   *
   *   tcsAoInitCAD          - initialise variables for the AO simulator
   *   tcsAoFollowCAD        - Implement FOLLOW for GAOS movement
   *   tcsAoMoveCAD          - implement the GAOS move command
   *   tcsAoZernikes         - supply dummy Zernikes when correcting
   *   tcsAosSimulate        - simulate the movement of the AOWFS
   *   tcsAosComplete        - signal completion of a move command
   *   tcsAoStop             - stop subsystem
   *   tcsAoGenericCAD       - general purpose CAD routine
   *   tcsAOcentreWfsCAD     - Simulated centreWfs command
   *   tcsAOcorrectCAD       - Simulated correct command
   *   tcsAOdeployAdcCAD     - Simulated deployAdc command
   *   tcsAOentShutterCAD    - Simulated entShutter command
   *   tcsAOexitShutterCAD   - Simulated exitShuttercommand
   *   tcsAOlgsirisCAD       - Implement Altair LGS iris control
   *   tcsAOlgsNDfiltCAD     - Simulate LGS ND filter command
   *   tcsAOncpaCAD          - Set the filenames for flexure and ncp
   *   tcsAOngsNDfiltCAD     - Simulate BGS ND filter command
   *   tcsAOmoveAdcCAD       - Simulated moveAdc command
   *   tcsAOmoveAStarCAD     - Simulated moveAStar command
   *   tcsAOoiwfsSourceCAD   - Simulated oiwfsSource command
   *   tcsAOprepareCmCAD     - Simulated prepareCm command
   *   tcsAOselectBsCAD      - Simulated selectBs command
   *   tcsAOselectCalModeCAD - simulated selectCalMode command
   *   tcsAOsetTransform     - set transformation coeffs for image x,y
   *   tcsAOstrapCorrCtlCAD  - Implement strapCorrCtl
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsAosSimulation.c,v $
 * Revision 1.20  2014/02/08 02:10:21  gemvx
 * REL-1630 implement aoLgsTTFSource command and simulators
 *
 * Revision 1.19  2012/05/01 15:39:25  cjm
 * Add code for lgsp1Source command
 *
 * Revision 1.18  2009/12/01 13:48:24  cjm
 * Fix error in generating error estimates
 *
 * Revision 1.17  2007/01/09 14:33:19  cjm
 * Remove spurious extra comment characters
 *
 * Revision 1.16  2006/12/12 15:15:26  cjm
 * Implement simulations of several new Altair commands
 *
 * Revision 1.15  2006/09/18 21:05:17  gemvx
 * mbec
 * remove [500-2500] range check of central wavelength for Altair Science ADC [frs 6121]
 *
 * Revision 1.14  2003/05/07 12:06:33  dlt
 * Allow zero for matrix id in correct command
 *
 * Revision 1.13  2002/11/22 00:12:26  cjm
 * Allow a default bandwidth to be specified
 *
 * Revision 1.12  2002/11/19 09:03:40  dlt
 * Output X/Y of last prepared control matrix
 *
 * Revision 1.11  2002/11/08 12:07:25  cjm
 * Add routine setTransform
 *
 * Revision 1.10  2002/10/04 14:52:51  cjm
 * Add routine tcsAoZernikes
 *
 * Revision 1.9  2002/10/02 08:54:29  cjm
 * Output Altair shutter positions
 *
 * Revision 1.8  2002/04/04 14:56:16  cjm
 * Fix typo in comments that referred to incorrect axis
 *
 * Revision 1.7  2002/02/27 13:49:44  ptaylor
 * Altair simulation now up to date wrt Altair/TCS ICD
 *
 * Revision 1.6  2001/05/25 07:23:21  cjm
 * Use menuCarstates include file not car.h
 *
 * Revision 1.5  2001/05/17 14:50:37  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.4  2001/04/17 15:55:19  cjm
 * Initialise xdemandv etc. to avoid possible ininitialised variables
 *
 * Revision 1.3  2000/08/18 16:36:37  cjm
 * Read TCS data from field J rather than F
 *
 * Revision 1.2  1999/06/16 21:26:48  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.1.1.1  1998/11/08 00:21:09  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.5  1998/06/08 10:11:58  tcs
 * Fix bug in probe simulation
 *
 * Revision 1.4  1998/03/25 17:11:40  cjm
 * Add support for selectBs, selectCalMode and oiwfsSource
 *
 * Revision 1.3  1998/01/15 17:09:17  pbt
 * On receipt of a new trackId it does not always go BUSY
 *
 * Revision 1.2  1997/11/20 12:33:56  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.1  1997/10/31 12:33:30  pbt
 * Simulation code for Gemini AO system
 *
 */
/* *INDENT-ON* */



#include <string.h>
#include <epicsStdioRedirect.h>
#include <epicsStdlib.h>
#include <math.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>

#include "tcsAos.h"
#include "tcsConstants.h"
#include "tcsServo.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "timeLib.h"
#include "tcsRandom.h"

#define ZDMAX 73.0          /* Maximum operational ZD for Gemini telescope */
#define CASS_ANG_MIN   0.0  /* Cassegrain rotator angle range */
#define CASS_ANG_MAX 360.0
#define AOWFS_XMIN   -37.2   /* AO WFS X/Y probe position limits */
#define AOWFS_XMAX    37.2
#define AOWFS_YMIN   -37.2
#define AOWFS_YMAX    37.2

/* Control matrix ID */
static int aoControlMatId = 0 ;

/* Guide probe states */
static int StateProbe;

/* probe positions */

static double x;
static double y;
static double z;

/* Demand position from MOVE command (3 guide probes) */

static double xtarget;
static double ytarget;
static double ztarget;

static int count = 0;

/* Default transform coefficients */
static double aoSimt2a[6]= {0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
static double aoFocusCoeffs[3] = {0.0, 0.0, 0.0};

/*+
 *   Function name:
 *   tcsAoInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the AO control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the AO control system.
 *
 *   Invocation:
 *   tcsAoInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *   External variables:
 *   Any external variables used in this function or procedure
 *
 *   Prior requirements:
 *   None
 *
 *-
 */

void tcsAoInit(void)
{
    static int first = TRUE;

    if (first) first = FALSE;
    StateProbe = STOPPED;
}

/*+
 *   Function name:
 *   tcsAoFollowCAD
 *
 *   Purpose:
 *   Implement the follow CAD record in the GAOS  simulator
 *
 *   Description:
 *   This function implements the follow CAD record in the AO simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. Since all the 
 *   data is being transmitted to separate records the function of this
 *   routine is simply to set some internal flags that signal the internal
 *   state of the simulator to other pieces of code.
 *
 *   Invocation:
 *   tcsAoFollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   Prior requirements:
 *   None
 *
 *-
 */

long tcsAoFollowCAD(struct cadRecord *pcad)
{

/* CAD directive is in field DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
      StateProbe = FOLLOWING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"On");
      return CAD_ACCEPT;
      break;  /* End menuDirectiveSTART */

/* The STOP CAD directive simply sets the axis
   state flags to STOPPED   */

   case menuDirectiveSTOP:
      StateProbe = STOPPED;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"Off");
      return CAD_ACCEPT;

   default :
      return CAD_ACCEPT;
      break;
   }
}


/*+
 *   Function name:
 *   tcsAoMoveCAD
 *
 *   Purpose:
 *   Implement the Move CAD record in the GAOS  simulator
 *
 *   Description:
 *   This function implements the move CAD record in the GAOS simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. 
 *
 *   Invocation:
 *   tcsAoMoveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<) status  (long)  return status, 0 = OK
 *
 *   Deficiencies:
 *-
 */

long tcsAoMoveCAD(struct cadRecord *pcad)
{
    double guideX, guideY, guideZ, cassAng, zd, sodiumAlt;
    long status;

/* The CAD directive is field  DIR */
    switch (pcad->dir) {

    case menuDirectiveSTART:
    case menuDirectivePRESET:
       
        status = CAD_REJECT;
        tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

/* Decode Guide X position */
        if (!tcsDcLen(pcad->a)) {
          tcsCsAppendMessage (pcad, "No Guide X pos given");
          break ;
        }     
        if (tcsDcDouble ("Guide X: ", pcad->a, &guideX, pcad))
          break;
        if (guideX < AOWFS_XMIN || guideX > AOWFS_XMAX) {
            tcsCsAppendMessage (pcad, "X pos out of range") ;
            break ;
        }
	
/* Decode Guide Y position */
        if (!tcsDcLen(pcad->b)) {
          tcsCsAppendMessage (pcad, "No Guide Y pos given");
          break ;
        }     
        if (tcsDcDouble ("Guide Y: ", pcad->b, &guideY, pcad))
          break;
        if (guideY < AOWFS_YMIN || guideY > AOWFS_YMAX) {
            tcsCsAppendMessage (pcad, "Y pos out of range") ;
            break ;
        }
/* Decode Guide Z position */
        if (!tcsDcLen(pcad->c)) {
          tcsCsAppendMessage (pcad, "No Guide Z pos given");
          break ;
        } 
        if (tcsDcDouble ("Guide Z: ", pcad->c, &guideZ, pcad))
          break;
        if (guideZ < -1.0 || guideZ > 1.0) {
            tcsCsAppendMessage (pcad, "Z pos out of range") ;
            break ;
        }
/* Decode Cassegrain angle value */
        if (tcsDcLen(pcad->d)) {
          if (tcsDcDouble ("Cass Angle: ",  pcad->d, &cassAng, pcad))
              break;
          if (cassAng < CASS_ANG_MIN || cassAng > CASS_ANG_MAX) {
              tcsCsAppendMessage (pcad, "Cass angle out of range") ;
              break ;
          }
        }
/* Decode Zenith distance value */
        if (tcsDcLen(pcad->e)) {
          if (tcsDcDouble ("Zenith distance: ",  pcad->e, &zd, pcad))
              break;
          if (zd < 0.0 || zd > ZDMAX) {
              tcsCsAppendMessage (pcad, "ZD out of range") ;
              break ;
          }
        }
/* Decode Sodium altitude value */
        if (tcsDcLen(pcad->f)) {
          if (tcsDcDouble ("Sodium altitude: ",  pcad->f, &sodiumAlt, pcad))
              break;
          if (sodiumAlt < 85.0 || sodiumAlt > 100.0) {
              tcsCsAppendMessage (pcad, "Sodium Alt out of range") ;
              break ;
          }
        }

        xtarget = guideX;
        ytarget = guideY;
        ztarget = guideZ;
        if (pcad->dir == menuDirectiveSTART) 
        {
         StateProbe = MOVING;
         strcpy(pcad->vala, "Off");
        }
        strcpy(pcad->mess, "Command accepted");

        return CAD_ACCEPT;
        break;                  /* End PmenuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
    case menuDirectiveSTOP:
        strcpy(pcad->mess, "Move: argument is valid");
        StateProbe = STOPPED;

/* Output acceptance message */
        strcpy(pcad->vala, "Off");
        strcpy(pcad->mess, "Command accepted");
        return CAD_ACCEPT;
        break;

    default:
        return CAD_ACCEPT;
        break;
    }    
    return(status);
}

/*+
 *   Function name:
 *   tcsAosSimulate
 *
 *   Purpose:
 *   Simulates behaviour of the AO probe without any hardware
 *
 *   Description:
 *   This routine is linked to the tcsAosSimulate record and performs the main
 *   simulation of the AO probe. At present the simulation is very simple. If the
 *   guide probe is stopped then the output is constant. If an axis is active 
 *   then the output is just the demand . 
 *
 *   Inputs :
 *
 *   a => default startup x position (mm)
 *   b => default startup y position (mm)
 *   c => default startup z position (mm)
 *   d => max probe velocity (mm/sec)
 *   j => Input demand array from TCS:
 *    Element 0  = Time now
 *    Element 1  = Target time
 *    Element 2  = Track identifier
 *    Element 3  = Demanded X position
 *    Element 4  = Demanded Y position
 *    Element 5  = Demanded Z position
 *
 *
 *   Outputs :
 * 
 *   vala => time at which positions apply
 *   valb => current x (mm)
 *   valc => current y (mm)
 *   vald => current z (mm)
 *   vale => x error (mm)
 *   valf => y error (mm)
 *   valg => z error (mm)
 *   valh => status
 *   vali => trackid
 *   valj => disable or enable following processing chain
 *
 *   Invocation:
 *   tcsAosSimulate(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies:
 *   The calculations assume the record is being scanned at 20Hz (through a
 *   constant DT). It should fetch the scan rate from the .SCAN field
 *
 *-
 */

long tcsAosSimulate(struct genSubRecord *pgsub)
{

    static int first = TRUE ;
    static int substat;      /* subsystem status */
    static double trackid;   /* current track id */

    double now;                 /* current time */
    unsigned long arraySize;    /* number of elements in inout demand array */
    double AOSdemand[6];        /* demand data array from kernel */
    double xdemand;             /* X demand for Chop state A, B, and C */
    double ydemand;             /* Y demand for Chop state A, B, and C */
    double zdemand;             /* Z demand for Chop state A, B, and C */
    double xnow, ynow, znow;    /* X,Y,Z servo demands */
    double xdemandv, ydemandv;  /* X,Y demand velocity */
    double zdemandv;            /* Z demand velocity */
    double newtrack;            /* track id of demand */
    int newstat;                /* new subsystem status */
    int stateProbe;             /* local copy of probe states */
    int linkSelect;             /* Mask for downstream processing */

    double tappl;               /* time for which demands are correct */
    static int inPositionX;     /* X now in position flag */
    static int inPositionY;     /* Y now in position flag */
    static int inPositionZ;     /* Z now in position flag */
    static int inPositionCount = 0 ;   /* X, Y and Z all successively in position count */
    static double tlast;        /* Time at last entry */
    static double xlast;        /* Previous X demands */
    static double ylast;        /* Previous Y demands */
    static double zlast;        /* Previous Z demands */
    static double xvel;         /* Current X probe velocity */
    static double yvel;         /* Current Y probe velocity */
    static double zvel;         /* Current Z probe velocity */
    static double xerr;         /* Current X position error */
    static double yerr;         /* Current Y position error */
    static double zerr;         /* Current Z position error */

    static struct ServoState servoStateX;
    static struct ServoState servoStateY;
    static struct ServoState servoStateZ;
    static struct ServoConfig servoConfigX;
    static struct ServoConfig servoConfigY;
    static struct ServoConfig servoConfigZ;

    count++;

/*   Get a local copy of the probe state as the global values may get changed
   from elsewhere */
    stateProbe = StateProbe;

    if (first) {

/* Set servo initial values */
        servoConfigX.dvmax = 12.5;
        servoConfigX.gs = 4.0;
        servoConfigX.gp = 1.0;
        servoConfigX.gi = 0.1;
        servoConfigX.pi = 1.0;
        servoConfigX.pok = 0.010;
        servoConfigX.tok = 0.1;
        servoStateX.pdtold = *(double *) pgsub->a;
        servoConfigX.noise = 0.0;
        timeNow(&(servoStateX.told));
        servoStateX.told -= 0.05;
        servoStateX.tout = servoStateX.told;
        servoStateX.vd = 0.0;
        servoStateX.accum = 0.0;
        x = servoStateX.pdtold;
        xvel = 0.0;

        servoConfigY.dvmax = 12.5;
        servoConfigY.gs = 1.0;
        servoConfigY.gp = 1.5;
        servoConfigY.gi = 0.7;
        servoConfigY.pi = 0.5;
        servoConfigY.pok = 0.010;
        servoConfigY.tok = 0.1;
        servoStateY.pdtold = *(double *) pgsub->b;
        servoConfigY.noise = 0.0;
        timeNow(&(servoStateY.told));
        servoStateY.told -= 0.05;
        servoStateY.tout = servoStateY.told;
        servoStateY.vd = 0.0;
        servoStateY.accum = 0.0;
        y = servoStateY.pdtold;
        yvel = 0.0;

        servoConfigZ.dvmax = 12.5;
        servoConfigZ.gs = 4.0;
        servoConfigZ.gp = 1.0;
        servoConfigZ.gi = 0.1;
        servoConfigZ.pi = 1.0;
        servoConfigZ.pok = 0.010;
        servoConfigZ.tok = 0.1;
        servoStateZ.pdtold = *(double *) pgsub->c;
        servoConfigZ.noise = 0.0;
        timeNow(&(servoStateZ.told));
        servoStateZ.told -= 0.05;
        servoStateZ.tout = servoStateZ.told;
        servoStateZ.vd = 0.0;
        servoStateZ.accum = 0.0;
        z = servoStateZ.pdtold;
        zvel = 0.0;

        newstat = menuCarstatesIDLE;
        substat = -1;
        trackid = 0.0;
        first = FALSE;
    }
/* fetch latest velocities etc */
    servoConfigX.vtmax = *(double *) pgsub->d;
    servoConfigY.vtmax = *(double *) pgsub->d;
    servoConfigZ.vtmax = *(double *) pgsub->d;

/* Get demand data array */
    arraySize = pgsub->noj;
    memcpy(AOSdemand, pgsub->j, arraySize * sizeof(double));
    tappl    = AOSdemand[1];
    newtrack = AOSdemand[2];
    xdemand  = AOSdemand[3];
    ydemand  = AOSdemand[4];
    zdemand  = AOSdemand[5];


/* send demands to servo */
    timeNow(&now);

    xdemandv = 0.0 ;
    ydemandv = 0.0 ;
    zdemandv = 0.0 ;

    if (stateProbe == MOVING) {
        inPositionX = tcsServo(now, xtarget, 0, &servoConfigX,
                        &servoStateX, &x, &xvel);
        xerr = xtarget - x;
        inPositionY = tcsServo(now, ytarget, 0, &servoConfigY,
                        &servoStateY, &y, &yvel);
        yerr = ytarget - y;
        inPositionZ = tcsServo(now, ztarget, 0, &servoConfigZ,
                        &servoStateZ, &z, &zvel);
        zerr = ztarget - z;

    } else if (stateProbe == FOLLOWING) {
        if (tappl > tlast) {
            xdemandv = (xdemand - xlast) / (tappl - tlast);
            ydemandv = (ydemand - ylast) / (tappl - tlast);
            zdemandv = (zdemand - zlast) / (tappl - tlast);
        }
        xnow = xdemand + xdemandv * (now - tappl);
        inPositionX = tcsServo(tappl, xnow, 0, &servoConfigX,
                               &servoStateX,
                               &x, &xvel);
        xerr = xnow - x;

        ynow = ydemand + ydemandv * (now - tappl);
        inPositionY = tcsServo(tappl, ynow, 0, &servoConfigY,
                        &servoStateY, &y, &yvel);
        yerr = ynow - y;
        znow = zdemand + zdemandv * (now - tappl);
        inPositionZ = tcsServo(tappl, znow, 0, &servoConfigZ,
                        &servoStateZ, &z, &zvel);
        zerr = znow - z;

    } else {
        inPositionX = tcsServo(now, x, 1, &servoConfigX,
                        &servoStateX, &x, &xvel);
        xerr = 0.0;
        inPositionY = tcsServo(now, y, 1, &servoConfigY,
                        &servoStateY, &y, &yvel);
        yerr = 0.0;
        inPositionZ = tcsServo(now, z, 1, &servoConfigZ,
                        &servoStateZ, &z, &zvel);
        zerr = 0.0;
    }

    if (inPositionX && inPositionY && inPositionZ)
        inPositionCount++;
    else
        inPositionCount = 0 ;

/* Round values to nearest micron */
    x = (floor(((1000.0 * x)) + 0.5)) / 1000.0;
    y = (floor(((1000.0 * y)) + 0.5)) / 1000.0;
    z = (floor(((1000.0 * z)) + 0.5)) / 1000.0;   

/* Initialise the link selection field. The bits in this field 
   are as follows :
     Bit 0 = Process completion record
     Bit 1 = Process CAR record
     Bit 2 = Process trackId record */
    linkSelect = 0;

/* Determine new subsystem state. To be 'all in position', 
   X, Y and Z must be in position 10x in successive calls */     

        if (inPositionCount > 10 ) 
          {
          newstat = menuCarstatesIDLE;
 /* If not following, set to STOPPED */
          if (stateProbe == MOVING || stateProbe == STOPPING)
             {
              StateProbe = STOPPED ;
              linkSelect += 1;     /* Trigger record 'complete' */
             }
 /* If not following, set to STOPPED */
          } 
        else
/* Not in position */
           newstat = menuCarstatesBUSY;

/* Set the link selection field and update the subsystem state */

    if (newstat != substat) {
        substat = newstat;
        linkSelect += 2;           /* Trigger update of CAR record */
    }
    if (newtrack != trackid) {
        trackid = newtrack;
/* If out of position, reset count when new trackId */
        if (!inPositionX || !inPositionY || !inPositionZ) inPositionCount = 0;
        linkSelect += 4;           /* Trigger update of trackId record */
    }

/* save demands */
    tlast = tappl;
    xlast = xdemand;
    ylast = ydemand;
    zlast = zdemand;

/* now output the results */
    *(double *) pgsub->vala = tappl;
    *(double *) pgsub->valb = x;
    *(double *) pgsub->valc = y;
    *(double *) pgsub->vald = z;
    *(double *) pgsub->vale = xerr;
    *(double *) pgsub->valf = yerr;
    *(double *) pgsub->valg = zerr;
    *(double *) pgsub->valh = substat;
    *(double *) pgsub->vali = trackid;
    *(long *) pgsub->valj = linkSelect;

    return CAD_ACCEPT;
}

/*+
 *   Function name:
 *   tcsAosComplete
 *
 *   Purpose:
 *   Signal complete of a GAOS move command
 *
 *   Description:
 *   Signals completion of a move command by writing IDLE to the appropriate
 *   CAR record.
 *
 *   Invocation:
 *   tcsAosComplete(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *) pointer to gensub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAosComplete(struct genSubRecord *pgsub)
{

/* output values for CAR Message and State fields */
    strcpy(pgsub->vala, "Stopped");
    *(long *)pgsub->valb = menuCarstatesIDLE;

    return 0;
}

/*+
 *   Function name:
 *   tcsAoStop
 *
 *   Purpose:
 *   Stops the mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAoStop
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *-
 */

long tcsAoStop(struct genSubRecord *pgsub)
{
    StateProbe = STOPPED;
    strncpy(pgsub->vala, "Off", 3);
    return (0);
}

/*+
 *   Function name:
 *   tcsAoGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the A & G
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAoGenericCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   Only responds to the START directive
 *
 *-
 */

long tcsAoGenericCAD(struct cadRecord *pcad)
{
    int status;                 /* return status */
    char command[29];           /* command name */
    int i, j;                   /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
    for (i = 0, j = 0; i < 29; i++, j++) {
        command[j] = pcad->name[i];
        if (!(pcad->name[i]))
            break;
        if (command[j] == ':')
            j = -1;
    }

    switch (pcad->dir) {
    case menuDirectiveSTART:

        /* write output message (n.b. no more that 28 characters) */
        sprintf(pcad->mess, "GAOS : %.13s started", command);

        /* If its a STOP command, output the following flag value (zero) */
        if (strncmp(command, "stop", 4) == 0)
            strcpy(pcad->vala, "Off");
        else
        {
/* Copy over the parameters to the output fields */

         strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
         strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
         strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
         strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
         strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
         strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
        }
        status = CAD_ACCEPT;
        break;

    default:
        status = 0;
        break;
    }
    return (status);
}

/*+
 *   Function name:
 *   tcsAOcentreWfsCAD
 *
 *   Purpose:
 *   Emulate the AO centreWfs command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS centreWfs command.
 *
 *   Invocation:
 *   tcsAOcentreWfsCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOcentreWfsCAD (struct cadRecord *pcad)

{
    long status ;                            /* Return status */
    long offsetFlag;

    status = CAD_ACCEPT;
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    switch (pcad->dir) 
    {
     case menuDirectivePRESET:
     case menuDirectiveSTART:
       status = CAD_REJECT;
/* Decode offset flag */
       if (!tcsDcLen(pcad->a)) {
         tcsCsAppendMessage (pcad, "No offset flag given");
         break ;
       }  
       if (tcsDcLong ("Offset flag: ", pcad->a, &offsetFlag, pcad))
         break;
       if (offsetFlag < 0 || offsetFlag > 1) {
           tcsCsAppendMessage (pcad, "Offset flag invalid") ;
           break ;
       }
       status = CAD_ACCEPT;
       break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOcorrectCAD
 *
 *   Purpose:
 *   Emulate the AO correct command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS correct command.
 *
 *   Invocation:
 *   tcsAOcorrectCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => state (ON/OFF)
 *   b => Matrix ID
 *   c => Override bias flag (0/1)
 *
 *   EPICS outputs:
 *
 *   vala => 0 = off, 1 = on
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOcorrectCAD (struct cadRecord *pcad)
{
  long status ;                            /* Return status */
  long matrixID, overrideFlag ;
  int code;
  
/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :

        status = CAD_REJECT ;
/* Decode close servo loop status  */
        if (!tcsDcLen(pcad->a)) {
          tcsCsAppendMessage (pcad, "No servo loop status");
          break ;
        }  
        if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;
	
/* Decode control matrix ID (optional) */
        if (tcsDcLen(pcad->b))
        {
          if (tcsDcLong ("Matrix ID: ", pcad->b, &matrixID, pcad))
            break;
          if (matrixID < 0) {
            tcsCsAppendMessage (pcad, "Invalid matrix ID") ;
            break ;
          }
        }
/* Decode override flag */
        if (!tcsDcLen(pcad->c)) {
          tcsCsAppendMessage (pcad, "No override flag");
          break ;
        }  
        if (tcsDcLong ("Override flag: ", pcad->c, &overrideFlag, pcad))
          break;
        if (overrideFlag < 0 || overrideFlag > 1) {
            tcsCsAppendMessage (pcad, "Invalid flag (C)") ;
            break ;
        }

      *(long *)pcad->vala = (long)code ;
      status = CAD_ACCEPT;
      break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}


/*
 *   Function name:
 *   tcsAOentShutterCAD
 *
 *   Purpose:
 *   Emulate the AO entshutter command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS entry shutter command.
 *
 *   Invocation:
 *   tcsAOentShutterCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (OPEN/CLOSE)
 *
 *   EPICS outputs:
 *   
 *   vala => current position 1 = Open, 0 = Closed
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOentShutterCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :

     status = CAD_REJECT ;

/* Check the requested state (ON/OFF) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"OPEN",4) != 0) && (strncmp(ustring,"CLOSE",5) !=0) )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "AO entshutter: position not OPEN/CLOSE") ;
       return status ;
     }
     
     if (!strncmp (ustring, "OPEN", 4) ) {
      *(long *)pcad->vala = 1 ;
     } else {
      *(long *)pcad->vala = 0;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOexitShutterCAD
 *
 *   Purpose:
 *   Emulate the AO exitshutter command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS exit shutter command.
 *
 *   Invocation:
 *   tcsAOexitShutterCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (OPEN/CLOSE)
 *
 *   EPICS outputs:
 *
 *   vala => current position 1 = Open, 0 = Closed
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOexitShutterCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :

     status = CAD_REJECT ;

/* Check the requested state (ON/OFF) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"OPEN",4) != 0) && (strncmp(ustring,"CLOSE",5) !=0) )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "AO exitshutter: position not OPEN/CLOSE") ;
       return status ;
     }

     if (!strncmp (ustring, "OPEN", 4) ) {
      *(long *)pcad->vala = 1 ;
     } else {
      *(long *)pcad->vala = 0;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOlgsirisCAD
 *
 *   Purpose:
 *   Emulate the AO lgsirisAssembly command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS LGS iris control.
 *   Note that in the real GAOS this is implemented as an assembly record 
 *   not a CAD as is done here. 
 *
 *   Invocation:
 *   tcsAOlgsirisCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (OPEN/CLOSE)
 *
 *   EPICS outputs:
 *
 *   vala => current position Open, Close or percentage opening
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAOlgsirisCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */
  double dval ;                            /* Demand opening percentage */
  static char ins[MAX_STRING_SIZE] ;
  char *endp;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;
     strcpy(ins, pcad->a);

/* Check the requested state (OPEN/CLOSE) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ((strncmp(ustring,"OPEN",4) != 0) && (strncmp(ustring,"CLOSE",5) !=0)) {
       dval = strtod(ustring, &endp);
/* Unfortunately, errno is unlikely to ever be set so this first test is
*  always likely to pass with dval set to 0.0
*/
       if (ustring != endp && *endp == '\0') {
         if (dval > 100.0 || dval < 0.0) {
           status = CAD_REJECT ;
           strcpy (pcad->mess, "AO lgsiris: position out of range") ;
           return status ;
         }
         if (dval == 0.0) {
           strcpy(ins, "close");
         }
       } else {
         status = CAD_REJECT ;
         strcpy (pcad->mess, "AO lgsiris: position invalid") ;
         return status ;
       }
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART :
     strcpy(pcad->vala, ins);
     break ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOlgsNDfiltCAD
 *
 *   Purpose:
 *   Emulate the AO lgsNDfiltAssembly command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS LGS ND filter
 *   control. Note that in the real GAOS this is implemented as an 
 *   assembly record not a CAD as is done here. 
 *
 *   Invocation:
 *   tcsAOlgsNDfiltCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (In/Out)
 *
 *   EPICS outputs:
 *
 *   vala => current position In or Out 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAOlgsNDfiltCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* Check the requested state (IN/OUT) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ((strncmp(ustring,"IN",2) != 0) && (strncmp(ustring,"OUT",3) !=0)) {
       strcpy (pcad->mess, "LGS ND position invalid") ;
       return status ;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART :
     strcpy(pcad->vala, pcad->a);
     break ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOncpaCAD
 *
 *   Purpose:
 *   Emulate the ncpa command
 *
 *   Description:
 *   The files for reading the ncp errors and flexure are set 
 *   by this command. For the simulator we do nothing
 *   except copy the inputs to the outputs.
 *
 *   Invocation:
 *   tcsAOncpaCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *   a => file containing non-common path errors
 *   b => file containing flexure corrections 
 *
 *   EPICS outputs:
 *   vala => file containing non-common path errors
 *   valb => file containing flexure corrections 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAOncpaCAD (struct cadRecord *pcad)
{
  long status ;                            /* Return status */
  
/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

        status = CAD_REJECT ;

/* Just test for empty inputs */
        if (!tcsDcLen(pcad->a)) {
          tcsCsAppendMessage (pcad, "No ncpa file");
          break ;
        }  
        if (!tcsDcLen(pcad->b)) {
          tcsCsAppendMessage (pcad, "No flexure file");
          break ;
        }  

      status = CAD_ACCEPT;
      break;

     case menuDirectiveSTART :
      strcpy(pcad->vala, pcad->a);
      strcpy(pcad->valb, pcad->b);

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOngsNDfiltCAD
 *
 *   Purpose:
 *   Emulate the AO ngsNDfiltAssembly command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS NGS ND filter
 *   control. Note that in the real GAOS this is implemented as an 
 *   assembly record not a CAD as is done here. 
 *   It is essentially the same routine as the equivalent LGS one but
 *   needs to be a different function because the name is fixed by
 *   the macro substitutions on the capfast schematic.
 *
 *   Invocation:
 *   tcsAOngsNDfiltCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (In/Out)
 *
 *   EPICS outputs:
 *
 *   vala => current position In or Out 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAOngsNDfiltCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* Check the requested state (IN/OUT) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ((strncmp(ustring,"IN",2) != 0) && (strncmp(ustring,"OUT",3) !=0)) {
       strcpy (pcad->mess, "NGS ND position invalid") ;
       return status ;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveSTART :
     strcpy(pcad->vala, pcad->a);
     break ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOdeployAdcCAD
 *
 *   Purpose:
 *   Emulate the AO  deployAdc command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS deploy ADC command.
 *
 *   Invocation:
 *   tcsAOdeployAdcCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => position (IN/OUT)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOdeployAdcCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  char ustring[MAX_STRING_SIZE] ;          /* Buffer for upper case strings */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :

     status = CAD_REJECT ;

/* Check the requested position (IN/OUT) */
     tcsDcUc (pcad->a, MAX_STRING_SIZE, ustring) ;
     if ( (strncmp(ustring,"IN",2) != 0) && (strncmp(ustring,"OUT",3) !=0) )
     {
       status = CAD_REJECT ;
       strcpy (pcad->mess, "AO deployAdc : position not IN/OUT") ;
       return status ;
     }

     status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOmoveAdcCAD
 *
 *   Purpose:
 *   Emulate the AO moveAdc command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS move ADC command.
 *
 *   Invocation:
 *   tcsAOmoveAdcCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Rotator angle (0->360 degs)
 *   b => Zenith distance
 *   c => central wavelength (nm)
 *   d => Auto-adjust ADC flag (ON/OFF)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOmoveAdcCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  double parangle, cenwave, zd ;      /* Input parameter values */
  int code;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {
     case menuDirectivePRESET :
     case menuDirectiveSTART :

        status = CAD_REJECT ;
/* First check the Cassegrain rotator angle */
        if (!tcsDcLen(pcad->a)) {
          tcsCsAppendMessage (pcad, "No rotator angle given");
          break ;
        }
        if (tcsDcDouble ("Rotator angle: ", pcad->a, &parangle, pcad)) break ;
        if (parangle < CASS_ANG_MIN || parangle > CASS_ANG_MAX )
        {
          tcsCsAppendMessage (pcad, "Rotator angle out of range") ;
          break ;
        }
/* Then check the zenith distance */
        if (!tcsDcLen(pcad->b)) {
          tcsCsAppendMessage (pcad, "No zenith distance given");
          break ;
        }
        if (tcsDcDouble ("Zenith distance: ", pcad->b, &zd, pcad)) break ;
        if (zd < 0.0 || zd > ZDMAX )
        {
          tcsCsAppendMessage (pcad, "Zenith distance out of range") ;
          break ;
        }
     
/* Then check the requested central wavelength */
        if (!tcsDcLen(pcad->c)) {
          tcsCsAppendMessage (pcad, "No central wavelength given");
          break ;
        }
        if (tcsDcDouble ("wavelength: ", pcad->c, &cenwave, pcad)) break ;
 
/* Then check the adjust ADC flag value (ON or OFF)  */
        if (!tcsDcLen(pcad->d)) {
          tcsCsAppendMessage (pcad, "No ADC adjust status given");
          break ;
        }
        if (tcsDcOnOff (" ", pcad->d, &code, pcad)) break ;
	
     status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;


     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*
 *   Function name:
 *   tcsAOmoveAStarCAD
 *
 *   Purpose:
 *   Emulate the AO moveAStar command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS moveAStar command.
 *
 *   Invocation:
 *   tcsAOmoveAStarCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => Position of artifical star calibration unit
 *   b => Probe X position (mm.)
 *   c => Probe Y position (mm.)
 *   d => Probe Z position (mm.)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOmoveAStarCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  static char *bsopts[] = {"ASTAR", "FLOOD", "PARK", 
                           "FLENS", "LGS", "NGS", NULL} ; /* Position names */
  int bs ;          /* Index of selected position */
  double probeX, probeY, probeZ ;          /* Input parameter values */

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :

       status = CAD_REJECT ;

/* Decode position name */   
       if (!tcsDcLen(pcad->a)) {
         tcsCsAppendMessage (pcad, "No position given");
         break ;
       }  
       if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;
       
       if (bs == 1)     /* Probe positions needed only for ASTAR (=1) */
       {
/* Decode Probe X position */
         if (!tcsDcLen(pcad->b)) {
           tcsCsAppendMessage (pcad, "No probe X pos given");
           break ;
         }  
         if (tcsDcDouble ("Probe X: ", pcad->b, &probeX, pcad))
           break;
         if (probeX < AOWFS_XMIN || probeX > AOWFS_XMAX) {
             tcsCsAppendMessage (pcad, "X pos out of range") ;
             break ;
         }
/* Decode probe Y position */
         if (!tcsDcLen(pcad->c)) {
           tcsCsAppendMessage (pcad, "No probe Y pos given");
           break ;
         }  
         if (tcsDcDouble ("Probe Y: ", pcad->c, &probeY, pcad))
           break;
         if (probeY < AOWFS_YMIN || probeY > AOWFS_YMAX) {
             tcsCsAppendMessage (pcad, "Y pos out of range") ;
             break ;
         }
/* Decode probe Y position */
         if (!tcsDcLen(pcad->d)) {
           tcsCsAppendMessage (pcad, "No probe Z pos given");
           break ;
         }  
         if (tcsDcDouble ("Probe Z: ", pcad->d, &probeZ, pcad))
           break;
         if (probeZ < 1.0 || probeZ > 100.0) {
             tcsCsAppendMessage (pcad, "Z pos out of range") ;
             break ;
         }
       }
       status = CAD_ACCEPT ;
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsAOoiwfsSourceCAD
 *
 *   Purpose:
 *   Implements the command that selects which OIWFS source to use
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOoiwfsSourceCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Use OIWFS? either ON or OFF
 *      b => Bandwidth of low pass filter applied
 *
 *   EPICS output paramters:  
 *      vala => Use OIWFS?
 *      valb => Bandwidth of low pass filter applied
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcDouble        (tcsDecode)      Validate an input double
 *   tcsDcLong          (tcsDecode)      Validate an input long
 *   tcsDcString        (tcsDecode)      Validate an input string
 *   tcsCsAppendMessage (tcsCadSupport)  Add string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *
 *-
 */
  
long tcsAOoiwfsSourceCAD (struct cadRecord *pcad)
 
{
 
  long status ;           /* Return status */
  int code ;              /* Index of selected AO state */
  long bandwidth ;        /* Bandwidth Hz. */
 
/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
 
   case menuDirectivePRESET :
     status = CAD_REJECT ;
/* Decode (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No OIWFS ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;

/* Decode bandwidth */
     if (code == 1)  /* Switch ON */
     {
	 if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No bandwidth given");
         break ;
       }
       if (tcsDcLong ("bandwidth : ", pcad->b, &bandwidth, pcad)) break ;
       if (bandwidth != -1) {
         if (bandwidth > 500 || bandwidth < 0) {
           tcsCsAppendMessage (pcad, "bandwidth out of range ");
           break ;
         }
       }
     } 

     status = CAD_ACCEPT ;
        
   break ;
 
   case menuDirectiveSTART :
 
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;
}

/*+
 *   Function name:
 *   tcsAOlgsttSourceCAD
 *
 *   Purpose:
 *   Implements the command that turns on/off the LGS+P1 and LGS+OI modes. 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOlgsttSourceCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => toggle Use PWFS1 for LGS TTF either ON or OFF
 *      b => toggle Use OIWFS for LGS TTF either ON or OFF
 *
 *   EPICS output paramters:  
 *      vala => Use PWFS1 for LGS TTF (0 or 1) 
 *      valb => Use OIWFS for LGS TTF (0 or 1) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcDouble        (tcsDecode)      Validate an input double
 *   tcsDcLong          (tcsDecode)      Validate an input long
 *   tcsDcString        (tcsDecode)      Validate an input string
 *   tcsCsAppendMessage (tcsCadSupport)  Add string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *
 *-
 */
  
long tcsAOlgsttSourceCAD (struct cadRecord *pcad)
 
{
 
  long status ;           /* Return status */
  static int code1, code2 ;              /* Index of selected AO state */
 
/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
 
   case menuDirectivePRESET :
     status = CAD_REJECT ;
/* Decode (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No PWFS1 ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->a, &code1, pcad)) break ;

     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No OIWFS ON/OFF given");
       break ;
     }
     if (tcsDcOnOff (" ", pcad->b, &code2, pcad)) break ;

     status = CAD_ACCEPT ;
        
   break ;
 
   case menuDirectiveSTART :
 
     *(long *)pcad->vala = code1 ;
     *(long *)pcad->valb = code2 ;
 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;
}


/*
 *   Function name:
 *   tcsAOprepareCmCAD
 *
 *   Purpose:
 *   Emulate the AO prepareCm command
 *
 *   Description:
 *   This routine provides a minimal emulation of the GAOS prepareCm command.
 *
 *   Invocation:
 *   tcsAOprepareCmCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   Epics input parameters:
 *   a => Guide X position  (mm.)
 *   b => Guide Y position  (mm.)
 *   c => Seeing (optional) (metres)
 *   d => Guide Object estimated magnitude (optional)
 *   e => Aloft windspeed (optional)
 *   f => Use Field lens (1) or not (0)
 *
 *   Epics output parameters:
 *
 *   vala => Control Matrix ID
 *   valb => Guide X position  (mm.)
 *   valc => Guide Y position  (mm.)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *
 *-
 */
long tcsAOprepareCmCAD (struct cadRecord *pcad)

{
  long status ;                            /* Return status */
  static double guideX, guideY;            /* Input parameter values */
  double seeing, mag, wspeed ;
  static long useFlens = 0 ;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :
     case menuDirectiveSTART :
       status = CAD_REJECT;

/* Decode Guide X position */
       if (!tcsDcLen(pcad->a)) {
         tcsCsAppendMessage (pcad, "No Guide X pos given");
         break ;
       } 
       if (tcsDcDouble ("Guide X: ", pcad->a, &guideX, pcad))
         break;
       if (guideX < AOWFS_XMIN || guideX > AOWFS_XMAX) {
           tcsCsAppendMessage (pcad, "X pos out of range") ;
           break ;
       }
	
/* Decode Guide Y position */
       if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No Guide Y pos given");
         break ;
       } 
       if (tcsDcDouble ("Guide Y: ", pcad->b, &guideY, pcad))
         break;
       if (guideY < AOWFS_YMIN || guideY > AOWFS_YMAX) {
           tcsCsAppendMessage (pcad, "Y pos out of range") ;
           break ;
       }
/* Decode Seeing value */
       if (tcsDcLen(pcad->c)) {
         if (tcsDcDouble ("Seeing: ",  pcad->c, &seeing, pcad))
           break;
         if (seeing <= 0.0 || seeing > 1.0) {
             tcsCsAppendMessage (pcad, "Seeing value out of range") ;
             break ;
         }
       }
/* Decode guide object mag.  */
       if (tcsDcLen(pcad->d)) {
         if (tcsDcDouble ("Magnitude: ", pcad->d, &mag, pcad))
           break;
         if (mag < -2.0 || mag > 20.0) {
             tcsCsAppendMessage (pcad, "Magnitude out of range") ;
             break ;
         }
       }

/* Decode aloft windspeed  */
       if (tcsDcLen(pcad->e)) {
         if (tcsDcDouble ("Windspeed: ", pcad->e, &wspeed, pcad))
           break;
         if (wspeed < 0.0 ) {
             tcsCsAppendMessage (pcad, "Windspeed out of range") ;
             break ;
         }
       }

/* Decode use of field lens */
       if (tcsDcLen(pcad->f)) {
         if (tcsDcLong ("Use Flens: ", pcad->f, &useFlens, pcad))
           break;
         if (useFlens < 0 || useFlens > 1) {
             tcsCsAppendMessage (pcad, "Use Flens must be 0 or 1") ;
             break ;
         }
       }

     status = CAD_ACCEPT ;
     if (pcad->dir == menuDirectiveSTART)
     {
       aoControlMatId++ ;               /* Increment control matrix ID */
       *(long *)pcad->vala = aoControlMatId ;
       *(double *)pcad->valb = guideX ;
       *(double *)pcad->valc = guideY ;
     }
     break;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}


/*+
 *   Function name:
 *   tcsAOselectBsCAD
 *
 *   Purpose:
 *   Implements a simulation of the selectBs AO command 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOselectBsCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Which beam splitter IJHK or LM
 *
 *   EPICS output paramters:
 *      vala => demand beam splitter IJHK or LM
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *
 *-
 */
  
long tcsAOselectBsCAD (struct cadRecord *pcad)
 
{
 
  long status ;           /* Return status */
  static char *bsopts[] = {"IJHK", "LM", NULL} ;
  int bs ;                /* Index of selected beam splitter */
 
/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
 
   case menuDirectivePRESET :
 
     status = CAD_REJECT ;
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;
 
     status = CAD_ACCEPT ;
        
   break ;
 
   case menuDirectiveSTART :
 
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;
}


/*+
 *   Function name:
 *   tcsAOselectCalModeCAD
 *
 *   Purpose:
 *   Implements a simulation of the AO selectCalMode command 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOselectCalModeCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     a => Artificial light source status (ON or OFF)
 *     b => Visual intensity of NGS (%age)
 *     c => Visual intensity of flood source (%age)
 *     d => Visual intensity of LGS source (%age)
 *
 *   EPICS output paramters:
 *     vala => Artificial light source status (ON or OFF)
 *     valb => Visual intensity of NGS (%age)
 *     valc => Visual intensity of flood source (%age)
 *     vald => Visual intensity of LGS source (%age)
 * *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *-
 */
  
long tcsAOselectCalModeCAD (struct cadRecord *pcad)
 
{
 
  long status ;           /* Return status */
  long ngsIntens, floodIntens, lgsIntens;
  int code ;              /* Index of selected calibration mode */
 
/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
   case menuDirectivePRESET :

     status = CAD_REJECT ;
/* Decode artifical star status flag (ON/OFF) */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No ON or OFF given");
       break ;
     }  
     if (tcsDcOnOff (" ", pcad->a, &code, pcad)) break ;
/* Decode visual intensity of NGS */
     if (code == 1)    /* Calibration source(s) ON */
     {
       if (!tcsDcLen(pcad->b)) {
         tcsCsAppendMessage (pcad, "No NGS intens. given");
         break ;
       }  
       if (tcsDcLong ("NGS intensity: ", pcad->b, &ngsIntens, pcad))
         break;
       if (ngsIntens < 0 || ngsIntens > 100) {
           tcsCsAppendMessage (pcad, "NGS intensity invalid") ;
           break ;
       }
/* Decode visual intensity of Flood source */
       if (!tcsDcLen(pcad->c)) {
         tcsCsAppendMessage (pcad, "No Flood intens. given");
         break ;
       }  
       if (tcsDcLong ("Flood intensity: ", pcad->c, &floodIntens, pcad))
         break;
       if (floodIntens < 0 || floodIntens > 100) {
           tcsCsAppendMessage (pcad, "Flood intensity invalid") ;
           break ;
       }
/* Decode visual intensity of NGS */
       if (!tcsDcLen(pcad->d)) {
         tcsCsAppendMessage (pcad, "No LGS intens. given");
         break ;
       }  
       if (tcsDcLong ("LGS intensity: ", pcad->d, &lgsIntens, pcad))
         break;
       if (lgsIntens < 0 || lgsIntens > 100) {
           tcsCsAppendMessage (pcad, "LGS intensity invalid") ;
           break ;
       }
     }
 
     status = CAD_ACCEPT ;       
     break ;
 
   case menuDirectiveSTART :
 
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
     strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
     strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
     strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE) ;
 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;
}

/*+
 *   Function name:
 *   tcsAOflattenCAD
 *
 *   Purpose:
 *   Implements a simulation of the flatten AO command 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOflattenCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *     None
 *
 *   EPICS output parameters:
 *     None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *
 *-
 */
  
long tcsAOflattenCAD (struct cadRecord *pcad)
 
{
 
  long status ;           /* Return status */

/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
 
   case menuDirectivePRESET :
   case menuDirectiveSTART : 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;
}

/*
 *   Function name:
 *   tcsAOstatsCAD
 *
 *   Purpose:
 *   Implements a simulation of the stats AO command 
 *
 *   Description:
 *   The routine simply validates its inputs then performs the necessary
 *   unit conversions before outputting the data.
 *
 *   Invocation:
 *   tcsAOstatsCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *
 *   a => DHS file name
 *   b => Desired number of samples 
 *   c => Desired sample rate
 *   d => Desired trigger times
 *
 *   EPICS output parameters :
 *   vala => DHS file name
 *   valb => Desired number of samples 
 *   valc => Desired sample rate
 *   vald => Desired trigger times
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcdouble        (tcsDecode)      Validate an input double 
 *   tcsCsAppendMessage (tcsCadSupport)  Append string to CAD MESS field
 *   tcsCsCadName       (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN   (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked     (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm  (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsAOstatsCAD (struct cadRecord *pcad)
 
{
  long status ;                            /* Return status */
  double sampleRate, triggerTime ;         /* Input parameter values */
  long numSamp;

/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
    status = CAD_ACCEPT ;

    switch (pcad->dir)
    {
 
     case menuDirectivePRESET :

     status = CAD_REJECT ;

/* First check the DHS file name */
     if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "No DHS filename given");
       break ;
     }
/* Then check the number of samples */
     if (!tcsDcLen(pcad->b)) {
       tcsCsAppendMessage (pcad, "No number of samples given");
       break ;
     }
     if (tcsDcLong ("Number of samples: ", pcad->b, &numSamp, pcad)) break ;
     if (numSamp < 1 )
     {
       tcsCsAppendMessage (pcad, "Number of samples out of range") ;
       break ;
     }
  
/* Then check the requested sample rate */
     if (!tcsDcLen(pcad->c)) {
       tcsCsAppendMessage (pcad, "No sample rate given");
       break ;
     }
     if (tcsDcDouble ("sample rate: ", pcad->c, &sampleRate, pcad)) break ;
     if (sampleRate < 0.0 )
     {
       tcsCsAppendMessage (pcad, "sample rate invalid") ;
       break ;
     }
 
/* Then check the trigger time, if supplied */
     if (tcsDcLen(pcad->d)) {
       if (tcsDcDouble ("sample rate: ", pcad->d, &triggerTime, pcad)) break ;
       if (triggerTime < 0.0 )
       {
         tcsCsAppendMessage (pcad, "Trigger time invalid") ;
         break ;
       }
     }
     status = CAD_ACCEPT ;
     break ;

     case menuDirectiveSTART :
 
       strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE);
       strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE);
       strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE);
       strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE);
       break;
 
     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;
   }
 
   return status ;
}

/*+
 *   Function name:
 *   tcsAOuseLwfsCAD
 *
 *   Purpose:
 *   Implements a simulation of the useLwfs AO command 
 *
 *   Description:
 *   The routine simply validates the input and then writes the data to
 *   the output links.
 *
 *   Invocation:
 *   tcsAOuseLwfsCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Use Laser WFS (ON/OFF)
 *
 *   EPICS output paramters:
 *      vala => Use Laser WFS (ON/OFF)
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsCadName      (tcsCadSupport)  Fetch name of CAD
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *
 *-
 */
  
long tcsAOuseLwfsCAD (struct cadRecord *pcad)
{
 
  long status ;           /* Return status */
  static char *bsopts[] = {"ON", "OFF", NULL} ;  /* Possible state strings */
  int bs ;                /* Index of selected state */
 
/* Set message prefix */
 
  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);
 
  status = CAD_ACCEPT ;
 
  switch (pcad->dir)
  {
 
   case menuDirectivePRESET :
 
     status = CAD_REJECT ;
     if (tcsDcString (bsopts, " ", pcad->a, &bs, pcad)) break ;
 
     status = CAD_ACCEPT ;
        
   break ;
 
   case menuDirectiveSTART :
 
     strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
 
   break ;
 
   case menuDirectiveMARK :
   break ;
 
   case menuDirectiveSTOP :
   break ;
 
   case menuDirectiveCLEAR :
   break ;
 
  }
 
  return status ;

}

/*+
 *   Function name:
 *   tcsAoZernikes
 *
 *   Purpose:
 *   Supply dummy Zernikes when Altair is correcting
 *
 *   Description:
 *   This routine fetches the randomly generated Zernike data created
 *   by the simulator and, if the "correct" command has been given to
 *   Altair outputs them so they can be picked up by the TCS.
 *   A scaled noise signal is added to the data to make it a bit more
 *   realistic ands so the data can be seen to change.
 *
 *   Invocation:
 *   tcsAoZernikes(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub  (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   a => corrections on (= 1) or off (= 0)
 *   b => Simulated tip Z1 (mm)
 *   c => Simulated tilt Z2 (mm)
 *   d => Simulated focus Z3 (mm)
 *   e => Simulated astigmatism Z4/Z5 (mm)
 *   f => Simulated coma Z6/Z7 (mm)
 *   g => Simulated spherical Z8 (mm)
 *   h => Simulated trefoil Z9/Z10 (mm)
 *   i => Simulated Z11/Z12 (mm)
 *   j => Simulated Z13/Z14 (mm)
 *   k => Simulated Z15 (mm)
 *   l => Simulated Z16/Z17 (mm)
 *   m => Simulated Z18/Z19 (mm)
 *   n => Sigma on a 1.0 mm Zernike
 *
 *   Epics outputs:
 *
 *   valj => Array of 40 doubles for TCS
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsAoZernikes(struct genSubRecord *pgsub) 
{
#define ARRMAX4 40

  static double aoData[ARRMAX4] ; /* Output data */
  static long generating = FALSE ; /* Flag to show data is being generated */
  static double aoStartTime ;     /* Start time of data generating */
  long correcting ;
  double Zmean[19] ;              /* Mean Zernike terms */
  double Zerr ;                   /* Noise term */
  double tnow ;                   /* Current time (TAI) */
  double sigma ;                  /* Current error on 1mm Zernike */
  int i ;                         /* Loop counter */
  unsigned long outArraySize;     /* Size of output data array */
  long altairNumZernikes ;        /* No. of Zernikes to output */
  double altairInterval ;         /* How often to output Zernikes (secs) */

/* Fetch all input data from EPICS links */
  correcting = *(long *)pgsub->a ;
  Zmean[0] = *(double *)pgsub->b ;
  Zmean[1] = *(double *)pgsub->c ;
  Zmean[2] = *(double *)pgsub->d ;
  Zmean[3] = *(double *)pgsub->e ;
  Zmean[4] = Zmean[3] ;
  Zmean[5] = *(double *)pgsub->f ;
  Zmean[6] = Zmean[5] ;
  Zmean[7] = *(double *)pgsub->g ;  /* Spherical */
  Zmean[8] = *(double *)pgsub->h ;  /* Trefoil */
  Zmean[9] = Zmean[8] ;
  Zmean[10] = *(double *)pgsub->i ;
  Zmean[11] = Zmean[10] ;
  Zmean[12] = *(double *)pgsub->j ;
  Zmean[13] = Zmean[12] ;
  Zmean[14] = *(double *)pgsub->k ;
  Zmean[15] = *(double *)pgsub->l ;
  Zmean[16] = Zmean[15] ;
  Zmean[17] = *(double *)pgsub->m ;
  Zmean[18] = Zmean[17] ;
  Zerr      = *(double *)pgsub->n ;
  altairNumZernikes = *(long *)pgsub->o ;
  altairInterval    = *(double *)pgsub->p ;

  if (correcting && !generating) {
    generating = TRUE ;
    timeNow(&aoStartTime) ;
  } else if (!correcting) {
    generating = FALSE ;
  }

  if (generating) {
    timeNow(&tnow) ;
    if (tnow - aoStartTime > altairInterval ) {
      aoData[0] = tnow ;
      aoData[1] = (double)altairNumZernikes ;
      sigma = (double)tcsGresid((float)Zerr) ;
      for (i = 2; i < ARRMAX4; i++)
        aoData[i] = 0.0 ;
      for (i = 0; i < altairNumZernikes; i++) {
        aoData[21 + i] = sigma ;
        aoData[2 + i]  = Zmean[i] + aoData[21 + i] ;
      }
      aoStartTime = tnow ;
    }
  }

/* Output data to EPICS */
  outArraySize = pgsub->novj ;
  memcpy (pgsub->valj, aoData, outArraySize * sizeof (double) ) ;

  return 0;

}


/*+
 *   Function name:
 *   tcsAOsetTransform
 *
 *   Purpose:
 *   Set coordinate transformation coefficients for image x,y positions
 *
 *   Description:
 *   The Altair optics distort the image plane when they are inserted into
 *   the beam. The distortion depends also on the orientation and
 *   deployment of the ADC. This routine allows a simulation of these affects
 *   by allowing the user to set the coefficients that determine the 
 *   amount of distortion. At the moment there is no attempt to link
 *   these coefficients to the ADC but it does allow realistic coefficients
 *   to be passed to the TCS.
 *   The coefficients are input in a format that is most intuitive for the 
 *   user but then transformed into 6 affine coefficients. The transformation
 *   is in the sense that map undistorted TCS x,y coords into Altair coords. 
 *   Until the interface is fixed, this routine also provides the focus
 *   offset and tilt coefficients that are used by the TCS to adjust the
 *   focus of the telescope and WFS when Altair is in the beam.
 *
 *   Invocation:
 *   tcsAOsetTransform(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub   (struct gensubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *   a => relative orientation (degs)
 *   b => non-perpendicularity (degs)
 *   c => x scale ;
 *   d => y scale ;
 *   e => x zero point ;
 *   f => y zero point ;
 *   g => focus shift (mm)
 *   h => X focus tilt
 *   i => Y focus tilt
 *   j => trigger to cause the record to process
 *
 *   Epics outputs:
 *   vala => array of focus coefficients
 *   valj => array of affine coefficients to map TCS coords to Altair coords
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsAOsetTransform (struct genSubRecord *pgsub) 
{

  double orient ;             /* Relative orientation (rads) */
  double nonperp ;            /* Non perpendicularity (degs) */
  double xscale, yscale ;     /* Scales in x and y */
  double xzero, yzero ;       /* Zero points in x and y */

  double zzero ;              /* Focus offset (mm) */
  double zxtilt, zytilt ;     /* Tilt of focal plane (mm / mm) */
  double costh, sinth ;       /* cos/sine of orientation */
  double cosp2, sinp2 ;       /* cos/sine of non-perp semi-angle */
  double Acoeff, Bcoeff ;
  double Ccoeff, Dcoeff ;     /* Intermediate variables */

/* Read in all user data. Note there is no check on the validity. This is
*  assumed done at the EPICS level.
*/
  orient  = *(double *)pgsub->a * D2R ;
  nonperp = *(double *)pgsub->b * D2R ;
  xscale  = *(double *)pgsub->c ;
  yscale  = *(double *)pgsub->d ;
  xzero   = *(double *)pgsub->e ;
  yzero   = *(double *)pgsub->f ;

  zzero   = *(double *)pgsub->g ;
  zxtilt  = *(double *)pgsub->h ;
  zytilt  = *(double *)pgsub->i ;

/* Convert these numbers into the corresponding affine connection coeffs */
  costh = cos(orient) ;
  sinth = sin(orient) ;
  cosp2 = cos(nonperp/2) ;
  sinp2 = sin(nonperp/2) ;
  Acoeff = costh * cosp2 + sinth * sinp2 ;
  Bcoeff = costh * sinp2 + sinth * cosp2 ;
  Ccoeff = costh * sinp2 - sinth * cosp2 ;
  Dcoeff = costh * cosp2 - sinth * sinp2 ;

  aoSimt2a[1] = Acoeff * xscale ;
  aoSimt2a[2] = Bcoeff * yscale ;
  aoSimt2a[0] = aoSimt2a[1] * xzero + aoSimt2a[2] * yzero ;
  aoSimt2a[4] = Ccoeff * xscale ;
  aoSimt2a[5] = Dcoeff * yscale ;
  aoSimt2a[3] = aoSimt2a[4] * xzero + aoSimt2a[5] * yzero ;

  if (xscale < 0.0) {
    aoSimt2a[2] = -aoSimt2a[2];
    aoSimt2a[4] = -aoSimt2a[4];
  }

  aoFocusCoeffs[0] = zzero ;
  aoFocusCoeffs[1] = zxtilt ;
  aoFocusCoeffs[2] = zytilt ;

/* Output them ready for the the TCS */
  memcpy (pgsub->vala, aoFocusCoeffs, 3 * sizeof(double)) ;
  memcpy (pgsub->valj, aoSimt2a, 6* sizeof(double)) ;

  return 0 ;

}

/*
 *   Function name:
 *   tcsAOstrapCorrCtlCAD
 *
 *   Purpose:
 *   Emulate the strapCorrCtl command
 *
 *   Description:
 *   Simply check the input for validity. Currently no part of
 *   the simulator is affected by whether the STRAP correction
 *   is on or off
 *
 *   Invocation:
 *   tcsAOstrapCorrCtlCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters :
 *   a => Correction control flag (0/1)
 *
 *   EPICS outputs:
 *   vala => 0 = off, 1 = on
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *-
 */
long tcsAOstrapCorrCtlCAD (struct cadRecord *pcad)
{
  long status ;                            /* Return status */
  static long corrCtlFlag ;
  
/* Set message prefix */
   tcsCsSetMessageN(pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT ;
    switch (pcad->dir) 
    {

     case menuDirectivePRESET :

        status = CAD_REJECT ;
/* Decode correction control flag */
        if (!tcsDcLen(pcad->a)) {
          tcsCsAppendMessage (pcad, "No flag");
          break ;
        }  
        if (tcsDcLong ("Flag: ", pcad->a, &corrCtlFlag, pcad))
          break;
        if (corrCtlFlag < 0 || corrCtlFlag > 1) {
            tcsCsAppendMessage (pcad, "Invalid flag") ;
            break ;
        }

      status = CAD_ACCEPT;
      break;

     case menuDirectiveSTART :
      *(long *)pcad->vala = corrCtlFlag ;

     case menuDirectiveMARK:
     case menuDirectiveCLEAR:
     case menuDirectiveSTOP:
     break;

     default:
     strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
     status = CAD_REJECT;
     break;
   }

   return status ;
}

epicsRegisterFunction(tcsAOuseLwfsCAD);
epicsRegisterFunction(tcsAosComplete);
epicsRegisterFunction(tcsAOselectCalModeCAD);
epicsRegisterFunction(tcsAoGenericCAD);
epicsRegisterFunction(tcsAoMoveCAD);
epicsRegisterFunction(tcsAOselectBsCAD);
epicsRegisterFunction(tcsAoFollowCAD);
epicsRegisterFunction(tcsAOsetTransform);
epicsRegisterFunction(tcsAOlgsirisCAD);
epicsRegisterFunction(tcsAOentShutterCAD);
epicsRegisterFunction(tcsAOlgsttSourceCAD);
epicsRegisterFunction(tcsAOmoveAdcCAD);
epicsRegisterFunction(tcsAoStop);
epicsRegisterFunction(tcsAOncpaCAD);
epicsRegisterFunction(tcsAOoiwfsSourceCAD);
epicsRegisterFunction(tcsAoZernikes);
epicsRegisterFunction(tcsAOcorrectCAD);
epicsRegisterFunction(tcsAOcentreWfsCAD);
epicsRegisterFunction(tcsAOstatsCAD);
epicsRegisterFunction(tcsAosSimulate);
epicsRegisterFunction(tcsAOmoveAStarCAD);
epicsRegisterFunction(tcsAOngsNDfiltCAD);
epicsRegisterFunction(tcsAOprepareCmCAD);
epicsRegisterFunction(tcsAOlgsNDfiltCAD);
epicsRegisterFunction(tcsAOstrapCorrCtlCAD);
epicsRegisterFunction(tcsAOdeployAdcCAD);
epicsRegisterFunction(tcsAOexitShutterCAD);
epicsRegisterFunction(tcsAOflattenCAD);
