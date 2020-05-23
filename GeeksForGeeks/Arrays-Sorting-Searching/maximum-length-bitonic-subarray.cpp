// http://www.practice.geeksforgeeks.org/problem-page.php?pid=578
// http://www.geeksforgeeks.org/maximum-length-bitonic-subarray/

/*
8
20 10 1 2 3 4 2 10

7
8 1 3 7 4 2 9
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int&);
void findIncLen(int [MAX], int, int [MAX], int [MAX]);
void showLongestBitonicSubarray(int [MAX], int, int [MAX], int [MAX]);

int main() {
	int n;
	int arr[MAX];
	int incLen_left[MAX];
	int incLen_right[MAX];

	input(arr, n);
	findIncLen(arr, n, incLen_left, incLen_right);
	showLongestBitonicSubarray(arr, n, incLen_left, incLen_right);

	return 0;
}

void input(int arr[MAX], int& n) {
	printf("Enter length of array:\t");
	scanf("%d", &n);

	printf("Enter the array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void findIncLen(int arr[MAX], int n, int incLen_left[MAX], int incLen_right[MAX]) {
	int prevEle;

	// calculate length of increasing subsequence from left
	incLen_left[0] = 1;
	prevEle = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > arr[i - 1]) {
			incLen_left[i] = incLen_left[i - 1] + 1;
		} else {
			incLen_left[i] = 1;
		}
	}

	// calculate length of increasing subsequence from right
	incLen_right[n - 1] = 1;
	prevEle = arr[n - 1];
	for (int i = n - 2; i >= 0; i--) {
		if (arr[i] > arr[i + 1]) {
			incLen_right[i] = incLen_right[i + 1] + 1;
		} else {
			incLen_right[i] = 1;
		}
	}
}

void showLongestBitonicSubarray(int arr[MAX], int n, int incLen_left[MAX], int incLen_right[MAX]) {
	int maxLen;
	int maxLenInd_left;
	int maxLenInd_right;

	maxLen = 0;
	for (int i = 0; i < n; i++) {
		if (incLen_left[i] + incLen_right[i] - 1 > maxLen) {
			maxLen = incLen_left[i] + incLen_right[i] - 1;
			maxLenInd_left = i - incLen_left[i] + 1;
			maxLenInd_right = i + incLen_right[i] - 1;
		}
	}

	printf("\nThe length of longest bitonic subarray is %d:-\n", maxLen);
	for (int i = maxLenInd_left; i <= maxLenInd_right; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
