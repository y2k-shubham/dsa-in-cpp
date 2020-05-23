// Karumanchi, DP, Problem 1, page 387

#include <cstdio>
#include <iostream>

using namespace std;

int myWay(int);
int bookWay(int);

int main() {
	int n;

	cout << "Enter n:\t";
	cin >> n;

	cout << "\nT(n) 1:\t" << myWay(n) << endl;
	cout << "T(n) 2:\t" << bookWay(n) << endl;

	return 0;
}

int myWay(int n) {
	if (n <= 1) {
		return 2;
	} else if (n == 2) {
		return 2 * myWay(n - 1) * myWay(n - 2);
	} else {
		return myWay(n - 1) + 2 * myWay(n - 1) * myWay(n - 2);
	}
}

int bookWay(int n) {
	if (n <= 1) {
		return 2;
	} else {
		int sum = 0;

		for (int i = 1; i < n; i++) {
			sum += 2 * bookWay(i) * bookWay(i - 1);
		}

		return sum;
	}
}

