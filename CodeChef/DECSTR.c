#include <stdio.h>
#include <string.h>

#define size 105

void fillAlphabets(char []);
void generateStrings(char [], int);

int main() {
	int T;
	char A[size];

	scanf("%d", &T);

	fillAlphabets(A);
	generateStrings(A, T);

	return 0;
}

void fillAlphabets(char A[]) {
	int i;
	char c;

	c = 'a';
	A[size - 1] = '\0';

	for (i = (size - 2); i >= 0; i--) {
		A[i] = c;
		c++;

		if (c > 'z') {
			c = 'a';
		}
	}
}

void generateStrings(char A[], int T) {
	int i;
	int K;
	int adj;

	for (i = 1; i <= T; i++) {
		scanf("%d", &K);

        if (K <= 25) {
            adj = 0;
        } else if (K <= 50) {
            adj = 1;
        } else if (K <= 75) {
            adj = 2;
        } else {
            adj = 3;
        }

		if (K > 0) {
			printf("%s\n", &A[size - K - 2 - adj]);
		} else {
			printf("\n");
		}
	}
}
