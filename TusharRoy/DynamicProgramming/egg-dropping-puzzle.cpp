#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;
#define MAX 100

void init(int T[MAX][MAX], int f, int e) {
	for (int j = 1; j <= f; j++) {
		T[1][j] = j;
	}
}

void calc(int T[MAX][MAX], int f, int e) {
	for (int i = 2; i <= e; i++) {
		for (int j = 1; j <= f; j++) {
			if (j < i) {
				T[i][j] = T[i - 1][j];
			} else {
				int minVal = INT_MAX;
				for (int k = 1; k <= j; k++) {
					minVal = min(minVal, max(T[i - 1][k - 1], T[i][j - k]));
				}
				T[i][j] = 1 + minVal;
			}
		}
	}
}

void showTab(int T[MAX][MAX], int f, int e) {
	printf("\nTable is:-\n");
	for (int i = 1; i <= e; i++) {
		for (int j = 1; j <= f; j++) {
			printf("%d ", T[i][j]);
		}
		printf("\n");
	}
	cout << endl;
}

int main() {
	int f, e;
	int T[MAX][MAX];

	scanf("%d%d", &f, &e);

	init(T, f, e);
	calc(T, f, e);
	showTab(T, f, e);

	return 0;
}

