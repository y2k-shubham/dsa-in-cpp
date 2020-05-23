// Karumanchi, Searching, problem 37, page 292

/*
7
1 2 3 4 0 -1 -1

7
1 2 4 4 0 -1 -1

7
1 2 3 4 0 0 -1

7
2 2 2 2 2 2 2

7
10 20 30 40 50 60 70

7
9 8 7 6 5 4 3
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findMaxInd(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);

	int ind = findMaxInd(arr, 0, len - 1);
	if (ind >= 0) {
		printf("\nGreatest element is arr[%d] = %d\n", ind, arr[ind]);
	} else {
		printf("\nMore than one greatest elements present in array\n");
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

int findMaxInd(int arr[MAX], int lo, int hi) {
	if (lo > hi) {
		// error
		return -1;
	} else if (lo == hi) {
		// single element left, should be maximum
		return lo;
	} else if (lo == hi - 1) {
		// two elements left, return index of maximum
		if (arr[lo] > arr[hi]) {
			return lo;
		} else {
			return hi;
		}
	} else {
		// three or more elements left, recurse
		int mid = (lo + hi) / 2;

		if (arr[mid - 1] < arr[mid] && arr[mid] < arr[mid + 1]) {
			return findMaxInd(arr, mid + 1, hi);
		} else if (arr[mid - 1] > arr[mid] && arr[mid] > arr[mid + 1]) {
			return findMaxInd(arr, lo, mid - 1);
		} else if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1]) {
			// found max element
			return mid;
		} else {
			// god knows what
			return -1;
		}
	}
}

