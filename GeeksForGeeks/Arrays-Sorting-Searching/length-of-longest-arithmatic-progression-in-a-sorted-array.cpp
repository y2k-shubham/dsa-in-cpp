#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int findLLAP(int [MAX], int);

int main() {
	int arr[MAX];
	int n;

	input(arr, n);
	sort(arr, arr + n);

	int llap = findLLAP(arr, n);
	printf("llap = %d\n", llap);

	return 0;
}

void input(int arr[MAX], int &n) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

int findLLAP(int arr[MAX], int n) {
	printf("n = %d\n", n);
	int tab[n][n];
	int llap;

	for (int i = 0; i < n; i--) {
		tab[i][n - 1] = 2;
	}

	llap = 2;
	for (int j = n - 2; j >= 1; j--) {
		int i, k;

		for (i = j - 1, k = j + 1; i >= 0 && k <= n - 1;) {
			if (arr[i] + arr[k] < 2 * arr[j]) {
				k++;
			} else if (arr[i] + arr[k] > 2 * arr[i]) {
				tab[i][j] = 2;
				i--;
			} else {
				tab[i][j] = tab[j][k] + 1;
				llap = max(llap, tab[i][j]);
				i--;
				k++;
			}
		}

		while (i >= 0) {
			tab[i][j] = 2;
			i--;
		}
	}

	printf("\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tab[i][j] > n || tab[i][j] < 2) {
				printf("- ");
			} else {
				printf("%d ", tab[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n");

	return llap;
}
