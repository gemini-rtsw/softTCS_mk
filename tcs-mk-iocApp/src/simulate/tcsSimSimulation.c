/*
*   FILENAME
*   tcsSimSimulation.c
*
*   FUNCTION NAME(S)
*   tcsSimLog - subroutine for the time system log record
*   tcsSimNullInit - null initialisation routine for subroutine records
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSimSimulation.c,v $
 * Revision 1.4  2001/05/25 07:24:49  cjm
 * Remove sir.h
 *
 * Revision 1.3  2001/04/17 15:56:18  cjm
 * Include stdio.h to avoid warnings
 *
 * Revision 1.2  1999/06/16 21:26:51  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.1.1.1  1998/11/08 00:21:11  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.2  1997/12/01 16:31:06  pbt
 * Add routine tcsSimScanControl
 *
 * Revision 1.1  1997/02/10 17:11:20  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/05/22 22:12:21  cjm
 * Initial version
 *
 */
/* *INDENT-ON* */


#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <subRecord.h>
#include <sirRecord.h>
#include <genSubRecord.h>
#include "tcsSimSimulation.h"
#include "timeLib.h"

/*+
 *   Function name:
 *   tcsSimLog
 *
 *   Purpose:
 *   Supports log record as defined in ICD4
 *   The log record in question is that for the time system used by
 *   the TCS internal simulations
 *
 *   Description:
 *   The routine reads the current time using the timeNowC routine and
 *   then formats it as prescribed by ICD4. It then appends the
 *   message written by the user, truncating it if neccessary in order
 *   to fit within the maximum string length supported by EPICS.
 *   The completed message is then output.
 *   The time scale used is currently UTC.
 *
 *   Invocation:
 *   tcsSimLog(psir)
 *
 *   This routine is only expected to be called by the EPICS process
 *   routine
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psir     (struct sirRecord *)  ptr to SIR record structure
 *
 *   Function value:
 *   Status  - used by process to set the BSRV field
 * 
 *   Deficiencies:
 *   The user string can easly be truncated as it can only effectively
 *   contain 16 characters. This cannot be corrected without recompiling
 *   the whole of EPICS. To try and preserve the whole message, the user
 *   input is copied unchanged to the IMSS field
 *
 *-
 */

 long tcsSimLog (struct sirRecord *psir)

{

char logstring[MAX_STRING_SIZE] ;    /* output string */
int  idate[7] ;                      /* dated returned from timeNowC */

/* Fetch current date & time and format as per ICD4 */

 timeNowC (UTC, 2, idate) ;
 sprintf (logstring, "%4d-%2.2d-%2.2d-%2.2d:%2.2d:%2.2d.%2.2d ",
          idate[0], idate[1], idate[2], idate[3], idate[4], idate[5],
          idate[6]) ;

/* Fetch message string set by user and concatenate with date */

 strncat (logstring, psir->val, MAX_STRING_SIZE - 24) ;

 strncpy (psir->imss, psir->val, MAX_STRING_SIZE) ;
 strncpy (psir->val, logstring, MAX_STRING_SIZE) ;

 return 0 ;

}


/*+
 *   Function name:
 *   tcsSimNullInit
 *
 *   Purpose:
 *   Null initialisation routine for subroutine records
 *
 *   Description:
 *   This routine is just a place holder, it does nothing.
 *
 *   Invocation:
 *   tcsSimNullInit(psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     struct subRecord *  Pointer to psub structure
 *
 *   Function value:
 *   Return status as a long
 *
 *-
 */

long tcsSimNullInit (struct subRecord *psub)
{

  return 0 ;

}

/*+
 *   Function name:
 *   tcsSimScanControl
 *
 *   Purpose:
 *   gensub to control internal simulator by outputting
 *   a string to the SCAN field of the relevant record
 *
 *   Invocation:
 *   tcsAgStop
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input parameters :
 *
 *   a    => Integer value : 0 = Switch simulation ON; 1 = Switch simulation OFF   
 *   b    => String for SCAN field when switching ON (Always 'Passive' for OFF)
 *   vala => output string for simulator control
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

long tcsSimScanControl(struct genSubRecord *pgsub)
{
    if (*(long *)(pgsub->a))
      strncpy(pgsub->vala, pgsub->b, MAX_STRING_SIZE);
    else
      strcpy(pgsub->vala,"Passive");
    return (0);
}
epicsRegisterFunction(tcsSimScanControl);
epicsRegisterFunction(tcsSimLog);
epicsRegisterFunction(tcsSimNullInit);



