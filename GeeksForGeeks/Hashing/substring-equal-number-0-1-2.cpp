// http://www.geeksforgeeks.org/substring-equal-number-0-1-2/

/*
0102010
10210211
102100211
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <string>

using namespace std;
#define MAX 100

void way_1(string);
void findCumFreq(string, int [3][MAX]);
int findCount(string, int [3][MAX]);
void showTab(string, int [3][MAX]);
void way_2(string);

int main() {
	string str;

	cout << "Enter string of 0s, 1s and 2s:\t";
	cin >> str;

	way_1(str);
	way_2(str);

	return 0;
}

// O(n^2) time and space
void way_1(string str) {
	int freq[3][MAX];

	findCumFreq(str, freq);
	int ans = findCount(str, freq);
	showTab(str, freq);

	cout << "WAY-1:\tNo of substrings having equal no of 0s, 1s and 2s is " << ans << endl;
}

void findCumFreq(string str, int freq[3][MAX]) {
	str = ' ' + str;
	freq[0][0] = freq[1][0] = freq[2][0] = 0;

	for (int i = 1; i < str.length(); i++) {
		freq[0][i] = freq[0][i - 1];
		freq[1][i] = freq[1][i - 1];
		freq[2][i] = freq[2][i - 1];

//		printf("at str[%d] = %c, inc freq of freq[%d][%d]\n", i, str[i], (str[i] - '0'), i);
		freq[str[i] - '0'][i]++;
	}
}

int findCount(string str, int freq[3][MAX]) {
	int count = 0;

	for (int i = 3; i < str.length(); i++) {
		for (int j = i - 3; j >= 0; j -= 3) {
			int del0 = freq[0][i] - freq[0][j];
			int del1 = freq[1][i] - freq[1][j];
			int del2 = freq[2][i] - freq[2][j];

			if (del0 == del1 && del0 == del2) {
				count++;
//				printf("count incremented for str[%d .. %d], del = %d\n", j, i, del0);
			}
		}
	}

	return count;
}

void showTab(string str, int freq[3][MAX]) {
	str = ' ' + str;
	cout << "\nFreq table is:-\n";

	cout << "Char\t";
	for (int i = 0; i < str.length(); i++) {
		printf("%c\t", str[i]);
	}
	cout << endl;

	cout << "Ind\t";
	for (int i = 0; i < str.length(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	for (int n = 0; n < 3; n++) {
		printf("Freq-%d\t", n);
		for (int i = 0; i < str.length(); i++) {
			printf("%d\t", freq[n][i]);
		}
		cout << endl;
	}
	cout << endl;
}

// O(nlogn) time and O(n) space
void way_2(string str) {
	map <pair <int, int>, int> delFreq;
	int f0, f1, f2;
	int count;

	f0 = f1 = f2 = 0;
	count = 0;
	delFreq.insert(make_pair(make_pair(0, 0), 1));

	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '0') {
			f0++;
		} else if (str[i] == '1') {
			f1++;
		} else {
			f2++;
		}

		pair <int, int> del = make_pair(f0 - f1, f0 - f2);

		count += delFreq[del];
		delFreq[del]++;
	}

	cout << "WAY-1:\tNo of substrings having equal no of 0s, 1s and 2s is " << count << endl;
}
