// http://www.geeksforgeeks.org/bitwise-and-or-of-a-range/
// http://code.geeksforgeeks.org/ubylTU

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
void findBitAnd(long long int, long long int);

int main() {
	long long int x, y;

	cout << "Enter x & y:\t";
	cin >> x >> y;

	findBitAnd(x, y);

	return 0;
}

void findBitAnd(long long int x, long long int y) {
	long long int _and = 0;
	long long int diff = y - x;
	int bitLen = (int) ceil(log2(y));

	for (int i = 0; i <= bitLen; i++) {
		if (diff <= ((long long int) pow(2, i))) {
			// if difference of x & y is less than or equal to 2^i, then i'th bit of
			// result will be set (1) only if ith bit of both x and y are set
			if (((x & (1 << i)) > 0) && ((y & (1 << i)) > 0)) {
				_and |= (1 << i);
			}
		} else {
			// if difference of x & y exceeds 2^i, (i counted from right to left)
			// then i'th bit of result will definitely be zero
		}
	}

	printf("AND of numbers from %lld to %lld is:\t%lld\t", x, y, _and);
	for (int j = bitLen; j >= 0; j--) {
		if ((_and & (1 << j)) == 0) {
			printf("0");
		} else {
			printf("1");
		}
	}
	cout << endl;
}

