#include <stdio.h>

void inputAndProcess(long long int [], int);
long long int compute(long long int, long long int);
void output(long long int [], int);

int main() {
	int T;

	scanf("%d", &T);
	long long int result[T];

	inputAndProcess(result, T);
	output(result, T);

	return 0;
}

void inputAndProcess(long long int result[], int T) {
    int i;
    long long int n;
    long long int k;

    for (i = 0; i < T; i++) {
        scanf("%d%d", &n, &k);
        result[i] = compute(n, k);
    }
}

long long int compute(long long int n, long long int r) {
	long long int result;
	long long int i;

	result = 1;
	if (r > (n / 2)) {
		r = n - r;
	}

	for (i = 0; i < r; i++) {
		result *= n;
		result /= i;
		n--;
	}

	return result;
}

void output(long long int result[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%lld\n", result[i]);
    }
}
