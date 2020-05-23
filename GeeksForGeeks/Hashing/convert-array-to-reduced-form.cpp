// http://www.geeksforgeeks.org/convert-array-reduced-form/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=608

#include <cstdio>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int&);
void createMap(int [MAX], int, map <int, int>&);
void changeArray(int [MAX], int, map <int, int>);
void output(int [MAX], int);

int main() {
	int n;
	int arr[MAX];
	int arrCpy[MAX];
	map <int, int> rankMap;

	input(arr, n);

	memcpy(arrCpy, arr, n * sizeof(int));
	sort(arrCpy, arrCpy + n);
	createMap(arrCpy, n, rankMap);

	changeArray(arr, n, rankMap);
	output(arr, n);

	return 0;
}

void input(int arr[MAX], int& n) {
	printf("Enter length of array:\t");
	scanf("%d", &n);

	printf("Enter the elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void createMap(int arr[MAX], int n, map <int, int>& rankMap) {
	for (int i = 0; i < n; i++) {
		rankMap[arr[i]] = i;
	}
}

void changeArray(int arr[MAX], int n, map <int, int> rankMap) {
	for (int i = 0; i < n; i++) {
		arr[i] = rankMap[arr[i]];
	}
}

void output(int arr[MAX], int n) {
	printf("\nThe reduced array is:-\n");
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}
