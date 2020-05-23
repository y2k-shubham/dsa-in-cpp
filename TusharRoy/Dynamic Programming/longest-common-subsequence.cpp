// TusharRoy

/*
abcdaf
acbcf

BDCABA
ABCBDAB
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
#define MAX 100

void input(string &, string &);
void init(int [MAX][MAX], int, int);
void findLCS(string, string, int [MAX][MAX]);
void showLCS(string, string, int [MAX][MAX]);

int main() {
	string str1, str2;
	int tab[MAX][MAX];

	input(str1, str2);
	init(tab, str1.length(), str2.length());

	findLCS(str1, str2, tab);
	showLCS(str1, str2, tab);

	return 0;
}

void input(string &str1, string &str2) {
	cout << "Enter 1st string:\t";
	getline(cin, str1);

	cout << "Enter 2nd string:\t";
	getline(cin, str2);
}

void init(int tab[MAX][MAX], int rows, int cols) {
	for (int i = 0; i <= rows; i++) {
		tab[i][0] = 0;
	}

	for (int j = 0; j <= cols; j++) {
		tab[0][j] = 0;
	}
}

void findLCS(string str1, string str2, int tab[MAX][MAX]) {
	for (int i = 1; i <= str1.length(); i++) {
		for (int j = 1; j <= str2.length(); j++) {
			if (str1[i - 1] == str2[j - 1]) {
				tab[i][j] = tab[i - 1][j - 1] + 1;
			} else {
				tab[i][j] = max(tab[i - 1][j], tab[i][j - 1]);
			}
		}
	}
}

void showLCS(string str1, string str2, int tab[MAX][MAX]) {
	int i, j;
	string lcs;

	i = str1.length();
	j = str2.length();

	while (i > 0 && j > 0) {
		if (tab[i][j] == tab[i - 1][j]) {
			i--;
		} else if (tab[i][j] == tab[i][j - 1]) {
			j--;
		} else {
			lcs = str1.at(i - 1) + lcs;
			i--;
			j--;
		}
	}

	cout << "\nLCS of given strings is:\t" << lcs;
	printf("\nLength of LCS is:\t\t%d\n", tab[str1.length()][str2.length()]);
}

