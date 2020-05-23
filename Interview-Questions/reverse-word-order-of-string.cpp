// http://www.geeksforgeeks.org/reverse-words-in-a-given-string/
/*
geeks quiz practice code
	getting	good at,  ,.! 123876 coding    needs a l  ot of 	practice
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void revWords_1(string&);
void revWords_2(string&);
void revPart(string&, int, int);
bool isAlpha(char);
void swapS(string&, int, int);

int main() {
	string sen;
	string sen_Copy;

	cout << "Enter a sentence:\t";
	getline(cin, sen);
	sen_Copy = sen;

	revWords_1(sen);
	reverse(sen.begin(), sen.end());

	revWords_1(sen_Copy);
	reverse(sen_Copy.begin(), sen_Copy.end());

	cout << "String with words reversed is:\t" << sen << endl;
	cout << "String with words reversed is:\t" << sen_Copy << endl;

	return 0;
}

void revWords_1(string& sen) {
	int i, j, k, len;

	i = 0;
	j = 0;
	k = 0;
	len = sen.size();
	while (true) {
		// consume space
		while (k < len && isAlpha(sen[k]) == false) {
//			printf("inner loop 1\n");
			k++;
		}

		if (k < sen.size()) {
			i = k;

			// find last char of word
			while (k < len && isAlpha(sen[k]) == true) {
//				printf("inner loop 2\n");
				k++;
			}

			// reverse all chars of word
			j = k - 1;
			while (i < j) {
//				printf("inner loop 3\n");
				swapS(sen, i, j);
				i++;
				j--;
			}
		}

		if (k >= len) {
			break;
		}
	}
}

void revWords_2(string& sen) {
	int i = 0;
	int j = 0;
	int len = sen.size();

	while (i < len) {
		if (isAlpha(sen[i]) == false) {
			revPart(sen, i - 1, j);
			i++;
			j = i;
		} else {
			i++;
		}
	}
}

bool isAlpha(char c) {
	if ('a' <= c && c <= 'z') {
		return true;
	} else if ('A' <= c && c <= 'Z') {
		return true;
	} else if ('0' <= c && c <= '9') {
		return true;
	} else {
		return false;
	}
}

void swapS(string& sen, int i, int j) {
	char tmp = sen[i];
	sen[i] = sen[j];
	sen[j] = tmp;
}

void revPart(string& sen, int i, int j) {
	while (i < j) {
//				printf("inner loop 3\n");
		swapS(sen, i, j);
		i++;
		j--;
	}
}

