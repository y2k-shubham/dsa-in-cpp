// http://www.geeksforgeeks.org/dynamic-programming-set-10-0-1-knapsack-problem/
// http://cse.unl.edu/~goddard/Courses/CSCE310J/Lectures/Lecture8-DynamicProgramming.pdf

/*
7
4
1 4 5 7
1 3 4 5
*/

#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX 100

void input(int *, int *, int [MAX], int [MAX]);
void calc(int, int, int [MAX], int [MAX], int [MAX][MAX]);
void output(int W, int n, int [MAX], int [MAX], int [MAX][MAX]);
void showMat(int [MAX][MAX], int, int, const char *);

int main() {
	int W;
	int n;
	int val[MAX];
	int w[MAX];
	int prof[MAX][MAX];

	input(&W, &n, val, w);
	calc(W, n, val, w, prof);

	showMat(prof, n, W, "profit");
	output(W, n, val, w, prof);

	return 0;
}

void input(int * W, int * n, int val[MAX], int w[MAX]) {
	int i;

	printf("Enter capacity:\t");
	scanf("%d", W);

	printf("Enter no of items:\t");
	scanf("%d", n);

	printf("Enter values of items:-\n");
	for (i = 1; i <= *n; i++) {
		scanf("%d", &val[i]);
	}

	printf("Enter weights of items:-\n");
	for (i = 1; i <= *n; i++) {
		scanf("%d", &w[i]);
	}
}

void calc(int W, int n, int val[MAX], int w[MAX], int prof[MAX][MAX]) {
	int i, j;

	memset(prof, 0, sizeof(prof));
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= W; j++) {
			if (w[i] > j) {
				prof[i][j] = prof[i - 1][j];
			} else {
				int newProf = prof[i - 1][j - w[i]] + val[i];

				if (newProf > prof[i - 1][j]) {
					prof[i][j] = newProf;
				} else {
					prof[i][j] = prof[i - 1][j];
				}
			}
		}
	}
}

void output(int W, int n, int val[MAX], int w[MAX], int prof[MAX][MAX]) {
	int stack[n];
	int i, j, capUsed, top, ind;

	j = W;
	top = -1;
	capUsed = 0;
	for (i = n; i > 0; i--) {
		if (prof[i - 1][j] == prof[i][j]) {
			continue;
		} else {
			stack[++top] = i;
			j -= w[i];
			capUsed += w[i];
		}
	}

	printf("\nThe included items are:-");
	printf("\nIndex\t");
	for (ind = top; ind >= 0; ind--) {
		printf("%d\t", stack[ind]);
	}
	printf("\nWeight\t");
	for (ind = top; ind >= 0; ind--) {
		printf("%d\t", w[stack[ind]]);
	}
	printf("\nValue\t");
	for (ind = top; ind >= 0; ind--) {
		printf("%d\t", val[stack[ind]]);
	}

	printf("\nTotal profit earned:\t%d", prof[n][W]);
	printf("\nTotal capacity used:\t%d\n", capUsed);
}

void showMat(int mat[MAX][MAX], int row, int col, const char * name) {
	int i, j;

	printf("\nThe matrix %s is:-\n", name);
	for (i = 0; i <= row; i++) {
		for (j = 0; j <= col; j++) {
			printf("%d\t", mat[i][j]);
		}
		printf("\n\n");
	}
	printf("\n\n");
}
