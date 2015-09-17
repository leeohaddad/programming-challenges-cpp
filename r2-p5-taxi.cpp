/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 5 - Taxi                         Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define debug_off 1

using namespace std;

int petr,petrRaise, driver, driverReduction;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" petr=%d;\n",petr);
	printf(" petrRaise=%d;\n",petrRaise);
	printf(" driver=%d;\n",driver);
	printf(" driverReduction=%d;\n",driverReduction);
}
#endif

int main () {

	#ifdef debug_on
		printf("\n| P5 - Taxi |\n");
	#endif

    /* read program arguments */
	scanf("%d %d %d %d", &petr, &petrRaise, &driver, &driverReduction);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	driver = driver + driverReduction;
	while (petr < driver - driverReduction) {
        driver = driver - driverReduction;
        #ifdef debug_on
            printf("driver lowers to %d\n",driver);
        #endif
        if (petr + petrRaise >= driver) {
            printf("%d\n",driver);
            return 0;
        }
        petr = petr + petrRaise;
        #ifdef debug_on
            printf("petr raises to %d\n",petr);
        #endif
	}
    printf("%d\n",petr);

	return 0;
}

/*

1607. Taxi
Time limit: 0.5 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1607

Petr likes going by taxi. For him, it is not only the pleasure of a fast and comfortable ride, but also the opportunity to bargain with the driver over the fare. The bargaining between Petr and taxi drivers always follows the same scheme:
— To the airport! I pay 150 roubles.
— No, I won't take you for 150. Let's go for 1000.
— Are you crazy? I haven't got that much on me! Ok, let it be 200.
— Are you laughing? I agree to 900.
— Well, I'll give 250.
— Guy, do you know how much gas is? Pay 800 and off we go!
…
Such a dialog continues until they agree on the fare. Petr always increases his amount by the same number, and the taxi driver decreases it in the same way. The driver would not ask a sum that is less than that offered by Petr. In this case, he will agree with Petr's offer. Petr will act similarly.

Input:
The single input line contains four integer numbers: the initial Petr's offer a, Petr's raise to his offer b, the initial fare required by the driver c, and the driver's reduction of his fare d; 1 ≤ a, b, c, d ≤ 10000.

Output:
Output the amount of money that Petr will pay for the ride.

Sample:

Input:
150 50 1000 100
Output:
450

*/
