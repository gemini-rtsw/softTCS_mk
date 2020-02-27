/*
*   FILENAME
*   tcsEcsSimulation.c
*
*   This module holds the routines that are used in the ECS Simulation 
*
*   FUNCTION NAME(S)
*   tcsEcInitCAD - initialise variables for the Enclosure simulator
*   tcsEcMoveCAD - implement the Enclosure move command
*   tcsEcMoveDomeCAD - implement the moveDome command
*   tcsEcMoveShtrsCAD - implement the moveShtrs command
*   tcsECmoveVgatesCAD - implement the moveVgates command
*   tcsEcParkCAD      - implement the park command
*   tcsEcParkDomeCAD - implement the parkDome command
*   tcsEcParkShtrsCAD - implement the parkShtrs command
*   tcsEcParkVgatesCAD - implement the parkVgates command
*   tcsEcsSimOutput   - provides output from global memory 
*   tcsEcsSimulate - simulate the movement of the dome and shutters 
*   tcsEcsComplete - signal completion of a move command
*   tcsEcStop - stop enclosure
*   tcsECthermalCAD  - implement the thermal command
*   tcsEcGenericCAD - General purpose CAD routine
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEcsSimulation.c,v $
 * Revision 1.5  2003/03/13 01:29:48  cjm
 * Mimic behaviour of real PLC and discard shutter demands whilst moving
 *
 * Revision 1.4  2001/05/17 14:50:37  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.3  1999/06/16 21:26:49  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.2  1999/05/12 06:04:58  cjm
 * Allow az demand of less than 0.0
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.19  1998/09/14 22:00:00  tcs
 * Implement in position
 *
 * Revision 1.18  1998/09/05 01:49:30  tcs
 * Output in position flags
 *
 * Revision 1.17  1998/05/22 07:33:04  cjm
 * Generate extra ECS SAD items in tcsEcsSimOutput
 *
 * Revision 1.16  1998/05/19 13:51:10  cjm
 * Handle shutdown mode in thermal command
 *
 * Revision 1.15  1998/03/31 11:22:06  cjm
 * Changes to match ECS gamma release of March 98
 *
 * Revision 1.14  1998/03/24 14:58:20  cjm
 * Change subroutine names to accommodate latest ECS CAD names
 *
 * Revision 1.13  1998/02/10 15:44:43  pbt
 * Get shutter limits via EPICS record links
 *
 * Revision 1.12  1997/11/21 17:06:55  pbt
 * Changed status output from simulator : no menuCarstatesERROR now returned
 *
 * Revision 1.11  1997/11/20 12:33:58  pbt
 * Change GenericCAD routines to copy input to output fields
 *
 * Revision 1.10  1997/09/24 16:32:42  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.9  1997/09/23 11:50:05  tcs
 * Remove redundant includes
 *
 * Revision 1.8  1997/09/23 09:43:56  pbt
 * Removed carOR routine
 *
 * Revision 1.7  1997/07/23 13:28:55  cjm
 * Enhanced simulator to match latest ECS ICD
 *
 * Revision 1.6  1997/07/15 13:37:36  cjm
 * Updated to handle top & bottom shutter
 *
 * Revision 1.5  1997/06/24 15:31:00  pbt
 * Corrected erroneous rejection for menuDirectiveCLEAR directives
 *
 * Revision 1.4  1997/06/23 14:39:21  pbt
 * Extra routines for ECS simulation
 *
 * Revision 1.3  1997/04/16 15:57:21  pbt
 * Use symbol CAD_REJECT consistently
 *
 * Revision 1.2  1997/03/05 10:06:34  tcs
 * Update servo parameters
 *
 * Revision 1.1  1997/02/10 17:10:35  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.10  1996/12/10 17:58:27  pbt
 * Simulator CADs now set followS value via output VALA field
 *
 * Revision 1.9  1996/12/03 12:32:21  pbt
 * Increase position accuracy required to be 'in position'
 *
 * Revision 1.8  1996/11/28 08:09:31  cjm
 * Fix triggering of activeC and trackid
 *
 * Revision 1.7  1996/11/20 18:08:33  pbt
 * Changed kernel and simulation code to use genSub records
 *
 * Revision 1.6  1996/11/12 18:05:34  pbt
 * Various updates : STOP command and MOVE command default parameters
 *
 * Revision 1.5  1996/11/07 15:07:52  pbt
 * Stop sets to STOPPING state. Corrected bug in completion test (stateAz->stateEl)
 *
 * Revision 1.4  1996/07/24 14:00:27  tcs
 * improved servo parameters
 *
 * Revision 1.3  1996/07/23 14:59:18  tcs
 * tidy up routine names and add header to include files
 *
 * Revision 1.2  1996/07/23 10:03:40  tcs
 * Add TEST & PARK plus generic CAD mechanism
 *
 * Revision 1.1  1996/07/19 13:39:15  tcs
 * Enclosure simulator
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

#include "tcsEcs.h"
#include "tcsConstants.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "tcsServo.h"
#include "timeLib.h"

static double minBotShtr = 0.5;       /* Min elevation of bottom shutter */
static double maxBotShtr = 63.7;      /* Max elevation of bottom shutter */
static double minTopShtr = 10.6;      /* Min elevation of top shutter */
static double maxTopShtr = 105.0;     /* Max elevation of top shutter */

/* State of axes */
static int StateAz;
static int StateEl;
static int MoveActive;

/* Shutter seal status */
static char shtrSealed[7] ;

/* Demand position from move command */
static double aztarget;
static double elTopTarget;
static double elBotTarget;

static double az;          /* current azimuth */
static double elTop;       /* current elevation of top shutter */
static double elBot;       /* current elevation of bottom shutter */

/*+
 *   Function name:
 *   tcsEcInit
 *
 *   Purpose:
 *   Initialise the internal simulation of the enclosure control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the enclosure control system.
 *
 *   Invocation:
 *   tcsEcInit()
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

void tcsEcInit (void )
{
   static int first = TRUE;

   if (first) first = FALSE;
   StateAz = STOPPED;
   StateEl = STOPPED;
}

long tcsEcFollowCAD (struct cadRecord *pcad)
{

/* CAD directive is in field DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
      StateAz = FOLLOWING;
      StateEl = FOLLOWING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"On");
      return 0;
      break;  /* End menuDirectiveSTART */

/* The STOP CAD directive simply sets the axis
   state flags to STOPPED   */

   case menuDirectiveSTOP:
      StateAz = STOPPED;
      StateEl = STOPPED;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      strcpy(pcad->vala,"Off");
      return 0;

   default :
      return 0;
      break;
   }
}

/*+
 *   Function name:
 *   tcsEcMoveCAD
 *
 *   Purpose:
 *   Implement the Move CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the move CAD record in the enclosure simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record.  
 *   Due to changes in interface specifications etc. this CAD is now never
 *   triggerred directly but is instead activated by other CADs in the 
 *   simulator. 
 *
 *   Invocation:
 *   tcsEcMoveCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   a => enclosure azimuth demand (degs)
 *   b => top shutter elevation demand (degs)
 *   c => bottom shutter elevation demand (degs)
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
 *   This command only exists for historical reasons. It should be removed 
 *   and the relevant subroutine code added to move_shtrs and move_dome. 
 *   Currently the limits are hardcoded, this needs to be changed
 *-
 */

long tcsEcMoveCAD (struct cadRecord *pcad)
{
   double azMove, elTopMove, elBotMove;
   int azNitem, elTopNitem, elBotNitem;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
   case menuDirectivePRESET:
      strcpy(pcad->mess, "Move: arguments are valid");
      azNitem = sscanf (pcad->a, "%lf ", &azMove);
      if ( azNitem < 1)
      {
         azMove = az/3600.0 ;
      }
      else if (azMove < 0.0 || azMove > 360.0)
      {
         strcpy(pcad->mess, "Move: azimuth out of range");
         return CAD_REJECT;
      }

      elTopNitem = sscanf (pcad->b, "%lf ", &elTopMove);
      if ( elTopNitem < 1)
      {
        elTopMove = elTop/3600.0 ;
      }
      else if (elTopMove < 0.5 || elTopMove > 106.5)
      {
         strcpy(pcad->mess, "Move: elevation out of range");
         return CAD_REJECT;
      }
  
      elBotNitem = sscanf (pcad->c, "%lf ", &elBotMove);
      if ( elBotNitem < 1)
      {
        elBotMove = elBot/3600.0 ;
      }
      else if (elBotMove < 0.5 || elBotMove > 60.0)
      {
         strcpy(pcad->mess, "Move: elevation out of range");
         return CAD_REJECT;
      }
  
/* Must have at least one of Az and El specified */
      if (azNitem < 1 && elTopNitem < 1 && elBotNitem < 1) 
      {
        strcpy(pcad->mess, "Move: No az or el specified");
        return CAD_REJECT;
      }        

      aztarget = azMove * 3600;
      elTopTarget = elTopMove * 3600;
      elBotTarget = elBotMove * 3600;
      if (pcad->dir == menuDirectiveSTART) 
      {
         StateAz = MOVING;
         StateEl = MOVING;
         MoveActive = TRUE;
      }
      strcpy(pcad->vala,"Off");
      strcpy(pcad->mess, "Command accepted");

      return 0;
      break;   /* End PmenuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateAz = STOPPING;
      StateEl = STOPPING;

/* Output acceptance message */

      strcpy(pcad->vala,"Off");
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
 *   tcsEcMoveDomeCAD
 *
 *   Purpose:
 *   Implement the move_dome CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the move_dome CAD record in the enclosure
 *   simulator. It checks the input data for validity and then sets
 *   a flag to let the simulator know there is a new target position
 *   and that the dome state is "moving" 
 *
 *   Invocation:
 *   tcsEcMoveDomeCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   b => enclosure azimuth demand (degs)
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
 *-
 */

long tcsEcMoveDomeCAD (struct cadRecord *pcad)
{
   double azMove;
   int azNitem;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
   case menuDirectivePRESET:
      strcpy(pcad->mess, "Move: arguments are valid");
      azNitem = sscanf (pcad->b, "%lf ", &azMove);
      if ( azNitem < 1)
      {
         azMove = az/3600.0 ;
      }
      else if (azMove < -360.0 || azMove > 360.0)
      {
         strcpy(pcad->mess, "Move: azimuth out of range");
         return CAD_REJECT;
      }

      if (azMove < 0.0) azMove += 360.0 ;
      aztarget = azMove * 3600;
      if (pcad->dir == menuDirectiveSTART) 
      {
         StateAz = MOVING;
         MoveActive = TRUE;
      }

      return CAD_ACCEPT;
      break;   /* End menuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateAz = STOPPING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      return CAD_ACCEPT;
      break;

   default:
      return CAD_ACCEPT;
      break;
   }
}

/*+
 *   Function name:
 *   tcsEcMoveShtrsCAD
 *
 *   Purpose:
 *   Implement the move_shtrs CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the move_shtrs CAD record in the 
 *   enclosure simulator.
 *   The directives START and STOP are supported although in practice 
 *   STOP will probably be moved to a separate record.  
 *
 *   Invocation:
 *   tcsEcMoveShtrsCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   b => top shutter elevation demand (degs)
 *   c => bottom shutter elevation demand (degs)
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
 *-
 */

long tcsEcMoveShtrsCAD (struct cadRecord *pcad)
{
   double elTopMove, elBotMove;
   int elTopNitem, elBotNitem;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectiveSTART:
   case menuDirectivePRESET:
      strcpy(pcad->mess, "Move: arguments are valid");

      elTopNitem = sscanf (pcad->b, "%lf ", &elTopMove);

      if ( elTopNitem < 1)
      {
        elTopMove = elTop/3600.0 ;
      }
      else if ((elTopMove < minTopShtr) || (elTopMove > maxTopShtr))
      {
         strcpy(pcad->mess, "move_shtrs: elevation out of range");
         return CAD_REJECT;
      }
  
      elBotNitem = sscanf (pcad->c, "%lf ", &elBotMove);
      if ( elBotNitem < 1)
      {
        elBotMove = elBot/3600.0 ;
      }
      else if ((elBotMove < minBotShtr) || (elBotMove > maxBotShtr))
      {
         strcpy(pcad->mess, "move_shtrs: elevation out of range");
         return CAD_REJECT;
      }
  
      elTopTarget = elTopMove * 3600;
      elBotTarget = elBotMove * 3600;
      if (pcad->dir == menuDirectiveSTART) 
      {
         StateEl = MOVING;
         MoveActive = TRUE;
      }
      strcpy(pcad->mess, "Command accepted");

      return CAD_ACCEPT;
      break;   /* End PmenuDirectiveSTART or menuDirectivePRESET */

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateEl = STOPPING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      return CAD_ACCEPT;
      break;

   default:
      return CAD_ACCEPT;
      break;
   }
}

/*+
 *   Function name:
 *   tcsECmoveVgatesCAD
 *
 *   Purpose:
 *   Implement the moveVgates CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the moveVgates CAD record in the 
 *   enclosure simulator.
 *
 *   Invocation:
 *   tcsECmoveVgatesCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Epics input parameters:
 *
 *   b => East vent gate position
 *   c => West vent gate position
 *
 *   Epics output parameters:
 *   
 *   valb => East vent gate position
 *   valc => West vent gate position
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

long tcsECmoveVgatesCAD (struct cadRecord *pcad)
{
   static double vgEmove, vgWmove;
   int vgNEitem, vgNWitem;
   long ret = CAD_ACCEPT;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:
      strncpy(pcad->mess, "moveVgates: arguments are valid", MAX_STRING_SIZE);
      vgNEitem = sscanf (pcad->b, "%lf ", &vgEmove);
      if ( vgNEitem < 1)
      {
         vgEmove = 0.0 ;
      }
      else if (vgEmove < 0.0 || vgEmove > 100.0)
      {
         strcpy(pcad->mess, "moveVgates: East position out of range");
         ret =  CAD_REJECT;
      }

      vgNWitem = sscanf (pcad->c, "%lf ", &vgWmove);
      if ( vgNWitem < 1)
      {
         vgWmove = 0.0 ;
      }
      else if (vgWmove < 0.0 || vgWmove > 100.0)
      {
         strcpy(pcad->mess, "moveVgates: West position out of range");
         ret =  CAD_REJECT;
      }

  
/* Must have at least one of West & East position specified */
      if (vgNEitem < 1 && vgNWitem < 1) 
      {
        strcpy(pcad->mess, "moveVgates: No positions specified");
        ret = CAD_REJECT;
      }        

      break;   /* End menuDirectivePRESET */

   case menuDirectiveSTART:

      *(double *)pcad->valb = vgEmove ;
      *(double *)pcad->valc = vgWmove ;
      break ;

   case menuDirectiveMARK:
   case menuDirectiveSTOP:
   case menuDirectiveCLEAR:
      break;

   default:
      strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
      ret = CAD_REJECT;
      break;
   }

   return ret;
}

/*+
 *   Function name:
 *   tcsEcPark
 *
 *   Purpose:
 *   Implement the ECS park command
 *
 *   Description:
 *   The park command parks the dome, shutters and vent gates. It does
 *   this by fanning out the park command to the lower level commands
 *   park_dome, park_shtrs and park_vgates. The fanning out is achieved
 *   by this routine which simply passes on whatever command directives it
 *   receives to the above three commands. 
 *
 *   Invocation:
 *   tcsEcPark (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pcad   (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsEcPark (struct cadRecord *pcad)
{
   *(long *)pcad->vala = pcad->dir;
   *(long *)pcad->valb = pcad->dir;
   *(long *)pcad->valc = pcad->dir;
   return CAD_ACCEPT;
}
/*+
 *   Function name:
 *   tcsEcParkDomeCAD
 *
 *   Purpose:
 *   Implement the park_dome CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the parkDome CAD record in the enclosure
 *   simulator. It checks the input data for validity and then sets
 *   a flag to let the simulator know there is a new target position
 *   and that the dome state is "moving". In this regard it acts the
 *   same as the moveDome command. 
 *
 *   Invocation:
 *   tcsEcParkDomeCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   b => enclosure azimuth demand for "position" tag (degs)
 *   c => identifier for park position
 *   d => default azimuth park position (degs)
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
 *   The code always uses the same default park position whenever the 
 *   park identifier isn't "POSITION".
 *
 *-
 */

long tcsEcParkDomeCAD (struct cadRecord *pcad)
{
   static char *parkOpts[] = {"DEFAULT","POSITION","ACCESS1","ACCESS2","ACCESS3" } ;
   static double azPark ;                 /* Az park position (degs) */
   static long parkId ;                   /* Index to park identifier */
   long status;                           /* Return status */

/* Set message prefix */

   tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT ;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

     status = CAD_REJECT ;

     if (tcsDcLong ("id : ", pcad->c, &parkId, pcad) ) break ;

/* For simulator accept any string as valid park identifier and use the 
*  default park azimuth. If the identiifer is "position" however than use
*  the user supplied azimuth 
*/

     if (strncmp (parkOpts[parkId], "POSITION", 8 ) == 0) {
       if (tcsDcDouble ("az: ", pcad->b, &azPark, pcad))
         break ;
     } else {
       if (tcsDcDouble ("az: ", pcad->d, &azPark, pcad))
         break ;
     }

     if (azPark < 0.0 || azPark > 360.0) {
       tcsCsAppendMessage (pcad, "Dome az. out of range") ;
       break ;
     }

     status = CAD_ACCEPT ;
     break ;

   case menuDirectiveSTART :

/* Copy data to ECS simulator */

     aztarget = azPark * 3600.0 ;
     StateAz = MOVING ;
     MoveActive = TRUE ;
     break ;

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateAz = STOPPING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      break;

   default:
      break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsEcParkShtrsCAD
 *
 *   Purpose:
 *   Implement the park_shtrs CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the park_shtrs CAD record in the enclosure
 *   simulator. It checks the input data for validity and then sets
 *   a flag to let the simulator know there is a new target position
 *   and that the dome state is "moving". In this regard it acts the
 *   same as the move_shtrs command. 
 *
 *   Invocation:
 *   tcsEcParkShtrsCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   d => default bottom shutter park position (degs)
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
 *-
 */

long tcsEcParkShtrsCAD (struct cadRecord *pcad)
{
   static double shtrPark ;               /* shutter park position */
   long status;                           /* Return status */

/* Set message prefix */

   tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT ;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

     status = CAD_REJECT ;

     if (tcsDcDouble ("position : ", pcad->d, &shtrPark, pcad))
      break ;

     if ( shtrPark < minTopShtr || shtrPark > maxTopShtr) {
       tcsCsAppendMessage (pcad, "top shutter out of range") ;
       break ;
     }

     if ( shtrPark < minBotShtr || shtrPark > maxBotShtr) {
       tcsCsAppendMessage (pcad, "bottom shutter out of range") ;
       break ;
     }
     status = CAD_ACCEPT ;
     break ;

   case menuDirectiveSTART :

/* Copy data to ECS simulator */

     elTopTarget = shtrPark * 3600.0 ;
     elBotTarget = shtrPark * 3600.0 ;
     StateEl= MOVING ;
     MoveActive = TRUE ;
     break ;

/* This routine is called by the CAD STOP directive
   It simply sets the axis state flags to STOPPED   */
   case menuDirectiveSTOP:  
      StateEl = STOPPING;

/* Output acceptance message */

      strcpy(pcad->mess, "Command accepted");
      break;

   default:
      break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsEcParkVgatesCAD
 *
 *   Purpose:
 *   Implement the park_vgates CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the park_vgates CAD record in the enclosure
 *   simulator. The routine fetches the default park positions for 
 *   the east and west vent gates and then forwards them to the moveVgates
 *   CAD record 
 *
 *   Invocation:
 *   tcsEcParkVgatesCAD (pcad)
 *
 *   Epics input parameters:
 *  
 *   d => default vent gate park position 
 *
 *   Epics output parameters:
 * 
 *   vala => East vent gate demand position
 *   valb => West vent gate demand position
 *   vald => Directive to the move_vgates CAD record 
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
 *-
 */

long tcsEcParkVgatesCAD (struct cadRecord *pcad)
{
   static double gatePark ;               /* vent gate  park position */
   long status;                           /* Return status */

/* Set message prefix */

   tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

   status = CAD_ACCEPT ;

/* The CAD directive is field  DIR */
   switch (pcad->dir)
   {
   case menuDirectivePRESET:

     status = CAD_REJECT ;

     if (tcsDcDouble ("position: ", pcad->d, &gatePark, pcad))
      break ;

     if (gatePark < 0.0 || gatePark > 1.0) {
       tcsCsAppendMessage (pcad, "gate out of range") ;
       break ;
     }

     *(long *)pcad->vald = pcad->dir;
     status = CAD_ACCEPT ;
     break ;

   case menuDirectiveSTART :

/* Trigger the moveVgates command */

   strncpy (pcad->vala, pcad->d, MAX_STRING_SIZE) ;
   strncpy (pcad->valb, pcad->d, MAX_STRING_SIZE) ;
   *(long *)pcad->vald = pcad->dir;

     break ;

   default:
      *(long *)pcad->vald = pcad->dir;
      break;
   }

   return status ;
}

/*+
 *   Function name:
 *   tcsECthermalCAD
 *
 *   Purpose:
 *   Implement the thermal CAD record in the enclosure simulator
 *
 *   Description:
 *   This function implements the thermal CAD record in the 
 *   enclosure simulator. The demand mode is verified and then copied
 *   to the output.
 *
 *   Invocation:
 *   tcsECthermalCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  pointer to cadRecord structure
 *
 *   Epics input parameters:
 *
 *   a => Mode demand either "0", "1" or "2"
 *
 *   Epics output oarameters:
 *
 *   vala => mode demand either 0, 1 or 2 
 *
 *   Function value:
 *   Return status
 *
 *   Prior requirements:
 *   None
 *
 *-
 */

long tcsECthermalCAD (struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    static long modeId ;
    static char *thermMode[] = {"PASSIVE", "ACTIVE", "SHUTDOWN"} ;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL) ;

   switch (pcad->dir)
   {
   case menuDirectivePRESET:

      ret = CAD_REJECT ;

      if (!tcsDcLen(pcad->a)) {
       tcsCsAppendMessage (pcad, "Mode is null") ;
       break ;
      }
      if (tcsDcLong ("mode : ", pcad->a, &modeId, pcad)) break ;
 
      if (!strncmp(thermMode[modeId],"PASSIVE",7) &&
          !strncmp(thermMode[modeId],"ACTIVE",6)  &&
          !strncmp(thermMode[modeId], "SHUTDOWN", 8)) {
        tcsCsAppendMessage (pcad, "Mode must be ACTIVE, PASSIVE or SHUTDOWN");
        break ;
      }

      ret = CAD_ACCEPT ;
      break;   /* End menuDirectivePRESET */

   case menuDirectiveSTART:

      *(long *)pcad->vala = modeId ;
      break ;

   case menuDirectiveMARK:
   case menuDirectiveSTOP:
   case menuDirectiveCLEAR:
      break;

   default:
      tcsCsAppendMessage(pcad, "Unknown CAD directive");
      ret = CAD_REJECT;
      break;
   }

   return ret;
}


/*+
 *   Function name:
 *   tcsEcsSimOutput
 *
 *   Purpose:
 *   Makes local memory data available to EPICS
 *
 *   Description:
 *   This routine makes data held in C variables visible to Epics. It is
 *   only needed due to running out of output links in the tcsEcsSimulate
 *   routine.
 *
 *   Invocation:
 *   tcsEcsSimOutput (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *) Pointer to gensub structure
 *
 *   Epics inputs:
 *  
 *   b => thermal mode
 *
 *   Epics outputs :
 *  
 *   vala => Whether follow mode is "On" or "Off"
 *   valb => Thermal mode
 *   valc => Shutter sealed status
 *   vald => Bottom shutter state
 *   vale => Top shutter state
 *   valf => Dome state
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsEcsSimOutput (struct genSubRecord *pgsub)

{
   static char *thermalModes[] = {"Passive", "Active_Low", "Active_Hi",
                                  "Shutdown"} ;
   int mode ;         

/* Set following string */
   if ((StateAz == FOLLOWING) && (StateEl == FOLLOWING)) 
     strcpy (pgsub->vala, "On") ;
   else
     strcpy (pgsub->vala, "Off") ;

/* Fetch thermal mode and set output string */
   mode = floor(*(double *)pgsub->b) ;
   if (mode < 0 || mode > 3)
     strcpy (pgsub->valb, "Error") ;
   else
     strcpy (pgsub->valb, thermalModes[mode]) ;

/* Output the shutter sealed status */
   strcpy (pgsub->valc, shtrSealed) ;

/* Set output strings for the dome and shutter status */

   switch (StateEl) {

     case STOPPED:
        strcpy (pgsub->vald, "Stopped") ;
        strcpy (pgsub->vale, "Stopped") ;
        break ;

     case MOVING:
     case FOLLOWING:
        strcpy (pgsub->vald, "Moving") ;
        strcpy (pgsub->vale, "Moving") ;
        break ;

     case STOPPING:
        strcpy (pgsub->vald, "Stopping");
        strcpy (pgsub->vale, "Stopping");
        break ;

     default:
        strcpy (pgsub->vald, "Error");
        strcpy (pgsub->vale, "Error");
        break ;

   }

   switch (StateAz) {

     case STOPPED:
        strcpy (pgsub->valf, "Stopped") ;
        break ;

     case MOVING:
     case FOLLOWING:
        strcpy (pgsub->valf, "Moving") ;
        break ;

     case STOPPING:
        strcpy (pgsub->valf, "Stopping");
        break ;

     default:
        strcpy (pgsub->valf, "Error");
        break ;

   }


   return 0 ;
   
}

/*+
 *   Function name:
 *   tcsEcsShutLimits
 *
 *   Purpose:
 *   Get shutter limits from EPIC records
 *
 *   Description:
 *    Drag in the minimum and maximum top and bootom
 *    shutter limits from the records in the simulator.
 *    Store the values in variables global to this module.
 *
 *   Epics inputs :
 *
 *   a => Minimum Bottom Shutter position (degs.)
 *   b => Maximum Bottom Shutter position (degs.)
 *   c => Minimum Top Shutter position (degs.)
 *   d => Maximum Top Shutter position (degs.)
 *
 *   Invocation:
 *   tcsEcsShutLimits (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pgsub (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsEcsShutLimits (struct genSubRecord *pgsub)

{
   minBotShtr =  *(double *)(pgsub->a) ;
   maxBotShtr =  *(double *)(pgsub->b) ;
   minTopShtr =  *(double *)(pgsub->c) ;
   maxTopShtr =  *(double *)(pgsub->d) ;
   return 0 ;
   
}


/*+
 *   Function name:
 *   tcsEcsSimulate
 *
 *   Purpose:
 *   Simulates behaviour of enclosure & shutters without any hardware
 *
 *   Description:
 *   This routine is linked to the TcsEcsSimulate record and performs the main
 *   simulation of the Enclosure. The dome and shutters each have their
 *   own servo loop with realistic parameters so that moving a mechanism
 *   to a demand position behaves like the real hardware. 
 *   The simulation mimcs the behaviour of the real PLC which ignores
 *   new demands if the shutter is already moving. 
 *
 *   Epics inputs :
 *
 *   b => azimuth default for dome (degrees)
 *   d => elevation default for shutters (degress)
 *   h => max dome velocity (degs/s)
 *   j => max shutter velocity (deg/s)
 *   f => input demand array for ECS from TCS kernel :
 *      Element 0  = Time when data sent
 *      Element 1  = Target time
 *      Element 2  = Track identifier
 *      Element 3  = Demanded Azimuth
 *      Element 4  = Demanded Top Shutter Elevation
 *      Element 5  = Demanded Bottom Shutter Elevation
 *
 *   Outputs :
 * 
 *   vala => current azimuth (rads)
 *   valb => current top shutter elevation (rads)
 *   valc => current bottom shutter elevation (rads)
 *   vald => azimuth error (rads)
 *   vale => top shutter elevation error (rads)
 *   valf => bottom shutter elevation error (rads)
 *   valg => status
 *   valh => track identifier
 *   vali => link selection flag
 *   valj => State of shutters 0 = Open, 1 = Closed
 *   valk => dome in position;
 *   vall => top shutter in position;
 *   valm => bottom shutter in position;
 *   valn => overall in  position;
 *
 *   Invocation:
 *   tcsEcsSimulate(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (genSubRecord *) pointer to genSub record structure
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

long tcsEcsSimulate (genSubRecord *pgsub) 

{

   static int first = TRUE;
   static int substat;        /* subsystem status */
   static double trackid;     /* current track id */

   static double azv;         /* current velocity */
   static double azerr;       /* azimuth error */

   static double elvTop;         /* current velocity */
   static double elerrTop ;      /* elevation error */

   static double elvBot;         /* current velocity */
   static double elerrBot ;      /* elevation error */

   unsigned long arraySize ;  /* number of elements in inout demand array */
   double ECSdemand[6] ;      /* demand data array from kernel */
   double azdemand;           /* azimuth demand */
   double elTopdemand;           /* elevation demand */
   double elBotdemand;           /* elevation demand */
   double azStop ;            /* Az demand when stopping */
   double elTopStop ;         /* Top shutter demand when stopping */
   double elBotStop ;         /* Bottom shutter demand when stopping */
   double newtrack;           /* track id of demand */
   int newstat;               /* new subsystem status */
   int inPositionAz;          /* in position Az flag */
   int inPositionEl;          /* in position El flag */
   int inPosition;            /* All in position flag */
   int inPositionTopEl;          /* in position flag */
   int inPositionBotEl;          /* in position flag */
   int stateAz;               /* local copy of azimuth state */
   int stateEl;               /* local copy of elevation state */

   static double tappl;      /* time for which demands are correct */
   double now;                /* current time */
   int linkSelect;            /* Mask for downstream processing */
   double del ;               /* Elevation difference top & bot shutter */

   static int topStillMoving = 0;
   static int botStillMoving = 0;
   static double topCurrDemand ;
   static double botCurrDemand ;

   static struct ServoState servoStateAz;
   static struct ServoState servoStateTopEl;
   static struct ServoState servoStateBotEl;
   static struct ServoConfig servoConfigAz;
   static struct ServoConfig servoConfigTopEl;
   static struct ServoConfig servoConfigBotEl;

/* Get a local copy of the axis states as the global values may get changed
   from elsewhere */

   stateAz = StateAz;
   stateEl = StateEl;

      if (first)            /* set "last" position to default position */
      {
         servoConfigAz.dvmax = 300.0;
         servoConfigAz.gs = 15.0;
         servoConfigAz.gp = 4.0;
         servoConfigAz.gi = 0.4;
         servoConfigAz.pi = 50.0;
         servoConfigAz.pok = 180.0;
         servoConfigAz.tok = 0.1;
         servoStateAz.pdtold = *(double *)pgsub->b * 3600.0;
         servoConfigAz.noise = 0.0;
         timeNow( &(servoStateAz.told) );
         servoStateAz.told -= 0.5;
         servoStateAz.tout = servoStateAz.told;
         servoStateAz.vd = 0.0;
         servoStateAz.accum = 0.0;
         az = servoStateAz.pdtold;
         azv = 0.0;
/* Top shutter*/
         servoConfigTopEl.dvmax = 300.0;
         servoConfigTopEl.gs = 15.0;
         servoConfigTopEl.gp = 4.0;
         servoConfigTopEl.gi = 0.4;
         servoConfigTopEl.pi = 50.0;
         servoConfigTopEl.pok = 180.0;
         servoConfigTopEl.tok = 0.1;
         servoStateTopEl.pdtold = *(double *)pgsub->d * 3600.0;
         servoConfigTopEl.noise = 0.0;
         timeNow( &(servoStateTopEl.told) );
         servoStateTopEl.told -= 0.5;
         servoStateTopEl.tout = servoStateTopEl.told;
         servoStateTopEl.vd = 0.0;
         servoStateTopEl.accum = 0.0;
         elTop = servoStateTopEl.pdtold;
         elvTop = 0.0;
         topCurrDemand = elTop ;
/* Bottom shutter*/
         servoConfigBotEl.dvmax = 300.0;
         servoConfigBotEl.gs = 15.0;
         servoConfigBotEl.gp = 4.0;
         servoConfigBotEl.gi = 0.4;
         servoConfigBotEl.pi = 50.0;
         servoConfigBotEl.pok = 180.0;
         servoConfigBotEl.tok = 0.1;
         servoStateBotEl.pdtold = *(double *)pgsub->d * 3600.0;
         servoConfigBotEl.noise = 0.0;
         timeNow( &(servoStateBotEl.told) );
         servoStateBotEl.told -= 0.5;
         servoStateBotEl.tout = servoStateBotEl.told;
         servoStateBotEl.vd = 0.0;
         servoStateBotEl.accum = 0.0;
         elBot = servoStateBotEl.pdtold;
         elvBot = 0.0;
         botCurrDemand = elBot ;

         newstat = menuCarstatesIDLE;
         substat = -1;
         trackid = 0.0;
         first = FALSE;
      }

/* fetch latest velocities etc */

      servoConfigAz.vtmax = *(double *)pgsub->h * 3600.0;
      servoConfigTopEl.vtmax = *(double *)pgsub->j * 3600.0;
      servoConfigBotEl.vtmax = *(double *)pgsub->j * 3600.0;

/* Read in input demand array data from kernel */
      arraySize = pgsub->nof ;
      memcpy(ECSdemand, pgsub->f, arraySize * sizeof(double)) ;
      tappl    = ECSdemand[1] ;
      newtrack = ECSdemand[2] ;
      azdemand = ECSdemand[3] / AS2R;
      elTopdemand = ECSdemand[4] / AS2R;
      elBotdemand = ECSdemand[5] / AS2R;

/* send demands to servos */
      if (stateAz == MOVING)
      {
         if ( (aztarget - servoStateAz.pdtold) < -648000.0 )
         {
            aztarget += 1296000.0;
         }
         else if ( (aztarget - servoStateAz.pdtold) > 648000.0 )
         {
            aztarget -= 1296000.0;
         }
         timeNow( &now );
         inPositionAz = tcsServo( now, aztarget, 0, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = aztarget - az;
      }
      else if (stateAz == FOLLOWING)
      {
         if ( (azdemand - servoStateAz.pdtold) < -648000.0 )
         {
            azdemand += 1296000.0;
         }
         else if ( (azdemand - servoStateAz.pdtold) > 648000.0 )
         {
            azdemand -= 1296000.0;
         }
         inPositionAz = tcsServo( tappl, azdemand, 0, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = azdemand - az;
      }
      else
      {
         timeNow( &now );
         azStop = az ;
         inPositionAz = tcsServo( now, azStop, 1, &servoConfigAz, 
            &servoStateAz, &az, &azv);
         azerr = azStop - az ;
      }
      if ( az >= 1296000.0 )
      {
         az -= 1296000.0;
         servoStateAz.pdtold -= 1296000.0;
      }
      else if ( az < 0.0 )
      {
         az += 1296000.0;
         servoStateAz.pdtold += 1296000.0;
      }

      if (stateEl == MOVING)
      {
         if (!topStillMoving)
           topCurrDemand = elTopTarget ;
         timeNow( &now );
         inPositionTopEl = tcsServo( now, topCurrDemand, 0, &servoConfigTopEl, 
            &servoStateTopEl, &elTop, &elvTop);
         elerrTop = elTopTarget - elTop;
      }
      else if (stateEl == FOLLOWING)
      {
         inPositionTopEl = tcsServo( tappl, elTopdemand, 0, &servoConfigTopEl, 
            &servoStateTopEl, &elTop, &elvTop);
         elerrTop = elTopdemand - elTop;
      }
      else
      {
         timeNow( &now );
         elTopStop = elTop;
         inPositionTopEl = tcsServo( now, elTopStop, 1, &servoConfigTopEl, 
            &servoStateTopEl, &elTop, &elvTop);
         elerrTop = elTopStop - elTop;
      }

      if (stateEl == MOVING) {
         if (!botStillMoving)
           botCurrDemand = elBotTarget ;
         timeNow( &now );
         inPositionBotEl = tcsServo( now, botCurrDemand, 0, &servoConfigBotEl, 
            &servoStateBotEl, &elBot, &elvBot);
         elerrBot = elBotTarget - elBot;
      }
      else if (stateEl == FOLLOWING)
      {
         inPositionBotEl = tcsServo( tappl, elBotdemand, 0, &servoConfigBotEl, 
            &servoStateBotEl, &elBot, &elvBot);
         elerrBot = elBotdemand - elBot;
      }
      else
      {
         timeNow( &now );
         elBotStop = elBot ;
         inPositionBotEl = tcsServo( now, elBotStop, 1, &servoConfigBotEl, 
            &servoStateBotEl, &elBot, &elvBot);
         elerrBot = elBotStop - elBot;
      }

/* Detemine new subsystem state */

      if (inPositionTopEl) 
        topStillMoving = 0 ;
      else
        topStillMoving = 1 ;

      if (inPositionBotEl)
        botStillMoving = 0 ;
      else 
        botStillMoving = 1;

      inPositionEl = inPositionTopEl && inPositionBotEl;

/* Set separate Az/El states if they are in position, not Following */
      if ( inPositionAz && ( stateAz == MOVING || stateAz == STOPPING ) )
         StateAz = STOPPED;
      if ( inPositionEl && ( stateEl == MOVING || stateEl == STOPPING ) )
         StateEl = STOPPED;

 /* Detemine new subsystem state */
      inPosition   = inPositionEl && inPositionAz ;
      if (inPosition)
         {
         if ( stateAz == STOPPED && stateEl == STOPPED )
           {
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

/* Check if shutters are open or closed */

      del = elTop - elBot;
      if (del < 0.0) del = -del;

/* now output the results */
 
      *(double *)pgsub->vala = az * AS2R;
      *(double *)pgsub->valb = elTop * AS2R;
      *(double *)pgsub->valc = elBot * AS2R;
      *(double *)pgsub->vald = azerr * AS2R;
      *(double *)pgsub->vale = elerrTop * AS2R;
      *(double *)pgsub->valf = elerrBot * AS2R;
      *(double *)pgsub->valg = substat;
      *(double *)pgsub->valh = trackid;
      *(long *)pgsub->vali   = (long)linkSelect;
      if (del < 360.0) {
        *(double *)pgsub->valj = 1.0 ;
        strcpy (shtrSealed, "Closed") ;
      } else {
        *(double *)pgsub->valj = 0.0 ;
        strcpy (shtrSealed, "Open") ;
      }
      *(long *)pgsub->valk   = (long)inPositionAz;
      *(long *)pgsub->vall   = (long)inPositionTopEl;
      *(long *)pgsub->valm   = (long)inPositionBotEl;
      *(long *)pgsub->valn   = (long)inPosition;

      return 0;
}
  
/*+
 *   Function name:
 *   tcsEcsComplete
 *
 *   Purpose:
 *   Signal complete of a move command
 *
 *   Description:
 *   Signals completion of a move command by writing IDLE to the appropriate
 *   CAR record.
 *
 *   Invocation:
 *   tcsEcsComplete(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub    (genSubRecord *) pointer to genSub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsEcsComplete (genSubRecord *psub)
{

/* output values for CAR Message and State fields */

   strcpy(psub->valb, "Stopped");
   *(double *)psub->vala = menuCarstatesIDLE;
   return 0;
}

/*+
 *   Function name:
 *   tcsEcStop
 *
 *   Purpose:
 *   Stops the mount
 *
 *   Description:
 *
 *   Invocation:
 *   tcsEcStop
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

long tcsEcStop (struct genSubRecord *pgsub)
{
   StateAz = STOPPING;
   StateEl = STOPPING;
   strncpy(pgsub->vala, "Off", 3);
   return(0);
}

/*+
 *   Function name:
 *   tcsECstopDomeCAD
 *
 *   Purpose:
 *   Implement the stopDome ECS routine
 *
 *   Description:
 *   Simply set the flag to indicate the dome motion is stopped.
 *
 *   Invocation:
 *   tcsECstopDomeCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pcad   (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsECstopDomeCAD (struct cadRecord *pcad)
{
   StateAz = STOPPING;
   return CAD_ACCEPT;
}

/*+
 *   Function name:
 *   tcsECstopShtrsCAD
 *
 *   Purpose:
 *   Implement the stopShtrs ECS routine
 *
 *   Description:
 *   Simply set the flag to indicate the shutter motion is stopped.
 *
 *   Invocation:
 *   tcsECstopShtrsCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pcad   (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsECstopShtrsCAD (struct cadRecord *pcad)
{
   StateEl = STOPPING;
   return  CAD_ACCEPT;
}


/*+
 *   Function name:
 *   tcsEcGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the Enclosure
 *
 *   Description:
 *
 *   Invocation:
 *   tcsEcTestCAD(pcad)
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

long tcsEcGenericCAD (struct cadRecord *pcad)
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
      sprintf(pcad->mess, "Enclosure: %.9s started", command);
  /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"Off");
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
 *   tcsECstopVgatesCAD
 *
 *   Purpose:
 *   Implement the stopVgates ECS routine
 *
 *   Description:
 *   Currently this is a completely null routine.
 *
 *   Invocation:
 *   tcsECstopVgatesCAD (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)  pcad   (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsECstopVgatesCAD (struct cadRecord *pcad)

{

  return CAD_ACCEPT ;

}
epicsRegisterFunction(tcsEcFollowCAD);
epicsRegisterFunction(tcsEcsComplete);
epicsRegisterFunction(tcsEcParkDomeCAD);
epicsRegisterFunction(tcsEcGenericCAD);
epicsRegisterFunction(tcsEcsSimulate);
epicsRegisterFunction(tcsECmoveVgatesCAD);
epicsRegisterFunction(tcsECstopVgatesCAD);
epicsRegisterFunction(tcsEcsShutLimits);
epicsRegisterFunction(tcsEcParkVgatesCAD);
epicsRegisterFunction(tcsEcMoveDomeCAD);
epicsRegisterFunction(tcsECstopDomeCAD);
epicsRegisterFunction(tcsEcParkShtrsCAD);
epicsRegisterFunction(tcsECstopShtrsCAD);
epicsRegisterFunction(tcsEcStop);
epicsRegisterFunction(tcsEcMoveShtrsCAD);
epicsRegisterFunction(tcsEcsSimOutput);
epicsRegisterFunction(tcsECthermalCAD);
epicsRegisterFunction(tcsEcPark);
