#include <bits/stdc++.h>

using namespace std;

int main() {
	string str = "";

	while (getline(cin, str) != "return 0;") {
		int i;
		int j = 0;
		for (i = 0; str[i] != '\0'; i++) {
			if (str[i] == '/' && str[i+1] == '/') {
				break;
			}

			if (str[i] == '-' && str[i+1] == '>') {
				str[i] = '';
				str[i+1] = '.';
			}
		}
		cout << str << endl;

	}

	cout << str;

	return 0;
}
