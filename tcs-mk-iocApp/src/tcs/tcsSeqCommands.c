/*
*   FILENAME
*   tcsSeqCommands.c
*
*   FUNCTION NAME(S)
*
*    tcsSimpleSeqComm
*    tcsCADinit 
*    tcsCADreboot 
*    tcsCADdatum 
*    tcsCADtest 
*    tcsCADobserve 
*    tcsCADendObserve 
*    tcsCADpause 
*    tcsCADcontinue 
*    tcsCADabort 
*    tcsCADstop 
*    tcsCADguide 
*    tcsCADendGuide 
*    tcsCADverify 
*    tcsCADendVerify 
*    tcsCADpark 
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsSeqCommands.c,v $
 * Revision 1.4  2001/05/24 10:40:04  cjm
 * Use new menuCarStates and menuDirective constants
 *
 * Revision 1.3  1999/06/16 21:27:31  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.2  1998/11/16 18:37:11  cjm
 * Send default datum parameters to mount when datum sequence command is issued
 *
 * Revision 1.1.1.1  1998/11/08 00:21:08  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.9  1998/07/28 15:11:36  tcs
 * Change calling sequence for pvload version 2.12
 *
 * Revision 1.8  1998/02/06 14:28:25  tcs
 * Prevent enclosure being disabled by park CAD except on START
 *
 * Revision 1.7  1998/01/21 17:29:05  pbt
 * Return error value in tcsSeqInitActions routine
 *
 * Revision 1.6  1998/01/13 11:52:14  tcs
 * Change names of CAD subroutines
 *
 * Revision 1.5  1997/12/03 17:38:03  pbt
 * Set enclosure auto move flags to FALSE in SeqInitActions
 *
 * Revision 1.4  1997/10/10 07:17:05  cjm
 * Set ECS enable flags in park
 *
 * Revision 1.3  1997/10/03 11:21:59  pbt
 * Park command changed in M1 and PARK sequence command
 *
 * Revision 1.2  1997/03/05 09:36:59  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:11:05  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.8  1997/02/10 14:44:44  pbt
 * Changes to allow initialization (pvload etc) for INIT sequence command
 *
 * Revision 1.7  1997/01/20 15:35:24  pbt
 * New routines to read simulation file names -
 * but commented 'init'out use of pvload etc. (bug)
 *
 * Revision 1.6  1997/01/17 12:38:38  pbt
 * Updated sequence command CAD subroutines for new and renamed commands
 *
 * Revision 1.5  1996/12/13 13:24:56  tcs
 * replace tcsLibrary with tcsDecode routines
 *
 * Revision 1.4  1996/12/13 10:07:56  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.3  1996/12/12 16:57:14  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.2  1996/08/01 15:00:58  tcs
 * comment out debugging output
 *
 * Revision 1.1  1996/07/23 10:39:33  pbt
 * Separate module for TCS sequence command subroutines
 *
 *
 */
/* *INDENT-ON* */

#include  <unistd.h>
#include  <epicsStdioRedirect.h>
#include  <registryFunction.h>
#include  <epicsExport.h>
#include  <string.h>
#include  <iocsh.h> 
#include  <math.h>
#include  <dbDefs.h>
#include  <cadRecord.h>
#include  <cad.h>
#include  "tcsConstants.h"
#include  "tcsCommands.h"
#include  "tcsConfig.h"
#include  "tcsCadInfo.h"
#include  "tcsReadCarInfo.h"
#include  "slalib.h"
#include  "tcsPointing.h"
#include  "timeLib.h"
#include  "tcsCadSupport.h"
#include  "tcsEcsLib.h"


   #define MAX_PATH_LEN 256

   static char tcsSimDefFile[MAX_PATH_LEN];    /* TCS Simulation defaults parameter file name */
   static char tcsDefFile[MAX_PATH_LEN];       /* Main TCS defaults parameter file name */
   static char tcsCurrDefFile[MAX_PATH_LEN];   /* TCS current values defaults parameter file name */

/*+
 *   Function name:
 *   tcsSimpleSeqComm
 *
 *   Purpose:
 *   Implement a simple OCS sequence command
 *
 *   Description:
 *   At present this routine has nothing to do as there are no parameters
 *   associated with the command. Hence there is nothing to check and
 *   everything is handled by EPICS.
 *
 *   At present the output message does not appear in the mess field
 *   due to the current implementation of the CAD
 *
 *   Invocation:
 *   tcsSimpleSeqComm (pcad) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) CAD record structure
 *
 *   Function value:
 *   (<) status (long) Status return, 0 = OK
 * 
 *-
 */

long tcsSimpleSeqComm ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  char *comname;         /* Command name without prefix */

  status = CAD_ACCEPT ;
  comname = tcsCsCadName( pcad );

  switch (pcad->dir)
  {
    case menuDirectiveMARK:
#if 0
    printf ("%s: mark received\n", pcad->name) ;
#endif
    tcsCsSetMessageN( pcad, comname, ": MARK accepted", (char*)NULL);
    break ;

    case menuDirectivePRESET :
#if 0
    printf ("%s: preset received\n", pcad->name) ;
#endif
    status = tcsConfigMarkSeqComm(pcad->name, pcad->mess)  ;
    if (status)
      status = CAD_REJECT ;
    break ;

    case menuDirectiveSTART :
#if 0
    printf ("%s:  start received\n", pcad->name) ;
#endif
    tcsCsSetMessageN( pcad, comname, ": START accepted", (char*)NULL);
    break ;

    case menuDirectiveSTOP :
#if 0
    printf ("%s: stop received\n", pcad->name) ;
#endif
    tcsCsSetMessageN( pcad, pcad->name, ": ", comname, 
       " cannot be stopped", (char*)NULL);
    break ;

    case menuDirectiveCLEAR :
#if 0
    printf ("%s: clear received\n", pcad->name) ;
#endif
    tcsCsSetMessageN( pcad, comname, ": CLEAR accepted", (char*)NULL);
    break ;

    default :
#if 0
    printf ("%s: default\n", pcad->name) ;
#endif
    tcsCsSetMessageN( pcad, comname, ": Unrecognised directive", (char*)NULL);
    status = CAD_REJECT ;
    break ;

  }
  return status ;
}


/*+
 *   Function name:
 *   tcsSaveDefFnames
 *
 *   Purpose:
 *   Save the full path names of the pvload initial parameter files
 *
 *   Description:
 *   The partial path names of 3 files are input : using a 
 *   call to getcwd the the full path names are constructed and
 *   saved in variables global to this module.
 *
 *   Invocation:
 *    tcsSaveDefFnames(simdef, tcsdef, tcscurr) 
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *         >  simdef    char *    Name of TCS simulation initial value parameter file
 *         >  tcsdef    char *    Name of main TCS initial value parameter file
 *         >  tcscurr   char *    Name of TCS 'current value' initial value parameter file
 *
 *   Function value:
 *   (<) status (long) Status return, 0 = OK
 *
 *   External functions:
 *   getcwd          VxWorks/POSIX routine     Get current working directory
 *
 *   External variables:
 *    <    tcsSimDefFile   char *   TCS Simulation initial value parameter filename
 *    <    tcsDefFile      char *   Main TCS initial value parameter filename
 *    <    tcsCurrDefFile  char *   TCS 'current value' initial value parameter filename
 *-
 */
void tcsSaveDefFnames(char *simdef, char *tcsdef, char *tcscurr)
{
   char cwd[MAX_PATH_LEN];

/* Get current working directory */
   getcwd(cwd, sizeof(cwd));

/* Construct full file names. If a path is relative, prepend current dir and / */
   memset(tcsSimDefFile, 0, MAX_PATH_LEN);
   memset(tcsDefFile, 0, MAX_PATH_LEN);
   memset(tcsCurrDefFile, 0, MAX_PATH_LEN);

   if (simdef[0] == '/') {
     strncpy(tcsSimDefFile, simdef, MAX_PATH_LEN - 1);
   } else {
     sprintf(tcsSimDefFile,"%s/%s", cwd, simdef);
   }

   if (simdef[0] == '/') {
     strncpy(tcsDefFile, tcsdef, MAX_PATH_LEN - 1);
   } else {
     sprintf(tcsDefFile,"%s/%s", cwd, tcsdef);
   }

   if (simdef[0] == '/') {
     strncpy(tcsCurrDefFile, tcscurr, MAX_PATH_LEN - 1);
   } else {
     sprintf(tcsCurrDefFile,"%s/%s", cwd, tcscurr);
   }

   printf("%s\n", tcsSimDefFile);
   printf("%s\n", tcsDefFile);
   printf("%s\n", tcsCurrDefFile);
}


int pvload(
    char *file,                 /* (>) name of file containing list of PV
                                       assignments (if NULL, stdin is used) */

    char *subst,                /* (>) list of macro substitutions of the form
                                       "a=b, c=d", where "$(a)" references
                                       macro a (can be NULL) */

    int flags) ;                /* (>) extra flags:
                                        1 bit   => debugging ("-d")
                                        2 bit   => no CA init ("-n") 
                                        4 bit   => abort shell on error */


/*+
 *   Function name:
 *    tcsSeqInitActions
 *
 *   Purpose:
 *   Carry out any TCS internal initialisation to be done on receipt
 *   of an init sequence command. This function will normally be
 *   called from within a sequence program.
 *
 *   Description:
 *    At the moment the following actions are carried out when an init
 *    sequence command is received by the TCS :
 *    - 3 calls to pvload, having constructed the full file names for the pvload
 *      parameter files
 *    - Read in the CAR and CAD info from the current database, re-initialising
 *      the internal data structures representing these records.
 *    - Set the carousel/shutter automatic move flags to FALSE
 *
 *   Invocation:
 *     tcsSeqInitActions(prefix)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *         >  prefix    char *    Top-level TCS EPICS prefix (e.g. "tcs:")
 *
 *   Function value:
 *   (<) status (long) Status return, 0 = OK
 *
 *   External functions:
 *       pvload
 *
 *-
 */
long tcsSeqInitActions( char *prefix )
{
   char startpars[256];
   long retstat = 0;    /* Return value */

/* Construct start parameters for first pvload call : simulator default file */
   sprintf(startpars,"top=%s, mc=%smc:, cr=%scr:, m2=%sm2:, ec=%sec:, ag=%sag:, ws=%sws:",
           prefix, prefix, prefix, prefix, prefix, prefix, prefix); 
   retstat = pvload(tcsSimDefFile, startpars, 2);
   if (retstat != 0) return retstat;
   printf("pvload(%s,%s)\n", tcsSimDefFile, startpars);

/* Construct start parameters for second pvload call : TCS default file
   The top-level TCS EPICS prefix was supplied as a parameter */
   sprintf(startpars,"top=%s", prefix); 
   retstat = pvload(tcsDefFile, startpars, 2);
   if (retstat != 0) return retstat;
   printf("pvload(%s,%s)\n", tcsDefFile, startpars);

/* Construct start parameters for third pvload call : TCS current value file */
   sprintf(startpars,"top=%s", prefix); 
   retstat = pvload(tcsCurrDefFile, startpars, 2);
   if (retstat != 0) return retstat;
   printf("pvload(%s,%s)\n", tcsCurrDefFile, startpars);

/* Read in CAR and CAD record information */
   retstat = tcsReadCarInfo(prefix);
   if (retstat != 0) return retstat;
   retstat = tcsReadCadInfo(prefix);
   if (retstat != 0) return retstat;

/* Set the automatic move flags to FALSE for dome and shutters */
   tcsEcsEnableDome(FALSE);
   tcsEcsEnableShtrs(FALSE);

   return retstat;
}


long tcsCADinit ( struct cadRecord *pcad)

{
   long status ;          /* return status */
   status = tcsSimpleSeqComm(pcad);
   return status ;

}

long tcsCADreboot ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}
long tcsCADdatum ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);

/* This is something of a fudge. The datum command is specified to have 
*  no parameters. Unfortuneately, the mount has a number of different
*  ways to datum which require additional parameters to be sent to it. 
*  The TCS gets round this by sending default values which have been
*  initialised by pvload. 
*  N.B. field A can't be used as the OCS writes "MARK" into this field
*/  
  if (pcad->dir == menuDirectiveSTART) {
    strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
    strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
    strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE) ;
  } ;
    
  return status ;

}

long tcsCADtest ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADobserve ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADendObserve ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADpause ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADcontinue ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADabort ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADstop ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADguide ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADendGuide ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADverify ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}

long tcsCADendVerify ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  return status ;

}
long tcsCADpark ( struct cadRecord *pcad)

{
  long status ;          /* return status */
  status = tcsSimpleSeqComm(pcad);
  if (pcad->dir == menuDirectiveSTART) {

/* Set parameter for PARKing M1 */
    strncpy(pcad->vala, "PARK", 4) ;

/* Make sure that automatic updates of the dome & shutters are disabled */
    tcsEcsEnableDome (FALSE);
    tcsEcsEnableShtrs (FALSE);
  }
  return status ;

}
epicsRegisterFunction(tcsCADpause);
epicsRegisterFunction(tcsCADabort);
epicsRegisterFunction(tcsCADstop);
epicsRegisterFunction(tcsCADtest);
epicsRegisterFunction(tcsCADpark);
epicsRegisterFunction(tcsCADreboot);
epicsRegisterFunction(tcsCADendGuide);
epicsRegisterFunction(tcsCADinit);
epicsRegisterFunction(tcsCADendObserve);
epicsRegisterFunction(tcsCADdatum);
epicsRegisterFunction(tcsCADcontinue);
epicsRegisterFunction(tcsCADobserve);
epicsRegisterFunction(tcsCADguide);
epicsRegisterFunction(tcsCADendVerify);
epicsRegisterFunction(tcsCADverify);


static const iocshArg tcsSaveDefNamesArg0 = {"tcsSimDef",     iocshArgString };
static const iocshArg tcsSaveDefNamesArg1 = {"tcsSimSiteDef", iocshArgString };
static const iocshArg tcsSaveDefNamesArg2 = {"tcsSimCurrDef", iocshArgString };

static const iocshArg *tcsSaveDefNamesArgs[] = { &tcsSaveDefNamesArg0,
					         &tcsSaveDefNamesArg1,
					         &tcsSaveDefNamesArg2 };

static const iocshFuncDef tcsSaveDefNamesFuncDef =
         {"tcsSaveDefFnames", 3, tcsSaveDefNamesArgs};

	 
static void tcsSaveDefNamesCallFunc(const iocshArgBuf *args)
{
   tcsSaveDefFnames(args[0].sval, args[1].sval, args[2].sval);
}

static void registerTcsSaveDefNamesCommands(void)
{
      iocshRegister(&tcsSaveDefNamesFuncDef, tcsSaveDefNamesCallFunc);
}
epicsExportRegistrar(registerTcsSaveDefNamesCommands);

