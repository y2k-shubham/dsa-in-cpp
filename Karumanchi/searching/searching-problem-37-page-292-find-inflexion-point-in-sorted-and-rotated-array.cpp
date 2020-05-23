// correct code, but complicated as hell

/*
5
10 15 20 0 5

5
50 5 20 30 40

9
5 9 13 19 31 47 56 85 197

9
85 197 5 9 13 19 31 47 56

9
19 31 47 56 85 197 5 9 13

7
2 2 2 2 5 -1 0

7
5 -1 0 2 2 2 2

7
2 5 -1 0 2 2 2

7
2 2 2 2 2 2 2

5
4 5 1 2 3

5
1 2 3 4 5

5
5 1 2 3 4

5
3 4 5 1 2

5
2 3 4 5 1

5
1 2 3 4 5
*/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findInflexion(int [MAX], int, int);
int findPivot(int [MAX], int, int);

int siz;

int main() {
	int arr[MAX], len;

	input(arr, len);
	siz = len;

	int ind = findInflexion(arr, 0, len - 1);
	if (ind >= 0) {
		printf("\nInflexion point is arr[%d] = %d\n", ind, arr[ind]);
	} else {
		printf("\nArray isn't rotated\n");
	}

	ind = findPivot(arr, 0, len - 1);
	if (ind >= 0 && ind != len - 1) {
		printf("Pivot is arr[%d] = %d\n", ind, arr[ind]);
	} else {
		printf("Array isn't rotated\n");
	}

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

// accounts for repetition
int findInflexion(int arr[MAX], int lo, int hi) {
	if (lo > hi) {
//		printf("\nlo = %d\thi = %d\treturned -1\n", lo, hi);
		return -1;
	} else {
		int mid = (lo + hi) / 2;
//		printf("\narr[lo] = arr[%d] = %d\tarr[mid] = arr[%d] = %d\tarr[hi] = arr[%d] = %d\n", lo, arr[lo], mid, arr[mid], hi, arr[hi]);

		if (arr[lo] <= arr[mid] && arr[mid] <= arr[hi]) {
			if (mid - 1 >= 0 && arr[mid] < arr[mid - 1]) {
//				printf("returned arr[mid - 1] = arr[%d] = %d\n", (mid - 1), arr[mid - 1]);
				return mid - 1;
			} else if (mid + 1 <= siz - 1 && arr[mid + 1] < arr[mid]) {
//				printf("returned arr[mid] = arr[%d] = %d\n", mid, arr[mid]);
				return mid;
			} else {
//				printf("returned -1\n");
				return -1;
			}
		} else if (arr[lo] < arr[mid]) {
			if (mid + 1 <= hi && arr[mid + 1] < arr[mid]) {
//				printf("returned arr[mid] = arr[%d] = %d\n", mid, arr[mid]);
				return mid;
			} else {
//				printf("going rightwards\n");
				return findInflexion(arr, mid + 1, hi);
			}
		} else if (arr[mid] < arr[hi]) {
			if (mid - 1 >= lo && arr[mid] < arr[mid - 1]) {
//				printf("returned arr[mid - 1] = arr[%d] = %d\n", (mid - 1), arr[mid - 1]);
				return mid - 1;
			} else {
//				printf("going leftwards\n");
				return findInflexion(arr, lo, mid - 1);
			}
		} else if (arr[mid] == arr[lo]) {
			if (arr[hi] != arr[mid]) {
//				printf("going rightwards as left is all equal\n");
				return findInflexion(arr, mid + 1, hi);
			} else {
//				printf("trying 1st possibility left\n");
				int lInd = findInflexion(arr, lo, mid - 1);
				if (lInd > 0) {
//					printf("1st possibility left valid, returning arr[lInd] = arr[%d] = %d\n", lInd, arr[lInd]);
					return lInd;
				} else {
//					printf("1st possibility invalid, going rightwards\n");
					return findInflexion(arr, mid + 1, hi);
				}
			}
		} else {
			if (arr[lo] != arr[mid]) {
//				printf("going leftwards as right is all equal\n");
				return findInflexion(arr, lo, mid - 1);
			} else {
//				printf("trying 1st possibility right\n");
				int rInd = findInflexion(arr, mid + 1, hi);
				if (rInd > 0) {
//					printf("1st possibility right valid, returning arr[rInd] = arr[%d] = %d\n", rInd, arr[rInd]);
					return rInd;
				} else {
//					printf("1st possibility invalid, going leftwards\n");
					return findInflexion(arr, lo, mid - 1);
				}
			}
		}
	}
}

// considers only unique elements in array
int findPivot(int arr[MAX], int lo, int hi) {
	if (lo > hi) {
		return -1;
	} else if (lo == hi) {
		return lo;
	} else if (lo == hi - 1) {
		if (arr[lo] > arr[hi]) {
			return lo;
		} else {
			return hi;
		}
	} else {
		int mid = (lo + hi) / 2;

		if (arr[lo] < arr[mid]) {
			return findPivot(arr, mid, hi);
		} else {
			return findPivot(arr, lo, mid);
		}
	}
}

