/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 20                   Professor Marcel   **/
/**   Problema C - Jupiter Attacks!                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d59f7455fe80169127c6/view?index=2   **/
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
#define MAX_N 100005
#define debug_off 1

using namespace std;

int B, P, L, N;
int fenwickTree[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" B=%d;\n P=%d;\n L=%d;\n N=%d;\n", B, P, L, N);
}
#endif

int intModP (int a) {
    return ((a % P) + P) % P;
}

void addValue (int bytePosition, int value) {
    value = value % P;
    for (bytePosition = bytePosition + 1; bytePosition < MAX_N; bytePosition = bytePosition + (bytePosition & -bytePosition)) {
        fenwickTree[bytePosition] = intModP(fenwickTree[bytePosition] + value);
    }
}

int doQuery (int where) {
    int result = 0;
    for (where = where + 1; where > 0; where = where - (where & -where)) {
        result = intModP(result + fenwickTree[where]);
    }
    return result;
}

int at (int a) {
    return intModP(doQuery(a) - doQuery(a - 1));
}

/* this one was too slow */
/* int intPowerKeepingModP (int a, int b) {
    int result, loop;
    if (b == 0)
        return 1;
    result = 1;
    for (loop=0; loop<b; loop++)
        result = (1LL * result * a) % P;
    return result;
} */

int intPowerKeepingModP (int a, int b) {
    if (b == 0)
        return 1;
    if (b & 1) { /* b is odd, cannot be divided by 2 */
        return (1LL * a * intPowerKeepingModP(a, b - 1)) % P;
    } else { /* uses property a^b = a^(b/2)^2 */
        int half = intPowerKeepingModP(a, b / 2);
        return (1LL * half * half) % P;
    }
}

int main () {
    int scanResult, I, V, J, modP, powered, result;
    char command, trash;

    #ifdef debug_on
        printf("\n| C20.C - Jupiter Attacks! |\n");
    #endif

    while (true) {
        /* read case arguments */
        scanResult = scanf(" %d %d %d %d ", &B, &P, &L, &N);
        if (scanResult < 4 || ((B == 0 && P == 0 && L == 0 && N == 0)))
            break;

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
        memset(fenwickTree, 0, sizeof fenwickTree);
        while (N--) {
            /* read simulation arguments */
            scanf("%c", &command);
            if (command == 'E') {
                scanf("%d %d", &I, &V);
                #ifdef debug_on
                    printf("  Editing: %c %d %d\n", command, I, V);
                #endif
                addValue(I, -at(I));
                addValue(I, (1LL * V * intPowerKeepingModP(B, L - I)) % P);
                scanf("%c", &trash);
            } else {
                scanf("%d %d", &I, &J);
                #ifdef debug_on
                    printf("  Hash Command: %c %d %d\n", command, I, J);
                #endif
                modP = intModP(doQuery(J) - doQuery(I - 1));
                powered = intPowerKeepingModP(B, L - J);
                result = (1LL * modP * intPowerKeepingModP(powered, P - 2)) % P;
                printf("%d\n", result);
                scanf("%c", &trash);
            }
        }
        printf("-\n");
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}