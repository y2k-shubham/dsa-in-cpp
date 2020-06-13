// TusharRoy

/*
xaymlz
x?y*z

axbymlz
a?y*z

asoidfdsn
*

a
?

a
*?

a
?*

a
??
*/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
#define MAX 100

void input(string &, string &);
void init(string, int, string, int, bool [MAX][MAX]);
void fillTab(string, int, string, int, bool [MAX][MAX]);
void showTab(string, int, string, int, bool [MAX][MAX]);

int main() {
	string str, pat;
	int sLen, pLen;
	bool tab[MAX][MAX];

	input(str, pat);

	sLen = str.length();
	pLen = pat.length();

	init(str, sLen, pat, pLen, tab);

	fillTab(str, sLen, pat, pLen, tab);
	showTab(str, sLen, pat, pLen, tab);

	if (tab[sLen][pLen] == true) {
		cout << "String matches pattern\n";
	} else {
		cout << "String doesn't match pattern\n";
	}

	return 0;
}

void input(string &str, string &pat) {
	cout << "Enter string:\t";
	getline(cin, str);

	cout << "Enter pattern:\t";
	getline(cin, pat);
}

void init(string str, int sLen, string pat, int pLen, bool tab[MAX][MAX]) {
	// init 1st column with false
	for (int i = 1; i <= sLen; i++) {
		tab[i][0] = false;
	}

	// init 1st row
	tab[0][0] = true;
	for (int j = 1; j <= pLen; j++) {
		if (pat[j - 1] == '*') {
			tab[0][j] = true;
		} else {
			tab[0][j] = false;
		}
	}
}

void fillTab(string str, int sLen, string pat, int pLen, bool tab[MAX][MAX]) {
	for (int i = 1; i <= sLen; i++) {
		for (int j = 1; j <= pLen; j++) {
			if (str[i - 1] == pat[j - 1]) {
				// characters match, so take diagonal value
				tab[i][j] = tab[i - 1][j - 1];
			} else if (pat[j - 1] == '?') {
				// wild card ? found, so take diagonal value
				tab[i][j] = tab[i - 1][j - 1];
			} else if (pat[j - 1] == '*') {
				// wild card *, so take either top value or left value
				tab[i][j] = tab[i - 1][j] || tab[i][j - 1];
			} else {
				// no match
				tab[i][j] = false;
			}
		}
	}
}

void showTab(string str, int sLen, string pat, int pLen, bool tab[MAX][MAX]) {
	printf("\nTable is:-\n");

	// Print Headings
	cout << "\t[-1]\t";
	for (int i = 0; i < pLen; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "\t\t";
	for (int i = 1; i <= pLen; i++) {
		cout << pat.at(i - 1) << "\t";
	}
	cout << endl;

	// Print 1st row
	cout << "[-1]\t";
	for (int j = 0; j <= pLen; j++) {
		(tab[0][j]) ? (cout << "T\t") : (cout << "F\t");
	}
	cout << endl;

	// Print remaining rows
	for (int i = 1; i <= sLen; i++) {
		printf("[%d] %c\t", i, str[i - 1]);
		for (int j = 0; j <= pLen; j++) {
			if (tab[i][j]) {
				printf("T\t");
			} else {
				printf("F\t");
			}
		}
		cout << endl;
	}
	cout << endl;
}

