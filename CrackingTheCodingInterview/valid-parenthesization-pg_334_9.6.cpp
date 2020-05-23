#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void findParenzation(char [MAX], int, int, int, int);
void showArr(char [MAX], int);

int main() {
	int n;
	char arr[MAX];

	printf("Enter n:\t");
	scanf("%d", &n);

	findParenzation(arr, 0, n, n, n);

	return 0;
}

void findParenzation(char arr[MAX], int ind, int n, int lRem, int rRem) {
	if (lRem == 0 && rRem == 0) {
		showArr(arr, 2 * n);
	} else {
		if (lRem > 0) {
			arr[ind] = '(';
			findParenzation(arr, ind + 1, n, lRem - 1, rRem);
		}
		if (rRem > lRem) {
			arr[ind] = ')';
			findParenzation(arr, ind + 1, n, lRem, rRem - 1);
		}
	}
}

void showArr(char arr[MAX], int lim) {
	for (int i = 0; i < lim; i++) {
		putchar(arr[i]);
	}
	printf("\n");
}
