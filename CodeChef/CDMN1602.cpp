#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100001

/*

1
7
6 0 1 0 1 3 9
1 4 0 0 2 5 7

*/

int main() {
	int T;
	int N;
	int M;
	int i;
	int num;
	int ctr;
	int zeroA;
	int zeroB;
	int freq[MAX];
	int arr[MAX];

	scanf("%d", &T);
	while (T--) {
		scanf("%d", &N);
		memset(freq, 0, sizeof(freq));
		ctr = 0;
		zeroA = 0;
		zeroB = 0;

		for (i = 0; i < N; i++) {
			scanf("%d", &num);
			freq[num]++;
		}
		zeroA = freq[0];

		for (i = 0; i < N; i++) {
			scanf("%d", &num);
			arr[i] = num;
			if (num == 0) {
				zeroB++;
			}
		}

		scanf("%d", &M);

		if (M == 0) {
			ctr = zeroA * (N - zeroB) + zeroB * (N - zeroA) + zeroA * zeroB;
		} else {
			for (i = 0; i < N; i++) {
				if ((arr[i] > 0) && ((M % arr[i]) == 0)) {
					ctr += freq[M / arr[i]];
				}
			}
		}

		printf("%d\n", ctr);
	}

	return 0;
}
