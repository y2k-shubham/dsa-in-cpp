// Karumanchi, DP, problem 36, page 408, longest palindromic substring

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

void init(bool [MAX][MAX], string, int);
void showTab(bool [MAX][MAX], string, int, const char *);
void findLPS(bool [MAX][MAX], string, int);

int main() {
	string str;
	int len;
	bool tab[MAX][MAX];

	cout << "Enter a string:\t";
	cin >> str;
	len = str.length();

	init(tab, str, len);
	showTab(tab, str, len, "tab[][] before calculation");

	findLPS(tab, str, len);
	showTab(tab, str, len, "tab[][] after calculation");

	return 0;
}

void init(bool tab[MAX][MAX], string str, int len) {
	memset(tab, 0, len * MAX * sizeof(bool));

	for (int i = 0; i < len; i++) {
		tab[i][i] = true;
	}

	for (int i = 1; i < len; i++) {
		if (str[i - 1] == str[i]) {
			tab[i - 1][i] = true;
		} else {
			tab[i - 1][i] = false;
		}
	}
}

void showTab(bool tab[MAX][MAX], string str, int len, const char * name) {
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
			if (tab[i][j]) {
				cout << "T\t";
			} else {
				cout << "F\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void findLPS(bool tab[MAX][MAX], string str, int len) {
	int mLen = 1;
	int mBeg = 0;

	for (int rLen = 3; rLen <= len; rLen++) {
		int rLo = 0;
		int cLo = rLen - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			tab[i][j] = (tab[i + 1][j - 1]) && (str[i] == str[j]);
			if (tab[i][j]) {
				int cLen = j - i + 1;

				if (cLen > mLen) {
					mLen = cLen;
					mBeg = i;
				}
			}

			i++;
			j++;
		}
	}

	cout << "\nLongest palindromic substring is ";
	for (int i = mBeg; i <= mBeg + mLen - 1; i++) {
		putc(str[i], stdout);
	}
	cout << endl;
}

