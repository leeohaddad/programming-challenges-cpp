/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 24 - Pick Up Sticks              Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 1000000
/* #define debug_on 1 */
#define ever (loop=1;loop>0;loop++)
#define true 1
#define false 0
typedef int bool;

struct list {
	int id;
	struct list *next;
};

struct stick {
	int nParents; /* sticks above count */
	struct list *children; /* sticks below */
	bool removed; 
};

#ifdef debug_on
/* print arguments */
void printArgs (int n, int m, int sticksAbove[MAX_SIZE][2]) {
	int loop;
	printf("\nArguments:\n");
	printf(" n=%d;\n",n);
	printf(" m=%d;\n",m);
	printf(" sticksAbove:\n");
	for (loop=0; loop<m; loop++)
		printf("  %d %d\n",sticksAbove[loop][0],sticksAbove[loop][1]);
}
#endif

void isAbove (int above, int below, struct stick *sticks) {
	struct list *lastChild;
	struct list *newChild;
	sticks[below].nParents++;
	newChild = malloc(sizeof(struct list));
	newChild->id = below;
	newChild->next = NULL;
	if (sticks[above].children == NULL) {
		sticks[above].children = newChild;
		return;
	}
	else {
		for (lastChild=sticks[above].children; lastChild->next!=NULL; lastChild=lastChild->next);
		lastChild->next = newChild;
	}
}

/* if possible, remove the stick and try to remove the sticks below it */
void tryToRemove (struct stick *sticks, int stick, int *removedSticksCount, int *removedSticks) {
	struct list *child;
	if (sticks[stick].nParents > 0) {
		#ifdef debug_on
			printf("  tryed to remove %d, but it has %d unremoved sticks above.\n",stick+1,sticks[stick].nParents);
		#endif
		return;
	}
	if (sticks[stick].removed == true) {
		#ifdef debug_on
			printf("  tryed to remove %d, but it was already removed.\n",stick+1);
		#endif
		return;
	}
	#ifdef debug_on
		printf("  removing stick %d.\n",stick+1);
	#endif
	sticks[stick].removed = true;
	removedSticks[*removedSticksCount] = stick+1;
	*removedSticksCount = *removedSticksCount + 1;
	for (child=sticks[stick].children; child!=NULL; child=child->next) {
		sticks[child->id].nParents--;
		#ifdef debug_on
			printf("    #parents for %d is now %d.\n",child->id+1,sticks[child->id].nParents);
		#endif
	}
	for (child=sticks[stick].children; child!=NULL; child=child->next)
		tryToRemove(sticks, child->id, removedSticksCount, removedSticks);
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, m, loop, removedSticksCount;
	struct stick *sticks;
	int *removedSticks;
	int sticksAbove[MAX_SIZE][2];
	#ifdef debug_on
		printf("\nP4 - Pick Up Sticks:\n");
	#endif

	for ever {
		scanf("%d", &n);
		scanf("%d", &m);
		sticks = malloc(n * sizeof(struct stick));
		removedSticks = malloc(n * sizeof(int));
		removedSticksCount = 0;
		if (n == 0 || m == 0)
			return 0;
		/* init sticks */
		for (loop=0; loop<n; loop++) {
			sticks[loop].nParents = 0;
			sticks[loop].children = NULL;
			sticks[loop].removed = false;
		}
		/* read restrictions */
		for (loop=0; loop<m; loop++) {
			scanf("%d", &sticksAbove[loop][0]);
			scanf("%d", &sticksAbove[loop][1]);
			isAbove(sticksAbove[loop][0]-1, sticksAbove[loop][1]-1, sticks);
		}


		#ifdef debug_on
			printArgs(n,m,sticksAbove);
			printf("\nProblem Solution:\n");
		#endif

		for (loop=0; loop<n; loop++)
			if (sticks[loop].nParents == 0)
				tryToRemove(sticks, loop, &removedSticksCount, removedSticks);
		if (removedSticksCount == n) {
			for (loop=0; loop<removedSticksCount; loop++) {
				printf("%d\n",removedSticks[loop]);
			}
		}
		else {
			printf("IMPOSSIBLE\n");
			#ifdef debug_on
				printf("Removed sticks: %d/%d\n",removedSticksCount,n);
			#endif
		}

		#ifdef debug_on
			printf("\n--------------------\n");
		#endif
	}

	return 0;
}

/*

11686 - Pick up sticks
Time limit: 5.000 seconds 
url: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=2733

Pick up sticks is a fascinating game.
A collection of coloured sticks are
dumped in a tangled heap on the
table.  Players take turns trying
to pick up a single stick at a time
without moving any of the other
sticks. It is very difficult to pick up
a stick if there is another stick lying
on top of it. The players therefore
try to pick up the sticks in an order
such that they never have to pick
up a stick from underneath another
stick.

Input:
The input consists of several test
cases.  The first line of each test
case contains two integers n and m each at least one and no greater than one million.
The integer n is the number of sticks, and m is the number of lines that follow.
The sticks are numbered from 1 to n.
Each of the following lines contains a pair of integers a, b, indicating that there is a point where stick a lies on top of stick b.
The last line of input is `0 0'. These zeros are not values of n and m, and should not be processed as such.

Output:
For each test case, output n lines of integers, listing the sticks in the order in which they could be
picked up without ever picking up a stick with another stick on top of it. If there are multiple such
correct orders, any one will do. If there is no such correct order, output a single line containing the
word `IMPOSSIBLE'.

SampleInput:
3 2
1 2
2 3
0 0

SampleOutput:
1
2
3

*/