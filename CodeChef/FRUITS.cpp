#include <cstdio>
#include <iostream>
#include <cstdlib>

bool isEven(int);
bool isOdd(int);

int main() {
	int T;
	int N;
	int M;
	int K;
	int diff;

	scanf("%d", &T);
	while (T--) {
		scanf("%d%d%d", &N, &M, &K);
		diff = abs(N - M);

		if (diff >= K) {
			printf("%d\n", (diff - K));
		}/*else if ((isEven(diff) && isEven(K)) || (isOdd(diff) && isOdd(K))) {
			printf("0\n");
		} else {
			printf("1\n");
		}*/
		else {
			printf("0\n");
		}
	}
}

bool isEven(int n) {
	if (n & 1) {
		return false;
	} else {
		return true;
	}
}

bool isOdd(int n) {
	if (n & 1) {
		return true;
	} else {
		return false;
	}
}
