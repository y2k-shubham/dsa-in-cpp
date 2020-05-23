// Karumanchi, DP, Problem 17, 0-1 Knapsack with Dulicates allowed
// Time: O(nC)		Space: O(C)

/*
4
1 2		2 5		4 9		5 13
15
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <utility>
#include <algorithm>

struct node {
	int val;
	int item;
	int par;
};

using namespace std;
#define MAX 100

void input(pair <int, int> [MAX], int &, int &);
void calc(pair <int, int> [MAX], int, int, node [MAX]);
void showSolnArr(pair <int, int> [MAX], node soln[MAX], int);
void showItemArr(pair <int, int> [MAX], int);

int main() {
	pair <int, int> items[MAX];
	int n, C;
	node soln[MAX];

	input(items, n, C);
	sort(items + 1, items + (n + 1));

	calc(items, n, C, soln);
	showItemArr(items, n);
	showSolnArr(items, soln, C);

//	output(items, n, C, soln);

	return 0;
}

void input(pair <int, int> items[MAX], int &n, int &C) {
	cout << "Enter no of items:\t";
	cin >> n;

	cout << "Enter (weight, value) of items:-\n";
	for (int i = 1; i <= n; i++) {
		int wgt, val;
		cin >> wgt >> val;

		items[i].first = wgt;
		items[i].second = val;
	}

	cout << "Enter knapsack capacity:\t";
	cin >> C;
}

void calc(pair <int, int> items[MAX], int n, int C, node soln[MAX]) {
	soln[0].val = 0;
	soln[0].par = 0;
	soln[0].item = 0;

	for (int i = 1; i <= C; i++) {
		int maxVal, maxItem, maxPar;
		maxVal = INT_MIN;

		printf("\n==========\nFor cap i = %d\n", i);
		for (int j = 1; items[j].first <= i; j++) {
//			printf("for crrVal, adding items[%d].sec = %d\tand soln[%d - %d] = soln[%d] = %d\n", j, items[j].second, i, items[j].first, (i - items[j].first), soln[i - items[j].first].val);
			int crrVal = items[j].second + soln[i - items[j].first].val;
			if (crrVal > maxVal) {
				maxVal = crrVal;
				maxItem = j;
				maxPar = i - items[j].first;
				printf("updated\tmVal = %d\tmItem = %d\tmPar = %d\n", maxVal, maxItem, maxPar);
			}
		}

		if (maxVal > soln[i - 1].val) {
//			printf("\nstoring\tmVal = %d\tmItem = %d\tmPar = %d\n", maxVal, maxItem, maxPar);
			soln[i].val = maxVal;
			soln[i].par = maxPar;
			soln[i].item = maxItem;
		} else {
//			printf("\nstoring\tmVal = %d\tmItem = %d\tmPar = %d\n", soln[i - 1].val, 0, soln[i - 1].par);
			soln[i].val = soln[i - 1].val;
			soln[i].par = soln[i - 1].par;
			soln[i].item = 0;
		}
		printf("soln[%d]\tmVal = %d\tmItem = %d\tmPar = %d\n", i, soln[i].val, soln[i].item, soln[i].par);
	}
}

void showSolnArr(pair <int, int> items[MAX], node soln[MAX], int C) {
	printf("\nSolution array is:-");

//	cout << "Cap:\t";
//	for (int i = 0; i <= C; i++) {
//		printf("[%d]\t", i);
//	}
//	cout << endl << endl;
//
//	cout << "Val:\t";
//	for (int i = 0; i <= C; i++) {
//		printf("%d\t", soln[i].val);
//	}
//	cout << endl << endl;
//
//	cout << "Item:\t";
//	for (int i = 0; i <= C; i++) {
//		cout << soln[i].item << "\t";
//	}
//	cout << endl << endl;
//
//	cout << "Par:\t";
//	for (int i = 0; i <= C; i++) {
//		cout << soln[i].par << "\t";
//	}
//	cout << endl << endl;

	for (int i = 0; i <= C; i++) {
		printf("\nCap:\t%d\n", i);
		printf("Val:\t%d\n", soln[i].val);
		printf("Item:\t%d (%d, %d)\n", soln[i].item, items[soln[i].item].first, items[soln[i].item].second);
		printf("Par:\t%d\n", soln[i].par);
	}
}

void showItemArr(pair <int, int> item[MAX], int n) {
	printf("\nItem array is:-\n");

	cout << "Ind:\t";
	for (int i = 1; i <= n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Wgt:\t";
	for (int i = 1; i <= n; i++) {
		cout << item[i].first << "\t";
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 1; i <= n; i++) {
		cout << item[i].second << "\t";
	}
	cout << endl;
}


