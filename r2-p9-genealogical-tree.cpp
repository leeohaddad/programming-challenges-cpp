/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 9 - Genealogical Tree            Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_SIZE 105
#define debug_off 1

using namespace std;

int n;
vector<int> children[MAX_SIZE];
vector<int> parents[MAX_SIZE];
bool processed[MAX_SIZE];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
	unsigned int inner_loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	for (loop=0; loop<n; loop++) {
        printf(" |#%d|\n  children:",loop+1);
        for (inner_loop=0; inner_loop<children[loop].size(); inner_loop++)
            printf(" %d",children[loop][inner_loop]+1);
        printf("\n  parents:");
        for (inner_loop=0; inner_loop<parents[loop].size(); inner_loop++)
            printf(" %d",parents[loop][inner_loop]+1);
        printf("\n");
	}
}
#endif

void processMartian (int index) {
    unsigned int loop;
    if (processed[index])
        return;
    for (loop=0; loop<parents[index].size(); loop++)
        processMartian(parents[index][loop]);
    if (processed[index])
        return;
    printf("%d ", index+1);
    processed[index] = true;
}

int main () {
    int loop;
    int arg;

	#ifdef debug_on
		printf("\n| P9 - Genealogical Tree |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%d", &arg);
		while (arg != 0) {
            children[loop].push_back(arg-1);
            parents[arg-1].push_back(loop);
            scanf("%d", &arg);
		}
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	for (loop=0; loop<n; loop++) {
        processMartian(loop);
	}
	printf("\n");

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1022. Genealogical Tree
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1022

Background:
The system of Martians’ blood relations is confusing enough. Actually, Martians bud when they want and where they want. They gather together in different groups, so that a Martian can have one parent as well as ten. Nobody will be surprised by a hundred of children. Martians have got used to this and their style of life seems to them natural.
And in the Planetary Council the confusing genealogical system leads to some embarrassment. There meet the worthiest of Martians, and therefore in order to offend nobody in all of the discussions it is used first to give the floor to the old Martians, than to the younger ones and only than to the most young childless assessors. However, the maintenance of this order really is not a trivial task. Not always Martian knows all of his parents (and there’s nothing to tell about his grandparents!). But if by a mistake first speak a grandson and only than his young appearing great-grandfather, this is a real scandal.

Problem:
Your task is to write a program, which would define once and for all, an order that would guarantee that every member of the Council takes the floor earlier than each of his descendants.

Input:
The first line of the standard input contains an only number N, 1 ≤ N ≤ 100 — a number of members of the Martian Planetary Council. According to the centuries-old tradition members of the Council are enumerated with integers from 1 up to N. Further, there are exactly N lines, moreover, the i-th line contains a list of i-th member’s children. The list of children is a sequence of serial numbers of children in a arbitrary order separated by spaces. The list of children may be empty. The list (even if it is empty) ends with 0.

Output:
The standard output should contain in its only line a sequence of speakers’ numbers, separated by spaces. If several sequences satisfy the conditions of the problem, you are to write to the standard output any of them. At least one such sequence always exists.

Sample:

Input:
5
0
4 5 1 0
1 0
5 3 0
3 0
Output:
2 4 5 3 1

*/
