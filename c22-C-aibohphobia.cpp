/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 22                   Professor Marcel   **/
/**   Problema C - Aibohphobia                                     Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c320f6fa9de49e5c797b/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <stdio.h>
// #include <cstdlib>
// #include <cmath> 
#include <cstring>
// #include <set>
// #include <vector>
#include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_STRING 6105
#define debug_off 1

using namespace std;

int t, len;
char S[MAX_STRING];
char inverse_S[MAX_STRING];
short dpTable[MAX_STRING][MAX_STRING]; /* dynammicProgrammingTable */

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" h=%d;\n h=%d;\n",h,w);
}
#endif

int main () {
    int loop, innerLoop;

    #ifdef debug_on
        printf("\n| C22.C - Aibohphobia |\n");
    #endif

    /* read #cases */
    scanf("%d", &t);
    getchar();
    
    while(t--) {
        /* read case arguments */
        fgets(S, MAX_STRING, stdin);
        len = strlen(S);
        S[len-1] = 0;
        len--;

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        strcpy(inverse_S, S);
        reverse(inverse_S, inverse_S+len);
        for (loop=0; loop<=len; loop++)
        {
            dpTable[loop][0]=0;
            dpTable[0][loop]=0;
        }
        for (loop=1; loop<=len; loop++)
            for (innerLoop=1; innerLoop<=len; innerLoop++)
                if (S[loop-1] == inverse_S[innerLoop-1])
                    dpTable[loop][innerLoop] = dpTable[loop-1][innerLoop-1]+1;
                else
                    dpTable[loop][innerLoop] = max(dpTable[loop-1][innerLoop], dpTable[loop][innerLoop-1]);
        printf("%d\n", len - dpTable[len][len]);
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
