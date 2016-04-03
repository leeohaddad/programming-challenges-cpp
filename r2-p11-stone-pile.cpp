/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 11 - Stone Pile                   Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
/* #define debug_on 1 */

using namespace std;

int n, sum=0;
vector<long> weights;

#ifdef debug_on
/* print arguments */
void printArgs () {
	unsigned int loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" weights:\n");
	for (loop=0; loop<weights.size(); loop++) {
		printf("  %ld\n",weights[loop]);
	}
}
#endif

long longAbs(long value) {
    if (value >= 0)
        return value;
    return -value;
}

bool intCompare (int a, int b){
	return a < b;
}

long bruteResult;
void bruteForceSolution (int index, long firstPile) {
    long attempt;
    if (index < n) {
        bruteForceSolution(index+1, firstPile+weights[index]);
        bruteForceSolution(index+1, firstPile);
    }
    else {
        attempt = longAbs(sum-2*firstPile);
        if (attempt < bruteResult)
            bruteResult = attempt;
    }
}

int main () {
    int loop;
    long arg; /* halfSum, firstPile=0; */

	#ifdef debug_on
		printf("\n| P11 - Stone Pile |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%ld", &arg);
		weights.push_back(arg);
		sum+=arg;
	}

	#ifdef debug_on
		printArgs();
		printf("sum=%ld;",sum);
		printf("\nProblem Solution:\n");
	#endif

	/* WA7 solution */
	/* sort(weights.begin(), weights.end(), intCompare);
	firstPile = halfSum = (sum + 1)/2;
	for (loop=n-1; loop>=0; loop--) {
        if (weights[loop] <= firstPile) {
            firstPile-=weights[loop];
            #ifdef debug_on
                printf(" %ld is on first pile!\n",weights[loop]);
            #endif
        }
	}
	printf("%ld\n",longAbs(sum-2*(halfSum-firstPile))); */

	/* brute force solution */
	bruteResult = sum;
	bruteForceSolution(0,0);
	printf("%ld\n",bruteResult);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1005. Stone Pile
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1005

You have a number of stones with known weights w1, …, wn. Write a program that will rearrange the stones into two piles such that weight difference between the piles is minimal.

Input:
Input contains the number of stones n (1 ≤ n ≤ 20) and weights of the stones w1, …, wn (integers, 1 ≤ wi ≤ 100000) delimited by white spaces.

Output:
Your program should output a number representing the minimal possible weight difference between stone piles.

Sample:

Input:
5
5 8 13 27 14
Output:
3

*/
