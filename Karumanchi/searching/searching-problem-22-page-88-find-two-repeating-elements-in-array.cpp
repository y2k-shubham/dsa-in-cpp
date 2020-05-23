// Data Structures and Algorithms Made Easy - Karumanchi, Searching, problem 22, page 88
// assumption, array of length n has elements in range 1 to n and the two repeating elements
// occur exactly twice

/*
9
7 5 9 2 5 4 3 2 1 8 6

5
1 5 4 5 3 2 1

2
1 2 2 1

3
1 3 2 1 3
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findXOR(int [MAX], int);
void findXOR(int [MAX], int, int, int &, int &);

int main() {
	int arr[MAX], n;
	int xor_com, xor_1, xor_2;

	input(arr, n);

	xor_com = findXOR(arr, n);				// xor of all array numbers and numbers from 1 to n
	xor_com = xor_com & ~(xor_com - 1);			// rightmost set bit

	findXOR(arr, n, xor_com, xor_1, xor_2);
	printf("\nTwo repeating numbers are:\t%d and %d\n", xor_1, xor_2);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("For range of numbers 1..n, enter n:\t");
	cin >> n;

	printf("Enter (n + 2) = (%d + 2) = %d elements of array:-\n", n, (n + 2));
	for (int i = 0; i < n + 2; i++) {
		cin >> arr[i];
	}
}

int findXOR(int arr[MAX], int n) {
	// XOR of all array elements
	int xor_arr = 0;
	for (int i = 0; i < n + 2; i++) {
		xor_arr ^= arr[i];
	}

	// XOR of all integers from 1 .. n
	int xor_1toN = 0;
	for (int i = 1; i <= n; i++) {
		xor_1toN ^= i;
	}

	return (xor_arr ^ xor_1toN);
}

void findXOR(int arr[MAX], int n, int mask, int &xor_1, int &xor_2) {
	xor_1 = xor_2 = 0;

	// find xor of array elements having kth bit set as well as of those having kth bit not set
	for (int i = 0; i < n + 2; i++) {
		if (arr[i] & mask) {
			xor_1 ^= arr[i];
		} else {
			xor_2 ^= arr[i];
		}
	}

	// find xor of integers from 1 to n having kth bit set as well of those having kth bit not set
	for (int i = 1; i <= n; i++) {
		if (i & mask) {
			xor_1 ^= i;
		} else {
			xor_2 ^= i;
		}
	}
}

