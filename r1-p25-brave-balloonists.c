/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 25 - Brave Balloonists           Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_SIZE 10
#define MAX_PRIMES 1460
/* #define debug_on 1 */
#define true 1
#define false 0
typedef int bool;

#ifdef debug_on
/* print arguments */
void printArgs (int elements[MAX_SIZE]) {
	int loop;
	printf("\nArguments:\n");
	printf(" elements:\n");
	for (loop=0; loop<MAX_SIZE; loop++)
		printf("  %d\n",elements[loop]);
}
#endif

/* check if a number is prime */
bool isPrime (int number) {
	int maxPossibleDivisor, loop;
	maxPossibleDivisor = number/2; /* sqrt(number); */
	for(loop=3; loop<=maxPossibleDivisor; loop=loop+2) {
		if(number%loop==0) {
			return false;
		}
	}
	return true;
}

/* given a prime number, calculate the next prime number */
int calculateNextPrime (int currentPrime) {
	currentPrime = currentPrime + 2;
	while (!isPrime(currentPrime))
		currentPrime = currentPrime + 2; /* because all even numbers are divisible by 2 */
	return currentPrime;
}

/* factorized a number into prime numbers and registers the result in the arrays */
void primeFactorization (int number, int primes[MAX_PRIMES], int instancesCount[MAX_PRIMES], int primesUsed[MAX_PRIMES], int *maxPrimeDefined, int *primesUsedCount) {
	int currentPrimeIndex = 0;
	#ifdef debug_on
		printf("primeFactorization(%d)\n",number);
	#endif
	while (number > 1) {
		if (currentPrimeIndex > *maxPrimeDefined) {
			primes[currentPrimeIndex] = calculateNextPrime(primes[currentPrimeIndex-1]);
			*maxPrimeDefined = *maxPrimeDefined;
		}
		while (number % primes[currentPrimeIndex] == 0) {
			number = number / primes[currentPrimeIndex];
			if (instancesCount[currentPrimeIndex] == 0) {
				primesUsed[*primesUsedCount] = currentPrimeIndex;
				*primesUsedCount = *primesUsedCount + 1;
			}
			instancesCount[currentPrimeIndex] = instancesCount[currentPrimeIndex] + 1;
			#ifdef debug_on
				printf("%d\n",primes[currentPrimeIndex]);
			#endif
		}
		currentPrimeIndex++;
	}
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int elements[MAX_SIZE];
	int primes[MAX_PRIMES], instancesCount[MAX_PRIMES], primesUsed[MAX_PRIMES];
	int maxPrimeDefined, primesUsedCount;
	int numberOfDivisors, loop;
	#ifdef debug_on
		printf("\nP25 - Brave Balloonists:\n");
	#endif
	primes[0] = 2;
	primes[1] = 3; /* necessary to be defined for currentPrime+=2 logic to work */
	maxPrimeDefined = 1;
	primesUsedCount = 0;
	
	/* read program arguments */
	for (loop=0; loop<MAX_SIZE; loop++) {
		scanf("%d", &elements[loop]);
		primeFactorization(elements[loop],primes,instancesCount,primesUsed,&maxPrimeDefined,&primesUsedCount);
	}
	
	#ifdef debug_on
		printArgs(elements);
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	numberOfDivisors = 1;
	for (loop=0; loop<primesUsedCount; loop++) {
		numberOfDivisors = numberOfDivisors * (instancesCount[primesUsed[loop]] + 1);
	}
	#ifdef debug_on
		printf("result: %d MOD 10 = ", numberOfDivisors);
	#endif
	printf("%d\n",numberOfDivisors%10);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1049. Brave Balloonists
Time limit: 2.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1049

Ten mathematicians are flying on a balloon over the Pacific ocean. When they are crossing the equator they decide to celebrate this event and open a bottle of champagne. Unfortunately, the cork makes a hole in the balloon. Hydrogen is leaking out and the balloon is descending now. Soon it will fall into the ocean and all the balloonists will be eaten by hungry sharks.
But not everything is lost yet. One of the balloonists can sacrifice himself jumping out, so that his friends would live a little longer. Only one problem still exists: who is the one to get out. There is a fair way to solve this problem. First, each of them writes an integer ai not less than 1 and not more than 10000. Then they calculate the magic number N that is the number of positive divisors of the product a1*a2*…*a10. For example, the number of positive integer divisors of 6 is 4 (they are 1,2,3,6). The hero (a mathematician who will be thrown out) is determined according to the last digit of N. Your task is to find this digit.

Input:
Input contains ten integer numbers (each number is in separate line).

Output:
Output a single digit from 0 to 9 — the last digit of N.

Sample:

Input:
1
2
6
1
3
1
1
1
1
1
Output:
9

*/