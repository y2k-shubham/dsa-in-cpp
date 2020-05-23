// https://www.hackerearth.com/challenge/college/cc2/algorithm/clean-string/

/*
10
jalpaiguri

-1
sksaimipsrmafegoouatfo

-1
sksaimipsrmafegoouaetfo
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <set>

using namespace std;
#define MAX 100005

void makeVowelSet(set <char>&);
int findFirstAlphaOfType(string, set <char>, int, bool);

int main() {
	string str;
	int N;
	set <char> vowelSet;

	cin >> N >> str;
	makeVowelSet(vowelSet);

	int prevVowLen = 0;
	int prevConLen = 0;

	int i = findFirstAlphaOfType(str, vowelSet, 0, true);
	if (i < str.size()) {
		int firstVowInd = i;
		prevVowLen = 1;

		i = findFirstAlphaOfType(str, vowelSet, i, false);
		if (i < str.size()) {
			prevVowLen = i - firstVowInd;
			prevConLen = prevVowLen + 1;

			i++;
			while (i < str.size()) {
				if (vowelSet.find(str[i]) != vowelSet.end()) {
					prevVowLen++;
				} else {
					prevConLen = max(prevVowLen, prevConLen) + 1;
				}

				i++;
			}
		}
	}

	cout << prevConLen << endl;

	return 0;
}

void makeVowelSet(set <char>& vowelSet) {
	vowelSet.insert('a');
	vowelSet.insert('e');
	vowelSet.insert('i');
	vowelSet.insert('o');
	vowelSet.insert('u');
	vowelSet.insert('A');
	vowelSet.insert('E');
	vowelSet.insert('I');
	vowelSet.insert('O');
	vowelSet.insert('U');
}

int findFirstAlphaOfType(string str, set <char> vowelSet, int from, bool vowelType) {
	int i;

	for (i = from; i < str.size(); i++) {
		if (vowelType == true && vowelSet.find(str[i]) != vowelSet.end()) {
			break;
		} else if (vowelType == false && vowelSet.find(str[i]) == vowelSet.end()) {
			break;
		}
	}

	return i;
}

