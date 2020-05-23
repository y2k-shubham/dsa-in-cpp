// http://www.geeksforgeeks.org/next-higher-number-with-same-number-of-set-bits/

#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;
#define MAX_BIT_POS 31

pair <int, int> findPos(int);
bool isSet(int, int);
void showBinary(int);

int main() {
	int n;

	printf("Enter an integer:\t");
	scanf("%d", &n);
	showBinary(n);

//	showBinary(INT_MAX);

	// find position of first 1 preceded by 0 in binary representation
	pair <int, int> tmpPair = findPos(n);
	int pos = tmpPair.first;
	int ctr = tmpPair.second;

	if (pos < MAX_BIT_POS - 1) {
		// set 1 in position of 0
		n = n | (1 << (pos + 1));

		// clear lower bits of number and create ctr no of 1s in lowest order positions
		n = n & (~((1 << (pos + 1)) - 1));
		n = n | ((1 << ctr) - 1);

		printf("\nNext higher number with same no of 1s in binary representation is %d\n", n);
		showBinary(n);
	} else {
		printf("\nNo bigger number with same no of 1s in binary is possible\n");
	}

	return 0;
}

pair <int, int> findPos(int n) {
	int pos = 0;
	int ctr = 0;

	while (pos < MAX_BIT_POS - 1) {
		if (isSet(n, pos) == true) {
			if (isSet(n, pos + 1) == false) {
				break;
			} else {
				ctr++;
			}
		}
		pos++;
	}

	return make_pair(pos, ctr);
}

bool isSet(int n, int pos) {
	if ((n & (1 << pos)) > 0) {
		return true;
	} else {
		return false;
	}
}

void showBinary(int n) {
	printf("Binary representation of %d is:-\n", n);
	for (int i = MAX_BIT_POS; i >= 0; i--) {
		if (isSet(n, i) == true) {
			printf("1");
		} else {
			printf("0");
		}
	}
	cout << endl;
}

