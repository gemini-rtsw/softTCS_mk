/*
   *   FILENAME
   *   tcsAomSimulation.c
   *
   *   This module holds the routines that are used in the AOM Simulation 
   *
   *   FUNCTION NAME(S)
   *   tcsAomGenericCAD - general purpose CAD routine
   *   tcsAomCtrlCAD    - simple implementation of the probe Ctrl commands
   *   tcsAomMoveCAD    - implements the move command for each probe
   *   tcsAomSimulation - servo simulation of probes
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsAomSimulation.c,v $
 * Revision 1.1  2007/12/18 10:05:42  cjm
 * Initial simulator code for AOM
 *
 */
/* *INDENT-ON* */



#include <string.h>
#include <epicsStdioRedirect.h>
#include <math.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>
#include <dbCommon.h>
#include <recSup.h>

#include "tcsAom.h"
#include "tcsConstants.h"
#include "slalib.h"
#include "tcsServo.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "timeLib.h"
#include "tcsRandom.h"

/* Guide probe limits (mm) */
#define MAXRAD 41.0
#define MAXXPR1 15.0
#define MINXPR2 -15.0

/* Guide probe states */
static int StateProbe[3];

/* probe position (3 guide probes ) */ 

static double x[3];
static double y[3];

/* Demand position from MOVE command (3 guide probes). 
*/

static double xtarget[3];
static double ytarget[3];

/* Target position in focal plane (mm for all probes) */
static double xftarget[3];
static double yftarget[3];

/* Default transformation coefficients for OIWFS */
static double tcs2oiwfs[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 1.0} ;
                                  
/*+
 *   Function name:
 *   tcsAomInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the AOM control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the AOM control system.
 *
 *   Invocation:
 *   tcsAomInit()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      None
 *
 *   Function value:
 *      None
 * 
 *   Prior requirements:
 *   None
 *
 *-
 */

void tcsAomInit(void)
{
    static int first = TRUE;
    int i;

    if (first)
        first = FALSE;
    for (i = 0; i < 3; i++) {
        StateProbe[i] = STOPPED;
    }
}

/*+
 *   Function name:
 *   tcsAomFollowCAD
 *
 *   Purpose:
 *   Implement the follow CAD record in the AOM simulator
 *
 *   Description:
 *   This function implements the follow CAD record in the AOM simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. Since all the 
 *   data is being transmitted to separate records the function of this
 *   routine is simply to set some internal flags that signal the internal
 *   state of the simulator to other pieces of code.
 *
 *   Invocation:
 *   tcsAomFollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */

long tcsAomFollowCAD(struct cadRecord *pcad)
{
  static long iprobe;
  long status ;

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;

  switch (pcad->dir) {
  case menuDirectivePRESET:
    if (tcsDcLong ("probe: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 3) {
      tcsCsAppendMessage (pcad, "number out of range") ;
      break ;
    }
    iprobe-- ;
    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART:
    StateProbe[iprobe] = FOLLOWING;
    strcpy(pcad->vala, "ON");
    status = CAD_ACCEPT ;
    break;          

  case menuDirectiveSTOP:
    if (tcsDcLong ("probe: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 3) {
      tcsCsAppendMessage (pcad, "number out of range") ;
      break ;
    }
    iprobe--;
    StateProbe[iprobe] = STOPPED;
    strcpy(pcad->vala, "OFF");
    break ;

  default:
      break;
  }

  return status ;
}

/*+
 *   Function name:
 *   tcsAomMoveCAD
 *
 *   Purpose:
 *   Implement the Move CAD record in the AOM simulator
 *
 *   Description:
 *   This function implements the move CAD record in the AOM simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. 
 *
 *   Epics inputs :
 *
 *   a => X position
 *   b => Y position
 *   d => probe number
 *
 *   Invocation:
 *   tcsAomMoveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<) status  (long)  return status, 0 = OK
 *
 *-
 */

long tcsAomMoveCAD(struct cadRecord *pcad)
{
  static double xin[3], yin[3];
  long iprobe ;                  /* Probe number 1 to 3 initially */
  long status ;
  double radius ;

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;
    
  switch (pcad->dir) {
    case menuDirectivePRESET:
      if (tcsDcLong("Probe: ", pcad->d, &iprobe, pcad) ) break ;
      if (iprobe < 1 || iprobe > 3) {
        tcsCsAppendMessage (pcad, "number out of range") ;
        break ;
      } 

      iprobe-- ;

      if (tcsDcDouble("x: ", pcad->a, &xin[iprobe], pcad) ) break ;
      if (xin[iprobe] < -MAXRAD || xin[iprobe] > MAXRAD) {
        tcsCsAppendMessage (pcad, "max X exceeded") ;
        break ;
      }
      if (tcsDcDouble("y: ", pcad->b, &yin[iprobe], pcad) ) break ;
      if (yin[iprobe] < -MAXRAD || yin[iprobe] > MAXRAD) {
        tcsCsAppendMessage (pcad, "max Y exceeded") ;
        break ;
      }

      radius = sqrt(yin[iprobe]*yin[iprobe] + xin[iprobe]*xin[iprobe]);
      if (radius > MAXRAD) {
        tcsCsAppendMessage (pcad, "max radius exceeded") ;
        break ;
      } 
      if (iprobe == 0) {
        if (xin[iprobe] > MAXXPR1) {
          tcsCsAppendMessage (pcad, "Probe 1: x > 15.0") ;
          break ;
        }
      }
      if (iprobe == 1) {
        if (xin[iprobe] < MINXPR2) {
          tcsCsAppendMessage (pcad, "Probe 2: x < -15.0") ;
          break ;
        }
      }
      status = CAD_ACCEPT ;
      break ;

    case menuDirectiveSTART:
      if (tcsDcLong("Probe: ", pcad->d, &iprobe, pcad) ) break ;
      if (iprobe < 1 || iprobe > 3) {
        tcsCsAppendMessage (pcad, "number out of range") ;
        break ;
      } 

      iprobe-- ;
      xftarget[iprobe] = xin[iprobe];
      yftarget[iprobe] = yin[iprobe];
      xtarget[iprobe] = xin[iprobe] ;
      ytarget[iprobe] = yin[iprobe] ;
      StateProbe[iprobe] = MOVING;
      strcpy(pcad->vala, "OFF");         /* Set follow mode off  */
      status = CAD_ACCEPT ;

      break;                

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */

    case menuDirectiveSTOP:
      if (tcsDcLong("Probe: ", pcad->d, &iprobe, pcad) ) break ;
      if (iprobe < 1 || iprobe > 3) {
        tcsCsAppendMessage (pcad, "number out of range") ;
        break ;
      } 

      strcpy(pcad->vala, "OFF");
      break;

    default:
        break;
    }

    return status ;

}


/*+
 *   Function name:
 *   tcsAomSimulate
 *
 *   Purpose:
 *   Simulates behaviour of the AOM without any hardware
 *
 *   Description:
 *   This routine is linked to the tcsAomSimulate record and performs the main
 *   simulation of the AOM. It was based on the simulation used for
 *   the A&G probes 
 *
 *   Inputs :
 *
 *   b => probe number
 *   d => default startup x position (mm or degs)
 *   f => default startup y position (mm or degs)
 *   h => default startup z position (mm)
 *   l => maximum probe velocity
 *   n => X and Y position tolerances
 *   o => Z position tolerance
 *   j => Input demand array from TCS:
 *    Element 0  = Time now
 *    Element 1  = Target time
 *    Element 2  = Track identifier
 *    Element 3  = Demanded X position 
 *    Element 4  = Demanded Y position 
 *    Element 5  = Demanded Z position 
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
 *   valh => X and Y tolerance (mm)
 *   vali => Z tolerance (mm)
 *   valh => status
 *   vali => trackid
 *   valj => disable or enable following processing chain
 *   valk => in position flag
 *   vall => RT angle
 *   valm => PA angle
 *   valn => Quality of stream of input demands
 *
 *   Invocation:
 *   tcsAomSimulate(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Deficiencies:
 *   The calculations assume the record is being scanned at 20Hz (through a
 *   constant DT). It should fetch the scan rate from the .SCAN field
 *
 *-
 */

long tcsAomSimulate(struct genSubRecord *pgsub)
{
    static int count[3] =
    {0, 0, 0};

    static int first[3] =
    {TRUE, TRUE, TRUE};
    static int substat[3];      /* subsystem status */
    static double trackid[3];   /* current track id */

    int iprobe;                 /* probe number */
    double now;                 /* current time */
    unsigned long arraySize;    /* number of elements in inout demand array */
    double AOMdemand[5];        /* demand data array from kernel */
    double xdemand ;            /* Follow x demand */
    double ydemand ;            /* Follow y demand */
    double xft, yft ;           /* Targets in mm for probe 1 and 2 */
    double xnow, ynow;          /* X,Y servo demands */
    double xdemandv, ydemandv;  /* X,Y demand velocity */
    double newtrack;            /* track id of demand */
    int newstat;                /* new subsystem status */
    int stateProbe[3];          /* local copy of probe states */
    int linkSelect;             /* Mask for downstream processing */
    double xfplane, yfplane ;   /* Probe position in focal plane (mm) */
    double xferr, yferr ;       /* x,y errors in focal plane */
    char arrayS[20] ;           /* State of incoming data */

    double tappl;               /* time for which demands are correct */
    static int inPositionX[3];         /* X now in position flag */
    static int inPositionY[3];         /* Y now in position flag */
    static int inPosition[3] =  {FALSE, FALSE, FALSE };  
    static double tlast[3];     /* Time at last entry */
    static double xlast[3];     /* Previous X demands */
    static double ylast[3];     /* Previous Y demands */
    static double xvel[3];      /* Current X probe velocity */
    static double yvel[3];      /* Current Y probe velocity */
    static double xerr[3];      /* Current X position error */
    static double yerr[3];      /* Current Y position error */

    static struct ServoState servoStateX[3];
    static struct ServoState servoStateY[3];
    static struct ServoConfig servoConfigX[3];
    static struct ServoConfig servoConfigY[3];

    count[0]++;
    count[1]++;
    count[2]++;

/*  Get probe number */
    iprobe = floor(*(double *) pgsub->b);
    iprobe--;

/*   Get a local copy of the probe state as the global values may get changed
   from elsewhere */
    stateProbe[iprobe] = StateProbe[iprobe];

    if (first[iprobe]) {

/* Set servo initial values */
        servoConfigX[iprobe].dvmax = 12.5;
        servoConfigX[iprobe].gs = 4.0;
        servoConfigX[iprobe].gp = 1.0;
        servoConfigX[iprobe].gi = 0.1;
        servoConfigX[iprobe].pi = 1.0;
        servoConfigX[iprobe].tok = 0.5;
        servoStateX[iprobe].pdtold = *(double *) pgsub->d;
        servoConfigX[iprobe].noise = 0.0;
        timeNow(&(servoStateX[iprobe].told));
        servoStateX[iprobe].told -= 0.05;
        servoStateX[iprobe].tout = servoStateX[iprobe].told;
        servoStateX[iprobe].vd = 0.0;
        servoStateX[iprobe].accum = 0.0;
        x[iprobe] = servoStateX[iprobe].pdtold;
        xvel[iprobe] = 0.0;
        servoConfigY[iprobe].dvmax = 12.5;
        servoConfigY[iprobe].gs = 1.0;
        servoConfigY[iprobe].gp = 1.5;
        servoConfigY[iprobe].gi = 0.7;
        servoConfigY[iprobe].pi = 0.5;
        servoConfigY[iprobe].tok = 0.5;
        servoStateY[iprobe].pdtold = *(double *) pgsub->f;
        servoConfigY[iprobe].noise = 0.0;
        timeNow(&(servoStateY[iprobe].told));
        servoStateY[iprobe].told -= 0.05;
        servoStateY[iprobe].tout = servoStateY[iprobe].told;
        servoStateY[iprobe].vd = 0.0;
        servoStateY[iprobe].accum = 0.0;
        y[iprobe] = servoStateY[iprobe].pdtold;
        yvel[iprobe] = 0.0;

        newstat = menuCarstatesIDLE;
        substat[iprobe] = -1;
        trackid[iprobe] = 0.0;
        first[iprobe] = FALSE;
    }
/* fetch latest velocities & tolerances */
    servoConfigX[iprobe].vtmax = *(double *) pgsub->l;
    servoConfigY[iprobe].vtmax = *(double *) pgsub->l;
    servoConfigX[iprobe].pok   = *(double *) pgsub->n;
    servoConfigY[iprobe].pok   = *(double *) pgsub->n;

/* Get demand data array */
    arraySize = pgsub->noj;
    memcpy(AOMdemand, pgsub->j, arraySize * sizeof(double));
    tappl = AOMdemand[1];
    newtrack = AOMdemand[2];
    xdemand  = AOMdemand[3] ;
    ydemand  = AOMdemand[4] ;

    strcpy(arrayS, "GOOD") ;

/* send demands to servo. */
    timeNow(&now);

/* Initialise demand velocities to 0.0. This was found to be neccesary if
*  the optimiser was used. Without it the probes would exhibit ocillatory
*  behaviour.
*/
    xdemandv = 0.0;
    ydemandv = 0.0;

    if (stateProbe[iprobe] == MOVING) {
      xnow = xtarget[iprobe] ;
      xft  = xftarget[iprobe] ;
      inPositionX[iprobe] = tcsServo(now, xnow, 0, &servoConfigX[iprobe],
                        &servoStateX[iprobe], &x[iprobe], &xvel[iprobe]);
      xerr[iprobe] = xnow - x[iprobe];

      ynow = ytarget[iprobe] ;
      yft  = yftarget[iprobe] ;
      inPositionY[iprobe] = tcsServo(now, ynow, 0, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
      yerr[iprobe] = ynow - y[iprobe];


    } else if (stateProbe[iprobe] == FOLLOWING) {
        if (tappl > tlast[iprobe]) {
            xdemandv = (xdemand - xlast[iprobe]) / (tappl - tlast[iprobe]);
            ydemandv = (ydemand - ylast[iprobe]) / (tappl - tlast[iprobe]);
        }
        xnow = xdemand + xdemandv * (now - tappl);
        xft  = AOMdemand[3] ;
   
        inPositionX[iprobe] = tcsServo(tappl, xnow, 0, &servoConfigX[iprobe],
                               &servoStateX[iprobe],
                               &x[iprobe], &xvel[iprobe]);
        xerr[iprobe] = xnow - x[iprobe];

        ynow = ydemand + ydemandv * (now - tappl);
        yft  = AOMdemand[4] ;
        inPositionY[iprobe] = tcsServo(tappl, ynow, 0, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
        yerr[iprobe] = ynow - y[iprobe];

    } else {
        inPositionX[iprobe] = tcsServo(now, x[iprobe], 1, &servoConfigX[iprobe],
                        &servoStateX[iprobe], &x[iprobe], &xvel[iprobe]);
        xerr[iprobe] = 0.0;
        inPositionY[iprobe] = tcsServo(now, y[iprobe], 1, &servoConfigY[iprobe],
                        &servoStateY[iprobe], &y[iprobe], &yvel[iprobe]);
        yerr[iprobe] = 0.0;
        xft = yft = 0.0; /* Not used for STOPPEd state but prevents warnings */
    }

    inPosition[iprobe] = inPositionX[iprobe] && inPositionY[iprobe] ;

/* Round values to nearest micron */
    x[iprobe] = (floor(((1000.0 * x[iprobe])) + 0.5)) / 1000.0;
    y[iprobe] = (floor(((1000.0 * y[iprobe])) + 0.5)) / 1000.0;

/* Initialise the link selection field. The bits in this field 
   are as follows :
     Bit 0 = Process completion record
     Bit 1 = Process CAR record
     Bit 2 = Process trackId record */
    linkSelect = 0;

/* Determine new subsystem state. To be 'all in position', 
   X, Y and Z must be in position 10x in successive calls */     

        if (inPosition[iprobe]) 
          {
          newstat = menuCarstatesIDLE;
 /* If not following, set to STOPPED */
          if (stateProbe[iprobe] == MOVING || stateProbe[iprobe] == STOPPING)
             {
              StateProbe[iprobe] = STOPPED ;
              linkSelect += 1;     /* Trigger record 'complete' */
             }
 /* If not following, set to STOPPED */
          } 
        else
/* Not in position */
          newstat = menuCarstatesBUSY;


/* Set the link selection field and update the subsystem state */

    if (newstat != substat[iprobe]) {
        substat[iprobe] = newstat;
        linkSelect += 2;           /* Trigger update of CAR record */
    }
    if (newtrack != trackid[iprobe]) {
        trackid[iprobe] = newtrack;
        inPosition[iprobe] = FALSE;
        linkSelect += 4;           /* Trigger update of trackId record */
    }

/* save demands */
    tlast[iprobe] = tappl;
    xlast[iprobe] = xdemand;
    ylast[iprobe] = ydemand;

    xfplane = x[iprobe] ;
    yfplane = y[iprobe] ;
    xferr   = xerr[iprobe] ;
    yferr   = yerr[iprobe] ;

/* now output the results */
    *(double *) pgsub->vala = tappl;
    *(double *) pgsub->valb = xfplane;
    *(double *) pgsub->valc = yfplane;
    *(double *) pgsub->vale = xferr;
    *(double *) pgsub->valf = yferr;
    *(double *) pgsub->valh = substat[iprobe];
    *(double *) pgsub->vali = trackid[iprobe];
    *(long *) pgsub->valj = linkSelect;
    *(long *) pgsub->valk = inPosition[iprobe];
    strcpy (pgsub->valn, arrayS) ;

    return 0;
}

/*+
 *   Function name:
 *   tcsAomComplete
 *
 *   Purpose:
 *   Signal complete of a move command
 *
 *   Description:
 *   Signals completion of a move command by writing IDLE to the appropriate
 *   CAR record.
 *
 *   Invocation:
 *   tcsAomComplete(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub    (genSubRecord *) pointer to genSub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAomComplete(genSubRecord *psub)
{

/* output values for CAR Message and State fields */
    strcpy(psub->valb, "Stopped");
    *(double *)psub->vala = menuCarstatesIDLE;
    return 0;
}

/*+
 *   Function name:
 *   tcsAgsOiwfsCoeffs
 *
 *   Purpose:
 *   Output transformation coefficients to EPICS
 *
 *   Description:
 *   Write the appropriate transformation coefficients to VALJ.
 *   A set of parameters can be input in user coordinates e.g. orientation
 *   xscale etc. and these are transformed into a set of 6 affine
 *   coefficients that can be passed to the TCS
 *
 *   Invocation:
 *   tcsAgsOiwfsCoeffs(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (genSubRecord *) pointer to genSub structure
 *
 *   Epics inputs:
 *  
 *   a => relative orientation (degs)
 *   b => non-perpendicularity (degs)
 *   c => x scale ;
 *   d => y scale ;
 *   e => x zero point ;
 *   f => y zero point ;
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAomOiwfsCoeffs(genSubRecord *pgsub)
{

  double orient ;             /* Relative orientation (rads) */
  double nonperp ;            /* Non perpendicularity (degs) */
  double xscale, yscale ;     /* Scales in x and y */
  double xzero, yzero ;       /* Zero points in x and y */

  double costh, sinth ;       /* cos/sine of orientation */
  double cosp2, sinp2 ;       /* cos/sine of non-perp semi-angle */
  double Acoeff, Bcoeff ;
  double Ccoeff, Dcoeff ;     /* Intermediate variables */

  double localo2t[6] ;        /* Local copy of oiwfs to tcs params */
  double localt2o[6] ;        /* Local copy of tcs to oiwfs params */

  int jstat ;                 /* Status from inversion */
  int i ;                     /* Loop counter */

/* Read in all user data. Note there is no check on the validity. This is
*  assumed done at the EPICS level.
*/
  orient = *(double *)pgsub->a * D2R ;
  nonperp = *(double *)pgsub->b * D2R ;
  xscale  = *(double *)pgsub->c ;
  yscale  = *(double *)pgsub->d ;
  xzero   = *(double *)pgsub->e ;
  yzero   = *(double *)pgsub->f ;

/* Convert these numbers into the corresponding affine connection coeffs */
  costh = cos(orient) ;
  sinth = sin(orient) ;
  cosp2 = cos(nonperp/2) ;
  sinp2 = sin(nonperp/2) ;
  Acoeff = costh * cosp2 + sinth * sinp2 ;
  Bcoeff = costh * sinp2 + sinth * cosp2 ;
  Ccoeff = costh * sinp2 - sinth * cosp2 ;
  Dcoeff = costh * cosp2 - sinth * sinp2 ;

  localo2t[1] = Acoeff * xscale ;
  localo2t[2] = Bcoeff * yscale ;
  localo2t[0] = localo2t[1] * xzero + localo2t[2] * yzero ;
  localo2t[4] = Ccoeff * xscale ;
  localo2t[5] = Dcoeff * yscale ;
  localo2t[3] = localo2t[4] * xzero + localo2t[5] * yzero ;

  if (xscale < 0.0) {
    localo2t[2] = -localo2t[2] ;
    localo2t[4] = -localo2t[4] ;
  }

/* Invert the transformation */
  slaInvf (localo2t, localt2o, &jstat) ;

/* If inversion was successful then we have a valid set of coefficients to
*  transform OIWFS coords to TCS and vice versa so store these away for
*  later use
*/

  if (jstat == 0) {
    for (i = 0; i < 6 ; i++) {
      tcs2oiwfs[i] = localt2o[i] ;
    }
  }

  memcpy (pgsub->valj, tcs2oiwfs, 6 * sizeof(double)) ;

  return 0;
}

/*+
 *   Function name:
 *   tcsAgStopCAD
 *
 *   Purpose:
 *   CAD to stop specified A&G probe
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAgStopCAD
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
 *-
 */

long tcsAomStopCAD(struct cadRecord *pcad)
{
    int nitem ;
    int iprobe = 0;

/* CAD directive is in field DIR */
    switch (pcad->dir) 
    {
    case menuDirectiveSTART:
    case menuDirectivePRESET:
        strcpy(pcad->mess, "Stop: argument is valid");
        nitem = sscanf(pcad->a, "%d ", &iprobe);
        if (nitem < 1 || iprobe < 0 || iprobe > 3) 
            {
              strcpy(pcad->mess, "Stop: probe number out of range");
              return CAD_REJECT;
            } 
        if (pcad->dir == menuDirectiveSTART)
          {
          if (iprobe == 0) 
             {
              StateProbe[0] = STOPPED ;
              StateProbe[1] = STOPPED ;
              StateProbe[2] = STOPPED ;
             } 
             else 
              StateProbe[--iprobe] = STOPPED ;
          }

/* Output acceptance message */
       strcpy(pcad->mess, "Command accepted");
       strncpy(pcad->vala, "OFF", 3);
       return CAD_ACCEPT;
       break;              /* End menuDirectiveSTART or menuDirectivePRESET */

       case menuDirectiveMARK:
       case menuDirectiveCLEAR:
       case menuDirectiveSTOP:
       break;

       default:
       strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
       return CAD_REJECT;
       break;
    }

    return CAD_ACCEPT ;
}


/*+
 *   Function name:
 *   tcsAomStop
 *
 *   Purpose:
 *   gensub to stop all A&G probes
 *
 *   Invocation:
 *   tcsAgStop
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to pgsub structure
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

long tcsAomStop(struct genSubRecord *pgsub)
{
    StateProbe[0] = STOPPED;
    StateProbe[1] = STOPPED;
    StateProbe[2] = STOPPED;
    strncpy(pgsub->vala, "OFF", 3);
    strncpy(pgsub->valb, "OFF", 3);
    strncpy(pgsub->valc, "OFF", 3);
    return (0);
}



/*+
 *   Function name:
 *   tcsAomGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the AOM 
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAomGenericCAD(pcad)
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

long tcsAomGenericCAD(struct cadRecord *pcad)
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
        sprintf(pcad->mess, "AOM: %.13s started", command);

        /* If its a STOP command, output the following flag value (zero) */
        if (strncmp(command, "stop", 4) == 0)
            strcpy(pcad->vala, "OFF");
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
 *   tcsAomCtrlCAD
 *
 *   Purpose:
 *   Implement the NGS probe Ctrl command
 *
 *   Description:
 *
 *   Invocation:
 *   tcsAomCtrlCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Epics inputs:
 *   a => The control command, Datum, Park, Init or Test
 *
 *   Epics outputs:
 *   vala => Index of the control command (1 .. 4)
 *   valb => X park position of probe
 *   valc => Y park position of probe
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsAomCtrlCAD(struct cadRecord *pcad)
{
    int status;                 /* return status */
    static char *ctrlOpts [] = {"DATUM", "PARK", "INIT", "TEST", NULL};
    static int ctrlIndex ;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL);

    status = CAD_ACCEPT;

    switch (pcad->dir) {

    case menuDirectivePRESET:
      status = CAD_REJECT;

      if (tcsDcString(ctrlOpts, " ", pcad->a, &ctrlIndex, pcad)) break;
      status = CAD_ACCEPT;
      break ;

    case menuDirectiveSTART:

      *(long *)pcad->vala = ctrlIndex + 1;
      strcpy(pcad->valb, pcad->b);
      strcpy(pcad->valc, pcad->c);

      status = CAD_ACCEPT;
      break;

    default:
      break;
    }
    return (status);
}

epicsRegisterFunction(tcsAomMoveCAD);
epicsRegisterFunction(tcsAomCtrlCAD);
epicsRegisterFunction(tcsAomSimulate);
epicsRegisterFunction(tcsAomGenericCAD);
epicsRegisterFunction(tcsAomFollowCAD);
epicsRegisterFunction(tcsAomStop);
epicsRegisterFunction(tcsAomStopCAD);
