/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 28                   Professor Marcel   **/
/**   Problema A - New Year Transportation                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce66921926e63b4daea4/view?index=0   **/
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

int n, t, position;
bool canGo;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" n=%d;\n t=%d;\n",n,t);
}
#endif

int main () {
	int loop;
	
	#ifdef debug_on
		printf("\n| C28.A - New Year Transportation |\n");
	#endif

   /* read program arguments */
   scanf("%d %d", &n, &t);
   int a[n];
   for (loop=1; loop<n; loop++)
      scanf("%d", &a[loop]);

   #ifdef debug_on
   	printArgs();
   	printf("\nProblem Solution:\n");
   #endif

	/* solution */
   canGo = false;
   position = 1;
   while(position < n) {
      position += a[position];
      if(position == t) {
         canGo = true;
         break;
      }
      if (position > t)
      	break;
    }
    if (canGo)
      printf("YES\n");
   else
      printf("NO\n");

	#ifdef debug_on
	printf("\n--------------------\n");
	#endif
	return 0;
}