
/*
3 3
1 1 1
1 0 1
0 1 0

4 5
1 1 0 1 1
0 1 1 1 1
1 0 1 0 1
0 0 0 1 0

5 6
0 1 1 0 1 1
1 1 1 1 0 0
1 0 1 0 0 1
1 0 0 1 0 0
0 1 0 1 1 1

4 5
1 0 1 0 1
1 1 1 0 1
1 1 1 1 0
0 1 1 1 0

4 4
1 1 0 1
1 1 0 1
1 1 0 1
1 1 0 0

1 1
0

2 2
1 0
0 1

2 2
0 1
0 1

0 0

1 4
1 0 1 0

4 1
0
1
1
1

4 5
1 1 1 0 1
0 1 1 0 1
1 0 1 0 0
1 1 1 1 1

4 5
0 0 1 0 1
0 0 0 0 1
0 0 1 0 1
0 0 1 0 1

4 5
0 1 1 0 1
0 1 1 0 1
0 1 1 0 1
0 1 1 0 1

4 5
1 0 1 0 1
1 0 1 0 1
1 0 1 0 1
1 0 1 0 1

4 5
1 0 1 0 1
0 1 0 1 0
1 0 1 0 1
0 1 0 1 0
1 0 1 0 1

*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 100

void input(int mat[MAX][MAX], int &m, int &n) {
	cin >> m >> n;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> mat[i][j];
		}
	}
}

void findSum(int mat[MAX][MAX], int m, int n, int sum[MAX][MAX]) {
	for (int j = 0; j < n; j++) {
		sum[0][j] = mat[0][j];

		for (int i = 1; i < m; i++) {
			if (mat[i][j] == 0) {
				sum[i][j] = 0;
			} else {
				sum[i][j] += sum[i - 1][j] + 1;
			}
		}
	}
}

void swapCol(int sum[MAX][MAX], int m, int c1, int c2) {
	for (int i = 0; i < m; i++) {
		int tmp = sum[i][c1];
		sum[i][c1] = sum[i][c2];
		sum[i][c2] = tmp;
	}
}

void showMat(int mat[MAX][MAX], int m, int n) {
	cout << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d\t", mat[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void rearrange(int sum[MAX][MAX], int m, int n) {
	int mSize = 0;
	for (int i = 0; i < m; i++) {
		// bubble sort
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n - 1; k++) {
				if (sum[i][k] > sum[i][k + 1]) {
					swapCol(sum, m, k, k + 1);
				}
			}
		}
//		showMat(sum, m, n);

		// find max rect
		for (int j = n - 1; j >= 0; j--) {
//			printf("at [%d][%d] take max with %d\n", i, j, sum[i][j] * (n - 1 - j + 1));
			mSize = max(mSize, sum[i][j] * (n - 1 - j + 1));
		}
	}

	cout << endl << mSize << endl;
}

int main() {
	int mat[MAX][MAX];
	int sum[MAX][MAX];
	int m, n;

	input(mat, m, n);
	findSum(mat, m, n, sum);
//	showMat(sum, m, n);
	rearrange(sum, m, n);

	return 0;
}

