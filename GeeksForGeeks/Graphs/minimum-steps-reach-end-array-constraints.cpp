// http://www.geeksforgeeks.org/minimum-steps-reach-end-array-constraints/
// http://stackoverflow.com/questions/11134497/constant-sized-vector

/*
5
5 4 2 5 0

19
0 1 2 3 4 5 6 7 5 4 3 6 0 1 2 3 4 5 7
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void init(vector <pair <int, int> > &, int, int, int);
void init(vector <vector <int> > &);
void showArray(int [MAX], int, const char *);
void showPosVec(vector <vector <int> >);
void showJmpVec(int [MAX], vector <pair <int, int> >, const char *);
void showPath(vector <pair <int, int> >, int);
void createPosVec(int [MAX], int, vector <vector <int> > &);
void bfs(int [MAX], int, vector <pair <int, int> > &, vector <vector <int> >);

int main() {
	int arr[MAX], len;
	vector <pair <int, int> > minJmp;
	vector <vector <int> > numPos;

	input(arr, len);
	showArray(arr, len, "arr[]");

	init(numPos);
	createPosVec(arr, len, numPos);
	showPosVec(numPos);

	init(minJmp, len, INT_MAX, -1);
	showJmpVec(arr, minJmp, "before BFS");

	bfs(arr, len, minJmp, numPos);
	showJmpVec(arr, minJmp, "after BFS");

	printf("\nMin no of jumps taken to reach end are %d\n", minJmp[len - 1].first);
	showPath(minJmp, len - 1);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-" << endl;
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void init(vector <pair <int, int> > &minJmp, int len, int defVal1, int defVal2) {
//	minJmp.reserve(len);				// not working
	for (int i = 0; i < len; i++) {
//		minJmp[i].first = defVal1;
//		minJmp[i].second = defVal1;
		minJmp.push_back(make_pair(defVal1, defVal2));
	}
}

void init(vector <vector <int> > &numPos) {
	numPos.reserve(10);				// This isn't working
	for (int i = 0; i < 10; i++) {
		vector <int> tmp;
		numPos.push_back(tmp);
	}
}

void createPosVec(int arr[MAX], int len, vector <vector <int> > &numPos) {
	for (int i = 0; i < len; i++) {
		numPos[arr[i]].push_back(i);
	}
}

void showArray(int arr[MAX], int len, const char * msg) {
	printf("\n%s array is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl << endl;
}

void showPosVec(vector <vector <int> > numPos) {
	printf("\nnumPos vector is:-\n");

	for (int i = 0; i < 10; i++) {
		printf("%d\t->\t", i);

		for (vector <int>::iterator j = numPos[i].begin(); j != numPos[i].end(); j++) {
			printf("%d ", (*j));
		}
		cout << endl;
	}
}

void showJmpVec(int arr[MAX], vector <pair <int, int> > minJmp, const char * msg) {
	printf("\n%s minJmp vector is:-\n", msg);

	int len = minJmp.size();
	int ind = 0;
	for (vector <pair <int, int> >::iterator i = minJmp.begin(); i != minJmp.end(); i++, ind++) {
		if ((*i).first != INT_MAX) {
			printf("a[%d] = %d\t%d\t%d\n", ind, arr[ind], (*i).first, (*i).second);
		} else {
			printf("a[%d] = %d\t_\t%d\n", ind, arr[ind], (*i).second);
		}
	}
}

void showPath(vector <pair <int, int> > minJmp, int crr) {
	if (crr == 0) {
		printf("\nPath taken to reach end is:-\n");
		printf("0 -> ");
	} else {
		showPath(minJmp, minJmp[crr].second);

		if (crr == minJmp.size() - 1) {
			printf("%d\n", crr);
		} else {
			printf("%d -> ", crr);
		}
	}
}

void bfs(int arr[MAX], int len, vector <pair <int, int> > &minJmp, vector <vector <int> > numPos) {
	queue <int> que;

	que.push(0);
	minJmp[0].first = minJmp[0].second = 0;

//	printf("\nBFS on array\n");
	while (!que.empty()) {
		int ind = que.front();
		que.pop();

//		printf("\npopped %d from que", ind);

		if (ind > 0 && minJmp[ind - 1].first > minJmp[ind].first + 1) {
			minJmp[ind - 1].first = minJmp[ind].first + 1;
			minJmp[ind - 1].second = ind;
			que.push(ind - 1);
		}

		if (ind < len - 1 && minJmp[ind + 1].first > minJmp[ind].first + 1) {
			minJmp[ind + 1].first = minJmp[ind].first + 1;
			minJmp[ind + 1].second = ind;
			que.push(ind + 1);
		}

		for (vector <int>::iterator i = numPos[arr[ind]].begin(); i != numPos[arr[ind]].end(); i++) {
			if (minJmp[*i].first > minJmp[ind].first + 1) {
				minJmp[*i].first = minJmp[ind].first + 1;
				minJmp[*i].second = ind;
				que.push(*i);
			}
		}

//		showJmpVec(arr, minJmp);
	}
}

