// http://www.geeksforgeeks.org/count-palindrome-sub-strings-string/
// majority code taken from longest-palindromic-substring.cpp

/*
forgeeksskeegfor
abaaa
geek
abaab
abbaeae
a
aa
ab
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;
#define MAX 100

void init(string, int, int[MAX][MAX]);
void showTab(string, int, int [MAX][MAX], const char *);
void fillTab(string, int, bool [MAX][MAX], int [MAX][MAX]);
void init(string, int, bool[MAX][MAX]);
void showTab(string, int, bool [MAX][MAX], const char *);
void fillTab(string, int, bool [MAX][MAX]);

int main() {
	string str;
	int len;
	int tabI[MAX][MAX];
	bool tabB[MAX][MAX];

	cout << "Enter a string:\t";
	cin >> str;
	len = str.length();

	memset(tabI, 0, len * MAX * sizeof(int));
	memset(tabB, false, len * MAX * sizeof(int));

	init(str, len, tabB);
	init(str, len, tabI);
	showTab(str, len, tabB, "before filling, tabB[][]");
	showTab(str, len, tabI, "before filling, tabI[][]");

	fillTab(str, len, tabB);
	fillTab(str, len, tabB, tabI);
	showTab(str, len, tabB, "after filling, tabB[][]");
	showTab(str, len, tabI, "after filling, tabB[][]");

	cout << "\nNo of Palindromic Substring is " << tabI[0][str.size() - 1] << endl;

	return 0;
}

void init(string str, int len, int tab[MAX][MAX]) {
	// initialize diagonal elements
	for (int i = 0; i < len; i++) {
		tab[i][i] = 1;
	}

	// initialize above-diagonal elements
	for (int i = 0; i < len - 1; i++) {
		tab[i][i + 1] = (str[i] == str[i + 1]) ? 3 : 2;
	}
}

void showTab(string str, int len, int tab[MAX][MAX], const char * when) {
	printf("\n%s is:-\n", when);

	printf("\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]=%c\t", i, str[i]);
	}
	cout << endl;

	for (int i = 0; i < len; i++) {
		int j;
		printf("[%d]=%c\t", i, str[i]);

		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < len; j++) {
			printf("%d\t", tab[i][j]);
		}

		cout << endl;
	}
}

void fillTab(string str, int len, bool tabB[MAX][MAX], int tabI[MAX][MAX]) {
	for (int l = 3; l <= len; l++) {
		int rLo = 0;
		int cLo = l - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			tabI[i][j] = tabI[i + 1][j] + tabI[i][j - 1] - tabI[i + 1][j - 1];
			if (tabB[i][j] == true) {
				tabI[i][j]++;
			}
			i++;
			j++;
		}
	}
}

void init(string str, int len, bool tab[MAX][MAX]) {
	// initialize diagonal elements
	for (int i = 0; i < len; i++) {
		tab[i][i] = true;
	}

	// initialize above-diagonal elements
	for (int i = 0; i < len - 1; i++) {
		tab[i][i + 1] = (str[i] == str[i + 1]) ? true : false;
	}
}

void showTab(string str, int len, bool tab[MAX][MAX], const char * when) {
	printf("\n%s is:-\n", when);

	printf("\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]=%c\t", i, str[i]);
	}
	cout << endl;

	for (int i = 0; i < len; i++) {
		int j;
		printf("[%d]=%c\t", i, str[i]);

		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < len; j++) {
			if (tab[i][j] == true) {
				printf("T\t");
			} else {
				printf("F\t");
			}
		}

		cout << endl;
	}
}

void fillTab(string str, int len, bool tab[MAX][MAX]) {
	for (int l = 3; l <= len; l++) {
		int rLo = 0;
		int cLo = l - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			if (str[i] == str[j]) {
				tab[i][j] = tab[i + 1][j - 1];
			}
			i++;
			j++;
		}
	}
}


