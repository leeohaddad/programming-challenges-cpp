/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 4 - Tennis Game                  Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100000
/* #define debug_on 1 */
#define true 1
#define false 0
typedef int bool;

/* read program arguments */
int readArgs (int serve_winner[MAX_SIZE], int player1Victories[MAX_SIZE], int player2Victories[MAX_SIZE]) {
	int n, loop;
	scanf("%d", &n);
	/* process first serve result */
	scanf("%d", &serve_winner[0]);
	player1Victories[0] = 2 - serve_winner[0];
	player2Victories[0] = serve_winner[0] - 1;
	/* process other serve results */
	for (loop=1; loop<n; loop++) {
		scanf("%d", &serve_winner[loop]);
		player1Victories[loop] = player1Victories[loop-1] - serve_winner[loop] + 2;
		player2Victories[loop] = player2Victories[loop-1] + serve_winner[loop] - 1;
	}
	return n;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n, int serve_winner[MAX_SIZE], int player1Victories[MAX_SIZE], int player2Victories[MAX_SIZE]) {
	int loop;
	printf("\nArguments:\n");
	printf(" n=%d;\n",n);
	printf(" serve_winner:\n");
	for (loop=0; loop<n; loop++)
		printf("  %d (%d x %d)\n",serve_winner[loop],player1Victories[loop],player2Victories[loop]);
}
#endif

int int_max (int x, int y) {
	return ( (x > y) ? x : y );
}

int int_min (int x, int y) {
	return ( (x < y) ? x : y );
}

/* search for an integer in array using binary search */
int binarySearch (int x, int first, int last, int *vector) {
   if (first > last) return -1;
   else {
      int middle = (first + last)/2;
      if (vector[middle] == x) return middle;
      if (vector[middle] > x)
         return binarySearch(x, first, middle-1, vector);
      else  
         return binarySearch(x, middle+1, last, vector); 
   } 
}

/* merge two sorted arrays in a sorted way */
void merge (int p, int q, int r, int v[MAX_SIZE][2])
{
   int i, j, k, w[MAX_SIZE][2];

   for (i = 0, k = p; k < q; ++i, ++k) {
		w[i][0] = v[k][0];
		w[i][1] = v[k][1];
   }
   for (j = r-p-1, k = q; k < r; --j, ++k) {
	   w[j][0] = v[k][0];
	   w[j][1] = v[k][1];
   }
   i = 0; j = r-p-1;
   for (k = p; k < r; ++k)
      if (w[i][0] < w[j][0]) {
		v[k][0] = w[i][0];
		v[k][1] = w[i++][1];
	  }
      else if (w[i][0] > w[j][0])  {
		v[k][0] = w[j][0];
		v[k][1] = w[j--][1];
	  }
	  else /* (w[i][0] == w[j][0]) */ { 
		if (w[i][1] <= w[j][1]) {
			v[k][0] = w[i][0];
			v[k][1] = w[i++][1];
		}
		else /* (w[i][1] > w[j][1]) */ {
			v[k][0] = w[j][0];
			v[k][1] = w[j--][1];
		}
	  }
}

/* sort array using mergesort algorithm */
void merge_sort (int p, int r, int v[MAX_SIZE][2])
{
   if (p < r-1) {
      int q = (p + r)/2;
      merge_sort (p, q, v);
      merge_sort (q, r, v);
      merge (p, q, r, v);
   }
}

void trySolution (int t, int n, int player1Victories[MAX_SIZE], int player2Victories[MAX_SIZE], int result[MAX_SIZE][2], int *resultsCount) {
	int serve, maxSetDuration, p1WinsToCompleteSet, p2WinsToCompleteSet;
	int binarySearchMax, binarySearchResult, p1SetsCount, p2SetsCount;
	#ifdef debug_on
		printf("trySolution(t=%d)\n",t);
	#endif
	serve = 0;
	p1SetsCount = 0;
	p2SetsCount = 0;
	maxSetDuration = 2 * t - 1;
	p1WinsToCompleteSet = t;
	p2WinsToCompleteSet = t;
	while (serve < n)
	{
		binarySearchMax = int_min(serve+maxSetDuration-1, n-1);
		binarySearchResult = binarySearch(p1WinsToCompleteSet, serve, binarySearchMax, player1Victories);
		if (binarySearchResult != -1) {
			p1SetsCount++;
			while (binarySearchResult > 0 && player1Victories[binarySearchResult-1] == p1WinsToCompleteSet)
				binarySearchResult--;
			p1WinsToCompleteSet = p1WinsToCompleteSet + t;
			p2WinsToCompleteSet = p2WinsToCompleteSet + (binarySearchResult - serve + 1 - t);
		}
		else {
			binarySearchMax = int_min(serve+maxSetDuration-1, n-1);
			binarySearchResult = binarySearch(p2WinsToCompleteSet, serve, binarySearchMax, player2Victories);
			if (binarySearchResult == -1)
				return;
			p2SetsCount++;
			while (binarySearchResult > 0 && player2Victories[binarySearchResult-1] == p2WinsToCompleteSet)
				binarySearchResult--;
			p1WinsToCompleteSet = p1WinsToCompleteSet + (binarySearchResult - serve + 1 - t);
			p2WinsToCompleteSet = p2WinsToCompleteSet + t;
		}
        #ifdef debug_on
        if (t==1)
            printf("WinsInSet: %d x %d (SetsWon: %d x %d) [toSet: %d %d] serve = %d\n",player1Victories[binarySearchResult],player2Victories[binarySearchResult],p1SetsCount,p2SetsCount,p1WinsToCompleteSet,p2WinsToCompleteSet,serve);
        #endif
		serve = binarySearchResult + 1;
	}
    #ifdef debug_on
    if (t==1)
        printf("|Result| p1Sets:%d; p2Sets:%d; serve:%d;\n",p1SetsCount,p2SetsCount,serve);
    #endif
	if (serve == n) {
	    if (p1SetsCount > p2SetsCount && player1Victories[n-1] > player1Victories[n-2]) {
			result[*resultsCount][0] = p1SetsCount;
			result[*resultsCount][1] = t;
			*resultsCount = *resultsCount + 1;
		}
	    else if (p2SetsCount > p1SetsCount && player2Victories[n-1] > player2Victories[n-2]) {
			result[*resultsCount][0] = p2SetsCount;
			result[*resultsCount][1] = t;
			*resultsCount = *resultsCount + 1;
		}
	}
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, maxServesWon, setsSizeAttempt, resultsCount, loop;
	int serve_winner[MAX_SIZE], player1Victories[MAX_SIZE], player2Victories[MAX_SIZE], result[MAX_SIZE][2];
	#ifdef debug_on
		printf("\nP4 - Tennis Game:\n");
	#endif

	n = readArgs(serve_winner, player1Victories, player2Victories);

	#ifdef debug_on
		printArgs(n,serve_winner,player1Victories,player2Victories);
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	resultsCount = 0;
	maxServesWon = int_max(player1Victories[n-1], player2Victories[n-1]);
	
	for (setsSizeAttempt=maxServesWon; setsSizeAttempt>0; setsSizeAttempt--) {
		trySolution(setsSizeAttempt,n,player1Victories,player2Victories,result,&resultsCount);
	}
	merge_sort(0,resultsCount-1,result);
	printf("%d\n",resultsCount);
	for (loop=0; loop<resultsCount; loop++)
		printf("%d %d\n",result[loop][0],result[loop][1]);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

D. Tennis Game
time limit per test: 2 seconds
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/496/D

Petya and Gena love playing table tennis. A single match is played according to the following rules: a match consists of multiple sets, each set consists of multiple serves. Each serve is won by one of the players, this player scores one point. As soon as one of the players scores t points, he wins the set; then the next set starts and scores of both players are being set to 0. As soon as one of the players wins the total of s sets, he wins the match and the match is over. Here s and t are some positive integer numbers.
To spice it up, Petya and Gena choose new numbers s and t before every match. Besides, for the sake of history they keep a record of each match: that is, for each serve they write down the winner. Serve winners are recorded in the chronological order. In a record the set is over as soon as one of the players scores t points and the match is over as soon as one of the players wins s sets.
Petya and Gena have found a record of an old match. Unfortunately, the sequence of serves in the record isn't divided into sets and numbers s and t for the given match are also lost. The players now wonder what values of s and t might be. Can you determine all the possible options?

Input:
The first line contains a single integer n — the length of the sequence of games (1 ≤ n ≤ 10^5).
The second line contains n space-separated integers ai. If ai = 1, then the i-th serve was won by Petya, if ai = 2, then the i-th serve was won by Gena.
It is not guaranteed that at least one option for numbers s and t corresponds to the given record.

Output:
In the first line print a single number k — the number of options for numbers s and t.
In each of the following k lines print two integers si and ti — the option for numbers s and t. Print the options in the order of increasing si, and for equal si — in the order of increasing ti.

Sample test(s):

Input:
5
1 2 1 2 1
Output:
2
1 3
3 1

Input:
4
1 1 1 1
Output:
3
1 4
2 2
4 1

Input:
4
1 2 1 2
Output:
0

Input:
8
2 1 2 1 1 1 1 1
Output:
3
1 6
2 3
6 1

*/