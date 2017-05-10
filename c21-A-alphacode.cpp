/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 21                   Professor Marcel   **/
/**   Problema A - Alphacode                                       Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c306f6fa9de49e5c74a5/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

// #include <iostream>
#include <cstdio>
// #include <cstdlib>
// #include <cmath>
#include <cstring>
// #include <set>
// #include <vector>
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_STRING 5001
#define debug_off 1
#define ever (;;)

using namespace std;

char input[MAX_STRING];
long long dpTable[MAX_STRING];

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Argument:\n\"");
    printf("%s\" \n",input);
}
#endif

int main () {
	int strlength, loop;
	char charA, charB;

    #ifdef debug_on
        printf("\n| C21.A - Alphacode |\n");
    #endif

    for ever {
        /* read case arguments */
		scanf("%s", input);
		if (input[0] == '0')
			break;

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
		strlength = strlen(input);
		dpTable[0] = dpTable[1] = 1;
		for (loop = 2; loop<=strlength; loop++) {
			dpTable[loop] = 0;
			charA = input[loop - 2] - '0';
			charB = input[loop - 1] - '0';
			if (charA == 1 || (charA == 2 && charB <= 6)) /* segment is ambiguous */
				dpTable[loop] += dpTable[loop - 2];
			if (charB != 0)
				dpTable[loop] += dpTable[loop - 1];
		}
		printf("%lld\n", dpTable[strlength]);

    	#ifdef debug_on
        	printf("--------------------\n");
    	#endif
	}
    return 0;
}