// http://www.geeksforgeeks.org/check-if-each-internal-node-of-a-bst-has-exactly-one-child/

/*
5
20 10 11 13 12

5
20 10 11 12 13

5
10 20 11 12 13

5
11 20 10 12 13
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
bool method_1(int [MAX], int);
bool method_2(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);

	bool res1 = method_1(arr, len);
	bool res2 = method_2(arr, len);
	if (res1 == res2) {
		if (res1) {
			printf("\nIt's a skewed bst's preorder traversal\n");
		} else {
			printf("\nIt's not a skewed bst's preorder traversal\n");
		}
	} else {
		printf("\nSome error\t");
		if (res1) {
			cout << "res1 = true\t";
		} else {
			cout << "res1 = false\t";
		}
		if (res2) {
			cout << "res2 = true\n";
		} else {
			cout << "res2 = false\n";
		}
	}

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of sequence\t";
	cin >> len;

	cout << "Enter pre-order traversal of BST:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

bool method_1(int arr[MAX], int len) {
	for (int i = 0; i < len - 3; i++) {
		// either both next and last elements are greater than current or both are lesser than current
		if ((arr[i] > arr[i + 1] && arr[i] > arr[len - 1]) || (arr[i] < arr[i + 1] && arr[i] < arr[len - 1])) {
			continue;
		} else {
			return false;
		}
	}

	return true;
}

bool method_2(int arr[MAX], int len) {
	if (len < 3) {
		return true;
	} else {
		int min, max;

		// initialize min and max with last two elements
		if (arr[len - 1] < arr[len - 2]) {
			min = arr[len - 1];
			max = arr[len - 2];
		} else {
			min = arr[len - 2];
			max = arr[len - 1];
		}

		/*
		now scan remaining array backwards,
		if an element lies in range between min and max, then return false
		otherwise update min or max (whichever applicable) and continue scanning backwards
		*/
		for (int i = len - 3; i >= 0; i--) {
			if (arr[i] >= min && arr[i] <= max) {
				return false;
			} else if (arr[i] < min) {
				min = arr[i];
			} else {
				max = arr[i];
			}
		}

		return true;
	}
}

