/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 17                   Professor Marcel   **/
/**   Problema D - Randomly-priced Tickets                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d5707455fe801691225a/view?index=3   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define INFINITE 0x3f3f3f3f
#define MAX_N 105
#define MAX_C 10005
#define debug_off 1

using namespace std;

int N, R, C, a, b, m, testCasesCount;
int graph[MAX_N][MAX_N];
double dynamicProgrammingTable[MAX_N][MAX_C]; /* [length][cost] */

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, inner_loop;
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
    printf(" R=%d;\n",R);
    printf(" Graph:\n ");
    for (loop=0; loop<N; loop++) {
        for (inner_loop=0; inner_loop<N; inner_loop++) {
            printf(" %d",graph[loop][inner_loop]);
        }
        printf("\n ");
    }
}
#endif

void applyFloydWarshall () {
    int loop, inner_loop, outer_loop;
    for (outer_loop=0; outer_loop<N; outer_loop++) {
        for (loop=0; loop<N; loop++) {
            for (inner_loop=0; inner_loop<N; inner_loop++) {
                graph[loop][inner_loop] = min(graph[loop][inner_loop], graph[loop][outer_loop] + graph[outer_loop][inner_loop]);
            }
        }
    }
}

void calculatePossibilities () {
    int loop, inner_loop, outer_loop;
    dynamicProgrammingTable[0][0] = 1;
    for (outer_loop=0; outer_loop<=N; outer_loop++) {
        for (loop=0; loop<MAX_C; loop++) {
            if (dynamicProgrammingTable[outer_loop][loop] == 0)
                continue;
            for (inner_loop=1; inner_loop<=R && loop + inner_loop < MAX_C; inner_loop++) {
                dynamicProgrammingTable[outer_loop+1][loop + inner_loop] += dynamicProgrammingTable[outer_loop][loop] / R;
            }
        }
    }
}

int main () {
    int loop, inner_loop, outer_loop, distance;
    double cumulativeProbability;
    char sArg[MAX_N];

    #ifdef debug_on
        printf("\n| C17.D - Randomly-priced Tickets |\n");
    #endif

    /* read first dataset arguments */
    scanf("%d", &testCasesCount);
    for (outer_loop=0; outer_loop<testCasesCount; outer_loop++) {
        /* init */
        memset(dynamicProgrammingTable, 0, sizeof(dynamicProgrammingTable));

        /* read program arguments */
        scanf("%d %d", &N, &R);
        for (loop=0; loop<N; loop++) {
            scanf("%s", sArg);
            for (inner_loop=0; inner_loop<N; inner_loop++)
                graph[loop][inner_loop] = (sArg[inner_loop] == 'Y' ? 1 : INFINITE);
        }

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        applyFloydWarshall(); /* check for indirect bounds */
        calculatePossibilities();
        printf("Case %d\n", outer_loop+1);
        scanf("%d", &C);
        for (loop=0; loop<C; loop++) {
            scanf("%d %d %d", &a, &b, &m);
            a--;
            b--;
            distance = graph[a][b];
            cumulativeProbability = 0;
            if (distance == INFINITE) {
                cumulativeProbability = 0;
            }
            else {
                for (inner_loop=m; inner_loop>=0; inner_loop--) {
                    cumulativeProbability += dynamicProgrammingTable[distance][inner_loop];
                }
            }
            printf("%.6lf\n", cumulativeProbability);
        }
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}