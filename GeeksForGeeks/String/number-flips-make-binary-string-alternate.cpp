// http://www.geeksforgeeks.org/number-flips-make-binary-string-alternate/

/*
001
0001010111
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

pair <int, int> findFreq(string, int);
void showFlips(string, int);

int main() {
	string str;

	cout << "Enter a binary string:\t";
	cin >> str;

	pair <int, int> pE = findFreq(str, 0);
	pair <int, int> pO = findFreq(str, 1);

	if ((pE.first + pO.second) < (pE.second + pO.first)) {
		printf("Min no of flips needed = %d\n", (pE.first + pO.second));
		showFlips(str, 1);
	} else {
		printf("Min no of flips needed = %d\n", (pE.second + pO.first));
		showFlips(str, 0);
	}

	return 0;
}

pair <int, int> findFreq(string str, int bPos) {
	pair <int, int> freq = make_pair(0, 0);

	for (int i = bPos; i < str.length(); i += 2) {
		if (str[i] == '0') {
			freq.first++;
		} else {
			freq.second++;
		}
	}

	return freq;
}

void showFlips(string str, int eReqDig) {
	int oReqDig = 1 - eReqDig;

	printf("\nRequired flips are:-\n");
	for (int i = 0; i < str.length(); i++) {
		if (((i & 1) == 0) && ((str[i] - '0') != eReqDig)) {
			printf("flip str[%d] from %d to %d\n", i, oReqDig, eReqDig);
		} else if (((i & 1) == 1) && ((str[i] - '0') != oReqDig)) {
			printf("flip str[%d] from %d to %d\n", i, eReqDig, oReqDig);
		}
	}
}

