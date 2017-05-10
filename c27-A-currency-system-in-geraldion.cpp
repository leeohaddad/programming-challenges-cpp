/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 27                   Professor Marcel   **/
/**   Problema A - Currency System in Geraldion                    Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce7f921926e63b4dafbe/view?index=0   **/
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
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define debug_off 1

using namespace std;

int n, value;
bool hasValueOne = false;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
}
#endif

int main () {
	int loop;
	
	#ifdef debug_on
		printf("\n| C27.A - Currency System in Geraldion |\n");
	#endif

	/* read n */
	scanf("%d", &n);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
   for (loop=0; loop<n; loop++) {
		scanf("%d", &value);
      if (value == 1) {
         hasValueOne = true;
      }
   }

   if (hasValueOne == true)
   	printf("-1\n");
   else
   	printf("1\n");

	#ifdef debug_on
	printf("\n--------------------\n");
	#endif
	return 0;
}