/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema B - Prime Time                                      Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c373f6fa9de49e5c82e4/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 10000
#define debug_off 1

using namespace std;

int n;
int isPrimeArray[MAX_N];
int primeFactors[MAX_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

int getIthPrime (int i) {
    int count = 0;
    int loop = 0;
    while (count < i) {
        while (isPrimeArray[loop] == 0)
            loop++;
        loop++;
        if (isPrimeArray[loop==1])
            count++;
        else return i;
    }
    return i;
}

int isPrime (int number) {
    int primeToTest;
    int primeIndex = 2;
    #ifdef debug_on
    #ifdef specific_debug
        printf("IsPrime? %d\n",number);
        for (loop=0; loop<20; loop++)
            printf("%d => %d\n",loop,isPrimeArray[loop]);
    #endif
    #endif
    if (isPrimeArray[number-1] != -1)
        return isPrimeArray[number-1];
    primeToTest = 2;
    while (primeToTest < number && primeToTest != -1)
    {
        if (number % primeToTest == 0)
        {
            isPrimeArray[number-1] = 0;
            #ifdef debug_on
                printf("%d is not prime because it divides by %d!\n", number, primeToTest);
            #endif
            return 0;
        }
        primeIndex++;
        primeToTest = getIthPrime(primeIndex);
    }
    isPrimeArray[number-1] = 1;

    #ifdef debug_on
        printf("%d is prime!\n", number);
    #endif
    return 1;
}

int findNextPrime (int currentNumber) {
    #ifdef debug_on
        printf("\nfindNextPrime: %d\n",currentNumber);
    #endif
    currentNumber++;
    while (isPrime(currentNumber) == 0) {
        currentNumber++;
    }
    #ifdef debug_on
        printf(" found %d\n",currentNumber);
    #endif
    return currentNumber;
}

int main () {
    int prime;
    int currentFactor;
    int firstPrint;
    int loop;

    #ifdef debug_on
        printf("\n| C2.B - Prime Time |\n");
    #endif

    /* read program arguments */
    scanf("%d", &n);

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    for (loop=0; loop<n; loop++) {
        isPrimeArray[loop] = -1;
        primeFactors[loop] = 0;
    }
    isPrimeArray[0] = 0;
    isPrimeArray[1] = 1;
    isPrimeArray[2] = 1;
    for (loop=1; loop<=n; loop++) {
        currentFactor = loop;
        prime = 2;
        while (currentFactor != 1) {
            #ifdef debug_on
                printf("currentFactor: %d\n",currentFactor);
            #endif
            while (currentFactor % prime == 0) {
                primeFactors[prime-1]++;
                currentFactor = currentFactor/prime;
            }
            prime = findNextPrime(prime);
        }   
    }

    /* output */
    firstPrint = 1;
    for (loop=0; loop<n; loop++) {
        if (primeFactors[loop] > 0) {
            if (firstPrint == 1) {
                printf("%d^%d", loop+1, primeFactors[loop]);
                firstPrint = 0;
            }
            else 
                printf(" * %d^%d", loop+1, primeFactors[loop]);
        }
    }
    printf("\n");

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}