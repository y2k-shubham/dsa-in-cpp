// http://www.geeksforgeeks.org/lcs-longest-common-subsequence-three-strings/
// extending LCS to 3D (dynamic programming) memoization table

/*
geeks
geeksfor
geeksforgeeks

abcd1e2
bc12ea
bd1ea
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;
#define MAX 100

void init(char [MAX][MAX][MAX], int, int, int);
void fillTab(string, string, string, char [MAX][MAX][MAX]);
string findLCS(string, string, string, char [MAX][MAX][MAX]);

int main() {
	string str_1, str_2, str_3;
	char tab[MAX][MAX][MAX];

	cout << "Enter the strings:-\n";
	cin >> str_1 >> str_2 >> str_3;

	str_1 = ' ' + str_1;
	str_2 = ' ' + str_2;
	str_3 = ' ' + str_3;
	init(tab, str_1.size(), str_2.size(), str_3.size());

	fillTab(str_1, str_2, str_3, tab);
	cout << "\nLength of LCS is " << ((int) tab[str_1.size() - 1][str_2.size() - 1][str_3.size() - 1]) << endl;
	cout << "LCS is " << findLCS(str_1, str_2, str_3, tab) << endl;

	return 0;
}

void init(char tab[MAX][MAX][MAX], int dim_1, int dim_2, int dim_3) {
	for (int i = 0; i < dim_1; i++) {
		for (int j = 0; j < dim_2; j++) {
			for (int k = 0; k < dim_3; k++) {
				tab[i][j][k] = 0;
			}
		}
	}
}

void fillTab(string str_1, string str_2, string str_3, char tab[MAX][MAX][MAX]) {
	for (int i = 1; i < str_1.size(); i++) {
		for (int j = 1; j < str_2.size(); j++) {
			for (int k = 1; k < str_3.size(); k++) {
				if (str_1[i] == str_2[j] && str_1[i] == str_3[k]) {
					tab[i][j][k] = tab[i - 1][j - 1][k - 1] + 1;
//					printf("str_1[%d] = str_2[%d] = str_3[%d] = %c\ttab[%d][%d][%d] = %d\n", i, j, k, str_1[i], i, j, k, ((int) tab[i][j][k]));
				} else {
					tab[i][j][k] = max(max(tab[i - 1][j][k], tab[i][j - 1][k]), tab[i][j][k - 1]);
//					printf("tab[%d][%d][%d] = %d\n", i, j, k, ((int) tab[i][j][k]));
				}
			}
		}
	}
}

string findLCS(string str_1, string str_2, string str_3, char tab[MAX][MAX][MAX]) {
	string lcs;
	int i, j, k;

	i = str_1.size() - 1;
	j = str_2.size() - 1;
	k = str_3.size() - 1;

	while (i > 0 && j > 0 && k > 0) {
		if (tab[i][j][k] > tab[i - 1][j - 1][k - 1]) {
			lcs = str_1[i] + lcs;
			i--;
			j--;
			k--;
		} else if (tab[i][j][k] == tab[i - 1][j][k]) {
			i--;
		} else if (tab[i][j][k] == tab[i][j - 1][k]) {
			j--;
		} else {
			k--;
		}
	}

	return lcs;
}

