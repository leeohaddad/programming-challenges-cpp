/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 18                   Professor Marcel   **/
/**   Problema C - Equal Sum Sets                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d5bb7455fe8016912a7c/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N 25
#define MAX_K 15
#define MAX_S 160
#define debug_off 1

using namespace std;

int n, k, s;
int setsRegistry[MAX_N][MAX_K][MAX_S];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

int countSets (int N, int K, int S) {
    if (S < 0 || K < 0)
        return 0;
    if (N == 0)
        return ((S == 0 && K == 0) ? 1 : 0);
    if (setsRegistry[N][K][S] == -1)
        setsRegistry[N][K][S] = countSets(N-1, K, S) + countSets(N-1, K-1, S-N);
    return setsRegistry[N][K][S];
}

int main () {
    #ifdef debug_on
        printf("\n| C18.C - Equal Sum Sets |\n");
    #endif

    /* read first dataset arguments */
    scanf("%d %d %d", &n, &k, &s);
    while (n+k+s > 0) {
        /* init */
        memset(setsRegistry, -1, sizeof(setsRegistry));

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        printf("%d\n", countSets(n, k, s));
        
        /* read next dataset arguments */
        scanf("%d %d %d", &n, &k, &s);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}