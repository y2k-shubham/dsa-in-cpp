// Doesn't work for repetitions

#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void swap(string &, int, int);
void showPerms(string &, int);
int ctr = 0;

int main() {
	string str;

	cout << "Enter string:\t";
	getline(cin, str);
	sort(str.begin(), str.end());

	cout << "Permutations of entered string are:-\n";
	showPerms(str, 0);
	cout << "No of permutations = " << ctr << endl;

	return 0;
}

void showPerms(string &str, int crrInd) {
	if (crrInd == str.length() - 1) {
		cout << str << endl;
		ctr++;
	} else {
		showPerms(str, crrInd + 1);
		for (int i = crrInd + 1; i < str.length(); i++) {
			if (str.at(crrInd) != str.at(i)) {
				swap(str, crrInd, i);
				showPerms(str, crrInd + 1);
				swap(str, crrInd, i);
			}
		}
	}
}

void swap(string &str, int i, int j) {
	char c = str[i];
	str[i] = str[j];
	str[j] = c;
}

