/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 30                   Professor Marcel   **/
/**   Problema A - Vanya and Books                                 Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce7a921926e63b4daf8d/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
#include <stdio.h>
// #include <cstdio>
// #include <cstdlib>
// #include <math.h>
// #include <cmath> 
// #include <cstring>
// #include <set>
// #include <vector>
// #include <stack>
#include <algorithm>
// #include <utility>
// #include <iomanip>
#define debug_off 1

using namespace std;

long long n;
long long digits;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
}
#endif

int main () {
	long long loop, aux;
	
	#ifdef debug_on
		printf("\n| C28.A - Vanya and Books |\n");
	#endif

   /* read program arguments */
   scanf("%lld", &n);

   #ifdef debug_on
   	printArgs();
   	printf("\nProblem Solution:\n");
   #endif

	/* solution */
   digits = 0;
   for (loop=1, aux=1; loop<=10; loop++, aux *= 10)
      digits += max(0ll, min(n, aux * 10 - 1) - aux + 1) * loop;
   printf("%lld\n", digits);

	#ifdef debug_on
	printf("\n--------------------\n");
	#endif
	return 0;
}