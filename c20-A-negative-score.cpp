/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 20                   Professor Marcel   **/
/**   Problema A - Negative Score                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c373f6fa9de49e5c82e9/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N_Q 100005
#define MAX_SEGTREE 300005
#define MAX_NUM 2000000005
#define debug_off 1

using namespace std;

long long T, N, Q, A, B;
long long segTree[MAX_SEGTREE];
long long scores[MAX_N_Q];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" N=%lld;\n",N);
    for (loop=1; loop<=N; loop++) {
        printf("   Score: %lld\n",scores[loop]);
    }
    printf(" Q=%lld;\n",Q);
}
#endif

long long longMin (long long a, long long b) { 
    return a < b ? a : b; 
}

/* inline functions are optimized by compiler */
inline void scanStdin (long long &a) { 
    char character = a = 0;
    int sign = 1; 
    while(character < 33)
        character = getc(stdin); 
    if (character == '-') {
        sign = -1;
        character = getc(stdin);   
    }
    while(character > 33) {
        a = a * 10 + character - '0';
        character = getc(stdin);   
    }
    a *= sign; 
}

void buildSegTree(int current, int rangeStart, int rangeEnd){ 
    if (rangeStart > rangeEnd)
        return; 
    if (rangeStart == rangeEnd) {
        segTree[current] = scores[rangeStart]; 
        return; 
    } 
    buildSegTree(current << 1, rangeStart, (rangeStart + rangeEnd) >> 1); 
    buildSegTree((current << 1) + 1,((rangeStart + rangeEnd) >> 1) + 1, rangeEnd); 
    segTree[current] = longMin(segTree[current << 1], segTree[(current << 1) + 1]);
} 
 
long long runQuery(int current, int rangeStart, int rangeEnd) {
    if(rangeStart > rangeEnd || A > rangeEnd || B < rangeStart) /* intersection is null */
        return MAX_NUM; 
    if(rangeStart >= A && rangeEnd <= B) /* [A,B] contains [rangeStart,rangeEnd] */
        return segTree[current]; 
    return longMin(runQuery(current << 1, rangeStart, (rangeStart + rangeEnd) >> 1), runQuery((current << 1) + 1,((rangeStart + rangeEnd) >> 1) + 1, rangeEnd)); 
}  

int main () {
    int loop, scenarioIndex;

    #ifdef debug_on
        printf("\n| C20.A - Negative Score |\n");
    #endif

    /* read number of cases */
    scanStdin(T);
    scenarioIndex = 1;
    while(T--) {

        /* read case arguments */
        scanStdin(N);
        scanStdin(Q);
        for(loop=1; loop<=N; loop++)
            scanStdin(scores[loop]);

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
        buildSegTree(1, 1, N);
        printf("Scenario #%d:\n", scenarioIndex++);
        while(Q--) {
            scanStdin(A);
            scanStdin(B);
            printf("%lld\n", runQuery(1, 1, N));
        }
    }
    return 0;

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
