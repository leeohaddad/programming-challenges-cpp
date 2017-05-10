/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 10                   Professor Marcel   **/
/**   Problema A - Slick                                           Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c382f6fa9de49e5c848a/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define ZERO N*1*M
#define MAX_M_N 255
#define debug_off 1

using namespace std;

int N, M, uniqueSlickCount, partialCount;
int binaryMatrix[MAX_M_N][MAX_M_N];
int wasVisited[MAX_M_N][MAX_M_N];
int slicksCount[MAX_M_N*MAX_M_N];
set< pair<int,int> > unexplored;
set< pair<int,int> > exploring;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, innerLoop;
    set< pair<int,int> >::iterator setIterator;
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
    printf(" M=%d;\n",M);
    printf(" binaryMatrix=%d;\n",M);
    for (loop=0; loop<N; loop++) {
        for (innerLoop=0; innerLoop<M; innerLoop++) {
            printf("%d ",binaryMatrix[loop][innerLoop]);
        }
        printf("\n");
    }
    printf(" unexplored=%d;\n",(int)unexplored.size());
    for (setIterator=unexplored.begin(); setIterator!=unexplored.end(); setIterator++) {
        printf("(%d,%d) // ",(*setIterator).first,(*setIterator).second);
    }
    printf("\n");
}
#endif

void checkSlicks (int row, int col, int component) {
    wasVisited[row][col] = 1;
    unexplored.erase(make_pair(row,col));
    exploring.insert(make_pair(row,col));
    partialCount++;
    #ifdef debug_on
        if (component == 0) {
            printf("  starting new Component! (current count: %d)\n", uniqueSlickCount+1);
        }
        printf("   checkSlicks(%d, %d)\n", row, col);
    #endif
    if (row > 0 && wasVisited[row-1][col] < 1 && binaryMatrix[row-1][col] != 0)
        checkSlicks(row-1, col, component);
    if (row < N && wasVisited[row+1][col] < 1 && binaryMatrix[row+1][col] != 0)
        checkSlicks(row+1, col, component);
    if (col > 0 && wasVisited[row][col-1] < 1 && binaryMatrix[row][col-1] != 0)
        checkSlicks(row, col-1,  component);
    if (col < M && wasVisited[row][col+1] < 1 && binaryMatrix[row][col+1] != 0)
        checkSlicks(row, col+1,  component);
}

int main () {
    int arg, loop, innerLoop, totalAmmount, row, col;
    set< pair<int,int> >::iterator setIterator;

    #ifdef debug_on
        printf("\n| C10.A - Slick |\n");
    #endif

    while (1==1) {
        /* read program arguments */
        scanf("%d", &N);
        scanf("%d", &M);
        if (N == 0 && M == 0)
            break;
        slicksCount[ZERO] = 0;
        for (loop=0; loop<N; loop++) {
            for (innerLoop=0; innerLoop<M; innerLoop++) {
                scanf("%d", &arg);
                binaryMatrix[loop][innerLoop] = arg;
                wasVisited[loop][innerLoop] = 0;
                slicksCount[N*loop + innerLoop] = 0;
                if (arg != 0)
                    unexplored.insert(make_pair(loop,innerLoop));
                else
                    slicksCount[ZERO] = slicksCount[ZERO] + 1;
            }
        }

        /* init */
        uniqueSlickCount = 0;

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        while (unexplored.size() > 0) {
            partialCount = 0;
            row = unexplored.begin()->first;
            col = unexplored.begin()->second;
            checkSlicks(row, col, 0);
            if (partialCount > 0) {
                uniqueSlickCount++;
                #ifdef debug_on
                    printf("    uniqueSlickCount grew: %d\n",uniqueSlickCount);
                #endif
            }
            slicksCount[partialCount-1] = slicksCount[partialCount-1] + 1;
            #ifdef debug_on
                if (partialCount > 0)
                    printf("     currently we have %d components of size %d\n",slicksCount[partialCount-1],partialCount);
            #endif
        }
        totalAmmount = N*M;
        #ifdef debug_on
            printf("   totalAmmount: %d\n",totalAmmount);
            printf("   zeroQuantity: %d\n",slicksCount[ZERO]);
        #endif
        totalAmmount = totalAmmount - slicksCount[ZERO];
        loop = 0;
        printf("%d\n",uniqueSlickCount);
        while (totalAmmount > 0) {
            if (slicksCount[loop] > 0) {
                printf("%d %d\n", loop+1, slicksCount[loop]);
                totalAmmount = totalAmmount - slicksCount[loop]*(loop+1);
                #ifdef debug_on
                    printf("   decreacingAmmount by component %d: %d. Remaining: %d\n", loop+1, slicksCount[loop], totalAmmount);
                if (loop >= N*M && totalAmmount > 0) {
                    printf("Houston, whe have a problem!");
                    break;
                }
                #endif
            }
            loop++;
        }
        #ifdef debug_on
            if (totalAmmount > 0)
                printf("Houston, whe have a problem!");
        #endif

    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}