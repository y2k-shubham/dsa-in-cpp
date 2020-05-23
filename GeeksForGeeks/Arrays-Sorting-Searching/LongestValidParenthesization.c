#include <stdio.h>
#include <string.h>

#define MAX 100
#define max(a, b) ((a > b) ? a : b)

int main() {
	char arr[MAX];
	int arrLen;
	int open;
	int close;
	int crrLen;
	int maxLen;
	int crrStrtInd;
	int maxStrtInd;
	int i;
	int j;

	printf("\nEnter paranthesization string:\t");
	scanf("%s", arr);

	arrLen = strlen(arr);
	maxLen = 0;
	crrLen = 0;
	open = 0;
	close = 0;

	for (i = 0; i < arrLen; i++) {
		if (arr[i] == '(') {
			if (open == 0 && crrLen == 0) {
				crrStrtInd = i;
			}
			open++;
		} else {
			close++;

			if (close <= open) {
				crrLen += 2;
				if (crrLen > maxLen) {
					maxLen = crrLen;
					maxStrtInd = crrStrtInd;
				}
			} else {
				open = 0;
				close = 0;
				crrLen = 0;
			}
		}
	}

	printf("The longest valid sequence is:\t");
	for (i = 0, j = 0; j < maxLen - 1; i++) {
		if (j > 0) {
			j++;
		}

		if (i != maxStrtInd) {
			printf(" ");
		} else {
			printf("^");
			j = 1;
		}
	}
	printf("^\n                              \t");
	for (i = 0; i < maxStrtInd; i++) {
        printf(" ");
	}
	for (i = maxStrtInd, j = 1; j <= maxLen; i++, j++) {
		printf("%c", arr[i]);
	}
	printf("\nLength of longest sequence is:\t%d\n", maxLen);

	return 0;
}
