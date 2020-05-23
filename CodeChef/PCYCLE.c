#include <stdio.h>

void input(int [], int [], int);
void count(int [], int);
void output(int [], int);

int main() {
	int N;

	scanf("%d", &N);
	int arr_1[N + 1];
	int arr_2[N + 1];

	input(arr_1, arr_2, N);
	count(arr_2, N);
	output(arr_1, N);

	return 0;
}

void input(int arr_1[], int arr_2[], int N) {
	int i;

	for (i = 1; i <= N; i++) {
		scanf("%d", &arr_1[i]);
		arr_2[i] = arr_1[i];

		//printf("%d\t", arr_1[i]);
	}
}

void count(int arr[], int N) {
	int i;
	int j;
	int k;
	int startElement;
	int noOfCycles;

    noOfCycles = 0;
	for (i = 1; i <= N; i++) {
        //printf("\n\n====\nStarting at position i = %d, arr[%d] = %d\n", i, i, arr[i]);

		// find first unused element
		for (j = i; (j <= N) && (arr[j] == -999); j++) {
		}

		if (j <= N) {
            //printf("Unused position found at j = %d, arr[%d] = %d\n\n", j, j, arr[j]);
            //printf("arr[%d] = %d marked as used\n", j, arr[j]);

            noOfCycles++;
            k = arr[j];
            arr[j] = -999;
			startElement = j;

			for (j = k; j != startElement; j = arr[j], arr[k] = -999) {
                k = j;
                //printf("arr[%d] = %d marked as used\n", j, arr[j]);
			}
			//printf("%d\n", startElement);
		} else {
            break;
		}
	}

	printf("%d\n", noOfCycles);
}

void output(int arr[], int N) {
	int i;
	int j;
	int k;
	int startElement;

	for (i = 1; i <= N; i++) {
        //printf("\n\n====\nStarting at position i = %d, arr[%d] = %d\n", i, i, arr[i]);

		// find first unused element
		for (j = i; (j <= N) && (arr[j] == -999); j++) {
		}

		if (j <= N) {
            //printf("Unused position found at j = %d, arr[%d] = %d\n\n", j, j, arr[j]);
            //printf("arr[%d] = %d marked as used\n", j, arr[j]);

            k = arr[j];
            arr[j] = -999;
			startElement = j;

            printf("%d", startElement);
			for (j = k; j != startElement; j = arr[j], arr[k] = -999) {
                k = j;
                printf(" %d", j);
                //printf("arr[%d] = %d marked as used\n", j, arr[j]);
			}
			printf(" %d\n", startElement);
			//printf("%d\n", startElement);
		} else {
            break;
		}
	}

	//printf("%d\n", noOfCycles);
}
