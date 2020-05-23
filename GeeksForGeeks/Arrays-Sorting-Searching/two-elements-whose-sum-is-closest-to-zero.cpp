// http://www.geeksforgeeks.org/two-elements-whose-sum-is-closest-to-zero/
#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 1010

void input(int [MAX], int &);
void findEles(int [MAX], int, int &, int &);
int abs(int);

int main() {
	int arr[MAX];
	int n;
	int closeE1, closeE2;

	input(arr, n);
	sort(arr, arr + n);

	findEles(arr, n,  closeE1, closeE2);
	printf("\nSum closest to zero is:-\n%d + %d = %d\n", closeE1, closeE2, closeE1 + closeE2);

	return 0;
}

void input(int arr[MAX], int &n) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void findEles(int arr[MAX], int n, int &closeE1, int &closeE2) {
	int minDiff;
	int i, j;

	minDiff = INT_MAX;
	for (i = 0, j = n - 1; i < j;) {
		int sum = arr[i] + arr[j];

		if (abs(sum) < minDiff) {
			minDiff = abs(sum);
			closeE1 = arr[i];
			closeE2 = arr[j];
		}

		if (sum > 0) {
			j--;
		} else if (sum < 0) {
			i++;
		} else {
			break;
		}
	}
}

int abs(int a) {
	if (a >= 0) {
		return a;
	} else {
		return -a;
	}
}
