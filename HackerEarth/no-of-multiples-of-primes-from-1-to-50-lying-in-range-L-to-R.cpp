#include <bits/stdc++.h>
using namespace std;

void createPrimesVec(vector <long long int> &, long long int);
long long int calc(long long int, long long int, vector <long long int>);
long long int findCount(long long int, long long int, vector <long long int>, long long int);
long long int findLessMul(long long int, long long int);
long long int findGreatMul(long long int, long long int);

int main() {
	long long int T;

	cin >> T;
	while (T-- > 0) {
		long long int L, R, N;
		vector <long long int> primes;

		cin >> L >> R >> N;

		createPrimesVec(primes, N);
		long long int ans = calc(L, R, primes);

		cout << ans << endl;
	}
}

void createPrimesVec(vector <long long int> &primes, long long int N) {
	long long int p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

	for (long long int i = 0; i < 15; i++) {
		if (p[i] <= N) {
			primes.push_back(p[i]);
		} else {
			break;
		}
	}
}

void showPrimesVec(vector <long long int> primes) {
	printf("\nPrimes vector is:-\n");
	for (vector <long long int>::iterator i = primes.begin(); i != primes.end(); i++) {
		printf("%d ", (*i));
	}
	cout << endl << endl;
}

long long int calc(long long int L, long long int R, vector <long long int> primes) {
	long long int count = 0;

	for (long long int i = 0; i < primes.size(); i++) {
		count += findCount(L, R, primes, i);
	}

	return count;
}

long long int findCount(long long int L, long long int R, vector <long long int> primes, long long int ind) {
	long long int sum = 0;
	long long int p = primes[ind];
	long long int minMul, maxMul;

	minMul = findGreatMul(L, p);
	maxMul = findLessMul(R, p);
	if (minMul >= L && maxMul <= R) {
		sum += (maxMul - minMul) / p + 1;
//		printf("\nNo of direct multiples of %d = %d\n", p, sum);
	}

	long long int exp = ((long long int) pow(2, ind)) - 1;
	for (long long int i = 1; i <= exp; i++) {
		long long int subMul = p;
		long long int lim = (long long int) ceil(log2(i));
		long long int onesCount = 0;
//		printf("No of muls of\t");

		for (long long int j = 0; j < min(lim + 1, ind); j++) {
			if (((1 << j) & i) > 0) {
				onesCount++;
				subMul *= primes[j];
//				printf("%d * ", primes[j]);
			}
		}
//		printf(" %d = %d,\t", p, subMul);

		minMul = findGreatMul(L, subMul);
		maxMul = findLessMul(R, subMul);
		if (minMul >= L && maxMul <= R) {
			if ((onesCount & 1) > 0) {
//				printf("%d subtracted\n", ((maxMul - minMul) / subMul + 1));
				sum -= (maxMul - minMul) / subMul + 1;
			} else {
//				printf("%d added\n", ((maxMul - minMul) / subMul + 1));
				sum += (maxMul - minMul) / subMul + 1;
			}
		}
	}
//	printf("final count = %d\n", sum);

	return sum;
}

long long int findLessMul(long long int N, long long int f) {
	long long int q = N / f;
	return (q * f);
}

long long int findGreatMul(long long int N, long long int f) {
	long long int q = N / f;
	if ((q * f) >= N) {
		return (q * f);
	} else {
		return ((q + 1) * f);
	}
}

