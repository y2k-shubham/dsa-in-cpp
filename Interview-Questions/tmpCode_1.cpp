#include <bits/stdc++.h>
using namespace std;

int noOfFactors(int, int, int);
int hcf(int, int);
int lcm(int, int);

int main() {
	int big, small;
	int lo, hi;

	cin >> lo >> hi;
	cin >> big >> small;

	int fC1 = noOfFactors(big, lo, hi);
	int fC2 = noOfFactors(small, lo, hi);

	int fC12 = noOfFactors(lcm(big, small), lo, hi);

	printf("\ndiv by %d = %d\n", big, fC1);
	printf("div by %d = %d\n", small, fC2);
	printf("div by both %d and %d = %d\n", big, small, fC12);
	printf("div only by %d = %d\n", big, (fC1 - fC12));
	printf("div only by %d = %d\n", small, (fC2 - fC12));

	return 0;
}

int noOfFactors(int d, int lo, int hi) {
	int a = lo + (d - (lo % d));
	int l = hi - (hi % d);

	int n = ((l - a) / d) + 1;
	return n;
}

int hcf(int big, int small) {
	if ((big % small) == 0) {
		return small;
	} else {
		return hcf(small, big % small);
	}
}

int lcm(int big, int small) {
	return ((big * small) / hcf(big, small));
}

