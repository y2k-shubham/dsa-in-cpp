// http://www.geeksforgeeks.org/program-nth-catalan-number/
// Direct formula for nth Catalan number: 2n-C-(n + 1)

#include <cstdio>
#include <iostream>

using namespace std;

void findCatalanNums(long long *, int);
void output(long long *, int);

int main() {
	int n;

	cout << "Enter n:\t";
	cin >> n;

	long long T[n + 1];

	findCatalanNums(T, n);
	output(T, n);

	return 0;
}

void findCatalanNums(long long * T, int n) {
	T[0] = T[1] = 1;

	for (int i = 2; i <= n; i++) {
		long long sum = 0;
		if (i & 1) {
			// if i is odd
			for (int j = 0; j <= (i / 2) - 1; j++) {
				sum += T[j] * T[i - j - 1];
			}
			T[i] = (sum * 2) + (T[i / 2] * T[i / 2]);
		} else {
			// if i is even
			for (int j = 0; j <= ((i - 1) / 2); j++) {
				sum += T[j] * T[i - j - 1];
			}
			T[i] = (sum * 2);
		}
	}
}

void output(long long * T, int n) {
	printf("Catalan Numbers upto from 0 to %d are:-\n", n);
	for (int i = 0; i <= n; i++) {
		printf("T[%d] = %lld\n", i, T[i]);
	}
	printf("\n");
}

