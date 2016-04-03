/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 14 - Anansi's Cobweb             Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define MAX_SIZE_N 100005
#define debug_off 1

using namespace std;

int n, m, q, parts;
vector< pair<int,int> > threads;
vector<int> toRemove;
int parent[MAX_SIZE_N];
int rank[MAX_SIZE_N];
int result[MAX_SIZE_N];
bool willBeRemoved[MAX_SIZE_N];

#ifdef debug_on
/* print arguments */
void printArgs () {
	unsigned int loop;
	map< int,set<int> >::iterator mapSetIterator;
	set<int>::iterator setIterator;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" m=%d;\n",m);
	printf(" threads:\n");
	for (loop=0; loop<threads.size(); loop++)
        printf("  %d %d\n",threads[loop].first+1,threads[loop].second+1);
	printf(" q=%d;\n",q);
	printf(" toRemove:\n");
	for (loop=0; loop<toRemove.size(); loop++)
        printf("  %d\n",toRemove[loop]+1);
}
#endif

int findParent (int index) {
    if(parent[index]==index) return index;
    parent[index] = findParent(parent[index]);
    return parent[index];
}
   
void link (int indexA, int indexB) {
    int aParent, bParent;
    aParent = findParent(indexA);
    bParent = findParent(indexB);
    if(aParent==bParent)
        return;
    parts--;
    
    if(rank[aParent]<rank[bParent]) parent[aParent] = bParent;
    else{
        parent[bParent] = aParent;
        if(rank[aParent]==rank[bParent])
            rank[aParent]++;
    }
} 
int main () {
    int loop, argA, argB;
    pair<int,int> thread;

	#ifdef debug_on
		printf("\n| P14 - Anansi's Cobweb |\n");
	#endif

    /* read program arguments */
	scanf("%d %d", &n, &m);
	for (loop=0; loop<m; loop++) {
		scanf("%d %d", &argA, &argB);
        argA--;
        argB--;
		thread = make_pair(argA,argB);
        threads.push_back(thread);
	}
    memset(willBeRemoved,false,sizeof(willBeRemoved));
	scanf("%d", &q);
	for (loop=0; loop<q; loop++) {
		scanf("%d", &argA);
        toRemove.push_back(argA-1);
        willBeRemoved[argA-1] = true;
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

    /* solution */
    for(loop=0; loop<n; loop++){
        parent[loop] = loop;
        rank[loop] = 0;
    }
    parts = n;
    for(loop=0; loop<m; loop++){
        if (!willBeRemoved[loop]) {
            link(threads[loop].first, threads[loop].second);
        }
    }
    for(loop=q-1; loop>=0; loop--){
        result[loop] = parts;
        link(threads[toRemove[loop]].first, threads[toRemove[loop]].second);
    }
    printf("%d",result[0]);
    for(loop=1; loop<q; loop++)
        printf(" %d",result[loop]);
    printf("\n");

    #ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1671. Anansi's Cobweb
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1671

Usatiy-Polosatiy XIII decided to destroy Anansi's home — his cobweb. The cobweb consists of N nodes, some of which are connected by threads. Let us say that two nodes belong to the same piece if it is possible to get from one node to the other by threads. Usatiy-Polosatiy has already decided which threads and in what order he would tear and now wants to know the number of pieces in cobweb after each of his actions.

Input:
The first line contains integers N and M — the number of nodes and threads in the cobweb, respectively(2 ≤ N ≤ 100000; 1 ≤ M ≤ 100000). Each of the next M lines contains two different integers — the 1-based indices of nodes connected by current thread. The threads are numbered from 1 to M in the order of description. Next line contains an integer Q which denotes the quantity of threads Usatiy-Polosatiy wants to tear (1 ≤ Q ≤ M). The last line contains numbers of these threads — different integers separated by spaces.

Output:
Output Q integers — the number of pieces in Anansi's cobweb after each of Usatiy-Polosatiy's action. Separate numbers with single spaces.

Samples:

Input:
4 4
1 2
2 3
1 3
3 4
3
2 4 3
Output:
1 2 3

Input:
3 1
1 2
1
1
Output:
3

*/
