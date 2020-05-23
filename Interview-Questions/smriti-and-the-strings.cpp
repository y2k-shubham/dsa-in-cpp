// https://www.hackerrank.com/contests/womens-codesprint/challenges/smriti-and-strings
// https://github.com/qianghaowork/WomenCodeSprint/blob/master/smriti_string.cpp

/*
1
bjce 2
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string largestStr(string& str, int m) {
	string res = "";
	int count = 0;
	int len = str.length();
	vector<int> pos(len+1, 0);
	pos[0] = -1;
	int j = 1;
	while(j<len) {
		if ( pos[j]>=0 && str[pos[j]] < str[j]) {
			count++;
			str[pos[j]] = '-';
			pos[j] = pos[pos[j]];
		} else {
			pos[j+1] = j;
			j++;
		}
		if (count==m)
			break;
	}
	j=len-1;
	while(count<m) {
		if ( str[j]!='-') {
			count++;
			str[j] = '-';
		}
		j--;
	}

	for(int i=0; i<len; ++i) {
		if (str[i]!='-')
			res += str[i];
	}

	return res;
}

int main() {
	/* Enter your code here. Read input from STDIN. Print output to STDOUT */
	int T = 0;
	cin >> T;
	while(T--) {
		int m = 0;
		string str = "";
		cin >> str >> m;

		cout << largestStr(str, m) << endl;
	}
	return 0;
}

