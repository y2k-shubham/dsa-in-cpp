// http://www.geeksforgeeks.org/rearrange-array-alternating-positive-negative-items-o1-extra-space/
// Order of elements should be preserved

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
#define isEven(n) ((n % 2 == 0) ? true : false)

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void rearrange(int [MAX], int);
int findFirstEle(int [MAX], int, int, bool);
void rotateRight(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len, "Original");

	rearrange(arr, len);
	showArray(arr, len, "Rearranged");

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

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void rearrange(int arr[MAX], int len) {
	for (int i = 0; i < len - 1; i++) {
		int j = -1;

		if (arr[i] >= 0 && isEven(i)) {
			j = findFirstEle(arr, i + 1, len - 1, false);
		} else if (arr[i] < 0 && !isEven(i)) {
			j = findFirstEle(arr, i + 1, len - 1, true);
		}

		if (j > 0) {
			rotateRight(arr, i, j);
		}
	}
}

int findFirstEle(int arr[MAX], int lo, int hi, bool positive) {
	for (int i = lo; i <= hi; i++) {
		if (positive && arr[i] >= 0) {
			return i;
		} else if (!positive && arr[i] < 0) {
			return i;
		}
	}

	return -1;
}

void rotateRight(int arr[MAX], int lo, int hi) {
	int tmp = arr[hi];

	for (int i = hi; i > lo; i--) {
		arr[i] = arr[i - 1];
	}

	arr[lo] = tmp;
}

