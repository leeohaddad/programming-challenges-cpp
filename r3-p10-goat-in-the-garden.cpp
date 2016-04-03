/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 10 - Goat In The Garden          Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define debug_off 1
#define PI 3.1415926535
#define Circle_Is_Fully_Inside_Square radius<=0.5f*size
#define Square_Is_Fully_Inside_Circle radius>=(0.5f*size*sqrt(2.0f))

using namespace std;

float size, radius, halfAngleCos, angle, segmentSize;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" size=%.3f;\n",size);
	printf(" radius=%.3f;\n",radius);
}
#endif

int main () {

	#ifdef debug_on
		printf("\n| P10 - Goat In The Garden |\n");
	#endif

    /* read program arguments */
	scanf("%f %f", &size, &radius);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	if (Circle_Is_Fully_Inside_Square)
        printf("%0.3f", (PI * radius * radius));
    else if (Square_Is_Fully_Inside_Circle)
        printf("%0.3f", (size * size));
    else {
		halfAngleCos = 0.5f * size / radius; 
		angle = 2.0f * acos(halfAngleCos);
		segmentSize = 0.5f * radius * radius * (angle - sin(angle));
		#ifdef debug_on
        	printf("Angle: %.3f; CircleArea: %.3f; SegmentArea: %.3f;\n", angle, PI*radius*radius, 4*segmentSize);
        #endif
        printf("%0.3f", PI * radius * radius - 4 * abs(segmentSize));
    }

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1084. Goat in the Garden
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1084

Someone has let a goat in a square kitchen-garden and had bound it to a stake. The stake is driven into the ground in the very midst of the square. The goat is hungry as a hunter and very voracious, and eats everything that can be reached without leaving the square and tearing off the rope. What area of the kitchen-garden will be ate round?

Input:
contains lengths of the garden sides and a cord length in meters (positive integers not exceeding 100, located in one line and separated with a space).

Output:
should contain an area of the kitchen-garden (in square meters to within 3 symbols after a decimal point), ate round by the goat.

Sample:

Input:
10 6
Output:
95.091

*/
