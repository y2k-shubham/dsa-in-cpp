/*
Input:
4 4
9 6 5 2
8 7 6 5
7 3 1 6
1 1 1 7
Output:
9 8 7 6 5 6 7

Input:
4 4
19 6 7 2
 8 5 6 5
 7 3 1 6
 1 1 1 7
Output:
9 8 7 6 5 6 7

*/

#include <cstdio>
#include <iostream>
#include <stack>
#include <climits>

using namespace std;

#define MAX 100
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

void init(int [MAX][MAX], int, int);
void input(int [MAX][MAX], int &, int &);
void calc(int [MAX][MAX], int, int, int [MAX][MAX], int &, int &, int&);
void update(int [MAX][MAX], int, int, int &, int &, int &);
void showTable(int [MAX][MAX], int, int, const char *);
void output(int [MAX][MAX], int [MAX][MAX], int, int, int);
int abs(int);

int main() {
	int rows, cols;
	int maxLen, maxLenIndCol, maxLenIndRow;
	int mat[MAX][MAX];
	int tab[MAX][MAX];

	input(mat, rows, cols);

	init(tab, rows, cols);
	//showTable(tab, rows, cols, "tab table before calc");

	calc(mat, rows, cols, tab, maxLen, maxLenIndCol, maxLenIndRow);
	showTable(tab, rows, cols, "tab table after calc");

	output(mat, tab, maxLen, maxLenIndCol, maxLenIndRow);

	return 0;
}

void init(int tab[MAX][MAX], int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tab[i][j] = 1;
		}
	}
}

void input(int mat[MAX][MAX], int &rows, int &cols) {
	printf("Enter dimensions as (rows, cols):\t");
	scanf("%d%d", &rows, &cols);

	printf("Enter the elements of matrix:-\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void calc(int mat[MAX][MAX], int rows, int cols, int tab[MAX][MAX], int &maxLen, int &maxLenIndCol, int &maxLenIndRow) {
	maxLen = INT_MIN;

	// fill first row
	for (int j = 1; j < cols; j++) {
		if (abs(mat[0][j] - mat[0][j - 1]) == 1) {
			tab[0][j] = tab[0][j - 1] + 1;
			update(tab, 0, j, maxLen, maxLenIndCol, maxLenIndRow);
		}
	}

	for (int i = 1; i < rows; i++) {
		// fill first element of a row
		if (abs(mat[i][0] - mat[i - 1][0]) == 1) {
			tab[i][0] = tab[i - 1][0] + 1;
			update(tab, i, 0, maxLen, maxLenIndCol, maxLenIndRow);
		}

		// fill remaining elements of a row
		for (int j = 1; j < cols; j++) {
			if (abs(mat[i][j] - mat[i - 1][j]) == 1) {
				tab[i][j] = max(tab[i][j], tab[i - 1][j] + 1);
				update(tab, i, j, maxLen, maxLenIndCol, maxLenIndRow);
			}

			if (abs(mat[i][j] - mat[i][j - 1]) == 1) {
				tab[i][j] = max(tab[i][j], tab[i][j - 1] + 1);
				update(tab, i, j, maxLen, maxLenIndCol, maxLenIndRow);
			}
		}
	}
}

int abs(int a) {
	if (a < 0) {
		return -a;
	} else {
		return a;
	}
}

void update(int tab[MAX][MAX], int row, int col, int &maxLen, int &maxLenIndCol, int &maxLenIndRow) {
	if (tab[row][col] > maxLen) {
		maxLen = tab[row][col];
		maxLenIndCol = col;
		maxLenIndRow = row;
	}
}

void showTable(int arr[MAX][MAX], int rows, int cols, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void output(int mat[MAX][MAX], int tab[MAX][MAX], int maxLen, int maxLenIndCol, int maxLenIndRow) {
	int i, j;
	int ctr;
	stack <int> stk;

	for (i = maxLenIndRow, j = maxLenIndCol, ctr = 1; ctr <= maxLen; ctr++) {
		stk.push(mat[i][j]);

//		if (i >= 1 && abs(mat[i][j] - mat[i - 1][j]) == 1) {
//			i--;
//		} else {
//			j--;
//		}

		if (i >= 1 && (tab[i][j] - tab[i - 1][j]) == 1) {
			i--;
		} else {
			j--;
		}
	}

	printf("\nThe elements forming longest snake sequence are:-\n");
	while (!stk.empty()) {
		printf("%d\t", stk.top());
		stk.pop();
	}
	printf("\n");
}
