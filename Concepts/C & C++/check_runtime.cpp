#include <bits/stdc++.h>
using namespace std;

#define LIM 3200000

int main() {
	int a, b, c;

	a = 1;
	b = LIM;
	for (int i = 1; i <= LIM; i++) {
		a++;
		b--;
		c += (a > b) ? ((b > 0) ? (a / b) : 0) : ((a > 0) ? (b / a) : 0);
	}

	return 0;
}

