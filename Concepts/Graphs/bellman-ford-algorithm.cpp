// TusharRoy
/*
Input
5
0 1 4	0 2 5	0 3 8
1 2 -3
2 4 4
3 4 2
4 3 1
-1 -1 -1
0
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <utility>

using namespace std;

void input(vector <list <pair <int, int> > > &, int &, int &, int &);
void init(vector <list <pair <int, int> > > &, int);
void init(map <int, pair <int, int> > &, int);
int add(int, int);
bool bellman_ford(vector <list <pair <int, int> > >, int, int, int, map <int, pair <int, int> > &);
void output(map <int, pair <int, int> >, int, int);

int main() {
	int V, E;
	int src;
	vector <list <pair <int, int> > > adjList;
	map <int, pair <int, int> > dist;

	input(adjList, V, E, src);
	init(dist, V);

	if (bellman_ford(adjList, V, E, src, dist)) {
		output(dist, V, src);
	} else {
		printf("\nGraph contains -ve cycle\n");
	}

	return 0;
}

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

	printf("\nEnter source vertex:\t");
	scanf("%d", &source);
}

void init(vector <list <pair <int, int> > > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjList.push_back(tmp);
	}
}

void init(map <int, pair <int, int> > & dist, int V) {
	for (int i = 0; i < V; i++) {
		dist[i] = make_pair(INT_MAX, i);
	}
}

bool bellman_ford(vector <list <pair <int, int> > > adjList, int V, int E, int src, map <int, pair <int, int> >& dist) {
	int i;
	int distSum;

	distSum = -1;
	dist[src].first = 0;

	for (i = 1; (distSum != 0) && (i < V); i++) {
		distSum = 0;
		for (int v = 0; v < V; v++) {
			for (list <pair <int, int> >::iterator it = adjList[v].begin(); it != adjList[v].end(); it++) {
				if (dist[it -> first].first > add(dist[v].first, it -> second)) {
					dist[it -> first].first = add(dist[v].first, it -> second);
					dist[it -> first].second = v;
					distSum += dist[it -> first].first;
				}
			}
		}
	}

	if (i == V) {
		distSum = 0;
		map <int, pair <int, int> > distCopy = dist;

		for (int v = 0; v < V; v++) {
			for (list <pair <int, int> >::iterator it = adjList[v].begin(); it != adjList[v].end(); it++) {
				if (dist[it -> first].first > add(dist[v].first, it -> second)) {
					dist[it -> first].first = add(dist[v].first, it -> second);
					dist[it -> first].second = v;
					distSum += dist[it -> first].first;
				}
			}
		}

		dist = distCopy;
		if (distSum != 0) {
			return false;
		}
	}

	return true;
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return a + b;
	}
}

void output(map <int, pair <int, int> > dist, int V, int src) {
	printf("\nShortest distances of nodes from %d are:-\n", src);

	printf("Node\tDist\tParent\n");
	for (map <int, pair <int, int> >::iterator it = dist.begin(); it != dist.end(); it++) {
		if ((it -> second).first != INT_MAX) {
			printf("%d\t%d\t%d\n", it -> first, (it -> second).first, (it -> second).second);
		} else {
			printf("%d\t-\t%d\n", it -> first, (it -> second).second);
		}
	}
}
