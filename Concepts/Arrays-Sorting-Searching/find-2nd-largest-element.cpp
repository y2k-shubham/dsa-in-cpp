#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void find2ndLargest(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	find2ndLargest(arr, len);

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void find2ndLargest(int arr[MAX], int len) {
	if (len < 2) {
		printf("\n2nd Largest element doesn't exist\n");
	} else {
		int max1val, max1ind;
		int max2val;

		max1val = max2val = INT_MIN;
		for (int i = 0; i < len; i++) {
			if (arr[i] >= max1val) {
				// every time highest element is found, transfer previously found highest value to
				// max2val variable
				max2val = max1val;
				max1val = arr[i];
				max1ind = i;
			}
		}

		if (max2val == INT_MIN) {
			// if unluckily the first element of the array was highest, then max2val won't be updated
			// so we'll need another traversal to find 2nd highest element
			for (int i = 0; i < len; i++) {
				if (arr[i] > max2val && i != max1ind) {
					max2val = arr[i];
				}
			}
		}

		printf("\n2nd largest element is %d\n", max2val);
	}
}

