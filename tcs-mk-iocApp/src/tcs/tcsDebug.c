#include <errlog.h>
#include <iocsh.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include <epicsTypes.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "tcsDebug.h"
#include <genSubRecord.h>

struct Stats {
	char name[MAX_STRING_SIZE];
	unsigned stages;
	struct timeval lastReset;
	unsigned long enter;
	unsigned long through;
	unsigned long *stage_counts;
};

#define INITIALISING_STAGES 20
#define MONITORING_STAGES 11
#define MAX_VALS 20
#define genSubJ 9

static struct Stats initialising = { "initialising", INITIALISING_STAGES };
static struct Stats monitoring   = { "monitoring", MONITORING_STAGES };

const char *initialising_stg_strs[INITIALISING_STAGES] = 
	{"all done 1st", "all done", "mc to", "cr to" ,"mc not done", "cr not done", 
	"ec not done", "ec to",	"m2 not done", "m2 to", "ag not done", "ag to",
	"aom not done", "aom to", "ao not done", "ao to", "gp not done", "gp to", 
	"m1 not done", "m1 to"};
const char *monitoring_stg_strs[MONITORING_STAGES] = 
	{"mc not conn", "cr not conn", "ec not conn", "m2 not conn", "ag not conn", 
	"ao not conn", "aom not conn","gp not conn","m1 not conn", "init busy", "reboot" };

static void resetStats(struct Stats *st) {
	//gettimeofday(&st->lastReset, NULL);
	st->through = 0;
	st->enter = 0;

	if (st->stage_counts == NULL)
		st->stage_counts = (unsigned long *)malloc(sizeof(unsigned long) * st->stages);
	memset(st->stage_counts, 0, sizeof(unsigned long) * st->stages);
}

void tcsInitSeqStats(void) {
	errlogPrintf("tcsDebug: initializing statistics\n");
	resetStats(&initialising);
	resetStats(&monitoring);
	if (!initialising.stage_counts || !monitoring.stage_counts)
		errlogPrintf("tcsDebug: ERROR initializing the stage counters\n");
}

void throughSeqCounter(SEQ_STATE state) {
	errlogPrintf("Entering %d - v1.1\n", state);
	switch (state) {
		case INITIALISING_ST:
			initialising.through ++;
			break;
		case MONITORING_ST:
			monitoring.through ++;
			break;
		default:
			break;
	}
}

void enterSeqCounter(SEQ_STATE state) {
	errlogPrintf("Went through %d\n", state);
	switch (state) {
		case INITIALISING_ST:
			initialising.enter ++;
			break;
		case MONITORING_ST:
			monitoring.enter ++;
			break;
	}
}

int seqStateRuleHit(SEQ_STATE state, int stage) {
	struct Stats *st = NULL;

	switch(state) {
		case INITIALISING_ST:
			st = &initialising;
			break;
		case MONITORING_ST:
			st = &monitoring;
			break;
	}

	if ((st != NULL) && (stage < st->stages))
		st->stage_counts[stage] += 1;
	return 1;
}

static void printStats(struct Stats *st, const char* strs[] ) {
	errlogPrintf("Data is currently being published to GEA.\n");
	//TEST code
	/*
	static int val = 0;
	int i;
	for (i=0; i<st->stages; i++){
		st->stage_counts[i] = val++;
	}
	st->through = val++;
	st->enter = val++;*/
}


void publishStats(int stages, struct Stats *st, struct genSubRecord *pgsub) {
  void **valptr;
  void **inptr;
  int i;
  valptr = &pgsub->vala;
  inptr = &pgsub->a;
  if (stages > MAX_VALS)
  {
    errlogPrintf("Too many values to be put on genSub vals %d > %d\n", stages, MAX_VALS);
    return;
  }	 
  for (i=0; i<stages; i++, valptr++, inptr++)
  {
    if(i == genSubJ) {
    	valptr++;
    	inptr++;
    }

    *(double *)*valptr = st->stage_counts[i];
    *(double *)*inptr += st->stage_counts[i];
  }
  return;	
}

long tcsInitGS (struct genSubRecord *pgsub)
{
  publishStats(INITIALISING_STAGES, &initialising, pgsub);
  return 0;
}

long tcsMonGS (struct genSubRecord *pgsub)
{ /** Fill up entry and through counts for both states here, unfortunately there
    * is not enough vals to accomplish this in only 1 genSub record **/
  static long controlVal = 0;
  publishStats(MONITORING_STAGES, &monitoring, pgsub);
  
  if (MONITORING_STAGES+9 > MAX_VALS)
  {
    errlogPrintf("Too many values to be put on genSub Monitoring vals %d > %d\n", 
                 MONITORING_STAGES+9, MAX_VALS);
  }
  else
  {
    *(double *)pgsub->valm = controlVal++; 
    *(double *)pgsub->valn = initialising.through; 
    *(double *)pgsub->valo += initialising.through; 
    *(double *)pgsub->valp = initialising.enter; 
    *(double *)pgsub->valq += initialising.enter; 
    *(double *)pgsub->valr = monitoring.through; 
    *(double *)pgsub->vals += monitoring.through; 
    *(double *)pgsub->valt = monitoring.enter; 
    *(double *)pgsub->valu += monitoring.enter; 
  }
  
  resetStats(&initialising);
  resetStats(&monitoring);
  /** Since the stats where published until they are reset there could have been a new
   *  count, this count wouldn't be recorded but this reporting does not pretend to be
   *  that accurate - we want to avoid the use of mutexes here. Another solution could 
   *  be to never reset the stats.  **/
  return 0;
}

static void tcsSeqStats(void) {
	printStats(&monitoring, monitoring_stg_strs);
	//resetStats(&monitoring);
	printStats(&initialising, initialising_stg_strs);
	//resetStats(&initialising);
}

static const iocshArg tcsSeqStatsInfoArg0 = {"tcsSeqStats", iocshArgString };

static const iocshFuncDef tcsSeqStatsFuncDef =
         {"tcsSeqStats", 0, NULL};

static void tcsSeqStatsCallFunc(const iocshArgBuf *args)
{
   tcsSeqStats();
}

static void registerSeqStatsCommands(void)
{
      iocshRegister(&tcsSeqStatsFuncDef, tcsSeqStatsCallFunc);
}
epicsExportRegistrar(registerSeqStatsCommands);
epicsRegisterFunction(tcsInitGS);
epicsRegisterFunction(tcsMonGS);
epicsRegisterFunction(tcsSeqStats);
epicsRegisterFunction(tcsInitSeqStats);
