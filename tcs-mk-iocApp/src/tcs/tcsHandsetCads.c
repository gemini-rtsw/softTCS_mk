/*
 *   FILENAME
 *   tcsHandsetCads.c
 *
 *   FUNCTION NAME(S)
 *   tcsCADhandset -    handset CAD routine
 *   tcsCADhandConfig - hanset configuration CAD routine
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsHandsetCads.c,v $
 * Revision 1.6  2015/06/10 10:27:05  cjm
 * Potentially log handset commands
 *
 * Revision 1.5  2001/05/24 10:23:27  cjm
 * Use new menuDirective constants
 *
 * Revision 1.4  2001/01/15 11:37:17  dlt
 * New handset interface
 *
 * Revision 1.3  2000/07/03 08:46:23  dlt
 * Add offset index to incrOffset command
 *
 * Revision 1.2  1999/01/22 03:17:36  dlt
 * add incrOffset CAD
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.4  1998/09/02 20:19:12  tcs
 * Avoid checking unused arguments
 *
 * Revision 1.3  1998/01/12 16:23:16  tcs
 * Change CAD subroutine names to tcsCADxxxx
 *
 * Revision 1.2  1998/01/05 15:55:46  tcs
 * Correct type of output step size
 *
 * Revision 1.1  1997/12/02 13:45:36  tcs
 * Convert handsets to CAD interface
 *
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include  <string.h>
#include  <dbDefs.h>
#include  <cadRecord.h>
#include  <cad.h>
#include  "tcsConstants.h"
#include  "tcsPointing.h"
#include  "tcsConfig.h"
#include  "slalib.h"
#include  <subRecord.h>
#include  "tcsInterlocks.h"
#include  "tcsDecode.h"
#include  "tcsCadSupport.h"
#include  "tcsLogSupport.h"


/*+
 *   Function name:
 *   tcsCADhandset
 *
 *   Purpose:
 *   Implements a handset button
 *
 *   Description:
 *   The increment direction is converted to an integer and written to the
 *   output link.
 *
 *   Invocation:
 *   tcsHandset (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Increment direction
 *
 *   EPICS output parameters:
 *      vala => Increment direction
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADhandset (struct cadRecord *pcad)
{

  long status ;           /* Return status */
  static int dir;         /* Direction specification */
  char message[256];
  char *cadname;

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_ACCEPT ;

/* Pull in and validate the data on the CAD input fields */

     switch (pcad->a[0]) {
     case 'U':
     case 'u':
        dir = 0;
        break;
     case 'D':
     case 'd':
        dir = 1;
        break;
     case 'L':
     case 'l':
        dir = 2;
        break;
     case 'R':
     case 'r':
        dir = 3;
        break;
     default:
        tcsCsAppendMessage( pcad, "Invalid direction specification");
        status = CAD_REJECT ;
        break;
     }

     if ( status == CAD_ACCEPT) 
        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(long *) pcad->vala = (long)dir ;

      cadname = tcsCsCadName(pcad);
      sprintf(message, "%s : Direction: %s", cadname, pcad->a);
      tcsLogMessage(message);

   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}

/*+
 *   Function name:
 *   tcsCADhandConfig
 *
 *   Purpose:
 *   Configures a handset.
 *
 *   Description:
 *   The input links are read, the data validated, converted to internal
 *   representation and written to the output links.
 *
 *   Invocation:
 *   tcsCADhandConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Step size.
 *      b => virtual telescope selection
 *      c => offset type (RADEC | AZEL | TANGENT PLANE)
 *
 *   EPICS output parameters:
 *      vala => Step size.
 *      valb => virtual telescope selection mask
 *      valc => offset type
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   Any external functions used in this function or procedure e.g
 *   function1      (library name)     What function does
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADhandConfig (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double step;     /* Step size */
  static int tel;         /* Telescope selection mask */
  static OFFCOORD coord;  /* Coordinate type */
  char *telnames[] = {
     "MOUNT",
     "SOURCE A", "SOURCE B", "SOURCE C",
     "SOURCE_A", "SOURCE_B", "SOURCE_C",
     "SOURCE", "PWFS1", "PWFS2", "OIWFS",
     "ALL", NULL
  };
  int name;
  char message[256];
  char *cadname;


/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

     status = CAD_REJECT ;

/* Pull in and validate the data on the CAD input fields */
     if (tcsDcDouble ("step: ", pcad->a, &step, pcad)) break ;


/* Decode virtual telescope specification */
     if (strcmp( tcsCsCadName(pcad), "guideHandConfig" ) != 0 ) {
        if (tcsDcString(telnames, "telescope name: ", pcad->b, &name, pcad))
               break;

/* Construct virtual telescope mask */
        switch (name) {
        case 0: tel = MOUNT_M; break;
        case 1: tel = SOURCE_A_M; break;
        case 2: tel = SOURCE_B_M; break;
        case 3: tel = SOURCE_C_M; break;
        case 4: tel = SOURCE_A_M; break;
        case 5: tel = SOURCE_B_M; break;
        case 6: tel = SOURCE_C_M; break;
        case 7: tel = SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        case 8: tel = PWFS1_M; break;
        case 9: tel = PWFS2_M; break;
        case 10: tel = OIWFS_M; break;
        case 11: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M |
                       PWFS1_M | PWFS2_M | OIWFS_M; break;
        }

/* Offset type */
        if (strcmp( tcsCsCadName(pcad), "poHandConfig" ) != 0 ) {
           if (tcsDcOffCoord("offset type: ", pcad->c, &coord, pcad)) break;
        }
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(double *) pcad->vala = (double)step ;
      *(long *) pcad->valb = (long)tel ;
      *(long *) pcad->valc = (long)coord ;

      cadname = tcsCsCadName(pcad) ;
      sprintf(message, "%s : step: %s tel: %s type: %s", 
                                      cadname, pcad->a, pcad->b, pcad->c);
      tcsLogMessage(message);


   break ;

   case menuDirectiveMARK :
   break ;

   case menuDirectiveSTOP :
   break ;

   case menuDirectiveCLEAR :
   break ;

  }

  return status ;
}
epicsRegisterFunction(tcsCADhandConfig);
epicsRegisterFunction(tcsCADhandset);
