// slight modification of the classical subset-sum problem
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=351
// http://www.geeksforgeeks.org/dynamic-programming-subset-reqSum-problem/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;
#define MAX 101

int * input(int *, int *, int &);
void init(int *, bool *, int, int);
void fillTab(int *, int, int, bool *);
void output(int *, int, int, bool *);
void showTable(bool *, int, int);

int main() {
	int T;
	int n, reqSum, actSum;
	int * arr;

	scanf("%d", &T);

	while (T-- > 0) {
		arr = input(&n, &reqSum, actSum);

		if (actSum % 2 != 0) {
			printf("NO\n");
		} else {
			sort(arr, arr + n);

			if (reqSum < *arr || reqSum > actSum) {
				//printf("required sum is not possible\n");
			} else {
				bool tab[n][reqSum + 1];

				init(arr, &tab[0][0], n, reqSum);
				fillTab(arr, n, reqSum, &tab[0][0]);
				//showTable(&tab[0][0], n, reqSum);
				//output(arr, n, reqSum, &tab[0][0]);
				if (tab[n - 1][reqSum]) {
					printf("YES\n");
				} else {
					printf("NO\n");
				}
			}
		}
		free(arr);
	}

	return 0;
}

int * input(int * n, int * reqSum, int &actSum) {
	//printf("Enter no of elements:\t");
	scanf("%d", n);

	int * arr = (int *) malloc((*n) * sizeof(int));
	actSum = 0;

	//printf("Enter elements of array one-b-one:-\n");
	for (int i = 0; i < *n; i++) {
		scanf("%d", &arr[i]);
		actSum += arr[i];
	}

	//printf("Enter the desired sum:\t");
	//scanf("%d", reqSum);
	* reqSum = actSum / 2;

	return arr;
}

void init(int * arr, bool * tab, int n, int reqSum) {
	// reqSum zero can be made by excluding all numbers, so it's true everywhere
	for (int i = 0; i < n; i++) {
		* (tab + i * (reqSum + 1) + 0) = true;
	}

	for (int j = 1; j <= reqSum; j++) {
		* (tab + j) = false;
	}

	* (tab + *arr) = true;
}

void fillTab(int * arr, int n, int reqSum, bool * tab) {
	bool cond_1, cond_2;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= reqSum; j++) {
			cond_1 = * (tab + (i - 1) * (reqSum + 1) + j);

			if (j < * (arr + i)) {
				* (tab + i * (reqSum + 1) + j) =  cond_1;
			} else {

				if (*(arr + i) <= j) {
					cond_2 = * (tab + (i - 1) * (reqSum + 1) + (j - * (arr + i)));
				} else {
					cond_2 = false;
				}

				* (tab + i * (reqSum + 1) + j) =  cond_1 || cond_2;
			}
		}
	}
}

void showTable(bool * tab, int n, int reqSum) {
	printf("\nThe constructed table is:-\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= reqSum; j++) {
			if (* (tab + i * (reqSum + 1) + j)) {
				printf("1 ");
			} else {
				printf("_ ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void output(int * arr, int n, int reqSum, bool * tab) {
	if (* (tab + (n - 1) * (reqSum + 1) + reqSum)) {
		printf("\nrequired sum is possible by following subset:-\n");

		int row, col, crrSum;

		row = n - 1;
		col = reqSum;
		crrSum = 0;

		while (row != 0 && col != 0) {
			if (* (tab + (row - 1) * (reqSum + 1) + col)) {
				row--;
			} else {
				printf("%d\t", * (arr + row));
				crrSum += * (arr + row);
				col -= * (arr + row);
				row--;
			}
		}

		if (crrSum < reqSum) {
			printf("%d", * arr);
		}
		printf("\n");
	} else {
		printf("required sum is not possible\n");
	}
}
