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
void init(int [MAX], int, int, int, bool);
string getSeq(string, int [MAX], int);

int main() {
	string str;
	int N;
	int cSLen[MAX];
	int prevInd[MAX];
	set <char> vowelSet;

	cin >> N >> str;
	makeVowelSet(vowelSet);

	int prevVowInd = -1;
	int prevConInd = -1;
//	int maxCSLen = 0;

	int i = findFirstAlphaOfType(str, vowelSet, 0, true);
	init(prevInd, 0, i, -1, false);
	if (i < str.size()) {
		cSLen[i] = 1;
		prevVowInd = i;

		i = findFirstAlphaOfType(str, vowelSet, i, false);
		if (i < str.size()) {
			init(cSLen, prevVowInd + 1, i, 2, true);
			init(prevInd, prevVowInd + 1, i, prevVowInd, true);
//			cSLen[i - 1] = i - prevVowInd;
			prevVowInd = i - 1;

			cSLen[i] = cSLen[i - 1] + 1;
			prevConInd = i;
//			maxCSLen = cSLen[i];

			i++;
			while (i < str.size()) {
				if (vowelSet.find(str[i]) != vowelSet.end()) {
					cSLen[i] = cSLen[prevVowInd] + 1;
					prevInd[i] = prevVowInd;
					prevVowInd = i;
				} else {
					cSLen[i] = max(cSLen[prevVowInd], cSLen[prevConInd]) + 1;
					prevInd[i] = (cSLen[prevVowInd] > cSLen[prevConInd]) ? prevVowInd : prevConInd;
					prevConInd = i;
//					maxCSLen = max(maxCSLen, cSLen[i]);
				}

				i++;
			}
		}
	}

	if (prevConInd > 0) {
		cout << cSLen[prevConInd] << endl;
		cout << getSeq(str, prevInd, prevConInd) << endl;
	}

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

void init(int prevInd[MAX], int from, int to, int val, bool inc) {
	for (int i = from; i <= to; i++) {
		prevInd[i] = val;
		if (inc) {
			val++;
		}
	}
}

string getSeq(string str, int prevInd[MAX], int ind) {
	string seq;

	seq += str[ind];
	do {
		ind = prevInd[ind];
		seq = str[ind] + seq;
	} while (ind >= 0 && prevInd[ind] >= 0);

	return seq;
}

