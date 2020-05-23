// http://www.geeksforgeeks.org/length-longest-sub-string-can-make-removed/

/*
1011100000100
111011
101001100000
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

int main() {
	string str;
	vector <pair <char, int> > vec;
	int maxLen, maxLIndL, maxLIndR;

	cout << "Enter binary string:\t";
	cin >> str;

	vec.push_back(make_pair('@', -1));
	maxLen = 0;

	for (int i = 0; i < str.length(); i++) {
		vec.push_back({str[i], i});

		if (vec.size() >= 3 && vec[vec.size() - 3].first == '1' && vec[vec.size() - 2].first == '0' && vec[vec.size() - 1].first == '0') {
			vec.pop_back();
			vec.pop_back();
			vec.pop_back();
		}

		if (i - vec.back().second > maxLen) {
			maxLen = i - vec.back().second;
			maxLIndL = vec.back().second + 1;
			maxLIndR = i;
		}
	}

	if (maxLen > 0) {
		printf("maximum length string that can be removed is str[%d .. %d] of length %d\n", maxLIndL, maxLIndR, maxLen);
	} else {
		printf("no substring can be removed\n");
	}

	return 0;
}
