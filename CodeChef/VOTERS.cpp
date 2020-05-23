#include <stdio.h>
#include <stdbool.h>
#include <climits>

#define max 150000

void scanInt(int &);
bool isPresent(int [], int, int, int);
void input(int [], int);
void output(int [], int [], int [], int [], int, int, int);
void showArray(int [], int);

int main() {
	int N1;
	int N2;
	int N3;

	scanInt(N1);
	scanInt(N2);
	scanInt(N3);

	int A[N1 + 1];
	int B[N2 + 1];
	int C[N3 + 1];
	int finalList[max];

	input(A, N1);
	input(B, N2);
	input(C, N3);
	output(A, B, C, finalList, N1, N2, N3);

	return 0;
}

void scanInt(int &x) {
	register int c;

	c = getchar();
	x = 0;

	// ignoring characters (consuming unwanted bits)
	for ( ; ((c < 48) || (c > 57)); ) {
		c = getchar();
	}

	// reading and constructing numbers
	for ( ; ((c > 47) && (c < 58)); ) {
		x = (x << 3) + (x << 1) + c - 48;
		c = getchar();
	}
}

bool isPresent(int arr[], int lo, int hi, int ele) {
	int mid;

	while (lo <= hi) {
        //printf("inside loop");
        //printf("\nlo = %d\nhi = %d\nmid = %d\narr[mid] = %d\nele = %d\n", lo, hi, mid, arr[mid], ele);
        mid = (lo + hi) >> 1;

        if (ele < arr[mid]) {
            hi = mid - 1;
            //printf("hi changed to %d\n", hi);
        } else if (ele > arr[mid]) {
            lo = mid + 1;
            //printf("lo changed to %d\n", lo);
        } else {
            arr[mid] = -999;
            return true;
        }
	}

    return false;
    /*
	if ((lo == hi) && (arr[lo] == ele)) {
        return true;
	} else {
        return false;
	}
	*/
}

void input(int arr[], int len) {
	int i;

	for (i = 0; i < len; i++) {
		scanInt(arr[i]);
	}
}

void showArray(int arr[], int len) {
    int i;

    for (i = 0; i < len; i++) {
        if (arr[i] == -999) {
            printf("_\t");
        } else {
            printf("%d\t", arr[i]);
        }
    }
    printf("\n");
}

void output(int A[], int B[], int C[], int finalList[], int N1, int N2, int N3) {
	int i;
	int j;
	int k;
	int l;
	int ele;
	int ctr;
	bool result_1;
	bool result_2;

	A[N1] = B[N2] = C[N3] = INT_MAX;
	i = j = k = l = ctr = 0;

	while (/*(ctr <= 50) && */((i <= N1) || (j <= N2) || (k <= N3)) && !((A[i] == INT_MAX) && (B[j] == INT_MAX) && (C[k] == INT_MAX))) {
        //++ctr;

        /*
        printf("\nA = ");
        showArray(A, N1);
        printf("B = ");
        showArray(B, N2);
        printf("C = ");
        showArray(C, N3);
        printf("f = ");
        showArray(finalList, l);
        printf("\n");
        */

        while (A[i] == -999) {
            ++i;
        }
        while (B[j] == -999) {
            ++j;
        }
        while (C[k] == -999) {
            ++k;
        }
        if (((ele = A[i]) <= B[j]) && (ele <= C[k])) {
            //printf("ele = %d from A\n", ele);
            i++;
            result_1 = isPresent(B, 0, (N2 - 1), ele);
            result_2 = isPresent(C, 0, (N3 - 1), ele);
            if (result_1 || result_2) {
                //printf("%d is present in two lists\n", ele);
                finalList[l++] = ele;
            }
        } else if (((ele = B[j]) <= A[i]) && (ele <= C[k])) {
            //printf("ele = %d from B\n", ele);
            j++;
            result_1 = isPresent(A, 0, (N1 - 1), ele);
            result_2 = isPresent(C, 0, (N3 - 1), ele);
            if (result_1 || result_2) {
                //printf("%d is present in two lists\n", ele);
                finalList[l++] = ele;
            }
        } else if (((ele = C[k]) <= A[i]) && (ele <= B[j])) {
            //printf("ele = %d from C\n", ele);
            k++;
            result_1 = isPresent(B, 0, (N2 - 1), ele);
            result_2 = isPresent(A, 0, (N1 - 1), ele);
            if (result_1 || result_2) {
                //printf("%d is present in two lists\n", ele);
                finalList[l++] = ele;
            }
        }
	}

	printf("%d\n", l);
	for (i = 0; i < l; i++) {
        printf("%d\n", finalList[i]);
	}
}
