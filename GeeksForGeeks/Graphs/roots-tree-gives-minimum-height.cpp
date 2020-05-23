// http://www.geeksforgeeks.org/roots-tree-gives-minimum-height/
// here set has been only only for initial sorting (how lame)

/*
5
0 2
1 2
2 3
3 4
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <set>
#include <utility>
#include <queue>

using namespace std;
#define MAX 100

void input(bool [MAX][MAX], int &, int [MAX]);
void showMat(bool [MAX][MAX], int);
void showSet(set <pair <int, int> >);
void makeSet(int [MAX], int, set <pair <int, int> > &);
queue <int> makeQue(set <pair <int, int> >);
void findVert(bool [MAX][MAX], int, int [MAX], set <pair <int, int> >);

int main() {
	bool adj[MAX][MAX];
	int V;
	int deg[MAX];
	set <pair <int, int> > degVertSet;

	memset(deg, 0, MAX * sizeof(int));
	memset(adj, false, MAX * MAX * sizeof(bool));

	input(adj, V, deg);
	showMat(adj, V);

	makeSet(deg, V, degVertSet);
	showSet(degVertSet);

	findVert(adj, V, deg, degVertSet);

	return 0;

}

// method to read input from console
void input(bool adj[MAX][MAX], int &V, int deg[MAX]) {
	int src, dst;

	printf("Enter no of vertices:\t");
	cin >> V;

	cout << "Enter edges as (src, dst):-" << endl;
	cin >> src >> dst;

	while (src >= 0 && dst >= 0) {
		adj[src][dst] = true;
		adj[dst][src] = true;

		deg[src]++;
		deg[dst]++;

		cin >> src >> dst;
	}
}

// method to show adjacency matrix
void showMat(bool adj[MAX][MAX], int V) {
	printf("\nAdjacency matrix is:-\n");

	cout << "\t";
	for (int i = 0; i < V; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	for (int i = 0; i < V; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < V; j++) {
			if (adj[i][j] == true) {
				printf("T\t");
			} else {
				cout << "_\t";
			}
		}
		cout << endl;
	}
}

void showSet(set <pair <int, int> > degVertSet) {
	printf("\nSet of vertices and degrees is:-\n");
	for (set <pair <int, int> >::iterator i = degVertSet.begin(); i != degVertSet.end(); i++) {
		printf("%d (%d)\t", (*i).second, (*i).first);
	}
	cout << endl;
}

void showQue(queue <int> que) {
	printf("\nQue is:-\n");
	while (!que.empty()) {
		printf("%d\t", que.front());
		que.pop();
	}
	cout << endl;
}

void makeSet(int deg[MAX], int V, set <pair <int, int> > &degVertSet) {
	for (int i = 0; i < V; i++) {
		degVertSet.insert(make_pair(deg[i], i));
	}
}

queue <int> makeQue(set <pair <int, int> > degVertSet) {
	queue <int> que;

	for (set <pair <int, int> >::iterator i = degVertSet.begin(); (*i).first == 1; i++) {
		que.push((*i).second);
	}

	return que;
}

void findVert(bool adj[MAX][MAX], int V, int deg[MAX], set <pair <int, int> > degVertSet) {
	queue <int> que = makeQue(degVertSet);
	int remVert = V;

	while (remVert > 2) {
		int v = que.front();
		que.pop();
		remVert--;

//		cout << "\nRemoving edge of " << v;
		for (int i = 0; i < V; i++) {
			if (adj[v][i] == true) {
				adj[v][i] = false;
				adj[i][v] = false;

				deg[i]--;
				if (deg[i] == 1) {
					que.push(i);
				}

				break;
			}
		}

//		showQue(que);
	}

	printf("\nVertices that minimize height of tree are:-");
	showQue(que);
}

