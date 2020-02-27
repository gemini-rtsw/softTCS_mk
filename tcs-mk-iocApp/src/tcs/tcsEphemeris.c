/*
*   FILENAME
*   tcsEphemeris.c
*
*   FUNCTION NAME(S)
*   interpPoly       - compute the interpolating polynomial
*   evalPoly         - evaluate the interpolating polynomial
*   tcsEphemerisDump - print ephemeris table to screen
*   tcsEphemerisFrame - fetch frame of the input ephemeris data
*   tcsEphemerisLoad - attempt to load an ephemeris file from the JPL service
*   tcsEphemerisTarget - retrive a target from a loaded ephemeris 
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEphemeris.c,v $
 * Revision 1.11  2016/05/09 16:08:20  gemvx
 * REL-2468: Added new target parameter for ephemeris file.
 *
 * Revision 1.10  2014/10/01 16:29:44  cjm
 * Add message if ephem debug file open fails
 *
 * Revision 1.9  2013/09/11 15:41:47  cjm
 * New interpoaltion for ephemeris files
 *
 * Revision 1.8  2012/06/01 15:54:55  cjm
 * Don'r force output to APPT but honour frame request
 *
 * Revision 1.7  2011/11/03 09:34:54  cjm
 * Comment out variables only used in debug
 *
 * Revision 1.6  2011/09/20 14:04:18  cjm
 * Rework of ephemeris code to fix bug with large rates
 *
 * Revision 1.5  2007/12/18 10:21:26  cjm
 * Handle ephemerides for new guiders
 *
 * Revision 1.4  2005/12/23 14:51:35  cjm
 * New routine tcsEphemerisFrame and return track rates
 *
 * Revision 1.3  2005/12/15 09:41:41  cjm
 * Let user choose frame of returned target position
 *
 * Revision 1.2  2005/10/21 15:38:09  cjm
 * Return health from tcsEphemerisTarget
 *
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <string.h>
#include <math.h>
#include "tcsConstants.h"
#include "slalib.h"
#include "slamac.h"
#include "timeLib.h"
#include "tcsEphemeris.h"
#include "astLib.h"
#include "tcsPointing.h"

/* Constants to define where certain fields start in the ephemeris file */
#define JDSTART 19 
#define RASTART 40
#define DECSTART 54
#define DRASTART 69 

#define MJDOFF 2400000.5

/* Allow for loading 1440 records i.e. 24 hours worth at one per minute */
#define MAXRECORDS 1440 
static int nrecords[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static FRAMETYPE ephframe[11] ={APPT, APPT, APPT, APPT, APPT, APPT, APPT,
                                APPT, APPT, APPT, APPT};

static int ephemdebug = 1 ;
static FILE *dbgephemfp = NULL ;

struct eitem {
   double mjd;           /* Modified Julian date of the current target */
   double ra;           /* RA (rads) */
   double dec;           /* Dec (rads) */
   double dra;          /* dRA/dt*cos(dec)  in arcsecs/hr */
   double ddec;          /* dDec/dt in arcsec/hr */
} ;

/* Set up for all 11 virtual telescopes. Although in practice we only
*  expect to have to handle sourceA, pwfs1, pwfs2,  oiwfs and the 
*  guiders g1 to g4.
*/
static struct eitem etable[11][MAXRECORDS];

/*+
 *   Function name:
 *   interpPoly 
 *
 *   Purpose:
 *   Generate an interpolating polynomial for a set of data points 
 *
 *   Description:
 *   The polynomial coefficients produced are in the Newtonian form
 *   Note that the input array of function values is modified and
 *   is returned as the array of coeffcients
 *
 *   Invocation:
 *   interpPoly(n, f, x, coeffs)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    n   (int)  Number of samples over which to interpolate 
 *      (>)    x   (double *) Values at which function is given
 *      (!)    f   (double *) On input function, on output coeffs 
 *
 *   Function value:
 *      None
 *-
 */
void interpPoly(int n, double *x, double *f)
{
  int k ;
  int i ;

  for ( k = 1; k < n ; k++ ) {
    for (i = 0; i < n - k ; i++) {
      f[i] = (f[i+1] - f[i]) / (x[i+k] - x[i]);
    }
  }

}

/*+
 *   Function name:
 *   evalPoly 
 *
 *   Purpose:
 *   Evaluate an interpolating polynomial for a given value  
 *
 *   Description:
 *   Uses nested multiplication for efficiency assuming the coefficients
 *   are in the Newtonian form
 *
 *   Invocation:
 *   f = evalPoly(n, x, c, z)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    n   (int)  Number of  polynomial coefficients 
 *      (>)    x   (double *) Values at which function is given
 *      (>)    c   (double *) Polynomial coeffcients 
 *      (>)    z   (double) Value at which polynomial is to be evaluated
 *
 *   Function value:
 *      (<)    x  (double) Value of polynomial at the given value 
 *-
 */
double evalPoly(int n, double *x, double *c, double z)
{
  double val ;
  int i ;

  val = c[0];
  for (i = 0; i  < (n - 1); i++) {
    val = c[i+1] + val * (z - x[i+1]);
  }

  return val ;
}

/*+
 *   Function name:
 *   tcsEphemerisFrame
 *
 *   Purpose:
 *   Returns the frame of the original input data 
 *
 *   Description:
 *   Simply returns the stored value of the frame in which the JPL Horizons
 *   data was supplied for a particular telescope target.
 *
 *   Invocation:
 *   tcsEphemerisFrame(tel, &frame)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  tel      TELESCOPE  Virtual telescope
 *      (<)  frame    FRAMETYPE  Frame of the ephemeris data
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *   Fails silently if tel is out of range
 * 
 *-
 */

void tcsEphemerisFrame(TELESCOPE tel, FRAMETYPE *frame)
{
  if (tel > G4 || tel < MOUNT) {
    *frame = APPT;
  } else {
    *frame = ephframe[tel];
  }
}

/*+
 *   Function name:
 *   tcsEphemerisLoad
 *
 *   Purpose:
 *   Load of file of ephemeris data into memory
 *
 *   Description:
 *   This routine first checks if the filename it has been given can be opened.
 *   If so, it scans it until it finds the entry $$SOE. Using the current
 *   time it then locates the first entry that is later than the current time.
 *   All entries after this are loaded into memory up to a limit of 1440
 *   records or until the $$EOE line is read.
 *
 *   Invocation:
 *   status = tcsEphemerisLoad(filename, telescope, tnow, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)  filename  (char *)  Filename to be loaded
 *      (>)  tel       (enum)    TELESCOPE
 *      (>)  tnow      (double)  Current time UTC (MJD)
 *      (<)  mess      (char *)  Error message if status is non-zero
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   Any known problems with the function
 *
 *-
 */

int tcsEphemerisLoad(char *filename, TELESCOPE tel, double tnow, char *mess)
{
  int status = 0;
  FILE *fp ;
  char line[120];
  int notfound ;
  double jd ;                   /* Julian Date read from file */
  double mjd ;                  /* Modified Julian Date corresponding to jd */
  double ra ;                   /* RA in rads read from file */
  double dec ;                  /* Dec in rads read from file */
  double dra ;                  /* dra/dt as read from file */
  double ddec ;                 /* ddec/dt as read from file */
  int nitems ;                  /* No. of valid items read from line */
  int sstat ;                   /* Return status from slalib calls */
  int nind ;                    /* Index into char array */
  int firstline ;               /* Flag to show first line of file */
  struct eitem lastitem = { 0, 0, 0, 0, 0 };        /* Last data set from file */

  strcpy(mess,"");
  mjd = 0.0;

/* First try and open the file */
  if ((fp = fopen(filename,"r")) == NULL) {
    strcpy (mess, "Failed to open ephemeris file");
    status = -1;
  } else {

/* First pass, read the file to see if a header can be found that
*  specifies the frame of the following coordinates. If not then
*  we'll assume apparent as that is the default for JPL output.
*/
    notfound = 1;
    while (notfound) {
      if (fgets (line, 120, fp) != NULL) {
        if (!strncmp(line, " Date", 5)) {
/* Extract the coordinate frame. Default to APPT */
          if (strstr(line, "ICRF")) {
            ephframe[tel] = FK5;
          } else if (strstr(line, "FK4")) {
            ephframe[tel] = FK4;
          } else {
            ephframe[tel] = APPT;
          }
          notfound = 0;
        }
      } else {
        rewind(fp);
	notfound = 0;
      }
    }

/* Search through the file until the line starting $$SOE is found */
    notfound = 1;
    while (notfound) {
      if (fgets (line, 120, fp) != NULL) {
        if (!strncmp(line, "$$SOE", 5)) notfound = 0;
      } else {
        strcpy(mess, "Invalid file - no $$SOE");
        status = -1 ;
        fclose(fp) ;
        return status ;
      }
    } 

/* Now read and count the lines up to the $$EOE characters. Don't flag
 * an error if we get to the end of the file without finding a $$EOE.
 * This allows a bit more flexibility in the format. The important
 * thing is to find some valid records.
 */
       
    firstline = 1;
    notfound = 1 ;
    nrecords[tel] = 0;
    while (notfound && (nrecords[tel] < MAXRECORDS)) {
      if (fgets (line, 120, fp) != NULL) {

/* Check the validity of the line and whether we have found the terminating 
 * characters
 */
        if (!strncmp(line, "$$EOE", 5)) {
          notfound = 0;
        } else {

/* First thing to read is the JD which we store as an MJD */
         nitems = sscanf(line+JDSTART, "%lf", &jd);                   
         if (nitems == EOF || nitems == 0) {
           strcpy(mess, "Error reading Julian date");
           status = -1 ;
           fclose(fp);
           return status ;
         } else {
           mjd = jd - MJDOFF;
         } 

/* Now convert the RA */
         nind = 1;
         slaDafin(line+RASTART, &nind, &ra, &sstat);
         if (sstat) {
           if (sstat == 1) {
             strcpy(mess, "Missing RA fields");
           } else if (sstat == -1) {
             strcpy( mess, "Bad RA hours field");
           } else if (sstat == -2) {
             strcpy(mess, "Bad RA mins field");
           } else {
             strcpy(mess, "Bad RA secs field");
           }
           fclose(fp);
           status = -1;
           return status ;
         } else {
           ra *= 15.0;
         }

/* Now convert the Dec */
         nind = 1;
         slaDafin(line+DECSTART, &nind, &dec, &sstat);
         if (sstat) {
           if (sstat == 1) {
             strcpy(mess, "Missing Dec fields");
           } else if (sstat == -1) {
             strcpy( mess, "Bad Dec degs. field");
           } else if (sstat == -2) {
             strcpy(mess, "Bad Dec mins field");
           } else {
             strcpy(mess, "Bad Dec secs field");
           }
           fclose(fp);
           status = -1;
           return status ;
         }

/* Finally read the differential rates */
         nitems = sscanf(line+DRASTART, "%lf %lf", &dra, &ddec);         
         if (nitems == EOF || nitems == 0) {
           strcpy(mess, "Error reading diff rates");
           status = -1 ;
           fclose(fp);
           return status ;
         } 

/* Check that the current time is not before the first file entry.
*  If it is we can't slew the telescope there as we'd have to extrapolate
*  the data backwards in time. 
*/

          if (firstline) {
            if (tnow < mjd) {
              strcpy(mess, "No data for current time");
              status = -1;
              fclose(fp);
              return status ;
            }
            firstline = 0;
          }


/* If the file entry is for a time before the current time then there is no
*  point in storing the data. 
*  Discarding all the old data also means we can feed the TCS with a file
*  for a whole semester although the file read time might then be excessive.
*/
 
          if (mjd > tnow) {         
            if (nrecords[tel] == 0) {
              etable[tel][0] = lastitem ;
              nrecords[tel]++ ;
            }
            etable[tel][nrecords[tel]].mjd = mjd;
            etable[tel][nrecords[tel]].ra  = ra ;
            etable[tel][nrecords[tel]].dec = dec ;
            etable[tel][nrecords[tel]].dra  = dra ;
            etable[tel][nrecords[tel]].ddec = ddec ;
            nrecords[tel]++ ;
          } else {

/* Save the last line until we have some valid data. Otherwise we'll
*  find we have already read past the data we need when we find our 
*  first valid entry 
*/
            if (nrecords[tel] == 0 ) {
              lastitem.mjd = mjd;
              lastitem.ra  = ra;
              lastitem.dec = dec ;
              lastitem.dra = dra;
              lastitem.ddec = ddec;
            }
          }
        }
      } else {                             /* Null read from file */
        notfound = 0;
      }
    }                               /* End of main while clause */
    fclose(fp);
/* We've finished reading the file so check that we've got at least some
*  records. If the last entry in the file was for a time already earlier
*  than the present or if we've only got one valid entry then we can't 
*  interpolate.
*/
    if (nrecords[tel] < 2 || mjd < tnow) {
      strcpy(mess, "No relevant data in file");
      printf("nrecords = %d, tnow, mjd = %16.8f %16.8f\n", nrecords[tel],
              tnow, mjd);
      nrecords[tel] = 0 ;
      status = -1;
    } 
  }
  return status;
}


/*+
 *   Function name:
 *   tcsEphemerisTarget
 *
 *   Purpose:
 *   Return the current target position from a loaded ephemeris
 *
 *   Description:
 *   The ephemeris as loaded in memory is searched for appropriate records.
 *   The data is then used to interpolate the coordinates to get the
 *   position at time tnow.
 *
 *   Invocation:
 *   status = tcsEphemerisTarget(tnow, tel, frame, &ra, &dec, &dra, &ddec,
 *                               health, mess)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)   tnow    (double)   time as MJD, UTC time scale 
 *      (>)   tel     (enum)     TELESCOPE
 *      (>)   frame   (enum)     FRAMETYPE of the returned coords
 *      (<)   ra      (double *) RA in rads
 *      (<)   dec     (double *) Dec in rads
 *      (<)   dra     (double *) Tabulated RA track rate rads/day 
 *      (<)   ddec    (double *) Tabulated Dec track rate rads/day 
 *      (<)   health  (char *)   Health string
 *      (<)   mess    (char *)   Error message if status is non-zero
 *
 *   Function value:
 *   (<)  status  (int)  Return status, 0 = OK
 * 
 *   Deficiencies:
 *   There is a small uncertainty in the JPL data in that the RA rates
 *   are mutiplied by cos(dec) but is the dec apparent, FK5 or FK4? The
 *   assumption here is that it is the same as frame of the position
 *   data. The reason for this choice is that it is known that the TSD
 *   uses this frame when displaying the data.
 *
 *-
 */

int tcsEphemerisTarget(double tnow, TELESCOPE tel, FRAMETYPE frame,
                       double *ra, double *dec, double *dra, double *ddec,
                       char *health, char *mess)
{

  int status = 0;
  int ind  ;               /* Index of the located record */
  int found ;              /* Flag for when a record is found */
  int i ;
  double aoprms[15] ;      /* Observed to apparent parameters */
  struct PMPXRV pmotion ;  /* Not actually filled in */
  struct TELP telp ;     
  struct EPOCH equinox ;  
  struct EPOCH epoch ;
  double tt ;              /* Time on tt time scale */
/*
  int dechmsf[4], rahmsf[4] ;
  char decsign, rasign ;
*/
  double ranow, decnow ;   /* RA & Dec at tnow interpolated from tables */
  double dranow, ddecnow ; /* Diff. rates now interpolated from tables */ 
  double cra[3], cdec[3];  /* Interpolation coefficients */
  double mjd[3] ;          /* Times of samples */
  
  strcpy(mess,"");
  strcpy(health, "GOOD");
  *ra = 0.0;
  *dec = 0.0;
  *dra = 0.0 ;
  *ddec = 0.0;
  ind = 0;
  found = 0 ;
  status = 0;
  pmotion.pm = 0 ;
  pmotion.pmRA = 0.0 ;
  pmotion.pmDec = 0.0;
  pmotion.px = 0.0 ;
  pmotion.rv = 0.0 ;

/*
* Check we have at least three records. This is the minimum number if
* we are going to use parabolic interpolation
*/
  if (nrecords[tel] < 3) {
    strcpy(mess, "No ephemeris available");
    strcpy(health, "BAD");
    status = -1 ;
  } else {

/* Search through ephemeris for the entries either side of the current time
*  then interpolate to get the acceleration. Finally compute the current
*  target at tnow
*  If there is a valid entry found we need to make sure the index is large
*  enough as we are going to access elements at ind, ind+1 and ind+2
*/
    for (i = 0; i < nrecords[tel] - 2; i++) {
      if (tnow > etable[tel][i].mjd && tnow < etable[tel][i+1].mjd) {
        ind = i ;
        found = 1 ;
/*
        slaDr2tf(4, etable[tel][i].ra, &rasign, rahmsf);
        slaDr2af(3, etable[tel][i].dec, &decsign, dechmsf);
        printf("%d %18.9f %02d %02d %02d.%04d %c%02d %02d %02d.%03d %10.5f %10.4f\n",
               i, 
               etable[tel][i].mjd, rahmsf[0], rahmsf[1], rahmsf[2], rahmsf[3],
               decsign, dechmsf[0], dechmsf[1], dechmsf[2], dechmsf[3],
               etable[tel][i].dra, etable[tel][i].ddec); 
*/
        break ;
      }
    }

    if (!found) {
      strcpy (mess, "No relevant data in ephemeris");
      strcpy (health, "BAD");
      status = -1;
    } else {
      for (i = 0; i < 3; i++) {
        cra[i]  = etable[tel][ind - 1 + i].ra ;
        cdec[i] = etable[tel][ind - 1 + i].dec;
        mjd[i]  = etable[tel][ind - 1 + i].mjd; 
      }
      interpPoly(3, mjd, cra);
      interpPoly(3, mjd, cdec);

/* Compute positions and velocities at tnow */
      ranow = evalPoly(3, mjd, cra, tnow);
      decnow = evalPoly(3, mjd, cdec, tnow);

/* Evaluate velocity, rads/day. Note this is only exact if parabolic
*  interpolation has been used.
*/
      dranow  = cra[1] + cra[0] * (2.0 * tnow - mjd[2] - mjd[1]);
      ddecnow = cdec[1] + cdec[0] * (2.0 * tnow - mjd[2] - mjd[1]);

/*
      slaDr2tf(4, ranow, &rasign, rahmsf);
      slaDr2af(3, decnow, &decsign, dechmsf);
      printf ("%18.9f %02d %02d %02d.%04d %c%02d %02d %02d.%03d %10.5f %10.4f\n",
              tnow, rahmsf[0], rahmsf[1], rahmsf[2], rahmsf[3],
              decsign, dechmsf[0], dechmsf[1], dechmsf[2], dechmsf[3],
              dranow*cos(decnow)/(24.0 * DAS2R), ddecnow/(24.0 *DAS2R));
*/
      
      tt = tnow + slaDtt(tnow)/864000.0 ;
      tcsGetAoprms(aoprms);
      tcsGetTelParams(SOURCE_A, &telp);
      if (ephframe[tel] == FK5) {
        equinox.year = 2000.0;
        equinox.type = 'J';
        epoch.year = 2000.0 ;
        epoch.type = 'J';
      } else if (ephframe[tel] == FK4) {
        equinox.year = 1950.0;
        equinox.type = 'B';
        epoch.year = 1950.0 ;
        epoch.type = 'B';
      } else {
/* The ephemeris frame is apparent so we don't care what the equinox and
*  epoch are
*/
        equinox.year = 2000.0;
        equinox.type = 'J';
        epoch.year = 2000.0 ;
        epoch.type = 'J';
      }
      astCocoR (ranow, decnow, pmotion, dranow/86400.0, ddecnow/86400.0,
                ephframe[tel], equinox, epoch, frame, equinox, tt, aoprms, telp,
                ra, dec, dra, ddec);
      *dra *= 86400.0;
      *ddec *= 86400.0;
      if (ind == nrecords[tel] - 2) {
        strcpy(health, "WARNING");
        strcpy(mess, "Last entry in ephemeris file");
      }
      if (dbgephemfp) {
        fprintf(dbgephemfp, "%18.10f %14.10f %14.10f %12.6f %12.6f %5d %18.10f %18.10f %18.10f %14.10f %14.10f %14.10f %14.10f %14.10f %14.10f %12.6f %12.6f\n",
                tnow, ranow * DR2D, decnow * DR2D, dranow * DR2AS / 24.0, ddecnow * DR2AS / 24.0,
                ind, etable[tel][ind-1].mjd, etable[tel][ind].mjd, etable[tel][ind+1].mjd,
                etable[tel][ind-1].ra*DR2D, etable[tel][ind].ra*DR2D, etable[tel][ind+1].ra*DR2D,
                etable[tel][ind-1].dec*DR2D, etable[tel][ind].dec*DR2D, etable[tel][ind+1].dec*DR2D,
                etable[tel][ind].dra, etable[tel][ind].ddec);
      }
    }
    
  }

  return status ;
}

void tcsEphemerisOpen() 
{
      if (ephemdebug == 1 ) {
        if (!dbgephemfp) {
          if ((dbgephemfp = fopen("ephem.dbg", "w")) == NULL) {
            printf("Failed to open ephem.dbg\n");
          }
        }
      }

}

void tcsEphemerisClose() 
{
  if (dbgephemfp) {
    fclose(dbgephemfp) ;
  }

}
/*+
 *   Function name:
 *   tcsEphemerisDump
 *
 *   Purpose:
 *   Print current contents of ephemeris table to the screen
 *
 *   Description:
 *   For each entry, the data is formatted back to how it was read by
 *   the JPL Horizons file and printed to the screen
 *
 *   Invocation:
 *   tcsEphemerisDump()
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (>)    tel   (enum)   TELESCOPE
 *
 *   Function value:
 *      None
 * 
 *-
 */

void tcsEphemerisDump(TELESCOPE tel)
{
   int i ;        
   int iy, im, id ;            /* Year, month and day numbers */
   double fd ;                 /* Fraction of a day */
   int jstat ;                 /* Status from slalib */
   int ih, imin ;              /* Hour and minute numbers */
   float secs ;
   int ra[4] ;                 /* Target RA */
   int dec[4] ;                /* Target Dec */
   char rsign ;
   char dsign ;
   double tmjd ;               /* Time now (MJD) */
   double rarad, decrad ;
   int status ;                /* Return status */
   char mess[80];              /* Return message */
   char hlth[8] ;              /* Ephemeris health */
   double dra, ddec ;          /* Track rates (not used here) */

   char *months[] = {"Jan", "feb", "Mar", "Apr", "May", "Jun", 
                     "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
   char *telnames[] ={"Mount", "SourceA", "SourceB", "SourceC", "PWFS1",
                      "PWFS2", "OIWFS", "G1", "G2", "G3", "G4"};

   if (tel > G4 || tel < MOUNT) {
     printf ("\nValid indices are from 0 to 10\n");
     return ;
   }
   if (nrecords[tel] == 0) {
     printf("\nThere is no ephemeris data currently loaded for %s\n",
            telnames[tel]);
   } else {
     printf("\nNo. of records = %d for %s \n\n", nrecords[tel], telnames[tel]);
     if (ephframe[tel] == FK5) {
       printf("         Date          RA(FK5)       Dec(FK5)    dRA/dt ddec/dt\n");
     } else if (ephframe[tel] == FK4) {
       printf("         Date          RA(FK4)       Dec(FK4)    dRA/dt ddec/dt\n");
     } else {
       printf("         Date          RA(Appt)     Dec(Appt)    dRA/dt ddec/dt\n");
     }
     for (i = 0; i < nrecords[tel]; i++) {
       slaDjcl(etable[tel][i].mjd, &iy, &im, &id, &fd, &jstat);
       ih = fd * 24.0 ;
       imin = (fd * 24.0 - ih)*60.0;
       if (((fd *24.0 - ih)*60.0 - imin) >= 0.5) imin++ ;
       slaDr2tf (4, etable[tel][i].ra, &rsign, ra);
       slaDr2af (3, etable[tel][i].dec, &dsign, dec); 
       printf ("%4d-%s-%02d %02d:%02d  %02d %02d %02d.%04d  %c%02d %02d %02d.%03d %6.2f %6.2f\n", 
               iy, months[im-1], id, ih, imin, 
               ra[0], ra[1], ra[2], ra[3], 
               dsign, dec[0], dec[1], dec[2], dec[3],
               etable[tel][i].dra, etable[tel][i].ddec);
     }
     printf ("\n");

/* Fetch the current time and perform an interpolation to make sure we get
*  a sensible result
*/
     timeNowD(UTC, &tmjd) ;
     status = tcsEphemerisTarget(tmjd, tel, FK5, &rarad, &decrad, &dra, &ddec,
                                 hlth, mess);
     if (status) {
       printf ("Failed to interpolate ephemeris table\n");
       printf ("%s\n", mess) ;
     } else {
       if (!strncmp(hlth, "WARNING", 7)) {
         printf ("Warning - %s\n\n", mess);
       }
       slaDjcl(tmjd, &iy, &im, &id, &fd, &jstat);
       ih = fd * 24.0 ;
       imin = (fd * 24.0 - ih)*60.0;
       secs = ((fd * 24.0 - ih)*60.0 - imin)*60.0 ;
       slaDr2tf (4, rarad, &rsign, ra);
       slaDr2af (3, decrad, &dsign, dec); 
       printf("\n");
       printf("Current time and target position (FK5)\n");
       printf ("%4d-%s-%02d %02d:%02d:%03.1f %02d %02d %02d.%04d  %c%02d %02d %02d.%03d \n", 
               iy, months[im-1], id, ih, imin, secs,
               ra[0], ra[1], ra[2], ra[3], 
               dsign, dec[0], dec[1], dec[2], dec[3]);

     }
   }

}
