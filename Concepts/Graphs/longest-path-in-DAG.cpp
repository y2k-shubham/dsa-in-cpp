// taught by professor Madhavan Mukund of Chennai Mathematical Institute
// https://www.youtube.com/watch?v=nu88oy8U0Vo

/*
Input:
8
0 2 1	0 3 1	0 4 1
1 2 1	1 7 1
2 5 1
3 5 1	3 7 1
4 7 1
5 6 1
6 7 1
-1 -1 -1

*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

void input(vector <list <pair <int, int> > > &, int &, int &);
void init(vector <list <pair <int, int> > > &, int);
void init(vector <int> &, int);
void showList(vector <list <pair <int, int> > >, const char *);
void showList(vector <int>, int, const char *, const char *);
void calcIndegrees(vector <list <pair <int, int> > >, int, vector <int> &);
void topoSort(vector <list <pair <int, int> > >, int, vector <int>, vector <int>&);

int main() {
	int V, E;
	vector <list <pair <int, int> > > adjList;
	vector <int> indegree;
	vector <int> longPath;

	input(adjList, V, E);
	showList(adjList, "adjacency list after input");

	init(indegree, V);
	init(longPath, V);

	calcIndegrees(adjList, V, indegree);
	showList(indegree, V, "indegrees of vertices", "indeg");

	topoSort(adjList, V, indegree, longPath);
	showList(longPath, V, "longest path to vertices", "path");

	return 0;
}

void input(vector <list <pair <int, int> > > &adjList, int &V, int &E) {
	printf("Enter no of vertices:\t");
	scanf("%d", &V);

	init(adjList, V);
	int src, dst, wgt;

	printf("\nEnter edges as (src, dst, wgt):-\n(Enter -1 to terminate)\n");
	scanf("%d%d%d", &src, &dst, &wgt);

	E = 0;
	while (src != -1 && dst != -1) {
		++E;
		adjList[src].push_back(make_pair(dst, wgt));
		//output(par, n);
		scanf("%d%d%d", &src, &dst, &wgt);
	}
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void init(vector <int> &indegree, int V) {
	for (int i = 0; i < V; i++) {
		indegree.push_back(0);
	}
}

void showList(vector <list <pair <int, int> > > adjList, const char * msg) {
	int vNo = 0;

	printf("\nThe %s is:-\n", msg);
	for (vector <list <pair <int, int> > >::iterator i = adjList.begin(); i != adjList.end(); i++, vNo++) {
		printf("%d\t:\t", vNo);
		for (list <pair <int, int> >::iterator j = (*i).begin(); j != (*i).end(); j++) {
			printf("[%d %d]\t", j -> first, j -> second);
		}
		printf("\n");
	}
}

void showList(vector <int> longPath, int V, const char * msg, const char * name) {
	printf("\nLongest %s are:-\n", msg);

	printf("Vert:\t");
	for (int i = 0; i < V; i++) {
		printf("%d\t", i);
	}
	printf("\n");

	printf("%s:\t", name);
	for (int i = 0; i < V; i++) {
		printf("%d\t", longPath[i]);
	}
	printf("\n");
}

void calcIndegrees(vector <list <pair <int, int> > > adjList, int V, vector <int> &indegree) {
	for (vector <list <pair <int, int> > >::iterator i = adjList.begin(); i != adjList.end(); i++) {
		for (list <pair <int, int> >::iterator j = (*i).begin(); j != (*i).end(); j++) {
			indegree[j -> first]++;
		}
	}
}

void topoSort(vector <list <pair <int, int> > > adjList, int V, vector <int> indegree, vector <int> &longPath) {
	queue <int> topoOrder;
	bool done[V];

	// enqueue vertices having indegree 0
	for (int i = 0; i < V; i++) {
		if (indegree[i] == 0) {
			topoOrder.push(i);
		}
		done[i] = false;
	}

	while (!topoOrder.empty()) {
		// dequeue a vertex and mark it as done
		int crrVert = topoOrder.front();
		topoOrder.pop();
		done[crrVert] = true;

		// iterate over it's adjacent vertices (to whom our crrVert has outgoing edges)
		for (list <pair <int, int> >::iterator it = adjList[crrVert].begin(); it != adjList[crrVert].end(); it++) {
			// decrement indegree of each neighbor vertex
			indegree[it -> first]--;
			if (indegree[it -> first] == 0) {
				// if indegree becomes zero, enqueue the neighbor vertex
				topoOrder.push(it -> first);
			}

			// if neighbor is not done, then update it's longest path, if possible
			if (!done[it -> first]) {
				longPath[it -> first] = max(longPath[it -> first], (longPath[crrVert] + it -> second));
			}
		}
	}
}


