// not an actual question, just implemented minimum range query for segment tree
//  http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/

/*
6
1 3 5 7 9 11
*/

#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>

#define MAX 100
#define min(a, b) ((a < b) ? a : b)
#define lChild(a) (2 * a + 1)
#define rChild(a) (2 * a + 2)
#define parent(a) ((a - 1) / 2)

void input(int [MAX], int &);
void createTree(int [MAX], int, int, int [MAX], int);
void showArray(int [MAX], int, const char *);
int minQuery(int [MAX], int, int, int, int, int);
void updateTree(int [MAX], int, int, int, int, int, int);
void updateArray(int [MAX], int, int, int);

int main() {
	int arr[MAX];
	int arrLen;
	int tree[MAX];
	int treeLen;

	input(arr, arrLen);

	treeLen = (int) (2 * powf(2, ceil(log2(arrLen))) - 1);
	memset(tree, 0, treeLen * sizeof(int));

	createTree(arr, 0, arrLen - 1, tree, 0);

	int choice = -1;
	while (choice != 5) {
		printf("\n1. Query");
		printf("\n2. Update");
		printf("\n3. Show Tree");
		printf("\n4. Show Array");
		printf("\n5. Exit");

		printf("\nEnter your choice:\t");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				int qLo, qHi;
				printf("\nEnter query range:\t");
				scanf("%d%d", &qLo, &qHi);

				if (0 <= qLo && qHi <= (arrLen - 1)) {
					printf("Min in range arr[%d] - arr[%d] is %d\n", qLo, qHi, minQuery(tree, 0, arrLen - 1, 0, qLo, qHi));
				} else {
					printf("Error! : Invalid Range\n");
				}

				break;

			case 2:
				int uLo, uHi, delta;

				printf("\nEnter update range:\t");
				scanf("%d%d", &uLo, &uHi);

				if (!(0 <= uLo && uHi <= (arrLen - 1))) {
					printf("Error! : Invalid Range\n");
					break;
				}

				printf("Enter delta:\t\t");
				scanf("%d", &delta);

				updateArray(arr, uLo, uHi, delta);
				updateTree(tree, 0, arrLen - 1, 0, uLo, uHi, delta);

				break;

			case 3:
				showArray(tree, treeLen, "tree");
				break;

			case 4:
				showArray(arr, arrLen, "array");
				break;

			case 5:
				continue;

			default:
				printf("\nError! : Invalid Input\n");
		}
	}

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

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\nThe %s is:-\n", msg);

	printf("Ind:\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Val:\t");
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void updateArray(int arr[MAX], int lo, int hi, int delta) {
	for (int i = lo; i <= hi; i++) {
		arr[i] += delta;
	}
}

void createTree(int arr[MAX], int lo, int hi, int tree[MAX], int pos) {
	if (lo == hi) {
		// copy single array element to it's correct position in segment tree
		tree[pos] = arr[lo];
	} else {
		int mid = (lo + hi) / 2;

		createTree(arr, lo, mid, tree, lChild(pos));
		createTree(arr, mid + 1, hi, tree, rChild(pos));

		tree[pos] = min(tree[lChild(pos)], tree[rChild(pos)]);
	}
}

int minQuery(int tree[MAX], int lo, int hi, int pos, int qLo, int qHi) {
	if (hi < qLo || qHi < lo) {
		// no overlap
		return INT_MAX;
	} else if (qLo <= lo && hi <= qHi) {
		// total overlap
		return tree[pos];
	} else {
		// partial overlap
		int mid = (lo + hi) / 2;
		return min(minQuery(tree, lo, mid, lChild(pos), qLo, qHi), minQuery(tree, mid + 1, hi, rChild(pos), qLo, qHi));
	}
}

void updateTree(int tree[MAX], int lo, int hi, int pos, int uLo, int uHi, int delta) {
	if (uHi < lo || hi < uLo) {
		// no overlap, do nothing
	} else if (lo == hi) {
		// just one element, update made to actual array element in tree
		tree[pos] += delta;
	} else {
		int mid = (lo + hi) / 2;

		updateTree(tree, lo, mid, lChild(pos), uLo, uHi, delta);
		updateTree(tree, mid + 1, hi, rChild(pos), uLo, uHi, delta);

		tree[pos] = min(tree[lChild(pos)], tree[rChild(pos)]);
	}
}
