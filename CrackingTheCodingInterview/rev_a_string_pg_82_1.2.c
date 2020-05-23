#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define MAX_LEN 100

void reverse(char *);
void swapChars(char *, int, int);

// problem 1.2 given on page 82 of Cracking the Coding Interview 5th Edition PDF

int main() {
	char * str;

	str = (char *) malloc(sizeof(char) * MAX_LEN);

	printf("Enter a string:\t");
	fgets(str, MAX_LEN - 1, stdin);
	str[strlen(str) - 1] = '\0';

	printf("\nThe original string is:\t%s\n", str);
	reverse(str);
	printf("The reversed string is:\t%s\n", str);

	return 0;
}

void reverse(char * str) {
	int i;
	int len;

	len = strlen(str);
	for (i = 0; i < len / 2; i++) {
		swapChars(str, i, len - i - 1);
	}
}

void swapChars(char * str, int ind_1, int ind_2) {
	char temp;

	temp = str[ind_1];
	str[ind_1] = str[ind_2];
	str[ind_2] = temp;
}
