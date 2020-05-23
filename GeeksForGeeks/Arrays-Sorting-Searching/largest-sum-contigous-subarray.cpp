// http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
// assumption:	sum should include at-least single element of array
//				(you can't have zero as answer when all elements are negative)

/*
6

8
2 3 -8 -1 2 4 -2 3

9
8 -1 -3 7 4 -9 -19 64 128

8
8 -1 -3 7 4 -9 -19 10

8
8 -1 -3 7 4 -9 -19 16

4
-39 -69 -18 -45

4
-39 0 -69 -45
*/

#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void findMaxSumSubarray(int [MAX], int, int &, int &, int &);
void output(int [MAX], int, int);

int main() {
	int t;

	cin >> t;
	while (t-- > 0) {
		int arr[MAX], len;
		int maxSum, maxIndL, maxIndR;

		cout << endl << "======================" << endl;
		input(arr, len);

		findMaxSumSubarray(arr, len, maxSum, maxIndL, maxIndR);

		output(arr, maxIndL, maxIndR);
	}

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void findMaxSumSubarray(int arr[MAX], int len, int &maxSum, int &maxIndL, int &maxIndR) {
	int crrSum, crrIndL, crrIndR;

	maxSum = INT_MIN;
	crrSum = 0;
	maxIndL = maxIndR = -1;

	for (int i = 0; i < len; i++) {
		if (crrSum == 0) {
			crrSum = arr[i];
			crrIndL = crrIndR = i;
		} else {
			crrSum += arr[i];
			crrIndR = i;
		}

		if (crrSum > maxSum) {
			maxSum = crrSum;
			maxIndL = crrIndL;
			maxIndR = crrIndR;
		}

		if (crrSum < 0) {
			crrSum = 0;
			crrIndL = crrIndR = -1;
		}
	}
}

void output(int arr[MAX], int mIndL, int mIndR) {
	if (mIndL < 0) {
		printf("\nThere's no subarray with positive sum\n");
	} else {
		int sum = 0;

		printf("\nMaximum sum subarray is:-\n");
		for (int i = mIndL; i <= mIndR; i++) {
			printf("%d ", arr[i]);
			sum += arr[i];
		}
		printf("\nSum of maximum sum-subarray is %d\n", sum);
	}
}

