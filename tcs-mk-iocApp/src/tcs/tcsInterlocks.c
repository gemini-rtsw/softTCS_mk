/*
*   FILENAME
*   tcsInterlocks.c
*
*   FUNCTION NAME(S)
*   tcsInterlock - attached to the interlock record
*   tcsInterlocked - returns flag to show if commands are interlocked out
*   tcsPvload      - wrapper for pvload that sets an interlock if it fails
*   tcsUpdateState - attached to the updatestate record
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsInterlocks.c,v $
 * Revision 1.2  2003/10/12 19:48:29  cjm
 * Wrapper for pvload to trap errors
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:10:41  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.1  1996/09/27 07:17:37  cjm
 * Initial version of interlock code
 *
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include  <iocsh.h> 

#include <dbDefs.h>
#include <subRecord.h>

#include "tcsInterlocks.h"
#include "tcsSeqConstants.h"

/* Define this here to avoid warnings. There is no header file to define
*  pvload but it is unlikely that the interface will ever change now
*/
int pvload (char *file, char *subst, int flags) ;

static int TCSState ;  /* either booting, initialising or running */
static int Interlocked ; /* True ( = 1) if GIS has requested an interlock */
static int pvloadFailed ; /* True if pvload fails on startup */


/*+
 *   Function name:
 *   tcsInterLock
 *
 *   Purpose:
 *   Saves interlock state set by the GIS
 *
 *   Description:
 *   The Gemini Interlock System can send an interlock demand to the TCS.
 *   This routine saves the state of that demand for use by other parts
 *   of the TCS.
 *
 *   Invocation:
 *   tcsInterlock (psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     (struct subRecord *) Pointer to subroutine structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsInterlock (struct subRecord *psub) 

{

 long status ;

 Interlocked = psub->a ;

 status = 0 ;

 return status ;
  
}


/*+
 *   Function name:
 *   tcsPvload
 *
 *   Purpose:
 *   A wrapper for pvload to trap errors on startup
 *
 *   Description:
 *   This routine wraps the pvload call so that the error return from
 *   that routine can be trapped. If an error occurs (normally due
 *   to a syntax error following some editing) then an interlock 
 *   will be set to prevent any commands being issued. Experience
 *   has shown that the errors printed at startup are missed and
 *   then it is often very hard to diagnose the resultant 
 *   misbehaviour of the TCS. Usually everything works it is just
 *   that parameters that should be set aren't.
 *
 *   Invocation:
 *   status = tcsPvload (filename, macros, flags)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  filename (char *)  pvload filename
 *      (>)  macros   (char *)  macros for expansion - see pvload documentation
 *      (>)  flags    (int)     flags - see pvload documentation
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *-
 */

/* int tcsPvload (char *filename, char *macros, int flags) */
int tcsPvload (char *filename, char *macros)
{

  int pstat ;       /* Return status from pvload */
  int flags =0;
  
  pstat = pvload (filename, macros, flags) ;
  if (pstat) {
    pvloadFailed = 1 ;
    printf ("*** pvload failed with status %d ***\n", pstat);
  }

  return pstat ;

}


/*+
 *   Function name:
 *   tcsUpdateState
 *
 *   Purpose:
 *   Stores the state of the TCS whenever the state record is processed
 *
 *   Description:
 *   On startup, the TCS passes through the states booting, initialising 
 *   and finally running. This routine stores the state of the TCS for
 *   use by other parts of the TCS.
 *
 *   Invocation:
 *   tcsUpdateState (psub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    psub   (struct subRecord *)  Pointer to subroutine structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsUpdateState (struct subRecord *psub)

{

  long status ;

  TCSState = psub->a ;

  status = 0 ;

  return status ;

}


/*+
 *   Function name:
 *   tcsInterlocked 
 *
 *   Purpose:
 *   Queries the interlock state of the TCS
 *
 *   Description:
 *   The TCS is required to interlock out all commands whenever the GIS
 *   has issued an interlock demand. It is also necessary to interlock out
 *   commands at system boot time to prevent users issuing commands
 *   before the TCS has properly initialised. This routine returns a
 *   flag that enables a calling routine to determine if either of these
 *   interlock conditions are true. It is intended that this routine
 *   is called by every CAD routine before any other processing. If an
 *   interlock is present a descriptive message is also returned which the
 *   CAD can return in its MESS field.
 *
 *   Invocation:
 *   interlock = tcsInterlocked(message)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (<)    mess     (char * )  message string
 *
 *   Function value:
 *   (<)  interlock  (int)  0 = no interlock, 1 = interlock in place 
 * 
 *-
 */

int tcsInterlocked (char *message)

{

  if (Interlocked)
  {
    strcpy (message, "GIS Interlock present") ;
    return (Interlocked) ;
  }

  if (TCSState != RUNNING)
  {
    strcpy (message, "TCS still initialising");
    return (1) ;
  }

  if (pvloadFailed) {
    strcpy (message, "pvload failed - fix file then reboot");
    return (pvloadFailed) ;
  }

  strcpy (message, " ") ;
  return 0 ;

}
epicsRegisterFunction(tcsUpdateState);

static const iocshArg tcsPvloadArg0 = {"tcsFilename", iocshArgString };
static const iocshArg tcsPvloadArg1 = {"tcsMacros",   iocshArgString };
/* static const iocshArg tcsPvloadArg2 = {"tcsFlags",    iocshArgInt }; */

static const iocshArg *tcsPvloadArgs[] = { &tcsPvloadArg0,
					   &tcsPvloadArg1 };
/*					   &tcsPvloadArg2 };  */

static const iocshFuncDef tcsPvloadFuncDef =
         {"tcsPvload", 2, tcsPvloadArgs};

	 
static void tcsPvloadCallFunc(const iocshArgBuf *args)
{
/*   tcsPvload(args[0].sval, args[1].sval, args[2].ival); */
   tcsPvload(args[0].sval, args[1].sval);
}

static void registerTcsPvloadCommands(void)
{
      iocshRegister(&tcsPvloadFuncDef, tcsPvloadCallFunc);
}
epicsExportRegistrar(registerTcsPvloadCommands);
