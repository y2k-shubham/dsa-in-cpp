// https://www.codechef.com/FEB16/problems/CHEFDETE
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100010

void input(bool [MAX], int &);
void output(bool [MAX], int);
void showArray(bool [MAX], int);

int main() {
	int N;
	bool isSmallCriminal[MAX];

	input(isSmallCriminal, N);

	if (N > 1) {
		output(isSmallCriminal, N);
	} else {
		printf("1\n");
	}

	return 0;
}

void input(bool isSmallCriminal[MAX], int &N) {
	int reportsTo;

	scanf("%d", &N);
	memset(isSmallCriminal, true, (N + 1) * sizeof(bool));
	//showArray(isSmallCriminal, N);

	scanf("%d", &reportsTo);
	for (int i = 2; i <= N; i++) {
		scanf("%d", &reportsTo);
		isSmallCriminal[reportsTo] = false;
	}
	//showArray(isSmallCriminal, N);
}

void output(bool isSmallCriminal[MAX], int N) {
	int i;

	for (i = 1; i <= N; i++) {
		if (isSmallCriminal[i]) {
			printf("%d", i);
			break;
		}
	}

	for (i++; i <= N; i++) {
		if (isSmallCriminal[i]) {
			printf(" %d", i);
		}
	}
	printf("\n");
}

void showArray(bool isSmallCriminal[MAX], int N) {
	printf("\nThe array is:-\n");
	for (int i = 1; i <= N; i++) {
		if (isSmallCriminal[i]) {
			printf("1 ");
		} else {
			printf("0 ");
		}
	}
	printf("\n");
}
