/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 1                    Professor Marcel   **/
/**   Problema C - Pangram                                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/561dce6f921926e63b4daf0b/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug_off 1

using namespace std;

int n;
vector<char> elements;
int latinAlphabet[26];

#ifdef debug_on
/* print arguments */
void printArgs () {
    unsigned int loop;
    printf("Arguments:\n");
    printf(" n=%d;\n",n);
    printf(" elements:\n");
    for (loop=0; loop<elements.size(); loop++)
        printf("  %c\n",elements[loop]);
}
#endif

int main () {
   int loop, letterCount;
   char arg;

    #ifdef debug_on
        printf("\n| C1.C - Pangram |\n");
    #endif

    /* init alphabet array */
    for (loop=0; loop<26; loop++)
        latinAlphabet[loop] = 0;
    letterCount = 0;

    /* read program arguments */
    scanf("%d", &n);
    scanf("%c", &arg);
    for (loop=0; loop<n; loop++) {
        scanf("%c", &arg);
        elements.push_back(arg);
        if (arg >= 97 && arg <= 122 && latinAlphabet[arg-97] == 0)
        {
            latinAlphabet[arg-97] = 1;
            letterCount++;
        }
        else if (arg >= 65 && arg <= 90 && latinAlphabet[arg-65] == 0)
        {
            latinAlphabet[arg-65] = 1;
            letterCount++;
        }
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    if (letterCount == 26)
        printf("YES\n");
    else
        printf("NO\n");

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}