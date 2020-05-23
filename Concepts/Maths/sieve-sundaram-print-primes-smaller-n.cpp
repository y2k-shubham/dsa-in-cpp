// http://www.geeksforgeeks.org/sieve-sundaram-print-primes-smaller-n/
// Space: O(n / 2), where we have to display primes till n

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 10000

void findPrimes(bool [MAX], int);
void showPrimes(bool [MAX], int, int);

int main() {
	int n, nNew;
	bool sieve[MAX];

	printf("Enter limit n:\t");
	cin >> n;

	nNew = (n - 2) / 2;
	memset(sieve, false, (n + 1) * sizeof(bool));

	findPrimes(sieve, nNew);
	showPrimes(sieve, n, nNew);

	return 0;
}

void findPrimes(bool sieve[MAX], int nNew) {
	for (int i = 1; i <= nNew; i++) {
		for (int j = i; (i + j + 2 * i * j) <= nNew; j++) {
			sieve[i + j + 2 * i * j] = true;
		}
	}
}

void showPrimes(bool sieve[MAX], int n, int nNew) {
	printf("\nPrimes upto %d are:-\n", n);

	if (n >= 2) {
		printf("2 ");
		for (int i = 1; i <= nNew; i++) {
			if (sieve[i] == false) {
				printf("%d ", (2 * i + 1));
			}
		}
	}

	cout << endl;
}

