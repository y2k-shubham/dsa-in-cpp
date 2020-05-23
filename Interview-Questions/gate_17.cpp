
#include <stdio.h>
#include <cstdlib>

int * assignValue(int *x, int val) {
	*x = val;
	return x;
}

int main() {
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

	return 0;
}

