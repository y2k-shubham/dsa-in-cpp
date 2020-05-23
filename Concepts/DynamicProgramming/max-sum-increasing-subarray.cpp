#include <cstdio>
#include <iostream>

#define MAX 100

void input(int *, int [MAX]);
void output(int, int [MAX]);

int main() {
	int n;
	int arr[MAX];

	input(&n, arr);
	output(n, arr);

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

void output(int n, int arr[MAX]) {
	int crrSum;
	int maxSum;
	int startInd;
	int endInd;
	int mStartInd;
	int mEndInd;

	crrSum = arr[0];
	maxSum = 0;
	startInd = endInd = 0;

	for (int i = 1; i < n; i++) {
		if (arr[i] > arr[i - 1]) {
			crrSum += arr[i];
			endInd++;
		} else {
			if (crrSum > maxSum) {
				maxSum = crrSum;
				mStartInd = startInd;
				mEndInd = i - 1;
			}
			startInd = endInd = i;
			crrSum = 0;
		}
	}

	printf("\nMax sum is between arr[%d] = %d and arr[%d] = %d and is equal to %d\n", mStartInd, arr[mStartInd], mEndInd, arr[mEndInd], maxSum);
}
