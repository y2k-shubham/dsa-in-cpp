// http://www.geeksforgeeks.org/dynamic-programming-set-9-binomial-coefficient/
#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int&, int&);
void calc(int [MAX][MAX], int, int);

int main() {
	int n, r;
	int coeff[MAX][MAX];

	input(n, r);
	calc(coeff, n, r);

	printf("\nnCr = %d\n", coeff[n][r]);

	return 0;
}

void input(int& n, int& r) {
	printf("Enter n:\t");
	scanf("%d", &n);

	printf("Enter r:\t");
	scanf("%d", &r);

	r = (n - r < r) ? (n - r) : r;
}

void calc(int coeff[MAX][MAX], int n, int r) {
	for (int i = 0; i <= r; i++) {
		coeff[0][i] = 0;
	}
	for (int j = 0; j <= n; j++) {
		coeff[j][0] = 1;
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= r; j++) {
			coeff[i][j] = coeff[i - 1][j - 1] + coeff[i - 1][j];
		}
	}
}
