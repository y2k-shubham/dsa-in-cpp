// http://www.geeksforgeeks.org/median-of-two-sorted-arrays/			(equal-length arrays)
// Amazon, DE Shaw

// Space: O(1)
// Time: O(logn)

/*
5
4	19	23	25	116
11	57	282	296	353

1
23
43

2
13 45
16 56

2
13 45
46 56

2
13 45
46 56

41
153 292 491 1869 2995 3902 4827 5436 5447 5705 6334 9894 9961 11478 11538 11942 12382 14604 14771 15724 16827 17035 17421 18467 18716 19169 19718 19895 19912 21726 23281 23811 24464 25667 26299 26500 26962 28145 28703 29358 32391
288 778 1842 3035 3548 4664 6729 6868 7711 8723 8942 9040 9741 12316 12623 12859 15006 15141 15350 15890 17673 19264 19629 20037 22190 22648 23805 24084 24370 24393 25547 27446 27529 27644 28253 30106 30333 31101 31322 32662 32757
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
#define MAX 100

void input(int [MAX], int, const char *);
void showArr(int [MAX], int, const char *);
void findMedian(int [MAX], int, int, int [MAX], int, int);
void showMedian(int [MAX], int, int, int [MAX], int, int);

int main() {
	int len;
	int arr_1[MAX], arr_2[MAX];

	printf("Enter lengths of arrays:\t");
	scanf("%d", &len);

	input(arr_1, len, "arr_1");
	input(arr_2, len, "arr_2");

	showArr(arr_1, len, "arr_1");
	showArr(arr_2, len, "arr_2");

	findMedian(arr_1, 0, len - 1, arr_2, 0, len - 1);

	return 0;
}

void input(int arr[MAX], int len, const char * name) {
	printf("\nEnter elements of %s[]:-\n", name);

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArr(int arr[MAX], int len, const char * name) {
	printf("\n%s[] array is:-\n", name);

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

void findMedian(int arr_1[MAX], int lo_1, int hi_1, int arr_2[MAX], int lo_2, int hi_2) {
	int len_1 = hi_1 - lo_1 + 1;
	int len_2 = hi_2 - lo_2 + 1;

	if (len_1 + len_2 <= 4) {
		showMedian(arr_1, lo_1, hi_1, arr_2, lo_2, hi_2);
	} else {
		int mid_1 = (lo_1 + hi_1) / 2;
		int mid_2 = (lo_2 + hi_2) / 2;

		printf("\narr_1[%d ..%d.. %d] = %d\n", lo_1, mid_1, hi_1, arr_1[mid_1]);
		printf("arr_2[%d ..%d.. %d] = %d\n", lo_2, mid_2, hi_2, arr_2[mid_2]);

		if (arr_1[mid_1] <= arr_2[mid_2]) {
			findMedian(arr_1, mid_1, hi_1, arr_2, lo_2, mid_2);
		} else {
			findMedian(arr_1, lo_1, mid_1, arr_2, mid_2, hi_2);
		}
	}
}

void showMedian(int arr_1[MAX], int lo_1, int hi_1, int arr_2[MAX], int lo_2, int hi_2) {
	printf("\nMedians are:-\n");

	printf("arr_1[%d] = %d\n", lo_1, arr_1[lo_1]);
	printf("arr_1[%d] = %d\n", hi_1, arr_1[hi_1]);
	printf("arr_2[%d] = %d\n", lo_2, arr_2[lo_2]);
	printf("arr_2[%d] = %d\n", hi_2, arr_2[hi_2]);

//	if (arr_1[lo_1] > arr_2[lo_2]) {
//		printf("arr_1[%d] = %d\n", lo_1, arr_1[lo_1]);
//	} else {
//		printf("arr_2[%d] = %d\n", lo_2, arr_2[lo_2]);
//	}
//
//	if (arr_1[hi_1] < arr_2[hi_2]) {
//		printf("arr_1[%d] = %d\n", hi_1, arr_1[hi_1]);
//	} else {
//		printf("arr_2[%d] = %d\n", hi_2, arr_2[hi_2]);
//	}
}
