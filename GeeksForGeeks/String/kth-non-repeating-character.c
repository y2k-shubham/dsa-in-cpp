// http://www.geeksforgeeks.org/kth-non-repeating-character/
// http://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/
// done using single pass of input string

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 256
#define LEN 10000

void findRepeatChars(char *, bool [MAX], int [MAX]);
int cmpfunc(const void *, const void *);
void showArray(int [MAX], int, const char *);

int main() {
	bool hasOccured[MAX] = {[0 ... (MAX - 1)] = false};
	int index[MAX] = {[0 ... (MAX - 1)] = INT_MAX};
	char * str;
	int k;

	str = calloc(LEN, sizeof(char));

	printf("Enter string:\t");
	fgets(str, LEN, stdin);
	str[strlen(str) - 1] = '\0';	// remove newline character

	printf("Enter k:\t");
	scanf("%d", &k);

	findRepeatChars(str, hasOccured, index);

	//showArray(index, MAX, "before sorting");
	qsort(index, MAX, sizeof(int), cmpfunc);
	//showArray(index, MAX, "after sorting");

	printf("\nkth non-repeating char is:\t%c\n", str[index[k - 2]]);

	return 0;
}

void findRepeatChars(char * str, bool hasOccured[MAX], int index[MAX]) {
	int i;
	int len = strlen(str);

	for (i = 0; i < len; i++) {
		if (hasOccured[str[i]] == false) {
//			printf("\nread str[%d] = %c\thasOccured[%c] = false\tindex[%c] = %d", i, str[i], str[i], str[i], i);
			hasOccured[str[i]] = true;
			index[str[i]] = i;
		} else {
//			printf("\nread str[%d] = %c\thasOccured[%c] = true\tindex[%c] = INT_MAX", i, str[i], str[i], str[i]);
			index[str[i]] = INT_MAX;
		}
	}
//	printf("\n");
}

int cmpfunc (const void * a, const void * b) {
	//to sort in descending order, swap a and b
   return ( *(int*)a - *(int*)b );
}

void showArray(int a[MAX], int size, const char * msg) {
	int i;

	printf("\nindex array %s is:-\n", msg);
	for (i = 0; i < size; i++) {
		if (a[i] == INT_MAX) {
			printf("INT_MAX ");
		} else {
			printf("%d ", a[i]);
		}
	}
	printf("\n");
}

