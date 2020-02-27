/********************************************************************
 *+
 * Module Name:
 *	tcsM1s.h
 *
 * Description:
 *	Header file for tcsM1sSimulation.c
 *
 * Original Author:	Andy Foster
 * Original Date:	16/9/96
 *
 * Adapted for use in TCS M1 simulation
 * PBT 30/4/97.
 *
 ********************************************************************/
/* *INDENT-OFF* */
/*
 * $Log: tcsM1s.h,v $
 * Revision 1.1.1.1  1998/11/08 00:21:10  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/05/07 11:45:37  pbt
 * Primary Control simulator code
 *
 */
/* *INDENT-ON* */


#ifndef M1S_H
#define M1S_H


#ifndef CAD_ACCEPT
#define CAD_ACCEPT	0
#define CAD_REJECT	1
#endif


/*
 *	Symbolic constants
 */

/* Levels of Debugging */

#define DNONE 0
#define DMIN  1
#define DFULL 2

/* Range of Mirror Temperature */

#define TLOWER -15.0
#define TUPPER  30.0

/* Range for Time of Day */

#define HOURS_MIN 0.0
#define HOURS_MAX 24.0

/* Zernike Coefficients - Allowed Range */

#define ZMIN      -100.0
#define ZMAX       100.0

/* Rotational and Displacement ranges for the DEFINITION command */

#define XROTMIN -17.5		/* in milli-radians 17.5 mrad ~ 1deg */
#define XROTMAX 17.5

#define YROTMIN -17.5
#define YROTMAX 17.5

#define ZROTMIN -17.5
#define ZROTMAX 17.5

#define XDSPMIN -10.0
#define XDSPMAX 10.0

#define YDSPMIN -10.0
#define YDSPMAX 10.0

#define ZDSPMIN -10.0
#define ZDSPMAX 10.0

#define DEF_PARAMS 6

/* Which offsets have been zeroed? (ZERODEMANDS) */

#define FIG  0
#define DEFN 1

/* Choices of Support System */

#define APSS    0
#define ACTIVE  1
#define PASSIVE 2

/* Maximum frequency for Data Logging */

#define MAX_FREQ 1.0

/* Misc */

#define OFF 0
#define ON  1

/* Number of Mirror Zones */

#define ZTHREE 0
#define ZSIX   1

/* Sources of elevation */

#define PCS 0
#define MCS 1


/*
 *	Function Prototypes
 */

int tblIndex(const char *table[], const char *match);
void tcsM1Init (void ) ;
long check_numeric(char *);


#endif
