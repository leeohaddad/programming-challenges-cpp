/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 16 - Cryptography                Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 15001
/* #define debug_on 1 */
#define true 1
#define false 0
typedef int bool;

/* read program arguments through command line parameters or through runtime user input */
int readArgs (int indexes[MAX_SIZE], int *maxIndex) {
	int n, loop;
	*maxIndex = 0;
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%d", &indexes[loop]);
		if (indexes[loop] > *maxIndex)
			*maxIndex = indexes[loop];
	}
	return n;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n, int indexes[MAX_SIZE], int maxIndex) {
	int loop;
	printf("\nArguments:\n");
	printf(" n=%d;\n",n);
	printf(" maxIndex=%d\n",maxIndex);
	printf(" indexes:\n");
	for (loop=0; loop<n; loop++)
		printf("  %d\n",indexes[loop]);
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

/* calculate the fist n prime numbers and stores them in vector primes */
void calculateFirstNPrimes (int n, int primes[MAX_SIZE]) {
	int loop, attempt;
	primes[0] = 0;
	primes[1] = 2;
	primes[2] = 3;
	attempt = 5;
	for (loop=3; loop<=n; loop++) {
		while (!isPrime(attempt))
			attempt = attempt + 2; /* because all even numbers are divisible by 2 */
		primes[loop] = attempt;
		attempt = attempt + 2;
	}
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, maxIndex, loop;
	int indexes[MAX_SIZE];
	int primes[MAX_SIZE];
	#ifdef debug_on
		printf("\nP16 - Cryptography:\n");
	#endif

	n = readArgs(indexes, &maxIndex);

	#ifdef debug_on
		printArgs(n,indexes, maxIndex);
		printf("\nProblem Solution:\n");
	#endif

	/* Solution */
	calculateFirstNPrimes(maxIndex, primes);
	for (loop=0; loop<n; loop++) {
		printf("%d\n",primes[indexes[loop]]);
	}

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1086. Cryptography
Time limit: 2.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1086

While preparing this problem set the jury has run into the following problem: it was necessary to send by e-mail the texts of the problems. As it is well known, e-mail is not reliable, messages are sent not enciphered, there is a danger that someone can intercept them. The members of the program committee wanted no participant know the texts of the problems before the start of the contest. That's why they resorted to cryptography methods in order to save the texts of the problems from an unsanctioned reading. The jury gas worked up a new way of enciphering of a text. It is not patented yet, so it's kept secret. However, we'll reveal you one secret: the new algorithm is based on the work with prime numbers. In particular, in uses a calculation of n-th by order prime number.
Several members of the program committee independently have worked up programs that make such calculations, but these programs produce different answers. Each one of the programmers is sure that his program works correctly. That's why the jury has reached the deadlock and can't continue working. The contest is about not to take place.
You are to help to the jury and to save the contest. We want you to write a program that calculates the n-th by order prime number. The main thing is that your program should work correctly.

Input:
First line contains a positive integer k. Then k positive integers follow (one in each line). The numbers don't exceed 15000.

Output:
For each number n you should output the n-th by order prime number. Each number should be in its line.

Sample:

Input:
4
3
2
5
7
Output:
5
3
11
17

Notes:
The prime number is a positive integer that has exactly two different positive divisors, i.e. 1 is not a prime number.

*/