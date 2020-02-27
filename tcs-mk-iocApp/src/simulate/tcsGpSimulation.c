/*
*   FILENAME
*   tcsGpSimulation.c
*
*   This module holds the routines that are used in the GPOL Simulation
*
*   FUNCTION NAME(S)
*
*   tcsGpGenericCAD - general purpose CAD routine
*   tcsGpplateMoveCAD - simulates the GPOL plateBeam and platePark commands
*   tcsGpplateSeqCAD - simulate the GPOL seq command
*
*/
/* *INDENT-OFF* */
/*
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <ctype.h>
#include <registryFunction.h>
#include <epicsExport.h>

#include <dbDefs.h>
#include <subRecord.h>
#include <genSubRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <menuCarstates.h>

#include "tcsDecode.h"
#include "tcsCadSupport.h"

/*+
 *   Function name:
 *   tcsGpplateAngleCAD
 *
 *   Purpose:
 *   Implements a simulation of the GPOL plateAngle command
 *
 *   Description:
 *   The routine accepts whatever angle is sent and checks if it is one
 *   of those that should set the Hall sensor. If it is then the Hall
 *   sensor output is set to CLOSED otherwise it is set to OPEN.
 *
 *   Invocation:
 *   tcsGpplateAngleCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Epics inputs:
 *   e -> Upper plate name
 *   f -> Upper plate angle (degs) 
 *   g -> Middle plate name
 *   h -> Middle plate angle (degs) 
 *   i -> Lower plate name
 *   j -> Lower plate angle (degs) 
 *
 *   Epics outputs:
 *   valf -> Upper plate demand (degs)
 *   valh -> Middle plate demand (degs)
 *   valj -> Lower plate demand (degs)
 *   valq -> Mask to process output links
 *   valr -> Upper plate Hall switch (OPEN | CLOSED)
 *   vals -> Middle plate Hall switch (OPEN | CLOSED)
 *   valt -> Lower plate Hall switch (OPEN | CLOSED)
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsGpplateAngleCAD (struct cadRecord *pcad)
{
   int status;                /* return status */

   static int moveUpper ;
   static int moveMiddle ;
   static int moveLower ;
   static double upAngle ;
   static double midAngle ;
   static double lowAngle ;
   static double prevUpAngle = 10.0;
   static double prevMidAngle = 10.0;
   static double prevLowAngle = 10.0 ;
  

   double tol ;               /* Tolerance for Hall switches */
   long mask ;                /* Mask for triggering links */
   double da ;                /* Difference of successive demands (degs) */

   status = CAD_ACCEPT ;
   tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);


   switch(pcad->dir)
   {
   case menuDirectivePRESET:

     status = CAD_REJECT ;

/* Check the input demands for validity */
      if (tcsDcNotEmpty(pcad->e)) {
        if (tcsDcDouble ("upper :", pcad->f, &upAngle, pcad))
          break;
        if (upAngle < 0 || upAngle > 360.0) {
          tcsCsAppendMessage (pcad, "upper: out of range") ;
          break ;
        }
        moveUpper = 1 ;
      } else {
        moveUpper = 0 ;
      } 

      if (tcsDcNotEmpty(pcad->g)) {
        if (tcsDcDouble ("middle :", pcad->h, &midAngle, pcad))
          break;
        if (midAngle < 0 || midAngle > 360.0) {
          tcsCsAppendMessage (pcad, "middle: out of range") ;
          break ;
        }
        moveMiddle = 1 ;
      } else {
        moveMiddle = 0 ;
      }

      if (tcsDcNotEmpty(pcad->i)) {
        if (tcsDcDouble ("lower :", pcad->j, &lowAngle, pcad))
          break;
        if (lowAngle < 0 || lowAngle > 360.0) {
          tcsCsAppendMessage (pcad, "middle: out of range") ;
          break ;
        }
        moveLower = 1 ;
      } else {
        moveLower = 0 ;
      }

      status = CAD_ACCEPT ;

      break ;

   case menuDirectiveSTART:

/* write output message (n.b. no more that 28 characters) */
      printf("GPOLsim: %s started\n", tcsCsCadName(pcad));

/* Output the relevant angles and switch statuses depending on the input
*  demands.
*/
      tol = 1.0 ;           /* From tests on Gemini North */
      mask = 17 ;           /* Always drive links 1 and 5 */

      if (moveUpper) {
       if (((upAngle > -tol) && (upAngle < tol)) || 
           ((upAngle > 22.5 - tol) && (upAngle < 22.5 + tol)) ||
           ((upAngle > 45.0 - tol) && (upAngle < 45.0 + tol)) ||
           ((upAngle > 67.5 - tol) && (upAngle < 67.5 + tol)) ||
           ((upAngle > 90.0 - tol) && (upAngle < 90.0 + tol)) ||
           ((upAngle > 135.0 - tol) && (upAngle < 135.0 + tol))) {
         strcpy(pcad->valr, "CLOSED") ;
         da = prevUpAngle - upAngle ;
         if (da < 0.0 ) da = -da ;
         if (da > 2*tol) mask += 2 ;
    
       } else {
         strcpy(pcad->valr, "OPEN") ;
       }
       strcpy(pcad->valf, pcad->f) ; 
      }
      if (moveMiddle) {
       if (((midAngle > -tol) && (midAngle < tol)) || 
           ((midAngle > 22.5 - tol) && (midAngle < 22.5 + tol)) ||
           ((midAngle > 45.0 - tol) && (midAngle < 45.0 + tol)) ||
           ((midAngle > 67.5 - tol) && (midAngle < 67.5 + tol)) ||
           ((midAngle > 90.0 - tol) && (midAngle < 90.0 + tol)) ||
           ((midAngle > 135.0 - tol) && (midAngle < 135.0 + tol))) {
         strcpy(pcad->vals, "CLOSED") ;
         da = prevMidAngle - midAngle ;
         if (da < 0.0) da = -da ;
         if (da > 2*tol) mask += 4 ;
       } else {
         strcpy(pcad->vals, "OPEN") ;
       }
       strcpy(pcad->valh, pcad->h) ;
      }
      if (moveLower) {
       if (((lowAngle > -tol) && (lowAngle < tol)) || 
           ((lowAngle > 22.5 - tol) && (lowAngle < 22.5 + tol)) ||
           ((lowAngle > 45.0 - tol) && (lowAngle < 45.0 + tol)) ||
           ((lowAngle > 67.5 - tol) && (lowAngle < 67.5 + tol)) ||
           ((lowAngle > 90.0 - tol) && (lowAngle < 90.0 + tol)) ||
           ((lowAngle > 135.0 - tol) && (lowAngle < 135.0 + tol))) {
         strcpy(pcad->valt, "CLOSED") ;
         da = prevLowAngle - lowAngle ;
         if (da < 0.0) da = -da ;
         if (da > 2*tol) mask += 8 ;
       } else {
         strcpy(pcad->valt, "OPEN") ;
       }
       strcpy(pcad->valj, pcad->j) ;
      }

      *(long *)pcad->valq = mask ;
      prevUpAngle = upAngle ;
      prevMidAngle = midAngle ;
      prevLowAngle = lowAngle ;
    
      break;

   default:

      break;
   }
   return(status);
}

long tcsGpInitplateAngleCAD (struct cadRecord *pcad)
{

/* Simple set the switch outputs to OPEN */
   strcpy(pcad->valr, "OPEN") ;
   strcpy(pcad->vals, "OPEN") ;
   strcpy(pcad->valt, "OPEN") ;

   return 0 ;

}

/*+
 *   Function name:
 *   tcsGpplateMoveCAD
 *
 *   Purpose:
 *   Implements a simulation of the GPOL plateBeam and platePark commands
 *
 *   Description:
 *   Each input plate name is checked to see if it has been set or not.
 *   If it is set then a flag is also set to indicate that when the command
 *   is started the park or beam  switch for that plate should be opened. 
 *   For this simulation we don't care what the actual plate name is, any
 *   non empty string will do.
 *
 *   Invocation:
 *   tcsGpplateMoveCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsGpplateMoveCAD (struct cadRecord *pcad)
{
   int status;                /* return status */
   char command[29];          /* command name */
   int i, j;                  /* loop counters */

   long upPlateFlag  ;
   long midPlateFlag ;
   long lowPlateFlag ;

/* Extract the command name from the record name (whatever comes after the
   last colon) */
   for ( i = 0, j = 0; i < 29; i++, j++ )
   {
      command[j] = pcad->name[i];
      if ( !(pcad->name[i]) ) break;
      if ( command[j] == ':' ) j = -1;
   }

/* Whatever the directive, accept it */
   status = CAD_ACCEPT ;

   switch(pcad->dir)
   {
   case menuDirectiveSTART:

/* Check whether the input plate names are set  */
     if(tcsDcNotEmpty(pcad->e))
        upPlateFlag  = 1 ;
     else
        upPlateFlag = 0 ;
     if(tcsDcNotEmpty(pcad->f)) 
        midPlateFlag = 1 ;
     else
        midPlateFlag = 0 ;
     if(tcsDcNotEmpty(pcad->g))
        lowPlateFlag = 1 ;
     else
        lowPlateFlag = 0 ;

   /* write output message (n.b. no more that 28 characters) */
      printf("GPOLsim: %s started\n", command);

   /* Output the flags */
      *(long *)pcad->vala = upPlateFlag ;
      *(long *)pcad->valb = midPlateFlag ;
      *(long *)pcad->valc = lowPlateFlag ;

      break;

   default:

      break;
   }
   return(status);
}

/*+
 *   Function name:
 *   tcsGpplateSeqCAD
 *
 *   Purpose:
 *   Implements a simulation of the GPOL seq command
 *
 *   Description:
 *   The seq command in GPOL is layered on top of the standard CAD commands
 *   that were delivered with the original instrument. Its purpose was to
 *   overcome some of the limitations of GPOL and in particular allow 
 *   the plate carriages to be driven in and out and the plates set to a 
 *   specific angle with a single command. In the real GPOL, the seq command
 *   is mostly implemented with a state sequence program. For this simulation
 *   we just use drive the standard CAD records.
 *
 *   Invocation:
 *   tcsGpplateSeqCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Epics inputs:
 *   a -> Upper carriage position ("PARKED" | "INBEAM") 
 *   b -> Upper plate angle (degs) 
 *   c -> Middle carriage position ("PARKED" | "INBEAM") 
 *   d -> Middle plate angle (degs) 
 *   e -> Lower carriage position ("PARKED" | "INBEAM") 
 *   f -> Lower plate angle (degs) 
 *   g -> Name of upper plate
 *   h -> Name of middle plate
 *   i -> Name of lower plate
 *
 *   Epics outputs:
 *   vala -> Upper late name
 *   valb -> Upper plate demand (degs)
 *   valc -> Middle plate name
 *   vald -> Middle plate demand (degs)
 *   vale -> Lower plate name
 *   valf -> Lower plate demand (degs)
 *   valg -> Upper plate name
 *   valh -> Middle plate name
 *   vali -> Lower plate name
 *   valj -> Upper plate name
 *   valk -> Middle plate name
 *   vall -> Lower plate name
 *   valq -> Mask to process output links
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsGpplateSeqCAD (struct cadRecord *pcad)
{
   int status;                /* return status */

   static int issuePlateAngle ;  /* Issue the plateAngle command */ 
   static int issuePlateBeam ; 
   static int issuePlatePark ;
   static int upperPark ;
   static int middlePark ;
   static int lowerPark;
   static int upperBeam ;
   static int middleBeam ;
   static int lowerBeam ;
   static char *posnOpts[] = {"PARKED", "INBEAM", NULL} ;

   long mask ;                /* Mask for triggering links */
   int posn ;

   status = CAD_ACCEPT ;
   tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);


   switch(pcad->dir)
   {
   case menuDirectivePRESET:

     status = CAD_REJECT ;

/* Initialise the flags to issue commands */
     issuePlateAngle = 0 ;
     issuePlateBeam = 0 ;
     issuePlatePark = 0;
     upperPark      = 0;
     middlePark     = 0;
     lowerPark      = 0;

/* Check if we must issue the plateAngle command */
     if (tcsDcNotEmpty(pcad->b) || tcsDcNotEmpty(pcad->d) ||
         tcsDcNotEmpty(pcad->f)) {
      issuePlateAngle = 1 ;
     }

/* Check that the correct parameters have been set and if so whether the
*  platePark or plateBeam commands need to be issued 
*/
     if (pcad->a[0]) {
       if (tcsDcString (posnOpts, " ", pcad->a, &posn, pcad)) break ;
       if (posn == 0) {
         issuePlatePark = 1 ;
         upperPark = 1 ;
       } else {
         issuePlateBeam = 1 ;
         upperBeam = 1 ;
       }
     }
     if (pcad->c[0]) {
       if (tcsDcString (posnOpts, " ", pcad->c, &posn, pcad)) break ;
       if (posn == 0) {
         issuePlatePark = 1 ;
         middlePark = 1; 
       } else {
         issuePlateBeam = 1 ;
         middleBeam = 1 ;
       }
     }
     if (pcad->e[0]) {
       if (tcsDcString (posnOpts, " ", pcad->e, &posn, pcad)) break ;
       if (posn == 0) {
         issuePlatePark = 1 ;
         lowerPark = 1 ;
       } else {
         issuePlateBeam = 1 ;
         lowerBeam = 1;
       }
     }

     status = CAD_ACCEPT ;
     break ;

   case menuDirectiveSTART:

      mask = 0 ;

/* write output message (n.b. no more that 28 characters) */
      printf("GPOLsim: %s started\n", tcsCsCadName(pcad));

/* Output the relevant demands depending on the input demands */
      if (issuePlateAngle ) {
        strcpy(pcad->vala, pcad->g);
        strcpy(pcad->valc, pcad->h);
        strcpy(pcad->vale, pcad->i);
        strcpy(pcad->valb, pcad->b);
        strcpy(pcad->vald, pcad->d);
        strcpy(pcad->valf, pcad->f);
        mask += 1; 
      }

      if (issuePlatePark) {
        if (upperPark)
          strcpy(pcad->valg, pcad->g);
        if (middlePark)
          strcpy(pcad->valh, pcad->h);
        if (lowerPark)
          strcpy(pcad->vali, pcad->i);
        mask += 2;
      }

      if (issuePlateBeam) {
        if (upperBeam)
          strcpy(pcad->valj, pcad->g);
        if (middleBeam)
          strcpy(pcad->valk, pcad->h);
        if (lowerBeam)
          strcpy(pcad->vall, pcad->i);
        mask+= 4 ;
      }

      *(long *)pcad->valq = (long)mask ;
    
      break;

   default:

      break;
   }
   return(status);
}

/*+
 *   Function name:
 *   tcsGpGenericCAD
 *
 *   Purpose:
 *   Implement a generic command for GPOL
 *
 *   Description:
 *
 *   Invocation:
 *   tcsGpGenericCAD(pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *)  Pointer to pcad structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   Deficiencies:
 *   Only responds to the START directive
 *
 *-
 */

long tcsGpGenericCAD (struct cadRecord *pcad)
{
   int status;                /* return status */
   char command[29];          /* command name */
   int i, j;                  /* loop counters */

/* Extract the command name from the record name (whatever comes after the
   last colon) */
   for ( i = 0, j = 0; i < 29; i++, j++ )
   {
      command[j] = pcad->name[i];
      if ( !(pcad->name[i]) ) break;
      if ( command[j] == ':' ) j = -1;
   }

   switch(pcad->dir)
   {
   case menuDirectiveSTART:

   /* write output message (n.b. no more that 28 characters) */
      printf("GPOLsim: %s started\n", command);
      
 /* If its a STOP command, output the following flag value (zero) */
      if (strncmp(command, "stop", 4) == 0) strcpy(pcad->vala,"Off");
      else
    /* Copy over the parameters to the output fields */
       {
       strncpy(pcad->vale, pcad->e, MAX_STRING_SIZE) ;
       strncpy(pcad->valf, pcad->f, MAX_STRING_SIZE) ;
       strncpy(pcad->valg, pcad->g, MAX_STRING_SIZE) ;
       strncpy(pcad->valh, pcad->h, MAX_STRING_SIZE) ;
       strncpy(pcad->vali, pcad->i, MAX_STRING_SIZE) ;
       strncpy(pcad->valj, pcad->j, MAX_STRING_SIZE) ;
       }
      status = CAD_ACCEPT;
      break;

   default:
      status = 0;
      break;
   }
   return(status);
}
epicsRegisterFunction(tcsGpGenericCAD);
epicsRegisterFunction(tcsGpplateMoveCAD);
epicsRegisterFunction(tcsGpplateAngleCAD);
epicsRegisterFunction(tcsGpplateSeqCAD);
epicsRegisterFunction(tcsGpInitplateAngleCAD);
