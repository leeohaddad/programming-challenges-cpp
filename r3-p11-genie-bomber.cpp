/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 11 - Genie Bomber                Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <math.h>
#define MAX_CITIES 105
#define debug_off 1
#define error 0.00001

using namespace std;

long n, rG, rC, maxDistance;
long cities[MAX_CITIES][2];

typedef struct {
	double x,y;
} point;

#ifdef debug_on
/* print arguments */
void printArgs () {
	int loop;
	printf("Arguments:\n");
	printf(" n=%ld;\n",n);
	printf(" cities:\n");
	for (loop=0; loop<n; loop++)
		printf("  %ld %ld\n",cities[loop][0],cities[loop][1]);
	printf(" R=%ld;\n",rG);
	printf(" r=%ld;\n",rC);
}
#endif

double distanceBetweenPoints (double xA, double yA, double xB, double yB) {
	double dX, dY;
	dX = xB - xA;
	dY = yB - yA;
	return sqrt(dX*dX + dY*dY);
}

int calculateCitiesDestroyed (double centerX, double centerY) {
	int loop, result;
	result = 0;
	for (loop=0; loop<n; loop++) {
		if (distanceBetweenPoints(centerX,centerY,cities[loop][0],cities[loop][1]) <= maxDistance)
			result++;
	}
	return result;
}

int tryCircleWithPointsAAndBInBoarder(double xA, double yA, double xB, double yB, double radius)
{
	int result;
	double mirrorDistance;
	double distance = distanceBetweenPoints(xA,yA,xB,yB);
 	if (xA==xB && yA==yB)
 	{
 		return -1;	
 	}
	#ifdef debug_on
		printf(" tryCirclesWithPointsAAndBInBoarder A=(%.2f , %.2f) B=(%.2f , %.2f): R=%.2f\n",xA,yA,xB,yB,radius);
	#endif
	if(abs(distance - 2*radius) <= error)
	{
		result = calculateCitiesDestroyed((xA+xB)/2,(yA+yB)/2);
		#ifdef debug_on
			printf("  exactly one circle %.2f , %.2f: %d cities destroyed\n",(xA+xB)/2,(yA+yB)/2,result);
		#endif
	}
 
	else if(distance > 2*radius)
	{
		result = calculateCitiesDestroyed(xA,yA);
		#ifdef debug_on
			printf("  trying edge %.2f , %.2f: %d cities destroyed\n",xA,yA,result);
		#endif
	}   
	else
	{
		mirrorDistance = sqrt(pow(radius,2) - pow(distance/2,2));
		result = calculateCitiesDestroyed((xA+xB)/2 + mirrorDistance*(yA-yB)/distance,(yA+yB)/2 + mirrorDistance*(xB-xA)/distance);
		#ifdef debug_on
			printf("  trying border %.5f , %.5f: %d cities destroyed\n",(xA+xB)/2 + mirrorDistance*(yA-yB)/distance,(yA+yB)/2 + mirrorDistance*(xB-xA)/distance,result);
		#endif
	}
	return result;
}

int main () {
   int loop, inner_loop, result, citiesDestroyed;
   long arg;
   double midX, midY;

	#ifdef debug_on
		printf("\n| P11 - Genie Bomber |\n");
	#endif

    /* read program arguments */
	scanf("%ld", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%ld", &arg);
		cities[loop][0] = arg;
		scanf("%ld", &arg);
		cities[loop][1] = arg;
	}
	scanf("%ld %ld", &rG, &rC);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	maxDistance = rG - rC; /* to ensure that the cities can be destroyed completely by the genius */
	if (maxDistance < 0 ) {
		result = 0; /* genius cannot destroy any city because bomb radius is less than city radius */
	}
	else if (maxDistance == 0) {
		result = 1; /* genius can destroy only one city because bomb radius is equal city radius */
	}
	else {
		result = 0;
		/* throw bombs at cities centers (loop==inner_loop) and at middlePoints between cities (loop!=inner_loop) */
		for (loop=0; loop<n; loop++) {
			for (inner_loop=0; inner_loop<n; inner_loop++) {
				midX = 0.5f * (cities[loop][0] + cities[inner_loop][0]);
				midY = 0.5f * (cities[loop][1] + cities[inner_loop][1]);
				#ifdef debug_on
					printf("  trying mid %.2f , %.2f: ",midX ,midY);
				#endif
				citiesDestroyed = calculateCitiesDestroyed(midX,midY);
				if (citiesDestroyed > result)
					result = citiesDestroyed;
				#ifdef debug_on
					printf("  %d cities destroyed\n", citiesDestroyed);
				#endif
				citiesDestroyed = tryCircleWithPointsAAndBInBoarder(cities[loop][0],cities[loop][1],cities[inner_loop][0],cities[inner_loop][1],maxDistance-error);
				if (citiesDestroyed > result)
					result = citiesDestroyed;
			}
		}	
	}
	printf("%d\n",result);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1332. Genie Bomber
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1332

The last survivor was a certain Pitirim Schwartz, an erstwhile monk and inventor of the forked musket rest, who was selflessly laboring on the genie-bomber project. The essence of the project was to drop on the enemy cities bottles with genies who had been held imprisoned no less than three thousand years. It is well known that genies in their free state are capable only of destroying cities or constructing palaces. A thoroughly aged genie, reasoned Schwartz, was not about to start building palaces, and therefore things would go badly for the enemy. A definite obstacle to the realization of this concept was an insufficient supply of bottled genies, but Schwartz counted on overcoming this through the deep dragging of the Red and Mediterranean Seas.
The genie-bomber project has eventually entered the experimentation stage. Research fellows’ doubles have constructed N cities in the testing area. Each of these cities is a circle with a radius of r. As M. M. Kamnoedov provided only one bottled genie for the experiment, experimenters decided to demolish as many cities as possible for the sake of science. It is generally known that a genie demolishes everything in the range of R around the bottle’s touchdown point. Any city contained completely within this demolition area is ruined. Before the experiment is conducted, you are required to find the maximum possible number of cities that one genie can ruin.

Input:
The first line contains the number N of cities (1 ≤ N ≤ 100). The following N lines contain the coordinates xi, yi of city centers (xi, yi are integers, |xi|, |yi| ≤ 10000). City centers don’t coincide with each other.
The last line contains radius R of the genie’s area of destruction and the city radius r (1 ≤ R, r ≤ 10000). R and r are integers.

Output:
Output the maximum number of cities that can be destroyed by one bottled genie.

Samples:

Input:
3
0 0
0 4
4 0
3 1
Output:
2

Input:
5
0 0
0 1
0 2
0 3
0 4
1 1
Output:
1

*/
