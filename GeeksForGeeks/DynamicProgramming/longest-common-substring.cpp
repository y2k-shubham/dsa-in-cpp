// http://www.geeksforgeeks.org/longest-common-substring/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1439

/*
GeeksForGeeks
GeeksQuiz

abcdxyz
xyzabcd

zxabcdezy
pyzabcdezx
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

#define MAX 100
#define maxVal(a, b) ((a > b) ? a : b)

void input(string&, const char *);
void findLCS(string, string, int [MAX][MAX]);
void showTab(string, string, int [MAX][MAX]);

int main() {
	string str1, str2;
	int lcs[MAX][MAX];

	input(str1, "1st");
	input(str2, "2nd");

	findLCS(str1, str2, lcs);
	showTab(str1, str2, lcs);

	return 0;
}

void input(string& str, const char * which) {
	printf("Enter %s string:\t", which);
	cin >> str;
//	str = str.substr(0, str.length() - 1);
}

void findLCS(string str1, string str2, int lcs[MAX][MAX]) {
	int len1, len2;
	int i, j;
	int r, c;
	int maxLen;

	memset(lcs, 0, sizeof(lcs));
	len1 = str1.length();
	len2 = str2.length();
	maxLen = 0;

	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			if (i == 0 || j == 0) {
				lcs[i][j] = 0;
			} else if (str1[i - 1] == str2[j - 1]) {
				lcs[i][j] = 1 + lcs[i - 1][j - 1];

				if (lcs[i][j] > maxLen) {
					maxLen = lcs[i][j];
					r = i;
					c = j;
				}
			} else {
				lcs[i][j] = 0;
			}
		}
	}

	printf("\nLength of lcs is:\t%d\n", maxLen);
	cout << "LCS is " << str1.substr(r - maxLen, maxLen) << endl;
}

void showTab(string str1, string str2, int lcs[MAX][MAX]) {
	int len1, len2;
	int i, j;

	len1 = str1.length();
	len2 = str2.length();

	printf("\ntab[][] is:-\n");

	cout << "\t";
	for (int j = 0; j <= len2; j++) {
		if (j == 0) {
			printf("[0]\t");
		} else {
			printf("[%d]=%c\t", j, str2[j - 1]);
		}
	}
	cout << endl;

	for (int i = 0; i <= len1; i++) {
		if (i == 0) {
			printf("[0]\t");
		} else {
			printf("[%d]=%c\t", i, str1[i - 1]);
		}

		for (int j = 0; j <= len2; j++) {
			printf("%d\t", lcs[i][j]);
		}
		cout << endl;
	}
}


