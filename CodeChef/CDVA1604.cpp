#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

int main() {
	//queue <int> line;
	//int n;
	int i;
	int N;
	int T;

	/*
	printf("size\tsurvivor\n");
	for (n = 2; n <= 500; n++) {
		// fill the queue
		for (i = 1; i <= n; i++) {
			line.push(i);
		}

		// simulate line killing
		while (line.size() > 1) {
			line.pop();
			line.push(line.front());
			line.pop();
		}

		printf("%d\t%d\n", n, line.front());
		line.pop();
	}
	*/

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d", &N);
		if (N == 1) {
			// don't know
			printf("1\n");
		} else {
			for (i = 2; i <= N; i = i << 1) {
			}
			i = i >> 1;

			if ((N - i) == 0) {
				printf("%d\n", N);
			} else {
				printf("%d\n", (N - i) * 2);
			}
		}
	}

	return 0;
}
