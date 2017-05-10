/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 18                   Professor Marcel   **/
/**   Problema B - Black or White                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c358f6fa9de49e5c7fd7/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N 205
#define GIANTNUM 1000000000
#define debug_off 1

using namespace std;

int N;
int sequenceToPaint[MAX_N];
int dynamicProgrammingMatrix[MAX_N][MAX_N][MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" N=%d;\n",m);
    printf(" Sequence To Paint:\n");
    for (loop=0; loop<N; loop++)
        printf("  %d\n", sequenceToPaint[loop]);
}
#endif

int minimizeUnpaintedIntegers (int n, int lblack, int lwhite){
    if (n > N)
        return 0;
    if (dynamicProgrammingMatrix[n][lblack][lwhite] != -1)
        return dynamicProgrammingMatrix[n][lblack][lwhite];
    dynamicProgrammingMatrix[n][lblack][lwhite] = GIANTNUM;
    if ((lblack == 0 || sequenceToPaint[n] > sequenceToPaint[lblack]) &&
        (lwhite==0 || sequenceToPaint[n] < sequenceToPaint[lwhite]))
        return dynamicProgrammingMatrix[n][lblack][lwhite] = min(minimizeUnpaintedIntegers(n+1,lblack,n), min(minimizeUnpaintedIntegers(n+1,n,lwhite), 1+minimizeUnpaintedIntegers(n+1,lblack,lwhite)));
    else if (lblack == 0 || sequenceToPaint[n] > sequenceToPaint[lblack])
        return dynamicProgrammingMatrix[n][lblack][lwhite] = min(minimizeUnpaintedIntegers(n+1,n,lwhite), 1+minimizeUnpaintedIntegers(n+1,lblack,lwhite));
    else if (lwhite == 0 || sequenceToPaint[n] < sequenceToPaint[lwhite])
        return dynamicProgrammingMatrix[n][lblack][lwhite] = min(minimizeUnpaintedIntegers(n+1,lblack,n), 1+minimizeUnpaintedIntegers(n+1,lblack,lwhite));
    else return dynamicProgrammingMatrix[n][lblack][lwhite] = 1+minimizeUnpaintedIntegers(n+1,lblack,lwhite);
}

int main () {
    int loop;

    #ifdef debug_on
        printf("\n| C18.B - Black or White |\n");
    #endif

    scanf("%d", &N);
    while (N != -1) {
        /* read program arguments */
        for (loop=1; loop<=N; loop++)
            scanf("%d", &sequenceToPaint[loop]);
    
        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        memset(dynamicProgrammingMatrix, -1, sizeof(dynamicProgrammingMatrix));
        printf("%d\n", minimizeUnpaintedIntegers(1, 0, 0));
        
        scanf("%d", &N);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}