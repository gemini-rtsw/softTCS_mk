/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsGuideCad.c
*
*   FUNCTION NAME(S)
*   tcsCADconfigWFS - configWFS cad processing function
*
*/
/*
 * $Log:
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
#include "tcsConstants.h"
#include "tcsConfig.h"
#include "tcsInterlocks.h"
#include "tcsDecode.h"
#include "tcsCadSupport.h"
#include "tcsLogSupport.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADconfigWFS
 *
 *   Purpose:
 *   Implements config WFS CADs
 *
 *   Description:
 *   On the PRESET directive checks all the input argument for validity
 *   and that the source is visible. If these tests are passed then marks
 *   the CAD and loads the data into the appropriate telescope control
 *   block.
 *
 *   Invocation:
 *   tcsCADconfigWFS( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *    The meanings of the input cadRecord structure are:
 *
 *      a Nod state A chop state A enable
 *      b Nod state A chop state B enable
 *      c Nod state A chop state C enable
 *      d Nod state B chop state A enable
 *      e Nod state B chop state B enable
 *      f Nod state B chop state C enable
 *      g Nod state C chop state A enable
 *      h Nod state C chop state B enable
 *      i Nod state C chop state C enable
 *
 *   Epics outputs:
 *
 *      vala Nod state A chop state A enable
 *      valb Nod state A chop state B enable
 *      valc Nod state A chop state C enable
 *      vald Nod state B chop state A enable
 *      vale Nod state B chop state B enable
 *      valf Nod state B chop state C enable
 *      valg Nod state C chop state A enable
 *      valh Nod state C chop state B enable
 *      vali Nod state C chop state C enable
 *
 *   Function value:
 *   Return value from function e.g.
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


long tcsCADconfigWFS(struct cadRecord *pcad)
{
    int status;
    static struct GUIDE guide[7];
    char* cadname;              /* Command name without prefix */
    int nguide;                 /* Index into guide structure array */
    int act[3][3];              /* Enable flags */
    char message[256];

/* Guide number from name of CAD */
    cadname = tcsCsCadName( pcad );
    if (!strcmp(cadname, "configPwfs1")) {
        nguide = 0;
    } else if (!strcmp(cadname, "configPwfs2")) {
        nguide = 1;
    } else if (!strcmp(cadname, "configOiwfs")) {
        nguide = 2;
    } else if (!strcmp(cadname, "configG1")) {
        nguide = 3;
    } else if (!strcmp(cadname, "configG2")) {
        nguide = 4;
    } else if (!strcmp(cadname, "configG3")) {
        nguide = 5;
    } else if (!strcmp(cadname, "configG4")) {
        nguide = 6;
    } else {
        tcsCsAppendMessage(pcad, "cad record name invalid");
        status = CAD_REJECT ;
        return status ;
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

/* Node enable flags */
        if (tcsDcOnOff("Nod A chop A enable: ", pcad->a, &act[0][0], pcad)) 
           break;
        if (tcsDcOnOff("Nod A chop B enable: ", pcad->b, &act[0][1], pcad)) 
           break;
        if (tcsDcOnOff("Nod A chop C enable: ", pcad->c, &act[0][2], pcad)) 
           break;
        if (tcsDcOnOff("Nod B chop A enable: ", pcad->d, &act[1][0], pcad)) 
           break;
        if (tcsDcOnOff("Nod B chop B enable: ", pcad->e, &act[1][1], pcad)) 
           break;
        if (tcsDcOnOff("Nod B chop C enable: ", pcad->f, &act[1][2], pcad)) 
           break;
        if (tcsDcOnOff("Nod C chop A enable: ", pcad->g, &act[2][0], pcad)) 
           break;
        if (tcsDcOnOff("Nod C chop B enable: ", pcad->h, &act[2][1], pcad)) 
           break;
        if (tcsDcOnOff("Nod C chop C enable: ", pcad->i, &act[2][2], pcad)) 
           break;

/* Load the data into the configuration block */
        guide[nguide].act[0][0].field = 'A';
        strncpy(guide[nguide].act[0][0].instring, pcad->a, MAX_STRING_SIZE);
        guide[nguide].act[0][0].val = act[0][0];

        guide[nguide].act[0][1].field = 'B';
        strncpy(guide[nguide].act[0][1].instring, pcad->b, MAX_STRING_SIZE);
        guide[nguide].act[0][1].val = act[0][1];

        guide[nguide].act[0][2].field = 'C';
        strncpy(guide[nguide].act[0][2].instring, pcad->c, MAX_STRING_SIZE);
        guide[nguide].act[0][2].val = act[0][2];

        guide[nguide].act[1][0].field = 'D';
        strncpy(guide[nguide].act[1][0].instring, pcad->d, MAX_STRING_SIZE);
        guide[nguide].act[1][0].val = act[1][0];

        guide[nguide].act[1][1].field = 'E';
        strncpy(guide[nguide].act[1][1].instring, pcad->e, MAX_STRING_SIZE);
        guide[nguide].act[1][1].val = act[1][1];

        guide[nguide].act[1][2].field = 'F';
        strncpy(guide[nguide].act[1][2].instring, pcad->f, MAX_STRING_SIZE);
        guide[nguide].act[1][2].val = act[1][2];

        guide[nguide].act[2][0].field = 'G';
        strncpy(guide[nguide].act[2][0].instring, pcad->g, MAX_STRING_SIZE);
        guide[nguide].act[2][0].val = act[2][0];

        guide[nguide].act[2][1].field = 'H';
        strncpy(guide[nguide].act[2][1].instring, pcad->h, MAX_STRING_SIZE);
        guide[nguide].act[2][1].val = act[2][1];

        guide[nguide].act[2][2].field = 'I';
        strncpy(guide[nguide].act[2][2].instring, pcad->i, MAX_STRING_SIZE);
        guide[nguide].act[2][2].val = act[2][2];

        if (tcsConfigMarkComm(pcad->name, pcad->mess))
            break;
        tcsConfigSetGuide(nguide, &guide[nguide]);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strcpy(pcad->vala, guide[nguide].act[0][0].val ? "On" : "Off");
        strcpy(pcad->valb, guide[nguide].act[0][1].val ? "On" : "Off");
        strcpy(pcad->valc, guide[nguide].act[0][2].val ? "On" : "Off");
        strcpy(pcad->vald, guide[nguide].act[1][0].val ? "On" : "Off");
        strcpy(pcad->vale, guide[nguide].act[1][1].val ? "On" : "Off");
        strcpy(pcad->valf, guide[nguide].act[1][2].val ? "On" : "Off");
        strcpy(pcad->valg, guide[nguide].act[2][0].val ? "On" : "Off");
        strcpy(pcad->valh, guide[nguide].act[2][1].val ? "On" : "Off");
        strcpy(pcad->vali, guide[nguide].act[2][2].val ? "On" : "Off");

        sprintf(message, "%s : AA: %s AB: %s AC: %s BA: %s BB: %s BC: %s CA: %s CB: %s CC: %s", 
         cadname, pcad->a, pcad->b, pcad->c, 
                  pcad->d, pcad->e, pcad->f,
                  pcad->g, pcad->h, pcad->i);
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
epicsRegisterFunction(tcsCADconfigWFS);
