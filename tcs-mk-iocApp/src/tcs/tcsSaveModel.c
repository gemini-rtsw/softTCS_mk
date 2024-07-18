#include <stdio.h>
#include <registryFunction.h>
#include <epicsExport.h>
#include "genSubRecord.h"

/* 
 * These indices should match the ones used in tcsSeqInit.st
 */
#define RESTORE_A   0
#define RESTORE_B   1
#define RESTORE_C   2
#define RESTORE_D   3
#define RESTORE_E   4
#define RESTORE_F   5
#define RESTORE_G   6
#define RESTORE_H   7
#define RESTORE_I   8
// 9(J) is not used
#define RESTORE_K   10
#define RESTORE_L   11
#define RESTORE_M   12
#define RESTORE_N   13
#define M2_XCORR    14
#define M2_YCORR    15
#define DEMAND_EL   16

/*+
 *   Function name:
 *   dump_array
 *
 *   Purpose:
 *   Print array contents
 *
 *   Description:
 *   Print the contents of an array of doubles
 *
 *   Invocation:
 *   dump_array(array, max_values)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   (>) array (double *)   Array of doubles
 *   (>) max_values (int)   Number of elements in the array
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *-
 */
static void dump_array(double array[], int max_values) {
    int n;
    for (n = 0; n < max_values; n++)
        printf("%lg\n", array[n]);
}

#if 0
/* Functions used during simulation. Kept here for reference.
 */
long tcsOpticsFigureTotals(struct genSubRecord *pgsub)
{
    int n = 10;

    *(double *)pgsub->vala = n++;
    *(double *)pgsub->valb = n++;
    *(double *)pgsub->valc = n++;
    *(double *)pgsub->vald = n++;
    *(double *)pgsub->vale = n++;
    *(double *)pgsub->valf = n++;
    *(double *)pgsub->valg = n++;
    *(double *)pgsub->valh = n++;
    *(double *)pgsub->vali = n++;
    *(double *)pgsub->valk = n++;
    *(double *)pgsub->vall = n++;
    *(double *)pgsub->valm = n++;
    *(double *)pgsub->valn = n++;
    *(double *)pgsub->valo = n++;
    *(double *)pgsub->valp = n++;
    *(double *)pgsub->valq = n++;
    *(double *)pgsub->valr = n++;
    *(double *)pgsub->vals = n++;
    *(double *)pgsub->valt = n++;
    return 0L;
}

long tcsOpticsM1Restore(struct genSubRecord *pgsub)
{
    printf("tcsOpticsM1Restore\n");
    printf("a: %lg\n", *(double *) pgsub->a);
    printf("b: %lg\n", *(double *) pgsub->b);
    printf("c: %lg\n", *(double *) pgsub->c);
    printf("d: %lg\n", *(double *) pgsub->d);
    printf("e: %lg\n", *(double *) pgsub->e);
    printf("f: %lg\n", *(double *) pgsub->f);
    printf("g: %lg\n", *(double *) pgsub->g);
    printf("h: %lg\n", *(double *) pgsub->h);
    printf("i: %lg\n", *(double *) pgsub->i);
    printf("j: %lg\n", *(double *) pgsub->j);
    printf("k: %lg\n", *(double *) pgsub->k);
    printf("l: %lg\n", *(double *) pgsub->l);
    printf("m: %lg\n", *(double *) pgsub->m);
    printf("n: %lg\n", *(double *) pgsub->n);
    printf("o: %lg\n", *(double *) pgsub->o);
    printf("p: %lg\n", *(double *) pgsub->p);
    printf("q: %lg\n", *(double *) pgsub->q);
    printf("r: %lg\n", *(double *) pgsub->r);
    printf("s: %lg\n", *(double *) pgsub->s);
    printf("t: %lg\n", *(double *) pgsub->t);
    return 0L;
}
#endif

/*+
 *   Function name:
 *   saveModel
 *
 *   Purpose:
 *   Save the M1 model
 *
 *   Description:
 *   Save the M1 model to a file for later restore
 *
 *   Invocation:
 *   saveModel(char *file_name, char *prefix, double values[], int max_values)
 *
 *   Parameters: (">" input, "!" modified, "<" output)
 *   (>) array (double *)   Array of doubles
 *   (>) array (double *)   Database prefix
 *   (>) max_values (int)   Number of elements in the array
 *
 *   Function value:
 *   None
 *
 *   Deficiencies:
 *-
 */
int saveModel(char *file_name, char *prefix, double values[], int max_values) {
    FILE    *fp;

    fprintf(stderr, "file_name=(%s), max_values=%d\n", file_name, max_values);
    dump_array(values, max_values);

    if ((fp = fopen(file_name, "w")) == NULL) {
        fprintf(stderr, "Cannot open file (%s)\n", file_name);
        return -1L;
    }

    /*
     * Write the group data
     */
    fprintf(fp, "group {\n");
    fprintf(fp, "%%double %sdrives:figureTotals.VALA ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.A = %g ;\n", prefix, values[RESTORE_A]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALB ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.B = %lg ;\n", prefix, values[RESTORE_B]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALC ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.C = %lg ;\n", prefix, values[RESTORE_C]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALD ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.D = %lg ;\n", prefix, values[RESTORE_D]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALE ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.E = %lg ;\n", prefix, values[RESTORE_E]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALF ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.F = %lg ;\n", prefix, values[RESTORE_F]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALG ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.G = %lg ;\n", prefix, values[RESTORE_G]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALH ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.H = %lg ;\n", prefix, values[RESTORE_H]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALI ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.I = %lg ;\n", prefix, values[RESTORE_I]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALK ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.K = %lg ;\n", prefix, values[RESTORE_K]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALL ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.L = %lg ;\n", prefix, values[RESTORE_L]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALM ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.M = %lg ;\n", prefix, values[RESTORE_M]);
    fprintf(fp, "%%double %sdrives:figureTotals.VALN ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.N = %lg ;\n", prefix, values[RESTORE_N]);
    fprintf(fp, "%%double %sm2XErrorCorr ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.P = %lg ;\n", prefix, values[M2_XCORR]);
    fprintf(fp, "%%double %sm2YErrorCorr ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.Q = %lg ;\n", prefix, values[M2_YCORR]);
    fprintf(fp, "%%double %sdemandEl;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.O = %lg ;\n", prefix, values[DEMAND_EL]);
    fprintf(fp, "};\n");

    /*
     * Write the trigger data
     */
    fprintf(fp, "%%double %sdrives:figureTotals.VALJ ;\n", prefix);
    fprintf(fp, "double %sdrives:restoreM1.J = %lg;\n", prefix, 0.0);

    fclose(fp);

    return 0;
}
