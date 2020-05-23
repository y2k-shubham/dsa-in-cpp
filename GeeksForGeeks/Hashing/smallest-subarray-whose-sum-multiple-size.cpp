// http://www.geeksforgeeks.org/smallest-subarray-whose-sum-multiple-size/

/*
6
1 1 2 2 4 2
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <climits>

using namespace std;

#define MAX_LEN 100

void input(int [MAX_LEN], int &);
void init(int [MAX_LEN]);
void showArr(int [MAX_LEN], int);
void findSubArr(int [MAX_LEN], int, int [MAX_LEN]);

int main() {
	int arr[MAX_LEN], len;
	int modInd[MAX_LEN];		// used as a map

	input(arr, len);
	init(modInd);

	showArr(arr, len);
	findSubArr(arr, len, modInd);

	return 0;
}

void input(int Arr[MAX_LEN], int &N) {
	printf("Enter length of array:-\n");
	scanf("%d", &N);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < N; i++) {
		scanf("%d", &Arr[i]);
	}
}

void init(int arr[MAX_LEN]) {
	for (int i = 0; i < MAX_LEN; i++) {
		arr[i] = INT_MAX;
	}
}

void showArr(int Arr[MAX_LEN], int N) {
	printf("\nThe array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < N; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < N; i++) {
		printf("%d\t", Arr[i]);
	}
	printf("\n");
}

void findSubArr(int arr[MAX_LEN], int N, int modInd[MAX_LEN]) {
	int minLen, minLIndL, minLIndR;
	int sum;

	sum = 0;
	modInd[0] = -1;
	minLen = INT_MAX;

	for (int i = 0; i < N; i++) {
		sum += arr[i];
		int crrMod = sum % N;

		if (modInd[crrMod] < N) {
			int crrLen = i - modInd[crrMod];
			if (crrLen < minLen) {
				minLen = crrLen;
				minLIndL = modInd[crrMod] + 1;
				minLIndR = i;
			}
		}

		modInd[crrMod] = i;
	}

	if (minLen != INT_MAX) {
		printf("\nSmallest subarray having sum which is multiple of arr[] length %d is arr[%d .. %d] of length %d\n", N, minLIndL, minLIndR, minLen);
	} else {
		printf("\nNo subarray has sum which is multiple of arr[] length %d\n", N);
	}
}

