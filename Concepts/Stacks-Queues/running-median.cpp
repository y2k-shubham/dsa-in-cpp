// http://stackoverflow.com/questions/10657503/find-running-median-from-a-stream-of-integers
// http://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/

#include <cstdio>
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

void input(priority_queue <int, vector <int>, greater <int> >&, priority_queue <int, vector <int> >&);
void showHeap(priority_queue <int, vector <int> >);
void showHeap(priority_queue <int, vector <int>, greater <int> >);

int main() {
	priority_queue <int, vector <int>, greater <int> > minHeap;
	priority_queue <int, vector <int> > maxHeap;

	input(minHeap, maxHeap);
	while (true) {
		int ele;
		cin >> ele;

		if (ele < maxHeap.top()) {
			maxHeap.push(ele);
		} else {
			minHeap.push(ele);
		}

		//printf("\nminHeap.size() = %d\tmaxHeap.size() = %d\tdiff = %d\t", minHeap.size(), maxHeap.size(), (minHeap.size() - maxHeap.size()));
		if (((int) (minHeap.size() - maxHeap.size())) > 1) {
			//printf("called if\n");
			maxHeap.push(minHeap.top());
			minHeap.pop();
		} else if (((int) (minHeap.size() - maxHeap.size())) < (-1)) {
			//printf("called else\n");
			minHeap.push(maxHeap.top());
			maxHeap.pop();
		}

		showHeap(minHeap);
		showHeap(maxHeap);

		if (minHeap.size() == maxHeap.size()) {
			cout << ((minHeap.top() + maxHeap.top()) / 2.0f) << endl << endl;
		} else if (minHeap.size() > maxHeap.size()) {
			cout << (minHeap.top()) << endl << endl;
		} else {
			cout << (maxHeap.top()) << endl << endl;
		}
	}

	return 0;
}

void input(priority_queue <int, vector <int>, greater <int> >& minHeap, priority_queue <int, vector <int> >& maxHeap) {
	int ele_1, ele_2;

	printf("Enter elements to find running median:-\n");

	cin >> ele_1;
	cout << ele_1 << endl << endl;

	cin >> ele_2;
	cout << ((ele_1 + ele_2) / 2.0f) << endl << endl;

	if (ele_1 < ele_2) {
		maxHeap.push(ele_1);
		minHeap.push(ele_2);
	} else {
		maxHeap.push(ele_2);
		minHeap.push(ele_1);
	}

	showHeap(minHeap);
	showHeap(maxHeap);
	cout << endl;
}

void showHeap(priority_queue <int, vector <int> > maxHeap) {
	printf("Max Heap is:\t");
	while (maxHeap.empty() == false) {
		cout << maxHeap.top() << "\t";
		maxHeap.pop();
	}
	cout << endl;
}

void showHeap(priority_queue <int, vector <int>, greater <int> > minHeap) {
	printf("Min Heap is:\t");
	while (minHeap.empty() == false) {
		cout << minHeap.top() << "\t";
		minHeap.pop();
	}
	cout << endl;
}

