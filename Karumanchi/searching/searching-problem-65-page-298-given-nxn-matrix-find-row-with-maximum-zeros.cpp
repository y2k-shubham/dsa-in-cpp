// Karumanchi, Searching, problem 65, page 298

/*
Given a nxn matrix where each row contains sequence of 0s followed by sequence of 1s, find the
row that contains maximum no of 1s
*/

/*
5
0 0 0 0 0
0 0 1 1 1
0 0 0 1 1
0 1 1 1 1
0 0 0 0 0

5
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

5
0 1 1 1 1
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

5
0 1 1 1 1
0 0 0 0 0
0 0 0 0 0
1 1 1 1 1
0 0 0 0 0
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX][MAX], int &);
void findMax1Row(int [MAX][MAX], int);

int main() {
	int mat[MAX][MAX], n;

	input(mat, n);
	findMax1Row(mat, n);

	return 0;
}

void input(int mat[MAX][MAX], int &n) {
	printf("Enter dimension of nxn matrix.\tn = ");
	cin >> n;

	printf("Enter %dx%d matrix:-\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> mat[i][j];
		}
	}
}

void findMax1Row(int mat[MAX][MAX], int n) {
	int mRowCount, mRowInd;
	int i, j;

	mRowCount = -1;
	for (i = 0, j = n - 1; i < n && j >= 0; ) {
		if (mat[i][j] == 1) {
			int crrRowCount = (n - 1) - j + 1;
			if (crrRowCount > mRowCount) {
				mRowCount = crrRowCount;
				mRowInd = i;
			}
		}

		if (j == 0) {
			break;
		}

		if (j > 0 && mat[i][j - 1] == 1) {
			j--;
		} else {
			i++;
		}
	}

	if (mRowCount < 0) {
		printf("\nThere are no 1's in the matrix\n");
	} else {
		printf("\nRow %d has maximum 1's equal to %d\n", mRowInd, mRowCount);
	}
}

