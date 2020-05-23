/*
Input:
5
0 2 1	0 1 4
1 4 4
2 1 2	2 3 4
3 4 4
-1 -1 -1
0

Output:
The output table is:-
Vert:   0       1       2       3       4
Par:    0       2       0       2       1
PLen:   0       3       1       5       7
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <map>
#include <climits>

using namespace std;

void init(vector <list <pair <int, int> > > &, int);
void init(vector <bool> &, int);
void init(map <int, pair <int, int> > &, int);
void input(vector <list <pair <int, int> > > &, int &, int &);
void showList(vector <list <pair <int, int> > >);
void dijkstra(vector <list <pair <int, int> > >, map <int, pair <int, int> > &, vector <bool> &, int, int);
void output(map <int, pair <int, int> >, vector <bool>, int);

int main() {
	int n;
	int src;
	vector <list <pair <int, int> > > adjList;
	map <int, pair <int, int> > path;
	vector <bool> permanent;

	input(adjList, n, src);
	init(permanent, n);
	init(path, n);
	showList(adjList);

	dijkstra(adjList, path, permanent, n, src);
	output(path, permanent, n);

	return 0;
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 1; i <= n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void init(vector <bool> &permanent, int n) {
	for (int i = 1; i <= n; i++) {
		permanent.push_back(false);
	}
}

void init(map <int, pair <int, int> > &path, int n) {
	for (int i = 0; i < n; i++) {
		path[i] = make_pair(INT_MAX, -1);
	}
}

void input(vector <list <pair <int, int> > > &adjList, int &n, int &source) {
	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	init(adjList, n);
	int src, dst, wgt;

	printf("\nEnter edges as (src, dst, wgt):-\n");
	scanf("%d%d%d", &src, &dst, &wgt);

	while (src != -1 && dst != -1 && wgt != -1) {
		adjList[src].push_back(make_pair(dst, wgt));
		scanf("%d%d%d", &src, &dst, &wgt);
	}

	printf("\nEnter the source vertex:\t");
	scanf("%d", &source);
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

void dijkstra(vector <list <pair <int, int> > > adjList, map <int, pair <int, int> > &path, vector <bool> &permanent, int n, int src) {
	path[src].first = 0;
	path[src].second = src;
	path[n] = make_pair(INT_MAX, -1);

	int v = src;
	while (path[v].first < INT_MAX) {
		permanent[v] = true;

		for (list <pair <int, int> >::iterator it = adjList[v].begin(); it != adjList[v].end(); it++) {
			if (path[it -> first].first > path[v].first + it -> second) {
				path[it -> first].first = path[v].first + it -> second;
				path[it -> first].second = v;
			}
		}

		int minPathLen = INT_MAX;
		int minPathVert = n;
		for (int i = 0; i < n; i++) {
			if (!permanent[i] && path[i].first < minPathLen) {
				minPathLen = path[i].first;
				minPathVert = i;
			}
		}

		v = minPathVert;
	}
}

void output(map <int, pair <int, int> > path, vector <bool> visited, int n) {
	printf("\nThe output table is:-\n");

	printf("Vert:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", i);
	}

	printf("\nPar:\t");
	for (int i = 0; i < n; i++) {
		if (visited[i]) {
			printf("%d\t", path[i].second);
		} else {
			printf("-\t");
		}
	}

	printf("\nPLen:\t");
	for (int i = 0; i < n; i++) {
		if (visited[i]) {
			printf("%d\t", path[i].first);
		} else {
			printf("~\t");
		}
	}
	printf("\n");
}
