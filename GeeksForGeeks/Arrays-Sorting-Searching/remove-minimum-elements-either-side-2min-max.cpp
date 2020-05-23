// Amazon Interview Question: http://www.practice.geeksforgeeks.org/problem-page.php?pid=445
// Editorial: http://www.geeksforgeeks.org/remove-minimum-elements-either-side-2min-max/
#include <cstdio>
#include <iostream>
#include <climits>
#include <cstring>

using namespace std;
#define MAX 1000
#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

void input(int [MAX], int);
void output(int [MAX], int, int, int, int, int);
void findMinMax(int [MAX], int, int, int *, int *);
int findMin(int [MAX], int, int);
int findMax(int [MAX], int, int);
int approach_1(int [MAX], int, int, int *, int *, int *, int *);
short approach_2(int [MAX], int, int, int, int, short [MAX][MAX], int *, int *, int *, int *);

int main() {
	int T;
	int N;
	int mini;
	int maxi;
	int lo;
	int hi;
	int arr[MAX];
	int count;
	short countTab[MAX][MAX];

	cout << "Enter no of test cases:\t";
	scanf("%d", &T);
	while (T-- > 0) {
		cout << "\nEnter length of array N = ";
		scanf("%d", &N);
		input(arr, N);

		lo = -1;
		hi = -1;
		mini = INT_MAX;
		maxi = INT_MIN;
		memset(countTab, -1, sizeof(countTab));

		//count = approach_1(arr, 0, N - 1, &lo, &hi, &mini, &maxi);
		count = approach_2(arr, 0, N - 1, findMin(arr, 0, N - 1), findMax(arr, 0, N - 1), countTab, &lo, &hi, &mini, &maxi);
		output(arr, lo, hi, mini, maxi, count);
	}

	return 0;
}

void input(int arr[MAX], int N) {
	int i;

	cout << "Enter the array:-" << endl;
	for (i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
}

void output(int arr[MAX], int lo, int hi, int mini, int maxi, int count) {
	int i;

	cout << "\nThe trimmed array is:-" << endl;
	for (i = lo; i <= hi; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;

	cout << "No of trims:\t" << count << endl;
	cout << "Minimum:\t" << mini << endl;
	cout << "Maximum:\t" << maxi << endl << endl;
}

void findMinMax(int arr[MAX], int lo, int hi, int * mini, int * maxi) {
	int i;

	*mini = INT_MAX;
	*maxi = INT_MIN;
	for (i = lo; i <= hi; i++) {
		if (arr[i] < *mini) {
			*mini = arr[i];
		}
		if (arr[i] > *maxi) {
			*maxi = arr[i];
		}
	}
}

int findMin(int arr[MAX], int lo, int hi) {
	int i;
	int mini;

	mini = INT_MAX;
	for (i = lo; i <= hi; i++) {
		if (arr[i] < mini) {
			mini = arr[i];
		}
	}

	return mini;
}

int findMax(int arr[MAX], int lo, int hi) {
	int i;
	int maxi;

	maxi = INT_MIN;
	for (i = lo; i <= hi; i++) {
		if (arr[i] > maxi) {
			maxi = arr[i];
		}
	}

	return maxi;
}

int approach_1(int arr[MAX], int lo, int hi, int * mLo, int * mHi, int * mini, int * maxi) {
	if (lo <= hi) {
		int cMini;
		int cMaxi;

		findMinMax(arr, lo, hi, &cMini, &cMaxi);

		if (2 * cMini > cMaxi) {
			*mini = cMini;
			*maxi = cMaxi;
			*mLo = lo;
			*mHi = hi;
			return 0;
		} else {
			return 1 + min(approach_1(arr, lo + 1, hi, mLo, mHi, mini, maxi), approach_1(arr, lo, hi - 1, mLo, mHi, mini, maxi));
		}
	} else {
		return 0;
	}
}

short approach_2(int arr[MAX], int lo, int hi, int cMini, int cMaxi, short count[MAX][MAX], int * mLo, int * mHi, int * mini, int * maxi) {
	if (lo <= hi) {
		if (2 * cMini > cMaxi) {
			*mini = cMini;
			*maxi = cMaxi;
			*mLo = lo;
			*mHi = hi;
			return 0;
		} else if (count[lo][hi] >= 0) {
			return count[lo][hi];
		} else {
			short ctr_1;
			short ctr_2;

			if (arr[lo] == cMini) {
				cMini = findMin(arr, lo + 1, hi);
			}
			if (arr[lo] == cMaxi) {
				cMaxi = findMax(arr, lo + 1, hi);
			}
			ctr_1 = approach_2(arr, lo + 1, hi, cMini, cMaxi, count, mLo, mHi, mini, maxi);

			if (arr[hi] == cMini) {
				cMini = findMin(arr, lo, hi - 1);
			}
			if (arr[hi] == cMaxi) {
				cMaxi = findMax(arr, lo, hi - 1);
			}
			ctr_2 = approach_2(arr, lo, hi - 1, cMini, cMaxi, count, mLo, mHi, mini, maxi);

			count[lo][hi] = 1 + min(ctr_1, ctr_2);
			return count[lo][hi];
		}
	} else {
		return 0;
	}
}

