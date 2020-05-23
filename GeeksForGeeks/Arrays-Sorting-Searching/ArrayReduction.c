#include <stdio.h>

void input(int [], int);
void findDelta(int [], int [], int);
void findSize(int [], int, int);

int main() {
	int len;
	int k;

	printf("\nEnter length of array:\t");
	scanf("%d", &len);

	int arr[len];
	int delta[len];

	input(arr, len);
	findDelta(arr, delta, len);

	printf("Enter value of k:\t");
	scanf("%d", &k);

	findSize(delta, len, k);

	return 0;
}

void input(int arr[], int len) {
	int i;

    printf("Enter the array:\t");
	for (i = 0; i < len; i++) {
		scanf("%d", &arr[i]);
	}
}

void findDelta(int arr[], int delta[], int len) {
	int i;

	delta[0] = -1;
	for (i = 1; i < len; i++) {
		delta[i] = arr[i] - arr[i - 1];
	}
}

void findSize(int delta[], int len, int k) {
	int i;
	int reducedLen;

	reducedLen = len;
	for (i = 1; i < len - 1;) {
		if (delta[i++] == k) {
			if (delta[i++] == k) {
				reducedLen -= 3;
			}
		}
	}

	printf("The reduced length will be %d\n", reducedLen);
}
