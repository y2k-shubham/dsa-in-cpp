#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define size_primeFinder 31607
#define size_primes 3150
#define size_sieve 100050
//#define pc(x) putchar_unlocked(x);

void findPrimes(bool []);
void showStartingPrimes_1(bool []);
void showStartingPrimes_2(int [], int);
void fillSieve(int [], int, int);
void showSieve(int [], int, int);
void outputSieve(int [], int, int);
int copyPrimes(bool [], int []);
void reduceSieve(int [], int, int [], int, int);
void cancelFactors(int [], int, int, int, int);
int findFirstFactorIndex(int [], int, int, int);
void adjustLimit(int *);
//inline void writeInt(int);

int main() {
	bool primeFinder[size_primeFinder + 1];
	int primes[size_primes];
	int primeCount;
	int t;
	int m;
	int n;

	memset(primeFinder, true, (size_primeFinder + 1));
	findPrimes(primeFinder);
	//showStartingPrimes_1(primeFinder);
	primeCount = copyPrimes(primeFinder, primes);
	//free(&primeFinder[0]);

	int sieve[size_sieve];
	//showStartingPrimes_2(primes, primeCount);
	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &m, &n);

		adjustLimit(&m);
		if (n < 2) {
			continue;
		}

		fillSieve(sieve, m, n);
		//showSieve(sieve, m, n);
		reduceSieve(primes, primeCount, sieve, m, n);
		outputSieve(sieve, m, n);
	}

	return 0;
}

void adjustLimit(int * n) {
	if ((*n) < 2) {
		(*n) = 2;
	}
}

void reduceSieve(int primes[], int primeCount, int sieve[], int m, int n) {
	int i;
	int firstFactorIndex;
	int currentPrime;

	//printf("\nCanceling Factors:-\n");
	currentPrime = 2;
	for (i = 0; ((currentPrime * currentPrime) <= n) && (i < primeCount); currentPrime = primes[++i]) {
		//printf("\n===\nChecking factors of %d\n", primes[i]);
		//printf("%d\t", currentPrime);
		//printf("exe1\t");
		firstFactorIndex = findFirstFactorIndex(sieve, m, n, currentPrime);
		//printf("The first factor of %d is %d at index %d\n", primes[i], sieve[firstFactorIndex], firstFactorIndex);
		//printf("exe2\t");
		if (firstFactorIndex >= 0) {
			//printf("Canceling Factors of %d\n\n", primes[i]);
			cancelFactors(sieve, m, n, currentPrime, firstFactorIndex);
			//printf("exe3\t");
			//printf("%d\t", primes[i]);
		}
		//printf("===\n");
	}
	//printf("\n");
}

void cancelFactors(int sieve[], int m, int n, int divisor, int startingIndex) {
	int i;
	int len;

	if (sieve[startingIndex] == divisor) {
		i = startingIndex + divisor;
	} else {
		i = startingIndex;
	}

	len = (n - m + 1);
	for (; i < len; i += divisor) {
		//printf("Canceled %d at index %d\n", sieve[i], i);
		sieve[i] = -666;
	}
}

int findFirstFactorIndex(int sieve[], int m, int n, int divisor) {
	int i;
	int len;
	int index;

	len = (n - m + 1);
	//printf("\nm = %d\nn = %d\nlen = %d\n\n", m, n, len);
	/*
	for (i = 0; i < len; i++) {
		if ((sieve[i] % divisor) == 0) {
			//printf("%d is divisible by %d\n", sieve[i], divisor);
			return i;
		} else {
			//printf("%d is not divisible by %d\n", sieve[i], divisor);
		}
	}
	*/
	index = divisor - (m % divisor);

	if (index < len) {
		return index;
	} else {
		return -999;
	}

	return -999;
}

int copyPrimes(bool primeFinder[], int primes[]) {
	int i;
	int j;

	//printf("\nCopying Primes:-\n");
	primes[0] = 2;
	for (i = 3, j = 1; i <= size_primeFinder; i += 2) {
		if (primeFinder[i]) {
			//printf("%d\t", i);
			primes[j++] = i;
		}
	}
	//printf("\n");

	return j;
}

void findPrimes(bool primeFinder[]) {
	int i;
	int skipIndex;

	primeFinder[0] = false;
	primeFinder[1] = false;

	for (i = 3; i <= size_primeFinder; i += 2) {
		while (!primeFinder[i]) {
			i += 2;
		}

		//printf("\n===\nPrime Found:\t%d\n", i);
		for (skipIndex = (i << 1); skipIndex <= size_primeFinder; skipIndex += i) {
			//printf("Factor Canceled:\t%d\n", skipIndex);
			primeFinder[skipIndex] = false;
		}
		//printf("===\n");
	}
}

void showStartingPrimes_1(bool primeFinder[]) {
	int i;
	//int ctr;

	printf("\nThe prime are:-\n2\t");
	for (i = 3; i <= size_primeFinder; i += 2) {
		if (primeFinder[i]) {
			//++ctr;
			printf("%d\t", i);
		}
	}
	printf("\n");
	//printf("no of primes = %d\n", ctr);
}

void showStartingPrimes_2(int primes[], int primeCount) {
	int i;
	//int ctr;

	printf("\nThe primes are:-\n");
	for (i = 0; i < primeCount; i++) {
		printf("%d\t", primes[i]);
	}
	printf("\n");
	//printf("no of primes = %d\n", ctr);
}

void fillSieve(int sieve[], int m, int n) {
	int i;
	int j;


	for (i = 0, j = m; j <= n; i++, j++) {
		sieve[i] = j;
	}
}

void outputSieve(int sieve[], int m, int n) {
	int i;
	int len;
	int element;

	len = (n - m + 1);

	//printf("\nThe sieve is:-\n");
	if (m == 2) {
		printf("2\n");
	}

	for (i = 1; i < len; i++) {
		element = sieve[i];
		if (element > 0) {
			printf("%d\n", element);
			//writeInt(element);
		}
	}
	//printf("\n");
}

void showSieve(int sieve[], int m, int n) {
	int i;
	int len;
	int element;

	len = (n - m + 1);

	printf("\nThe sieve is:-\n");
	if (m == 2) {
		printf("2\n");
	}

	for (i = 0; i < len; i++) {
		element = sieve[i];
		if (element > 0) {
			printf("%d\t", element);
		}
	}
	printf("\n");
}
