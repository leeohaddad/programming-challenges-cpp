/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 10                   Professor Marcel   **/
/**   Problema C - Mr. Kitayuta's Colorful Graph                   Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce68921926e63b4daec6/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_NODES 105
#define MAX_EDGES 105
#define MAX_TESTS 105
#define debug_off 1

using namespace std;

int n, m, q;
vector<int> connections[MAX_EDGES][MAX_NODES];
vector< pair<int, int> > tests;
int visitedNodeAtColor[MAX_NODES][MAX_EDGES];

#ifdef debug_on
/* print arguments */
void printArgs () {
    vector< pair<int, int> >::iterator pairVectorIterator;
    printf("Arguments:\n");
    printf(" n=%d;\n m=%d;\n",n,m);
    printf(" q=%d;\n Tests:\n",q);
    for (pairVectorIterator=tests.begin(); pairVectorIterator!=tests.end(); pairVectorIterator++) {
        printf("  %d %d\n",(*pairVectorIterator).first,(*pairVectorIterator).second);
    }
}
#endif

int tryToReachThroughColor (int initial, int destiny, int color) {
    //vector<int> connections[MAX_EDGES][MAX_NODES];
    vector<int>::iterator vectorIterator;
    #ifdef debug_on
        printf("  Visiting node %d seeking node %d through color %d [#connections: %d] [visited: %d]!\n",initial,destiny,color,connections[color][initial].size(),visitedNodeAtColor[initial][color]);
        if (initial == destiny)
            printf("   Found it! Color %d is viable!\n",color);
    #endif
    if (initial == destiny)
        return 1;
    if (visitedNodeAtColor[initial][color] == 1)
        return 0;
    visitedNodeAtColor[initial][color] = 1;
    for (vectorIterator=connections[color][initial].begin(); vectorIterator!=connections[color][initial].end(); vectorIterator++) {
        if (tryToReachThroughColor(*vectorIterator, destiny, color) == 1)
            return 1;
    }
    return 0;
}

int main () {
    int a, b, c, loop, inner_loop, u, v, result;
    vector< pair<int, int> >::iterator pairVectorIterator;

    #ifdef debug_on
        printf("\n| C10.C - Mr. Kitayuta's Colorful Graph |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &n, &m);
    for (loop=0; loop<m; loop++) {
        scanf("%d %d %d", &a, &b, &c);
        connections[c][a].push_back(b);
        connections[c][b].push_back(a);
    }
    scanf("%d", &q);
    for (loop=0; loop<q; loop++) {
        scanf("%d %d", &u, &v);
        tests.push_back(make_pair(u,v));
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    for (pairVectorIterator=tests.begin(); pairVectorIterator!=tests.end(); pairVectorIterator++) {
        result = 0;
        for (loop=0; loop<=m; loop++) {
            #ifdef debug_on
                printf(" test: (%d -> %d); currentColor: %d\n",(*pairVectorIterator).first,(*pairVectorIterator).second,loop);
            #endif
            for (inner_loop=0; inner_loop<=n; inner_loop++)
                visitedNodeAtColor[inner_loop][loop] = 0;
            result = result + tryToReachThroughColor((*pairVectorIterator).first, (*pairVectorIterator).second, loop);   
        }
        printf("%d\n",result);
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}