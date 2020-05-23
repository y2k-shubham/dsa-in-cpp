// http://www.geeksforgeeks.org/rearrange-a-string-so-that-all-same-characters-become-atleast-dist-distance-away/

/*
aaaabbbcc
2

aacbbc
3

geeksforgeeks
3

aaa
2
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MAX 256

struct info {
	char ch;
	int freq;
	int dist;
};

void input(string &, int &);
void init(int [MAX]);
void findFreq(string, vector <info> &, int [MAX]);
info createInfo(char, int, int);
void showVec(vector <info>, int [MAX]);
char getEligChar(vector <info>);
void decDist(vector <info> &);
bool rearrange(int, string &, vector <info>, int [MAX]);

int main() {
	vector <info> chars;
	int ind[MAX];
	string inStr;
	string outStr;
	int dist;

	input(inStr, dist);
	init(ind);

	outStr.resize(inStr.size());
	outStr.clear();

	findFreq(inStr, chars, ind);
	showVec(chars, ind);

	if (rearrange(dist, inStr, chars, ind)) {
		cout << "\nRearranged string:\t" << inStr << endl;
	} else {
		cout << "\nRearrangement not possible" << endl;
	}

	return 0;
}

void input(string &inStr, int &dist) {
	printf("Enter string:\t");
	getline(cin, inStr);

	printf("Enter distance:\t");
	cin >> dist;
}

void init(int ind[MAX]) {
	for (int i = 0; i < MAX; i++) {
		ind[i] = -1;
	}
}

void findFreq(string inStr, vector <info> &chars, int ind[MAX]) {
	for (int i = 0; i < inStr.length(); i++) {
		char ch = inStr[i];

		if (ind[ch] < 0) {
			chars.push_back(createInfo(ch, 1, 0));
			ind[ch] = chars.size() - 1;
		} else {
			chars[ind[ch]].freq++;
		}
	}
}

info createInfo(char ch, int freq, int dist) {
	info newChar;

	newChar.ch = ch;
	newChar.freq = freq;
	newChar.dist = dist;

	return newChar;
}

void showVec(vector <info> chars, int ind[MAX]) {
	cout << "\nVector of chars is:-\n";

	printf("Ind:\t");
	for (int i = 0; i < chars.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Char:\t";
	for (int i = 0; i < chars.size(); i++) {
		printf("%c\t", chars[i].ch);
	}
	cout << endl;

	cout << "Freq:\t";
	for (int i = 0; i < chars.size(); i++) {
		cout << chars[i].freq << "\t";
	}
	cout << endl;

	cout << "Dist:\t";
	for (int i = 0; i < chars.size(); i++) {
		cout << chars[i].dist << "\t";
	}
	cout << endl;
}

char getEligChar(vector <info> chars) {
	int maxFreq = -1;
	char maxFreqChar;

	for (int i = 0; i < chars.size(); i++) {
		if (chars[i].dist <= 0 && chars[i].freq > maxFreq) {
			maxFreq = chars[i].freq;
			maxFreqChar = chars[i].ch;
		}
	}

	if (maxFreq == -1) {
		return '\0';
	} else {
		return maxFreqChar;
	}
}

void decDist(vector <info> &chars) {
	for (int i = 0; i < chars.size(); i++) {
		chars[i].dist--;
	}
}

bool rearrange(int dist, string &outStr, vector <info> chars, int ind[MAX]) {
	for (int i = 0; i < outStr.size(); i++) {
//		showVec(chars, ind);
		char ch = getEligChar(chars);

		if (ch == '\0') {
			return false;
		} else {
//			printf("eligible char = %c\n", ch);
			outStr[i] = ch;
			decDist(chars);

			chars[ind[ch]].freq--;
			chars[ind[ch]].dist = dist - 1;
		}
	}
	cout << endl;

	return true;
}

