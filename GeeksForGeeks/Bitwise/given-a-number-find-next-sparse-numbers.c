// Question URL : http://www.geeksforgeeks.org/given-a-number-find-next-sparse-number/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=391
/*
    Problem: Given a positive integer n, find the smallest sparse number >= n
             Sparse Numbers are those that do not have consecutive 1's in
             their binary representation. If given number is already sparse, print it
*/

#include <stdio.h>
#include <limits.h>
#include <math.h>

#define INT_LEN 32

int promote_1(int);
int promote_2(int);
void showPos(int, int);
int getBit(int, int);
int isBitSet(int, int);

int main() {
	int T;
	int n;

	scanf("%d", &T);

	while (T-- > 0) {
		//printf("Enter a positive integer:\t");
		scanf("%d", &n);

		//printf("\nThe sparse no >= %d is (method 1):\t%d\n", n, promote_1(n));
		//printf("\nThe sparse no >= %d is (method 2):\t%d\n", n, promote_2(n));
		printf("%d\n", promote_2(n));
	}

	return 0;
}

int promote_1(int n) {
	int prev;
	int curr;
	int i;

	prev = 0;
	for (i = 0; i < INT_LEN; i++) {
		//showPos(n, i);
		curr = getBit(n, i);

		if (curr & prev) {
			while (isBitSet(n, i)) {
				i++;
			}
			i--;

			if (!isBitSet(n, i + 2)) {
				// if first 1 of continous sequence of 1's can be shifted by one place to it's left, do it
				n = n | (1 << (i + 1));
				n = n & (INT_MAX - (((int) pow(2, (i + 1))) - 1));
			}

			// otherwise try to shift the leading 1 of another continous sequence of 1's that lie before the previous sequence
			prev = 1;
			i++;
			continue;
		}
		prev = curr;
	}

	return n;
}

int promote_2(int n) {
	int crr, prev, i;

	prev = 0;
	for (i = INT_LEN - 1; i >= 0; i--) {
		crr = getBit(n, i);

		if (prev & crr) {
			break;
		} else {
			prev = crr;
		}
	}

	if (i < 0) {
		// do nothing: it's already a sparse number, just return it
	} else {
		i++;
		while (i <= INT_LEN && ((isBitSet(n, i) && isBitSet(n, i + 2)) || (!isBitSet(n, i)))) {
			i++;
		}

		n = n | (1 << (i + 1));
		n = n & (INT_MAX - (((int) pow(2, (i + 1))) - 1));
	}

	return n;
}

void showPos(int num, int pos) {
	int i;

	for (i = INT_LEN - 1; i >= 0; i--) {
		printf("%d", getBit(num, i));
	}

	printf("\n");
	for (i = INT_LEN - 1; i > pos; i--) {
		printf(" ");
	}
	printf("^\n\n");
}

int getBit(int num, int pos) {
	if (isBitSet(num, pos)) {
		return 1;
	} else {
		return 0;
	}
}

int isBitSet(int num, int pos) {
	return (num & (1 << pos));
}
