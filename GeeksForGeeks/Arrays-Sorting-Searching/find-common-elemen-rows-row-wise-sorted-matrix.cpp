// http://www.geeksforgeeks.org/find-common-element-rows-row-wise-sorted-matrix/
/*

4 5
1 2 3 4 5
2 4 5 8 10
3 5 7 9 11
1 3 5 7 9

*/
#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void input(int&, int&, int [MAX][MAX]);
void showComEle_1(int, int, int [MAX][MAX]);
int findMinEleRow(int, int [MAX][MAX], int [MAX]);

int main() {
	int m, n;
	int mat[MAX][MAX];

	input(m, n, mat);
	showComEle_1(m, n, mat);

	return 0;
}

void input(int& m, int& n, int mat[MAX][MAX]) {
	printf("Enter dimensions of matrix:\t(m, n) = ");
	scanf("%d%d", &m, &n);

	printf("Enter the matrix:-\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void showComEle_1(int m, int n, int mat[MAX][MAX]) {
	printf("\nThe common elements of all rows are:-\n");

	int lastEleInd[MAX];
	for (int i = 0; i < MAX; i++) {
		lastEleInd[i] = n - 1;
	}

	bool canRun = true;;
	while (canRun) {
		int minEleRow = findMinEleRow(m, mat, lastEleInd);
		int minEle = mat[minEleRow][lastEleInd[minEleRow]];
		bool noChange = true;

		//printf("\nminEleRow = %d and minEle = %d\n", minEleRow, minEle);
		for (int i = 0; i < m; i++) {
			if (mat[i][lastEleInd[i]] > minEle) {
				//printf("lastEleInd[%d] decreased to %d\n", i, lastEleInd[i] - 1);
				lastEleInd[i]--;
				noChange = false;

				if (lastEleInd[i] < 0) {
					//printf("lastEleInd[%d] became -ve (1st loop), when minEleRow = %d and minEle = %d\n", i, minEleRow, minEle);
					canRun = false;
					break;
				}
			}
		}

		if (canRun && noChange) {
			//printf("%d\n", minEle);
			//printf("\nNo change encountered\n");
			for (int i = 0; i < m; i++) {
				lastEleInd[i]--;
				//printf("lastEleInd[%d] decreased to %d\n", i, lastEleInd[i] - 1);

				if (lastEleInd[i] < 0) {
					//printf("lastEleInd[%d] became -ve (1st loop), when minEleRow = %d and minEle = %d\n", i, minEleRow, minEle);
					canRun = false;
					break;
				}
			}
		}
	}
}

int findMinEleRow(int m, int mat[MAX][MAX], int lastEleInd[MAX]) {
	int minEleRow;
	int minEle = INT_MAX;

	for (int i = 0; i < m; i++) {
		if (mat[i][lastEleInd[i]] < minEle) {
			minEle = mat[i][lastEleInd[i]];
			minEleRow = i;
		}
	}

	return minEleRow;
}
