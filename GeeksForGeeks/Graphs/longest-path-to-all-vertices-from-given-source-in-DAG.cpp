// http://www.geeksforgeeks.org/find-longest-path-directed-acyclic-graph/

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

Input:
6
0 1 5	0 2 3
1 2 2	1 3 6
2 3 7	2 4 4	2 5 2
3 4 -1	3 5 1
4 5 -2
-1 -1 -1
Src = 1
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <utility>
#include <climits>
#include <cmath>

using namespace std;

void input(vector <list <pair <int, int> > > &, int &, int &, int &);
void init(vector <list <pair <int, int> > > &, int);
void init(vector <int> &, int, int);
void showList(vector <list <pair <int, int> > >, const char *);
void showList(vector <int>, int, const char *, const char *);
void showQueue(queue <int>, const char *);
void topoSort(vector <list <pair <int, int> > >, int, vector <int>, queue <int> &);
void calcIndegrees(vector <list <pair <int, int> > >, int, vector <int> &);
void findLongPath(vector <list <pair <int, int> > >, int, queue <int>, vector <int> &, vector <int> &, int);
int add(int, int);

int main() {
	int V, E, src;
	vector <list <pair <int, int> > > adjList;
	vector <int> indegree;
	queue <int> topoOrder;
	vector <int> longPath, parent;

	input(adjList, V, E, src);
	showList(adjList, "adjacency list after input");

	init(indegree, V, 0);
	init(parent, V, -1);
	init(longPath, V, INT_MIN);

	calcIndegrees(adjList, V, indegree);
	showList(indegree, V, "indegrees of vertices", "indeg");

	topoSort(adjList, V, indegree, topoOrder);
	showQueue(topoOrder, "topological order");

	findLongPath(adjList, V, topoOrder, longPath, parent, src);
	showList(parent, V, "parent of various vertices", "par");
	showList(longPath, V, "longest path to various nodes", "path");

	return 0;
}

void input(vector <list <pair <int, int> > > &adjList, int &V, int &E, int &source) {
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

	printf("\nEnter source vertex:\t");
	scanf("%d", &source);
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void init(vector <int> &vec, int V, int val) {
	for (int i = 0; i < V; i++) {
		vec.push_back(val);
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
	printf("\nThe %s are:-\n", msg);

	printf("Vert:\t");
	for (int i = 0; i < V; i++) {
		printf("%d\t", i);
	}
	printf("\n");

	printf("%s:\t", name);
	for (int i = 0; i < V; i++) {
		if (longPath[i] == INT_MAX) {
			printf("INF\t");
		} else if (longPath[i] == INT_MIN) {
			printf("INF\t");
		} else {
			printf("%d\t", longPath[i]);
		}
	}
	printf("\n");
}

void showQueue(queue <int> topoOrder, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	while (!topoOrder.empty()) {
		printf("%d ", topoOrder.front());
		topoOrder.pop();
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

void topoSort(vector <list <pair <int, int> > > adjList, int V, vector <int> indegree, queue <int> &topoOrder) {
	queue <int> topoOrderTmp;
	bool ordered[V];

	for (int i = 0; i < V; i++) {
		if (indegree[i] == 0) {
			topoOrder.push(i);
			topoOrderTmp.push(i);
			ordered[i] = true;
		} else {
			ordered[i] = false;
		}
	}

	while (!topoOrderTmp.empty()) {
		int crrVert = topoOrderTmp.front();
		topoOrderTmp.pop();

		for (list <pair <int, int> >::iterator it = adjList[crrVert].begin(); it != adjList[crrVert].end(); it++) {
			if (!ordered[it -> first]) {
				indegree[it -> first]--;
				if (indegree[it -> first] == 0) {
					topoOrder.push(it -> first);
					topoOrderTmp.push(it -> first);
					ordered[it -> first] = true;
				}
			}
		}
	}
}

void findLongPath(vector <list <pair <int, int> > > adjList, int V, queue <int> topoOrder, vector <int> &longPath, vector <int> &par, int src) {
	// remove all vertices before source vertex from que
	// not really required
	while (topoOrder.front() != src) {
		topoOrder.pop();
	}

	longPath[src] = 0;
	par[src] = src;
	while (!topoOrder.empty()) {
		int crrVert = topoOrder.front();
		topoOrder.pop();

//		if (longPath[crrVert] != INT_MIN) {
//			printf("\nDequeued\tVert %d\tPath = %d\tPar = %d\n", crrVert, longPath[crrVert], par[crrVert]);
//		} else {
//			printf("\nDequeued\tVert %d\tPath = NIFN\tPar = %d\n", crrVert, par[crrVert]);
//		}

		for (list <pair <int, int> >::iterator it = adjList[crrVert].begin(); it != adjList[crrVert].end(); it++) {
			if (longPath[it -> first] < add(longPath[crrVert], it -> second)) {
//				int origPath = longPath[it -> first];
//				int origPar = par[it -> first];

				longPath[it -> first] = add(longPath[crrVert], it -> second);
				par[it -> first] = crrVert;

				//				if (origPath != INT_MIN) {
//					printf("Updated Vertex %d\tfrom\tPath %d\tPar %d\tto\tPath %d\tPar %d\n", it -> first, origPath, origPar, longPath[it -> first], par[it -> first]);
//				} else {
//					printf("Updated Vertex %d\tfrom\tPath NINF\tPar %d\tto\tPath %d\tPar %d\n", it -> first, origPar, longPath[it -> first], par[it -> first]);
//				}
			}
		}
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else if (a == INT_MIN || b == INT_MIN) {
		return INT_MIN;
	} else {
		return a + b;
	}
}
