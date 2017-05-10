/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 9                    Professor Marcel   **/
/**   Problema A - Kefa and Park                                   Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce7f921926e63b4dafda/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 100005
#define debug_off 1

using namespace std;

int n, m;
int hasCat[MAX_N];
int nodeWasVisited[MAX_N];
set<int> adjacentNodes[MAX_N];
set<int> possibleLeaves;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    set<int>::iterator setIterator;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" m=%d;\n",m);
    for (loop=0; loop<n; loop++)
        printf("  %d", hasCat[loop]);
    printf("\n");
    for (loop=0; loop<n; loop++) {
        printf("  Adjacency for #%d:",loop);
        for (setIterator=adjacentNodes[loop].begin(); setIterator!=adjacentNodes[loop].end(); setIterator++)
            printf(" %d",*setIterator);
        printf("\n");
    }
}
#endif

void countPossibleLeaves (int node, int catsCount) {
    int availableNodes;
    set<int>::iterator setIterator;
    if (nodeWasVisited[node] == 1)
        return;
    nodeWasVisited[node] = 1;
    if (hasCat[node])
        catsCount++;
    else
        catsCount = 0;
    #ifdef debug_on
        printf("  At node %d, the catsCount is %d\n",node,catsCount);
    #endif
    if (catsCount > m)
        return;
    availableNodes = 0;
    for (setIterator=adjacentNodes[node].begin(); setIterator!=adjacentNodes[node].end(); setIterator++)
        if (nodeWasVisited[*setIterator] == 0)
            availableNodes++;
    if (availableNodes == 0) {
        possibleLeaves.insert(node);
        #ifdef debug_on
            printf("   It's possible to visit restaurant at leave %d\n",node);
        #endif
    }
    else
        for (setIterator=adjacentNodes[node].begin(); setIterator!=adjacentNodes[node].end(); setIterator++)
            countPossibleLeaves(*setIterator,catsCount);
}

int main () {
    int loop, arg, secondArg;

    #ifdef debug_on
        printf("\n| C9.A - Kefa and Park |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &n, &m);
    for (loop=0; loop<n; loop++) {
        scanf("%d", &arg);
        hasCat[loop] = arg;
        nodeWasVisited[loop] = 0;
    }
    for (loop=1; loop<n; loop++) {
        scanf("%d %d", &arg, &secondArg);
        adjacentNodes[arg-1].insert(secondArg-1);
        adjacentNodes[secondArg-1].insert(arg-1);
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    countPossibleLeaves(0,0);
    printf("%d\n",(int)possibleLeaves.size());

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}