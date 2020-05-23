// http://www.geeksforgeeks.org/ola-interview-experience-set-12/

/*
5
chola ike hike olas fool
*ola*

5
chola ike hike olas fool
*ola?

5
skinet ike hike olas bikerss
*i?e*

5
a bd d e3 3
?

5
a bd d e3 3
*

5
a bd d e3 3
*?

5
a bd d e3 3
*??
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

void input(vector <string>&, string&);
void match(vector <string>, string);
bool doesMatch(string, int, string, int);

int main() {
	vector <string> vec;
	string pat;

	input(vec, pat);
	match(vec, pat);;

	return 0;
}

void input(vector <string>& vec, string& pat) {
	int len;

	printf("Enter no of strings:\t");
	scanf("%d", &len);
	vec.reserve(len);

	printf("Enter %d strings:-\n", len);
	for (int i = 1; i <= len; i++) {
		string str;
		cin >> str;
		vec.push_back(str);
	}

	printf("\nEnter pattern:\t");
	cin >> pat;
}

void match(vector <string> vec, string pat) {
	cout << endl;
	for (int i = 0; i < vec.size(); i++) {
		printf("vec[%d] = ", i);
		if (doesMatch(vec[i], 0, pat, 0)) {
			cout << vec[i] << "\t" << "matches" << endl;
		} else {
			cout << vec[i] << "\t" << "does not match" << endl;
		}
	}
}

bool doesMatch(string str, int iStr, string pat, int iPat) {
	if (iPat >= pat.length() && iStr >= str.length()) {
		return true;
	} else if (iPat < pat.length() && iStr < str.length()) {
		if ((pat[iPat] == str[iStr]) || (pat[iPat] == '?')) {
			return doesMatch(str, iStr + 1, pat, iPat + 1);
		} else if (pat[iPat] == '*') {
			bool matchFound = false;

			for (int i = iStr; !matchFound && i <= str.length(); i++) {
				matchFound = matchFound || doesMatch(str, i, pat, iPat + 1);
			}

			return matchFound;
		} else {
			return false;
		}
	} else if (iPat < pat.length() && pat[iPat] == '*') {
		return true;
	} else {
		return false;
	}
}

