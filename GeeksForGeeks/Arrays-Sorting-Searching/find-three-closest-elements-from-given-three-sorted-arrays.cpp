// http://www.geeksforgeeks.org/find-three-closest-elements-from-given-three-sorted-arrays/

/*
Input:
3
1 4 10
3
2 15 20
2
10 12
Output:
10 15 10

Input:
3
20 24 100
5
2 19 22 79 800
5
10 12 23 24 119
Output:
24 22 23 or
24 22 24

Input:
2
8 100
3
2 9 10
3
2 9 10
Output:
8 9 9

Input:
5
4 7 9 12 15
5
0 8 10 14 20
5
6 12 16 30 50
Output:
7 8 6

Input:
3
4 7 30
2
1 2
2
20 40
Output:
4 2 20
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>
#include <cstdlib>

using namespace std;

#define MAX 100
#define max(a, b, c) ((a > b && a > c) ? a : ((b > a && b > c) ? b : c))
#define min(a, b, c) ((a < b && a < c) ? a : ((b < a && b < c) ? b : c))

void input(int [MAX], int &, const char *);
void method_2(int [MAX], int, int [MAX], int, int [MAX], int);
void method_3(int [MAX], int, int [MAX], int, int [MAX], int);
void binSearchClosest(int [MAX], int, int, int, int &, int &);

int main() {
	int n1, n2, n3;
	int a1[MAX], a2[MAX], a3[MAX];

	input(a1, n1, "first");
	input(a2, n2, "second");
	input(a3, n3, "third");

	method_2(a1, n1, a2, n2, a3, n3);
	method_3(a1, n1, a2, n2, a3, n3);

	return 0;
}

void input(int a[MAX], int &n, const char * msg) {
	printf("\nEnter size of %s array:\t", msg);
	scanf("%d", &n);

	printf("Enter elements of %s array:-\n", msg);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
}

void method_2(int a1[MAX], int n1, int a2[MAX], int n2, int a3[MAX], int n3) {
	int e1, e2, e3;
	int minDiff;

	minDiff = INT_MAX;
	for (int i = 0; i < n1; i++) {
		int tmp1, tmp2, tmp3;

		tmp1 = a1[i];
		int crrDiff;

		crrDiff = INT_MAX;
		binSearchClosest(a2, 0, n2 - 1, tmp1, crrDiff, tmp2);

		crrDiff = INT_MAX;
		binSearchClosest(a3, 0, n3 - 1, tmp1, crrDiff, tmp3);

		crrDiff = abs(tmp1 - tmp2) + abs(tmp2 - tmp3) + abs(tmp3 - tmp1);
		if (crrDiff < minDiff) {
			minDiff = crrDiff;
			e1 = tmp1;
			e2 = tmp2;
			e3 = tmp3;
		}
	}

	printf("\nClosest elements using method_2 are:\t%d\t%d\t%d\n", e1, e2, e3);
}

void binSearchClosest(int a[MAX], int lo, int hi, int ele, int &minDiff, int &minDiffEle) {
	if (lo <= hi) {
		int mid = (lo + hi) / 2;

		if (abs(ele - a[mid]) < minDiff) {
			minDiff = abs(ele - a[mid]);
			minDiffEle = a[mid];

			if (minDiff == 0) {
				return;
			}
		}

		if (ele < a[mid]) {
			binSearchClosest(a, lo, mid - 1, ele, minDiff, minDiffEle);
		} else {
			binSearchClosest(a, mid + 1, hi, ele, minDiff, minDiffEle);
		}
	}
}

void method_3(int a1[MAX], int n1, int a2[MAX], int n2, int a3[MAX], int n3) {
	int i1, i2, i3;
	int e1, e2, e3;
	int minDiff;

	minDiff = INT_MAX;
	for (i1 = i2 = i3 = 0; ; ) {
		int tmp1 = (i1 < n1) ? a1[i1] : tmp1;
		int tmp2 = (i2 < n2) ? a2[i2] : tmp2;
		int tmp3 = (i3 < n3) ? a3[i3] : tmp3;

		int maxE = max(tmp1, tmp2, tmp3);
		int minE = min(tmp1, tmp2, tmp3);

		if (maxE - minE < minDiff) {
			minDiff = maxE - minE;
			e1 = tmp1;
			e2 = tmp2;
			e3 = tmp3;
		}

		if (i1 < n1 && minE == a1[i1]) {
			i1++;
		} else if (i2 < n2 && minE == a2[i2]) {
			i2++;
		} else if (i3 < n3) {
			i3++;
		} else {
			break;
		}
	}

	printf("Closest elements using method_3 are:\t%d\t%d\t%d\n", e1, e2, e3);
}
