/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema D - Copying                                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c0f6fa9de49e5c61e8/view?index=3   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#define debug_off 1

using namespace std;

long long N, K;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" N=%lld;\n",N);
    printf(" K=%lld;\n",K);
}
#endif

int main () {
    /* int installed, willInstall, timeInHours; */
    int nBuilder, geometricProgressionPart, wireLimitsPart;

    #ifdef debug_on
        printf("\n| C2.D - Copying |\n");
    #endif

    /* read program arguments */
    scanf("%lld", &N);
    scanf("%lld", &K);
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    geometricProgressionPart = 0;
    nBuilder = 1;
    while (nBuilder < K && 2*nBuilder < N) {
        geometricProgressionPart++;
        nBuilder = nBuilder * 2;
    }
    wireLimitsPart = (N - nBuilder)/K;
    if ((N - nBuilder)%K)
        wireLimitsPart++;

    /* timeInHours = 0;
    installed = 1;
    while (installed < N) {
        willInstall = K;
        if (installed < willInstall)
            willInstall = installed;
        if (N - installed < willInstall)
            willInstall = N - installed;
        installed = installed + willInstall;
        timeInHours++;
    } */

    /* output */
    printf("%d\n",geometricProgressionPart+wireLimitsPart);
    /* printf("%d\n",timeInHours); */

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}