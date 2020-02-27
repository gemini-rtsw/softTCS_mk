/*
*   FILENAME
*   tcsSaveLoadCad.c
*
*   FUNCTION NAME(S)
*   tcsSaveLoadCad    - Define Channel Access event handler routine for save/load commands
*                       issued
*   loadcallback      - Event handler routine called for LOAD CAD record. 
*   savecallback      - Event handler routine called for SAVE CAD record
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSaveLoadCad.c,v $
 * Revision 1.4  2012/10/01 15:53:49  cjm
 * Remove un-needed print statement
 *
 * Revision 1.3  2001/05/24 10:40:03  cjm
 * Use new menuCarStates and menuDirective constants
 *
 * Revision 1.2  1999/03/22 22:07:50  dlt
 * Use %ld for printing longs
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/02/10 17:11:01  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1996/12/20 15:08:21  pbt
 * Uses save/load file path prefix to select file destination
 *
 * Revision 1.3  1996/12/12 16:57:13  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.2  1996/09/30 17:01:03  pbt
 * Alterations to tcsConfig save and load routines
 *
 * Revision 1.1  1996/09/06 10:58:11  pbt
 * Task to implement the SAVE and LOAD CAD commands, using Channel Access calls.
 *
 *
 *
 *
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <string.h>
#include <cadef.h>
#include <db_access.h>
#include <cadRecord.h>
#include <menuCarstates.h>
#include "tcsConstants.h"
#include "tcsConfig.h"
#include "tcsChannelAccess.h"
#include "slalib.h"
#include <epicsThread.h>
#include <epicsEvent.h>
#include <epicsExport.h>
#include <epicsPrint.h>
#include <iocsh.h>

void loadcallback (struct event_handler_args arg) ;
void savecallback (struct event_handler_args arg) ;


/*+
 *   Function name:
 *   tcsSaveLoadCad
 *
 *   Purpose:
 *   Initialize the SAVE/LOAD CAR values and define the EPICS Channel Access 
 *   event handler routines to be used when the SAVE or LOAD CAD records are
 *   triggered.
 *
 *   Description:
 *   This routine is to implement the SAVE and LOAD commands in the TCS. It needs to be 
 *   run as a separate VxWorks task rather than in the CAD subroutine since the actions use
 *   file I/O and extensive Channel Access calls and block for a considerable time.
 *
 *   It sets up EPICS Channel Access event routines which are called whenever the value 
 *   in the associated records saveP:start and loadP:start changes. This is triggered 
 *   by a START directive being issued to the CAD records.
 *
 *   Invocation:
 *   tcsSaveLoadCad(top)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  top     (char *)     The top-level database name string
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Channel Access return status, 0 = OK
 * 
 *   External functions:
 *   ca_task_initialize, ca_pend_event   EPICS Channel Access library
 *   tcsCaPut, tcsCaEventHandler         tcsChannelAccess
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
int tcsSaveLoadCad(char *top)
{
  /* int ca_status ; */
  int carval ;
  /* ca_status = ca_task_initialize() ;
  if (ca_status != ECA_NORMAL)
  {
   printf ("Channel access failed to initialise\n") ;
   return(-1) ;
  } */
  
  /* Create ca context with preemptive callback enabled -- Now required in EPICS 3.14 */
  SEVCHK(ca_context_create(ca_enable_preemptive_callback), "tcsSaveLoadCad() calling ca_context_create()");
  

/* Initialise CAR values */
  carval = menuCarstatesIDLE ;
  tcsCaPut(top, "saveC.IVAL", &carval) ;
  tcsCaPut(top, "loadC.IVAL", &carval) ;

/* Set up the event handler routines, passing the 'top' parameter */
  tcsCaEventHandler(top, "loadP:start.VAL", loadcallback) ;
  tcsCaEventHandler(top, "saveP:start.VAL", savecallback) ;

  ca_pend_event(0.0) ;
  return(0) ;
}

/*+
 *   Function name:
 *   loadcallback
 *
 *   Purpose:
 *   This is the event handler routine triggered when the LOAD CAD record has a
 *   START directive issued.
 *
 *   Description:
 *   Sets the LOAD CAR state to busy, then reads and puts the LOAD input parameters
 *   (this ensures that any defaults are displayed on a dm screen). The TCB data
 *   is read from the specified file and then all the CAD record input fields 
 *   are set to the newly loaded values. The LOAD CAR status is set back to IDLE
 *   (or ERROR if an error ocurred).  
 *
 *   Invocation:
 *   loadcallback(arg)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  arg     (struct event_handler_args arg)     Channel Access data block
 *
 *  The data structure 'event_handler_args' is as follows :
 *
 *      void    *usr;   * User argument supplied when event added  (='top' string)   
 *      chid    chid;   * Channel id                                   
 *      long    type;   * the type of the value returned (long aligned)
 *      long    count;  * the element count of the item returned       
 *      void    *dbr;   * Pointer to the value returned                
 *      int     status; * CA Status of the op from server - CA V4.1    
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsCaPut, tcsCaGet                               tcsChannelAccess
 *   tcsConfigLoadTcb, tcsConfigSetAllTargetFields    tcsConfig
 *   slaIntin                                         slaLib
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

void loadcallback (struct event_handler_args arg)
{
   static int first = TRUE ;
   char top[8] ;
   int carval;
   int markval = 0 ;
   int nptr, status ;
   char errmess[MAX_STRING_SIZE] ;
   char LtcbDefn[MAX_STRING_SIZE] ;
   long tcbDefn ;
   char Lfilename[MAX_STRING_SIZE] ;

   if (first)
   {
     first = FALSE ;
     return ;
   }

   strncpy(top, (char *)arg.usr, 8) ;     /* Get supplied argument = "top" */

/* Set the CAR status to BUSY */
   carval = menuCarstatesBUSY ;
   (void) tcsCaPut(top, "loadC.IVAL", &carval) ;

/* Get/Put the input parameter values for the LOAD command */
   tcsCaGet(top, "load.A", LtcbDefn) ;
   tcsCaGet(top, "load.B", Lfilename) ;
   tcsCaPut(top, "load.A", LtcbDefn) ;
   tcsCaPut(top, "load.B", Lfilename) ;
   tcsCaPut(top, "load.MARK", &markval) ;

   nptr = 1 ;
   slaIntin (LtcbDefn, &nptr, &tcbDefn, &status) ;
/* Read the TCB data in from the specified file */
   status = tcsConfigLoadTcb(tcbDefn, Lfilename, errmess);
   if (status == 0) 
     {
/* Set all the newly loaded CAD input field string values */
     tcsConfigSetAllTargetFields(top, tcbDefn) ;
     carval = menuCarstatesIDLE ;
     }
   else
     carval = menuCarstatesERROR ;
/* Set the LOAD CAR status to IDLE or ERROR */
   (void) tcsCaPut(top, "loadC.IMSS", errmess) ;
   (void) tcsCaPut(top, "loadC.IVAL", &carval) ;
}

/*+
 *   Function name:
 *   savecallback
 *
 *   Purpose:
 *   This is the event handler routine triggered when the SAVE CAD record has a
 *   START directive issued.
 *
 *   Description:
 *   Sets the SAVE CAR state to busy, then reads and puts the SAVE input parameters
 *   (this ensures that any defaults are displayed on a dm screen). The TCB data
 *   is written to the specified file ; The SAVE CAR status is then set back to IDLE
 *   (or ERROR if an error ocurred).  
 *
 *   Invocation:
 *   savecallback(arg)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  arg     (struct event_handler_args arg)     Channel Access data block
 *
 *  The data structure 'event_handler_args' is as follows :
 *
 *      void    *usr;   * User argument supplied when event added  (='top' string)   
 *      chid    chid;   * Channel id                                   
 *      long    type;   * the type of the value returned (long aligned)
 *      long    count;  * the element count of the item returned       
 *      void    *dbr;   * Pointer to the value returned                
 *      int     status; * CA Status of the op from server - CA V4.1    
 *
 *   Function value:
 *   None
 * 
 *   External functions:
 *   tcsCaPut, tcsCaGet  tcsChannelAccess
 *   tcsConfigSaveTcb    tcsConfig
 *   slaIntin            slaLib
 *
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */
void savecallback (struct event_handler_args arg)
{
   static int first = TRUE ;
   char top[8] ;
   int carval ;
   int markval = 0 ;
   int nptr, status ;
   char errmess[MAX_STRING_SIZE] ;
   char StcbDefn[MAX_STRING_SIZE] ;
   long tcbDefn ;
   char Sfilename[MAX_STRING_SIZE] ;
   char Scomment[MAX_STRING_SIZE] ;

   if (first)
   {
     first = FALSE ;
     return ;
   }

   strncpy(top, (char *)arg.usr, 8) ;     /* Get supplied argument = "top" */

/* Set the CAR status to BUSY */
   carval = menuCarstatesBUSY ;
   (void) tcsCaPut(top, "saveC.IVAL", &carval) ;

/* Get/Put the input parameter values for the LOAD command. This forces
   any dm display of these fields to be updated  */
   tcsCaGet(top, "save.A", StcbDefn) ;
   tcsCaGet(top, "save.B", Sfilename) ;
   tcsCaGet(top, "save.C", Scomment) ;
   tcsCaPut(top, "save.A", StcbDefn) ;
   tcsCaPut(top, "save.B", Sfilename) ;
   tcsCaPut(top, "save.C", Scomment) ;
   tcsCaPut(top, "save.MARK", &markval) ;

   nptr = 1 ;
   slaIntin (StcbDefn, &nptr, &tcbDefn, &status) ;

   status = tcsConfigSaveTcb(tcbDefn, Sfilename, Scomment, errmess);
   if (status == 0)
     carval = menuCarstatesIDLE ;
   else
     carval = menuCarstatesERROR ;
   (void) tcsCaPut(top, "saveC.IMSS", errmess) ;
   (void) tcsCaPut(top, "saveC.IVAL", &carval) ;
}
static const iocshArg tcsSaveLoadCadArg0 = {"top", iocshArgString };

static const iocshArg *tcsSaveLoadCadArgs[] = { &tcsSaveLoadCadArg0 };

static const iocshFuncDef tcsSaveLoadCadFuncDef =
         {"tcsSaveLoadCad", 1, tcsSaveLoadCadArgs};

static void tcsSaveLoadCadCallFunc(const iocshArgBuf *args)
{
   tcsSaveLoadCad(args[0].sval);
}

static void registerTcsSaveLoadCadCommands(void)
{
      iocshRegister(&tcsSaveLoadCadFuncDef, tcsSaveLoadCadCallFunc);
}
epicsExportRegistrar(registerTcsSaveLoadCadCommands);
