/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 13                   Professor Marcel   **/
/**   Problema B - Restoring Painting                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57526ebcbd5f641300c9b205/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int n, a, b, c, d;
long long result;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n a=%d;\n b=%d;\n c=%d;\n d=%d;\n", n, a, b, c, d);
}
#endif

int main () {
    int firstVar, secondVar, thirdVar, fourthVar;

    #ifdef debug_on
        printf("\n| C13.B - Restoring Painting |\n");
    #endif

    /* read program arguments */
    scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    result = 0;
    for (firstVar=1; firstVar<=n; firstVar++) {
        secondVar = firstVar + b - c; /* x + a + b = a + y + c */
        thirdVar = firstVar + a - d; /* x + a + b = b + z + d */
        fourthVar = firstVar + a + b - c - d; /* x + a + b = c + d + w */
        if (secondVar<=0 || secondVar>n)
            continue; /* do not increase result */
        if (thirdVar<=0 || thirdVar>n)
            continue; /* do not increase result */
        if (fourthVar<=0 || fourthVar>n)
            continue; /* do not increase result */
        result++;
    }
    result = result * n;
    printf("%lld\n",result);

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}