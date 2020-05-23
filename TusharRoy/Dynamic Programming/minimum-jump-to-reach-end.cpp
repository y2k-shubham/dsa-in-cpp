#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 100
#define NIL -1
#define minVal(a, b) ((a < b) ? a : b)

void input(int [MAX], int &);
void calcJump_Y2K(int [MAX], int, int [MAX], int [MAX]);
void output_Y2K(int [MAX], int, int [MAX], int [MAX]);
void calcJump_TR(int [MAX], int, int [MAX], int [MAX]);
void output_TR(int [MAX], int, int [MAX], int [MAX]);
void showArrRec(int [MAX], int [MAX], int, bool);

int main() {
	int n;
	int arr[MAX];
	int jmpCount[MAX];
	int jmpInd[MAX];

	input(arr, n);

	calcJump_Y2K(arr, n, jmpCount, jmpInd);
	output_Y2K(arr, n, jmpCount, jmpInd);

	calcJump_TR(arr, n, jmpCount, jmpInd);
	output_TR(arr, n, jmpCount, jmpInd);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of elements:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void calcJump_Y2K(int arr[MAX], int n, int jmpCount[MAX], int jmpInd[MAX]) {
	jmpCount[n - 1] = 0;
	jmpInd[n - 1] = NIL;

	for (int i = n - 2; i >= 0; i--) {
		if (arr[i] == 0) {
			jmpCount[i] = INT_MAX;
			jmpInd[i] = NIL;
		} else {
			int minCount = INT_MAX;
			int minInd;
			int k = 1;

			for (int j = i + 1; j < n && k <= arr[i]; j++, k++) {
				if (jmpCount[j] < minCount) {
					minCount = jmpCount[j];
					minInd = j;
				}
			}

			jmpCount[i] = minCount + 1;
			jmpInd[i] = minInd;
		}
	}
}

void output_Y2K(int arr[MAX], int n, int jmpCount[MAX], int jmpInd[MAX]) {
	printf("\nY2K method\nThe shortest path to reach other end of array is:-\n");

	printf("Ind:\t");
	for (int i = 0; i != NIL; i = jmpInd[i]) {
		printf("[%d]\t", i);
	}

	printf("\nVal:\t");
	for (int i = 0; i != NIL; i = jmpInd[i]) {
		printf("%d\t", arr[i]);
	}

	printf("\n\nThe minimum no of jumps are:\t%d\n", jmpCount[0]);
}

void calcJump_TR(int arr[MAX], int n, int jmpCount[MAX], int jmpInd[MAX]) {
	jmpCount[0] = 0;
	jmpInd[0] = NIL;

	for (int i = 1; i < n; i++) {
		int minCount = INT_MAX;
		int minInd;

		for (int j = 0; j < i; j++) {
			if (arr[j] + j >= i) {
				if (jmpCount[j] < minCount) {
					minCount = jmpCount[j];
					minInd = j;
				}
			}
		}

		jmpCount[i] = minCount + 1;
		jmpInd[i] = minInd;
	}
}

void output_TR(int arr[MAX], int n, int jmpCount[MAX], int jmpInd[MAX]) {
	printf("\nTR method\nThe shortest path to reach other end of array is:-\n");

	printf("Ind:\t");
	showArrRec(arr, jmpInd, n - 1, true);

	printf("\nVal:\t");
	showArrRec(arr, jmpInd, n - 1, false);

	printf("\n\nThe minimum no of jumps are:\t%d\n", jmpCount[n - 1]);

}

void showArrRec(int arr[MAX], int jmpInd[MAX], int i, bool showInd) {
	if (i == 0) {
		if (showInd) {
			printf("[%d]\t", i);
		} else {
			printf("%d\t", arr[i]);
		}
	} else {
		showArrRec(arr, jmpInd, jmpInd[i], showInd);
		if (showInd) {
			printf("[%d]\t", i);
		} else {
			printf("%d\t", arr[i]);
		}
	}
}
