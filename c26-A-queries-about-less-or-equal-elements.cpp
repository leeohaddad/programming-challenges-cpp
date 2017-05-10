/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 26                   Professor Marcel   **/
/**   Problema A - Queries about less or equal elements            Curso: BCC   **/
/**   https://www.codepit.io/#/problems/565e03e7f53fca8c09330b16/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
// #include <stdio.h>
#include <cstdio>
#include <cstdlib>
// #include <math.h>
// #include <cmath> 
// #include <cstring>
// #include <set>
// #include <vector>
// #include <stack>
#include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_N_M 200005
#define MAX_NUM 1000000005
#define debug_off 1

using namespace std;

int n, m;
int a[MAX_N_M];
int b[MAX_N_M];

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n m=%d;\n",m);
}

void printVectors () {
	int loop;
	printf("Vectors:\n");
	printf(" n=%d;\n", n);
	for (loop=0; loop<n; loop++)
		printf("  -> %d\n", a[loop]);
	printf(" m=%d;\n", m);
	for (loop=0; loop<m; loop++)
		printf("  -> %d\n", b[loop]);
}
#endif

/* https://www.ime.usp.br/~pf/algoritmos/aulas/mrgsrt.html */
void intercala (int p, int q, int r, int v[])
{
   int i, j, k;
   int aux[MAX_N_M];
   
   for (i = p; i < q; ++i)
      aux[i-p] = v[i];
   for (j = q; j < r; ++j)
      aux[r-p+q-j-1] = v[j];
   i = 0; j = r-p-1;
   for (k = p; k < r; ++k)
      if (aux[i] <= aux[j])
         v[k] = aux[i++];
      else
         v[k] = aux[j--];
}

/* https://www.ime.usp.br/~pf/algoritmos/aulas/mrgsrt.html */
void mergesort (int p, int r, int v[])
{
   if (p < r-1) {
      int q = (p + r) / 2;
      mergesort (p, q, v);
      mergesort (q, r, v);
      intercala (p, q, r, v);
   }
}

int modifiedBinSearchR (int x, int e, int d, int v[]) {
   if (e > d) return e;
   else {
      int m = (e + d) / 2;
      if (v[m] == x)
      	return m;
      if (v[m] < x)  
         return modifiedBinSearchR (x, m+1, d, v);
      else  
         return modifiedBinSearchR (x, e, m-1, v); 
   } 
}

int modifiedBinSearch(int x, int n)
{
	int first = 0, last = n - 1, mid;
	while (first <= last)
	{
		mid = (first + last) / 2;
		#ifdef debug_on
			printf("  first: %d\n  mid: %d\n  last: %d\n", first, mid, last);
		#endif
		if (first == last)
		{
			if (a[first] == x || a[first] < x)
				return first + 1;
			else if (a[first] > x)
				return first;
		}
		if (a[mid] == x || a[mid] < x)
			first = mid + 1;
		else if (a[mid] > x)
			last = mid - 1;
	}
	return first;
}

int main () {
	int loop, result;
	
	#ifdef debug_on
		printf("\n| C26.A - Queries about less or equal elements |\n");
	#endif

	/* read program arguments */
	scanf("%d %d", &n, &m);
	for (loop=0; loop<n; loop++)
		scanf("%d", &a[loop]);
	for (loop=0; loop<m; loop++)
		scanf("%d", &b[loop]);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
   sort(a, a+n);
   #ifdef debug_on
		printVectors();
	#endif
   for (loop=0; loop<m; loop++) {
      if (b[loop] < a[0]) {
   		result = 0;
   	}
   	else if (b[loop] > a[n-1]) {
   		result = n;
   	}
   	else {
   		result = modifiedBinSearch(b[loop], n);
   	}
   	printf("%d ", result);
   }
   printf("\n");

	#ifdef debug_on
	printf("\n--------------------\n");
	#endif
	return 0;
}