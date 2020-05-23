#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 200

void input(int [MAX], int &, const char *, char);
int search(int [MAX], int, int, int, int);

int main() {
	int m, n;
	int X[MAX], Y[MAX];
	int count;

	input(X, m, "first", 'X');
	input(Y, n, "second", 'Y');

	sort(X, X + m);
	sort(Y, Y + n);

	count = 0;
	for (int i = 0; i < n; i++) {
		int ind = search(X, m, 0, m - 1, Y[i]);

		while (ind < m && X[ind] == Y[i]) {
			ind++;
		}

		if (ind < m) {
			count += m - ind + 1;
		}
	}

	printf("No of pairs such that x^y > y^x is %d\n", count);

	return 0;
}

void input(int arr[MAX], int &len, const char * msg, char name) {
	printf("\nEnter size of %s array %c[]:\t", msg, name);
	scanf("%d", &len);

	printf("Enter elements of %s array %c[] one-by-one:-\n", msg, name);
	for (int i = 0; i < len; i++) {
		scanf("%d", &arr[i]);
	}
}

int search(int arr[MAX], int len, int lo, int hi, int ele) {
	if (lo > hi) {
		if (hi < 0) {
			return 0;
		} else if (lo == len) {
			return len;
		} else {
			return lo;
		}
	} else {
		int mid = (lo + hi) / 2;

		if (arr[mid] < ele) {
			return search(arr, len, lo + 1, hi, ele);
		} else if (arr[mid] > ele) {
			return search(arr, len, lo, hi - 1, ele);
		} else {
			return mid + 1;
		}
	}
}

