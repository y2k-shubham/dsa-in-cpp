// http://www.geeksforgeeks.org/remove-minimum-elements-either-side-2min-max/

/*
9
4 5 100 9 10 11 12 15 200

4
4 7 5 6

4
20 7 5 6

4
20 4 1 3

4
20 3 1 3

4
20 3 2 4

4
20 3 2 3
*/

#include <cstdio>
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
void init(int [MAX], tuple <int, int, int, int, int> [MAX][MAX], int);
void showTab(int [MAX], int, tuple <int, int, int, int, int> [MAX][MAX], int, const char *);
void fillTab(int [MAX], int, tuple <int, int, int, int, int> [MAX][MAX]);
void showSoln(int [MAX], int, tuple <int, int, int, int, int> [MAX][MAX]);
void betterWay(int [MAX], int);

int main() {
	int arr[MAX], len;
	tuple <int, int, int, int, int> tab[MAX][MAX];

	input(arr, len);
	showArray(arr, len);

	init(arr, tab, len);

	cout << endl << "BEFORE FILLING TABLE" << endl;
	showTab(arr, len, tab, 0, "Step-Count");
	showTab(arr, len, tab, 1, "Min-Max");
	showTab(arr, len, tab, 2, "Parent");
	cout << endl << "============================" << endl;

	fillTab(arr, len, tab);

	cout << endl << "AFTER FILLING TABLE" << endl;
	showTab(arr, len, tab, 0, "Step-Count");
	showTab(arr, len, tab, 1, "Min-Max");
	showTab(arr, len, tab, 2, "Parent");
	cout << endl << "============================" << endl;

	showArray(arr, len);
	showSoln(arr, len, tab);

	betterWay(arr, len);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 1; i <= len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i =  1; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void init(int arr[MAX], tuple <int, int, int, int, int> tab[MAX][MAX], int len) {
	for (int i = 1; i <= len; i++) {
		for (int j = 1; j <= len; j++) {
			(get <0> (tab[i][j])) = INT_MAX;
			(get <1> (tab[i][j])) = INT_MAX;
			(get <2> (tab[i][j])) = INT_MIN;
			(get <3> (tab[i][j])) = -1;
			(get <4> (tab[i][j])) = -1;
		}
	}

	for (int i = 1; i <= len; i++) {
		(get <0> (tab[i][i])) = 0;
		(get <1> (tab[i][i])) = arr[i];
		(get <2> (tab[i][i])) = arr[i];
	}
}

void showTab(int arr[MAX], int len, tuple <int, int, int, int, int> tab[MAX][MAX], int choice, const char * msg) {
	printf("\n%s table is:-\n", msg);

	cout << "\t";
	for (int i = 1; i <= len; i++) {
		printf("a[%d]\t", i);
	}
	cout << endl;

	cout << "\t";
	for (int i = 1; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;

	for (int i = 1; i <= len; i++) {
		printf("[%d]=%d\t", i, arr[i]);
		for (int j = 1; j <= len; j++) {
			if (choice == 0) {
				if (get <0> (tab[i][j]) == INT_MAX) {
					printf("_\t");
				} else {
					printf("%d\t", get <0> (tab[i][j]));
				}
			} else if (choice == 1) {
				if (get <1> (tab[i][j]) == INT_MAX) {
					printf("_,_\t");
				} else {
					printf("%d,%d\t", get <1> (tab[i][j]), get <2> (tab[i][j]));
				}
			} else {
				if (get <3> (tab[i][j]) < 0) {
					printf("_,_\t");
				} else {
					printf("%d,%d\t", get <3> (tab[i][j]), get <4> (tab[i][j]));
				}
			}
		}
		cout << endl;
	}
}

void fillTab(int arr[MAX], int len, tuple <int, int, int, int, int> tab[MAX][MAX]) {
	int rBeg = 1;
	for (int cBeg = 2; cBeg <= len; cBeg++) {
		int i = rBeg;
		int j = cBeg;

		while (j <= len) {
			int minOv = min(get <1> (tab[i + 1][j]), get <1> (tab[i][j - 1]));
			int maxOv = max(get <2> (tab[i + 1][j]), get <2> (tab[i][j - 1]));

			if (2 * minOv > maxOv) {
				// property already satisfied
				get <0> (tab[i][j]) = 0;
			} else if (get <0> (tab[i + 1][j]) < get <0> (tab[i][j - 1])) {
				get <0> (tab[i][j]) = get <0> (tab[i + 1][j]) + 1;
				get <3> (tab[i][j]) = i + 1;
				get <4> (tab[i][j]) = j;
			} else {
				get <0> (tab[i][j]) = get <0> (tab[i][j - 1]) + 1;
				get <3> (tab[i][j]) = i;
				get <4> (tab[i][j]) = j - 1;
			}

			get <1> (tab[i][j]) = minOv;
			get <2> (tab[i][j]) = maxOv;

			i++;
			j++;
		}
	}
}

void showSoln(int arr[MAX], int len, tuple <int, int, int, int, int> tab[MAX][MAX]) {
	printf("\nOperations needed to get desired array are:-\n");

	int i, j;
	for (i = 1, j = len; j >= i && get <0> (tab[i][j]) > 0; ) {
		if (get <3> (tab[i][j]) > i) {
			// remove first element of range i .. j
			printf("remove arr[%d] = %d\n", i, arr[i]);
			i++;
		} else {
			// remove last element of range i .. j
			printf("remove arr[%d] = %d\n", j, arr[j]);
			j--;
		}
	}

	printf("\nFinal array after chopping is:-\n");

	cout << "Ind:\t";
	for (int k = i; k <= j; k++) {
		printf("[%d]\t", k);
	}
	cout << endl;

	cout << "Val:\t";
	for (int k = i; k <= j; k++) {
		printf("%d\t", arr[k]);
	}
	cout << endl;
}

void betterWay(int arr[MAX], int len) {
	int maxRSize;
	int maxRIndL, maxRIndR;

	maxRSize = 0;
	for (int i = 1; i <= len; i++) {
		int minVal = INT_MAX;
		int maxVal = INT_MIN;

		for (int j = i; j <= len; j++) {
			int ele = arr[j];
			minVal = min(minVal, ele);
			maxVal = max(maxVal, ele);

			if (2 * minVal <= maxVal) {
				break;
			} else if (j - i + 1 > maxRSize) {
				maxRSize = j - i + 1;
				maxRIndL = i;
				maxRIndR = j;
			}
		}
	}

	printf("\nFinal array after chopping is:-\n");

	cout << "Ind:\t";
	for (int k = maxRIndL; k <= maxRIndR; k++) {
		printf("[%d]\t", k);
	}
	cout << endl;

	cout << "Val:\t";
	for (int k = maxRIndL; k <= maxRIndR; k++) {
		printf("%d\t", arr[k]);
	}
	cout << endl;
}


