// http://www.geeksforgeeks.org/union-and-intersection-of-two-sorted-arrays-2/

/*
5
1 3 4 5 7
4
2 3 5 6

5
1 3 4 5 7
1
4

5
1 3 4 5 7
0

*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &, const char *);
void showUnion(int [MAX], int, int [MAX], int);
void showIntersection(int [MAX], int, int [MAX], int);

int main() {
	int arr1[MAX], arr2[MAX];
	int len1, len2;

	input(arr1, len1, "first");
	input(arr2, len2, "second");

	showUnion(arr1, len1, arr2, len2);
	showIntersection(arr1, len1, arr2, len2);

	return 0;
}

void input(int arr[MAX], int &len, const char * msg) {
	printf("\nEnter length of %s array:\t", msg);
	cin >> len;

	printf("Enter elements of %s array:\t", msg);
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showUnion(int arr1[MAX], int len1, int arr2[MAX], int len2) {
	int i, j;

	printf("\nUnion of arrays is:-\n");
	for (i = j = 0; i < len1 && j < len2; ) {
		if (arr1[i] < arr2[j]) {
			printf("%d ", arr1[i++]);
		} else if (arr1[i] > arr2[j]) {
			printf("%d ", arr2[j++]);
		} else {
			printf("%d ", arr1[i++]);
			j++;
		}
	}

	while (i < len1) {
		printf("%d ", arr1[i++]);
	}

	while (j < len2) {
		printf("%d ", arr2[j++]);
	}

	cout << endl;
}

void showIntersection(int arr1[MAX], int len1, int arr2[MAX], int len2) {
	int i, j;

	printf("\nIntersection of arrays is:-\n");
	for (i = j = 0; i < len1 && j < len2; ) {
		if (arr1[i] < arr2[j]) {
			i++;
		} else if (arr1[i] > arr2[j]) {
			j++;
		} else {
			printf("%d ", arr1[i++]);
			j++;
		}
	}
	cout << endl;
}

