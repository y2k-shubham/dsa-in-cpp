// http://www.geeksforgeeks.org/longest-palindrome-substring-set-1/
// TusharRoy

/*
forgeeksskeegfor
trigger
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;
#define MAX 100

// void init(string, int, bool[MAX][MAX]);
void showTab(string, int, bool [MAX][MAX], const char *);
void fillTab(string, int, bool [MAX][MAX], int &, int &);

int main() {
	string str;
	int len;
	bool tab[MAX][MAX];
	int r = 0, c = 0;

	cout << "Enter a string:\t";
	cin >> str;
	len = str.length();

	memset(tab, true, len * MAX * sizeof(bool));
	//init(str, len, tab);
	showTab(str, len, tab, "before filling");

	fillTab(str, len, tab, r, c);
	showTab(str, len, tab, "after filling");

	cout << "\nLongest Palindromic Substring is " << str.substr(r, (c - r + 1)) << endl;

	return 0;
}

// void init(string str, int len, bool tab[MAX][MAX]) {
// 	// initialize diagonal elements
// 	for (int i = 0; i < len; i++) {
// 		tab[i][i] = true;
// 	}

// 	// initialize above-diagonal elements
// 	for (int i = 0; i < len - 1; i++) {
// 		tab[i][i + 1] = (str[i] == str[i + 1]) ? true : false;
// 	}
// }

void showTab(string str, int len, bool tab[MAX][MAX], const char * when) {
	printf("\n%s tab[][] is:-\n", when);

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

void fillTab(string str, int len, bool tab[MAX][MAX], int &r, int &c) {
	r = c = 0;
	int mLen = 0;

	int cHi = len - 1;
	for (int l = 1; l <= len; l++) {
		int rLo = 0;
		int cLo = l - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			if (i == j) {
				tab[i][j] = true;
			} else if (str[i] == str[j]) {
				if ((j - i) == 1) {
					tab[i][j] = true;
				} else {
					tab[i][j] = tab[i + 1][j - 1];
				}
				if (tab[i][j] == true && (j - i + 1) > mLen) {
					mLen = j - i + 1;
					r = i;
					c = j;
				}
			} else {
				tab[i][j] = false;
			}
			i++;
			j++;
		}

	}

	// printf("mLen = %d\tr = %d\tc = %d\n", mLen, r, c);
}


