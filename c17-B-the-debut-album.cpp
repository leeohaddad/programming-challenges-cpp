/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 17                   Professor Marcel   **/
/**   Problema B - The Debut Album                                 Curso: BCC   **/
/**   https://www.codepit.io/#/problems/55c0f8fb9b6a001a6e7bf2b3/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_N 50005
#define desired_modulo 1000000007
#define debug_off 1

using namespace std;

int n, a, b;
long long dynamicProgrammingTable[MAX_N][2];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n a=%d;\n b=%d;\n",n,a,b);
}
#endif

int main () {
   int loop, inner_loop;

    #ifdef debug_on
        printf("\n| C17.B - The Debut Album |\n");
    #endif

    /* read program arguments */
    scanf("%d %d %d", &n, &a, &b);
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    dynamicProgrammingTable[0][0] = dynamicProgrammingTable[0][1] = 1;
    for (loop=1; loop<=n; loop++)
    {
        for (inner_loop=1; inner_loop<=min(a,loop); inner_loop++)
        {
            dynamicProgrammingTable[loop][0] += dynamicProgrammingTable[loop-inner_loop][1];
            dynamicProgrammingTable[loop][0] %= desired_modulo;
        }
        for (inner_loop=1; inner_loop<=min(b,loop); inner_loop++)
        {
            dynamicProgrammingTable[loop][1] += dynamicProgrammingTable[loop-inner_loop][0];
            dynamicProgrammingTable[loop][1] %= desired_modulo;
        }
    }
    printf("%lld\n", (dynamicProgrammingTable[n][0] + dynamicProgrammingTable[n][1]) % desired_modulo);
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}