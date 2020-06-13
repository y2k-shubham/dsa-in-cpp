/*
TusharRoy likes to code
10

Zindagi sanwaar doon, ek nayi bahaar doon. Duniya hi badal doon main to pyaara sa chamatkaar hoon.
20

*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;
#define MAX 100

void input(vector <string> &, int &);
void fillTab(vector <string>, int, int [MAX][MAX]);
void fillArr(vector <string>, int [MAX][MAX], int [MAX], int [MAX]);
void showTab(int [MAX][MAX], int);
void showArr(int [MAX], int, const char *);
int add(int, int);
void showSoln(vector <string>, int, int [MAX]);

int main() {
	vector <string> sen;
	int charLim;
	int tab[MAX][MAX];
	int cost[MAX], split[MAX];

	input(sen, charLim);

	fillTab(sen, charLim, tab);
	showTab(tab, sen.size());

	fillArr(sen, tab, cost, split);
	showArr(cost, sen.size(), "cost");
	showArr(split, sen.size(), "split");

	printf("\nMin Cost of displaying is %d\n", cost[0]);
	showSoln(sen, charLim, split);

	return 0;
}

void input(vector <string> &sen, int &charLim) {
	string line;
	string word;

	cout << "Enter sentence:\t";
	getline(cin, line);

	cout << "Enter char limit per line:\t";
	cin >> charLim;

	stringstream ss(line);
	while (ss >> word) {
		sen.push_back(word);
	}
}

void fillTab(vector <string> sen, int charLim, int tab[MAX][MAX]) {
	int lenSum[MAX];

	lenSum[0] = sen[0].length();
	for (int i = 1; i < sen.size(); i++) {
		lenSum[i] = lenSum[i - 1] + sen[i].length();
	}

	for (int i = 0; i < sen.size(); i++) {
		for (int j = i; j < sen.size(); j++) {
			int len = (i == 0) ? (lenSum[j] + j) : (lenSum[j] - lenSum[i - 1] + (j - i));
			if (len > charLim) {
				tab[i][j] = INT_MAX;
			} else {
				tab[i][j] = (int) ceil(pow((charLim - len), 2));
			}
		}
	}
}

void fillArr(vector <string> sen, int tab[MAX][MAX], int cost[MAX], int split[MAX]) {
	for (int i = sen.size() - 1; i >= 0; i--) {
		int j = sen.size() - 1;

		if (tab[i][j] != INT_MAX) {
			cost[i] = tab[i][j];
			split[i] = j + 1;
		} else {
			int minCost, minInd;
			minCost = INT_MAX;

			for (; j > i; j--) {
				int cost_left = tab[i][j - 1];
				int cost_right = cost[j];
				int cost_total = add(cost_left, cost_right);
//				printf("i = %d\tj = %d\tlcost = %d\trcost = %d\ttcost = %d\t", i, j, cost_left, cost_right, cost_total);

				if (cost_total < minCost) {
//					printf("minCost updated\n");
					minCost = cost_total;
					minInd = j;
				} else {
//					printf("minCost unchanged\n");
				}
			}
//			printf("\n");

			cost[i] = minCost;
			split[i] = minInd;
		}
	}
}

void showArr(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTab(int tab[MAX][MAX], int len) {
	cout << "\nTable is:-" << endl;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (j < i) {
				printf("\t");
			} else if (tab[i][j] == INT_MAX) {
				printf("INF\t");
			} else {
				printf("%d\t", tab[i][j]);
			}
		}
		cout << endl;
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return a + b;
	}
}

void showSoln(vector <string> sen, int charLim, int split[MAX]) {
	printf("Optimum printing format is:-\n");
	for (int i = 0; i < sen.size(); ) {
		cout << sen[i];

		int charPrinted = sen[i].length();
		for (int j = i + 1; j < split[i]; j++) {
			cout << " " << sen[j];
			charPrinted += sen[j].length() + 1;
		}

		while (charPrinted < charLim) {
			cout << "_";
			charPrinted++;
		}
		cout << endl;

		i = split[i];
	}
	cout << endl;
}

