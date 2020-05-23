/*
For every edge of an undirected acyclic graph, find the number of nodes across it's two ends.
In other words, if there are multiple queries asking if a particular edge be removed, how
many nodes will be present in the remaining two subgraphs, then answer such queries efficiently
*/

/*
22
0 1
1 4
2 4
3 4
4 6
5 6
6 7
7 8		7 9		7 12
9 10	9 13
10 11
13 14	13 16
14 19
15 16
16 17
18 20
19 20
20 21
-1 -1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

void input(vector <map <int, int> > &);
void output(vector <map <int, int> >, int);
int dfs(int, vector <map <int, int> >&, int, vector <bool>&);

int main() {
	int V;

	cout << "Enter V:\t";
	cin >> V;

	map <int, int> emptyMap;
	vector <map <int, int> > adjList (V, emptyMap);
	vector <bool> visited (V, false);

	input(adjList);
	output(adjList, V);

	dfs(V, adjList, 0, visited);
	output(adjList, V);

	return 0;
}

void input(vector <map <int, int> > &adjList) {
	int src, dest;

	printf("Enter edges as (src, dest):-\n");
	cin >> src >> dest;
	while (src >= 0 && dest >= 0) {
		adjList[src].insert(make_pair(dest, INT_MIN));
		adjList[dest].insert(make_pair(src, INT_MIN));

		cin >> src >> dest;
	}
}

void output(vector <map <int, int> > adjList, int V) {
	printf("\nAdjacency list is:-\n");

	for (int i = 0; i < V; i++) {
		printf("%d\t", i);

		for (map <int, int>::iterator it = adjList[i].begin(); it != adjList[i].end(); it++) {
			if ((*it).second == INT_MIN) {
				printf("%d _\t", (*it).first);
			} else {
				printf("%d (%d)\t", (*it).first, (*it).second);
			}
		}
		cout << endl;
	}
	cout << endl;
}

int dfs(int V, vector <map <int, int> >& adjList, int v, vector <bool>& visited) {
	int nodeCountTotal = 1;
	visited[v] = true;

	if (adjList[v].size() > 0) {
		for (map <int, int>::iterator i = adjList[v].begin(); i != adjList[v].end(); i++) {
			if (visited[(*i).first] == false) {
				int nodeCount = dfs(V, adjList, (*i).first, visited);
				nodeCountTotal += nodeCount;

//				printf("\nat node %d\t, found %d nodes through edge to %d\n", v, nodeCount, (*i).first);

				adjList[v][(*i).first] = nodeCount;
				adjList[(*i).first][v] = V - nodeCount;
			}
		}
	}

	return nodeCountTotal;
}

