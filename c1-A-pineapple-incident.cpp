/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema A - Pineapple Incident                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57887c2de7519413002a36ef/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int t, s, x;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" t=%d;\n s=%d;\n x=%d;\n",t,s,x);
}
#endif

int main () {
    int delta, mod;

    #ifdef debug_on
        printf("\n| C1.A - Pineapple Incident |\n");
    #endif

    /* read program arguments */
    scanf("%d %d %d", &t, &s, &x);
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (x < t)
        printf("NO\n");
    else {
        delta = x - t;
        mod = delta % s;
        if (delta == 1 && delta!=s)
            printf("NO\n");
        else if (mod <= 1)
            printf("YES\n");
        else
            printf("NO\n");
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}