/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 7 - Chat Online                  Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0
#define true 1
#define false 0
typedef int bool;

/* read little guys schedules through command line parameters or through runtime user input */
int **readArgs (int *p, int *q, int *l, int *r, int argc, char *argv[]) {
	int loop;
	int **schedules;
	if (argc>5 && (argc>=2*atoi(argv[1])+2*atoi(argv[2])+5) &&
			atoi(argv[1])>=1 && atoi(argv[1]) <= 50 && atoi(argv[2])>=1 && atoi(argv[2]) <= 50 &&
			atoi(argv[2])>=0 && atoi(argv[2]) <= 1000 && atoi(argv[4])>=0 && atoi(argv[4]) <= 1000) {
		*p = atoi(argv[1]);
		*q = atoi(argv[2]);
		*l = atoi(argv[3]);
		*r = atoi(argv[4]);
		if (debug_on && argc >= 2*(*p)+2*(*q)+6)
			printf("Expected result: %d.\n", atoi(argv[argc-1]));
		schedules = malloc((*p + *q) * sizeof(int *));
		for (loop=0; loop<(*p + *q); loop++) {
			schedules[loop] = malloc(2 * sizeof(int));
			schedules[loop][0] = atoi(argv[2*loop+5]);
			schedules[loop][1] = atoi(argv[2*loop+6]);
		}
	}
	else {
		if (debug_on)
			printf("p: ");
		scanf("%d", p);
		if (debug_on)
			printf("q: ");
		scanf("%d", q);
		if (debug_on)
			printf("l: ");
		scanf("%d", l);
		if (debug_on)
			printf("r: ");
		scanf("%d", r);
		schedules = malloc((*p + *q) * sizeof(int *));
		for (loop=0; loop<*p; loop++) {
			schedules[loop] = malloc(2 * sizeof(int));
			if (debug_on)
				printf("LittleZ schedule interval #%d values: ", loop+1);
			scanf("%d", &schedules[loop][0]);
			if (debug_on)
				printf(" ");
			scanf("%d", &schedules[loop][1]);
		}
		for (loop=*p; loop<(*p + *q); loop++) {
			schedules[loop] = malloc(2 * sizeof(int));
			if (debug_on)
				printf("LittleX schedule interval #%d values: ", loop+1 - *p);
			scanf("%d", &schedules[loop][0]);
			scanf("%d", &schedules[loop][1]);
		}
	}
	return schedules;
}

/* print p, q, l, r and the schedule table */
void printArgs (int p, int q, int l, int r, int **schedule) {
	int loop;	
	printf("Args: p=%d; q=%d; l=%d; r=%d;\n", p, q, l, r);
	printf("LittleZ:\n");
	for (loop=0; loop<p; loop++)
		printf(" %d->%d", schedule[loop][0], schedule[loop][1]);
	printf("\nLittleX:\n");
	for (loop=p; loop<(p+q); loop++)
		printf(" %d->%d", schedule[loop][0], schedule[loop][1]);
}

/* check if LittleX wake up moment t suits for online conversation */
bool momentSuits (int t, int p, int q, int **schedules) {
	int loopLX, loopLZ;
	int a, b, c, d;
	if (debug_on)
		printf("testing t=%d:\n",t);
	for (loopLZ=0; loopLZ<p; loopLZ++) {
		a = schedules[loopLZ][0];
		b = schedules[loopLZ][1];
		for (loopLX=p; loopLX<(p+q); loopLX++) {
			c = schedules[loopLX][0] + t;
			d = schedules[loopLX][1] + t;
			if (debug_on)
				printf(" a:%d b:%d ; c:%d d:%d\n",a,b,c,d);
			if (b>=c && d>=a) {
				if (debug_on)
					printf("result: true\n");
				return true;
			}
		}
	}
	if (debug_on)
		printf("result: false\n");
	return false;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int p, q, l, r, loop, result;
	int **schedules;
	if (debug_on)
		printf("\nP7 - Chat Online:\n");
	schedules = readArgs(&p, &q, &l, &r, argc, argv);
	if (debug_on)
		printArgs(p,q,l,r,schedules);

	if (p<1 || p>50 || q<1 || q>50 || l<0 || l>1000 || r<0 || r>1000) {
		printf("Invalid schedules. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}
	if (debug_on)
		printf("\nProblem Solution:\n");

	result = 0;
	for (loop=l; loop<=r; loop++) {
		if (momentSuits(loop,p,q,schedules) == true)
			result++;
	}
	printf("%d", result);

	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

B. Chat Online
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/469/B

Little X and Little Z are good friends. They always chat online. But both of them have schedules.
Little Z has fixed schedule. He always online at any moment of time between a1 and b1, between a2 and b2, ..., between ap and bp (all borders inclusive). But the schedule of Little X is quite strange, it depends on the time when he gets up. If he gets up at time 0, he will be online at any moment of time between c1 and d1, between c2 and d2, ..., between cq and dq (all borders inclusive). But if he gets up at time t, these segments will be shifted by t. They become [ci + t, di + t] (for all i).
If at a moment of time, both Little X and Little Z are online simultaneosly, they can chat online happily. You know that Little X can get up at an integer moment of time between l and r (both borders inclusive). Also you know that Little X wants to get up at the moment of time, that is suitable for chatting with Little Z (they must have at least one common moment of time in schedules). How many integer moments of time from the segment [l, r] suit for that?

Input:
The first line contains four space-separated integers p, q, l, r (1 ≤  p, q ≤ 50; 0 ≤ l ≤ r ≤ 1000).
Each of the next p lines contains two space-separated integers ai, bi (0 ≤ ai < bi ≤ 1000). Each of the next q lines contains two space-separated integers cj, dj (0 ≤ cj < dj ≤ 1000).
It's guaranteed that bi < ai + 1 and dj < cj + 1 for all valid i and j.

Output:
Output a single integer — the number of moments of time from the segment [l, r] which suit for online conversation.

Sample test(s):

Input:
1 1 0 4
2 3
0 1
Output:
3

Input:
2 3 0 20
15 17
23 26
1 4
7 11
15 17
Output:
20

*/