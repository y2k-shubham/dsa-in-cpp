// http://www.geeksforgeeks.org/dynamic-programming-set-28-minimum-insertions-to-form-a-palindrome/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;
#define MAX 100
#define minVal(a, b) ((a < b) ? a : b)

int findMinCount(string, int [MAX][MAX]);

int main() {
	string str;
	int mCharCount[MAX][MAX];
	int T;

	scanf("%d", &T);
	while (T--) {
		//printf("Enter a string:\t");
		cin >> str;

		memset(mCharCount, 0, sizeof(mCharCount));
		//printf("Min no of chars needed is %d\n", findMinCount(str, mCharCount));
		cout << findMinCount(str, mCharCount) << endl;
	}

	return 0;
}

int findMinCount(string str, int mCharCount[MAX][MAX]) {
	int gap, i, j, n;

	n = str.length();
	for (gap = 1; gap < n; gap++) {
		for (i = 0, j = gap; j < n; i++, j++) {
			if (str.at(i) == str.at(j)) {
				mCharCount[i][j] += 0 + mCharCount[i + 1][j - 1];
			} else {
				mCharCount[i][j] += 1 + minVal(mCharCount[i + 1][j], mCharCount[i][j - 1]);
			}
		}
	}

	return mCharCount[0][n - 1];
}
