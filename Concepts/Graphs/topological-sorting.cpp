// www.geeksforgeeks.org/topological-sorting/
// TusharRoy: Topological Sorting Graph ALgorithm

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

void input(vector <list <int> > &, int &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
void output(vector <list <int> >, int);
void topoSort(vector <list <int> >, int, vector <bool> &, stack <int> &, int);
void showStack(stack <int>);

int main() {
	int n;
	vector <list <int> > adjList;
	vector <bool> visited;
	stack <int> stk;

	input(adjList, n);
	init(visited, n);
	output(adjList, n);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			topoSort(adjList, n, visited, stk, i);
		}
	}
	showStack(stk);

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

void topoSort(vector <list <int> > adjList, int n, vector <bool> &visited, stack <int> &stk, int vert) {
	visited[vert] = true;

	for (list <int>::iterator it = adjList[vert].begin(); it != adjList[vert].end(); it++) {
		if (!visited[*it]) {
			topoSort(adjList, n, visited, stk, *it);
		}
	}

	stk.push(vert);
}

void showStack(stack <int> stk) {
	printf("\nThe topological sorting of graph is:-\n");
	while (!stk.empty()) {
		printf("%d\t", stk.top());
		stk.pop();
	}
}

