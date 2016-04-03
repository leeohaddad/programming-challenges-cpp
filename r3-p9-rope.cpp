/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 9 - Rope                         Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#define MAX_SIZE 105
#define debug_off 1
#define PI 3.1415926535

using namespace std;

int n;
float radius;
float nails[100][2];

#ifdef debug_on
/* print arguments */
void printArgs () {
	int loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" radius=%.2f;\n",radius);
	printf(" nails:\n");
	for (loop=0; loop<n; loop++)
		printf("  x=%.2f; y=%.2f;\n",nails[loop][0],nails[loop][1]);
}
#endif

float distanceToNextNail (int nailIndex) {
	float xDist, yDist, distance;
	int nextNailIndex = nailIndex+1;
	if (nextNailIndex == n)
		nextNailIndex = 0;
	xDist = nails[nextNailIndex][0] - nails[nailIndex][0];
	yDist = nails[nextNailIndex][1] - nails[nailIndex][1];
	distance = sqrt( pow(xDist,2) + pow(yDist,2) );
	return distance;
}

int main () {
    int loop;
    float x, y, ropeSize;

	#ifdef debug_on
		printf("\n| P9 - Rope |\n");
	#endif

    /* read program arguments */
	scanf("%d %f", &n, &radius);
	for (loop=0; loop<n; loop++) {
		scanf("%f %f", &x, &y);
		nails[loop][0] = x;
		nails[loop][1] = y;
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	ropeSize = 2 * PI * radius;
	#ifdef debug_on
		printf("ropeSize: %.2f\n",ropeSize);
	#endif
	for (loop=0; loop<n; loop++) {
		ropeSize = ropeSize + distanceToNextNail(loop);
		#ifdef debug_on
			printf("ropeSize: %.2f (+ %.2f)\n",ropeSize,distanceToNextNail(loop));
		#endif
	}
	/* http://www.brasilescola.com/matematica/comprimento-um-arco.htm */
	printf("%.2f\n",ropeSize);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1020. Rope
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1020

Plotters have barbarously hammered N nails into an innocent plane shape, so that one can see now only heads. Moreover, pursuing their mean object, they have hammered all the nails into the vertices of a convex polygon. After that they…it is awful… have roped off the nails, so that the shape felt upset (the rope was very thin). They’ve done it as it is shown in the figure.
Your task is to find out a length of the rope.

Input:
There two numbers in the first line of the standard input: N — a number of nails (1 ≤ N ≤ 100), and a real number R — a radius of heads of nails. All the heads have the same radius. Further there are N lines, each of them contains a pair of real coordinates (separated by a space) of centers of nails. An absolute value of the coordinates doesn’t exceed 100. The nails are described either in a clockwise or in a counterclockwise order starting from an arbitrary nail. Heads of different nails don’t overlap.

Output:
Output a real number with two digits precision (after a decimal point) — a length of the rope.

Sample:

Input:
4 1
0.0 0.0
2.0 0.0
2.0 2.0
0.0 2.0
Output:
14.28

*/
