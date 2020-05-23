// http://www.geeksforgeeks.org/find-the-nearest-smaller-numbers-on-left-side-in-an-array/

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;
#define MAX 100

void input(int [MAX], int&);
void output(int [MAX], int&);

int main() {
	int t;
	int n;
	int a[MAX];

	scanf("%d", &t);
	while (t--) {
		input(a, n);
		output(a, n);
	}

	return 0;
}

void input(int a[MAX], int& n) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
}

void output(int a[MAX], int& n) {
	stack <int> stk;

	for (int i = 0; i < n; i++) {
		int ele = a[i];
		while (!stk.empty() && stk.top() >= ele) {
			stk.pop();
		}

		if (stk.empty()) {
			printf("-1 ");
		} else {
			printf("%d ", stk.top());
		}

		stk.push(ele);
	}
}
