// http://www.geeksforgeeks.org/find-smallest-value-represented-sum-subset-given-array/
// Difficult Question

/*
4
1 1 3 7

6
1 3 6 10 11 15

4
1 1 1 1

6
1 2 5 10 20 40

6
1 2 3 4 5 6
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
int minNonGeneratingNum(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len);

	printf("\nMin non-generating number is %d\n", minNonGeneratingNum(arr, len));

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nArray is :-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i =  0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

int minNonGeneratingNum(int arr[MAX], int len) {
	int sum = 1;

	for (int i = 0; i < len; i++) {
		if (sum < arr[i]) {
			break;
		} else {
			sum += arr[i];
		}
	}

	return sum;
}

