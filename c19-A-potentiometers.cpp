/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 19                   Professor Marcel   **/
/**   Problema A - Potentiometers                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d52a7455fe8016911a1e/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#define MAX_STRINPUT 200
#define MAX_SEGTREE 2000005
#define debug_off 1

using namespace std;

int N;
int segTree[MAX_SEGTREE];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
}
#endif

void updateSegTree (int where, int value, int realPositionInSTrray, int begin, int end) {
    if (begin == end)
        segTree[realPositionInSTrray] = value;
    else {
        int half = (begin + end) / 2;
        if (where <= half)
            updateSegTree(where, value, 2 * realPositionInSTrray, begin , half);
        else
            updateSegTree(where, value, (2 * realPositionInSTrray) + 1, half + 1, end);
        segTree[realPositionInSTrray] = segTree[2 * realPositionInSTrray] + segTree[(2 * realPositionInSTrray) + 1];
    }
}

int doQuery (int from, int to, int realPositionInSTrray, int begin, int end) {
    if(from > end || to < begin)
        return 0;
    if(from <= begin && end <= to)
        return segTree[realPositionInSTrray];
    int half = (begin+end) / 2;
    return doQuery(from, to, 2 * realPositionInSTrray, begin , half) + doQuery(from, to , 2 * realPositionInSTrray + 1, half +1 , end);
}

int main () {
    int loop, arg, x, y, r, caseCount;
    char strArg[MAX_STRINPUT];
    bool shouldKeepGoing = true;
    bool isFirstLoop = true;

    #ifdef debug_on
        printf("\n| C19.A - Potentiometers |\n");
    #endif

    caseCount = 0;
    while (shouldKeepGoing) {
        /* read case arguments */
        scanf("%d", &N);
        if (N > 0) {
            memset(segTree, 0, sizeof(segTree));
            for (loop=1 ; loop<=N; loop++) {    
                scanf("%d", &arg);
                updateSegTree(loop, arg, 1, 1, N);
            }

            #ifdef debug_on
                printArgs();
                printf("\nProblem Solution:\n");
            #endif
        
            /* solution */
            if (isFirstLoop)
                isFirstLoop = false;
            else
                printf("\n");
            printf("Case %d:\n", ++caseCount);
            while (scanf("%s", strArg) > 0) {
                if (strArg[0] == 'S') { /* SET */
                    scanf("%d %d", &x, &r);
                    updateSegTree(x, r, 1, 1, N);
                }
                else if(strArg[0] == 'M') { /* MEASURE */
                    scanf("%d %d", &x, &y);
                    printf("%d\n", doQuery(x, y, 1, 1, N));
                }
                else { /* END */
                    break;
                }
            }
        }
        else shouldKeepGoing = false;
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}