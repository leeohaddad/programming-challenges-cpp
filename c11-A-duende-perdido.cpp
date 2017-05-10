/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 11                   Professor Marcel   **/
/**   Problema A - Duende Perdido                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2b5f6fa9de49e5c4f06/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N 15
#define MAX_M 15
#define ESCAPE 0
#define WAY 1
#define CRYSTAL 2
#define START 3
#define debug_off 1

using namespace std;

int N, M;
int caverna[MAX_N][MAX_M];
int d[MAX_N][MAX_M][MAX_N][MAX_M];
set< pair<int,int> > escapePoints;
queue< pair< pair<int,int> , int > > nextSearches;
int wasVisited[MAX_N][MAX_M];
int minimumDistance;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, inner_loop;
    printf("Arguments:\n");
    printf(" N=%d;\n M=%d;\n",N,M);
    printf(" Cave:\n");
    for (loop=0; loop<N; loop++) {
        for (inner_loop=0; inner_loop<M; inner_loop++) {
            printf("  %d", caverna[loop][inner_loop]);
        }
        printf("\n");
    }
}
#endif

int adaptedMin (int first, int second) {
    #ifdef debug_on_lvl2
        printf("    adaptedMin(%d,%d)\n",first,second);
    #endif
    if (first == 0)
        return second;
    if (first < second)
        return first;
    else return second;
}

void calculateDistancesFloydWarshall () {
    int kx, ky, ix, iy, jx, jy;
    for (kx=0; kx<N; kx++)
    for (ky=0; ky<M; ky++)
        for (ix=0; ix<N; ix++)
        for (iy=0; iy<M; iy++)
            for (jx=0; jx<N; jx++)
            for (jy=0; jy<M; jy++)
                if (d[ix][iy][kx][ky] != 0 && d[kx][ky][jx][jy] != 0)
                    d[ix][iy][jx][jy] = adaptedMin(d[ix][iy][jx][jy], d[ix][iy][kx][ky] + d[kx][ky][jx][jy]);
}

void breadthFirstSearch (int elementI, int elementJ, int dist) {
    #ifdef debug_on
        printf("breadthFirstSearch: (%d , %d): distance is %d\n",elementI,elementJ,dist);
    #endif
    if (elementI > 0 && wasVisited[elementI-1][elementJ] == 0) {
        wasVisited[elementI-1][elementJ] = 1;
        if (caverna[elementI-1][elementJ] == 1)
            nextSearches.push(make_pair(make_pair(elementI-1,elementJ),dist+1));
        else if (caverna[elementI-1][elementJ] == 0)
                if (dist+1 < minimumDistance)
                    minimumDistance = dist+1;
    }
    if (elementI < N-1 && wasVisited[elementI+1][elementJ] == 0) {
        wasVisited[elementI+1][elementJ] = 1;
        if (caverna[elementI+1][elementJ] == 1)
            nextSearches.push(make_pair(make_pair(elementI+1,elementJ),dist+1));
        else if (caverna[elementI+1][elementJ] == 0)
                if (dist+1 < minimumDistance)
                    minimumDistance = dist+1;
    }
    if (elementJ > 0 && wasVisited[elementI][elementJ-1] == 0) {
        wasVisited[elementI][elementJ-1] = 1;
        if (caverna[elementI][elementJ-1] == 1)
            nextSearches.push(make_pair(make_pair(elementI,elementJ-1),dist+1));
        else if (caverna[elementI][elementJ-1] == 0)
                if (dist+1 < minimumDistance)
                    minimumDistance = dist+1;
    }
    if (elementJ < M-1 && wasVisited[elementI][elementJ+1] == 0) {
        wasVisited[elementI][elementJ+1] = 1;
        if (caverna[elementI][elementJ+1] == 1)
            nextSearches.push(make_pair(make_pair(elementI,elementJ+1),dist+1));
        else if (caverna[elementI][elementJ+1] == 0)
                if (dist+1 < minimumDistance)
                    minimumDistance = dist+1;
    }
    if (nextSearches.size() > 0) {
        elementI = nextSearches.front().first.first;
        elementJ = nextSearches.front().first.second;
        dist = nextSearches.front().second;
        nextSearches.pop();
        breadthFirstSearch(elementI, elementJ, dist);
    }
}

int main () {
    int arg, loop, inner_loop, initialI, initialJ;
    /* int escapeI, escapeJ, minDistance, currentDistance; */
    set< pair<int,int> >::iterator pairSetIterator;

    #ifdef debug_on
        printf("\n| C11.A - Duende Perdido |\n");
    #endif

    /* read program arguments */
    scanf("%d", &N);
    scanf("%d", &M);
    for (loop=0; loop<N; loop++) {
        for (inner_loop=0; inner_loop<M; inner_loop++) {
            scanf("%d", &arg);
            caverna[loop][inner_loop] = arg;
            if (arg == ESCAPE) {
                escapePoints.insert(make_pair(loop, inner_loop));
            } 
            else if (arg == START) {
                initialI = loop;
                initialJ = inner_loop;
            }
            if (arg != CRYSTAL) {
                if (loop > 0 && caverna[loop-1][inner_loop] != CRYSTAL) {
                    d[loop][inner_loop][loop-1][inner_loop] = 1;
                    d[loop-1][inner_loop][loop][inner_loop] = 1;
                }
                if (inner_loop > 0 && caverna[loop][inner_loop-1] != CRYSTAL) {
                    d[loop][inner_loop][loop][inner_loop-1] = 1;
                    d[loop][inner_loop-1][loop][inner_loop] = 1;
                }
            }
        }
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    minimumDistance = N*M;
    breadthFirstSearch(initialI, initialJ, 0);
    /* calculateDistancesFloydWarshall();
    minDistance = N*M;
    for (pairSetIterator=escapePoints.begin(); pairSetIterator!=escapePoints.end(); pairSetIterator++) {
        escapeI = (*pairSetIterator).first;
        escapeJ = (*pairSetIterator).second;
        currentDistance = d[initialI][initialJ][escapeI][escapeJ];
        #ifdef debug_on
            printf("  Escape: %d, %d; Distance: %d\n",escapeI,escapeJ,currentDistance);
        #endif
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
        }
    }
    printf("%d\n",minDistance); */
    printf("%d\n",minimumDistance);
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}