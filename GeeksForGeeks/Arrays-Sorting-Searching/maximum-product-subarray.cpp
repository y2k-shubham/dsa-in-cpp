// http://www.geeksforgeeks.org/maximum-product-subarray/
// http://www.geeksforgeeks.org/maximum-product-subarray-set-2-using-two-traversals/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=433

// Set-1
// Time:	O(n)
// Space:	O(1)

// Set-2
// Time:	O(2n)
// Space:	O(1)

/*
Input
5
6 -3 -10 0 2
Output
180

Input
5
-1 -3 -10 0 60
Output
60

Input
5
-2 -3 0 -2 -40
Output
80

Input
6
2 3 4 5 -1 0
Output
120

Input
10
8 -2 -2 0 8 0 -6 -8 -6 -1
Output
288

Input
4
-1 -2 -3 4
Output
24

Input
1
-60
Output
0

Input
4
7 -3 -6 9
Output
1134

Input
7
1 -2 -3 0 7 -8 -2
Output
112
*/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
int findMaxProdSet1(int [MAX], int);
int findMaxProdSet2(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len);

	cout << "Max product of any subarray is " << findMaxProdSet1(arr, len) << endl;
	cout << "Max product of any subarray is " << findMaxProdSet2(arr, len) << endl;

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

int findMaxProdSet1(int arr[MAX], int len) {
	int nProd, pProd;
	int mProd;

	nProd = pProd = 0;
	mProd = 0;

	cout << endl;
	for (int i = 0; i < len; i++) {
		if (arr[i] > 0) {
			pProd = max(arr[i], pProd * arr[i]);
			nProd = 0;
		} else if (arr[i] < 0) {
			int pProdOld = pProd;

			pProd = max(0, nProd * arr[i]);
			nProd = min(arr[i], pProdOld * arr[i]);
		} else {
			pProd = nProd = 0;
		}

		mProd = max(mProd, pProd);

		//printf("at arr[%d] = %d\tpProd = %d\tnProd = %d\tmProd = %d\n", i, arr[i], pProd, nProd, mProd);
	}

	return mProd;
}

int findMaxProdSet2(int arr[MAX], int len) {
	int mProd, cProd;

	mProd = 0;

	cProd = 0;
	for (int i = 0; i < len; i++) {
		cProd = (cProd == 0) ? arr[i] : (cProd * arr[i]);
		mProd = max(mProd, cProd);
	}

	cProd = 0;
	for (int i = len - 1; i >= 0; i--) {
		cProd = (cProd == 0) ? arr[i] : (cProd * arr[i]);
		mProd = max(mProd, cProd);
	}

	return mProd;
}

