// TusharRoy
// https://www.youtube.com/watch?v=ZBHKZF5w4YU
// to deal with minimum no in range queries

#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>
#include <cstring>

#define MAX 100
#define minVal(a, b) ((a < b) ? a : b)

void input(int [MAX], int &);
void createTree(int [MAX], int, int, int [MAX], int);
void showTree(int [MAX], int);
int query(int, int, int [MAX], int, int, int);
void takeQueries(int [MAX], int);

int main() {
	int arr[MAX];
	int arrLen;
	int tree[MAX];
	int treeLen;

	input(arr, arrLen);

	treeLen = (int) (pow(2, ceil(log(arrLen) / log(2))) * 2 - 1);
	memset(tree, 0xFF, sizeof(tree));	// ideally it's wrong as it won't initialize to infinity

	createTree(arr, 0, arrLen - 1, tree, 0);
	showTree(tree, treeLen);

	takeQueries(tree, arrLen);

	return 0;
}

void input(int arr[MAX], int &arrLen) {
	printf("Enter length of array:\t");
	scanf("%d", &arrLen);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < arrLen; i++) {
		scanf("%d", &arr[i]);
	}
}

void createTree(int arr[MAX], int lo, int hi, int tree[MAX], int pos) {
	if (lo == hi) {
		tree[pos] = arr[lo];
	} else {
		int mid = (lo + hi) / 2;

		createTree(arr, lo, mid, tree, 2 * pos + 1);
		createTree(arr, mid + 1, hi, tree, 2 * pos + 2);

		tree[pos] = minVal(tree[2 * pos + 1], tree[2 * pos + 2]);
	}
}

void showTree(int tree[MAX], int treeLen) {
	printf("\nThe segment tree array is:-\n");
	for (int i = 0; i < treeLen; i++) {
		printf("%d\t", tree[i]);
	}
	printf("\n");
}

void takeQueries(int tree[MAX], int arrLen) {
	int lo, hi;

	printf("\nEnter query (lo, hi) = ");
	scanf("%d%d", &lo, &hi);

	while (lo != -1 && hi != -1) {
		printf("min of arr[%d .. %d] = %d\n", lo, hi, query(lo, hi, tree, 0, arrLen - 1, 0));

		printf("\nEnter query (lo, hi) = ");
		scanf("%d%d", &lo, &hi);
	}
}

int query(int qLo, int qHi, int tree[MAX], int lo, int hi, int pos) {
	if (qLo <= lo && qHi >= hi) {
		return tree[pos];
	} else if (qLo > hi || qHi < lo) {
		return INT_MAX;
	} else {
		int mid = (lo + hi) / 2;

		return minVal(query(qLo, qHi, tree, lo, mid, 2 * pos + 1), query(qLo, qHi, tree, mid + 1, hi, 2 * pos + 2));
	}
}
