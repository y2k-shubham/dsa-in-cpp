// http://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/
// TusharRoy
// given list of denominations and a target amount, find the minimum number of coins that can
// be used from amongst given denominations (in whatever quantity) to obtain that amount.
// here assumption is infinite supply of coins of each denomination

/*
4
1 5 6 8
11

3
5 10 25
30

4
1 5 6 9
11

3
1 2 3
4

4
2 3 5 6
10
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void init(int [MAX][MAX], int, int);
void showMat(int [MAX][MAX], int, int);
void calcMinCoins(int [MAX][MAX], int [MAX], int, int);
void output(int [MAX][MAX], int [MAX], int, int);
int add(int, int);

int main() {
	int denom[MAX];
	int denCount, reqAmt;
	int tab[MAX][MAX];

	input(denom, denCount, reqAmt);

	init(tab, denCount, reqAmt);
	showMat(tab, denCount, reqAmt);

	calcMinCoins(tab, denom, denCount, reqAmt);
	showMat(tab, denCount, reqAmt);

	output(tab, denom, denCount, reqAmt);

	return 0;
}

void input(int denom[MAX], int &denCount, int &reqAmt) {
	printf("Enter no of denominations:\t");
	scanf("%d", &denCount);

	printf("Enter denominations-list:-\n");
	for (int i = 1; i <= denCount; i++) {
		cin >> denom[i];
	}

	cout << "Enter required amount:\t";
	cin >> reqAmt;
}

void init(int tab[MAX][MAX], int denCount, int reqAmt) {
	for (int i = 0; i <= denCount; i++) {
		tab[i][0] = 0;
	}

	for (int j = 0; j <= reqAmt; j++) {
		tab[0][j] = INT_MAX;
	}
}

void showMat(int tab[MAX][MAX], int denCount, int reqAmt) {
	printf("\nTable is:-\n");
	for (int i = 0; i <= denCount; i++) {
		for (int j = 0; j <= reqAmt; j++) {
			if (tab[i][j] != INT_MAX) {
				printf("%d ", tab[i][j]);
			} else {
				printf("~ ");
			}
		}
		printf("\n");
	}
}

void calcMinCoins(int tab[MAX][MAX], int denom[MAX], int denCount, int reqAmt) {
	for (int i = 1; i <= denCount; i++) {
		// copy values from above
		int j = 1;
		while (j < denom[i]) {
			tab[i][j] = tab[i - 1][j];
			j++;
		}

		// calculate min no of coins
		for ( ; j <= reqAmt; j++) {
			tab[i][j] = min(tab[i - 1][j], add(tab[i][j - denom[i]], 1));
		}
	}
}

void output(int tab[MAX][MAX], int denom[MAX], int denCount, int reqAmt) {
	printf("\nMinimum number of coins needed are:\t%d\n", tab[denCount][reqAmt]);
	printf("Coins included in solution are:-\n");

	int i = denCount;
	int j = reqAmt;
	while (j > 0) {
		while (tab[i][j] == tab[i - 1][j]) {
			i--;
		}

		printf("%d\t", denom[i]);
		j -= denom[i];
	}
	printf("\n");
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return a + b;
	}
}

