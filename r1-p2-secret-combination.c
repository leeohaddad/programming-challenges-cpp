/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 2 - Secret Combination           Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define debug_on 1==0
#define true 1
#define false 0
typedef int bool;

/* same as math.pow, but with int result & arguments */
int int_pow (int base, int factor) {
	if (factor == 0) return 1;
	if (factor == 1) return base;
	return base * int_pow(base, factor-1);
}

/* convert a positive long value into array of digits (0<=digit<=9) */
void longToDigitsArray (long number, int *digitsArray, int n) {
	int loop;
	for (loop=0; loop<n; loop++)
		digitsArray[loop] = (number % int_pow(10,n-loop)) / int_pow(10,n-loop-1);
}

/* convert a string with a positive long value into array of digits (0<=digit<=9) */
void stringToDigitsArray (char *source, int *digitsArray, int n) {
	int loop;
	for (loop=0; loop<n; loop++)
		digitsArray[loop] = source[loop] - '0';
}

/* fill destination with same values as source */
void copyDigits (int *source, int *destination, int n) {
	int loop;
	for (loop=0; loop<n; loop++)
		destination[loop] = source[loop];
}

/* read program arguments through command line parameters or through runtime user input */
int *readArgs (int *n, int argc, char *argv[]) {
	int loop;
	char readChar;
	int *numberAsArray;
	if (argc>2 && atoi(argv[1])>=1 && atoi(argv[1]) <= 1000) {
		*n = atoi(argv[1]);
		numberAsArray = malloc(*n * sizeof(int));
		if (debug_on)
			printf("%d digits on the display!\n", *n);
		if (argc >= 4 && debug_on) {
			stringToDigitsArray(argv[argc-1], numberAsArray, *n);
			printf("Expected result: ");
			for (loop=0; loop<*n; loop++)
				printf("%d", numberAsArray[loop]);
			printf(".\n");
		}
		stringToDigitsArray(argv[2], numberAsArray, *n);
	}
	else {
		if (debug_on)
			printf("#digits: ");
		scanf("%d", n);
		numberAsArray = malloc(*n * sizeof(int));
		if (debug_on)
			printf("initial display state: ");
		scanf("%c", &readChar);
		for (loop=0; loop<*n; loop++) {
			scanf("%c", &readChar);
			numberAsArray[loop] = readChar - '0';
		}
	}
	return numberAsArray;
}

/* check if int number is smaller than int compareTo */ 
bool isSmallerThan (int *number, int *compareTo, int n) {
	int loop;
	for (loop=0; loop<n; loop++) {
		if (number[loop] < compareTo[loop])
			return true;
		if (number[loop] > compareTo[loop])
			return false;
	}
	return false;
}

/* first button */
void addOne (int *digits, int n) {
	int loop;
	for (loop=0; loop<n; loop++) {
		digits[loop] = digits[loop]+1;
		if (digits[loop]>9)
			digits[loop] = digits[loop] - 10;
	}
}

/* second button */
void shiftRight (int *digits, int n) {
	int loop;
	int lastDigit = digits[n-1];
	for (loop=n-1; loop>0; loop--)
		digits[loop] = digits[loop-1];
	digits[0] = lastDigit;
}

/* find the minimum possible digits combination to display */
int main (int argc, char *argv[]) {
	int n, loop, inner_loop, n_adds;
	int *digits;
	int *result;
	if (debug_on)
		printf("\nP2 - Secret Combination:\n");
	
	digits = readArgs(&n, argc, argv);
	
	if (debug_on) {
		printf("initial digits: ");
		for (inner_loop=0; inner_loop<n; inner_loop++)
			printf("%d",digits[inner_loop]);
		printf("\n");
	}

	if (n<1 || n>1000) {
		printf("Invalid digits count. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}

	if (debug_on)
		printf("\nProblem Solution:\n");

	result = malloc(n * sizeof(int));
	copyDigits(digits,result,n);

	for (loop=0; loop<n; loop++) {
		shiftRight(digits,n);
		n_adds = 10 - digits[0];
		if (n_adds < 10)
			for (inner_loop=0; inner_loop<n_adds; inner_loop++)
				addOne(digits,n);
		if (isSmallerThan(digits,result,n))
			copyDigits(digits,result,n);

		if (debug_on) {
			printf("%d new_digits: ",n);
			for (inner_loop=0; inner_loop<n; inner_loop++)
				printf("%d",digits[inner_loop]);
			printf("\n");
		}
	}

	for (loop=0; loop<n; loop++)
		printf("%d",result[loop]);

	if (debug_on)
		printf("\n--------------------\n");
	return 0;
}

/*

B. Secret Combination
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/496/B

You got a box with a combination lock. The lock has a display showing n digits. There are two buttons on the box, each button changes digits on the display. You have quickly discovered that the first button adds 1 to all the digits (all digits 9 become digits 0), and the second button shifts all the digits on the display one position to the right (the last digit becomes the first one). For example, if the display is currently showing number 579, then if we push the first button, the display will show 680, and if after that we push the second button, the display will show 068.
You know that the lock will open if the display is showing the smallest possible number that can be obtained by pushing the buttons in some order. The leading zeros are ignored while comparing numbers. Now your task is to find the desired number.

Input:
The first line contains a single integer n (1 ≤ n ≤ 1000) — the number of digits on the display.
The second line contains n digits — the initial state of the display.

Output:
Print a single line containing n digits — the desired state of the display containing the smallest possible number.

Sample test(s):

Input: 
3
579
Output:
024

Input:
4
2014
Output:
0142

*/