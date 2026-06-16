/*
*   FILENAME
*   tcsChopControl.c
*
*   FUNCTION NAME(S)
*   tcsCADchop       - start/stop chopping
*   tcsCADchopConfig - setup chop parameters
*   tcsCADchopRelative - setup relative chopping
*   tcsCADdtelFocus  - offset the telescope focus
*   tcsCADm2Beam     - set default beam in SCS  
*   tcsCADm2GuideConfig - implement m2GuideConfig command
*   tcsCADm2GuideReset  - reset guiding configuration
*   tcsCADm2XYOffset - offset M2 in X and Y
*   tcsCADnod - nod to specified chop state
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsChopControl.c,v $
 * Revision 1.13  2003/11/10 14:39:11  gemvx
 * Provide new M2 guide reset command
 *
 * Revision 1.12  2003/07/14 12:39:02  cjm
 * Increase chop pa limits to +/- 360
 *
 * Revision 1.11  2003/04/09 10:10:03  dlt
 * Add none to chop modes
 *
 * Revision 1.10  2001/09/28 14:16:52  cjm
 * change duty cycle lower limit to 60%
 *
 * Revision 1.9  2001/05/24 10:18:57  cjm
 * Remove subcad include and use new menuDirective constants
 *
 * Revision 1.8  2001/05/05 23:58:18  cjm
 * Include stdio.h and initialise pari
 *
 * Revision 1.7  2000/11/21 14:18:10  cjm
 * Output chop throw in arcsec and chop PA in degress rather than radians
 *
 * Revision 1.6  2000/10/24 02:40:47  cjm
 * Add option A+B to m2GuideConfig
 *
 * Revision 1.5  2000/10/11 05:30:19  cjm
 * Rework m2GuideConfig command to have easier interface
 *
 * Revision 1.4  2000/06/19 00:56:35  cjm
 * Map the name OSCIR to ICS0
 *
 * Revision 1.3  2000/03/28 04:58:55  cjm
 * Shorten output messages so that important text isn't clipped
 *
 * Revision 1.2  1999/06/16 21:27:27  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.1.1.1  1998/11/08 00:21:03  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.20  1998/07/09 08:38:34  tcs
 * Trap null input for reset option in guideConfig and default to Off
 *
 * Revision 1.19  1998/07/01 12:07:24  tcs
 * Match sync source strings in chopConfig to latest ICD
 *
 * Revision 1.18  1998/06/17 16:06:05  tcs
 * Updated guideConfig and new m2Beam commands
 *
 * Revision 1.17  1998/01/12 16:23:11  tcs
 * Change CAD subroutine names to tcsCADxxxx
 *
 * Revision 1.16  1997/12/09 08:20:44  cjm
 * Make error messages for informative
 *
 * Revision 1.15  1997/12/08 10:00:33  cjm
 * Implement m2XYOffset command
 *
 * Revision 1.14  1997/12/01 09:06:57  cjm
 * Check for correct status back from slaDftlin
 *
 * Revision 1.13  1997/11/20 12:35:40  pbt
 * Add call to tcsConfigMarkComm for *all* CADs
 *
 * Revision 1.12  1997/11/05 11:36:31  tcs
 * Implement chop relative to IPA
 *
 * Revision 1.11  1997/09/25 12:20:08  cjm
 * Set DCAD_FIELD correctly in tcsChopRelative
 *
 * Revision 1.10  1997/09/23 11:34:35  tcs
 * Remove redundant includes
 *
 * Revision 1.9  1997/09/12 12:58:17  tcs
 * Add nod weight to mount filter
 *
 * Revision 1.8  1997/09/12 10:06:43  tcs
 * add tcs prefix to all cad routines
 *
 * Revision 1.7  1997/06/11 15:14:15  tcs
 * Implement wavelength CADs
 *
 * Revision 1.6  1997/06/02 09:58:21  tcs
 * Add slew CAD
 *
 * Revision 1.5  1997/04/21 15:36:52  cjm
 * Allow string test as valid input to chopConfig
 *
 * Revision 1.4  1997/04/03 14:30:07  cjm
 * Add chopRelative and rework chopConfig
 *
 * Revision 1.3  1997/03/24 15:14:46  cjm
 * Use new limit checks for M2 demands
 *
 * Revision 1.2  1997/03/05 09:36:54  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:19  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.12  1997/01/28 10:37:58  tcs
 * Correct typo in comments
 *
 * Revision 1.11  1997/01/23 10:46:35  tcs
 * kernel support for relative chopping
 *
 * Revision 1.10  1997/01/20 09:07:09  cjm
 * Add dtelFocus command
 *
 * Revision 1.9  1997/01/13 14:28:47  cjm
 * remove redundant code for targetMFilter
 *
 * Revision 1.8  1997/01/10 15:15:19  tcs
 * Add nod command
 *
 * Revision 1.7  1996/12/13 13:24:47  tcs
 * replace tcsLibrary with tcsDecode routines
 *
 * Revision 1.6  1996/12/13 10:07:42  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.5  1996/12/12 16:56:58  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.4  1996/11/08 10:04:07  cjm
 * Update to control simulators
 *
 * Revision 1.3  1996/11/05 11:04:34  cjm
 * Add code for TCS chop command
 *
 * Revision 1.2  1996/10/24 07:06:31  cjm
 * Fill out chopConfig CAD subroutine
 *
 * Revision 1.1  1996/10/21 13:42:57  cjm
 * Initial version
 *
 *
 */
/* *INDENT-ON* */

#include <string.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <ctype.h>
#include <dbDefs.h>
#include <subRecord.h>
#include <cadRecord.h>
#include <genSubRecord.h>
#include <cad.h>
#include "slalib.h"
#include "tcsPointing.h"
#include "tcsConstants.h"
#include "tcsConfig.h"
#include "tcsInterlocks.h"
#include "tcsDecode.h"
#include "tcsOptics.h"
#include "tcsCadSupport.h"


/*+
 *   Function name:
 *   tcsCADm2Beam 
 *
 *   Purpose:
 *   Set the default beam for the SCS
 *
 *   Description:
 *   The m2Beam command sets the default beam that the SCS will follow. 
 *   The TCS continuously sends the SCS the desired positions of the 
 *   A, B and C chop states. If no chop throw has been set then these three
 *   states are all identical. Once chopping starts then M2 will switch
 *   periodically between these states. Between setting the chop throw and
 *   prior to starting to chop this command allows one to force M2 into a 
 *   particular beam. This is expected to be used during acquisition of 
 *   guide stars for both ends of the chop.
 *
 *   Invocation:
 *   tcsCADm2Beam (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Desired beam A, B or C 
 *
 *   EPICS output paramters:
 *      vala => Demand beam A, B or C 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADm2Beam (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *beamOpts[] = {"A", "B", "C", NULL} ;
  int bs ;                /* Index of selected beam */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

/* In the PRESET stage the CAD inputs must all be checked for validity. Note
*  that any vlaues derived from the inputs which are also required at the
*  menuDirectiveSTART stage must be declared static.
*/

   case menuDirectivePRESET :

   status = CAD_REJECT ;
   if (tcsDcString (beamOpts, " ", pcad->a, &bs, pcad)) break ;

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

    strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;

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
 *   tcsCADm2GuideConfig 
 *
 *   Purpose:
 *   Implements the m2GuideConfig command in the TCS
 *
 *   Description:
 *   This routine simply validates the inputs for the m2GuideConfig command
 *   and if they are acceptable, outputs them to the SCS in a format that
 *   it accepts.
 *
 *   Invocation:
 *   tcsCADm2GuideConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => guide source e.g. pwfs1, pwfs2 etc.
 *      b => source sample frequency (Hz)
 *      c => filter type e.g. raw, lowpass etc.
 *      d => filter edge freq1 (hz)
 *      e => filter edge freq2 (Hz)
 *      f => beam (None | A | B | A+B | C)
 *      g => reset guide processing On or Off
 * 
 *
 *   EPICS output parameters:
 *      vala => guide source e.g. pwfs1, pwfs2 etc.
 *      valb => source sample frequency (Hz)
 *      valc => filter type e.g. raw, lowpass etc.
 *      vald => filter edge freq1 (hz)
 *      vale => filter edge freq2 (Hz)
 *      valf => beam A weight
 *      valg => beam B weight
 *      valh => beam C weight
 *      vali => reset guide processing On or Off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcString       (tcsDecode)      Validate an input string
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *   Deficiencies:
 *   This routine currently needs to be called once for each guide source.
 *   This means multiple guide sources can't be set up in a single 
 *   configuration. However, it is likely that a much simpler command
 *   will turn out to be what observers want. Once the true requirements
 *   are specified this command will be modified. 
 *   Another shortcoming is that the ranges for checking the validities
 *   of some of the parameters are hard coded.
 *
 *-
 */

long tcsCADm2GuideConfig (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static char *sourceOpts[] = {"PWFS1", "PWFS2", "OIWFS", "GAOS", "GYRO",
                                NULL } ;
  static char *filterOpts[] = {"OFF", "RAW", "LOWPASS", "HIGHPASS", "BANDPASS",
                              "BANDSTOP", NULL} ;
  static char *beamOpts[] = {"A", "B", "A+B", "C", "NONE", NULL} ;
  static char *resetOpts[] = {"OFF", "ON", NULL} ;
  double ssfreq ;     /* Source sample frequency (Hz) */
  double freq1 ;      /* Filter edge freq1 (Hz) */
  double freq2 ;      /* Filter edge freq2 (Hz) */
  char weightA[8] ;   /* Beam A weight */
  char weightB[8] ;   /* Beam B weight */
  char weightC[8] ;   /* Beam C weight */
  int sourceIndex ;   /* Index for guide source */
  int filterIndex ;   /* Index for filter type */
  static int beamIndex ;     /* Index for beam */
  static int resetIndex ;    /* Index for reset option */

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

   if (tcsDcString (sourceOpts, "source - ", pcad->a, &sourceIndex, pcad))
        break ;

   if (tcsDcDouble ("sample freq: ", pcad->b, &ssfreq, pcad)) break ;
   if (ssfreq < 0.1 || ssfreq > 200.0 ) {
     tcsCsAppendMessage (pcad, "sample freq. out of range");
     break ;
   }

   if (tcsDcString (filterOpts, "filter - ", pcad->c, &filterIndex, pcad))
     break ;

/* Only check the filter edge parameters if the filter type is appropriate */
   if (filterIndex > 1) {

     if (tcsDcDouble ("filter edge 1: ", pcad->d, &freq1, pcad)) break ;
     if (freq1 < 0.1 || freq1 > ssfreq/2.0) {
       tcsCsAppendMessage (pcad, "lower edge freq. out of range") ;
       break ;
     }

     if (tcsDcDouble ("filter edge 2: ", pcad->e, &freq2, pcad)) break ;
     if (freq2 < freq1 || freq2 > ssfreq/2.0) {
       tcsCsAppendMessage (pcad, "upper edge freq. out of range") ;
       break ;
     }

   }

   if (tcsDcString (beamOpts, "beam - ", pcad->f, &beamIndex, pcad))
     break ;


/* If input string is null then assume that reset is Off */
   if (pcad->g[0]) {
     if (tcsDcString (resetOpts, "reset - ", pcad->g, &resetIndex, pcad))
        break ;
   } else {
     resetIndex = 0 ;
   }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

   strcpy (weightA, "-2") ;
   strcpy (weightB, "-2") ;
   strcpy (weightC, "-2") ;
   if (beamIndex == 0) {
     strcpy(weightA, "-1") ;
   } else if (beamIndex == 1) {
     strcpy(weightB, "-1") ;
   } else if (beamIndex == 2) {
     strcpy(weightA, "-1") ;
     strcpy(weightB, "-1") ;
   } else if (beamIndex == 3) {
     strcpy(weightC, "-1") ;
   }
   strncpy (pcad->vala, pcad->a, MAX_STRING_SIZE) ;
   strncpy (pcad->valb, pcad->b, MAX_STRING_SIZE) ;
   strncpy (pcad->valc, pcad->c, MAX_STRING_SIZE) ;
   strncpy (pcad->vald, pcad->d, MAX_STRING_SIZE) ;
   strncpy (pcad->vale, pcad->e, MAX_STRING_SIZE) ;
   strncpy (pcad->valf, weightA, MAX_STRING_SIZE) ;
   strncpy (pcad->valg, weightB, MAX_STRING_SIZE) ;
   strncpy (pcad->valh, weightC, MAX_STRING_SIZE) ;
   strcpy (pcad->vali, resetOpts[resetIndex]) ;
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
 *   tcsCADm2GuideReset 
 *
 *   Purpose:
 *   Resets the guide configuration set up by the m2GuideConfig command
 *
 *   Description:
 *   The functionality of this command used to be included with the 
 *   m2GuideConfig command (by setting field G of that record) In practice
 *   this caused many difficulties as when the field was set to On all other
 *   inputs were ignored. You had to therefore remember to always set it
 *   back to Off. The SCS has now been modified to move the reset into a
 *   new comamnd and so the TCS has been similarly updated. 
 *
 *   Invocation:
 *   tcsCADm2GuideReset (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS output parameters:
 *      vala => reset guide processing On 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsCsSetMessageN  (tcsCadSupport)  Set CAD MESS field to a set of strings
 *   tcsInterlocked    (tcsInterlocks)  Check if TCS is interlocked
 *   tcsConfigMarkComm (tcsConfig)      Mark record as part of a configuration
 *
 *-
 */

long tcsCADm2GuideReset (struct cadRecord *pcad)
{
  long status ;           /* Return status */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

   case menuDirectivePRESET :

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT ;

   break ;

   case menuDirectiveSTART :

   strcpy (pcad->vala, "ON") ;
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
 *   tcsCADm2XYOffset
 *
 *   Purpose:
 *   Implements the command to offset the M2 XY table by specified amounts
 *
 *   Description:
 *   The secondary mirror is mounted onto an XY table that is driven to 
 *   maintain the alignment with M1 as a function of elevation and
 *   temperature. For engineering and test purposes it may be required to
 *   offset M2 from its normal position. This command allows user
 *   defined offsets to be applied. The offsets are absolute i.e. if an
 *   offset of 0.1mm is specified and then the command is re-issued then 
 *   the offset is still 0.1mm NOT 0.2mm.
 *
 *   Invocation:
 *   tcsCADm2XYOffset (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => X offset (mm)
 *      b => Y offset (mm) 
 *
 *   EPICS output paramters:
 *      vala => X offset (mm)
 *      valb => Y offset (mm) 
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
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   The limits to the sizes of the X and Y offsets are hard coded as
 *   the maximum expected range of X and Y travel. 
 *
 *-
 */

long tcsCADm2XYOffset (struct cadRecord *pcad)

{

  long status ;               /* Return status */
  static double xoff, yoff ;  /* X,Y offsets in mm */

/* Check for any interlocks */

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
  
/* Set message prefix */

  tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

  status = CAD_ACCEPT ;

  switch (pcad->dir) 
  {

/* In the PRESET stage the CAD inputs must all be checked for validity. Note
*  that any vlaues derived from the inputs which are also required at the
*  menuDirectiveSTART stage must be declared static.
*/

   case menuDirectivePRESET :

     status = CAD_REJECT;

     if (tcsDcDouble ("X offset: ", pcad->a, &xoff, pcad))
        break ;

     if (xoff < -M2XLIMIT || xoff > M2XLIMIT) {
       tcsCsAppendMessage(pcad, "X out of range") ;
       break ;
     }
       
     if (tcsDcDouble ("Y offset: ", pcad->b, &yoff, pcad))
        break ;

     if (yoff < -M2YLIMIT || yoff > M2YLIMIT) {
       tcsCsAppendMessage(pcad, " Y out of range") ;
       break ;
     }

   status = tcsConfigMarkComm (pcad->name, pcad->mess) ;
   if (status)
     status = CAD_REJECT ;
   else
     status = CAD_ACCEPT;

   break ;

   case menuDirectiveSTART :

     tcsOpticsSetM2XYOff(xoff, yoff) ;
     strncpy(pcad->vala, pcad->a, MAX_STRING_SIZE);
     strncpy(pcad->valb, pcad->b, MAX_STRING_SIZE);

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
 *   tcsCADchop
 *
 *   Purpose:
 *   Start and stop chopping
 *
 *   Description:
 *   Setting up a chop is a two stage process. Firstly the chop parameters
 *   must be specified either by explicitly giving the source A, B and C
 *   targets or implicitly by specifying a chop throw and position angle.
 *   Chopping is then stopped and started with the chop command. This
 *   routine handles the user input to that command. The command does
 *   more than just stop and start chopping it also gives control of
 *   M2's Digital Error Correction System (DECS). It is expected that
 *   only the first two parameters of this command are likely to be used
 *   by an observer. The third, fourth and fifth parameters will be
 *   used for engineering control.
 *
 *   Invocation:
 *   tcsCADchop (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input fields :
 *
 *   a => Chop control (On | Off)
 *   b => DECS control (On | Off)
 *   c => DECS freeze  (On | Off)
 *   d => DECS pause   (On | Off)
 *   e => DECS reset   (On | Off)
 *
 *   EPICS output fields :
 *
 *   vala => Chop control "On" or "Off"
 *   valb => DECS control "On" or "Off"
 *   valc => DECS freeze  "On" or "Off"
 *   vald => DECS pause   "On" or "Off"
 *   vale => DECS reset   "On" or "Off"
 *   valf => Chop control 1 = On, 0 = Off
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcOnOff     (tcsDecode)        Check for On or Off
 *   strcat         (ansiString)       Concatenate one string and another
 *   strcpy         (ansiString)       Copy one string to another
 *
 *   Prior requirements:
 *   A chop throw should have been set up before telling the SCS to begin
 *   chopping.
 *
 *-
 */

long tcsCADchop (struct cadRecord *pcad)

{

   long status ;           /* Return status */
   static int chopControl ;    /* 1 = On , 0 = Off */
   static int decsControl ;    /* 1 = On, 0 = Off */
   static int decsFreeze ;     /* 1 = On, 0 = Off */
   static int decsPause ;      /* 1 = On, 0 = Off */
   static int decsReset ;      /* 1 = On, 0 = Off */

/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;
   
/* Copy the name of the CAD record to the message field */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL) ;

   status = CAD_ACCEPT ;
   switch (pcad->dir) 
   {

      case menuDirectivePRESET :
      status = CAD_REJECT ;

/* Decode each input field. In all cases the strings On or Off are the 
*  only valid input. The strings can be upper or lower case 
*/

/* chop control */

      if (tcsDcOnOff ("control: ", pcad->a, &chopControl, pcad)) break ;

/* DECS control */

      if (tcsDcOnOff ("DECS control: ", pcad->b, &decsControl, pcad)) break ;

/* DECS freeze */

      if (tcsDcOnOff ("DECS freeze: ", pcad->c, &decsFreeze, pcad)) break ;

/* DECS Pause */

      if (tcsDcOnOff ("DECS pause: ", pcad->d, &decsPause, pcad)) break ;

/* DECS Reset */

      if (tcsDcOnOff ("DECS reset: ", pcad->e, &decsReset, pcad)) break ;

      if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT ;
      break ;

   case menuDirectiveSTART :

/* Copy validated data to the output links */

      strcpy(pcad->vala, chopControl ? "On" : "Off") ;    /*   chopControl  */
      strcpy(pcad->valb, decsControl ? "On" : "Off") ;    /*   decsControl  */
      strcpy(pcad->valc, decsFreeze ? "On" : "Off") ;     /*   decsFreeze   */
      strcpy(pcad->vald, decsPause ? "On" : "Off") ;      /*   decsPause    */
      strcpy(pcad->vale, decsReset ? "On" : "Off") ;      /*   decsReset    */ 
      *(long *)pcad->valf = chopControl ;

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
 *   tcsCADchopConfig
 *
 *   Purpose:
 *   Set up the chop configuration
 *
 *   Description:
 *   The purpose of this record is to set up the chop configuration of M2.
 *   Character string input is converted to upper case and, where
 *   appropriate, only the first character checked for validity.
 *
 *   Invocation:
 *   tcsCADchopConfig (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input fields:
 *  
 *   a => 2posn, 3posn, triangular or none
 *   b => synchronisation source 
 *   c => chop frequency (Hz)
 *   d => Duty cycle  
 *
 *   EPICS output fields :
 *
 *   vala => chop mode (string)
 *   valb => sync source (string) 
 *   valc => chop frequency (Hz) 
 *   vald => duty cycle (percentage) 
 *   vale => chop mode (integer) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   slaDfltin      (slalib)           String to double conversion
 *
 *   Deficiencies:
 *   At present the checking of the synchronisation source only uses 
 *   generic names source1, source2 etc. Once they are known the 
 *   true names will need to be coded in.
 *-
 */

long tcsCADchopConfig (struct cadRecord *pcad)

{

   long status ;           /* Return status */
   double lMaxChopThrow ;   /* Maximum allowable chop throw (arcsec) */
   double lMinChopFreq ;    /* Minimum chop frequency */
   double lMaxChopFreq ;    /* Maximum chop frequency */
   int nptr ;               /* Pointer for decoding input strings */
   int decodeStatus ;       /* decode status from slalib calls */
   static struct DCAD_FIELD inputChopFreq ;   /* Input chop frequency (Hz) */
   static struct ICAD_FIELD inputChopMode ;   /* Chop type as an integer */
   char st1[16];            /* holds formatted number for messages */
   char st2[16];            /* holds formatted number for messages */
   static char syncSource[16]; /* synchronisation source */
   static double dutyCycle; /* Duty cycle as a percentage */
   char *modes[] =   {      /* String representation of chop modes */
      "2POSN", "3POSN", "TRIANGULAR", "NONE", NULL
   };                       /* WARNING. Do not change the value of NONE without
                               changing tcsCadChopConfig.sch */
   static char *ssOpts[] = { /* Sync sources */
      "SCS","ICS0","ICS1","ICS2","ICS3","ICS4", "TEST", "OSCIR", NULL
   };
   int ssIndex = 0;
   int modeIndex = 0;
 
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

/* Copy the name of the CAD record to the message field */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL) ;

   status = CAD_ACCEPT;
   switch (pcad->dir) 
   {

   case menuDirectivePRESET :
      status = CAD_REJECT ;

/* Get the current chop frequency limits */
      tcsOpticsGetChopLimits (&lMaxChopThrow, &lMinChopFreq, &lMaxChopFreq ) ;
     
/* decode and check requested chop mode. A similar approach is taken as for 
 * chop type. See above.  */

      if (pcad->a[0]) {
         if (tcsDcString (modes, "chop modes ", pcad->a, &modeIndex, pcad))
            break;
      }
      inputChopMode.val= modeIndex ;
      strcpy (inputChopMode.instring, modes[modeIndex]) ;
      inputChopMode.field = 'A' ;

/* Only check the remaining parameters if the mode is not "none". */
      if ( modeIndex != 3 ) {

/* Check that synchronisation source is valid */
/* Note that a present the string "TEST" is also accepted. This is purely
*  to check error handling in the subsystem simulator i.e. TEST will be
*  passed to the subsystem and should be rejected.
*/

        if (pcad->b[0]) {
          if (tcsDcString (ssOpts, "sync. source ", pcad->b, &ssIndex, pcad))
            break ;
/* Map real instrument names to names that SCS understands */
          if (ssIndex == 7) ssIndex = 1; 
          strcpy (syncSource, ssOpts[ssIndex]) ;
        }


/* Decode and check requested chop frequency */

        nptr = 1 ;
        slaDfltin (pcad->c, &nptr,  &inputChopFreq.val, &decodeStatus ) ;
        if (decodeStatus > 0) {
           tcsCsAppendMessage (pcad, "chop frequency invalid or null") ;
           break ;
        } else if ((inputChopFreq.val < lMinChopFreq) ||
           (inputChopFreq.val > lMaxChopFreq)) {
           sprintf( st1, "%.3g", lMinChopFreq);
           sprintf( st2, "%.3g", lMaxChopFreq);
           tcsCsAppendMessageN (pcad, "freq. exceeds ", st1," to ", st2, 
              (char*)NULL) ;
           break ;
        }
        inputChopFreq.field = 'C' ;
  
/* Decode and check requested duty cycle parameter */

        nptr = 1;
        slaDfltin (pcad->d, &nptr, &dutyCycle, &decodeStatus);
        if (decodeStatus > 0) {
          tcsCsAppendMessage (pcad, "Duty cycle invalid or null");
          break ;
        } else if (dutyCycle < 60.0 || dutyCycle > 95.0) {
          tcsCsAppendMessage (pcad, "Duty cycle 65 to 95%");
          break;
        } 
      }

/* Tag this command and if successful store data in the TCB */

      if (tcsConfigMarkComm (pcad->name, pcad->mess)) break;

      tcsConfigSetChopParams (&inputChopFreq, &inputChopMode); 

      status = CAD_ACCEPT;

      break ;

   case menuDirectiveSTART :

/* Copy data to the output links */

      
      strcpy (pcad->vala, modes[inputChopMode.val]) ;
      strcpy (pcad->valb, syncSource);
      *(double *)pcad->valc = inputChopFreq.val;
      *(double *)pcad->vald = dutyCycle;
      *(long *)pcad->vale = inputChopMode.val ;

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
 *   tcsCADchopRelative
 *
 *   Purpose:
 *   Set up the relative chop parameters 
 *
 *   Description:
 *   Chopping can either be set up as relative or absolute. Relative
 *   chopping is where the user specifies the throw and position angle etc.
 *   rather than explicitly giving the coordinates of the end points of
 *   the throw. This routine checks that the user specified parameters
 *   are acceptable before passing them on to the kernel for execution.
 *   The chop throw is the total throw from state A to state B in the 
 *   case of two position chopping and from state B to state C in the case
 *   of three position chopping. The throw is also given in arcsec on the sky
 *   i.e. user units. M2 will be tilted about a factor of four more due
 *   to the magnification.
 *
 *   Invocation:
 *   tcsCADchopRelative (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS Input fields:
 *  
 *   a => chop throw (arcsec)
 *   b => Position angle (degs)
 *   c => Frame
 *   d => Equinox
 *
 *   EPICS output fields :
 *
 *   vala => chop throw (arcsec)
 *   valb => chop position angle (degs)
 *   valc => chop frame
 *   vald => chop equinox
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   slaDfltin      (slalib)           String to double conversion
 *
 *-
 */

long tcsCADchopRelative (struct cadRecord *pcad)

{

   long status ;               /* Return status */
   double lMaxChopThrow ;      /* Maximum allowable chop throw (arcsec) */
   double lMinChopFreq ;       /* Minimum chop frequency */
   double lMaxChopFreq ;       /* Maximum chop frequency */
   int nptr ;                  /* Pointer for decoding input strings */
   int decodeStatus ;          /* decode status from slalib calls */
   static struct DCAD_FIELD inputChopThrow ;  /* Input chop throw (rads) */
   static struct DCAD_FIELD inputChopPA ;     /* Input chop PA (rads) */
   static struct FRAMECAD_FIELD inputChopFrame ;  /* Input chop frame */
   static struct EPOCHCAD_FIELD inputChopEquinox ;  /* Input chop equinox */
   static double chopThrow ;   /* Chop throw (arcsec) */
   static double chopPA ;      /* Chop position angle (degs) */
   int pari ;                  /* pos angle relative to instrument */
   char st1[16];               /* holds formatted number for messages */
   char us[MAX_STRING_SIZE] ;  /* Uppercase version of string */
 
/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked (pcad->mess)) return CAD_REJECT;

/* Copy the name of the CAD record to the message field */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL) ;

   status = CAD_ACCEPT;
   switch (pcad->dir) 
   {

   case menuDirectivePRESET :
      status = CAD_REJECT ;

/* Get the current chop limits */
      tcsOpticsGetChopLimits (&lMaxChopThrow, &lMinChopFreq, &lMaxChopFreq ) ;
     
/* Decode and check input chop throw (arcsec on sky) */
      nptr = 1 ;
      slaDfltin (pcad->a, &nptr, &chopThrow, &decodeStatus) ;
      if (decodeStatus > 0) {
         tcsCsAppendMessage (pcad, "chop throw invalid or null") ;
         break ;
      } else if ((chopThrow < 0.0) ||
            (inputChopThrow.val > lMaxChopThrow)) {
         sprintf( st1, "%.4g", lMaxChopThrow);
         tcsCsAppendMessageN (pcad, "throw outside 0 to ", st1, 
            (char*)NULL) ;
         break ;
      } 
      inputChopThrow.val = chopThrow * AS2R ;
      inputChopThrow.field = 'A' ;

/* Decode and check requested chop position angle */

      nptr = 1 ;
      slaDfltin (pcad->b, &nptr, &chopPA, &decodeStatus) ;
      if (decodeStatus > 0) {
         tcsCsAppendMessage (pcad, "PA invalid or null") ;
         break ;
      } else if ((chopPA < -360.0) || (chopPA > 360.0)) {
         tcsCsAppendMessage (pcad, "PA range -180 to +180") ;
         break ;
      }
      inputChopPA.val = chopPA * D2R ;
      inputChopPA.field = 'B' ;

/* tracking frame and equinox */
      pari = 0 ;
      if ( pcad->c[ 0 ] ) {

/* test for the string "instrument" which means that the angle is relative
   to the IPA */
         tcsDcUc(pcad->c, sizeof us, us);
         if ( !strcmp( us, "INSTRUMENT") ) {
            pari = 1;
            inputChopFrame.val = FK5; 
            inputChopEquinox.val.year = 0.0; 
            inputChopEquinox.val.type = ' ';
         } else {
            if (tcsDcFrame("", pcad->c, &inputChopFrame.val, pcad)) break;
            if (inputChopFrame.val == FK4 || inputChopFrame.val == FK5) {
               if ( pcad->d[ 0 ] ) {
                  if (tcsDcEpoch("", pcad->d, &inputChopEquinox.val.type, 
                     &inputChopEquinox.val.year, pcad)) break;
               } else {
                  if (inputChopFrame.val == FK5) {
                     inputChopEquinox.val.type = 'J';
                     inputChopEquinox.val.year = 2000.0;
                  } else if (inputChopFrame.val == FK4) {
                     inputChopEquinox.val.type = 'B';
                     inputChopEquinox.val.year = 1950.0;
                  }
               }
            } else {
               inputChopEquinox.val.year = 0.0; 
               inputChopEquinox.val.type = ' ';
            }
         }

      } else {  /* frame is blank */

         if ( pcad->d[ 0] ) {
            if (tcsDcEpoch("", pcad->d, &inputChopEquinox.val.type, 
               &inputChopEquinox.val.year, pcad)) break;
            inputChopFrame.val = inputChopEquinox.val.type == 
               'B' ? FK4 : FK5;
   
         } else {    /* equinox is blank too */

            inputChopFrame.val = FK5;         /* default to FK5 */
            inputChopEquinox.val.year = 2000.0;
            inputChopEquinox.val.type = 'J';

         } 
      }
      inputChopFrame.field = 'C' ;
      inputChopEquinox.field = 'D' ;

/* Tag this command and if successful store data in the TCB */

      if (tcsConfigMarkComm (pcad->name, pcad->mess)) break;

      tcsConfigSetRelChopParams (1, &inputChopThrow, 
         &inputChopPA, &inputChopFrame, &inputChopEquinox, pari) ;
      status = CAD_ACCEPT;

      break ;

   case menuDirectiveSTART :

/* Copy data to the output links */

      *(double *)pcad->vala = chopThrow;
      *(double *)pcad->valb = chopPA ;
      strcpy (pcad->valc, tcsCsFrame(inputChopFrame.val)) ;
      sprintf(pcad->vald, "%c%.14f", inputChopEquinox.val.type,
         inputChopEquinox.val.year);

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
 *   tcsCADdtelFocus
 *
 *   Purpose:
 *   Implements the dtelFocus command to offset the telescope focus
 *
 *   Description:
 *   This routine checks the user input for validity and then sends the 
 *   data to the optics model to allow such things as the new effective 
 *   focal length to be calculated.
 *
 *   Invocation:
 *   tcsCADdtelFocus (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => User focus offset (mm) 
 *      b => Instrument focus offset (mm)
 * 
 *   EPICS output paramters:
 *      vala => User focus offset (mm) 
 *
 *   Function value:
 *   (<)  status  (long) Return status, 0 = OK
 * 
 *   External functions:
 *   tcsDcDouble          (tcsDecode)   Decode a double precision number
 *   tcsOpticsSetM2DzUser (tcsOptics)   Set user focus offset
 *   tcsOpticsGetTiltLimits (tcsOptics) Fetch tilt and focus limits 
 *
 *   Deficiencies:
 *   Currently the current focus position isn't
 *   available to this routine. It is not possible at the PRESET stage
 *   to check that the user request will lead to a valid demand.
 *
 *-
 */

long tcsCADdtelFocus (struct cadRecord *pcad)

{

   long status ;                    /* Return status */
   static double dzUser;            /* User requested offset */
   static double dzInst;            /* Instrument requested offset */
   static double dzTotal;           /* Total requested offset */
   double maxZ;                     /* Current z limit (mm) */
   double maxTilt;                  /* Current tilt limit (arcsec) */
   char str1[16];                   /* formatted string for number */

/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Copy the name of the CAD record to the message field */

   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL) ;

   status = CAD_ACCEPT ;
   switch (pcad->dir) 
   {

      case menuDirectivePRESET :
      status = CAD_REJECT;

      if (tcsDcDouble ("", pcad->a, &dzUser, pcad)) break;
      if (tcsDcDouble ("", pcad->b, &dzInst, pcad)) break;

      dzTotal = dzUser + dzInst;
      printf("dzUser = %d\n",dzUser);
      printf("dzInst = %d\n",dzInst);
      printf("dzTotal = %d\n",dzTotal);

/* Fetch the current z limits. At present the current z position is 
 * not available and so the offset is simply checked against the 
 * maximum permissible offset.
*/

     tcsOpticsGetTiltLimits (&maxTilt, &maxZ);

     if (dzTotal > maxZ || dzTotal < -maxZ)
     {
      sprintf (str1, "%.2g", maxZ);
      tcsCsAppendMessageN (pcad, "Z demand exceeds +/- ", str1, (char*)NULL);
      break;
     }

/* If the data is validated then mark this command as part of a configuration.
*/
      if (tcsConfigMarkComm (pcad->name, pcad->mess)) break;

      status = CAD_ACCEPT;

      break ;

   case menuDirectiveSTART :

/* Copy validated data to the output links and set the offset for the 
*  optics model
*/

      tcsOpticsSetM2DzUser (dzTotal);
      *(double *)pcad->vala = dzTotal;
      *(double *)pcad->valb = dzInst;

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
 *   tcsCADnod
 *
 *   Purpose:
 *   CAD routine for controlling nodding
 *
 *   Description:
 *   This routine is attached to the Nod CAD record. It sets the current
 *   nod state of the kernel
 *
 *   Invocation:
 *   tcsCADnod (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input fields :
 *
 *   a => Nod state: the chop for which the "star" is the target. The
 *        star is assumed to be the target originally specified for
 *        source A.
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
 *   Prior requirements:
 *   Operations that must be performed before calling this function
 *
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

long tcsCADnod (struct cadRecord *pcad)

{

   long status ;           /* Return status */
   int c;                  /* Nod state in ASCII */
   static int nod;         /* Nod state as integer */
   int i;                  /* Loop counter */
   char states[] = "ABC";  /* Allowed nod states */

/* Check for any interlocks */

   if (pcad->dir != menuDirectiveCLEAR)
      if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Copy the name of the CAD record to the message field */
   tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL) ;

   status = CAD_ACCEPT ;
   switch (pcad->dir) 
   {

      case menuDirectivePRESET :
         status = CAD_REJECT ;

         c = toupper( (int) *pcad->a );
         for ( nod = -1, i = 0; states[i]; i++ ) {
            if ( c == states[i] ) nod = i;
         }
         if ( nod == -1 ) {
            tcsCsAppendMessageN (pcad, "state must be one of A, B or C",
               (char*)NULL) ;
            break;
         }

         if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

         status = CAD_ACCEPT ;
         break ;

      case menuDirectiveSTART :

/* Call kernel nod routine */
         tcsNod( nod );

/* Copy data to the output links */
         ((char*)pcad->vala)[0] =  states[nod]; 
         ((char*)pcad->vala)[1] =  '\0'; 

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
epicsRegisterFunction(tcsCADm2GuideReset);
epicsRegisterFunction(tcsCADchopConfig);
epicsRegisterFunction(tcsCADchop);
epicsRegisterFunction(tcsCADdtelFocus);
epicsRegisterFunction(tcsCADchopRelative);
epicsRegisterFunction(tcsCADm2GuideConfig);
epicsRegisterFunction(tcsCADm2Beam);
epicsRegisterFunction(tcsCADnod);
epicsRegisterFunction(tcsCADm2XYOffset);
