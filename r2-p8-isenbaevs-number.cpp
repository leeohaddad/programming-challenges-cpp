/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 8 - Isenbaev's Number            Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#define MAX_TEAMS 105
#define MAX_LENGTH 25
#define debug_off 1

/* prrogres: WA3 */

using namespace std;

int n;
char teams[MAX_TEAMS][3][MAX_LENGTH];
map <string,int> isenbaevsNumbers;
map <string, vector<string> > contestantsGraph;
bool isenbaev = false;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, inner_loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" teams:\n");
	for (loop=0; loop<n; loop++) {
        printf("  %d:",loop+1);
		for (inner_loop=0; inner_loop<3; inner_loop++) {
			printf(" %20s",teams[loop][inner_loop]);
		}
		printf("\n");
	}
}
#endif

void processContestant (string name, int number) {
	unsigned int loop;
	if (number >= isenbaevsNumbers[name])
		return;
	isenbaevsNumbers[name] = number;
	for (loop=0; loop<contestantsGraph[name].size(); loop++)
		processContestant(contestantsGraph[name][loop], number+1);
}

int main () {
    int loop, inner_loop;
    char arg[MAX_LENGTH];
    map<string,int>::iterator pairIterator;

	#ifdef debug_on
		printf("\n| P8 - Isenbaev's Number |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		for (inner_loop=0; inner_loop<3; inner_loop++) {
			scanf("%s", arg);
			strcpy(teams[loop][inner_loop],arg);
			isenbaevsNumbers[arg] = MAX_TEAMS;
			if (strcmp(arg,"Isenbaev"))
                isenbaev = true;
		}
		contestantsGraph[teams[loop][0]].push_back(teams[loop][1]);
		contestantsGraph[teams[loop][0]].push_back(teams[loop][2]);
		contestantsGraph[teams[loop][1]].push_back(teams[loop][0]);
		contestantsGraph[teams[loop][1]].push_back(teams[loop][2]);
		contestantsGraph[teams[loop][2]].push_back(teams[loop][0]);
		contestantsGraph[teams[loop][2]].push_back(teams[loop][1]);
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	if (contestantsGraph["Isenbaev"].size() > 0)
        processContestant("Isenbaev",0);
    for(pairIterator = isenbaevsNumbers.begin(); pairIterator != isenbaevsNumbers.end(); pairIterator++) {
		if (pairIterator->second != MAX_TEAMS)
			cout << pairIterator->first << " " << pairIterator->second << endl;
		else
			cout << pairIterator->first << " undefined" << endl;
   }

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1837. Isenbaev's Number
Time limit: 0.5 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1837

Vladislav Isenbaev is a two-time champion of Ural, vice champion of TopCoder Open 2009, and absolute champion of ACM ICPC 2009. In the time you will spend reading this problem statement Vladislav would have solved a problem. Maybe, even two…
Since Vladislav Isenbaev graduated from the Specialized Educational and Scientific Center at Ural State University, many of the former and present contestants at USU have known him for quite a few years. Some of them are proud to say that they either played in the same team with him or played in the same team with one of his teammates…
Let us define Isenbaev's number as follows. This number for Vladislav himself is 0. For people who played in the same team with him, the number is 1. For people who weren't his teammates but played in the same team with one or more of his teammates, the number is 2, and so on. Your task is to automate the process of calculating Isenbaev's numbers so that each contestant at USU would know their proximity to the ACM ICPC champion.

Input:
The first line contains the number of teams n (1 ≤ n ≤ 100). In each of the following n lines you are given the names of the three members of the corresponding team. The names are separated with a space. Each name is a nonempty line consisting of English letters, and its length is at most 20 symbols. The first letter of a name is capital and the other letters are lowercase.

Output:
For each contestant mentioned in the input data output a line with their name and Isenbaev's number. If the number is undefined, output “undefined” instead of it. The contestants must be ordered lexicographically.

Sample:

Input:
7
Isenbaev Oparin Toropov
Ayzenshteyn Oparin Samsonov
Ayzenshteyn Chevdar Samsonov
Fominykh Isenbaev Oparin
Dublennykh Fominykh Ivankov
Burmistrov Dublennykh Kurpilyanskiy
Cormen Leiserson Rivest
Output:
Ayzenshteyn 2
Burmistrov 3
Chevdar 3
Cormen undefined
Dublennykh 2
Fominykh 1
Isenbaev 0
Ivankov 2
Kurpilyanskiy 3
Leiserson undefined
Oparin 1
Rivest undefined
Samsonov 2
Toropov 1

*/
