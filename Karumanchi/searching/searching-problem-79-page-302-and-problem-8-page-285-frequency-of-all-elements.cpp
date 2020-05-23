// Karumanchi,

// Searching, problem 79, page 302
// Given an array of length n having elements in range 9 - n-1, find frequency of all elements

//Searching, Problem 8, page 285
// Given an array of length n having elements in range 0 - n-1, find element having highest frequency

/*
7
2 3 1 1 3 4 1
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void showFreq(int [MAX], int);
void modify(int [MAX], int);
void find(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);
	showArray(arr, len, "original");

	modify(arr, len);
	showArray(arr, len, "modified");

	showFreq(arr, len);

	find(arr, len);

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:\t");
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

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

void showFreq(int arr[MAX], int len) {
	printf("\nFrequencies of elements are:-\n");

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	cout << "Freq:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i] / len);
	}
	cout << endl;
}

void modify(int arr[MAX], int len) {
	for (int i = 0; i < len; i++) {
		arr[arr[i] % len] += len;
	}
}

void find(int arr[MAX], int len) {
	int maxFreq, maxEle;

	maxFreq = -1;
	for (int i = 0; i < len; i++) {
		if (arr[i] / len > maxFreq) {
			maxFreq = arr[i] / len;
			maxEle = i;
		}
	}

	printf("\nElement %d has highest frequency of %d\n", maxEle, maxFreq);
}

