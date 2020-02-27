/*
*   FILENAME
*    tcsReadCarInfo.c
*
*   FUNCTION NAME(S)
*
*   tcsClearCarInfo     - Initialize the CAR data structure to NULL.
*   tcsPrintCarInfo     - Print out the CAR data structure contents
*   tcsFindCarnames     - Find the CAR names in the currently loaded EPICS database
*   tcsReadCarInfo      - Top-level routine to read TCS CAR data
*   tcsGetCar           - Get specified CAR record name
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsReadCarInfo.c,v $
 * Revision 1.2  2001/05/24 10:32:23  cjm
 * Change pdbBase to pdbbase for 3.13
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.3  1998/01/21 17:25:52  pbt
 * Provide return values (for errors) from Cad/Car search routines
 *
 * Revision 1.2  1997/09/01 14:51:30  pbt
 * Add extra check to ensure only top-level TCS CARs are read
 *
 * Revision 1.1  1997/02/10 17:10:59  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.2  1997/01/15 16:44:42  tcs
 * correct misuse of database pointer
 *
 * Revision 1.1  1997/01/10 14:30:38  pbt
 * New routines/sequence program to combine CAR values into softC record
 *
 *
 */
/* *INDENT-ON* */

#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <iocsh.h> 
#include <string.h>
#include <epicsTypes.h>
#include <dbStaticLib.h>
#include "tcsReadCarInfo.h"

extern struct dbBase *pdbbase;   /* Global pointer to base of current EPICS database */

/* TCS CAR records : list of names */
static char *tcsCarName[MAXCAR];

/*+
 *   Function name: tcsClearCarInfo
 *
 *   Purpose: 
 *   Initialize the data array for the CAR data
 *
 *   Description: 
 *   Initializes the pointers in the data array to NULL
 *
 *   Invocation:
 *   tcsClearCarInfo()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      None
 *
 *   Function value returned :
 *       None
 *
 *   External variables:
 *      !     tcsCarName      The global CAR data structure
 *-
 */

static void tcsClearCarInfo()
{ 
  int i;

  for (i=0; i<MAXCAR; i++)          /* Initialize pointer array */
    tcsCarName[i] = NULL ; 
}

/*+
 *   Function name: tcsPrintCarInfo
 *
 *   Purpose: 
 *   Prints the contents of the TCS CAR data structure
 *
 *   Description: 
 *   Prints the name of each defined TCS CAR record
 *
 *   Invocation:
 *   tcsPrintCarInfo()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      None
 *
 *   Function value returned :
 *       None
 *
 *   External variables:
 *      <     tcsCarName      The global CAR data structure
 *-
 */
void tcsPrintCarInfo()
{
  int i;

  for (i=0; i<MAXCAR; i++)
    if (tcsCarName[i] != NULL) printf("    %s\n", tcsCarName[i]);
}

/*+
 *   Function name: tcsFindCarNames
 *
 *   Purpose: 
 *   Finds the names of all the CAR records in the TCS database
 *
 *   Description:
 *   Accesses the EPICS database and searches for all the records
 *   with type 'car'. Allocates a new entry for the CAR
 *   record and stores its name
 *
 *   Invocation:
 *   tcsFindCarnames()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   top   char*    Top level database prefix (e.g. TCS:)
 *
 *   Function value returned :
 *       Integer number of CAR records found in the database 
 *
 *   External functions:
 *   dbInitEntry, dbFirstRecdes, dbFirstRecord,  dbGetRecordName, dbNextRecord
 *   (EPICS static database access routines. See Chapter 5 of EPICS
 *   "IOC Application Developer's Guide" for further details)
 *
 *   External variables:
 *      >     pdbbase              EPICS static database entry point (see dbStaticLib.h)
 *      !     tcsCarName           The global CAR data structure
 *-
 */
static int tcsFindCarnames(char *top)
{
  DBENTRY pdbentry;             /* Database entry */
  int status, tl;
  int ncar=0;                    /* Count of CAR records */
  char suffix[MAX_STRING_SIZE], recname[MAX_STRING_SIZE];

  if (strlen(top) == 0 || (strspn(top," ") == strlen(top)))
    { printf("Invalid TOP database prefix\n"); return -1; }
  else
    tl = strlen(top);
  dbInitEntry(pdbbase,&pdbentry);    /* Allocate DBENTRY on the stack */
  status = dbFirstRecordType (&pdbentry);  /* Get first record description */
  if (status) {printf("No database record descriptions\n"); return 0;}

/* Check record description name - interested only if it is "car" */
  while (!status) {
    if (strcmp("car", dbGetRecordTypeName (&pdbentry)) == 0)
    {
/* Get first record of this type */
      status = dbFirstRecord(&pdbentry);
      if (status) {printf("No CAR records!\n"); return 0;}
      else
/* Go through every CAR type record, getting the record name */ 
        while (!status) {
          strcpy(recname, dbGetRecordName(&pdbentry));
/* Only interested in top-level components with no colon after TOP prefix */
          strcpy(suffix, recname + tl);
          if ( (strncmp(recname, top, tl) == 0) && (strchr(suffix,':') == NULL) )
          {
            strcpy(recname, suffix);
/* Create new command entry and store the name */
            if ((tcsCarName[ncar] = (char *) malloc(strlen(recname))) == NULL)
              { printf("%d. Failed to allocate memory\n", ncar); return -1;}

            strcpy(tcsCarName[ncar], recname);
            ncar++;
            if (ncar >= MAXCAR) {printf("Exceeded %d car records\n", MAXCAR); return 0;}
          }
          status = dbNextRecord(&pdbentry);
        }
     }
  status = dbNextRecordType (&pdbentry);   /* Check through all record descriptions */
  }
  dbFinishEntry(&pdbentry);      /* Free entry off stack */
  return ncar;
}


/*+
 *   Function name: tcsReadCarInfo
 *
 *   Purpose: 
 *   Top-level routine that sets up the global CAR data in memory - 
 *   the list of CAR records from the database.
 *
 *   Description:
 *   Calls tcsClearCarInfo and tcsFindCarnames to read
 *   the database CAR.
 * 
 *   Invocation:
 *   tcsReadCarInfo(file)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   top   char*    Top level database prefix (e.g. TCS:)
 *    
 *   Function value returned :
 *    Number of CARs found : -1 if zero
 *
 *   External functions:
 *   tcsClearCarInfo, tcsFindCarnames
 *
 *   External variables:
 *      !     tcsCarName       The global CAR data structure
 *-
 */
int tcsReadCarInfo(char *top)
{
   int ncar;

   tcsClearCarInfo();                   /* Initialize CAR data structures */
   if ((ncar = tcsFindCarnames(top)) > 0)  /* If any CAR records are found ... */
     printf("Found %d CAR records in database\n", ncar);
   else
     printf("No CAR records found in database\n");
   if (ncar <= 0)
    return -1;
   else
    return 0;
}

/*+
 *   Function name: tcsGetCar
 *
 *   Purpose: 
 *   Get the name of a TCS CAR record
 *
 *   Description:
 *   Accesses the tcsCarName structure for the TCS CAR record specified
 *   by its index number. 
 *
 *   Invocation:
 *   tcsGetCar(ncar)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   ncar   int      Index number identifying the TCS CAR record
 *
 *   Function value returned :
 *       char *, pointer to TCS CAR record name. Returns
 *               NULL when no more CAR record entries or run off the end.
 *
 *   External functions
 *    none
 *
 *   External variables:
 *      >     tcsCarName     The global CAR data structure
 *-
 */
char *tcsGetCar(int ncar)
{
  if (ncar > MAXCAR) 
    return NULL;
  else
    return (tcsCarName[ncar]);
}

static const iocshArg tcsReadCarInfoArg0 = {"tcsSystem", iocshArgString };

static const iocshArg *tcsReadCarInfoArgs[] = { &tcsReadCarInfoArg0 };

static const iocshFuncDef tcsReadCarInfoFuncDef =
         {"tcsReadCarInfo", 1, tcsReadCarInfoArgs};

	 
static void tcsReadCarInfoCallFunc(const iocshArgBuf *args)
{
   tcsReadCarInfo(args[0].sval);
}

static void registerTcsReadCarInfoCommands(void)
{
      iocshRegister(&tcsReadCarInfoFuncDef, tcsReadCarInfoCallFunc);
}
epicsExportRegistrar(registerTcsReadCarInfoCommands);

