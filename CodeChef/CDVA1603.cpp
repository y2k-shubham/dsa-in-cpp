#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 1000000

int binSearch(float [MAX], int, float);

int main() {
	int T;
	int Q;
	int N;
	int i;
	int ind;
	float A[MAX];
	float K;

	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &N, &Q);

		// inpur numbers
		for (i = 0; i < N; i++) {
			scanf("%f", &A[i]);
		}

		// sort the array
		sort(A + 0, A + N);

		for (i = 0; i < Q; i++) {
			scanf("%f", &K);

			if (K < A[0]) {
				printf("%d\n", N);
			} else if (K > A[N - 1]) {
				printf("0\n");
			} else {
				ind = binSearch(A, N, K);
				if (ind >= 0) {
					printf("%d\n", (N - ind - 1));
				}
			}
		}
	}

	return 0;
}

int binSearch(float A[MAX], int N, float K) {
	int lo;
	int hi;
	int mid;

	lo = 0;
	hi = N - 1;

	while (lo != hi) {
		mid = (lo + hi) / 2;
		if (K < A[mid]) {
			hi = mid - 1;
		} else if (K > A[mid]) {
			lo = mid + 1;
		} else {
			return mid;
		}
	}

	/*
	if (hi >= 0 && hi < N && A[hi] < K) {
		return hi;
	} else {
		return lo;
	}
	*/

	if (lo >= 0 && lo < N && A[lo] == K) {
		return lo;
	} else if (lo >= 0 && lo < N && K < A[lo]) {
		return lo - 1;
	} else {
		return lo;
	}
}

