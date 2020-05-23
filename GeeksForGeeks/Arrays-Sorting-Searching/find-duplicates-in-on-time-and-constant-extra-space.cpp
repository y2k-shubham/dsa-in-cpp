/*
7
1 2 3 1 3 6 6

8
1 5 9 2 5 9 6 1
*/

#include <cstdio>
#include <iostream>
#include <cstdlib>

using namespace std;
#define MAX 100

int main() {
	int n;
	int arr[MAX];

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	cout << "\nRepeating elements are:-\n";
	for (int i = 0; i < n; i++) {
		if (arr[abs(arr[i])] > 0) {
			arr[abs(arr[i])] = -arr[abs(arr[i])];
		} else {
			printf("%d\t", abs(arr[i]));
		}
	}
	printf("\n");

	return 0;
}

