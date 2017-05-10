/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 22                   Professor Marcel   **/
/**   Problema B - Philosophers Stone                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c345f6fa9de49e5c7de1/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
#include <stdio.h>
// #include <cstdlib>
// #include <cmath> 
// #include <cstring>
// #include <set>
// #include <vector>
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX 105
#define debug_off 1

int T, h, w;
int dpTable[MAX][MAX]; /* dynammicProgrammingTable */

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" h=%d;\n h=%d;\n",h,w);
}
#endif

int maxThreeInts(int first, int second, int third)
{
    if (first >= second && first >= third)
        return first;
    if (second >= third)
        return second;
    return third;
}

int main () {
    int maxPossibleStones, loop, innerLoop;

    #ifdef debug_on
        printf("\n| C22.B - Philosophers Stone |\n");
    #endif

    /* read #cases */
    scanf("%d", &T);
    while (T--) {
        /* read case arguments */
        scanf("%d %d", &h, &w);

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
        for (loop=1; loop<=h; loop++)
        {
            for (innerLoop=1; innerLoop<=w; innerLoop++)
                scanf("%d", &dpTable[loop][innerLoop]);
            dpTable[loop][innerLoop] = 0;
            for (innerLoop=1; innerLoop<=w; innerLoop++)
                dpTable[loop][innerLoop] += maxThreeInts(dpTable[loop-1][innerLoop-1], dpTable[loop-1][innerLoop], dpTable[loop-1][innerLoop+1]);
        }
        maxPossibleStones = dpTable[h][1];
        for (loop=2; loop<=w; loop++)
            maxPossibleStones = maxThreeInts(maxPossibleStones, dpTable[h][loop], 0);
        printf("%d\n", maxPossibleStones);
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}