/*
Example 1:
Cormen 3rd Ed Page 711
6

0 16 13 0 0 0
0 0 10 12 0 0
0 4 0 0 14 0
0 0 9 0 0 20
0 0 0 7 0 4
0 0 0 0 0 0

0 5
Answer: 23

Example 2:
https://docs.google.com/viewer?url=http%3A%2F%2Fwww.cse.psu.edu%2F~sxr48%2Fcse565%2Flecture-notes%2F07demo-maxflow.pdf
6

0 10 10 0 0 0
0 0 2 4 8 0
0 0 0 0 9 0
0 0 0 0 0 10
0 0 0 6 0 10
0 0 0 0 0 0

0 5
Answer: 19

Example 3:
https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm
4

0 1000 1000 0
0 0 1 1000
0 0 0 1000
0 0 0 0

Answer: 2000
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <queue>

using namespace std;

#define NIL -1
#define MAX 100
#define minVal(a, b) ((a < b) ? a : b)

void input(int [MAX][MAX], int &, int &, int &);
void init(int [MAX], int);
void init(bool [MAX], int);
int findMaxFlow(int [MAX][MAX], int, int, int);
bool bfs(int [MAX][MAX], int, int [MAX], int, int);
int showPath(int [MAX][MAX], int [MAX], int);
void updateFlows(int [MAX][MAX], int [MAX], int, int);

int main() {
	int n;
	int adj[MAX][MAX];
	int src, snk;
	int maxFlow;

	input(adj, n, src, snk);
	maxFlow = findMaxFlow(adj, n, src, snk);

	printf("\nThe total (maximum) flow from %d to %d is:\t%d\n", src, snk, maxFlow);

	return 0;
}

void input(int adj[MAX][MAX], int &n, int &src, int &snk) {
	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	printf("Enter adjacency matrix:-\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &adj[i][j]);
		}
	}

	printf("Enter (src, snk):\t");
	scanf("%d%d", &src, &snk);
}

void init(int par[MAX], int n) {
	for (int i = 0; i < n; i++) {
		par[i] = NIL;
	}
}

void init(bool visited[MAX], int n) {
	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}
}

int findMaxFlow(int adj[MAX][MAX], int n, int src, int snk) {
	int totFlow;
	int par[MAX];

	totFlow = 0;
	init(par, n);

	printf("\nThe various flow paths are:-\n");
	while (bfs(adj, n, par, src, snk)) {
		int minFlow = showPath(adj, par, snk);
		printf("done (%d)\n", minFlow);

		updateFlows(adj, par, snk, minFlow);
		totFlow += minFlow;

		init(par, n);
	}

	return totFlow;
}

void updateFlows(int adj[MAX][MAX], int par[MAX], int snk, int minFlow) {
	int to, from;

	to = snk;
	while ((from = par[to]) != -1) {
		adj[from][to] -= minFlow;
		adj[to][from] += minFlow;

		to = from;
	}
}

bool bfs(int adj[MAX][MAX], int n, int par[MAX], int src, int snk) {
	queue <int> que;
	bool visited[MAX];

	que.push(src);
	init(visited, n);

	while (!que.empty()) {
		int crr = que.front();
		visited[crr] = true;
		que.pop();

		for (int i = 0; i < n; i++) {
			if (adj[crr][i] > 0 && !visited[i]) {
				visited[i] = true;
				que.push(i);
				par[i] = crr;

				if (i == snk) {
					return true;
				}
			}
		}
	}

	return false;
}

int showPath(int adj[MAX][MAX], int par[MAX], int crr) {
	if (par[crr] == NIL) {
		printf("%d -> ", crr);
		return INT_MAX;
	} else {
		//printf("at %d, going to parent %d\n", crr, par[crr]);
		int tmp = showPath(adj, par, par[crr]);
		int min = minVal(adj[par[crr]][crr], tmp);
		//printf("at %d, coming from parent %d\n", crr, par[crr]);
		printf("%d -> ", crr);
		return min;
	}
}
