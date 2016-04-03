/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 10 - Werewolf                    Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
#define MAX_SIZE 1005
#define debug_children_on 1
#define debug_off 1

using namespace std;

int n;
set<int> victims;
map< int, set<int> > parents;
map< int, set<int> > children;
bool isSuspect[MAX_SIZE];
bool pPocessed[MAX_SIZE];
bool cProcessed[MAX_SIZE];

#ifdef debug_on
/* print arguments */
void printArgs () {
	int loop;
	set<int>::iterator setIterator;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" familyhood:\n");
	for (loop=0; loop<n; loop++) {
		printf("  parents of %d:",loop+1);
		for (setIterator=parents[loop].begin(); setIterator!=parents[loop].end(); setIterator++)
			printf(" %d",(*setIterator)+1);
		printf("\n");
	}
	#ifdef debug_children_on
		for (loop=0; loop<n; loop++) {
			printf("  children of %d:",loop+1);
			for (setIterator=children[loop].begin(); setIterator!=children[loop].end(); setIterator++)
				printf(" %d",(*setIterator)+1);
			printf("\n");
		}
	#endif
	printf(" victims:\n");
	for (setIterator=victims.begin(); setIterator!=victims.end(); setIterator++)
		printf("  %d\n",(*setIterator)+1);
}
#endif

void eraseAncestors (int index) {
	set<int>::iterator setIterator;
	if (pPocessed[index])
		return;
	pPocessed[index] = true;
	isSuspect[index] = false;
	for (setIterator=parents[index].begin(); setIterator!=parents[index].end(); setIterator++)
		eraseAncestors(*setIterator);
}

void eraseDescendants (int index) {
	set<int>::iterator setIterator;
	if (cProcessed[index])
		return;
	cProcessed[index] = true;
	isSuspect[index] = false;
	for (setIterator=children[index].begin(); setIterator!=children[index].end(); setIterator++)
		eraseDescendants(*setIterator);
}

int main () {
	int loop, arg, child, scanfResult;
   char argc=' ';
   bool firstSuspectFound;
   set<int>::iterator setIterator;

	#ifdef debug_on
		printf("\n| P10 - Werewolf |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);

	scanfResult = scanf("%d", &arg);
	while (scanfResult == 1) {
		child = arg;
		scanfResult = scanf("%d", &arg);
		parents[child-1].insert(arg-1);
		children[arg-1].insert(child-1);
		scanfResult = scanf("%d", &arg);
	}
	scanf("%c",&argc); /* B */
	scanf("%c",&argc); /* L */
	scanf("%c",&argc); /* O */
	scanf("%c",&argc); /* O */
	scanf("%c",&argc); /* D */
	#ifdef debug_on
		printf("read char: %c\n",argc);
	#endif
	scanfResult = scanf("%d", &arg);
	while (scanfResult == 1) {
		victims.insert(arg-1);
		scanfResult = scanf("%d", &arg);
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	for (loop=0; loop<n; loop++) {
		isSuspect[loop] = true;
		pPocessed[loop] = false;
		cProcessed[loop] = false;
	}
	for (setIterator=victims.begin(); setIterator!=victims.end(); setIterator++) {
		eraseAncestors(*setIterator);
		eraseDescendants(*setIterator);
	}
	firstSuspectFound = false;
	for (loop=0; loop<n; loop++) {
		if (isSuspect[loop]) {
			if (firstSuspectFound)
				printf(" %d",loop+1);
			else
				printf("%d",loop+1);
			firstSuspectFound = true;
		}
	}
	if (!firstSuspectFound)
		printf("%d",0);
	printf("\n");

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1242. Werewolf
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1242

Knife. Moonlit night. Rotten stump with a short black-handled knife in it. Those who know will understand. Disaster in the village. Werewolf.
There are no so many residents in the village. Many of them are each other's relatives. Only this may help to find the werewolf. The werewolf is merciless, but his descendants never become his victims. The werewolf can drown the village in blood, but he never kills his ancestors.
It is known about all the villagers who is the child of whom. Also, the sad list of the werewolf's victims is known. Your program should help to determine the suspects. It would be a hard task, if a very special condition would not hold. Namely, citizens of the village are not used to leave it. If some ancestor of some citizen lives in the village, then also his immediate ancestor does. It means, that, for example, if the father of the mother of some citizen still lives in the village, than also his mother still lives.

Input:
The first line contains an integer N, 1 < N â‰¤ 1000, which is the number of the villagers. The villagers are assigned numbers from 1 to N. Further is the description of the relation "child-parent": a sequence of lines, each of which contains two numbers separated with a space; the first number in each line is the number of a child and the second number is the number of the child's parent. The data is correct: for each of the residents there are no more than two parents, and there are no cycles. The list is followed by the word "BLOOD" written with capital letters in a separate line. After this word there is the list of the werewolf's victims, one number in each line.

Output:
The output should contain the numbers of the residents who may be the werewolf. The numbers must be in the ascending order and separated with a space. If there are no suspects, the output should contain the only number 0.

Samples:

Input:
8
1 3
3 6
4 5
6 2
4 6
8 1
BLOOD
3
8
Output:
4 5 7

Input:
6
1 2
3 2
1 4
3 4
2 6
5 2
5 4
BLOOD
2
5
Output:
0

*/