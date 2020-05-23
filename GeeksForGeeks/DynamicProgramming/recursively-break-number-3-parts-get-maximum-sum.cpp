// http://www.geeksforgeeks.org/recursively-break-number-3-parts-get-maximum-sum/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
#define MAX 100

void showArr(int *, int, const char *);
void calc(int [MAX], int);

int main() {
	int sum[MAX];
	int n;

	cout << "Enter integer n:\t";
	cin >> n;

	calc(sum, n);
	showArr(sum, n + 1, "sum[] array");

	cout << "\nMaximum possible sum by recursively breaking n in 3 parts is " << sum[n] << endl;

	return 0;
}

void calc(int sum[MAX], int n) {
	sum[0] = 0;
	sum[1] = 1;

	for (int i = 2; i <= n; i++) {
		sum[i] = max(i, sum[i / 2] + sum[i / 3] + sum[i / 4]);
	}
}

void showArr(int * arr, int len, const char * msg) {
	printf("\n%s is:-\n", msg);

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


