// Karumanchi, DP, problem 35, page 407, longest palindromic subsequence

/*
piaipmppqpmriai
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 100

void init(int [MAX][MAX], int);
void showTab(int [MAX][MAX], string, int, const char *);
void showLPS(int [MAX][MAX], string, int);
void findLPS(int [MAX][MAX], string, int);

int main() {
	string str;
	int len;
	int tab[MAX][MAX];

	cout << "Enter a string:\t";
	cin >> str;
	len = str.length();

	init(tab, len);
	showTab(tab, str, len, "tab[][] before calculation");

	findLPS(tab, str, len);
	showTab(tab, str, len, "tab[][] after calculation");

	showLPS(tab, str, len);

	return 0;
}

void init(int tab[MAX][MAX], int len) {
	memset(tab, 0, len * MAX * sizeof(int));

	for (int i = 0; i < len; i++) {
		tab[i][i] = 1;
	}
}

void showTab(int tab[MAX][MAX], string str, int len, const char * name) {
	printf("\n%s is:-\n\t", name);

	for (int i = 0; i < len; i++) {
		printf("[%c]\t", str.at(i));
	}
	cout << endl;

	for (int i = 0; i < len; i++) {
		int j;
		printf("[%c]\t", str.at(i));

		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < len; j++) {
			cout << tab[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

void showLPS(int tab[MAX][MAX], string str, int len) {
	string lpsL, lpsR;

	int i = 0;
	int j = len - 1;
	while (tab[i][j] > 1) {
		if (tab[i][j] == tab[i + 1][j]) {
			i++;
		} else if (tab[i][j] == tab[i][j - 1]) {
			j--;
		} else {
			lpsL = lpsL + str[i];
			lpsR = str[j] + lpsR;
			i++;
			j--;
		}
	}

	if (tab[i][j] == 1) {
		cout << endl << "Longest Palindromic SubSequence is " << (lpsL + str[i] + lpsR) << endl;
	}
}

void findLPS(int tab[MAX][MAX], string str, int len) {
	for (int rLen = 2; rLen <= len; rLen++) {
		int rLo = 0;
		int cLo = rLen - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			if (str[i] == str[j]) {
				tab[i][j] = tab[i + 1][j - 1] + 2;
//				printf("(s[%d] = %c) == (s[%d] = %c)\tfilled %d + 2   = %d\n", i, str[i], j, str[j], tab[i - 1][j - 1], tab[i][j]);
			} else {
				tab[i][j] = max(tab[i + 1][j], tab[i][j - 1]);
//				printf("(s[%d] = %c) != (s[%d] = %c)\tfilled m(%d, %d) = %d\n", i, str[i], j, str[j], tab[i + 1][j], tab[i][j - 1], tab[i][j]);
			}

			i++;
			j++;
		}
//		cout << endl;
	}
}

