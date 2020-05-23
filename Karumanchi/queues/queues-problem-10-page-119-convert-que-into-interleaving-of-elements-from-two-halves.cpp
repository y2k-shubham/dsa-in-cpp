/*
10
11 12 13 14 15		16 17 18 19 20

11
11 12 13 14 15		16 17 18 19 20		21
*/

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

void input(queue <int> &);
void showQue(queue <int>);
void interleave(queue <int> &);

int main() {
	queue <int> que;

	input(que);
	showQue(que);

	interleave(que);
	showQue(que);

	return 0;
}

void input(queue <int> &que) {
	int n;

	printf("Enter no of elements:\t");
	scanf("%d", &n);

	cout << "Enter elements of que:-\n";
	for (int i = 1; i <= n; i++) {
		int ele;
		cin >> ele;

		que.push(ele);
	}
}

void showQue(queue <int> que) {
	cout << "\nQue is:-\n";
	while (!que.empty()) {
		cout << que.front() << "\t";
		que.pop();
	}
	cout << endl;
}

void interleave(queue <int> &que) {
	queue <int> tmpQue;
	int size = que.size();

	// move first half elements to another temporary que
	for (int i = 1; i <= size / 2; i++) {
		tmpQue.push(que.front());
		que.pop();
	}

	// interleave
	while (!tmpQue.empty()) {
		que.push(tmpQue.front());
		tmpQue.pop();

		que.push(que.front());
		que.pop();
	}

	// move last element if size is odd
	if (size & 1) {
		que.push(que.front());
		que.pop();
	}
}

