// http://www.geeksforgeeks.org/directi-programming-questions/

/*
3
2 1 3

3
1 2 3

5
2 4 3 5 1
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
int findCount(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len);
	printf("\nNo of possible probabilistic preorder traversals = %d\n", findCount(arr, 0, len - 1));

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

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

int findCount(int arr[MAX], int lo, int hi) {
	if (lo >= hi) {
		return 1;
	} else {
		int i;
		int root;
		bool grtFirst;

		root = arr[lo];
		if (arr[lo + 1] > root) {
			grtFirst = true;
		} else {
			grtFirst = false;
		}

		for (i = lo + 1; i <= hi; i++) {
			if (grtFirst && arr[i] < root) {
				break;
			} else if (!grtFirst && arr[i] > root) {
				break;
			}
		}

		if (i <= hi) {
			return 2 * findCount(arr, lo + 1, i - 1) * findCount(arr, i, hi);
		} else {
			return findCount(arr, lo + 1, hi);
		}
	}
}

