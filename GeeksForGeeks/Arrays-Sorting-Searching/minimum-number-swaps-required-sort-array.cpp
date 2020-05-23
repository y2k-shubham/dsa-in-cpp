// Problem: http://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/
// Submission: http://code.geeksforgeeks.org/iF6kFV

// Solution on above link is completely different and based on Graphs
// This solution is based on simple shuffling with the help of priority que + map (heap + map)

/*
4
4 3 2 1
Ans: 2

5
1 5 4 3 2
Ans: 2

5
4 5 2 1 3
Ans: 3

7
8 1 3 7 4 2 9
Ans: 3

7
8 1 4 7 3 2 9
Ans: 4
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <functional>
#include <utility>
#include <vector>
#include <map>

using namespace std;

void input(vector <int>&);
void clearCont(vector <int>&, priority_queue <int, vector <int> >&, map <int, int>&);
void makeQue(const vector <int>, priority_queue <int, vector <int> >&, map <int, int>&);
void showVec(const vector <int>);
void showQue(priority_queue <int, vector <int> >, map <int, int>);
void rearrange(vector <int>&, priority_queue <int, vector <int> >, map <int, int>&);
void swap(vector <int>&, map <int, int>&, int, int);

int main() {
	vector <int> vec;
	priority_queue <int, vector <int> > que;
	map <int, int> indMap;

	input(vec);
	makeQue(vec, que, indMap);

	showQue(que, indMap);
	showVec(vec);

	rearrange(vec, que, indMap);

	return 0;
}

void clearCont(vector <int>& vec, priority_queue <int, vector <int> >& que, map <int, int>& indMap) {
	vec.clear();
	indMap.clear();

	priority_queue <int, vector <int> > empQue;
	swap(que, empQue);
}

void input(vector <int>& vec) {
	int len;

	printf("Enter no of elements in vector:\t");
	cin >> len;
	vec.reserve(len);

	cout << "Enter elements of vector:-\n";
	for (int i = 0; i < len; i++) {
		int ele;
		cin >> ele;

		vec.push_back(ele);
	}
}

void makeQue(const vector <int> vec, priority_queue <int, vector <int> >& que, map <int, int>& indMap) {
	for (int i = 0; i < vec.size(); i++) {
		que.push(-vec[i]);
		indMap.insert(make_pair(vec[i], i));
	}
}

void showVec(const vector <int> vec) {
	printf("\nVector is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (vector <int>::const_iterator i = vec.begin(); i != vec.end(); i++) {
		printf("%d\t",*i);
	}
	cout << endl;
}

void showQue(priority_queue <int, vector <int> > que, map <int, int> indMap) {
	printf("\nPriority Que:-\n");
	while (!que.empty()) {
		int ele = -que.top();
		int ind = indMap[ele];
		que.pop();

		printf("arr[%d] = %d\n", ind, ele);
	}
}

void rearrange(vector <int>& vec, priority_queue <int, vector <int> > que, map <int, int>& indMap) {
	int count = 0;

	for (int i = 0; i < vec.size(); i++) {
		int ele = -que.top();
		int ind = indMap[ele];
		que.pop();

		if (vec[i] != ele) {
			count++;
			printf("\n%d. swap vec[%d] = %d and vec[%d] = %d", count, i, vec[i], ind, vec[ind]);
			swap(vec, indMap, i, ind);
			showVec(vec);
		}
	}

	printf("\nTotal no of swaps needed is %d\n", count);
}

void swap(vector <int>& vec, map <int, int>& indMap, int pos_1, int pos_2) {
	int tmp = vec[pos_1];
	vec[pos_1] = vec[pos_2];
	vec[pos_2] = tmp;

	indMap[vec[pos_1]] = pos_1;
	indMap[vec[pos_2]] = pos_2;
}

