/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 15 - Democracy in Danger         Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 9999
/* #define debug_on 1 */

/* read program arguments through command line parameters or through runtime user input */
int readArgs (int groupsSizes[MAX_SIZE]) {
	int k, loop;
	scanf("%d", &k);
	for (loop=0; loop<k; loop++) {
		scanf("%d", &groupsSizes[loop]);
	}
	return k;
}

#ifdef debug_on
/* print arguments */
void printArgs (int k, int groupsSizes[MAX_SIZE]) {
	int loop;
	printf("\nArguments:\n");
	printf(" k=%d;\n",k);
	printf(" number of voter in each group:\n");
	for (loop=0; loop<k; loop++)
		printf("  %d\n",groupsSizes[loop]);
}
#endif

/* merge two sorted arrays in a sorted way */
void merge (int p, int q, int r, int *v)
{
   int i, j, k, *w;
   w = malloc ((r-p) * sizeof (int));

   for (i = 0, k = p; k < q; ++i, ++k) w[i] = v[k];
   for (j = r-p-1, k = q; k < r; --j, ++k) w[j] = v[k];
   i = 0; j = r-p-1;
   for (k = p; k < r; ++k)
      if (w[i] <= w[j]) v[k] = w[i++];
      else v[k] = w[j--];
   free (w);
}

/* sort array using mergesort algorithm */
void merge_sort (int p, int r, int *v)
{
   if (p < r-1) {
      int q = (p + r)/2;
      merge_sort (p, q, v);
      merge_sort (q, r, v);
      merge (p, q, r, v);
   }
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int k, result, halfOfGeneralGroups, loop;
	int groupsSizes[MAX_SIZE];
	#ifdef debug_on
		printf("\nP15 - Democracy in Danger:\n");
	#endif

	k = readArgs(groupsSizes);

	#ifdef debug_on
		printArgs(k,groupsSizes);
		printf("\nProblem Solution:\n");
	#endif

	/* Solution */
	result = 0;
	halfOfGeneralGroups  = k/2 + 1;
	merge_sort(0, k, groupsSizes);
	for (loop=0; loop<halfOfGeneralGroups; loop++)
		result = result + groupsSizes[loop]/2 + 1;
	printf("%d\n",result);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1025. Democracy in Danger
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1025

Background:
In one of the countries of Caribbean basin all decisions were accepted by the simple majority of votes at the general meeting of citizens (fortunately, there were no lots of them). One of the local parties, aspiring to come to power as lawfully as possible, got its way in putting into effect some reform of the election system. The main argument was that the population of the island recently had increased and it was to longer easy to hold general meetings.
The essence of the reform is as follows. From the moment of its coming into effect all the citizens were divided into K (may be not equal) groups. Votes on every question were to be held then in each group, moreover, the group was said to vote “for” if more than half of the group had voted “for”, otherwise it was said to vote “against”. After the voting in each group a number of group that had voted “for” and “against” was calculated. The answer to the question was positive if the number of groups that had voted “for” was greater than the half of the general number of groups.
At first the inhabitants of the island accepted this system with pleasure. But when the first delights dispersed, some negative properties became obvious. It appeared that supporters of the party, that had introduced this system, could influence upon formation of groups of voters. Due to this they had an opportunity to put into effect some decisions without a majority of voters “for” it.
Let’s consider three groups of voters, containing 5, 5 and 7 persons, respectively. Then it is enough for the party to have only three supporters in each of the first two groups. So it would be able to put into effect a decision with the help of only six votes “for” instead of nine, that would be necessary in the case of general votes.

Problem:
You are to write a program, which would determine according to the given partition of the electors the minimal number of supporters of the party, sufficient for putting into effect of any decision, with some distribution of those supporters among the groups.

Input:
In the first line an only odd integer K — a quantity of groups — is written (1 ≤ K ≤ 101). In the second line there are written K odd integers, separated with a space. Those numbers define a number of voters in each group. The population of the island does not exceeds 9999 persons.

Output:
You should write a minimal quantity of supporters of the party, that can put into effect any decision.

Sample:

Input:
3
5 7 5
Output:
6

*/