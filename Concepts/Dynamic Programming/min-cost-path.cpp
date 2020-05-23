// http://www.geeksforgeeks.org/dynamic-programming-set-6-min-cost-path/

#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 100
#define isMin(a, b, c) (((a < b) && (a < c)) ? true : false)
#define minVal2(a, b) ((a < b) ? a : b)
#define minVal3(a, b, c) (isMin(a, b, c) ? a : (isMin(b, a, c) ? b : c))

void input(int [MAX][MAX], int&, int&);
void findPath(int [MAX][MAX], int [MAX][MAX], int, int);
void showPath(int [MAX][MAX], int [MAX][MAX], int, int);
void init(int [MAX][MAX], int, int);

int main() {
	int dimX, dimY;
	int cost[MAX][MAX];
	int path[MAX][MAX];

	input(cost, dimX, dimY);

	findPath(cost, path, dimX, dimY);
	showPath(cost, path, dimX, dimY);

	return 0;
}

void input(int cost[MAX][MAX], int& dimX, int& dimY) {
	printf("Enter x dim of cost:\t");
	scanf("%d", &dimX);

	printf("Enter y dim of cost:\t");
	scanf("%d", &dimY);

	init(cost, dimX, dimY);

	printf("Enter path matrix:-\n");
	for (int i = 0; i < dimY; i++) {
		for (int j = 0; j < dimX; j++) {
			scanf("%d", &cost[i][j]);
		}
	}
}

void findPath(int cost[MAX][MAX], int path[MAX][MAX], int dimX, int dimY) {
	init(path, dimX, dimY);

	// fill up bottom-right cell
	path[dimY - 1][dimX - 1] = cost[dimY - 1][dimX - 1];

	// fill up last rows and columns
	for (int i = dimY - 2; i >= 0; i--) {
		path[i][dimX - 1] = path[i + 1][dimX - 1] + cost[i][dimX - 1];
	}
	for (int j = dimX - 2; j >= 0; j--) {
		path[dimY - 1][j] = path[dimY - 1][j + 1] + cost[dimY - 1][j];
	}

	// fill up the table
	for (int i = dimY - 2; i >= 0; i--) {
		for (int j = dimX - 2; j >= 0; j--) {
			path[i][j] = minVal3(path[i + 1][j], path[i][j + 1], path[i + 1][j + 1]) + cost[i][j];
		}
	}
}

void init(int mat[MAX][MAX], int dimX, int dimY) {
	// initalize mat to infinity
	for (int i = 0; i < dimY; i++) {
		for (int j = 0; j < dimX; j++) {
			mat[i][j] = INT_MAX;
		}
	}
}

void showPath(int cost[MAX][MAX], int path[MAX][MAX], int dimX, int dimY) {
	int totalCost;
	int i, j;

	i = j = 0;
	totalCost = cost[0][0];

	printf("\nThe path is:-\n");
	printf("(0, 0)");
	while (!(i == dimY - 1 && j == dimX - 1)) {
		if (isMin(path[i + 1][j], path[i][j + 1], path[i + 1][j + 1]) && i < dimY - 1) {
			i++;
		} else if (isMin(path[i][j + 1], path[i + 1][j], path[i + 1][j + 1]) && j < dimX - 1) {
			j++;
		} else if (i < dimY - 1 && j < dimX - 1) {
			i++;
			j++;
		} else if (i < dimY - 1) {
			i++;
		} else {
			j++;
		}

		totalCost += cost[i][j];
		printf("\t->\t(%d, %d)", i, j);
	}
	cout << endl;

	i = j = 0;
	printf("%d", cost[0][0]);
	while (!(i == dimY - 1 && j == dimX - 1)) {
		if (isMin(path[i + 1][j], path[i][j + 1], path[i + 1][j + 1])) {
			i++;
		} else if (isMin(path[i][j + 1], path[i + 1][j], path[i + 1][j + 1])) {
			j++;
		} else if (isMin(path[i + 1][j + 1], path[i + 1][j], path[i][j + 1])) {
			i++;
			j++;
		} else if (i < dimY - 1) {
			// if reached last column, can only move down
			i++;
		} else {
			// if reached last row, can only move right
			j++;
		}

		printf("\t->\t%d", cost[i][j]);
	}
	cout << endl << endl;

	printf("Total path length is:\t%d\n", totalCost);
}
