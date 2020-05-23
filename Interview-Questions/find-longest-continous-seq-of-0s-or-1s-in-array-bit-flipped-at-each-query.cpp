// Modification of question asked in Delhivery

/*
16
0 1 1 1 0 1 0 1 0 0 0 0 1 1 1 0

11
0 1 1 0 1 0 0 0 1 1 0
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <cstring>
#include <cmath>

using namespace std;

struct stats {
	int lSeqEndInd, rSeqEndInd;
	bool lSeq0, rSeq0;
	pair <int, int> mSeqInd;
	bool mSeq0;
};

#define MAX 100
#define avg(a, b) ((a + b) / 2)
#define left(pos) (2 * pos + 1)
#define right(pos) (2 * pos + 2)
#define par(pos) ((pos - 1) / 2)

void input(int [MAX], int&, int&);
void showArr(int [MAX], int);
void showTree(int [MAX], int, int, stats [MAX], int);
void showStat(stats cStat, int, int, int);
stats createTree(int [MAX], int, int, stats [MAX], int);
stats updateTree(int [MAX], int, int, stats [MAX], int, int, int, int);
void doQueries(int [MAX], int, int, stats [MAX], int);

int main() {
	int arr[MAX], lenArr;
	int q;
	stats segTree[MAX];
	int lenTree;

	input(arr, lenArr, q);

//	memset(arr, 0, lenArr * sizeof(int));
	lenTree = 4 * ((int) powf(2, ceil(log(lenArr) / log(2)))) - 1;

	createTree(arr, 0, lenArr - 1, segTree, 0);
//	cout << "\nTht seg-tree is:-\n";
//	showTree(arr, 0, lenArr - 1, segTree, 0);

	doQueries(arr, lenArr, q, segTree, lenTree);

	return 0;
}

void input(int arr[MAX], int& lenArr, int& q) {
	printf("Enter length of array:\t");
	cin >> lenArr;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < lenArr; i++) {
		cin >> arr[i];
	}

	showArr(arr, lenArr);

	printf("\nEnter number of queries:\t");
	cin >> q;
}

void showArr(int arr[MAX], int lenArr) {
	printf("\na[] array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < lenArr; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < lenArr; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTree(int arr[MAX], int lo, int hi, stats segTree[MAX], int pos) {
	if (lo == hi) {
		printf("\narr[%d] = %d\n", lo, arr[lo]);
	} else {
		showTree(arr, lo, avg(lo, hi), segTree, left(pos));
		showTree(arr, avg(lo, hi) + 1, hi, segTree, right(pos));

		showStat(segTree[pos], lo, hi, pos);
//		printf("\narr[%d..%d]\n", lo, hi);
//		printf("lSeq = arr[%d..%d]\tlSeqType = %d\n", lo, segTree[pos].lSeqEndInd, (!segTree[pos].lSeq0));
//		printf("rSeq = arr[%d..%d]\trSeqType = %d\n", segTree[pos].rSeqEndInd, hi, (!segTree[pos].rSeq0));
//		printf("mSeq = arr[%d..%d]\tmSeqType = %d\n", segTree[pos].mSeqInd.first, segTree[pos].mSeqInd.second, (!segTree[pos].mSeq0));
	}
}

void showStat(stats cStat, int lo, int hi, int pos) {
	printf("\narr[%d..%d] at segTree[%d]\n", lo, hi, pos);
	printf("lSeq = arr[%d..%d]\tlSeqType = %d\n", lo, cStat.lSeqEndInd, (!cStat.lSeq0));
	printf("rSeq = arr[%d..%d]\trSeqType = %d\n", cStat.rSeqEndInd, hi, (!cStat.rSeq0));
	printf("mSeq = arr[%d..%d]\tmSeqType = %d\n", cStat.mSeqInd.first, cStat.mSeqInd.second, (!cStat.mSeq0));
}

stats createTree(int arr[MAX], int lo, int hi, stats segTree[MAX], int pos) {
	stats cStat;

	if (lo == hi) {
		cStat.mSeqInd.first = lo;
		cStat.mSeqInd.second = lo;
		cStat.mSeq0 = (arr[lo] == 0) ? true : false;

		cStat.lSeqEndInd = lo;
		cStat.lSeq0 = (arr[lo] == 0) ? true : false;

		cStat.rSeqEndInd = lo;
		cStat.rSeq0 = (arr[lo] == 0) ? true : false;
	} else if (lo < hi) {
		int mid = avg(lo, hi);
		bool lEndIndDone = false;
		bool rEndIndDone = false;

//		if (lo == mid) {
//			// when current pos stores results of two leaf nodes
//			if (arr[lo] == arr[hi]) {
//				// when both leaf nodes are same
//				cStat.mSeqInd.first = lo;
//				cStat.mSeqInd.second = hi;
//				cStat.mSeq0 = (arr[0] == 0) ? true : false;
//
//				cStat.lSeqEndInd = hi;
//				cStat.lSeq0 = (arr[lo] == 0) ? true : false;
//
//				cStat.rSeqEndInd = lo;
//				cStat.rSeq0 = (arr[lo] == 0) ? true : false;
//			} else {
//				// when both leaf nodes are different
//				cStat.mSeqInd.first = lo;
//				cStat.mSeqInd.second = lo;
//				cStat.mSeq0 = (arr[0] == 0) ? true : false;
//
//				cStat.lSeqEndInd = lo;
//				cStat.lSeq0 = (arr[lo] == 0) ? true : false;
//
//				cStat.rSeqEndInd = hi;
//				cStat.rSeq0 = (arr[hi] == 0) ? true : false;
//			}
//		} else {
		stats lStat = createTree(arr, lo, mid, segTree, left(pos));
		stats rStat = createTree(arr, mid + 1, hi, segTree, right(pos));

		cStat.mSeqInd = (lStat.mSeqInd.second - lStat.mSeqInd.first > rStat.mSeqInd.second - rStat.mSeqInd.first) ? lStat.mSeqInd : rStat.mSeqInd;
		cStat.mSeq0 = (lStat.mSeqInd.second - lStat.mSeqInd.first > rStat.mSeqInd.second - rStat.mSeqInd.first) ? lStat.mSeq0 : rStat.mSeq0;
		if (lStat.rSeq0 == rStat.lSeq0 && cStat.mSeqInd.second - cStat.mSeqInd.first < rStat.lSeqEndInd - lStat.rSeqEndInd) {
			cStat.mSeqInd.first = lStat.rSeqEndInd;
			cStat.mSeqInd.second = rStat.lSeqEndInd;
			cStat.mSeq0 = lStat.rSeq0;

			if (lStat.lSeq0 == rStat.lSeq0 && lStat.lSeqEndInd + 1 == mid + 1) {
				cStat.lSeqEndInd = rStat.lSeqEndInd;
				cStat.lSeq0 = lStat.lSeq0;
				lEndIndDone = true;
			} else if (rStat.rSeq0 == lStat.rSeq0 && rStat.rSeqEndInd - 1 == mid) {
				cStat.rSeqEndInd = lStat.rSeqEndInd;
				cStat.rSeq0 = rStat.rSeq0;
				rEndIndDone = true;
			}
		}

		if (lStat.lSeq0 == rStat.rSeq0 && lStat.lSeqEndInd + 1 == rStat.rSeqEndInd) {
			// l & r form a single continous sequence
			cStat.lSeqEndInd = (lEndIndDone == false) ? hi : cStat.lSeqEndInd;
			cStat.rSeqEndInd = (rEndIndDone == false) ? lo : cStat.rSeqEndInd;
		} else {
			cStat.lSeqEndInd = (lEndIndDone == false) ? lStat.lSeqEndInd : cStat.lSeqEndInd;
			cStat.rSeqEndInd = (rEndIndDone == false) ? rStat.rSeqEndInd : cStat.rSeqEndInd;
		}

		cStat.lSeq0 = (lEndIndDone == false) ? lStat.lSeq0 : cStat.lSeq0;
		cStat.rSeq0 = (rEndIndDone == false) ? rStat.rSeq0 : cStat.rSeq0;
//		}
	}

//	showStat(cStat, lo, hi, pos);
	segTree[pos] = cStat;
	return cStat;
}

stats updateTree(int arr[MAX], int lo, int hi, stats segTree[MAX], int pos, int updIndL, int updIndR, int updBit) {
	if ((updIndR < lo) || (updIndL > hi)) {
//		printf("printf at arr[%d..%d], upd-range (%d, %d) returned out-of-bound\n", lo, hi, updIndL, updIndR);
		return segTree[pos];
	}

	stats cStat;
	if (lo == hi) {
		cStat.mSeqInd.first = lo;
		cStat.mSeqInd.second = lo;
		cStat.mSeq0 = (updBit == 0) ? true : false;

		cStat.lSeqEndInd = lo;
		cStat.lSeq0 = (updBit == 0) ? true : false;

		cStat.rSeqEndInd = lo;
		cStat.rSeq0 = (updBit == 0) ? true : false;
	} else if (lo < hi) {
		int mid = avg(lo, hi);
		bool lEndIndDone = false;
		bool rEndIndDone = false;
		stats lStat = segTree[left(pos)];
		stats rStat = segTree[right(pos)];

		lStat = (updIndL <= mid) ? updateTree(arr, lo, mid, segTree, left(pos), updIndL, updIndR, updBit) : lStat;
		rStat = (updIndR >= mid + 1) ? updateTree(arr, mid + 1, hi, segTree, right(pos), updIndL, updIndR, updBit) : rStat;

//		printf("\nat arr[%d..%d], after updation", lo, hi);
//		showStat(lStat, lo, mid);
//		showStat(rStat, mid + 1, hi);

		cStat.mSeqInd = (lStat.mSeqInd.second - lStat.mSeqInd.first > rStat.mSeqInd.second - rStat.mSeqInd.first) ? lStat.mSeqInd : rStat.mSeqInd;
		cStat.mSeq0 = (lStat.mSeqInd.second - lStat.mSeqInd.first > rStat.mSeqInd.second - rStat.mSeqInd.first) ? lStat.mSeq0 : rStat.mSeq0;
		if (lStat.rSeq0 == rStat.lSeq0 && cStat.mSeqInd.second - cStat.mSeqInd.first < rStat.lSeqEndInd - lStat.rSeqEndInd) {
			cStat.mSeqInd.first = lStat.rSeqEndInd;
			cStat.mSeqInd.second = rStat.lSeqEndInd;
			cStat.mSeq0 = lStat.rSeq0;

			if (lStat.lSeq0 == rStat.lSeq0 && lStat.lSeqEndInd + 1 == mid + 1) {
				cStat.lSeqEndInd = rStat.lSeqEndInd;
				cStat.lSeq0 = lStat.lSeq0;
				lEndIndDone = true;
			} else if (rStat.rSeq0 == lStat.rSeq0 && rStat.rSeqEndInd - 1 == mid) {
				cStat.rSeqEndInd = lStat.rSeqEndInd;
				cStat.rSeq0 = rStat.rSeq0;
				rEndIndDone = true;
			}
		}

		if (lStat.lSeq0 == rStat.rSeq0 && lStat.lSeqEndInd + 1 == rStat.rSeqEndInd) {
			// l & r form a single continous sequence
			cStat.lSeqEndInd = (lEndIndDone == false) ? hi : cStat.lSeqEndInd;
			cStat.rSeqEndInd = (rEndIndDone == false) ? lo : cStat.rSeqEndInd;
		} else {
			cStat.lSeqEndInd = (lEndIndDone == false) ? lStat.lSeqEndInd : cStat.lSeqEndInd;
			cStat.rSeqEndInd = (rEndIndDone == false) ? rStat.rSeqEndInd : cStat.rSeqEndInd;
		}

		cStat.lSeq0 = (lEndIndDone == false) ? lStat.lSeq0 : cStat.lSeq0;
		cStat.rSeq0 = (rEndIndDone == false) ? rStat.rSeq0 : cStat.rSeq0;
	}

//	showStat(cStat, lo, hi, pos);
	segTree[pos] = cStat;
	return cStat;
}

void doQueries(int arr[MAX], int lenArr, int q, stats segTree[MAX], int lenTree) {
	int updIndL, updIndR, updBit;

	printf("\nEnter update queries:-\n");
	for (int i = 1; i <= q; i++) {
		printf("\n [startInd, endInd], updBit:\t");
		cin >> updIndL >> updIndR >> updBit;

		updateTree(arr, 0, lenArr - 1, segTree, 0, updIndL, updIndR, updBit);

		printf("Longest continous seq of bits is:\tarr[%d..%d] = {%d}\n", segTree[0].mSeqInd.first, segTree[0].mSeqInd.second, (!segTree[0].mSeq0));
	}
}

