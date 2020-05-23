// http://www.geeksforgeeks.org/find-subarray-with-given-sum/

/*
Input
6
1 4 20 3 10 5
33
Output
arr[2 .. 4]

Input
7
1 4 0 0 3 10 5
7
Output
arr[1 .. 4]

Input
2
1 4
0
Output
<nothing>
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void output(int [MAX], int, int);

int main() {
	int arr[MAX];
	int len;
	int reqSum;

	input(arr, len, reqSum);
	output(arr, len, reqSum);

	return 0;
}

void input(int arr[MAX], int &len, int &reqSum) {
	printf("Enter length of array:\t");
	scanf("%d", &len);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		scanf("%d", &arr[i]);
	}

	printf("Enter required sum:\t");
	scanf("%d", &reqSum);
}

void output(int arr[MAX], int len, int reqSum) {
	int crrSum;
	int lo, hi;

	lo = 0;
	hi = -1;
	crrSum = 0;

	cout << endl;
	while (lo < len) {
		if (crrSum < reqSum || lo > hi) {
			crrSum += arr[++hi];
		} else if (crrSum > reqSum) {
			crrSum -= arr[lo++];
		}

		if (crrSum == reqSum && lo <= hi) {
			printf("arr[%d .. %d] has sum %d\n", lo, hi, reqSum);

			if (hi < len) {
				crrSum += arr[++hi];
			} else {
				break;
			}
		}
	}
}
