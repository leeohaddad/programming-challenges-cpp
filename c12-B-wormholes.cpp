/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 12                   Professor Marcel   **/
/**   Problema B - Wormholes                                       Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2b8f6fa9de49e5c51bb/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_N 1005
#define MAX_M 2005
#define MAX_INT 2147483647
#define debug_off 1

using namespace std;

int c, n, m;
int wormholes[MAX_M][3];
int distances[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" m=%d;\n",m);
    printf(" wormholes:\n");
    for (loop=0; loop<m; loop++)
        printf("  %d %d %d\n", *(wormholes[0]), *(wormholes[1]), *(wormholes[2]));
}
#endif

bool checkPossibilityThroughBellmanFord () {
    int loop, inner_loop;
    bool foundAnyNegativeCicle = false;

    /* check distances */
    for (loop=0; loop<=n; loop++)
        distances[loop] = MAX_INT;
    distances[0] = 0; 
    for (loop=0; loop<n-1; loop++) {
        for (inner_loop=0; inner_loop<m; inner_loop++) {
            if (distances[wormholes[inner_loop][0]] + wormholes[inner_loop][2] < distances[wormholes[inner_loop][1]] )
                distances[wormholes[inner_loop][1]] = distances[wormholes[inner_loop][0]] + wormholes[inner_loop][2];
        }
    }
    
    /* search for negative cycles */
    for (loop=0; loop<m; loop++) {
        if (distances[wormholes[loop][0]] + wormholes[loop][2] < distances[wormholes[loop][1]])
            foundAnyNegativeCicle = true;
    }
    return foundAnyNegativeCicle;
}

int main () {
   int loop, outer_loop;

    #ifdef debug_on
        printf("\n| C12.B - Wormholes |\n");
    #endif

    scanf("%d", &c);
    for (outer_loop=0; outer_loop<c; outer_loop++) {
        /* read program arguments */
        scanf("%d %d", &n, &m);
        for (loop=0; loop<m; loop++) {
            scanf ("%d %d %d", &wormholes[loop][0], &wormholes[loop][1], &wormholes[loop][2]);
        }

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        if (checkPossibilityThroughBellmanFord() == true)
            printf ("possible\n");
        else
            printf ("not possible\n");
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}