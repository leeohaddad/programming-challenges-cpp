/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 19 - Cut Ribbon                  Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int n, a, b, c;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" a=%d b=%d c=%d;\n",a,b,c);
}
#endif

int main () {
	int maxPieces, minFactor, maxFactorA, maxFactorB, maxFactorC, loopA, loopB, loopC;

	#ifdef debug_on
		printf("\n| P19 - Cut Ribbon |\n");
	#endif

    /* read program arguments */
	scanf("%d %d %d %d", &n, &a, &b, &c);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	maxPieces = 1;
	minFactor = a;
	if (minFactor > b)
		minFactor = b;
	if (minFactor > c)
		minFactor = c;
	if (n % minFactor == 0)
	{
		maxPieces = n / minFactor;
	}
	else
	{
		maxFactorA = n / a + 1;
		for (loopA=0; loopA<maxFactorA; loopA++)
		{
			maxFactorB = (n - loopA*a) / b + 1;
			for (loopB=0; loopB<maxFactorB; loopB++)
			{
				maxFactorC = (n - loopA*a - loopB*b) / c + 1;
				for (loopC=0; loopC<maxFactorC; loopC++)
				{
					if (loopA*a + loopB*b + loopC*c == n)
					{
					if (loopA+loopB+loopC > maxPieces)
						maxPieces = loopA+loopB+loopC;
					}
				}
			}
		}
	}
	printf("%d\n",maxPieces);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

A. Cut Ribbon
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/189/A

Polycarpus has a ribbon, its length is n. He wants to cut the ribbon in a way that fulfils the following two conditions:
After the cutting each ribbon piece should have length a, b or c.
After the cutting the number of ribbon pieces should be maximum.
Help Polycarpus and find the number of ribbon pieces after the required cutting.

Input:
The first line contains four space-separated integers n, a, b and c (1 ≤ n, a, b, c ≤ 4000) — the length of the original ribbon and the acceptable lengths of the ribbon pieces after the cutting, correspondingly. The numbers a, b and c can coincide.

Output:
Print a single number — the maximum possible number of ribbon pieces. It is guaranteed that at least one correct ribbon cutting exists.

Sample test(s):

Input:
5 5 3 2
Output:
2

Input:
7 5 5 2
Output:
2

Note:
In the first example Polycarpus can cut the ribbon in such way: the first piece has length 2, the second piece has length 3.

In the second example Polycarpus can cut the ribbon in such way: the first piece has length 5, the second piece has length 2.

*/