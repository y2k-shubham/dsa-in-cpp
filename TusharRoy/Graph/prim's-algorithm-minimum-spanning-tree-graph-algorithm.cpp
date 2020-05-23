// TusharRoy

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
// For INT_MAX
#include <climits>
// STL
#include <utility>
#include <vector>
#include <list>
#include <map>

using namespace std;

#define MAX 100
#define lC(i) (2 * i + 1)
#define rC(i) (2 * i + 2)
#define par(i)	((i - 1) / 2)

// input
void input(vector <list <pair <int, int> > > &, int &, int &, int &);
// initialization
void init(vector <list <pair <int, int> > > &, int);
void init(vector <pair <int, int> > &, map <int, int> &, int, int);
void init(map <int, pair <int, int> > &, int);
// output
void showAdjList(vector <list <pair <int, int> > >, int, const char *);
void showHeap(vector <pair <int, int> >, int);
void showMap(map <int, int>, int);
// heap + map
bool isPresent(map <int, int>, int);
void decKey(vector <pair <int, int> > &, map <int, int> &, int, int);
void swap(vector <pair <int, int> > &, int, int);
void minHeapify(vector <pair <int, int> > &, map <int, int> &, int);
// prim's algorithm
void primsMST(vector <list <pair <int, int> > >, int, int, int, vector <pair <int, int> > &, map <int, int> &, vector <list <pair <int, int> > > &);

int main() {
	// for graph
	vector <list <pair <int, int> > > adjList, MSTList;
	int V, E;
	int src;

	// for heap + map
	vector <pair <int, int> > minHeap;
	map <int, int> vertToInd;

	input(adjList, V, E, src);
	showAdjList(adjList, V, "original graph");

	init(minHeap, vertToInd, V, src);
//	showHeap(minHeap, V);
//	showMap(vertToInd, V);

	init(MSTList, V);
	primsMST(adjList, V, E, src, minHeap, vertToInd, MSTList);
	showAdjList(MSTList, V, "MST");

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

void init(vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, int V, int src) {
	minHeap.push_back(make_pair(src, 0));
	vertToInd.insert(make_pair(src, 0));

	int vNo, i;
	for (vNo = 0, i = 1; vNo < V; vNo++) {
		if (vNo != src) {
			minHeap.push_back(make_pair(vNo, INT_MAX));
			vertToInd.insert(make_pair(vNo, i));
			i++;
		}
	}
}

void init(map <int, pair <int, int> > &parent, int V) {
	for (int i = 0; i < V; i++) {
		parent.insert(make_pair(i, make_pair(-1, INT_MAX)));
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

void showHeap(vector <pair <int, int> > minHeap, int V) {
	printf("\nMin-Heap vector is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < V; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Vert:\t";
	for (int i = 0; i < V; i++) {
		printf("%d\t", minHeap[i].first);
	}
	cout << endl;

	cout << "Dist:\t";
	for (int i = 0; i < V; i++) {
		if (minHeap[i].second < INT_MAX) {
			printf("%d\t", minHeap[i].second);
		} else {
			printf("INF\t");
		}
	}
	cout << endl << endl;
}

void showMap(map <int, int> vertToInd, int V) {
	printf("\nVertex to Index Map is:-\n");

	cout << "Vert:\t";
	for (int i = 0; i < V; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	cout << "Ind:\t";
	for (int i = 0; i < V; i++) {
		printf("%d\t", vertToInd[i]);
	}
	cout << endl;
}

// min-heap + map
bool isPresent(map <int, int> vertToInd, int V) {
	if (vertToInd.find(V) == vertToInd.end()) {
		return false;
	} else {
		return true;
	}
}

void decKey(vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, int vert, int newDist) {
	minHeap[vertToInd[vert]].second = newDist;

	for (int v = vertToInd[vert]; par(v) != v; ) {
		if (minHeap[v].second < minHeap[par(v)].second) {
			vertToInd[minHeap[v].first] = par(v);
			vertToInd[minHeap[par(v)].first] = v;

			swap(minHeap, v, par(v));
			v = par(v);
		} else {
			break;
		}
	}
}

void swap(vector <pair <int, int> > &minHeap, int p1, int p2) {
	pair <int, int> tmp = minHeap[p1];
	minHeap[p1] = minHeap[p2];
	minHeap[p2] = tmp;
}

void minHeapify(vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, int pos) {
	int minPos;

	if (lC(pos) < minHeap.size() && minHeap[lC(pos)].second < minHeap[pos].second) {
		minPos = lC(pos);
	} else {
		minPos = pos;
	}

	if (rC(pos) < minHeap.size() && minHeap[rC(pos)].second < minHeap[minPos].second) {
		minPos = rC(pos);
	}

	if (minPos != pos) {
		vertToInd[minHeap[pos].first] = minPos;
		vertToInd[minHeap[minPos].first] = pos;

		swap(minHeap, pos, minPos);
		minHeapify(minHeap, vertToInd, minPos);
	}
}

pair <int, int> extractMin(vector <pair <int, int> > &minHeap, map <int, int> &vertToInd) {
	pair <int, int> minPair = minHeap[0];
	int lPos = minHeap.size() - 1;

	vertToInd[minHeap[lPos].first] = 0;
	swap(minHeap, 0, lPos);

	minHeap.resize(lPos);
	vertToInd.erase(minPair.first);

	minHeapify(minHeap, vertToInd, 0);
	return minPair;
}

// Prim's
void primsMST(vector <list <pair <int, int> > > adjList, int V, int E, int src, vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, vector <list <pair <int, int> > > &MSTList) {
	map <int, pair <int, int> > parent;

	init(MSTList, V);
	init(parent, V);

	while (!minHeap.empty()) {
		pair <int, int> minPair = extractMin(minHeap, vertToInd);

		if (parent[minPair.first].first >= 0) {
			MSTList[minPair.first].push_back(make_pair(parent[minPair.first].first, parent[minPair.first].second));
			MSTList[parent[minPair.first].first].push_back(make_pair(minPair.first, parent[minPair.first].second));
		}

		for (list <pair <int, int> >::iterator i = adjList[minPair.first].begin(); i != adjList[minPair.first].end(); i++) {
			if (isPresent(vertToInd, (*i).first) && (*i).second < minHeap[vertToInd[(*i).first]].second) {
				decKey(minHeap, vertToInd, (*i).first, (*i).second);
				parent[(*i).first].first = minPair.first;
				parent[(*i).first].second = (*i).second;
			}
		}
	}
}

