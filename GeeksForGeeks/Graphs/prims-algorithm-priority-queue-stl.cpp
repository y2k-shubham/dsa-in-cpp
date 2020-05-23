// http://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/

/*
Self-Made example
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
Total weight of all edges in original graph: 60
Total weight of all edges in MST      graph: 37

Cormen 3rd edition page 635 example
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
Total weight of all edges in original graph: 93
Total weight of all edges in MST      graph: 37

TusharRoy Prim's MST video 1st example
4 5

0 1 1	0 3 3
1 2 1	1 3 3
2 3 1
-1 -1 -1

0
Total weight of all edges in original graph: 9
Total weight of all edges in MST      graph: 3

TusharRoy Prim's MST video 2nd example
6 9

0 1 3	0 3 1
1 2 1	1 3 3
2 3 1	2 4 5	2 5 4
3 4 6
4 5 2
-1 -1 -1

0
Total weight of all edges in original graph: 26
Total weight of all edges in MST      graph: 9
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

#define MAX 100

// input
void input(vector <list <pair <int, int> > > &, int &, int &, int &);
// initialization
void init(vector <list <pair <int, int> > > &, int);
void init(map <int, pair <int, int> > &, int);
// output
void showAdjList(vector <list <pair <int, int> > >, int, const char *);
// prim's MST
void primsMST(vector <list <pair <int, int> > >, int, int, int, vector <list <pair <int, int> > > &);

int main() {
	// for graph
	vector <list <pair <int, int> > > adjList, MSTList;
	int V, E;
	int src;

	input(adjList, V, E, src);
	showAdjList(adjList, V, "original graph");

	primsMST(adjList, V, E, src, MSTList);
	showAdjList(MSTList, V, "MST graph");

	return 0;
}

// input
void input(vector <list <pair <int, int> > > &adjList, int &V, int &E, int &source) {
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

void init(map <int, pair <int, int> > &par, int V) {
	for (int i = 0; i < V; i++) {
		par.insert(make_pair(i, make_pair(i, INT_MAX)));
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

// prims's algorithm
void primsMST(vector <list <pair <int, int> > > adjList, int V, int E, int src, vector <list <pair <int, int> > > &MSTList) {
	// min-priority queue, here first holds distance of a vertex from MST and second holds the vertex itself
	priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > minHeap;
	// vector to indicate whether or not a vertex has been included in MST
	bool inMST[V];
	// map that stores information of parent vertex (first) and distance to it (second)
	map <int, pair <int, int> > par;

	// initialize data structures
	init(MSTList, V);
	init(par, V);
	memset(inMST, false, V * sizeof(bool));

	// put source vertex in map with distance zero and mark distance to it's parent as 0
	minHeap.push(make_pair(0, src));
	par[src].second = 0;

	// iterate as long as minHeap isn't empty
	while (!minHeap.empty()) {
		// take out that vertex from minHeap which is closest to current MST
		pair <int, int> minPair = minHeap.top();
		int v = minPair.second;
		minHeap.pop();

		// mark this vertex as included in MST
		inMST[v] = true;

		// iterate over vertices adjacent to this vertex
		for (list <pair <int, int> >::iterator i = adjList[v].begin(); i != adjList[v].end(); i++) {
			// read and adjacent vertex (note that vertex is first and distance is second)
			int vert = (*i).first;
			int wgt = (*i).second;

			// if vert hasn't already been included in MST and it's distance is lesser than current known distance
			if ((inMST[vert] == false) && (wgt < par[vert].second)) {
				// update weight and parent (note that vertex is first and distance is second)
				par[vert].first = v;
				par[vert].second = wgt;

				// put it into minHeap (note that distance is first and vertex is second)
				minHeap.push(make_pair(wgt, vert));
			}
		}
	}

	// include parent edges to all vertices (except source) into the MST
	for (map <int, pair <int, int> >::iterator i = par.begin(); i != par.end(); i++) {
		int v = (*i).first;
		int p = ((*i).second).first;
		int w = ((*i).second).second;

		MSTList[v].push_back(make_pair(p, w));
		MSTList[p].push_back(make_pair(v, w));
	}
}

