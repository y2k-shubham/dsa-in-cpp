#include <cstdio>
#include <iostream>

using namespace std;

int get_hcf(int, int);
int hcf(int, int);
int find_nCr(int, int);

int get_hcf(int dDend, int dSor) {
	if (dDend % dSor == 0) {
		return dSor;
	} else {
		return get_hcf(dSor, dDend % dSor);
	}
}

int hcf(int a, int b) {
	if (a > b) {
		return get_hcf(a, b);
	} else {
		return get_hcf(b, a);
	}
}

int main() {
	int n, r, nCr;

	printf("Enter n:\t");
	scanf("%d", &n);

	printf("Enter r:\t");
	scanf("%d", &r);

	nCr = find_nCr(n, r);
	printf("\nnCr = %d\n", nCr);

	return 0;
}

int find_nCr(int n, int r) {
	int numOrig, denOrig;
	int numMul, denMul;
	int hcf1;
	int hcf2;

	numOrig = denOrig = 1;
	numMul = n;
	denMul = (n - r < r) ? n - r : r;

	while (denMul > 0) {
		hcf1 = hcf(numOrig, denMul);
		hcf2 = hcf(denOrig, numMul);

		numOrig /= hcf1;
		denOrig /= hcf2;

		numOrig *= numMul / hcf2;
		denOrig *= denMul / hcf1;

		numMul--;
		denMul--;
	}

	return numOrig / denOrig;
}
