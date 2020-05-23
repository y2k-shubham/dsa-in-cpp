/*
000
111
0
1
10100010
01101011
00101111001
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

void input(string&);
void findSubString(string, int&, int&);
void output(string, int, int);
void flip(string);

int main() {
	string str;

	input(str);

	int lInd, rInd;
	findSubString(str, lInd, rInd);

	output(str, lInd, rInd);
	flip(str);

	return 0;
}

void input(string& str) {
	printf("Enter a binary string:\t");
	cin >> str;
}

void findSubString(string str, int& mlInd, int& mrInd) {
	int ctr0, ctr1;
	int clInd, crInd;
	int mDiff;

	ctr0 = ctr1 = 0;
	clInd = crInd = -1;
	mDiff = 0;
	mlInd = mrInd = -1;

	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '0') {
			ctr0++;
		} else {
			ctr1++;
		}

		if (ctr0 <= ctr1) {
			ctr0 = ctr1 = 0;
			clInd = crInd = -1;
		} else {
			if (clInd < 0) {
				clInd = i;
			}
			crInd = i;

			int diff = ctr0 - ctr1;
			if (diff > mDiff) {
				mDiff = diff;
				mlInd = clInd;
				mrInd = crInd;
			}
		}
	}
}

void output(string str, int lInd, int rInd) {
	printf("\nSubstring that needs to be flipped is str[%d .. %d]\n", lInd, rInd);
}

void flip(string A) {
	int n = A.length();
	int i = 0;
	int ctr = 0;
	int ctrm = 0;
	int l,r;
	int lr,rr;

	lr = rr = -1;
	l = r = -1;
	while(i < n) {
		if(ctr < 0) {
			ctr = 0;
		}

		if(A[i] == '0') {
			ctr++;
			r = i;

			if(ctr == 1) {
				l = i;
			}

			if(ctr > ctrm) {
				lr = l;
				rr = r;
				ctrm = ctr;
			}
		} else
			ctr--;

		i++;
	}

	printf("l = %d, r = %d\n", lr,rr);
}

