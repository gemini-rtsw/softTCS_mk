/*
*   FILENAME
*    tcsReadCadInfo.c
*
*   FUNCTION NAME(S)
*
*   tcsClearCadInfo     - Initialize the CAD data structures to NULL.
*   tcsPrintCadInfo     - Print out the CAD data structure contents
*   tcsFindCadnames     - Find the CAD names in the currently loaded EPICS database
*   tcsCadIndex         - Return an integer index for a given CAD name
*   tcsSnameIndex       - Return an integer index for a given TCS subsystem name
*   tcsReadSubcommands  - Read in TCS subsystem CAD definitions from file
*   tcsReadCadInfo      - Top-level routine to read TCS CAD and subsystem CAD data
*   tcsCadInfoIsMarked  - return flag to show record is part of a configuration
*   tcsCadInfoSetMarked - set flag to show a record is part of a configuration
*   tcsCadInfoClearMarks - clear all configuration flags
*   tcsGetSubCad        - Get subsystem CAD record names associated with a given TCS CAD
*   tcsGetCad           - Get TCS CAD record names
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsReadCadInfo.c,v $
 * Revision 1.4  2002/04/12 15:03:02  ajf
 * Fix memPartAlloc bug. Increase size of malloced array by 1.
 * strlen does not include terminating NULL character.
 * strcpy does!
 *
 * Revision 1.3  2001/05/24 10:32:23  cjm
 * Change pdbBase to pdbbase for 3.13
 *
 * Revision 1.2  1999/03/22 22:07:12  dlt
 * Comment out unused static function
 *
 * Revision 1.1.1.1  1998/11/08 00:21:07  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.5  1998/01/21 17:25:51  pbt
 * Provide return values (for errors) from Cad/Car search routines
 *
 * Revision 1.4  1997/11/21 17:07:17  pbt
 * Output message when configuartion is empty
 *
 * Revision 1.3  1997/09/17 09:47:08  pbt
 * Add routine to check for empty configuration
 *
 * Revision 1.2  1997/06/02 09:58:29  tcs
 * Add slew CAD
 *
 * Revision 1.1  1997/02/10 17:10:58  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.9  1997/01/17 12:37:57  pbt
 * ReadCadInfo no longer uses file tcsSubCad.data
 *
 * Revision 1.8  1997/01/15 16:44:41  tcs
 * correct misuse of database pointer
 *
 * Revision 1.7  1996/07/25 13:41:12  pbt
 * Added function tcsGetCad to return names of TCS CAD records
 *
 * Revision 1.6  1996/07/24 07:35:11  cjm
 * Add tcsCadInfoGetMarked
 *
 * Revision 1.5  1996/07/16 12:49:16  cjm
 * Extra print statement
 *
 * Revision 1.4  1996/07/16 11:05:19  pbt
 * Added local structure type defs : tcsCommandData is now statically
 * defined here. Moved tcsGetSubCad from sequence program to here.
 *
 * Revision 1.3  1996/07/15 07:39:07  cjm
 * Add routines to set and clear configPart
 *
 * Revision 1.2  1996/07/12 14:37:28  pbt
 * Changed tcsFindCadnames to take 'top' as parameter, so as to correctly
 * select only top-level database CAD records
 *
 * Revision 1.1  1996/07/12 09:43:25  pbt
 * Routines to read TCS CAD data from database and file
 *
 *
 */
/* *INDENT-ON* */

#include <epicsStdlib.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <string.h>
#include <epicsTypes.h>
#include <iocsh.h> 
#include <dbStaticLib.h>
#include "tcsCadInfo.h"
#include "tcsConstants.h"
#include "tcsSeqConstants.h"

#define MAXLINE 128

/* TCS subsystem commands : linked list of command names */
struct tcsSubCommand {
    char *name;                  /* The subsystem (CAD) command */
    struct tcsSubCommand *next;  /* Pointer to next subcommand definition */
  };


/* The TCS command (CAD) name with associated subsystem commands */
struct tcsCommandDef {
    char *name;                         /* Name of CAD command */
    int configPart ;                   /* True if part of a configuration */
    struct tcsSubCommand *subCommands; /* Pointer to set of TCS subsystem (CAD) commands */
  };

extern struct dbBase *pdbbase;   /* Global pointer to base of current EPICS database */

static struct tcsCommandDef *tcsCommandData[MAXCAD];

static char *tcsSubsysName[] = {"MC","M1","M2","CR","EC","AG","AO","WS"};

/*+
 *   Function name: tcsConfigEmpty
 *
 *   Purpose: 
 *   Checks through the CAD data to see whether its empty (i.e. none
 *   are marked
 *
 *   Description: 
 *   Look throught the data structure, counting the CADs
 *   that are marked. Return TRUE if none are.  
 *
 *   Invocation:
 *   tcsConfigEmpty()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      None
 *
 *   Function value returned :
 *       TRUE if no CADs are marked, FALSE if any are.
 *
 *   External variables:
 *      !     tcsCommandData       The global CAD data structure
 *-
 */

int tcsConfigEmpty()
{
   int ncad, nmarked;

    ncad = 0;
    nmarked = 0;
    while (tcsCommandData[ncad] != NULL)
      {
      if (tcsCommandData[ncad]->configPart) nmarked++; 
      ncad++;
      }
    if (nmarked == 0) epicsPrintf("Configuration is empty\n");
    return (nmarked == 0) ;

}

/*+
 *   Function name: tcsClearCadInfo
 *
 *   Purpose: 
 *   Initialize the data structures for the CAD data
 *
 *   Description: 
 *   Initializes the pointers in the data structures to NULL
 *
 *   Invocation:
 *   tcsClearCadInfo()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      None
 *
 *   Function value returned :
 *       None
 *
 *   External variables:
 *      !     tcsCommandData       The global CAD data structure
 *-
 */

static void tcsClearCadInfo()
{ 
  int i;
  struct tcsSubCommand *scptr, *nscptr;

  for (i=0; i<MAXCAD; i++)          /* Initialize pointer array */
  {
    if (tcsCommandData[i] != NULL) 
    {
      if( tcsCommandData[i]->name )
      {
        free( tcsCommandData[i]->name );
        tcsCommandData[i]->name = NULL;
      }
      if ((nscptr = tcsCommandData[i]->subCommands) != NULL)
      {
        while (nscptr != NULL)
        {
          if( nscptr->name )
          {
            free( nscptr->name );
            nscptr->name = NULL;
          }
          scptr = nscptr;
          free(scptr);
          nscptr = scptr->next;
          scptr->next = NULL;
        }
        tcsCommandData[i]->subCommands = NULL;
      }
      free(tcsCommandData[i]);
      tcsCommandData[i] = NULL;
    }
  }
}

/*+
 *   Function name: tcsPrintCadInfo
 *
 *   Purpose: 
 *   Prints the contents of the TCS CAD data structures
 *
 *   Description: 
 *   Prints the names of each defined TCS CAD record and any
 *   associated subsystem CAD records
 *
 *   Invocation:
 *   tcsPrintCadInfo()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      None
 *
 *   Function value returned :
 *       None
 *
 *   External variables:
 *      <     tcsCommandData       The global CAD data structure
 *-
 */
void tcsPrintCadInfo()
{
  int i;
  struct tcsSubCommand *scptr;

  for (i=0; i<MAXCAD; i++) 
   if (tcsCommandData[i] != NULL) 
   {
     printf("CAD : %s, configPart %d\n", tcsCommandData[i]->name,
                                         tcsCommandData[i]->configPart);
     if ((scptr = tcsCommandData[i]->subCommands) != NULL)
       while (scptr != NULL)
         {
          printf("    %s\n", scptr->name); 
          scptr = scptr->next;
         }
   }
}

/*+
 *   Function name: tcsFindCadNames
 *
 *   Purpose: 
 *   FInds the names of all the CAD records in the TCS database
 *
 *   Description:
 *   Accesses the EPICS database and searches for all the records
 *   with type 'cad'. Allocates a data structure for the CAD
 *   record and stores its name
 *
 *   Invocation:
 *   tcsFindCadnames()
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   top   char*    Top level database prefix (e.g. TCS:)
 *
 *   Function value returned :
 *       Integer number of CAD records found in the database 
 *
 *   External functions:
 *   dbInitEntry, dbFirstRecdes, dbFirstRecord,  dbGetRecordName, dbNextRecord
 *   (EPICS static database access routines. See Chapter 5 of EPICS
 *   "IOC Application Developer's Guide" for further details)
 *
 *   External variables:
 *      >     pdbbase              EPICS static database entry point (see dbStaticLib.h)
 *      !     tcsCommandData       The global CAD data structure
 *-
 */
static int tcsFindCadnames(char *top)
{
  DBENTRY pdbentry;             /* Database entry */
  int status;
  int ncad=0;                    /* Count of CAD records */
  char suffix[MAX_STRING_SIZE], recname[MAX_STRING_SIZE];

  if (strlen(top) == 0 || (strspn(top," ") == strlen(top)))
    { printf("Invalid TOP database prefix\n"); return -1; }
  dbInitEntry(pdbbase,&pdbentry);     /* Allocate DBENTRY on the stack */
  status = dbFirstRecordType (&pdbentry);  /* Get first record description */
  if (status) {printf("No database record descriptions\n"); return 0;}

/* Check record description name - interested only if it is "cad" */
  while (!status) {
    if (strcmp("cad", dbGetRecordTypeName (&pdbentry)) == 0)
    {
/* Get first record of this type */
      status = dbFirstRecord(&pdbentry);
      if (status) {printf("No cad records!\n"); return 0;}
      else
/* Go through every "cad" type record, getting the record name */ 
        while (!status) {
          strcpy(recname, dbGetRecordName(&pdbentry));
/* Only interested in top-level components with no colon after TOP prefix */
          strcpy(suffix, recname + strlen(top));
          if (strchr(suffix,':') == NULL)
          {
            strcpy(recname, suffix);
/* Create new command entry and store the name */
            if ((tcsCommandData[ncad] = 
            (struct tcsCommandDef *) malloc(sizeof(struct tcsCommandDef)) ) == NULL)
              { printf("%d. Failed to allocate memory\n", ncad); return -1;}

            if ((tcsCommandData[ncad]->name = (char *) malloc(strlen(recname)+1)) == NULL)
              { printf("%d. Failed to allocate memory\n", ncad); return -1;}

            strcpy(tcsCommandData[ncad]->name, recname);
/* Initialize the TCS subsystem commands structure */
            tcsCommandData[ncad]->subCommands = NULL;
            ncad++;
            if (ncad >= MAXCAD) {printf("Exceeded %d cad records\n", MAXCAD); return 0;}
          }
          status = dbNextRecord(&pdbentry);
        }
     }
  status = dbNextRecordType (&pdbentry);   /* Check through all record descriptions */
  }
  dbFinishEntry(&pdbentry);      /* Free entry off stack */
  return ncad;
}

/*+
 *   Function name: tcsCadIndex
 *
 *   Purpose: 
 *   Return integer index number for a named TCS CAD record
 *
 *   Description:
 *   Searches the TCS CAD data structure for the CAD with the name
 *   as supplied. Returns index number when found.
 *
 *   Invocation:
 *   tcsCadIndex(cname)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   cname   char*    Name of CAD record
 *
 *   Function value returned :
 *       Integer index number if the CAD record is found
 *       Returns -1 if named CAD record not found.
 *
 *   External functions:
 *   None
 *
 *   External variables:
 *      >     tcsCommandData       The global CAD data structure
 *-
 */
int tcsCadIndex(char *cname)
{
   int ncad;

   ncad = 0;
   while (tcsCommandData[ncad] != NULL)
     if (strcmp(tcsCommandData[ncad]->name, cname) != 0) ncad++;
     else
       return ncad;

   return -1;
}

/*+
 *   Function name: tcsSnameIndex
 *
 *   Purpose: 
 *   Return integer index number for a TCS subsystem name string
 *
 *   Description:
 *   Searches the list of TCS subsystem names
 *   Returns index number of matching string.
 *
 *   Invocation:
 *   tcsSnameIndex(sname)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >    sname   char*    Name of TCS subsystem
 *
 *   Function value returned :
 *       Integer index number if the subsystem name is found
 *       Returns -1 if named subsystem is not found.
 *
 *   External functions:
 *   None
 *
 *   External variables:
 *      >     tcsSubsysName       Constant array of subsystem name strings
 *-
 */
int tcsSnameIndex(char *sname)
{
   int nsubsys;

   for (nsubsys = 0; nsubsys < NOSUBSYS; nsubsys++)
      if (strcmp(tcsSubsysName[nsubsys], sname) == 0) break;
   if (nsubsys == NOSUBSYS) 
     return -1;
   else
     return nsubsys;
}

#if 0
/*+
 *   Function name: tcsReadSubcommands
 *
 *   Purpose: 
 *   Read a file containing list of TCS CAD records and 
 *   associated TCS subsystem CAD records. Store the
 *   contents in a global memory structure.
 *
 *   Description:
 *    Open and read the file a line at a time. Each line is assumed
 *    to have the following set of space separated fields :
 *    <tcsCADname>  <subsys:CADname> <subsys:CADname> ...
 *
 *    Line starts with the TCS CAD name, followed by any number of
 *    associated TCS subsystem CAD names, each prefaced by the subsystem
 *    name, in upper case.
 *    Blank lines or lines with '#' in the first column are ignored (comment lines)
 *     
 *    The TCS subsystem CAD data is stored as a linked list associated with
 *    the TCS CAD record.
 * 
 *   Invocation:
 *   tcsReadSubcommands(filename)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >    filename   char*    Name of data file defining CAD records
 *
 *   Function value returned :
 *    None
 *
 *   External functions:
 *   None
 *
 *   External variables:
 *      !     tcsCommandData       The global CAD data structure
 *-
 */
static void tcsReadSubcommands(char *filename)
{
     FILE *fp;
     char line[MAXLINE];
     int n, nline, ncadname, nchar, ncad;
     char cadname[32];
     char *ptr, *readptr;
     struct tcsSubCommand *scptr;

     if (filename == NULL || strlen(filename) == 0) 
       {printf("Error - no subsystem command file name\n"); return;}
     fp = fopen(filename,"r");
     if (fp == NULL) {printf("Failed to open file %s\n", filename); return;}
     nline = 0;
     while ((ptr = fgets(line, MAXLINE, fp)) != NULL)
     {
      nline++;
      if ( (strlen(line) > 0) && (line[0] != '#') )   /* Skip blank and comment lines */
      {
        ncadname = 0;
        readptr = line;
        while ((n = sscanf(readptr,"%s %n", cadname, &nchar)) == 1)
          {
           ncadname++;
/* First cadname should be a TCS CAD record name : check it, get array index */
           if (ncadname == 1) 
             {
               ncad = tcsCadIndex(cadname);
               if (ncad < 0)
                 {
                 printf ("Line %d : %s is not a known CAD record\n", nline, cadname);
                 break;
                 }
             }
/* Its a TCS subsystem command name */
           else if (ncadname == 2)
             {    
/* Allocate first subsystem CAD name */
               tcsCommandData[ncad]->subCommands = 
                 (struct tcsSubCommand *)malloc(sizeof(struct tcsSubCommand));
               scptr = tcsCommandData[ncad]->subCommands;
               scptr->name = (char *)malloc(strlen(cadname)+1);
               strcpy(scptr->name, cadname);
               scptr->next = NULL;
             }
           else if (ncadname > 2)
/* Allocate another item in the TCS subsystem CAD list */
             {
               scptr->next = (struct tcsSubCommand *)malloc(sizeof(struct tcsSubCommand));
               scptr = scptr->next;
               scptr->name = (char *)malloc(strlen(cadname)+1);
               strcpy(scptr->name, cadname);
               scptr->next = NULL;
             }
                 
           readptr = readptr + nchar - 1;
          }  /* End while sscanf */
      }  /* End if non-blank line */
     }  /* End while fgets */
     fclose(fp);
}
#endif

/*+
 *   Function name: tcsReadCadInfo
 *
 *   Purpose: 
 *   Top-level routine that sets up the global CAD data in memory, both
 *   the list of CAD records from the database and the TCS subsystem
 *   CAD data.
 *
 *   Description:
 *   Calls tcsFindCadnames and tcsReadSubcommands to read
 *   the database CAD and subsystem CAD data
 * 
 *   Invocation:
 *   tcsReadCadInfo(top)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >    top   char*    Top-level TCS database prefix string
 *
 *   Function value returned :
 *    Number of CADS found
 *
 *   External functions:
 *   tcsClearCadInfo, tcsFindCadnames, tcsReadSubcommands
 *
 *   External variables:
 *      !     tcsCommandData       The global CAD data structure
 *-
 */
int tcsReadCadInfo(char *top)
{
   int ncad;

   tcsClearCadInfo();                   /* Initialize CAD data structures */
   if ((ncad = tcsFindCadnames(top)) > 0)  /* If any CAD records are found ... */
     {
     printf("Found %d CAD records in database\n", ncad);
#if 0
     tcsReadSubcommands(file);          /* Read the file defining TCS subsystem CAD records */
#endif
     }
   else
     printf("No CAD records found in database\n");
   if (ncad <= 0)
     return -1;
    else
     return 0;
}


/*+
 *   Function name:
 *   tcsCadInfoGetMarked
 *
 *   Purpose:
 *   Returns a flag to show if record is part of a configuration
 *
 *   Description:
 *   Finds the index to the record name. If it is found then returns the 
 *   configPart flag. If the record is not found then the routine returns 0.
 *
 *   Invocation:
 *   ncad = tcsCadInfoGetMarked(recname, &configPart)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    recname  (char *)   Name of record
 *
 *   Function value:
 *      (<)   (int)  TRUE if command is marked
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

int tcsCadInfoIsMarked (char *recname)

{
 int ncad ;           /* index into command data array */

  ncad = tcsCadIndex(recname) ;

  if (ncad >= 0 )
    return tcsCommandData[ncad]->configPart;
  else
    return 0;
}
/*+
 *   Function name:
 *   tcsCadInfoSetMarked
 *
 *   Purpose:
 *   Set a flag to show a command is part of a configuration
 *
 *   Description:
 *   Searches through the list of loaded cad records then sets the flag
 *   that shows this command is part of a configuration.
 *
 *   Invocation:
 *   ncad = tcsCadInfoSetMarked(recname)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    recname  (char *)  Command name
 *
 *   Function value:
 *   (<)  status  (int)  Return status
 *       <0  => error
 *       >=0 => index to cad record
 * 
 *-
 */

int tcsCadInfoSetMarked (char *recname) 

{

 int ncad ;           /* index into command data array */

 ncad = tcsCadIndex(recname) ;

 if (ncad >= 0 )
  tcsCommandData[ncad]->configPart = TRUE ;

 return ncad ;

}

 
/*+
 *   Function name:
 *   tcsCadInfoClearMarks
 *
 *   Purpose:
 *   Clear all flags that show commands are part of a configuration
 *
 *   Description:
 *   This routine is called at the start of a preset operation on a 
 *   configuration. It simply steps through the command data structure,
 *   setting all the configPart flags to false.
 *
 *   Invocation:
 *   tcsCadInfoClearMarks() 
 *
 *-
 */

void tcsCadInfoClearMarks (void)

{

 int ncad = 0 ;

 while (tcsCommandData[ncad] != NULL)
 {
   tcsCommandData[ncad]->configPart = FALSE ;
   ncad++ ;
 }

}

/*+
 *   Function name: tcsGetSubCad
 *
 *   Purpose: 
 *   Get the names of all the subsystem CAD records
 *
 *   Description:
 *   Accesses the tcsCommandData structure for the TCS CAD record specified
 *   by its index number. Returns, with each successive call, a pointer 
 *   to the name of the next associated subsystem CAD record. These were
 *   originally read from a file. Returns NULL when no more entries.
 *   This routine is designed to be re-entrant. It is called from a sequence
 *   program and so the parameter types must be primitive - hence use of
 *   type (char **) parameter which has to be cast in the routine to type 
 *   (struct tcsSubCommand **)
 *
 *   Invocation:
 *   tcsGetSubCad(index, first, ptr)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   index  int        Index number identifying this TCS CAD record
 *      !   first  first *    Pointer to first-time through flag. Must be TRUE on
 *                            first invocation to return the first list entry.
 *      !   ptr    char **    Pointer to pointer to next subsystem CAD entry
 *
 *   Function value returned :
 *       char *, pointer to next associated subsystem CAD record name. Returns
 *               NULL when no more subsystem CAD record entries on the list.
 *
 *   External functions
 *    none
 *
 *   External variables:
 *      >     tcsCommandData       The global CAD data structure
 *-
 */
char *tcsGetSubCad(int index, int *first, char **ptr)
{
  struct tcsSubCommand **scptr;

  scptr = (struct tcsSubCommand **)ptr;
  if (*first == TRUE)
    {
     *scptr = tcsCommandData[index]->subCommands;
     *first = FALSE;
    }
  else
    *scptr = (*scptr)->next;

  *ptr = (char *)(*scptr);
  if (*scptr != NULL)
     return (*scptr)->name;
  else
     return NULL;
}

/*+
 *   Function name: tcsGetCad
 *
 *   Purpose: 
 *   Get the name of each TCS CAD record in turn
 *
 *   Description:
 *   Accesses the tcsCommandData structure for the TCS CAD record specified
 *   by its index number. Returns, with each successive call, a pointer 
 *   to the name the CAD record. These were
 *   originally read from a file. Returns NULL when no more entries.
 *   This routine is designed to be re-entrant. 
 *
 *   Invocation:
 *   tcsGetCad(ncad, first)
 *
 *   Parameters: (">" input, "!" modified, "<" output :
 *      >   ncad   int *      Index number identifying the TCS CAD record
 *      !   first  first *    Pointer to first-time through flag. Must be TRUE on
 *                            first invocation to return the first CAD entry.
 *
 *   Function value returned :
 *       char *, pointer to TCS CAD record name. Returns
 *               NULL when no more CAD record entries or run off the end.
 *
 *   External functions
 *    none
 *
 *   External variables:
 *      >     tcsCommandData       The global CAD data structure
 *-
 */
char *tcsGetCad(int *ncad, int *first)
{
  if (*first == TRUE)
    {
    *ncad = 0;
    *first = FALSE;
    }
  else
    (*ncad)++;
 
  if (*ncad > MAXCAD) 
    return NULL;
  else
    return (tcsCommandData[*ncad]->name);
}

static const iocshArg tcsReadCadInfoArg0 = {"tcsSystem", iocshArgString };

static const iocshArg *tcsReadCadInfoArgs[] = { &tcsReadCadInfoArg0 };

static const iocshFuncDef tcsReadCadInfoFuncDef =
         {"tcsReadCadInfo", 1, tcsReadCadInfoArgs};

	 
static void tcsReadCadInfoCallFunc(const iocshArgBuf *args)
{
   tcsReadCadInfo(args[0].sval);
}

static void registerTcsReadCadInfoCommands(void)
{
      iocshRegister(&tcsReadCadInfoFuncDef, tcsReadCadInfoCallFunc);
}
epicsExportRegistrar(registerTcsReadCadInfoCommands);

