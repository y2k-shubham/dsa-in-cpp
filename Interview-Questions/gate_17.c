#include <stdio.h>

int * assignValue(int *x, int val) {
	*x = val;
	return x;
}

void main() {
	int *x = malloc(sizeof(int));
	if (NULL == x) return;

	x = assignValue(x, 0);
	if (x) {
		x = (int *) malloc(sizeof(int));
		if (NULL == x) return;
		x = assignValue(x, 10);
	}

	printf("%d\n", *x);
	free(x);

}
