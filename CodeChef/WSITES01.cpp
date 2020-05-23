// https://www.codechef.com/MAY17/problems/WSITES01

/*
4
- codeforces
+ codechef
- youtube
+ google

5
- codeforces
+ codechef
- youtube
+ google
+ youporn

4
+ codeforces
+ codechef
+ youtube
+ google

4
- codeforces
- codechef
- youtube
- google

6
- similie
- simpsons
- sim
+ singer
+ synergy
- sync

7
- similie
- simpsons
- sim
+ singer
+ synergy
- sync
+ syncopate

1
+ piglatin

1
- piglatin
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <list>
#include <climits>

using namespace std;

#define LEN 26
#define MAX 200005

struct node {
	int count_ub;
	int count_b;
	bool ends_ub;
	bool ends_b;
	struct node * child[LEN];
};

node * createNode();
node * addSite(node *, bool, string, int, int);
void input(node *);
void showSites(node *);
void showSiteRec(node *, string);
void showFilterList(list <string>);
int findFilters(node *, string, list <string>&);
int findFilters(node *, list <string>&);

int main() {
	node * trie;
	list <string> filterList;
	int filterCount;

	trie = createNode();
	input(trie);
//	showSites(trie);

	if (trie -> count_ub == 0) {
		filterCount = findFilters(trie, filterList);
	} else if (trie -> count_b == 0) {
		filterCount = 0;
	} else {
		filterCount = findFilters(trie, "", filterList);
	}

	if (filterCount < 0) {
//		printf("\nNo solution\n");
		printf("-1\n");
	} else if (filterCount == 0) {
//		printf("\nFilter count is %d\n", filterCount);
		printf("-1\n");
	} else {
//		printf("\nFilter count is %d\n", filterCount);
		printf("%d\n", filterCount);
		showFilterList(filterList);
	}

	return 0;
}

void input(node * trie) {
	int N;
	string line;

	cin >> N;
	line.reserve(MAX);
	getline(cin, line);

	for (int i = 0; i < N; i++) {
		getline(cin, line);

		if (line[0] == '+') {
			trie -> count_ub++;
			trie -> child[line[2] - 'a'] = addSite(trie -> child[line[2] - 'a'], true, line, 3, line.length() - 1);
		} else {
			trie -> count_b++;
			trie -> child[line[2] - 'a'] = addSite(trie -> child[line[2] - 'a'], false, line, 3, line.length() - 1);
		}
	}
}

node * createNode() {
	node * newNode = (node *) malloc(sizeof(node));
	newNode -> count_ub = 0;
	newNode -> count_b = 0;
	newNode -> ends_ub = false;
	newNode -> ends_b = false;
	for (int i = 0; i < LEN; i++) {
		newNode -> child[i] = NULL;
	}
	return newNode;
}

node * addSite(node * trie, bool unblocked, string siteName, int crrInd, int lastInd) {
	// if node is empty, create new node
	if (trie == NULL) {
		trie = createNode();
	}

	// increment counter if site is unblocked
	if (unblocked) {
		trie -> count_ub++;
	} else {
		trie -> count_b++;
	}

	if (crrInd > lastInd) {
		// if name has been added upto last alphabet, mark completion
		trie -> ends_ub = unblocked;
		trie -> ends_b = !unblocked;
		//		cout << "Added word " << siteName << endl;
	} else {
		// otherwise recursively add remaining alphabets
		trie -> child[siteName[crrInd] - 'a'] = addSite(trie -> child[siteName[crrInd] - 'a'], unblocked, siteName, crrInd + 1, lastInd);
	}

	// return crrNode at the end
	return trie;
}

void showSites(node * trie) {
	printf("\nsites are:-\n");
	for (int i = 0; i < LEN; i++) {
		if (trie -> child[i] != NULL) {
			string pref = "";
			pref += (char) ('a' + i);
			showSiteRec(trie -> child[i], pref);
		}
	}
}

void showSiteRec(node * trie, string siteName) {
	if (trie -> ends_ub == true || trie -> ends_b == true) {
		cout << siteName << endl;

	}

	for (int i = 0; i < LEN; i++) {
		if (trie -> child[i] != NULL) {
			showSiteRec(trie -> child[i], siteName + ((char) ('a' + i)));
		}
	}
}

void showFilterList(list <string> filterList) {
//	printf("\nfilterList is:-\n");
	for (list <string>::iterator i = filterList.begin(); i != filterList.end(); i++) {
		cout << (* i) << endl;
	}
}

int findFilters(node * trie, string pref, list <string>& filterList) {
	if (trie == NULL) {
		return 0;
	} else if (trie -> count_ub == 0) {
		if (trie -> count_b != 0) {
			filterList.push_back(pref);
			return 1;
		} else {
			return 0;
		}
	} else if (trie -> count_b == 0) {
		return 0;
	} else if (trie -> ends_b == true && trie -> count_ub > 0) {
		return INT_MIN;
	} else {
		int prefCountTot = 0;

		for (int i = 0; i < 26; i++) {
			if (trie -> child[i] != NULL) {
				int prefCountCrr = findFilters(trie -> child[i], pref + ((char) ('a' + i)), filterList);

				if (prefCountCrr < 0) {
					return prefCountCrr;
				} else {
					prefCountTot += prefCountCrr;
				}
			}
		}

		return prefCountTot;
	}
}

int findFilters(node * trie, list <string>& filterList) {
	int filterCount = 0;

	for (int i = 0; i < LEN; i++) {
		if (trie -> child[i] != NULL) {
			filterCount++;

			string pref = "";
			pref += (char) ('a' + i);
			filterList.push_back(pref);
		}
	}

	return filterCount;
}

