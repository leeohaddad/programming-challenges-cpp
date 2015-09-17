/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 12 - Labyrinth                   Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
/* #define debug_on 1 */

/* read program arguments through command line parameters or through runtime user input */
int readArgs (char labyrinth[MAX_SIZE][MAX_SIZE], int argc, char *argv[]) {
	int n, loop, inner_loop;
	char trash;
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%c", &trash);
		for (inner_loop=0; inner_loop<n; inner_loop++)
			scanf("%c", &labyrinth[loop][inner_loop]);
	}
	return n;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n, char labyrinth[MAX_SIZE][MAX_SIZE]) {
	int loop, inner_loop;
	printf("\nArguments:\n");
	printf(" n=%d;\n",n);
	printf(" labyrinth:\n");
	for (loop=0; loop<n; loop++) {
		printf("  ");
		for (inner_loop=0; inner_loop<n; inner_loop++)
			printf("%c",labyrinth[loop][inner_loop]);
		printf("\n");
	}
}
#endif

long process (int line, int column, int n, char labyrinth[MAX_SIZE][MAX_SIZE], int wasProcessed[MAX_SIZE][MAX_SIZE]) {
	int result = 0;
	if (labyrinth[line][column]=='#' || wasProcessed[line][column]==1 || line<0 || column<0 || line>=n || column>=n)
		return 0;
	wasProcessed[line][column]=1;
	
	/* left */
	if (column==0) {
		if (line!=0)
			result++;
	}
	else if (labyrinth[line][column-1]=='#') {
		result++;
	}
	else
		result += process(line,column-1,n,labyrinth,wasProcessed);
	
	/* up */
	if (line==0) {
		if (column!=0)
			result++;
	}
	else if (labyrinth[line-1][column]=='#') {
		result++;
	}
	else
		result += process(line-1,column,n,labyrinth,wasProcessed);
	
	/* right */
	if (column==(n-1)) {
		if (line!=(n-1))
			result++;	
	}
	else if (labyrinth[line][column+1]=='#') {
		result++;	
	}
	else
		result += process(line,column+1,n,labyrinth,wasProcessed);
	
	/* down */
	if (line==(n-1)) {
		if (column!=(n-1))
			result++;
	}
	else if (labyrinth[line+1][column]=='#') {
		result++;
	}
	else
		result += process(line+1,column,n,labyrinth,wasProcessed);
	
	#ifdef debug_on
		printf("processing %d,%d: %d\n",line,column, result);
	#endif
	return result;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n;
	long wallsToPaint;
	char labyrinth[MAX_SIZE][MAX_SIZE];
	int wasProcessed[MAX_SIZE][MAX_SIZE];
	#ifdef debug_on
		printf("\nP12 - Labyrinth:\n");
	#endif

	n = readArgs(labyrinth, argc, argv);

	#ifdef debug_on
		printArgs(n,labyrinth);
		printf("\nProblem Solution:\n");
	#endif

	/* Solution */
	wallsToPaint = process(0,0,n,labyrinth,wasProcessed);
	if (wasProcessed[n-1][n-1] == 0)
		wallsToPaint += process(n-1,n-1,n,labyrinth,wasProcessed);
	printf("%ld\n", 3*3*wallsToPaint);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1033. Labyrinth
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1033

Administration of the labyrinth has decided to start a new season with new wallpapers. For this purpose they need a program to calculate the surface area of the walls inside the labyrinth. This job is just for you!
The labyrinth is represented by a matrix N×N (3 ≤ N ≤ 33, you see, ‘3’ is a magic digit!). Some matrix cells contain a dot character (‘.’) that denotes an empty square. Other cells contain a diesis character (‘#’) that denotes a square filled by monolith block of stone wall. All squares are of the same size 3×3 meters.
The walls are constructed around the labyrinth (except for the upper left and lower right corners, which are used as entrances) and on the cells with a diesis character. No other walls are constructed. There always will be a dot character at the upper left and lower right corner cells of the input matrix.
Your task is to calculate the area of visible part of the walls inside the labyrinth. In other words, the area of the walls' surface visible to a visitor of the labyrinth. Note that there's no holes to look or to move through between any two adjacent blocks of the wall. The blocks are considered to be adjacent if they touch each other in any corner. See picture for an example: visible walls inside the labyrinth are drawn with bold lines. The height of all the walls is 3 meters.

Input:
The first line of the input contains the single number N. The next N lines contain N characters each. Each line describes one row of the labyrinth matrix. In each line only dot and diesis characters will be used and each line will be terminated with a new line character. There will be no spaces in the input.

Output:
Your program should print to the output a single integer — the exact value of the area of the wallpaper needed.

Sample:

Input:
5
.....
...##
..#..
..###
.....
Output:
198

*/