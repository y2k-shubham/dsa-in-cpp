/*
Input:
10
4 1 3 2 16 9 10 14 8 7
After Build-Heap, Output:
16 14 10 8 7 9 3 2 4 1

10
1 2 3 4 7 8 9 10 14 16

10
16 4 10 14 7 9 3 2 8 1
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void buildMaxHeap(int [MAX], int);
void maxHeapify(int [MAX], int, int);
void swap(int [MAX], int, int);
void heapSort(int [MAX], int);
int extractMax(int [MAX], int &);

int main() {
	int size;
	int heap[MAX];

	input(heap, size);
	showArray(heap, size, "after input");

	heapSort(heap, size);

	buildMaxHeap(heap, size);
	showArray(heap, size, "after building max heap");

	return 0;
}

void input(int heap[MAX], int &size) {
	printf("Enter size of array:\t");
	scanf("%d", &size);

	printf("Enter elements of array one-by-one:-\n");
	for (int i = 0; i < size; i++) {
		scanf("%d", &heap[i]);
	}
}

void showArray(int heap[MAX], int size, const char * msg) {
	printf("\nThe array %s is:-\n", msg);
	for (int i = 0; i < size; i++) {
		printf("%d ", heap[i]);
	}
	printf("\n");
}

void buildMaxHeap(int heap[MAX], int size) {
	for (int i = size / 2; i >= 0; i--) {
//		printf("\nbefore calling maxHeapify on heap[%d] = %d", i, heap[i]);
//		showArray(heap, size, "heap[]");

		maxHeapify(heap, size, i);
	}
}

void maxHeapify(int heap[MAX], int size, int crrInd) {
	int lCInd = crrInd * 2 + 1;
	int rCInd = crrInd * 2 + 2;

	// find index of max among crrNode, it's left child and right child
	int maxInd = crrInd;
	if (rCInd < size && heap[rCInd] > heap[crrInd]) {
		maxInd = rCInd;
	}
	if (lCInd < size && heap[lCInd] > heap[maxInd]) {
		maxInd = lCInd;
	}

	if (maxInd != crrInd) {
		// if current node is not greater than it's children, we need to swap
		swap(heap, crrInd, maxInd);
		maxHeapify(heap, size, maxInd);
	}
}

void swap(int heap[MAX], int ind_1, int ind_2) {
	int tmp = heap[ind_1];
	heap[ind_1] = heap[ind_2];
	heap[ind_2] = tmp;
}

void heapSort(int heap[MAX], int size) {
	int heapClone[MAX];
	int sizeClone;

	memcpy(heapClone, heap, size * sizeof(int));
	sizeClone = size;
	buildMaxHeap(heapClone, size);

	printf("\nOutput of heap-sort is:-\n");
	while (sizeClone >= 1) {
		printf("%d ", extractMax(heapClone, sizeClone));
	}
	printf("\n");
}

int extractMax(int heap[MAX], int &size) {
	int max = heap[0];

	swap(heap, 0, size - 1);
	size--;
	maxHeapify(heap, size, 0);

	return max;
}
