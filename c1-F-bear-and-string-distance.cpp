/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema F - Bear and String Distance                        Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57526ee9bd5f641300c9b2b3/view?index=5   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int n, k;
vector<char> elements;

#ifdef debug_on
/* print arguments */
void printArgs () {
    unsigned int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" k=%d;\n",k);
    printf(" elements:\n");
    for (loop=0; loop<elements.size(); loop++)
        printf("  %c\n",elements[loop]);
}
#endif

int main () {
   int loop;
   unsigned int u_loop;
   char arg;
   vector<char> result;

    #ifdef debug_on
        printf("\n| C1.F - Bear and String Distance |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &n, &k);
    scanf("%c", &arg);
    for (loop=0; loop<n; loop++) {
        scanf("%c", &arg);
        elements.push_back(arg);
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    for (u_loop=0; u_loop<elements.size(); u_loop++)
    {
        if (k == 0) {
            result.push_back(elements[u_loop]);
        }
        else {
            if (abs('a' - elements[u_loop]) > abs('z' - elements[u_loop])) {
                if (abs('a' - elements[u_loop]) < k) {
                    k = k - abs('a' - elements[u_loop]);
                    result.push_back('a');
                }
                else {
                    result.push_back(elements[u_loop] - k);
                    k = 0;
                }
            }
            else {
                if (abs('z' - elements[u_loop]) < k) {
                    result.push_back('z');
                    k = k - abs('z' - elements[u_loop]);
                }
                else {
                    result.push_back(elements[u_loop] + k);
                    k = 0;
                }
            }
        }
    }
    if (k > 0)
        printf("%d\n",-1);
    else {
        for (u_loop=0; u_loop<result.size(); u_loop++)
            printf("%c",result[u_loop]);
        printf("\n");
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}