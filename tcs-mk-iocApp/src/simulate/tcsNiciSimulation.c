/*
   *   FILENAME
   *   tcsNiciSimulation.c
   *
   *   This module holds the routines that are used in the NICI Simulation 
   *
   *   FUNCTION NAME(S)
   *   tcsNiciTtf   - read data from sky simulator
   *
 */
/* *INDENT-OFF* */
/*
 * $Log: tcsNiciSimulation.c,v $
 * Revision 1.1  2006/04/25 14:05:10  cjm
 * Source code for NICI simulator
 *
 *
 */
/* *INDENT-ON* */


#include <string.h>
#include <epicsStdioRedirect.h>
#include <epicsExport.h>
#include <math.h>
#include <registryFunction.h>

#include <dbDefs.h>
#include <genSubRecord.h>
#include <menuCarstates.h>
#include <dbCommon.h>
#include <recSup.h>
#include <epicsPrint.h>

static int niciWfsMeasuring ;   /* TRUE when OIWFS is in use */


/*+
 *   Function name:
 *   tcsNiciTtf
 *
 *   Purpose:
 *   Simulated genSub record sending WFS data to the TCS.
 *   In this case the data is the time-averaged tip/tilt/focus data
 *
 *   Description:
 *   Simulation simply copies over the data sent to this record
 *   by the optics simulator.
 *   Note that output data array is declared static so that it retains 
 *   values between invocations. This ensures that we don't get
 *   spurious uninitialized data on the output links.
 *
 *   Invocation:
 *   tcsNiciTtf(pgsub)
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!)    pgsub     (struct genSubRecord *)  Pointer to pgsub structure
 *
 *   EPICS input fields :
 *
 *   a => Data from sky simulator 
 *   j => Flag to show if NICI WFS is taking data
 *
 *   EPICS output fields :
 * 
 *   valj => Array of 8 (double) data items for TCS
 *
 *   Function value:
 *   status 
 * 
 *-
 */
long tcsNiciTtf (struct genSubRecord *pgsub)
{
#define ARRMAX3 32

    static int first = TRUE;
    unsigned long outArraySize;      /* Number of array items in field J/VALJ */
    static double niciOidata[ARRMAX3];
    double temp ;

    niciWfsMeasuring = *(long *)pgsub->j;

/* Note how we scale and swap the data from the sky simulator. This assumes
*  that the real NICI will produce data with the same scaling etc. as the 
*  other OIWFS. This may turn out not to be the case
*/
    if (niciWfsMeasuring) {
      memcpy(niciOidata, pgsub->a, 8*sizeof(double));
      temp = niciOidata[2]*0.05;
      niciOidata[2] = -niciOidata[3]*0.05;
      niciOidata[3] = temp;
    } 

/* Output data array to TCS on VALJ */
    outArraySize = pgsub->novj;
    if (outArraySize > ARRMAX3) {
      if (first) errlogPrintf("tcsNiciTtf : invalid field VALJ array size\n");
    } 
    memcpy(pgsub->valj, niciOidata, outArraySize * sizeof(double));

    first = FALSE;
    return 0;

}
epicsRegisterFunction(tcsNiciTtf);
