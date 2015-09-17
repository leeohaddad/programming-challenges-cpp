/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 11 - Ecological Premium          Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
/* #define debug_on 1 */

int main (int argc, char *argv[]) {
	int n, f, loop, inner_loop;
	long farmSize, animalsCount, environmentFriendliness, partialResult;
	#ifdef debug_on
		printf("\nP11 - Ecological Premium:\n");
	#endif

	scanf("%d",&n);
	for (loop=0; loop<n; loop++) {
		partialResult = 0;
		scanf("%d",&f);
		for (inner_loop=0; inner_loop<f; inner_loop++) {
			scanf("%ld %ld %ld", &farmSize, &animalsCount, &environmentFriendliness);
			partialResult += farmSize*environmentFriendliness;
		}
		printf("%ld\n",partialResult);
	}

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

10300 - Ecological Premium
Time limit: 3.000 seconds
url: https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1241

German farmers are given a premium depending on the conditions at their farmyard.  Imagine the
following simplified regulation: you know the size of each farmer's farmyard in square meters and the
number of animals living at it. We won't make a difference between different animals, although this is
far from reality. Moreover you have information about the degree the farmer uses environment-friendly
equipment and practices, expressed in a single integer greater than zero.  The amount of money a
farmer receives can be calculated from these parameters as follows. First you need the space a single
animal occupies at an average. This value (in square meters) is then multiplied by the parameter that
stands for the farmer's environment-friendliness, resulting in the premium a farmer is paid per animal
he owns. To compute the final premium of a farmer just multiply this premium per animal with the
number of animals the farmer owns.

Input:
The first line of input contains a single positive integer n (<20), the number of test cases. Each test
case starts with a line containing a single integer f (0<f<20), the number of farmers in the test
case. This line is followed by one line per farmer containing three positive integers each: the size of
the farmyard in square meters, the number of animals he owns and the integer value that expresses the
farmers environment-friendliness. Input is terminated by end of file. No integer in the input is greater
than 100000 or less than 0.

Output:
For each test case output one line containing a single integer that holds the summed burden for Ger-
many's budget, which will always be a whole number. Do not output any blank lines.

SampleInput:
3
5
1 1 1
2 2 2
3 3 3
2 3 4
8 9 2
3
9 1 8
6 12 1
8 1 1
3
10 30 40
9 8 5
100 1000 70

SampleOutput:
38
86
7445

*/