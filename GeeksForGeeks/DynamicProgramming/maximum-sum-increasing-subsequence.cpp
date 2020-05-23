// http://www.geeksforgeeks.org/dynamic-programming-set-14-maximum-sum-increasing-subsequence/

/*
7
1 101 2 3 100 4 5
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void init(int [MAX], int, pair <int, int> [MAX]);
int calc(int [MAX], int, pair <int, int> [MAX]);
void output(int [MAX], int, pair <int, int> [MAX], int);
void showArray(pair <int, int> [MAX], int, const char *);
void showArray(int [MAX], int, const char *);

int main() {
	int arr[MAX];
	int n;
	pair <int, int> soln[MAX];

	input(arr, n);
	showArray(arr, n, "arr");

	init(arr, n, soln);
	showArray(soln, n, "soln after init");

	int endInd = calc(arr, n, soln);
	showArray(soln, n, "soln after calc");

	printf("\nSum of maximum sum increasing subsequence is %d\n", soln[endInd].first);

	printf("Maximum sum increasing subsequence is:-\n");
	output(arr, n, soln, endInd);

	return 0;
}

void input(int arr[MAX], int &n) {
	cout << "Enter n:\t";
	cin >> n;

	printf("Enter array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void init(int arr[MAX], int n, pair <int, int> soln[MAX]) {
	for (int i = 0; i < n; i++) {
		soln[i].first = max(arr[i], 0);
		soln[i].second = i;
	}
}

int calc(int arr[MAX], int n, pair <int, int> soln[MAX]) {
	int maxSum, maxSumEndInd;

	maxSum = -1;
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (arr[j] < arr[i] && soln[i].first < soln[j].first + arr[i]) {
				soln[i].first = soln[j].first + arr[i];
				soln[i].second = j;

				if (soln[i].first > maxSum) {
					maxSum = soln[i].first;
					maxSumEndInd = i;
				}
			}
		}
	}

	return maxSumEndInd;
}

void output(int arr[MAX], int n, pair <int, int> soln[MAX], int ind) {
	if (soln[ind].second == ind) {
		printf("arr[%d] = %d\n", ind, arr[ind]);
	} else {
		output(arr, n, soln, soln[ind].second);
		printf("arr[%d] = %d\n", ind, arr[ind]);
	}
}

void showArray(pair <int, int> arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Sum:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i].first);
	}
	cout << endl;

	cout << "Par:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i].second);
	}
	cout << endl;
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

