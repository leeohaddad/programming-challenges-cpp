/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 9                    Professor Marcel   **/
/**   Problema B - Dungeon Master                                  Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2b8f6fa9de49e5c517d/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_LRC 35
#define debug_off 1

using namespace std;

int L, R, C;
int dungeonMap[MAX_LRC][MAX_LRC][MAX_LRC];
int spotWasQueued[MAX_LRC][MAX_LRC][MAX_LRC];
queue<int> queueA, queueB, queueC, minutesTrack;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, innerLoop, superDepthLoop;
    printf("Arguments:\n");
    printf(" L=%d;\n",L);
    printf(" R=%d;\n",R);
    printf(" C=%d;\n",C);
    printf("\n");
    for (loop=0; loop<L; loop++) {
        for (innerLoop=0; innerLoop<R; innerLoop++) {
            for (superDepthLoop=0; superDepthLoop<C; superDepthLoop++) {
                printf("%c",dungeonMap[loop][innerLoop][superDepthLoop]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
    }
}
#endif

void processQueue () {
    int a, b, c, minutes;
    a = queueA.front();
    queueA.pop();
    b = queueB.front();
    queueB.pop();
    c = queueC.front();
    queueC.pop();
    minutes = minutesTrack.front();
    minutesTrack.pop();
    #ifdef debug_on
        printf("  processQueue() -> a: %d, b: %d, c: %d, minutes: %d\n",a,b,c,minutes);
    #endif
    if (a > 0 && dungeonMap[a-1][b][c] != '#' && spotWasQueued[a-1][b][c] == 0) {
        if (dungeonMap[a-1][b][c] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a-1);
        queueB.push(b);
        queueC.push(c);
        minutesTrack.push(minutes+1);
        spotWasQueued[a-1][b][c] = 1;
    }
    if (a < L-1 && dungeonMap[a+1][b][c] != '#' && spotWasQueued[a+1][b][c] == 0) {
        if (dungeonMap[a+1][b][c] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a+1);
        queueB.push(b);
        queueC.push(c);
        minutesTrack.push(minutes+1);
        spotWasQueued[a+1][b][c] = 1;
    }
    if (b > 0 && dungeonMap[a][b-1][c] != '#' && spotWasQueued[a][b-1][c] == 0) {
        if (dungeonMap[a][b-1][c] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a);
        queueB.push(b-1);
        queueC.push(c);
        minutesTrack.push(minutes+1);
        spotWasQueued[a][b-1][c] = 1;
    }
    if (b < R-1 && dungeonMap[a][b+1][c] != '#' && spotWasQueued[a][b+1][c] == 0) {
        if (dungeonMap[a][b+1][c] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a);
        queueB.push(b+1);
        queueC.push(c);
        minutesTrack.push(minutes+1);
        spotWasQueued[a][b+1][c] = 1;
    }
    if (c > 0 && dungeonMap[a][b][c-1] != '#' && spotWasQueued[a][b][c-1] == 0) {
        if (dungeonMap[a][b][c-1] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a);
        queueB.push(b);
        queueC.push(c-1);
        minutesTrack.push(minutes+1);
        spotWasQueued[a][b][c-1] = 1;
    }
    if (c < C-1 && dungeonMap[a][b][c+1] != '#' && spotWasQueued[a][b][c+1] == 0) {
        if (dungeonMap[a][b][c+1] == 'E') {
            printf("Escaped in %d minute(s).\n",minutes+1);
            return;
        }
        queueA.push(a);
        queueB.push(b);
        queueC.push(c+1);
        minutesTrack.push(minutes+1);
        spotWasQueued[a][b][c+1] = 1;
    }
    if (queueA.size() > 0)
        processQueue();
    else
        printf("Trapped!\n");
}

int main () {
    int loop, innerLoop, superDepthLoop, finishedRun, SA=-1, SB=-1, SC=-1, EA=-1, EB=-1, EC=-1;
    char arg;

    #ifdef debug_on
        printf("\n| C9.B - Dungeon Master |\n");
    #endif

    finishedRun = 0;
    while (finishedRun == 0) {
        /* read program arguments */
        scanf("%d %d %d", &L, &R, &C);
        if (L == 0 && R == 0 && C == 0)
            return 0;
        scanf("%c", &arg);

        for (loop=0; loop<L; loop++) {
            for (innerLoop=0; innerLoop<R; innerLoop++) {

                    scanf(" %c", &arg);
                    dungeonMap[loop][innerLoop][0] = arg;
                    if (arg == 'S') {
                    
                        SA = loop;
                        SB = innerLoop;
                        SC = 0;
                    }
                    else if (arg == 'E') {
                        EA = loop;
                        EB = innerLoop;
                        EC = 0;
                    }
                    spotWasQueued[loop][innerLoop][0] = 0; 

                for (superDepthLoop=1; superDepthLoop<C; superDepthLoop++) {
                    scanf(" %c", &arg);
                    dungeonMap[loop][innerLoop][superDepthLoop] = arg;
                    if (arg == 'S') {
                    
                        SA = loop;
                        SB = innerLoop;
                        SC = superDepthLoop;
                    }
                    else if (arg == 'E') {
                        EA = loop;
                        EB = innerLoop;
                        EC = superDepthLoop;
                    }
                    spotWasQueued[loop][innerLoop][superDepthLoop] = 0;
                
                }
            }
        }

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        if (SA == -1 || SB == -1 || SC == -1)
            printf("Error!");
        else if (EA == -1 || EB == -1 || EC == -1) {
            printf("Trapped!\n");
        }
        else {
            queueA.push(SA);
            queueB.push(SB);
            queueC.push(SC);
            minutesTrack.push(0);
            spotWasQueued[SA][SB][SC] = 1;
            processQueue();   
        }
	while (queueA.size() > 0) {
            queueA.pop();
            queueB.pop();
            queueC.pop();
            minutesTrack.pop();
	}
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
