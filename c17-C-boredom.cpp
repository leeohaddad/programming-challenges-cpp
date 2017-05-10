/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 17                   Professor Marcel   **/
/**   Problema C - Boredom                                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dcf4efdd359ad3c573aa2/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_N 100005
#define debug_off 1

using namespace std;

int n;
int alexSequence[MAX_N];
long long dynamicProgrammingTable[MAX_N];
long long c[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" Alex's Sequence:\n");
    for (loop=0; loop<n; loop++)
        printf("  %d\n",alexSequence[loop]);
}
#endif

int main () {
   int loop;

    #ifdef debug_on
        printf("\n| C17.C - Boredom |\n");
    #endif

    /* init */
    memset(c, 0, sizeof(c));

    /* read program arguments */
    scanf("%d", &n);
    for (loop=0; loop<n; loop++) {
        scanf("%d", &alexSequence[loop]);
        c[alexSequence[loop]]++;
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    dynamicProgrammingTable[0] = 0;
    dynamicProgrammingTable[1] = c[1];
    for (loop=2; loop<MAX_N; loop++) {
        dynamicProgrammingTable[loop] = max(dynamicProgrammingTable[loop-1], dynamicProgrammingTable[loop-2] + loop*c[loop]);
    }
    printf("%lld\n", dynamicProgrammingTable[MAX_N-1]);
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}