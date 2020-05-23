// Karumanchi, Searching, Problem 59, Page 296
// Time: O(n / 2)		Space: O(1)			:D

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findMajEle(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	printf("\nMajority element is:\t%d\n", findMajEle(arr, len));

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:\t");
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

int findMajEle(int arr[MAX], int len) {
	for (int i = 0; i <= len / 2; i++) {
		if (arr[i] == arr[i + 1]) {
			return arr[i];
		} else if (arr[i] == arr[i + 2]) {
			return arr[i];
		}
	}
}

