/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 8 - 24 Game                      Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0

/* read sequence length through command line parameters or through runtime user input */
int readArgs (int argc, char *argv[]) {
	int n;
	if (argc>=2 && atoi(argv[1])>=1 && atoi(argv[1]) <= 100000) {
		n = atoi(argv[1]);
	}
	else {
		if (debug_on)
			printf("n: ");
		scanf("%d", &n);
	}
	return n;
}

void print24GameAnswer (int n) {
	if (n > 5) {
		print24GameAnswer(n-2);
		printf("%d - %d = 1\n",n,n-1);
		printf("1 * 24 = 24\n");
	}
	else if (n == 5) {
		printf("YES\n");
		printf("5 - 1 = 4\n");
		printf("4 - 2 = 2\n");
		printf("2 * 3 = 6\n");
		printf("6 * 4 = 24\n");
	}
	else if (n == 4) {
		printf("YES\n");
		printf("1 * 2 = 2\n");
		printf("2 * 3 = 6\n");
		printf("6 * 4 = 24\n");
	}
	else {
		printf("NO");
	}
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n;
	if (debug_on)
		printf("\nP8 - 24 Game:\n");
	n = readArgs(argc, argv);
	
	if (n<1 || n>100000) {
		printf("Invalid sequence length. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}
	if (debug_on)
		printf("\nProblem Solution:\n");

	print24GameAnswer(n);

	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

A. 24 Game
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/468/A

Little X used to play a card game called "24 Game", but recently he has found it too easy. So he invented a new game.
Initially you have a sequence of n integers: 1, 2, ..., n. In a single step, you can pick two of them, let's denote them a and b, erase them from the sequence, and append to the sequence either a + b, or a - b, or a × b.
After n - 1 steps there is only one number left. Can you make this number equal to 24?

Input:
The first line contains a single integer n (1 ≤ n ≤ 105).

Output:
If it's possible, print "YES" in the first line. Otherwise, print "NO" (without the quotes).
If there is a way to obtain 24 as the result number, in the following n - 1 lines print the required operations an operation per line. Each operation should be in form: "a op b = c". Where a and b are the numbers you've picked at this operation; op is either "+", or "-", or "*"; c is the result of corresponding operation. Note, that the absolute value of c mustn't be greater than 1018. The result of the last operation must be equal to 24. Separate operator sign and equality sign from numbers with spaces.
If there are multiple valid answers, you may print any of them.

Sample test(s):

Input:
1
Output:
NO

Input:
8
Output:
YES
8 * 7 = 56
6 * 5 = 30
3 - 4 = -1
1 - 2 = -1
30 - -1 = 31
56 - 31 = 25
25 + -1 = 24

*/