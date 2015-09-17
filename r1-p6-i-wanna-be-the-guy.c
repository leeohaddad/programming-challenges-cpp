/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 6 - I Wanna Be The Guy           Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0
#define true 1
#define false 0
typedef int bool;

/* read number of levels & levels they can pass through command line parameters or through runtime user input */
int *readArgs (int *n, int *p, int *q, int argc, char *argv[]) {
	int loop;
	int *levelsTheyCanPass, *buffer;
	if (argc>=4 && atoi(argv[1])>=1 && atoi(argv[1]) <= 100) {
		*n = atoi(argv[1]);
		*p = atoi(argv[2]);
		*q = atoi(argv[3+(*p)]);
		if (debug_on)
			printf("%d levels found in arguments!\n", *n);
		levelsTheyCanPass = malloc((*p + *q) * sizeof(int));
		for (loop=0; loop<*p; loop++) {
			levelsTheyCanPass[loop] = atoi(argv[loop+3]);
		}
		for (loop=0; loop<*q; loop++) {
			levelsTheyCanPass[loop + *p] = atoi(argv[loop+4 + *p]);
		}
	}
	else {
		if (debug_on)
			printf("#levels: ");
		scanf("%d", n);
		if (debug_on)
			printf("p: ");
		scanf("%d", p);
		buffer = malloc(*p * sizeof(int));
		if (debug_on)
			printf("levels LittleX can pass:");
		for (loop=0; loop<*p; loop++) {
			if (debug_on)
				printf(" ");
			scanf("%d", &buffer[loop]);
		}
		if (debug_on)
			printf("q: ");
		scanf("%d", q);
		levelsTheyCanPass = malloc((*p + *q) * sizeof(int));
		for (loop=0; loop<*p; loop++)
			levelsTheyCanPass[loop] = buffer[loop];
		if (debug_on)
			printf("levels LittleY can pass:");
		for (loop=0; loop<*q; loop++) {
			if (debug_on)
				printf(" ");
			scanf("%d", &levelsTheyCanPass[loop + *p]);
		}
	}
	return levelsTheyCanPass;
}

/* prints n, p, q and levelsTheyCanPass */
void printArguments (int n, int p, int q, int *levelsTheyCanPass) {
	int loop;
	printf("n=%d\n",n);
	printf("p=%d:",p);
	for (loop=0; loop<p; loop++)
		printf(" %d",levelsTheyCanPass[loop]);
	printf(";\n");
	printf("q=%d:",q);
	for (loop=0; loop<q; loop++)
		printf(" %d",levelsTheyCanPass[loop + p]);
	printf(".\n");
}

/* check if the little guys can pass all levels */
bool theyCanPassAllLevels (int n, int p, int q, int *levelsTheyCanPass) {
	int possibleRedundancyNumber, differentLevelsPassed, loop;
	bool *levels;
	differentLevelsPassed = 0;
	possibleRedundancyNumber = p + q - n;
	levels = malloc(n * sizeof(bool));
	for (loop=0; loop<n; loop++)
		levels[loop] = false;
	for (loop=0; loop<(p+q); loop++) {
		if (levels[levelsTheyCanPass[loop]-1] == true) {
			possibleRedundancyNumber--;
			if (possibleRedundancyNumber<0)
				return false;
		}
		else differentLevelsPassed++;
		levels[levelsTheyCanPass[loop]-1] = true;
	}
	if (differentLevelsPassed < n)
		return false;
	return true;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, p, q;
	int *levelsTheyCanPass;
	if (debug_on)
		printf("\nP6 - I Wanna Be The Guy:\n");
	levelsTheyCanPass = readArgs(&n, &p, &q, argc, argv);
	if (debug_on)
		printArguments(n,p,q,levelsTheyCanPass);

	if (n<1 || n>100) {
		printf("Invalid levels number. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}
	if (debug_on)
		printf("\nProblem Solution:\n");

	if (theyCanPassAllLevels(n,p,q,levelsTheyCanPass))
		printf("I become the guy.");
	else
		printf("Oh, my keyboard!");

	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

A. I Wanna Be the Guy
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/469/A

There is a game called "I Wanna Be the Guy", consisting of n levels. Little X and his friend Little Y are addicted to the game. Each of them wants to pass the whole game.
Little X can pass only p levels of the game. And Little Y can pass only q levels of the game. You are given the indices of levels Little X can pass and the indices of levels Little Y can pass. Will Little X and Little Y pass the whole game, if they cooperate each other?

Input:
The first line contains a single integer n (1 ≤  n ≤ 100).
The next line contains an integer p (0 ≤ p ≤ n) at first, then follows p distinct integers a1, a2, ..., ap (1 ≤ ai ≤ n). These integers denote the indices of levels Little X can pass. The next line contains the levels Little Y can pass in the same format. It's assumed that levels are numbered from 1 to n.

Output:
If they can pass all the levels, print "I become the guy.". If it's impossible, print "Oh, my keyboard!" (without the quotes).

Sample test(s):

Input:
4
3 1 2 3
2 2 4
Output:
I become the guy.

Input:
4
3 1 2 3
2 2 3
Output:
Oh, my keyboard!

Note:
In the first sample, Little X can pass levels [1 2 3], and Little Y can pass level [2 4], so they can pass all the levels both.
In the second sample, no one can pass level 4.

*/