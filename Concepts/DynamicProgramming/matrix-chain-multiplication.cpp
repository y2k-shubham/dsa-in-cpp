// http://www.geeksforgeeks.org/dynamic-programming-set-8-matrix-chain-multiplication/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

#define MAX 100
#define minVal(a, b) ((a < b) ? a : b)

void input(int [MAX], int&);
void findPzation(int [MAX], int [MAX][MAX], int [MAX][MAX], int);
void init(int [MAX][MAX], int, int);
void output(int [MAX][MAX], int, int);
void showMat(int [MAX][MAX], int, const char *);

int main() {
	int n;
	int dim[MAX];
	int cost[MAX][MAX];
	int pIndex[MAX][MAX];

	input(dim, n);
	findPzation(dim, cost, pIndex, n);

	showMat(cost, n, "cost");
	showMat(pIndex, n, "pIndex");

	printf("\n");
	output(pIndex, 1, n);
	printf("The min no of operations is %d\n", cost[1][n]);

	return 0;
}

void input(int dim[MAX], int& n) {
	printf("Enter length of matrices chain:\t");
	scanf("%d", &n);

	printf("Enter matrices dimension chain:-\n");
	for (int i = 0; i <= n; i++) {
		scanf("%d", &dim[i]);
	}
}

void findPzation(int dim[MAX], int cost[MAX][MAX], int pIndex[MAX][MAX], int n) {
	init(cost, n + 1, INT_MAX);
	init(pIndex, n + 1, -1);

	for (int i = 0; i <= n; i++) {
		cost[i][i] = 0;
	}

	for (int L = 2; L <= n; L++) {
		int j = L;
		for (int i = 1; i <= n - L + 2; i++, j++) {
			int k;
			int minCost = INT_MAX;
			int minInd;

			for (k = i; k < j; k++) {
				int pCost;
				if ((pCost = cost[i][k] + cost[k + 1][j] + dim[i - 1] * dim[k] * dim[j]) < minCost) {
					minCost = pCost;
					minInd = k;
				}
			}

			cost[i][i + L - 1] = minCost;
			pIndex[i][i + L - 1] = minInd;
		}
	}
}

void init(int mat[MAX][MAX], int n, int val) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mat[i][j] = val;
		}
	}
}

void output(int pIndex[MAX][MAX], int i, int j) {
	if (i == j) {
		printf("A%d", i);
	} else {
		printf("(");
		output(pIndex, i, pIndex[i][j]);
		output(pIndex, pIndex[i][j] + 1, j);
		printf(")");
	}
}

void showMat(int mat[MAX][MAX], int n, const char * name) {
	printf("\nThe matrix %s is:-\n", name);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (j < i) {
				printf("\t");
			} else if (mat[i][j] == INT_MAX || mat[i][j] < 0) {
				printf("_\t");
			} else {
				printf("%d\t", mat[i][j]);
			}
		}
		printf("\n\n");
	}
	printf("\n\n");
}
