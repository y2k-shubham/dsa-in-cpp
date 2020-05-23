// http://www.geeksforgeeks.org/check-if-a-number-is-bleak/
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

int count1sInBinary(int);
bool isBleak(int);
void showBinary(int);

int main() {
	int n;

	printf("Enter a positive integer:\t");
	scanf("%d", &n);

	if (isBleak(n)) {
		printf("\nIt is bleak number\n");
	} else {
		printf("\nIt is not bleak number\n");
	}

	return 0;
}

int count1sInBinary(int n) {
	int ctr = 0;

	while (n > 0) {
		ctr += n & 1;
		n >>= 1;
	}

	return ctr;
}

bool isBleak(int n) {
	if (n == 0) {
		return false;
	}
	bool isBleak = true;
	int loLim = n - (int) ceil((log(n) / log(2)));

	for (int i = loLim; i < n; i++) {
		if (i + count1sInBinary(i) == n) {
			printf("\n%d = %d + ctr-1s(", n, i);
			showBinary(i);
			printf(")");
			isBleak = false;
		}
	}

	return isBleak;
}

void showBinary(int n) {
	int shift = ((int) ceil((log(n) / log(2)))) - 1;

	while (shift >= 0) {
		cout << ((n >> shift) & 1);
		shift--;
	}
}
