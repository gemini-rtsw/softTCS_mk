/*
   *   FILENAME
   *   tcsGsaoiSimulation.c
   *
   *   This module holds the routines that are used in the GSAOI Simulation 
   *
   *   FUNCTION NAME(S)
   *   tcsGemsRotCorrections - simulate a constant rotator error
   *   tcsGemsZernikes    - provide simulated Zernkes for M1
   *   tcsGsaoiGenericCAD - general purpose CAD routine
   *   tcsGsaoidataODGWCAD   - implementation of the dataODGW command
   *   tcsGsaoiseqODGWCAD   - implementation of the seqODGW command
   *   tcsGsaoiStop - stop all ODGW
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsGsaoiSimulation.c,v $
 * Revision 1.7  2010/12/03 14:06:03  cjm
 * Fix typo
 *
 * Revision 1.6  2010/05/27 07:27:59  cjm
 * Output to vald & valh
 *
 * Revision 1.5  2010/02/26 18:53:04  gemvx
 * Emulate the latest GSAOI commands
 *
 * Revision 1.4  2009/12/01 13:49:49  cjm
 * Add simulations for Zernikes, rotator corrections and setup command
 *
 * Revision 1.3  2009/11/02 16:38:01  cjm
 * Make sure id doesn't change when not guiding
 *
 * Revision 1.2  2009/10/30 17:21:40  cjm
 * Add routine to generate rotator guide corrections
 *
 * Revision 1.1  2007/12/18 10:07:08  cjm
 * Basic GSAOI simulator
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

#include "tcsGsaoi.h"
#include "tcsConstants.h"
#include "slalib.h"
#include "tcsServo.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "timeLib.h"
#include "tcsRandom.h"

/* Guide window states */
static int StateProbe[4];

/*+
 *   Function name:
 *   tcsGsaoiInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the GSAOI control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the GSAOI control system.
 *
 *   Invocation:
 *   tcsGsaoiInit()
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

void tcsGsaoiInit(void)
{
    static int first = TRUE;
    int i;

    if (first)
        first = FALSE;
    for (i = 0; i < 4; i++) {
        StateProbe[i] = STOPPED;
    }
}

/*+
 *   Function name:
 *   tcsGsaoiFollowCAD
 *
 *   Purpose:
 *   Implement the follow CAD record in the GSAOI simulator
 *
 *   Description:
 *   This function implements the follow CAD record in the GSAOI simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. Since all the 
 *   data is being transmitted to separate records the function of this
 *   routine is simply to set some internal flags that signal the internal
 *   state of the simulator to other pieces of code.
 *
 *   Invocation:
 *   tcsGsaoiFollowCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 *
 *-
 */

long tcsGsaoiFollowCAD(struct cadRecord *pcad)
{
  static long iprobe;
  long status ;

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;

  switch (pcad->dir) {
  case menuDirectivePRESET:
    if (tcsDcLong ("window: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 4) {
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
    if (tcsDcLong ("window: ", pcad->a, &iprobe, pcad)) break ;
    if (iprobe < 1 || iprobe > 4) {
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
 *   tcsGsaoiGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the GSAOI 
 *
 *   Description:
 *
 *   Invocation:
 *   tcsgsaoiGenericCAD(pcad)
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

long tcsGsaoiGenericCAD(struct cadRecord *pcad)
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
        sprintf(pcad->mess, "GSAOI: %.13s started", command);

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
 *   tcsGsaoidataODGWCAD
 *
 *   Purpose:
 *   Minimal implementation of the GSAOI dataODGW command.
 *
 *   Description:
 *   This command is a minimal implementation of GSAOI's dataODGW.
 *   Currently it simply copies some inputs to outputs so they
 *   can be passed on to the records that the TCS reads.
 *   There is no checking of validity and the command is 
 *   always accepted.
 *   This command and seqODGW essentially replace the earlier
 *   GSAOI setup command
 *
 *   Invocation:
 *   tcsGsaoidataODGWCAD(pcad)
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

long tcsGsaoidataODGWCAD(struct cadRecord *pcad)
{
  int status;                 /* return status */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;
   
  switch (pcad->dir) {
    case menuDirectivePRESET:

      status = CAD_ACCEPT;
      break ;

    case menuDirectiveSTART:

/* Copy over the parameters to the output fields */

      strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
      strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
      strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
      strncpy(pcad->vald, pcad->d, MAX_STRING_SIZE) ;
      strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
      strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
      strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
      strncpy(pcad->valh, pcad->h, MAX_STRING_SIZE) ;
      strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
      strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;
      strncpy(pcad->valk, pcad->k, MAX_STRING_SIZE) ;
      strncpy(pcad->valm, pcad->m, MAX_STRING_SIZE) ;

      status = CAD_ACCEPT;
      break;

    default:
      status = CAD_ACCEPT;
      break;
  }
  return (status);
}

/*+
 *   Function name:
 *   tcsGsaoiseqODGWCAD
 *
 *   Purpose:
 *   Minimal implementation of the GSAOI seqODGW command.
 *
 *   Description:
 *   The command simply copies the inputs to the outputs for
 *   use by the downstream processing. No checks are made
 *   on the validity of the data passed.
 *
 *   Invocation:
 *   tcsGsaoiseqODGWCAD(pcad)
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

long tcsGsaoiseqODGWCAD(struct cadRecord *pcad)
{
  int status;                 /* return status */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *)NULL) ;

  status = CAD_REJECT ;
   
  switch (pcad->dir) {
    case menuDirectivePRESET:

      status = CAD_ACCEPT;
      break ;

    case menuDirectiveSTART:

/* Copy over the parameters to the output fields */

      strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE) ;
      strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE) ;
      strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE) ;
      strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
      strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
      strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
      strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
      strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;

      status = CAD_ACCEPT;
      break;

    default:
      status = CAD_ACCEPT;
      break;
  }
  return (status);
}

/*+
 *   Function name:
 *   tcsGemsRotCorrections
 *
 *   Purpose:
 *   This is a very basic simulation of the data that GeMS system will
 *   generate to provide corrections for the rotator. If "guiding"
 *   is turned on it will write data into VALJ with a new id every
 *   time it is called (excpected to be 1 Hz). If "guiding" is off then
 *   the data will still be written but the id won't be updated.
 *   The value written is set by an input field.
 *
 *   Invocation:
 *   tcsGemsRotCorrections(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 *
 *-
 */
long tcsGemsRotCorrections(struct genSubRecord *pgsub)
{
    static double data[3] ;
    double inval ;
    double tai ;
    static int first = 1 ;

    long guiding ;

    guiding = *(long *)pgsub->a ;
    inval   = *(double *)pgsub->b;

    timeNow(&tai) ;
    if (first) {
      data[1] = tai ;
      first = 0 ;
    }

    data[0] = tai;
    data[2] = inval ;

    if (guiding) {
      data[1] = tai;
    }

    *(long *)pgsub->vala = guiding ;
    *(double *)pgsub->valb = inval ;
    memcpy(pgsub->valj, data, 3 * sizeof(double));
    
    return (0);
}

/*+
 *   Function name:
 *   tcsGemsZernikes
 *
 *   Purpose:
 *   Supply dummy Zernikes when the GeMS is correcting
 *
 *   Description:
 *   This routine fetches the randomly generated Zernike data created
 *   by the simulator and, if the "correct" command has been given to
 *   the RTCSeq outputs them so they can be picked up by the TCS.
 *   A scaled noise signal is added to the data to make it a bit more
 *   realistic ands so the data can be seen to change.
 *
 *   Invocation:
 *   tcsGemsZernikes(pgsub)
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

long tcsGemsZernikes(struct genSubRecord *pgsub)
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
  long gemsNumZernikes ;        /* No. of Zernikes to output */
  double gemsInterval ;         /* How often to output Zernikes (secs) */

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
  gemsNumZernikes = *(long *)pgsub->o ;
  gemsInterval    = *(double *)pgsub->p ;

  if (correcting && !generating) {
    generating = TRUE ;
    timeNow(&aoStartTime) ;
  } else if (!correcting) {
    generating = FALSE ;
  }

  if (generating) {
    timeNow(&tnow) ;
    if (tnow - aoStartTime > gemsInterval ) {
      aoData[0] = tnow ;
      aoData[1] = (double)gemsNumZernikes ;
      sigma = (double)tcsGresid((float)Zerr) ;
      for (i = 2; i < ARRMAX4; i++)
        aoData[i] = 0.0 ;
      for (i = 0; i < gemsNumZernikes; i++) {
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
 *   tcsGsaoiStop
 *
 *   Purpose:
 *   gensub to stop all ODGW following 
 *
 *   Invocation:
 *   tcsGsaoiStop
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
long tcsGsaoiStop(struct genSubRecord *pgsub)
{
    StateProbe[0] = STOPPED;
    StateProbe[1] = STOPPED;
    StateProbe[2] = STOPPED;
    StateProbe[3] = STOPPED;
    strncpy(pgsub->vala, "OFF", 3);
    strncpy(pgsub->valb, "OFF", 3);
    strncpy(pgsub->valc, "OFF", 3);
    strncpy(pgsub->vald, "OFF", 3);
    return (0);
}

epicsRegisterFunction(tcsGemsRotCorrections);
epicsRegisterFunction(tcsGsaoiGenericCAD);
epicsRegisterFunction(tcsGsaoidataODGWCAD);
epicsRegisterFunction(tcsGsaoiStop);
epicsRegisterFunction(tcsGemsZernikes);
epicsRegisterFunction(tcsGsaoiseqODGWCAD);
