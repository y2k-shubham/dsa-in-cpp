// Page 328, 9.3
// n = 11
// -40 -20 -1 1 2 3 5 7 8 12 13
// -40 -20 1 1 2 2 5 7 8 10 10

#include <stdio.h>
#define minVal(a, b) ((a < b) ? a : b)
#define maxVal(a, b) ((a > b) ? a : b)

void input(int *, int);
void findMagicInd(int *, int, int);
void findMagicIndNonDistinct(int *, int, int);

int main() {
	int n;

	printf("Enter n:\t");
	scanf("%d", &n);

	int arr[n];

	input(&arr[0], n);
	printf("\nMagic indices are:-\n");
	findMagicIndNonDistinct(&arr[0], 0, n - 1);

	return 0;
}

void input(int * arr, int n) {
	int i;
	printf("Enter sorted array of %d integers:-\n", n);
	for (i = 0; i < n; i++) {
		scanf("%d", (arr + i));
	}
}

void findMagicInd(int * arr, int lo, int hi) {
	if (lo <= hi) {
		int mid = (lo + hi) / 2;

		if (arr[mid] == mid) {
			printf("arr[%d] = %d\n", mid, mid);
			findMagicInd(arr, lo, mid - 1);
			findMagicInd(arr, mid + 1, hi);
		} else if (arr[mid] < mid) {
			findMagicInd(arr, mid + 1, hi);
		} else {
			findMagicInd(arr, lo, mid - 1);
		}
	}
}

void findMagicIndNonDistinct(int * arr, int lo, int hi) {
	if (lo <= hi) {
		int mid = (lo + hi) / 2;

		if (arr[mid] == mid) {
			printf("arr[%d] = %d\n", mid, mid);
			findMagicIndNonDistinct(arr, lo, mid - 1);
			findMagicIndNonDistinct(arr, mid + 1, hi);
		} else {
			findMagicIndNonDistinct(arr, lo, minVal((mid - 1), arr[mid]));
			findMagicIndNonDistinct(arr, maxVal((mid + 1), arr[mid]), hi);
		}
	}
}
