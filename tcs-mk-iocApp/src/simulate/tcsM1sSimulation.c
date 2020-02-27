/*
*   FILENAME
*   tcsM1sSimulation.c
*
*   Author:		Andy Foster
*   Original Date:	16/09/96
*
*   Modified for use in TCS internal simulation
*   Philip Taylor, 30 April 1997.
*
*   This file contains the functions which are
*   called from the associated CAD record whenever
*   that record processes (i.e. when a command enters
*   the M1 system).
*
*   FUNCTION NAME(S)
*
*   tcsMcInit
*   tcsM1testCAD
*   tcsM1initCAD
*   tcsM1resetCAD
*   tcsM1simulateCAD
*   tcsM1FollowCAD
*   tcsM1thermalCAD
*   tcsM1supportsCAD
*   tcsM1read_lutCAD
*   tcsM1bulktempCAD
*   tcsM1figureCAD
*   tcsM1FigureTotals   - make total figure corrections available to EPICS
*   tcsM1definitionCAD
*   tcsM1parkCAD
*   tcsM1Position       - makes total offsets from LUT available to EPICS
*   tcsM1zerodemandsCAD
*   tcsM1modeCAD
*   tcsM1elev_sourceCAD
*   tcsM1trussTemp      - generate simulated truss temperatures
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsM1sSimulation.c,v $
 * Revision 1.6  2011/05/03 14:39:47  cjm
 * Support applying steps and glitches to the temperatures
 *
 * Revision 1.5  2002/02/22 10:52:03  cjm
 * Provide simulated truss temperatures
 *
 * Revision 1.4  2001/05/17 14:50:38  cjm
 * Use new menuDirectives and remove mosub references
 *
 * Revision 1.3  1999/03/11 00:08:27  cjm
 * Fix typo that copied zernSum[12] into valn
 *
 * Revision 1.2  1999/03/01 09:19:35  cjm
 * Add routine to provide figure totals and modify park command to correctly handle unpark
 *
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.9  1997/12/12 08:20:28  cjm
 * Support servo for M1 movements
 *
 * Revision 1.8  1997/11/20 08:09:54  cjm
 * Upgrade m1Btempset routine to latest ICD
 *
 * Revision 1.7  1997/11/10 15:43:09  cjm
 * Code to keep track of total offsets
 *
 * Revision 1.6  1997/11/05 15:44:00  pbt
 * Corrected bug in m1Park (uninitialised variable)
 *
 * Revision 1.5  1997/10/03 11:21:57  pbt
 * Park command changed in M1 and PARK sequence command
 *
 * Revision 1.4  1997/09/24 16:32:43  pbt
 * Modified Stop routine : now called from gensub
 *
 * Revision 1.3  1997/09/23 09:43:57  pbt
 * Removed carOR routine
 *
 * Revision 1.2  1997/06/04 16:55:57  pbt
 * m1CarOR now takes extra input fields (a->k)
 *
 * Revision 1.1  1997/05/07 11:45:38  pbt
 * Primary Control simulator code
 *
 */
/* *INDENT-ON* */

#include <math.h>
#include <time.h>
#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <caeventmask.h>
#include <dbFldTypes.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <dbEvent.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <subRecord.h>
#include <dbCommon.h>
#include <recSup.h>
#include <cad.h>
#include <menuCarstates.h>

#include "tcsConstants.h"
#include "tcsDecode.h"
#include "tcsM1s.h"
#include "tcsServo.h"
#include "timeLib.h"

#define DEBUG 0


/* String tables for symbolic constants */

LOCAL const char *simulateStrings[] = {
    "NONE",	/* No simulation */
    "VSM",	/* Minimal operation, commands respond */
    "FAST",	/* Fast simulation */
    "FULL",	/* Full simulation, realistic responses */
    NULL
};

LOCAL const char *onOffStrings[] = {
    "OFF", 	/* OFF */
    "ON", 	/* ON */
    NULL
};

LOCAL const char *supportsStrings[] = {
    "APSS", 	/* APSS */
    "ACTIVE", 	/* ACTIVE */
    "PASSIVE", 	/* PASSIVE */
    NULL
};

LOCAL const char *zeroDmdStrings[] = {
    "FIGURE",		/* FIG */
    "DEFINITION",	/* DEFN */
    NULL
};

LOCAL const char *parkStrings[] = {
    "PARK",		/* PARK */
    "UNPARK",		/* UNPARK */
    NULL
};

LOCAL const char *modeStrings[] = {
    "3ZONE", 	/* ZTHREE */
    "6ZONE", 	/* ZSIX */
    NULL
};

LOCAL const char *elevStrings[] = {
    "PCS", 	/* PCS */
    "MCS", 	/* MCS */
    NULL
};


/* Limits arrays for the definition command */

LOCAL const double definitionMin[] = {
    XROTMIN, YROTMIN, ZROTMIN,
    XDSPMIN, YDSPMIN, ZDSPMIN
};

LOCAL const double definitionMax[] = {
    XROTMAX, YROTMAX, ZROTMAX,
    XDSPMAX, YDSPMAX, ZDSPMAX
};

/* State of primary */
static int StateM1;

/* Flags for support control system states */
static int stateAPSS = FALSE ;
static int stateACTIVE = FALSE ;
static int statePASSIVE = FALSE ;

/* Flag for thermal control state */
static int thermalControl = FALSE ;

/* Total offsets relative to LUT as defined by the definition command.
*  Positions are measured in mm and rotations in millirads.
*/
static double definitionSum[] = {
    0.0, 0.0, 0.0,
    0.0, 0.0, 0.0
};

#define AO_NUM_ZERNIKES         14      /* Number of Zernike coefficients */

/* Total Zernike offsets relative to LUT as defined by figure command */
static double zernSum[AO_NUM_ZERNIKES] ;

/* The LUTs listed: */

char *lutname[] = {
    "aoMatC",
    "aoMatR",
    "aoMatM",
    "aoMatPosition",
    "aoMatDirection",
    "aoMatFlimits",
    "pssMatPosToVol",
    "pssMatSnsToPos",
    "pssMatSensorLUT",
    "pssMatVolToPos",
    "pssMatPosToSns"};


/* Count the entries */

const int nLuts = (sizeof lutname) / (sizeof lutname[0]); 

/********************************************************************
 *+
 * Routine name:
 *	tblIndex
 *
 * Function:
 *	Matches a given string against a table of strings
 *	and returns the index of the matching entry, or -1 if not found.
 *	String table ends with a NULL pointer (NB, not an empty string).
 *	It is assumed that there will be fewer than 50 possible strings, 
 *	to allow some kind of termination in case the NULL is omitted.
 *
 * Invocation:
 *	index = tblIndex (table, match);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) table  (char *[])  Table of strings to check against
 *	(>) match  (char *)    String to match
 *
 * Function value:
 *	index  (int)  Index number of matching string, or -1 if none.
 * 
 * External functions:
 *	strcmp  (string)  String comparison
 *
 *-
 */

int tblIndex(const char *table[], const char *match)
{
    int index;
 
    assert(table != NULL);
    assert(match != NULL);

    for (index = 0; table[index] != NULL; index++) {
        assert(index < 50);
  
        if (strcmp(table[index], match) == 0) {
            return index;
        }
    }
  
    /* No match found */
    return -1;
}

/********************************************************************
 *+
 * Routine name:
 *	lutIndex
 *
 * Function:
 *	Matches a given LUT identifier
 *	and returns the index of the matching entry, or -1 if not found.
 *
 * Invocation:
 *	index = lutIndex (match);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) match  (char *)    String to match
 *
 * Function value:
 *	index  (int)  Index number of matching string, or -1 if none.
 * 
 * External variables:
 *	(>) lutname  char[]   Array of LUT names
 *	(>) nLuts    (int)    Size of lutname[] array
 *
 * External functions:
 *	strcmp  (string)  String comparison
 *
 *-
 */

int lutIndex(const char *match) {
    int index;
 
    assert(match != NULL);

    for (index = 0; index<nLuts; index++) {
        if (strcmp(lutname[index], match) == 0) {
            return index;
        }
    }
  
    /* No match found */
    return -1;
}

/*+
 *   Function name:
 *   tcsM1Init
 *
 *   Purpose:
 *   Initialise the internal simulation of the Primary control system
 *
 *   Description:
 *   This routine simply creates and intialises the variables needed by
 *   the TCS's internal simulation of the Primary control system.
 *
 *   Invocation:
 *   tcsM1Init()
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

void tcsM1Init (void )
{
   static int first = TRUE;

   if (first) first = FALSE;

}


/********************************************************************
 *+
 * Routine name:
 *	cadRetString
 *
 * Function:
 *	Converts the cad return value into an ACCEPT or REJECT string
 *	in the given field of the CAD record, and signals the change
 *	of this field to the database (ie Channel Access).
 *
 * Invocation:
 *	cadRetString (pcad, pcad->vala, ret);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(>) ret                  (long)  Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 *
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 * 
 *-
 */
LOCAL void cadRetString(struct cadRecord *pcad, void *pfield, long ret)
{
    assert(ret == CAD_ACCEPT || ret == CAD_REJECT);
    if (ret == CAD_ACCEPT) {
	strcpy(pfield, "ACCEPTED");
    } else {
	strcpy(pfield, "REJECTED");
    }
    db_post_events(pcad, pfield, DBE_VALUE);
}


/********************************************************************
 *+
 * Routine name:
 *	tcsM1simulateCAD
 *
 * Function:
 *	CAD subroutine for Simulate command
 *	which sets the simulation mode of the PCS.
 *
 * Invocation:
 *	status = tcsM1simulateCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, NONE, VSM, FAST or FULL
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  NONE=0, VSM=1, FAST=2, FULL=3
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1simulateCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int index;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	/* Check Arg 1 (B) */
	index = tblIndex(simulateStrings, pcad->b);
	if (index < 0) {
	    strncpy(pcad->mess, "Arg 1 = {NONE, VSM, FAST, FULL}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/*
 *  Function tcsM1FollowCAD included for 
 *  consistency with other subsystem simulators
 */
long tcsM1FollowCAD(struct cadRecord *pcad)
{
   if (pcad->dir == menuDirectiveSTART || pcad->dir == menuDirectiveMARK)
     printf("Warning : M1 follow CAD MARK or START issued (not implemented)\n");
   return 0;
}


/********************************************************************
 *+
 * Routine name:
 *	tcsM1thermalCAD
 *
 * Function:
 *	CAD subroutine for Thremal command
 *	which turns the thermal management system on and off.
 *
 * Invocation:
 *	status = tcsM1thermalCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, ON or OFF
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  OFF=0, ON=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1thermalCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int index;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	/* Check Arg 1 (B) */
	index = tblIndex(onOffStrings, pcad->b);
	if (index < 0) {
	    strncpy(pcad->mess, "Arg 1 = {OFF, ON}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
        thermalControl = (index == 1);
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	tcsM1supportsCAD
 *
 * Function:
 *	CAD subroutine for Supports command
 *	which turns the PSS, APSS and AOS supports systems on & off.
 *
 * Invocation:
 *	status = tcsM1supportsCAD (pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  Supports CAD record
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, support system
 *	(>) pcad->c           (char [])  Input C, ON or OFF
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  APSS=0, ACTIVE=1, PASSIVE=2
 *	(<) pcad->valc         (long *)  OFF=0, ON=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */

long tcsM1supportsCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int indexSystem, indexState ;
    int stateVal ;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);
    assert(pcad->ftvc == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	*pcad->c = '\0';
	db_post_events(pcad, pcad->c, DBE_VALUE);

	*(long *) pcad->valc = 0;
	db_post_events(pcad, pcad->valc, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	/* Check Arg 1 (B) */
	indexSystem = tblIndex(supportsStrings, pcad->b);
	if (indexSystem < 0) {
	    strncpy(pcad->mess, "Arg 1 = {APSS, ACTIVE, PASSIVE}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = indexSystem;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	/* Check Arg 2 (C) */
	indexState = tblIndex(onOffStrings, pcad->c);
	if (indexState < 0) {
	    strncpy(pcad->mess, "Arg 2 = {OFF, ON}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
/* Set flags */
        stateVal = (indexState == 1);
        switch (indexSystem) {
          case 0 :
          stateAPSS = stateVal ;
          break ;
 
          case 1 :
          stateACTIVE = stateVal ;
          break ;
 
          case 2 :
          statePASSIVE = stateVal ;
          break ;
        }
	*(long *) pcad->valc = indexState;
	db_post_events(pcad, pcad->valc, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1read_lutCAD
 *
 * Function:
 *	CAD subroutine for read_lut command
 *	which reads a control system Look-Up-Table from a given file.
 *
 *	N.B. Opening a file or checking for ones existence must be 
 *	done in a separate task started from menuDirectiveSTART. It takes too 
 *	long to do file I/O from record processing, so we accept the 
 *	file pathname without checking here.
 *
 * Invocation:
 *	status =  tcsM1read_lutCAD (pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  read_lut CAD record
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, LUT identifier
 *	(>) pcad->c           (char [])  Input C, Path to LUT file
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  identifier index
 *	(<) pcad->valc         (long *)  LUT file path
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in gem3 CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */

long tcsM1read_lutCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int lutId;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);
    assert(pcad->ftvc == DBF_STRING);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	*pcad->c = '\0';
	db_post_events(pcad, pcad->c, DBE_VALUE);

	*(char *) pcad->valc = '\0';
	db_post_events(pcad, pcad->valc, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	/* Check Arg 1 (B) */
	lutId = lutIndex(pcad->b);
	if (lutId < 0) {
	    strncpy(pcad->mess, "Unknown LUT Identifier", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = lutId;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	/* Check Arg 2 (C) */
	if ((pcad->c[0] == '\0') ||
	    strlen(pcad->c) > MAX_STRING_SIZE) {
	    strncpy(pcad->mess, "Bad Pathname", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	strncpy(pcad->valc, pcad->c, MAX_STRING_SIZE);
	db_post_events(pcad, pcad->valc, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1bulktempCAD
 *
 * Function:
 *	CAD subroutine for Bulktemp command
 *	which sets the time and temperature for the Mirror Cell 
 *	thermal management subsystem.  Thermal control must be switched 
 *	on for this command to be accepted.
 *
 * Invocation:
 *	status =  tcsM1bulktempCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Temperature in Celcius
 *	(>) pcad->c           (char [])  Offset when surface heating on
 *      (>) pcad->d           (char [])  Offset when surface heating off
 *      (>) pcad->e           (char [])  Offset to surface temp.  
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (double *)  Target temperature in Celcius
 *	(<) pcad->valc         (double *)  Offset when surface heating on
 *      (<) pcad->vald        (double *) Offset when surface heating off
 *      (<) pcad->vale        (double *) Offset to surface temperature 
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1bulktempCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    double local;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_DOUBLE);
    assert(pcad->ftvc == DBF_DOUBLE);
    assert(pcad->ftvd == DBF_DOUBLE);
    assert(pcad->ftve == DBF_DOUBLE);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(double *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	*pcad->c = '\0';
	db_post_events(pcad, pcad->c, DBE_VALUE);

	*(double *) pcad->valc = 0;
	db_post_events(pcad, pcad->valc, DBE_VALUE);

	*pcad->d = '\0';
	db_post_events(pcad, pcad->d, DBE_VALUE);

	*(double *) pcad->vald = 0;

	*pcad->e = '\0';
	db_post_events(pcad, pcad->e, DBE_VALUE);

	*(double *) pcad->vale = 0;
	break;

    case menuDirectivePRESET:
	if (thermalControl == 0) {
	    strncpy(pcad->mess, "Thermal Control not switched ON", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	if (check_numeric(pcad->b)) {
	    strncpy(pcad->mess, "Temperature not numeric", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	local = strtod(pcad->b, NULL);
	if (local < TLOWER || local > TUPPER) {
	    strncpy(pcad->mess, "Temperature out of range", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(double *) pcad->valb = local;
	db_post_events(pcad, pcad->valb, DBE_VALUE);

	if (check_numeric(pcad->c)) {
	    strncpy(pcad->mess, "Offset not numeric", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	local = strtod(pcad->c, NULL);
	if (local < TLOWER || local > TUPPER) {
	    strncpy(pcad->mess, "Offset out of range", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(double *) pcad->valc = local;
	db_post_events(pcad, pcad->valc, DBE_VALUE);

	if (check_numeric(pcad->d)) {
	    strncpy(pcad->mess, "Offset not numeric", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	local = strtod(pcad->d, NULL);
	if (local < TLOWER || local > TUPPER) {
	    strncpy(pcad->mess, "Offset out of range", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(double *) pcad->vald = local;
	db_post_events(pcad, pcad->vald, DBE_VALUE);

	if (check_numeric(pcad->e)) {
	    strncpy(pcad->mess, "Offset not numeric", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	local = strtod(pcad->e, NULL);
	if (local < TLOWER || local > TUPPER) {
	    strncpy(pcad->mess, "Offset out of range", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(double *) pcad->vale = local;
	db_post_events(pcad, pcad->vale, DBE_VALUE);

	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1figureCAD
 *
 * Function:
 *	CAD subroutine for Figure command
 *	which applies an additional Zernike polynomial to the mirror
 *	figure.  Rejected if Active optics subsystem is not ON.
 *
 * Invocation:
 *	status =  tcsM1figureCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad              (struct cadRecord *)  Figure CAD record
 *	(>) pcad->dir         (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, Coefficient Z4
 *	(>) pcad->c           (char [])  Input C, Coefficient Z5
 *	(>) pcad->d           (char [])  Input D, Coefficient Z8
 *	(>) pcad->e           (char [])  Input E, Coefficient Z9
 *	(>) pcad->f           (char [])  Input F, Coefficient Z10
 *	(>) pcad->g           (char [])  Input G, Coefficient Z11
 *	(>) pcad->h           (char [])  Input H, Coefficient Z12
 *	(>) pcad->i           (char [])  Input I, Coefficient Z13
 *	(>) pcad->j           (char [])  Input J, Coefficient Z14
 *	(>) pcad->k           (char [])  Input K, Coefficient Z15
 *	(>) pcad->l           (char [])  Input L, Coefficient Z16
 *	(>) pcad->m           (char [])  Input M, Coefficient Z17
 *	(>) pcad->n           (char [])  Input N, Coefficient Z18
 *	(>) pcad->o           (char [])  Input O, Coefficient Z19
 *	(>) pcad->p           (char [])  Active optics ON/OFF state
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala        (char *)  ACCEPT or REJECT
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 *
 * External variables:
 *	(<) pZernikes  (double *)  New Zernike coefficients.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1figureCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int i;
    char *cptr;
    void **vptr;
    double local;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_DOUBLE);
    assert(pcad->ftvc == DBF_DOUBLE);
    assert(pcad->ftvd == DBF_DOUBLE);
    assert(pcad->ftve == DBF_DOUBLE);
    assert(pcad->ftvf == DBF_DOUBLE);
    assert(pcad->ftvg == DBF_DOUBLE);
    assert(pcad->ftvh == DBF_DOUBLE);
    assert(pcad->ftvi == DBF_DOUBLE);
    assert(pcad->ftvj == DBF_DOUBLE);
    assert(pcad->ftvk == DBF_DOUBLE);
    assert(pcad->ftvl == DBF_DOUBLE);
    assert(pcad->ftvm == DBF_DOUBLE);
    assert(pcad->ftvn == DBF_DOUBLE);
    assert(pcad->ftvo == DBF_DOUBLE);
    
    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	cptr = pcad->b;
	vptr = &pcad->valb;
	for (i = 0; i < AO_NUM_ZERNIKES;
	     i++, vptr++, cptr += MAX_STRING_SIZE) {
	    strcpy(cptr, "0.0");
	    db_post_events(pcad, cptr, DBE_VALUE);

	    *(double *) (*vptr) = 0.0;
	    db_post_events(pcad, *vptr, DBE_VALUE);
	}
	break;

    case menuDirectivePRESET:
	if (stateACTIVE == 0) {
	    strncpy(pcad->mess, "Active Supports not ON", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	cptr = pcad->b;
	vptr = &pcad->valb;

	for (i = 0; i < AO_NUM_ZERNIKES;
	     i++, vptr++, cptr += MAX_STRING_SIZE) {
	    if (check_numeric(cptr)) {
		strncpy(pcad->mess, "Argument not numeric", MAX_STRING_SIZE);
		ret = CAD_REJECT;
		break;
	    }
	    local = strtod(cptr, NULL);
	    if (local < ZMIN || local > ZMAX) {
		strncpy(pcad->mess, "Argument out of range", MAX_STRING_SIZE);
		ret = CAD_REJECT;
		break;
	    }
	    *(double *) (*vptr) = local;
	    db_post_events(pcad, *vptr, DBE_VALUE);
	    

	}
	break;

    case menuDirectiveMARK:
        break ;

    case menuDirectiveSTART:

/* Increment the total Zernike demand by the current offsets */
        cptr = pcad->b ;
        for (i = 0; i < AO_NUM_ZERNIKES ; i++, cptr += MAX_STRING_SIZE ) {
           zernSum[i] += strtod(cptr, NULL) ;
        }
        break ;

    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/*+
 *   Function name:
 *   tcsM1FigureTotals
 *
 *   Purpose:
 *   Makes total figure corrections available to EPICS
 *
 *   Description:
 *   Write the array zenSum to the first 14 outputs of a gensub
 *
 *   Invocation:
 *   tcsM1FigureTotals(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub  (struct genSubRecord *) Pointer to genSub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

int tcsM1FigureTotals ( struct genSubRecord *pgsub)
{

  *(double *)pgsub->vala = zernSum[0] ;
  *(double *)pgsub->valb = zernSum[1] ;
  *(double *)pgsub->valc = zernSum[2] ;
  *(double *)pgsub->vald = zernSum[3] ;
  *(double *)pgsub->vale = zernSum[4] ;
  *(double *)pgsub->valf = zernSum[5] ;
  *(double *)pgsub->valg = zernSum[6] ;
  *(double *)pgsub->valh = zernSum[7] ;
  *(double *)pgsub->vali = zernSum[8] ;
  *(double *)pgsub->valj = zernSum[9] ;
  *(double *)pgsub->valk = zernSum[10] ;
  *(double *)pgsub->vall = zernSum[11] ;
  *(double *)pgsub->valm = zernSum[12] ;
  *(double *)pgsub->valn = zernSum[13] ;

  return 0 ;
}
/********************************************************************
 *+
 * Routine name:
 *	 tcsM1definitionCAD
 *
 * Function:
 *	CAD subroutine for Definition command
 *	which adjusts the mirror position and rotation.
 *
 * Invocation:
 *	status =  tcsM1definitionCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, Rotation about X-axis
 *	(>) pcad->c           (char [])  Input C, Rotation about Y-axis
 *	(>) pcad->d           (char [])  Input D, Rotation about Z-axis
 *	(>) pcad->e           (char [])  Input E, Displacement along X-axis
 *	(>) pcad->f           (char [])  Input F, Displacement along Y-axis
 *	(>) pcad->g           (char [])  Input G, Displacement along Z-axis
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (double *)  X rotation
 *	(<) pcad->valc         (double *)  Y rotation
 *	(<) pcad->vald         (double *)  Z rotation
 *	(<) pcad->vale         (double *)  X displacement
 *	(<) pcad->valf         (double *)  Y displacement
 *	(<) pcad->valg         (double *)  Z displacement
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1definitionCAD(struct cadRecord *pcad)
{
    int i;
    long ret = CAD_ACCEPT;
    char *cptr;
    void **vptr;
    double local;

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	cptr = pcad->b;
	vptr = &pcad->valb;
	for (i = 0; i < DEF_PARAMS; i++, vptr++, cptr += MAX_STRING_SIZE) {
	    strcpy(cptr, "0.0");
	    db_post_events(pcad, cptr, DBE_VALUE);

	    *(double *) (*vptr) = 0.0;
	    db_post_events(pcad, *vptr, DBE_VALUE);
	}
	break;

    case menuDirectivePRESET:
	if (stateAPSS == 0) {
	    strncpy(pcad->mess, "APSS not ON", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	if (statePASSIVE == 0) {
	    strncpy(pcad->mess, "Passive Supports not ON", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}

	cptr = pcad->b;
	vptr = &pcad->valb;
	for (i = 0; i < DEF_PARAMS; i++, vptr++, cptr += MAX_STRING_SIZE) {
	    if (check_numeric(cptr)) {
		strncpy(pcad->mess, "Argument not numeric", MAX_STRING_SIZE);
		ret = CAD_REJECT;
		break;
	    }
	    local = strtod(cptr, NULL);
	    if (local < definitionMin[i] || local > definitionMax[i]) {
		strncpy(pcad->mess, "Argument out of range", MAX_STRING_SIZE);
		ret = CAD_REJECT;
		break;
	    }

	    *(double *) (*vptr) = local;
	    db_post_events(pcad, *vptr, DBE_VALUE);
	}
	break;

    case menuDirectiveMARK:
        break ;

    case menuDirectiveSTART:

/* Increment the current position by the requested amounts */

	cptr = pcad->b;
	for (i = 0; i < DEF_PARAMS; i++, cptr += MAX_STRING_SIZE) {
	    definitionSum[i] += strtod(cptr, NULL);
        }
        break ;

    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1parkCAD
 *
 * Function:
 *	CAD subroutine for Park command
 *	which parks and unparks the mirror.
 *
 * Invocation:
 *	status =  tcsM1parkCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, PARK or UNPARK
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  PARK=0, UNPARK=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1parkCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    char parkString[MAX_STRING_SIZE] ;
    int index;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
/* Check Arg 1 (B) */
        tcsDcUc (pcad->b, MAX_STRING_SIZE, parkString) ;
/* Default is PARK */
	if (strlen(parkString) == 0) strncpy(parkString,"PARK",4) ;
	index = tblIndex(parkStrings, parkString);
	if (index < 0)
        {
	    strncpy(pcad->mess, "Arg 1 = {PARK, UNPARK}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
/* PARK : switch off all systems */
        if (index == 0) {
          stateAPSS = 0;
          stateACTIVE = 0;
          statePASSIVE = 0;
          thermalControl = 0;
        } else {
          stateAPSS = 1;
          stateACTIVE = 1;
          statePASSIVE = 1;
          thermalControl = 1;
        }
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1zerodemandsCAD
 *
 * Function:
 *	CAD subroutine for Zerodemands command
 *	which resets the integrated figure or definition values.
 *
 * Invocation:
 *	status =  tcsM1zerodemandsCAD (pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  Supports CAD record
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, FIGURE or DEFINITION
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  FIG=0, DEFN=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */

long tcsM1zerodemandsCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int index;
    int i ;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	index = tblIndex(zeroDmdStrings, pcad->b);
	if (index < 0) {
	    strncpy(pcad->mess, "Arg 1 = {FIGURE, DEFINITION}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
        break ;
    case menuDirectiveSTART:

        if (*(long *)pcad->valb == 1) {
          for (i=0 ; i < DEF_PARAMS; i++ ) {
             definitionSum[i] = 0.0;
          }
        } else {
          for (i=0 ; i < AO_NUM_ZERNIKES ; i++ ) {
             zernSum[i] = 0.0 ;
          }
        } 
        break ;
 
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1modeCAD
 *
 * Function:
 *	CAD subroutine for Mode command
 *	which selects betwen 3-zone and 6-zone passive supports.
 *
 * Invocation:
 *	status =  tcsM1modeCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, 3ZONE or 6ZONE
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  3ZONE=0, 6ZONE=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1modeCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int index;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	index = tblIndex(modeStrings, pcad->b);
	if (index < 0) {
	    strncpy(pcad->mess, "Arg 1 = {3ZONE, 6ZONE}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}


/********************************************************************
 *+
 * Routine name:
 *	 tcsM1elev_sourceCAD
 *
 * Function:
 *	CAD subroutine for Elev_source command
 *	which indicates where to obtain the current telescope 
 *	elevation angle from.
 *
 * Invocation:
 *	status =  tcsM1elev_sourceCAD(pcad);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) pcad   (struct cadRecord *)  CAD record instance
 *	(>) pcad->dir  (unsigned short)  CAD Directive, one of:
 *		menuDirectiveCLEAR  => Clear inputs
 *		menuDirectivePRESET => Check input values
 *		menuDirectiveMARK   => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTART  => Ignored, returns CAD_ACCEPT
 *		menuDirectiveSTOP   => Ignored, returns CAD_ACCEPT
 *	(>) pcad->b           (char [])  Input B, PCS or MCS
 *	(<) pcad->mess        (char [])  Error message text
 *	(<) pcad->vala         (char *)  ACCEPT or REJECT
 *	(<) pcad->valb         (long *)  PCS=0, MCS=1
 *
 * Function value:
 *	status  (long)    Command status, one of:
 *		CAD_ACCEPT  =>  Command Ok
 *		CAD_REJECT  =>  Command rejected.
 * 
 * Deficiencies:
 *	Compensates for deficiencies in CAD record processing by
 *	calling db_post_events for fields it changes.
 *
 *-
 */
long tcsM1elev_sourceCAD(struct cadRecord *pcad)
{
    long ret = CAD_ACCEPT;
    int index;

    assert(pcad->ftva == DBF_STRING);
    assert(pcad->ftvb == DBF_LONG);

    switch (pcad->dir) {
    case menuDirectiveCLEAR:
	*pcad->b = '\0';
	db_post_events(pcad, pcad->b, DBE_VALUE);

	*(long *) pcad->valb = 0;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectivePRESET:
	index = tblIndex(elevStrings, pcad->b);
	if (index < 0) {
	    strncpy(pcad->mess, "Arg 1 = {PCS, MCS}", MAX_STRING_SIZE);
	    ret = CAD_REJECT;
	    break;
	}
	*(long *) pcad->valb = index;
	db_post_events(pcad, pcad->valb, DBE_VALUE);
	break;

    case menuDirectiveMARK:
    case menuDirectiveSTART:
    case menuDirectiveSTOP:
	break;

    default:
	strncpy(pcad->mess, "Unknown CAD directive", MAX_STRING_SIZE);
	ret = CAD_REJECT;
	break;
    }
    cadRetString(pcad, pcad->vala, ret);
    return ret;
}

/*+
 *   Function name:
 *   tcsM1GenericCAD
 *
 *   Purpose:
 *   Implement a generic command for the M1
 *
 *   Description:
 *
 *   Invocation:
 *   tcsM1TestCAD(pcad)
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

long tcsM1GenericCAD (struct cadRecord *pcad)
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
      sprintf(pcad->mess, "M1: %.16s started", command);
 /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"Off");
      status = 0;
      break;

   default:
      status = 0;
      break;
   }
   return(status);
}


/*+
 *   Function name:
 *   tcsM1Position
 *
 *   Purpose:
 *   Makes offsets from LUT available to EPICS
 *
 *   Description:
 *   The M1 simulator keeps track of the total offsets from the nominal
 *   LUT positions. These offsets are set and cleared with the definition
 *   and zerodemands commands. This record implements a servo for each of
 *   the axes of the mirror such that when a new total offset is applied
 *   the mirror moves smoothly to the new demand. The current mirror
 *   position is made available to EPICS. 
 *
 *   Invocation:
 *   tcsM1Position (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   Epics inputs:
 *   a => the CAR status of the definition command
 *   b => the CAR status of the figure command
 *   c => the CAR status of the zerodemands command
 *
 *   Epics outputs:
 *   vala => demand X displacement from nominal (mm)
 *   valb => demand Y displacement from nominal (mm)
 *   valc => demand Z displacement from nominal (mm)
 *   vald => demand Rotation about X axis (mrads)
 *   vale => demand Rotation about Y axis (mrads)
 *   valf => demand Rotation about Z axis (mrads)
 *   valg => mask for triggering links
 *   valh => array of current positions for sky simulator
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsM1Position (struct genSubRecord *pgsub)
{

 static int first = TRUE ;               /* Flag for initialisation */
 static struct ServoState servoStateX ;  /* Servo state for X axis */
 static struct ServoState servoStateY ;  /* Servo state for Y axis */
 static struct ServoState servoStateZ ;  /* Servo state for Z axis */
 static struct ServoState servoStateRx;  /* Servo state for X rotations */
 static struct ServoState servoStateRy;  /* Servo state for Y rotations */

 static struct ServoConfig servoConfigXYZ; /* Servo configuration for X,Y, Z */
 static struct ServoConfig servoConfigRXY; /* Servo configuration for rots */

 int inPosX ;                            /* X axis in position flag */
 int inPosY ;                            /* Y axis in position flag */
 int inPosZ ;                            /* Z axis in position flag */
 int inPosRx ;                           /* Rx axis in position flag */
 int inPosRy ;                           /* Ry axis in position flag */
 int inPos ;                             /* Combined in position status */

 static double currRx ;                  /* Current Rx offset (arcsec) */ 
 static double currRy ;                  /* Current Ry offset (arcsec) */ 

 static double currXv ;                  /* Current X velocity */
 static double currYv ;                  /* Current Y velocity */
 static double currZv ;                  /* Current Z velocity */
 static double currRxv ;                 /* Current Rx velocity */
 static double currRyv ;                 /* Current Ry velocity */

 long carDefn ;                           /* CAR status of definition command */
 long carFigure;                          /* CAR status of figure command */
 long carZero ;                           /* CAR status of zero demands */
 
 int linkMask ;                           /* mask for triggerring outputs */
 double now ;                             /* Current time */
 static double m1Posns[6] ;               /* Current positions mm & rads */ 

/* Set up servo parameters */

 if (first) {
   servoConfigXYZ.dvmax = 0.05 ;        /* max acceleration (mm/s/s) */
   servoConfigXYZ.vtmax = 0.1;          /* Max velocity (mm/s) */
   servoConfigXYZ.gs = 0.2 ;           /* Square root gain */
   servoConfigXYZ.gp = 0.4 ;            /* Proportional gain */
   servoConfigXYZ.gi = 0.01 ;           /* Integrator gain */
   servoConfigXYZ.pi = 0.05 ;           /* Integrator window (mm) */
   servoConfigXYZ.pok = 0.01;          /* In position distance (mm) */
   servoConfigXYZ.tok = 0.4 ;           /* Close enough in time (s) */
   servoConfigXYZ.noise = 0.0;          /* Noise */
   servoConfigRXY.dvmax = 1.0 ;        /* max acceleration (arcsec/s/s) */
   servoConfigRXY.vtmax = 2.0;          /* Max velocity (arcsec/s) */
   servoConfigRXY.gs = 0.8 ;           /* Square root gain */
   servoConfigRXY.gp = 0.4 ;            /* Proportional gain */
   servoConfigRXY.gi = 0.01 ;            /* Integrator gain */
   servoConfigRXY.pi = 1.0 ;           /* Integrator window (arcsec) */
   servoConfigRXY.pok = 0.05;          /* In position distance (arcsec) */
   servoConfigRXY.tok = 0.4 ;           /* Close enough in time (s) */
   servoConfigRXY.noise = 0.0;          /* Noise */

/* Set current state of each axis */
   timeNow ( &(servoStateX.told) );
   servoStateX.told -= 0.2 ;
   servoStateX.pdtold = 0.0;
   servoStateX.vd = 0.0 ;
   servoStateX.tout = servoStateX.told ;
   servoStateX.accum = 0.0;
 
   memcpy (&servoStateY, &servoStateX, sizeof (struct ServoState));
   memcpy (&servoStateZ, &servoStateX, sizeof (struct ServoState));
   memcpy (&servoStateRx, &servoStateX, sizeof (struct ServoState));
   memcpy (&servoStateRy, &servoStateX, sizeof (struct ServoState));
   
   first = FALSE ;
 }

/* Fetch current CAR statuses and initialise mask */ 

   carDefn = *(long *)pgsub->a;
   carFigure = *(long *)pgsub->b;
   carZero = *(long *)pgsub->c ;
   linkMask = 0;

/* Fetch the current time */

 timeNow (&now) ;

/* Find if in position */

 inPosX = tcsServo (now, definitionSum[3], 0, &servoConfigXYZ, 
                    &servoStateX, &m1Posns[0], &currXv ) ; 

 inPosY = tcsServo (now, definitionSum[4], 0, &servoConfigXYZ, 
                    &servoStateY, &m1Posns[1], &currYv ) ; 
 inPosZ = tcsServo (now, definitionSum[5], 0, &servoConfigXYZ, 
                    &servoStateZ, &m1Posns[2], &currZv ) ; 
 inPosRx = tcsServo (now, definitionSum[0]/(1000.0*AS2R), 0, &servoConfigRXY, 
                    &servoStateRx, &currRx, &currRxv ) ; 
 inPosRy = tcsServo (now, definitionSum[1]/(1000.0*AS2R), 0, &servoConfigRXY, 
                    &servoStateRy, &currRy, &currRyv ) ; 

 inPos = inPosX && inPosY && inPosZ && inPosRx && inPosRy ;
 
 if (carDefn == menuCarstatesBUSY && inPos) {
   linkMask += 1 ; 
 }
 if (carFigure == menuCarstatesBUSY && inPos)
   linkMask += 2 ;
 if (carZero == menuCarstatesBUSY && inPos )
   linkMask += 4 ;

/* Output current demand data as well as current positions */

  *(double *)pgsub->vala = definitionSum[3];
  *(double *)pgsub->valb = definitionSum[4];
  *(double *)pgsub->valc = definitionSum[5];
  *(double *)pgsub->vald = definitionSum[0];
  *(double *)pgsub->vale = definitionSum[1];
  *(double *)pgsub->valf = definitionSum[2];

  *(long *)pgsub->valg = linkMask ;

  m1Posns[3] = currRx * AS2R ;
  m1Posns[4] = currRy * AS2R ;
  m1Posns[5] = definitionSum[2] / 1000.0 ;

  memcpy (pgsub->valh, m1Posns, 6 * sizeof(double)) ;
  
  return 0;

} 

/*+
 *   Function name:
 *   tcsM1stop
 *
 *   Purpose:
 *   Stops primary movement
 *
 *   Description:
 *
 *   Invocation:
 *   status = tcsM1Stop(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
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

long tcsM1Stop (struct genSubRecord *pgsub)
{
   StateM1 = STOPPED;
   strncpy(pgsub->vala, "Off", 3);
   return(0);
}



/********************************************************************
 *+
 * Routine name:
 *	check_numeric
 *
 * Function:
 *	Checks for a legal numeric string
 *	in its input parameter.
 *
 * Invocation:
 *	status = check_numeric (string);
 *
 * Parameters: (">" input, "!" modified, "<" output)  
 *	(>) string  (char *)    String to check
 *
 * Function value:
 *	status  (long)    Description, one of the values:
 *		OK     =>  Ok
 *		ERROR  =>  Not a legal number
 * 
 * External functions:
 *	strtod  (stdlib)    Decimal conversion.
 *	isspace (ctype)     Whitespace testing.
 *
 * Deficiencies:
 *	.
 *
 *-
 */
long check_numeric(char *buf)
{
    char *chk;

    /* Skip leading spaces */
    while (isspace((int)*buf))
	buf++;

    /* Try to convert to double */
    (void) strtod(buf, &chk);

    /* Not numeric if pointers identical */
    if (buf == chk)
	return (-1);

    /* Skip trailing spaces */
    while (isspace((int)*chk))
	chk++;

    /* Ok if nothing left */
    if (*chk == '\0')
	return (0);

    /* Otherwise not numeric */
    return (-1);
}


/*+
 *   Function name:
 *   tcsM1trussTemp
 *
 *   Purpose:
 *   Generates simulated truss temperatures for use by focus loop in TCS
 *
 *   Description:
 *   This routine provides a simple simulation of the variation in the 
 *   telescope truss temperatures as a function of time. The function
 *   generated is a sine wave with a maximum at midday and a minimum
 *   at midnight. The user can offset the sine wave with a constant 
 *   zero point or by setting the amplitude to zero provide a constant
 *   input.
 *
 *   Invocation:
 *   tcsM1trussTemp(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub  (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *   a => Zero point of sensor ANB101 (deg C)
 *   b => Amplitude of sinusoidal temperature for ANB101 (deg C) 
 *   c => Zero point of sensor ANB103 (deg C)
 *   d => Amplitude of sinusoidal temperature for ANB103 (deg C) 
 *   e => Step size for temperature jumps if step model enabled (deg C)
 *   f => Time interval for step (s)
 *   g => Size of temperature spike to be added to data (deg C)
 *   h => Time between samples with spikes added (s)
 *   k => Whether or not to apply spikes to the data
 *   l => Whether to generate a step in temperature 
 *
 *   Epics outputs:
 *   vala = > Temperature of sensor ANB101 (deg C)
 *   valb = > Temperature of sensor ANB103 (deg C)
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

int tcsM1trussTemp ( struct genSubRecord *pgsub)
{

  double anb101Zero, anb103Zero ;  /* Zero points for two node boxes (deg C) */
  double anb101Amp, anb103Amp ;    /* Amplitudes of sine waves (deg C) */
  double anbStep ;                 /* Step size (deg C) */
  double anbStepTime ;             /* Duration of step (s) */
  double anbSpike ;                /* Amplitude of temperature spikes (deg C) */
  double anbSpikeInterval ;        /* Time between spikes (s) */
  long   applySpikes ;             /* Whether or not to apply spikes */
  long   applyStep ;               /* Whether to apply a step */

  int status ;
  int hmsf[4] ;                    /* hours minutes seconds and fraction */
  double cost ;                    /* Cos of current time of day */
  double secsNow ;                 /* Elapsed seconds since midnight */

  static int first = 1 ;
  static double lastSpike ;
  double anb101Temp, anb103Temp ;  /* Generated temperatures */
  static int applyingStep = 0;
  static double stepStart ;
  static double stepSize ;         /* Size of step per second */
  static double currStep = 0.0 ; 

/* Read data from the input links */
  anb101Zero = *(double *)pgsub->a ;
  anb101Amp  = *(double *)pgsub->b ;
  anb103Zero = *(double *)pgsub->c ;
  anb103Amp  = *(double *)pgsub->d ;
  anbStep    = *(double *)pgsub->e ;
  anbStepTime = *(double *)pgsub->f ;
  anbSpike   = *(double *)pgsub->g ;
  anbSpikeInterval = *(double *)pgsub->h ;
  applySpikes = *(long *)pgsub->k ;
  applyStep = *(long *)pgsub->l ;


/* Read current time of day and convert to seconds since midnight */
  status = timeNowT(UTC, 0, hmsf) ;
  if (status) {
    secsNow = 0.0 ;
  } else {
    secsNow = hmsf[0]*3600.0 + hmsf[1]*60.0 + hmsf[2];
  }

  if (first) {
    lastSpike = secsNow ;
    first = 0 ;
  }

  cost = cos(2.0 * PI * secsNow/86400.0) ;

  anb101Temp = anb101Zero - anb101Amp * cost ;
  anb103Temp = anb103Zero - anb103Amp * cost ;

  if (applySpikes) {
    if (secsNow > lastSpike + anbSpikeInterval) {
      lastSpike = secsNow ;
      anb101Temp += anbSpike ;
      anb103Temp += anbSpike ;
    }
  }

  if (applyStep) {
    applyingStep = 1 ;
    stepStart = secsNow ;
    stepSize = anbStep/anbStepTime ;
    *(long *)pgsub->l = 0;
  }

  if (applyingStep) {
    if (secsNow > stepStart + anbStepTime ) {
      applyingStep = 0;
    } else {
/* Watch for wraps around midnight */
      if (secsNow < stepStart) {
        stepStart -= 86400.0 ;
      }
      currStep = (secsNow - stepStart) * stepSize ;
    }
  }

/* Continue applying the step after it has completed */
  anb101Temp += currStep ;
  anb103Temp += currStep ;

/* Output the new temperatures */
  *(double *)pgsub->vala = anb101Temp ;
  *(double *)pgsub->valb = anb103Temp ;
  *(double *)pgsub->valc = currStep ;

  return 0 ;
}
epicsRegisterFunction(tcsM1parkCAD);
epicsRegisterFunction(tcsM1Position);
epicsRegisterFunction(tcsM1Stop);
epicsRegisterFunction(tcsM1FollowCAD);
epicsRegisterFunction(tcsM1bulktempCAD);
epicsRegisterFunction(tcsM1figureCAD);
epicsRegisterFunction(tcsM1GenericCAD);
epicsRegisterFunction(tcsM1supportsCAD);
epicsRegisterFunction(tcsM1elev_sourceCAD);
epicsRegisterFunction(tcsM1read_lutCAD);
epicsRegisterFunction(tcsM1zerodemandsCAD);
epicsRegisterFunction(tcsM1simulateCAD);
epicsRegisterFunction(tcsM1trussTemp);
epicsRegisterFunction(tcsM1thermalCAD);
epicsRegisterFunction(tcsM1definitionCAD);
epicsRegisterFunction(tcsM1FigureTotals);
epicsRegisterFunction(tcsM1modeCAD);
