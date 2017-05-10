/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema D - 1, 10, 100, 1000...                             Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c2f6fa9de49e5c634b/view?index=3   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define debug_off 1

using namespace std;

int n;
vector<long> elements;
set<long long> onePositions;

#ifdef debug_on
/* print arguments */
void printArgs () {
    unsigned int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" elements:\n");
    for (loop=0; loop<elements.size(); loop++)
        cout << "  " << elements[loop] << endl;
}
#endif

void registerOnesUntil (long long index) {
    long long seeker = 1;
    int sum = 1;
    onePositions.insert(seeker);
    while (seeker < index) {
        seeker = seeker + sum++;
        onePositions.insert(seeker);
    }
}

int main () {
   int loop, arg, max;
   unsigned int u_loop;

    #ifdef debug_on
        printf("\n| C1.D - 1, 10, 100, 1000... |\n");
    #endif

    max = 0;
    /* read program arguments */
    scanf("%d", &n);
    for (loop=0; loop<n; loop++) {
        cin >> arg;
        elements.push_back(arg);
        if (arg > max)
            max = arg;
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    registerOnesUntil(max);
    if (elements.size() > 0) {     
        for (u_loop=0; u_loop<elements.size(); u_loop++)
            if (onePositions.find(elements[u_loop]) != onePositions.end())
                printf("1 ");
            else
                printf("0 ");
        printf("\n");
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}