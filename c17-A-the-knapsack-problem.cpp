/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 17                   Professor Marcel   **/
/**   Problema A - The Knapsack Problem                            Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c5f6fa9de49e5c655a/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_S 2005
#define MAX_N 2005
#define debug_off 1

using namespace std;

int S, N;
long long weights[MAX_N];
long long values[MAX_N];
long long dynamicProgrammingTable[MAX_S][MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" S=%d;\n",S);
    printf(" N=%d;\n",N);
    printf(" items:\n");
    for (loop=0; loop<N; loop++) {
        printf("  w:%lld v:%lld\n",weights[loop],values[loop]);
    }
}
#endif

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}
 
long long knapsack(int maxWeight, int n)
{
    long long firstOption, secondOption;
    #ifdef debug_on
        printf("    knapsack(%d,%d)\n",maxWeight,n);
    #endif
    if (dynamicProgrammingTable[maxWeight][n] != -1)
        return dynamicProgrammingTable[maxWeight][n];
    if (n == 0 || maxWeight == 0)
        return 0;
    if (weights[n-1] > maxWeight)
        return knapsack(maxWeight, n-1); /* nth item doesn't fit */
    firstOption = values[n-1] + knapsack(maxWeight - weights[n-1], n-1); /* nth item goes */
    secondOption = knapsack(maxWeight, n-1); /* nth item stays */
    dynamicProgrammingTable[maxWeight][n] = max(firstOption,secondOption);
    return dynamicProgrammingTable[maxWeight][n];
}

int main () {
   int loop;

    #ifdef debug_on
        printf("\n| C17.A - The Knapsack Problem |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &S, &N);
    for (loop=0; loop<N; loop++)
        scanf("%lld %lld", &weights[loop], &values[loop]);

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    memset(dynamicProgrammingTable, -1, sizeof(dynamicProgrammingTable));
    printf("%lld\n", knapsack(S, N));
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}