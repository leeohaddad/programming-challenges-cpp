/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema A - Vanya and Lanterns                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce67921926e63b4daeb2/view?index=0   **/
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
long long i;
set<long long> elements;
set<long long>::iterator setIterator, firstElement, lastElement;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" i=%lld;\n",i);
    printf(" elements:\n");
    for (setIterator=elements.begin(); setIterator!=elements.end(); setIterator++)
        printf("  %lld\n",*setIterator);
}
#endif

int main () {
   int loop;
   long long arg;
   long long previous;
   double radius, toCompare;

    #ifdef debug_on
        printf("\n| C2.A - Vanya and Lanterns |\n");
    #endif

    /* read program arguments */
    scanf("%d", &n);
    scanf("%lld", &i);
    for (loop=0; loop<n; loop++) {
        scanf("%lld", &arg);
        elements.insert(arg);
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    setIterator = elements.begin();
    radius = previous = *setIterator;
    lastElement = elements.end();
    if (n > 1) {
        setIterator++;
        for (setIterator=setIterator; setIterator!=lastElement; setIterator++)
        {
            toCompare = *setIterator;
            #ifdef debug_on
                printf("current: %lld ; previous: %lld ; radius: %.3f ;\n",toCompare,previous,radius);
            #endif
            if ((toCompare - previous)/2.0 > radius)
                radius = (toCompare - previous)/2.0;
            previous = toCompare;
        }
    }
    lastElement--;
    toCompare = ((double)i - (double)(*lastElement));
    if (toCompare > radius)
    {
        radius = toCompare;
        #ifdef debug_on
            printf("lastElement: %lld ; radius: %.3f ; roadSize: %lld ; distance: %.10f\n",*lastElement,radius,i,(double)i - (double)(*lastElement));
        #endif
    }
    printf("%.10lf\n", radius);

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}