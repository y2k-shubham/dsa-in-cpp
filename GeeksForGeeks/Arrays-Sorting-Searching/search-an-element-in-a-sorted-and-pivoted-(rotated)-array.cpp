// http://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=146
// CrackingTheCodingInterview 5th Edition PDF page 373 (actual page no 364)
// Assumption: array has only unique elements, Cracking.. solution also covers repetitions

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100006

void input(int [MAX], int &, int &);
int findInd(int [MAX], int, int, int);

int main() {
	int T;
	int N;
	int A[MAX];
	int k;

	scanf("%d", &T);
	while (T-- > 0) {
		input(A, N, k);
		printf("%d\n", findInd(A, 0, N - 1, k));
	}

	return 0;
}

void input(int A[MAX], int &N, int &k) {
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &A[i]);
	}

	scanf("%d", &k);
}

int findInd(int A[MAX], int lo, int hi, int k) {
	int mid = (lo + hi) / 2;

	if (A[mid] == k) {
		return mid;
	} else if (lo > hi) {
		return -1;
	} else {
		if (A[lo] < A[mid]) {
			if (A[lo] <= k && k < A[mid]) {
				return findInd(A, lo, mid - 1, k);
			} else {
				return findInd(A, mid + 1, hi, k);
			}
		} else if (A[lo] > A[mid]) {
			if (A[mid] < k && k <= A[hi]) {
				return findInd(A, mid + 1, hi, k);
			} else {
				return findInd(A, lo, mid - 1, k);
			}
		}
	}
}
