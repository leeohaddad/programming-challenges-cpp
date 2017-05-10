/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 5                    Professor Marcel   **/
/**   Problema A - Richness of words                               Curso: BCC   **/
/**   https://www.codepit.io/#/problems/54ffc3e1d0095dde91c6bb51/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#define MAX_N 10000
#define debug_off 1

using namespace std;

int n, min_i, max_i;

#ifdef debug_on
/* print arguments */
void printArgs () {
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
}
#endif

int getMinimumPalindromesCount (int length) {
    if (length <= 0)
        return 0;
    if (length == 1)
        return 1;
    if (length == 2)
        return 2;
    return 3; 
}

int getMaximumPalindromesCount (int length) {
    if (length < 0)
        return 0;
    return length; 
}

void findPalindrome (int i, int n) {
    int loop;
    int loopsSum = 0;
    int currentLoopRange;
    char nextChar;
    string resultString = "";
    #ifdef debug_on
        printf("\nfindPalindrome: %d\n",i);
    #endif
    if (i < min_i || i > max_i) {
        cout << i << " : NO" << endl;
        return;
    }
    currentLoopRange = 26;
    while (currentLoopRange > 0) {
        if (26 < currentLoopRange)
            currentLoopRange = 26;
        if (i < currentLoopRange)
            currentLoopRange = i;
        loopsSum = loopsSum + currentLoopRange;
        nextChar = 'a';
        for (loop=0; loop<currentLoopRange; loop++) {
            resultString.append(1u,nextChar);
            nextChar++;
            #ifdef debug_on
                cout << resultString << endl << "|" << "nextChar" << "|" << endl;
            #endif
        }
        if (i > loopsSum) {
            currentLoopRange = n - loopsSum;
            if (i-26 < currentLoopRange)
                currentLoopRange = i-26;
            loopsSum = loopsSum + currentLoopRange;
            for (loop=0; loop<currentLoopRange; loop++)
                resultString.append(1u,'z');
        }
        currentLoopRange = n - loopsSum;
    }
    cout << i << " : " << resultString << endl;
}

int main () {
    int i;

    #ifdef debug_on
        printf("\n| C5.A - Richness of words |\n");
    #endif

    /* read program arguments */
    scanf("%d", &n);

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    min_i = getMinimumPalindromesCount(n);
    max_i = getMaximumPalindromesCount(n);
    for (i=0; i<n; i++)
        findPalindrome(i+1,n);

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}