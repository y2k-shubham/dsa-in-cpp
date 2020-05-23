// http://www.geeksforgeeks.org/longest-repeating-subsequence/
// modification of LCS

/*
Input
abc
Output
None

Input
aab
Output
a

Input
aabb
Output
ab

Input
axxxy
Output
xx
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
#define MAX 100

void init(int [MAX][MAX], int);
void findLRSS(string, int [MAX][MAX]);
void showLRSS(string, int [MAX][MAX]);

int main() {
	string str;
	int tab[MAX][MAX];

	cout << "Enter string:\t";
	getline(cin, str);

	init(tab, str.length());
	findLRSS(str, tab);

	showLRSS(str, tab);

	return 0;
}

void init(int tab[MAX][MAX], int len) {
	for (int j = 0; j <= len; j++) {
		tab[0][j] = 0;
	}

	for (int i = 0; i <= len; i++) {
		tab[i][0] = 0;
	}
}

void findLRSS(string str, int tab[MAX][MAX]) {
	for (int i = 1; i <= str.length(); i++) {
		for (int j = 1; j <= str.length(); j++) {
			if (i != j && str[i - 1] == str[j - 1]) {
				tab[i][j] = 1 + tab[i - 1][j - 1];
			} else {
				tab[i][j] = max(tab[i - 1][j], tab[i][j - 1]);
			}
		}
	}
}

void showLRSS(string str, int tab[MAX][MAX]) {
//	cout << "It's length is " << tab[str.length()][str.length()] << endl;
	if (tab[str.length()][str.length()] > 0) {
		string sub;
		int i, j;

		i = j = str.length();
		while (i >= 0 && j >= 0) {
			if (i != j && str[i - 1] == str[j - 1]) {
				sub = str[i - 1] + sub;
				i--;
				j--;
			} else if (tab[i - 1][j] > tab[i][j - 1]) {
				i--;
			} else {
				j--;
			}
		}

		cout << "\nLongest repeating subsequence is " << sub << endl;
		cout << "It's length is " << tab[str.length()][str.length()] << endl;
	} else {
		cout << "\nNo repeating subsequence exists\n";
	}
}

