/*
12
i like sam sung samsung mobile ice cream icecream man go mango
ilikesamsungmobile

9
i like ice cream icecream and man go mango
ilikeicecreamandmango
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void input(set <string>&, string&);
void showSet(set <string>);
void showVec(string, vector <bool>);
void showAllSegmentations(set <string>, string, vector <bool>&, int);
void showCrrSegmentation(string, vector <bool>);

int main() {
	set <string> dict;
	string str;

	input(dict, str);
//	showSet(dict);

	vector <bool> vec(str.size());
	vec.assign(str.size(), false);
//	showVec(str, vec);

	printf("\nPossible segmentations are:-\n");
	showAllSegmentations(dict, str, vec, 0);

	return 0;
}

void input(set <string>& dict, string& str) {
	int n;
	string word;

	printf("Enter size of dictionary:\t");
	cin >> n;

	printf("Enter words of dictionary:-\n");
	for (int i = 1; i <= n; i++) {
		cin >> word;
		dict.insert(word);
	}

	printf("\nEnter string to be segmented:\t");
	cin >> str;
}

void showSet(set <string> dict) {
	printf("\nDictionary of words is:-\n");
	for (set <string>::iterator i = dict.begin(); i != dict.end(); i++) {
		cout << (*i) << "\t";
	}
	cout << endl;
}

void showVec(string str, vector <bool> vec) {
	printf("\nSegmentation vector is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Str:\t";
	for (int i = 0; i < str.size(); i++) {
		printf("%c\t", str[i]);
	}
	cout << endl;

	cout << "Split:\t";
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] == true) {
			printf("T\t");
		} else {
			printf("F\t");
		}
	}
	cout << endl;
}

void showAllSegmentations(set <string> dict, string str, vector <bool>& vec, int ind) {
	if (ind == str.size()) {
		showCrrSegmentation(str, vec);
	} else {
		string crrWord;

		for (int i = ind; i < str.size(); i++) {
			crrWord += str[i];

			if (dict.find(crrWord) != dict.end()) {
				vec[i] = true;
				showAllSegmentations(dict, str, vec, i + 1);
				vec[i] = false;
			}
		}
	}
}

void showCrrSegmentation(string str, vector <bool> vec) {
	string crrWord;

	for (int i = 0; i < vec.size(); i++) {
		crrWord += str[i];

		if (vec[i] == true) {
			cout << crrWord << " ";
			crrWord.clear();
		}
	}
	cout << endl;
}

