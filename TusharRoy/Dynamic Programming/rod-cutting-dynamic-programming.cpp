// TUshar Roy

/*
5
4
1 2		2 5		3 7		4 8
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>

using namespace std;

void input(int &, vector <pair <int, int> > &, int &);
void init(vector <vector <int> > &, int, int);
void calc(int, vector <pair <int, int> >, int, vector <vector <int> > &);
void output(int, vector <pair <int, int> >, int, vector <vector <int> >);

int main() {
	int actLen, lenCtr;
	vector <pair <int, int> > lenList;
	vector <vector <int> > tab;

	input(actLen, lenList, lenCtr);
	init(tab, lenCtr, actLen);
	calc(actLen, lenList, lenCtr, tab);
	output(actLen, lenList, lenCtr, tab);

	return 0;
}

void input(int &actLen, vector <pair <int, int> > &lenList, int &lenCtr) {
	cout << "Enter actual length of rod:\t";
	cin >> actLen;

	cout << "Enter no of cut-sizes:\t";
	cin >> lenCtr;

	lenList.push_back(make_pair(-1, -1));
	cout << "Enter list of cut-size and profit:-\n";
	for (int i = 0; i < lenCtr; i++) {
		int len, prof;
		cin >> len >> prof;

		lenList.push_back(make_pair(len, prof));
	}
}

void init(vector <vector <int> > &tab, int lenCtr, int actLen) {
	for (int i = 0; i <= lenCtr; i++) {
		vector <int> vec ({0});
		tab.push_back(vec);
	}

	for (int j = 1; j <= actLen; j++) {
		tab[0].push_back(0);
	}
}

void calc(int actLen, vector <pair <int, int> > lenList, int lenCtr, vector <vector <int> > &tab) {
	for (int i = 1; i <= lenCtr; i++) {
		int j = 0;
		while (j < lenList[i].first) {
			tab[i].push_back(tab[i - 1][j]);
			j++;
		}

		while (j <= actLen) {
			tab[i].push_back(max(tab[i - 1][j], tab[i][j - lenList[i].first] + lenList[i].second));
			j++;
		}
	}
}

void output(int actLen, vector <pair <int, int> > lenList, int lenCtr, vector <vector <int> > tab) {
	cout << "\nMaximum possible profit is:\t" << tab[lenCtr][actLen];
	cout << "\nCut-lengths used are:-\n";

	int i, j;
	for (i = lenCtr, j = actLen; j > 0; ) {
		if (tab[i][j] == tab[i - 1][j]) {
			i--;
		} else {
			cout << lenList[i].first << "\t";
			j -= lenList[i].first;
		}
	}
	cout << endl;
}

