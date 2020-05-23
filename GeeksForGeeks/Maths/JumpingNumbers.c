#include <stdio.h>
#include <math.h>

int findNoOfDigits(int);
void showJumpingNumbers1(int, int, int);
void showJumpingNumbers2(int, int, int, int);

int main() {
	int x;
	int noOfDigits;
	int i;
	int j;

	printf("Enter x:\t");
	scanf("%d", &x);

	noOfDigits = findNoOfDigits(x);

	for (i = 1; i < noOfDigits; i++) {
		printf("\nJumping Numbers of %d digits:-\n", i);
		for (j = 1; j < 10; j++) {
			showJumpingNumbers1(j, i, 1);
		}
	}

	printf("\nJumping Numbers of %d digits:-\n", noOfDigits);
	for (j = 1; j < 10; j++) {
		showJumpingNumbers2(j, i, 1, x);
	}
	printf("\n");

	return 0;
}

int findNoOfDigits(int num) {
	if (num / 10 == 0) {
		return 1;
	} else {
		return 1 + findNoOfDigits(num / 10);
	}
}

void showJumpingNumbers1(int crrNum, int maxDigitCount, int crrDigitCount) {
	if (crrDigitCount < maxDigitCount) {
		int lastDigit;
		lastDigit = crrNum % 10;

		if (lastDigit - 1 >= 0) {
			showJumpingNumbers1(crrNum * 10 + lastDigit - 1, maxDigitCount, crrDigitCount + 1);
		}
		if (lastDigit + 1 <= 9) {
			showJumpingNumbers1(crrNum * 10 + lastDigit + 1, maxDigitCount, crrDigitCount + 1);
		}
	} else {
		printf("%d\t", crrNum);
	}
}

void showJumpingNumbers2(int crrNum, int maxDigitCount, int crrDigitCount, int limit) {
	if (crrNum <= limit / pow(10, maxDigitCount - crrDigitCount)) {
		if (crrDigitCount < maxDigitCount) {
			int lastDigit;
			lastDigit = crrNum % 10;

			if (lastDigit - 1 >= 0) {
				showJumpingNumbers2(crrNum * 10 + lastDigit - 1, maxDigitCount, crrDigitCount + 1, limit);
			}
			if (lastDigit + 1 <= 9) {
				showJumpingNumbers2(crrNum * 10 + lastDigit + 1, maxDigitCount, crrDigitCount + 1, limit);
			}
		} else {
			printf("%d\t", crrNum);
		}
	}
}
