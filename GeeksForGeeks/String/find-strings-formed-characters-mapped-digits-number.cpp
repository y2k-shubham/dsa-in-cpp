// http://www.geeksforgeeks.org/find-strings-formed-characters-mapped-digits-number/

/*
121
22
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
#define COL 3

void createDigVec(int, vector <int> &);
void init(map <int, int> &);
void showStrings(char [][COL], vector <int> &, map <int, int> &, string &, int);

int main() {
	char table[][COL] = {
		{},
		{ 'A', 'B', 'C' },
		{ 'D', 'E', 'F' },
		{ 'G', 'H', 'I' },
		{ 'J', 'K', 'L' },
		{ 'M', 'N', 'O' },
		{ 'P', 'Q', 'R' },
		{ 'S', 'T', 'U' },
		{ 'V', 'W', 'X' },
		{ 'Y', 'Z' }
	};
	vector <int> numV;
	map <int, int> digFirstInd;
	int numI;
	string str;

	cout << "Enter integer:\t";
	cin >> numI;

	createDigVec(numI, numV);
	init(digFirstInd);

	str.resize(numV.size());
	showStrings(table, numV, digFirstInd, str, 0);
}

void createDigVec(int numI, vector <int> &numV) {
	while (numI > 0) {
		int dig = numI % 10;
		numI /= 10;
		numV.push_back(dig);
	}
	reverse(numV.begin(), numV.end());
}

void init(map <int, int> &digFirstInd) {
	for (int i = 1; i <= 9; i++) {
		digFirstInd.insert(make_pair(i, -1));
	}
}

void showStrings(char table[][COL], vector <int> &numV, map <int, int> &digFirstInd, string &str, int ind) {
	if (ind == numV.size()) {
		cout << str << endl;
	} else {
		int dig = numV[ind];

		if (digFirstInd[dig] == -1) {
			int lim = (dig == 9) ? 2 : 3;
			for (int i = 0; i < lim; i++) {
				// first occurrence
				digFirstInd[dig] = ind;
				str[ind] = table[dig][i];

//				printf("at first occurrence of %d, [%d], used %c\n", dig, ind, str[ind]);
//				printf("substituted str[%d] = %c\n", ind, str[i]);

				showStrings(table, numV, digFirstInd, str, ind + 1);
			}
			digFirstInd[dig] = -1;
		} else {
			str[ind] = str[digFirstInd[dig]];
//			printf("at next  occurrence of %d, [%d], used %c\n", dig, ind, str[ind]);
			showStrings(table, numV, digFirstInd, str, ind + 1);
		}
	}
}

