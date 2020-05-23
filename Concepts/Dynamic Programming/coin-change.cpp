#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int&, int [MAX], int&);
void findWays2d(int, int [MAX], int);
void findWays1d(int, int [MAX], int);

int main() {
	int n, m; // n = amount of change, m = no of available denominations
	int den[MAX];

	input(n, den, m);
	findWays2d(n, den, m);
	findWays1d(n, den, m);

	return 0;
}

void input(int& n, int den[MAX], int& m) {
	printf("Enter no of denominations:\t");
	scanf("%d", &m);

	printf("Enter the list of available denominations:-\n");
	for (int i = 0; i < m; i++) {
		scanf("%d", &den[i]);
	}

	printf("Enter the amount of change:\t");
	scanf("%d", &n);
}

void findWays2d(int n, int den[MAX], int m) {
	int ways2d[m + 1][n + 1];

	memset(ways2d, 0, sizeof(ways2d));
	for (int i = 0; i <= m; i++) {
		ways2d[i][0] = 1;
	}

	for (int i = 1; i <= m; i++) {
		int crrDen = den[i - 1];
		for (int j = 1; j <= n; j++) {
			ways2d[i][j] = ways2d[i - 1][j];
			if (j - crrDen >= 0) {
				ways2d[i][j] += ways2d[i][j - crrDen];
			}
		}
	}

	printf("\nNo of ways to give change are:\t%d\n", ways2d[m][n]);
}

void findWays1d(int n, int den[MAX], int m) {
	int ways1d[n + 1];

	memset(ways1d, 0, sizeof(ways1d));
	ways1d[0] = 1;

	for (int i = 0; i < m; i++) {
		for (int j = den[i]; j <= n; j++) {
			ways1d[j] += ways1d[j - den[i]];
		}
	}

	printf("No of ways to give change are:\t%d\n", ways1d[n]);
}
