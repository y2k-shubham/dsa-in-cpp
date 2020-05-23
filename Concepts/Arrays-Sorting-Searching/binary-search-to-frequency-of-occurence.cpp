/*
12
0 0 1 1 1 3 5 7 7 9 9 9
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
int binarySearch(int [MAX], int, int, int);

int main() {
	int n;
	int arr[MAX];
	int ele;

	input(arr, n, ele);
	printf("\nfreq of occurence = %d\n", binarySearch(arr, 0, n - 1, ele));

	return 0;
}

void input(int arr[MAX], int &n, int &ele) {
	printf("Enter no of elements in array:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	printf("Enter element to be searched:\t");
	scanf("%d", &ele);
}

int binarySearch(int arr[MAX], int lo, int hi, int ele) {
	if (lo > hi) {
		return 0;
	} else {
		int mid = (lo + hi) / 2;

		if (ele < arr[mid]) {
			return binarySearch(arr, lo, mid - 1, ele);
		} else if (ele > arr[mid]) {
			return binarySearch(arr, mid + 1, hi, ele);
		} else {
			int lFreq = binarySearch(arr, lo, mid - 1, ele);
			int rFreq = binarySearch(arr, mid + 1, hi, ele);

			return lFreq + rFreq + 1;
		}
	}
}
