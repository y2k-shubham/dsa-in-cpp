// http://www.geeksforgeeks.org/lexicographically-previous-permutation-in-c/

/*
Input
781234
Output
748321

Input
781239
Output
739821

Input
765789
Output
759876

Input
766789
Output
698776

Input
667899
Output
Already Lexicographically Least

Input
781112233455556678888999
Output
779998888866555543322111
*/

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int findLSwapInd(string);
int findRSwapInd(string, int);
bool comparator(const char &, const char &);

int main() {
	string str;
	int swapIndL, swapIndR;

	cout << "Enter string:\t";
	cin >> str;

	swapIndL = findLSwapInd(str);
	if (swapIndL < 0) {
		cout << "String already lexicographically smallest\n";
	} else {
		swapIndR = findRSwapInd(str, swapIndL);

		if (swapIndR < 0) {
			cout << "\nError\n";
			return 1;
		}

		swap(str[swapIndR], str[swapIndL]);

		reverse(str.begin() + swapIndL + 1, str.end());
//		sort(str.begin() + swapIndL + 1, str.end(), comparator);
		cout << "Lexicographically previous string is " << str << endl;
	}

	return 0;
}

bool comparator(const char &a, const char &b) {
	return a > b;
}

int findLSwapInd(string str) {
	char prev = str[str.length() - 1];
	for (int i = str.length() - 2; i >= 0; i--) {
		char curr = str[i];
		if (curr > prev) {
			return i;
		} else {
			prev = curr;
		}
	}

	return -1;
}

int findRSwapInd(string str, int swapIndL) {
	for (int i = str.length() - 1; i > swapIndL; i--) {
		if (str[i] < str[swapIndL]) {
			return i;
		}
	}

	return -1;
}

