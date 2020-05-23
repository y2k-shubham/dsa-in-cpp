// Karumanchi, Searching, Problem 73, page 300

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

int way_1(int);
int way_2(int);

int main() {
	int n;

	cout << "Enter n:\t";
	cin >> n;

	printf("\nNo of zeros in %d!:\t%d\n", n, way_1(n));
	printf("No of zeros in %d!:\t%d\n", n, way_2(n));

	return 0;
}

int way_1(int n) {
	int ctr = 0;

	while (n > 0) {
		ctr += n / 5;
		n /= 5;
	}

	return ctr;
}

int way_2(int n) {
	int ctr = 0;
	int div = 5;

	while (n / div > 0) {
		ctr += n / div;
		div *= 5;
	}

	return ctr;
}

