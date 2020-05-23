// WRONG CODE

// http://www.geeksforgeeks.org/find-maximum-number-possible-by-doing-at-most-k-swaps/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1044

/*
Input
3
4 1234567
3 3435335
2 1034

Output
7654321
5543333
4301

Input
1
4 61892795431

Output
99876125431
*/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void swap(string &, int, int);
void insertionSort(string &, int);

int main() {
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		string S;
		int K;

		cin >> K >> S;
		insertionSort(S, K);
		cout << S << endl;
	}

	return 0;
}

void swap(string &S, int pos_1, int pos_2) {
	char c = S[pos_1];
	S[pos_1] = S[pos_2];
	S[pos_2] = c;
}

void insertionSort(string &S, int K) {
	char maxDig, crrDig;
	int maxDigInd, crrDigInd;

	crrDigInd = 0;
	for (int i = 1; crrDigInd < S.length() && i <= K; crrDigInd++) {
		crrDig = S[crrDigInd];

		if (crrDig == '9') {
			continue;
		} else {
			// find index of greatest digit of number to the right of crrDig
			maxDig = '0';
			for (int j = S.length() - 1; j > crrDigInd; j--) {
				if (S.at(j) > maxDig) {
					maxDig = S[j];
					maxDigInd = j;
				}

				if (maxDig == '9') {
					break;
				}
			}

			// swap crrDig and maxDig, if doing do makes number bigger
			if (maxDig > crrDig) {
				swap(S, crrDigInd, maxDigInd);
				i++;
			}
		}
	}
}

