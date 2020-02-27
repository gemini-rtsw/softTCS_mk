/*
*   FILENAME
*   tcsMcsSimulation.c
*
*   This module holds the routines that are used in the MCS Simulation 
*
*   FUNCTION NAME(S)
*   tcsMcInitCAD - initialise variables for the Mount simulator
*   tcsMcMoveCAD - implement the Mount move command
*   tcsMcsSimulate - simulate the movement of the mount
*   tcsMcsTimeStampedPos - generate timestamped data for TCS
*   tcsMcsComplete - signal completion of a move command
*   tcsMcsStop - stop subsystem
*   tcsMcsGenericCAD - general purpose CAD routine
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsMcsSimulation.c,v $
 * Revision 1.10  2015/06/12 12:37:30  cjm
 * Allow elevation greater than 90 for testing
 *
 * Revision 1.9  2015/05/18 09:34:42  cjm
 * Fix error in logic for mount completion
 *
 * Revision 1.8  2001/05/17 14:50:38  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.7  1999/06/29 05:06:11  cjm
 * Add routine to generate time stamped position and velocity array in line with new MCS
 *
 * Revision 1.6  1999/06/16 21:26:51  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.5  1999/01/27 23:29:31  dlt
 * Make followS value match the real MCS
 *
 * Revision 1.4  1999/01/21 20:53:55  cjm
 * Output flag showing datum state from tcsMcsDatumVals
 *
 * Revision 1.3  1998/11/19 21:17:02  cjm
 * Modify to comply with latest MCS implementation, mainly input and output in degrees rather than rads
 *
 * Revision 1.2  1998/11/16 18:40:55  cjm
 * Update, move, tolerance, azconfig and elconfig commands to match latest MCS implementation
 *
 * Revision 1.1.1.1  1998/11/08 00:21:11  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.12  1998/09/05 01:49:31  tcs
 * Output in position flags
 *
 * Revision 1.11  1998/01/20 14:18:06  tcs
 * Tweak servo to stop elevation overshoot
 *
 * Revision 1.10  1997/11/21 17:06:57  pbt
 * Changed status output from simulator : no menuCarstatesERROR now returned
 *
 * Revision 1.9  1997/11/20 12:34:01  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.8  1997/10/24 21:50:48  tcs
 * Increase POK
 *
 * Revision 1.7  1997/09/24 16:32:46  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.6  1997/09/23 11:50:07  tcs
 * Remove redundant includes
 *
 * Revision 1.5  1997/09/23 09:43:59  pbt
 * Removed carOR routine
 *
 * Revision 1.4  1997/07/15 11:30:20  pbt
 * Added extra simulated CAD command routines
 *
 * Revision 1.3  1997/04/16 15:57:22  pbt
 * Use symbol CAD_REJECT consistently
 *
 * Revision 1.2  1997/03/05 10:06:35  tcs
 * Update servo parameters
 *
 * Revision 1.1  1997/02/10 17:10:46  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.26  1996/12/10 17:58:30  pbt
 * Simulator CADs now set followS value via output VALA field
 *
 * Revision 1.25  1996/11/28 08:10:01  cjm
 * Fix triggering of activeC and trackid
 *
 * Revision 1.24  1996/11/20 18:08:35  pbt
 * Changed kernel and simulation code to use genSub records
 *
 * Revision 1.23  1996/11/12 18:05:36  pbt
 * Various updates : STOP command and MOVE command default parameters
 *
 * Revision 1.22  1996/11/07 15:07:53  pbt
 * Stop sets to STOPPING state. Corrected bug in completion test (stateAz->stateEl)
 *
 * Revision 1.21  1996/10/23 12:09:53  tcs
 * fix following constant demand
 *
 * Revision 1.20  1996/10/18 13:38:43  tcs
 * Make servos interpolate properly
 *
 * Revision 1.19  1996/09/11 13:40:47  tcs
 * Change azimuth wrap limits to -180/+360
 *
 * Revision 1.18  1996/07/24 14:00:27  tcs
 * improved servo parameters
 *
 * Revision 1.17  1996/07/23 15:00:01  tcs
 * tidy up routine names and add header to include files
 *
 * Revision 1.16  1996/07/23 10:03:42  tcs
 * Add TEST & PARK plus generic CAD mechanism
 *
 * Revision 1.15  1996/07/22 09:46:05  pbt
 * Whoops, syntax error corrected!
 *
 * Revision 1.14  1996/07/22 09:33:17  pbt
 * Added Test command subroutine
 *
 * Revision 1.13  1996/07/19 13:45:09  tcs
 * misc fixes
 *
 * Revision 1.12  1996/07/12 14:51:37  tcs
 * improved servo algorithm
 *
 * Revision 1.11  1996/07/09 13:18:04  tcs
 * revised track id logic and enhanced simulators
 *
 * Revision 1.10  1996/07/08 14:29:35  tcs
 * Implement track identifier scheme
 *
 * Revision 1.9  1996/06/24 14:22:51  tcs
 * generate azimuth and rotator angles in range -270/+270
 *
 * Revision 1.8  1996/06/21 13:50:17  tcs
 * elevation limit and MOVE logic changes
 *
 * Revision 1.7  1996/06/17 07:29:39  cjm
 * Tidy up, add control of error term etc.
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <genSubRecord.h>
#include <subRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>
#include <dbCommon.h>
#include <recSup.h>

#include "tcsMcs.h"
#include "tcsConstants.h"
#include "tcsServo.h"
#include "timeLib.h"

/* State of axes */
static int StateAz;
static int StateEl;
static int MoveActive;

/* Demand postion from move command */
static double aztarget;
static double eltarget;

static double az;          /* current azimuth */
static double el;          /* current elevation */

/*+
 *   Function name:
 *   tcsMcInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the mount control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the mount control system.
 *
 *   Invocation:
 *   tcsMcInit()
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


void tcsMcInit (void )
{
   static int first = TRUE;

   if (first) first = FALSE;
   StateAz = STOPPED;
   StateEl = STOPPED;
}

long tcsMcFollowCAD (struct cadRecord *pcad)
{

/* CAD directive is in field DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
      StateAz = FOLLOWING;
      StateEl = FOLLOWING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"ON");
      return 0;
      break;  /* End menuDirectiveSTART */

/* The STOP CAD directive simply sets the axis
   state flags to STOPPED   */

   case menuDirectiveSTOP:
      StateAz = STOPPED;
      StateEl = STOPPED;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"OFF");
      return 0;

   default :
      return 0;
      break;
   }
}

/*+
 *   Function name:
 *   tcsMcMoveCAD
 *
 *   Purpose:
 *   Implement the Move CAD record in the mount simulator
 *
 *   Description:
 *   This function implements the move CAD record in the mount simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record. 
 *
 *   Invocation:
 *   tcsMcMoveCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Epics inputs:
 *
 *   c => Azimuth demand (degs)
 *   d => Elevation demand (degs)
 *
 *   Epics outputs:
 *
 *   vala => Following status "OFF" 
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
 *-
 */

long tcsMcMoveCAD (struct cadRecord *pcad)
{
   double azMove, elMove;
   int azNitem, elNitem;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
   case menuDirectivePRESET:
      strcpy(pcad->mess, "Move: arguments are valid");
      azNitem = sscanf (pcad->c, "%lf ", &azMove);
      if ( azNitem < 1)
       {
         azMove = az/3600.0 ;
       }
      else if (azMove < -180.0 || azMove > 360.0)
      {
         strcpy(pcad->mess, "Move: azimuth out of range");
         return CAD_REJECT;
      }

      elNitem = sscanf (pcad->d, "%lf ", &elMove);
      if ( elNitem < 1) 
      {
        elMove = el/3600.0 ;
      }
/* Allow move above 90 for testing */
      else if (elMove < 0.0 || elMove > 91.0)
      {
        strcpy(pcad->mess, "Move: elevation out of range");
        return CAD_REJECT;
      }

/* Must have at least one of Az and El specified */
      if (azNitem < 1 && elNitem < 1) 
      {
        strcpy(pcad->mess, "Move: No az or el specified");
        return CAD_REJECT;
      }        

      aztarget = azMove * 3600;
      eltarget = elMove * 3600;
      if (pcad->dir == menuDirectiveSTART) 
      {
         StateAz = MOVING;
         StateEl = MOVING;
         MoveActive = TRUE;
      }

      strcpy(pcad->vala,"OFF");
      strcpy(pcad->mess, "Command accepted");
      return 0;
      break;   /* End PmenuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateAz = STOPPING;
      StateEl = STOPPING;

/* Output acceptance message */

      strcpy(pcad->vala,"OFF");
      strcpy(pcad->mess, "Command accepted");
      return 0;
      break;

   default:
      return 0;
      break;
   }
}

/*+
 *   Function name:
 *   tcsMcsSimulate
 *
 *   Purpose:
 *   Simulates behaviour of the mount without any hardware
 *
 *   Description:
 *   This routine is linked to the TcsMcsSimulate record and performs the main
 *   simulation of the Mount. At present the simulation is very simple. If an
 *   axis is stopped then the output is constant. If an axis is active but
 *   no move is in progress then the output is just the demand plus a small
 *   random error. If a move is in progress then the current position is just
 *   the last position plus an increment. 
 *
 *   Inputs :
 *
 *   b => azimuth default (degrees)
 *   d => elevation default (degrees)
 *   f => max azimuth velocity (degs/s)
 *   h => max elevation velocity (deg/s)
 *   j => input demand array for MCS from TCS kernel :
 *      Element 0  = Time when data sent
 *      Element 1  = Target time
 *      Element 2  = Track identifier
 *      Element 3  = Demanded Azimuth (degs)
 *      Element 4  = Demanded Elevation (degs)
 *
 *   t => noise term (arcsec)
 *
 *   Outputs :
 * 
 *   vala => time at which positions apply
 *   valb => current azimuth (degs)
 *   valc => current elevation (degs)
 *   vald => azimuth error (degs)
 *   vale => elevation error (degs)
 *   valf => status
 *   valg => track identifier
 *   valh => time at which positions apply
 *   vali => disable or enable following processing chain
 *   valj => Az inPosition state
 *   valk => El inPosition state
 *   vall => Overall inPosition state
 *
 *   Invocation:
 *   tcsMcsSimulate(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to genSub record data structure
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

long tcsMcsSimulate (struct genSubRecord *pgsub) 

{
   static int Count = 0;
   static int first = TRUE;
   static int dbgPrintFirst = TRUE ;
   static int substat;        /* subsystem status */
   static double trackid;     /* current track id */

   static double azv;         /* current velocity */
   static double azerr;       /* azimuth error */

   static double elv;         /* current velocity */
   static double elerr ;      /* elevation error */

   unsigned long arraySize ;  /* number of elements in inout demand array */
   double MCSdemand[5] ;      /* demand data array from kernel */
   double azdemand;           /* azimuth demand */
   double eldemand;           /* elevation demand */
   static double azdemandv;   /* azimuth demand velocity */
   static double eldemandv;   /* elevation demand velocity */
   double newtrack;           /* track id of demand */
   int newstat;               /* new subsystem status */
   int inPositionAz;          /* Az in position flag */
   int inPositionEl;          /* El in position flag */
   int inPosition;            /* All in position flag */
   int stateAz;               /* local copy of azimuth state */
   int stateEl;               /* local copy of elevation state */
   int linkSelect ;           /* selects which downstream links are processed */

   double tappl;             /* time for which demands are correct */
   static double now;         /* current time */
   double azn;                /* azimuth demand "now" */
   double eln;                /* elevation demand now */

   static double tlast;
   static double azlast;
   static double ellast;

   static struct ServoState servoStateAz;
   static struct ServoState servoStateEl;
   static struct ServoConfig servoConfigAz;
   static struct ServoConfig servoConfigEl;

   Count++ ;

/* Get a local copy of the axis states as the global values may get changed
   from elsewhere */

   stateAz = StateAz;
   stateEl = StateEl;

      if (first)            /* set "last" position to default position */
      {
         servoConfigAz.dvmax = 360.0;
         servoConfigAz.gs = 20.0;
         servoConfigAz.gp = 5.0;
         servoConfigAz.gi = 0.5;
         servoConfigAz.pi = 1.0;
         servoConfigAz.pok = 0.2;
         servoConfigAz.tok = 0.1;
         servoStateAz.pdtold = *(double *)pgsub->b * 3600.0;
         timeNow( &(servoStateAz.told) );
         servoStateAz.told -= 0.05;
         servoStateAz.tout = servoStateAz.told;
         servoStateAz.vd = 0.0;
         servoStateAz.accum = 0.0;
         az = servoStateAz.pdtold;
         azv = 0.0;
         servoConfigEl.dvmax = 180.0;
         servoConfigEl.gs = 15.0;
         servoConfigEl.gp = 4.0;
         servoConfigEl.gi = 0.4;
         servoConfigEl.pi = 1.0;
         servoConfigEl.pok = 0.2;
         servoConfigEl.tok = 0.1;
         servoStateEl.pdtold = *(double *)pgsub->d * 3600.0;
         timeNow( &(servoStateEl.told) );
         servoStateEl.told -= 0.05;
         servoStateEl.tout = servoStateEl.told;
         servoStateEl.vd = 0.0;
         servoStateEl.accum = 0.0;
         el = servoStateEl.pdtold;
         elv = 0.0;

         substat = -1;
         newstat = menuCarstatesIDLE;
         trackid = 0.0;
         first = FALSE;
      }

/* fetch latest velocities etc */

      servoConfigAz.vtmax = *(double *)pgsub->f * 3600.0;
      servoConfigEl.vtmax = *(double *)pgsub->h * 3600.0;
      servoConfigAz.noise = *(double *)pgsub->t;
      servoConfigEl.noise = *(double *)pgsub->t;

/* Read in input demand array data from kernel */
      arraySize = pgsub->noj ;
      memcpy(MCSdemand, pgsub->j, arraySize * sizeof(double)) ;
      tappl   = MCSdemand[1] ;
      newtrack = MCSdemand[2] ;
      azdemand = MCSdemand[3] * 3600.0;
      eldemand = MCSdemand[4] * 3600.0;

/* get the current time */
      timeNow( &now );

/* send demands to servos */
      if (stateAz == MOVING)
      {
         inPositionAz = tcsServo( now, aztarget, 0, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = aztarget - az;
      }
      else if (stateAz == FOLLOWING)
      {
         if ( tappl > tlast )
         {
            azdemandv = (azdemand - azlast) / (tappl - tlast);
         }
         azn = azdemand + azdemandv * (now - tappl);
         inPositionAz = tcsServo( now, azn, 0, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = azn - az;
      }
      else
      {
         inPositionAz = tcsServo( now, az, 1, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = 0.0;
      }
      if (stateEl == MOVING)
      {
         inPositionEl = tcsServo( now, eltarget, 0, &servoConfigEl, 
            &servoStateEl, &el, &elv);
         elerr = eltarget - el;
      }
      else if (stateEl == FOLLOWING)
      {
         if ( tappl > tlast )
         {
            eldemandv = (eldemand - ellast) / (tappl - tlast);
         }
         eln = eldemand + eldemandv * (now - tappl);
         inPositionEl = tcsServo( now, eln, 0, &servoConfigEl, 
            &servoStateEl, &el, &elv);
         elerr = eln - el;
      }
      else
      {
         inPositionEl = tcsServo( now, el, 1, &servoConfigEl, 
            &servoStateEl, &el, &elv);
         elerr = 0.0;
      }


/* Set separate Az/El states if they are in position, not Following */
      if ( inPositionAz && ( stateAz == MOVING || stateAz == STOPPING ) )
         StateAz = STOPPED;
      if ( inPositionEl && ( stateEl == MOVING || stateEl == STOPPING ) )
         StateEl = STOPPED;

/* Initialise the link selection field. The bits in this field 
   are as follows :
    +1/Bit 0 = Process completion record
    +2/Bit 1 = Process CAR record
    +4/Bit 2 = Process trackId record */

      linkSelect = 0;

 /* Detemine new subsystem state */
      inPosition   = inPositionEl && inPositionAz ;
      if (inPosition) {
         if ( stateAz == STOPPED && stateEl == STOPPED ) {
           if (MoveActive == TRUE) {
             MoveActive = FALSE;
             linkSelect += 1;     /* Trigger record 'complete' */
           }
         }
         newstat = menuCarstatesIDLE;
      }
      else
         newstat = menuCarstatesBUSY;

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
      dbgPrintFirst = FALSE ;

/* save demands */
      tlast = tappl;
      azlast = azdemand;
      ellast = eldemand;

/* now output the results */
 
      *(double *)pgsub->vala = now;
      *(double *)pgsub->valb = az / 3600.0;
      *(double *)pgsub->valc = el / 3600.0;
      *(double *)pgsub->vald = azerr / 3600.0;
      *(double *)pgsub->vale = elerr / 3600.0;
      *(double *)pgsub->valf = substat;
      *(double *)pgsub->valg = trackid;
      *(double *)pgsub->valh = now;
      *(long *)pgsub->vali = (long)linkSelect ;
      *(long *)pgsub->valj = (long)inPositionAz ;
      *(long *)pgsub->valk = (long)inPositionEl ;
      *(long *)pgsub->vall = (long)inPosition ;
      *(double *)pgsub->valm = azv / 3600.0 ;
      *(double *)pgsub->valn = elv / 3600.0 ;

   return 0;
}
  
/*+
 *   Function name:
 *   tcsMcsTimeStampedPos
 *
 *   Purpose:
 *   Provide array of time stamped positions for TCS
 *
 *   Description:
 *   Simply pull in the data calculated by the simulation and assemble it
 *   into the correct form for the TCS. 
 *
 *   Invocation:
 *   tcsMcsTimeStampedPos(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *)  Pointer to gensub structure
 *
 *   Epics inputs:
 *
 *   a => Time stamp of az/el position
 *   b => Current azimuth (degs)
 *   c => Current azimuth velocity (deg/s)
 *   d => Current elevation (degs)
 *   e => Current elevation velocity (deg/s)
 *
 *   Epics outputs:
 *
 *   vala => array of timestamp, positions and velocities
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsMcsTimeStampedPos (struct genSubRecord *pgsub)
{
  double mcArray[6] ;      /* Array to hold time stamped positions */

/* Fetch data from input links */
  mcArray[0] = *(double *)pgsub->a ;
  mcArray[1] = *(double *)pgsub->b ;
  mcArray[2] = *(double *)pgsub->c ;
  mcArray[3] = *(double *)pgsub->a ;
  mcArray[4] = *(double *)pgsub->d ;
  mcArray[5] = *(double *)pgsub->e ;
  
/* Place on output links */
  memcpy (pgsub->vala, mcArray, 6 * sizeof(double)) ;

  return 0 ;

}

/*+
 *   Function name:
 *   tcsMcsComplete
 *
 *   Purpose:
 *   Signal complete of a move command
 *
 *   Description:
 *   Signals completion of a move command by writing IDLE to the appropriate
 *   CAR record.
 *
 *   Invocation:
 *   tcsMcsComplete(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub    (genSubRecord *) pointer to genSub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsMcsComplete (genSubRecord *psub)
{

/* output values for CAR Message and State fields */

   strcpy(psub->valb, "Stopped");
   *(double *)psub->vala = menuCarstatesIDLE;
   return 0;
}

/*+
 *   Function name:
 *   tcsMcStop
 *
 *   Purpose:
 *   Stops the mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsMcStop
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

long tcsMcStop (struct genSubRecord *pgsub)
{
   StateAz = STOPPING;
   StateEl = STOPPING;
   strncpy(pgsub->vala, "OFF", 3);
   return(0);
}

/*+
 *   Function name:
 *   tcsMCencConfigCAD
 *
 *   Purpose:
 *   Implement the el/az config CAD record in the mount simulator
 *
 *   Description:
 *   This function implements the el/az config CAD record in the mount simulator.
 *
 *   Invocation:
 *    tcsMCencConfigCAD(pcad)
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

long tcsMCencConfigCAD (struct cadRecord *pcad)
{
   char algorithm[10], command[29];
   int i, j;
   long ret = CAD_ACCEPT;

/* Extract the command name from the record name (whatever comes after the
   last colon) */
   for ( i = 0, j = 0; i < 29; i++, j++ )
   {
      command[j] = pcad->name[i];
      if ( !(pcad->name[i]) ) break;
      if ( command[j] == ':' ) j = -1;
   }

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

      strncpy(algorithm, pcad->a, 10);
      if (strlen(algorithm) == 0)
      {
         sprintf(pcad->mess, "%.13s : Algorithm not specified", command);
         ret =  CAD_REJECT;
      }

      break;   /* End menuDirectivePRESET */

   case menuDirectiveMARK:
   case menuDirectiveSTART:
   case menuDirectiveSTOP:
   case menuDirectiveCLEAR:
      break;

   default:
      sprintf(pcad->mess, "%.13s : Unknown CAD directive", command);
      ret = CAD_REJECT;
      break;
   }

   return ret;
}

/* Calls to tcsMCencConfigCAD for the Az and El configure commands */

long tcsMCazconfigCAD (struct cadRecord *pcad)
{
  long ret;
  ret =  tcsMCencConfigCAD(pcad);
  return ret;
}

long tcsMCelconfigCAD (struct cadRecord *pcad)
{
  long ret;
  ret = tcsMCencConfigCAD(pcad);
  return ret;
}


/*+
 *   Function name:
 *   tcsMCtoleranceCAD
 *
 *   Purpose:
 *   Implement the tolerance CAD record in the mount simulator
 *
 *   Description:
 *   This function implements the tolerance CAD record in the mount simulator.
 *
 *   Invocation:
 *    tcsMCtoleranceCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Epics inputs:
 *   a => position tolerance of azimuth axis (degs)
 *   b => velocity tolerance of azimuth axis (degs/s)
 *   c => position tolerance of elevation axis (degs)
 *   d => velocity tolerance of elevation axis (degs/s)
 *
 *   Function value:
 *   Return status
 *
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   Only checks tolerances on the azimuth axis
 *
 *-
 */

long tcsMCtoleranceCAD (struct cadRecord *pcad)
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

/*+
 *   Function name:
 *   tcsMClogCAD
 *
 *   Purpose:
 *   Implement the log CAD record in the mount simulator
 *
 *   Description:
 *   This function implements the log CAD record in the mount simulator.
 *
 *   Invocation:
 *    tcsMClogCAD(pcad)
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

long tcsMClogCAD (struct cadRecord *pcad)
{
   int nitemA;
   double lograte;
   long ret = CAD_ACCEPT;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

      nitemA = sscanf (pcad->a, "%lf", &lograte);
      if (nitemA < 1 || lograte < 1.0 || lograte > 2000.0)
      {
         strncpy(pcad->mess, "MCS Log : invalid frequency specified", MAX_STRING_SIZE);
         ret =  CAD_REJECT;
      }   

      break;   /* End menuDirectivePRESET */
   case menuDirectiveMARK:
   case menuDirectiveSTART:
   case menuDirectiveSTOP:
   case menuDirectiveCLEAR:
      break;

   default:
      strncpy(pcad->mess, "MCS Log  : invalid CAD directive", MAX_STRING_SIZE);
      ret = CAD_REJECT;
      break;
   }

   return ret;
}


/*+
 *   Function name:
 *   tcsMcGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the Mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsMcTestCAD(pcad)
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

long tcsMcGenericCAD (struct cadRecord *pcad)
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
      sprintf(pcad->mess, "Mount: %.13s started", command);
  /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"OFF");
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
   return(status);
}

/*+
 *   Function name:
 *   tcsMcDatumVals
 *
 *   Purpose:
 *   Output string status value to axis SIRs
 *
 *   Description:
 *
 *   Invocation:
 *   tcsMcDatumVals
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

long tcsMcDatumVals (struct genSubRecord *pgsub)
{
   if (!(*(long *)pgsub->a))
   {
     strcpy(pgsub->valb, "NOT DATUMED");
     strcpy(pgsub->valc, "NOT DATUMED");
   }
   else
   {
     strcpy(pgsub->valb, "DATUMED");
     strcpy(pgsub->valc, "DATUMED");
   }

   *(long *)pgsub->vala = *(long *)pgsub->a ;

   return(0);
}
epicsRegisterFunction(tcsMCtoleranceCAD);
epicsRegisterFunction(tcsMcStop);
epicsRegisterFunction(tcsMcDatumVals);
epicsRegisterFunction(tcsMcGenericCAD);
epicsRegisterFunction(tcsMcFollowCAD);
epicsRegisterFunction(tcsMClogCAD);
epicsRegisterFunction(tcsMCelconfigCAD);
epicsRegisterFunction(tcsMCazconfigCAD);
epicsRegisterFunction(tcsMcsSimulate);
epicsRegisterFunction(tcsMcsTimeStampedPos);
epicsRegisterFunction(tcsMcMoveCAD);
epicsRegisterFunction(tcsMcsComplete);
