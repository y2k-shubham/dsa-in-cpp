// http://www.geeksforgeeks.org/count-palindromic-subsequence-given-string/
// WRONG PROGRAM, it's not an extension of Longest Palindromic Subsequence
// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/

/*
abcd
aab
aaaa
bbabcbcab
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100

int init(string str, int [MAX][MAX]);
void showTab(string, int [MAX][MAX], const char *);
int fillTab(string, int [MAX][MAX]);
string getLPS(string, int [MAX][MAX]);

int main() {
	string str;
	int tab[MAX][MAX];
	int ctr;

	cout << "Enter a string:\t";
	cin >> str;

	memset(tab, 0, sizeof(int) * str.length() * str.length());
	ctr = init(str, tab);
	showTab(str, tab, "before filling");

	ctr += fillTab(str, tab);
	showTab(str, tab, "after filling");

	cout << "\nLongest Palindromic Subsequence is " << getLPS(str, tab) << endl;
	cout << "No of palindromic subsequences is " << ctr << endl;

	return 0;
}

int init(string str, int tab[MAX][MAX]) {
	int len = str.length();
	int ctr = len;

	// fill diagonal elements
	for (int i = 0; i < len; i++) {
		tab[i][i] = 1;
	}

	// fill above-diagonal elements
	for (int i = 0; i < len - 1; i++) {
		if (str[i] == str[i + 1]) {
			tab[i][i + 1] = 2;
			ctr++;
		} else {
			tab[i][i + 1] = 1;
		}
	}

	return ctr;
}

void showTab(string str, int tab[MAX][MAX], const char * when) {
	int len = str.length();

	printf("\n%s, tab[][] is:-\n", when);

	cout << "\t";
	for (int j = 0; j < len; j++) {
		printf("[%d]=%c\t", j, str[j]);
	}
	cout << endl;

	for (int i = 0; i < len; i++) {
		int j = 0;

		printf("[%d]=%c\t", i, str[i]);

		while (j < i) {
			printf("_\t");
			j++;
		}

		for (; j < len; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

string getLPS(string str, int tab[MAX][MAX]) {
	string lpsL, lpsR;
	int i, j;
	int len;

	len = str.length();
	i = 0;
	j = len - 1;
	while (i != j && tab[i][j] > 0) {
		printf("at tab[%d][%d] = %d\t", i, j, tab[i][j]);
		if (tab[i][j] == tab[i + 1][j]) {
			i++;
			printf("going down\n");
		} else if (tab[i][j] == tab[i][j - 1]) {
			j--;
			printf("going left\n");
		} else {
			lpsL = lpsL + str[i];
			lpsR = str[j] + lpsR;
			i++;
			j--;
			printf("going diagonal\t");
			cout << "lpsL = " << lpsL << "\tlpsR = " << lpsR << endl;
		}
	}

	if (i == j) {
		return (lpsL + str[i] + lpsR);
	} else {
		return (lpsL + lpsR);
	}
}

int fillTab(string str, int tab[MAX][MAX]) {
	int len = str.length();
	int ctr = 0;

	for (int l = 3; l <= len; l++) {
		int rLo = 0;
		int cLo = l - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;

		while (j <= cHi) {
			if (str[i] == str[j]) {
				tab[i][j] = tab[i + 1][j - 1] + 2;
				ctr++;
			} else {
				tab[i][j] = max(tab[i + 1][j], tab[i][j - 1]);
			}

			i++;
			j++;
		}
	}

	return ctr;
}

