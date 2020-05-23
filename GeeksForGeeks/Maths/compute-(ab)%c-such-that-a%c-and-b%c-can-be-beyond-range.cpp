// http://www.geeksforgeeks.org/compute-abc-such-that-ac-bc-can-be-beyond-range/
#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	int a, b, c;

	cout << "Enter (a, b, c):\t";
	cin >> a >> b >> c;

	printf("Result of (%d x %d) % %d is %d\n", a, b, c, findProdMod(a, b, c));

	return 0;
}

int findProdMod(int a, int b, int c) {
	if (b == c) {
		return 0;
	}

	int res = findProdMod(a, b / 2, c);

	if (b & 1) {
		return
	}
}
