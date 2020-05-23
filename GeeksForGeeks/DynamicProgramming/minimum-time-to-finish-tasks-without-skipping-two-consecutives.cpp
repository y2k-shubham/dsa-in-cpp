/* http://www.geeksforgeeks.org/minimum-time-to-finish-tasks-without-skipping-two-consecutive/
 * it's not actually dynamic programming as no memoization has been used, rather it's
 * a normal array question bearing some similarity with Dynamic Programming
 */

/*
 * although memoization does take place here, but since we need only the previous value
 * to take further decision, instead on constructing table, we opt for O(1) space
 */

 /*
 Inp:
 7
 8 1 3 7 4 2 9
 Out:
 10

 Inp:
 8
 10 5 2 4 8 6 7 10
 Out:
 22

 Inp:
 2
 10 30
 Out:
 10

 Inp:
 1
 10
 Out:
 10

 Inp:
 4
 10 5 7 10
 Out:
 12
 */

#include <cstdio>
#include <iostream>

using namespace std;

#define MAX 100
#define min(a, b) ((a < b) ? a : b)

void input(int [MAX], int &);
void calc(int [MAX], int);

int main() {
	int n;
	int arr[MAX];

	input(arr, n);
	calc(arr, n);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of tasks:\t");
	scanf("%d", &n);

	printf("Enter duration of tasks one-by-one:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void calc(int arr[MAX], int n) {
	int crrInc, crrExc;
	int prevInc, prevExc;

	prevInc = crrInc = arr[0];
	prevExc = crrExc = 0;

	for (int i = 1; i < n; i++) {
		// find the minimum time taken to finish activities 0..i if ith activity is included
		// implies that if we're including current (ith) activity, we may or may-not include
		// the previous (i - 1 th) activity
		crrInc = min(prevInc, prevExc) + arr[i];

		// find minimum time taken to finish 0..i activities 0..i if ith activity is excluded
		// implies that if we're excluding current (ith) activity, then we have to include
		// previous (i - 1 th) activity
		crrExc = prevInc;

		// update previous times of including and excluding the current activity
		prevInc = crrInc;
		prevExc = crrExc;
	}

	printf("\nMinimum total finish time is %d\n", min(crrInc, crrExc));
}
