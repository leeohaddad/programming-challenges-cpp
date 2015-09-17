/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 3 - Removing Columns             Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0
#define true 1
#define false 0
typedef int bool;

/* read letters table through command line parameters or through runtime user input */
char **readArgs (int *n, int *m, int argc, char *argv[]) {
	int loop, inner_loop;
	char **letters;
	if (argc>3 && (argc>=atoi(argv[1])+3) && atoi(argv[1])>=1 && atoi(argv[1]) <= 100 && atoi(argv[2])>=1 && atoi(argv[2]) <= 100) {
		*n = atoi(argv[1]);
		*m = atoi(argv[2]);
		if (debug_on)
			printf("%d x %d letters matrix found in arguments!\n", *n, *m);
		if (debug_on && argc >= *n+4)
			printf("Expected result: .\n");
		letters = malloc(*n * sizeof(char *));
		for (loop=0; loop<*n; loop++) {
			letters[loop] = malloc(*m * sizeof(char));
				for (inner_loop=0; inner_loop<*m; inner_loop++)
					letters[loop][inner_loop] = argv[loop+3][inner_loop];
		}
	}
	else {
		if (debug_on)
			printf("n: ");
		scanf("%d", n);
		if (debug_on)
			printf("m: ");
		scanf("%d", m);
		letters = malloc(*n * sizeof(char *));
		for (loop=0; loop<*n; loop++) {
			if (debug_on)
				printf("word for line #%d: ", loop+1);
			letters[loop] = malloc(*m * sizeof(char));
			scanf("%d",&inner_loop);
			for (inner_loop=0; inner_loop<*m; inner_loop++) {
				scanf("%c",&letters[loop][inner_loop]);
			}
		}
	}
	return letters;
}

/* print letters table */
void printLetters (char **letters, int n, int m) {
	int loop,inner_loop;
	for (loop=0; loop<n; loop++) {
		for (inner_loop=0; inner_loop<m; inner_loop++) {
			printf("%c",letters[loop][inner_loop]);
		}
		printf("\n");
	}
}

/* compare 2 rows & returns -1 if firstRow <= secondRow or the index of char that makes firstRow lexicographically larger */ 
int compare2Rows (char *firstRow, char *secondRow, int m) {
	int loop;
	for (loop=0; loop<m; loop++) {
		if (firstRow[loop] < secondRow[loop])
			return -1;
		if (firstRow[loop] > secondRow[loop])
			return loop;
	}
	return -1;
}

/* compare table rows to identify some column that breaks the lexicographical top-to-bottom order */
int getBadColumnId (char **letters, int n, int m) {
	int loop;
	int compareResult;
	for (loop=0; loop<n-1; loop++) {
		compareResult = compare2Rows(letters[loop],letters[loop+1],m);
		if (compareResult != -1)
			return compareResult;
	}
	return -1;
}

/* remove column "badTableColumnId" from letters table & returns the new table */
char **removeColumn(int badTableColumnId, char **letters, int *n, int *m) {
	char **buffer = letters;
	int loop, inner_loop;
	if (*m == 0)
		return letters;
	if (debug_on)
		printf("removeColumn(%d):\n",badTableColumnId);
	letters = malloc(*n * sizeof(char *));
	for (loop=0; loop<*n; loop++) {
		letters[loop] = malloc((*m - 1) * sizeof(char));
		for (inner_loop=0; inner_loop<badTableColumnId; inner_loop++) {
			letters[loop][inner_loop] = buffer[loop][inner_loop];
		}
		for (inner_loop=badTableColumnId+1; inner_loop<*m; inner_loop++) {
			letters[loop][inner_loop-1] = buffer[loop][inner_loop];
		}
	}
	free(buffer);
	*m = *m - 1;
	return letters;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	char **letters;
	int n;
	int m;
	int result = 0;
	int badTableColumnId;
	if (debug_on)
		printf("\nP3 - Removing Columns:\n");
	
	letters = readArgs(&n,&m,argc,argv);
	if (debug_on)
		printLetters(letters,n,m);
	if (n<1 || m<1 || n>100 || m>100) {
		printf("Invalid table size. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}

	if (debug_on)
		printf("\nProblem Solution:\n");
	badTableColumnId = getBadColumnId(letters,n,m);
	while (badTableColumnId > -1) {
		letters = removeColumn(badTableColumnId,letters,&n,&m);
		badTableColumnId = getBadColumnId(letters,n,m);
		result++;
		if (debug_on)
			printLetters(letters,n,m);
	}
	
	printf("%d",result);
	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

C. Removing Columns
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/496/C

You are given an n × m rectangular table consisting of lower case English letters. In one operation you can completely remove one column from the table. The remaining parts are combined forming a new table. For example, after removing the second column from the table
 abcd
 edfg
 hijk
we obtain the table:
 acd
 efg
 hjk
A table is called good if its rows are ordered from top to bottom lexicographically, i.e. each row is lexicographically no larger than the following one. Determine the minimum number of operations of removing a column needed to make a given table good.

Input:
The first line contains two integers  — n and m (1 ≤ n, m ≤ 100).
Next n lines contain m small English letters each — the characters of the table.

Output:
Print a single number — the minimum number of columns that you need to remove in order to make the table good.

Sample test(s):

Input:
1 10
codeforces
Output:
0

Input:
4 4
case
care
test
code
Output:
2

Input:
5 4
code
forc
esco
defo
rces
Output:
4

Note:
In the first sample the table is already good.
In the second sample you may remove the first and third column.
In the third sample you have to remove all the columns (note that the table where all rows are empty is considered good by definition).
Let strings s and t have equal length. Then, s is lexicographically larger than t if they are not equal and the character following the largest common prefix of s and t (the prefix may be empty) in s is alphabetically larger than the corresponding character of t.

*/