/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 16 - Map Coloring                Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#define MAX_SIZE 105
#define debug_off 1

using namespace std;

int n;
vector<long> neighborhood[MAX_SIZE];
int colors[MAX_SIZE];
bool wasColored[MAX_SIZE];
bool error = false;

#ifdef debug_on
/* print arguments */
void printArgs () {
	unsigned int loop;
	int signed_loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" neighborhood:\n");
	for (signed_loop=0; signed_loop<n; signed_loop++) {
		printf("  neighbors of %d:",signed_loop+1);
		for (loop=0; loop<neighborhood[signed_loop].size(); loop++)
			printf(" %ld",neighborhood[signed_loop][loop]+1);
		printf("\n");
	}
}
#endif

bool setColor (int index, int color) {
	unsigned int loop;
	if (colors[index] == color)
		return true;
	if (colors[index] + color == 1) {
		error = true;
		return false;
	}
	#ifdef debug_on
		printf("setColor(%d, %d);\n",index+1,color);
	#endif
	colors[index] = color;
	wasColored[index] = true;
	for (loop=0; loop<neighborhood[index].size(); loop++) {
		if (setColor(neighborhood[index][loop], 1-color) == false)
			return false;
	}
	return true;
}

int main () {
    int loop;
    long arg;

	#ifdef debug_on
		printf("\n| P16 - Map Coloring |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%ld", &arg);
		while (arg != 0) {
			neighborhood[loop].push_back(arg-1);
			neighborhood[arg-1].push_back(loop);
			scanf("%ld", &arg);
		}
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	for (loop=0; loop<n; loop++) {
		colors[loop] = -1;
		wasColored[loop] = false;
	}
	for (loop=0; loop<n; loop++)
		if (!wasColored[loop])
			setColor(loop,0);
	if (!error) {
		for (loop=0; loop<n; loop++)
			printf("%d",colors[loop]);
	}
	else printf("%d",-1);
	printf("\n");

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1080. Map Coloring
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1080

We consider a geographical map with N countries numbered from 1 to N (0 < N < 99). For every country we know the numbers of other countries which are connected with its border. From every country we can reach to any other one, eventually crossing some borders. Write a program which determines whether it is possible to color the map only in two colors — red and blue in such a way that if two countries are connected their colors are different. The color of the first country is red. Your program must output one possible coloring for the other countries, or show, that such coloring is impossible.

Input:
On the first line is written the number N. On the following N lines, the i-th line contains the countries to which the i-th country is connected. Every integer on this line is bigger than i, except the last one which is 0 and marks that no more countries are listed for country i. If a line contains 0, that means that the i-th country is not connected to any other country, which number is larger than i.

Output:
The output contains exactly one line. If the coloring is possible, this line must contain a list of zeros and ones, without any separators between them. The i-th digit in this sequence is the color of the i-th country. 0 corresponds to red color, and one — to blue color. If a coloring is not possible, output the integer −1.

Sample:

Input:
3
2 0
3 0
0
Output:
010

*/
