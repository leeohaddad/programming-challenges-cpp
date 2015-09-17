/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 2 - Game                         Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define BOARD_SIZE 4
#define MAX_MOVES BOARD_SIZE*BOARD_SIZE+1
#define MOVE_RANGE 3
#define debug_off 1

using namespace std;

vector< pair<int,int> > coinsToFlip;
int numberOfMoves;

#ifdef debug_on
/* print game board */
void printBoard (int gameBoard[BOARD_SIZE][BOARD_SIZE]) {
	unsigned int loop, inner_loop;
	for (loop=0; loop<BOARD_SIZE; loop++) {
        printf("  ");
        for (inner_loop=0; inner_loop<BOARD_SIZE; inner_loop++) {
            if (gameBoard[loop][inner_loop] == 1) {
                printf("B");
            }
            else {
                printf("W");
            }
        }
        printf("\n");
    }
}

/* print arguments */
void printArgs (int gameBoard[BOARD_SIZE][BOARD_SIZE], int moveDescription[MOVE_RANGE][MOVE_RANGE]) {
	unsigned int loop, inner_loop;
	printf("Arguments:\n");
	printf(" board:\n");
	printBoard(gameBoard);
	printf(" move description:\n");
	for (loop=0; loop<MOVE_RANGE; loop++) {
        printf("  ");
        for (inner_loop=0; inner_loop<MOVE_RANGE; inner_loop++)
            printf("%d",moveDescription[loop][inner_loop]);
        printf("\n");
	}
}
#endif

void undoMove(int i, int j, int gameBoard[BOARD_SIZE][BOARD_SIZE]) {
    unsigned int loop;
    int finalI, finalJ;
    for (loop=0; loop<coinsToFlip.size(); loop++) {
        finalI = i + coinsToFlip[loop].first;
        finalJ = j + coinsToFlip[loop].second;
        if (finalI >= 0 && finalI < BOARD_SIZE && finalJ >= 0 && finalJ < BOARD_SIZE) {
            gameBoard[finalI][finalJ] = 1 - gameBoard[finalI][finalJ];
        }
    }
}

void makeMove (int i, int j, int gameBoard[BOARD_SIZE][BOARD_SIZE], int *movesCount, int *wCount, int *bCount) {
    unsigned int loop;
    int finalI, finalJ;
    *movesCount = *movesCount + 1;
    #ifdef debug_on
        printf("makeMove(i=%d, j=%d, m=%d) =",i,j,*movesCount);
    #endif
    for (loop=0; loop<coinsToFlip.size(); loop++) {
        finalI = i + coinsToFlip[loop].first;
        finalJ = j + coinsToFlip[loop].second;
        if (finalI >= 0 && finalI < BOARD_SIZE && finalJ >= 0 && finalJ < BOARD_SIZE) {
            #ifdef debug_on
                printf(" [%d %d]",finalI,finalJ);
            #endif
            gameBoard[finalI][finalJ] = 1 - gameBoard[finalI][finalJ];
            if (gameBoard[finalI][finalJ] == 1) {
                *wCount = *wCount - 1;
                *bCount = *bCount + 1;
            }
            else {
                *wCount = *wCount + 1;
                *bCount = *bCount - 1;
            }
        }
    }
    if (*wCount == 0 || *bCount == 0) {
        if (*movesCount < numberOfMoves)
            numberOfMoves = *movesCount;
    }
    #ifdef debug_on
        printf("\n");
        printBoard(gameBoard);
    #endif
}

void minimalPathToVictory (int i, int j, int gameBoard[BOARD_SIZE][BOARD_SIZE], int movesCount, int wCount, int bCount) {
    int nextI, nextJ;
    #ifdef debug_on
        printf("minimalPathToVictory(i=%d, j=%d, m=%d, w=%d, b=%d)\n",i,j,movesCount,wCount,bCount);
    #endif
    nextI = i;
    nextJ = j;
    nextJ++;
    if (nextJ >= BOARD_SIZE) {
        nextI++;
        nextJ = 0;
        if (nextI >= BOARD_SIZE) {
            makeMove(i,j,gameBoard,&movesCount,&wCount,&bCount);
            undoMove(i,j,gameBoard);
            return;
        }
    }
    minimalPathToVictory(nextI,nextJ,gameBoard,movesCount,wCount,bCount);
    makeMove(i,j,gameBoard,&movesCount,&wCount,&bCount);
    minimalPathToVictory(nextI,nextJ,gameBoard,movesCount,wCount,bCount);
    undoMove(i,j,gameBoard);
}

int main () {
    char readChar;
    int loop, inner_loop, wCount, bCount;
    int gameBoard[BOARD_SIZE][BOARD_SIZE];
    int moveDescription[MOVE_RANGE][MOVE_RANGE];

	#ifdef debug_on
		printf("\n| P2 - Game |\n");
	#endif

    /* read program arguments */
    wCount = 0;
    bCount = 0;
	for (loop=0; loop<BOARD_SIZE; loop++) {
        for (inner_loop=0; inner_loop<BOARD_SIZE; inner_loop++) {
            scanf("%c", &readChar);
            if (readChar == 'W') {
                gameBoard[loop][inner_loop] = 0;
                wCount++;
            }
            else /* (readChar == 'B') */ {
                gameBoard[loop][inner_loop] = 1;
                bCount++;
            }
        }
        scanf("%c", &readChar);
	}
	for (loop=0; loop<MOVE_RANGE; loop++) {
        for (inner_loop=0; inner_loop<MOVE_RANGE; inner_loop++) {
            scanf("%c", &readChar);
            moveDescription[loop][inner_loop] = readChar -'0';
            if (moveDescription[loop][inner_loop] == 1) {
                coinsToFlip.push_back(make_pair(loop-1,inner_loop-1));
            }
        }
        scanf("%c", &readChar);
	}

	#ifdef debug_on
		printArgs(gameBoard,moveDescription);
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
    if (wCount == 0 || bCount == 0) {
        #ifdef debug_on
            printf("Initial board is already solved!\n");
        #endif
        printf("0\n");
        return 0;
    }
	numberOfMoves = MAX_MOVES;
	minimalPathToVictory(0,0,gameBoard,0,wCount,bCount);
	if (numberOfMoves > BOARD_SIZE*BOARD_SIZE) {
        printf("Impossible\n");
	}
	else {
        printf("%d\n",numberOfMoves);
    }

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1122. Game
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1122

At SKB Kontur we have to work much. So there is no sin in taking a rest and playing from time to time. Consider for example the following famous one-player game.
We have a 4×4 field. There are chips with one side painted white and another side painted black on the field. Some of the chips are with their white side up and the others are with their white side down at the moment. Each move consists in turning over a chip together with all the chips that are adjacent to it vertically and horizontally (i.e. 5 chips altogether). The aim is to come to the position in which all the chips are with the same side up.
Naturally, one is easily bored with this game because interesting and unexpected positions become fewer as time goes on. That is why a modified version of the game is now more popular at SKB Kontur. In this version a move consists in turning over a fixed combination of chips within a 3×3 square. For example, a move may consist in turning over all the diagonal neighbors of a chosen chip.
The combination of chips is chosen arbitrarily; it may be assigned in the form of a 3×3 field in which the central cell corresponds to the cell at which a move as made. For example, in picture at the left the upper combination corresponds to a standard game and the lower combination is for the game described in the previous paragraph. Note that a combination can be asymmetrical. Each move is made at one of the cells of the playing field (i.e. the central cell of the 3×3 move-defining square is selected among the field's cells). Prescriptions to turn over chips at cells which are outside the 4×4 field are ignored.
In this game it would be nice to know if it is possible to reach a position in which all the chips are with the same side up and if it's possible to do this then in how many moves. You are to write a program which answers these questions.

Input:
The first four lines describe the initial arrangement of chips. A symbol "W" stands for a chip which lies with its white side up and a symbol "B" stands for a chip which lies with its black side up. The next three lines describe a move: the chips that are to be turned over are shown by "1" and others are shown by "0".

Output:
If it is impossible to reach the aim of the game you should output the word "Impossible", otherwise you should output the minimal number of moves necessary to come to the final position.

Sample:

Input:
WWWW
WBBW
WBWW
WWWW
101
010
101
Output:
Impossible

*/
