/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 2                    Professor Marcel   **/
/**   Problema C - Tiro ao Alvo                                    Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5369c2c7f6fa9de49e5c65c5/view?index=2   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>
#define MAX_CIRCLES 100000
#define debug_off 1

using namespace std;

int C, T;
long long radius[MAX_CIRCLES];
vector< pair<int,int> > throws;

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop;
    vector< pair<int,int> >::iterator pairVectorIterator;
    printf("Arguments:\n");
    printf(" C=%d;\n",C);
    for (loop=0; loop<C; loop++)
        printf("  Radius=%.0f\n",sqrt(radius[loop]));
    printf(" T=%d;\n",T);
    for (pairVectorIterator=throws.begin(); pairVectorIterator!=throws.end(); pairVectorIterator++)
        printf("  Throw=(%d,%d)\n",(*pairVectorIterator).first,(*pairVectorIterator).second);
}
#endif

int bs (long long array[], int startIndex, int endIndex, double myValue) {
    int middleIndex = (startIndex + endIndex)/2;
    if (myValue < array[middleIndex]) {
        if (myValue > array[middleIndex-1])
            return middleIndex;
        return bs(array,startIndex,middleIndex,myValue);
    }
    else if (myValue > array[middleIndex]) {
        if (myValue < array[middleIndex+1])
            return middleIndex+1;
        return bs(array,middleIndex+1,endIndex,myValue);
    }
    else return middleIndex;
}

int main () {
    set<long long>::iterator setIterator;
    vector< pair<int,int> >::iterator pairVectorIterator;
    int loop, throwScore;
    long long score, arg, secondArg;
    double distance;

    #ifdef debug_on
        printf("\n| C2.C - Tiro ao Alvo |\n");
    #endif

    /* read program arguments */
    scanf("%d", &C);
    scanf("%d", &T);
    for (loop=0; loop<C; loop++) {
        scanf("%lld",&arg);
        arg = arg * arg;
        radius[loop] = arg;   
    }
    for (loop=0; loop<T; loop++) {
        scanf("%lld",&arg);
        scanf("%lld",&secondArg);
        throws.push_back(make_pair(arg,secondArg));   
    }

    #ifdef debug_on
        printArgs();
        printf("\nProblem Solution:\n");
    #endif

    /* solution */
    score = 0;
    for (pairVectorIterator=throws.begin(); pairVectorIterator!=throws.end(); pairVectorIterator++) {
        distance = 1.0f*((*pairVectorIterator).first) * 1.0f*((*pairVectorIterator).first);
        distance = 1.0f*((*pairVectorIterator).second) * 1.0f*((*pairVectorIterator).second) + distance;
        #ifdef debug_on
            printf("Checking throw: (%d,%d) [distance: %.2f]\n",(*pairVectorIterator).first,(*pairVectorIterator).second,distance);
        #endif
        /*miss = 0;
        for (loop=0; loop<C; loop++) {
            if (distance > radius[loop])
            {
                miss++;
                #ifdef debug_on
                    printf(" -> Miss! Distance: %.2f; Radius: %lld\n",distance,*setIterator);
                #endif
            }
            else break;
        }
        throwScore = C - miss;*/
        if (distance < radius[0])
            throwScore = C;
        else if (distance > radius[C-1])
            throwScore = 0;
        else
            throwScore = C-bs(radius,0,C,distance);
        score += throwScore;
        #ifdef debug_on
            printf(" => ThrowScore: %d\n",throwScore);
        #endif
    }

    /* output */
    printf("%lld\n",score);

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}