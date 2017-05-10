/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 20                   Professor Marcel   **/
/**   Problema B - Interval Product                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d5af7455fe8016912915/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <vector>
#include <algorithm>
#include <utility>
#include <iomanip>
#define MAX_SEGTREE 1001000
#define debug_off 1

using namespace std;

int N, K;
int sequence[MAX_SEGTREE];
int segTree[MAX_SEGTREE];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
    printf(" K=%d;\n",K);
    printf(" Sequence:\n");
    for (loop=1; loop<=N; loop++) {
        printf("   Element: %d\n",scores[loop]);
    }
}

void printSegTree () {
    for (int i=0; i<pow(2, log2(n)+1); i++)
        cout << segTree[i] << ' ';
    cout << endl << endl;
}
#endif

void initSegTree (int left, int right, int node) {
    if (left > right)
        return;

    if (left == right) {
        segTree[node] = sequence[right];
    }
    else {
        initSegTree(left, (left + right)/2, 2 * node + 1);
        initSegTree((left + right)/2 + 1, right, 2 * node + 2);
        #ifdef debug_on
            cout << node << ' ' << 2 * node + 1 << ' ' << 2 * node + 2 << endl;
        #endif
        segTree[node] = segTree[2 * node + 1] * segTree[2 * node + 2];
    }
}

void updateSegTree (int node, int left, int right, int x){

    if (left > right || left > x || right < x)
        return;

    if (left == right) {
        segTree[node] = sequence[left];
        return;
    }

    updateSegTree (2*node+1, left, (left + right)/2, x);
    updateSegTree (2*node+2, (left + right)/2+1, right, x);
    segTree[node] = segTree[2*node+1]*segTree[2*node+2];
}

int doQuery (int node, int left, int right, int i, int j) {
    int p1, p2;

    if (left > right || left > j || right < i)
        return -100;

    if (left >= i && right <= j)
        return segTree[node];

    p1 = doQuery(2 * node + 1, left, (left + right)/2, i, j); 
    p2 = doQuery(2 * node + 2, (left + right)/2 + 1, right, i, j);

    #ifdef debug_on
        cout << p1 << ' ' << left << ' ' << right << ' ' << i << ' ' << j << endl;
    #endif

    if (p1 != -100 && p2 != -100)
        return p1 * p2;
    else if (p1 == -100)
        return p2;
    else
        return p1;
}

int main () {
    int loop, result;
    int argOne, argTwo;
    char command;

    #ifdef debug_on
        printf("\n| C20.B - Interval Product |\n");
    #endif

    while (true) {
        /* read program arguments */
        cin >> N >> K;
        if (!cin)
            break;
        for (loop=0; loop<N; loop++) {
            cin >> sequence[loop];
            if (sequence[loop] > 0)
                sequence[loop] = 1;
            else if (sequence[loop] < 0)
                sequence[loop] = -1;
        }

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
        initSegTree(0, N-1, 0);
        
        #ifdef debug_on
            printSegTree();
        #endif

        for (loop=0; loop<K; loop++){
            cin >> command >> argOne >> argTwo;

            #ifdef debug_on
                printSegTree();
            #endif

            if (command == 'C'){
                // Command "change": updating the segTree...
                if (argTwo > 0)
                    sequence[argOne-1] = 1;
                else if (argTwo < 0)
                    sequence[argOne-1] = -1;
                else
                    sequence[argOne-1] = 0;
                updateSegTree(0, 0, N-1, argOne-1);
            }
            else {
                // Command "product": doing the query... 
                result = doQuery(0, 0, N-1, argOne-1, argTwo-1);
                if (result == 0)
                    cout << '0';
                else if (result > 0)
                    cout << '+';
                else
                    cout << '-';
                #ifdef debug_on
                    cout << endl;
                #endif
            }
        }
        cout << endl;

    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
