#include <stdio.h>
#include <string.h>

#define max_len 25001

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
	char M[max_len];
	char W[max_len];
	int lenM;
	int lenW;
	int i;
	int m;
	int w;

	for (i = 0; i < T; i++) {
		scanf("%s%s", M, W);
		lenM = strlen(M);
		lenW = strlen(W);

		if (lenM < lenW) {
			for (m = 0, w = 0; (m < lenM) && (w < lenW); w++) {
				if (W[w] == M[m]) {
					m++;
				}
			}

			result[i] = (m == lenM) ? 1 : 0;
		} else {
			for (w = 0, m = 0; (w < lenW) && (m < lenM); m++) {
				if (W[w] == M[m]) {
					w++;
				}
			}

			result[i] = (w == lenW) ? 1 : 0;
		}
	}
}

void output(int result[], int T) {
	char * answer[] = {"NO", "YES"};
	int i;

	for (i = 0; i < T; i++) {
		printf("%s\n", answer[result[i]]);
	}
}
