// http://www.geeksforgeeks.org/sum-absolute-differences-pairs-given-array/

// Time:	O(n)
// Space:	O(n)	(above link gives O(1) space solution)

/*
4
1 2 3 4

5
1 8 9 15 16

9
1 2 3 4 5 7 9 11 14
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

// input
void input(int [MAX], int &);
// output
void showArr(int [MAX], int, const char *);
// calculation
void findCumDiff(int [MAX], int, int [MAX]);
void findAbsDiffSum(int [MAX], int, int[MAX]);

int main() {
	int arr[MAX], len;
	int cumDiff[MAX];

	input(arr, len);
	showArr(arr, len, "arr[]");

	findCumDiff(arr, len, cumDiff);
	showArr(cumDiff, len, "cumDiff[]");

	findAbsDiffSum(arr, len, cumDiff);

	return 0;
}

// input
void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of (sorted) array:\t";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

// output
void showArr(int a[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

// calculation
void findCumDiff(int arr[MAX], int len, int cumDiff[MAX]) {
	cumDiff[len - 1] = 0;
	for (int i = len - 2; i >= 0; i--) {
		cumDiff[i] = (arr[len - 1] - arr[i]) + cumDiff[i + 1];
	}
}

void findAbsDiffSum(int arr[MAX], int len, int cumDiff[MAX]) {
	int sum = (len <= 0) ? 0 : cumDiff[0];

	for (int i = len - 2; i >= 1; i--) {
		int remSum = cumDiff[0] - cumDiff[i];
		sum += remSum - ((arr[len - 1] - arr[i]) * i);
	}

	cout << "\nSum of absolute differences of all pairs is " << sum << endl << endl;
}

