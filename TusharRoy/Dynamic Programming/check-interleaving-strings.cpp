// http://www.geeksforgeeks.org/check-whether-a-given-string-is-an-interleaving-of-two-other-given-strings-set-2/

/*
axy
aab
aaxaby

axy
aab
abaaxy

xxy
xxz
xxzxxxy

xxx
xxx
xxxxxx

xy
wz
wzxy

xy
x
xxy

yx
x
xxy

xxy
xxz
xxxxzy
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define MAX 100

void fillFirstRow(string, int, string, bool [MAX][MAX]);
void fillFirstCol(string, int, string, bool [MAX][MAX]);
void showTab(bool [MAX][MAX], int, int);
void checkInterLeaving(string, int, string, int, string, bool [MAX][MAX]);

int main() {
	string str1, str2, str3;
	int len1, len2;
	bool tab[MAX][MAX];

	printf("Enter 1st string:\t");
	cin >> str1;
	len1 = str1.length();

	printf("Enter 2nd string:\t");
	cin >> str2;
	len2 = str2.length();

	printf("Enter string to be checked:\t");
	cin >> str3;

	memset(tab, false, (len1 + 1) * (len2 + 1) * sizeof(bool));
	tab[0][0] = true;

	fillFirstRow(str2, len2, str3, tab);
	fillFirstCol(str1, len1, str3, tab);
	checkInterLeaving(str1, len1, str2, len2, str3, tab);

	return 0;
}

void fillFirstRow(string str2, int len2, string str3, bool tab[MAX][MAX]) {
	for (int i = 1; i <= len2; i++) {
		if (str2.at(i - 1) == str3[i - 1] && tab[0][i - 1] == true) {
			tab[0][i] = true;
		} else {
			tab[0][i] = false;
		}
	}
}

void fillFirstCol(string str1, int len1, string str3, bool tab[MAX][MAX]) {
	for (int i = 1; i <= len1; i++) {
		if (str1[i - 1] == str3[i - 1] && tab[i - 1][0] == true) {
			tab[i][0] = true;
		} else {
			tab[i][0] = false;
		}
	}
}

void checkInterLeaving(string str1, int len1, string str2, int len2, string str3, bool tab[MAX][MAX]) {
//	printf("before filling:-\n");
//	showTab(tab, len1, len2);

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str2[j - 1] == str3[i + j - 1] && tab[i][j - 1] == true) {
				tab[i][j] = true;
			} else if (str1[i - 1] == str3[i + j - 1] && tab[i - 1][j] == true) {
				tab[i][j] = true;
			} else {
				tab[i][j] = false;
			}
		}
	}

	showTab(tab, len1, len2);

	if (tab[len1][len2] == true) {
		printf("It is interleaving\n");
	} else {
		printf("It is not interleaving\n");
	}
}

void showTab(bool tab[MAX][MAX], int len1, int len2) {
	printf("\nTable is:-\n");
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			if (tab[i][j] == true) {
				printf("T ");
			} else {
				printf("F ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

