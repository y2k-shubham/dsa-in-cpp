/*
7
8 1 3 7 4 2 9

4
3 1 5 8
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <utility>
#include <vector>
#include <stack>

using namespace std;

struct data {
	int optSum;
	int splInd;
};

void input(vector <int> &);
void init(vector <vector <data> > &, vector <int>);
void showVec(vector <int>, const char *);
void showTab(vector <vector <data> >, vector <int>, const char *);
void output(vector <vector <data> >, vector <int>, int, int);
void calc(vector <int> seq, vector <vector <data> > &tab);

int main() {
	vector <int> seq;
	vector <vector <data> > tab;

	input(seq);
	init(tab, seq);

	showVec(seq, "sequence of balloons");
	showTab(tab, seq, "table after initialization");

	calc(seq, tab);
	showTab(tab, seq, "table after calculation");

	printf("\nMaximum possible profit is %d\n", (tab[0][seq.size() - 1].optSum + (seq[0] * seq[seq.size() - 1]) + max(seq[0], seq[seq.size() - 1])));
//	printf("Bursting strategy is:-\n");
//	output(tab, seq, 0, seq.size() - 1);

	return 0;
}

void input(vector <int> &seq) {
	int n;

	cout << "Enter no of balloons:\t";
	cin >> n;

	cout << "Enter sequence of balloons:-\n";
	for (int i = 0; i < n; i++) {
		int val;
		cin >> val;
		seq.push_back(val);
	}
}

void init(vector <vector <data> > &tab, vector <int> seq) {
	int n = seq.size();

	for (int i = 1; i <= n; i++) {
		vector <data> tmp (n);
		tab.push_back(tmp);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tab[i][j].optSum = 0;
			tab[i][j].splInd = -1;
		}
	}

	for (int i = 2; i < n; i++) {
		tab[i - 2][i].optSum = seq[i - 2] * seq[i - 1] * seq[i];
		tab[i - 2][i].splInd = -1;
	}
}

void showVec(vector <int> seq, const char * msg) {
	printf("\n%s is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < seq.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < seq.size(); i++) {
		printf("%d\t", seq[i]);
	}
	cout << endl;
}

void showTab(vector <vector <data> > tab, vector <int> seq, const char * msg) {
	int n = seq.size();
	printf("\nThe %s is:-\n", msg);

	printf("\t");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", seq[i]);
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		printf("[%d]\t", seq[i]);

		for (int j = 0; j < n; j++) {
			printf("%d,%d\t", tab[i][j].splInd, tab[i][j].optSum);
		}
		cout << endl;
	}
	cout << endl;
}

void output(vector <vector <data> > tab, vector <int> seq, int lo, int hi) {
	if (hi - lo <= 2) {
		printf("(%d %d %d)", seq[lo], seq[lo + 1], seq[hi]);
	} else {
		printf("(");
		output(tab, seq, lo, tab[lo][hi].splInd);
		output(tab, seq, tab[lo][hi].splInd, hi);
		printf(")");
	}
}

void calc(vector <int> seq, vector <vector <data> > &tab) {
	int n = seq.size();

	for (int len = 4; len <= n; len++) {
		int cLo = len - 1;
		int cHi = n - 1;

		int i, j;
		for (i = 0, j = cLo; j <= cHi; i++, j++) {
			int maxVal = -1;
			int maxInd;

			for (int k = i + 1; k < j; k++) {
				int crrVal = tab[i][k].optSum + tab[k][j].optSum + (seq[i] * seq[k] * seq[j]);

				if (crrVal > maxVal) {
					maxVal = crrVal;
					maxInd = k;
				}
			}

			tab[i][j].optSum = maxVal;
			tab[i][j].splInd = maxInd;
		}
	}
}

