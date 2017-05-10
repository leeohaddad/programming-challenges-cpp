/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 11                   Professor Marcel   **/
/**   Problema C - Arbitrage                                       Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c365f6fa9de49e5c815b/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <map>
#include <iostream>
#define MAX_N 35
#define debug_off 1

using namespace std;

int n, m;
double d[MAX_N][MAX_N];
map<string,int> currenciesIndexes;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, inner_loop;
    map<string,int>::iterator mapIterator;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" Currencies:\n");
    for (mapIterator=currenciesIndexes.begin(); mapIterator!=currenciesIndexes.end(); mapIterator++) {
        cout << "  " << (*mapIterator).first << ": " << (*mapIterator).second << endl;
    }
    printf(" Conversions Table:\n");
    for (loop=0; loop<n; loop++) {
        for (inner_loop=0; inner_loop<n; inner_loop++) {
            printf("  %.5f", d[loop][inner_loop]);
        }
        printf("\n");
    }
}
#endif

void checkArbitrageFloydWarshall () {
    int k, i, j;
    for (k=0; k<n; k++)
        for (i=0; i<n; i++)
            for (j=0; j<n; j++)
                if (d[i][k] != 0.0 && d[k][j] != 0.0)
                    d[i][j] = max(d[i][j], d[i][k] * d[k][j]);
}

int main () {
    int loop, inner_loop, firstIndex, secondIndex, casesCounter, dollarIndex;
    double secondArg;
    string arg, thirdArg;

    #ifdef debug_on
        printf("\n| C11.C - Arbitrage |\n");
    #endif

    casesCounter = 0;
    scanf("%d", &n);
    while (n > 0) {
        casesCounter++;
        /* read program arguments */
        for (loop=0; loop<n; loop++) {
            for (inner_loop=0; inner_loop<n; inner_loop++) {
                if (loop == inner_loop)
                    d[loop][inner_loop] = 1.0;
                else 
                    d[loop][inner_loop] = 0.0;
            }
            cin >> arg;
            currenciesIndexes.insert(make_pair(arg,loop));   
        }
        scanf("%d", &m);
        for (loop=0; loop<m; loop++) {
            cin >> arg;
            cin >> secondArg;
            cin >> thirdArg;
            firstIndex = currenciesIndexes[arg];
            secondIndex = currenciesIndexes[thirdArg];
            d[firstIndex][secondIndex] = secondArg;
            #ifdef debug_on
                cout << "\n  registering conversion: " << arg << " (" << firstIndex << ") to " << thirdArg << " (" << secondIndex << ") with rate " << secondArg << endl;
            #endif
        }

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif

        /* solution */
        checkArbitrageFloydWarshall();
        dollarIndex  = currenciesIndexes["USDollar"];
        #ifdef debug_on
            printArgs();
        #endif
        if (d[dollarIndex][dollarIndex] > 1.0)
            printf("Case %d: Yes\n", casesCounter);
        else
            printf("Case %d: No\n", casesCounter);

        currenciesIndexes.clear();
        scanf("%d", &n);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}
