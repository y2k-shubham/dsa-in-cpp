// TusharRoy
// Uses STL list::sort

/*
4
5
0 1 1	0 2 3
1 2 1	1 3 1
2 3 1

6
9
0 1 3	0 3 1
1 2 1	1 3 3
2 3 1	2 4 5	2 5 4
3 4 6
4 5 2
*/

#include <iostream>
#include <cstdio>
#include <utility>
#include <vector>
#include <list>

struct edge {
	int nod_1;
	int nod_2;
	int wgt;
};

using namespace std;

void input(int &, list <edge> &);
void init(vector <pair <int, int> > &, int);
bool comparator(const edge &, const edge &);
void showList(vector <pair <int, int> >, int);
void showList(list <edge>, const char *);
void kruskalMST(vector <pair <int, int> > &, int, list <edge>, list <edge> &);
int findSet(vector <pair <int, int> >, int);

int main() {
	// declaration
	vector <pair <int, int> > nodeList;
	int n;
	list <edge> edgeList;
	list <edge> MSTList;

	// input
	input(n, edgeList);

	// initialization of nodes
	init(nodeList, n);
	showList(nodeList, n);

	// sorting of edges by length
	edgeList.sort(comparator);
	showList(edgeList, "edges sorted by weight");

	// determination of MST and displaying the solution
	kruskalMST(nodeList, n, edgeList, MSTList);
	showList(MSTList, "edges of MST");

	return 0;
}

// input and initialization
void input(int &n, list <edge> &edgeList) {
	// input no of nodes
	cout << "Enter no of nodes:\t";
	cin >> n;

	// input all edges
	int e;

	cout << "Enter no of edges:\t";
	cin >> e;

	cout << "Enter edges as (nod_1, nod_2, wgt):-\n";
	for (int i = 1; i <= e; i++) {
		int nod_1, nod_2, wgt;
		cin >> nod_1 >> nod_2 >> wgt;

		edge tmp;
		tmp.nod_1 = nod_1;
		tmp.nod_2 = nod_2;
		tmp.wgt = wgt;

		edgeList.push_back(tmp);
	}
}

void init(vector <pair <int, int> > &nodeList, int n) {
	for (int i = 0; i < n; i++) {
		nodeList.push_back(make_pair(i, 0));
	}
}

// comparator for sorting edges
bool comparator(const edge &e1, const edge &e2) {
	return (e1.wgt < e2.wgt);
}

// output
void showList(vector <pair <int, int> > nodeList, int n) {
	printf("\nList of nodes is:-\n");

	cout << "Nod:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	cout << "Par:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", nodeList[i].first);
	}
	cout << endl;

	cout << "Rnk:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", nodeList[i].second);
	}
	cout << endl;
}

void showList(list <edge> eList, const char * msg) {
	int sum = 0;

	printf("\nList of %s is:-\n", msg);
	for (list <edge>::iterator i = eList.begin(); i != eList.end(); i++) {
		printf("[%d, %d]\t%d\n", (*i).nod_1, (*i).nod_2, (*i).wgt);
		sum += (*i).wgt;
	}

	cout << "Sum of weights of all edges is " << sum << endl;
}

// Kruskal's MST
void kruskalMST(vector <pair <int, int> > &nodeList, int n, list <edge> edgeList, list <edge> &MSTList) {
	for (list <edge>::iterator i = edgeList.begin(); i != edgeList.end(); i++) {
		int nod_1 = (*i).nod_1;
		int nod_2 = (*i).nod_2;
		int wgt = (*i).wgt;

		int par_1 = findSet(nodeList, nod_1);
		int par_2 = findSet(nodeList, nod_2);
		//printf("in edge [%d %d], %d\tp1 = %d\tp2 = %d\n", nod_1, nod_2, wgt, par_1, par_2);

		if (par_1 != par_2) {
			MSTList.push_back(*i);

			// nodeList[i].first denotes parent and nodeList[i].second denotes rank
			if (nodeList[par_1].second > nodeList[par_2].second) {
				nodeList[par_2].second = 0;
				nodeList[par_2].first = par_1;
			} else if (nodeList[par_1].second < nodeList[par_2].second) {
				nodeList[par_1].second = 0;
				nodeList[par_1].first = par_2;
			} else {
				nodeList[par_2].second = 0;
				nodeList[par_2].first = par_1;
				nodeList[par_1].second++;
			}
		}
	}
}

// helper method for find-set operation
int findSet(vector <pair <int, int> > nodeList, int i) {
	if (nodeList[i].first == i) {
		return i;
	} else {
		return (nodeList[i].first = findSet(nodeList, nodeList[i].first));
	}
}

