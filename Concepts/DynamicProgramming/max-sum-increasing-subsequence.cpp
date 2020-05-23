#include <cstdio>
#include <iostream>
#include <cstring>

#define MAX 100
#define max(a, b) ((a > b) ? a : b)

void input(int *, int [MAX]);
int findMax1(int [MAX], int, int, int, int [MAX]);
int findMax2(int [MAX], int, int, int, int [MAX], int [MAX]);

int main() {
	int n;
	int arr[MAX];
	int sumI[MAX];
	int sumE[MAX];

	memset(sumI, -1, sizeof(sumI));
	memset(sumE, -1, sizeof(sumE));

	input(&n, arr);
	printf("\nMax sum of any subsequence is:\t%d\n", findMax2(arr, n, 0, -1, sumI, sumE));

	return 0;
}

void input(int * n, int arr[MAX]) {
	printf("Enter length of array:\t");
	scanf("%d", n);

	printf("Enter the array:-\n");
	for (int i = 0; i < *n; i++) {
		scanf("%d", &arr[i]);
	}
}

int findMax1(int arr[MAX], int len, int ind, int prev, int sum[MAX]) {
	if (ind < len) {
		//printf("\n=============\narr[%d] = %d\n\n", ind, arr[ind]);
		if (sum[ind] >= 0) {
			printf("For, arr[%d] = %d,\tsum[%d] = %d already found, returned\n============\n", ind, arr[ind], ind, sum[ind]);
			return sum[ind];
		} else {
			int sumInc;
			int sumExc;

			sumInc = arr[ind] + findMax1(arr, len, ind + 1, arr[ind], sum);
			if (arr[ind] > prev) {
				sumExc = findMax1(arr, len, ind + 1, prev, sum);
			} else {
				sumExc = 0;
			}

			printf("For arr[%d] = %d,\tsumInc = %d\tsumExc = %d\n=============\n", ind, arr[ind], sumInc, sumInc);
			sum[ind] = max(sumInc, sumExc);
			return sum[ind];
		}
	} else {
		printf("\n=============\nEnd Reached\n============\n\n");
		return 0;
	}
}

int findMax2(int arr[MAX], int len, int ind, int prev, int sumI[MAX], int sumE[MAX]) {
	if (ind < len) {
		int sumInc;
		int sumExc;

		if (arr[ind] > prev) {
			if (sumI[ind] >= 0) {
				sumInc = sumI[ind];
			} else {
				sumInc = sumI[ind] = arr[ind] + findMax2(arr, len, ind + 1, arr[ind], sumI, sumE);
			}
		} else {
			sumInc = 0;
		}

		if (sumE[ind] >= 0) {
			sumExc = sumE[ind];
		} else {
			sumExc = findMax2(arr, len, ind + 1, prev, sumI, sumE );
		}

		return  max(sumInc, sumExc);
	} else {
		return 0;
	}
}
