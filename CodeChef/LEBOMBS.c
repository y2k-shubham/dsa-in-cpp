#include <stdio.h>
#include <string.h>

#define size 1000

void inputAndProcess(int [], int);
void output(int [], int);

int main() {
	int T;

	scanf("%d", &T);
	int result[T];

	inputAndProcess(result, T);
	output(result, T);

	return 0;
}

void inputAndProcess(int result[], int T) {
	char S[size + 1];
	int i;
	int j;
	int N;
	int diff;
	int prevIndex;
	int countDestroyed;

	for (i = 0; i < T; i++) {
		scanf("%d%s", &N, S);

        // initialize j, countDestroyed and prevIndex
		if (S[0] == '1') {
			countDestroyed = 2;
			prevIndex = 0;
			j = 1;
		} else {
			countDestroyed = 0;
			prevIndex = -999;
			j = 0;
		}

        // read through the string S[] and count the no of destroyed buildings
		for (; j < N; j++) {
			if (S[j] == '1') {
				if ((diff = (j - prevIndex)) <= 2) {
					countDestroyed += diff;
				} else {
					countDestroyed += 3;
				}
				prevIndex = j;
			}
		}

        // adjust the count if the last building had bomb
		if (prevIndex == (N - 1)) {
			countDestroyed--;
		}

        // store the result of no of buildings NOT destroyed
		result[i] = N - countDestroyed;
	}
}

void output(int result[], int T) {
	int i;

	for (i = 0; i < T; i++) {
		printf("%d\n", result[i]);
	}
}
