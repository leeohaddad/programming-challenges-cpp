/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 18                   Professor Marcel   **/
/**   Problema D - Clique in the Divisibility Graph                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce81921926e63b4db013/view?index=3   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 1000005
#define debug_off 1

using namespace std;

int n;
int elementsOfSubsetA[MAX_N];
int position[MAX_N];
int dynamicProgrammingArray[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" elements from subset A:\n");
    for (loop=0; loop<n; loop++)
        printf("  %d", elementsOfSubsetA[loop]);
}
#endif

int main () {
    int loop, inner_loop, result;

    #ifdef debug_on
        printf("\n| C18.D - Clique in the Divisibility Graph |\n");
    #endif

    /* read program arguments */
    scanf("%d", &n);
    for (loop=1; loop<=n; loop++) {
        scanf("%d", &elementsOfSubsetA[loop]);
        position[elementsOfSubsetA[loop]] = loop;
        dynamicProgrammingArray[loop] = 1;   
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    for (loop=1; loop<=n; loop++) {
        for (inner_loop=elementsOfSubsetA[loop]*2; inner_loop<=elementsOfSubsetA[n]; inner_loop+=elementsOfSubsetA[loop]) {
            dynamicProgrammingArray[position[inner_loop]] = max(dynamicProgrammingArray[position[inner_loop]], dynamicProgrammingArray[loop] + 1);
        }
    }
    result = 0;
    for (loop=1; loop<=n; loop++) {
        result = max(result, dynamicProgrammingArray[loop]);
    }
    printf("%d\n", result);
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}