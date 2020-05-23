// http://www.geeksforgeeks.org/find-all-reachable-nodes-from-every-node-present-in-a-given-set/

/*
7
7
0 1 1
0 2 1
1 3 1
2 3 1
4 5 1
4 6 1
5 6 1
-1 -1 -1
0 1 4 -1
*/

// Basic I/O
#include <cstdio>
#include <iostream>
// for memset
#include <cstring>
// For INT_MAX
#include <climits>
// STL
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <queue>

using namespace std;

#define MAX 100

// input
void input(vector <list <pair <int, int> > > &, int &, int &);
void input(list <int> &);
// initialization
void init(vector <list <pair <int, int> > > &, int);
void init(map <int, int> &, int);
// output
void showAdjList(vector <list <pair <int, int> > >, int, const char *);
void showMap(list <int>, map <int, int>, map <int, list <int> >);
// computation
void findComps(vector <list <pair <int, int> > >, int, list <int>, map <int, int> &, map <int, list <int> > &);
list <int> bfs(vector <list <pair <int, int> > >, int, int, map <int, int> &, int);

int main() {
	// for graph
	vector <list <pair <int, int> > > adjList;
	int V, E;
	// for list of vertices
	list <int> verts;
	// for storing result
	map <int, int> vertToCompNo;
	map <int, list <int> > compNoToList;

	input(adjList, V, E);
	showAdjList(adjList, V, "original graph");

	input(verts);
	init(vertToCompNo, V);

	findComps(adjList, V, verts, vertToCompNo, compNoToList);
	showMap(verts, vertToCompNo, compNoToList);

	return 0;
}

// input
void input(vector <list <pair <int, int> > > &adjList, int &V, int &E) {
	cout << "Enter no of vertices:\t";
	cin >> V;

	cout << "Enter no of edges:\t";
	cin >> E;

	int src, dst, wgt;
	init(adjList, V);

	printf("\nEnter edges as (src, dst, wgt):-\n(-1 -1 -1 to terminate)\n");
	cin >> src >> dst >> wgt;

	while (src >= 0 && dst >= 0 && wgt >= 0) {
		adjList[src].push_back(make_pair(dst, wgt));
		adjList[dst].push_back(make_pair(src, wgt));
		cin >> src >> dst >> wgt;
	}
}

void input(list <int> &verts) {
	int v;

	printf("Enter list of vertices:-\n(-1 to terminate)\n");
	cin >> v;

	while (v >= 0) {
		verts.push_back(v);
		cin >> v;
	}
}

// initialization
void init(vector <list <pair <int, int> > > &adjList, int V) {
	for (int i = 1; i <= V; i++) {
		list <pair <int, int> > tmpList;
		adjList.push_back(tmpList);
	}
}

void init(map <int, int> &compNo, int V) {
	for (int i = 0; i < V; i++) {
		compNo.insert(make_pair(i, -1));
	}
}

// output
void showAdjList(vector <list <pair <int, int> > > adjList, int V, const char * msg) {
	printf("\nAdjacency List of %s is:-\n", msg);

	int totWgt = 0;
	for (int i = 0; i < V; i++) {
		list <pair <int, int> > crrList = adjList[i];
		cout << i << ":\t";

		for (list <pair <int, int> >::iterator j = crrList.begin(); j != crrList.end(); j++) {
			printf("[%d %d]\t", (*j).first, (*j).second);
			totWgt += (*j).second;
		}
		cout << endl;
	}
	printf("Total weight of edges of %s is %d\n\n", msg, (totWgt / 2));
}

void showMap(list <int> verts, map <int, int> vertToCompNo, map <int, list <int> > compNoToList) {
	printf("\nList of reachable vertices from each vertex is:-\n");
	for (list <int>::iterator i = verts.begin(); i != verts.end(); i++) {

		printf("%d[%d] => ", (*i), vertToCompNo[(*i)]);
		for (list <int>::iterator j = compNoToList[vertToCompNo[(*i)]].begin(); j != compNoToList[vertToCompNo[(*i)]].end(); j++) {
			printf("%d ", *j);
		}

		cout << endl;
	}
	cout << endl;
}

// computation
void findComps(vector <list <pair <int, int> > > adjList, int V, list <int> verts, map <int, int> &vertToCompNo, map <int, list <int> > &compNoToList) {
	int compCount = 0;

	for (int i = 0; i < V; i++) {
		if (vertToCompNo[i] < 0) {
			compCount++;
			list <int> vertList = bfs(adjList, V, i, vertToCompNo, compCount);
			compNoToList.insert(make_pair(compCount, vertList));
		}
	}
}

list <int> bfs(vector <list <pair <int, int> > > adjList, int V, int src, map <int, int> &vertToCompNo, int compNo) {
	queue <int> que;
	list <int> vertList;

	que.push(src);
	while (!que.empty()) {
		int v = que.front();
		que.pop();

		if (vertToCompNo[v] < 0) {
			vertToCompNo[v] = compNo;

			for (list <pair <int, int> >::iterator i = adjList[v].begin(); i != adjList[v].end(); i++) {
				que.push((*i).first);
			}

			vertList.push_back(v);
		}
	}

	return vertList;
}

