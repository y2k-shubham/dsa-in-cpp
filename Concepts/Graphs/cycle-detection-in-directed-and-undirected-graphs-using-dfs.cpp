/*

Input
0
6
0 1
0 4
0 5
2 3
2 4
-1 -1
Output
No Cycle

Input
1
6
0 1
0 4
2 4
3 2
5 0
-1 -1
Output
No Cycle

Input
1
7
0 1
0 2
1 3
1 4
2 3
4 3
5 3
6 4
6 5
-1 -1
Output
No Cycle

Input
1
7
0 1
0 2
1 3
1 4
2 3
3 5
4 3
6 4
6 5
5 2
-1 -1
Output
Cycle

0
6
0 1
0 4
0 5
2 3
2 4
-1 -1
Output
no cycle

0
6
0 1
1 2
2 3
3 4
4 5
5 0
5 2
-1 -1
Output
cycle

*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

void input(vector <list <int> > &, int &, bool &);
void init(vector <bool> &, int);
void init(vector <list <int> > &, int);
void output(vector <list <int> >, int);
void dfsIter(vector <list <int> >, vector <bool> &, vector <bool> &, int, bool);

int main() {
	int n;
	bool directed;
	vector <list <int> > adjList;
	vector <bool> visiting;
	vector <bool> visited;

	input(adjList, n, directed);

	init(visiting, n);
	init(visited, n);

	output(adjList, n);
	dfsIter(adjList, visiting, visited, n, directed);

	return 0;
}

void input(vector <list <int> > &adjList, int &n, bool &directed) {
	int choice;

	printf("0 = Undirected Graph\n1 = Directed Graph\nEnter your choice:\t");
	scanf("%d", &choice);

	printf("Enter no of vertices:\t");
	scanf("%d", &n);

	init(adjList, n);
	int nod_1, nod_2;

	if (choice == 0) {
		directed = false;
		printf("Enter edges as (node_1, node_2):-\n(Enter -1 to terminate)\n");
	} else {
		directed = true;
		printf("Enter edges as (src, dest):-\n(Enter -1 to terminate)\n");
	}
	scanf("%d%d", &nod_1, &nod_2);

	while (nod_1 != -1 && nod_2 != -1) {
		adjList[nod_1].push_back(nod_2);

		if (!directed) {
			adjList[nod_2].push_back(nod_1);
		}
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

void dfsIter(vector <list <int> > adjList, vector <bool> &visiting, vector <bool> &visited, int n, bool directed) {
	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			//printf("\n===========\nDFS on node %d\n==========\n", i);

			stack <int> stk_nod;
			stack <int> stk_par;

			stk_nod.push(i);
			stk_par.push(-1);

			while (!stk_nod.empty()) {
				int crr_nod = stk_nod.top();
				int crr_par = stk_par.top();

				//printf("\n------------------");
				//printf("\ncrr_nod = %d\tcrr_par = %d\n", crr_nod, crr_par);
				if (!visiting[crr_nod]) {
					visiting[crr_nod] = true;
					//visited[crr_nod] = false;

					for (list <int>::iterator it = adjList[crr_nod].begin(); it != adjList[crr_nod].end(); it++) {
						if ((directed && visiting[*it]) || (!directed && *it != crr_par && visiting[*it])) {
							// cycle found
							printf("\nCycle Present\n");
							return;
						} else if ((directed && !visited[*it]) || (!directed && !visiting[*it])) {
							//printf("node %d\tparent %d\tpushed to stack\n", *it, crr_nod);
							stk_nod.push(*it);
							stk_par.push(crr_nod);
						}
					}
				} else {
					crr_nod = stk_nod.top();
					crr_par = stk_par.top();

					stk_nod.pop();
					stk_par.pop();

					visiting[crr_nod] = false;
					visited[crr_nod] = true;

					//printf("\nnode %d\tparent %d\tpopped from stack\n", crr_nod, crr_par);
				}
				//printf("------------------\n");
			}
		}
	}

	printf("\nNo Cycle Present\n");
}
