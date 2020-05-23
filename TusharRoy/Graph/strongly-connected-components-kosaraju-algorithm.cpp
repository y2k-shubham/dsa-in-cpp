/*
Input:
11
0 1
1 2
2 0
1 3
3 4
4 5
5 3
6 5
6 7
7 8
8 9
9 6
9 10
-1 -1

Output:
run and see!
*/

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <stack>

using namespace std;
#define MAX 100

void showAdjList(vector <list <int> >, int, const char *);
void init(vector <list <int> > &, int);
void init(vector <bool> &, int);
void input(vector <list <int> > &, vector <list <int> > &, int);
void pass_1(vector <list <int> >, int, stack <int> &);
void pass_2(vector <list <int> >, int, stack <int>, vector <list <int> > &, int &);
void showStack(stack <int>);

int main() {
	int n;
	int compCount;
	vector <list <int> > compList;
	vector <list <int> > actGraph;
	vector <list <int> > revGraph;
	stack <int> finishOrder;

	printf("Enter no of nodes:\t");
	scanf("%d", &n);

	init(actGraph, n);
	init(revGraph, n);

	input(actGraph, revGraph, n);

	showAdjList(actGraph, n, "adjacency list of original graph");
	showAdjList(revGraph, n, "adjacency list of reverse graph");

	pass_1(actGraph, n, finishOrder);
	showStack(finishOrder);

	pass_2(revGraph, n, finishOrder, compList, compCount);
	showAdjList(compList, compCount, "list of connected components");

	return 0;
}

void init(vector <bool> &visited, int n) {
	for (int i = 0; i < n; i++) {
		visited.push_back(false);
	}
}

void init(vector <list <int> > &graph, int n) {
	for (int i = 0; i < n; i++) {
		list <int> emptyList;
		graph.push_back(emptyList);
	}
}

void showAdjList(vector <list <int> > adjList, int n, const char * msg) {
	printf("\nThe %s is:-\n", msg);
	for (int i = 0; i < n; i++) {
		printf("ver %d\t:\t", i);
		for (list <int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++) {
			printf("%d\t", *it);
		}
		printf("\n");
	}
}

void input(vector <list <int> > &actGraph, vector <list <int> > &revGraph, int n) {
	int src, dst;

	printf("\nEnter edges as (src, dst):-\n(Enter (-1, -1) to terminate)\n");
	scanf("%d%d", &src, &dst);

	while (src != -1 && dst != -1) {
		actGraph[src].push_back(dst);
		revGraph[dst].push_back(src);

		scanf("%d%d", &src, &dst);
	}
}

void showStack(stack <int> stk) {
	printf("\nThe finish-order stack is:-\n");
	while (!stk.empty()) {
		printf("%d\t", stk.top());
		stk.pop();
	}
	printf("\n");
}

void pass_1(vector <list <int> > actGraph, int n, stack <int> &finishOrder) {
	vector <bool> visited;
	init(visited, n);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			stack <int> dfsStack;
			dfsStack.push(i);
			//printf("\n==========\nDFS started at node %d\n", i);

			while (!dfsStack.empty()) {
				int crrNode = dfsStack.top();
				//printf("\n%d read from stack\t");

				if (!visited[crrNode]) {
					//printf("marked visited, iterating over it's children\n");
					visited[crrNode] = true;
					for (list <int>::iterator it = actGraph[crrNode].begin(); it != actGraph[crrNode].end(); it++) {
						if (!visited[*it]) {
							dfsStack.push(*it);
							//printf("%d pushed to stack\n", *it);
						}
					}
				} else {
					//printf("was visited, popped from stack and pushed to finishOrder\n");
					dfsStack.pop();
					finishOrder.push(crrNode);
				}
			}
		}
	}
}

void pass_2(vector <list <int> > revGraph, int n, stack <int> finishOrder, vector <list <int> > &compList, int &compCount) {
	vector <bool> visited;
	init(visited, n);

	compCount = 0;
	while (!finishOrder.empty()) {
		int i = finishOrder.top();
		finishOrder.pop();

		if (!visited[i]) {
			// now we'll get a new connected component
			list <int> tmpList;
			stack <int> dfsStack;

			compList.push_back(tmpList);
			compCount++;

			dfsStack.push(i);
			while (!dfsStack.empty()) {
				int crrNode = dfsStack.top();

				if (!visited[crrNode]) {
					visited[crrNode] = true;
					for (list <int>::iterator it = revGraph[crrNode].begin(); it != revGraph[crrNode].end(); it++) {
						if (!visited[*it]) {
							dfsStack.push(*it);
						}
					}
				} else {
					compList[compCount - 1].push_back(crrNode);
					dfsStack.pop();
				}
			}
		}
	}
}
