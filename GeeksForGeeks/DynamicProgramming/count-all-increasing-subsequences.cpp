// http://www.geeksforgeeks.org/count-all-increasing-subsequences/

/*
4
1 2 3 4

4
4 3 6 5

5
3 2 4 5 4
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArr(int *, int, const char *);
void findCount(int [MAX], int, int [10]);

int main() {
	int arr[MAX], n;
	int count[10];

	input(arr, n);
	showArr(arr, n, "original array");

	memset(count, 0, sizeof(count));
	findCount(arr, n, count);
	showArr(count, 10, "count array");

	int sum = 0;
	for (int i = 0; i < 10; i++) {
		sum += count[i];
	}
	printf("\nNo of increasing subsequences are %d\n", sum);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of elements:\t");
	cin >> n;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
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

void findCount(int arr[MAX], int len, int count[10]) {
	for (int i = 0; i < len; i++) {
		int sum = 0;
		for (int j = arr[i] - 1; j >= 0; j--) {
			sum += count[j];
		}

		count[arr[i]] += sum + 1;

//		char * msg = (char *) malloc(100);
//		sprintf(msg, "count[] array after reading arr[%d] = %d", i, arr[i]);
//		showArr(count, 10, msg);
	}
}

