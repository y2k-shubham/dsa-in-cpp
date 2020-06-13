// TusharRoy

/*
iamace
i	am	ace	a	mac	-1

iamnmac
i	am	ace	a	mac	-1
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <unordered_set>

using namespace std;
#define MAX 100

void input(string &, unordered_set <string>&);
bool fillTab(unordered_set <string>, string, int, pair <bool, int> [MAX][MAX]);
void showTab(pair <bool, int> [MAX][MAX], string, int);
void showSet(unordered_set <string>);
void showSoln(string, pair <bool, int> [MAX][MAX], int, int);

int main() {
	string str;
	int len;
	unordered_set <string> dict;
	pair <bool, int> tab[MAX][MAX];

	input(str, dict);
	len = str.length();
	showSet(dict);

	bool res = fillTab(dict, str, len, tab);
	showTab(tab, str, len);

	if (res) {
		cout << "Given string can be split into valid words:-\n";
		showSoln(str, tab, 0, len - 1);
		cout << endl;
	} else {
		cout << "Given string can not be split\n";
	}

	return 0;
}

void input(string& str, unordered_set <string>& dict) {
	string word;

	cout << "Enter string to be split:\t";
	cin >> str;

	cout << "Enter dictionary of words:-\n(-1 to terminate)\n";
	cin >> word;

	while (word.compare("-1") != 0) {
		dict.insert(word);
		cin >> word;
	}
}

bool fillTab(unordered_set <string> dict, string str, int len, pair <bool, int> tab[MAX][MAX]) {
	const int rStart = 0;
	int cStart;
	int siz;

	for (siz = 1; siz <= len; siz++) {
		cStart = siz - 1;

		int i = rStart;
		int j = cStart;
		while (j < len) {
			tab[i][j] = make_pair(false, -1);

			if (dict.find(str.substr(i, (j - i + 1))) != dict.end()) {
				// substring present in dictionary
				tab[i][j].first = true;
				tab[i][j].second = -1;
			} else {
				for (int k = i; k < j; k++) {
					if (tab[i][k].first == true && tab[k + 1][j].first == true) {
						tab[i][j].first = true;
						tab[i][j].second = k;
						break;
					}
				}
			}

			i++;
			j++;
		}
	}

	return tab[0][len - 1].first;
}

void showSet(unordered_set <string> dict) {
	printf("\nWords of dictionary are:-\n");
	for (unordered_set <string>::iterator it = dict.begin(); it != dict.end(); it++) {
		cout << *it << "\t";
	}
	cout << endl << endl;
}

void showTab(pair <bool, int> tab[MAX][MAX], string str, int len) {
	printf("\nTable is:-\n");

	cout << "\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << "\n";

	cout << "\t";
	for (int i = 0; i < len; i++) {
		cout << str.at(i) << "\t";
	}
	cout << "\n";

	for (int i = 0; i < len; i++) {
		int j;

		printf("[%d] %c\t", i, str[i]);

		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < len; j++) {
			if (tab[i][j].first == true) {
				printf("(T, %d)\t", tab[i][j].second);
			} else {
				printf("(F)\t");
			}
		}

		cout << endl;
	}
	cout << endl;
}

void showSoln(string str, pair <bool, int> tab[MAX][MAX], int i, int j) {
	if (tab[i][j].second == -1) {
		cout << str.substr(i, (j - i + 1)) << " ";
	} else {
		int splitInd = tab[i][j].second;

		showSoln(str, tab, i, splitInd);
		showSoln(str, tab, splitInd + 1, j);
	}
}

