#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 500
//#define abs(a) ((a >= 0) ? a : (-1 * a))

int abs(int);

int main() {
	int T;
	int N;
	int arr[MAX];
	int sum;
	int lim;
	int i;

	scanf("%d", &T);
	while (T--) {
		// input
		scanf("%d", &N);
		N *= 2;
		for (i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}

		// sort
		sort(arr, arr + (N - 1));

		// calculate
		lim = (N / 2) - 1;
		sum = 0;
		for (i = 0; i <= lim; i++) {
			//printf("(arr[%d] = %d) - (arr[%d] = %d) = %d\n", i, arr[i], N - i - 1, arr[N - i - 1], abs(arr[i] - arr[N - i - 1]));
			sum += abs(arr[i] - arr[N - i - 1]);
		}

		// output
		cout << sum;
	}

	return 0;
}

int abs(int n) {
	if (n >= 0) {
		return n;
	} else {
		return -1 * n;
	}
}
