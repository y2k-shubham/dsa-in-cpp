// https://www.youtube.com/watch?v=ohHWQf1HDfU
// kadane's modification for minimum sum subarray: http://www.geeksforgeeks.org/maximum-contiguous-circular-sum/
// CrackTheCoding.. page 452, 17.8

/*
8
2 3 -8 -1 2 4 -2 3

10
1 -3 2 -5 7 6 -1 -4 11 -23
*/

#include <cstdio>
#include <cmath>
#include <cstring>

#define MAX 100

void input(int [MAX], int &);
void output(int [MAX], int, int, int, const char *);
void findMaxSumSubArray(int [MAX], int, int &, int &, int &);
void findMinSumSubArray_Me(int [MAX], int, int &, int &, int &);
void findMimSumSubArray_Standard(int [MAX], int, int &, int &, int &);

int main() {
	int arr[MAX];
	int len;
	int maxLo, maxHi, maxSum;
	int minLo, minHi, minSum;

	input(arr, len);

	findMaxSumSubArray(arr, len, maxLo, maxHi, maxSum);
	output(arr, maxLo, maxHi, maxSum, "Max");

	// compiler misbehaving, not my fault. even ideone sucks here
//	findMinSumSubArray_Me(arr, len, minLo, minHi, minSum);
//	output(arr, minLo, minHi, minSum, "Min");

	findMimSumSubArray_Standard(arr, len, minLo, minHi, minSum);
	output(arr, minLo, minHi, minSum, "Min");

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter length of array:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void output(int arr[MAX], int maxLo, int maxHi, int maxSum, const char * msg) {
	printf("\n%s sum sub-array is:-\n", msg);

	printf("Ind:\t");
	for (int i = maxLo; i <= maxHi; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Val:\t");
	for (int i = maxLo; i <= maxHi; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");

	printf("%s sum is:\t%d\n", msg, maxSum);
}

void findMaxSumSubArray(int arr[MAX], int len, int &maxLo, int &maxHi, int &maxSum) {
	int crrLo, crrHi, crrSum;

	crrSum = 0;
	maxSum = 0;
	for (int i = 0; i < len; i++) {
		if (arr[i] + crrSum > 0) {
			if (crrSum == 0) {
				crrLo = crrHi = i;
				crrSum = arr[i];
			} else {
				crrHi = i;
				crrSum += arr[i];
			}

			if (crrSum > maxSum) {
				maxSum = crrSum;
				maxLo = crrLo;
				maxHi = crrHi;
			}
		} else {
			crrSum = 0;
		}
	}
}

void findMinSumSubArray_Me(int arr[MAX], int len, int &minLo, int &minHi, int &minSum) {
	int crrLo, crrHi, crrSum;

	crrSum = 0;
	minSum = 0;
	for (int i = 0; i < len; i++) {
		printf("\nat arr[%d] = %d\tcrrSum = %d\tminSum = %d\n", i, arr[i], crrSum, minSum);

		if (crrSum + arr[i] < 0) {
			if (crrSum = 0) {
				crrLo = crrHi = i;
				crrSum = arr[i];
			} else {
				crrHi = i;
				crrSum += arr[i];
			}
			printf("updated\tcrrLo = %d\tcrrHi = %d\tcrrSum = %d\n", crrLo, crrHi, crrSum);

			if (crrSum < minSum) {
				printf("min values also updated\n");
				minSum = crrSum;
				minLo = crrLo;
				minHi = crrHi;
			}
		} else {
			printf("no updates, crrSum reset to 0\n");
			crrSum = 0;
		}
	}
}

void findMimSumSubArray_Standard(int arr[MAX], int len, int &minLo, int &minHi, int &minSum) {
	int arrCpy[MAX];
	memcpy(arrCpy, arr, sizeof(int) * len);

	for (int i = 0; i < len; i++) {
		arrCpy[i] = -arrCpy[i];
	}

	findMaxSumSubArray(arrCpy, len, minLo, minHi, minSum);
	minSum = -minSum;
}

