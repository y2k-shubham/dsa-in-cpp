#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

void input(queue <int> &, int &);
void showQue(queue <int>, const char *);
void revQue(queue <int> &);
void insAtFront(queue <int> &, int);

int main() {
	queue <int> que;
	int ele;

	input(que, ele);
	showQue(que, "Que");

	revQue(que);
	showQue(que, "Reversed que");

	revQue(que);
	insAtFront(que, ele);
	showQue(que, "Que after front insertion");

	return 0;
}

void input(queue <int> &que, int &fEle) {
	int n;

	cout << "Enter no of elements:\t";
	cin >> n;

	cout << "Enter elements of que:-\n";
	for (int i = 1; i <= n; i++) {
		int ele;
		cin >> ele;

		que.push(ele);
	}

	cout << "Enter element to be inserted at front:\t";
	cin >> fEle;
}

void showQue(queue <int> que, const char * msg) {
	printf("\n%s is:-\n", msg);
	while (!que.empty()) {
		cout << que.front() << "\t";
		que.pop();
	}
	cout << endl;
}

void revQue(queue <int> &que) {
	if (!que.empty()) {
		int ele = que.front();
		que.pop();
		revQue(que);
		que.push(ele);
	}
}

void insAtFront(queue <int> &que, int ele) {
	revQue(que);
	que.push(ele);
	revQue(que);
}

