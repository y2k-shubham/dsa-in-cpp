// Assumption:	All repeating elements occur even no of times in the array

#include <cstdio>
#include <iostream>

/*
6
2 4 7 9 2 4

10
5 5 7 7 6 3 9 9 9 9

8
5 5 7 7 6 3 9 9
*/

using namespace std;
#define MAX 100

int main() {
	int n;
	int arr[MAX];
	int xor_all = 0;
	int bitPos;

	// input and find XOR of all numbers
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		xor_all ^= arr[i];
	}

	// find rightmost (actually we may find any) set bit in XOR of all numbers of array
	// following step (finding right-most set bit can be done in O(1) time using X & ~(X -1)
	// the above operation will give a number where rightmost set bit of X is 1 and all others are 0
	for (bitPos = 0; bitPos < 32; bitPos++) {
		if ((xor_all & (1 << bitPos)) != 0) {
			break;
		}
	}

	/*
	Concept
	Since all numbers except two occur even no of times in the array, XOR of all numbers will of
	the array will be same as XOR of the only two non-repeating elements. Once we have XOR of two
	non repeating elements in array, we need to find a bit that is set in it. It is then guaranteed
	that the set bit will differ in the two non-repeating elements (otherwise it would have been 0)

	Now we scan the array again and this time find two XORs. All numbers where the kth bit found
	above is set, are XORed to one integer and remaining are XORed to other integer. At the end,
	the two integers correspond to the non-repeating elements of the array
	*/

	int res1 = 0;
	int res2 = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] & (1 << bitPos)) {
			res1 ^= arr[i];
		} else {
			res2 ^= arr[i];
		}
	}

	printf("\nNon-repeating elements are %d and %d\n", res1, res2);
	return 0;
}

