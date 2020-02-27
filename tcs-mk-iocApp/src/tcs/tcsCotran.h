#ifndef COTRANLIBHDEF
#define COTRANLIBHDEF

#include <tcsConstants.h>

/*
**  - - - - - - - - - - - -
**   t c s C o t r a n . h
**  - - - - - - - - - - - -
**
**  TCS coordinate transformation library macros and
**  prototype function declarations.
**
**  D.L.Terrett   23 October 1996
**
**  Copyright RAL 1996.  All rights reserved.
*/

/* Function prototypes */

int tcsCtOffToSph ( FRAMETYPE, double[], OFFCOORD, double, double, double[] );
int tcsCtSphToOff ( FRAMETYPE, double[], OFFCOORD, double[], double*, double* );
#endif
