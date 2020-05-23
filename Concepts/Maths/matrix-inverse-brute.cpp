// Time complexity >= O(n ^ 4)
// By gaussian elimination, it comes out to be O(N ^ 3)

/*
3
1 2 3
4 5 6
7 8 9

3
1 0 0
0 1 0
0 0 1

2
1 9
2 7

4
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16

5
4 5 9 7 1
5 2 9 6 4
3 0 8 0 4
2 5 5 6 9
7 1 9 1 7
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(float [MAX][MAX], int& n);
int findDet(float [MAX][MAX], int);
void copyMat(float [MAX][MAX], float [MAX][MAX], int, int, int);
void showMat(float [MAX][MAX], int);

int main() {
	float mat[MAX][MAX];
	float adj[MAX][MAX];
	float det;
	int n;

	input(mat, n);
	showMat(mat, n);

	det = findDet(mat, n);
	printf("value of determinant is %f\n", det);
//	printf("ops = %d\n", ops);

//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			float newMat[MAX][MAX];
//			copyMat(mat, newMat, n, i, j);
//
//			printf("\nafter removing r = %d, c = %d", i, j);
//			showMat(newMat, n - 1);
//		}
//	}

	return 0;
}

void input(float mat[MAX][MAX], int& n) {
	printf("Enter dimension n for nxn matrix:\t");
	scanf("%d", &n);

	printf("Enter nxn matrix:-\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%f", &mat[i][j]);
		}
	}
}

int findDet(float mat[MAX][MAX], int n) {
	if (n == 0) {
		return 0;
	} else if (n == 1) {
		return mat[0][0];
	} else {
		float newMat[MAX][MAX];
		float res = 0.0f;

		for (int j = 0; j < n; j++) {
			copyMat(mat, newMat, n, 0, j);
			float prod = mat[0][j] * findDet(newMat, n - 1);
			res += ((j % 2) == 0) ? (prod) : (-prod);
		}

		return res;
	}
}

void copyMat(float mat[MAX][MAX], float newMat[MAX][MAX], int n, int r, int c) {
	int ii = 0;

	for (int i = 0; i < n; i++) {
		if (i != r) {
			int jj = 0;

			for (int j = 0; j < n; j++) {
				if (j != c) {
					newMat[ii][jj] = mat[i][j];
					jj++;
				}
			}
			ii++;
		}
	}
}

void showMat(float mat[MAX][MAX], int n) {
	printf("\n\t");
	for (int j = 0; j < n; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < n; j++) {
			printf("%2.1f\t", mat[i][j]);
		}
		cout << endl;
	}
}

