// Karumanchi, DP, problem 37, page 409
// http://www.geeksforgeeks.org/count-distinct-occurrences-as-a-subsequence/

/*
   my interpretation of the problem: count no of occurrences of a given subsequence
   in the given string
*/

/*
mapabqacbbapcrbpbcmbbjcs
abbcb

baramararac
ara

mississippis
is
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 100

void input(string &, string &);
void init(int [MAX][MAX], int, int, string, string);
void showTab(int [MAX][MAX], int, int, string, string, const char *);
void fillTab(int [MAX][MAX], int, int, string, string);

int main() {
	string str, sub;
	int strLen, subLen;
	int tab[MAX][MAX];

	input(str, sub);
	strLen = str.length() - 1;
	subLen = sub.length() - 1;

	init(tab, strLen, subLen, str, sub);
	showTab(tab, strLen, subLen, str, sub, "tab[][] after initialization");

	fillTab(tab, strLen, subLen, str, sub);
	showTab(tab, strLen, subLen, str, sub, "tab[][] after computation");

	return 0;
}

void input(string &str, string &sub) {
	cout << "Enter original string:\t";
	cin >> str;
	str = '_' + str;

	cout << "Enter subsequence to be searched:\t";
	cin >> sub;
	sub = '_' + sub;
}

void init(int tab[MAX][MAX], int strLen, int subLen, string str, string sub) {
	memset(tab, 0, (strLen + 1) * (subLen + 1) * sizeof(int));

	for (int j = 1; j <= strLen; j++) {
		tab[1][j] = tab[1][j - 1];
		if (sub[1] == str[j]) {
			tab[1][j]++;
		}
	}
}

void showTab(int tab[MAX][MAX], int strLen, int subLen, string str, string sub, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "\t";
	for (int i = 1; i <= strLen; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "\t";
	for (int i = 1; i <= strLen; i++) {
		printf("%c\t", str[i]);
	}
	cout << endl;

	for (int i = 1; i <= subLen; i++) {
		printf("[%d] %c\t", i, sub[i]);
		for (int j = 1; j <= strLen; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void fillTab(int tab[MAX][MAX], int strLen, int subLen, string str, string sub) {
	for (int i = 2; i <= subLen; i++) {
		for (int j = 1; j <= strLen; j++) {
			if (sub[i] == str[j]) {
				tab[i][j] = min(tab[i - 1][j - 1],  tab[i][j - 1] + 1);
			} else {
				tab[i][j] = tab[i][j - 1];
			}
		}
	}
}


