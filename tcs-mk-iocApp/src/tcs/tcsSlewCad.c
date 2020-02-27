/* *INDENT-OFF* */
/*
*   FILENAME
*   tcsSlewCad.c
*
*   FUNCTION NAME(S)
*   tcsCADslew - CAD processing routine for the slew CAD
*
*/
/*
 * $Log:
 */
/* *INDENT-ON* */

#include <string.h>
#include <registryFunction.h>
#include <epicsStdioRedirect.h>
#include <epicsExport.h>
#include <dbDefs.h>
#include <cad.h>
#include <cadRecord.h>
#include <subRecord.h>
#include "tcsConstants.h"
#include "tcsConfig.h"
#include "tcsInterlocks.h"
#include "tcsCadSupport.h"
#include "tcsDecode.h"
#include "tcsEcsLib.h"
#include "tcsLogSupport.h"

/* *INDENT-OFF* */
/*+
 *   Function name:
 *   tcsCADslew
 *
 *   Purpose:
 *   CAD processing routine for the "slew" CAD record.
 *
 *   Description:
 *   Sets various entries in the current configuration block to default
 *   values appropriate for a new configuration that slews the telescope
 *   to a new target.
 *
 *   The CAD must be executed before any of the configuration setting CADs
 *   so that items that have been explicitly set are not overwritten.
 *
 *   Invocation:
 *   tcsCADslew( pcad );
 *
 *   Parameters: (">" input, "!" modified, "<" output)  
 *      (!) pcad   (struct cadRecord*)   pointer to cad record structure
 *
 *   EPICS input parameters:
 *      a => Reset chop
 *      b => Reset source offsets
 *      c => Reset source track rates
 *      d => Reset mount offsets
 *      e => Reset mount track rates
 *      f => Short circuit filter 1
 *      g => Short circuit filter 2
 *      h => Reset local pointing model
 *      i => Disable guiding
 *      j => Reset guide offsets
 *      k => Reset pointing origin offsets
 *
 *   Function value:
 *   (<)  status  (long)  Return status, 0 = OK
 * 
 *   External functions:
 *   tcsEcsSetSlewFlag  (tcsEcsLib)   Set slew flag for tcsDriveECS function
 *
 *   External variables:
 *   Any external variables used in this function or procedure e.g.
 *   (>)   <name>    <C type>    <variable description>
 *
 *   Prior requirements:
 *   none
 *
 *   Deficiencies:
 *   Currently the slew flag for the Enclosure is set whenever this command
 *   is executed. It might be better to make this an option.
 *
 *-
*/
/* *INDENT-ON* */

long tcsCADslew(struct cadRecord *pcad)
{
    int status;
    int chop, soff, sdt, moff, mdt, sc1, sc2, lpm, guide, goff, pooff;
    static struct SLEW slew;
    char message[256];
    char *cadname;

/* Check for interlocks */
    if (pcad->dir != menuDirectiveCLEAR)
        if (tcsInterlocked(pcad->mess)) return CAD_REJECT;


/* Set message prefix */
    tcsCsSetMessageN (pcad, tcsCsCadName(pcad), ": ", (char *) NULL);

    status = CAD_ACCEPT;
    switch (pcad->dir) {
    case menuDirectivePRESET:
        status = CAD_REJECT;

/* Pull in and validate the data on the CAD input fields */
        if ( pcad->a[0] ) {
            if (tcsDcOnOff("reset chop: ", pcad->a, &chop, pcad)) break;
        } else {
            chop = 1;
        }
        if ( pcad->b[0] ) {
            if (tcsDcOnOff("reset source offsets: ", pcad->b, &soff, pcad)) 
                break;
        } else {
            soff = 1;
        }
        if ( pcad->c[0] ) {
            if (tcsDcOnOff("reset source track rates: ", pcad->c, &sdt, pcad)) 
                break;
        } else {
            sdt = 1;
        }
        if ( pcad->d[0] ) {
            if (tcsDcOnOff("reset mount offsets: ", pcad->d, &moff, pcad)) 
                break;
        } else {
            moff = 1;
        }
        if ( pcad->e[0] ) {
            if (tcsDcOnOff("reset mount track rates: ", pcad->e, &mdt, pcad)) 
                break;
        } else {
            mdt = 1;
        }
        if ( pcad->f[0] ) {
            if (tcsDcOnOff("short circuit filter 1: ", pcad->f, &sc1, pcad)) 
                break;
        } else {
            sc1 = 1;
        }
        if ( pcad->g[0] ) {
            if (tcsDcOnOff("short circuit filter 2: ", pcad->g, &sc2, pcad)) 
                break;
        } else {
            sc2 = 1;
        }
        if ( pcad->h[0] ) {
            if (tcsDcOnOff("reset local pointing model: ", pcad->h, &lpm, pcad))
                break;
        } else {
            lpm = 0;
        }
        if ( pcad->i[0] ) {
            if (tcsDcOnOff("disable guiding: ", pcad->i, &guide, pcad))
                break;
        } else {
            guide = 1;
        }
        if ( pcad->j[0] ) {
            if (tcsDcOnOff("reset guide offsets: ", pcad->j, &goff, pcad))
                break;
        } else {
            goff = 1;
        }
        if ( pcad->k[0] ) {
            if (tcsDcOnOff("clear pointing origin offset: ", pcad->k, &pooff,
                    pcad))
                break;
        } else {
            pooff = 1;
        }

/* Mark this CAD as part of the configuration */
        if (tcsConfigMarkComm(pcad->name, pcad->mess)) break;

/* Set the data in the configuration block */
          slew.chop.val = chop;
          slew.chop.field = 'A';
          strncpy(slew.chop.instring, pcad->a, MAX_STRING_SIZE);
          slew.soff.val = soff;
          slew.soff.field = 'B';
          strncpy(slew.soff.instring, pcad->b, MAX_STRING_SIZE);
          slew.sdt.val = sdt;
          slew.sdt.field = 'C';
          strncpy(slew.sdt.instring, pcad->c, MAX_STRING_SIZE);
          slew.moff.val = moff;
          slew.moff.field = 'D';
          strncpy(slew.moff.instring, pcad->d, MAX_STRING_SIZE);
          slew.mdt.val = mdt;
          slew.mdt.field = 'E';
          strncpy(slew.mdt.instring, pcad->e, MAX_STRING_SIZE);
          slew.sc1.val = sc1;
          slew.sc1.field = 'F';
          strncpy(slew.sc1.instring, pcad->f, MAX_STRING_SIZE);
          slew.sc2.val = sc2;
          slew.sc2.field = 'G';
          strncpy(slew.sc2.instring, pcad->g, MAX_STRING_SIZE);
          slew.lpm.val = lpm;
          slew.lpm.field = 'H';
          strncpy(slew.lpm.instring, pcad->h, MAX_STRING_SIZE);
          slew.guide.val = guide;
          slew.guide.field = 'I';
          strncpy(slew.guide.instring, pcad->i, MAX_STRING_SIZE);
          slew.goff.val = goff;
          slew.goff.field = 'J';
          strncpy(slew.goff.instring, pcad->j, MAX_STRING_SIZE);
          slew.pooff.val = pooff;
          slew.pooff.field = 'K';
          strncpy(slew.pooff.instring, pcad->k, MAX_STRING_SIZE);

/*  Set slew parameters in configuration block */
          tcsConfigSetSlew(&slew);

        status = CAD_ACCEPT;
        break;

    case menuDirectiveSTART:

/* Copy validated inputs argument to output CAD fields */
        strcpy(pcad->vala, slew.chop.val ? "On" : "Off");
        strcpy(pcad->valb, slew.soff.val ? "On" : "Off");
        strcpy(pcad->valc, slew.sdt.val ? "On" : "Off");
        strcpy(pcad->vald, slew.moff.val ? "On" : "Off");
        strcpy(pcad->vale, slew.mdt.val ? "On" : "Off");
        strcpy(pcad->valf, slew.sc1.val ? "On" : "Off");
        strcpy(pcad->valg, slew.sc2.val ? "On" : "Off");
        strcpy(pcad->valh, slew.lpm.val ? "On" : "Off");
        strcpy(pcad->vali, slew.guide.val ? "On" : "Off");
        strcpy(pcad->valj, slew.goff.val ? "On" : "Off");
        strcpy(pcad->valk, slew.pooff.val ? "On" : "Off");

/*  Set the mask that determines what additional processing happens */
        strcpy(pcad->vals, "Off");
        *(long*) pcad->valt = 0;
        if ( slew.chop.val ) *(long*) pcad->valt += 1;

/*  Set the flag to tell the enclosure to slew */
        tcsEcsSetSlewFlag();

        cadname = tcsCsCadName(pcad);
        sprintf(message, "%s : A: %s B: %s", cadname, pcad->a, pcad->b);
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
epicsRegisterFunction(tcsCADslew);
