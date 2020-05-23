/*
Input:
5 5
0 0 0 0 1
1 0 1 1 1
1 0 1 0 1
1 1 1 1 1
0 0 1 1 1
Output:
3 x 3

Input:
7 6
0 0 1 1 1 1
1 1 1 1 0 1
1 1 0 1 1 1
0 1 1 1 0 1
0 0 0 1 1 1
1 0 1 1 0 1
0 1 0 1 1 0
Output:
3x3

Input:
7 6
0 0 1 1 1 1
1 1 1 1 0 1
1 1 0 1 1 1
0 1 1 1 1 1
0 1 0 0 1 1
1 1 1 0 1 1
0 1 1 1 1 0
Output:
4x4

Input:
7 6
0 0 1 0 1 1
1 0 1 1 0 1
1 1 0 1 1 1
0 1 1 1 0 1
0 1 0 0 1 0
1 1 0 1 1 1
0 1 1 1 1 0
Output:
2 x 2
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX][MAX], int &, int &);
void calc(int [MAX][MAX], int, int, int [MAX][MAX], int [MAX][MAX], int &, int &, int &);
void output(int [MAX][MAX], int, int, int, int, int);

int main() {
	int rows, cols;
	int mat[MAX][MAX];
	int vCnt[MAX][MAX];
	int hCnt[MAX][MAX];
	int mSize;
	int mIndBot, mIndRit;

	input(mat, rows, cols);

	memset(vCnt, 0, sizeof(int) * (rows + 1) * (cols + 1));
	memset(hCnt, 0, sizeof(int) * (rows + 1) * (cols + 1));

	calc(mat, rows, cols, vCnt, hCnt, mSize, mIndBot, mIndRit);
	output(mat, rows, cols, mSize, mIndBot, mIndRit);

	return 0;
}

void input(int mat[MAX][MAX], int &rows, int &cols) {
	printf("Enter dimen as (rows, cols):\t");
	scanf("%d%d", &rows, &cols);

	printf("Enter the table:-\n");
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void calc(int mat[MAX][MAX], int rows, int cols, int vCnt[MAX][MAX], int hCnt[MAX][MAX], int &mSize, int &mIndBot, int &mIndRit) {
	mSize = 0;

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			if (mat[i][j] == 0) {
				vCnt[i][j] = hCnt[i][j] = 0;
			} else {
				vCnt[i][j] = vCnt[i - 1][j] + 1;
				hCnt[i][j] = hCnt[i][j - 1] + 1;

				int minCnt = min(hCnt[i][j], vCnt[i][j]);
				while (minCnt > mSize) {
					if ((minCnt > mSize) && (min(hCnt[i - minCnt + 1][j], vCnt[i][j - minCnt + 1]) >= minCnt)) {
						mSize = minCnt;
						mIndBot = i;
						mIndRit = j;
						break;
					} else {
						minCnt--;
					}
				}
			}
		}
	}
}

void output(int mat[MAX][MAX], int rows, int cols, int mSize, int mIndBot, int mIndRit) {
	printf("\nThe size of max square bounded by 1's is:\t%d X %d\n", mSize, mSize);

	int mIndTop, mIndLft;

	mIndTop = mIndBot - mSize + 1;
	mIndLft = mIndRit - mSize + 1;

	printf("The highlighted sub-matrix is:-\n");
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			if ((((i == mIndTop) || (i == mIndBot)) && ((mIndLft <= j) && (j <= mIndRit))) ||
					(((j == mIndLft) || (j == mIndRit)) && ((mIndTop <= i) && (i <= mIndBot)))) {
				printf("I ");
			} else if (mat[i][j] == 1) {
				printf("| ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
	}
}
