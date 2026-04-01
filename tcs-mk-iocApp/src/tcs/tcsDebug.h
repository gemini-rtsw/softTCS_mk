#ifndef __TCSDEBUG__
#define __TCSDEBUG__

typedef enum {
	INITIALISING_ST,
	MONITORING_ST
} SEQ_STATE;

void tcsInitSeqStats();
void throughSeqCounter(SEQ_STATE);
void enterSeqCounter(SEQ_STATE);
int seqStateRuleHit(SEQ_STATE, int);
#endif // __TCSDEBUG__
