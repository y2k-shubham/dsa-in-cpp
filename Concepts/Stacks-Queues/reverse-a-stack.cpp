#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

void input(stack <int> &);
void output(stack <int>, const char *);
void revStack(stack <int> &);
void insertAtBottom(stack <int> &, int);

int main() {
	stack <int> stk;

	input(stk);

	output(stk, "original stack");
	cout << endl;

	revStack(stk);

	output(stk, "reversed stack");
	cout << endl;

	return 0;
}

void input(stack <int> &stk) {
	int ele;

	cout << "Enter elements of stack:\t";
	cin >> ele;

	while (ele != -1) {
		stk.push(ele);
		cin >> ele;
	}
}

void output(stack <int> stk, const char * msg) {
	if (stk.empty()) {
		printf("\nThe %s is:-\n", msg);
	} else {
		int ele = stk.top();
		stk.pop();

		output(stk, msg);

		cout << ele << " ";
	}
}

void revStack(stack <int> &stk) {
	if (!stk.empty()) {
		int ele = stk.top();
		stk.pop();

		revStack(stk);
		insertAtBottom(stk, ele);
	}
}

void insertAtBottom(stack <int> &stk, int ele) {
	if (stk.empty()) {
		stk.push(ele);
	} else {
		int tmp = stk.top();
		stk.pop();

		insertAtBottom(stk, ele);
		stk.push(tmp);
	}
}

