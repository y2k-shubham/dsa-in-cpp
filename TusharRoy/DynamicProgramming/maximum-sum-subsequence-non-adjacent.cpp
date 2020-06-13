// TusharRoy
// Karumanchi DP, problem 9, page 389
// Karumanchi DP, problem 11, page 390

/*
6
4 1 1 4 2 1

6
5 5 10 40 50 35

10
8 7 6 5 7 7 6 0 7 2

10
8 6 0 4 8 3 0 8 3 4

6
1 9 4 5 8 7

6
-110 80 30 10 90 80

6
-10 -50 -20 -40 -70 80

6
10 -10 -50 -60 -70 30

6
-10 -10 -50 -60 -70 -30

6
-10 -10 -50 -60 0 -30

2
5 10

0

2
5 -10

1
5

1
-5
*/

#include <cstdio>
#include <iostream>
#include <cmath>

#define MAX 100
using namespace std;

void input(int [MAX], int &);
void calcTR(int [MAX], int);
void calcTRSoln(int [MAX], int, int [MAX]);
void calcTRSolnNeg(int [MAX], int, int [MAX]);
void calcNKSolnNeg(int [MAX], int, int [MAX]);
void calcNK_Triples(int [MAX], int, int [MAX]);
void output(int [MAX], int, int [MAX]);
void showArray(int [MAX], int, const char *);

int main() {
	int arr[MAX];
	int len;
	int inc[MAX];

	input(arr, len);

//	calcTR(arr, len);				// TusharRoy's solution, gives answer, not actual sequence
//	calcTRSoln(arr, len, inc);		// Extension of above, builds array for actual sequence
	calcTRSolnNeg(arr, len, inc);	// Extension of above, accounts for negative numbers also
	output(arr, len, inc);

	calcNKSolnNeg(arr, len, inc);		// Karumanchi's solution
	output(arr, len, inc);

	calcNK_Triples(arr, len, inc);
	showArray(inc, len, "triples inc[] array is");

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

// this method only finds value of max sum subsequence having no adjacent elements, without displaying actual solution
void calcTR(int arr[MAX], int len) {
	// TusharRoy's solution

	int inc = arr[0];
	int exc = 0;

	for (int i = 1; i < len; i++) {
		int incOld = inc;
		inc = max(inc, exc + arr[i]);
		exc = incOld;
	}

	printf("\nMaximum sum of non-adjacent element subsequence is %d\n", max(inc, exc));
}

// this method creates inc[] array for displaying actual solution
void calcTRSoln(int arr[MAX], int len, int inc[MAX]) {
	// Extension of TusharRoy's solution

	inc[0] = arr[0];
	int exc = 0;

	for (int i = 1; i < len; i++) {
		int incOld = inc[i - 1];
		inc[i] = max(inc[i - 1], exc + arr[i]);
		exc = incOld;
	}
}

// this method creates inc[] array while also accounting for negative numbers in array (only initialization step differs from above)
void calcTRSolnNeg(int arr[MAX], int len, int inc[MAX]) {
	// Extension of TusharRoy's solution

	inc[0] = max(0, arr[0]);
	int exc = 0;

	for (int i = 1; i < len; i++) {
		int incOld = inc[i - 1];
		inc[i] = max(inc[i - 1], exc + arr[i]);
		exc = incOld;
	}
}

void calcNKSolnNeg(int arr[MAX], int len, int inc[MAX]) {
	// Karumanchi's solution (no inc / exc and works for negative numbers)
	inc[0] = max(arr[0], 0);
	inc[1] = max(inc[0], max(0, arr[1]));

	for (int i = 2; i < len; i++) {
		if (arr[i] > 0) {
			inc[i] = max(inc[i - 2] + arr[i], inc[i - 1]);
		} else {
			inc[i] = inc[i - 1];
		}
	}
}

void output(int arr[MAX], int len, int inc[MAX]) {
	int i;
	printf("\nMaximum sum of non-adjacent element subsequence is %d\n", inc[len - 1]);

	printf("Included numbers are:-\n");
	for (i = len - 1; i >= 1; ) {
		if (inc[i] == inc[i - 1]) {
			i--;
		} else {
			printf("arr[%d] = %d\n", i, arr[i]);
			i -= 2;
		}
	}

	if (i == 0 && arr[0] > 0) {
		printf("arr[0] = %d\n", arr[0]);
	} else {
		printf("\n");
	}
}

// Can't take 3 consecutive elements (but can take 2 consecutive elements)
void calcNK_Triples(int arr[MAX], int len, int inc[MAX]) {
	inc[0] = arr[0];
	inc[1] = arr[0] + arr[1];
	inc[2] = max(arr[0] + arr[1], max(arr[0] + arr[2], arr[1] + arr[2]));

	for (int i = 3; i < len; i++) {
		inc[i] = max(arr[i] + arr[i - 1] + inc[i - 3],
					 max(arr[i] + inc[i - 2], inc[i - 1]));
	}
}

void showArray(int a[MAX], int len, const char * name) {
	printf("\n%s array is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

