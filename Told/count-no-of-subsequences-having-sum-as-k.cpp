/*
7
8 1 3 7 4 2 9
11

12
8 1 0 3 7 4 0 0 2 0 9 0
11

10
8 1 3 7 4 12 2 9 5 2
11
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void showArray(int [MAX], int);
void showTab(int [MAX][MAX], int [MAX], int, int);
void init(int [MAX][MAX], int [MAX], int, int);
void findWays(int [MAX], int, int, int [MAX][MAX]);
void showWays(int [MAX], int [MAX][MAX], int, int, string, int);

int main() {
	int arr[MAX], len;
	int k;
	int tab[MAX][MAX];

	input(arr, len, k);
	init(tab, arr, len, k);

	showArray(arr, len);
	showTab(tab, arr, len, k);

	findWays(arr, len, k, tab);

	showArray(arr, len);
	showTab(tab, arr, len, k);

	cout << "\nPossible subsequences that add up to " << k << " are:-\n";
	showWays(arr, tab, len, k, "", k);

	return 0;
}

void input(int arr[MAX], int &len, int &k) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 1; i <= len; i++) {
		cin >> arr[i];
	}

	printf("Enter required sum k:\t");
	cin >> k;
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTab(int tab[MAX][MAX], int arr[MAX], int len, int k) {
	cout << "\nTable is:-\n";

	cout << "\t";
	for (int j = 0; j <= k; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i <= len; i++) {
		if (i == 0) {
			printf("[%d]\t", i);
		} else {
			printf("[%d]=%d\t", i, arr[i]);
		}

		for (int j = 0; j <= k; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void init(int tab[MAX][MAX], int arr[MAX], int len, int k) {
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= k; j++) {
			tab[i][j] = 0;
		}
	}

	tab[0][0] = 1;
	int ctr = 0;
	for (int i = 1; i <= len; i++) {
		tab[i][0] = tab[i - 1][0];
		if (arr[i] == 0) {
			ctr++;
			tab[i][0] = (int) (ceil(pow(2, ctr)));
		}
	}
}

void findWays(int arr[MAX], int len, int k, int tab[MAX][MAX]) {
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= k; j++) {
			if (j < arr[i]) {
				tab[i][j] = tab[i - 1][j];
			} else {
				tab[i][j] = tab[i - 1][j] + tab[i - 1][j - arr[i]];
			}
		}
	}
}

void showWays(int arr[MAX], int tab[MAX][MAX], int row, int col, string str, int reqSum) {
	if (row == 0 || col == 0) {
		if (reqSum == 0) {
			cout << str << endl;
		}
	} else if (tab[row][col] == tab[row - 1][col]) {
		showWays(arr, tab, row - 1, col, str, reqSum);
	} else {
		// including element arr[row]
		char numCS[MAX];
		string numCPPS;

		sprintf(numCS, "%d", arr[row]);
		for (int i = strlen(numCS) - 1; i >= 0; i--) {
			numCPPS = numCS[i] + numCPPS;
		}

		showWays(arr, tab, row - 1, col - arr[row], numCPPS + " " + str, reqSum - arr[row]);

		// excluding element arr[row]
		showWays(arr, tab, row - 1, col, str, reqSum);
	}
}

