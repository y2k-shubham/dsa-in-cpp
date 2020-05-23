// TusharRoy
// Solution Reconstruction from https://www.youtube.com/watch?v=GMzVeWpyTN0 at 28:00 min

/*
4
2 3 6 4 5

6
30 35 15 5 10 20 25
*/

#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void init(int [MAX][MAX], int);
void calcSplit(int [MAX], int, int [MAX][MAX], int [MAX][MAX]);
void showMat(int [MAX][MAX], int, const char *);
void output(int [MAX][MAX], int, int);

int main() {
	int dim[MAX], n;
	int cost[MAX][MAX], split[MAX][MAX];

	input(dim, n);
	init(cost, n);

	calcSplit(dim, n, cost, split);

	showMat(cost, n, "cost");
	showMat(split, n, "split");

	cout << "\nOptimal multiplication order is:-\n";
	output(split, 0, n - 1);
	cout << endl;

	return 0;
}

void input(int dim[MAX], int &n) {
	printf("Enter no of matrices:\t");
	cin >> n;

	cout << "Enter dimension array:-\n";
	for (int i = 0; i <= n; i++) {
		cin >> dim[i];
	}
}

void init(int mat[MAX][MAX], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			mat[i][j] = 0;
		}
	}
}

void calcSplit(int dim[MAX], int n, int cost[MAX][MAX], int split[MAX][MAX]) {
	for (int col = 1; col < n; col++) {
		int i = 0;
		int j = col;

		for ( ; j < n; i++, j++) {
			int minCost = INT_MAX;
			int minSplit;

			for (int k = i; k < j; k++) {
				int crrCost = cost[i][k] + cost[k + 1][j] + dim[i] * dim[k + 1] * dim[j + 1];
				if (crrCost < minCost) {
					minCost = crrCost;
					minSplit = k;
				}
			}

			cost[i][j] = minCost;
			split[i][j] = minSplit;
		}
	}
}

void showMat(int mat[MAX][MAX], int n, const char * msg) {
	printf("\n%s[][] matrix is:-\n", msg);

	cout << "\t";
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		int j;

		printf("[%d]\t", i);

		for (j = 0; j < i; j++) {
			cout << "\t";
		}

		for (; j < n; j++) {
			printf("%d\t", mat[i][j]);
		}

		cout << endl;
	}
}

void output(int split[MAX][MAX], int i, int j) {
	if (i == j) {
		printf(" A%d ", i);
	} else {
		cout << "(";
		output(split, i, split[i][j]);
		output(split, split[i][j] + 1, j);
		cout << ")";
	}
}
