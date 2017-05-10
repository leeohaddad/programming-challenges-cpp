/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 23                   Professor Marcel   **/
/**   Problema A - Circle of Winter                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c2f6fa9de49e5c63f8/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <stdio.h>
// #include <cstdlib>
#include <cmath> 
// #include <cstring>
#include <set>
// #include <vector>
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_STRING 6105
#define debug_off 1

using namespace std;

int n;
double radius;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

int main () {
    int loop, x, y;
    double dist;

    #ifdef debug_on
        printf("\n| C23.A - Circle of Winter |\n");
    #endif

    /* read program arguments and calculate radius */
    scanf("%d", &n);
    for (loop=0; loop<n; loop++) {
        scanf("%d %d", &x, &y);
        dist = sqrt(x*x + y*y);
        if (dist > radius)
            radius = dist;
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    cout.precision(14);
    cout << 0 << " " << 0 << " " << radius << endl;

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
