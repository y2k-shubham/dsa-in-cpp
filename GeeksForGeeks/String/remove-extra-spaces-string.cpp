// http://www.geeksforgeeks.org/remove-extra-spaces-string/

/*
3
   Hello Geeks . Welcome   to  GeeksforGeeks   .

puuchiiPoncho.. .
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;
void removeExtraSpaces(string &);

int main() {
	int T;
	string str;

	cin >> T;
	getline(cin, str);

	while (T-- > 0) {
		cout << endl;
		getline(cin, str);

		removeExtraSpaces(str);

		cout << "\"" << str << "\"" << endl;
	}

	return 0;
}

void removeExtraSpaces(string &str) {
	int i, j;
	bool spaceWritten = true;

	for (i = 0, j = 0; i < str.length(); i++, j++) {
		char c = str.at(i);

		if (!spaceWritten) {
			// if last character written wasn't space, write current character normally
			str[j] = str[i];
		} else {
			if (c == ' ') {
				// do nothing
				j--;
			} else if (!ispunct(c)) {
				// if not punctuation, then write normally
				str[j] = str[i];
			} else {
				// if punctuation, then write in place of previously written space
				str[--j] = str[i];
			}
		}

		// update status of last character written
		spaceWritten = (str[i] == ' ');
	}

	str.resize(j);
}

