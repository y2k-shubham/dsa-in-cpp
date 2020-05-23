#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

#define MAX_LEN 10
#define dRow 10
#define dCol 8

void createDefaceTable(int [dRow][dCol]);
char getSmallerDigit(char, char, int [dRow][dCol]);
char getBiggerDigit(char, char, int [dRow][dCol]);
void defaceScore(char [MAX_LEN], char [MAX_LEN], char [MAX_LEN], int [dRow][dCol]);

int main() {
	int defaceTable[dRow][dCol];
	int T;
	char S[MAX_LEN];
	char M[MAX_LEN];
	char defaced[MAX_LEN];
	char crrDig;
	char maxDig;
	char defDig;

	//printf("Enter no of test cases:\t");
	//scanf("%d", &T);
	createDefaceTable(defaceTable);

	//while (T--) {
	/*
	printf("\nEnter actual  score:\t");
	scanf("%s", S);

	printf("Enter maximum score:\t");
	scanf("%s", M);

	defaceScore(S, M, defaced, defaceTable);
	printf("The defaced score is:\t%s\n", defaced);
	*/
	//}

	printf("(crrDig maxDig) = ");
	scanf(" %c", &crrDig);
	scanf(" %c", &maxDig);
	getchar();
	while (crrDig >= '0' && maxDig >= '0') {
		defDig = getBiggerDigit(crrDig, maxDig, defaceTable);
		printf("digit crrDig = %c with maxDig = %c defaced to %c\n", crrDig, maxDig, defDig);

		printf("\n(crrDig maxDig) = ");
		scanf(" %c", &crrDig);
	    scanf(" %c", &maxDig);
	    getchar();
	}

	return 0;
}

void defaceScore(char S[MAX_LEN], char M[MAX_LEN], char defaced[MAX_LEN], int defaceTable[dRow][dCol]) {
	int maximize;
	int digM;
	int digS;
	int i;
	int j;

	maximize = 0;
	digM = strlen(M);
	digS = strlen(S);

	printf("\n");
	// copy extra digits
	for (i = 0, j = digS; j < digM; i++, j++) {
		defaced[i] = M[i];
		printf("digit %c copied from M[%d] to defaced[%d]\n", M[i], i, i);
	}

	printf("\n");
	// start defacing from left side
	for (j = 0; i <= digM; i++, j++) {
		defaced[i] = getBiggerDigit(S[j], M[i], defaceTable);
		if (defaced[i] == '\0') {
			// if S[j] can't be defaced to be <= M[i] then break the loop and set maximize to true
			printf("digit S[%d] = %c with M[%d] = %c could not be defaced\n", j, S[j], i, M[i]);
			maximize = 1;
			break;
		} else {
			printf("digit S[%d] = %c with M[%d] = %c defaced to %c\n", j, S[j], i, M[i], defaced[i]);
		}
	}

	printf("\n");
	if (i <= digM) {
		// reduce the digit S[j] with smallest possible place value to be lower than corresponding M[i]
		for (--i, --j; j >= 0; i--, j--) {
			printf("digit defaced[%d] = %c ", i, defaced[i]);
			defaced[i] = getSmallerDigit(S[j], M[i], defaceTable);

			if (defaced[i] != '\0') {
				// if your'e able to reduce any digit below it's counterpart maximum, then break the loop
				printf("with S[%d] = %c with M[%d] = %c reduced to %c\n", j, S[j], i, M[i], defaced[i]);
				break;
			} else {
				printf("with S[%d] = %c with M[%d] = %c could not be reduced\n", j, S[j], i, M[i]);
			}
		}

		if (i >= 0) {
			printf("\ncopied digit defaced[%d] = %c reduced to ", i, defaced[i]);
			defaced[i]--;
			printf("%c\n", defaced[i]);
			for (j = 0, ++i; i <= digM; i++, j++) {
				defaced[i] = getBiggerDigit(S[j], '9', defaceTable);
				printf("digit S[%d] = %c with M[%d] = %c maximized to %c\n", j, S[j], i, M[i], defaced[i]);
			}
			return;
		}
	}

	printf("\n");
	if (j < 0) {
		// if your'e unable to reduce any digit, then remove the most significant digit
		// copy extra digits
		i = 1;
		printf("No digits could be reduced, most-significant digit %c removed and i set to %d\n", defaced[0], i);
		for (j = digS; j < (digM - 1); i++, j++) {
			printf("digit defaced[%d] = %c maximized to 9\n", i, defaced[i]);
			defaced[i] = '9';
		}
	} else {
		++i;
		++j;
		printf("i incremented to %d and j incremented to %d\n", i, j);
		// do nothing
	}

	printf("\n");
	// maximize the remaining digits in the right, if needed
	if (maximize) {
		// start defacing from left side
		for (j = 0; i <= digM; i++, j++) {
			defaced[i] = getBiggerDigit(S[j], '9', defaceTable);
			printf("digit S[%d] = %c with M[%d] = %c maximized to %c\n", j, S[j], i, M[i], defaced[i]);
			if (defaced[i] == '\0') {
				// if S[j] can't be defaced to be <= M[i] then break the loop
				break;
			}
		}
	}
	printf("\n");
}

char getSmallerDigit(char crrDig, char maxDig, int defaceTable[dRow][dCol]) {
	int i;

	for (i = 0; defaceTable[crrDig - '0'][i] != crrDig; i++) {
	}

	for (--i; i >= 0 && defaceTable[crrDig - '0'][i] > maxDig; i--) {
	}

	if (i >= 0) {
		return defaceTable[crrDig - '0'][i];
	} else {
		return '\0';
	}
}

char getBiggerDigit(char crrDig, char maxDig, int defaceTable[dRow][dCol]) {
	int i;

    i = 0;
    printf("defaceTable[%d][%d] = %d\tcompared with %d\n", (crrDig - '0'), i, defaceTable[crrDig - '0'][i], (maxDig - '0'));
	for (i = 0; defaceTable[crrDig - '0'][i] <= (maxDig - '0'); i++) {
	}
	i--;

	if (i > 0) {
		return defaceTable[crrDig - '0'][i];
	} else {
		return '\0';
	}
}

void createDefaceTable(int defaceTable[dRow][dCol]) {
	defaceTable[0][0] = 0;
	defaceTable[0][1] = 8;
	defaceTable[0][2] = INT_MAX;

	defaceTable[1][0] = 0;
	defaceTable[1][1] = 1;
	defaceTable[1][2] = 3;
	defaceTable[1][3] = 4;
	defaceTable[1][4] = 7;
	defaceTable[1][5] = 8;
	defaceTable[1][6] = 9;
	defaceTable[1][7] = INT_MAX;

	defaceTable[2][0] = 2;
	defaceTable[2][1] = 8;
	defaceTable[2][2] = INT_MAX;

	defaceTable[3][0] = 3;
	defaceTable[3][1] = 8;
	defaceTable[3][2] = 9;
	defaceTable[3][3] = INT_MAX;

	defaceTable[4][0] = 4;
	defaceTable[4][1] = 8;
	defaceTable[4][2] = 9;
	defaceTable[4][3] = INT_MAX;

	defaceTable[5][0] = 5;
	defaceTable[5][1] = 6;
	defaceTable[5][2] = 8;
	defaceTable[5][3] = 9;
	defaceTable[5][4] = INT_MAX;

	defaceTable[6][0] = 6;
	defaceTable[6][1] = 8;
	defaceTable[6][2] = INT_MAX;

	defaceTable[7][0] = 3;
	defaceTable[7][1] = 7;
	defaceTable[7][2] = 8;
	defaceTable[7][3] = 9;
	defaceTable[7][4] = INT_MAX;

	defaceTable[8][0] = 8;
	defaceTable[8][1] = INT_MAX;

	defaceTable[9][0] = 8;
	defaceTable[9][1] = 9;
	defaceTable[9][2] = INT_MAX;
}
