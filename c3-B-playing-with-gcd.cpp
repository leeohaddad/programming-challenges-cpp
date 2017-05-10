/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 3                    Professor Marcel   **/
/**   Problema B - Playing with GCD                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/56337f8a25b873c24feb7189/view?index=1   **/
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
#define TRUNCATE_ERROR_FIX 0.3
#define debug_off 1

using namespace std;

int T;
int countResults[MAX_N];
int primes[MAX_PRIMES];
int maxPrimeDefined;
set<int> primeMultiples[MAX_PRIMES];
set<int> numbersCounted;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" T=%d;\n",T);
}
#endif

int gcd (int first, int second) {
    first = abs(first);
    second = abs(second);
    if (second == 0)
        return first;
    return gcd(second, first % second);
}

/* check if a number is prime, assumes primes are calculated in an sorted manner */
bool isPrime (int number) {
    int loop;
    int numSquareRoot = sqrt(number);
    #ifdef debug_on
        printf("  isPrime(): number=%d; numSquareRoot=%d\n",number,numSquareRoot);
    #endif
    for (loop=0; (loop<maxPrimeDefined && primes[loop]<=numSquareRoot); loop++) {
        if (number%(primes[loop]) == 0)
            return false;
    }
    maxPrimeDefined++;
    #ifdef debug_on
        printf("  isPrime() is setting primes[%d] to %d\n",maxPrimeDefined,number);
    #endif
    primes[maxPrimeDefined] = number;
    return true;
}

/* given a prime number, calculate the next prime number */
int calculateNextPrime (int currentPrime) {
    currentPrime = currentPrime + 2;
    while (!isPrime(currentPrime))
        currentPrime = currentPrime + 2; /* because all even numbers are divisible by 2 */
    return currentPrime;
}

/* long long countNumbersWithCommonDivisors (set<int> primesUsed, int limit, int currentProduct) {
    set<int>::iterator setIterator, anotherSetIterator;
    #ifdef debug_on
        printf("  countNumbersWithCommonDivisors - primesUsed.size(): %d - currentProduct: %d\n", (int)primesUsed.size(), currentProduct);
    #endif
    if (primesUsed.size() == 0)
        return 0;
    numbersCounted.clear();
    for (setIterator=primesUsed.begin(); setIterator!=primesUsed.end(); setIterator++) {
        for (anotherSetIterator=primeMultiples[*setIterator].begin(); anotherSetIterator!=primeMultiples[*setIterator].end(); anotherSetIterator++) {
            numbersCounted.insert(*anotherSetIterator);
        }
    }
    #ifdef debug_on
        printf("  numbersCounted: ");
        for (setIterator=numbersCounted.begin(); setIterator!=numbersCounted.end(); setIterator++)
            printf("%d ",*setIterator);
        printf("\n");
    #endif
    return ((long long)numbersCounted.size());
} */

int eulerTotientFunction (int number, set<int> primesUsed) {
    double result = 1.0;
    set<int>::iterator setIterator;
    for (setIterator=primesUsed.begin(); setIterator!=primesUsed.end(); setIterator++)
        result = result * (1.0 - (1.0/((double)(*setIterator))));
    result = result * number;
    #ifdef debug_on
        printf("   eulerTotientFunction(%d) = %d [%.4f]\n", number, (int)(result + TRUNCATE_ERROR_FIX), result);
    #endif
    return (int)(result + TRUNCATE_ERROR_FIX);
}

/* factorized a number into prime numbers and registers the result in the arrays */
int countByPrimeFactorization (int number, int primes[MAX_PRIMES]) {
    int currentPrimeIndex = 0, originalNumber = number;
    int result;
    set<int> primesUsed;
    set<int>::iterator setIterator;
    #ifdef debug_on
        printf("\nprimeFactorization(%d)\n",number);
    #endif
    while (number > 1) {
        if (currentPrimeIndex > maxPrimeDefined) {
            primes[currentPrimeIndex] = calculateNextPrime(primes[currentPrimeIndex-1]);
            #ifdef debug_on
                printf(" currentPrimeIndex: %d; currentPrime: %d;\n",currentPrimeIndex,primes[currentPrimeIndex]);
            #endif
        }
        while (number % primes[currentPrimeIndex] == 0) {
                number = number / primes[currentPrimeIndex];
            primesUsed.insert(primes[currentPrimeIndex]);
            #ifdef debug_on
                printf("  currentPrime: %d\n",primes[currentPrimeIndex]);
            #endif
        }
        currentPrimeIndex++;
    }
    result = originalNumber - eulerTotientFunction(originalNumber,primesUsed);
    #ifdef debug_on
        printf("    currentResult: %d\n", result);
    #endif
    return result;
}

int main () {
    int loop, N, biggestN, pointer;
    int count;
    #ifdef debug_on
    int inner_loop, even_inner_loop;
    int countTwo;
    #endif
    
    #ifdef debug_on
        printf("\n| C3.B - Playing with GCD |\n");
    #endif

    /* init */
    primes[0] = 2;
    primes[1] = 3; /* necessary to be defined for currentPrime+=2 logic to work */
    maxPrimeDefined = 1;
    countResults[0] = 0;
    biggestN = 0;
    count = 0;

    /* read program arguments and solve */
    scanf("%d", &T);
    for (loop=0; loop<T; loop++) {
        scanf("%d", &N);
        if (N > biggestN) {
            for (pointer=biggestN+1; pointer<=N; pointer++) {
                count = count + countByPrimeFactorization(pointer,primes);
                #ifdef debug_on
                    printf("     currentCount: %d\n", count);
                #endif
                countResults[pointer] = count;
            }
            biggestN = N;
        }
        printf("Case %d: %d\n", loop+1, countResults[N]);
        #ifdef debug_on
            countTwo = 0;
            for (inner_loop=1; inner_loop<=N; inner_loop++)
                for (even_inner_loop=1; even_inner_loop<=inner_loop; even_inner_loop++)
                    if (gcd(inner_loop, even_inner_loop) > 1) {
                        /* printf(" Pair: %d and %d\n", inner_loop, even_inner_loop); */
                        countTwo++;
                    }
            printf("  Check: %d\n", countTwo);
        #endif
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}