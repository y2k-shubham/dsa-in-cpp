// https://www.codechef.com/MAY17/problems/MXMEDIAN
// Median of Adjacent Maximum Numbers

/*
3
1
1 2
3
1 2 3 4 5 6
3
1 3 3 3 2 2

*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100005

void input(vector <int>&, int&);
void output(vector <int>, int);

int main() {
	int T;
	int N;
	vector <int> A(MAX);

	cin >> T;
	while (T-- > 0) {
		input(A, N);

		sort(A.begin(), A.begin() + 2 * N);

//		printf("output\n");
		cout << A[N + (N / 2)] << endl;
		output(A, N);
//		printf("------\n");
	}

	return 0;
}

void input(vector <int>& A, int& N) {
	cin >> N;
	for (int i = 0; i < (2 * N); i++) {
		scanf("%d", &A[i]);
	}
}

void output(vector <int> A, int N) {
	for (int i = 0; i < N - 1; i++) {
		printf("%d %d ", A[i], A[i + N]);
	}
	printf("%d %d\n", A[N - 1], A[2 * N - 1]);
}

