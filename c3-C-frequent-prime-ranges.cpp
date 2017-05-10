/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 3                    Professor Marcel   **/
/**   Problema C - Frequent Prime Ranges                           Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c351f6fa9de49e5c7f37/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#define MAX_N 100005
#define MAX_PRIMES 100005
#define debug_off 1

using namespace std;

long long T;
vector< pair<long long,long long> > testCases;
long long primes[MAX_PRIMES];
long long primesCount[MAX_PRIMES];
long long maxPrimeDefined;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" T=%lld;\n",T);
}
#endif

/* check if a number is prime, assumes primes are calculated in an sorted manner */
bool isPrime (long long number) {
    long long loop;
    for (loop=0; loop<maxPrimeDefined; loop++) {
        if (number%(primes[loop]) == 0)
            return false;
    }
    maxPrimeDefined++;
    #ifdef debug_on
        printf("  isPrime() is setting primes[%lld] to %lld\n",maxPrimeDefined,number);
    #endif
    primes[maxPrimeDefined] = number;
    return true;
}

/* given a prime number, calculate the next prime number; assumes currentPrime is prime */
long long calculateNextPrime (long long currentPrime) {
    primesCount[currentPrime+1] = maxPrimeDefined + 1;
    currentPrime = currentPrime + 2;
    while (!isPrime(currentPrime)) {
        primesCount[currentPrime] = maxPrimeDefined + 1;
        primesCount[currentPrime+1] = maxPrimeDefined + 1;
        currentPrime = currentPrime + 2; /* because all even numbers are divisible by 2 */   
    }
    primesCount[currentPrime] = maxPrimeDefined + 1;
    return currentPrime;
}

int main () {
    long long loop, N, K, maxNumber, intervalsCount, valueToIncrease, a;
    vector< pair<long long,long long> >::iterator vectorIterator;
    
    #ifdef debug_on
        printf("\n| C3.C - Frequent Prime Ranges |\n");
    #endif

    /* init */
    primes[0] = 2;
    primes[1] = 3; /* necessary to be defined for currentPrime+=2 logic to work */
    maxPrimeDefined = 1;
    primesCount[0] = 0;
    primesCount[1] = 0;
    primesCount[2] = 1;
    primesCount[3] = 2;
    maxNumber = 0;
    
    /* read program arguments and solve */
    scanf("%lld", &T);
    for (loop=0; loop<T; loop++) {
        scanf("%lld %lld", &N, &K);
        testCases.push_back(make_pair(N,K));
        if (N > maxNumber)
            maxNumber = N;
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    while (primes[maxPrimeDefined] < maxNumber)
        calculateNextPrime(primes[maxPrimeDefined]);   
    #ifdef debug_on
        printf("  primes: [");
        for (loop=0; loop<=maxPrimeDefined; loop++)
            printf("%lld, ",primes[loop]);
        printf("]\n");
        printf("  primesCount: [");
        loop = 0;
        for (loop=0; loop<=primes[maxPrimeDefined]; loop++)
            printf("%lld, ",primesCount[loop]);
        printf("]\n");
    #endif
    for (vectorIterator=testCases.begin(); vectorIterator!=testCases.end(); vectorIterator++) {
        intervalsCount = 0;
        N = (*vectorIterator).first;
        K = (*vectorIterator).second;
        #ifdef debug_on
            printf(" K: %lld\n", K);
        #endif
        a = 2;
        if (K == 0) {
            while (a <= N)
                intervalsCount = intervalsCount + (N - a++ + 1);
        }
        else {
            while (a <= N) {
                #ifdef debug_on
                    printf("  a: %lld; N: %lld; primesCount[a-1]: %lld; minimumPrime: %lld // intervalsCount: %lld -> %lld\n",a,N,primesCount[a-1],primes[primesCount[a-1] + K - 1], intervalsCount, intervalsCount + (N - (primes[primesCount[a-1] + K - 1]) + 1));
                #endif
                valueToIncrease = (N - (primes[primesCount[a-1] + K - 1]) + 1);
                if (valueToIncrease > 0 && primesCount[a-1] + K - 1 <= maxPrimeDefined)
                    intervalsCount = intervalsCount + valueToIncrease;
                a++;
            }
        }
        printf("%lld\n",intervalsCount);
    }

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}