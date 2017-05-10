/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 6                    Professor Marcel   **/
/**   Problema A - Comparing Two Long Integers                     Curso: BCC   **/
/**   https://www.codepit.io/#/problems/56967eec0ad43c62122e0f11/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#define MAX_DIGITS 1000005
#define debug_off 1

using namespace std;

int n;
char first[MAX_DIGITS];
char second[MAX_DIGITS];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int index = 0;
    printf("Arguments:\n");
    //printf(" first=%s\n",first);
    //printf(" second=%s\n",second);
    printf(" first=");
    while (first[index] != '\0')
        printf("%c",first[index++]);
    printf("\n");
    index = 0;
    printf(" second=");
    while (second[index] != '\0')
        printf("%c",second[index++]);
    printf("\n");
}
#endif

int main () {
    int loop, index, fStart, sStart, fLength, sLength, fFinished, sFinished;

    #ifdef debug_on
        printf("\n| C6.A - Comparing Two Long Integers |\n");
    #endif

    /* read program arguments */
    scanf("%s %s", first, second);
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    index = 0;
    fStart = -1;
    sStart = -1;
    fLength = 0;
    sLength = 0;
    fFinished = 0;
    sFinished = 0;
    while (fFinished + sFinished < 2) {
        if (fFinished == 0) {
            if (first[index] == '\0')
                fFinished = 1;
            else if (fStart == -1) {
                if (first[index] != '0') {
                    fStart = index;
                    fLength = 1;
                }
            }
            else {
                fLength++;
            }
        }
        if (sFinished == 0) {
            if (second[index] == '\0')
                sFinished = 1;
            else if (sStart == -1) {
                if (second[index] != '0') {
                    sStart = index;
                    sLength = 1;
                }
            }
            else {
                sLength++;
            }
        }
        index++;
    }
    #ifdef debug_on
        printf("fStart: %d; sStart: %d; fLength: %d; sLength: %d;\n",fStart,sStart,fLength,sLength);
    #endif
    if (fLength > sLength)
        printf(">\n");
    else if (fLength < sLength)
        printf("<\n");
    else {
        for (loop=0; loop<fLength; loop++) {
            #ifdef debug_on
                printf("  comparing %c and %c\n",first[fStart+loop],second[sStart+loop]);
            #endif
            if (first[fStart+loop] > second[sStart+loop]) {
                printf(">\n");
                return 0;
            }
            else if (first[fStart+loop] < second[sStart+loop]) {
                printf("<\n");
                return 0;
            }
        }
        printf("=\n");
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}