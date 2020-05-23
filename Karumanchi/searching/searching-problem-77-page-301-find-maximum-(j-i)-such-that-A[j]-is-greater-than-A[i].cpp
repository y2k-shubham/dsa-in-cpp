// Karumanchi, Searching, problem 77, page 301

/*
7
8 1 3 7 4 2 9

7
3 8 7 4 9 1 2

7
8 1 3 7 9 4 2
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void calcLMin(int [MAX], int, int [MAX]);
void calcRMax(int [MAX], int, int [MAX]);
void findSoln(int [MAX], int, int [MAX], int [MAX]);

int main() {
	int arr[MAX], len;
	int lMin[MAX], rMax[MAX];

	input(arr, len);
	showArray(arr, len, "original");

	calcLMin(arr, len, lMin);
	calcRMax(arr, len, rMax);

	findSoln(arr, len, lMin, rMax);

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:\t");
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void calcLMin(int arr[MAX], int len, int lMin[MAX]) {
	int minTillNow = INT_MAX;

	for (int i = 0; i < len; i++) {
		minTillNow = min(minTillNow, arr[i]);
		lMin[i] = minTillNow;
	}
}

void calcRMax(int arr[MAX], int len, int rMax[MAX]) {
	int maxTillNow = INT_MIN;

	for (int i = len - 1; i >= 0; i--) {
		maxTillNow = max(maxTillNow, arr[i]);
		rMax[i] = maxTillNow;
	}
}

void findSoln(int arr[MAX], int len, int lMin[MAX], int rMax[MAX]) {
	int i, j;
	int maxDiff, mDiffI, mDiffJ;

	maxDiff = -1;
	for (i = j = 0; i < len && j < len; ) {
		if (lMin[i] >= rMax[j]) {
			i++;
		} else {
			if (maxDiff < j - i) {
				maxDiff = j - i;
				mDiffI = i;
				mDiffJ = j;
			}

			j++;
		}
	}

	printf("\nmax(j - i), such that A[j] > A[i] is:-\n");
	printf("(j - i) = (%d - %d) = %d\nfor A[i] = A[%d] = %d\tand\nA[j] = A[%d] = %d\n", mDiffJ, mDiffI, (mDiffJ - mDiffI), mDiffI, arr[mDiffI], mDiffJ, arr[mDiffJ]);
}

