// ceiling of element in sorted array:	http://www.geeksforgeeks.org/search-floor-and-ceil-in-a-sorted-array/
// tushar roy's video:	https://www.youtube.com/watch?v=S9oUiVYEq7E
// geeks for geeks' (slightly different explanation): http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void init(int [MAX], int, int);
int findFloorInd(int [MAX], int, int, int);
int findCeilInd(int [MAX], int, int, int);
void showArray(int [MAX], int, const char *);
int findLIS(int [MAX], int, int [MAX], int [MAX]);
void output(int [MAX], int [MAX], int);

int main() {
	int n;
	int arr[MAX];
	int lisLen;
	int seqEndInd[MAX];
	int parInd[MAX];

	input(arr, n);

	init(parInd, n, -1);
	lisLen = findLIS(arr, n, seqEndInd, parInd);

	printf("\nThe length of LIS is:\t%d", lisLen);
	printf("\nThe LIS is:-\n");

	output(arr, parInd, seqEndInd[lisLen - 1]);

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

void init(int arr[MAX], int n, int val) {
	for (int i = 0; i < n; i++) {
		arr[i] = val;
	}
}

// Just for implementation - not needed in LIS
int findFloorInd(int arr[MAX], int lo, int hi, int ele) {
	if (arr[hi] < ele) {
		// element greater than greatest element of array, so floor is the greatest element
		return hi;
	} else if (arr[lo] > ele) {
		// floor of ele doesn't exist in array
		return -1;
	} else {
		// element may or may not be present in array, but it's floor is definitely present
		int mid = (lo + hi) / 2;

		if (arr[mid] < ele) {
			// might have to look leftwards
			if (mid - 1 >= lo && arr[mid - 1] < ele) {
				// found floor
				return mid - 1;
			} else {
				// further search needed
				return findFloorInd(arr, lo, mid - 1, ele);
			}
		} else if (ele == arr[mid]) {
			// might still have to look leftwards for first occurrence of ele in arr[]
			if (mid - 1 >= lo && arr[mid - 1] == ele) {
				// yeah, go leftwards
				return findFloorInd(arr, lo, mid - 1, ele);
			} else {
				// floor found
				return mid;
			}
		} else {
			// might have to go rightwards
			if (mid + 1 <= hi && ele < arr[mid + 1]) {
				// found floor
				return mid;
			} else {
				// further search needed
				return findFloorInd(arr, mid + 1, hi, ele);
			}
		}
	}
}

int findCeilInd(int arr[MAX], int lo, int hi, int ele) {
	// cases where ele lies outside range of elements in array
	// nothing to be done, just return the ceiling index directly
	if (ele < arr[lo]) {
		return lo;
	} else if (ele > arr[hi]) {
		return -1;
	}

	int mid = (lo + hi) / 2;

	if (ele < arr[mid]) {
		// means ceiling either found or towards left of mid
		if ((mid - 1 >= lo) && (arr[mid - 1] < ele)) {
			return mid;
		} else {
			return findCeilInd(arr, lo, mid - 1, ele);
		}
	} else if (ele == arr[mid]) {
		// means ceiling either found or towards left of mid
		// (because there are multiple elements equal to ele in arr[])
		if ((mid - 1 >= lo) && (arr[mid - 1] == ele)) {
			return findCeilInd(arr, 0, mid - 1, ele);
		} else {
			return mid;
		}
	} else {
		// means ceiling either found or is towards right of mid
		if ((mid + 1 <= hi) && (ele <= arr[mid + 1])) {
			return mid + 1;
		} else {
			return findCeilInd(arr, mid + 1, hi, ele);
		}
	}
}

void showArray(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-", msg);

	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}

	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}

	printf("\n");
}

int findLIS(int arr[MAX], int n, int seqEndInd[MAX], int parInd[MAX]) {
	int lisLen;
	int seqEndEle[MAX];

	lisLen = 1;
	seqEndInd[0] = 0;
	seqEndEle[0] = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] > seqEndEle[lisLen - 1]) {
			lisLen++;
			seqEndInd[lisLen - 1] = i;
			seqEndEle[lisLen - 1] = arr[i];
			parInd[i] = seqEndInd[lisLen - 2];
		} else if (arr[i] < seqEndEle[0]) {
			seqEndInd[0] = i;
			seqEndEle[0] = arr[i];
		} else {
			int ceilInd = findCeilInd(seqEndEle, 0, lisLen - 1, arr[i]);
			seqEndInd[ceilInd] = i;
			seqEndEle[ceilInd] = arr[i];
			parInd[i] = seqEndInd[ceilInd - 1];
		}
	}

	return lisLen;
}

void output(int arr[MAX], int parInd[MAX], int crrInd) {
	if (parInd[crrInd] == -1) {
		printf("%d ", arr[crrInd]);
	} else {
		output(arr, parInd, parInd[crrInd]);
		printf("%d ", arr[crrInd]);
	}
}
