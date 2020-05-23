// TusharRoy

/*
Array Input
11
3 2 -1 6 5 4 -3 3 7 2 3

Queries
0 5
0 9
0 6
5 8
9 10
2 6
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void createTree(int [MAX], int, int [MAX], int);
int getParent(int);
int getNext(int);
void updateArr(int [MAX], int, int);
void updateTree(int [MAX], int, int, int);
int query(int [MAX], int, int);
int getRangeSum(int [MAX], int);

int main() {
	int arr[MAX], aLen;
	int tree[MAX], tLen;

	input(arr, aLen);
	showArray(arr, aLen, "arr[]");

	tLen = aLen + 1;
	memset(tree, 0, tLen * sizeof(int));

	createTree(arr, aLen, tree, tLen);
	showArray(tree, tLen, "tree[]");

	int qLo, qHi;
	int ind, delta;
	int choice = -1;

	while (choice != 4) {
		cout << endl;
		printf("1. Query\n");
		printf("2. Update\n");
		printf("3. Show\n");
		printf("4. Exit\n");

		printf("\nEnter choice:\t");
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Enter query range:\t";
				cin >> qLo >> qHi;

				printf("Sum of arr[%d .. %d] = %d\n", qLo, qHi, query(tree, qLo, qHi));

				break;

			case 2:
				cout << "Enter update (ind, delta):\t";
				cin >> ind >> delta;

				updateArr(arr, ind, delta);
				updateTree(tree, tLen, ind, delta);

				break;

			case 3:
				showArray(arr, aLen, "arr[]");
				showArray(tree, tLen, "tree[]");
				break;

			case 4:
				continue;

			default:
				cout << "Invalid Input\n";
		}
	}

	return 0;
}

void input(int arr[MAX], int &aLen) {
	cout << "Enter length of array:\t";
	cin >> aLen;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < aLen; i++) {
		cin >> arr[i];
	}
}

void showArray(int a[MAX], int len, const char * name) {
	printf("\n%s array is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

void createTree(int arr[MAX], int aLen, int tree[MAX], int tLen) {
	for (int i = 0; i < aLen; i++) {
		int val = arr[i];

		for (int j = i + 1; j < tLen; j = getNext(j)) {
			tree[j] += val;
		}
	}
}

int getParent(int ind) {
	return ind & (ind - 1);
}

int getNext(int ind) {
	int ind_2s_comp = -ind;
	return ind + (ind & ind_2s_comp);
}

int query(int tree[MAX], int qLo, int qHi) {
	if (qLo == 0) {
		return getRangeSum(tree, qHi);
	} else {
		int smallSum = getRangeSum(tree, qLo - 1);
		int bigSum = getRangeSum(tree, qHi);

		return bigSum - smallSum;
	}
}

int getRangeSum(int tree[MAX], int rHi) {
	int sum = 0;
	++rHi;

	while (rHi > 0) {
		sum += tree[rHi];
		rHi = getParent(rHi);
	}

	return sum;
}

void updateArr(int arr[MAX], int uInd, int uDelta) {
	arr[uInd] += uDelta;
}

void updateTree(int tree[MAX], int tLen, int uInd, int uDelta) {
	for (int i = uInd + 1; i < tLen; i = getNext(i)) {
		tree[i] += uDelta;
	}
}

