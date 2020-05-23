// http://www.geeksforgeeks.org/detect-cycle-undirected-graph/
// https://www.youtube.com/watch?v=n_t0a_8H8VY

/*
Input:
7
0 1
1 2
3 4
5 6
4 5
2 6
-1 -1
Output: No cycle

Input:
6
0 1
3 5
2 4
2 1
5 4
3 2
-1 -1
Output: Cycle

Input:
5
1 0
0 2
1 2
0 3
3 4
-1 -1
Output: Cycle

Input:
5
1 0
0 2
0 3
3 4
2 0
-1 -1
Output: Cycle
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;

void input(vector <list <int> > &, int &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
void output(vector <list <int> >, int);
void dfsIter(vector <list <int> >, vector <bool>, int);
bool dfsRec(vector <list <int> >, vector <bool> &, int, int);

int main() {
	int n;
	vector <list <int> > adjList;
	vector <bool> visited;

	input(adjList, n);
	init(visited, n);
	output(adjList, n);
	dfsIter(adjList, visited, n);
	if (!dfsRec(adjList, visited, 0, -1)) {
		printf("dfsRec  : No cycle present in graph\n");
	}

	return 0;
}

void input(vector <list <int> > &adjList, int &n) {
	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	init(adjList, n);
	int nod_1, nod_2;

	printf("\nEnter edges as (node_1, node_2):-\n(Enter -1 to terminate)\n");
	scanf("%d%d", &nod_1, &nod_2);

	while (nod_1 != -1 && nod_2 != -1) {
		adjList[nod_1].push_back(nod_2);
		adjList[nod_2].push_back(nod_1);
		//output(par, n);
		scanf("%d%d", &nod_1, &nod_2);
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

void dfsIter(vector <list <int> > adjList, vector <bool> visited, int n) {
	stack <int> stk_nod;
	stack <int> stk_par;

	stk_nod.push(0);
	stk_par.push(-1);

	while (!stk_nod.empty()) {
		int crrVert = stk_nod.top();
		int crrPar = stk_par.top();

		stk_nod.pop();
		stk_par.pop();

		if (!visited[crrVert]) {
			visited[crrVert] = true;
			for (list <int>::iterator it = adjList[crrVert].begin(); it != adjList[crrVert].end(); it++) {
				if (*it != crrPar) {
					if (visited[*it] == true) {
						printf("\ndfsIter : Cycle detected at edge %d-%d\n", crrVert, *it);
						return;
					} else {
						stk_nod.push(*it);
						stk_par.push(crrVert);
						//printf("At %d, pushed %d to stack\n", crrVert, *it);
					}
				}
			}
		} else {

		}
		//printf("\n");
	}

	printf("\ndfsIter : No Cycle present in Graph\n");
}

bool dfsRec(vector <list <int> > adjList, vector <bool> &visited, int crr, int prev) {
	visited[crr] = true;

	bool cycPresent = false;
	for (list <int>::iterator it = adjList[crr].begin(); !cycPresent && it != adjList[crr].end(); it++) {
		if (*it != prev) {
			if (visited[*it] == true) {
				printf("dfsRec  : Cycle detected at edge %d-%d\n", crr, *it);
				return true;
			} else {
				//printf("at %d, prev = %d, going to %d\n", crr, prev, *it);
				cycPresent = cycPresent || dfsRec(adjList, visited, *it, crr);
			}
		}
	}

	visited[crr] = false;
	return cycPresent;
}
