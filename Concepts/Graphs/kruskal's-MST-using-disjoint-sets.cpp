// TusharRoy

/*
4
1 0 1
1 2 2
1 3 1
3 2 1
0 2 3
-1 -1 -1

6
0 1 3	0 3 1
1 2 1	1 3 3
2 3 1	2 4 5	2 5 2
3 4 6
4 5 2
-1 -1 -1

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
#include <vector>
#include <list>
#include <utility>
#include <cstdlib>
#include <cstring>

using namespace std;
struct edge {
	int src;
	int dst;
	int wgt;
};

#define MAX 100

void input(edge [MAX], int &, int &);
void init(int [MAX], int, int);
void init(vector <list <pair <int, int> > > &, int);
void showList(vector <list <pair <int, int> > >);
void showEdges(edge [MAX], int, const char *);
int comparator(const void *, const void *);
void kruskalMST(edge [MAX], int, int, int [MAX], int [MAX], vector <list <pair <int, int> > > &);
bool makeUnion(int [MAX], int [MAX], int, int);
int findSet(int [MAX], int);
void bubbleSort(edge edges[MAX], int);
void swap(edge edges[MAX], int, int);

int main() {
	int V, E;
	edge edges[MAX];
	vector <list <pair <int, int> > > adjList;
	int par[MAX], ran[MAX];

	input(edges, V, E);

	init(adjList, V);
	init(par, V, -1);
	init(ran, V, 0);

	showEdges(edges, E, "Before sorting");
	//qsort(edges, E, sizeof(edge), comparator);
	bubbleSort(edges, E);
	showEdges(edges, E, "After sorting");

	kruskalMST(edges, V, E, par, ran, adjList);
	showList(adjList);

	return 0;
}

void input(edge edges[MAX], int &V, int &E) {
	printf("Enter no of vertices:\t");
	scanf("%d", &V);

	int src, dst, wgt;

	printf("\nEnter edges as (src, dst, wgt):-\n(Enter -1 to terminate)\n");
	scanf("%d%d%d", &src, &dst, &wgt);

	E = 0;
	while (src != -1 && dst != -1) {
		edges[E].src = src;
		edges[E].dst = dst;
		edges[E].wgt = wgt;
		E++;

		scanf("%d%d%d", &src, &dst, &wgt);
	}
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void showList(vector <list <pair <int, int> > > adjList) {
	int vNo = 0;

	printf("\nThe adjacency list is:-\n");
	for (vector <list <pair <int, int> > >::iterator i = adjList.begin(); i != adjList.end(); i++, vNo++) {
		printf("%d\t:\t", vNo);
		for (list <pair <int, int> >::iterator j = (*i).begin(); j != (*i).end(); j++) {
			printf("[%d %d]\t", j -> first, j -> second);
		}
		printf("\n");
	}
}

void showEdges(edge edges[MAX], int E, const char * msg) {
	printf("\n%s, edges of graph are:-\n", msg);
	for (int i = 0; i < E; i++) {
		printf("%d -> %d [%d]\n", edges[i].src, edges[i].dst, edges[i].wgt);
	}
}

void init(int arr[MAX], int n, int val) {
	for (int i = 0; i < n; i++) {
		if (val < 0) {
			arr[i] = i;
		} else {
			arr[i] = val;
		}
	}
}

int comparator(const void * p1, const void * p2) {
	int * p1Tmp, * p2Tmp;
	int p1Val, p2Val;

	p1Tmp = (int *) malloc(sizeof(int));
	p2Tmp = (int *) malloc(sizeof(int));

	memcpy(p1Tmp, p1 + 2 * sizeof(int), sizeof(int));
	memcpy(p2Tmp, p2 + 2 * sizeof(int), sizeof(int));

	p1Val = * ((int *) p1Tmp);
	p2Val = * ((int *) p2Tmp);

	return p1Val > p2Val;
}

void bubbleSort(edge edges[MAX], int E) {
	for (int i = 0; i < E; i++) {
		for (int j = 0; j < E - i - 1; j++) {
			if (edges[j].wgt > edges[j + 1].wgt) {
				swap(edges, j, j + 1);
			}
		}
	}
}

void swap(edge edges[MAX], int pos_1, int pos_2) {
	int tmp;

	tmp = edges[pos_1].src;
	edges[pos_1].src = edges[pos_2].src;
	edges[pos_2].src = tmp;

	tmp = edges[pos_1].dst;
	edges[pos_1].dst = edges[pos_2].dst;
	edges[pos_2].dst = tmp;

	tmp = edges[pos_1].wgt;
	edges[pos_1].wgt = edges[pos_2].wgt;
	edges[pos_2].wgt = tmp;
}

void kruskalMST(edge edges[MAX], int V, int E, int par[MAX], int ran[MAX], vector <list <pair <int, int> > > &adjList) {
	int i, edgCtr;

	printf("\n");
	for (i = 0, edgCtr = 0; edgCtr < V - 1; i++) {
		int src = edges[i].src;
		int dst = edges[i].dst;
		int wgt = edges[i].wgt;

		if (makeUnion(par, ran, src, dst)) {
			adjList[src].push_back(make_pair(dst, wgt));
			//adjList[dst].push_back(make_pair(src, wgt));
			edgCtr++;
		} else {
			printf("Edge %d.%d [%d] discarded\n", src, dst, wgt);
		}
	}

	while (i < E) {
		int src = edges[i].src;
		int dst = edges[i].dst;
		int wgt = edges[i].wgt;

		printf("Edge %d.%d [%d] discarded\n", src, dst, wgt);

		i++;
	}
}

bool makeUnion(int par[MAX], int ran[MAX], int nod_1, int nod_2) {
	int par_1 = findSet(par, nod_1);
	int par_2 = findSet(par, nod_2);

	if (par_1 != par_2) {
		if (ran[par_1] == ran[par_2]) {
			ran[par_1]++;
			par[par_2] = par_1;
		} else if (ran[par_1] > ran[par_2]) {
			par[par_2] = par_1;
		} else {
			par[par_1] = par_2;
		}
		return true;
	} else {
		return false;
	}
}

int findSet(int par[MAX], int nod) {
	if (par[nod] == nod) {
		return nod;
	} else {
		par[nod] = findSet(par, par[nod]);
		return par[nod];
	}
}
