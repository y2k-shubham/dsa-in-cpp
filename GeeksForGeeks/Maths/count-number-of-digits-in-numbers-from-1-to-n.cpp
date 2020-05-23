#include <cstdio>
#include <iostream>
#include <cmath>

int countDigits(int);
int findSum(int, int);
void findSigmas(int [10]);
int sigmaN(int);

int main() {
	int n;
	int digitsCount;
	int sum;

	printf("Enter an integer:\t");
	scanf("%d", &n);

	digitsCount = countDigits(n);
	sum = findSum(n, digitsCount);

	printf("The sum of digits of  all numbers from 1 to %d is:\t%d\n", n, sum);

	return 0;
}

int countDigits(int n) {
	if (n == 0) {
		return 0;
	} else {
		return 1 + countDigits(n / 10);
	}
}

int findSum(int n, int digitsCount) {
	int sum;
	int powOf_10;
	int nRemLeft;
	int nRemRight;
	int i;
	int nCopy;
	int crrDigit;
	int sigmaN[10];

	if (n < 10) {
		return (n * (n + 1) / 2);
	}

	// initialize variables
	powOf_10 = 1;
	sum = 0;
	findSigmas(sigmaN);

	// find contribution of least significant place
	nCopy = n;
	crrDigit = nCopy % 10;

	nRemLeft = n / (10 * powOf_10);
	nRemRight = n % powOf_10;

	sum += powOf_10 * (nRemLeft * sigmaN[9] + sigmaN[crrDigit]);
	powOf_10 *= 10;

				// find contribution of all places except first & last
	for (i = 2; i < digitsCount; i++) {
		nCopy /= 10;
		crrDigit = nCopy % 10;

		nRemLeft = n / (10 * powOf_10);
		nRemRight = n % powOf_10;

		sum += powOf_10 * (nRemLeft * sigmaN[9] + sigmaN[crrDigit - 1]) + (nRemRight + 1) * crrDigit;
		powOf_10 *= 10;
	}

	// find contribution of most significant place
	nCopy /= 10;
	crrDigit = nCopy % 10;

	nRemLeft = 1;
	nRemRight = n % powOf_10;

	sum += powOf_10 * sigmaN[crrDigit - 1] + (nRemRight + 1) * crrDigit;

	// return the result
	return sum;
}

void findSigmas(int sigma_N[10]) {
	int i;

	for (i = 0; i <= 9; i++) {
		sigma_N[i] = sigmaN(i);
	}
}

int sigmaN(int n) {
	return (n * (n + 1) / 2);
}

