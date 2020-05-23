// http://www.practice.geeksforgeeks.org/problem-page.php?pid=819
// WRONG PROGRAM

/*
15

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

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findPivot(int [MAX], int, int);
int binSearch(int [MAX], int, int, int);

int main() {
	int t;

	printf("Enter no of test cases:\t");
	scanf("%d", &t);

	while (t-- > 0) {
		int arr[MAX];
		int n;
		int pivotInd;

		input(arr, n);
		//pivotInd = findPivot(arr, 0, n - 1);
		pivotInd = binSearch(arr, n, 0, n - 1);

		if (pivotInd >= 0) {
			printf("The pivot element is arr[%d] = %d\n", pivotInd, arr[pivotInd]);
		} else {
			printf("No pivot element found, array is normally sorted\n");
		}
	}

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("\nEnter length of array:\t");
	scanf("%d", &n);

	printf("Enter elements of array one-by-one:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

int findPivot(int arr[MAX], int lo, int hi) {
	if (lo > hi) {
		return -1;
	} else {
		int mid = (lo + hi) / 2;

		if ((lo < mid && arr[mid - 1] > arr[mid]) && ((mid == hi) || (mid < hi && arr[mid] < arr[mid + 1]))) {
			printf("arr[%d] = %d found here 1\n", mid, arr[mid]);
			return mid;
		} else if (mid < hi && arr[mid] > arr[mid + 1]) {
			printf("arr[%d] = %d found here 2\n", (mid + 1), arr[mid + 1]);
			return mid + 1;
		} else if (arr[lo] < arr[mid]) {
			return findPivot(arr, mid + 1, hi);
		} else {
			return findPivot(arr, lo, mid - 1);
		}
	}
}

int binSearch(int arr[MAX], int n, int lo, int hi) {
	if (lo == hi) {
		int lEle = (0 < lo) ? arr[lo - 1] : INT_MAX;
		int rEle = (hi < n - 1) ? arr[hi + 1] : INT_MIN;

		if (lEle > arr[lo] && arr[lo] < rEle) {
			return lo;
		} else {
			return -1;
		}
	} else {
		int mid = (lo + hi) / 2;

		if (arr[lo] < arr[mid] && arr[mid] < arr[hi]) {
			return -1;
		} else if (arr[lo] < arr[mid]) {
			return binSearch(arr, n, mid + 1, hi);
		} else {
			return binSearch(arr, n, lo, mid);
		}
	}
}

