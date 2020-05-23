// Given a stack like 4 5 -2 -3 11 10 5 6 20, check whether all pairs of elements in it
// (leaving topmost element 20, as it can't form pair in this case) are consecutive numbers or not

/*
9
4 5		-2 -3		11 10		5 6		20

9
4 5		-2 -3		11 13		5 6		20
*/

#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

void input(stack <int> &);
void revStackUsingQue(stack <int> &);
void checkAndFormQue(stack <int> &, queue <int> &);
int abs(int);
void recreateStack(stack <int> &, queue <int> &);
void showStack(stack <int>);
void showQue(queue <int>);
void revStack(stack <int> &);
void insAtBottom(stack <int> &, int);

int main() {
	stack <int> stk;
	queue <int> que;

	input(stk);
//	showStack(stk);

	// Reverse using either of the following methods
	revStackUsingQue(stk);
	revStack(stk);

//	showStack(stk);

	checkAndFormQue(stk, que);
//	showStack(stk);
//	showQue(que);

	recreateStack(stk, que);
//	showStack(stk);
//	showQue(que);

	return 0;
}

void input(stack <int> &stk) {
	int n;

	cout << "Enter no of elements in stack:\t";
	cin >> n;

	cout << "Enter elements of stack:-\n";
	for (int i = 1; i <= n; i++) {
		int ele;

		cin >> ele;
		stk.push(ele);
	}
}

void revStackUsingQue(stack <int> &stk) {
	queue <int> que;

	// move elements from stack to queue
	while (!stk.empty()) {
		que.push(stk.top());
		stk.pop();
	}

	// move elements from queue back to stack
	while (!que.empty()) {
		stk.push(que.front());
		que.pop();
	}
}

void checkAndFormQue(stack <int> &stk, queue <int> &que) {
	bool isLikeThat = true;

	while (!stk.empty()) {
		int ele_1 = stk.top();
		stk.pop();
		que.push(ele_1);

		if (!stk.empty()) {
			int ele_2 = stk.top();
			stk.pop();
			que.push(ele_2);

			if (abs(ele_1 - ele_2) != 1) {
				isLikeThat = false;
			}
		}
	}

	if (isLikeThat) {
		cout << "Stack is like that\n";
	} else {
		cout << "Stack is not like that\n";
	}
}

int abs(int a) {
	if (a >= 0) {
		return a;
	} else {
		return -a;
	}
}

void recreateStack(stack <int> &stk, queue <int> &que) {
	while (!que.empty()) {
		stk.push(que.front());
		que.pop();
	}
}

void showStack(stack <int> stk) {
	revStack(stk);

	cout << "\nThe stack is:-\n";
	while (!stk.empty()) {
		cout << stk.top() << "\t";
		stk.pop();
	}
	cout << endl;
}

void showQue(queue <int> que) {
	cout << "\nThe que is:-\n";
	while (!que.empty()) {
		cout << que.front() << "\t";
		que.pop();
	}
	cout << endl;
}

void revStack(stack <int> &stk) {
	if (!stk.empty()) {
		int ele = stk.top();
		stk.pop();

		revStack(stk);
		insAtBottom(stk, ele);
	}
}

void insAtBottom(stack <int> &stk, int ele) {
	if (stk.empty()) {
		stk.push(ele);
	} else {
		int topEle = stk.top();
		stk.pop();

		insAtBottom(stk, ele);
		stk.push(topEle);
	}
}

