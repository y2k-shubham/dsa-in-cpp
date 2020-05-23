// TusharRoy

/*
0
6
7
0 1 5	0 3 9	0 4 2
1 2 2
2 3 3
3 5 2
5 4 3
0
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
void init(vector <pair <int, int> > &, map <int, int> &, map <int, int> &, map <int, int> &, int, int);
void init(map <int, pair <int, int> > &, int);
// output
void showAdjList(vector <list <pair <int, int> > >, const char *);
void showHeap(vector <pair <int, int> >);
void showMap(map <int, int>, const char *);
// heap + map
bool isPresent(map <int, int>, int);
void decKey(vector <pair <int, int> > &, map <int, int> &, int, int);
void swap(vector <pair <int, int> > &, int, int);
void minHeapify(vector <pair <int, int> > &, map <int, int> &, int);
// dijkstra's algorithm
void dijkstra(vector <list <pair <int, int> > >, vector <pair <int, int> > &, map <int, int> &, map <int, int> &, map <int, int> &);
int add(int, int);

int main() {
	// for graph
	vector <list <pair <int, int> > > adjList;
	int V, E;
	int src;
	// for heap + map
	vector <pair <int, int> > minHeap;
	map <int, int> vertToInd;
	// for disjkstra's algorithm
	map <int, int> vertToDst;
	map <int, int> vertToPar;

	// input
	input(adjList, V, E, src);
	printf("\n================");
	showAdjList(adjList, "original graph");

	// initialization
	init(minHeap, vertToInd, vertToDst, vertToPar, V, src);
	printf("\n=================\nBefore running Dijkstra's algorithm:-\n");
	showHeap(minHeap);
	showMap(vertToInd, "Dijsktra's vertex to index map");
	showMap(vertToDst, "Dijsktra's vertex to distance map");
	showMap(vertToPar, "Dijsktra's vertex to parent map");

	// computation
	dijkstra(adjList, minHeap, vertToInd, vertToDst, vertToPar);
	printf("\n=================\nAfter running Dijkstra's algorithm:-\n");
//	showHeap(minHeap);
	showMap(vertToInd, "Dijsktra's vertex to index map");
	showMap(vertToDst, "Dijsktra's vertex to distance map");
	showMap(vertToPar, "Dijsktra's vertex to parent map");

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

void init(vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, map <int, int> &vertToDst, map <int, int> &vertToPar, int V, int src) {
	minHeap.push_back(make_pair(src, 0));
	vertToInd.insert(make_pair(src, 0));
	vertToDst.insert(make_pair(src, 0));
	vertToPar.insert(make_pair(src, src));

	int vNo, i;
	for (vNo = 0, i = 1; vNo < V; vNo++) {
		if (vNo != src) {
			minHeap.push_back(make_pair(vNo, INT_MAX));
			vertToInd.insert(make_pair(vNo, i));
			vertToDst.insert(make_pair(vNo, INT_MAX));
			vertToPar.insert(make_pair(vNo, -1));
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
void showAdjList(vector <list <pair <int, int> > > adjList, const char * msg) {
	printf("\nAdjacency List of %s is:-\n", msg);

	int V = adjList.size();
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
	printf("Total weight of edges of %s is %d\n", msg, (totWgt / 2));
}

void showHeap(vector <pair <int, int> > minHeap) {
	int V = minHeap.size();
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

void showMap(map <int, int> intToInt, const char * msg) {
	int V = intToInt.size();
	printf("\n%s is:-\n", msg);

	cout << "Vert:\t";
	for (int i = 0; i < V; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	cout << "Ind:\t";
	for (int i = 0; i < V; i++) {
		if (intToInt[i] == INT_MAX) {
			printf("INF\t");
		} else {
			printf("%d\t", intToInt[i]);
		}
	}
	cout << endl;
}

// min-heap + map
bool isPresent(map <int, int> vertToInd, int v) {
	if (vertToInd.find(v) == vertToInd.end()) {
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

// dijkstra's algorithm
void dijkstra(vector <list <pair <int, int> > > adjList, vector <pair <int, int> > &minHeap, map <int, int> &vertToInd, map <int, int> &vertToDst, map <int, int> &vertToPar) {
	int V = adjList.size();

	while (!minHeap.empty()) {
		pair <int, int> minPair = extractMin(minHeap, vertToInd);
		int crrVert = minPair.first;
		int crrDist = minPair.second;
		vertToInd[crrVert] = -1;

		for (list <pair <int, int> >::iterator i = adjList[crrVert].begin(); i != adjList[crrVert].end(); i++) {
			int v = (*i).first;
			int newDist = add(crrDist, (*i).second);

			if (isPresent(vertToInd, v) && newDist < vertToDst[v]) {
				decKey(minHeap, vertToInd, v, newDist);
				vertToDst[v] = newDist;
				vertToPar[v] = crrVert;
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

