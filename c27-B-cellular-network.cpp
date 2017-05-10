/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 27                   Professor Marcel   **/
/**   Problema B - Cellular Network                                Curso: BCC   **/
/**   https://www.codepit.io/#/problems/579c42b74b66422800e761ad/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
// #include <stdio.h>
#include <cstdio>
// #include <cstdlib>
// #include <math.h>
#include <cmath> 
// #include <cstring>
// #include <set>
// #include <vector>
// #include <stack>
#include <algorithm>
// #include <utility>
// #include <iomanip>
#define debug_off 1

using namespace std;

int n, m;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n m=%d;\n",n,m);
}
#endif

int main () {
	int loop, innerLoop;
	long long result = 0;
	
	#ifdef debug_on
		printf("\n| C27.B - Cellular Network |\n");
	#endif

	/* solution */
	while (~scanf("%d %d", &n, &m)) {
		#ifdef debug_on
			printArgs();
			printf("\nProblem Solution:\n");
		#endif
   	long long cities[n];
   	long long towers[m];
   	innerLoop = 0;
		for (loop=0; loop<n; loop++)
			scanf("%lld", cities + loop);
		for (loop=0; loop<m; loop++)
			scanf("%lld", towers + loop);
		for (loop=0; loop<n; loop++) {
      	while (innerLoop + 1 < m && abs(cities[loop] - towers[innerLoop]) >= abs(cities[loop] - towers[innerLoop+1]))
      		innerLoop++;
      	result = max(result, abs(cities[loop] - towers[innerLoop]));
   	}
		printf("%lld\n", result);
   }

	#ifdef debug_on
	printf("\n--------------------\n");
	#endif
	return 0;
}