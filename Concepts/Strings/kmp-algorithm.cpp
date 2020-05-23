// TusharRoy

/*
abcbcglx
bcgl

abcxabcdabxabcdabcdabcy
abcdabcy

abxabcabcaby
abcaby

abyabcabyabyabyabcabyabyabc
abyaby

abyabcabyabyabyabcabyabycbc
abyaby

pqr
acacabacacabacacac
*/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
#define MAX 100

void buildSufArr(string, int [MAX]);
void showArray(string, int [MAX]);
void matchAndShow(string, string, int [MAX]);

int main() {
	string str, pat;
	int sufArr[MAX];

	printf("Enter string to be searched:\t");
	getline(cin, str);

	printf("Enter pattern to be searched:\t");
	getline(cin, pat);

	buildSufArr(pat, sufArr);
	showArray(pat, sufArr);
	matchAndShow(str, pat, sufArr);

	return 0;
}

void buildSufArr(string pat, int sufArr[MAX]) {
	int i, j;

	sufArr[0] = 0;
	for (i = 0, j = 1; j < pat.length(); ) {
		if (pat[i] == pat.at(j)) {
			sufArr[j] = i + 1;
			i++;
			j++;
		} else if (i > 0) {
			i = sufArr[i - 1];
		} else {
			sufArr[j] = 0;
			j++;
		}
	}
}

void showArray(string pat, int sufArr[MAX]) {
	printf("\nSuffix array is:-\n");

	printf("Ind\t");
	for (int i = 0; i < pat.size(); i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Char:\t");
	for (int i = 0; i < pat.length(); i++) {
		printf("%c\t", pat.at(i));
	}
	printf("\n");

	printf("Len:\t");
	for (int i = 0; i < pat.size(); i++) {
		printf("%d\t", sufArr[i]);
	}
	printf("\n");
}

void matchAndShow(string str, string pat, int sufArr[MAX]) {
	if (str.length() >= pat.size()) {
		int i, j;

		printf("\nThe pattern matches are:-\n");
		for (i = 0, j = 0; i < str.length(); ) {
//			printf("str[%d] = %c\tpat[%d] = %c\n", i, str[i], j, pat[j]);
			if (str[i] == pat.at(j)) {
				i++;
				j++;

				if (j == pat.length()) {
					int patSInd = i - pat.length();
					int patEInd = i - 1;

					printf("Pattern found between str[%d] and str[%d]\n", patSInd, patEInd);

					j = sufArr[j - 1];
				}
			} else if (j > 0) {
				if (i > str.length() - pat.size()) {
					break;
				}
				j = sufArr[j - 1];
			} else {
				i++;
			}
		}
	} else {
		printf("\nPattern is bigger than string to be searched\n");
	}
}
