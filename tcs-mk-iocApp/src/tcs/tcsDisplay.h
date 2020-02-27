/*
*   FILENAME
*   tcsDisplay.h
*
*   DESCRIPTION
*   Routine definitions for tcs display routines
*
*/
/* *INDENT-OFF* */
/*
 * $Log:
 */
/* *INDENT-ON* */

#ifndef TCSDISPLAY_H
#define TCSDISPLAY_H

#include "tcsConstants.h"

void tcsLimitDisplay(int limerror, double ellimit, double timetorise, 
                     char *errstring);
#endif
