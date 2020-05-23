/*
    given 3 sorted arrays A[p], B[q], and C[r],
    find elements i, j, k from the three arrays such that
    max(abs(a[i] - b[j]), abs(b[j] - c[k]), abs(c[k] - a[i]))
	is minimized
*/
#include <stdio.h>
#include <limits.h>

#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a > b) ? b : a)
#define SIZE 100

void input(int [], int *, char);
int findElements(int [], int, int *, int [], int, int *, int [], int, int *, int);
int getMinDiffPos(int, int [], int, int, int);
int abs(int a);

int main() {
	int A[SIZE];
	int B[SIZE];
	int C[SIZE];
	int p;
	int q;
	int r;
	int minimum;
	int i;
	int j;
	int k;

	input(A, &p, 'A');
	input(B, &q, 'B');
	input(C, &r, 'C');

	minimum = INT_MAX;
	minimum = findElements(A, p, &i, B, q, &j, C, r, &k, minimum);
	minimum = findElements(B, q, &j, C, r, &k, A, p, &i, minimum);
	minimum = findElements(C, r, &k, A, p, &i, B, q, &j, minimum);

	printf("\nA[%d] = %d\tB[%d] = %d\tC[%d] = %d\tdiff = %d\n", i, A[i], j, B[j], k, C[k], minimum);

	return 0;
}

void input(int arr[], int * len, char arrName) {
	int i;

	printf("\nEnter length of %c:\t", arrName);
	scanf("%d", len);

	printf("Enter elements of %c:\t", arrName);
	for (i = 0; i < *len; i++) {
		scanf("%d", &arr[i]);
	}
}

int findElements(int arr_1[], int len_1, int * ind_1, int arr_2[], int len_2, int * ind_2, int arr_3[], int len_3, int * ind_3, int minimum) {
	int i;
	int pos_2;
	int pos_3;

    printf("\n");
	for (i = 0; i < len_1; i++) {
		pos_2 = getMinDiffPos(arr_1[i], arr_2, len_2, 0, len_2 - 1);
		pos_3 = getMinDiffPos(arr_1[i], arr_3, len_3, 0, len_3 - 1);

		printf("For ele %d, ele2 = %d and ele3 = %d\n", arr_1[i], arr_2[pos_2], arr_3[pos_3]);

		if (max(abs(arr_1[i] - arr_2[pos_2]), abs(arr_1[i] - arr_3[pos_3])) < minimum) {
			minimum = max(abs(arr_1[i] - arr_2[pos_2]), abs(arr_1[i] - arr_3[pos_3]));
            * ind_1 = i;
			* ind_2 = pos_2;
			* ind_3 = pos_3;
		}
	}

	return minimum;
}

int abs(int a) {
    if (a < 0) {
        return -1 * a;
    } else {
        return a;
    }
}

int getMinDiffPos(int ele, int arr[], int len, int lo, int hi) {
	if (lo <= hi) {
		int mid;

		mid = (lo + hi) / 2;
        printf("ele = %d\tarr[%d] = %d\tarr[%d] = %d\tarr[%d] = %d\n", ele, lo, arr[lo], mid, arr[mid], hi, arr[hi]);
		if (ele < arr[mid]) {
            //printf("called with 1st half\tlo = %d\tmid = %d\thi = %d\n", lo, mid, hi);
			return getMinDiffPos(ele, arr, len, lo, mid - 1);
		} else if (ele > arr[mid]) {
		    //printf("Called with 2nd half\n");
			return getMinDiffPos(ele, arr, len, mid + 1, hi);
		} else {
		    //printf("Equal ele found\n");
			return mid;
		}
	} else {
        //printf("Reached single element\n");
		int diff_1;
		int diff_2;
		int diff_3;

		diff_1 = (lo > 0) ? abs(arr[lo - 1] - ele) : INT_MAX;
		diff_2 = abs(arr[lo] - ele);
		diff_3 = (hi < len - 1) ? abs(arr[lo + 1] - ele) : INT_MAX;

        if (diff_1 != INT_MAX) {
            printf("diff_1 = abs(%d - %d) = %d\n", arr[lo - 1], ele, diff_1);
        }
        printf("diff_2 = abs(%d - %d) = %d\n", arr[lo], ele, diff_2);
        if (diff_3 != INT_MAX) {
            printf("diff_3 = abs(%d - %d) = %d\n", arr[lo + 1], ele, diff_3);
        }

		if  (diff_1 <= diff_2 && diff_1 <= diff_3) {
            //printf("mid - 1 is closest\n\n");
            printf("returning index %d based on least value of diff_1 = %d\n\n", lo - 1, diff_1);
			return lo - 1;
		} else if (diff_2 <= diff_3 && diff_2 <= diff_1) {
		    //printf("mid is closest\n\n");
		    printf("returning index %d based on least value of diff_2 = %d\n\n", lo, diff_2);
			return lo;
		} else {
		    //printf("mid + 1 is closest\n\n");
		    printf("returning index %d based on least value of diff_3 = %d\n\n", lo + 1, diff_3);
			return lo + 1;
		}
	}
}
