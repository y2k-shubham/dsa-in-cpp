// http://www.practice.geeksforgeeks.org/problem-page.php?pid=579
// http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/

/*
ABDEFGABEF
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <string>
#include <map>

using namespace std;

int main() {
	string str;
	map <char, int> prevInd;
	int maxLen, maxLenInd;
	int crrLen, crrLenInd;

	printf("Enter a string:\t");
	cin >> str;

	maxLen = crrLen = 1;
	maxLenInd = crrLenInd = 0;
	prevInd[str[0]] = 0;

	for (int i = 1; i < str.length(); i++) {
		//printf("\nRead char str[%d] = %c\n", i, str[i]);

		if (prevInd.find(str[i]) == prevInd.end()) {
			//printf("New char, crrLen incremented to %d\n", crrLen + 1);
			crrLen++;
		} else {
			int prevIndOf_str_i = prevInd[str[i]];
			//printf("Char was already present at index %d\n", prevIndOf_str_i);
			crrLen = i - prevIndOf_str_i;

			if ((i - prevIndOf_str_i) > crrLen) {
				crrLen++;
				//printf("crrLen incremented to %d\ncrrLenInd unchanged at %d\n", crrLen, crrLenInd);
			} else {
				//crrLen -= prevIndOf_str_i - crrLenInd;
				crrLen = i - prevIndOf_str_i;
				crrLenInd = prevIndOf_str_i + 1;
				//printf("crrLen decremented to %d\ncrrLenInd changed to %d\n", crrLen, crrLenInd);
			}
		}

		if (crrLen >= maxLen) {
			maxLen = crrLen;
			maxLenInd = crrLenInd;
			//printf("maxLen and maxLenInd updated\n");
		}

		prevInd[str[i]] = i;
	}

	cout << "\nLongest substring having unique characters is " << str.substr(maxLenInd, maxLen) << " with length " << maxLen << endl;

	return 0;
}
