/*
*   FILENAME
*   Put file name here
*
*   DESCRIPTION
*   Short description of what the file is a header for
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEphemeris.h,v $
 * Revision 1.4  2005/12/23 14:45:09  cjm
 * Add tcsEphemerisFrame
 *
 * Revision 1.3  2005/12/14 16:44:20  cjm
 * Add frame to tcsEphemerisTarget call
 *
 * Revision 1.2  2005/10/21 14:24:59  cjm
 * Add extra parameter to tcsEphemerisTarget
 *
 * Revision 1.1  2005/10/20 15:08:23  cjm
 * Header file for ephemeris library
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSEPHEMERIS_H 
#define TCSEPHEMERIS_H 

void tcsEphemerisDump(TELESCOPE tel);
void tcsEphemerisFrame(TELESCOPE tel, FRAMETYPE *frame);
int tcsEphemerisLoad(char *filename, TELESCOPE tel, double tnow, char *mess);
int tcsEphemerisTarget(double tnow, TELESCOPE tel, FRAMETYPE frame, 
                       double *ra, double *dec, double *dra, double *ddec,
                       char *health, char *mess);

#endif
