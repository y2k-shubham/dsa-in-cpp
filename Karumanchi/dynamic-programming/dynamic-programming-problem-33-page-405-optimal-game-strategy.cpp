// Karumanchi, DP, problem 33, page 405
// http://www.geeksforgeeks.org/dynamic-programming-set-31-optimal-strategy-for-a-game/

/*
7
8 1 3 7 4 2 9

4
5 3 7 10

4
8 15 3 7

4
2 2 2 2

6
20 30 2 2 2 10
*/

#include <cstdio>
#include <iostream>
#include <utility>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100

// input, initialization and pre-computation
void inputSTDIN(int [MAX], int &);
void inputFILE(int [MAX], int &);
void init(pair <int, int> [MAX][MAX], int [MAX], int, bool);
void findSum(int [MAX], int [MAX], int);
// output
void showArr(int [MAX], int, const char *);
void showTab(pair <int, int> [MAX][MAX], int [MAX], int, const char *);
void showSoln(bool taken[MAX], int [MAX], int, int);
// top-down dynamic programming computation
void findMaxScore(pair <int, int> [MAX][MAX], pair <int, int> [MAX][MAX], int [MAX], int [MAX], int);
void findSoln(pair <int, int> [MAX][MAX], int [MAX], int, bool [MAX], bool [MAX]);

int main() {
	int coins[MAX], len;
	int cumSum[MAX];
	pair <int, int> tabScor[MAX][MAX], tabPrnt[MAX][MAX];
	bool tak_1[MAX], tak_2[MAX];

//	inputSTDIN(coins, len);
	inputFILE(coins, len);

	findSum(cumSum, coins, len);
	init(tabScor, coins, len, true);
	init(tabPrnt, coins, len, false);

	showArr(coins, len, "coins[] array");
	showArr(cumSum, len, "sum[] array");

	cout << "\n========================\nBefore computing" << endl;
	showTab(tabScor, coins, len, "tabScor[][]");
	showTab(tabPrnt, coins, len, "tabPrnt[][]");

	findMaxScore(tabScor, tabPrnt, coins, cumSum, len);

	cout << "\n========================\nAfter computing" << endl;
	showTab(tabScor, coins, len, "tabScor[][]");
	showTab(tabPrnt, coins, len, "tabPrnt[][]");

	findSoln(tabPrnt, coins, len, tak_1, tak_2);

	cout << "\n========================" << endl;
	showSoln(tak_1, coins, len, 1);
	showSoln(tak_2, coins, len, 2);

	return 0;
}

// Input, initialization and pre-computation
void inputSTDIN(int coins[MAX], int &len) {
	cout << "Enter no of coins:\t";
	cin >> len;

	cout << "Enter values of coins:-" << endl;
	coins[0] = -1;
	for (int i = 1; i <= len; i++) {
		cin >> coins[i];
	}
}

void inputFILE(int coins[MAX], int &len) {
	FILE * f = fopen("opt_game_ip_5.txt", "r");

	cout << "Enter no of coins:\t";
	fscanf(f, "%d", &len);
	cout << len << endl;

	cout << "Enter values of coins:-" << endl;
	coins[0] = -1;
	for (int i = 1; i <= len; i++) {
		fscanf(f, "%d", &coins[i]);
		cout << coins[i] << "\t";
	}
	cout << endl;
}

void init(pair <int, int> tab[MAX][MAX], int coins[MAX], int len, bool score) {
	int valDum;

	if (score) {
		valDum = 0;
	} else {
		valDum = -1;
	}

	for (int i = 0; i <= len; i++) {
		tab[i][0].first = valDum;
		tab[i][0].second = valDum;

		tab[0][i].first = valDum;
		tab[0][i].second = valDum;
	}

	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			if (i == j) {
				tab[i][j].first = (score) ? coins[i] : i;
				tab[i][j].second = valDum;
			} else {
				tab[i][j].first = valDum;
				tab[i][j].second = valDum;
			}
		}
	}
}

void findSum(int cumSum[MAX], int coins[MAX], int len) {
	cumSum[0] = 0;
	for (int i = 1; i <= len; i++) {
		cumSum[i] = cumSum[i - 1] + coins[i];
	}
}

// output
void showArr(int arr[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i <= len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void showTab(pair <int, int> tab[MAX][MAX], int coins[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);
	cout << "\t";

	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", coins[i]);
	}
	cout << endl;

	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", coins[i]);
		int j;

		for (j = 1; j < i; j++) {
			printf("\t");
		}

		for (; j <= len; j++) {
			printf("%d,%d\t", tab[i][j].first, tab[i][j].second);
		}
		cout << endl;
	}
}

void showSoln(bool taken[MAX], int coins[MAX], int len, int player) {
	printf("\nCoins taken by player %d are:-\n", player);

	cout << "Ind:\t";
	for (int i = 1; i <= len; i++) {
		if (taken[i]) {
			printf("[%d]\t", i);
		}
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 1; i <= len; i++) {
		if (taken[i]) {
			printf("%d\t", coins[i]);
		}
	}
	cout << endl;
}

// top-down dynamic programming computation
void findMaxScore(pair <int, int> tabScor[MAX][MAX], pair <int, int> tabPrnt[MAX][MAX], int coins[MAX], int cumSum[MAX], int len) {
	for (int rSize = 2; rSize <= len; rSize++) {
		int rLo = 0;
		int cLo = rSize - 1;
		int cHi = len;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			if ((coins[i] + tabScor[i + 1][j].second) > (coins[j] + tabScor[i][j - 1].second)) {
				tabScor[i][j].first = coins[i] + tabScor[i + 1][j].second;
				tabPrnt[i][j].first = i;

				tabScor[i][j].second = (cumSum[j] - cumSum[i - 1]) - tabScor[i][j].first;
				tabPrnt[i][j].second = j;
			} else {
				tabScor[i][j].first = coins[j] + tabScor[i][j - 1].second;
				tabPrnt[i][j].first = j;

				tabScor[i][j].second = (cumSum[j] - cumSum[i - 1]) - tabScor[i][j].first;
				tabPrnt[i][j].second = i;
			}

			i++;
			j++;
		}
	}
}

void findSoln(pair <int, int> tabPrnt[MAX][MAX], int coins[MAX], int len, bool tak_1[MAX], bool tak_2[MAX]) {
	memset(tak_1, false, (len + 1) * sizeof(bool));
	memset(tak_2, false, (len + 1) * sizeof(bool));

	int lo = 1;
	int hi = len;
	int turn = 1;

	while (lo <= hi) {
		if (turn == 1) {
			tak_1[tabPrnt[lo][hi].first] = true;
			turn = 2;
		} else {
			tak_2[tabPrnt[lo][hi].first] = true;
			turn = 1;
		}

		if (tabPrnt[lo][hi].first == lo) {
			lo++;
		} else {
			hi--;
		}
	}
}
