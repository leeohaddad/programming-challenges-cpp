/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 9 - Two Sets                     Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/* #define debug_on 1 */
#define true 1
#define false 0
typedef int bool;

/* read initial set through command line parameters or through runtime user input */
int *readArgs (int *n, int *a, int *b, int argc, char *argv[]) {
	int loop;
	int *initialSet;
	if (argc>4 && (argc>=atoi(argv[1])+4) && atoi(argv[1])>=1 && atoi(argv[1]) <= 100000) {
		*n = atoi(argv[1]);
		*a = atoi(argv[2]);
		*b = atoi(argv[3]);
		initialSet = malloc(*n * sizeof(int));
		for (loop=0; loop<*n; loop++) {
			initialSet[loop] = atoi(argv[loop+4]);
		}
	}
	else {
		#ifdef debug_on
			printf("n: ");
		#endif
		scanf("%d", n);
		#ifdef debug_on
			printf("a: ");
		#endif
		scanf("%d", a);
		#ifdef debug_on
			printf("b: ");
		#endif
		scanf("%d", b);
		initialSet = malloc(*n * sizeof(int));
		for (loop=0; loop<*n; loop++) {
			#ifdef debug_on
				printf("element #%d value: ", loop+1);
			#endif
			scanf("%d", &initialSet[loop]);
		}
	}
	return initialSet;
}

#ifdef debug_on
/* print arguments */
void printArgs (int n, int a, int b, int *initialSet) {
	int loop;
	printf("\nArguments:\n");
	printf(" n=%d; a=%d; b=%d;\n",n,a,b);
	printf(" initialSet:\n");
	for (loop=0; loop<n; loop++)
		printf("  %d\n",initialSet[loop]);
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

/* search for an integer in array using binary search */
int binarySearch (int x, int e, int d, int *v) {
   if (e > d) return -1;
   else {
      int m = (e + d)/2;
      if (v[m] == x) return m;
      if (v[m] < x)  
         return binarySearch(x, m+1, d, v);
      else  
         return binarySearch(x, e, m-1, v); 
   } 
}

/* look for an int in array and return its index */
int findElementIndex (int number, int n, int *initialSet, bool alreadyFoundResult) {
	int result = binarySearch(number, 0, n-1, initialSet);
	if (!alreadyFoundResult) {
		#ifdef debug_on
			if (result != -1)
				printf("true: contains %d\n", number);
			else
				printf("false: does not contain %d\n", number);
		#endif
	}
	return result;
}

int tryToFitInSet (int index, int set, int n, int a, int b, int *initialSet, int *result, bool checkDeeply) {
	int cIndex, ocIndex, ccIndex, iBuffer, ciBuffer;
	#ifdef debug_on
		printf("tryToFitInSet: %d in set %d",initialSet[index],set);
		if (checkDeeply)
			printf(" deeply");
		printf("\n");
	#endif
	while (set > 1)
		set = set - 2;
	if (result[index] == set) {
		return 1;
	}
	if (set == 0) {
		cIndex = findElementIndex(a-initialSet[index],n,initialSet,false);
		if (cIndex!=-1 && result[cIndex]!=1) {
			if (!checkDeeply)
				return cIndex;
			else {
				iBuffer = result[index];
				ciBuffer = result[cIndex];
				result[index] = 0;
				result[cIndex] = 0;
				ocIndex = findElementIndex(b-initialSet[index],n,initialSet,false);
				#ifdef debug_on
					printf("check if other complementary of %d can survive\n", initialSet[index]);
				#endif
				if (tryToFitInSet(ocIndex,2,n,a,b,initialSet,result,checkDeeply) == -1) {
					result[index] = iBuffer;
					result[cIndex] = ciBuffer;
					return -1;
				}
				ccIndex = findElementIndex(b-initialSet[cIndex],n,initialSet,false);
				#ifdef debug_on
					printf("check if other complementary of %d that is complementary of %d can survive\n", initialSet[cIndex], initialSet[index]);
				#endif
				if (ccIndex!=-1 && tryToFitInSet(ccIndex,2,n,a,b,initialSet,result,checkDeeply)==-1) {
					result[index] = iBuffer;
					result[cIndex] = ciBuffer;
					return -1;
				}
				return cIndex;
			}
		}
		else return -1;
	} else /* (set == 1) */ {
		cIndex = findElementIndex(b-initialSet[index],n,initialSet,false);
		if (cIndex!=-1 && result[cIndex]!=0) {
			if (!checkDeeply)
				return cIndex;
			else {
				iBuffer = result[index];
				ciBuffer = result[cIndex];
				result[index] = 1;
				result[cIndex] = 1;
				ocIndex = findElementIndex(a-initialSet[index],n,initialSet,false);
				#ifdef debug_on
					printf("check if other complementary of %d can survive\n", initialSet[index]);
				#endif
				if (tryToFitInSet(ocIndex,3,n,a,b,initialSet,result,checkDeeply) == -1) {
					result[index] = iBuffer;
					result[cIndex] = ciBuffer;
					return -1;
				}
				ccIndex = findElementIndex(a-initialSet[cIndex],n,initialSet,false);
				#ifdef debug_on
					printf("check if other complementary of %d that is complementary of %d can survive\n", initialSet[cIndex], initialSet[index]);
				#endif
				if (ccIndex!=-1 && tryToFitInSet(ccIndex,3,n,a,b,initialSet,result,checkDeeply)==-1) {
					result[index] = iBuffer;
					result[cIndex] = ciBuffer;
					return -1;
				}
				return cIndex;
			}
		}
		else return -1;
	}
}

/* separate the numbers into two sets respecting restrictions a & b */
bool separateInTwoSets (int n, int a, int b, int *initialSet, int *result) {
	int loop, index;
	bool finishedIteration = false;
	for (loop=0; loop<n; loop++) 
		result[loop] = -1;
	for (loop=0; loop<n; loop++) {
		#ifdef debug_on
			if (result[loop] == -1)
				printf("\ncheck %d for %d(%d) and %d(%d):\n",initialSet[loop],a,a-initialSet[loop],b,b-initialSet[loop]);
		#endif
		finishedIteration = false;
		if (result[loop] != -1)
			finishedIteration = true;
		if (!finishedIteration) {
			index = tryToFitInSet(loop,0,n,a,b,initialSet,result,false);
			if (index != -1) {
				if (tryToFitInSet(loop,1,n,a,b,initialSet,result,false) != -1) {
					if (tryToFitInSet(loop,0,n,a,b,initialSet,result,true) == -1) {
						if (tryToFitInSet(loop,1,n,a,b,initialSet,result,true) == -1) {
							printf("NO\n");
							return false;
						}
					}
					#ifdef debug_on
						printf("goes to set %d\n",result[loop]);
					#endif
				}
				else {
					result[loop] = 0;
					result[index] = 0;
					finishedIteration = true;
					#ifdef debug_on
						printf("goes to set 0\n");
					#endif
				}
			}
			else {
				index = tryToFitInSet(loop,1,n,a,b,initialSet,result,false);
				if (index != -1) {
					result[loop] = 1;
					result[index] = 1;
					finishedIteration = true;
					#ifdef debug_on
						printf("goes to set 1\n");
					#endif
				}
				else {
					printf("NO\n");
					return false;
				}
			}
		}
	}
	return true;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int n, a, b, loop;
	int *initialSet, *orderedSet, *result;
   	#ifdef debug_on
		printf("\nP9 - Two Sets:\n");
	#endif
	initialSet = readArgs(&n, &a, &b, argc, argv);
	#ifdef debug_on
		printArgs(n,a,b,initialSet);
	#endif
	orderedSet = malloc(n * sizeof(int));
	for (loop=0; loop<n; loop++)
		orderedSet[loop] = initialSet[loop];
	merge_sort(0,n,orderedSet);

	if (n<1 || n>100000 || a<1 || a>1000000000 || b<1 || b>1000000000) {
		printf("Invalid parameters. Aborting...\n");
		printf("\n--------------------\n");
		return 1;	
	}
	#ifdef debug_on
		printf("\nProblem Solution:\n");
	#endif

	result = malloc(n * sizeof(int));
	if (separateInTwoSets(n,a,b,orderedSet,result)) {
		printf("YES\n");
		for (loop=0; loop<n; loop++) {
			#ifdef debug_on
				printf("%d - %d ( ",loop+1,initialSet[loop]);
			#endif
			printf("%d ",result[findElementIndex(initialSet[loop],n,orderedSet,true)]);
			#ifdef debug_on
				printf(")\n");
			#endif
		}
		printf("\n");
	}

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

B. Two Sets
time limit per test: 1 second
memory limit per test: 256 megabytes
input: standard input
output: standard output
url: http://codeforces.com/problemset/problem/468/B

Little X has n distinct integers: p1, p2, ..., pn. He wants to divide all of them into two sets A and B. The following two conditions must be satisfied:
If number x belongs to set A, then number a - x must also belong to set A.
If number x belongs to set B, then number b - x must also belong to set B.
Help Little X divide the numbers into two sets or determine that it's impossible.

Input:
The first line contains three space-separated integers n, a, b (1 ≤ n ≤ 105; 1 ≤ a, b ≤ 109). The next line contains n space-separated distinct integers p1, p2, ..., pn (1 ≤ pi ≤ 109).

Output:
If there is a way to divide the numbers into two sets, then print "YES" in the first line. Then print n integers: b1, b2, ..., bn (bi equals either 0, or 1), describing the division. If bi equals to 0, then pi belongs to set A, otherwise it belongs to set B.
If it's impossible, print "NO" (without the quotes).

Sample test(s):
Input:
4 5 9
2 3 4 5
Output:
YES
0 0 1 1

Input:
3 3 4
1 2 4
Output:
NO

Note:
It's OK if all the numbers are in the same set, and the other one is empty.

*/