/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 14                   Professor Marcel   **/
/**   Problema A - Amity Assessment                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/57526ed5bd5f641300c9b263/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

string bessie, bessieFirst, bessieSecond, elsie, elsieFirst, elsieSecond;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    cout << " bessieFirst=" << bessieFirst << endl << " bessieSecond" << bessieSecond << endl;
    cout << " elsieFirst=" << elsieFirst << endl << " elsieSecond" << elsieSecond << endl;
}
#endif

int main () {
    #ifdef debug_on
        printf("\n| C14.A - Amity Assessment |\n");
    #endif

    /* read program arguments */
    cin >> bessieFirst >> bessieSecond;
    cin >> elsieFirst >> elsieSecond;

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    swap(bessieSecond[0], bessieSecond[1]);
    swap(elsieSecond[0], elsieSecond[1]);
    bessie = bessieFirst + bessieSecond;
    elsie = elsieFirst + elsieSecond;
    bessie.erase(bessie.find('X'), 1);
    elsie.erase(elsie.find('X'), 1);
    if((bessie + bessie).find(elsie) != string::npos)
        printf("YES\n");
    else
        printf("NO\n");

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}