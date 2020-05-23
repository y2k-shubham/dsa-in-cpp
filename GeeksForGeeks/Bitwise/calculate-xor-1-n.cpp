// http://www.geeksforgeeks.org/calculate-xor-1-n/
// Below solution is brute force O(n)
// Improved O(1) solution is given in above link. It says

/*
1- Find the remainder of n by moduling it with 4.
2- If rem = 0, then xor will be same as n.
3- If rem = 1, then xor will be 1.
4- If rem = 2, then xor will be n+1.
5- If rem = 3 ,then xor will be 0.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
	int lim = 50;
	int _xor = 0;

	for (int i = 1; i <= lim; i++) {
		_xor ^= i;
		int init = (int) ceil(log2(lim));

		printf("%d\t%d\t", i, _xor);
		for (int j = init; j >= 0; j--) {
			if ((_xor & (1 << j)) == 0) {
				printf("0");
			} else {
				printf("1");
			}
		}
		cout << endl;
	}

	return 0;
}

