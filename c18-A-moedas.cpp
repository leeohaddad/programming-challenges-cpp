/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 18                   Professor Marcel   **/
/**   Problema A - Moedas                                          Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2b5f6fa9de49e5c4eca/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_M 50005
#define MAX_N 100
#define debug_off 1

using namespace std;

int n, m;
int coins[MAX_N];
int requiredCoins[MAX_M]; /* dynamicProgrammingVector */

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" m=%d;\n",m);
    printf(" n=%d;\n",n);
    printf(" Coins:\n");
    for (loop=0; loop<n; loop++)
        printf("   %d\n", coins[loop]);
}
#endif

int main () {
    int loop, inner_loop;

    #ifdef debug_on
        printf("\n| C18.A - Moedas |\n");
    #endif

    scanf("%d", &m);
    while (m != 0) {
        /* init */
        memset(requiredCoins, 0, sizeof(requiredCoins));

        /* read program arguments */
        scanf("%d", &n);
        for (loop=0; loop<n; loop++) {
            scanf("%d", &coins[loop]);
            requiredCoins[coins[loop]] = 1;
        }
    
        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        for (loop=1; loop<=m; loop++){
            if (requiredCoins[loop] > 0) {
                for (inner_loop=0; inner_loop<n; inner_loop++){
                    if (loop + coins[inner_loop] > m)
                        break;
                    if (requiredCoins[loop+coins[inner_loop]] == 0)
                        requiredCoins[loop+coins[inner_loop]] = requiredCoins[loop] + 1;
                    else
                        requiredCoins[loop+coins[inner_loop]] = min(requiredCoins[loop+coins[inner_loop]], requiredCoins[loop] + 1);
                }
            }
        }
        if (requiredCoins[m] > 0)
            printf("%d\n", requiredCoins[m]);
        else printf("Impossivel\n");
        
        scanf("%d", &m);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}