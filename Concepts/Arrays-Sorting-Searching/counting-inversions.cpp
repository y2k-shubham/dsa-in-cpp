// http://www.geeksforgeeks.org/counting-inversions/

/*
5
2 4 1 3 5

5
1 20 6 4 5
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void output(int [MAX], int, const char *);
int mergeSort(int [MAX], int, int);
int merge(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	output(arr, len, "input");

	int invCount = mergeSort(arr, 0, len - 1);

	output(arr, len, "sorting");
	printf("\nInversion count of array is %d\n", invCount);

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

void output(int arr[MAX], int n, const char * msg) {
	printf("\nThe array after %s is:-\n", msg);

	printf("Ind:\t");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

int mergeSort(int arr[MAX], int lo, int hi) {
	if (hi > lo) {
		int mid = (lo + hi) / 2;

		int c1 = mergeSort(arr, lo, mid);
		int c2 = mergeSort(arr, mid + 1, hi);

		int c3 = merge(arr, lo, hi);

		return (c1 + c2 + c3);
	} else {
		return 0;
	}
}

int merge(int arr[MAX], int lo, int hi) {
	int aux[MAX];
	int i, j, k, mid;
	int lim_1, lim_2;
	int invCount;

	mid = (lo + hi) / 2;
	lim_1 = mid;
	lim_2 = hi;

	i = lo;
	j = lim_1 + 1;
	k = 0;

	invCount = 0;
	for (; i <= lim_1 && j <= lim_2; ) {
		if (arr[i] <= arr[j]) {
			aux[k++] = arr[i++];
		} else {
			aux[k++] = arr[j++];
			invCount += lim_1 - i + 1;
		}
	}

	while (i <= lim_1) {
		aux[k++] = arr[i++];
	}

	while (j <= lim_2) {
		aux[k++] = arr[j++];
	}

	for (k = 0, i = lo; i <= lim_2; i++, k++) {
		arr[i] = aux[k];
	}

	return invCount;
}

