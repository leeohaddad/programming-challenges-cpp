/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 25                   Professor Marcel   **/
/**   Problema A - Parentheses Balance                             Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2b8f6fa9de49e5c52d4/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
// #include <stdio.h>
#include <cstdio>
// #include <cstdlib>
// #include <math.h>
// #include <cmath> 
#include <cstring>
// #include <set>
// #include <vector>
#include <stack>
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_STRING 140
#define debug_off 1

using namespace std;

int n;
stack<char> checkerStack;
char myString[MAX_STRING];

#ifdef debug_on
/* print arguments */
void printArgs () {
  int loop;
  printf("Arguments:\n");
  printf(" n=%d;\n",n);
}
#endif

int main () {
	int loop, len;

  #ifdef debug_on
    printf("\n| C25.A - Parentheses Balance |\n");
  #endif

  /* read program arguments */
	scanf("%d", &n);
	getc(stdin);

  #ifdef debug_on
    printArgs();
    printf("\nProblem Solution:\n");
  #endif

  /* solution */
	while (n--) {
		while (!checkerStack.empty())
			checkerStack.pop();
		gets(myString);
		len = strlen(myString);
		for (loop=0; loop<len; loop++) {
			if (myString[loop] == '(' || myString[loop] == '[') {
				checkerStack.push(myString[loop]);
			} else if (myString[loop] == ')') {
				if (checkerStack.empty() || checkerStack.top() != '(') {
					checkerStack.push('a');
					break;
				}
				checkerStack.pop();
			} else if (myString[loop] == ']') {
				if (checkerStack.empty() || checkerStack.top() != '[') {
					checkerStack.push('a');
					break;
				}
				checkerStack.pop();
			}
		}
		if(checkerStack.empty())
			printf("Yes\n");
		else
			printf("No\n");
	}

	#ifdef debug_on
  printf("\n--------------------\n");
  #endif
  return 0;
}