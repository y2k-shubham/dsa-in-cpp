// http://www.geeksforgeeks.org/sum-minimum-maximum-elements-subarrays-size-k/
// Directi, Flipkart, Amazon

// Time: O(n)
// Space: O(n)

/*
7
8 1 3 7 4 2 9
3
*/

#include <cstdio>
#include <iostream>
#include <deque>
#include <vector>

using namespace std;

void input(vector <int>&, int&);
void showVec(vector <int>);
void extremeInWindow(vector <int>, int, bool);
bool isUseless(int, int, bool);

int main() {
	vector <int> vec;
	int k;

	input(vec, k);
	showVec(vec);

	extremeInWindow(vec, k, true);
	extremeInWindow(vec, k, false);

	return 0;
}

void input(vector <int>& vec, int& k) {
	int n;

	printf("Enter length of array:\t");
	cin >> n;
	vec.reserve(n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		int ele;
		cin >> ele;

		vec.push_back(ele);
	}

	printf("Enter window size:\t");
	cin >> k;
}

void showVec(vector <int> vec) {
	printf("\nElements of array are:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (vector <int>::iterator i = vec.begin(); i != vec.end(); i++) {
		printf("%d\t", (*i));
	}
	cout << endl;
}

void extremeInWindow(vector <int> vec, int k, bool minimum) {
	deque <int> dq(k);
	int i;

	// fill dq for 1st window
	for (i = 0; i < vec.size() && i < k; i++) {
		// remove all elements smaller / greater than current element vec[i]
		while (!dq.empty() && isUseless(vec[dq.back()], vec[i], minimum)) {
			dq.pop_back();
		}

		// add current element vec[i] to dq
		dq.push_back(i);
	}

	if (minimum) {
		printf("\nSmallest elements of windows are:-\n");
	} else {
		printf("\nBiggest elements of windows are:-\n");
	}

	for (; i < vec.size(); i++) {
		// show smallest / biggest element of previous window
		printf("vec[%d .. %d]:\tvec[%d] = %d\n", (i - k), (i - 1), dq.front(), vec[dq.front()]);

		// remove all elements not in current window (at max, there can be 1)
		if (!dq.empty() && dq.front() <= (i - k)) {
			dq.pop_front();
		}

		// remove all elements smaller / greater than current element vec[i]
		while (!dq.empty() && isUseless(vec[dq.back()], vec[i], minimum)) {
			dq.pop_back();
		}

		// add current element vec[i] to dq
		dq.push_back(i);
	}

	// show smallest / biggest element of last window
	printf("vec[%d .. %d]:\tvec[%d] = %d\n", (i - k), (i - 1), dq.front(), vec[dq.front()]);
}

bool isUseless(int qEle, int crrEle, bool minimum) {
	if (minimum) {
		return (qEle >= crrEle);
	} else {
		return (qEle <= crrEle);
	}
}

