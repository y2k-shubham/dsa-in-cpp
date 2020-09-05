// http://www.geeksforgeeks.org/find-a-triplet-that-sum-to-a-given-value/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=732

/*
Time:  O(n^2)
Space: depends on sorting algorithm used, no extra space needed otherwise
*/

/*
6
12 3 4 1 6 9
24

10
-12 12 6 0 4 2 7 5 11 -1
6

27
174 430 405 706 627 813 376 94 566 37 737 142 815 995 257 653 937 839 483 356 16 132 231 842 626 12 638
1107
*/

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void findTriplet(int [MAX], int, int);
void showArray(int [MAX], int, const char *);

int main() {
	int arr[MAX], len;
	int reqSum;

	input(arr, len, reqSum);
	showArray(arr, len, "Original");

	sort(arr, arr + len);
	showArray(arr, len, "Sorted");

	findTriplet(arr, len, reqSum);

	return 0;
}

void input(int arr[MAX], int &len, int &reqSum) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-" << endl;
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}

	cout << "Enter required sum:\t";
	cin >> reqSum;
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("%s array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl << endl;
}

void findTriplet(int arr[MAX], int len, int reqSum) {
	for (int i = 0; i < len - 2; i++) {
		int remSum = reqSum - arr[i];
		int j, k;

		j = i + 1;
		k = len - 1;
		for (; j < k; ) {
			int crrSum = arr[j] + arr[k];

			if (crrSum < remSum) {
				j++;
			} else if (crrSum > remSum) {
				k--;
			} else {
				break;
			}
		}

		if (j < k) {
			printf("arr[%d] = %d\tarr[%d] = %d\tarr[%d] = %d\tadd to %d\n", i, arr[i], j, arr[j], k, arr[k], reqSum);
		}
	}
}

