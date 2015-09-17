/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação              Professora Cris    **/
/**   Problema 14 - Lucky Tickets. Easy!        Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX_SUM_PLUS_ONE 37
/* #define debug_on 1 */

/* math power function applied to integers */
int int_pow(int number, int factor) {
	if (factor == 0)
		return 1;
	else
		return int_pow(number, factor-1) * number;
}

/* return the sum of the digits from a number */
int sumDigits (int number) {
	int result = 0;
	while (number > 0) {
		result = result + number%10;
		number = number/10;
	}
	return result;
}

/* check all possible numbers with the determined size for the given digits sum and return the count */
int getPossibleDigitsCombinationCountForSumWithSize (int sum, int size) {
	int result, loop;
	if (size == 1) {
		if (sum>9 || sum<0)
			return 0;
		else
			return 1;
	}
	else {
		result = 0;
		for (loop=0; loop<=9; loop++) {
			result = result + getPossibleDigitsCombinationCountForSumWithSize(sum - loop, size-1);	
		}
	}
	return result;
}

/* solve the problem */
int main (int argc, char *argv[]) {
	int numberOfDigits, halfNumberOfDigits, loop, prefix, sum, loopRoof, result;
	int possibleDigitsCombinationCount[MAX_SUM_PLUS_ONE];
	#ifdef debug_on
		printf("\nP14 - Lucky Tickets. Easy!:\n");
	#endif

	/* readArg */
	scanf("%d", &numberOfDigits);

	#ifdef debug_on
		printf("Argument:\n n=%d\n",numberOfDigits);
		printf("\nProblem Solution:\n");
	#endif

	/* Solution */
	result = 0;
	halfNumberOfDigits = numberOfDigits/2;
	loopRoof = int_pow(10, halfNumberOfDigits);
	for (loop=0; loop<MAX_SUM_PLUS_ONE; loop++)
		possibleDigitsCombinationCount[loop] = 0;
	for (prefix=0; prefix<loopRoof; prefix++) {
		sum = sumDigits(prefix);
		if (possibleDigitsCombinationCount[sum] == 0) {
			possibleDigitsCombinationCount[sum] = getPossibleDigitsCombinationCountForSumWithSize(sum, halfNumberOfDigits);
			#ifdef debug_on
				printf("%d -> Calculating value for sum %d...result is %d\n", prefix, sum, possibleDigitsCombinationCount[sum]);
			#endif
		}
		#ifdef debug_on
		else {
			printf("%d -> Value for sum %d has been already calculated: %d\n", prefix, sum, possibleDigitsCombinationCount[sum]);
		}		
		#endif
		result = result + possibleDigitsCombinationCount[sum];
	}
	printf("%d\n",result);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1044. Lucky Tickets. Easy!
Time limit: 2.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1044

Background:
The public transport administration of Ekaterinburg is anxious about the fact that passengers don’t like to pay for passage doing their best to avoid the fee. All the measures that had been taken (hard currency premiums for all of the chiefs, increase in conductors’ salaries, reduction of number of buses) were in vain. An advisor especially invited from the Ural State University says that personally he doesn’t buy tickets because he rarely comes across the lucky ones (a ticket is lucky if the sum of the first three digits in its number equals to the sum of the last three ones). So, the way out is found — of course, tickets must be numbered in sequence, but the number of digits on a ticket may be changed. Say, if there were only two digits, there would have been ten lucky tickets (with numbers 00, 11, …, 99). Maybe under the circumstances the ratio of the lucky tickets to the common ones is greater? And what if we take four digits? A huge work has brought the long-awaited result: in this case there will be 670 lucky tickets. But what to do if there are six or more digits?

Problem:
So you are to save public transport of our city. Write a program that determines a number of lucky tickets for the given number of digits. By the way, there can’t be more than nine digits on one ticket.

Input:
Contains a positive even integer not greater than 9.

Output:
Should contain a number of tickets such that the sum of the first half of digits is equal to the sum of the second half of digits.

Sample:

Input:
4
Output:
670

*/
