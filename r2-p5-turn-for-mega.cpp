/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 5 - Turn for MEGA                Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define debug_off 1

using namespace std;

int k, n;
vector<int> carsByMinute;

#ifdef debug_on
/* print arguments */
void printArgs () {
	unsigned int loop;
	printf("Arguments:\n");
	printf(" k=%d;\n",k);
	printf(" n=%d;\n",n);
	printf(" carsByMinute:\n");
	for (loop=0; loop<carsByMinute.size(); loop++)
		printf("  %d\n",carsByMinute[loop]);
}
#endif

int int_max (int a, int b) {
    if (a>b)
        return a;
    return b;
}

int main () {
    int loop;
    int arg, cars;

	#ifdef debug_on
		printf("\n| P5 - Turn for MEGA |\n");
	#endif

    /* read program arguments */
	scanf("%d", &k);
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%d", &arg);
		carsByMinute.push_back(arg);
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	cars = 0;
	for (loop=0; loop<n; loop++) {
        cars += carsByMinute[loop];
        cars = int_max(0,cars-k);
	}
	printf("%d\n",cars);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1787. Turn for MEGA
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1787

A traffic light at the turn for the “MEGA” shopping center from the Novomoskovskiy highway works in such a way that k cars are able to take a turn in one minute. At weekends all the residents of the city drive to the mall to take a shopping, which results in a huge traffic jam at the turn. Administration of the mall ordered to install a camera at the nearby bridge, which is able to calculate the number of cars approaching this turn from the city. The observation started n minutes ago. You should use the data from the camera to determine the number of cars currently standing in the traffic jam.

Input:
The first line contains integers k and n (1 ≤ k, n ≤ 100), which are the number of cars that can take a turn to “MEGA” in one minute and the number of minutes passed from the beginning of observation. The second line contains space-separated integers a1, …, an (0 ≤ ai ≤ 100), where ai is the number of cars that approached the turn during the i-th minute. The observation started at morning, when there were no cars at the turn.

Output:
Output the number of cars currently standing in the traffic jam.

Samples:

Input:
5 3
6 7 2
Output:
0

Input:
5 3
20 0 0
Outuput:
5

*/
