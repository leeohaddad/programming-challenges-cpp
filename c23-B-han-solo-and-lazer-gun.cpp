/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 23                   Professor Marcel   **/
/**   Problema B - Han Solo and Lazer Gun                          Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce70921926e63b4daf21/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <stdio.h>
// #include <cstdlib>
#include <cmath> 
// #include <cstring>
// #include <set>
#include <vector>
#include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_N 1005
#define debug_off 1

using namespace std;

int n, initialX, initialY, readX, readY;
vector< pair<int,int> > stormtroopers;
bool isShootingHere[MAX_N] = {};

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

int main () {
    int loop, innerLoop, result, firstTrooper, secondTrooper, innerFirst, innerSecond;
    
    #ifdef debug_on
        printf("\n| C23.B - Han Solo and Lazer Gun |\n");
    #endif

    /* read program arguments and populate stormtroopers */
    scanf("%d %d %d", &n, &initialX, &initialY);
    for (loop=0; loop<n; loop++) {
        scanf("%d %d", &readX, &readY);
        stormtroopers.push_back(make_pair(readX,readY));
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    result = 0;
    for (loop=0; loop<n; loop++) {
        firstTrooper = stormtroopers[loop].first;
        secondTrooper = stormtroopers[loop].second;
        if (!isShootingHere[loop]) {
            result++;
        }
        isShootingHere[loop] = true;
        for (innerLoop=loop+1; innerLoop<n; innerLoop++) {
            innerFirst = stormtroopers[innerLoop].first;
            innerSecond = stormtroopers[innerLoop].second;
            if (!isShootingHere[innerLoop] && (innerFirst - initialX) * (secondTrooper - initialY) == (firstTrooper - initialX) * (innerSecond - initialY)) {
                isShootingHere[innerLoop] = true;
            }
        }
    }
    cout << result << endl;

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}