/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 1 - Minimal Difficulty           Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0

/* read program arguments through command line parameters or through runtime user input */
int *readArgs (int *n, int argc, char *argv[]) {
	int loop;
	int *holds;
	if (argc>2 && (argc>=atoi(argv[1])+2) && atoi(argv[1])>=3 && atoi(argv[1]) <= 100) {
		*n = atoi(argv[1]);
		if (debug_on)
			printf("%d holds found in arguments!\n", *n);
		if (argc >= *n+3)
			if (debug_on)
				printf("Expected result: %d.\n", atoi(argv[argc-1]));
		holds = malloc(*n * sizeof(int));
		for (loop=0; loop<*n; loop++) {
			holds[loop] = atoi(argv[loop+2]);
		}
	}
	else {
		if (debug_on)
			printf("#holds: ");
		scanf("%d", n);
		holds = malloc(*n * sizeof(int));
		for (loop=0; loop<*n; loop++) {
			if (debug_on)
				printf("hold #%d height: ", loop+1);
			scanf("%d", &holds[loop]);
		}
	}
	return holds;
}

/* find current difficulty and check if min hole is bigger */
int main (int argc, char *argv[]) {
	int n, loop;
	int *holds;
	int currentDifficulty = 0;
	int minHole = 1001;
	int dif, hole;
	if (debug_on)
		printf("\nP1 - Minimal Difficulty:\n");
	holds = readArgs(&n, argc, argv);

	if (n<3 || n>100) {
		printf("Invalid holds number. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}
	if (debug_on)
		printf("\nProblem Solution:\n");
	for (loop=1; loop<n; loop++) {
		if (debug_on)
			printf("#%d: %d.\n", loop+1, holds[loop]);
		dif = holds[loop]-holds[loop-1];
		if (dif > currentDifficulty) {
			currentDifficulty = dif;
		}
		if (loop < n-1) {
			hole = holds[loop+1] - holds[loop-1];
			if (hole < minHole) 
				minHole = hole;
		}
	}
	if (minHole > currentDifficulty)
		currentDifficulty = minHole;
	printf("%d", currentDifficulty);
	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

A. Minimum Difficulty
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/496/A

Mike is trying rock climbing but he is awful at it.
There are n holds on the wall, i-th hold is at height ai off the ground. Besides, let the sequence ai increase, that is, ai < ai + 1 for all i from 1 to n - 1; we will call such sequence a track. Mike thinks that the track a1, ..., an has difficulty . In other words, difficulty equals the maximum distance between two holds that are adjacent in height.
Today Mike decided to cover the track with holds hanging on heights a1, ..., an. To make the problem harder, Mike decided to remove one hold, that is, remove one element of the sequence (for example, if we take the sequence (1, 2, 3, 4, 5) and remove the third element from it, we obtain the sequence (1, 2, 4, 5)). However, as Mike is awful at climbing, he wants the final difficulty (i.e. the maximum difference of heights between adjacent holds after removing the hold) to be as small as possible among all possible options of removing a hold. The first and last holds must stay at their positions.
Help Mike determine the minimum difficulty of the track after removing one hold.

Input:
The first line contains a single integer n (3 ≤ n ≤ 100) — the number of holds.
The next line contains n space-separated integers ai (1 ≤ ai ≤ 1000), where ai is the height where the hold number i hangs. The sequence ai is increasing (i.e. each element except for the first one is strictly larger than the previous one).

Output:
Print a single number — the minimum difficulty of the track after removing a single hold.

Sample test(s):

Input:
3
1 4 6
Output:
5

Input:
5
1 2 3 4 5
Output:
2

Input:
5
1 2 3 7 8
Output:
4

Note:
In the first sample you can remove only the second hold, then the sequence looks like (1, 6), the maximum difference of the neighboring elements equals 5.
In the second test after removing every hold the difficulty equals 2.
In the third test you can obtain sequences (1, 3, 7, 8), (1, 2, 7, 8), (1, 2, 3, 8), for which the difficulty is 4, 5 and 5, respectively. Thus, after removing the second element we obtain the optimal answer — 4.

*/