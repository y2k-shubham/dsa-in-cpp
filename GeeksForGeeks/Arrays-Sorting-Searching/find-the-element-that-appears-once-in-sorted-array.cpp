// http://practice.geeksforgeeks.org/problems/find-the-element-that-appears-once-in-sorted-array/0
// Ola Cabs, DE Shaw

/*
10

11
1 1 2 2 3 3 4 50 50 65 65

11
1 1 2 2 3 3 50 50 57 65 65

11
1 1 2 2 3 3 50 50 65 65 67

11
1 1 2 3 3 4 4 50 50 65 65

11
0 1 1 3 3 4 4 50 50 65 65

3
1 1 3

3
1 3 3

5
1 2 2 4 4

5
1 1 2 3 3

5
1 1 2 2 3
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 105

void input(int [MAX], int&);
void findNonRepeatedElement(int [MAX], int);
void showArr(int [MAX], int);
bool isEven(int);

int main() {
    int t;

    cin >> t;
    while (t-- > 0) {
        int arr[MAX];
        int len;

        input(arr, len);
        //showArr(arr, len);
        findNonRepeatedElement(arr, len);
    }

    return 0;
}

void input(int arr[MAX], int& len) {
    cin >> len;
    for (int i = 0; i < len; i++) {
        cin >> arr[i];
    }
}

void showArr(int arr[MAX], int len) {
    printf("\nInd:\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < len; i++) {
        printf("%d\t", arr[i]);
    }
    cout << endl;
}

void findNonRepeatedElement(int arr[MAX], int len) {
    int lo = 0;
    int hi = len - 1;
    int mid;
    int res;

    while ((hi - lo) >= 2) {
		if (arr[lo] != arr[lo + 1]) {
			res = lo;
			break;
		} else if (arr[hi] != arr[hi - 1]) {
			res = hi;
			break;
		} else {
			mid = (lo + hi) / 2;
			//printf("a[%d] = %d\ta[%d] = %d\ta[%d] = %d\n", lo, arr[lo], mid, arr[mid], hi, arr[hi]);

			if (isEven(mid - lo + 1)) {
				if (arr[mid] == arr[mid - 1]) {
					lo = mid + 1;
				} else {
					hi = mid - 1;
				}
			} else {
				if (arr[mid] == arr[mid - 1]) {
					hi = mid - 2;
				} else if (arr[mid] == arr[mid + 1]) {
					lo = mid + 2;
				} else {
					res = mid;
					break;
				}
			}
		}
    }

    //printf("\nUnique element is arr[%d] = %d\n", res, arr[res]);
    printf("%d\n", arr[res]);
}

bool isEven(int n) {
	return ((n % 2) == 0);
}
