/*

Input:
4
3 2
0 1
1 2
0 3
-1 -1
Output:
No Cycle

Input:
5
3 4
1 3
0 3
1 2
3 2
0 1
-1 -1
Output:
No Cycle

Input:
5
3 4
1 3
0 3
2 1
3 2
0 1
-1 -1
Output:
Cycle

*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

void input(vector <list <int> > &, int &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
void output(vector <list <int> >, int);
bool dfsRec(vector <list <int> >, vector <bool> &, int, int);

int main() {
	int n;
	vector <list <int> > adjList;
	vector <bool> visited;

	input(adjList, n);
	init(visited, n);
	output(adjList, n);

	if (!dfsRec(adjList, visited, 0, -1)) {
		printf("dfsRec  : No cycle present in graph\n");
	}

	return 0;
}

void input(vector <list <int> > &adjList, int &n) {
	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	init(adjList, n);
	int src, dst;

	printf("\nEnter edges as (src, dst):-\n(Enter -1 to terminate)\n");
	scanf("%d%d", &src, &dst);

	while (src != -1 && dst != -1) {
		adjList[src].push_back(dst);
		//output(par, n);
		scanf("%d%d", &src, &dst);
	}
}

void init(vector <bool> &visited, int n) {
	for (int i = 0; i < n; i++) {
		visited.push_back(false);
	}
}

void init(vector <list <int> > &adjList, int n) {
	for (int i = 0; i < n; i++) {
		list <int> tmp;
		adjList.push_back(tmp);
	}
}

void output(vector <list <int> > adjList, int n) {
	printf("\nThe adjacency list is:-\n");
	for (int i = 0; i < n; i++) {
		printf("ver %d\t:\t", i);
		for (list <int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++) {
			printf("%d\t", *it);
		}
		printf("\n");
	}
}

bool dfsRec(vector <list <int> > adjList, vector <bool>& visited, int crr, int prev) {
	visited[crr] = true;

	bool cycPresent = false;
	for (list <int>::iterator it = adjList[crr].begin(); it != adjList[crr].end(); it++) {
		if (*it != prev && visited[*it] == true) {
			printf("dfsRec  : Cycle detected at edge %d-%d\n", crr, *it);
			return true;
		} else {
			cycPresent = cycPresent || dfsRec(adjList, visited, *it, crr);
		}
	}

	visited[crr] = false;
	return cycPresent;
}

