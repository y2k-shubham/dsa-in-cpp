// http://www.geeksforgeeks.org/longest-path-between-any-pair-of-vertices/

// http://en.cppreference.com/w/cpp/iterator/next
// www.geeksforgeeks.org/topological-sorting/
// TusharRoy: Topological Sorting Graph ALgorithm

/*
6
0 1
1 2		1 5
5 3		5 4
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <iterator>

using namespace std;

void input(vector <list <int> > &, int &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
void init(vector <int> &, int);
void output(vector <list <int> >, int);
void topoSort(vector <list <int> >, int, vector <bool> &, stack <int> &, int);
void showStack(stack <int>);
void createTopoList(stack <int>, list <int> &);
void showTopoList(list <int>);
void findLongestPathLen(vector <list <int> >, list <int>, vector <int> &);

int main() {
	int n;
	vector <list <int> > adjList;
	vector <bool> visited;
	stack <int> stk;
	list <int> topoList;
	vector <int> pathLen;

	input(adjList, n);
	init(visited, n);
	output(adjList, n);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			topoSort(adjList, n, visited, stk, i);
		}
	}
	showStack(stk);

	createTopoList(stk, topoList);
	init(pathLen, n);
	findLongestPathLen(adjList, topoList, pathLen);

	return 0;
}

void input(vector <list <int> > &adjList, int &n) {
	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	init(adjList, n);
	int src, dst;

	printf("\nEnter edges as (src, dst):-\n(Enter -1 to terminate)\n");
	scanf("%d%d", &src, &dst);

	while (src != -1 && dst != -1) {
		adjList[src].push_back(dst);
		//output(par, n);
		scanf("%d%d", &src, &dst);
	}
}

void init(vector <bool> &visited, int n) {
	for (int i = 0; i < n; i++) {
		visited.push_back(false);
	}
}

void init(vector <list <int> > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <int> tmp;
		adjList.push_back(tmp);
	}
}

void init(vector <int> &pathLen, int n) {
	for (int i = 0; i < n; i++) {
		pathLen.push_back(0);
	}
}

void output(vector <list <int> > adjList, int n) {
	printf("\nThe adjacency list is:-\n");
	for (int i = 0; i < n; i++) {
		printf("ver %d\t:\t", i);
		for (list <int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++) {
			printf("%d\t", *it);
		}
		printf("\n");
	}
}

void showStack(stack <int> stk) {
	printf("\nThe topological sorting of graph is:-\n");
	while (!stk.empty()) {
		printf("%d\t", stk.top());
		stk.pop();
	}
}

void showTopoList(list <int> topoList) {
	printf("\nTopoList is:-\n");
	for (list <int>::iterator i = topoList.begin(); i != topoList.end(); i++) {
		printf("%d\t", (*i));
	}
	cout << endl;
}

void topoSort(vector <list <int> > adjList, int n, vector <bool> &visited, stack <int> &stk, int vert) {
	visited[vert] = true;

	for (list <int>::iterator it = adjList[vert].begin(); it != adjList[vert].end(); it++) {
		if (!visited[*it]) {
			topoSort(adjList, n, visited, stk, *it);
		}
	}

	stk.push(vert);
}

void createTopoList(stack <int> stk, list <int> &topoList) {
	while (!stk.empty()) {
		topoList.push_back(stk.top());
		stk.pop();
	}
}

void findLongestPathLen(vector <list <int> > adjList, list <int> topoList, vector <int> &pathLen) {
	int longestPathLen = 0;

	for (list <int>::iterator i = topoList.begin(); i != topoList.end(); i++) {
		for (list <int>::iterator j = adjList[*i].begin(); j != adjList[*i].end(); j++) {
			if (pathLen[*j] < pathLen[*i] + 1) {
				// if graph had weighted edges, instead of 1, we would have
				// checked and updated by adding those weights
				pathLen[*j] = pathLen[*i] + 1;
				longestPathLen = max(longestPathLen, pathLen[*j]);
			}
		}
	}

	printf("\nLongest path length is %d\n", longestPathLen);
}

