// http://www.geeksforgeeks.org/maximum-of-all-subarrays-of-size-k/
// set has been used as a max-Heap
// http://code.geeksforgeeks.org/6PQavh : Max-Heap method runs in O(nlogk) time
// The DeQue method runs in O(n) time
// O(n) time Dynamic Programming method can be found at http://www.zrzahid.com/sliding-window-minmax/

/*
13
8 1 3 7 4 2 9 7 6 6 8 6 5
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <deque>
#include <set>
#include <utility>

using namespace std;
#define MAX 100

// input
void input(int [MAX], int&, int&);
// output
void showArr(int [MAX], int);
void showPQue(set <pair <int, int> >);
// Method 1: using Max-Heap
void createPQue(int [MAX], int, set <pair <int, int> >&);
void showMaxElements_1(int [MAX], int, int);
pair <int, int> getFront(set <pair <int, int> >);
// Method 2: Using DeQue
void createDQue(int [MAX], int, deque <int>&);
void showMaxElements_2(int [MAX], int, int);
int getFront(deque <int>&, int, int);

int main() {
	int a[MAX], len;
	int k;

	input(a, len, k);
	showArr(a, len);

	showMaxElements_1(a, len, k);
	showMaxElements_2(a, len, k);

	return 0;
}

// input
void input(int a[MAX], int& len, int& k) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		cin >> a[i];
	}

	showArr(a, len);

	printf("\nEnter window-size:\t");
	cin >> k;
}

// output
void showArr(int a[MAX], int len) {
	printf("\na[] array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

void showPQue(set <pair <int, int> > pQue) {
	printf("\nPriority Queue:-\n");
	for (set <pair <int, int> >::iterator i = pQue.begin(); i != pQue.end(); i++) {
		pair <int, int> p = *i;
		printf("a[%d] = %d\n", p.second, -p.first);
	}
}

void showDQue(int a[MAX], deque <int> dQue) {
	printf("\nDQue is:-\n");
	while (dQue.empty() == false) {
		printf("a[%d] = %d\n", dQue.front(), a[dQue.front()]);
		dQue.pop_front();
	}
}

// Method 1: using Max-Heap
void createPQue(int a[MAX], int k, set <pair <int, int> >& pQue) {
	for (int i = 0; i < k; i++) {
		pQue.insert(make_pair(-a[i], i));
	}
}

void showMaxElements_1(int a[MAX], int len, int k) {
	if (len > 0) {
		set <pair <int, int> > pQue;
		pair <int, int> tmp;

		createPQue(a, k, pQue);

		printf("\nMax elements of successive %d sized windows are:-\n", k);
		tmp = getFront(pQue);

//		printf("\nat i = %d", k - 1);
//		showPQue(pQue);
		printf("Max ele in a[%d..%d] is a[%d] = %d\n", 0, k - 1, tmp.second, -tmp.first);

		for (int i = k; i < len; i++) {
			pQue.erase(make_pair(-a[i - k], i - k));
			pQue.insert(make_pair(-a[i], i));

			tmp = getFront(pQue);

//			printf("\nat i = %d", i);
//			showPQue(pQue);
			printf("Max ele in a[%d..%d] is a[%d] = %d\n", i - k + 1, i, tmp.second, -tmp.first);
		}
	}
}

pair <int, int> getFront(set <pair <int, int> > pQue) {
	pair <int, int> ele = *(pQue.begin());
	return ele;
}

// Method 2: using DeQue
void createDQue(int a[MAX], int k, deque <int>& dQue) {
	dQue.push_back(0);
	for (int i = 1; i < k; i++) {
		while (dQue.empty() == false && a[dQue.back()] < a[i]) {
			dQue.pop_back();
		}
		dQue.push_back(i);
	}
}

void showMaxElements_2(int a[MAX], int len, int k) {
	if (len > 0) {
		deque <int> dQue;
		int tmp;

		createDQue(a, k, dQue);

		printf("\nMax elements of successive %d sized windows are:-\n", k);
		tmp = getFront(dQue, k, k - 1);

		printf("Max ele in a[%d..%d] is a[%d] = %d\n", 0, k - 1, tmp, a[tmp]);
		for (int i = k; i < len; i++) {
			while (dQue.empty() == false && a[dQue.back()] < a[i]) {
				dQue.pop_back();
			}
			dQue.push_back(i);

			tmp = getFront(dQue, k, i);
			printf("Max ele in a[%d..%d] is a[%d] = %d\n", i - k + 1, i, tmp, a[tmp]);
		}
	}
}

int getFront(deque <int>& dQue, int k, int crrInd) {
	int ele = dQue.front();

	if (ele == crrInd - k + 1) {
		dQue.pop_front();
	}

	return ele;
}

