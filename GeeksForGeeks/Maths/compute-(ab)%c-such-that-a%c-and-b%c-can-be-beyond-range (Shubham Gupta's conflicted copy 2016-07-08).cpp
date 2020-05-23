// http://www.geeksforgeeks.org/compute-abc-such-that-ac-bc-can-be-beyond-range/
// Divide and Conquer, RunTime: O(lgN)

/*
1000000000007
10000000000005
1000000000000003
*/

#include <cstdio>
#include <iostream>

using namespace std;

long long int findProdMod(long long int, long long int, long long int);

int main() {
	long long int a, b, c;

	cout << "Enter (a, b, c):\t";
	cin >> a >> b >> c;

	printf("Result of (%lld x %lld) mod %lld is %lld\n", a, b, c, findProdMod(a, b, c));

	return 0;
}

long long int findProdMod(long long int a, long long int b, long long int c) {
	if (b == 0) {
		return 0;
	}

	long long int res = findProdMod(a, b / 2, c);

	if (b & 1) {
		return (((a % c) + 2 * (res % c)) % c);
	} else {
		return ((2 * (res % c)) % c);
	}
}

