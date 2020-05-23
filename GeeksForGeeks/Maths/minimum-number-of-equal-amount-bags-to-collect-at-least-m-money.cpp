// http://www.geeksforgeeks.org/minimum-number-of-equal-amount-bags-to-collect-at-least-m-money/

/*
12
2 5
27

9
4 5
45
*/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

void input(int&, int&, int&, int&);
void output(int, int, int, int);

int main() {
	int M, N;
	int X, Y;

	input(N, X, Y, M);
	output(N, X, Y, M);

	return 0;
}

void input(int& N, int& X, int& Y, int& M) {
	printf("Enter capacity of each bag:\t");
	scanf("%d", &N);

	printf("Enter denominations:\t");
	scanf("%d%d", &X, &Y);

	printf("Enter minimum total amount needed:\t");
	scanf("%d", &M);
}

void output(int N, int X, int Y, int M) {
	int maxCapUsed;

	maxCapUsed = 0;
//	cout << endl;
	for (int i = 1; i <= (N / X); i++) {
//		printf("for i = %d\t", i);
		int capUsed = i * X;
//		printf("capUsed = %d\t", capUsed);
		int capRem = N - capUsed;
//		printf("capRem = %d\t", capRem);
		capUsed = N - (capRem % Y);
//		printf("total capUsed = %d\n", capUsed);

		maxCapUsed = max(maxCapUsed, capUsed);
	}

	printf("\nUsed capacity of bags is %d\n", maxCapUsed);
	printf("No of bags is %d\n", ((int) ceil(((float) M) / maxCapUsed)));
}

