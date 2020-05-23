/*
Input:
17
2 4 3 3 1 5 6 6 4 3 4 0 0 2 3 5 4

Output:
Max-Area = 18
*/

#include <cstdio>
#include <iostream>
#include <stack>
#include <climits>

using namespace std;

#define MAX 100
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

int input(int [MAX], int &);
void calcLeftLesser(int [MAX], int, int [MAX], int [MAX]);
void calcRightLesser(int [MAX], int, int [MAX], int [MAX]);
void showArray(int [MAX], int , const char *);
void findMaxRect(int [MAX], int, int [MAX], int [MAX], int &, int &, int &);
void output(int [MAX], int, int, int, int, int);

int main() {
	int n;
	int arr[MAX];
	int maxHeight;
	int lLftE[MAX], lLftI[MAX];
	int lRitE[MAX], lRitI[MAX];
	int recIndLft, recIndRit, recHeight;

	maxHeight = input(arr, n);

	calcLeftLesser(arr, n, lLftE, lLftI);
	calcRightLesser(arr, n, lRitE, lRitI);

//	showArray(lLftE, n, "lesser element value - left");
//	showArray(lLftI, n, "lesser element index - left");
//
//	showArray(lRitE, n, "lesser element value - right");
//	showArray(lRitI, n, "lesser element index - right");

	findMaxRect(arr, n, lLftI, lRitI, recIndLft, recIndRit, recHeight);

	output(arr, n, maxHeight, recIndLft, recIndRit, recHeight);

	return 0;
}

int input(int arr[MAX], int &n) {
	int maxHeight = INT_MIN;

	printf("Enter no of towers:\t");
	scanf("%d", &n);

	printf("Enter heights of towers:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		maxHeight = max(maxHeight, arr[i]);
	}

	return maxHeight;
}

void calcLeftLesser(int arr[MAX], int n, int lLftE[MAX], int lLftI[MAX]) {
	stack <int> stkE;
	stack <int> stkI;

	for (int i = 0; i < n; i++) {
		int ele = arr[i];

		while (!stkE.empty() && stkE.top() >= ele) {
			stkE.pop();
			stkI.pop();
		}

		if (stkE.empty()) {
			lLftE[i] = -1;
			lLftI[i] = -1;
		} else {
			lLftE[i] = stkE.top();
			lLftI[i] = stkI.top();
		}

		stkE.push(ele);
		stkI.push(i);
	}
}

void calcRightLesser(int arr[MAX], int n, int lRitE[MAX], int lRitI[MAX]) {
	stack <int> stkE;
	stack <int> stkI;

	for (int i = n - 1; i >= 0; i--) {
		int ele = arr[i];

		while (!stkE.empty() && stkE.top() >= ele) {
			stkE.pop();
			stkI.pop();
		}

		if (stkE.empty()) {
			lRitE[i] = -1;
			lRitI[i] = n;
		} else {
			lRitE[i] = stkE.top();
			lRitI[i] = stkI.top();
		}

		stkE.push(ele);
		stkI.push(i);
	}
}

void showArray(int arr[MAX], int n, const char * msg) {
	printf("\nThe %s array is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void findMaxRect(int arr[MAX], int n, int lLftI[MAX], int lRitI[MAX], int &recIndLft, int &recIndRit, int &recHeight) {
	int maxAreaTillNow = 0;

	for (int i = 0; i < n; i++) {
		int crrArea = arr[i] * ((lRitI[i] - 1) - (lLftI[i] + 1) + 1);

		if (crrArea > maxAreaTillNow) {
			maxAreaTillNow = crrArea;
			recIndLft = lLftI[i] + 1;
			recIndRit = lRitI[i] - 1;
			recHeight = arr[i];
		}
	}
}

void output(int arr[MAX], int n, int maxHeight, int recIndLft, int recIndRit, int recHeight) {
	printf("\nArea of max rect is %d sq units", (recHeight * (recIndRit - recIndLft + 1)));

	printf("\nThe histogram visualization is:-\n");
	for (int h = maxHeight; h > 0; h--) {
		printf("h=%d\t", h);
		for (int i = 0; i < n; i++) {
			if ((recIndLft <= i && recIndRit >= i) && (h <= recHeight)) {
				printf("0 ");
			} else if (h == arr[i]) {
				printf("* ");
			} else if (arr[i] >= h) {
				printf("* ");
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}
