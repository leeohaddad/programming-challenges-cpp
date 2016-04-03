/***************************************************************/
/**                                                           **/
/**   Leonardo Haddad                           nº 7295361    **/
/**   Desafios de Programação - Round 2    Professora Cris    **/
/**   Problema 6 - Husband in a Shop            Curso: BCC    **/
/**                                                           **/
/***************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <deque>
#define MAX_SIZE 30
#define H_OK 0
#define H_LESS 1
#define H_ZERO 2
#define debug_off 1

using namespace std;

int m;
map<string,int> storage;
int n;
deque< pair<string,int> > husbands;
int minutes;

#ifdef debug_on
/* print arguments */
void printArgs () {
    map<string,int>::iterator pairIterator;
    deque< pair<string,int> >::iterator dequeIterator;
	printf("Arguments:\n");
	printf(" n=%d;\n",n);
	printf(" storage:\n");
    for(pairIterator = storage.begin(); pairIterator != storage.end(); pairIterator++) {
		cout << "  " << pairIterator->first << ": " << pairIterator->second << endl;
    }
	printf(" m=%d;\n",m);
	printf(" husbands:\n");
	for(dequeIterator = husbands.begin(); dequeIterator != husbands.end(); dequeIterator++) {
		cout << "  " << dequeIterator->first << ": " << dequeIterator->second << endl;
    }
}
#endif

int husband (pair<string,int> currentHusband)
{
    #ifdef debug_on
        cout << currentHusband.first << ": " << currentHusband.second << "/" << storage[currentHusband.first] << endl;
    #endif
    minutes++;
    if (storage[currentHusband.first] == 0)
        return H_ZERO;
    if (storage[currentHusband.first] < currentHusband.second)
        return H_LESS;
    storage[currentHusband.first] = storage[currentHusband.first] - currentHusband.second;
    return H_OK;
}

int main () {
    int loop, arg, returnValue;
    string text;
    char trashS[MAX_SIZE];
    pair<string,int> currentHusband, husbandBuffer;

	#ifdef debug_on
		printf("\n| P6 - Husband in a Shop |\n");
	#endif

    /* read program arguments */
	scanf("%d", &m);
	for (loop=0; loop<m; loop++) {
		scanf("%d",&arg);
		scanf("%s ",trashS);
		getline(cin,text);
		storage[text] = arg;
	}
	scanf("%d", &n);
	for (loop=0; loop<n; loop++) {
		scanf("%d",&arg);
		scanf("%s ",trashS);
		getline(cin,text);
		husbands.push_back(make_pair(text,arg));
	}

	#ifdef debug_on
		printArgs();
		printf("\nProblem Solution:\n");
	#endif

	/* solution */
	if (n == 0) {
        printf("0\n");
        return 0;
	}
	if (m == 0) {
        printf("%d\n",n);
        return 0;
	}
	minutes = 0;
	currentHusband = husbands.front();
    husbands.pop_front();
	while (!husbands.empty()) {
        returnValue = husband(currentHusband);
        husbandBuffer = currentHusband;
        currentHusband = husbands.front();
        husbands.pop_front();
        if (returnValue == H_LESS) {
            husbandBuffer.second = storage[husbandBuffer.first];
            husbands.push_front(husbandBuffer);
        }
	}
    husband(currentHusband);
	printf("%d\n",minutes);

	#ifdef debug_on
		printf("\n--------------------\n");
	#endif
	return 0;
}

/*

1795. Husband in a Shop
Time limit: 1.0 second
Memory limit: 64 MB
Url: http://acm.timus.ru/problem.aspx?space=1&num=1795

Mark comes home after a day of hard work. His wife, instead of feeding him, sends him to buy some bread. When Mark comes to a local shop, there is a long line of equally unhappy husbands. Mark joins the line. Fortunately, the line is moving rather quickly because each husband is asked to buy only one kind of a product.
When each husband comes to the counter, he asks for some amount of the product he needs to buy. If this amount of the product is available, he buys it and leaves the shop. If he is told that this product is unavailable, he gets terribly upset and also leaves the shop. If the available amount of the product is less than he needs, he doesn't know what to do and calls his wife for advice. In order to make a call without delaying the line, he lets one person come forward and calls his wife while standing second in line. The wife tell him to buy all the remaining products. After that he comes to the counter once again and, if the amount of the product is still the same, buys it. Otherwise, he lets one more person come forward and calls his wife again. If it happens so that the product is no longer available after a call, the customer leaves the shop empty-handed.
Mark is eager to return home and have dinner at last. Your task is to determine how many minutes will pass before he gets to the counter for the first time. Each customer spends exactly one minute at the counter and has enough time to call his wife if necessary while the following in line customer speaks to the shopgirl.

Input:
The first line contains the number m of different products sold at the shop (1 ≤ m ≤ 1000). Each of the following m lines describes one product. The descriptions have the form “amount of name”, where name is the name of the product (a nonempty string of length at most 20 consisting of lowercase English letters) and amount is the amount of units of this product left by the moment Mark entered the shop (it is a positive integer not exceeding 1000). All the products have distinct names.
In the following line you are given the number n of customers standing in the line before Mark (1 ≤ n ≤ 1000). The following n lines describe the products these customers want to buy in the same format in which the products in the shop are described. There can be more than one customer who want to buy the same product. Customers may want to buy a product that is not available at the shop. The information on the customers is given in the order from the beginning of the line to its end.

Output:
Output the number of minutes that Mark will stand in line before he gets to the counter for the first time.

Sample:

Input:
3
2 of sweets
4 of milk
1 of sausage
4
2 of milk
3 of sweets
3 of milk
1 of cheese
Output:
6

*/
