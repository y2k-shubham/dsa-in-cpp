#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 1000
#define minVal(a, b) ((a < b) ? a : b)

int main() {
	int T;
	int N;
	int B[MAX];
	int i;
	int minCount;
	int sum;

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		sum = 0;
		minCount = INT_MAX;

		for (i = 0; i < N; i++) {
			scanf("%d", &B[i]);

			minCount = minVal(minCount, B[i]);
			sum += B[i] - 1;
		}

		printf("%d %d\n", minCount - 1, sum);
	}

	return 0;
}
