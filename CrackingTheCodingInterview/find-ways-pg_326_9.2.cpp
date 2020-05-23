#include <cstdio>
#include <iostream>
#include <cstring>

// page 326_9.2

using namespace std;
#define maxVal(a, b) ((a > b) ? a : b)

void input(int *, char);
void fillLine(int *, int, int);
void findWays(int *, int, int);
void showTable(int *, int, int);

int main() {
	int x;
	int y;
	int xTmp;
	int yTmp;

	cout << "Enter the dimensions:-\n";
	input(&x, 'x');
	input(&y, 'y');

	int ways[x][y];
	memset(ways, 0, sizeof(ways));

	//printf("fillLine called");
	fillLine(&ways[0][0], x, y);
	ways[x - 1][y - 1] = 0;
	showTable(&ways[0][0], x, y);

	printf("\nEnter coordinates of obstacles\n(Enter (-1, -1) to terminate):-\n");
	printf("row = ");
	scanf("%d", &yTmp);
	printf("col = ");
	scanf("%d", &xTmp);
	while (xTmp >= 0 && yTmp >= 0) {
		ways[yTmp][xTmp] = -1;
		printf("\nrow = ");
		scanf("%d", &yTmp);
		printf("col = ");
		scanf("%d", &xTmp);
	}
	showTable(&ways[0][0], x, y);

	//printf("findWays called");
	findWays(&ways[0][0], x, y);
	showTable(&ways[0][0], x, y);
	cout << "\nNo of ways is:\t" << ways[0][0] << endl;

	return 0;
}

void input(int * var, char varName) {
	cout << varName << " = ";
	scanf("%d", var);
}

void fillLine(int * ways, int x, int y) {
	for (int j = x - 1; j >= 0; j--) {
		* (ways + (y - 1) * x + j) = 1;
	}
	for (int i = y - 1; i >= 0; i--) {
		* (ways + i * x + (x - 1)) = 1;
	}
}

void showTable(int * ways, int x, int y) {
	printf("\nThe table is:-\n");
	for (int i = 0; i < y; i++) {
		for (int j = 0; j < x; j++) {
			printf("%d\t", * (ways + i * x + j));
		}
		printf("\n");
	}
	printf("\n");
}

void findWays(int * ways, int x, int y) {
	int ctr;

	cout << "\nfilling bottom right\n";
	// fill bottom right triangle
	ctr = 0;
	while (ctr < x - 1 && ctr < y - 1) {
		int i = y - 2;
		int j = x - ctr - 2;

		for (; j < x - 1; i--, j++) {
			if (*(ways + i * x + j) >= 0) {
				*(ways + i * x + j) = maxVal(*(ways + x * (i + 1) + j), 0) + maxVal(*(ways + x * i +  j + 1), 0);
				printf("a[%d][%d]\t", i, j);
			}
		}
		printf("\n");

		ctr++;
	}

	// fill middle part
	int rInit;
	int rInitInc;
	int cInit;
	int cInitInc;
	int lim;

	if (x > y) {
		rInit = y - 2;
		rInitInc = 0;
		cInit = x - ctr - 2;
		cInitInc = -1;
		lim = x - ctr - 2;
	} else {
		rInit = y - 3;
		rInitInc = -1;
		cInit = 0;
		cInitInc = 0;
		lim = y - ctr - 2;
	}

	cout << "\nfilling middle\n";
	for (int k = 0; k < lim; k++) {
		int i = rInit;
		int j = cInit;

		for (int l = 0; l < ctr; l++, i--, j++) {
			if (*(ways + i * x + j) >= 0) {
				*(ways + i * x + j) = maxVal(*(ways + x * (i + 1) + j), 0) + maxVal(*(ways + x * i +  j + 1), 0);
				printf("a[%d][%d]\t", i, j);
			}
		}
		printf("\n");

		rInit += rInitInc;
		cInit += cInitInc;
	}

	cout << "\nfilling top left\n";
	// fill top-left part
	for (int k = 0; k < ctr; k++) {
		int i = ctr - k - 1;
		int j = 0;

		for (int l = 0; l < ctr - k; l++, i--, j++) {
			if (*(ways + i * x + j) >= 0) {
				*(ways + i * x + j) = maxVal(*(ways + x * (i + 1) + j), 0) + maxVal(*(ways + x * i +  j + 1), 0);
				printf("a[%d][%d]\t", i, j);
			}
		}
		printf("\n");
	}
}
