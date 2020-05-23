// http://www.geeksforgeeks.org/count-of-acute-obtuse-and-right-triangles-with-given-sides/

/*
6
2 3 9 10 12 15

11
2 3 5 6 7 9 11 19 23 27 29

11
2 4 5 7 9 9 12 13 15 16 25
*/

#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 100
#define sqr(n) (n * n)

void input(int [MAX], int &);
int findFloorInd_Norm(int [MAX], int, int, int);
int findCeilInd(int [MAX], int, int, int);
void showArray(int [MAX], int, const char *);
int findFloorInd_Norm(int [MAX], int, int, int);
int findFloorInd_Sqr(int [MAX], int, int, int);
int findCeilInd_Sqr(int [MAX], int, int, int);
void findTriangleCount(int [MAX], int, int&, int&, int&);

int main() {
	int arr[MAX], len;
	int countAcute, countRight, countObtuse;

	input(arr, len);
	sort(arr, arr + len);

	findTriangleCount(arr, len, countAcute, countRight, countObtuse);

	printf("\nNo of acute -angled triangles is %d\n", countAcute);
	printf("No of right -angled triangles is %d\n", countRight);
	printf("No of obtuse-angled triangles is %d\n", countObtuse);
	printf("Total no of possible triangles is %d\n", (countAcute + countRight + countObtuse));

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter length of array:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void showArray(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-", msg);

	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}

	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}

	printf("\n");
}

int findFloorInd_Norm(int arr[MAX], int lo, int hi, int sumAB) {
	if (arr[hi] < sumAB) {
		return hi;
	} else if (arr[lo] > sumAB) {
		return -1;
	} else {
		int mid = (lo + hi) / 2;

		if (arr[mid] < sumAB) {
			if (mid + 1 <= hi && arr[mid + 1] > sumAB) {
				return mid;
			} else {
				return findFloorInd_Norm(arr, mid + 1, hi, sumAB);
			}
		} else if (arr[mid] == sumAB) {
			if (mid - 1 >= lo && arr[mid - 1] < sumAB) {
				return mid;
			} else {
				return findFloorInd_Norm(arr, lo, mid - 1, sumAB);
			}
		} else {
			if (mid - 1 >= lo && arr[mid - 1] < sumAB) {
				return mid - 1;
			} else {
				return findFloorInd_Norm(arr, lo, mid - 1, sumAB);
			}
		}
	}
}

int findFloorInd_Sqr(int arr[MAX], int lo, int hi, int sumSqrAB) {
	if (sqr(arr[hi]) < sumSqrAB) {
		return hi;
	} else if (sqr(arr[lo]) > sumSqrAB) {
		return -1;
	} else {
		int mid = (lo + hi) / 2;

		if (sqr(arr[mid]) < sumSqrAB) {
			if (mid + 1 <= hi && sqr(arr[mid + 1]) > sumSqrAB) {
				return mid;
			} else {
				return findFloorInd_Sqr(arr, mid + 1, hi, sumSqrAB);
			}
		} else if (sqr(arr[mid]) == sumSqrAB) {
			if ((mid == lo) || (mid - 1 >= lo && sqr(arr[mid - 1]) < sumSqrAB)) {
				return mid;
			} else {
				return findFloorInd_Sqr(arr, lo, mid - 1, sumSqrAB);
			}
		} else {
			if (mid - 1 >= lo && sqr(arr[mid - 1]) < sumSqrAB) {
				return mid - 1;
			} else {
				return findFloorInd_Sqr(arr, lo, mid - 1, sumSqrAB);
			}
		}
	}
}

int findCeilInd_Sqr(int arr[MAX], int lo, int hi, int sumSqrAB) {
	if (sqr(arr[lo]) > sumSqrAB) {
		return lo;
	} else if (sqr(arr[hi]) < sumSqrAB) {
		return -1;
	} else {
		int mid = (lo + hi) / 2;

		if (sqr(arr[mid]) > sumSqrAB) {
			if (mid - 1 >= lo && sqr(arr[mid - 1]) < sumSqrAB) {
				return mid;
			} else {
				return findCeilInd_Sqr(arr, lo, mid - 1, sumSqrAB);
			}
		} else if (sqr(arr[mid]) == sumSqrAB) {
			if ((mid == hi) || (mid + 1 <= hi && sqr(arr[mid + 1]) > sumSqrAB)) {
				return mid;
			} else {
				return findCeilInd_Sqr(arr, mid + 1, hi, sumSqrAB);
			}
		} else {
			if (mid + 1 <= hi && sqr(arr[mid + 1]) > sumSqrAB) {
				return mid + 1;
			} else {
				return findCeilInd_Sqr(arr, mid + 1, hi, sumSqrAB);
			}
		}
	}
}

void findTriangleCount(int arr[MAX], int len, int& countAcute, int& countRight, int& countObtuse) {
	countAcute = countRight = countObtuse = 0;

	for (int i = 0; i < len - 2; i++) {
//		showArray(arr, len, "arr[]");

		for (int j = i + 1; j < len - 1; j++) {
			int floorIndNorm = findFloorInd_Norm(arr, j + 1, len - 1, arr[i] + arr[j]);
			int upLim = (arr[floorIndNorm] == arr[i] + arr[j]) ? (floorIndNorm - 1) : floorIndNorm;

			if (floorIndNorm < 0 || upLim == j) {
//				printf("For arr[%d] = %d and arr[%d] = %d, no triangles possible\n", i, arr[i], j, arr[j]);
			} else {
				//				printf("For arr[%d] = %d and arr[%d] = %d, %d triangles possible from arr[%d] = %d to arr[%d] = %d\n", i, arr[i], j, arr[j], (upLim - j), j + 1, arr[j + 1], upLim, arr[upLim]);

				int floorIndSqr = findFloorInd_Sqr(arr, j + 1, upLim, sqr(arr[i]) + sqr(arr[j]));
				int ceilIndSqr = findCeilInd_Sqr(arr, j + 1, upLim, sqr(arr[i]) + sqr(arr[j]));

//				printf("For arr[%d] = %d and arr[%d] = %d, sumSqr = %d, ", i, arr[i], j, arr[j], (sqr(arr[i]) + sqr(arr[j])));
				if (ceilIndSqr < 0) {
//					printf("Only acute -triangles possible till arr[%d] = %d\n", upLim, arr[upLim]);
					countAcute += upLim - j;
				} else if (floorIndSqr < 0) {
//					printf("Only obtuse-triangles possible till arr[%d] = %d\n", upLim, arr[upLim]);
					countObtuse += upLim - j;
				} else {
//					printf("\n%d Acute -triangles possible from arr[%d] = %d to arr[%d] = %d\n", ((sqr(arr[floorIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (floorIndSqr - j - 1) : (floorIndSqr - j)), j + 1, arr[j + 1], floorIndSqr, arr[floorIndSqr]);
//					printf("%d Right -triangles possible from arr[%d] = %d to arr[%d] = %d\n", ((sqr(arr[floorIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (ceilIndSqr - floorIndSqr + 1) : 0), floorIndSqr, arr[floorIndSqr], ceilIndSqr, arr[ceilIndSqr]);
//					printf("%d Obtuse-triangles possible from arr[%d] = %d to arr[%d] = %d\n", ((sqr(arr[ceilIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (upLim - ceilIndSqr) : (upLim - ceilIndSqr + 1)), ceilIndSqr, arr[ceilIndSqr], upLim, arr[upLim]);

					countAcute += (sqr(arr[floorIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (floorIndSqr - j - 1) : (floorIndSqr - j);
					countRight += (sqr(arr[floorIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (ceilIndSqr - floorIndSqr + 1) : 0;
					countObtuse += (sqr(arr[ceilIndSqr]) == sqr(arr[i]) + sqr(arr[j])) ? (upLim - ceilIndSqr) : (upLim - ceilIndSqr + 1);
				}
			}
		}
	}
}

