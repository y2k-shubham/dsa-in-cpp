// URL : http://www.geeksforgeeks.org/dynamic-programming-set-5-edit-distance/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define MAX_LEN 100
#define maxVal(a, b) ((a > b) ? a : b)
#define minVal(a, b) ((a < b) ? a : b)

int findEditDistDP(char [MAX_LEN], int, char [MAX_LEN], int);
void init(int *, int, int);

int main() {
	char str_1[MAX_LEN];
	char str_2[MAX_LEN];
	int len_1;
	int len_2;
	int minEditDist;

	printf("Enter 1st string:\t");
	scanf("%s", str_1);

	printf("Enter 2nd string:\t");
	scanf("%s", str_2);

	len_1 = strlen(str_1);
	len_2 = strlen(str_2);

	minEditDist = findEditDistDP(str_1, len_1, str_2, len_2);
	printf("The minimum edit distance between the two strings is:\t%d\n", minEditDist);

	return 0;
}

int findEditDistDP(char str_1[MAX_LEN], int len_1, char str_2[MAX_LEN], int len_2) {
	int editDist[len_1 + 1][len_2 + 1];

	memset(editDist, 0, sizeof(editDist));
	for (int i = 0; i <= len_1; i++) {
		for (int j = 0; j <= len_2; j++) {
			if (i == 0) {
				editDist[i][j] = j;
			} else if (j == 0) {
				editDist[i][j] = i;
			} else if (str_1[i - 1] == str_2[j - 1]) {
				editDist[i][j] = editDist[i - 1][j - 1];
			} else {
				editDist[i][j] = editDist[i - 1][j - 1];
				editDist[i][j] = minVal(editDist[i - 1][j], editDist[i][j]);
				editDist[i][j] = minVal(editDist[i][j - 1], editDist[i][j]);
				editDist[i][j]++;
			}
		}
	}

	return editDist[len_1][len_2];
}

