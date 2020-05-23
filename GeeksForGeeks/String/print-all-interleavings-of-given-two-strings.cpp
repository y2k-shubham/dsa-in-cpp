// http://www.geeksforgeeks.org/print-all-interleavings-of-given-two-strings/
#include <cstdio>
#include <iostream>
#include <cstring>

#define MAX 100
using namespace std;

void showInterLeave(char *, char *, char *, int);

int main() {
	char str1[MAX], str2[MAX], str3[MAX];
	int len1, len2, len3;

	printf("Enter 1st string:\t");
	fgets(str1, MAX - 1, stdin);
	str1[strlen(str1) - 1] = '\0';
	len1 = strlen(str1);

	printf("Enter 2nd string:\t");
	fgets(str2, MAX - 1, stdin);
	str2[strlen(str2) - 1] = '\0';
	len2 = strlen(str2);

	len3 = len1 + len2;
	str3[len1 + len2] = '\0';
	showInterLeave(str1, str2, str3, 0);

	return 0;
}

void showInterLeave(char * str1, char * str2, char * str3, int ind) {
	if (*str1 == '\0' && *str2 == '\0') {
		printf("%s\n", str3);
	} else {
		if (*str1 != '\0') {
			str3[ind] = *str1;
			showInterLeave(str1 + 1, str2, str3, ind + 1);
		}
		if (*str2 != '\0') {
			str3[ind] = *str2;
			showInterLeave(str1, str2 + 1, str3, ind + 1);
		}
	}
}

