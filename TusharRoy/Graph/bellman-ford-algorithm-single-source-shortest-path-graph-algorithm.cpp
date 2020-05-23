// TusharRoy

/*
TusharRoy Bellman-Ford Example
0
6 7

0 1 5	0 3 9	0 4 2
1 2 2
2 3 3
3 5 2
5 4 3

0
*/

// Basic IO
#include <cstdio>
#include <iostream>
// For storing shortest distance and parent of each vertex
#include <map>
// For adjacency list
#include <vector>
#include <list>
#include <utility>
// For using INT_MAX
#include <climits>

using namespace std;

// input
void input(vector <list <pair <int, int> > > &, int &, int &, int &);
// initialization
void init(vector <list <pair <int, int> > > &, int);
void init(map <int, int> &, int, int);
// output
void showAdjList(vector <list <pair <int, int> > >, int, const char *);
void showMap(map <int, int>, const char *, const char *);
// bellman ford algorithm
bool bellmanFord(vector <list <pair <int, int> > >, map <int, int> &, map <int, int> &);
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
	showMap(vertToDst, "Before running Bellman-Ford, vertToDist map", "Dist");
	showMap(vertToPar, "Before running Bellman-Ford, vertToPar map", "Par");

	printf("\n===========================================\n");
	if (bellmanFord(adjList, vertToDst, vertToPar)) {
		showMap(vertToDst, "After running Bellman-Ford, vertToDist map", "Dist");
		showMap(vertToPar, "After running Bellman-Ford, vertToPar map", "Par");
	}

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

// Bellman-Ford algorithm
bool bellmanFord(vector <list <pair <int, int> > > adjList, map <int, int> &vertToDst, map <int, int> &vertToPar) {
	int V = adjList.size();

	// run this loop V times (V-1 times for update and one more time to check for -ve cycle)
	for (int i = 1; i <= V; i++) {
		bool noChange = true;

		// scan through all edges of graph (in any order) and perform updates as needed
		for (int j = 0; j < V; j++) {
			for (list <pair <int, int> >::iterator k = adjList[j].begin(); k != adjList[j].end(); k++) {
				int v = (*k).first;
				int d = (*k).second;

				if (add(vertToDst[j], d) < vertToDst[v]) {
					noChange = false;
					vertToDst[v] = add(vertToDst[j], d);
					vertToPar[v] = j;
				}
			}
		}

		if (noChange) {
			// if there's been no change, then shortest paths have already been found
			return true;
		} else if (i == V) {
			// if there's a change in last (V'th) iteration, it means -ve cycle is present
			cout << "-ve cycle detected in graph" << endl;
			return false;
		}
	}

	return true;
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return (a + b);
	}
}

