// http://www.geeksforgeeks.org/check-for-identical-bsts-without-building-the-trees/

/*
6

4
2 4 1 3
2 1 4 3

4
2 4 1 3
2 4 3 1

4
2 4 1 3
2 3 1 4

9
8 3 6 1 4 7 10 14 13
8 10 14 3 6 4 1 7 13

9
8 3 6 1 4 10 7 14 13
8 10 14 3 6 4 1 7 13

9
8 3 6 1 4 7 10 13 14
8 10 14 3 6 4 1 7 13
*/

#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int, const char *);
bool areSameBST(int, int [MAX], int, int [MAX], int, int, int);
void showArray(int [MAX], int, const char *);

int main() {
	int t;

	cout << "Enter test cases:\t";
	cin >> t;

	while (t--) {
		int a[MAX], b[MAX], len;

		cout << "Enter length of arrays:\t";
		cin >> len;

		input(a, len, "first");
		input(b, len, "second");

//		showArray(a, len, "First");
//		showArray(b, len, "Second");

		if (areSameBST(len, a, 0, b, 0, INT_MIN, INT_MAX)) {
			printf("\nBoth sequences will form same BST\n");
		} else {
			cout << "\nBoth sequences will form different BSTs\n";
		}

		cout << "\n--------------------------------------------\n\n";
	}

	return 0;
}

void input(int arr[MAX], int len, const char * msg) {
	printf("\nEnter elements of %s array:-\n", msg);
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	cout << endl;
}

bool areSameBST(int len, int a[MAX], int ia, int b[MAX], int ib, int minVal, int maxVal) {
//	if (ia < len) {
//		printf("\ncall a[ia] = %d\t", ia, a[ia]);
//	} else {
//		printf("\ncall ia = %d\t", len);
//	}
//	if (ib < len) {
//		printf("\ncall b[ib] = %d\t", ib, b[ib]);
//	} else {
//		printf("\ncall ib = %d\t", len);
//	}
//	if (minVal == INT_MIN) {
//		printf("minVal = -INF\t");
//	} else {
//		printf("minVal = %d\t", minVal);
//	}
//	if (maxVal == INT_MAX) {
//		printf("maxVal = INF\t");
//	} else {
//		printf("maxVal = %d\t", maxVal);
//	}

	int i, j;

	for (i = ia; i < len; i++) {
		if (a[i] > minVal && a[i] < maxVal) {
			break;
		}
	}

	for (j = ib; j < len; j++) {
		if (b[j] > minVal && b[j] < maxVal) {
			break;
		}
	}

	if ((i == len) == (j == len)) {
		if (i == len) {
//			printf("i = j = len\ttrue\n");
			return true;
		} else if (a[i] == b[j]) {
//			printf("a[%d] = b[%d] = %d\trecurse\n", i, j, a[i]);
			return areSameBST(len, a, i + 1, b, j + 1, minVal, a[i]) && areSameBST(len, a, i + 1, b, j + 1, a[i], maxVal);
		} else {
//			printf("a[%d] = %d\tb[%d] = %d\tfalse\b", i, a[i], j, b[j]);
			return false;
		}
	} else {
//		if (ia == len) {
//			printf("i = len\tj = %d\tfalse\n", j);
//		} else {
//			printf("i = %d\tj = len\tfalse\n", i);
//		}
		return false;
	}
}

