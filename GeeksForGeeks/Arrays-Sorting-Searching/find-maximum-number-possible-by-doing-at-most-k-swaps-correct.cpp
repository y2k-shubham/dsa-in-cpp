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
void findMaxNum(string, int, string &);

int main() {
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		string S, maxS;
		int K;

		cin >> K >> S;
		maxS = S;

		findMaxNum(S, K, maxS);

		cout << maxS << endl;
	}

	return 0;
}

void swap(string &S, int pos_1, int pos_2) {
	char c = S[pos_1];
	S[pos_1] = S[pos_2];
	S[pos_2] = c;
}

void findMaxNum(string S, int K, string &maxS) {
	if (K > 0) {
		for (int i = 0; i < S.length(); i++) {
			for (int j = i + 1; j < S.length(); j++) {
				if (S[i] < S[j]) {
					swap(S, i, j);

					if (S.compare(maxS) > 0) {
						maxS = S;
					}
					findMaxNum(S, K - 1, maxS);

					swap(S, i, j);
				}
			}
		}
	}
}

