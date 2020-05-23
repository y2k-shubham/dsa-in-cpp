// http://www.geeksforgeeks.org/given-matrix-o-x-find-largest-subsquare-surrounded-x/
/*

5 5
X O X X X
X X X X X
X X O X O
X X X X X
X X X O O

5 6
X O X X X X
X O X X O X
X X X O O X
X X X X X X
X X X O X O

*/

#include <cstdio>
#include <iostream>

using namespace std;

#define MAX 100
#define minVal(a, b) ((a < b) ? a : b)

void input(char [MAX][MAX], int&, int&);
void calcTab(char [MAX][MAX], int, int, int [MAX][MAX], int [MAX][MAX]);
void findMaxSqr(int [MAX][MAX], int [MAX][MAX], int, int, int&, int&, int&);
void showMaxSqr(char [MAX][MAX], int, int, int);
void showMat(char [MAX][MAX], int, int, const char *);
void showMat(int [MAX][MAX], int, int, const char *);

int main() {
	int m, n;
	char mat[MAX][MAX];
	int vTab[MAX][MAX];
	int hTab[MAX][MAX];
	int maxDim, maxIndRow, maxIndCol;

	input(mat, m, n);
	showMat(mat, m, n, "mat");

	calcTab(mat, m, n, vTab, hTab);
	showMat(hTab, m, n, "hTab");
	showMat(vTab, m, n, "vTab");

	findMaxSqr(vTab, hTab, m, n, maxDim, maxIndRow, maxIndCol);
	showMaxSqr(mat, maxDim, maxIndRow - maxDim + 1, maxIndCol - maxDim + 1);

	return 0;
}

void input(char mat[MAX][MAX], int& m, int& n) {
	printf("Enter dimensions of matrix (m, n):\t");
	scanf("%d%d", &m, &n);
	getchar();

	printf("Enter the matrix:-\n");
	for (int i = 0; i < m; i++) {
		scanf("%c", &mat[i][0]);
		for (int j = 1; j < n; j++) {
			scanf(" %c", &mat[i][j]);
		}
		getc(stdin);
	}
}

void calcTab(char mat[MAX][MAX], int m, int n, int vTab[MAX][MAX], int hTab[MAX][MAX]) {
	for (int i = 0; i < m; i++) {
		if (mat[i][0] == 'X') {
			hTab[i][0] = 1;
		} else {
			hTab[i][0] = 0;
		}
	}
	for (int i = 0; i < m; i++) {
		for (int j = 1; j < n; j++) {
			if (mat[i][j] == 'X') {
				hTab[i][j] = hTab[i][j - 1] + 1;
			} else {
				hTab[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < n; j++) {
		if (mat[0][j] == 'X') {
			vTab[0][j] = 1;
		} else {
			vTab[0][j] = 0;
		}
	}
	for (int i = 1; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] == 'X') {
				vTab[i][j] = vTab[i - 1][j] + 1;
			} else {
				vTab[i][j] = 0;
			}
		}
	}
}

void findMaxSqr(int vTab[MAX][MAX], int hTab[MAX][MAX], int m, int n, int& maxDim, int& maxIndRow, int& maxIndCol) {
	maxDim = 0;

	for (int i = m - 1; i > 0; i--) {
		for (int j = n - 1; j > 0; j--) {
			int smaller = minVal(hTab[i][j], vTab[i][j]);

			while (smaller > maxDim) {
				if (smaller == 0 || (hTab[i - smaller + 1][j] >= smaller && vTab[i][j - smaller + 1] >= smaller)) {
					break;
				} else {
					smaller--;
				}
			}

			if (smaller > maxDim) {
				maxDim = smaller;
				maxIndRow = i;
				maxIndCol = j;
			}
		}
	}
}

void showMaxSqr(char mat[MAX][MAX], int maxDim, int rowStart, int colStart) {
	printf("\nThe largest square surrounded by X's is:-\n");
	for (int i = rowStart; i < rowStart + maxDim; i++) {
		for (int j = colStart; j < colStart + maxDim; j++) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
}

void showMat(char mat[MAX][MAX], int row, int col, const char * name) {
	printf("\nThe matrix %s is:-\n", name);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%c ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void showMat(int mat[MAX][MAX], int row, int col, const char * name) {
	printf("\nThe matrix %s is:-\n", name);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
