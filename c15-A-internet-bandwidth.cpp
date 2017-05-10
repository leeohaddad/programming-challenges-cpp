/*********************************************************************************/
/**                                                                             **/
/**   Leonardo Haddad                                              nº 7295361   **/
/**   Desafios de Programação - Contest 15                   Professor Marcel   **/
/**   Problema A - Internet Bandwidth                              Curso: BCC   **/
/**   https://www.codepit.io/#/problems/5430d58f7455fe80169125b0/view?index=0   **/
/**                                                                             **/
/*********************************************************************************/

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_BANDWIDTH 1005
#define MAX_INT 2147483647
#define debug_off 1

using namespace std;

int n, s, t, c;
int network[MAX_BANDWIDTH][MAX_BANDWIDTH];
int flow[MAX_BANDWIDTH][MAX_BANDWIDTH];
bool visited[MAX_BANDWIDTH];

#ifdef debug_on
/* print arguments */
void printArgs () {
    int loop, innerLoop;
    printf("Arguments:\n");
    printf(" n=%d;\n s=%d; t=%d; c=%d;\n",n);
    printf(" network:\n ");
    for (loop=0; loop<n; loop++) {
		for (innerLoop=0; innerLoop<n; innerLoop++)
			printf(" %d",network[loop][innerLoop]);
		printf("\n ");
	}
}
#endif

int send(int s, int t, int minResidualCapacity) {
	int loop, capacity;
    visited[s] = true;
    if (s == t)
		return minResidualCapacity;
    for(loop=1; loop<=n; loop++) {
        capacity = network[s][loop] - flow[s][loop];
        if (!visited[loop] && network[s][loop] - flow[s][loop] > 0) {
            if (int sent = send(loop, t, min(minResidualCapacity, capacity))) {
                flow[s][loop] = flow[s][loop] + sent;
                flow[loop][s] = flow[loop][s] - sent;
                return sent;
            }
        }
    }
    return 0;
}

int calculateFlowFordFulkerson (int networkID) {
    int totalBandwidth = 0;
    while(int sent = send(s, t, MAX_INT)) {
        totalBandwidth = totalBandwidth + sent;
        memset(visited, 0, sizeof(visited));
    }
    printf("Network %d\n",networkID);
    printf("The bandwidth is %d.\n",totalBandwidth);
	printf("\n");
}

int main () {
   int loop, currentNetworkID;
   int nodeA, nodeB, bandwidth;

    #ifdef debug_on
        printf("\n| C15.A - Internet Bandwidth |\n");
    #endif
	
	currentNetworkID = 0;
    scanf("%d", &n);
	while (n > 0) {
		/* init */
		currentNetworkID++;
        memset(network, 0, sizeof(network));
        memset(flow, 0, sizeof(flow));
        memset(visited, 0, sizeof(visited));
		
		/* read program arguments */
		scanf("%d %d %d", &s, &t, &c);
		for (loop=0; loop<c; loop++) {
			scanf("%d %d %d", &nodeA, &nodeB, &bandwidth);
            network[nodeA][nodeB] = network[nodeB][nodeA] += bandwidth;
		}

		#ifdef debug_on
			printArgs();
			printf("\nProblem Solution:\n");
		#endif

		/* solution */
		calculateFlowFordFulkerson(currentNetworkID);
		
		scanf("%d", &n);
	}

    #ifdef debug_on
        printf("\n--------------------\n");
    #endif
    return 0;
}