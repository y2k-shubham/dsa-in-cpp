// http://www.geeksforgeeks.org/segmented-sieve/
// Generation of all primes less than N using sieve and O(sqrt(N)) space

#include <cstdio>
#include <iostream>
#include <set>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100000

void findFirstSegPrimes(int, float, set <int> &);
void findRemSegPrimes(int, float, set <int>, set <int> &);
void showPrimes(set <int>, const char *, int);

int main() {
	int N;
	set <int> firstSegPrimes, allSegPrimes;

	printf("Enter N:\t");
	cin >> N;
	float sqrtNF = sqrtf(N);

	findFirstSegPrimes(N, sqrtNF, firstSegPrimes);
	showPrimes(firstSegPrimes, "first", N);

	allSegPrimes.insert(firstSegPrimes.begin(), firstSegPrimes.end());
	findRemSegPrimes(N, sqrtNF, firstSegPrimes, allSegPrimes);
	showPrimes(allSegPrimes, "all", N);

	return 0;
}

void findFirstSegPrimes(int N, float sqrtNF, set <int> &firstSegPrimes) {
	bool sieve[MAX];
	int sqrtNI = (int) ceil(sqrtNF);

	memset(sieve, true, (sqrtNI + 1) * sizeof(bool));
	sieve[0] = false;
	sieve[1] = false;

	for (int i = 2; i <= sqrtNI; i++) {
		if (sieve[i] == true) {
			// it's a prime
			firstSegPrimes.insert(i);

			for (int j = 2 * i; j <= sqrtNI; j += i) {
				sieve[j] = false;
			}
		}
	}
}

void findRemSegPrimes(int N, float sqrtNF, set <int> firstSegPrimes, set <int> &allSegPrimes) {
	bool sieve[MAX];
	int sqrtNI = (int) ceil(sqrtNF);

	int rLo = sqrtNI + 1;
	int rHi = min((rLo + sqrtNI - 1), N);

	for (; rLo <= N; rLo = rHi + 1, rHi += sqrtNI) {
		rHi = min(rHi, N);
		memset(sieve, true, (sqrtNI + 1) * sizeof(bool));

//		printf("\n(rLo, rHi) = (%d, %d)\n", rLo, rHi);
		for (set <int>::iterator i = firstSegPrimes.begin(); i != firstSegPrimes.end(); i++) {
			int p = *i;
//			printf("(%d)\n", p);

			int q = rLo / p;
			int f = p * q;
			if (f < rLo) {
				f += p;
			}

			while (f <= rHi) {
//				printf("%d marked composite\n", f);
				sieve[f - rLo] = false;
				f += p;
			}
		}

		for (int i = rLo; i <= rHi; i++) {
			if (sieve[i - rLo] == true) {
				//				printf("%d inserted as prime\n", i);
				allSegPrimes.insert(i);
			}
		}
	}
}

void showPrimes(set <int> primes, const char * segName, int N) {
	int ind = 1;

	printf("\nPrimes of %s segment(s) upto %d are:-\n", segName, N);
	for (set <int>::iterator i = primes.begin(); i != primes.end(); i++) {
		printf("%d.\t%d\n", ind++, (*i));
	}
	cout << endl;
}

