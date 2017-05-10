/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 22                   Professor Marcel   **/
/**   Problema B - Cube Numbers                                    Curso: BCC   **/
/**   https://www.codepit.io/#/problems/577c2ef38d41284d00e89843/view?index=1   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
// #include <cstdlib>
#include <cmath>
// #include <cstring>
// #include <set>
// #include <vector>
// #include <algorithm>
// #include <utility>
// #include <iomanip>
#define MAX_N 100005
#define MAX_CUBE 46
#define SUPREME 1000000
#define ever (;;)
#define debug_off 1

using namespace std;

int n;
int dpTableCubeSum[MAX_N];
int cubeNumbers[MAX_CUBE];

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

void computeCubeNumbers () {
	int loop;
	for(loop=0; loop<MAX_CUBE; loop++)
		cubeNumbers[loop] = (loop + 1) * (loop + 1) * (loop + 1);
}

int main () {
	int loop, innerLoop, caseCount, scanResult;

    #ifdef debug_on
        printf("\n| C22.B - Cube Numbers |\n");
    #endif

    /* init */
	computeCubeNumbers();
	dpTableCubeSum[0] = 0;
	for(loop=1; loop<MAX_N; loop++) {
		dpTableCubeSum[loop] = SUPREME;
		for(innerLoop=MAX_CUBE-1; innerLoop>=0; innerLoop--) {
			if(cubeNumbers[innerLoop] > loop)
				continue;
			dpTableCubeSum[loop] = min(dpTableCubeSum[loop], 1 + dpTableCubeSum[loop - cubeNumbers[innerLoop]]);
		}
	}
	caseCount = 1;

    for ever {
        /* read case arguments */
    	scanResult = scanf("%d", &n);

        #ifdef debug_on
            printArgs();
            printf("\nProblem Solution:\n");
        #endif
        
        /* solution */
        if (scanResult == EOF)
        	break;
		printf("Case #%d: %d\n", caseCount++, dpTableCubeSum[n]);

    	#ifdef debug_on
        	printf("--------------------\n");
    	#endif
	}
    return 0;
}