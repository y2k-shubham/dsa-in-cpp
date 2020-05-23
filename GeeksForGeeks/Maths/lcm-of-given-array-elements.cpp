// http://www.geeksforgeeks.org/lcm-of-given-array-elements/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=953

/*
4
1 2 8 3

5
2 7 3 9 4
*/

#include <bits/stdc++.h>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
void findLCM(int [MAX], int &);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len);

	findLCM(arr, len);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

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

void findLCM(int arr[MAX], int &len) {
	int lcm = arr[0];

	for (int i = 1; i < len; i++) {
		lcm = (lcm * arr[i]) / __gcd(lcm, arr[i]);
	}

	printf("\nLCM of array elements is %d\n", lcm);
}

