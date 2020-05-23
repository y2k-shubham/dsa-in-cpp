// http://www.geeksforgeeks.org/find-maximum-dot-product-two-arrays-insertion-0s/
// Directi

/*
3
3 6 7
5
2 3 1 7 8

3
3 6 7
5
2 3 1 7 4

3
4 5 1
6
1 2 3 6 1 4
*/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

void input(vector <int>&, const char *);
void showVec(vector <int>, const char *);
void initTab(vector <vector <int> >&, int, int);
void showTab(vector <vector <int> >, vector <int>, vector <int>, const char *);
void fillTab(vector <int>, vector <int>, vector <vector <int> >&);

int main() {
	vector <int> vecSmall, vecBig;
	vector <vector <int> > tab;

	input(vecSmall, "small");
	input(vecBig, "big");
	showVec(vecSmall, "vecSmall");
	showVec(vecBig, "vecBig");

	initTab(tab, vecSmall.size() + 1, vecBig.size() + 1);
	showTab(tab, vecSmall, vecBig, "before filling");

	fillTab(vecSmall, vecBig, tab);
	showTab(tab, vecSmall, vecBig, "after filling");

	return 0;
}

void input(vector <int>& vec, const char * name) {
	int len;

	printf("Enter size of %s vector:\t", name);
	cin >> len;
	vec.reserve(len);

	printf("Enter elements of %s vector:-\n", name);
	for (int i = 0; i < len; i++) {
		int ele;
		cin >> ele;

		vec.push_back(ele);
	}
}

void showVec(vector <int> vec, const char * name) {
	printf("\n%s vector is:-\n", name);

	printf("Ind:\t");
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 0; i < vec.size(); i++) {
		printf("%d\t", vec[i]);
	}
	cout << endl;
}

void initTab(vector <vector <int> >& tab, int row, int col) {
	tab.reserve(row);
	for (int i = 0; i < row; i++) {
		vector <int> vec;
		vec.resize(col);

		tab.push_back(vec);
	}

	for (int i = 0; i < row; i++) {
		tab[i][0] = 0;
	}

	for (int j = 0; j < col; j++) {
		tab[0][j] = 0;
	}
}

void showTab(vector <vector <int> > tab, vector <int> vecSmall, vector <int> vecBig, const char * when) {
	int row = tab.size();
	int col = tab[0].size();

	printf("\n%s, tab[][] is:-\n", when);
	
	printf("\t");
	for (int j = 0; j < col; j++) {
		if (j == 0) {
			printf("_\t");
		} else {
			printf("[%d]\t", vecBig[j - 1]);
		}
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		if (i == 0) {
			printf("_\t");
		} else {
			printf("[%d]\t", vecSmall[i - 1]);
		}

		for (int j = 0; j < col; j++) {
			if (j < i) {
				cout << "\t";
			} else {
				cout << tab[i][j] << "\t";
			}
		}
		cout << endl;
	}
}

void fillTab(vector <int> vecSmall, vector <int> vecBig, vector <vector <int> >& tab) {
	for (int i = 1; i <= vecSmall.size(); i++) {
		int j = i;
		tab[i][j] = tab[i - 1][j - 1] + (vecSmall[i - 1] * vecBig[j - 1]);

		for (j++; j <= vecBig.size(); j++) {
			tab[i][j] = max((tab[i - 1][j - 1] + (vecSmall[i - 1] * vecBig[j - 1])), tab[i][j - 1]);
		}
	}
}

