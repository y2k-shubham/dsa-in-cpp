#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void output(int [MAX], int, const char *);
void mergeSort(int [MAX], int, int);
void merge(int [MAX], int, int, int);

int main() {
	int n;
	int arr[MAX];

	input(arr, n);
	output(arr, n, "original");

	mergeSort(arr, 0, n - 1);
	output(arr, n, "sorted");

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

void output(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void mergeSort(int arr[MAX], int lo, int hi) {
	if (lo < hi) {
		int mid = (lo + hi) / 2;

		mergeSort(arr, lo, mid);
		mergeSort(arr, mid + 1, hi);

		merge(arr, lo, mid, hi);
	}
}

void merge(int arr[MAX], int lo, int mid, int hi) {
	int i, j, k;
	int buffer[hi - lo + 1];

	i = lo;
	j = mid + 1;
	k = 0;

	for (; (i <= mid) && (j <= hi); k++) {
		if (arr[i] <= arr[j]) {
			buffer[k] = arr[i++];
		} else {
			buffer[k] = arr[j++];
		}
	}

	while (i <= mid) {
		buffer[k++] = arr[i++];
	}

	while (j <= hi) {
		buffer[k++] = arr[j++];
	}

	for (k = 0, i = lo; i <= hi; i++, k++) {
		arr[i] = buffer[k];
	}
}
