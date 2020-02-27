/*
*   FILENAME
*   tcsTcb.h
*
*   DESCRIPTION
*   This file defines the Telescope Control Block structure
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsTcb.h,v $
 * Revision 1.10  2012/05/08 09:41:15  cjm
 * Add p1LGSMode and AOconfig to TCB
 *
 * Revision 1.9  2007/12/18 10:10:08  cjm
 * Expand all arrays to include space for new guiders
 *
 * Revision 1.8  2007/01/09 11:41:40  cjm
 * Dimension orbit and planet elements of TCB structure
 *
 * Revision 1.7  2005/10/20 15:11:06  cjm
 * Add an ephemeris flag to the TARGET structure
 *
 * Revision 1.6  2002/04/17 10:27:22  cjm
 * Add extra structure for pointing origin offsets
 *
 * Revision 1.5  2000/12/05 13:46:50  dlt
 * Add flag to zero guide star offsets
 *
 * Revision 1.4  2000/04/18 15:12:45  cjm
 * Make INSTRING_SIZE the same as MAX_STRING_SIZE
 *
 * Revision 1.3  1999/05/29 08:12:29  dlt
 * Move tf to genertic parameters
 *
 * Revision 1.2  1999/05/11 00:43:27  cjm
 * Add an array of 20 generic pointing parameters to struct TSPMP
 *
 * Revision 1.1.1.1  1998/11/08 00:21:08  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.1  1997/11/19 16:05:43  tcs
 * implement slew parameters
 *
 */
/* *INDENT-ON* */

#ifndef TCSTCB_H
#define TCSTCB_H

#include <epicsTypes.h>
#include <dbDefs.h>
#include <astLib.h>
#include "tcsConstants.h"

#define INSTRING_SIZE MAX_STRING_SIZE 

struct SCAD_FIELD {
      char val[MAX_STRING_SIZE] ;  /* The (string) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct ICAD_FIELD {
      int  val ;           /* The (int) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct DCAD_FIELD {
      double val ;         /* The (double) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct FRAMECAD_FIELD {
      FRAMETYPE val ;      /* The (type FRAMETYPE) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct TELCAD_FIELD {
      TELESCOPE val ;      /* The (type TELESCOPE) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct OFFCAD_FIELD {
      OFFCOORD val ;       /* The (type OFFSETTYPE) value of the item */
      char   field ;       /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;


struct EPOCHCAD_FIELD {
      struct EPOCH val ;  /* The value (type EPOCH) of the item */
      char field ;        /* The name of the CAD field corresponding to this it em */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

struct TARGET {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this target */
     struct DCAD_FIELD theta1 ;       /* RA or Az (rads) depending on frame */
     struct DCAD_FIELD theta2 ;       /* Dec or Elevation (rads) */
     struct SCAD_FIELD name ;         /* Name of Target */
     struct FRAMECAD_FIELD frame ;    /* Input frame  */
     struct EPOCHCAD_FIELD eqx ;      /* Equinox of supplied positions */
     struct EPOCHCAD_FIELD epoch ;    /* Epoch of supplied positions */
     int    pm ;                      /* False = pm inertially-zero */
     struct DCAD_FIELD pmRA ;         /* proper motion in RA */
     struct DCAD_FIELD pmDec ;        /* Proper motion in Dec */
     struct DCAD_FIELD parallax ;     /* Parallax of target */
     struct DCAD_FIELD rv ;           /* radial velocity */
     int    ephemeris ;               /* True = data from ephemeris file */
} ;

struct DIFFTRACK {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this track rate */
     struct FRAMECAD_FIELD frame ;    /* frame */
     struct EPOCHCAD_FIELD eqx ;      /* Equinox of frame */
     struct DCAD_FIELD t0 ;           /* Start time for differential tracking */
     struct DCAD_FIELD dtheta1 ;      /* Differential tracking in RA */
     struct DCAD_FIELD dtheta2 ;      /* Differential tracking in Dec */
} ;

struct TRACK {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this frame */
     struct FRAMECAD_FIELD frame ;   /* Tracking frame */
     struct EPOCHCAD_FIELD eqx ;     /* Equinox of tracking frame */
     double theta1;                  /* RA or Az in tracking frame */
     double theta2;                  /* Dec or El in tracking frame */
     double dtheta1;                 /* Differential rate in theta1 */
     double dtheta2;                 /* Differential rate in theta2 */
     double t0;                      /* Start time for differential tracking */
} ;
 
struct TARGETFILTER {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this filter */
     struct DCAD_FIELD bw ;           /* Bandwidth */
     struct DCAD_FIELD maxv ;         /* Maximum velocity */
     struct DCAD_FIELD grab ;         /* Grab distance */
     struct ICAD_FIELD sc ;           /* Short circuit */
} ;
 
struct POINTFILTER {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this filter */
     struct DCAD_FIELD weightA ;      /* Weight to be used for chop_A */
     struct DCAD_FIELD weightB ;      /* Weight for chop_B */
     struct DCAD_FIELD weightC ;      /* Weight for chop_C */
     struct DCAD_FIELD weightNod ;    /* Weight for nod */
     struct DCAD_FIELD bw ;           /* Bandwidth */
     struct DCAD_FIELD maxv ;         /* Maximum velocity */
     struct DCAD_FIELD grab ;         /* Grab distance */
     struct ICAD_FIELD sc ;           /* Short circuit */
} ;
 
struct IMAGEPOS {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this image position */
     struct DCAD_FIELD x ;            /* X position (mm) */
     struct DCAD_FIELD y ;            /* Y position (mm) */
} ;
 
 
struct OFFBASE {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set this offset from base */
     struct OFFCAD_FIELD coord ;      /* type of offset */
     struct DCAD_FIELD dtheta1 ;      /* offset from base of theta1 (rads) */
     struct DCAD_FIELD dtheta2 ;      /* offset from base of theta2 (rads) */
} ;

struct ROT {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set the postion angle */
     struct DCAD_FIELD ipa ;          /* instrument position angle */
     struct FRAMECAD_FIELD frame ;    /* tracking frame */
     struct EPOCHCAD_FIELD eqx ;      /* equinox of frame */
     struct DCAD_FIELD iaa ;          /* instrument alignment angle */
} ;

struct CHOP {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set the chop */
     struct FRAMECAD_FIELD frame ;    /* tracking frame */
     struct EPOCHCAD_FIELD eqx ;      /* equinox of frame */
     struct ICAD_FIELD mode ;         /* chopping mode */
     struct DCAD_FIELD throw ;        /* chop throw  */
     struct DCAD_FIELD pa ;           /* chop position angle */
     int pari ;                       /* Position angle relative to IPA */
} ;
 
struct GUIDE {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set the guide parameters */
     struct ICAD_FIELD act[3][3] ;    /* active flags */
} ;
 
/* Data that is used for all VT's, not specific to an individual target */
struct SYSCONFIG {
      int needsCheck ;                /* True if TCB needs checking */
      double reftime ;                /* Reference time for configuration */
      struct ICAD_FIELD p1LGSMode ;   /* Bypasses many checks if true */
      struct ICAD_FIELD AOconfig ;    /* Flag to show if configured for AO */
      struct ICAD_FIELD chopmode ;    /* Chopping mode */
      struct DCAD_FIELD chopfreq ;    /* Chop frequency (Hz) */
      struct ICAD_FIELD azwrap ;      /* Desired azimuth wrap state (-1/0/+1) */
      struct ICAD_FIELD rotwrap ;     /* Desired rotator wrap state (-1/0/+1) */
      struct ROT rot ;                /* Rotator configuration */
      struct ICAD_FIELD clipAtLimit ; /* Clip at Limit flag */
} ;

/* Effective wavelength */
struct WAVEL {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set the wavelength */
     struct DCAD_FIELD wavel ;        /* Effective wavelength */
} ;

struct PLANETCAD_FIELD {
      PLANET  val ;      /* The (type PLANET) value of the item */
      char   field ;     /* The name of the CAD field corresponding to this item */
      char instring[INSTRING_SIZE] ; /* The CAD input field string */
} ;

/* Planet name */
struct PLANET {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set it */
     struct PLANETCAD_FIELD code ;    /* Planet code */
     int override_rates  ;            /* Override differential rates flag */
} ;

/* Orbital elements */
struct ORBIT {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set it */
     struct ICAD_FIELD jform ;        /* Element set code */
     struct DCAD_FIELD epoch ;        /* Epoch of elements (TT MJD) */
     struct DCAD_FIELD orbinc ;       /* Orbital inclination */
     struct DCAD_FIELD anode ;        /* Longitude of ascending node */
     struct DCAD_FIELD perih ;        /* Longitude or argument of perihelion */
     struct DCAD_FIELD aorq ;         /* Mean or perihelion distance */
     struct DCAD_FIELD e ;            /* Eccentricity */
     struct DCAD_FIELD aorl ;         /* Mean anomoly or longitude */
     struct DCAD_FIELD dm ;           /* Daily motion */
} ;

struct SLEW {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set it */
     struct ICAD_FIELD chop ;         /* Reset chop */
     struct ICAD_FIELD nod ;          /* Reset nod state */
     struct ICAD_FIELD soff ;         /* Reset source offsets */
     struct ICAD_FIELD sdt ;          /* Reset source track rates */
     struct ICAD_FIELD moff ;         /* Reset mount offsets */
     struct ICAD_FIELD mdt ;          /* Reset mount track rates */
     struct ICAD_FIELD sc1 ;          /* Short circuit filter 1 */
     struct ICAD_FIELD sc2 ;          /* Short circuit filter 2 */
     struct ICAD_FIELD lpm ;          /* Reset local pointing model */
     struct ICAD_FIELD guide ;        /* Disable guiding */
     struct ICAD_FIELD goff ;         /* Reset guiding offsets */
     struct ICAD_FIELD pooff ;        /* Reset pointing origin offsets */
} ;

struct VGCONFIG {
     char cadname[MAX_STRING_SIZE] ;  /* The name of the CAD used to set it */
     int destination ;   /* Index of output to which data is written */
} ;

struct TCB {
     struct SYSCONFIG sysconfig ;     /* Non-target specific data */ 
     struct TARGET target[11] ;        /* Base Target */
     struct WAVEL wavel[11] ;          /* Effective wavelength */
     struct DIFFTRACK difftrack[11] ;  /* Differential tracking */
     struct TRACK track[11] ;          /* Tracking frame */
     struct IMAGEPOS por[4] ;         /* Base pointing origin */
     struct IMAGEPOS porob[3][4] ;    /* Offsets from base of pointing origin */
     struct OFFBASE ob[3][11] ;        /* Offsets from base of target */
     struct TARGETFILTER tf1 ;        /* Source filter 1 */
     struct POINTFILTER pf2 ;         /* Pointing filter 2 */
     struct CHOP chop[2];             /* Chop parameters */
     struct GUIDE guide[7];           /* Guide parameters */
     struct PLANET planet[11];         /* Planet code */
     struct ORBIT orbit[11];           /* Orbital elements */
     struct SLEW slew;                /* Slew parameters */
     struct VGCONFIG vgconfig[4];     /* Virtual guide configuration */
} ;

#endif
