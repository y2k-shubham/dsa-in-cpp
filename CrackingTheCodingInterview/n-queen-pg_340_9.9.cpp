#include <cstdio>
#include <iostream>

using namespace std;

#define MAX 100

void findWays(int [MAX], int, int);
bool isValid(int [MAX], int, int, int);
void showWay(int [MAX], int);
int abs(int);

int main() {
	int n;
	int col[MAX];

	printf("Enter board size:\t");
	scanf("%d", &n);

	findWays(col, n, 1);

	return 0;
}

void findWays(int col[MAX], int maxRow, int crrRow) {
	if (crrRow > maxRow) {
		showWay(col, maxRow);
	} else {
		for (int i = 1; i <= maxRow; i++) {
			if (isValid(col, maxRow, crrRow, i)) {
				col[crrRow] = i;
				findWays(col, maxRow, crrRow + 1);
			}
		}
	}
}

bool isValid(int col[MAX], int maxRow, int crrRow, int crrCol) {
	for (int i = 1; i < crrRow; i++) {
		// Check for column match
		if (col[i] == crrCol) {
			return false;
		}

		// Check for diagonal match
		if (abs(i - crrRow) == abs(col[i] - crrCol)) {
			return false;
		}
	}

	return true;
}

int abs(int n) {
	if (n < 0) {
		n *= -1;
	}
	return n;
}

void showWay(int col[MAX], int maxRow) {
	printf("\nArrangement is:-\n");
	for (int i = 1; i <= maxRow; i++) {
		for (int j = 1; j <= maxRow; j++) {
			if (col[i] == j) {
				printf("Q%d\t", i);
			} else {
				printf("_\t");
			}
		}
		printf("\n");
	}
	cout << endl;
}
