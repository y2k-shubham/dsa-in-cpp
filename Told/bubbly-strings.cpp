/*
aaabbb
abababab
abaabaabaaba
aabbababab
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <utility>

using namespace std;

bool checkBubbly(string);
void showPairing(string);
void showStack(stack <char>);

int main() {
	string str;

	printf("Enter a string:\t");
	cin >> str;

	if (checkBubbly(str)) {
		cout << "It is bubbly string\n";
		showPairing(str);
	} else {
		cout << "It is not bubbly string\n";
	}

	return 0;
}

bool checkBubbly(string str) {
	stack <char> stk;

	for (int i = 0; i < str.length(); i++) {
		char cStr = str[i];

		if (!stk.empty()) {
			char cStk = stk.top();

			if (cStr == cStk) {
				stk.pop();
			} else {
				stk.push(cStr);
			}
		} else {
			stk.push(cStr);
		}

		printf("\nat str[%d] = %c", i, cStr);
		showStack(stk);
		cout << endl;
	}

	return stk.empty();
}

void showPairing(string str) {
	stack <pair <char, int> > stk;
	int pairInd[100];

	for (int i = 0; i < str.length(); i++) {
		char cStr = str[i];

		if (!stk.empty()) {
			pair <int, int> cStk = stk.top();

			if (cStr == cStk.first) {
				pairInd[i] = cStk.second;
				pairInd[cStk.second] = i;
				stk.pop();
			} else {
				stk.push(make_pair(cStr, i));
			}
		} else {
			stk.push(make_pair(cStr, i));
		}
	}

	cout << "Pairing is:-\n";

	cout << "Ind:\t";
	for (int i = 0; i < str.length(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Chars:\t";
	for (int i = 0; i < str.length(); i++) {
		cout << str[i] << "\t";
	}
	cout << endl;

	cout << "PInd:\t";
	for (int i = 0; i < str.length(); i++) {
		cout << pairInd[i] << "\t";
	}
	cout << endl;
}

void showStack(stack <char> stk) {
	if (!stk.empty()) {
		char c = stk.top();
		stk.pop();

		showStack(stk);

		cout << c << "\t";
	} else {
		printf("\nStack is:-\n");
	}
}

