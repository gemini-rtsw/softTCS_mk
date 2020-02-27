/*
 *   FILENAME
 *   tcsAdjustCads.c
 *
 *   FUNCTION NAME(S)
 *   tcsCADincrOffset - Increment handset offset
 *   tcsCADcollAdj  -   Adjust collimation
 *   tcsCADpoAdj -      Adjust pointing origin
 *   tcsCADtarAdj -     Adjust target
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsAdjustCads.c,v $
 * Revision 1.7  2014/10/01 16:27:38  cjm
 * Add logging of commands
 *
 * Revision 1.6  2009/11/02 16:35:23  cjm
 * Allow adjustment of generic guiders 1 to 4
 *
 * Revision 1.5  2007/12/18 10:24:03  cjm
 * Add extra cases for new guiders
 *
 * Revision 1.4  2003/05/19 12:01:33  dlt
 * Fix bug in target and pointing origin adjustment CADs
 *
 * Revision 1.3  2003/04/08 10:55:45  dlt
 * Enable simultanious adjustment of multiple virtual telesceopes
 *
 * Revision 1.2  2001/05/24 10:15:15  cjm
 * Remove subcad include and use new menuDirective constants
 *
 * Revision 1.1  2001/01/15 11:37:17  dlt
 * New handset interface
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
#include  "astLib.h"
#include  <subRecord.h>
#include  "tcsInterlocks.h"
#include  "tcsDecode.h"
#include  "tcsCadSupport.h"
#include <genSubRecord.h>
#include  "tcsOptics.h"
#include "tcsLogSupport.h"

/*+
 *   Function name:
 *   tcsCADincrOffset
 *
 *   Purpose:
 *   Increments an offset.
 *
 *   Description:
 *   The input links are read, the data validated, converted to internal
 *   representation and written to the output links. The kernel increment
 *   offset routine is then called.
 *
 *   Invocation:
 *   tcsCADincrOffset (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => RA/Az increment.
 *      b => Dec/El increment.
 *      c => virtual telescope selection
 *      d => offset type (RADEC | AZEL | TANGENT PLANE)
 *      e => offset index
 *
 *   EPICS output parameters:
 *      vala => RA/Az increment.
 *      valb => Dec/El increment.
 *      valc => virtual telescope selection mask
 *      vald => offset type
 *      vale => offset index
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

long tcsCADincrOffset (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static double delta1;   /* Step size */
  static double delta2;   /* Step size */
  static int tel;         /* Telescope selection mask */
  static OFFCOORD coord;  /* Coordinate type */
  static long ioff;       /* Offset index */
  char *telnames[] = {
     "MOUNT",
     "SOURCE A", "SOURCE B", "SOURCE C",
     "SOURCE_A", "SOURCE_B", "SOURCE_C",
     "SOURCE", "PWFS1", "PWFS2", "OIWFS",
     "G1", "G2", "G3", "G4",
     "ALL", NULL
  };
  int name;
  char message[256];


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
     if (tcsDcDouble ("RA/Az increment: ", pcad->a, &delta1, pcad)) break ;
     if (tcsDcDouble ("Dec/El increment: ", pcad->b, &delta2, pcad)) break ;

/* Convert increments to radians. */
     delta1 *= AS2R;
     delta2 *= AS2R;

/* Decode virtual telescope specification */
     if (tcsDcString(telnames, "telescope name: ", pcad->c, &name, pcad))
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
     case 11: tel = G1_M; break;
     case 12: tel = G2_M; break;
     case 13: tel = G3_M; break;
     case 14: tel = G4_M; break;
     case 15: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M |
                    PWFS1_M | PWFS2_M | OIWFS_M | G1_M | G2_M |
                    G3_M | G4_M; break;
     }

/* Offset type */
     if (tcsDcOffCoord("offset type: ", pcad->d, &coord, pcad)) break;

/* Offset index */
     if (tcsDcLong("offset: ", pcad->e, &ioff, pcad)) break;

/* Offset must be in the range 0-2 */
     if ( ioff < 0 || ioff > 2 ) {
         tcsCsAppendMessage(pcad, "offset: outside 0-2");
         break;
     }

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(double *) pcad->vala = (double)delta1 ;
      *(double *) pcad->valb = (double)delta2 ;
      *(long *) pcad->valc = (long)tel ;
      *(long *) pcad->vald = (long)coord ;
      *(long *) pcad->vale = ioff ;

      sprintf(message, "%s : off1: %s off2: %s tel: %s coord: %s ioff: %s", 
         tcsCsCadName(pcad), pcad->a, pcad->b, pcad->c, pcad->d, pcad->e);
      tcsLogMessage(message);

/* Call the kernel routine. */
      tcsIncrOffsets( coord == TANPLANE, delta1, delta2, tel, ioff );

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
 *   tcsCADpoAdj
 *
 *   Purpose:
 *   Interface to the pointing origin adjustment handset,
 *
 *   Description:
 *   The input links are read, the data validated, converted to internal
 *   representation and written to the output links. The adjustment is then
 *   rotated into x/y and a kernel routine called to adjust the pointing
 *   origin offset.
 *
 *   Invocation:
 *   tcsCADpoAdj (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Frame of adjustment ( 3 = tracking frame, 2 = instrument
 *           x/y, 1 = focal plane x/y, 0 = Az/El)
 *      b => Size of adjustment (arcsec)
 *      c => angle of adjustment
 *      d => virtual telescope index or mask
 *
 *   EPICS output parameters:
 *      vala => Frame of adjustment
 *      valb => Size of adjustment (arcsec)
 *      valc => angle of adjustment
 *      vald => virtual telescope index or mask
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

long tcsCADpoAdj (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static long frame;      /* Adjustment frame */
  static double delta;    /* Adjustment size */
  static double angle;    /* Adjustment angle */
  static long vtindex;    /* Virtual telescope index */
  struct WCS_CTX ctx;     /* Ast context. */
  double fl;              /* Focal length */
  FRAMETYPE tframe;       /* Tracking frame. */
  struct EPOCH eqx;       /* Tracking equinox. */
  double wavel;           /* Wavelength */
  struct WCS wcs;         /* WCS transformation. */
  double time;
  double xz, yz, xs, ys, perp;
  double orient;          /* Relative orientation of frames. */
  double iaa;             /* Instrument alignment angle. */
  TELESCOPE_M mask;       /* Virtual telescope selection mask. */
  char message[256];

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
     if (tcsDcLong ("frame: ", pcad->a, &frame, pcad)) break ;
     if ( frame  < 0 || frame > 3 ) {
          tcsCsAppendMessage( pcad, "Invalid frame");
          break;
     }
     if (tcsDcDouble ("adjustment: ", pcad->b, &delta, pcad)) break ;
     tcsOpticsGetFl( &fl );
     delta *= AS2R * fl;
     if (tcsDcDouble ("angle: ", pcad->c, &angle, pcad)) break ;
     angle *= D2R;
     if (tcsDcLong ("vt index: ", pcad->d, &vtindex, pcad)) break ;
     if ( vtindex > 3 ) {
         tcsCsAppendMessage( pcad, "Invalid vt index");
         break;
     } else if ( vtindex < -15 ) {
         tcsCsAppendMessage( pcad, "Invalid vt mask");
         break;
     }
     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(long *) pcad->vala = (long)frame ;
      *(double *) pcad->valb = (double)delta ;
      *(double *) pcad->valc = (double)angle ;
      *(long *) pcad->vald = (long)vtindex ;

      sprintf(message, "%s : frame: %s delta: %s angle: %s index: %s", 
         tcsCsCadName(pcad), pcad->a, pcad->b, pcad->c, pcad->d);
      tcsLogMessage(message);

/* Tracking frame (either some sort of RA/Dec or Az/El) */
      if ( frame == 3 ) {

/* Generate tracking frame to focal plane transformation matrix. */
         tcsGetFrame( SOURCE_A, &tframe, &eqx.year, &wavel );
         eqx.type = tframe == FK4 ? 'B' : 'J';
         astGettr( tframe, eqx, wavel, 0, &wcs, &time);

/* Extract angle from transformation */
         slaDcmpf( wcs.coeffs, &xz, &yz, &xs, &ys, &perp, &orient);

/* Add to requested angle. */
         angle += orient + PI;
      }

/* Instrument x/y */
      if ( frame == 2 ) {

/* Subract the instrument alignment angle from the requested angle to
   convert to focal plane x/y. */
        tcsGetIaa( &iaa);
        angle -= iaa;
      }

/* Az/El */
      if ( frame == 0 ) {

/* Add the rotator mechanical angle to the requested angle to
   convert to x/y. */
        astGetctx( &ctx );
        angle += ctx.tel.rma;
      }

/* Call kernel routine. */
   if ( vtindex < 0 ) {
       mask = (TELESCOPE_M) ( -vtindex );
   } else {
       mask = (TELESCOPE_M)( 1 << vtindex );
   }
   tcsIncrPoOffsets( -1.0 * delta * sin(angle), delta * cos(angle), 
          mask, 0);

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
 *   tcsCADcollAdj
 *
 *   Purpose:
 *   Interface to the pointing model adjustment handset,
 *
 *   Description:
 *   The input links are read, the data validated, converted to internal
 *   representation and written to the output links. The adjustment is then
 *   rotated into CA/CE and written to the output links.
 *
 *   Invocation:
 *   tcsCADcollAdj (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Frame of adjustment ( 3 = mount tracking frame, 2 = instrument
 *           x/y, 1 = focal plane x/y, 0 = Az/El)
 *      b => Size of adjustment (arcsec)
 *      c => angle of adjustment
 *
 *   EPICS output parameters:
 *      vala => Frame of adjustment
 *      valb => Size of adjustment (arcsec)
 *      valc => angle of adjustment
 *      vald => ca step
 *      vale => ce step
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

long tcsCADcollAdj (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static long frame;      /* Adjustment frame */
  static double delta;    /* Adjustment size */
  static double angle;    /* Adjustment angle */
  struct WCS_CTX ctx;     /* Ast context. */
  FRAMETYPE tframe;       /* Tracking frame. */
  struct EPOCH eqx;       /* Tracking equinox. */
  double wavel;           /* Wavelength */
  struct WCS wcs;         /* WCS transformation. */
  double time;
  double xz, yz, xs, ys, perp;
  double orient;          /* Relative orientation of frames. */
  double iaa;             /* Instrument alignment angle. */


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
     if (tcsDcLong ("frame: ", pcad->a, &frame, pcad)) break ;
     if ( frame  < 0 || frame > 3 ) {
          tcsCsAppendMessage( pcad, "Invalid frame");
          break;
     }
     if (tcsDcDouble ("adjustment: ", pcad->b, &delta, pcad)) break ;
     if (tcsDcDouble ("angle: ", pcad->c, &angle, pcad)) break ;
     angle *= D2R;

     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(long *) pcad->vala = (long)frame ;
      *(double *) pcad->valb = (double)delta ;
      *(double *) pcad->valc = (double)angle ;

/* Tracking frame (either some sort of RA/Dec or Az/El) */
      if ( frame == 3 ) {

/* Generate tracking frame to focal plane transformation matrix. */
         tcsGetFrame( MOUNT, &tframe, &eqx.year, &wavel );
         eqx.type = tframe == FK4 ? 'B' : 'J';
         astGettr( tframe, eqx, wavel, 0, &wcs, &time);

/* Extract angle from transformation */
         slaDcmpf( wcs.coeffs, &xz, &yz, &xs, &ys, &perp, &orient);

/* Add to requested angle. */
         angle += orient + PI;
      }

/* Instrument x/y */
      if ( frame == 2 ) {

/* Subract the instrument alignment angle from the requested angle to
   convert to focal plane x/y. */
        tcsGetIaa( &iaa);
        angle -= iaa;
      }

/* Focal plane x/y */
      if ( frame != 0 ) {

/* Subtract the rotator mechanical angle from the requested angle to
   convert to Az/El. */
        astGetctx( &ctx );
        angle -= ctx.tel.rma;
      }

/* Write CA & CE adjustments to output links. */
      *(double *) pcad->vald = (double)( delta * sin(angle));
      *(double *) pcad->vale = (double)( -1.0 * delta * cos(angle));

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
 *   tcsCADtarAdj
 *
 *   Purpose:
 *   Interface to the target adjustment handset,
 *
 *   Description:
 *   The input links are read, the data validated, converted to internal
 *   representation and written to the output links. The adjustment is then
 *   rotated into x/y and a kernel routine called to adjust the target
 *   offset.
 *
 *   Invocation:
 *   tcsCADtarAdj (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pcad   (struct cadRecord*)  Pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Frame of adjustment ( 3 = tracking frame, 2 = instrument
 *           x/y, 1 = focal plane x/y, 0 = Az/El)
 *      b => Size of adjustment (arcsec)
 *      c => angle of adjustment
 *      d => virtual telescope index or mask
 *
 *   EPICS output parameters:
 *      vala => Frame of adjustment
 *      valb => Size of adjustment (arcsec)
 *      valc => angle of adjustment
 *      vald => virtual telescope index or mask
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

long tcsCADtarAdj (struct cadRecord *pcad)

{

  long status ;           /* Return status */
  static long frame;      /* Adjustment frame */
  static double delta;    /* Adjustment size */
  static double angle;    /* Adjustment angle */
  static long vtindex;    /* Virtual telescope index */
  struct WCS_CTX ctx;     /* Ast context. */
  FRAMETYPE tframe;       /* Tracking frame. */
  struct EPOCH eqx;       /* Tracking equinox. */
  double wavel;           /* Wavelength */
  struct WCS wcs;         /* WCS transformation. */
  double time;
  double xz, yz, xs, ys, perp;
  double orient;          /* Relative orientation of frames. */
  double iaa;             /* Instrument alignment angle. */
  TELESCOPE_M mask;       /* Virtual telescope selection mask. */
  char message[256];

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
     if (tcsDcLong ("frame: ", pcad->a, &frame, pcad)) break ;
     if ( frame  < 0 || frame > 3 ) {
          tcsCsAppendMessage( pcad, "Invalid frame");
          break;
     }
     if (tcsDcDouble ("adjustment: ", pcad->b, &delta, pcad)) break ;
     delta *= AS2R;
     if (tcsDcDouble ("angle: ", pcad->c, &angle, pcad)) break ;
     angle *= D2R;
     if (tcsDcLong ("vt index: ", pcad->d, &vtindex, pcad)) break ;
     if ( vtindex > 10 ) {
          tcsCsAppendMessage( pcad, "Invalid vt index");
          break;
     } else if ( vtindex < -2047 ) {
         tcsCsAppendMessage( pcad, "Invalid vt mask");
         break;
     }
     if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

     status = CAD_ACCEPT ;
   break ;

   case menuDirectiveSTART :

/* Copy the validated input data to the output */
      *(long *) pcad->vala = (long)frame ;
      *(double *) pcad->valb = (double)delta ;
      *(double *) pcad->valc = (double)angle ;
      *(long *) pcad->vald = (long)vtindex ;

      sprintf(message, "%s : frame: %s delta: %s angle: %s index: %s", 
         tcsCsCadName(pcad), pcad->a, pcad->b, pcad->c, pcad->d);
      tcsLogMessage(message);

/* Az/El */
      if ( frame == 0 ) {

/* Add the rotator mechanical angle to the requested angle to
   convert to focal plane x/y. */
        astGetctx( &ctx );
        angle += ctx.tel.rma;
      }

/* Instrument x/y */
      if ( frame == 2 ) {

/* Subract the instrument alignment angle from the requested angle to
   convert to focal plane x/y. */
        tcsGetIaa( &iaa);
        angle -= iaa;
      }

/* Not the tracking frame */
      if ( frame != 3 ) {

/* Generate tracking frame to focal plane transformation matrix. */
         tcsGetFrame( SOURCE_A, &tframe, &eqx.year, &wavel );
         eqx.type = tframe == FK4 ? 'B' : 'J';
         astGettr( tframe, eqx, wavel, 0, &wcs, &time);

/* Extract angle from transformation */
         slaDcmpf( wcs.coeffs, &xz, &yz, &xs, &ys, &perp, &orient);

/* Subtract from requested angle to convert to tracking frame. */
         angle -= orient + PI;
      }

/* Call kernel routine. */
      if ( vtindex < 0 ) {
          mask = (TELESCOPE_M) ( -vtindex );
      } else {
          mask = (TELESCOPE_M)( 1 << vtindex );
      }
      tcsIncrOffsets( 1, -1.0 * delta * sin(angle), delta * cos(angle), 
             mask, 0);

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
epicsRegisterFunction(tcsCADtarAdj);
epicsRegisterFunction(tcsCADincrOffset);
epicsRegisterFunction(tcsCADcollAdj);
epicsRegisterFunction(tcsCADpoAdj);
