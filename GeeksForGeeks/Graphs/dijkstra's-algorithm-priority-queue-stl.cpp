// http://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

/*
TusharRoy Dijkstra's Example
0
6 7

0 1 5	0 3 9	0 4 2
1 2 2
2 3 3
3 5 2
5 4 3

0

=====================================

Self-Made example
0
10 13

0 1 8	0 2 3	0 5 1
1 4 7	1 5 4
2 3 9	2 5 2
4 5 3
5 7 1
6 7 7
7 8 5	7 9 5
8 2 5
-1 -1 -1

0

==========================================

Cormen 3rd edition page 635 example
0
9 14

0 1 4	0 7 8
1 2 8	1 7 11
2 3 7	2 5 4	2 8 2
3 4 9	3 5 14
4 5 10
5 6 2
6 7 1	6 8 6
7 8 7
-1 -1 -1

5

==========================================

TusharRoy Prim's MST video 1st example
0
4 5

0 1 1	0 3 3
1 2 1	1 3 3
2 3 1
-1 -1 -1

0

==========================================

TusharRoy Prim's MST video 2nd example
0
6 9

0 1 3	0 3 1
1 2 1	1 3 3
2 3 1	2 4 5	2 5 4
3 4 6
4 5 2
-1 -1 -1

0
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
#include <functional>

using namespace std;

// input
void input(vector <list <pair <int, int> > > &, int &, int &, int &);
// initialization
void init(vector <list <pair <int, int> > > &, int);
void init(map <int, int> &, int, int);
// output
void showAdjList(vector <list <pair <int, int> > >, int, const char *);
void showMap(map <int, int>, const char *, const char *);
// dijkstra's algorithm
void dijkstra(vector <list <pair <int, int> > >, int, map <int, int> &, map <int, int> &);
int add(int, int);

int main() {
	// for graph
	vector <list <pair <int, int> > > adjList;
	int V, E;
	int src;
	map <int, int> vertToPar, vertToDst;

	input(adjList, V, E, src);
	showAdjList(adjList, V, "original graph");

	init(vertToDst, V, INT_MAX);
	init(vertToPar, V, -1);

	vertToDst[src] = 0;
	vertToPar[src] = src;

	printf("===========================================\n");
	showMap(vertToDst, "Before running Dijkstra's, vertToDist map", "Dist");
	showMap(vertToPar, "Before running Dijkstra's, vertToPar map", "Par");

	dijkstra(adjList, src, vertToDst, vertToPar);

	printf("\n===========================================\n");
	showMap(vertToDst, "After running Dijkstra's, vertToDist map", "Dist");
	showMap(vertToPar, "After running Dijkstra's, vertToPar map", "Par");

	return 0;
}

// input
void input(vector <list <pair <int, int> > > &adjList, int &V, int &E, int &source) {
	int type;

	cout << "0 - Undirected Graph\n1 - Directed   Graph\nEnter your choice:\t";
	cin >> type;

	cout << "Enter no of vertices:\t";
	cin >> V;

	cout << "Enter no of edges:\t";
	cin >> E;

	int src, dst, wgt;
	init(adjList, V);

	for (int i = 1; i <= E; i++) {
		cin >> src >> dst >> wgt;

		adjList[src].push_back(make_pair(dst, wgt));
		if (type == 0) {
			adjList[dst].push_back(make_pair(src, wgt));
		}
	}

	printf("\nEnter source vertex for MST:\t");
	cin >> source;
}

// initialization
void init(vector <list <pair <int, int> > > &adjList, int V) {
	for (int i = 1; i <= V; i++) {
		list <pair <int, int> > tmpList;
		adjList.push_back(tmpList);
	}
}

void init(map <int, int> &par, int V, int val) {
	for (int i = 0; i < V; i++) {
		par.insert(make_pair(i, val));
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

void showMap(map <int, int> intToInt, const char * msg1, const char * msg2) {
	int V = intToInt.size();
	printf("\n%s is:-\n", msg1);

	cout << "Vert:\t";
	for (int i = 0; i < V; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	printf("%s:\t", msg2);
	for (int i = 0; i < V; i++) {
		if (intToInt[i] == INT_MAX) {
			printf("INF\t");
		} else {
			printf("%d\t", intToInt[i]);
		}
	}
	cout << endl;
}

// dijkstra's algorithm
void dijkstra(vector <list <pair <int, int> > > adjList, int src, map <int, int> &vertToDst, map <int, int> &vertToPar) {
	int V = adjList.size();
	// min-priority queue, here first holds distance of a vertex from MST and second holds the vertex itself
	priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > minHeap;
	minHeap.push(make_pair(0, src));

	while (!minHeap.empty()) {
		pair <int, int> minPair = minHeap.top();
		minHeap.pop();

		int crrVert = minPair.second;
		int crrDist = minPair.first;

		for (list <pair <int, int> >::iterator i = adjList[crrVert].begin(); i != adjList[crrVert].end(); i++) {
			int v = (*i).first;
			int newDist = add(crrDist, (*i).second);

			if (vertToDst[v] > newDist) {
				vertToDst[v] = newDist;
				vertToPar[v] = crrVert;
				minHeap.push(make_pair(newDist, v));
			}
		}
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return (a + b);
	}
}

