/*
Input:
4 5
0 0 1 1 1
1 0 1 1 1
0 1 1 1 1
1 0 1 1 1

Output:
3 x 3
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define MAX 100
#define min(a, b, c) ((a <= b && a <= c) ? a : ((b <= a && b <= c) ? b : c))

void input(int [MAX][MAX], int &, int &);
void calc(int [MAX][MAX], int, int, int [MAX][MAX], int &, int &, int &);
void output(int [MAX][MAX], int, int, int, int, int);

int main() {
	int mat[MAX][MAX];
	int tab[MAX][MAX];
	int rows, cols;
	int maxSqrSize, maxSqrIndBot, maxSqrIndRit;

	input(mat, rows, cols);
	memset(tab, 0, sizeof(int) * (rows + 1) * (cols + 1));

	calc(mat, rows, cols, tab, maxSqrSize, maxSqrIndBot, maxSqrIndRit);
	output(mat, rows, cols, maxSqrSize, maxSqrIndBot, maxSqrIndRit);

	return 0;
}

void input(int mat[MAX][MAX], int &rows, int &cols) {
	printf("Enter dimension as (rows, cols):\t");
	scanf("%d%d", &rows, &cols);

	printf("Enter the matrix:-\n");
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void calc(int mat[MAX][MAX], int rows, int cols, int tab[MAX][MAX], int &maxSqrSize, int &maxSqrIndBot, int &maxSqrIndRit) {
	maxSqrSize = 0;

	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			if (mat[i][j] == 0) {
				tab[i][j] = 0;
			} else {
				tab[i][j] = min(tab[i - 1][j], tab[i][j - 1], tab[i - 1][j - 1]) + 1;

				if (tab[i][j] > maxSqrSize) {
					maxSqrSize = tab[i][j];
					maxSqrIndBot = i;
					maxSqrIndRit = j;
				}
			}
		}
	}
}

void output(int mat[MAX][MAX], int rows, int cols, int maxSqrSize, int maxSqrIndBot, int maxSqrIndRit) {
	printf("\nThe size of max sub-square of 1's is:\t%d X %d\n", maxSqrSize, maxSqrSize);

	int maxSqrIndLft, maxSqrIndTop;
	maxSqrIndLft = maxSqrIndRit - maxSqrSize + 1;
	maxSqrIndTop = maxSqrIndBot - maxSqrSize + 1;

	printf("The max sub-square highlighted in the matrix is:-\n");
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			if ((maxSqrIndLft <= j && j <= maxSqrIndRit) && (maxSqrIndTop <= i && i <= maxSqrIndBot)) {
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
