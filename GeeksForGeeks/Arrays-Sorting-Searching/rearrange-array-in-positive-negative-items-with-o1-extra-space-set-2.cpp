/* http://www.geeksforgeeks.org/rearrange-array-in-alternating-positive-negative-items-with-o1-extra-space-set-2/
   Approach discussed here used in shifNegatives()
*/

/* Similar complexity but different approach
   http://www.geeksforgeeks.org/rearrange-positive-and-negative-numbers-publish/
   Approach discussed here used in partition()
*/

// Order of elements in output doesn't matter, only negative-positive property should be maintained

/*
6
1 2 3 -4 -1 4

10
-5 -2 5 2 4 7 1 8 0 -8

4
-2 3 4 -1

3
-2 3 1

10
-5 3 4 5 -6 -2 8 9 -1 -4
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int partition(int [MAX], int);
int shiftNegatives(int [MAX], int);
void swap(int [MAX], int, int);
void rearrange(int [MAX], int, int);
void output(int [MAX], int, const char *);

int main() {
	int n;
	int arr[MAX];

	input(arr, n);
	output(arr, n, "input");

	int negPos = shiftNegatives(arr, n);			// either use this
	int negPos = partition(arr, n);					// or use this
	output(arr, n, "shifting");

	rearrange(arr, n, negPos);
	output(arr, n, "re-arrangement");

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

int partition(int arr[MAX], int n) {
	int i, j;

	for (i = -1, j = 0; j < n; j++) {
		if (arr[j] >= 0) {					// equality is critical for correctness
			swap(arr, j, ++i);
		}
	}

	return ++i;
}

int shiftNegatives(int arr[MAX], int n) {
	int startPtr, endPtr;

	for (endPtr = n - 1; endPtr >= 0 && arr[endPtr] < 0; endPtr--);

	for (startPtr = 0; startPtr < endPtr; startPtr++) {
		if (arr[startPtr] < 0) {
			swap(arr, startPtr, endPtr);
			for (endPtr--; endPtr > startPtr && arr[endPtr] < 0; endPtr--);
		}
	}

	return ++endPtr;
}

void swap(int arr[MAX], int ind_1, int ind_2) {
	int temp = arr[ind_1];
	arr[ind_1] = arr[ind_2];
	arr[ind_2] = temp;
}

void rearrange(int arr[MAX], int n, int negPos) {
	for (int i = 0; i < n && negPos < n && arr[i] > 0; i += 2) {
		swap(arr, i, negPos++);
	}
}

void output(int arr[MAX], int n, const char * msg) {
	printf("\nThe array after %s is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

