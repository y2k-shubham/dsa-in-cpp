// http://www.geeksforgeeks.org/efficiently-design-insert-delete-median-queries-set/
// Segment Tree (without lazy propagation), all elements in range 0 to 10^6

/*
1 1
4 1
7 1
8 1
9 1
-1 -1

0 3
2 5
3 2
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <cmath>
#include <cstring>

using namespace std;

#define MAXa 4
#define MAXt ((2 * MAXa) - 1)

#define lC(a) (2 * a + 1)
#define rC(a) (2 * a + 2)
#define par(a) ((a - 1) / 2)

int input(int [MAXa]);
void createTree(int [MAXa], int, int, int [MAXt], int);
void showArray(int [MAXt], int, const char *);
void showFreqArray(int [MAXa], int, const char *);
void updateArray(int [MAXa], int, int, int);
void updateTree(int [MAXt], int, int, int, int, int, int);
int queryMedian(int [MAXt], int, int, int, int);

int main() {
	int freqArr[MAXa], arrLen;
	int segTree[MAXt], treeLen;
	int eleCount;

	memset(freqArr, 0, sizeof(freqArr));
	memset(segTree, 0, sizeof(segTree));
	arrLen = MAXa;
	treeLen = MAXt;

	eleCount = input(freqArr);
	showFreqArray(freqArr, MAXa, "Original frequency array is");

	createTree(freqArr, 0, arrLen - 1, segTree, 0);
	showArray(segTree, treeLen, "Segment Tree array");

	int choice;
	int delta, uLo, uHi;
	int med1, med2;

	choice = -1;
	while (choice != 5) {
		cout << "\n1. Update";
		cout << "\n2. Find Median";
		cout << "\n3. Show Array";
		cout << "\n4. Show Tree";
		cout << "\n5. Exit";

		cout << "\nEnter choice:\t";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "\nEnter update range:\t";
				cin >> uLo >> uHi;

				cout << "Enter delta:\t";
				cin >> delta;

				eleCount += (uHi - uLo + 1) * delta;
				updateArray(freqArr, uLo, uHi, delta);
				updateTree(segTree, 0, arrLen - 1, 0, uLo, uHi, delta);

				break;

			case 2:
				if (eleCount % 2 == 1) {
					cout << "\nMedian is:\t" << queryMedian(segTree, 0, arrLen - 1, 0, eleCount / 2) << endl;
				} else {
					printf("\nMedians are:\t%d and %d\n", queryMedian(segTree, 0, arrLen - 1, 0, (eleCount / 2) - 1), queryMedian(segTree, 0, arrLen - 1, 0, eleCount / 2));
				}
				break;

			case 3:
				showFreqArray(freqArr, arrLen, "Frequency array");
				break;

			case 4:
				showArray(segTree, treeLen, "Segment tree array");
				break;

			case 5:
				continue;

			default:
				cout << "\nError! : Invalid Input" << endl;
		}
	}

	return 0;
}

int input(int freqArr[MAXa]) {
	int ele, freq;
	int ctr = 0;

	printf("Enter pairs (ele, freq) pairs:-\n");
	cin >> ele >> freq;

	while (ele != -1 && freq != -1) {
		ctr += freq;
		freqArr[ele] += freq;
		cin >> ele >> freq;
	}

	return ctr;
}

void showArray(int freqArr[MAXt], int len, const char * msg) {
	printf("\nThe %s is:-\n", msg);

	printf("Ind:\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Val:\t");
	for (int i = 0; i < len; i++) {
		printf("%d\t", freqArr[i]);
	}
	printf("\n");
}

void showFreqArray(int freqArr[MAXa], int len, const char * msg) {
	printf("\n%s is:-\n", msg);

	cout << "Ele:\t";
	for (int i = 0; i < len; i++) {
		if (freqArr[i] > 0) {
			printf("[%d]\t", i);
		}
	}
	cout << endl;

	cout << "Freq:\t";
	for (int i = 0; i < len; i++) {
		if (freqArr[i] > 0) {
			printf("%d\t", freqArr[i]);
		}
	}
	cout << endl;
}

void updateArray(int freqArr[MAXa], int lo, int hi, int delta) {
	for (int i = lo; i <= hi; i++) {
		freqArr[i] += delta;
	}
}

void createTree(int freqArr[MAXa], int lo, int hi, int segTree[MAXt], int pos) {
	if (lo == hi) {
		segTree[pos] += freqArr[lo];
	} else {
		int mid = (lo + hi) / 2;

		createTree(freqArr, lo, mid, segTree, lC(pos));
		createTree(freqArr, mid + 1, hi, segTree, rC(pos));

		segTree[pos] = segTree[lC(pos)] + segTree[rC(pos)];
	}
}

void updateTree(int segTree[MAXt], int lo, int hi, int pos, int uLo, int uHi, int delta) {
	if (hi < uLo || uHi < lo) {
		// do nothing
	} else {
		// some overlap is definitely there
		if (lo == hi) {
			// reached leaf node
			segTree[pos] += delta;
		} else {
			// whether there's partial or total overlap, recurse over left and right subtrees
			int mid = (lo + hi) / 2;

			updateTree(segTree, lo, mid, lC(pos), uLo, uHi, delta);
			updateTree(segTree, mid + 1, hi, rC(pos), uLo, uHi, delta);

			segTree[pos] = segTree[lC(pos)] + segTree[rC(pos)];
		}
	}
}

int queryMedian(int segTree[MAXt], int lo, int hi, int pos, int k) {
	if (lo == hi) {
//		printf("key = %d\tseg[%d] (%d .. %d) = %d\treturning lo = %d\n", k, pos, lo, hi, segTree[pos], lo);
		return lo;
	} else {
		int mid = (lo + hi) / 2;

//		printf("key = %d\tseg[%d] (%d .. %d) = %d\t", k, pos, lo, hi, segTree[pos]);
		if (segTree[lC(pos)] >= k) {
//			printf("traversing left subtree\n");
			return queryMedian(segTree, lo, mid, lC(pos), k);
		} else {
//			printf("traversing right subtree\n");
			return queryMedian(segTree, mid + 1, hi, rC(pos), k - segTree[lC(pos)]);
		}
	}
}

