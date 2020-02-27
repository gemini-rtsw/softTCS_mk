/*
*   FILENAME
*   tcsEcsLib.h
*
*   DESCRIPTION
*   Header file for tcsEcsLib.c
*
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEcsLib.h,v $
 * Revision 1.3  2014/09/18 15:02:49  cjm
 * Add tcsecsEffectiveSlitPosns
 *
 * Revision 1.2  1998/11/16 18:38:10  cjm
 * Add extra parameter shtrMode to tcsEcsCheckParams
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.6  1998/03/23 14:37:10  cjm
 * Add prototypes for CalcPosns, LimitTime etc.
 *
 * Revision 1.5  1997/11/05 16:45:32  cjm
 * Add tcsEcsVignette routine
 *
 * Revision 1.4  1997/09/16 11:06:46  cjm
 * Added extra routines to support Basic mode
 *
 * Revision 1.3  1997/07/25 16:46:32  cjm
 * Bring into line with latest tcsEcsLib.c
 *
 * Revision 1.2  1997/07/23 13:30:01  cjm
 * Update for latest tcsEcsLib.c
 *
 * Revision 1.1  1997/07/15 13:41:33  cjm
 * Initial version
 *
 * Revision 1.1  1997/02/10 17:10:40  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.5  1996/10/24 16:11:10  tcs
 * Pointing origin offset commands
 *
 */
/* *INDENT-ON* */

#ifndef TCSECSLIBH 
#define TCSECSLIBH 

void tcsEcsCalcPosns (double startHA, double startDec, double endHA,
                    double elLim, double clat, double slat,
                    double *domeAz, double *elTopShtr, double *elBotShtr,
                    double *elTopVShtr, double *elBotVShtr);
void tcsEcsCalcSlit (double el, double ellimit, SOURCEMODE sourceMode ,
                     double *elTopShtr, double *elBotShtr,
                     double *elTopVShtr, double *elBotVShtr) ;

int tcsEcsCheckParams (ENCMODE encMode, SHUTTERMODE shtrMode, 
                       double slitHeight, double slitWidth,
                       double encRadius, double entranceAp, 
                       double minScatWidth, double fieldRadius,
                       char *mess);
int tcsEcsClearSlewFlag (void);
void tcsEcsEffectiveSlitPosns(double currtopShtr, double currBotShtr,
                              double *vTopShtr, double *vBotShtr) ;
void tcsEcsEnableDome (int state);
void tcsEcsEnableShtrs (int state);
void tcsEcsGetEnableFlags (int *enabledDome, int *enabledShtrs) ;
void tcsEcsGetEncMode (ENCMODE *encMode) ;
void tcsEcsGetIssueMoves (int *issueMoves) ;
void tcsEcsGetParamDefs (double *encRadius, double *slitWidth, 
                        double *entranceAp, double *minScatWidth,
                        double *minSlitHeight, double *fieldRadius);
void tcsEcsGetPosnDefs (double *domePos, double *botShtrPos, 
                        double *topShtrPos) ;
void tcsEcsGetShutLimits (double *minBot, double *maxBot, double *minTop,
                          double *maxTop) ;
void tcsEcsGetUserParams (ENCMODE *encMode, SHUTTERMODE *slitMode, 
                          double *slitHeight);
void tcsEcsHaDec2AzEl ( double ha, double dec, double clat, double slat ,
                        double *az, double *el, double *x, double *y,
                        double *z) ;
void tcsEcsLimitTime (double startHA, double startDec, double domeAz, 
                      double elTopVShtr, double elBotVShtr, double dHA,
                      double clat, double slat, ENCLIMIT *limitType,
                      double *timeToLimit);
void tcsEcsSetIssueMoves (int state);
void tcsEcsSetParamDefs (double encRadius, double slitWidth, 
                        double entranceAp, double minScatWidth,
                        double minSlitHeight, double fieldRadius);
int tcsEcsSetPosnDefs (double domePos, double botShtrPos, double topShtrPos,
                       char *mess);
void tcsEcsSetSlewFlag (void) ;
int tcsEcsSetShutLimits (double minBot, double maxBot, double minTop,
                          double maxTop, char *mess) ;
void tcsEcsSetUserParams (ENCMODE encMode, SHUTTERMODE slitMode,
                         double slitHeight);
void tcsEcsVignette (double az, double el, double domeAz, double elTopShtr,
                     double elBotShtr, double *vfrac) ;

#endif
