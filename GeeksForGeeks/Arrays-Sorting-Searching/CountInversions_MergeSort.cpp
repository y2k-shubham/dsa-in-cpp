#include <stdio.h>
#include <climits>

void input(int *, int);
void output(int *, int);
void mergeSort(int *, int, int, int *);
void mergeArr(int *, int, int, int, int, int *);

int main() {
	int n;
	int inversions;

	printf("Enter no of elements:\t");
	scanf("%d", &n);

	int arr[n];
	input(&arr[0], n);

	inversions = 0;
	mergeSort(&arr[0], 0, n - 1, &inversions);

	printf("\nThe no of inversions are:\t%d\n", inversions);
	output(&arr[0], n);

	return 0;
}

void input(int * arr, int n) {
	int i;

	printf("Enter elements of array:-\n");
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void output(int * arr, int n) {
	int i;

	printf("The sorted array is:-\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void mergeSort(int * arr, int lo, int hi, int * inversions) {
	if (lo < hi) {
		int mid;

		mid = (lo + hi) / 2;
		mergeSort(arr, lo, mid, inversions);
		mergeSort(arr, mid + 1, hi, inversions);
		mergeArr(arr, lo, mid, mid + 1, hi, inversions);
	}
}

void mergeArr(int * arr, int lo_1, int hi_1, int lo_2, int hi_2, int * inversions) {
	int i;
	int j;
	int k;
	int len_1;
	int len_2;

	len_1 = (hi_1 - lo_1 + 1);
	len_2 = (hi_2 - lo_2 + 1);

	int tempArr_1[len_1 + 1];
	int tempArr_2[len_2 + 1];

	tempArr_1[len_1] = INT_MAX;
	tempArr_2[len_2] = INT_MAX;

	// copy elements to 1st array
	for (i = 0, j = lo_1; j <= hi_1; i++, j++) {
		tempArr_1[i] = arr[j];
	}

	// copy elements to 2nd array
	for (i = 0, j = lo_2; j <= hi_2; i++, j++) {
		tempArr_2[i] = arr[j];
	}

    // normal sentinel approach: inversions can't be counted this way
    /*
	for (i = lo_1, j = 0, k = 0; i <= hi_2; i++) {
        printf("comparing %d & %d\t", tempArr_1[j], tempArr_2[k]);
		if (tempArr_1[j] <= tempArr_2[k]) {
			arr[i] = tempArr_1[j++];
            printf("no inversion\n");
		} else {
			arr[i] = tempArr_2[k++];
			(* inversions) += (hi_1 - j);
			printf("inversion\n");
		}
	}
	*/

	for (i = lo_1, j = 0, k = 0; j < len_1 && k < len_2; i++) {
        //printf("comparing %d & %d\t", tempArr_1[j], tempArr_2[k]);
        if (tempArr_1[j] <= tempArr_2[k]) {
			arr[i] = tempArr_1[j++];
            //printf("no inversion\n");
		} else {
			arr[i] = tempArr_2[k++];
			(* inversions) += len_1 - j;
			//printf("inversion\n");
		}
	}

	while (j < len_1) {
        arr[i++] = tempArr_1[j++];
	}

	while (k < len_2) {
        arr[i++] = tempArr_2[k++];
	}
}
