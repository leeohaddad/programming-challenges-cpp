/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema E - Divisibility by Eight                           Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce7b921926e63b4dafac/view?index=4   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#define debug_off 1

using namespace std;

int number[105];
int size;
set<int> positions[10];

void printBigNumber () {
    int loop;
    if (size == 0)
        printf("0");
    for (loop=0; loop<size; loop++)
        if (number[loop] != -1)
            printf("%d",number[loop]);
    printf(";\n");
}

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" Size=%d;\n Number=",size);
    printBigNumber();
}
#endif

int tryToFindDigit (int digit, int minIndex) {
    set<int>::iterator setIterator;
    #ifdef debug_on
        printf("  tryToFindDigit: %d [%d]\n",digit,minIndex);
    #endif
    for (setIterator = positions[digit].begin(); setIterator != positions[digit].end(); setIterator++) {
        if (minIndex <= *setIterator) {
            #ifdef debug_on
                printf("    FOUND: %d\n",digit);
            #endif
            minIndex = *setIterator + 1;
            return minIndex;
        }
    }
    return 0;
}

int tryToBuildNumber (int multiplier) {
    int minIndex = 0, currentDigit, tenPow, currentNumber;
    currentNumber = multiplier;
    #ifdef debug_on
        printf(" tryToBuildNumber: %d\n",multiplier);
    #endif
    minIndex = 0;
    while (currentNumber != -1) {
        currentDigit = currentNumber;
        tenPow = 0;
        while (currentDigit >= 10) {
            currentDigit = currentDigit/10;
            tenPow++;   
        }
        if (currentNumber < 10)
            currentNumber = -1;
        else
            currentNumber = currentNumber%(int)floor(pow(10,tenPow));
        while (currentNumber != -1 && currentNumber < pow(10,tenPow-1)) {
            tenPow--;
            minIndex = tryToFindDigit(0,minIndex);
            if (minIndex == 0)
                return 0;
        }
        minIndex = tryToFindDigit(currentDigit,minIndex);
        if (minIndex == 0)
            return 0;
    }
    printf("YES\n%d\n",multiplier);
    return 1;
}

int main () {
    int readStatus, numericArg, multiplier;
    char arg;

    #ifdef debug_on
        printf("\n| C2.E - Divisibility by Eight |\n");
    #endif

    /* read program arguments */
    size = 0;
    readStatus = scanf("%c", &arg);
    while (readStatus > 0) {
        numericArg = arg - 48;
        #ifdef debug_on
            printf("numericArg: %d\n",numericArg);
        #endif
        if (numericArg >= 10 || numericArg < 0) {
            break;
        }
        number[size] = numericArg;
        positions[numericArg].insert(size);
        size++;
        readStatus = scanf("%c", &arg);
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (positions[0].size() > 0) {
        printf("YES\n0\n");
    }
    else if (positions[8].size() > 0) {
        printf("YES\n8\n");
    }
    else {
        multiplier = 16;
        while (multiplier < 1000) {
            if (tryToBuildNumber(multiplier) == 1)
                return 0;
            multiplier = multiplier + 8;
        }
        printf("NO\n");
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}