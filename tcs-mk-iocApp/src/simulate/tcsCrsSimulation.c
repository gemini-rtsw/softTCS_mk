/*
*   FILENAME
*   tcsCrsSimulation.c
*
*   This module holds the routines that are used in the CRS Simulation
*
*   FUNCTION NAME(S)
*   tcsCRcentreWrapCAD - implement centreWrap command
*   tcsCrInitCAD - initialise variables for the Rotator simulator
*   tcsCrMoveCAD - implement the Rotator move command
*   tcsCRrotconfigCAD - implement the rotconfig command 
*   tcsCrsSimulate - simulate the movement of the mount
*   tcsCrsComplete - signal completion of a move command
*   tcsCrsStop - stop subsystem
*   tcsCrsTimeStampedPos - routine to provide a time stamped rotator position
*   tcsCrsGenericCAD - general purpose CAD routine
*   tcsCRtoleranceCAD - implement the tolerance command
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsCrsSimulation.c,v $
 * Revision 1.7  2001/05/17 14:50:37  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.6  2000/06/03 01:55:55  cjm
 * Add routine tcsCRcentreWrapCAD
 *
 * Revision 1.5  1999/11/23 10:22:51  cjm
 * Read move parameter from input C as per latest CRCS implementation
 *
 * Revision 1.4  1999/06/16 21:26:49  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.3  1999/02/08 09:50:12  cjm
 * Add new routine tcsCrsTimeStampedPos and amend tcsCrsSimulate to allow for input/output in degs. rather than rads
 *
 * Revision 1.2  1999/01/21 20:53:07  cjm
 * Output flag showing datum state from tcsCrDatumVals
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.9  1998/09/05 01:49:29  tcs
 * Output in position flags
 *
 * Revision 1.8  1998/02/12 11:36:02  cjm
 * Add routine tcsCRrotconfigCAD
 *
 * Revision 1.7  1998/01/16 11:29:05  tcs
 * Add tolerance command and tweak servo to match Az
 *
 * Revision 1.6  1997/11/21 17:06:54  pbt
 * Changed status output from simulator : no menuCarstatesERROR now returned
 *
 * Revision 1.5  1997/11/20 12:33:57  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.4  1997/09/24 16:32:40  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.3  1997/04/16 15:57:20  pbt
 * Use symbol CAD_REJECT consistently
 *
 * Revision 1.2  1997/03/05 10:06:33  tcs
 * Update servo parameters
 *
 * Revision 1.1  1997/02/10 17:10:29  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.10  1996/12/10 17:58:26  pbt
 * Simulator CADs now set followS value via output VALA field
 *
 * Revision 1.9  1996/11/28 08:09:20  cjm
 * Fix triggering of activeC and trackid
 *
 * Revision 1.8  1996/11/20 18:08:32  pbt
 * Changed kernel and simulation code to use genSub records
 *
 * Revision 1.7  1996/11/07 16:48:44  pbt
 * Removed junk line at top of file
 *
 * Revision 1.6  1996/11/07 15:07:51  pbt
 * Stop sets to STOPPING state. Corrected bug in completion test (stateAz->stateEl)
 *
 * Revision 1.5  1996/10/23 12:09:52  tcs
 * fix following constant demand
 *
 * Revision 1.4  1996/10/18 13:38:42  tcs
 * Make servos interpolate properly
 *
 * Revision 1.3  1996/07/24 14:00:26  tcs
 * improved servo parameters
 *
 * Revision 1.2  1996/07/23 15:40:14  tcs
 * Add file header comments
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>

#include "tcsCrs.h"
#include "tcsConstants.h"
#include "tcsRandom.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "slalib.h"
#include "tcsServo.h"
#include "timeLib.h"

/* State of rotator */
static int StateRot;
static int MoveActive;

/* Demand postion from move command */
static double patarget;


/*+
 *   Function name:
 *   tcsCRcentreWrapCAD
 *
 *   Purpose:
 *   Implement the centreWrap command in the cass rotator simulator
 *
 *   Description:
 *   An almost empty routine as all the work of implementing the command
 *   is done within the database.
 *
 *   Invocation:
 *   tcsCRcentreWrapCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      t =>  dummy parameter to mark the command
 *
 *   EPICS output paramters:
 *      None
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcLong        (tcsDecode)        Decode an integer
 *   tcsDcString      (tcsDecode)        Match a string 
 *   tcsCsSetMessageN (tcsCadSupport)    Define a message  
 *
 *-
 */

long tcsCRcentreWrapCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */

/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :
   break ;

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

/* This routine is called once if the CRS is to be simulated, 
 * initialises some variables 
 */

void tcsCrInit (void )
{
   static int first = TRUE;
   if (first) first = FALSE;
   StateRot = STOPPED;
}

/* This routine is called by the FOLLOW CAD record. The START CAD
   directive sets the axis state flags to following   */

long tcsCrFollowCAD (struct cadRecord *pcad)
{

/* CAD directive is in field DIR */

   switch (pcad->dir)
   {
   case menuDirectiveSTART:
      StateRot = FOLLOWING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"On");
      return 0;
      break;  /* End menuDirectiveSTART */

/* The STOP CAD directive simply sets the axis 
      state flags to STOPPED   */

    case menuDirectiveSTOP:
      StateRot = STOPPED;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"Off");
      return 0;

   default :
      return 0;
      break;
   }
}

/* This routine is called by the MOVE CAD record. The START CAD
   directive sets the axis state flags to moving   */

long tcsCrMoveCAD (struct cadRecord *pcad)
{
   double pa;
   int nitem;

/* CAD directive is in field DIR */

   switch (pcad->dir)
   {
   case menuDirectiveSTART:
   case menuDirectivePRESET:
      strcpy(pcad->mess, "Move: argument is valid");
      nitem = sscanf (pcad->c, "%lf", &pa);
      if ( nitem != 1) 
      {
         strcpy(pcad->mess, "Move: argument is invalid");
      }
      else if (pa < -270.0 || pa > 270.0)
      {
         strcpy(pcad->mess, "Move: position angle out of range");
         return CAD_REJECT;
      }
      else
      {
         patarget = pa * 3600;
         if (pcad->dir == menuDirectiveSTART) 
         {
            StateRot = MOVING;
            MoveActive = TRUE;
         }
         strcpy(pcad->vala,"Off");
         strcpy(pcad->mess, "Command accepted");
      }

/* Output acceptance message */

      return 0;
      break;  /* End menuDirectiveSTART or menuDirectivePRESET */

/* The STOP CAD directive simply sets the axis 
   state flags to STOPPING   */

   case menuDirectiveSTOP:
      StateRot = STOPPING;

/* Output acceptance message */

      strcpy(pcad->vala,"Off");
      strcpy(pcad->mess, "Command accepted");
      return 0;

   default :
      return 0;
      break;
   }
}


/*+
 *   Function name:
 *   tcsCRrotconfigCAD
 *
 *   Purpose:
 *   Implement the rotconfig command in the cass rotator simulator
 *
 *   Description:
 *   This routine simply checks the input parameters for validity and then 
 *   accepts the command. The purpose of the command is to reconfigure the
 *   encoder but since this is purely a software simulation there is nothing
 *   to do. 
 *
 *   Invocation:
 *   tcsCRrotconfigCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a =>  demand algorithm
 *      b =>  demand head identifier
 *
 *   EPICS output paramters:
 *      vala => Current algorithm
 *      valb => current head identifier 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcLong        (tcsDecode)        Decode an integer
 *   tcsDcString      (tcsDecode)        Match a string 
 *   tcsCsSetMessageN (tcsCadSupport)    Define a message  
 *
 *-
 */

long tcsCRrotconfigCAD (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *algopts[] = {"FDE", "FULL", "N", "M&N", NULL} ;
  static long headId ;     /* Head identifier */
  static int algIndex ;   /* Index to demanded algorithm */

/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT;

/* Algorithm */
     if (tcsDcString (algopts, "algorithm : ", pcad->a, &algIndex, 
         pcad)) break ;

/* Head identifier */
     if (algIndex > 1) {
       if (tcsDcLong ("head id : ", pcad->b, &headId, pcad)) break;
       if (headId < 1 || headId > 15) {
         tcsCsAppendMessageN (pcad, "head Id. > 15 or < 1", (char *)NULL) ;
         break ;
       }
     }
    
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

   strcpy (pcad->vala, algopts[algIndex]) ;
   strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   
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



/* This routine is linked to the TcsCrsSimulate record and performs the main
 * simulation of the Rotator. At present the simulation is very simple. If the
 * rotator is stopped then the output is constant. If the rotator is active but
 * no move is in progress then the output is just the demand plus a small
 * random error. If a move is in progress then the current position is just
 * the last position plus an increment. 
 *
 * Inputs :
 * b => Rotator PA default (degrees)
 * c => max rotator velocity (degs/s)
 * i => encoder noise (arcsec)
 * j => demand array :
 *  Element 0  = Time now
 *  Element 1  = Target time
 *  Element 2  = Track identifier
 *  Element 3  = Demanded PA
 *
 *
 * Outputs :
 * 
 *  vala => time at which positions apply
 *  valb => current PA (degs)
 *  valc => current velocity (deg/sec)
 *  vald => PA error (degs)
 *  vale => status
 *  vali => disable or enable following processing chain
 *  valj => inPosition flag
 *
 */

long tcsCrsSimulate (struct genSubRecord *pgsub) 
{

   static int first = TRUE;
   static int substat;        /* subsystem status */
   static double trackid;     /* current track id */
   static double pa;          /* current position angle */
   static double pav;         /* current velocity */
   static double paerr;       /* PA error */
   double pan;                /* postion angle demand "now" */

   unsigned long arraySize ;  /* number of elements in input demand array */
   double CRSdemand[4] ;      /* demand data array from kernel */
   double pademand;           /* rotator demand */
   static double pademandv;   /* rotator demand velocity */
   double newtrack;           /* track id of demand */
   int newstat;               /* new subsystem status */
   int inPosition;            /* in position flag */
   int stateRot;              /* local copy of rotator state */
   int linkSelect;            /* select flags for downstream processing */

   static double tappl;       /* time for which demands are correct */
   static double now;         /* current time */

   static double tlast;
   static double palast;

   static struct ServoState servoState;
   static struct ServoConfig servoConfig;

/* Get a local copy of the rotator state as the global value may get changed
   from elsewhere */

   stateRot = StateRot;

      if (first)            /* Initialise servo simulator */
      {
         servoConfig.dvmax = 360.0;
         servoConfig.gs = 20.0;
         servoConfig.gp = 5.0;
         servoConfig.gi = 0.5;
         servoConfig.pi = 1.0;
         servoConfig.pok = 0.2;
         servoConfig.tok = 0.1;
         servoState.pdtold = *(double *)pgsub->b * 3600.0;
         timeNow( &(servoState.told) );
         servoState.told -= 0.05;
         servoState.tout = servoState.told;
         servoState.vd = 0.0;
         servoState.accum = 0.0;
         pa = servoState.pdtold;
         pav = 0.0;
         newstat = menuCarstatesIDLE;
         substat = -1;
         trackid = 0.0;
         first = FALSE;
      }

/* fetch latest velocities etc */

      servoConfig.vtmax = *(double *)pgsub->c * 3600.0;
      servoConfig.noise = *(double *)pgsub->i; 

/* Read in input demand array data from kernel */
      arraySize = pgsub->noj ;
      memcpy(CRSdemand, pgsub->j, arraySize * sizeof(double)) ;
      tappl   =  CRSdemand[1] ;
      newtrack = CRSdemand[2] ;
      pademand = CRSdemand[3] * 3600.0;

/* send demand to servo */
      timeNow( &now );
      if (stateRot == MOVING)
      {
         inPosition = tcsServo( now, patarget, 0, &servoConfig, &servoState,
            &pa, &pav);
         paerr = patarget - pa;
      } 
      else if (stateRot == FOLLOWING)
      {
         if ( tappl > tlast )
         {
            pademandv = (pademand - palast) / (tappl - tlast);
         }
         pan = pademand + pademandv * (now - tappl);
         inPosition = tcsServo( now, pan, 0, &servoConfig, &servoState,
            &pa, &pav);
         paerr = pan - pa;
      }
      else
      {
         inPosition = tcsServo( now, pa, 1, &servoConfig, &servoState,
            &pa, &pav);
         paerr = 0.0;
      }

/* Detemine new subsystem state */
      if (inPosition)
         {
         if ( stateRot == MOVING || stateRot == STOPPING )
           {
           StateRot = STOPPED;
           MoveActive = FALSE;
           linkSelect += 1;     /* Trigger record 'complete' */
           }
         newstat = menuCarstatesIDLE;
         }
      else
         newstat = menuCarstatesBUSY;
   
/* Initialise the link selection field. The bits in this field 
   are as follows :
    +1/Bit 0 = Process completion record
    +2/Bit 1 = Process CAR record
    +4/Bit 2 = Process trackId record */
      linkSelect = 0;
      if (newstat != substat)
      {
         substat = newstat;
         linkSelect += 2;           /* Trigger update of CAR record */
      }
      if (newtrack != trackid)
      {  
         trackid = newtrack;
         linkSelect +=4;           /* Trigger update of trackId record */
      } 
   
/* save demands */
      tlast = tappl;
      palast = pademand;
 
/* now output the results */

      *(double *)pgsub->vala = now;
      *(double *)pgsub->valb = pa / 3600.0;
      *(double *)pgsub->valc = pav / 3600.0;
      *(double *)pgsub->vald = paerr / 3600.0;
      *(double *)pgsub->vale = substat;
      *(double *)pgsub->valf = trackid;
      *(long *)pgsub->vali = (long)linkSelect;
      *(long *)pgsub->valj = (long)inPosition;

      return 0;
}
  
/* Routine to signal action completion of the MOVE command */

long tcsCrsComplete (genSubRecord *psub)
{

/* output values */

   strcpy(psub->valb, "Stopped");
   *(double *)psub->vala = menuCarstatesIDLE;
   return 0;
}

/*+
 *   Function name:
 *   tcsCrStop
 *
 *   Purpose:
 *   Stops the mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsCrStop
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

long tcsCrStop (struct genSubRecord *pgsub)
{
   StateRot = STOPPING;
   strncpy(pgsub->vala, "Off", 3);
   return(0);
}


/*+
 *   Function name:
 *   tcsCrsTimeStampedPos
 *
 *   Purpose:
 *   Provide an array with a time stamped position and velocity
 *
 *   Description:
 *   This routine simply pulls in the current timestamp, position and 
 *   velocity and then provides them in an array
 *
 *   Invocation:
 *   tcsCrsTimeStampedPos (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *
 *   Epics inputs:
 *
 *   a => current time (TAI)
 *   b => current position (degs)
 *   c => current velocity (degs/s)
 *
 *   Epics outputs:
 *
 *   vala => array of timestamp, position and velocity
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsCrsTimeStampedPos (struct genSubRecord *pgsub) 
{
  double crArray[3] ;       /* Array to hold CR time stamped position */

/* fetch time, position and velocity */
  crArray[0] = *(double *)pgsub->a ;
  crArray[1] = *(double *)pgsub->b ;
  crArray[2] = *(double *)pgsub->c ;

  memcpy (pgsub->vala, crArray, 3 * sizeof(double)) ;

  return 0 ;

}


/*+
 *   Function name:
 *   tcsCrGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the Rotator
 *
 *   Description:
 *
 *   Invocation:
 *   tcsCrTestCAD(pcad)
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

long tcsCrGenericCAD (struct cadRecord *pcad)
{
   int status;                /* return status */
   char command[29];          /* command name */
   int i, j;                  /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
   for ( i = 0, j = 0; i < 29; i++, j++ )
   {
      command[j] = pcad->name[i];
      if ( !(pcad->name[i]) ) break;
      if ( command[j] == ':' ) j = -1;
   }

   switch(pcad->dir)
   {
   case menuDirectiveSTART:

   /* write output message (n.b. no more that 28 characters) */
      sprintf(pcad->mess, "Rotator: %.11s started", command);
 /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"Off");
      else
    /* Copy over the parameters to the output fields */
       {
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
   return(status);
}

/*+
 *   Function name:
 *   tcsCrDatumVals
 *
 *   Purpose:
 *   Output string status value to rotator SIRs
 *
 *   Description:
 *
 *   Invocation:
 *   tcsCrDatumVal
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

long tcsCrDatumVals (struct genSubRecord *pgsub)
{
   if (!(*(long *)pgsub->a))
   {
     strcpy(pgsub->vala, "NOT DATUMED");
   }
   else
   {
     strcpy(pgsub->vala, "DATUMED");
   }

   *(long *)pgsub->valb = *(long *)pgsub->a ;

   return(0);
}

/*+
 *   Function name:
 *   tcsCRtoleranceCAD
 *
 *   Purpose:
 *   Implement the tolerance CAD record in the rotator simulator
 *
 *   Description:
 *   This function implements the tolerance CAD record in the rotator simulator.
 *
 *   Invocation:
 *    tcsCRtoleranceCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Function value:
 *   Return status
 *
 *   External variables:
 *   Any external variables used in this function or procedure
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *
 *-
 */

long tcsCRtoleranceCAD (struct cadRecord *pcad)
{
   int nitemA, nitemB;
   double tolpos, tolvel;
   long ret = CAD_ACCEPT;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

      nitemA = sscanf (pcad->a, "%lf", &tolpos);
      if (nitemA < 1 || tolpos < 0.0)
      {
         strncpy(pcad->mess, "Tolerance : invalid posn tolerance", MAX_STRING_SIZE);
         ret =  CAD_REJECT;
      }   

      nitemB = sscanf (pcad->b, "%lf", &tolvel);
      if (nitemB < 1 || tolvel < 0.0)
      {
         strncpy(pcad->mess, "Tolerance : invalid vel tolerance", MAX_STRING_SIZE);
         ret =  CAD_REJECT;
      }   

      break;   /* End menuDirectivePRESET */

   case menuDirectiveMARK:
   case menuDirectiveSTART:
   case menuDirectiveSTOP:
   case menuDirectiveCLEAR:
      break;

   default:
      strncpy(pcad->mess, "Tolerance : invalid CAD directive", MAX_STRING_SIZE);
      ret = CAD_REJECT;
      break;
   }

   return ret;
}
epicsRegisterFunction(tcsCrGenericCAD);
epicsRegisterFunction(tcsCrsTimeStampedPos);
epicsRegisterFunction(tcsCRrotconfigCAD);
epicsRegisterFunction(tcsCRcentreWrapCAD);
epicsRegisterFunction(tcsCrsComplete);
epicsRegisterFunction(tcsCrsSimulate);
epicsRegisterFunction(tcsCrDatumVals);
epicsRegisterFunction(tcsCrMoveCAD);
epicsRegisterFunction(tcsCrStop);
epicsRegisterFunction(tcsCRtoleranceCAD);
epicsRegisterFunction(tcsCrFollowCAD);
