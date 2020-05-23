// given an integer, find the smallest integer greater than or equal to it which
// is comprised entirely of 2's or 5's (or both)

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <int> getDigVec(int);
int getNum(vector <int>);
void showVec(vector <int>);
void findNum(vector <int> &);
void fillVec(vector <int> &, int, int);

int main() {
	int n;

	cout << "Enter an integer:\t";
	cin >> n;

	vector <int> nDig = getDigVec(n);
	showVec(nDig);

	findNum(nDig);
	showVec(nDig);

	printf("\nSmallest number >= %d comprised of 2's and 5's only is %d\n", n, getNum(nDig));

	return 0;
}

vector <int> getDigVec(int n) {
	vector <int> digVec;

	while (n > 0) {
		digVec.push_back(n % 10);
		n /= 10;
	}
	reverse(digVec.begin(), digVec.end());

	return digVec;
}

int getNum(vector <int> digVec) {
	int n = 0;

	for (int i = 0; i < digVec.size(); i++) {
		n *= 10;
		n += digVec[i];
	}

	return n;
}

void showVec(vector <int> vec) {
	cout << "\nThe vector is:-\n";

	cout << "Ind:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << "\t";
	}
	cout << endl;
}

void findNum(vector <int> &nDig) {
	int prev2Ind = -1;

	for (int i = 0; i < nDig.size(); i++) {
		if (nDig[i] < 2) {
			nDig[i] = 2;
			fillVec(nDig, i + 1, 2);
			break;
		} else if (nDig[i] == 2) {
			prev2Ind = i;
		} else if (nDig[i] == 3 || nDig[i] == 4) {
			nDig[i] = 5;
			fillVec(nDig, i + 1, 2);
			break;
		} else if (nDig[i] == 5) {
			// do nothing
		} else {
			if (prev2Ind >= 0) {
				nDig[prev2Ind] = 5;
				fillVec(nDig, prev2Ind + 1, 2);
				break;
			} else {
				nDig.push_back(2);
				fillVec(nDig, 0, 2);
				break;
			}
		}
	}
}

void fillVec(vector <int> &vec, int startInd, int fillVal) {
	for (int i = startInd; i < vec.size(); i++) {
		vec[i] = fillVal;
	}
}

