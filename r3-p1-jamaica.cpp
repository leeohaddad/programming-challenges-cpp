/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 1 - Jamaica                      Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#define VERTICAL 10005
#define PRECISION 1000000000
#define MAX_SIZE 305
#define debug_off 1

using namespace std;

int n, d;
double cities[MAX_SIZE][2];
map< pair<double,double> , pair< pair<double,double> , pair<double,double> > > roads;
map< pair<double,double> , pair< pair<double,double> , pair<double,double> > >::iterator mapIterator;
#ifdef debug_on
/* print arguments */
void printArgs () {
	int loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" cities:\n");
	for (loop=0; loop<n; loop++)
		printf("  %.0f %.0f\n",cities[loop][0],cities[loop][1]);
}
#endif

bool roadExists (pair< pair<double,double> , pair<double,double> > road) {
	#ifdef debug_on
		printf("roadExists: (%.2f %.2f) => (%.2f %.2f)\n", road.first.first, road.first.second, road.second.first, road.second.second);
	#endif
	if (road.first.first == 0 && road.first.second == 0 && road.second.first == 0 && road.second.second == 0)
		return false;
	return true;
}

void addToRoad (double a, double b, double xA, double yA, double xB, double yB) {
	double xBuffer, yBuffer;
	pair<double,double> keyPair, aPair, bPair;
	keyPair = make_pair(a,b);

	if ( (xA > xB) || (xA==xB && yA>yB) ) {
		xBuffer = xA;
		yBuffer = yA;
		xA = xB;
		yA = yB;
		xB = xBuffer;
		yB = yBuffer;
	}

	#ifdef debug_on
		printf("\naddToRoad: %.2f, %.2f, (%.2f, %.2f), (%.2f, %.2f);\n",a,b,xA,yA,xB,yB);
	#endif

	if (!roadExists(roads[keyPair])) {
		aPair = make_pair(xA,yA);
		bPair = make_pair(xB,yB);
		roads[keyPair] = make_pair( aPair , bPair );
		#ifdef debug_on
			printf("  Added (%.0f %.0f)=>(%.0f %.0f)\n",xA,yA,xB,yB);
		#endif
		return;
	}
	
	if (a == 0 && b >= VERTICAL) {
		// vertical road, X values are equal: will comparare by Y!
		if (yA < roads[keyPair].first.second) {
			// extend down
			roads[keyPair].first.first = xA;
			roads[keyPair].first.second = yA;
			#ifdef debug_on
				printf("  Extended down (%.0f %.0f)=>(%.0f %.0f)\n",roads[keyPair].first.first,roads[keyPair].first.second,roads[keyPair].second.first,roads[keyPair].second.second);
			#endif
		}
		if (yB > roads[keyPair].second.second) {
			// extend up
			roads[keyPair].second.first = xB;
			roads[keyPair].second.second = yB;
			#ifdef debug_on
				printf("  Extended up (%.0f %.0f)=>(%.0f %.0f)\n",roads[keyPair].first.first,roads[keyPair].first.second,roads[keyPair].second.first,roads[keyPair].second.second);
			#endif
		}
	}
	else {
		// compare by X
		if (xA < roads[keyPair].first.first) {
			// extend to the left
			roads[keyPair].first.first = xA;
			roads[keyPair].first.second = yA;
			#ifdef debug_on
				printf("  Extended left (%.0f %.0f)=>(%.0f %.0f)\n",roads[keyPair].first.first,roads[keyPair].first.second,roads[keyPair].second.first,roads[keyPair].second.second);
			#endif
		}
		if (xB > roads[keyPair].second.first) {
			// extend to the right
			roads[keyPair].second.first = xB;
			roads[keyPair].second.second = yB;
			#ifdef debug_on
				printf("  Extended right (%.0f %.0f)=>(%.0f %.0f)\n",roads[keyPair].first.first,roads[keyPair].first.second,roads[keyPair].second.first,roads[keyPair].second.second);
			#endif
		}
	}
}

int main () {
    int loop, inner_loop;
    double a, b, xA, yA, xB, yB, xDist, yDist, totalDistance;
    pair<double,double> keyPair;

   #ifdef debug_on
		printf("\n| P1 - Jamaica |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%lf %lf", &cities[loop][0], &cities[loop][1]);
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	totalDistance = d = 0;
	for (loop=0; loop<n; loop++) {
		for (inner_loop=loop+1; inner_loop<n; inner_loop++) {
			xA = cities[loop][0];
			xB = cities[inner_loop][0];
			yA = cities[loop][1];
			yB = cities[inner_loop][1];
			xDist = xB - xA;
			yDist = yB - yA;
			if (xDist == 0) {
				a = 0;
				b = VERTICAL + xA; // (xA == xB)
			}
			else {
				a = yDist / xDist;
				b = yA - a * xA;
			}
			a = floor((a*PRECISION) + 0.5) / PRECISION;
			b = floor((b*PRECISION) + 0.5) / PRECISION;
			addToRoad(a, b, xA, yA, xB, yB);
		}
	}
	for (mapIterator=roads.begin(); mapIterator!=roads.end(); mapIterator++) {
		xDist = mapIterator->second.second.first - mapIterator->second.first.first;
		yDist = mapIterator->second.second.second - mapIterator->second.first.second;
		totalDistance = totalDistance + sqrt(xDist*xDist + yDist*yDist);
		#ifdef debug_on
			printf("\n[%.15f, %.15f]     (%.0f, %.0f) -> (%.0f, %.0f) = %.5f (%.2f, %.2f)\n", mapIterator->first.first, mapIterator->first.second, mapIterator->second.first.first, mapIterator->second.first.second, mapIterator->second.second.first, mapIterator->second.second.second, sqrt(xDist*xDist + yDist*yDist), xDist, yDist);
		#endif
	}
	printf("%.0f\n",floor(totalDistance + 0.5f));
	
	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1588. Jamaica
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1588

Programmer Andrey is very lucky. The Governor-General of Jamaica invited him to visit this wonderful island. The whole trip, including plenty of entertainment, will be completely free for Andrey. He will only have to help the Jamaican Ministry of Transport and write a small program.
The point is that the Jamaican government decided to construct a new network of expressways, in order to boost the economic growth of the country. Each two cities are to be connected by a road going along a straight line. One road may connect several cities if they lie on the same straight line. Jamaican economists are sure that the new network will minimize transportation expenses. In order to estimate the cost of the project, it is required to determine the total length of the roads to be constructed, and this is the job for Andrey.

Input:
The first line contains the number n of cities in Jamaica (1 ≤ n ≤ 300). The next n lines contain the coordinates of the cities. In each of these lines, there are two integers xi and yi separated by a space (0 ≤ xi, yi ≤ 10000). There are no cities with coinciding coordinates.

Output:
Output the total length of the roads rounded to the nearest integer.

Sample:

Input:
4
0 0
0 100
100 0
50 50
Output:
412

*/
