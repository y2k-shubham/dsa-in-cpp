#include <stdio.h>

void charDemo(char, char);
void intDemo(int, int);
void longDemo(long, long);

int main() {
	charDemo(1, 32);
	intDemo(1, 32);
	longDemo(1, 32);

	return 0;
}

void charDemo(char lo, char hi) {
	char c;

	printf("\nchar demo:-\n");
	for (c = lo; c <= hi; c++) {
		printf("[%c\t%o\t%d\t%x]\n", c, c, c, c);
	}
	printf("\n");
}

void intDemo(int lo, int hi) {
	int i;

	printf("\nint demo:-\n");
	for (i = lo; i <= hi; i++) {
		printf("[%c\t%o\t%d\t%x]\n", i, i, i, i);
	}
	printf("\n");
}

void longDemo(long lo, long hi) {
	long i;

	printf("\nlong demo:-\n");
	for (i = lo; i <= hi; i++) {
		printf("[%c\t%o\t%d\t%x]\n", i, i, i, i);
	}
	printf("\n");
}
