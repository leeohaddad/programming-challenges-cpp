/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 10                   Professor Marcel   **/
/**   Problema B - Elevator Trouble                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c368f6fa9de49e5c819f/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_FLOORS 1000005
#define debug_off 1

using namespace std;

int f, s, g, u, d;
set<int> visitedFloors;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n s=%d;\n g=%d;\n u=%d;\n d=%d;\n",f,s,g,u,d);
}
#endif

int tryToReach (int destinyFloor, int currentFloor) {
    int distance, numberOfDisplacements;
    if (visitedFloors.find(currentFloor) != visitedFloors.end())
        return -1;
    visitedFloors.insert(currentFloor);
    if (currentFloor < destinyFloor) {
        distance = destinyFloor - currentFloor;
        if (distance < u) {
            numberOfDisplacements = distance/d;
            return numberOfDisplacements + tryToReach(destinyFloor,currentFloor-d*numberOfDisplacements);
        }
        else {
            numberOfDisplacements = distance/u;
            return numberOfDisplacements + tryToReach(destinyFloor,currentFloor+u*numberOfDisplacements);
        }
    }
    else if (currentFloor > destinyFloor) {
        distance = currentFloor - destinyFloor;
        if (distance < d) {
            numberOfDisplacements = distance/u;
            return numberOfDisplacements + tryToReach(destinyFloor,currentFloor+u*numberOfDisplacements);
        }
        else {
            numberOfDisplacements = distance/d;
            return numberOfDisplacements + tryToReach(destinyFloor,currentFloor-d*numberOfDisplacements);
        }
    }
    else return 0;
}

int main () {
   int currentFloor, minimumPath;

    #ifdef debug_on
        printf("\n| C10.B - Elevator Trouble |\n");
    #endif

    /* read program arguments */
    scanf("%d %d %d %d %d", &f, &s, &g, &u, &d);

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (s == g) {
        printf("0\n");
        return 0;
    }
    else if (d == 0) {
        if (s > g || u == 0 || (g-s)%u != 0) {
            printf("use the stairs\n");
            return 0;
        }
        printf("%d\n",(g-s)/u);
        return 0;
    }
    else if (u == 0) {
        if (s < g || d == 0 || (s-g)%d != 0) {
            printf("use the stairs\n");
            return 0;
        }
        printf("%d\n",(s-g)/d);
        return 0;
    }
    else {
        currentFloor = s;
        minimumPath = tryToReach(g,currentFloor);
    }
    if (minimumPath > -1)
        printf("%d\n",minimumPath);
    else
        printf("use the stairs\n");

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}