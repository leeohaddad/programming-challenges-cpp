/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema E - Find a Multiple                                 Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c1f6fa9de49e5c62e5/view?index=5   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#define MAX_N 10005
#define debug_off 1

using namespace std;

int N;
vector<int> numbersByModN[MAX_N];
int numbersCountByModN[MAX_N];
int modStateWasAchieved[MAX_N];
vector<int> solution;
set<int> availableMods;

#ifdef debug_on
/* print arguments */
void printArgs () {
    vector<int>::iterator vectorIterator;
    int loop;
    printf("Arguments:\n");
    printf(" N=%d;\n",N);
    for (loop=0; loop<N; loop++) {
        printf("  mod %d [%d]:",loop,numbersByModN[loop].size());
        if (numbersByModN[loop].size() > 0)
            for (vectorIterator=numbersByModN[loop].begin(); vectorIterator!=numbersByModN[loop].end(); vectorIterator++)
                printf(" %d",*vectorIterator);
        printf("\n");
    }
}
#endif

int tryBacktracking(int currentModSum) {
    vector<int>::iterator vectorIterator;
    set<int>::iterator setIterator;
    int mod, number, result;
    modStateWasAchieved[currentModSum] = 1;
    #ifdef debug_on
        printf("--------------------------------------------------\n");
        printf("printArgs()\n");
        printArgs();
        printf("--------------------------------------------------\n");
        printf("  currentModSum: %d\n",currentModSum);
        printf("   solution elements count: %d\n    ",solution.size());
        for (vectorIterator=solution.begin(); vectorIterator!=solution.end(); vectorIterator++) {
            printf("%d ",*vectorIterator);
        }
        printf("\n");
        printf("--------------------------------------------------\n");
        printf("   available elements count: %d\n    ",availableMods.size());
        for (setIterator=availableMods.begin(); setIterator!=availableMods.end(); setIterator++) {
            printf("%d[%d] ",*setIterator,numbersCountByModN[*setIterator]);
        }
        printf("\n");
        printf("--------------------------------------------------\n\n");
    #endif
    if (currentModSum == 0 && solution.size() > 0) {
        printf("%d\n",solution.size());
        for (vectorIterator=solution.begin(); vectorIterator!=solution.end(); vectorIterator++) {
            number = *vectorIterator;
            printf("%d\n",number);
        }
        return 1;
    }
    for (setIterator=availableMods.begin(); setIterator!=availableMods.end(); setIterator++) {
        mod = *setIterator;
        if (modStateWasAchieved[(currentModSum + mod)%N] == 0 || ((currentModSum + mod)%N) == 0) {
            solution.push_back(numbersByModN[mod].back());
            numbersByModN[mod].pop_back();
            numbersCountByModN[mod] = numbersCountByModN[mod] - 1;
            if (numbersCountByModN[mod] == 0) {
                availableMods.erase(mod);
            }
            result = tryBacktracking((currentModSum + mod)%N);
            if (result == 1) {
                return 1;
            }
            numbersCountByModN[mod] = numbersCountByModN[mod] + 1;
            if (numbersCountByModN[mod] == 1)
                availableMods.insert(mod);
            numbersByModN[mod].push_back(solution.back());
            solution.pop_back();
        }
    }
    return 0;
}

int main () {
    int loop, arg, argMod, result;

    #ifdef debug_on
        printf("\n| C2.F - Find a Multiple |\n");
    #endif

    /* read program arguments */
    scanf("%d", &N);
    for (loop=0; loop<N; loop++) {
        numbersCountByModN[loop] = 0;
        modStateWasAchieved[loop] = 0;
    }
    for (loop=0; loop<N; loop++) {
        scanf("%d", &arg);
        argMod = arg % N;
        numbersByModN[argMod].push_back(arg);
        numbersCountByModN[argMod] = numbersCountByModN[argMod] + 1;
        if (numbersCountByModN[argMod] == 1)
            availableMods.insert(argMod);
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (numbersByModN[0].size() > 0) {
        printf("1\n%d\n",numbersByModN[0].back());
    }
    else {
        result = tryBacktracking(0);
        if (result == 0)
            printf("0\n");
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}