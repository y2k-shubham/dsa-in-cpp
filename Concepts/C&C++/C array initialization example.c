#include <stdio.h>
#define MAX 100

void showArray(int [MAX], int, const char *);

int main() {
	int a[MAX] = {[0 ... (MAX - 1)] = 5};
	int b[MAX] = {5};

	showArray(a, MAX, "a");
	showArray(b, MAX, "b");

	return 0;
}

void showArray(int arr[MAX], int size, const char * msg) {
	int i;

	printf("\nArray %s is:-\n", msg);
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}
