/*
2
2 3
2
2 4

7
8 1 3 7 4 2 9
6
27 16 5 11 1 34
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 1000005

void input(unsigned short [MAX], int &, int &);
void query(unsigned short [MAX], int);

int main() {
	int N, Q;
	unsigned short boxNo[MAX];

	input(boxNo, N, Q);
	query(boxNo, Q);

	return 0;
}

void input(unsigned short boxNo[MAX], int &N, int &Q) {
	int Ci;
	int ind = 1;

	cin >> N;
	for (int i = 1; i <= N; i++) {
		scanf("%d", &Ci);

		unsigned short iCasted = (unsigned short) i;
		for (int j = 1; j <= Ci; j++) {
			boxNo[ind++] = iCasted;
		}
	}

	cin >> Q;
}

void query(unsigned short boxNo[MAX], int Q) {
	int chocNo;

	for (int i = 1; i <= Q; i++) {
		scanf("%d", &chocNo);
		printf("%hu\n", boxNo[chocNo]);
	}
}

