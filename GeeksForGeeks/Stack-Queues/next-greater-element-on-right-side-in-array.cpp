// 1st approach: same as one proposed in http://www.geeksforgeeks.org/find-the-nearest-smaller-numbers-on-left-side-in-an-array/
// and implemented in file find-the-nearest-smaller-numbers-on-left-side-in-an-array.cpp

// 2nd approach, as proposed in http://www.geeksforgeeks.org/next-greater-element/
#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void approach_1(int [MAX], int, int [MAX]);
void approach_2(int [MAX], int, int [MAX]);
void output(int [MAX], int [MAX], int);

int main() {
	int n;
	int arr[MAX];
	int nxtGr8[MAX];

	input(arr, n);

	approach_1(arr, n, nxtGr8);
	output(arr, nxtGr8, n);

	approach_2(arr, n, nxtGr8);
	output(arr, nxtGr8, n);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of elements:\t");
	scanf("%d", &n);

	printf("Enter elements of array one-by-one:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void approach_1(int arr[MAX], int n, int nxtGr8[MAX]) {
	stack <int> stk;

	for (int i = n - 1; i >= 0; i--) {
		int ele = arr[i];

		while (!stk.empty() && stk.top() <= ele) {
			stk.pop();
		}

		if (stk.empty()) {
			nxtGr8[i] = -1;
		} else {
			nxtGr8[i] = stk.top();
		}

		stk.push(ele);
	}
}

void output(int arr[MAX], int nxtGr8[MAX], int n) {
	printf("\nThe next greater elements on right are:-\n");

	printf("ind:\t");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("ele:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");

	printf("nxtGr8:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", nxtGr8[i]);
	}
	printf("\n");
}

void approach_2(int arr[MAX], int n, int nxtGr8[MAX]) {
	stack <int> stk;

	// here we don't push actual elements to stack, rather their indexes
	stk.push(0);
	for (int i = 1; i < n; i++) {
		int ele = arr[i];

		while (!stk.empty() && arr[stk.top()] < ele) {
			nxtGr8[stk.top()] = ele;
			stk.pop();
		}

		stk.push(i);
	}

	while (!stk.empty()) {
		nxtGr8[stk.top()] = -1;
		stk.pop();
	}
}
