/*
13
1 2 4 7 10 11 7 12 6 7 16 18 19
*/

#include <cstdio>
#include <stack>
#include <climits>
#include <cmath>

using namespace std;
#define MAX 100

// input
void input(int [MAX], int &);
// my method
void method_me(int [MAX], int);
void findNxtLsrOnRit(int [MAX], int, int [MAX]);
void findNxtGrtOnLft(int [MAX], int, int [MAX]);
// book method
void method_book(int [MAX], int);
void findMinOnRit(int [MAX], int, int [MAX]);
void findMaxOnLft(int [MAX], int, int [MAX]);

int main() {
	int arr[MAX];
	int n;

	input(arr, n);

	method_me(arr, n);
	method_book(arr, n);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter length of array:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

// my method
void method_me(int arr[MAX], int len) {
	int nxtLsrOnRit[MAX];
	int nxtGrtOnLft[MAX];
	int m, n;

	findNxtLsrOnRit(arr, len, nxtLsrOnRit);
	findNxtGrtOnLft(arr, len, nxtGrtOnLft);

	// increment m till we find elements for which next lesser element on right is INT_MIN (no lesser element on right)
	for (m = 0; m < len && nxtLsrOnRit[m] == INT_MIN; m++) {
	}

	// decrement n till we find elements for which next greater element on left if INT_MAX (no greater element on left)
	for (n = len - 1; n >= 0 && nxtGrtOnLft[n] == INT_MAX; n--) {
	}

	if (m < len && n >= 0) {
		printf("\nRange of numbers is:-\n");
		printf("arr[%d]\t-\tarr[%d]\n", m, n);
		printf("%d\t-\t%d\n", arr[m], arr[n]);
	} else {
		printf("\nArray is already sorted\n");
	}
}

void findNxtLsrOnRit(int arr[MAX], int n, int nxtLsrOnRit[MAX]) {
	stack <int> stk;

	for (int i = n - 1; i >= 0; i--) {
		while (!stk.empty() && stk.top() >= arr[i]) {
			stk.pop();
		}

		if (stk.empty()) {
			nxtLsrOnRit[i] = INT_MIN;
		} else {
			nxtLsrOnRit[i] = stk.top();
		}

		stk.push(arr[i]);
	}
}

void findNxtGrtOnLft(int arr[MAX], int n, int nxtGrtOnLft[MAX]) {
	stack <int> stk;

	for (int i = 0; i < n; i++) {
		while (!stk.empty() && stk.top() <= arr[i]) {
			stk.pop();
		}

		if (stk.empty()) {
			nxtGrtOnLft[i] = INT_MAX;
		} else {
			nxtGrtOnLft[i] = stk.top();
		}

		stk.push(arr[i]);
	}
}

// book method
void method_book(int arr[MAX], int len) {
	int minOnRit[MAX];
	int maxOnLft[MAX];
	int m, n;

	findMinOnRit(arr, len, minOnRit);
	findMaxOnLft(arr, len, maxOnLft);

	// increment m till we keep finding increasing sequence of numbers in beginning
	for (m = 1; m < len && arr[m - 1] <= arr[m]; m++) {
	}
	if (m == len) {
		printf("\nArray is already sorted\n");
		return;
	}

	// decrement n till we keep finding decreasing sequence of numbers in end
	for (n = len - 2; n >= 0 && arr[n] <= arr[n + 1]; n--) {
	}

	// decrement m till we find an element which is lesser than (or equal to) all elements to it's right
	for ( ; 0 <= m && arr[m] > minOnRit[m]; m--) {
	}
	m++;

	// increment n till we find an element which is greater than (or equal to) all elements to it's left
	for ( ; n < len && arr[n] < maxOnLft[n]; n++) {
	}
	n--;

	if (m < len && n >= 0) {
		printf("\nRange of numbers is:-\n");
		printf("arr[%d]\t-\tarr[%d]\n", m, n);
		printf("%d\t-\t%d\n", arr[m], arr[n]);
	} else {
		printf("\nArray is already sorted\n");
	}
}

void findMinOnRit(int arr[MAX], int len, int minOnRit[MAX]) {
	int minEle = INT_MAX;
	minOnRit[len - 1] = INT_MAX;

	for (int i = len - 2; 0 <= i; i--) {
		minOnRit[i] = min(minEle, arr[i + 1]);
		minEle = min(minEle, arr[i]);
	}
}

void findMaxOnLft(int arr[MAX], int len, int maxOnLft[MAX]) {
	int maxEle = INT_MIN;
	maxOnLft[0] = INT_MIN;

	for (int i = 1; i < len; i++) {
		maxOnLft[i] = max(maxEle, arr[i - 1]);
		maxEle = max(maxEle, arr[i]);
	}
}
