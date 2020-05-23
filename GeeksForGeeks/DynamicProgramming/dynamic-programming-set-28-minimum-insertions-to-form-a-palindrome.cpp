// http://www.geeksforgeeks.org/dynamic-programming-set-28-minimum-insertions-to-form-a-palindrome/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=557

/*
ab
aa
abcd
abcda
abcde
geeks
gseeks
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
#define MAX 100

void initBottomUp(string str, int [MAX][MAX]);
void initTopDown(int [MAX][MAX], int, int);
void showTab(string, int [MAX][MAX], const char *);
void fillBottomUp(string, int [MAX][MAX]);
int fillTopDown(string, int [MAX][MAX], int, int);
void showMods(string, int [MAX][MAX]);

int main() {
	string str;
	int tab[MAX][MAX];

	cout << "Enter a string:\t";
	cin >> str;

	cout << "\n==============BOTTOM-UP===============" << endl;
	initBottomUp(str, tab);
	showTab(str, tab, "before filling bottom-up");

	fillBottomUp(str, tab);
	showTab(str, tab, "after filling bottom-up");
	cout << "Min no of insertions needed = " << tab[0][str.length() - 1] << endl;

//	cout << "\n==============TOP-DOWN===============" << endl;
//	initTopDown(tab, str.length(), -1);
//	showTab(str, tab, "before filling top-down");
//
//	fillTopDown(str, tab, 0, str.length() - 1);
//	showTab(str, tab, "after filling top-down");
//	cout << "Min no of insertions needed = " << tab[0][str.length() - 1] << endl;

	// this method isn't working correctly
	showMods(str, tab);

	return 0;
}

void initBottomUp(string str, int tab[MAX][MAX]) {
	int len = str.length();

	// fill diagonal elements
	for (int i = 0; i < len; i++) {
		tab[i][i] = 0;
	}

	// fill above-diagonal elements
	for (int i = 0; i < len - 1; i++) {
		if (str[i] == str[i + 1]) {
			tab[i][i + 1] = 0;
		} else {
			tab[i][i + 1] = 1;
		}
	}
}

void initTopDown(int tab[MAX][MAX], int dim, int val) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			tab[i][j] = val;
		}
	}
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

void fillBottomUp(string str, int tab[MAX][MAX]) {
	int len = str.length();

	for (int l = 3; l <= len; l++) {
		int rLo = 0;
		int cLo = l - 1;
		int cHi = len - 1;

		int i = rLo;
		int j = cLo;
		while (j <= cHi) {
			if (str[i] == str[j]) {
				tab[i][j] = tab[i + 1][j - 1];
			} else {
				tab[i][j] = min(tab[i][j - 1], tab[i + 1][j]) + 1;
			}

			i++;
			j++;
		}
	}
}

int fillTopDown(string str, int tab[MAX][MAX], int lo, int hi) {
//	printf("\nat [%d][%d]\n", lo, hi);

	if (tab[lo][hi] >= 0) {
//		printf("already computed, returning [%d][%d] = %d\n", lo, hi, tab[lo][hi]);
		return tab[lo][hi];
	} else {
		if (lo == hi) {
//			printf("single character [%d][%d] = 0\n", lo, hi);
			tab[lo][lo] = 0;
		} else if (hi - lo == 1) {
			if (str[lo] == str[hi]) {
//				printf("two chars, str[%d] = str[%d] = %c\t[%d][%d] = 0\n", lo, hi, str[lo], lo, hi);
				tab[lo][hi] = 0;
			} else {
//				printf("two chars, str[%d] = %c != str[%d] = %c\t[%d][%d] = 1\n", lo, str[lo], hi, str[hi], lo, hi);
				tab[lo][hi] = 1;
			}
		} else {
			if (str[lo] == str[hi]) {
//				printf("str[%d] = str[%d] = %c match, making recursive call to [%d][%d]\n", lo, hi, str[lo], lo + 1, hi - 1);
				tab[lo][hi] = fillTopDown(str, tab, lo + 1, hi - 1);
			} else {
//				printf("str[%d] = %c & str[%d] = %c don't match, making recursive call to [%d][%d]\n", lo, str[lo], hi, str[hi], lo, hi - 1);
				tab[lo][hi] = min(fillTopDown(str, tab, lo, hi - 1), fillTopDown(str, tab, lo + 1, hi)) + 1;
			}
		}

//		printf("\nreturning [%d][%d] = %d\n", tab[lo][hi]);
		return tab[lo][hi];
	}
}

void showMods(string str, int tab[MAX][MAX]) {
	int i = 0;
	int j = str.length() - 1;

	cout << "\nRequired insertions are:-\n";
	while (j >= i && tab[i][j] != 0) {
		if (tab[i][j] == tab[i + 1][j - 1]) {
			i++;
			j--;
		} else if (tab[i + 1][j] < tab[i][j - 1]) {
			printf("insert %c corresponding to str[%d] at posn %d\n", str[i], i, j + 1);
			i++;
		} else {
			printf("insert %c corresponding to str[%d] at posn %d\n", str[j], j, i - 1);
			j--;
		}
	}
}

