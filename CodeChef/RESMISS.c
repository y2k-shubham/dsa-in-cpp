#include <stdio.h>

void input(int [], int [], int);
void findMinMax(int [], int [], int [], int [], int);
void output(int [], int [], int);

int main() {
	int T;

	scanf("%d", &T);

	int A[T];
	int B[T];
	int min[T];
	int max[T];

	input(A, B, T);
	findMinMax(A, B, min, max, T);
	output(min, max, T);

	return 0;
}

void input(int A[], int B[], int T) {
	int i;

	for (i = 0; i < T; i++) {
		scanf("%d%d", &A[i], &B[i]);
	}
}

void findMinMax(int A[], int B[], int min[], int max[], int T) {
	int i;

	for (i = 0; i < T; i++) {
		min[i] = (A[i] > B[i]) ? A[i] : B[i];
		max[i] = A[i] + B[i];
	}
}

void output(int min[], int max[], int T) {
	int i;

	for (i = 0; i < T; i++) {
		printf("%d %d\n", min[i], max[i]);
	}
}
