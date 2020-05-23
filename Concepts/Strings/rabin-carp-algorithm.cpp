#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int findHashCode(string, int);
void output(string, int, string, int);
void matchAndShow(string, string, int);

int main() {
	string str;
	string ptr;
	int base = 3;
	int hashCode;

	cout << "Enter string:\t";
	getline(cin, str);

	cout << "Enter pattern:\t";
	getline(cin, ptr);

	hashCode = findHashCode(ptr, base);
	output(str, base, ptr, hashCode);

	return 0;
}

int findHashCode(string ptr, int base) {
	int ptrLen = ptr.length();
	int code = 0;
	for (int i = 0; i < ptrLen; i++) {
		code += ptr[i] * (int) (pow(base, i));
	}
	return code;
}

void output(string str, int base, string ptr, int ptrCode) {
	int ptrLen = ptr.length();
	int matchCode = findHashCode(str.substr(0, ptrLen), base);
	//cout << "\nFor substring " << str.substr(0, ptrLen) << " matchCode = " << matchCode << endl;

	cout << endl;
	if (matchCode == ptrCode) {
		matchAndShow(str, ptr, 0);
	}

	for (int i = ptrLen; i < str.length(); i++) {
		matchCode -= str[i - ptrLen];
		matchCode /= base;
		matchCode += str[i] * (int) (pow(base, ptrLen - 1));

		//cout << "\nFor substring " << str.substr(i - ptrLen + 1, ptrLen) << " matchCode = " << matchCode << endl;

		if (matchCode == ptrCode) {
			matchAndShow(str, ptr, i - ptrLen + 1);
		}
	}
}

void matchAndShow(string str, string ptr, int sInd) {
	int i, j;

	for (i = sInd, j = 0; i < sInd + ptr.length(); i++, j++) {
		if (str[i] != ptr[j]) {
			break;
		}
	}

	if (i == sInd + ptr.length()) {
		cout << "Match found at index " << sInd << endl;
	}
}
