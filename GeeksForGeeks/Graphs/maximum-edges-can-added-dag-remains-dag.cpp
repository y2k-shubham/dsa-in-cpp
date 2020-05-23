// http://www.geeksforgeeks.org/maximum-edges-can-added-dag-remains-dag/
// actually, should use adjacency matrix instead of adjacency list for this question

// www.geeksforgeeks.org/topological-sorting/
// TusharRoy: Topological Sorting Graph ALgorithm

/*
6
2 3
3 1
4 0		4 1
5 0		5 2
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <iterator>		// used for STL next(iterator, count) method
#include <stack>
#include <utility>

using namespace std;

// input and initialization
void input(vector <list <int> > &, int &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
// topological sorting
void topoSort(vector <list <int> >, int, vector <bool> &, stack <int> &, int);
void getTopoOrderList(stack <int>, list <int> &);
// output
void output(vector <list <int> >, int);
void showStack(stack <int>);
void showTopoOrderList(list <int>);
void showPossibleNewEdges(list <pair <int, int> >);
// finding possible new edges using topological order
void findPossibleNewEdges(vector <list <int> >, list <int>, list <pair <int, int> > &);
bool isEdgePresent(vector <list <int> >, int, int);

int main() {
	int n;
	vector <list <int> > adjList;
	vector <bool> visited;
	stack <int> stk;
	list <int> topoOrderList;
	list <pair <int, int> > newEdgeList;

	input(adjList, n);
	init(visited, n);
	output(adjList, n);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			topoSort(adjList, n, visited, stk, i);
		}
	}
	showStack(stk);

	getTopoOrderList(stk, topoOrderList);
	showTopoOrderList(topoOrderList);

	findPossibleNewEdges(adjList, topoOrderList, newEdgeList);
	showPossibleNewEdges(newEdgeList);

	return 0;
}

// input and initialization
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

// topological sorting
void topoSort(vector <list <int> > adjList, int n, vector <bool> &visited, stack <int> &stk, int vert) {
	visited[vert] = true;

	for (list <int>::iterator it = adjList[vert].begin(); it != adjList[vert].end(); it++) {
		if (!visited[*it]) {
			topoSort(adjList, n, visited, stk, *it);
		}
	}

	stk.push(vert);
}

void getTopoOrderList(stack <int> stk, list <int> &topoOrderList) {
	while (!stk.empty()) {
		int v = stk.top();
		stk.pop();

		topoOrderList.push_back(v);
	}
}

// output
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
	cout << endl;
}

void showTopoOrderList(list <int> topoOrderList) {
	printf("\nTopological Order list of vertices is:-\n");
	for (list <int>::iterator i = topoOrderList.begin(); i != topoOrderList.end(); i++) {
		printf("%d\t", (*i));
	}
	cout << endl;
}

void showPossibleNewEdges(list <pair <int, int> > newEdgeList) {
	printf("\nList of possible new edges that can be added without creating a cycle is:-\n");
	for (list <pair <int, int> >::iterator i = newEdgeList.begin(); i != newEdgeList.end(); i++) {
		printf("%d -> %d\n", (*i).first, (*i).second);
	}
	cout << "No of possible new edges is " << newEdgeList.size() << endl;
	cout << endl;
}

// finding possible new edges using topological order
void findPossibleNewEdges(vector <list <int> > adjList, list <int> topoOrderList, list <pair <int, int> > &newEdgeList) {
	for (list <int>::iterator i = topoOrderList.begin(); i != topoOrderList.end(); i++) {
		for (list <int>::iterator j = next(i, 1); j != topoOrderList.end(); j++) {
			if (!isEdgePresent(adjList, *i, *j)) {
				newEdgeList.push_back({*i, *j});
			}
		}
	}
}

bool isEdgePresent(vector <list <int> > adjList, int src, int dst) {
	for (list <int>::iterator i = adjList[src].begin(); i != adjList[src].end(); i++) {
		if ((*i) == dst) {
			return true;
		}
	}

	return false;
}

