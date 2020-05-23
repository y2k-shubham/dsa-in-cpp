// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
// TusharRoy

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
int add(int, int);
void calcTotalWays(int [MAX][MAX], int [MAX], int, int);
void showWays(int [MAX], int, int, int, int [MAX]);
void output(int [MAX], int, int [MAX]);

int main() {
	int denom[MAX];
	int denCount, reqAmt;
	int tab[MAX][MAX];

	input(denom, denCount, reqAmt);

	init(tab, denCount, reqAmt);
	showMat(tab, denCount, reqAmt);

	calcTotalWays(tab, denom, denCount, reqAmt);
	showMat(tab, denCount, reqAmt);
	printf("\nNo of ways to return change:\t%d\n", tab[denCount][reqAmt]);

	int res[MAX];
	cout << "\nWays to return change are:-\n";
	showWays(denom, denCount, reqAmt, 1, res);

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
	for (int j = 0; j <= reqAmt; j++) {
		tab[0][j] = 0;
	}

	for (int i = 0; i <= denCount; i++) {
		tab[i][0] = 1;
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

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return a + b;
	}
}

void calcTotalWays(int tab[MAX][MAX], int denom[MAX], int denCount, int reqAmt) {
	for (int i = 1; i <= denCount; i++) {
		for (int j = 1; j <= reqAmt; j++) {
			tab[i][j] = tab[i][j - denom[i]] + tab[i - 1][j];
		}
	}
}

void showWays(int denom[MAX], int denCount, int reqAmt, int ind, int res[MAX]) {
	if (reqAmt == 0) {
		output(denom, denCount, res);
	} else if (ind <= denCount) {
		for (int i = 0; i * denom[ind] <= reqAmt; i++) {
			res[ind] = i;
			showWays(denom, denCount, reqAmt - i * denom[ind], ind + 1, res);
		}
	}
}

void output(int denom[MAX], int denCount, int res[MAX]) {
	for (int i = 1; i <= denCount; i++) {
		for (int j = 1; j <= res[i]; j++) {
			printf("%d ", denom[i]);
		}
	}
	cout << endl;
}

