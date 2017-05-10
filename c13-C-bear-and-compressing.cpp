/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 13                   Professor Marcel   **/
/**   Problema C - Bear and Compressing                            Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57526ecfbd5f641300c9b24e/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define MAX_N 6
#define debug_off 1

using namespace std;

int n, q;
vector< pair<string,char> > operations;
int combinations[MAX_N][MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    vector< pair<string,char> >::iterator pairVectorIterator;
    printf("Arguments:\n");
    printf(" n=%d;\n", n);
    printf(" q=%d;\n", q);
    printf(" operations:\n");
    for (pairVectorIterator=operations.begin(); pairVectorIterator!=operations.end(); pairVectorIterator++)
        cout << "  " << (*pairVectorIterator).first << " => " << (*pairVectorIterator).second << endl;
}
#endif

int compress(char desiredChar, int last) {
    int loop;
    if (last == 1)
        return 1;
    int &result = combinations[desiredChar-'a'][last];
    if (result != -1)
        return result;
    result = 0;
    for (loop=0; loop<q; loop++) {
        if (desiredChar == operations[loop].second) {
            result = result + compress(operations[loop].first[0], last-1);
        }
    }
    return result;
}

int main () {
    int loop;

    #ifdef debug_on
        printf("\n| C13.C - Bear and Compressing |\n");
    #endif

    /* read program arguments */
    scanf("%d %d", &n, &q);
    operations = vector< pair<string,char> >(q);
    for (loop=0; loop<q; loop++) {
        cin >> operations[loop].first;
        cin >> operations[loop].second;
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    memset(combinations, -1, sizeof(combinations));
    printf("%d\n", compress('a', n));
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}