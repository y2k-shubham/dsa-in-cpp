// Karumanchi, DP, problem 18, page 394

/*
4
1 1		3 4		4 5		5 7
7
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAX 100

void input(pair <int, int> [MAX], int &, int &);
void init(int [MAX][MAX], int, int);
void calc(pair <int, int> [MAX], int, int, int [MAX][MAX]);
void output(pair <int, int> [MAX], int, int, int [MAX][MAX]);
void showTab(int [MAX][MAX], int, int);
void showItemArr(pair <int, int> [MAX], int);

int main() {
	pair <int, int> items[MAX];
	int n, C;
	int tab[MAX][MAX];

	input(items, n, C);
	showItemArr(items, n);

	init(tab, n, C);
	calc(items, n, C, tab);
	showTab(tab, n, C);

	output(items, n, C, tab);

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

void init(int tab[MAX][MAX], int n, int C) {
	for (int i = 0; i <= n; i++) {
		tab[i][0] = 0;
	}

	for (int j = 0; j <= C; j++) {
		tab[0][j] = 0;
	}
}

void calc(pair <int, int> items[MAX], int n, int C, int tab[MAX][MAX]) {
	for (int i = 1; i <= n; i++) {
		int j;

		for (j = 1; j < items[i].first && j <= C; j++) {
			tab[i][j] = tab[i - 1][j];
		}

		for (; j <= C; j++) {
			tab[i][j] = max(tab[i - 1][j], items[i].second + tab[i - 1][j - items[i].first]);
		}
	}
}

void output(pair <int, int> items[MAX], int n, int C, int tab[MAX][MAX]) {
	int i, j;

	printf("\nOptimal collection of items:-\n");
	for (i = n, j = C; j > 0 && i > 0; ) {
		if (tab[i][j] == tab[i - 1][j]) {
			i--;
		} else {
			printf("item %d (%d, %d)\n", i, items[i].first, items[i].second);
			j -= items[i].first;
			i--;
		}
	}

	printf("Total value of included items:\t%d\n", tab[n][C]);
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

void showTab(int tab[MAX][MAX], int n, int C) {
	printf("\nTable is:-\n");

	cout << "Cap:\t";
	for (int i = 0; i <= C; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	for (int i = 1; i <= n; i++) {
		printf("I%d\t", i);
		for (int j = 0; j <= C; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

