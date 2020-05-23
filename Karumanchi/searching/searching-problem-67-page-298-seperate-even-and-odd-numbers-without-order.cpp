// Karumanchi, Searching, Problem 67, Page 298

/*
Seperate the even and odd numbers in array, placing even before odd. Order of elements doesn't matter
*/

/*
7
8 1 3 7 4 2 9

7
8 2 4 6 10 12 16

7
9 7 5 17 15 13 11
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void rearrange(int [MAX], int);
void swap(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len, "original");

	rearrange(arr, len);
	showArray(arr, len, "rearranged");

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
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
	int lo = 0;
	int hi = len - 1;

	while (lo < hi) {
		while (arr[lo] % 2 == 0) {
			lo++;
		}

		while (arr[hi] % 2 == 1) {
			hi--;
		}

		if (lo < hi) {
			swap(arr, lo, hi);
			lo++;
			hi--;
		}
	}
}

void swap(int arr[MAX], int i1, int i2) {
	int tmp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = tmp;
}

