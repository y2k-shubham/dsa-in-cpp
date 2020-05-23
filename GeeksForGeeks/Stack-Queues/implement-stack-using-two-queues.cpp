// http://www.geeksforgeeks.org/implement-stack-using-queue/

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

void moveEle(queue <int> &, queue <int> &, int);

int main() {
	queue <int> q1, q2;		// version 1 : pop is O(n), push is O(1)
	queue <int> q3, q4;		// version 2 : pop is O(1), push is O(n)
	int choice, ele;

	choice = -1;
	while (choice != 5) {
		cout << "\n1. Push";
		cout << "\n2. Pop";
		cout << "\n3. IsEmpty";
		cout << "\n4. Exit";

		cout << "\n\nEnter your choice:\t";
		cin >> choice;

		switch (choice) {
			case 1:
				cout << "Enter element:\t";
				cin >> ele;
				q1.push(ele);

				q4.push(ele);
				moveEle(q3, q4, q3.size());
				swap(q3, q4);

				break;

			case 2:
				if (!q1.empty() == !q3.empty()) {
					if (!q1.empty()) {
						moveEle(q1, q2, q1.size() - 1);
						ele = q1.front();
						q1.pop();
						swap(q1, q2);

						if (q3.front() == ele) {
							q3.pop();
							cout << "Popped:\t" << ele << endl;
						} else {
							cout << "Some error\n";
						}
					} else {
						cout << "Stack underflow\n";
					}
				} else {
					cout << "Some error\n";
				}
				break;

			case 3:
				if (q1.empty() == q3.empty()) {
					if (q1.empty()) {
						cout << "True" << endl;
					} else {
						cout << "False" << endl;
					}
				} else {
					cout << "Some error\n";
				}
				break;

			case 4:
				continue;

			default:
				cout << "Invalid Input\n";
		}
	}

	return 0;
}

void moveEle(queue <int> &qSrc, queue <int> &qDst, int count) {
	for (int i = 1; i <= count; i++) {
		qDst.push(qSrc.front());
		qSrc.pop();
	}
}

