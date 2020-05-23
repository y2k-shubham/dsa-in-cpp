// http://www.geeksforgeeks.org/rearrange-array-maximum-minimum-form/
// constraints: input array contains sorted list of positive integers only (zero not included)
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void rearrange(int [MAX], int);
void makePositive(int [MAX], int);
void output(int [MAX], int, const char *);

int main() {
	int n;
	int arr[MAX];

	input(arr, n);
	output(arr, n, "original");

	sort(arr, arr + n);
	output(arr, n, "sorted");

	rearrange(arr, n);
	makePositive(arr, n);
	output(arr, n, "rearranged");

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of elements:\t");
	scanf("%d", &n);

	printf("Enter elements of array one-by-one:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void rearrange(int arr[MAX], int n) {
	for (int i = 0; i < n; i++) {
		// read the current element
		int crr = arr[i];

		while (crr > 0) {
			// if positive, it needs to be processed. so calculate it's new position j
			int j = (i < (n / 2)) ? ((2 * i) + 1) : (2 * (n - i - 1));

			// if element is already at correct position, terminate the loop
			if (i == j) {
				arr[i] = -arr[i];
				break;
			}

			// now replace variable crr with element which is currently at it's designated position
			swap(crr, arr[j]);

			// make arr[j] negative as it has moved to it's correct position
			arr[j] = -arr[j];

			// now i becomes j and our current element therefore becomes arr[j]
			i = j;
		}
	}
}

void makePositive(int arr[MAX], int n) {
	for (int i = 0; i < n; i++) {
		if (arr[i] < 0) {
			arr[i] = -arr[i];
		}
	}
}

void output(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
