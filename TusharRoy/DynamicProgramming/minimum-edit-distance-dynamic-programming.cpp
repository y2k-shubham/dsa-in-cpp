// TusharRoy

/*
azced
abcdef

geek
gesek

cat
cut

sunday
saturday

*/

#include <string>
#include <cstdio>
#include <iostream>

using namespace std;

#define MAX 100
#define max(a, b, c) ((a > b && a > c) ? a : ((b > a && b > c) ? b : c))
#define min(a, b, c) ((a < b && a < c) ? a : ((b < a && b < c) ? b : c))

void init(int [MAX][MAX], int, int);
void findMED(string, int, string, int, int [MAX][MAX]);
void showMat(int [MAX][MAX], int, int);
void output(string, string, int [MAX][MAX], int, int);

int main() {
	string str1, str2;
	int len1, len2;
	int tab[MAX][MAX];

	printf("Enter 1st string:\t");
	getline(cin, str1);
	len1 = str1.length();

	printf("Enter 2nd string:\t");
	getline(cin, str2);
	len2 = str2.length();

	init(tab, len1, len2);
	findMED(str1, len1, str2, len2, tab);

	showMat(tab, len1, len2);
	printf("Minimum Edit Distance is %d\n", tab[len1][len2]);

	printf("\nThe required edits are:-\n");
	output(str1, str2, tab, len1, len2);

	return 0;
}

void init(int tab[MAX][MAX], int len1, int len2) {
	tab[0][0] = 0;

	for (int j = 1; j <= len2; j++) {
		tab[0][j] = j;
	}

	for (int i = 1; i <= len1; i++) {
		tab[i][0] = i;
	}
}

void findMED(string str1, int len1, string str2, int len2, int tab[MAX][MAX]) {
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (str1[i - 1] == str2[j - 1]) {
				tab[i][j] = tab[i - 1][j - 1];
			} else {
				tab[i][j] = min(tab[i - 1][j], tab[i][j - 1], tab[i - 1][j - 1]) + 1;
			}
		}
	}
}

void showMat(int tab[MAX][MAX], int len1, int len2) {
	printf("\nTable is:-\n");
	for (int i = 0; i <= len1; i++) {
		for (int j = 0; j <= len2; j++) {
			printf("%d ", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void output(string str1, string str2, int tab[MAX][MAX], int i, int j) {
	if (i != 0 && j != 0) {
		if (str1[i - 1] == str2[j - 1]) {
			output(str1, str2, tab, i - 1, j - 1);
		} else {
			int minVal = min(tab[i - 1][j], tab[i][j - 1], tab[i - 1][j - 1]);

			if (tab[i - 1][j - 1] == minVal) {
				output(str1, str2, tab, i - 1, j - 1);
				printf("change str1[%d] = %c to str2[%d] = %c\n", (i - 1), str1[i - 1], (j - 1), str2[j - 1]);
			} else if (tab[i - 1][j] == minVal) {
				output(str1, str2, tab, i - 1, j);
				printf("delete str1[%d] = %c (or add %c to str2)\n", (i - 1), str1[i - 1], str1[i - 1]);
			} else {
				output(str1, str2, tab, i, j - 1);
				printf("delete str2[%d] = %c (or add %c to str1)\n", (j - 1), str2[j - 1], str2[j - 1]);
			}
		}
	}
}

