/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 13                   Professor Marcel   **/
/**   Problema A - Robot Sequence                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57526eedbd5f641300c9b2c2/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_N 205
#define U 85
#define D 68
#define R 82
#define L 76
#define UP_C 1000
#define DOWN_C -1000
#define RIGHT_C 1
#define LEFT_C -1
#define MY_SPOT 0
#define debug_off 1

using namespace std;

int n, substrings;
char sourceCode[MAX_N];
int codeCosts[MAX_N];
int costsDic[100];
int hasBeenCounted[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" Calvin's source code:\n");
    for (loop=0; loop<n; loop++) {
        printf("  %c (%d)", sourceCode[loop],codeCosts[loop]);
    }
}
#endif

void countSequences (int startIndex) {
    int loop, currentCheckSum;
    if (hasBeenCounted[startIndex] == 1)
        return;
    hasBeenCounted[startIndex] = 1;
    currentCheckSum = MY_SPOT + codeCosts[startIndex];
    for (loop=startIndex+1; loop<n; loop++) {
        currentCheckSum = currentCheckSum + codeCosts[loop];
        if (currentCheckSum == MY_SPOT)
            substrings++;
        countSequences(loop);
    }
}

int main () {
    int loop;
    char arg;

    #ifdef debug_on
        printf("\n| C13.A - Robot Sequence |\n");
    #endif

    /* init */
    costsDic[U] = UP_C;
    costsDic[D] = DOWN_C;
    costsDic[R] = RIGHT_C;
    costsDic[L] = LEFT_C;

    /* read program arguments */
    scanf("%d", &n);
    scanf("%c", &arg);
    for (loop=0; loop<n; loop++) {
        scanf("%c", &arg);
        sourceCode[loop] = arg;
        codeCosts[loop] = costsDic[(int)arg];
        hasBeenCounted[loop] = 0;
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    substrings = 0;
    countSequences(0);
    printf("%d\n",substrings);
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}