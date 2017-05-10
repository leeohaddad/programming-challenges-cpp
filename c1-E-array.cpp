/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema E - Array                                           Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dcf18fdd359ad3c57386d/view?index=4   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define debug_off 1

using namespace std;

int n;
vector<long> elements;
set<long> posGroup, negGroup, zeroGroup;
set<long>::iterator setIterator;

#ifdef debug_on
/* print arguments */
void printArgs () {
    unsigned int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" elements:\n");
    for (loop=0; loop<elements.size(); loop++)
        printf("  %ld\n",elements[loop]);
}
#endif

int main () {
   int loop;
   long arg;

    #ifdef debug_on
        printf("\n| C1.E - Array |\n");
    #endif

    /* read program arguments */
    scanf("%d", &n);
    for (loop=0; loop<n; loop++) {
        scanf("%ld", &arg);
        elements.push_back(arg);
        if (arg < 0)
            negGroup.insert(arg);
        else if (arg > 0)
            posGroup.insert(arg);
        else
            zeroGroup.insert(arg);
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (posGroup.size() == 0)
    {
        setIterator = negGroup.begin();
        posGroup.insert(*setIterator);
        negGroup.erase(setIterator);
        setIterator = negGroup.begin();
        posGroup.insert(*setIterator);
        negGroup.erase(setIterator);
    }
    if (negGroup.size()%2 == 0) {
        setIterator = negGroup.begin();
        zeroGroup.insert(*setIterator);
        negGroup.erase(setIterator);
    }
    printf("%d",negGroup.size());
    for (setIterator=negGroup.begin(); setIterator!=negGroup.end(); setIterator++)
    {
        printf(" %ld",*setIterator); 
    }
    printf("\n%d",posGroup.size());
    for (setIterator=posGroup.begin(); setIterator!=posGroup.end(); setIterator++)
    {
        printf(" %ld",*setIterator); 
    }
    printf("\n%d",zeroGroup.size());
    for (setIterator=zeroGroup.begin(); setIterator!=zeroGroup.end(); setIterator++)
    {
        printf(" %ld",*setIterator); 
    }
    printf("\n");

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}