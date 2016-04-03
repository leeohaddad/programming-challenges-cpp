/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 3    Professora Cris    **/
/**   Problema 17 - Median on the Plane         Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <cfloat>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#define debug_off 1
#define infinite DBL_MAX

using namespace std;

int n;
vector< pair<long,long> > points;
set< double > angleFactors;
map< double , int > indexByAngleFactor;

#ifdef debug_on
/* print arguments */
void printArgs () {
	unsigned int loop;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" points:\n");
	for (loop=0; loop<points.size(); loop++)
		printf("  %ld %ld\n",points[loop].first,points[loop].second);
}
#endif

int chooseLeftLowerElement ()
{
	int index = 0;
	unsigned int loop;
	for (loop=0; loop<points.size(); loop++)
	{

		if ((points[loop].first < points[index].first) || (points[loop].first == points[index].first && points[loop].second < points[index].second))
		{
			index = loop;
		}	
	}
	#ifdef debug_on
		printf("  chooseLeftLowerElement() - Result: (%ld %ld) index %d.\n",points[index].first,points[index].second,index+1);
	#endif
	return index;
}

double calculateAngleFactor (int indexA, int indexB)
{
	long xDif = points[indexB].first - points[indexA].first;
	long yDif = points[indexB].second - points[indexA].second;
	if (xDif == 0)
	{
		if (yDif > 0)
			return infinite;
		return -infinite;
	}
	return ((double) yDif / xDif);
}

int main () {
   int loop, mainElementIndex, secondElementIndex;
	unsigned int unsigned_loop;
   long argX, argY;
   double angleFactor;
   set< double >::iterator setIterator;

	#ifdef debug_on
		printf("\n| P17 - Median on the Plane |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%ld %ld", &argX, &argY);
		points.push_back(make_pair(argX,argY));
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	mainElementIndex = chooseLeftLowerElement();
	loop=0;
	for (unsigned_loop=0; unsigned_loop<points.size(); unsigned_loop++)
	{
		if (loop != mainElementIndex)
		{
			angleFactor = calculateAngleFactor(mainElementIndex,loop);
			indexByAngleFactor[angleFactor] = loop;
			angleFactors.insert(angleFactor);
		}
		loop++;
	}
	loop = 0;
	for (setIterator=angleFactors.begin(); setIterator!=angleFactors.end(); setIterator++)
	{
		if (loop == (-1+n/2))
		{
			secondElementIndex = indexByAngleFactor[*setIterator];
			printf("%d %d\n", mainElementIndex+1, secondElementIndex+1);
			#ifdef debug_on
				printf("  right: %.2f for index %d.\n",*setIterator,indexByAngleFactor[*setIterator]+1);
			#endif
		}
		#ifdef debug_on
		else
		{
			printf("  wrong: %.2f for index %d.\n",*setIterator,indexByAngleFactor[*setIterator]+1);
		}
		#endif
		loop++;
	}
	
	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1207. Median on the Plane
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1207

The are N points on the plane (N is even). No three points belong to the same strait line. Your task is to select two points in such a way, that strait line they belong to divides the set of points into two equal-sized parts.

Input:
First line contains one integer N (2 ≤ N ≤ 10000). Each of next N lines contains pair of integers xi, yi (−109 ≤ xi, yi ≤ 109), the coordinates of i-th point.

Output:
Print the numbers of selected points.

Sample:

Input:
4
0 0
1 0
0 1
1 1
Output:
1 4

*/
