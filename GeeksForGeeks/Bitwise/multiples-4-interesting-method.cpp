// http://www.geeksforgeeks.org/multiples-4-interesting-method/

#include <cstdio>
#include <iostream>

using namespace std;

int main() {
	int T;

	cout << "Enter no of test cases:\t";
	cin >> T;

	while (T-- > 0) {
		int n;

		cout << "Enter n:\t";
		cin >> n;

		if ((n & 3) > 0) {
			printf("%d is not a multiple of 4\n", n);
		} else {
			printf("%d is  a multiple of 4\n", n);
		}
	}

	return 0;
}
