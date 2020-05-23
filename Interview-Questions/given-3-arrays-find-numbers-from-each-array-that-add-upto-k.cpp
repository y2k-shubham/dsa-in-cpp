// Directii Interview Question
// http://ambitionbox.com/directi-interview-questions
// Time: O(n^2 + 3nlogn)		Space: O(1)

/*
8
1 1 2 9 11 13 15 15
2 3 5 6 6 7 8 8
-4 -10 0 0 0 10 12 19
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>
#include <utility>

using namespace std;
#define MAX 100

void input(int [MAX], int, const char *);
void findNums(int [MAX], int [MAX], int [MAX], int, int);

int main() {
	int a1[MAX], a2[MAX], a3[MAX];
	int len;
	int k;

	cout << "Enter length of arrays:\t";
	cin >> len;

	input(a1, len, "first");
	input(a2, len, "second");
	input(a3, len, "third");

	sort(a1, a1 + len);
	sort(a2, a2 + len);
	sort(a3, a3 + len);

	cout << "Enter required sum k:\t";
	cin >> k;

	findNums(a1, a2, a3, len, k);

	return 0;
}

void input(int arr[MAX], int len, const char * msg) {
	printf("Enter elements of %s array:\t", msg);
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void findNums(int a1[MAX], int a2[MAX], int a3[MAX], int len, int reqSum) {
	cout << endl << "Numbers adding upto " << reqSum << " are:-\n";
	for (int i = 0; i < len; i++) {
		int j, k;
		set <pair <int, int> > indSet;
		int remSum = reqSum - a1[i];

		// if we use reverse initialization for j and k, then also we'll get solution (possible different)
		for (j = 0, k = len - 1; j < len && k >= 0; ) {
			int crrSum = a2[j] + a3[k];

			if (crrSum < remSum) {
				j++;
			} else if (crrSum > remSum) {
				k--;
			} else {
				indSet.insert(make_pair(j, k));
				printf("a1[%d] = %d\ta2[%d] = %d\ta3[%d] = %d\n", i, a1[i], j, a2[j], k, a3[k]);
				j++;
//				break;
			}
		}

		// like this
		for (j = len - 1, k = 0; j >= 0 && k < len; ) {
			int crrSum = a2[j] + a3[k];

			if (crrSum < remSum) {
				k++;
			} else if (crrSum > remSum) {
				j--;
			} else if (indSet.find(make_pair(j, k)) == indSet.end()) {
				indSet.insert(make_pair(j, k));
				printf("a1[%d] = %d\ta2[%d] = %d\ta3[%d] = %d\n", i, a1[i], j, a2[j], k, a3[k]);
				k++;
//				break;
			} else {
				k++;
			}
		}
	}
}

