#include <cstdio>
#include <iostream>
#include <climits>
#include <cstring>

#define MAX 5010
#define maxNum(a, b) ((a > b) ? a : b)

void findNoOfDecrypts(char [MAX], int [MAX], int);
void showArray(int [MAX], int);

int main() {
	char code[MAX];
	int ways[MAX];
	int len;

	scanf("%s", code);
	while (code[0] != '0') {
		len = strlen(code);
		memset(ways, '\0', sizeof(ways));

		findNoOfDecrypts(code, ways, len);
		printf("%d\n", ways[0]);

		scanf("%s", code);
	}

	return 0;
}

void findNoOfDecrypts(char code[MAX], int ways[MAX], int len) {
	int i;

	ways[len - 1] = 1;
	ways[len] = 1;

    //printf("digit = %c\t\t", code[len - 1]);
    //showArray(ways, len);

	for (i = (len - 2); i >= 0; i--) {
		if ((code[i] == '1') || (code[i] == '2' && code[i + 1] <= '6')) {
			ways[i] = ways[i + 2];
		}
		ways[i] += ways[i + 1];

		//printf("digit = %c\t\t", code[i]);
		//showArray(ways, len);
	}
}

void showArray(int arr[MAX], int len) {
    int i;

    for (i = 0; i < len; i++) {
        if (arr[i] == 0) {
            printf(" _");
        } else {
            printf(" %d", arr[i]);
        }
    }
    printf("\n");
}
