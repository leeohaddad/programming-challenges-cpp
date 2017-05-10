/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 7                    Professor Marcel   **/
/**   Problema C - Prime Ring Problem                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d5917455fe80169125e0/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 16
#define MAX_PROSSIBLE_PRIME 2*MAX_N+1
#define debug_off 1

using namespace std;

vector<int> n;
set<int> primes;
int combination[MAX_N];
int numberIsInUse[MAX_PROSSIBLE_PRIME];
int currentIndex;

#ifdef debug_on
/* print arguments */
void printArgs () {
    vector<int>::iterator vectorIterator;
    printf("Arguments:\n");
    printf(" n =");
    for (vectorIterator=n.begin(); vectorIterator!=n.end(); vectorIterator++)
        printf(" %d",*vectorIterator);
    printf("\n");
}
#endif

void printCurrentCombination (int n) {
    int loop;
    printf("1");
    for (loop=1; loop<n; loop++)
        printf(" %d",combination[loop]);
    printf("\n");
}

void findPrimeRings (int n) {
    set<int>::iterator setIterator;
    int difference;
    #ifdef debug_on_level_two
        printf(" printPrimeRings(%d)\n",n);
    #endif
    if (currentIndex == n)
        if (primes.find(1+combination[currentIndex-1]) != primes.end())
            printCurrentCombination(n);
    for (setIterator=primes.begin(); setIterator!=primes.end() && (*setIterator)<=2*n; setIterator++) {
        difference = (*setIterator) - combination[currentIndex-1];
        if (difference>0 && difference<=n && numberIsInUse[difference]==0) {
            numberIsInUse[difference] = 1;
            combination[currentIndex] = difference;
            currentIndex++;
            findPrimeRings(n);
            currentIndex--;
            numberIsInUse[difference] = 0;
        }
    }
}

int main () {
    int arg, scanfResult, caseCount;
    vector<int>::iterator vectorIterator;

    #ifdef debug_on
        int loop;
        printf("\n| C7.C - Prime Ring Problem |\n");
    #endif

    /* init: configure set of primes less than 16+16=32 */
    primes.insert(2);
    primes.insert(3);
    primes.insert(5);
    primes.insert(7);
    primes.insert(11);
    primes.insert(13);
    primes.insert(17);
    primes.insert(19);
    primes.insert(23);
    primes.insert(29);
    primes.insert(31);
    
    /* read program arguments and solve */
    scanfResult = scanf("%d", &arg);
    while (scanfResult != -1) {
        n.push_back(arg);
        scanfResult = scanf("%d", &arg);
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    caseCount = 1;
    combination[0] = 1;
    currentIndex = 1;
    numberIsInUse[1] = 1;
    for (vectorIterator=n.begin(); vectorIterator!=n.end(); vectorIterator++) {
        printf("Case %d:\n",caseCount++);
        #ifdef debug_on
            printf(" combination(%d):",currentIndex);
            for (loop=0; loop<currentIndex; loop++)
                printf(" %d",combination[loop]);
            printf("\n");
            printf("  numberIsInUse:");
            for (loop=0; loop<MAX_PROSSIBLE_PRIME; loop++)
                printf(" %d |",numberIsInUse[loop]);
            printf("\n");
        #endif
        findPrimeRings(*vectorIterator);
        if ((vectorIterator+1) != n.end())
            printf("\n");
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}