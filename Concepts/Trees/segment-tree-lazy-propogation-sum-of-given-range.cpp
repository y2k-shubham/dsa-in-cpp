// http://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/
// TusharRoy

/*
6
1 3 5 7 9 11
*/

#include <cstdio>
#include <climits>
#include <cstring>
#include <cmath>

#define MAX 100
#define lC(a) (2 * a + 1)
#define rC(a) (2 * a + 2)

void input(int [MAX], int &);
void buildTree(int [MAX], int, int, int [MAX], int);
void showArray(int [MAX], int, const char *);
int sumQuery(int [MAX], int [MAX], int, int, int, int, int);
void updateTree(int [MAX], int [MAX], int, int, int, int, int, int);
void updateArray(int [MAX], int, int, int);

int main() {
	int arr[MAX], tree[MAX], lazyTree[MAX];
	int arrLen, treeLen;

	input(arr, arrLen);
	treeLen = (int) (2 * powf(2, ceil(log2(arrLen))) - 1);

	memset(tree, 0, sizeof(int) * treeLen);
	memset(lazyTree, 0, sizeof(int) * treeLen);
	buildTree(arr, 0, arrLen - 1, tree, 0);

	int choice = -1;
	while (choice != 6) {
		printf("\n1. Query");
		printf("\n2. Update");
		printf("\n3. Show Tree");
		printf("\n4. Show Lazy Tree");
		printf("\n5. Show Array");
		printf("\n6. Exit");

		printf("\nEnter your choice:\t");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				int qLo, qHi;
				printf("\nEnter query range:\t");
				scanf("%d%d", &qLo, &qHi);

				if (0 <= qLo && qHi <= (arrLen - 1)) {
					printf("Sum in range arr[%d] - arr[%d] is %d\n", qLo, qHi, sumQuery(tree, lazyTree, 0, arrLen - 1, 0, qLo, qHi));
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
				updateTree(tree, lazyTree, 0, arrLen - 1, 0, uLo, uHi, delta);

				break;

			case 3:
				showArray(tree, treeLen, "tree");
				break;

			case 4:
				showArray(lazyTree, treeLen, "lazy tree");
				break;

			case 5:
				showArray(arr, arrLen, "array");
				break;

			case 6:
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

void buildTree(int arr[MAX], int lo, int hi, int tree[MAX], int pos) {
	if (lo == hi) {
		tree[pos] = arr[lo];
	} else {
		int mid = (lo + hi) / 2;

		buildTree(arr, lo, mid, tree, lC(pos));
		buildTree(arr, mid + 1, hi, tree, rC(pos));

		tree[pos] = tree[lC(pos)] + tree[rC(pos)];
	}
}

void updateTree(int tree[MAX], int lazyTree[MAX], int lo, int hi, int pos, int uLo, int uHi, int delta) {
	if (hi < uLo || uHi < lo) {
		// no overlap, but make pending updates
		tree[pos] += lazyTree[pos] * (hi - lo + 1);
		if (hi != lo) {
			// we update child only if it is not a leaf node
			lazyTree[lC(pos)] += lazyTree[pos];		// here we increment lC & rC by sum
			lazyTree[rC(pos)] += lazyTree[pos];		// of pending updates and delta
		}
		lazyTree[pos] = 0;
	} else if (uLo <= lo && hi <= uHi) {
		// total overlap
		tree[pos] += (lazyTree[pos] + delta) * (hi - lo + 1);
		if (hi != lo) {
			// we update child only if it is not a leaf node
			lazyTree[lC(pos)] += lazyTree[pos] + delta;		// here we increment lC & rC by sum
			lazyTree[rC(pos)] += lazyTree[pos] + delta;		// of pending updates and delta
		}
		lazyTree[pos] = 0;
	} else {
		// partial overlap
		tree[pos] += lazyTree[pos] * (hi - lo + 1) + delta;
		if (hi != lo) {
			lazyTree[lC(pos)] += lazyTree[pos];			// here we increment lC & rC by pending
			lazyTree[rC(pos)] += lazyTree[pos];			// updates only
		}
		lazyTree[pos] = 0;

		if (hi != lo) {
			int mid = (lo + hi) / 2;
			updateTree(tree, lazyTree, lo, mid, lC(pos), uLo, uHi, delta);
			updateTree(tree, lazyTree, mid + 1, hi, rC(pos), uLo, uHi, delta);
			tree[pos] = (tree[lC(pos)] /*+ lazyTree[lC(pos)] * (mid - lo + 1)*/) + (tree[rC(pos)] /*+ lazyTree[rC(pos) * (hi - mid)]*/);
		}
	}
}

int sumQuery(int tree[MAX], int lazyTree[MAX], int lo, int hi, int pos, int qLo, int qHi) {
	if (hi < qLo || qHi < lo) {
		// no overlap
		return 0;
	} else if (qLo <= lo && hi <= qHi) {
		// total overlap
		tree[pos] += lazyTree[pos];
		lazyTree[lC(pos)] += lazyTree[pos];
		lazyTree[rC(pos)] += lazyTree[pos];
		lazyTree[pos] = 0;

		return tree[pos];
	} else {
		// partial overlap
		tree[pos] += lazyTree[pos];
		lazyTree[lC(pos)] += lazyTree[pos];
		lazyTree[rC(pos)] += lazyTree[pos];
		lazyTree[pos] = 0;

		int mid = (lo + hi) / 2;
		tree[pos] = sumQuery(tree, lazyTree, lo, mid, lC(pos), qLo, qHi) + sumQuery(tree, lazyTree, mid + 1, hi, rC(pos), qLo, qHi);

		return tree[pos];
	}
}

void updateArray(int arr[MAX], int lo, int hi, int delta) {
	for (int i = lo; i <= hi; i++) {
		arr[i] += delta;
	}
}

