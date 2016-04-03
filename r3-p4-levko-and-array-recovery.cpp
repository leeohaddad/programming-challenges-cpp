/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 4 - Levko and Array Recovery     Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ABS_LIMIT 1000000000
#define MAX_SIZE 5005
#define debug_off 1

using namespace std;

int n, m;
long operations[MAX_SIZE][4];

#ifdef debug_on
/* print arguments */
void printArgs () {
	int loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" m=%d;\n",m);
	printf(" operations:\n");
	for (loop=0; loop<m; loop++) {
		printf("  %ld %ld %ld %ld\n",operations[loop][0],operations[loop][1],operations[loop][2],operations[loop][3]);
	}
}
/* print solution */
void printSolutionAttempt (long max[MAX_SIZE], int currentOp) {
	int loop;
	printf("tryToSolve:\n");
	printf(" currentOp=%d;\n",currentOp);
	printf(" max:\n");
	for (loop=0; loop<n; loop++)
		printf("  %ld\n",max[loop]);
	printf("\n");
}
#endif

long longMin (long a, long b) {
	if (a<b)
		return a;
	else
		return b;
}

bool checkResult (long max[MAX_SIZE]) {
	int loop, inner_loop;
	bool resultOK;
	long result[MAX_SIZE];
	for (loop=0; loop<n; loop++) {
		if (max[loop] < -ABS_LIMIT)
			return false;
		result[loop] = longMin(max[loop],ABS_LIMIT);
		max[loop] = result[loop];
	}
	for (loop=0; loop<m; loop++) {
		if (operations[loop][0] == 1) {
			for (inner_loop=operations[loop][1]-1; inner_loop < operations[loop][2]; inner_loop++)
				result[inner_loop] = result[inner_loop] + operations[loop][3];
		}
		else /* if (operations[loop][0] == 2) */ {
			resultOK = false;
			for (inner_loop=operations[loop][1]-1; inner_loop < operations[loop][2]; inner_loop++) {
				if (result[inner_loop] == operations[loop][3])
					resultOK = true;
			}
			if (!resultOK)
				return false;
		}
	}

	printf("YES\n");
	printf("%ld",max[0]);
	for (loop=1; loop<n; loop++)
		printf(" %ld",max[loop]);
	printf("\n");
	return true;
}

bool tryToSolve(long max[MAX_SIZE], int currentOp) {
	int loop, op, rangeA, rangeB, arg;
	#ifdef debug_on
		printSolutionAttempt(max,currentOp);
	#endif
	// check if finished checking operations
	if (currentOp == 0) {
		return checkResult(max);
	}
	// retrieve operation infos
	op = operations[currentOp-1][0];
	rangeA = operations[currentOp-1][1]-1;
	rangeB = operations[currentOp-1][2]-1;
	arg = operations[currentOp-1][3];
	// set intervals outside range
	for (loop=0; loop<rangeB; loop++)
		max[loop] = max[loop];
	for (loop=rangeB+1; loop<n; loop++)
		max[loop] = max[loop];
	// execute current operation inside range
	if (op == 1) {
		// sum operation
		for (loop=rangeA; loop<=rangeB; loop++)
			max[loop] = max[loop] - arg;
		// keep checking operations
		if (tryToSolve(max,currentOp-1))
			return true;
	}
	else /* if (op == 2) */ {
		// max operation
		for (loop=rangeA; loop<=rangeB; loop++) {
			if (max[loop] > arg)
				max[loop] = arg;
			else
				max[loop] = max[loop];
		}
		if (tryToSolve(max,currentOp-1))
			return true;
	}
	// attempt failed
	return false;
}

int main () {
    int loop;
    long arg1, arg2, arg3, arg4;
    long max[MAX_SIZE];

	#ifdef debug_on
		printf("\n| P4 - Levko and Array Recovery |\n");
	#endif

    /* read program arguments */
	scanf("%d %d", &n, &m);
	for (loop=0; loop<m; loop++) {
		scanf("%ld %ld %ld %ld", &arg1, &arg2, &arg3, &arg4);
		operations[loop][0] = arg1;
		operations[loop][1] = arg2;
		operations[loop][2] = arg3;
		operations[loop][3] = arg4;
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif
	
	/* presets */ 
	for (loop=0; loop<n; loop++)
		max[loop] = ABS_LIMIT;

	/* solution */
	if (!tryToSolve(max,m))
		printf("NO\n");
	
	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

A. Levko and Array Recovery
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/contest/360/problem/A

Levko loves array a1, a2, ... , an, consisting of integers, very much. That is why Levko is playing with array a, performing all sorts of operations with it. Each operation Levko performs is of one of two types:
    Increase all elements from li to ri by di. In other words, perform assignments aj = aj + di for all j that meet the inequation li ≤ j ≤ ri.
    Find the maximum of elements from li to ri. That is, calculate the value . 
Sadly, Levko has recently lost his array. Fortunately, Levko has records of all operations he has performed on array a. Help Levko, given the operation records, find at least one suitable array. The results of all operations for the given array must coincide with the record results. Levko clearly remembers that all numbers in his array didn't exceed 109 in their absolute value, so he asks you to find such an array.

Input:
The first line contains two integers n and m (1 ≤ n, m ≤ 5000) — the size of the array and the number of operations in Levko's records, correspondingly.
Next m lines describe the operations, the i-th line describes the i-th operation. The first integer in the i-th line is integer ti (1 ≤ ti ≤ 2) that describes the operation type. If ti = 1, then it is followed by three integers li, ri and di (1 ≤ li ≤ ri ≤ n,  - 104 ≤ di ≤ 104) — the description of the operation of the first type. If ti = 2, then it is followed by three integers li, ri and mi (1 ≤ li ≤ ri ≤ n,  - 5·107 ≤ mi ≤ 5·107) — the description of the operation of the second type.
The operations are given in the order Levko performed them on his array.

Output:
In the first line print "YES" (without the quotes), if the solution exists and "NO" (without the quotes) otherwise.
If the solution exists, then on the second line print n integers a1, a2, ... , an (|ai| ≤ 109) — the recovered array.

Sample test(s):

Input:
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 8

Output:
YES
4 7 4 7

Input:
4 5
1 2 3 1
2 1 2 8
2 3 4 7
1 1 3 3
2 3 4 13
Output:
NO

*/