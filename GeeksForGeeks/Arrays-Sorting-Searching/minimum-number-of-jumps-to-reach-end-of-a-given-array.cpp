// http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=153

/*
12

11
1 3 5 8 9 2 6 7 6 8 9

5
1 1 1 1 1

5
0 1 1 1 1

5
4 1 1 1 1

5
3 1 1 1 1

7
1 2 3 4 5 6 7

7
1 3 7 4 2 8 9

7
5 4 3 2 1 1 0

7
6 5 4 3 2 1 0

7
7 6 5 4 3 2 1

15
13 12 11 10 9 8 7 6 5 4 3 2 1 1 0

15
13 12 11 10 9 8 7 6 5 4 3 2 1 0 0
*/

#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;
#define MAX 101

int steps;

void input(int arr[MAX], int &len) {
	cin >> len;
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

int findMinJumpRec(int arr[MAX], int hi, int crr) {
	if (crr == hi) {
		// reached last index
		return 0;
	} else if (arr[crr] == 0) {
		return -1;
	} else if (crr + arr[crr] >= hi) {
		return 1;
	} else {
		int maxVal, maxInd;
		maxVal = -1;

		for (int i = crr + 1; i <= crr + arr[crr]; i++) {
			if (i + arr[i] >= hi) {
				maxInd = i;
				break;
			} else if (arr[i] + i >= maxVal) {
				maxInd = i;
				maxVal = arr[i] + i;
			}
		}

		return findMinJumpRec(arr, hi, maxInd) + 1;
	}
}

int findMinJumpIter(int arr[MAX], int hi) {
	int ctr, crr;
	ctr = crr = 0;

	while (true) {
		if (crr == hi) {
			// reached last index
			steps++;
			break;
		} else if (arr[crr] == 0) {
			return -1;
		} else if (crr + arr[crr] >= hi) {
			// possible to reach end in single jump
			steps++;
			ctr++;
			break;
		} else {
			steps++;
			int maxVal, maxInd;
			maxVal = -1;

			for (int i = crr + 1; i <= crr + arr[crr]; i++) {
				steps++;
				if (i + arr[i] >= hi) {
					maxInd = i;
					break;
				} else if (arr[i] + i >= maxVal) {
					maxInd = i;
					maxVal = arr[i] + i;
				}
			}

			ctr++;
			crr = maxInd;
		}
	}

	return ctr;
}

int main() {
	int T;

	cin >> T;
	while (T-- > 0) {
		int arr[MAX], len;

		cout << endl;

		steps = 0;
		input(arr, len);

		int count = findMinJumpIter(arr, len - 1);

		printf("Min Jumps = %d\tSteps taken = %d\n", count, steps);
	}

	return 0;
}

