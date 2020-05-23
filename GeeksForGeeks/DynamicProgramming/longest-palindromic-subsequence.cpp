// http://www.geeksforgeeks.org/dynamic-programming-set-12-longest-palindromic-subsequence/

// http://www.algorithmist.com/index.php/Longest_Common_Subsequence
// http://www.geeksforgeeks.org/dynamic-programming-set-4-longest-common-subsequence/
// http://www.ics.uci.edu/~eppstein/161/960229.html

/*
apfsbqmtrcrljqdskkp
cabca
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX 100
#define maxVal(a, b) ((a > b) ? a : b)

void input(string&, const char *);
void findLCS(string, string, int [MAX][MAX]);
string getLCSRec(string, string, int [MAX][MAX], int, int);
string getLCSIter(string, string, int [MAX][MAX]);
void showTab(string, string, int [MAX][MAX], const char *);

int main() {
	string str1, str2;
	int lcs[MAX][MAX];

	input(str1, "");
	str2 = str1;
	reverse(str2.begin(), str2.end());

	findLCS(str1, str2, lcs);
	showTab(str1, str2, lcs, "after filling");

	cout << "The lcs is:\t" << getLCSRec(str1, str2, lcs, str1.length(), str2.length()) << endl;
	cout << "The lcs is:\t" << getLCSIter(str1, str2, lcs) << endl;

	return 0;
}

void input(string& str, const char * which) {
	printf("Enter %s string:\t", which);
	cin >> str;
}

void findLCS(string str1, string str2, int lcs[MAX][MAX]) {
	int len1, len2;
	int i, j;

	memset(lcs, 0, sizeof(lcs));
	len1 = str1.length();
	len2 = str2.length();

	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			if (i == 0 || j == 0) {
				lcs[i][j] = 0;
			} else if (str1[i - 1] == str2[j - 1]) {
				lcs[i][j] = 1 + lcs[i - 1][j - 1];
			} else {
				lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
			}
		}
	}

	printf("\nLength of lcs is:\t%d\n", lcs[len1][len2]);
}

void showTab(string str1, string str2, int tab[MAX][MAX], const char * when) {
	int len1 = str1.length();
	int len2 = str2.length();

	printf("\n%s, tab[][] is:-\n", when);

	cout << "\t";
	for (int j = 0; j <= len2; j++) {
		printf("[%d]=%c\t", j, str2[j - 1]);
	}
	cout << endl;

	for (int i = 0; i <= len1; i++) {
		printf("[%d]=%c\t", i, str1[i - 1]);
		for (int j = 0; j <= len2; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

string getLCSRec(string str1, string str2, int lcs[MAX][MAX], int row, int col) {
	if (row < 0 || col < 0) {
		return "";
	} else if (str1[row] == str2[col]) {
		return getLCSRec(str1, str2, lcs, row - 1, col - 1) + str1[row];
	} else if (lcs[row - 1][col] > lcs[row][col - 1]) {
		return getLCSRec(str1, str2, lcs, row - 1, col);
	} else {
		return getLCSRec(str1, str2, lcs, row, col - 1);
	}
}

string getLCSIter(string str1, string str2, int lcs[MAX][MAX]) {
	int i, j;
	string lcsStr;

	i = str1.length() - 1;
	j = str2.length() - 1;

	while (i >= 0 && j >= 0) {
		if (str1[i] == str2[j]) {
			lcsStr = str1[i] + lcsStr;
			i--;
			j--;
		} else if (i > 0 && j > 0 && lcs[i - 1][j] > lcs[i][j - 1]) {
			i--;
		} else {
			j--;
		}
	}

	return lcsStr;
}

