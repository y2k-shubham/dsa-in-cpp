#include <stdio.h>
#include <string.h>

void fillPowers(int [], int, int, int);
int adjust(int, int, int, int []);
void findDistribution(int [], int , int [], int);
void output(int [], int);

int main() {
	int A;
	int N;
	int K;

	scanf("%d %d %d", &A, &N, &K);

	int chamber[K];
	int power[K];
	memset(chamber, 0, (K * sizeof(int)));

	fillPowers(power, N, K, A);
	A = adjust(A, N, K, power);
	//printf("After adjustment, A = %d\n", A);

	findDistribution(chamber, K, power, A);
	output(chamber, K);

	return 0;
}

void fillPowers(int power[], int N, int K, int A) {
	int index;
	int prod;

	prod = 1;
	index = 0;
	N++;

	while ((index < K) && (prod <= A)) {
		power[index++] = prod;
		prod *= N;
	}
}

int adjust(int A, int N, int K, int power[]) {
	int capacity;
	int index;

	capacity = 0;
	for (index = 0; index < K; index++) {
		capacity += power[index];
	}
	capacity *= N;

	if (capacity < A) {
        A %= (capacity + 1);
	}

	return A;
}

void findDistribution(int chamber[], int K, int power[], int A) {
	int index;
	int particles;

	for (index = (K - 1); power[index] > A; index--) {
	}

	while (A > 0) {
		particles = A / power[index];
		chamber[index] = particles;
		A %= power[index];
		index--;
	}
}

void output(int chamber[], int K) {
	int i;

	printf("%d", chamber[0]);
	for (i = 1; i < K; i++) {
		printf(" %d", chamber[i]);
	}
	printf("\n");
}
