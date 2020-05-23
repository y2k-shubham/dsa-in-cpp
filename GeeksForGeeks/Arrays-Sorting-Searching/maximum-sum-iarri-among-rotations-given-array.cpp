// http://www.geeksforgeeks.org/maximum-sum-iarri-among-rotations-given-array/

/*
4
8 3 1 2

4
1 2 8 3
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
int findSum(int [MAX], int);
void findMaxProdSum(int [MAX], int, int, int &, int &);
void showMaxRotation(int [MAX], int, int);

int main() {
	int arr[MAX], len;
	int sum;
	int maxSum, maxSumInd;

	input(arr, len);
	showArray(arr, len);

	sum = findSum(arr, len);
	findMaxProdSum(arr, len, sum, maxSum, maxSumInd);

	cout << "\nMaximum sum of any rotation of array is:\t" << maxSum << endl;
	showMaxRotation(arr, len, maxSumInd);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

int findSum(int arr[MAX], int len) {
	int sum = 0;

	for (int i = 0; i < len; i++) {
		sum += arr[i];
	}

	return sum;
}

void findMaxProdSum(int arr[MAX], int len, int sum, int &maxSum, int &maxSumInd) {
	maxSum = 0;
	maxSumInd = 0;

	// find sum in initial configuration
	for (int i = 0; i < len; i++) {
		maxSum += arr[i] * i;
	}

	// find sums of other configurations (rotations) and take maximum
	int prevSum = maxSum;
	for (int i = 0; i < len - 1; i++) {
		int crrSum = prevSum + (arr[i] * (len - 1)) - (sum - arr[i]);
		if (crrSum > maxSum) {
			maxSum = crrSum;
			maxSumInd = i;
		}

		prevSum = crrSum;
	}
}

void showMaxRotation(int arr[MAX], int len, int maxSumInd) {
	int ctr, i;

	printf("\nRotation that yields maximum sum is:-\n");
	maxSumInd = maxSumInd + 1;

	cout << "Ind:\t";
	for (ctr = 1, i = maxSumInd; ctr <= len; ctr++, i = (i + 1) % len) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (ctr = 1, i = maxSumInd; ctr <= len; ctr++, i = (i + 1) % len) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

