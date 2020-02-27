/* *INDENT-OFF* */
/*
 *   FILENAME
 *   tcsVtCads.c
 *
 *   FUNCTION NAME(S)
 *   tcsCADtarget   - Target CAD processing function
 *   tcsCADtrack    - Tracking frame CAD processing function
 *   tcsCADoffset   - Offset CAD processing function
 *   tcsCADporigin  - Pointing origin CAD processing function
 *   tcsCADoffsetPo - Pointing origin offset CAD processing function
 *   tcsCADdiffTr   - Differential tracking CAD processing function
 *   tcsCADwavel    - Wavelength CAD processing function
 *
 */
/*
 * $Log: tcsVtCads.c,v $
 * Revision 1.17  2016/05/09 16:08:20  gemvx
 * REL-2468: Added new target parameter for ephemeris file.
 *
 * Revision 1.16  2014/10/01 16:25:33  cjm
 * Add logging of commands
 *
 * Revision 1.15  2012/06/01 15:58:25  cjm
 * Make sure initial target frame is APPT for ephemeris data
 *
 * Revision 1.14  2007/12/18 10:09:19  cjm
 * Upgrade to handle the four new generic guiders
 *
 * Revision 1.13  2005/12/23 14:32:11  cjm
 * Use frame of ephemeris data for frame of target
 *
 * Revision 1.12  2005/12/14 16:37:45  cjm
 * New call sequence for tcsEphemerisTarget
 *
 * Revision 1.11  2005/10/21 15:42:36  cjm
 * Handle health return of ephemeris
 *
 * Revision 1.10  2005/10/20 15:09:02  cjm
 * Extend CADtarget to handle ephemeris files
 *
 * Revision 1.9  2003/10/17 16:35:19  gemvx
 * Handle target brightness parameter
 *
 * Revision 1.8  2002/04/09 23:33:18  dlt
 * Fix wrong setting of ntarget for PWFS1 in wavelength CAD
 *
 * Revision 1.7  2002/02/20 15:50:14  dlt
 * Improve TT handling
 *
 * Revision 1.6  2001/05/24 10:40:04  cjm
 * Use new menuCarStates and menuDirective constants
 *
 * Revision 1.5  2001/05/06 00:02:01  cjm
 * Minor changes to eliminate warnings
 *
 * Revision 1.4  2000/06/30 13:26:01  dlt
 * Correct units on output link of diffTrack
 *
 * Revision 1.3  2000/04/18 15:14:00  cjm
 * Fix bug that strings were being copied to locations that did't have enough space for them
 *
 * Revision 1.2  1999/06/16 21:27:32  dlt
 * Tidy up use of strcpy
 *
 * Revision 1.1.1.1  1998/11/08 00:21:08  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.12  1998/01/13 11:52:16  tcs
 * Change names of CAD subroutines
 *
 * Revision 1.11  1998/01/08 15:18:47  tcs
 * Change source CAD names
 *
 * Revision 1.10  1997/11/13 13:25:22  tcs
 * Revised guide star scheme
 *
 * Revision 1.9  1997/09/23 11:41:07  tcs
 * Remove blank line from comments
 *
 * Revision 1.8  1997/06/11 15:14:23  tcs
 * Implement wavelength CADs
 *
 * Revision 1.7  1997/06/09 15:55:56  tcs
 * Always define pm structure
 *
 * Revision 1.6  1997/05/28 16:34:45  cjm
 * Extra comments and different units for some outputs
 *
 * Revision 1.5  1997/05/16 12:21:38  tcs
 * make consistent use of frame/wavel/eqx
 *
 * Revision 1.4  1997/05/15 14:15:12  tcs
 * Move differential tracking to separate CAD
 *
 * Revision 1.3  1997/04/24 13:26:13  tcs
 * Make no epoch or pm imply an epoch of now
 *
 * Revision 1.2  1997/03/05 09:37:00  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:11:26  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.15  1997/02/05 11:00:43  tcs
 * Correct setting of CAD output links
 *
 * Revision 1.14  1997/01/24 14:25:26  tcs
 * Move tracking frame to separate CAD
 *
 * Revision 1.13  1997/01/23 10:45:31  tcs
 * Change epoch type to char
 *
 * Revision 1.12  1996/12/13 15:11:00  tcs
 * remove definition of CAD_REJECT and CAD_ACCEPT
 *
 * Revision 1.11  1996/12/13 15:06:08  tcs
 * cosmetic changes
 *
 * Revision 1.10  1996/12/12 16:57:15  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.9  1996/11/07 16:18:13  tcs
 * correct defaulting of frame/equinox
 *
 * Revision 1.8  1996/11/04 11:39:07  tcs
 * Add flag for inertially zero proper motions in B
 *
 * Revision 1.7  1996/10/25 10:12:43  tcs
 * Correct differential tracking units
 *
 * Revision 1.6  1996/10/24 16:11:16  tcs
 * Pointing origin offset commands
 *
 * Revision 1.5  1996/10/24 14:55:58  cjm
 * Restore RA/Dec Az/El labelling
 *
 * Revision 1.4  1996/10/24 12:10:51  tcs
 * add pointing origin commands
 *
 * Revision 1.3  1996/10/23 12:12:19  tcs
 * move offset unit conversion to tcsPointing
 *
 * Revision 1.2  1996/10/22 15:59:49  tcs
 * Add configuration offset commands
 *
 * Revision 1.1  1996/10/08 14:03:10  tcs
 * CAD commands for virtual telescope configuration
 *
 */
/* *INDENT-ON* */


#include <string.h>
#include <math.h>
#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <subRecord.h>
#include <cadRecord.h>
#include <cad.h>
#include <slalib.h>
#include <timeLib.h>
#include "tcsConstants.h"
#include "tcsConfig.h"
#include "tcsInterlocks.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "tcsEphemeris.h"
#include "tcsLogSupport.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADtarget
 *
 *   Purpose:
 *   Implements the various target CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADtarget( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *   Epics inputs:
 *      a => Object name: Up to 40 characters
 *      b => Coordinate system of position: AZEL_TOPO, APPT, FK5 or FK4.
 *      c => RA or Azimuth
 *      d => Dec or Elevation
 *      e => Equinox of position
 *      f => Epoch of position
 *      g => parallax: arcsec
 *      h => proper motion in RA: sec/year
 *      i => proper motion in Dec: arcsec/year
 *      j => radial velocity: km/s
 *      k => String describing brightness/magnitude
 *      l => Ephemeris file name
 *      m => Path to ephemeris files location (read from tcs:def:ephFolder)
 *
 *   Epics outputs:
 *
 *      vala => Object name
 *      valb => Coordinate system of position
 *      valc => RA or Azimuth (degs)
 *      vald => Dec or Elevation (degs)
 *      vale => Equinox of position
 *      valf => Epoch of position
 *      valg => Parallax (arcsecs)
 *      valh => Proper Motion in RA (s/yr)
 *      vali => Proper Motion in Dec (arcsec/yr)
 *      valj => Radial velocity (km/s)
 *      valk => Brightness description
 *      vall => Ephemeris file name
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   Prior requirements:
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADtarget(struct cadRecord *pcad)
{
    int status;
    static struct TARGET target[11];
    char* cadname;              /* Command name without prefix */
    int ntarget;                /* Index into target structure array */
    TELESCOPE tel;              /* Telescope name */
    char sname[MAX_STRING_SIZE];        /* source name */
    FRAMETYPE frame;            /* frame */
    double theta1;              /* RA or Azimuth */
    double theta2;              /* Dec or Elevation */
    double eqx;                 /* Equinox of position */
    char eqtype;                /* Type of equinox (B or J) */
    double epoch;               /* Epoch of position */
    char eptype;                /* Type of epoch (B or J) */
    int pm;                     /* False = pm inertially zero */
    double pmRA;                /* Proper motion in RA (radians/day) */
    double pmDec;               /* Proper motion in declination (rad/day) */
    double parallax;            /* Parallax (arcsec) */
    double rv;                  /* Radial velocity (km/s) */
    double traw;                /* Reference time */
    double tt;                  /* TT at reference time */
    int ind ;                   /* Temporary index */
    char *snp ;             
    double tmjd ;               /* Current time (MJD) */
    char mess[MAX_STRING_SIZE]; /* Return error message */
    char hlth[8];               /* Health of ephemeris */
    int ephemeris ;             /* True = data from ephemeris file */
    double dtheta1, dtheta2 ;   /* Track rates (not used) */
    char message[256];
    char ephFile[MAX_STRING_SIZE]; /* Ephemeris file name */
    char ephBasePath[MAX_STRING_SIZE]; /* Path to ephemeris files */
    char fullEphFileName[2*MAX_STRING_SIZE];

/* Telescope name from name of CAD */
    cadname = tcsCsCadName( pcad );
    if (!strcmp(cadname, "mount")) {
        tel = MOUNT;
        ntarget = 0;
    } else if (!strcmp(cadname, "sourceA")) {
        tel = SOURCE_A;
        ntarget = 1;
    } else if (!strcmp(cadname, "sourceB")) {
        tel = SOURCE_B;
        ntarget = 2;
    } else if (!strcmp(cadname, "sourceC")) {
        tel = SOURCE_C;
        ntarget = 3;
    } else if (!strcmp(cadname, "pwfs1")) {
        tel = PWFS1;
        ntarget = 4;
    } else if (!strcmp(cadname, "pwfs2")) {
        tel = PWFS2;
        ntarget = 5;
    } else if (!strcmp(cadname, "oiwfs")) {
        tel = OIWFS;
        ntarget = 6;
    } else if (!strcmp(cadname, "g1")) {
        tel = G1;
        ntarget = 7;
    } else if (!strcmp(cadname, "g2")) {
        tel = G2;
        ntarget = 8;
    } else if (!strcmp(cadname, "g3")) {
        tel = G3;
        ntarget = 9;
    } else if (!strcmp(cadname, "g4")) {
        tel = G4;
        ntarget = 10;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
        return CAD_REJECT ;
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/*  Object name. If the name ends in .eph then the name is interpreted
 *  as a file as generated by the JPL ephemeris service. The target
 *  name is then taken as the characters before the .eph and after any
 *  directory delimiter. 
 */
        strcpy(sname, pcad->a);
	strcpy(ephFile, pcad->l);
        if ( strtok(ephFile, " \t")!=NULL || strstr(sname,".eph")) {
          if (tel == MOUNT || tel == SOURCE_B || tel == SOURCE_C) {
            tcsCsAppendMessage(pcad, "Ephemeris input not supported");
            return status;
          }
	  
	  strcpy(ephBasePath, pcad->m);
	  if(strtok(ephBasePath, " \t")==NULL) {
	    strcpy(ephBasePath, "/");
	  }
 
          if(strstr(sname, ".eph")) {
	    strcpy(ephFile, sname);
	    ind = strlen(sname) - 4;
	    sname[ind] = '\0';
	    snp = strrchr(sname, '/');
	    if (snp) {
	      strcpy(sname, snp+1);
	    }
	  }

	  if(ephFile[0] == '/') {
	    strcpy(fullEphFileName, ephFile);
	  } else {
	    strcpy(fullEphFileName, ephBasePath);
	    if(fullEphFileName[strlen(fullEphFileName)-1]!='/') {
	      strcat(fullEphFileName, "/");
	    }
	    strcat(fullEphFileName, ephFile);
	  }

/* Now load the ephemeris  */
          tcsConfigGetReftime(CURRENT, &traw);
          timeThenD(traw, UTC, &tmjd);
          timeThenD(traw, TT, &tt);

          if (tcsEphemerisLoad(fullEphFileName, tel, tmjd, mess)) {
            tcsCsAppendMessage(pcad, mess);
            break ;
          }


/* Extract the data for the current time.  We can chose what frame we
*  would like the data in. Currently we always select APPT 
*/
          tcsEphemerisFrame(tel, &frame);
          frame = APPT ;
          if (tcsEphemerisTarget(tmjd, tel, frame, &theta1, &theta2, &dtheta1,
                                 &dtheta2, hlth, mess)) { 
            tcsCsAppendMessage(pcad, mess);
            break ;
          }
          if (frame == FK5) {
            eqtype = 'J';
            eqx = 2000.0 ;
          } else if (frame == FK4) {
            eqtype = 'B';
            eqx = 1950.0 ;
          } else {
            frame = APPT;
            eqtype = ' ';
            eqx = 0.0 ;
          }
          epoch = slaEpj(tt);
          eptype = 'J';
          pm = 0;
          parallax = 0.0;
          pmRA = 0.0;
          pmDec = 0.0;
          rv = 0.0;  
          ephemeris = 1;

        } else {

/*  Frame and equinox. The defaults for these two fields are related by
   the following rules:
   FK5 => J2000
   eqx < 1984.0 => B else J
   Jxxxx => FK5
   Bxxxx => FK4 */
          if ( pcad->b[ 0 ] ) {
             if (tcsDcFrame("frame: ", pcad->b, &frame, pcad)) break;
             if (frame == FK4 || frame == FK5) {
                if ( pcad->e[ 0 ] ) {
                   if (tcsDcEpoch("equinox: ", pcad->e, &eqtype, &eqx,
                       pcad)) break;
                } else {
                   if (frame == FK5) {
                      eqtype = 'J';
                      eqx = 2000.0;
                   } else if (frame == FK4) {
                      eqtype = 'B';
                      eqx = 1950.0;
                   }
                }
             } else {
                eqx = 0.0;  /* not relevant for this frame */
                eqtype = ' ';
             }
          } else {     /* frame is blank */
              if ( pcad->c[ 0 ] ) {
                 if (tcsDcEpoch("equinox: ", pcad->e, &eqtype, &eqx, 
                    pcad)) break;
                 frame = eqtype == 'B' ? FK4 : FK5;
              } else {
                 frame = FK5;
                 eqtype = 'J';
                 eqx = 2000.0;
              }
          }

/* target position */
          if (tcsDcRadec("position: ", frame, pcad->c, pcad->d, &theta1,
                          &theta2, pcad)) break;

/* Assume no proper motions until parallax or proper motion detected */
          pm = 0;
          parallax = 0.0;
          pmRA = 0.0;
          pmDec = 0.0;

/* parallax */
          if ( pcad->g[ 0 ] ) {
             if (tcsDcPx("parallax: ", pcad->g, &parallax, pcad)) break;
             pm = 1;
          }

/* proper motions */
          if ( pcad->h[ 0 ] ) {
             if (tcsDcPmra("proper motion: ", pcad->h, &pmRA, pcad)) break;
             pm = 1;
          }
          if ( pcad->i[ 0 ] ) {
             if (tcsDcPmdec("proper motion: ", pcad->i, &pmDec, pcad)) break;
             pm = 1;
          }

/* epoch */
          if ( pcad->f[ 0 ] ) {
             if (tcsDcEpoch("epoch: ", pcad->f, &eptype, &epoch, 
                pcad)) break;
          } else {    /* blank */
              if ( pm ) {      /* proper motions so use same as equinox */
                 epoch = eqx;
                 eptype = eqtype;
              } else {
                 tcsConfigGetReftime(CURRENT, &traw);
                 timeThenD(traw, TT, &tt);
                 epoch = slaEpj( tt );
                 eptype = 'J';
              }
          }

/* radial velocity */
          if (tcsDcRv("radial velocity: ", pcad->j, &rv, pcad)) break;
     
          ephemeris = 0;

        }

/* Load the data into the configuration block */
        strcpy(target[ntarget].cadname, strrchr(pcad->name, ':') + 1);

        target[ntarget].name.field = 'A';
        strcpy(target[ntarget].name.instring, pcad->a);
        strcpy(target[ntarget].name.val, sname);

        target[ntarget].frame.field = 'B';
        strcpy(target[ntarget].frame.instring, pcad->b);
        target[ntarget].frame.val = frame;

        target[ntarget].theta1.field = 'C';
        strcpy(target[ntarget].theta1.instring, pcad->c);
        target[ntarget].theta1.val = theta1;

        target[ntarget].theta2.field = 'D';
        strcpy(target[ntarget].theta2.instring, pcad->d);
        target[ntarget].theta2.val = theta2;

        target[ntarget].eqx.field = 'E';
        strcpy(target[ntarget].eqx.instring, pcad->e);
        target[ntarget].eqx.val.year = eqx;
        target[ntarget].eqx.val.type = eqtype;

        target[ntarget].epoch.field = 'F';
        strcpy(target[ntarget].epoch.instring, pcad->f);
        target[ntarget].epoch.val.year = epoch;
        target[ntarget].epoch.val.type = eptype;

        target[ntarget].parallax.field = 'G';
        strcpy(target[ntarget].parallax.instring, pcad->g);
        target[ntarget].parallax.val = parallax;

        target[ntarget].pm = pm;

        target[ntarget].pmRA.field = 'H';
        strcpy(target[ntarget].pmRA.instring, pcad->h);
        target[ntarget].pmRA.val = pmRA;

        target[ntarget].pmDec.field = 'I';
        strcpy(target[ntarget].pmDec.instring, pcad->i);
        target[ntarget].pmDec.val = pmDec;

        target[ntarget].rv.field = 'J';
        strcpy(target[ntarget].rv.instring, pcad->j);
        target[ntarget].rv.val = rv;

        target[ntarget].ephemeris = ephemeris ;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetTarget(tel, &target[ntarget]);

/* As the target frame has changed the reference time for differential 
   track rates must be updated to the reference time and
   the track rates set to zero */
        tcsConfigGetReftime(CURRENT, &traw);
        timeThenD(traw, TT, &tt);
        tcsConfigUpdateDiffTrack(tel, tt, TRUE);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strcpy(pcad->vala, target[ntarget].name.val);
        strcpy(pcad->valb, tcsCsFrame(target[ntarget].frame.val)); 
        *(double *) pcad->valc = target[ntarget].theta1.val/D2R;
        *(double *) pcad->vald = target[ntarget].theta2.val/D2R;
        sprintf(pcad->vale, "%c%.14f", target[ntarget].eqx.val.type,
                target[ntarget].eqx.val.year);
        sprintf(pcad->valf, "%c%.14f", target[ntarget].epoch.val.type,
                target[ntarget].epoch.val.year);
        *(double *) pcad->valg = target[ntarget].parallax.val;
        *(double *) pcad->valh = target[ntarget].pmRA.val/S2R;
        *(double *) pcad->vali = target[ntarget].pmDec.val/AS2R;
        *(double *) pcad->valj = target[ntarget].rv.val;
	strcpy (pcad->valk, pcad->k) ;
	strcpy (pcad->vall, pcad->l) ;

        sprintf(message, "%s : RA: %s Dec: %s", cadname, pcad->c, pcad->d);
        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADtrack
 *
 *   Purpose:
 *   Implements the various frame CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADtrack( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *      a Coordinate system for tracking
 *      b Equinox of tracking coordinate system
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADtrack(struct cadRecord *pcad)
{
    int status;
    static struct TRACK track[11];
    char* cadname;              /* Command name without prefix */
    int ntrack;                 /* Index into track array */
    TELESCOPE tel;              /* Telescope name */
    FRAMETYPE frame;            /* tracking frame */
    double eqx;                 /* Equinox of tracking frameposition */
    char type;                  /* Type of equinox (B or J) */
    double traw;                /* Reference time */
    double tt;                  /* TT at reference time */

/* Telescope name from name of CAD */
    cadname = tcsCsCadName(pcad);
    ntrack = 0;
    tel = MOUNT;

    if (!strcmp(cadname, "trackMount")) {
        tel = MOUNT;
        ntrack = 0;
    }
    else if (!strcmp(cadname, "trackSourceA")) {
        tel = SOURCE_A;
        ntrack = 1;
    }
    else if (!strcmp(cadname, "trackSourceB")) {
        tel = SOURCE_B;
        ntrack = 2;
    }
    else if (!strcmp(cadname, "trackSourceC")) {
        tel = SOURCE_C;
        ntrack = 3;
    }
    else if (!strcmp(cadname, "trackPwfs1")) {
        tel = PWFS1;
        ntrack = 4;
    }
    else if (!strcmp(cadname, "trackPwfs2")) {
        tel = PWFS2;
        ntrack = 5;
    }
    else if (!strcmp(cadname, "trackOiwfs")) {
        tel = OIWFS;
        ntrack = 6;
    }
    else if (!strcmp(cadname, "trackG1")) {
        tel = G1;
        ntrack = 7;
    }
    else if (!strcmp(cadname, "trackG2")) {
        tel = G2;
        ntrack = 8;
    }
    else if (!strcmp(cadname, "trackG3")) {
        tel = G3;
        ntrack = 9;
    }
    else if (!strcmp(cadname, "trackG4")) {
        tel = G4;
        ntrack = 10;
    }
    else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess))  return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* tracking frame The defaults for these two fields are related by
   the following rules:
   FK5 => J2000
   eqx < 1984.0 => B else J
   Jxxxx => FK5
   Bxxxx => FK4 */
        if ( pcad->a[ 0 ] ) {
           if (tcsDcFrame("frame: ", pcad->a, &frame, pcad)) break;
           if (frame == FK4 || frame == FK5) {
              if ( pcad->b[ 0 ] ) {
                 if (tcsDcEpoch("equinox: ", pcad->b, &type, &eqx,
                     pcad)) break;
              } else {
                 if (frame == FK5) {
                    type = 'J';
                    eqx = 2000.0;
                 } else if (frame == FK4) {
                    type = 'B';
                    eqx = 1950.0;
                 }
              }
           } else {
              eqx = 0.0;  /* not relevant for this frame */
              type = ' ';
           }
        } else {     /* frame is blank */
            if ( pcad->b[ 0 ] ) {
               if (tcsDcEpoch("equinox: ", pcad->b, &type, &eqx, 
                  pcad)) break;
               frame = type == 'B' ? FK4 : FK5;
            } else {
               frame = FK5;
               type = 'J';
               eqx = 2000.0;
            }
        }

/* As the tracking frame has changed the reference time for differential 
   track rates and position must be updated to the reference time */
        tcsConfigGetReftime(CURRENT, &traw);
        timeThenD(traw, TT, &tt);
        tcsConfigUpdateDiffTrack(tel, tt, FALSE);

/* Load the data into the configuration block */
        strcpy(track[ntrack].cadname, cadname);

        track[ntrack].frame.field = 'A';
        strncpy(track[ntrack].frame.instring, pcad->a, MAX_STRING_SIZE);
        track[ntrack].frame.val = frame;

        track[ntrack].eqx.field = 'B';
        strncpy(track[ntrack].eqx.instring, pcad->b, MAX_STRING_SIZE);
        track[ntrack].eqx.val.year = eqx;
        track[ntrack].eqx.val.type = type;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetTrack(tel, &track[ntrack]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strncpy(pcad->vala, tcsCsFrame(track[ntrack].frame.val), 
                MAX_STRING_SIZE);
        sprintf(pcad->valb, "%c%.14f", track[ntrack].eqx.val.type,
                track[ntrack].eqx.val.year);

        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADoffset
 *
 *   Purpose:
 *   Implements the various offset CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADoffset( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:

 *      a Offset type: RAdec or TangentPlane
 *      b Offset in RA (secs) or Azimuth (arcsecs)
 *      c Offset in Dec or Elevation (arcsecs)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADoffset(struct cadRecord *pcad)
{
    int status;
    static struct OFFBASE offbase[31];
    char* cadname;              /* Command name without prefix */
    int noffbase;               /* Index into offbase array */
    TELESCOPE tel;              /* Telescope name */
    int noff;                   /* Offset index */
    OFFCOORD coord;             /* Offset coordinates (RADec or Tangent plane) */
    double dtheta1;             /* RA or Azimuth */
    double dtheta2;             /* Dec or Elevation */
    char message[256];          /* Message for log file */

/* Telescope name and offset index from name of CAD */
    cadname = tcsCsCadName( pcad);

    noff = 0;
    if (!strcmp(cadname, "offsetMount")) {
        tel = MOUNT;
        noffbase = 0;
    } else if (!strcmp(cadname, "offsetSourceA")) {
        tel = SOURCE_A;
        noffbase = 1;
    } else if (!strcmp(cadname, "offsetSourceA1")) {
        tel = SOURCE_A;
        noff = 1;
        noffbase = 2;
    } else if (!strcmp(cadname, "offsetSourceA2")) {
        tel = SOURCE_A;
        noff = 2;
        noffbase = 3;
    } else if (!strcmp(cadname, "offsetSourceB")) {
        tel = SOURCE_B;
        noffbase = 4;
    } else if (!strcmp(cadname, "offsetSourceB1")) {
        tel = SOURCE_B;
        noff = 1;
        noffbase = 5;
    } else if (!strcmp(cadname, "offsetSourceB2")) {
        tel = SOURCE_B;
        noff = 2;
        noffbase = 6;
    } else if (!strcmp(cadname, "offsetSourceC")) {
        tel = SOURCE_C;
        noffbase = 7;
    } else if (!strcmp(cadname, "offsetSourceC1")) {
        tel = SOURCE_C;
        noff = 1;
        noffbase = 8;
    } else if (!strcmp(cadname, "offsetSourceC2")) {
        tel = SOURCE_C;
        noff = 2;
        noffbase = 9;
    } else if (!strcmp(cadname, "offsetPwfs1A")) {
        tel = PWFS1;
        noffbase = 10;
    } else if (!strcmp(cadname, "offsetPwfs1B")) {
        tel = PWFS1;
        noff = 1;
        noffbase = 11;
    } else if (!strcmp(cadname, "offsetPwfs1C")) {
        tel = PWFS1;
        noff = 2;
        noffbase = 12;
    } else if (!strcmp(cadname, "offsetPwfs2A")) {
        tel = PWFS2;
        noffbase = 13;
    } else if (!strcmp(cadname, "offsetPwfs2B")) {
        tel = PWFS2;
        noff = 1;
        noffbase = 14;
    } else if (!strcmp(cadname, "offsetPwfs2C")) {
        tel = PWFS2;
        noff = 2;
        noffbase = 15;
    } else if (!strcmp(cadname, "offsetOiwfsA")) {
        tel = OIWFS;
        noffbase = 16;
    } else if (!strcmp(cadname, "offsetOiwfsB")) {
        tel = OIWFS;
        noff = 1;
        noffbase = 17;
    } else if (!strcmp(cadname, "offsetOiwfsC")) {
        tel = OIWFS;
        noff = 2;
        noffbase = 18;
    } else if (!strcmp(cadname, "offsetG1A")) {
        tel = G1;
        noffbase = 19;
    } else if (!strcmp(cadname, "offsetG1B")) {
        tel = G1;
        noff = 1;
        noffbase = 20;
    } else if (!strcmp(cadname, "offsetG1C")) {
        tel = G1;
        noff = 2;
        noffbase = 21;
    } else if (!strcmp(cadname, "offsetG2A")) {
        tel = G2;
        noffbase = 22;
    } else if (!strcmp(cadname, "offsetG2B")) {
        tel = G2;
        noff = 1;
        noffbase = 23;
    } else if (!strcmp(cadname, "offsetG2C")) {
        tel = G2;
        noff = 2;
        noffbase = 24;
    } else if (!strcmp(cadname, "offsetG3A")) {
        tel = G3;
        noffbase = 25;
    } else if (!strcmp(cadname, "offsetG3B")) {
        tel = G3;
        noff = 1;
        noffbase = 26;
    } else if (!strcmp(cadname, "offsetG3C")) {
        tel = G3;
        noff = 2;
        noffbase = 27;
    } else if (!strcmp(cadname, "offsetG4A")) {
        tel = G4;
        noffbase = 28;
    } else if (!strcmp(cadname, "offsetG4B")) {
        tel = G4;
        noff = 1;
        noffbase = 29;
    } else if (!strcmp(cadname, "offsetG4C")) {
        tel = G4;
        noff = 2;
        noffbase = 30;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
        return CAD_REJECT ;
    }


/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Offset type */
        if (tcsDcOffCoord("", pcad->a, &coord, pcad)) break;

/* dtheta1 and 2 */
        if (tcsDcOffset("", pcad->b, &dtheta1, pcad)) break;
        if (tcsDcOffset("", pcad->c, &dtheta2, pcad)) break;

/* Load the data into the configuration block */
        strcpy(offbase[noffbase].cadname, strrchr(pcad->name, ':') + 1);

        offbase[noffbase].coord.field = 'A';
        strncpy(offbase[noffbase].coord.instring, pcad->a, MAX_STRING_SIZE);
        offbase[noffbase].coord.val = coord;

        offbase[noffbase].dtheta1.field = 'B';
        strncpy(offbase[noffbase].dtheta1.instring, pcad->b, MAX_STRING_SIZE);
        offbase[noffbase].dtheta1.val = dtheta1;

        offbase[noffbase].dtheta2.field = 'C';
        strncpy(offbase[noffbase].dtheta2.instring, pcad->c, MAX_STRING_SIZE);
        offbase[noffbase].dtheta2.val = dtheta2;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetOffset(tel, noff, &offbase[noffbase]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strncpy( pcad->vala, tcsCsOffCoord(offbase[noffbase].coord.val), 
               MAX_STRING_SIZE);
        *(double *) pcad->valb = offbase[noffbase].dtheta1.val;
        *(double *) pcad->valc = offbase[noffbase].dtheta2.val;
        sprintf(message, "%s : Type: %s off1: %s off2: %s", cadname, 
                                                   pcad->a, pcad->b, pcad->c);

        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADporigin
 *
 *   Purpose:
 *   Implements the pointing origin CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADporigin( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:

 *      a x pointing origin (millimetres)
 *      b x pointing origin (millimetres)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADporigin(struct cadRecord *pcad)
{
    int status;
    static struct IMAGEPOS imagepos[4];
    char* cadname;              /* Command name without prefix */
    int nimpos;                 /* Index into imagepos array */
    TELESCOPE tel;              /* Telescope name */
    double x;                   /* x pointing origin */
    double y;                   /* y pointing origin */
    char message[256];

/* Telescope name from name of CAD */
    cadname = tcsCsCadName( pcad);
    nimpos = 0;
    tel = MOUNT;

    strcpy(cadname, strrchr(pcad->name, ':') + 1);
    if (!strcmp(cadname, "poriginM")) {
        tel = MOUNT;
        nimpos = 0;
    } else if (!strcmp(cadname, "poriginA")) {
        tel = SOURCE_A;
        nimpos = 1;
    } else if (!strcmp(cadname, "poriginB")) {
        tel = SOURCE_B;
        nimpos = 2;
    } else if (!strcmp(cadname, "poriginC")) {
        tel = SOURCE_C;
        nimpos = 3;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess))  return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* x & y */
        if (tcsDcPo("", pcad->a, &x, pcad)) break;
        if (tcsDcPo("", pcad->b, &y, pcad)) break;

/* Load the data into the configuration block */
        strcpy(imagepos[nimpos].cadname, strrchr(pcad->name, ':') + 1);

        imagepos[nimpos].x.field = 'A';
        strncpy(imagepos[nimpos].x.instring, pcad->a, MAX_STRING_SIZE);
        imagepos[nimpos].x.val = x;

        imagepos[nimpos].y.field = 'B';
        strncpy(imagepos[nimpos].y.instring, pcad->b, MAX_STRING_SIZE);
        imagepos[nimpos].y.val = y;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetPo(tel, &imagepos[nimpos]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        *(double *) pcad->vala = imagepos[nimpos].x.val;
        *(double *) pcad->valb = imagepos[nimpos].y.val;
        sprintf(message, "%s : x: %s y: %s", cadname, pcad->a, pcad->b);
        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}
/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADoffsetPo
 *
 *   Purpose:
 *   Implements the pointing origin offset CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADoffsetPo( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:

 *      a x pointing origin offset (millimetres)
 *      b x pointing origin offset (millimetres)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADoffsetPo(struct cadRecord *pcad)
{
    int status;
    static struct IMAGEPOS imagepos[10];
    int nimpos;                 /* Index into imagepos array */
    char* cadname;              /* Command name without prefix */
    TELESCOPE tel;              /* Telescope name */
    int noff;                   /* Offset index */
    double x;                   /* x pointing origin */
    double y;                   /* y pointing origin */
    char message[256];      

/* Telescope name from name of CAD */
    cadname = tcsCsCadName( pcad);
    nimpos = 0;
    tel = MOUNT;

    noff = 0;
    if (!strcmp(cadname, "offsetPoM")) {
        tel = MOUNT;
        nimpos = 0;
    } else if (!strcmp(cadname, "offsetPoA")) {
        tel = SOURCE_A;
        nimpos = 1;
    } else if (!strcmp(cadname, "offsetPoA1")) {
        tel = SOURCE_A;
        noff = 1;
        nimpos = 2;
    } else if (!strcmp(cadname, "offsetPoA2")) {
        tel = SOURCE_A;
        noff = 2;
        nimpos = 3;
    } else if (!strcmp(cadname, "offsetPoB")) {
        tel = SOURCE_B;
        nimpos = 4;
    } else if (!strcmp(cadname, "offsetPoB1")) {
        tel = SOURCE_B;
        noff = 1;
        nimpos = 5;
    } else if (!strcmp(cadname, "offsetPoB2")) {
        tel = SOURCE_B;
        noff = 2;
        nimpos = 6;
    } else if (!strcmp(cadname, "offsetPoC")) {
        tel = SOURCE_C;
        nimpos = 7;
    } else if (!strcmp(cadname, "offsetPoC1")) {
        tel = SOURCE_C;
        noff = 1;
        nimpos = 8;
    } else if (!strcmp(cadname, "offsetPoC2")) {
        tel = SOURCE_C;
        noff = 2;
        nimpos = 9;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* x & y */
        if (tcsDcPo("", pcad->a, &x, pcad)) break;
        if (tcsDcPo("", pcad->b, &y, pcad)) break;

/* Load the data into the configuration block */
        strcpy(imagepos[nimpos].cadname, strrchr(pcad->name, ':') + 1);

        imagepos[nimpos].x.field = 'A';
        strncpy(imagepos[nimpos].x.instring, pcad->a, MAX_STRING_SIZE);
        imagepos[nimpos].x.val = x;

        imagepos[nimpos].y.field = 'B';
        strncpy(imagepos[nimpos].y.instring, pcad->b, MAX_STRING_SIZE);
        imagepos[nimpos].y.val = y;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetPoOffset(tel, noff, &imagepos[nimpos]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        *(double *) pcad->vala = imagepos[nimpos].x.val;
        *(double *) pcad->valb = imagepos[nimpos].y.val;
        sprintf(message, "%s : x: %s y: %s", cadname, pcad->a, pcad->b);
        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADdiffTr
 *
 *   Purpose:
 *   Implements the various target CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADdiffTr( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *      a Coordinate system of rate: AZEL_TOPO, APPT, FK5 or FK4.
 *      b Equinox of frame
 *      c reference epoch for differential tracking
 *      d differential tracking in RA or Azimuth: s/s or arcsec/s
 *      e differential tracking in Dec or Elevation: arcsec/s
 *
 *   Epics outputs:
 *      vala -> Coordinate frame of rate
 *      valb -> Equinox of the frame
 *      valc -> Reference epoch (TT as an MJD)
 *      vald -> Differential rate in RA (s/s)
 *      vale -> Differential rate in Dec (arcsec/s)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADdiffTr(struct cadRecord *pcad)
{
    int status;
    static struct DIFFTRACK difftrack[11];
    char* cadname;              /* Command name without prefix */
    int ntarget;                /* Index into target structure array */
    TELESCOPE tel;              /* Telescope name */
    FRAMETYPE frame;            /* frame */
    double eqx;                 /* Equinox of position */
    char type;                  /* B or J */
    double t0;                  /* Reference epoch for diff tracking */
    double dtheta1;             /* Differental track rate in RA or Azimuth */
    double dtheta2;             /* Diff track rate in Dec or elevation */
    double traw;                /* Reference time */
    double tt;                  /* TT at reference time */
    int j;                      /* Status return. */
    char message[256];

/* Telescope name from name of CAD */
    cadname = tcsCsCadName( pcad );
    if (!strcmp(cadname, "difTrMount")) {
        tel = MOUNT;
        ntarget = 0;
    } else if (!strcmp(cadname, "difTrSourceA")) {
        tel = SOURCE_A;
        ntarget = 1;
    } else if (!strcmp(cadname, "difTrSourceB")) {
        tel = SOURCE_B;
        ntarget = 2;
    } else if (!strcmp(cadname, "difTrSourceC")) {
        tel = SOURCE_C;
        ntarget = 3;
    } else if (!strcmp(cadname, "difTrPwfs1")) {
        tel = PWFS1;
        ntarget = 4;
    } else if (!strcmp(cadname, "difTrPwfs2")) {
        tel = PWFS2;
        ntarget = 5;
    } else if (!strcmp(cadname, "difTrOiwfs")) {
        tel = OIWFS;
        ntarget = 6;
    } else if (!strcmp(cadname, "difTrG1")) {
        tel = G1;
        ntarget = 7;
    } else if (!strcmp(cadname, "difTrG2")) {
        tel = G2;
        ntarget = 8;
    } else if (!strcmp(cadname, "difTrG3")) {
        tel = G3;
        ntarget = 9;
    } else if (!strcmp(cadname, "difTrG4")) {
        tel = G4;
        ntarget = 10;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
        return CAD_REJECT ;
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Frame The defaults for these two fields are related by
   the following rules:
   FK5 => J2000
   eqx < 1984.0 => B else J
   Jxxxx => FK5
   Bxxxx => FK4 */
        if ( pcad->a[ 0 ] ) {
           if (tcsDcFrame("frame: ", pcad->a, &frame, pcad)) break;
           if (frame == FK4 || frame == FK5) {
              if ( pcad->b[ 0 ] ) {
                 if (tcsDcEpoch("equinox: ", pcad->b, &type, &eqx,
                     pcad)) break;
              } else {
                 if (frame == FK5) {
                    type = 'J';
                    eqx = 2000.0;
                 } else if (frame == FK4) {
                    type = 'B';
                    eqx = 1950.0;
                 }
              }
           } else {
              eqx = 0.0;  /* not relevant for this frame */
              type = ' ';
           }
        } else {     /* frame is blank */
            if ( pcad->b[ 0 ] ) {
               if (tcsDcEpoch("equinox: ", pcad->b, &type, &eqx, 
                  pcad)) break;
               frame = type == 'B' ? FK4 : FK5;
            } else {
               frame = FK5;
               type = 'J';
               eqx = 2000.0;
            }
        }

/* Zero time */
        j = tcsDcT0("diff tracking: ", pcad->c, &t0, pcad);
        if ( j < 0 ) break;

        if ( j > 0 ) {
             tcsConfigGetReftime(CURRENT, &traw);
             timeThenD(traw, TT, &tt);

/* Interpret blank as "now". */
             if ( j == 2 )
                 t0 = tt;

/* Interpret fractional result as "today". */
             else if ( j == 1 )
                 t0 += floor(tt);
        }

/* differential tracking */
        if (tcsDcDt("diff tracking: ",frame, pcad->d, pcad->e, &dtheta1, 
            &dtheta2, pcad)) break;

/* Update position to the new zero time time */
        tcsConfigUpdateDiffTrack(tel, t0, FALSE);

/* Load the data into the configuration block */
        strcpy(difftrack[ntarget].cadname, strrchr(pcad->name, ':') + 1);

        difftrack[ntarget].frame.field = 'A';
        strncpy(difftrack[ntarget].frame.instring, pcad->a, MAX_STRING_SIZE);
        difftrack[ntarget].frame.val = frame;

        difftrack[ntarget].eqx.field = 'B';
        strncpy(difftrack[ntarget].eqx.instring, pcad->b, MAX_STRING_SIZE);
        difftrack[ntarget].eqx.val.year = eqx;
        difftrack[ntarget].eqx.val.type = type;

        difftrack[ntarget].t0.field = 'C';
        strncpy(difftrack[ntarget].t0.instring, pcad->c, MAX_STRING_SIZE);
        difftrack[ntarget].t0.val = t0;

        difftrack[ntarget].dtheta1.field = 'D';
        strncpy(difftrack[ntarget].dtheta1.instring, pcad->d, MAX_STRING_SIZE);
        difftrack[ntarget].dtheta1.val = dtheta1;

        difftrack[ntarget].dtheta2.field = 'E';
        strncpy(difftrack[ntarget].dtheta2.instring, pcad->e, MAX_STRING_SIZE);
        difftrack[ntarget].dtheta2.val = dtheta2;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetDiffTrack(tel, &difftrack[ntarget]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strncpy(pcad->vala, tcsCsFrame(difftrack[ntarget].frame.val), 
               MAX_STRING_SIZE);
        sprintf(pcad->valb, "%c%.14f", difftrack[ntarget].eqx.val.type,
                difftrack[ntarget].eqx.val.year);
        *(double *) pcad->valc = difftrack[ntarget].t0.val;
        *(double *) pcad->vald = difftrack[ntarget].dtheta1.val/S2R/86400.0;
        *(double *) pcad->vale = difftrack[ntarget].dtheta2.val/AS2R/86400.0;

        sprintf(message, "%s : dRA: %s dDec: %s", cadname, pcad->d, pcad->e);
        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADwavel
 *
 *   Purpose:
 *   Implements the various wavelength CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADwavel( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a effective wavelength: microns
 *
 *   Epics outputs:
 *
 *      vala -> Wavelength (Angstroms)
 *
 *   Function value:
 *   Return value from function e.g.
 *   (<)  status  (int)  Return status, 0 = OK
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
 *   none
 *
 *   Deficiencies:
 *   none
 *
 *-
 */
/* *INDENT-ON* */


long tcsCADwavel(struct cadRecord *pcad)
{
    int status;
    static struct WAVEL wavel[11];
    char* cadname;              /* Command name without prefix */
    int ntarget;                /* Index into target structure array */
    TELESCOPE tel;              /* Telescope name */
    double lwavel;               /* Effective wavelength (microns) */
    char message[256];

/* Telescope name from name of CAD */
    cadname = tcsCsCadName( pcad );
    if (!strcmp(cadname, "wavelMount")) {
        tel = MOUNT;
        ntarget = 0;
    } else if (!strcmp(cadname, "wavelSourceA")) {
        tel = SOURCE_A;
        ntarget = 1;
    } else if (!strcmp(cadname, "wavelSourceB")) {
        tel = SOURCE_B;
        ntarget = 2;
    } else if (!strcmp(cadname, "wavelSourceC")) {
        tel = SOURCE_C;
        ntarget = 3;
    } else if (!strcmp(cadname, "wavelPwfs1")) {
        tel = PWFS1;
        ntarget = 4;
    } else if (!strcmp(cadname, "wavelPwfs2")) {
        tel = PWFS2;
        ntarget = 5;
    } else if (!strcmp(cadname, "wavelOiwfs")) {
        tel = OIWFS;
        ntarget = 6;
    } else if (!strcmp(cadname, "wavelG1")) {
        tel = G1;
        ntarget = 7;
    } else if (!strcmp(cadname, "wavelG2")) {
        tel = G2;
        ntarget = 8;
    } else if (!strcmp(cadname, "wavelG3")) {
        tel = G3;
        ntarget = 9;
    } else if (!strcmp(cadname, "wavelG4")) {
        tel = G4;
        ntarget = 10;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
        return CAD_REJECT ;
    }

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set prefix for messages */
    tcsCsSetMessageN( pcad, cadname, ": ", (char*)NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* effective wavelength */
        if (tcsDcWl("wavelength: ", pcad->a, &lwavel, pcad)) break;

/* Load the data into the configuration block */
        strcpy(wavel[ntarget].cadname, strrchr(pcad->name, ':') + 1);

        wavel[ntarget].wavel.field = 'A';
        strncpy(wavel[ntarget].wavel.instring, pcad->a, MAX_STRING_SIZE);
        wavel[ntarget].wavel.val = lwavel;

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetWavel(tel, &wavel[ntarget]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        *(double *) pcad->vala = wavel[ntarget].wavel.val*10000.0;

        sprintf(message, "%s : Wavelength: %s", cadname, pcad->a);
        tcsLogMessage(message);
        break;

    case menuDirectiveMARK:
        break;

    case menuDirectiveSTOP:
        break;

    case menuDirectiveCLEAR:
        break;
    }
    return status;
}
epicsRegisterFunction(tcsCADtarget);
epicsRegisterFunction(tcsCADtrack);
epicsRegisterFunction(tcsCADoffsetPo);
epicsRegisterFunction(tcsInterlock);
epicsRegisterFunction(tcsCADdiffTr);
epicsRegisterFunction(tcsCADporigin);
epicsRegisterFunction(tcsCADoffset);
epicsRegisterFunction(tcsCADwavel);
