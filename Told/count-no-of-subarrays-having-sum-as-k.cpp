// only works when all elements of array are >= 0 (not sure for -ve numbers, should work actually)

/*
7
8 1 3 7 4 2 9
11

12
8 1 0 3 7 4 0 0 2 0 9 0
11
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void findSubArrays(int [MAX], int, int, map <int, list <int> > &);
list <int> createList(int);
void showSubArrays(int [MAX], int, list <int>, int);
void showArray(int [MAX], int);

int main() {
	int arr[MAX], len;
	int k;
	map <int, list <int> > sumToInd;

	input(arr, len, k);

	showArray(arr, len);
	findSubArrays(arr, len, k, sumToInd);

	return 0;
}

void input(int arr[MAX], int &len, int &k) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}

	printf("Enter required sum k:\t");
	cin >> k;
}

void findSubArrays(int arr[MAX], int len, int k, map <int, list <int> > &sumToInd) {
	int crrSum = 0;
	sumToInd.insert(make_pair(0, createList(-1)));

	printf("\nSub arrays having sum of %d are:-\n", k);
	for (int i = 0; i < len; i++) {
		crrSum += arr[i];
		if (sumToInd.find(crrSum - k) != sumToInd.end()) {
			showSubArrays(arr, len, sumToInd[crrSum - k], i);
		}

		if (sumToInd.find(crrSum) == sumToInd.end()) {
			sumToInd.insert(make_pair(crrSum, createList(i)));
		} else {
			sumToInd[crrSum].push_back(i);
		}
	}
}

list <int> createList(int ele) {
	list <int> newList;
	newList.push_back(ele);
	return newList;
}

void showSubArrays(int arr[MAX], int len, list <int> startInd, int endInd) {
	for (list <int>::iterator it = startInd.begin(); it != startInd.end(); it++) {
		printf("arr[%d .. %d] = {%d .. %d}\n", (*it + 1), endInd, arr[(*it + 1)], arr[endInd]);
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
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

