/*
*   FILENAME
*   tcsGuide.h
*
*   DESCRIPTION
*   Definitions of the functions in tcsGuide.c that are callable from
*   other modules
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsGuide.h,v $
 * Revision 1.5  2010/11/29 14:09:48  cjm
 * Add new init, move, park routines for ODGW
 *
 * Revision 1.4  2010/05/27 07:32:28  cjm
 * Add tcsGuideSetOdgwFollowState
 *
 * Revision 1.3  2010/02/26 18:50:41  gemvx
 * Modify parameters to tcsSetupODGW
 *
 * Revision 1.2  2009/12/01 13:46:05  cjm
 * Add routines supporting ODGW
 *
 * Revision 1.1  2009/10/30 17:16:19  cjm
 * definitions of public routines from tcsGuide.c
 *
 *
 */
/* *INDENT-ON* */

#ifndef TCSGUIDE_H 
#define TCSGUIDE_H 

double tcsGetRotCorr(void);
void tcsGuideInitOdgwPosns(int window, double xc, double yc);
void tcsGuideSetODGWCenter(int window, double xc, double yc);
void tcsSetODGWCorner(int window, double xc, double yc);
void tcsSetODGWGuidePeriod(int window, double period);
void tcsSetODGWGuiding(int window, int guiding);
int  tcsGuideAnyOdgwFollowing(void);
int  tcsGuideGetODGWFollowing(int window);
void tcsGuideSetOdgwFollowState(int window, int following);
void tcsSetupODGW (int windowSize, int saveIndex, int guiderIndex, 
		   int displayIndex, double displayRate);
void tcsGuideMoveOdgw(int window, long ix, long iy) ;
void tcsGuideParkOdgw(int window) ;
void tcsSetRotatorGuideMode(int state);
void tcsZeroRotCorr(void);

#endif
