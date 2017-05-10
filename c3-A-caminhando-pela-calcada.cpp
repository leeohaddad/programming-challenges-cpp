/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 3                    Professor Marcel   **/
/**   Problema A - Caminhando pela calçada                         Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2bdf6fa9de49e5c604b/view?index=0   **/
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

long long T;
vector< vector<long long> > testCases;

#ifdef debug_on
/* print arguments */
void printArgs () {
    long long A, B, C, D;
    vector<long long> bufferVector;
    vector<long long>::iterator vectorIterator;
    vector< vector<long long> >::iterator vectorVectorIterator;
    printf("Arguments:\n");
    printf(" T=%lld;\n",T);
    for (vectorVectorIterator=testCases.begin(); vectorVectorIterator!=testCases.end(); vectorVectorIterator++) {
        bufferVector = *vectorVectorIterator;
        vectorIterator = bufferVector.begin();
        A = *vectorIterator;
        vectorIterator++;
        B = *vectorIterator;
        vectorIterator++;
        C = *vectorIterator;
        vectorIterator++;
        D = *vectorIterator;
        printf("  (%lld,%lld) => (%lld,%lld)\n",A,B,C,D);
    }
}
#endif

long long greatestCommonDivisor (long long first, long long second) {
    first = abs(first);
    second = abs(second);
    if (second == 0)
        return first;
    return greatestCommonDivisor(second, first % second);
}

long long gcdR(long long x, long long y) {
   if(x < y)
      return gcdR(y, x);

   long long f = x % y;
   if(f == 0)
     return y;
   else
      return gcdR(y, f);
}

long long anotherGcd(long long x, long long y) {
    x = abs(x);
    y = abs(y);
    if(x < y)
      std::swap(x, y);
    while(y > 0){
      int f = x % y;
      x = y;
      y = f;
    }
    return x;
} 

int main () {
    long long loop, A, B, C, D, count;
    vector<long long> bufferVector;
    vector<long long>::iterator vectorIterator;
    vector< vector<long long> >::iterator vectorVectorIterator;

    #ifdef debug_on
        printf("\n| C3.A - Caminhando pela calçada |\n");
    #endif

    /* read program arguments */
    scanf("%lld", &T);
    for (loop=0; loop<T; loop++) {
        scanf("%lld", &A);
        scanf("%lld", &B);
        scanf("%lld", &C);
        scanf("%lld", &D);
        bufferVector.push_back(A);
        bufferVector.push_back(B);
        bufferVector.push_back(C);
        bufferVector.push_back(D);
        testCases.push_back(bufferVector);
        bufferVector.pop_back();
        bufferVector.pop_back();
        bufferVector.pop_back();
        bufferVector.pop_back();
    }
    
    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    for (vectorVectorIterator=testCases.begin(); vectorVectorIterator!=testCases.end(); vectorVectorIterator++) {
        bufferVector = *vectorVectorIterator;
        vectorIterator = bufferVector.begin();
        A = *vectorIterator;
        vectorIterator++;
        B = *vectorIterator;
        vectorIterator++;
        C = *vectorIterator;
        vectorIterator++;
        D = *vectorIterator;
        count = 2;
        if (A == C && B == D) {
            count = 1;
        }
        else if (A == C) {
            if (D > B)
                count = D - B + 1;
            else
                count = B - D + 1;
        }
        else if (B == D) {
            if (C > A)
                count = C - A + 1;
            else
                count = A - C + 1;
        }
        else {
            count = greatestCommonDivisor(C-A, D-B) + 1;
        }
        printf("%lld\n",count);
    }
    
    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}