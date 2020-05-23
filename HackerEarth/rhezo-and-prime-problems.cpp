// https://www.hackerearth.com/practice/algorithms/dynamic-programming/introduction-to-dynamic-programming-1/practice-problems/algorithm/rhezo-and-prime-problems/

/*
4
8 1 3 7

7
8 1 3 7 4 2 9

8
9 8 1 3 7 4 2 9
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX1 100005
#define MAX2 5005

void input(int [MAX2], int&);
void genPrimes(bool [MAX1], vector <int>&);
void showVec(vector <int>);
void showArr(int [MAX2], int, const char *);
void findCumSum(int [MAX2], int, int [MAX2]);
void calcPoints(int [MAX2], int, vector <int>, int [MAX2]);

int main() {
	bool sieve[MAX1];
	vector <int> primes(9593);	// no of primes upto 100000 = 9592
	int points[MAX2], N;
	int cumSum[MAX2], dp[MAX2];

	genPrimes(sieve, primes);
//	showVec(primes);

	input(points, N);
	showArr(points, N, "points[]");

	findCumSum(points, N, cumSum);
	showArr(cumSum, N, "cumSum[]");

	calcPoints(cumSum, N, primes, dp);
	showArr(dp, N, "dp[]");

	return 0;
}

void input(int points[MAX2], int& N) {
	cout << "Enter no of games:\t";
	cin >> N;

	cout << "Enter the elements of array:-\n";
	for (int i = 1; i <= N; i++) {
		cin >> points[i];
	}
	points[0] = -1;
}

void genPrimes(bool sieve[MAX1], vector <int>& primes) {
	memset(sieve, true, MAX1 * sizeof(bool));
	int ind = 0;

	sieve[0] = sieve[1] = false;
	for (int i = 2; i < MAX1; i++) {
		if (sieve[i] == true) {
			for (int j = 2 * i; j < MAX1; j += i) {
				sieve[j] = false;
			}
			primes[ind++] = i;
		}
	}
}

void showVec(vector <int> primes) {
	printf("\nPrimes are:-\n");
	for (int i = 0; i < primes.size(); i++) {
		printf("%d ", primes[i]);
	}
	cout << endl;
}

void showArr(int points[MAX2], int N, const char * name) {
	printf("\n%s array is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i <= N; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i <= N; i++) {
		printf("%d\t", points[i]);
	}
	cout << endl;
}

void findCumSum(int points[MAX2], int N, int cumSum[MAX2]) {
	cumSum[0] = 0;
	for (int i = 1; i <= N; i++) {
		cumSum[i] = cumSum[i - 1] + points[i];
	}
}

void calcPoints(int cumSum[MAX2], int N, vector <int> primes, int dp[MAX2]) {
	dp[0] = dp[1] = 0;

	for (int i = 2; i <= N; i++) {
		dp[i] = dp[i - 1];

//		printf("\nat dp[%d]\n", i);
		for (int j = 0; primes[j] <= i; j++) {
			if (i - primes[j] > 0) {
//				printf("dp[%d] = max(%d, %d) = %d\n", i, dp[i], dp[i - primes[j] - 1] + cumSum[i] - cumSum[i - primes[j]], max(dp[i], dp[i - primes[j] - 1] + cumSum[i] - cumSum[i - primes[j]]));
				dp[i] = max(dp[i], dp[i - primes[j] - 1] + cumSum[i] - cumSum[i - primes[j]]);
			} else if (i - primes[j] == 0) {
//				printf("cumSum[%d] = %d\n", i, cumSum[i]);
//				printf("dp[%d] = max(%d, %d) = %d\n", i, dp[i], cumSum[i], max(dp[i], cumSum[i]));
				dp[i] = max(dp[i], cumSum[i]);
			}
			//			printf("after checking for primes[%d] = %d, dp[%d] = %d\n", j, primes[j], i, dp[i]);
		}
	}
}


