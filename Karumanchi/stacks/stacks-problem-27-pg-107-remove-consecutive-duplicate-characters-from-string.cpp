// Data Structures and Algorithms made Easy, Stacks, problem 27, page 107

#include <cstdio>
#include <iostream>
#include <string>
#include <stack>

using namespace std;

void method_1(string);
void method_2(string);

int main() {
	string str;

	cout << "Enter a string:\t";
	getline(cin, str);

	method_1(str);
	method_2(str);

	return 0;
}

void method_1(string str) {
	int i, j;

	i = j = 0;
	while (i < str.length()) {
		if (j == 0) {
			str[j] = str[i];
			j++;
		} else if (str[i] != str[j - 1]) {
			str[j] = str[i];
			j++;
		} else {
			j--;
		}
		i++;
	}
	str.resize(j);

	cout << "\nModified string:\t" << str;
}

void method_2(string str) {
	stack <char> stk;
	int i, j;

	for (i = 0, j = 0; i < str.length(); i++) {
		char c = str[i];

		if (!stk.empty() && stk.top() == c) {
			stk.pop();
			j--;
		} else {
			str[j] = c;
			j++;
			stk.push(c);
		}
	}
	str.resize(j);

	cout << "\nModified string:\t" << str << endl;
}
