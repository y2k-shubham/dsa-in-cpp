/*
Input:
4 6
1 0 0 1 1 1
1 0 1 1 0 1
0 1 1 1 1 1
0 0 1 1 1 1

Output:
Max-Area = 18
*/

#include <cstdio>
#include <iostream>
#include <stack>
#include <climits>
#include <cstring>

using namespace std;

#define MAX 100
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

void input(int [MAX][MAX], int &, int &);
void calcLeftLesser(int [MAX], int, int [MAX], int [MAX]);
void calcRightLesser(int [MAX], int, int [MAX], int [MAX]);
void showArray(int [MAX], int , const char *);
int findMaxRect(int [MAX], int, int [MAX], int [MAX], int &, int &, int &);
void addRows(int *, int [MAX], int);
void output(int [MAX][MAX], int, int, int, int, int, int, int);

int main() {
	int rows, cols;
	int mat[MAX][MAX];
	int arr[MAX];
	int lLftE[MAX], lLftI[MAX];
	int lRitE[MAX], lRitI[MAX];
	int recIndLft, recIndRit, recHeight;
	int maxRecArea, maxRecIndLft, maxRecIndRit, maxRecTopInd, maxRecBotInd;

	input(mat, rows, cols);
	memset(arr, 0, sizeof(arr));

	maxRecArea = 0;
	for (int i = 0; i < rows; i++) {
		addRows(mat[i], arr, cols);

		calcLeftLesser(arr, cols, lLftE, lLftI);
		calcRightLesser(arr, cols, lRitE, lRitI);
		int crrArea = findMaxRect(arr, cols, lLftI, lRitI, recIndLft, recIndRit, recHeight);

		if (crrArea > maxRecArea) {
			maxRecArea = crrArea;
			maxRecBotInd = i;
			maxRecTopInd = i - recHeight + 1;
			maxRecIndLft = recIndLft;
			maxRecIndRit = recIndRit;
		}
	}

	output(mat, rows, cols, maxRecArea, maxRecTopInd, maxRecBotInd, maxRecIndLft, maxRecIndRit);

	return 0;
}

void input(int mat[MAX][MAX], int &rows, int &cols) {
	printf("Enter dimensions as (rows, cols):\t");
	scanf("%d%d", &rows, &cols);

	printf("Enter matrix:-\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			scanf("%d", &mat[i][j]);
		}
	}
}

void calcLeftLesser(int arr[MAX], int n, int lLftE[MAX], int lLftI[MAX]) {
	stack <int> stkE;
	stack <int> stkI;

	for (int i = 0; i < n; i++) {
		int ele = arr[i];

		while (!stkE.empty() && stkE.top() >= ele) {
			stkE.pop();
			stkI.pop();
		}

		if (stkE.empty()) {
			lLftE[i] = -1;
			lLftI[i] = -1;
		} else {
			lLftE[i] = stkE.top();
			lLftI[i] = stkI.top();
		}

		stkE.push(ele);
		stkI.push(i);
	}
}

void calcRightLesser(int arr[MAX], int n, int lRitE[MAX], int lRitI[MAX]) {
	stack <int> stkE;
	stack <int> stkI;

	for (int i = n - 1; i >= 0; i--) {
		int ele = arr[i];

		while (!stkE.empty() && stkE.top() >= ele) {
			stkE.pop();
			stkI.pop();
		}

		if (stkE.empty()) {
			lRitE[i] = -1;
			lRitI[i] = n;
		} else {
			lRitE[i] = stkE.top();
			lRitI[i] = stkI.top();
		}

		stkE.push(ele);
		stkI.push(i);
	}
}

void showArray(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

int findMaxRect(int arr[MAX], int n, int lLftI[MAX], int lRitI[MAX], int &recIndLft, int &recIndRit, int &recHeight) {
	int maxAreaTillNow = 0;

	for (int i = 0; i < n; i++) {
		int crrArea = arr[i] * ((lRitI[i] - 1) - (lLftI[i] + 1) + 1);

		if (crrArea > maxAreaTillNow) {
			maxAreaTillNow = crrArea;
			recIndLft = lLftI[i] + 1;
			recIndRit = lRitI[i] - 1;
			recHeight = arr[i];
		}
	}

	return maxAreaTillNow;
}

void addRows(int * mat, int arr[MAX], int cols) {
	for (int i = 0; i < cols; i++) {
		if (* (mat + i) == 0) {
			arr[i] = 0;
		} else {
			arr[i] += * (mat + i);
		}
	}
}

void output(int mat[MAX][MAX], int rows, int cols, int mRecArea, int mRecIndTop, int mRecIndBot, int mRecIndLft, int mRecIndRit) {
	printf("\nThe area of biggest rect of 1's is:\t%d\n", mRecArea);

	printf("The highlighted sub-matrix (rectangular) is:-\n");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (((mRecIndTop <= i) && (i <= mRecIndBot)) && ((mRecIndLft <= j) && (j <= mRecIndRit))) {
				printf("I ");
			} else {
				if (mat[i][j] == 1) {
					printf("| ");
				} else {
					printf("0 ");
				}
			}
		}
		printf("\n");
	}
}
