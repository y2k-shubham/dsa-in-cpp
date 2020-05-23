// http://www.geeksforgeeks.org/find-all-triplets-in-a-sorted-array-that-forms-geometric-progression/

/*
6
1 2 6 10 18 54

8
2 8 10 15 16 30 32 64

6
1 2 6 18 36 54
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
void showTriplets(int [MAX], int);
void findACforGivenB(int [MAX], int, int, int, int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len);

	showTriplets(arr, len);

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
	for (int i =  0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTriplets(int arr[MAX], int len) {
	printf("\nTriplets in Geometric progression are:-\n");
	for (int i = 1; i < len - 1; i++) {
		findACforGivenB(arr, i, 0, i - 1, i + 1, len - 1);
	}
}

void findACforGivenB(int arr[MAX], int meanInd, int lLo, int lHi, int rLo, int rHi) {
	int meanVal = arr[meanInd];
	int reqProd = meanVal * meanVal;

//	printf("\n============================\n");
//	printf("meanVal = a[%d] = %d\n", meanInd, meanVal);
	int lPtr, rPtr;
	for (lPtr = lLo, rPtr = rHi; lPtr <= lHi && rPtr >= rLo; ) {
//		printf("\narr[%d .. %d] = (%d .. %d)\t", lPtr, lHi, arr[lPtr], arr[lHi]);
//		printf("arr[%d .. %d] = (%d .. %d)\n", rLo, rPtr, arr[rLo], arr[rPtr]);

		if (arr[lPtr] * arr[rLo] > reqProd || arr[lHi] * arr[rPtr] < reqProd) {
			// can't obtain required product
//			printf("can't obtain required product %d, returning\n", reqProd);
			return;
		}
		int crrProd = arr[lPtr] * arr[rPtr];

		if (crrProd < reqProd) {
//			printf("(crrProd = %d) < (reqProd = %d), incrementing lPtr\n", crrProd, reqProd);
			lPtr++;
		} else if (crrProd > reqProd) {
//			printf("(crrProd = %d) > (reqProd = %d), decrementing rPtr\n", crrProd, reqProd);
			rPtr--;
		} else {
			// found
			printf("(a[%d] = %d)\t", lPtr, arr[lPtr]);
			printf("(a[%d] = %d)\t", meanInd, meanVal);
			printf("(a[%d] = %d)\n", rPtr, arr[rPtr]);
			lPtr++;
			rPtr--;
		}
	}

//	printf("\nexiting normally\n");
}

