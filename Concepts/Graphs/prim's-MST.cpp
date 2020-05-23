/*
Input:
6
0 1 3	0 3 1
1 0 3	1 2 1	1 3 3
2 1 1	2 3 1	2 4 5	2 5 4
3 0 1	3 1 3	3 2 1	3 4 6
4 2 5	4 3 6	4 5 2
5 2 4	5 4 2
-1 -1 -1

*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <utility>
#include <climits>

using namespace std;
#define MAX 100

void init(vector <list <pair <int, int> > > &, int);
void init(pair <int, int> [MAX], int, map <int, int> &);
void init(map <int, int> &, int);
void input(vector <list <pair <int, int> > > &, int &, int &, int &);
void showList(vector <list <pair <int, int> > >, const char *);
void showList(list <pair <int, int> >, const char *);
void showArray(pair <int, int> [MAX], int, const char *);
void showMap(map <int, int>, int, const char *);
void minHeapify(pair <int, int> [MAX], int, map <int, int> &, int);
void buildMinHeap(pair <int, int> [MAX], int, map <int, int> &);
void heapDecreaseKey(pair <int, int> [MAX], int, map <int, int> &, int, int);
void swap(pair <int, int> [MAX], int, int, map <int, int> &);
void store(pair <int, int> [MAX], map <int, int> &, int, int, int);
void primMST(vector <list <pair <int, int> > >, int, int, pair <int, int> [MAX], int &, map <int, int> &, map <int, int> &, list <pair <int, int> > &);

int main() {
	// heap variables
	pair <int, int> heap[MAX];
	int size;
	map <int, int> pos;
	// graph variables
	vector <list <pair <int, int> > > adjList;
	int V, E, src;
	// MST variables
	list <pair <int, int> > edgesMST;
	map <int, int> parMST;

	// input
	input(adjList, V, E, src);

	printf("\n====================\n");
	showList(adjList, "after input");

	// initialization
	size = V;
	init(heap, size, pos);
	init(parMST, V);
	store(heap, pos, src, src, 0);

	// building heap
	buildMinHeap(heap, size, pos);
	showArray(heap, size, "after build heap");

	// Prim's MST
	primMST(adjList, V, E, heap, size, pos, parMST, edgesMST);

	// output
	showMap(parMST, V, "after building MST");
	showList(edgesMST, "list of edges included in MST");

	return 0;
}

// input and initialize
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

	printf("\nEnter the source vertex:\t");
	scanf("%d", &source);
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void init(pair <int, int> arr[MAX], int n, map <int, int> &pos) {
	for (int i = 0; i < n; i++) {
		store(arr, pos, i, i, INT_MAX);
	}
}

void init(map <int, int> &parMST, int V) {
	for (int i = 0; i < V; i++) {
		parMST.insert(make_pair(i, i));
	}
}

// show
void showList(vector <list <pair <int, int> > > adjList, const char * msg) {
	int vNo = 0;

	printf("\nThe adjacency list %s is:-\n", msg);
	for (vector <list <pair <int, int> > >::iterator i = adjList.begin(); i != adjList.end(); i++, vNo++) {
		printf("%d\t:\t", vNo);
		for (list <pair <int, int> >::iterator j = (*i).begin(); j != (*i).end(); j++) {
			printf("[%d %d]\t", j -> first, j -> second);
		}
		printf("\n");
	}
}

void showMap(map <int, int> parMST, int V, const char * msg) {
	printf("\nThe parent map %s is:-\n", msg);
	printf("Node\tParent\n");
	for (map <int, int>::iterator it = parMST.begin(); it != parMST.end(); it++) {
		printf("%d\t%d\n", it -> first, it -> second);
	}
	printf("\n");
}

void showList(list <pair <int, int> > edgesMST, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (list <pair <int, int> >::iterator it = edgesMST.begin(); it != edgesMST.end(); it++) {
		printf("[%d->%d]\t", it -> first, it -> second);
	}
	printf("\n");
}

void showArray(pair <int, int> arr[MAX], int n, const char * msg) {
	printf("\nAfter %s, the heap[] array is:-\n", msg);

	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i].first);
	}
	printf("\n");

	for (int i = 0; i < n; i++) {
		if (arr[i].second == INT_MAX) {
			printf("INF\t");
		} else {
			printf("%d\t", arr[i].second);
		}
	}
	printf("\n");
}

// heap methods
void minHeapify(pair <int, int> heap[MAX], int size, map <int, int> &pos, int crrInd) {
	int lCInd = (crrInd * 2) + 1;
	int rCInd = (crrInd * 2) + 2;

	int minInd = crrInd;
	if ((rCInd < size) && (heap[rCInd].second < heap[crrInd].second)) {
		minInd = rCInd;
	}
	if ((lCInd < size) && (heap[lCInd].second < heap[minInd].second)) {
		minInd = lCInd;
	}

	if (minInd != crrInd) {
		swap(heap, crrInd, minInd, pos);
		minHeapify(heap, size, pos, minInd);
	}
}

void buildMinHeap(pair <int, int> heap[MAX], int size, map <int, int> &pos) {
	for (int i = size / 2; i >= 0; i--) {
		minHeapify(heap, size, pos, i);
	}
}

int heapExtractMin(pair <int, int> heap[MAX], int &size, map <int, int> &pos) {
	int minDistNode = heap[0].first;
//	printf("minDistNode = %d\tminDist = %d\n", minDistNode, heap[0].second);

	swap(heap, 0, size - 1, pos);
	size--;
	pos[heap[size].first] = -1;

	minHeapify(heap, size, pos, 0);
//	showArray(heap, size, "after removing node");

//	printf("going to return minDistNode = %d\n", minDistNode);
	return minDistNode;
}

void heapDecreaseKey(pair <int, int> heap[MAX], int size, map <int, int> &pos, int crrInd, int newKey) {
//	heap[crrInd].second = newKey;
	store(heap, pos, crrInd, heap[crrInd].first, newKey);

	int parInd = (crrInd - 1) / 2;
	while ((crrInd >= 0) && (heap[parInd].second > heap[crrInd].second)) {
		swap(heap, parInd, crrInd, pos);

		crrInd = parInd;
		parInd = (crrInd - 1) / 2;
	}
}

void swap(pair <int, int> heap[MAX], int pos_1, int pos_2, map <int, int> &pos) {
	int tmpNode = heap[pos_1].first;
	int tmpDist = heap[pos_1].second;

	store(heap, pos, pos_1, heap[pos_2].first, heap[pos_2].second);
	store(heap, pos, pos_2, tmpNode, tmpDist);
}

void store(pair <int, int> heap[MAX], map <int, int> &pos, int ind, int node, int dist) {
	heap[ind].first = node;
	heap[ind].second = dist;
	pos[node] = ind;
}

// Prim's MST
void primMST(vector <list <pair <int, int> > > adjList, int V, int E, pair <int, int> heap[MAX], int &size, map <int, int> &pos, map <int, int> &parMST, list <pair <int, int> > &edgesMST) {
	while (size > 0) {
		int crrNode = heapExtractMin(heap, size, pos);
//		printf("\nNode %d extracted from heap", crrNode);
//		showArray(heap, V, "after extracting node");

		if (size < V - 1) {
			edgesMST.push_back(make_pair(parMST[crrNode], crrNode));
//			printf("Edge %d -> %d added to MST\n", parMST[crrNode], crrNode);
		}

		for (list <pair <int, int> >::iterator it = adjList[crrNode].begin(); it != adjList[crrNode].end(); it++) {
			if ((pos[it -> first] != -1) && (heap[pos[it -> first]].second > it -> second)) {
//				if (heap[pos[it -> first]].second != INT_MAX) {
//					printf("\ndistance of node %d decreased from %d to %d", it -> first, heap[pos[it -> first]].second, it -> second);
//				} else {
//					printf("\ndistance of node %d decreased from INF to %d", it -> first, it -> second);
//				}
				parMST[it -> first] = crrNode;
				heapDecreaseKey(heap, size, pos, pos[it -> first], it -> second);

//				showArray(heap, V, "after updating distance");
			}
		}
	}
}
