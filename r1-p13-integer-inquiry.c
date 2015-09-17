/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 13 - Integer Inquiry             Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 102
/* #define debug_on 1 */

/* read program arguments through command line parameters or through runtime user input */
int readArgs (int veryLongIntegers[MAX_SIZE][MAX_SIZE], int integersLengths[MAX_SIZE], int *maxLength) {
	int veryLongIntegerIndex, veryLongIntegerPosition, scanfResult;
	char digit;
	*maxLength = 0;
	veryLongIntegerIndex = 0;
	scanfResult = scanf("%c", &digit);
	while (scanfResult == 1) {
		veryLongIntegerPosition = 0;
		while (digit != '\n') {
			veryLongIntegers[veryLongIntegerIndex][veryLongIntegerPosition++] = digit - '0';
			scanfResult = scanf("%c", &digit);
		}
		integersLengths[veryLongIntegerIndex] = veryLongIntegerPosition;
		if (veryLongIntegerPosition > *maxLength)
			*maxLength = veryLongIntegerPosition;
		veryLongIntegerIndex++;
		if (veryLongIntegerPosition==1 && veryLongIntegers[veryLongIntegerIndex-1][0]==0)
			return veryLongIntegerIndex;
		scanfResult = scanf("%c", &digit);
	}
	return veryLongIntegerIndex;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n, int veryLongIntegers[MAX_SIZE][MAX_SIZE], int integersLengths[MAX_SIZE]) {
	int loop, inner_loop;
	printf("\nArguments:\n");
	printf(" #veryLongIntegers=%d;\n",n);
	printf(" veryLongIntegers:\n");
	for (loop=0; loop<n; loop++) {
		printf("  (l:%d) ", integersLengths[loop]);
		for (inner_loop=0; inner_loop<integersLengths[loop]; inner_loop++) {
			printf("%d",veryLongIntegers[loop][inner_loop]);
		}
		printf("\n");
	}
}
#endif

/* sum veryLongIntegers */
int sumVeryLongIntegers (int n, int veryLongIntegers[MAX_SIZE][MAX_SIZE], int integersLengths[MAX_SIZE], int result[MAX_SIZE], int maxLength) {
	int loop, inner_loop, partialSum, valueToSend, numberIndex;
	valueToSend = 0;
	loop = 0;
	for (loop=0; loop<maxLength+2; loop++) {
		#ifdef debug_on
			printf("(%d): ", loop+1);
		#endif
		partialSum = 0;
		for (inner_loop=0; inner_loop<n; inner_loop++) {
			if (loop < integersLengths[inner_loop]) {
				numberIndex = integersLengths[inner_loop] - loop - 1;
				partialSum = partialSum + veryLongIntegers[inner_loop][numberIndex];
				#ifdef debug_on
					printf("%d(%d) ", veryLongIntegers[inner_loop][numberIndex], partialSum);
				#endif
			}
		}
		/* printf("[%d resto 10 = %d + %d = %d] ", partialSum, partialSum%10, valueToSend, partialSum%10 + valueToSend); */
		partialSum = partialSum + valueToSend;
		valueToSend = partialSum/10;
		result[loop] = partialSum%10;
		#ifdef debug_on
			printf("= %d (valueToSend=%d)\n", result[loop], valueToSend);
		#endif
	}
	while (result[loop-1] == 0)
		loop--;
	return loop;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, maxLength, loop;
	int integersLengths[MAX_SIZE];
	int veryLongIntegers[MAX_SIZE][MAX_SIZE];
	int result[MAX_SIZE];
	#ifdef debug_on
		printf("\nP13 - Integer Inquiry:\n");
	#endif

	n = readArgs(veryLongIntegers,integersLengths,&maxLength);

	#ifdef debug_on
		printArgs(n,veryLongIntegers,integersLengths);
		printf("\nProblem Solution:\n");
	#endif

	n = sumVeryLongIntegers(n,veryLongIntegers,integersLengths,result,maxLength);
	for (loop=n-1; loop>=0; loop--)
		printf("%d",result[loop]);
	printf("\n");

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

424 - Integer Inquiry
Time limit: 3.000 seconds
Url: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=365

One of the first users of BIT's new supercomputer was Chip Diller. He extended his exploration of powers of 3 to go from 0 to 333 and he explored taking various sums of those numbers.
``This supercomputer is great,'' remarked Chip. ``I only wish Timothy were here to see these results.'' (Chip moved to a new apartment, once one became available on the third floor of the Lemon Sky apartments on Third Street.)

Input:
The input will consist of at most 100 lines of text, each of which contains a single VeryLongInteger. Each VeryLongInteger will be 100 or fewer characters in length, and will only contain digits (no VeryLongInteger will be negative).
The final input line will contain a single zero on a line by itself.

Output:
Your program should output the sum of the VeryLongIntegers given in the input.

Sample Input:
123456789012345678901234567890
123456789012345678901234567890
123456789012345678901234567890
0

Sample Output:
370370367037037036703703703670

*/