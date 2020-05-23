#include <stdio.h>
#include <strings.h>
#include <math.h>

#define INT_LEN 32
#define minVal(a, b) ((a < b) ? a : b)
#define maxVal(a, b) ((a > b) ? a : b)

// Google Interview Question
// URL: http://www.geeksforgeeks.org/calculate-sum-of-bitwise-and-of-all-pairs/
/*
    Question: Program to find sum of bitwise AND of all pairs of numbers of a list in linear time

    Solution:  (i) Given that integers are stored as set of 32-bits, we first determine the count of numbers having i'th bit set for all 0 <= i <= 31
              (ii) Next we notice that if there are k numbers having i'th bit set, then there will be kC2 pairs of bitwise AND operations where the
                   resulting i'th bit will be set
             (iii) Each such AND operation will contribute 2^i to the result
              (iv) Hence we have to find sum of all kC2 * 2^i, where 0 <= i <= 31 and 1 <= k <= n
*/

void input(int *, int);
void findCounts(int *, int, int [INT_LEN]);
int calcSum(int [INT_LEN]);
int nCr(int, int);

int main() {
	int n;
	int sum;
	int pos[INT_LEN];

	printf("Enter n:\t");
	scanf("%d", &n);

	int arr[n];

	input(&arr[0], n);
	findCounts(&arr[0], n, pos);
	sum = calcSum(pos);

	printf("The sum of bitwise & of all pairs is:\t%d\n", sum);

	return 0;
}

void input(int * arr, int n) {
    printf("Enter %d positive integers:-\n", n);
	while (n-- > 0) {
		scanf("%d", arr + n);
	}
}

void findCounts(int * arr, int n, int pos[INT_LEN]) {
	int i;
	int j;
	int num;

	memset(pos, 0, INT_LEN * sizeof(int));

	for (i = 0; i < INT_LEN; i++) {
		num = 1 << i;
		for (j = 0; j < n; j++) {
			if (num & * (arr + j)) {
				pos[i]++;
			}
		}
	}
}

int calcSum(int pos[INT_LEN]) {
	int i;
	int sum;

	sum = 0;
	for (i = 0; i < INT_LEN; i++) {
		sum += (1 << i) * nCr(pos[i], 2);
	}

	return sum;
}

// best way to calculate nCr can be found at: http://stackoverflow.com/questions/11809502/which-is-better-way-to-calculate-ncr
int nCr(int n, int r) {
	int n_r;
	int numerator;
	int denominator;
	int lim;

	n_r = n - r;
	numerator = 1;
	denominator = 1;
	lim = maxVal(r, n_r);

	// find numerator
	while (n >= lim) {
		numerator *= n;
		n--;
	}

	// find denominator
	while (r > 1) {
		denominator *= r;
		r--;
	}

	// return result
	return numerator / denominator;
}
