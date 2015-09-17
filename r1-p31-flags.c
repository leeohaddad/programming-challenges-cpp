/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 31 - Flags                       Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define ALL_FREE 0
#define NO_WHITE 1
#define NO_RED 2
/* #define debug_on 1 */


/* read program arguments */
int readArgs () {
	int n;
	scanf("%d", &n);
	return n;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n) {
	printf("\nArgument:\n");
	printf(" n=%d;\n",n);
}
#endif

long countCombinations (int n, int restriction) {
	long result;
	#ifdef debug_on
		printf("countCombinations(%d,%d)\n",n,restriction);
	#endif
	if (n == 0) {
		#ifdef debug_on
			printf("return 1\n");
		#endif
		return 1;
	}
	if (n == 1) {
		#ifdef debug_on
			printf("return %d\n",(1 + (restriction==ALL_FREE)));
		#endif
		return (1 + (restriction==ALL_FREE));
	}
	result = 0;
	/* try WHITE standalone */
	if (restriction != NO_WHITE) {
		#ifdef debug_on
			printf("try(%d,WHITE)\n",n);
		#endif
		result = result + countCombinations(n-1, NO_WHITE);
	}
	/* try RED standalone */
	if (restriction != NO_RED) {
		#ifdef debug_on
			printf("try(%d,RED)\n",n);
		#endif
		result = result + countCombinations(n-1, NO_RED);
	}
	/* if WHITE try BLUE-RED */
	if (restriction == NO_WHITE) {
		#ifdef debug_on
			printf("try(%d,BLUE-RED)\n",n);
		#endif
		result = result + countCombinations(n-2, NO_RED);
	}
	/* if RED try BLUE-WHITE */
	if (restriction == NO_RED) {
		#ifdef debug_on
			printf("try(%d,BLUE-WHITE)\n",n);
		#endif
		result = result + countCombinations(n-2, NO_WHITE);
	}
	#ifdef debug_on
		printf("return %d\n",result);
	#endif
	return result;
}

long long empiricalSolution (int n) {
	int loop;
	long long sum, lastElement, buffer;
	if (n==1 || n==2)
		return 2;
	lastElement = 2;
	sum = 2;
	for (loop=3; loop<=n; loop++) {
		buffer = sum;
		sum = sum + lastElement;
		lastElement = buffer;
	}
	return sum;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n;
	long long result;
	#ifdef debug_on
		printf("\nP31 - Flags:\n");
	#endif

	n = readArgs();

	#ifdef debug_on
		printArgs(n);
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	/* result = countCombinations(n, ALL_FREE); */
	/* result above was rejected due to time limit on test #9 */
	/* analysing the results, I noticed c(n) = c(n-1) + c(n-2) */
	result = empiricalSolution(n);
	printf("%lld\n",result);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1225. Flags
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1225

On the Day of the Flag of Russia a shop-owner decided to decorate the show-window of his shop with textile stripes of white, blue and red colors. He wants to satisfy the following conditions:
Stripes of the same color cannot be placed next to each other.
A blue stripe must always be placed between a white and a red or between a red and a white one.
Determine the number of the ways to fulfill his wish.
Example. For N = 3 result is following:

Input:
N, the number of the stripes, 1 ≤ N ≤ 45.

Output:
M, the number of the ways to decorate the shop-window.

Sample:

Input:
3
Output:
4

*/