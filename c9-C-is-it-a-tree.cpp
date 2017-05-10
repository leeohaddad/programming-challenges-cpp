/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 9                    Professor Marcel   **/
/**   Problema C - Is it a tree                                    Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c321f6fa9de49e5c7984/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N 10005
#define debug_off 1

using namespace std;

int N, M, connected;
set<int> edges[MAX_N];
int visitedEdge[MAX_N][MAX_N];
int visited[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
    printf(" M=%d;\n",M);
}
#endif

int checkCycles (int index) {
    set<int>::iterator setIterator;
    connected++;
    visited[index] = 1;
    for (setIterator=edges[index].begin(); setIterator!=edges[index].end(); setIterator++) {
        if (visitedEdge[index][*setIterator] == 0 && visitedEdge[*setIterator][index] == 0) {
            visitedEdge[index][*setIterator] = 1;
            visitedEdge[*setIterator][index] = 1;
            if (visited[*setIterator] == 1)
                return 1;
            if (checkCycles(*setIterator) == 1)
                return 1;   
        }
    }
    return 0;
}

int main () {
    int loop, innerLoop, arg, secondArg;
    
    #ifdef debug_on
        printf("\n| C9.C - Is it a tree |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &N, &M);
    if (M != N - 1) {
        printf("NO\n");
        return 0;
    }
    for (loop=0; loop<M; loop++) {
        scanf("%d", &arg);
        scanf("%d", &secondArg);
        edges[arg-1].insert(secondArg-1);
        edges[secondArg-1].insert(arg-1);
        visited[loop] = 0;        
    }
    visited[M] = 0;
    for (loop=0; loop<N; loop++) {
        for (innerLoop=0; innerLoop<N; innerLoop++) {
            visitedEdge[loop][innerLoop] = 0;
        }
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    connected = 0;
    if (checkCycles(0) == 0 && connected == N)
        printf("YES\n");
    else
        printf("NO\n");
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}