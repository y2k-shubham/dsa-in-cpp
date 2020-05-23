// http://www.geeksforgeeks.org/find-if-there-is-a-path-of-more-than-k-length-from-a-source/
// Idea: Simple Brute-Force Backtracking
// Complexity: If source is given (like here), then O(n!), otherwise O(n X n!)
// Note: Complexity has been calculated assuming a completely connected graph

/*
Common Input:
9

0 1 4		0 7 8
1 0 4		1 2 8		1 7 11
2 1 8		2 3 7		2 5 4		2 8 2
3 2 7		3 4 9		3 5 14
4 3 9		4 5 10
5 2 4		5 3 14		5 4 10		5 6 2
6 5 2		6 7 1		6 8 6
7 0 8		7 1 11		7 6 1		7 8 7
8 2 2		8 6 6		8 7 7
-1 -1 -1

0

Input: (k = )
58
Output: true
Path: 0 -> 7 -> 1 -> 2 -> 8 -> 6 -> 5 -> 3 -> 4

Input: (k = )
62
Output: false

*/

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <stack>

using namespace std;
#define MAX 100

void input(vector <list <pair <int, int> > > &, int &, int &, int &);
void init(vector <list <pair <int, int> > > &, int);
void init(vector <bool> &, int);
void showList(vector <list <pair <int, int> > >, int);
bool hasPath(vector <list <pair <int, int> > >, int, vector <bool> &, stack <int> &, int, int, int);
void showPath(stack <int>);

int main() {
	vector <list <pair <int, int> > > adjNode;
	vector <list <pair <int, int> > > adjWght;
	vector <bool> visited;
	stack <int> path;
	int k;
	int n;
	int src;

	input (adjNode, n, src, k);
	init (visited, n);

	showList (adjNode, n);

	if (hasPath(adjNode, n, visited, path, src, 0, k)) {
		printf("\nPath greater than length %d is present\n", k);
		showPath(path);
		printf("NULL\n");
	} else {
		printf("Path greater than length %d is not present\n", k);
	}

	return 0;
}

void input (vector <list <pair <int, int> > > &adjNode, int &n, int &source, int &k) {
	int src, dst, wgt;

	printf ("Enter no of nodes:\t");
	scanf ("%d", &n);

	init (adjNode, n);

	printf ("Enter edges as (src, dst, wgt):-\n");
	scanf ("%d%d%d", &src, &dst, &wgt);
	while (src >= 0 && dst >= 0 && wgt >= 0) {
		adjNode[src].push_back (make_pair(dst, wgt));
		scanf ("%d%d%d", &src, &dst, &wgt);
	}

	printf ("Enter the source:\t");
	scanf ("%d", &source);

	printf ("Enter the minimum length threshold:\t");
	scanf ("%d", &k);
}

void init (vector <list <pair <int, int> > > &adjNode, int n) {
	for (int i = 0; i < n; i++) {
		list <pair <int, int> > tmp;
		adjNode.push_back (tmp);
	}
}

void init (vector <bool> &visited, int n) {
	for (int i = 0; i < n; i++) {
		visited.push_back (false);
	}
}

void showList (vector <list <pair <int, int> > > adjNode, int n) {
	printf ("\nThe adjacency list is:-\n");
	for (int i = 0; i < n; i++) {
		printf ("%d\t=\t", i);
		for (list <pair <int, int> >::iterator it = adjNode[i].begin(); it != adjNode[i].end(); it++) {
			printf ("[%d, %d] -> ", it -> first, it -> second);
		}
		printf ("NULL\n");
	}
	printf ("\n");
}

bool hasPath(vector <list <pair <int, int> > > adjNode, int n, vector <bool> &visited, stack <int> &path, int crrNode, int crrLen, int minLen) {
	visited[crrNode] = true;
	path.push(crrNode);

	for (list <pair <int, int> >::iterator it = adjNode[crrNode].begin(); it != adjNode[crrNode].end(); it++) {
		if (!visited[it -> first]) {
			if (crrLen + it -> second <= minLen) {
				if (hasPath(adjNode, n, visited, path, it -> first, crrLen + it -> second, minLen)) {
					return true;
				}
			} else {
//				printf("crrNode = %d\t, prevNode = %d\tcrrLen = %d\tit-len = %d\tminLen = %d\n", it -> first, path.top(), crrLen, it -> second, minLen);
//				printf("true returned\n");
				path.push(it -> first);
				return true;
			}
		}
	}

	visited[crrNode] = false;
	path.pop();

	return false;
}

void showPath(stack <int> path) {
	if (!path.empty()) {
		int tmp = path.top();
		path.pop();

		showPath(path);

		printf("%d -> ", tmp);
	}
}
