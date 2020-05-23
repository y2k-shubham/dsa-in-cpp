#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showPerms(int [MAX], int, int);
void showArr(int [MAX], int);
void swapEle(int [MAX], int, int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showPerms(arr, len, 0);

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showPerms(int arr[MAX], int len, int ind) {
	if (ind == len - 1) {
		showArr(arr, len);
	} else {
		showPerms(arr, len, ind + 1);

		for (int i = ind + 1; i < len; i++) {
			if (arr[ind] != arr[i]) {
				swapEle(arr, ind, i);
				showPerms(arr, len, ind + 1);
				swapEle(arr, ind, i);
			}
		}
	}
}

void showArr(int arr[MAX], int len) {
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void swapEle(int arr[MAX], int i1, int i2) {
	int tmp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = tmp;
}

