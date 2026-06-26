
/*
*   FILENAME
*   tcsSeqSysSimulate.stpp
*
*   FUNCTION NAME(S)
*   This file contains a sequence for a TCS subsystem
*   initialisation simulation
*
*/
/* *INDENT-OFF* */
/*
 * $Log
 */
/* *INDENT-ON* */


/*+
 *   Module:
 *   tcsSeqSysSimulate.stpp
 *
 *   Purpose:
 *   This module provides the initialisation sequence program for the
 *   TCS's internal simulation of the subsystem. It starts
 *   and then monitors the state of the simulation as well as 
 *   handling the Reset and Init commands.
 *
 *   Description:
 *   "top" and "sys" database prifixes are supplied as start parameters.
 *    "sys" is the subsystem prefix (e.g. mc:) including colon.
 *
 *   Invocation:
 *   The program is normally started by the sequencer as follows
 *
 *   seq &tcsSeqSysSimulate, "top=tcs:, sys=<xx:>, sad = <xx:sad:>"
 *
 *   Deficiencies:
 *
 *-
 */


program tcsSeqSysSimulate ("top=tcs:")

option +r;    /* Re-entrant */

/* All defines go here */

#include "tcsSeqConstants.h"
#include "tcsSeqMacros.h"

%%#include "menuCarstates.h"
%%#include "tcsMcs.h"
%%#include "tcsCrs.h"
%%#include "tcsAgs.h"
%%#include "tcsM1s.h"
%%#include "tcsM2s.h"
%%#include "tcsEcs.h"
%%#include "tcsAos.h"
%%#include "tcsAom.h"
%%#include <string.h>

%%#include <epicsTypes.h>

/* Local variables */

float delayTime;                /* Seconds to wait befor setting state "Running" */
%%static char subsys[MAX_STRING_SIZE]; /* Subsystem identifier, including ':' suffix */

/* SNC assignments */

ASSVAR (int, startLoop, "{subsys}startLoop" ) ;
MONVAR (int, dbReloading, "{top}dbReloading" ) ;
ASSVAR (int, simState, "{sad}state" ); 
ASSVAR (string, health, "{sad}health" ) ;
ASSVAR (int, ecHealth, "{top}ec:health" ) ;
ASSVAR (int, initIVAL, "{subsys}initC.IVAL") ;
MONVAR (int, initCAR, "{subsys}initC" ) ;


/* State program starts here */

ss sysSim
{

   state init
   {
    when ()
     {
       strcpy(subsys, macValueGet("sys"));         /* The name of the simulated subsystem */
     } state start
   }

/* The start state is intended for any one time initialisation.
*  Health is set to good until proven otherwise
*/ 

  state start
  {
/* Wait for the dbReloading to be finished */
    when (dbReloading == 0)
   {
    initIVAL = menuCarstatesBUSY ;  /* Subsystem status becomes BUSY  while initialising */
    pvPut(initIVAL) ;
    delayTime = 5.0 ;          /* This is entirely arbitrary */
    startLoop = 1 ;
/* Call appropriate initialisation routine */
    if (!strncmp(subsys,"mc:",3)) tcsMcInit() ;
    if (!strncmp(subsys,"cr:",3)) 
    {
      delayTime = 3.0 ;
      tcsCrInit() ;
    }
    if (!strncmp(subsys,"ec:",3)) tcsEcInit() ;
    if (!strncmp(subsys,"m1:",3)) 
    {
      delayTime = 3.0 ;
      tcsM1Init() ;
    }
    if (!strncmp(subsys,"m2:",3)) tcsM2Init() ;
    if (!strncmp(subsys,"ag:",3)) tcsAgInit() ;
    if (!strncmp(subsys,"ao:",3)) tcsAoInit() ;
    if (!strncmp(subsys,"aom:",4)) tcsAomInit() ;
    if (!strncmp(subsys,"ec:",3))
    {
      ecHealth = 0;     /* GOOD */
      pvPut(ecHealth);
    }
    else
    {
      strcpy(health, "GOOD") ;
      pvPut(health) ;
    }
    simState = INITIALISING ;
    pvPut(simState) ;
   } state initialising
  }

/* This is a state to wait for the DB reloading to start */
 state dbReloading
  {
   when (dbReloading == 1)
    {
    } state start
  }

/* The initialisation state simply waits for delayTime seconds before
 * continuing. The real mount control system would be initialising
 * its hardware during this time.
*/

  state initialising
  {
   when(delay(delayTime))
   {
    pvPut(startLoop) ;
   }  state delaying
  }

/* This state was found neccessary to give the simulation loop time to
*  start up. Without the delay the tcsSeqInit state program would see
*  simState go to RUNNING and immediately try and grab the current 
*  az & el. This happened so quickly that the simulation loop hadn't
*  completed it's first iteration and so the current az & el were still
*  zero.
*/

  state delaying
  {
   when (delay(1.0))
   {
    simState = RUNNING ;
    pvPut(simState) ;
    initIVAL = menuCarstatesIDLE ;    /* Subsystem status becomes IDLE after initialising */
    pvPut(initIVAL) ;
   }  state monitoring
  }

/* The monitoring state looks for either the reset or init CAR
 * records  being set to busy. It then simply jumps to the dbReloading 
 * state which waits for the DB reloaded to start, then complete; after
 * delayTime seconds of setting the CAR records back to idle. 
*/

  state monitoring
  {
   when (initCAR == menuCarstatesBUSY)
   {
   }  state dbReloading
  }
}

