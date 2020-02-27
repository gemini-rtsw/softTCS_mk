/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsOffsetCad.c
*
*   FUNCTION NAME(S)
*   tcsCADabsorbOffset - CAD processing routine for the absorbOffset CAD
*   tcsCADabsorbPoOffset - CAD processing routine for the absorbPoOffset CAD
*   tcsCADclearOffset - CAD processing routine for the clearOffset CAD
*   tcsCADclearPoOffset - CAD processing routine for the clearPoOffset CAD
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */

#include <epicsStdioRedirect.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <cad.h>
#include <cadRecord.h>
#include <subRecord.h>
#include "tcsConstants.h"
#include "tcsDecode.h"
#include "tcsConfig.h"
#include "tcsInterlocks.h"
#include "tcsCadSupport.h"
#include "tcsPointing.h"
#include "tcsLogSupport.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADabsorbOffset
 *
 *   Purpose:
 *   CAD processing routine for the absorbOffset CAD record.
 *
 *   Description:
 *   Calls the kernel absorb offset routine
 *
 *   Invocation:
 *   tcsCADabsorbOffset( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a Virtual telescopes
 *      b Offsets
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   Prior requirements:
 *   none
 *
 *
 *-
*/
/* *INDENT-ON* */

long tcsCADabsorbOffset(struct cadRecord *pcad)
{
    int status;
    char *telnames[] = {
        "MOUNT",
        "SOURCE A", "SOURCE B", "SOURCE C",
        "SOURCE", "PWFS1", "PWFS2", "OIWFS",
        "ALL", "G1", "G2", "G3", "G4", NULL
    };
    char *offnames[] = { "ALL", NULL };
    static long ioff;
    static TELESCOPE_M tel;
    int name;
    char message[256];

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Decode virtual telescope specification */
        if (tcsDcString(telnames, "telescope name: ", pcad->a, &name, pcad))
            break;

/* Construct virtual telescope mask */
        switch (name) {
        case 0: tel = MOUNT_M; break;
        case 1: tel = SOURCE_A_M; break;
        case 2: tel = SOURCE_B_M; break;
        case 3: tel = SOURCE_C_M; break;
        case 4: tel = SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        case 5: tel = PWFS1_M; break;
        case 6: tel = PWFS2_M; break;
        case 7: tel = OIWFS_M; break;
        case 8: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M |
                       PWFS1_M | PWFS2_M | OIWFS_M |
                      G1_M | G2_M | G3_M | G4_M; break;
        case 9: tel = G1_M; break;
        case 10: tel = G2_M; break;
        case 11: tel = G3_M; break;
        case 12: tel = G4_M; break;
        }

/* Decode the offset number */
        if (tcsDcString(offnames, "offset: ", pcad->b, &name, pcad)) {

/* Reset message prefix */
           tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

/* Input was not "all" so try decoding as an integer */
           if (tcsDcLong("offset: ", pcad->b, &ioff, pcad)) break;

/* Offset must be in the range 0-2 */
           if ( ioff < 0 || ioff > 2 ) {
               tcsCsAppendMessage(pcad, "offset: outside 0-2");
               break;
           }

/* If 1 or 2, check that the the mount isn't included */
           if (ioff != 0) {
              if ( (tel & MOUNT) != 0 ) {
                  tcsCsAppendMessage(pcad,
                      "offset: must be zero for Mount");
                  break;
              }
           }
        } else {

/* Input was "all" */
            ioff = -1;
        }

        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:
        *(long *) pcad->vala = tel;
        *(long *) pcad->valb = ioff;
        sprintf(message, "%s : Name: %s offset: %s", tcsCsCadName(pcad), 
                                                            pcad->a, pcad->b);
        tcsLogMessage(message);

/* Call kernel routine */
        tcsAbsorbOffsets(tel, ioff);
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
 *   tcsCADclearOffset
 *
 *   Purpose:
 *   CAD processing routine for the clearOffset CAD record.
 *
 *   Description:
 *   Calls the kernel set offset routine
 *
 *   Invocation:
 *   tcsCADclearOffset( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a Virtual telescopes
 *      b Offsets
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
 *   Any known problems with the function
 *
 *-
*/
/* *INDENT-ON* */

long tcsCADclearOffset(struct cadRecord *pcad)
{
    int status;
    char *telnames[] = {
        "MOUNT",
        "SOURCE A", "SOURCE B", "SOURCE C",
        "SOURCE", "PWFS1", "PWFS2", "OIWFS",
        "ALL", "G1", "G2", "G3", "G4", NULL
    };
    char *offnames[] = { "ALL", NULL };
    static long ioff;
    static TELESCOPE_M tel;
    int name;
    char message[256];

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Decode virtual telescope specification */
        if (tcsDcString(telnames, "telescope : ", pcad->a, &name, pcad))
            break;

/* Construct virtual telescope mask */
        switch (name) {
        case 0: tel = MOUNT_M; break;
        case 1: tel = SOURCE_A_M; break;
        case 2: tel = SOURCE_B_M; break;
        case 3: tel = SOURCE_C_M; break;
        case 4: tel = SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        case 5: tel = PWFS1_M; break;
        case 6: tel = PWFS2_M; break;
        case 7: tel = OIWFS_M; break;
        case 8: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M |
                      PWFS1_M | PWFS2_M | OIWFS_M | 
                      G1_M | G2_M | G3_M | G4_M ; break;
        case 9: tel = G1_M; break;
        case 10: tel = G2_M; break;
        case 11: tel = G3_M; break;
        case 12: tel = G4_M; break;
        }

/* Decode the offset number */
        if (tcsDcString(offnames, "offset: ", pcad->b, &name, pcad)) {

/* Reset message prefix */
           tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

/* Input was not "all" so try decoding as an integer */
           if (tcsDcLong("offset: ", pcad->b, &ioff, pcad)) break;

/* Offset must be in the range 0-2 */
           if ( ioff < 0 || ioff > 2 ) {
               tcsCsAppendMessage(pcad, "offset: outside 0-2");
               break;
           }

/* If 1 or 2, check that the mount isn't included */
           if (ioff != 0) {
              if ( (tel & MOUNT) != 0 ) {
                  tcsCsAppendMessage(pcad,
                      "offset: must be zero for Mount");
                  break;
              }
           }
        } else {

/* Input was "all" */
            ioff = -1;
        }

        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:
        *(long *) pcad->vala = tel;
        *(long *) pcad->valb = ioff;

        sprintf(message, "%s : Name: %s offset: %s", tcsCsCadName(pcad), 
                                                            pcad->a, pcad->b);
        tcsLogMessage(message);

/* Call kernel routine */
        tcsSetOffsets(tel, ioff, 0.0, 0.0);
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
 *   tcsCADabsorbPoOffset
 *
 *   Purpose:
 *   CAD processing routine for the absorbPoOffset CAD record.
 *
 *   Description:
 *   Calls the kernel absorb pointing origin offset routine
 *
 *   Invocation:
 *   tcsCADabsorbPoOffset( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a Virtual telescopes
 *      b Offsets
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
 *   Any known problems with the function
 *
 *-
*/
/* *INDENT-ON* */

long tcsCADabsorbPoOffset(struct cadRecord *pcad)
{
    int status;
    char *telnames[] = {
        "MOUNT",
        "SOURCE A", "SOURCE B", "SOURCE C",
        "SOURCE", 
        "ALL", NULL
    };
    char *offnames[] = { "ALL", NULL };
    static long ioff;
    static TELESCOPE_M tel;
    int name;
    char message[256];

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Decode virtual telescope specification */
        if (tcsDcString(telnames, "telescope name: ", pcad->a, &name, pcad))
            break;

/* Construct virtual telescope mask */
        switch (name) {
        case 0: tel = MOUNT_M; break;
        case 1: tel = SOURCE_A_M; break;
        case 2: tel = SOURCE_B_M; break;
        case 3: tel = SOURCE_C_M; break;
        case 4: tel = SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        case 5: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        }

/* If a source VT has been included then decode the offset number */
        if (tcsDcString(offnames, "offset: ", pcad->b, &name, pcad)) {

/* Reset message prefix */
           tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

/* Input was not "all" so try decoding as an integer */
           if (tcsDcLong("offset: ", pcad->b, &ioff, pcad)) break;

/* Offset must be in the range 0-2 */
           if ( ioff < 0 || ioff > 2 ) {
               tcsCsAppendMessage(pcad, "offset: outside 0-2");
               break;
           }

/* If 1 or 2, check that only source VTs are included */
           if (ioff != 0) {
              if ( (tel & MOUNT_M) != 0 ) {
                  tcsCsAppendMessage(pcad, "offset: must be zero for Mount");
                  break;
              }
           }
        } else {

/* Input was "all" */
            ioff = -1;
        }

        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:
        *(long *) pcad->vala = tel;
        *(long *) pcad->valb = ioff;

        sprintf(message, "%s : Name: %s offset: %s", tcsCsCadName(pcad), 
                                                            pcad->a, pcad->b);
        tcsLogMessage(message);
/* Call kernel routine */
        tcsAbsorbPoOffsets(tel, ioff);
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
 *   tcsCADclearPoOffset
 *
 *   Purpose:
 *   CAD processing routine for the clearPoOffset CAD record.
 *
 *   Description:
 *   Calls the kernel set pointing origin offset routine
 *
 *   Invocation:
 *   tcsCADclearPoOffset( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a Virtual telescopes
 *      b Offsets
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
 *   Any known problems with the function
 *
 *-
*/
/* *INDENT-ON* */

long tcsCADclearPoOffset(struct cadRecord *pcad)
{
    int status;
    char *telnames[] = {
        "MOUNT",
        "SOURCE A", "SOURCE B", "SOURCE C",
        "SOURCE",
        "ALL", NULL
    };
    char *offnames[] = { "ALL", NULL };
    static long ioff;
    static TELESCOPE_M tel;
    int name;
    char message[256];

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;

/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Decode virtual telescope specification */
        if (tcsDcString(telnames, "telescope name: ", pcad->a, &name, pcad))
            break;

/* Construct virtual telescope mask */
        switch (name) {
        case 0: tel = MOUNT_M; break;
        case 1: tel = SOURCE_A_M; break;
        case 2: tel = SOURCE_B_M; break;
        case 3: tel = SOURCE_C_M; break;
        case 4: tel = SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        case 5: tel = MOUNT_M | SOURCE_A_M | SOURCE_B_M | SOURCE_C_M; break;
        }

/* If a source VT has been included then decode the offset number */
        if (tcsDcString(offnames, "offset: ", pcad->b, &name, pcad)) {

/* Reset message prefix */
           tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

/* Input was not "all" so try decoding as an integer */
           if (tcsDcLong("offset: ", pcad->b, &ioff, pcad)) break;

/* Offset must be in the range 0-2 */
           if ( ioff < 0 || ioff > 2 ) {
               tcsCsAppendMessage(pcad, "offset: outside 0-2");
               break;
           }

/* If 1 or 2, check that only source VTs are included */
           if (ioff != 0) {
              if ( (tel & MOUNT_M) != 0 ) {
                  tcsCsAppendMessage(pcad, "offset: must be zero for Mount");
                  break;
              }
           }
        } else {

/* Input was "all" */
            ioff = -1;
        }

        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:
        *(long *) pcad->vala = tel;
        *(long *) pcad->valb = ioff;

        sprintf(message, "%s : Name: %s offset: %s", tcsCsCadName(pcad), 
                                                            pcad->a, pcad->b);
        tcsLogMessage(message);

/* Call kernel routine */
        tcsSetPoOffsets(tel, ioff, 0.0, 0.0);
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
epicsRegisterFunction(tcsCADabsorbPoOffset);
epicsRegisterFunction(tcsCADclearOffset);
epicsRegisterFunction(tcsCADclearPoOffset);
epicsRegisterFunction(tcsCADabsorbOffset);
