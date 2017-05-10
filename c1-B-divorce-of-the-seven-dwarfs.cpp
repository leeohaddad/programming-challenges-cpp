/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema B - Divorce of the Seven Dwarfs                     Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c4f6fa9de49e5c64d8/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int main () {
    int arg, multiple, reading;

    #ifdef debug_on
        printf("\n| C1.B - Divorce of the Seven Dwarfs |\n");
    #endif

    multiple = 0;
    /* read program arguments */
    reading = scanf("%1d", &arg);
    while (reading == 1)
    {
        multiple = 10*multiple + arg;
        multiple = multiple%7;
        #ifdef debug_on
            printf("Arg: %d\n",arg);
            printf("Multiple: %d\n",multiple);
        #endif
        /* read program arguments */
        reading = scanf("%1d", &arg);
    }
    
    #ifdef debug_on
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    printf("%d\n",multiple);

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}