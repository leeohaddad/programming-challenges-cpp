/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 3 - Knight                       Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_SIZE 8
#define debug_off 1

using namespace std;

int n;
unsigned int n2;
int board[MAX_SIZE][MAX_SIZE];
vector< pair<char,int> > movesMade;

#ifdef debug_on
/* print arguments */
void printArgs () {
	printf("Arguments:\n");
	printf(" board size = %dx%d;\n",n,n);
}
#endif

bool tryToVisit(int i, int j) {
    unsigned int loop;
    if (i<0 || i>=n)
        return false;
    if (j<0 || j>=n)
        return false;
    if (board[i][j] == 1)
        return false;
    board[i][j] = 1;
    movesMade.push_back(make_pair(i+'a',j+1));
    if (movesMade.size() == n2) {
        for (loop=0; loop<movesMade.size(); loop++) {
            printf("%c%d\n",movesMade[loop].first,movesMade[loop].second);
        }
        return true;
    }
    if (tryToVisit(i+1,j+2))
        return true;
    if (tryToVisit(i+2,j-1))
        return true;
    if (tryToVisit(i-1,j-2))
        return true;
    if (tryToVisit(i-2,j-1))
        return true;
    if (tryToVisit(i-2,j+1))
        return true;
    if (tryToVisit(i+1,j-2))
        return true;
    if (tryToVisit(i-1,j+2))
        return true;
    if (tryToVisit(i+2,j+1))
        return true;
    board[i][j] = 0;
    movesMade.pop_back();
    return false;
}

int main () {

	#ifdef debug_on
		printf("\n| P3 - Knight |\n");
	#endif

    /* read program arguments */
	scanf("%d", &n);

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	n2 = n*n;
	if (!tryToVisit(0,0))
        printf("IMPOSSIBLE\n");

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1298. Knight
Time limit: 2.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1298

Even paratroopers have vacations. The flight to Sirius in the depths of “The Admiral Brisco” Leo Hao whiled away with chessboard. No, he did not like usual chess game, and in addition, he did not have likely rival. The whole day Leo amused himself with an interesting thing: he tried to travel over all cells of the chessboard with the knight so that the knight visited each cell only one time. Leo attempted one time, then second, but always something was wrong. Leo became a little angry. Then he attempted board 4*4 instead of 8*8. Again failure after failure. A little angry, with the chessboard under his arm, Leo went to look for a local programmer. They two together indeed will solve this problem.

Input:
There is only one number N (1 ≤ N ≤ 8) in the input.

Output:
If it is possible to travel with the knight over the square field N×N cells, then output should contain N2 lines with tour over the chessboard with mentioned property, otherwise the only word “IMPOSSIBLE”.

Samples:

Input:
3
Output:
IMPOSSIBLE

Input:
5
Output:
a1
c2
e1
d3
e5
c4
d2
e4
c5
a4
b2
d1
e3
d5
b4
a2
c1
e2
c3
b1
a3
b5
d4
b3
a5

*/
