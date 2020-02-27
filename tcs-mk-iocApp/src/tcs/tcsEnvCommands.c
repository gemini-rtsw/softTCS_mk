/*
*   FILENAME
*   tcsEnvCommands.c
*
*   FUNCTION NAME(S)
*   tcsCalcDewPoint     - calculates dew point from temp, press and humidity
*   tcsCADtemperature      - implements the command to set temperature
*   tcsCADhumidity         - implements the command to set humidity
*   tcsCADpressure         - implements the command to set pressure
*   tcsCADuseWS            - implements command useWS to select whether to use 
*                            Weather Server or not
*   tcsTempConv            - Converts deg C to deg K
*   tcsPressConv           - Checks range of input pressure
*   tcsHumidConv           - Converts % to RH
*   tcsLocalRemote         - Makes sure that local data is displayed as data used 
*                            by TCS when in local mode
*/
/* *INDENT-OFF* */
/*
 * $Log: tcsEnvCommands.c,v $
 * Revision 1.4  2002/02/19 17:19:28  ajf
 * Removed default settings for temperature, pressure and humidity for
 * the meteorological data. This fixes the problem of the TCS being
 * initialised in "remode" mode, yet having local values set. Pressing
 * "local" without entering any data no longer causes a TCS crash.
 *
 * Revision 1.3  2002/01/17 14:34:02  ajf
 * Changes to fix the crash of the TCS caused by selecting local on the
 * weather input screen and pressing apply. Also make sure the local data is
 * copied to the data used by the TCS when in local mode.
 *
 * Revision 1.2  2001/05/18 10:42:37  cjm
 * Replace mosub records and use new menuDirective constants
 *
 * Revision 1.1.1.1  1998/11/08 00:21:05  epics
 * Version 1-2 of the TCS as transferred from DRAL
 *
 * Revision 1.9  1998/02/10 15:39:52  pbt
 * Remove routine tcsEnvAlarm
 *
 * Revision 1.8  1998/01/12 16:23:14  tcs
 * Change CAD subroutine names to tcsCADxxxx
 *
 * Revision 1.7  1997/11/20 12:35:43  pbt
 * Add call to tcsConfigMarkComm for *all* CADs
 *
 * Revision 1.6  1997/10/02 14:24:43  tcs
 * Correct outputs of useWS cad
 *
 * Revision 1.5  1997/09/23 11:36:34  tcs
 * Add break to all cases
 *
 * Revision 1.4  1997/05/15 14:45:41  cjm
 * Mods to support alarm handler
 *
 * Revision 1.3  1997/05/13 10:58:25  cjm
 * Add calculation of dew point
 *
 * Revision 1.2  1997/03/05 09:36:57  tcs
 * tidy up cad outputs and messages
 *
 * Revision 1.1  1997/02/10 17:10:36  pbt
 * Recreate in tcs subdirectory
 *
 * Revision 1.7  1996/12/13 14:50:23  pbt
 * Various changes to CAD commands to conform to current conventions
 *
 * Revision 1.5  1996/12/13 10:07:50  tcs
 * rename tcs.h to tcsPointing.h
 *
 * Revision 1.4  1996/12/12 16:57:07  cjm
 * Rename tcsConfiguration.h to tcsConfig.h
 *
 * Revision 1.3  1996/10/29 17:04:42  pbt
 * Added routines for SIR record handling; amended range checking
 *
 * Revision 1.2  1996/10/28 17:33:00  pbt
 * Add subroutines for mosub conversion temp/humidity
 *
 * Revision 1.1  1996/10/24 14:33:55  pbt
 * Subroutines called by weather data input CAD records
 *
 *
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include  <string.h>
#include  <dbDefs.h>
#include  <cadRecord.h>
#include  <subRecord.h>
#include  <genSubRecord.h>
#include  <cad.h>
#include  <alarm.h>
#include  "tcsConstants.h"
#include  "tcsConfig.h"
#include  "tcsDecode.h"
#include  "tcsInterlocks.h"
#include  "slalib.h"
#include  "tcsCadSupport.h"


/* Symbols for remote/local weather server usage */
#define WS_REMOTE 0
#define WS_LOCAL  1

/* 
   Max/Min values for use with CAD record - cannot 
   use database values for CADs
*/
#define TEMP_MAX 50.0
#define TEMP_MIN -40.0
#define PRESS_MAX 1100.0
#define PRESS_MIN 300.0
#define HUMID_MAX 100.0
#define HUMID_MIN 0.0

#define ABS_ZERO 273.16

/* Ratio of gas constant divided by latent heat of vaporisation */

#define C1 0.0001846

/* Flag to show remote/local weather server usage */
static int WSinUse ;


long tcsLocalRemote( genSubRecord *pgsub )
{
  *(double *)pgsub->vala = *(double *)pgsub->a;
  *(double *)pgsub->valb = *(double *)pgsub->b;
  *(double *)pgsub->valc = *(double *)pgsub->c;
  return(0);
}


/*+
 *   Function name:
 *   tcsCalcDewPoint
 *
 *   Purpose:
 *   Calculate current dew point in degrees C
 *
 *   Description:
 *   This routine is used to calculate the current dew point when the 
 *   weather server is not available. It uses a simple formula that
 *   uses the temperature and humidity entered by the user.
 *   If the user specifies a humidity less than 0.01 then 0.01 is used
 *   instead to prevent the calculation blowing up.
 *
 *   Invocation:
 *   tcsCalcDewPoint(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)   pgsub    (struct genSubRecord *) Pointer to genSub structure
 *
 *   Epics inputs:
 *
 *   a => User input temperature (deg K)
 *   b => User input relative humidity (0 to 1.0) 
 *
 *   Epics outputs:
 *   
 *   vala => Calculated dew point (deg C) 
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *-
 */

long tcsCalcDewPoint (struct genSubRecord *pgsub)

{
  double rh ;            /* Relative humidity */
  double temperature ;   /* Input temperature (deg K) */
  double dewpoint ;      /* dew Point (deg C) */

/* Pull in input values */

  temperature = *(double *)pgsub->a;
  rh          = *(double *)pgsub->b;

  if( rh <= HUMID_MIN/100.0 ) rh = (HUMID_MIN+1.0)/100.0;
  if( rh >  HUMID_MAX/100.0 ) rh = HUMID_MAX/100.0;
  if( temperature < (TEMP_MIN + ABS_ZERO) ) temperature = TEMP_MIN + ABS_ZERO;
  if( temperature > (TEMP_MAX + ABS_ZERO) ) temperature = TEMP_MAX + ABS_ZERO;

  dewpoint = 1.0 / ( 1./temperature - C1 * log(rh)) - ABS_ZERO ;

  *(double *)pgsub->vala = dewpoint ;

  return 0;
}

/*+
 *   Function name:
 *   tcsCADtemperature
 *
 *   Purpose:
 *   Implements the TCS temperature command
 *
 *   Description:
 *   If the CAD directive is either PRESET or START then the input arguments
 *   are checked for validity. The only current EPICS input is the 
 *   temperature. If this is valid it is converted to deg K and output for
 *   Only if the directive is START is the input argument copied to the
 *   output argument after conversion.
 *
 *   Invocation:
 *    tcsCADtemperature (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs:
 *
 *   a => Temperature in deg Centigrade
 *
 *   Epics outputs:
 *
 *   vala => Temperature in deg K for slow loop 
 *   valb => Temperature in deg K for dew point calculation
 *   valc => Temperature in deg C for SAD
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *
 *   History:
 *   23-Oct-96 PBT  Initial version
 *   13-Dec-96 PBT  Changes to conform to 'standard' CAD command handling conventions
 *-
 */

long tcsCADtemperature (struct cadRecord *pcad) 
{
  static double temp;
  int status ;

/* Check for interlocks */
  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

/* Fetch name of cad for use in messages */
  tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

  status = CAD_ACCEPT ;
  switch (pcad->dir)
  {
    case menuDirectivePRESET :
    status = CAD_REJECT ;

/* Check that we are in local server mode */
    if (WSinUse != WS_LOCAL)
    {
      tcsCsAppendMessage(pcad,"mode not LOCAL") ;
      break;
    }

/* Try and convert the input argument string to a number */

    if (tcsDcDouble("", pcad->a, &temp, pcad)) 
    {
      tcsCsAppendMessage(pcad,"could not decode temperature") ;
      break;
    }

    if (temp < TEMP_MIN || temp > TEMP_MAX )
    {
      tcsCsAppendMessage(pcad,"value out of range") ;
      break;
    }
    if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART :
    *(double *)pcad->valc = temp;
/* Value OK, convert deg C to deg K */
    temp = temp + ABS_ZERO ;
    *(double *)pcad->vala = temp ;         /* Copy value to output field */
    *(double *)pcad->valb = temp;
    break;

  case menuDirectiveMARK :
    break ;

  case menuDirectiveSTOP:
    break ;

  case menuDirectiveCLEAR:
    break;

  default :
    break;

  }       /* End of switch statement */

return(status) ;

}


/*+
 *   Function name:
 *   tcsCADhumidity
 *
 *   Purpose:
 *   Implements the TCS humidity command
 *
 *   Description:
 *   If the CAD directive is either PRESET or START then the input arguments
 *   are checked for validity. The only current EPICS input is the 
 *   relative humidity expressed as a percentage.
 *   If valid the humidity is converted to a fractional value (0.0 -> 1.0)
 *   output for use by the slow control loop and the calculation of the 
 *   current dew point.
 *   Only if the directive is START is the input argument copied to the
 *   output argument after conversion.
 *
 *   Invocation:
 *    tcsCADhumidity (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Epics inputs:
 *
 *   a  => Humidity in % RH
 *
 *   Epics outputs:
 *
 *   vala => Humidity (0 to 1.0) for slow loop
 *   valb => Humidity (0 to 1.0) for dew point calculation
 *   valc => Humidity (0 to 100%) for SAD
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *
 *   History:
 *   23-Oct-96 PBT  Initial version
 *   13-Dec-96 PBT  Changes to conform to 'standard' CAD command handling conventions
 *-
 */

long tcsCADhumidity (struct cadRecord *pcad) 
{
  static double humid;
  int status ;

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

  status = CAD_ACCEPT ;

/* Fetch name of cad for use in messages */
  tcsCsSetMessageN( pcad, tcsCsCadName( pcad ), ": ", (char*)NULL);

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
    status = CAD_REJECT ;

/* Check that we are in local server mode */
    if (WSinUse != WS_LOCAL)
    {
      tcsCsAppendMessage(pcad,"Mode not LOCAL") ;
      break;
    }

/* Try and convert the input argument string to a number */

    if (tcsDcDouble("", pcad->a, &humid, pcad)) 
    {
      tcsCsAppendMessage(pcad,"Could not decode humidity");
      break;
    }

    if (humid < HUMID_MIN || humid > HUMID_MAX )
    {
      tcsCsAppendMessage(pcad,"value out of range") ;
      break;
    }
    if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART :
    *(double *)pcad->valc = humid;
/* Convert from % RH to fractional humidity */
     humid = humid * 0.01 ;
    *(double *)pcad->vala = humid ;         /* Copy value to output field */
    *(double *)pcad->valb = humid;
    break;

  case menuDirectiveMARK :
    break ;

  case menuDirectiveSTOP:
    break ;

  case menuDirectiveCLEAR:
    break;

  default :
    break;

 }       /* End of switch statement */

return(status) ;

}

/*+
 *   Function name:
 *   tcsCADpressure
 *
 *   Purpose:
 *   Implements the TCS pressure command
 *
 *   Description:
 *   If the CAD directive is either PRESET or START then the input arguments
 *   are checked for validity. The current EPICS input is:
 *
 *   a - Pressure in millibars
 * 
 *   If valid the pressure is output for use by the slow
 *   control loop.
 *
 *   Only if the directive is START is the input argument copied to the
 *   output argument.
 *
 *   Invocation:
 *    tcsCADpressure (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *
 *   History:
 *   23-Oct-96 PBT  Initial version
 *   13-Dec-96 PBT  Changes to conform to 'standard' CAD command handling conventions
 *-
 */

long tcsCADpressure (struct cadRecord *pcad) 
{
  static double press;
  int status ;

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

  status = CAD_ACCEPT ;

/* Fetch name of cad for use in messages */
  tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

  switch (pcad->dir)
  {
    case menuDirectivePRESET :
    status = CAD_REJECT ;

/* Check that we are in local server mode */
    if (WSinUse != WS_LOCAL)
    {
      tcsCsAppendMessage(pcad,"mode not LOCAL") ;
      break;
    }

/* Try and convert the input argument string to a number */

    if(tcsDcDouble("", pcad->a, &press, pcad))
    {
      tcsCsAppendMessage(pcad,"could not decode pressure") ;
      break;
    }

    if (press < PRESS_MIN || press > PRESS_MAX )
    {
      tcsCsAppendMessage(pcad,"value out of range") ;
      break;
    }
    if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART :
    *(double *)pcad->vala = press ;         /* Copy value to output field */
    *(double *)pcad->valb = press ;         /* Copy value to output field */
    *(double *)pcad->valc = press ;         /* Copy value to output field */
    break;

  case menuDirectiveMARK :
    break ;

  case menuDirectiveSTOP:
    break ;

  case menuDirectiveCLEAR:
    break;

  default :
    break;

 }       /* End of switch statement */

return(status) ;

}


/*+
 *   Function name:
 *   tcsCADuseWS
 *
 *   Purpose:
 *   Implements the TCS useWS CAD command to select from where
 *   TCS meteorological data is obtained.
 *
 *   Description:
 *   If the CAD directive is either PRESET or START then the input arguments
 *   are checked for validity. The current EPICS input is:
 *
 *   a - Where to get weather data :
 *        0 = WS_REMOTE (the external weather server)
 *        1 = WS_LOCAL  (use local CAD commands to supply values)
 * 
 *
 *   Only if the directive is START is the input argument copied to the
 *   output argument.
 *
 *   Invocation:
 *    tcsCADuseWS (pcad)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pcad     (struct cadRecord *) Pointer to CAD record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   History:
 *   23-Oct-96 PBT  Initial version
 *   13-Dec-96 PBT  Changes to conform to 'standard' CAD command handling conventions
 *-
 */

long tcsCADuseWS (struct cadRecord *pcad)
{
  static long wsloc;
  int status ;

  if (pcad->dir != menuDirectiveCLEAR)
    if (tcsInterlocked (pcad->mess)) return CAD_REJECT ;

  status = CAD_ACCEPT ;

/* Fetch name of cad for use in messages */
  tcsCsSetMessageN( pcad, tcsCsCadName(pcad), ": ", (char*)NULL);

  switch (pcad->dir)
  {
   case menuDirectivePRESET :
     status = CAD_REJECT ;

/* Try and convert the input argument string to a number */

    if (tcsDcLong("", pcad->a, &wsloc, pcad)) break;
    else if (wsloc != WS_REMOTE && wsloc != WS_LOCAL )
    {
       tcsCsAppendMessage(pcad,"value must be either REMOTE or LOCAL") ;
       break;
    }
    WSinUse = wsloc ; /* Save flag value for subsequent use */
    if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

    status = CAD_ACCEPT ;
    break ;

  case menuDirectiveSTART :

    *(double *)pcad->vala = (double) wsloc ;    /* Copy value to output field */
    *(double *)pcad->valb = (double) wsloc ;    /* Copy value to output field */
    *(double *)pcad->valc = (double) wsloc ;    /* Copy value to output field */
    break;

  case menuDirectiveMARK :
    break ;

  case menuDirectiveSTOP:
    break ;

  case menuDirectiveCLEAR:
    break;

  default :
    break;

 }       /* End of switch statement */

return(status) ;

}


/*+
 *   Function name:
 *   tcsTempConv
 *
 *   Purpose:
 *   Implements the conversion from deg C to Deg K for the
 *   data input from the Weather Server
 *
 *   Description:
 *   The EPICS input is:
 *
 *   a - Temperature in deg Centigrade
 *   b     =  Maximum allowed value
 *   c     =  Minimum allowed value
 *   d     =  Default value to adopt when input out-of-range
 *
 *   Output :
 *   
 *   vala = Temperature in degrees Kelvin
 *   valb = Temperature in degrees C 
 * 
 *   Invocation:
 *    When the associated genSub record is processed
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     (genSubRecord *) Pointer to genSub record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   History:
 *   28-Oct-96 PBT  Initial version
 *-
 */
long tcsTempConv ( genSubRecord *psub )
{
  double ctemp, ktemp ;
  int alarm = NO_ALARM ;

  ctemp = *(double *)psub->a ;
  if (ctemp > *(double *)psub->b || ctemp < *(double *)psub->c)
    {
     ctemp = *(double *)psub->d ;
     alarm = MINOR_ALARM ;
    }
  ktemp = ctemp + ABS_ZERO ;
  *(double *)psub->vala = ktemp ;
  *(double *)psub->valb = ctemp ;
  return(0) ;
}

/*+
 *   Function name:
 *   tcsPressConv
 *
 *   Purpose:
 *   Check value of input pressure to be in range
 *
 *   Description:
 *   The EPICS input is:
 *
 *   a     =  Pressure (from Weather Server) in millibars
 *   b     =  Maximum allowed value
 *   c     =  Minimum allowed value
 *   d     =  Default value to adopt when input out-of-range
 *
 *   Output :
 *   
 *   vala  = Same as input (except where out of range value is substituted
 *                          with default)
 *   valb  = Current pressure 
 * 
 *   Invocation:
 *    When the associated genSub record is processed
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     (genSubRecord *) Pointer to genSub record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   History:
 *   28-Oct-96 PBT  Initial version
 *-
 */
long tcsPressConv ( genSubRecord *psub )
{
  double press ;
  int alarm = NO_ALARM ;

  press = *(double *)psub->a ;
  if (press > *(double *)psub->b || press < *(double *)psub->c)
    {
     press = *(double *)psub->d ;
     alarm = MINOR_ALARM ;
    }
  *(double *)psub->vala = press ;
  *(double *)psub->valb = press ;
  return(0) ;

}

/*+
 *   Function name:
 *   tcsHumidConv
 *
 *   Purpose:
 *   Implements the conversion from % RH to fraction for
 *   data input from the Weather Server
 *
 *   Description:
 *   The EPICS input is:
 *
 *   a     =  Relative humidity as a % RH value
 *   b     =  Maximum allowed value
 *   c     =  Minimum allowed value
 *   d     =  Default value to adopt when input out-of-range
 *
 *   Output :
 *   
 *   vala  = Relative humidity as a fraction 0 -> 1 
 *   valb  = Relative Humidity as a percentage 
 * 
 *   Invocation:
 *    When the associated genSub record is processed
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    psub     (genSubRecord *) Pointer to genSub record structure
 *
 *   Function value:
 *   Return status
 * 
 *   Prior requirements:
 *   None
 *
 *   History:
 *   28-Oct-96 PBT  Initial version
 *-
 */
long tcsHumidConv ( genSubRecord *psub )
{
  double rhumid, fhumid ;
  int alarm = NO_ALARM ;

  rhumid = *(double *)psub->a ;
  if (rhumid > *(double *)psub->b || rhumid < *(double *)psub->c)
    {
     rhumid = *(double *)psub->d ;
     alarm  = MINOR_ALARM ;
    }
  fhumid = rhumid * 0.01 ;
  *(double *)psub->vala = fhumid ;
  *(double *)psub->valb = rhumid ;
  return(0) ;

}
epicsRegisterFunction(tcsCADtemperature);
epicsRegisterFunction(tcsCADpressure);
epicsRegisterFunction(tcsPressConv);
epicsRegisterFunction(tcsCalcDewPoint);
epicsRegisterFunction(tcsHumidConv);
epicsRegisterFunction(tcsLocalRemote);
epicsRegisterFunction(tcsTempConv);
epicsRegisterFunction(tcsCADhumidity);
epicsRegisterFunction(tcsCADuseWS);
