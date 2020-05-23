// http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/
// https://www.youtube.com/watch?v=CE2b_-XfVDk
// O(n^2) solution using dynamic programming

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100
#define maxVal(a, b) ((a > b) ? a : b)

void input(int [MAX], int);
void output(int [MAX], int);
void showSubSequence(int [MAX], int [MAX], int);

int main() {
	int arr[MAX];
	int n;

	cout << "Enter n:\t";
	cin >> n;

	input(arr, n);
	output(arr, n);

	return 0;
}

void input(int arr[MAX], int n) {
	printf("Enter array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void output(int arr[MAX], int n) {
	int lisLen[MAX];
	int lisPrevInd[MAX];
	int maxLisLen;
	int maxLisInd;

	//memset(lisLen, 1, sizeof(lisLen));
	for (int i = 0; i < n; i++) {
		lisLen[i] = 1;
	}
	maxLisLen = 0;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				if (lisLen[j] + 1 > lisLen[i]) {
					lisLen[i] = lisLen[j] + 1;
					lisPrevInd[i] = j;
				}

				if (lisLen[i] > maxLisLen) {
					maxLisLen = lisLen[i];
					maxLisInd = i;
				}
			}
		}
	}

	printf("\nThe longest increasing subsequence is:-\n");
	showSubSequence(arr, lisPrevInd, maxLisInd);
	printf("\nThe length of longest increasing subsequence is %d\n", maxLisLen);
}

void showSubSequence(int arr[MAX], int lisPrevInd[MAX], int lisInd) {
	if (lisPrevInd[lisInd] == 0) {
		printf("%d\t", arr[lisInd]);
	} else {
		showSubSequence(arr, lisPrevInd, lisPrevInd[lisInd]);
		printf("%d\t", arr[lisInd]);
	}
}

