// http://www.geeksforgeeks.org/equal-sum-xor/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
#define MAX 100

void findHoles(int, vector <int> &);
void showVec(int, vector <int>);
void showInts(vector <int>);

int main() {
	int n;
	vector <int> posn;

	cout << "Enter positive integer n:\t";
	cin >> n;

	findHoles(n, posn);

	showVec(n, posn);
	printf("\nPossible no of integers from 0 .. %d satisfying n+i = n^i are %d\n", n, ((int) pow(2, posn.size())));

	showInts(posn);

	return 0;
}

void findHoles(int n, vector <int> &posn) {
	int lim = (int) floor(log2(n));

	for (int i = 0; i <= lim; i++) {
		if ((n & (1 << i)) == 0) {
			posn.push_back(i);
		}
	}
}

void showVec(int n, vector <int> posn) {
	if (posn.empty()) {
		return;
	}

	int lim = (int) floor(log2(n));

	printf("\nHoles in the integer %d are:-\n", n);
	for (int i = lim + 1; i >= 0; i--) {
		if ((n & (1 << i)) != 0) {
			cout << "1";
		} else {
			cout << "0";
		}
	}
	cout << endl;

	for (int i = lim + 1; i >= 0; i--) {
		if (i == posn.back()) {
			cout << "^";
			posn.pop_back();
		} else {
			cout << " ";
		}
	}
	cout << endl;
}

void showInts(vector <int> posn) {
	int lim = (int) pow(2, posn.size());

	cout << "\nThe integers satisfying the property are:-\n";
	cout << "0\t";
	for (int i = 1; i <= lim; i++) {
		int num = 0;
		int lim2 = (int) ceil(log2(i));

		for (int j = 0; j < posn.size() && j <= lim2; j++) {
			if ((i & (1 << j)) != 0) {
				num = num | ((int) pow(2, posn[j]));
			}
		}

		if (num > 0) {
			cout << num << "\t";
		}
	}
	cout << endl;
}

