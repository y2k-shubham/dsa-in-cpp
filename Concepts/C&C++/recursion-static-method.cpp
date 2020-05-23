#include <stdio.h>

static int fact_1(int x) {
	if (x < 2) {
		return 1;
	} else {
		return (x * fact_1(x - 1));
	}
}

//int fact_2(static int x) {
//	if (x < 2) {
//		return 1;
//	} else {
//		return (x * fact_2(x - 1));
//	}
//}

int main() {
	printf("fact(%d) = %d\n", 0, fact_1(0));
	printf("fact(%d) = %d\n", 1, fact_1(1));
	printf("fact(%d) = %d\n", 2, fact_1(2));
	printf("fact(%d) = %d\n", 5, fact_1(5));

	return 0;
}

