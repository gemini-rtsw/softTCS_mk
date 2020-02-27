/*
*   FILENAME
*   tcsCombine.c
*
*   This module holds the routines that are used in combining
*    the subsystem CAR status values and messages
*
*   FUNCTION NAME(S)
*   tcsCarMessCombine - Combine the subsystem CAR error messages
*   tcsCarValCombine  - Combine the subsystem CAR status values
*   tcsCheckAOConfig  - check and set AO configuration health
*   tcsCheckTrack     - Test that all subsystem trackID values are equal 
*                       to kernel value
*   tcsCheckTrack1    - handles extra inputs from tcsCheckTrack
*   tcsCombIntHealth  - form overall TCS internal health value
*   tcsCombineMess    - combine messages ensuring a default is always given
*   tcsCombineMessSoftC - generate softC error message string
*   tcsCombineSoftC   - generate softC value from CAR record inputs
*   tcsHealthCombine  - form overall health value
*   tcsHealthCombine1 - form overall health value
*   tcsHealthIndex    - convert health string to index for edm
*   tcsStateIndex     - convert state string to an index
*   tcsSubcadVal      - Check for non-zero value from subsystem CADS
*   tcsErrorVal       - Output combined error status for top-level error
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsCombine.c,v $
 * Revision 1.21  2010/06/15 10:16:20  cjm
 * Added tcsCarMessCombine & tcsSubcadVal inputs. Corrected tcsCombineMess inputs.
 *
 * Revision 1.20  2010/04/12 12:37:20  cjm
 * Add tcsStateIndex to convert strings to indices
 *
 * Revision 1.19  2007/12/18 10:25:16  cjm
 * Upgrade to handle inputs from AOM and GSAOI
 *
 * Revision 1.18  2006/11/24 10:17:51  cjm
 * New routine tcsCheckAOConfig and improved health reporting
 *
 * Revision 1.17  2005/10/21 15:36:44  cjm
 * Include ephemeris health
 *
 * Revision 1.16  2005/05/09 00:59:27  gemvx
 * In checkTrack allow over ride of track ids
 *
 * Revision 1.15  2004/07/12 10:40:32  cjm
 * Make combination of AO status dependent on AO fold position
 *
 * Revision 1.14  2004/05/25 13:42:42  cjm
 * Re-enable CAR combine and copy through health message
 *
 * Revision 1.13  2004/05/06 16:03:43  cjm
 * Combine all CAR records
 *
 * Revision 1.12  2003/12/23 13:30:26  cjm
 * Once again comment out the combining of busy/idle
 *
 * Revision 1.11  2003/11/10 14:36:53  gemvx
 * Combine mount, rotator and A&G busy/idle
 *
 * Revision 1.10  2003/10/17 16:36:43  gemvx
 * Combine mount and cass rotator CAR status
 *
 * Revision 1.9  2003/07/25 09:29:07  cjm
 * Pull in p1, p2 and oi trackids in checkTrack
 *
 * Revision 1.8  2002/04/16 15:55:27  cjm
 * Add GPOL inputs to combinations
 *
 * Revision 1.7  2002/02/22 17:56:11  cjm
 * New routine to combine internal health and rework tcsHealthCombine
 *
 * Revision 1.6  2001/09/25 16:33:47  ptaylor
 * Modify tcsHealthCombine tcsCarMessCombine tcsCarValCombine: extra inputs
 *
 * Revision 1.5  2001/05/24 10:21:04  cjm
 * Use new menuCarState constants
 *
 * Revision 1.4  1999/07/10 03:54:04  cjm
 * *** empty log message ***
 *
 * Revision 1.3  1999/06/16 21:27:28  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.2  1999/01/24 01:46:14  cjm
 * Put out a default message if a subsystem reports an ERR status but doesn't supply a message of its own
 *
 * Revision 1.1.1.1  1998/11/08 00:21:03  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.8  1998/11/07 23:31:53  tcs
 * Add routines to generate softC from CAR inputs
 *
 * Revision 1.7  1998/04/07 20:47:00  cjm
 * BUSY state should over ride ERR not vice versa
 *
 * Revision 1.6  1998/02/16 09:48:57  tcs
 * Revised applyC logic
 *
 * Revision 1.5  1998/02/12 16:31:30  pbt
 * Take in whether subsystems are following when combining trackIDs
 *
 * Revision 1.4  1998/01/21 17:26:39  pbt
 * Error state always overrides other states for combined values
 *
 * Revision 1.3  1997/09/17 09:48:33  pbt
 * Change status value for when trackIDs are the same: 1 -> 0
 *
 * Revision 1.2  1997/08/21 10:40:55  tcs
 * Treat apply values > 0 as OK
 *
 * Revision 1.1  1997/07/09 13:43:41  pbt
 * Renamed tcsCarCombine, added health combine routine
 *
 * Revision 1.3  1997/04/23 15:47:20  pbt
 * Removed printf statements
 *
 * Revision 1.2  1997/04/23 10:49:35  pbt
 * Added routines for status & error message combining and handling
 *
 * Revision 1.1  1997/02/10 17:10:16  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.4  1997/02/10 14:45:20  pbt
 * Suppress error message for discrepant trackIDs at startup
 *
 * Revision 1.3  1997/01/14 17:39:07  pbt
 * Added function tcsCheckTrack to compare subsystem/kernel trackIDs
 *
 * Revision 1.2  1997/01/10 14:30:37  pbt
 * New routines/sequence program to combine CAR values into softC record
 *
 * Revision 1.1  1996/12/03 12:33:05  pbt
 * Routines to implement combination rules for multiple CAR value/message input
 *
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <math.h>

#include <dbDefs.h>
#include <dbCommon.h>
#include <recSup.h>
#include <genSubRecord.h>
#include <menuCarstates.h>
#include <tcsPointing.h>

#include "tcsProbeLib.h"
#include "tcsDecode.h"

#define TINY 1e-6

/*+
 *   Function name:
 *   tcsCarMessCombine
 *
 *   Purpose:
 *   Combines multiple input CAR message values and outputs a
 *   single message
 *
 *   Description:
 *   The routine is called by the genSub record CarMessCombine which
 *   takes in all the subsystem CAR message values via input links.
 *   The first non-null message encountered (if any) is output.
 *
 *   Inputs :
 *
 *   a..l => Input CAR messages from subsystem activeC CAR records.
 *           (j input is omitted as it triggers record)
 *
 *   Outputs :
 * 
 *   vala => Single message output to TCS:activeC top-level CAR record
 *
 *   Invocation:
 *   tcsCarMessCombine(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsCarMessCombine (struct genSubRecord *pgsub) 

{
    char instring[MAX_STRING_SIZE] ;

    strncpy(instring, (char *)pgsub->a, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->b, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->c, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->d, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->e, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->f, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->g, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->h, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->i, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->k, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
    strncpy(instring, (char *)pgsub->l, MAX_STRING_SIZE) ;
    instring[MAX_STRING_SIZE-1] = '\0';
    if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
      {
      strcpy((char *)pgsub->vala, instring) ;
      return 0;
      }
      
/* Default : just output null */
    strcpy((char *)pgsub->vala, "") ;
    return 0 ;  

}

/*+
 *   Function name:
 *   tcsCombineMess
 *
 *   Purpose:
 *   Combine multiple input CAR message values 
 *   and output a single message
 *
 *   Description:
 *   The routine is called by the genSub record CarMessCombine which
 *   takes in all the subsystem CAR message values via input links.
 *   An index is used to indicate which if any of the input links should
 *   have a message. If a message was expected but not found a default
 *   message is output.
 *
 *   Epics Inputs :
 *
 *   a    => Message from MCS activeC record
 *   b    => Message from SCS activeC record
 *   c    => Message from PCS activeC record
 *   d    => Message from CRCS activeC record
 *   e    => Message from ECS activeC record
 *   f    => Message from GAOS (Altair) activeC record
 *   g    => Message from A&G activeC record
 *   h    => Message from WS activeC record
 *   i    => Message from GPOL activeC record
 *   j    => Message from TCS softC internal CAR record
 *   k    => Message from AOM (Canopus) activeC record
 *   l    => Message from GSAOI activeC record
 *   m    => Index of subsystem that is in error
 *
 *   Outputs :
 * 
 *   vala => Single message output to TCS:activeC top-level CAR record
 *
 *   Invocation:
 *   tcsCombineMess(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsCombineMess (struct genSubRecord *pgsub) 

{
    char instring[MAX_STRING_SIZE] ;
    long subsysIndex ;

    subsysIndex = *(long *)pgsub->m ;

    if (subsysIndex == 1) {
      strncpy(instring, (char *)pgsub->a, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from Mount") ; 
      return 0;
    }
    if (subsysIndex == 2) {
      strncpy(instring, (char *)pgsub->b, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from M2") ; 
      return 0;
    }
    if (subsysIndex == 3) {
      strncpy(instring, (char *)pgsub->c, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from M1") ; 
      return 0;
    }
    if (subsysIndex == 4) {
      strncpy(instring, (char *)pgsub->d, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from Rotator") ; 
      return 0;
    }
    if (subsysIndex == 5) {
      strncpy(instring, (char *)pgsub->e, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from Enclosure") ; 
      return 0;
    }
    if (subsysIndex == 6) {
      strncpy(instring, (char *)pgsub->f, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from GAOS") ; 
      return 0;
    }
    if (subsysIndex == 7) {
      strncpy(instring, (char *)pgsub->g, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from A&G") ; 
      return 0;
    }
    if (subsysIndex == 8) {
      strncpy(instring, (char *)pgsub->h, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from weather server") ; 
      return 0;
    }
    if (subsysIndex == 9) {
      strncpy(instring, (char *)pgsub->i, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from GPOL") ; 
      return 0;
    }
    if (subsysIndex == 10) {
      strncpy(instring, (char *)pgsub->j, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified internal error from TCS") ; 
      return 0;
    }
    if (subsysIndex == 11) {
      strncpy(instring, (char *)pgsub->k, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from AOM") ; 
      return 0;
    }
    if (subsysIndex == 12) {
      strncpy(instring, (char *)pgsub->l, MAX_STRING_SIZE) ;
      instring[MAX_STRING_SIZE-1] = '\0';
      if ( (strlen(instring) != 0) && (strspn(instring," ") != strlen(instring)) )
        strcpy((char *)pgsub->vala, instring) ;
      else
        strcpy((char *)pgsub->vala, "Unspecified error from GSAOI") ; 
      return 0;
    }

/* Default : just output null */
    strcpy((char *)pgsub->vala, "") ;
    return 0 ;  

}


/*+
 *   Function name:
 *   tcsCombineMessSoftC
 *
 *   Purpose:
 *   Generate error message for softC when its value is menuCarstatesERROR
 *
 *   Description:
 *   This routine is triggerred if the computed softC value is 
 *   menuCarstatesERROR. It accesses the index to the relevant input link and
 *   then outputs that message string.
 *
 *   Invocation:
 *   tcsCombineMessSoftC (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub   (struct genSubRecord *) Pointer to gensub structure
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *
 *   Deficiencies:
 *   Ideally this code would be part of tcsCombineSoftC but at the moment 
 *   a gensub record can handle 20 inputs and there are 11 input CARs
 *   with a value and message each.
 *
 *-
 */

long tcsCombineMessSoftC (struct genSubRecord *pgsub) 
{

  long index ;           /* Index to error message */
  int i ;                /* Loop index */
  void **vptr ;

/* Fetch index and increment pointer to point at relevant error message */

  vptr = &pgsub->a ;
  index = *(long *)pgsub->t ;

  for (i = 0 ; i < index ; i++ ) {
    vptr++ ;
  }

  strncpy (pgsub->vala, (char *)(*vptr), MAX_STRING_SIZE ) ;
  
  return 0 ;
}

/*+
 *   Function name:
 *   tcsCombineSoftC
 *
 *   Purpose:
 *   Generate a value for softC from the input CAR record values
 *
 *   Description:
 *   Each CAR input is read. If any input is BUSY then the output is BUSY.
 *   If there are no BUSY inputs but there is at least one ERR input then
 *   the output is ERR. If all inputs are IDLE then the output is IDLE.
 *   Since a CAR record can't be set directly from IDLE to ERR, a flag
 *   is set if the current value of softC is IDLE and the new computed
 *   value is ERR. This flag is read by down stream processing so that
 *   a transition to BUSY is generated before the transition to ERR. In
 *   theory such a transition should never be generated but errors or
 *   bugs elsewhere might cause it. The index number of the first ERR
 *   status found is also output so that the correct error message
 *   can be identified later.
 *   N.B. at the moment a value can potentially be written to field U if
 *   a command were given to the weather server. At the moment however
 *   there are no such commands.
 *
 *   Invocation:
 *   tcsCombineSoftC (pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub    (struct genSubRecord *)  Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => value of xconfigC
 *   b => value of aoCommSentC
 *   c => value of agCommSentC
 *   d => value of crCommSentC
 *   e => value of ecCommSentC
 *   f => value of m1CommSentC
 *   g => value of m2CommSentC
 *   h => value of mcCommSentC
 *   i => value of kernelC
 *   j => value of loadC
 *   k => value of saveC
 *   l => value of gpCommSentC
 *   m => value of aomCommSentC
 *   n => value of gsaoiCommsentC
 *   t => current value of softC
 *
 *   Epics outputs:
 *
 *   vala => Flag 0/1 to trigger BUSY transition prior to ERR
 *   valb => Link select value 0/1/2
 *   valc => index of first input ERR value
 *   vald => computed softc value
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

#define NOCARINPUTS 14

long tcsCombineSoftC (struct genSubRecord *pgsub) 
{

int carBusy  ;             /* True if any input is BUSY */
int carError ;             /* True if any input is ERR */
void **vptr ;        
int i ;                    /* Index */


/* Initialise variables */

 carBusy = FALSE ;
 carError = FALSE ;
 vptr = &pgsub->a ;

/* Check for any BUSY inputs. */

 for (i = 0; i < NOCARINPUTS ; i++, vptr++ ) {
   if (*(long *)(*vptr) == menuCarstatesBUSY) {
     carBusy = TRUE ;
     break ;
   }
 }

/* If none are BUSY, check for any ERR inputs */

 if (!carBusy) {
   vptr = &pgsub->a ;
   for (i=0 ; i < NOCARINPUTS ; i++, vptr++ ) { 
     if (*(long*)(*vptr) == menuCarstatesERROR) {
       carError = TRUE ;
       break ;
     }
   }
 }

/* Set output values */

 if (carBusy) {
   *(long *)pgsub->vala = 0 ;
   *(long *)pgsub->valb = 2 ;
   *(long *)pgsub->valc = 0 ;
   *(long *)pgsub->vald = menuCarstatesBUSY ;
 } else if (carError) {
   if (*(long *)pgsub->t == menuCarstatesIDLE) 
     *(long *)pgsub->vala = 1 ;
   else
     *(long *)pgsub->vala = 0 ;
   *(long *)pgsub->valb = 3 ;
   *(long *)pgsub->valc = i ;
   *(long *)pgsub->vald = menuCarstatesERROR ;
 } else {
   *(long *)pgsub->vala = 0 ;
   *(long *)pgsub->valb = 1 ;
   *(long *)pgsub->valc = 0 ;
   *(long *)pgsub->vald = menuCarstatesIDLE ;
 } 

 return 0 ;

}


/*+
 *   Function name:
 *   tcsCombIntHealth
 *
 *   Purpose:
 *   Combines multiple health values and messages 
 *
 *   Description:
 *   Compare the input health values and then output the worst plus any
 *   health message 
 *
 *   Inputs :
 *
 *   a => Time health value
 *   b => Time health message
 *   c => Temperature monitoring health value
 *   d => Temperature monitoring health message 
 *   e => Ephemeris health value
 *   f => Ephemeris health message
 *   g => AO configuration health value
 *   h => AO configuration health message
 *
 *   Outputs :
 * 
 *   vala => Single combined health value
 *   valb => Health message
 *   valc => Combined health index
 *   vald => Time health index 
 *   vale => Temperature monitoring health index
 *   valf => Ephemeris monitoring health index
 *   valg => AO configuration monitoring health index
 *
 *   Invocation:
 *   tcsCombIntHealth(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *-
 */

long tcsCombIntHealth (struct genSubRecord *pgsub) 

{
   char outhealth[8] ;
   char mess[MAX_STRING_SIZE] ;
   long outHealthIndex ;
   long timeHealthIndex ;
   long sensorHealthIndex ;
   long ephemHealthIndex ;
   long aoConfigHealthIndex ;

   strcpy(outhealth,"GOOD");  /* Health is initially GOOD */
   strcpy(mess, " ") ;
   outHealthIndex = 0 ;
   timeHealthIndex = 0;
   sensorHealthIndex = 0;
   ephemHealthIndex = 0;
   aoConfigHealthIndex = 0;

   if (!strncmp((char *)pgsub->a,"GOOD",4) && 
       !strncmp((char *)pgsub->c,"GOOD",4) &&
       !strncmp((char *)pgsub->e,"GOOD",4) &&
       !strncmp((char *)pgsub->g,"GOOD",4)) {
/* Nothing to do */
   } else {
     if (!strncmp((char *)pgsub->a,"WARNING",7) || 
         !strncmp((char *)pgsub->c,"WARNING",7) ||
         !strncmp((char *)pgsub->e,"WARNING",7) ||
         !strncmp((char *)pgsub->g,"WARNING",7)) {
        strcpy(outhealth, "WARNING");
        outHealthIndex = 1 ;
        if (!strncmp((char *)pgsub->a,"WARNING",7)) {
          timeHealthIndex = 1 ;
          strcpy(mess, (char *)pgsub->b) ;
        } 
        if (!strncmp((char *)pgsub->c, "WARNING", 7)) {
          strcpy(mess, (char *)pgsub->d) ;
          sensorHealthIndex = 1 ;
        } 
        if (!strncmp((char *)pgsub->e, "WARNING", 7)) {
          strcpy(mess, (char *)pgsub->f) ;
          ephemHealthIndex = 1 ;
        }
        if (!strncmp((char *)pgsub->g, "WARNING", 7)) {
          strcpy(mess, (char *)pgsub->h) ;
          aoConfigHealthIndex = 1 ;
        }
     }
 
     if (!strncmp((char *)pgsub->a,"BAD",3) || 
         !strncmp((char *)pgsub->c,"BAD",3) ||
         !strncmp((char *)pgsub->e,"BAD",3) ||
         !strncmp((char *)pgsub->g,"BAD",3)) {
        strcpy(outhealth, "BAD");
        outHealthIndex = 2;
        if (!strncmp((char *)pgsub->a,"BAD",3)) {
          timeHealthIndex = 2 ;
          strcpy(mess, (char *)pgsub->b) ;
        } 
        if (!strncmp((char *)pgsub->c, "BAD",3)) {
          strcpy(mess, (char *)pgsub->d) ;
          sensorHealthIndex = 2 ;
        } 
        if (!strncmp((char *)pgsub->e, "BAD",3)) {
          strcpy(mess, (char *)pgsub->f) ;
          ephemHealthIndex = 2 ;
        }
        if (!strncmp((char *)pgsub->g, "BAD",3)) {
          strcpy(mess, (char *)pgsub->h) ;
          aoConfigHealthIndex = 2 ;
        }
     }
   }

   strcpy((char *)pgsub->valb, outhealth); 
   strcpy((char *)pgsub->vala, mess) ;
   *(long *)pgsub->valc = outHealthIndex ;
   *(long *)pgsub->vald = timeHealthIndex ;
   *(long *)pgsub->vale = sensorHealthIndex ;
   *(long *)pgsub->valf = ephemHealthIndex ;
   *(long *)pgsub->valg = aoConfigHealthIndex ;

   return 0;

}

/*+
 *   Function name:
 *   tcsHealthCombine
 *
 *   Purpose:
 *   Combines multiple health status string and outputs a
 *   single value
 *
 *   Description:
 *   The routine is called by the genSub record tcsHealthCombine which
 *   takes in all the subsystem health values via input links.
 *   The worst health status is output on VALA
 *
 *   Inputs :
 *
 *   a => A&G health value
 *   b => A&G health message
 *   c => CRCS health value
 *   d => CRCS health message
 *   e => ECS health value
 *   f => ECS health message
 *   g => Weather server health value
 *   h => Weather server health message 
 *   i => SCS health value
 *   j => SCS health message 
 *   k => MCS health value
 *   l => MCS health message 
 *   m => AO health value
 *   n => AO health message 
 *   o => M1 health value
 *   p => M1 health message 
 *   q => GPOL health value
 *   r => GPOL health message 
 *   s => AOM internal health value
 *   t => AOM internal health message
 *
 *   Outputs :
 * 
 *   vala => Single combined health value output for TCS:health top-level record
 *   valb => Health message
 *
 *   Invocation:
 *   tcsHealthCombine(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsHealthCombine (struct genSubRecord *pgsub) 

{
   char outhealth[8] ;
   char mess[MAX_STRING_SIZE] ;
   int aoConfig ;
   char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

   strcpy(outhealth,"BAD");  /* Health is initially BAD */
   strcpy(mess, " ") ;

   aoConfig = tcsProbeGetAOConfig();


   if (!strncmp((char *)pgsub->a,"GOOD",4) && 
       !strncmp((char *)pgsub->c,"GOOD",4) &&
       !strncmp((char *)pgsub->e,"GOOD",4) && 
       !strncmp((char *)pgsub->g,"GOOD",4) &&
       !strncmp((char *)pgsub->i,"GOOD",4) && 
       !strncmp((char *)pgsub->k,"GOOD",4) &&
       (!aoConfig || !strncmp((char *)pgsub->m,"GOOD",4)) &&
       !strncmp((char *)pgsub->o,"GOOD",4) &&
       !strncmp((char *)pgsub->q,"GOOD",4) && 
       (!aoConfig || !strncmp((char *)pgsub->s,"GOOD",4))) {
      strcpy(outhealth, "GOOD");
   } else {
     if (!strncmp((char *)pgsub->a,"WARNING",7) || 
         !strncmp((char *)pgsub->c,"WARNING",7) ||
         !strncmp((char *)pgsub->e,"WARNING",7) || 
         !strncmp((char *)pgsub->g,"WARNING",7) ||
         !strncmp((char *)pgsub->i,"WARNING",7) || 
         !strncmp((char *)pgsub->k,"WARNING",7) ||
         (!strncmp((char *)pgsub->m,"WARNING",7) && aoConfig) ||
         !strncmp((char *)pgsub->o,"WARNING",7) ||
         !strncmp((char *)pgsub->q,"WARNING",7) || 
         (!strncmp((char *)pgsub->s,"WARNING",7) && aoConfig)) {
        strcpy(outhealth, "WARNING");

/* The order of checking below will output the first subsystem in the list */
        if (!strncmp((char *)pgsub->a,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->b) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor A&G health");
          }
        } else if (!strncmp((char *)pgsub->c,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->d) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor CR health");
          }
        } else if (!strncmp((char *)pgsub->e,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->f) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor ECS health");
          }
        } else if (!strncmp((char *)pgsub->g,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->h) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor WS health");
          }
        } else if (!strncmp((char *)pgsub->i,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->j) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor M2 health");
          }
        } else if (!strncmp((char *)pgsub->k,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->l) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor MCS health");
          }
        } else if ((!strncmp((char *)pgsub->m,"WARNING",7) && aoConfig)) {
          strcpy(mess, (char *)pgsub->n) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor AO health");
          }
        } else if (!strncmp((char *)pgsub->o,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->p) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor M1 health");
          }
        } else if (!strncmp((char *)pgsub->q,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->r) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor GPOL health");
          }
        } else if (!strncmp((char *)pgsub->s,"WARNING",7) && aoConfig) {
          strcpy(mess, (char *)pgsub->t) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor AOM health");
          }
        }
     } 
     if (!strncmp((char *)pgsub->a,"BAD",3) || 
         !strncmp((char *)pgsub->c,"BAD",3) ||
         !strncmp((char *)pgsub->e,"BAD",3) || 
         !strncmp((char *)pgsub->g,"BAD",3) ||
         !strncmp((char *)pgsub->i,"BAD",3) || 
         !strncmp((char *)pgsub->k,"BAD",3) ||
         (!strncmp((char *)pgsub->m,"BAD",3) && aoConfig) ||
         !strncmp((char *)pgsub->o,"BAD",3) ||
         !strncmp((char *)pgsub->q,"BAD",3) || 
         (!strncmp((char *)pgsub->s,"BAD",3) && aoConfig)) {
        strcpy(outhealth, "BAD");
        if (!strncmp((char *)pgsub->a,"BAD",3)) {
          strcpy(mess, (char *)pgsub->b) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad A&G health");
          }
        } else if (!strncmp((char *)pgsub->c,"BAD",3)) {
          strcpy(mess, (char *)pgsub->d) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad CR health");
          }
        } else if (!strncmp((char *)pgsub->e,"BAD",3)) {
          strcpy(mess, (char *)pgsub->f) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad ECS health");
          }
        } else if (!strncmp((char *)pgsub->g,"BAD",3)) {
          strcpy(mess, (char *)pgsub->h) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad WS health");
          }
        } else if (!strncmp((char *)pgsub->i,"BAD",3)) {
          strcpy(mess, (char *)pgsub->j) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad M2 health");
          }
        } else if (!strncmp((char *)pgsub->k,"BAD",3)) {
          strcpy(mess, (char *)pgsub->l) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad MCS health");
          }
        } else if ((!strncmp((char *)pgsub->m,"BAD",3) && aoConfig )) {
          strcpy(mess, (char *)pgsub->n) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad AO health");
          }
        } else if (!strncmp((char *)pgsub->o,"BAD",3)) {
          strcpy(mess, (char *)pgsub->p) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad M1 health");
          }
        } else if (!strncmp((char *)pgsub->q,"BAD",3)) {
          strcpy(mess, (char *)pgsub->r) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad GPOL health");
          }
        } else if (!strncmp((char *)pgsub->s,"BAD",3) && aoConfig) {
          strcpy(mess, (char *)pgsub->t) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for bad AOM health");
          }
        }
     }

   }
   strcpy((char *)pgsub->vala, outhealth); 
   strcpy((char *)pgsub->valb, mess) ;

   return 0;

}

/*+
 *   Function name:
 *   tcsHealthCombine1
 *
 *   Purpose:
 *   Combines multiple health status string and outputs a
 *   single value
 *
 *   Description:
 *   This routine is a companion to tcsHealthCombine. It only exists
 *   because there were too many inputs for a single gensub and so the
 *   health calculation had to be split into two.
 *
 *   Inputs :
 *
 *   a => Combined health value from tcsHealthCombine 
 *   b => Combined health message from tcsHealthCombine
 *   c => TCS internal health value
 *   d => TCS internal health message
 *   e => GSAOI health value
 *   f => GSAOI health message
 *
 *   Outputs :
 * 
 *   vala => Single combined health value output for TCS:health top-level record
 *   valb => Health message
 *
 *   Invocation:
 *   tcsHealthCombine1(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsHealthCombine1 (struct genSubRecord *pgsub) 

{
   char outhealth[8] ;
   char mess[MAX_STRING_SIZE] ;
   char alpha[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int aoConfig ;

   strcpy(outhealth,"BAD");  /* Health is initially BAD */
   strcpy(mess, " ") ;

   aoConfig = tcsProbeGetAOConfig();

   if (!strncmp((char *)pgsub->a,"GOOD",4) && 
       !strncmp((char *)pgsub->c,"GOOD",4) &&
       !strncmp((char *)pgsub->e,"GOOD",4))  {
      strcpy(outhealth, "GOOD");
   } else {
     if (!strncmp((char *)pgsub->a,"WARNING",7) || 
         !strncmp((char *)pgsub->c,"WARNING",7) || 
         !strncmp((char *)pgsub->e,"WARNING",7)) {
       strcpy(outhealth, "WARNING");

/* The order of checking below will output the first subsystem in the list */
        if (!strncmp((char *)pgsub->a,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->b) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor health");
          }
        } else if (!strncmp((char *)pgsub->c,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->d) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor TCS health");
          }
        } else if (!strncmp((char *)pgsub->e,"WARNING",7)) {
          strcpy(mess, (char *)pgsub->f) ;
          if (!strpbrk(mess, alpha)) {
            strcpy(mess, "No reason given for poor GSAOI health");
          }
        }
     } 
     if (!strncmp((char *)pgsub->a,"BAD",3) || 
         !strncmp((char *)pgsub->c,"BAD",3) || 
         !strncmp((char *)pgsub->e,"BAD",3)) {
       strcpy(outhealth, "BAD");
       if (!strncmp((char *)pgsub->a,"BAD",3)) {
         strcpy(mess, (char *)pgsub->b) ;
         if (!strpbrk(mess, alpha)) {
           strcpy(mess, "No reason given for bad health");
         }
       } else if (!strncmp((char *)pgsub->c,"BAD",3)) {
         strcpy(mess, (char *)pgsub->d) ;
         if (!strpbrk(mess, alpha)) {
           strcpy(mess, "No reason given for bad TCS health");
         }
       } else if (!strncmp((char *)pgsub->e,"BAD",3)) {
         strcpy(mess, (char *)pgsub->f) ;
         if (!strpbrk(mess, alpha)) {
           strcpy(mess, "No reason given for bad GSAOI health");
         }
       }
     }
   }
   strcpy((char *)pgsub->vala, outhealth); 
   strcpy((char *)pgsub->valb, mess) ;

   return 0;

}

/*+
 *   Function name:
 *   tcsHealthIndex
 *
 *   Purpose:
 *   Convert health string to index
 *
 *   Description:
 *   This routine converts the valid health strings to an index. This
 *   was found to be necessary when some screens were converted to edm
 *   as the color rules must be evaluated based on records that 
 *   return numbers.
 *
 *   Inputs :
 *
 *   a => Health string (GOOD, WARNING or BAD) 
 *
 *   Outputs :
 * 
 *   vala => Health index (0, 1 or 2)
 *
 *   Invocation:
 *   tcsHealthIndex(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsHealthIndex (struct genSubRecord *pgsub) 

{
   long healthVal = 2 ;

   if (!strncmp((char *)pgsub->a, "GOOD", 4)) {
     healthVal = 0 ;
   } else if (!strncmp ((char *)pgsub->a, "WARNING", 7)) {
     healthVal = 1 ;
   }

   *(long *)pgsub->vala = healthVal ;
     
   return 0;

}

/*+
 *   Function name:
 *   tcsStateIndex
 *
 *   Purpose:
 *   Convert state string to index
 *
 *   Description:
 *   This routine converts the valid stste strings to an index. This
 *   was needed for GSAOI which provided its state as a string e.g.
 *   "BOOTING", "INITIALISING" etc. rather than a number as did 
 *   other systems. Note that the TCS does not recognize the 
 *   state "CONFIGURING" and so maps this to "RUNNING". 
 *
 *   Inputs :
 *
 *   a => State string (BOOTING, INIIALISING, RUNNING or CONFIGURING) 
 *
 *   Outputs :
 * 
 *   vala => State index (0, 1 or 2)
 *
 *   Invocation:
 *   tcsStateIndex(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *-
 */

long tcsStateIndex (struct genSubRecord *pgsub) 

{
   long StateVal = 0 ;
   char ucState[MAX_STRING_SIZE];

   tcsDcUc((char *)pgsub->a, 20, ucState);

   if (!strncmp(ucState, "BOOTING", 7)) {
     StateVal = 0 ;
   } else if (!strncmp (ucState, "INITIALISING", 12)) {
     StateVal = 1 ;
   } else if (!strncmp (ucState, "RUNNING", 7)) {
     StateVal = 2 ;
   } else if (!strncmp (ucState, "CONFIGURING", 11)) {
     StateVal = 2 ;
   }

   *(long *)pgsub->vala = StateVal ;
     
   return 0;

}

/*+
 *   Function name:
 *   tcsCarValCombine
 *
 *   Purpose:
 *   Combines multiple input CAR status values and outputs a
 *   single value
 *
 *   Description:
 *   The routine is called by the genSub record CarValCombine which
 *   takes in all the subsystem CAR message values via input links.
 *   Any BUSY value sets output to BUSY. If the output is menuCarstatesERROR
 *   then an index is also output to identify which subsystem was in error
 *
 *   Epics Inputs :
 *
 *      a => CAR status from Mount
 *      b => CAR status from M2
 *      c => CAR status from M1
 *      d => CAR status from CRCS
 *      e => CAR status from ECS
 *      f => CAR status from AO
 *      g => CAR status from A&G
 *      h => CAR status from WS
 *      i => CAR status from GPOL
 *      j => CAR status from softC
 *      k => CAR status from AOM
 *      l => CAR status from GSAOI
 *      m => (Type long) Input value from checking of subsystem trackIDs. 
 *           ( = 0 if all subsystem trackID's are equal to TCS value) *
 *
 *   Epics Outputs :
 * 
 *   vala => Single status value output to TCS:activeC top-level CAR record
 *   valb => index of subsystem that is in error
 *
 *   Invocation:
 *   tcsCarValCombine(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsCarValCombine (struct genSubRecord *pgsub) 

{
    long   subsysIndex ;
    double outval ;   /* Output CAR status value */
    static int trackErrcount = 0; /* Maintain record of trackid discrepancy */
    static int trackHadBusy = 0;  /* TRUE only after the first BUSY state has occurred */
    int aoConfig ;

/* Default output value is IDLE */
    outval = menuCarstatesIDLE ;

/* First check for any BUSY subsystems. Note that if the AO system is
*  not configured then we don't use the AO status in the calculation of
*  the overall status
*/
    aoConfig = tcsProbeGetAOConfig();
    if ( *(double *)pgsub->a == menuCarstatesBUSY 
         || *(double *)pgsub->b == menuCarstatesBUSY
         || *(double *)pgsub->c == menuCarstatesBUSY 
         || *(double *)pgsub->d == menuCarstatesBUSY
         || *(double *)pgsub->e == menuCarstatesBUSY 
         || (*(double *)pgsub->f == menuCarstatesBUSY && aoConfig)
         || *(double *)pgsub->g == menuCarstatesBUSY 
         || *(double *)pgsub->h == menuCarstatesBUSY
         || *(double *)pgsub->i == menuCarstatesBUSY 
         || *(double *)pgsub->j == menuCarstatesBUSY
         || (*(double *)pgsub->k == menuCarstatesBUSY && aoConfig)
         || (*(double *)pgsub->l == menuCarstatesBUSY && aoConfig))
    {
        outval = menuCarstatesBUSY;
        trackHadBusy = 1;
        trackErrcount = 0;

    } else if ( *(double *)pgsub->a == menuCarstatesERROR 
         || *(double *)pgsub->b == menuCarstatesERROR
         || *(double *)pgsub->c == menuCarstatesERROR 
         || *(double *)pgsub->d == menuCarstatesERROR
         || *(double *)pgsub->e == menuCarstatesERROR 
         || (*(double *)pgsub->f == menuCarstatesERROR && aoConfig)
         || *(double *)pgsub->g == menuCarstatesERROR 
         || *(double *)pgsub->h == menuCarstatesERROR
         || *(double *)pgsub->i == menuCarstatesERROR 
         || *(double *)pgsub->j == menuCarstatesERROR
         || (*(double *)pgsub->k == menuCarstatesERROR && aoConfig)
         || (*(double *)pgsub->l == menuCarstatesERROR && aoConfig)) {
      outval = menuCarstatesERROR;
     }

/* And override the value if the trackIDs are not equal to the TCS */
   if ( (*(long *)pgsub->m != 0) ) 
   {
      trackErrcount++;
/* Error message if 20 consecutive discrepancies (to avoid spurious error
*  on transient condition) and have had at least one BUSY state 
*  i.e. this is not simply a startup discrepancy due to delayed subsystem 
*  startup 
*/
      if (trackHadBusy == 1 && trackErrcount == 20)
         printf("Error - discrepancy in subsystem TrackIDs\n");
      outval = menuCarstatesBUSY;
   }

   subsysIndex = 0 ;
   if (outval == menuCarstatesERROR) {
     if (*(double *)pgsub->a == menuCarstatesERROR)
       subsysIndex = 1 ;
     else if (*(double *)pgsub->b == menuCarstatesERROR)
       subsysIndex = 2 ;
     else if (*(double *)pgsub->c == menuCarstatesERROR)
       subsysIndex = 3 ;
     else if (*(double *)pgsub->d == menuCarstatesERROR)
       subsysIndex = 4 ;
     else if (*(double *)pgsub->e == menuCarstatesERROR)
       subsysIndex = 5 ;
     else if ((*(double *)pgsub->f == menuCarstatesERROR && aoConfig))
       subsysIndex = 6 ;
     else if (*(double *)pgsub->g == menuCarstatesERROR)
       subsysIndex = 7 ;
     else if (*(double *)pgsub->h == menuCarstatesERROR)
       subsysIndex = 8 ;
     else if (*(double *)pgsub->i == menuCarstatesERROR)
       subsysIndex = 9 ;
     else if (*(double *)pgsub->j == menuCarstatesERROR)
       subsysIndex = 10 ; 
     else if (*(double *)pgsub->k == menuCarstatesERROR)
       subsysIndex = 11 ;   
     else if (*(double *)pgsub->l == menuCarstatesERROR)
       subsysIndex = 12 ;   }

/* Output the values */
   *(double *)pgsub->vala = outval ;
   *(long *)pgsub->valb = subsysIndex ;

   return 0;

}

/*+
 *   Function name:
 *   tcsCheckAOConfig
 *
 *   Purpose:
 *   Check consistency of AO configuration
 *
 *   Description:
 *   This routine checks the consistency of the AO configuration 
 *   currently set in the TCS. If the user has configured the TCS for
 *   AO use but the AO fold is not deployed then the TCS health is set
 *   to warning. Similarly if the fold is deployed but the TCS is not
 *   configured for AO use then again the TCS health is set to warning.
 *   Note that there is always the possibility that the TCS health
 *   may flash to warning briefly when changing AO configurations.
 *   This is because the configureForAO command is an "immediate"
 *   command and thus is always triggerred before the command to move
 *   the AO fold if they are in the same configuration.
 *
 *   Epics outputs
 *   vala => Health value "GOOD", "WARNING" or "BAD"
 *   valb => Health message 
 *
 *   Invocation:
 *   tcsCheckAOConfig(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   External functions:
 *   tcsProbeGetAOConfig  (tcsProbeLib)   Get user set AO configuration
 *   tcsProbeGetAOFold    (tcsProbeLib)   Get state of AO fold
 *
 *-
 */
/* *INDENT-ON* */

long tcsCheckAOConfig (struct genSubRecord *pgsub)

{
   char health[8] ;
   char mess[MAX_STRING_SIZE];
   int aoConfig ;
   int aoFold ;

   strcpy(health, "GOOD");
   strcpy(mess, "");

   aoConfig = tcsProbeGetAOConfig();
   aoFold   = tcsProbeGetAoFold();

   if (aoFold == 1 && !aoConfig) {
     strcpy(health, "WARNING");
     strcpy(mess, "AO Fold in but not configured for AO");
   }

   if (aoFold == 0 && aoConfig) {
     strcpy(health, "WARNING");
     strcpy(mess, "Configured for AO but AO fold is out");
   }

   if (aoFold > 2 && aoConfig) {
     strcpy(health, "WARNING");
     strcpy(mess, "AO Configured but fold status unknown");
   }

   strcpy(pgsub->vala, health);
   strcpy(pgsub->valb, mess);
   return 0;

}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCheckTrack
 *
 *   Purpose:
 *   Combines multiple input subsystem trackIDs and outputs a
 *   single value : TRUE if all input values are equal to
 *   the TCS kernel trackID value.
 *
 *   Description:
 *   The routine is called by the genSub record checkTrack which
 *   takes in all the subsystem trackID values via input links.
 *   ALternate links take in the follow status (1 = TRUE)
 *   Any zero value is ignored. The TCS kernel value is obtained
 *   using tcsGetTrackid and the output value is TRUE if all input
 *   values are equal to the TCS kernel value. Those subsystems
 *   that are not Following have their trackIDs ignored
 *   It is possible to ignore all the subsystem trackids by 
 *   inputting a 1 to pgsub->s . This can be used to prevent the
 *   TCS state staying permanently BUSY if a subsystem does not
 *   handle the trackid correctly.
 *
 *   Inputs :
 *
 *   a,c,e,g,i,k,m,o,q => (Type double) Input subsystem trackIDs
 *   b,d,f,h,j,l,n,p,r => (Type long) Input Follow status, 1 = TRUE
 *   s => Disable/Enable flag
 *
 *   Output :
 * 
 *   vala => (Type long) Single status value. 
 *                 0 => All subsystem trackIDs are equal to TCS kernel value
 *                 1 => Some subsystem trackIDs are not equal to TCS kernel value
 *
 *   Invocation:
 *   tcsCheckTrack(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   External functions:
 *   tcsGetTrackid      Get the value of the TCS kernel trackID.
 *
 *-
 */
/* *INDENT-ON* */

long tcsCheckTrack (struct genSubRecord *pgsub)

{
   double tcsTrackid ;            /* TCS kernel trackID */
   long outval;                   /* Output value */
   double invala, invalc, invale, invalg, invali, invalk, invalm,
          invalo, invalq ; 
   long invalb, invald, invalf, invalh, invalj, invall, invaln, 
        invalp, invalr ; 

   outval = 1;                    /* Default output value */

/* Get current TCS kernel trackID value */
   tcsGetTrackid(&tcsTrackid);

/* Get all 18 input values */
   invala = *(double *)pgsub->a;
   invalb = *(long *)pgsub->b;
   invalc = *(double *)pgsub->c;
   invald = *(long *)pgsub->d;
   invale = *(double *)pgsub->e;
   invalf = *(long *)pgsub->f;
   invalg = *(double *)pgsub->g;
   invalh = *(long *)pgsub->h;
   invali = *(double *)pgsub->i;
   invalj = *(long *)pgsub->j;
   invalk = *(double *)pgsub->k;
   invall = *(long *)pgsub->l;
   invalm = *(double *)pgsub->m;
   invaln = *(long *)pgsub->n;
   invalo = *(double *)pgsub->o;
   invalp = *(long *)pgsub->p;
   invalq = *(double *)pgsub->q;
   invalr = *(long *)pgsub->r;


/* If all input trackIDs are zero, ignore it and return */
   if ((invala < TINY) && (invalc < TINY) && (invale < TINY) && (invalg < TINY)
        && (invali < TINY) && (invalk < TINY) && (invalm < TINY)
        && (invalo < TINY) && (invalq < TINY) ) {
      *(long *)pgsub->vala = outval;
      return 0;
    }

/* Each zero input or where subsystem is not following,
   ignore by setting value to TCS kernel value */
   if (invala < TINY || invalb == 0) invala = tcsTrackid;
   if (invalc < TINY || invald == 0) invalc = tcsTrackid;
   if (invale < TINY || invalf == 0) invale = tcsTrackid;
   if (invalg < TINY || invalh == 0) invalg = tcsTrackid;
   if (invali < TINY || invalj == 0) invali = tcsTrackid;
   if (invalk < TINY || invall == 0) invalk = tcsTrackid;
   if (invalm < TINY || invaln == 0) invalm = tcsTrackid;
   if (invalo < TINY || invalp == 0) invalo = tcsTrackid;
   if (invalq < TINY || invalr == 0) invalq = tcsTrackid;

/* If all input trackIDs are the same as kernel trackID, output 0 */
   if ((fabs(invala - tcsTrackid) < TINY) && (fabs(invalc - tcsTrackid) < TINY)
     && (fabs(invale - tcsTrackid) < TINY) && (fabs(invalg - tcsTrackid) < TINY)
     && (fabs(invali - tcsTrackid) < TINY) && (fabs(invalk - tcsTrackid) < TINY)
     && (fabs(invalm - tcsTrackid) < TINY) && (fabs(invalo - tcsTrackid) < TINY)
     && (fabs(invalq - tcsTrackid) < TINY)) outval = 0;
   
/* If the over ride is set then just output a zero as if all the 
*  track ids were within range
*/
   if (*(long *)pgsub->s == 1) outval = 0;

   *(long *)pgsub->vala = outval;

   return 0;

}

/*+
 *   Function name:
 *   tcsCheckTrack1
 *
 *   Purpose:
 *   Combines multiple input subsystem trackIDs and outputs a
 *   single value : TRUE if all input values are equal to
 *   the TCS kernel trackID value.
 *
 *   Description:
 *   The routine is called by the genSub record checkTrack1 which
 *   takes in all the subsystem trackID values plus the output
 *   of checkTrack via input links.
 *   It follows the same logic as checkTrack and is only coded as a separate
 *   routine because there are insufficient links on a single gensub 
 *   to pull in all the relevant data.
 *
 *   Inputs :
 *
 *   a,c,e,g,i,k,m,o,q => (Type double) Input subsystem trackIDs
 *   b,d,f,h,j,l,n,p,r => (Type long) Input Follow status, 1 = TRUE
 *   s => Disable/Enable flag
 *   t => Output of checkTrack 
 *
 *   Output :
 * 
 *   vala => (Type long) Single status value. 
 *                 0 => All subsystem trackIDs are equal to TCS kernel value
 *                 1 => Some subsystem trackIDs not equal to TCS kernel value
 *
 *   Invocation:
 *   tcsCheckTrack1(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   External functions:
 *   tcsGetTrackid      Get the value of the TCS kernel trackID.
 *
 *-
 */
/* *INDENT-ON* */

long tcsCheckTrack1 (struct genSubRecord *pgsub)

{
   double tcsTrackid ;            /* TCS kernel trackID */
   long outval;                   /* Output value */
   long invalt;                   /* Output value of checkTrack */
   double invala, invalc, invale;
   long invalb, invald, invalf;

   outval = 1;                    /* Default output value */

/* Get current TCS kernel trackID value */
   tcsGetTrackid(&tcsTrackid);

/* Get all nput values */
   invala = *(double *)pgsub->a;
   invalb = *(long *)pgsub->b;
   invalc = *(double *)pgsub->c;
   invald = *(long *)pgsub->d;
   invale = *(double *)pgsub->e;
   invalf = *(long *)pgsub->f;
   invalt = *(long *)pgsub->t;


/* If all input trackIDs are zero, ignore them and return input from previous
 * checkTrack
 */
   if ((invala < TINY) && (invalc < TINY) && (invale < TINY) ) {
      *(long *)pgsub->vala = invalt;
      return 0;
    }

/* Each zero input or where subsystem is not following,
   ignore by setting value to TCS kernel value */
   if (invala < TINY || invalb == 0) invala = tcsTrackid;
   if (invalc < TINY || invald == 0) invalc = tcsTrackid;
   if (invale < TINY || invalf == 0) invale = tcsTrackid;

/* If all input trackIDs are the same as kernel trackID, output 0 */
   if ((fabs(invala - tcsTrackid) < TINY) && (fabs(invalc - tcsTrackid) < TINY)
     && (fabs(invale - tcsTrackid) < TINY) && invalt == 0) outval = 0;
   
/* If the over ride is set then just output a zero as if all the 
*  track ids were within range. This same over ride will have been
*  read into checkTrack
*/
   if (*(long *)pgsub->s == 1) outval = 0;

   *(long *)pgsub->vala = outval;

   return 0;

}

/*+
 *   Function name:
 *   tcsSubcadVal
 *
 *   Purpose:
 *   Combines multiple input status values and outputs a
 *   single value
 *
 *   Description:
 *   The routine is called by an EPICS gensub record which
 *   takes in status values via input links.
 *   The first non-zero input value sets the output status 1, 
 *   zero otherwise.
 *
 *   Inputs :
 *
 *   a..j => (Type double) Input subsystem CAD status values.
 *
 *   Output :
 * 
 *   vala => Single status value for output. Value output is
 *           1 for any non-zero input status, 0 otherwise
 *
 *   Invocation:
 *   tcsSubcadVal(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsSubcadVal (struct genSubRecord *pgsub) 

{

/* Check through all inputs for any non-zero status values */
    if ( (*(double *)(pgsub->a) != 0) || (*(double *)(pgsub->b) != 0) 
      || (*(double *)(pgsub->c) != 0) || (*(double *)(pgsub->d) != 0)
      || (*(double *)(pgsub->e) != 0) || (*(double *)(pgsub->f) != 0)
      || (*(double *)(pgsub->g) != 0) || (*(double *)(pgsub->h) != 0) 
      || (*(double *)(pgsub->i) != 0) || (*(double *)(pgsub->j) != 0))
      {
      *(double *)pgsub->vala = 1;
      return 0;
      }
    else
/* Default output value is 0 */
     { 
     *(double *)pgsub->vala = 0;
     return 0;
     }
}

/*+
 *   Function name:
 *   tcsErrorVal
 *
 *   Purpose:
 *   Combines multiple overall error status values and outputs a
 *   single value for the combined error
 *
 *   Description:
 *   The routine is called by an EPICS gensub record which
 *   takes in both CAD and CAR status values via input links.
 *   The first non-zero input value sets the output status 1, 
 *   zero otherwise.
 *
 *   Inputs :
 *
 *   a, c =>(Type double) Input subsystem CAD status values.
 *    b   =>(Type double) Input CAR status value
 *
 *   Output :
 * 
 *   vala => Single status value for output. Value output is
 *           1 for any error input status, 0 otherwise
 *
 *   Invocation:
 *   tcsErrorVal(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *) pointer to pgsub structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None.
 *
 *   Deficiencies
 *
 *-
 */

long tcsErrorVal (struct genSubRecord *pgsub) 

{

/* Check through CAD & CAR status inputs for any error status values */

    if ( (*(double *)(pgsub->a) == -1) || (*(double *)(pgsub->c) == -1) ||
         (*(double *)(pgsub->b) == menuCarstatesERROR) ) 
      {
      *(double *)pgsub->vala = 1;
      return 0;
      }
    else
/* Default output value is 0 */
     { 
     *(double *)pgsub->vala = 0;
     return 0;
     }
}
epicsRegisterFunction(tcsCombineMess);
epicsRegisterFunction(tcsCarMessCombine);
epicsRegisterFunction(tcsCheckAOConfig);
epicsRegisterFunction(tcsCombineSoftC);
epicsRegisterFunction(tcsHealthCombine);
epicsRegisterFunction(tcsHealthCombine1);
epicsRegisterFunction(tcsCarValCombine);
epicsRegisterFunction(tcsSubcadVal);
epicsRegisterFunction(tcsCheckTrack);
epicsRegisterFunction(tcsErrorVal);
epicsRegisterFunction(tcsCombIntHealth);
epicsRegisterFunction(tcsCombineMessSoftC);
epicsRegisterFunction(tcsHealthIndex);
epicsRegisterFunction(tcsStateIndex);
