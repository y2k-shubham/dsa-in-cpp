// http://www.geeksforgeeks.org/maximum-sum-pairs-specific-difference/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1456
// Space: O(n)
// Time: O(nlogn + n)	(sorting + dp)

/*
7
3 5 10 15 17 12 9
4

4
5 15 10 300
12
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void showArray(int [MAX], int, const char *);
void showPairs(int [MAX], int, int, int [MAX]);
void fillArr(int [MAX], int, int, int [MAX]);

int main() {
	int arr[MAX], len;
	int diffLim;
	int maxSum[MAX];

	input(arr, len, diffLim);
	showArray(arr, len, "after input, arr[]");

	sort(arr, arr + len);
	showArray(arr, len, "after sorting, arr[]");

	// Array based solution
	fillArr(arr, len, diffLim, maxSum);
	showArray(maxSum, len, "after filling, maxSum[]");

	cout << "\nMaximum possible sum is " << maxSum[len - 1] << endl;
	showPairs(arr, len, diffLim, maxSum);

	return 0;
}

void input(int arr[MAX], int &n, int &diffLim) {
	cout << "Enter n:\t";
	cin >> n;

	printf("Enter array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}

	cout << "Enter difference limit:\t";
	cin >> diffLim;
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void fillArr(int arr[MAX], int len, int diffLim, int maxSum[MAX]) {
	maxSum[0] = 0;
	maxSum[1] = (arr[1] - arr[0] < diffLim) ? (arr[0] + arr[1]) : 0;

	for (int i = 2; i < len; i++) {
		if (arr[i] - arr[i - 1] < diffLim) {
			maxSum[i] = max(maxSum[i  - 1], maxSum[i - 2] +  arr[i - 1] + arr[i]);
		} else {
			maxSum[i] = maxSum[i - 1];
		}
	}
}

void showPairs(int arr[MAX], int len, int diffLim, int maxSum[MAX]) {
	printf("\nDisjoint pairs having |p2 - p1| < %d that maximize the sum are:-\n", diffLim);

	for (int j = len - 1; j >= 1; ) {
		if (maxSum[j] == maxSum[j - 1]) {
			j--;
		} else {
			printf("(%d, %d)\t", arr[j - 1], arr[j]);
			j -= 2;
		}
	}
	cout << endl;
}

