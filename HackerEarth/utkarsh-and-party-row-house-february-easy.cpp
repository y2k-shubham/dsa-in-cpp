#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100010

int main() {
	int N;
	int Q;
	int L;
	int R;
	int S;
	int K;
	int queryType;
	long long sum;
	int diff;
	int i;
	int j;
	int A[MAX];

	scanf("%d%d", &N, &Q);

	// input all A's
	for (i = 1; i <= N; i++) {
		scanf("%d", &A[i]);
	}

	// input and process queries
	for (i = 1; i <= Q; i++) {
		scanf("%d", &queryType);

		switch (queryType) {
			case 1:
				scanf("%d%d%d", &K, &L, &R);
				if (L <= K && K <= R) {
					// find sum from L to K - 1
					for (j = L, sum = 0, diff = K - L; j < K; j++, diff--) {
						sum += A[j] * diff;
						//printf("(A[%d] = %d) * %d = %d\n", j, A[j], diff, A[j] * diff);
					}
					// find sum from K + 1 to R
					for (j = K + 1, diff = 1; j <= R; j++, diff++) {
						sum += A[j] * diff;
						//printf("(A[%d] = %d) * %d = %d\n", j, A[j], diff, A[j] * diff);
					}
				} else if (K <= L) {
					// find sum from L to K - 1
					for (j = L, sum = 0, diff = L - K; j <= R; j++, diff++) {
						sum += A[j] * diff;
						//printf("(A[%d] = %d) * %d = %d\n", j, A[j], diff, A[j] * diff);
					}
				} else if (K >= R) {
					// find sum from L to K - 1
					for (j = L, sum = 0, diff = K - L; j <= R; j++, diff--) {
						sum += A[j] * diff;
						//printf("(A[%d] = %d) * %d = %d\n", j, A[j], diff, A[j] * diff);
					}
				}
				// output
				printf("%d\n", sum);
				break;

			case 2:
				scanf("%d%d", &K, &S);
				A[K] += S;
				break;
		}
	}

	return 0;
}
