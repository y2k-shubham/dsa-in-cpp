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
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void buildMaxHeap(int [MAX], int);
void maxHeapify(int [MAX], int, int);
void swap(int [MAX], int, int);
void heapSort(int [MAX], int);
int extractMax(int [MAX], int &);
void increaseKey(int [MAX], int, int, int);
void decreaseKey(int [MAX], int, int, int);
void insert(int [MAX], int &, int);

int main() {
	int size;
	int heap[MAX];

	input(heap, size);
	showArray(heap, size, "after input");

	buildMaxHeap(heap, size);
	showArray(heap, size, "after building max heap");

	int choice = -1;
	while (choice != 8) {
		printf("\n1. Show-Max");
		printf("\n2. Remove-Max");
		printf("\n3. Insert");
		printf("\n4. Increase-Key");
		printf("\n5. Decrease-Key");
		printf("\n6. Heap-Sort");
		printf("\n7. Show-Heap");
		printf("\n8. Exit");

		printf("\n\nEnter your choice:\t");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("Max element is:\t%d\n", heap[0]);
				break;

			case 2:
				printf("Max element removed is:\t%d\n", extractMax(heap, size));
				break;

			case 3:
				int key;

				printf("\nEnter key:\t");
				scanf("%d", &key);

				insert(heap, size, key);
				break;

			case 4:
			case 5:
				int pos, newKey;

				printf("\nEnter (pos, newKey):\t");
				scanf("%d%d", &pos, &newKey);

				if (choice == 4) {
					increaseKey(heap, size, pos, newKey);
				} else {
					decreaseKey(heap, size, pos, newKey);
				}

				break;

			case 6:
				heapSort(heap, size);
				break;

			case 7:
				showArray(heap, size, "heap[]");

			case 8:
				continue;

			default:
				printf("\nError! : invalid input [%d]\n", choice);
		}
	}

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
		printf("[%d]\t", i);
	}
	printf("\n");
	for (int i = 0; i < size; i++) {
		printf("%d\t", heap[i]);
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

void increaseKey(int heap[MAX], int size, int crrInd, int newKey) {
	if (heap[crrInd] >= newKey) {
		printf("\nError! : old key [%d] >= newKey [%d]\n", heap[crrInd], newKey);
	} else if (crrInd >= size) {
		printf("\nError! : invalid position [%d]\n", crrInd);
	} else {
		heap[crrInd] = newKey;

		int parInd = (crrInd - 1) / 2;
		while (crrInd >= 0 && heap[parInd] < heap[crrInd]) {
			swap(heap, parInd, crrInd);
			crrInd = parInd;
			parInd = (crrInd - 1) / 2;
		}
	}
}

void decreaseKey(int heap[MAX], int size, int crrInd, int newKey) {
	if (heap[crrInd] <= newKey) {
		printf("\nError! : old key [%d] <= newKey [%d]\n", heap[crrInd], newKey);
	} else if (crrInd >= size) {
		printf("\nError! : invalid position [%d]\n", crrInd);
	} else {
		heap[crrInd] = newKey;
		maxHeapify(heap, size, crrInd);
	}
}

void insert(int heap[MAX], int &size, int key) {
	if (size == MAX) {
		printf("\nError! : heap over flow\n");
	} else {
		heap[size++] = INT_MIN;
		increaseKey(heap, size, size - 1, key);
	}
}
