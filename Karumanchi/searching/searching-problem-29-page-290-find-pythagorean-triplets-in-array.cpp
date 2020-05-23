// Karumanchi, Searching, Problem 29, Page 290
// Time: O(n^2)		Space: (sorting space) O(logN)

/*
9
5 15 17 12 13 8 6 9 10
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100

void input(pair <int, int> [MAX], int &);
void quickSort(pair <int, int> [MAX], int, int);
int partition(pair <int, int> [MAX], int, int);
void swap(pair <int, int> [MAX], int, int);
void showTriplets(pair <int, int> [MAX], int);
void showArray(pair <int, int> [MAX], int, const char *);

int main() {
	pair <int, int> arr[MAX];
	int len;

	input(arr, len);
	showArray(arr, len, "original");

	quickSort(arr, 0, len - 1);
	showArray(arr, len, "sorted");

	showTriplets(arr, len);

	return 0;
}

void input(pair <int, int> arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		int ele;
		cin >> ele;

		arr[i].first = i;
		arr[i].second = ele;
	}
}

void quickSort(pair <int, int> arr[MAX], int lo, int hi) {
	if (lo < hi) {
		int pInd = partition(arr, lo, hi);
		quickSort(arr, lo, pInd - 1);
		quickSort(arr, pInd + 1, hi);
	}
}

int partition(pair <int, int> arr[MAX], int lo, int hi) {
	int pEle = arr[hi].second;
	int i, j;

	for (i = lo - 1, j = lo; j < hi; j++) {
		if (arr[j].second < pEle) {
			++i;
			swap(arr, i, j);
		}
	}

	++i;
	swap(arr, i, j);

	return i;
}

void swap(pair <int, int> arr[MAX], int i1, int i2) {
	pair <int, int> tmp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = tmp;
}

void showArray(pair <int, int> arr[MAX], int len, const char * msg) {
	printf("\nThe %s array is :-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		if (strcmp(msg, "sorted") == 0) {
			printf("[%d]\t", arr[i].first);
		} else {
			printf("[%d]\t", i);
		}
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i].second);
	}
	cout << endl;
}

void showTriplets(pair <int, int> arr[MAX], int len) {
	printf("Pythagorean triplets in array are:-\n");
	for (int i = 2; i < len; i++) {
		int reqSqrSum = (int) (ceil(pow(arr[i].second, 2)));
		int j, k;

		for (j = 0, k = i - 1; j < k; ) {
			int crrSqrSum = (int) (ceil(pow(arr[j].second, 2))) + (int) (ceil(pow(arr[k].second, 2)));

			if (crrSqrSum < reqSqrSum) {
				j++;
			} else if (crrSqrSum > reqSqrSum) {
				k--;
			} else {
				printf("arr[%d] = %d\tarr[%d] = %d\tarr[%d] = %d\n", arr[j].first, arr[j].second, arr[k].first, arr[k].second, arr[i].first, arr[i].second);
				break;
			}
		}
	}
}

