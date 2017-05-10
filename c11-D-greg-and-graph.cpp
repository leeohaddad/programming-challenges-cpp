/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 11                   Professor Marcel   **/
/**   Problema D - Greg and Graph                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dcf14fdd359ad3c573844/view?index=3   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define MAX_N 505
#define debug_off 1

using namespace std;

int n;
long long graphAdjacency[MAX_N][MAX_N], result[MAX_N];
int toRemove[MAX_N];
bool f[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, inner_loop;
    printf("Arguments:\n");
    printf(" n=%d;\n", n);
    printf(" graph adjacency:\n ");
    for (loop=1; loop<=n; loop++) {
        for (inner_loop=1; inner_loop<=n; inner_loop++) {
            printf(" %lld",graphAdjacency[loop][inner_loop]);
        }
        printf("\n ");
    }
}
#endif

int main () {
    int loop, inner_loop, outer_loop, scanResult, elementToRemove;

    #ifdef debug_on
        printf("\n| C11.D - Greg and Graph |\n");
    #endif
    
    scanResult = scanf("%d", &n);
    while(scanResult == 1) {
        /* read program arguments */
        for (loop=1; loop<=n; loop++) {
            for (inner_loop=1; inner_loop<=n; inner_loop++) {
                scanf("%lld", &graphAdjacency[loop][inner_loop]);
                result[0] = result[0] + graphAdjacency[loop][inner_loop];
            }
        }
        for(loop=n; loop>=1; loop--)
            scanf("%d",&toRemove[loop]);

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        for(loop=0; loop<=n; loop++)
            f[loop] = false;
        for(outer_loop=1; outer_loop<=n; outer_loop++)
        {
            result[outer_loop] = 0;
            elementToRemove = toRemove[outer_loop];
            f[elementToRemove] = true;
            for(loop=1; loop<=n; loop++)
                for(inner_loop=1; inner_loop<=n; inner_loop++)
                {
                    graphAdjacency[loop][inner_loop] = min(graphAdjacency[loop][inner_loop] , graphAdjacency[loop][elementToRemove] + graphAdjacency[elementToRemove][inner_loop]);
                    if(f[loop] && f[inner_loop])
                        result[outer_loop] = result[outer_loop] + graphAdjacency[loop][inner_loop];
                }
        }
        for(loop=n; loop>=1; loop--)
            printf("%lld ", result[loop]);
        printf("\n");
        scanResult = scanf("%d", &n);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}