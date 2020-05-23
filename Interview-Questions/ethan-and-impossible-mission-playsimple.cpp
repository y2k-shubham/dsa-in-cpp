/*
7
8 1 3 7 4 2 9
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 10005

void input(int&, int&, long long&, long long [MAX]);
void showArr(long long [MAX], int, const char *);
void findProdMod(int, long long, long long[MAX], long long[MAX], int, int, int);
void queries(int, int, long long, long long [MAX], long long [MAX]);

int main() {
	long long a[MAX], leftProdMod[MAX], rightProdMod[MAX];
	long long M;
	int N, Q;

	input(N, Q, M, a);
	showArr(a, N, "a[]");

	findProdMod(N, M, a, leftProdMod, 0, N - 1, 1);
	findProdMod(N, M, a, rightProdMod, N - 1, 0, -1);
	showArr(leftProdMod, N, "leftProdMod[]");
	showArr(rightProdMod, N, "rightProdMod[]");

	queries(N, Q, M, leftProdMod, rightProdMod);

	return 0;
}

void input(int& N, int& Q, long long& M, long long a[MAX]) {
	printf("Enter size of array:\t");
	cin >> N;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}

	printf("Enter modulo:\t");
	cin >> M;

	printf("Enter no of queries:\t");
	cin >> Q;
}

void showArr(long long arr[MAX], int len, const char * name) {
	printf("\n%s array is:-\n", name);

	printf("Ind:\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 0; i < len; i++) {
		printf("%lld\t", arr[i]);
	}
	cout << endl;
}

void findProdMod(int N, long long M, long long a[MAX], long long prodModArr[MAX], int startInd, int endInd, int delta) {
	long long prodModCrr = 1;
	for (int i = startInd; i != endInd + delta; i += delta) {
		prodModCrr *= a[i];
		prodModCrr %= M;
		prodModArr[i] = prodModCrr;
	}
}

void queries(int N, int Q, long long M, long long leftProdMod[MAX], long long rightProdMod[MAX]) {
	int startInd, endInd;

	printf("\nEnter queries:-\n");
	for (int i = 1; i <= Q; i++) {
		long long prodMod = (endInd - startInd + 1 == N) ? 0 : 1;
		cin >> startInd >> endInd;

		if (startInd > 0) {
			prodMod *= leftProdMod[startInd - 1];
			prodMod %= M;
		}
		if (endInd < N - 1) {
			prodMod *= rightProdMod[endInd + 1];
			prodMod %= M;
		}
		cout << prodMod << endl;
	}
}

