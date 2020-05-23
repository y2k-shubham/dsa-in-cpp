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

4
7 2 3 6
13

3
3 2 4
6
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void init(int [MAX], int);
void findMinCoinCount(int [MAX], int, int, int [MAX], int [MAX]);
int add(int, int);
void showArray(int [MAX], int, const char *);
void findCoins(int [MAX], int);

int main() {
	int denom[MAX], denCount;
	int reqAmt;
	int minCount[MAX], denUsed[MAX];

	input(denom, denCount, reqAmt);
	init(minCount, reqAmt);
	init(denUsed, reqAmt);

	findMinCoinCount(denom, denCount, reqAmt, minCount, denUsed);
	showArray(minCount, reqAmt, "minCount");
	showArray(denUsed, reqAmt, "denUsed");

	printf("\nMinimum no of coins needed is %d\n", minCount[reqAmt]);
	findCoins(denUsed, reqAmt);

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

void init(int minCount[MAX], int reqAmt) {
	minCount[0] = 0;
	for (int i = 1; i <= reqAmt; i++) {
		minCount[i] = INT_MAX;
	}
}

void findMinCoinCount(int denom[MAX], int denCount, int reqAmt, int minCount[MAX], int denUsed[MAX]) {
	for (int i = 1; i <= denCount; i++) {
		int crrDen = denom[i];

		for (int j = crrDen; j <= reqAmt; j++) {
			if (add(minCount[j - crrDen], 1) < minCount[j]) {
				minCount[j] = minCount[j - crrDen] + 1;
				denUsed[j] = crrDen;
			}
		}
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return a + b;
	}
}

void showArray(int arr[MAX], int len, const char * name) {
	printf("\nArray %s is:-\n", name);

	printf("Ind:\t");
	for (int i = 0; i <= len; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Val:\t");
	for (int i = 0; i <= len; i++) {
		if (arr[i] == INT_MAX) {
			printf("INF\t");
		} else {
			printf("%d\t", arr[i]);
		}
	}
	printf("\n");
}

void findCoins(int denUsed[MAX], int reqAmt) {
	printf("Coins in solution are:-\n");
	for (int i = reqAmt; i > 0; ) {
		printf("%d ", denUsed[i]);
		i -= denUsed[i];
	}
	printf("\n");
}

