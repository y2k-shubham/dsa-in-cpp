// http://www.geeksforgeeks.org/remove-a-and-bc-from-a-given-string/
// Google Interview Question: to be done in-place
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str;
	int i, j;
	bool endsWithac = false;

	printf("Enter a string:\t");
	getline(cin, str);

	if (str.length() >= 2 && str[str.length() - 2] == 'a' && str[str.length() - 1] == 'c') {
		endsWithac = true;
	}

	for (i = 0, j = 0; i < str.length(); ) {
		while ((i < str.length()) && (str[i] != 'b') && !((i < str.length() - 2) && (str[i] == 'a') && (str[i + 1] == 'c'))) {
			str[j] = str[i];
			i++;
			j++;

			// following line makes sure that ac never appears in output
			if (j >= 2 && str[j - 2] == 'a' && str[j - 1] == 'c') {
				j -= 2;
			}
		}

		if (i < str.length()) {
			if (str[i] == 'b') {
				i++;
			} else {
				i += 2;
			}
		}
	}
	str.resize(j);

	if (endsWithac) {
		// if any ac is present at end of string, it is removed here
		str.resize(j - 2);
	}

	cout << "Modified string:\t\"" << str << "\"" << endl;

	return 0;
}
