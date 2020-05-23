// http://www.geeksforgeeks.org/minimum-edges-reverse-make-path-source-destination/
// Above link contains much more clever solution

// Priority Que: http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
// Submission at GeeksForGeeks: http://code.geeksforgeeks.org/7kY16d

/*
Please note the input format

First integer (7 for Input 1 & 11 for Input 2) denotes no of vertices in graph

After this, we enter several pairs, denoting edges of the graph. No of edges
until is not specified, we keep entering edges till pair (-1, -1) is encountered
For example, in input 1 below, we have edges 0->1, 2->1, 2->3 and so on till 6->4

Finally, at last, there's a pair denoting source and destination vertices
((0, 6) in Input 1 below and (0, 10) in input 2 below)
*/

/*
========================
Input 1
------------------------
7

0 1
2 1		2 3
4 5
5 1
6 3		6 4
-1 -1

0 6
========================
Input 2
------------------------
11

0 1		0 2
1 4
3 0
4 7
5 2
6 3
8 5		8 10
9 6
10 7
-1 -1

0 10
========================
*/

/*

> Please make sure to read the input format and sample inputs given in the comments in the beginning of the program.
> The method findRevCount() contains the modified BFS implemented with the help of priority que to create a map that stores minimum no of edge reversals needed to reach any vertex of the graph. Read detailed comments given inside this method to understand the approach.
> The class myComparator declared before the main() method is used as comparator for priority que.
> Priority que stores pairs of integers and pairs having lower value of second item of pair (no of reversals needed to reach vertex, which is stored as first item of pair) have a higher priority.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <functional>
#include <map>
#include <climits>

using namespace std;
#define MAX 100

void input(bool [MAX][MAX], int &, int &, int &);
void showMat(bool [MAX][MAX], int);
bool comparator(const pair <int, int> &, const pair <int, int> &);
void findRevCount(bool [MAX][MAX], int, int, int);
void showMap(map <int, int>);

// comparator class for priority_queue
class myComparator {
public:
	myComparator() {
	}

	bool operator() (const pair <int, int> &p1, const pair <int, int> &p2) {
		if (p2.second < p1.second) {
			return false;
		} else if (p1.second < p2.second) {
			return true;
		} else if (p1.first < p2.first) {
			return true;
		} else {
			return false;
		}
	}
};

int main() {
	bool adj[MAX][MAX];
	int V;
	int src, dst;

	// read inputs from console and display the adjacency matrix
	input(adj, V, src, dst);
	showMat(adj, V);

	// find and display minimum no of reversal needed to reach varios vertices
	findRevCount(adj, V, src, dst);

	return 0;
}

// method to read input from console
void input(bool adj[MAX][MAX], int &V, int &source, int &destination) {
	int src, dst;

	printf("Enter no of vertices:\t");
	cin >> V;

	cout << "Enter edges as (src, dst):-" << endl;
	memset(adj, false, V * V * sizeof(bool));

	cin >> src >> dst;
	while (src >= 0 && dst >= 0) {
		adj[src][dst] = true;
		cin >> src >> dst;
	}

	printf("Enter (src, dst):\t");
	cin >> source >> destination;
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

// method to find and display minimum no of reversals needed to reach various vertices
void findRevCount(bool adj[MAX][MAX], int V, int src, int dst) {
	// priority que is used to store a pair containing vertex as first item and no of
	// reversals needed to reach it as the second item.

	// A map revCount is used to store
	// the minimum no of reversals needed to reach various vertices; it is initialized with
	// infinity (INT_MAX) for all vertices except source vertex, which is initialized with 0

	// V = no of vertices in graph
	// v = variable for storing a vertex popped from priority que
	// r = variable for storing no of reversals needed to reach the vertex popped from que

	priority_queue <pair <int, int>, vector <pair <int, int> >, myComparator> que;
	map <int, int> revCount;
	int v, r;

	// initially, source vertex is pushed to priority que with reversal count as 0
	// and map is initialized with infinity (INT_MAX), except source vertex, which is
	// initialized with 0
	que.push({src, 0});
	for (int i = 0; i < V; i++) {
		revCount.insert(make_pair(i, INT_MAX));
	}
	revCount[src] = 0;

	// now we perform modified BFS until priority que becomes empty
	while (!que.empty()) {
		// deque a pair from priority que and store first and second items in v & r
		pair <int, int> p = que.top();
		que.pop();
		int v = p.first;
		int r = p.second;

		// if r exceeds revCount[v], then it means that this vertex 'v' has already
		// been explored through a path having lesser no of reversals, because we are
		// using a priority que which places items having lesser no of reversals
		// (pair.second) before items having greater no of reversals
		// so we need not explore it again, and we move to next iteration of loop
		if (r > revCount[v]) {
			continue;
		}

		// we explore all adjacent vertices of v and add only those to que, which have
		// best (smallest) known reversal-count grater that reversal count r of vertex v
		// best known reversal count of all such vertices is updated while adding to que
		for (int j = 0; j < V; j++) {
			if (adj[v][j] == true && revCount[j] > r) {
				que.push(make_pair(j, r));
				revCount[j] = r;
			}
		}

		// this is the next loop in which incoming edges to vertex v are examined
		// if reversing any such vertex gives a smaller reversal count for the opposite
		// vertex (r + 1), than what is the current best known reversal count (revCount[i])
		// then we add it to priority que with and update it's best known reversal count
		for (int i = 0; i < V; i++) {
			if (adj[i][v] == true && revCount[i] > (r + 1)) {
				que.push({i, r + 1});
				revCount[i] = r + 1;
			}
		}
	}

	printf("\nMin no of reversals needed to reach to various vertices from source %d are:-\n", src);
	showMap(revCount);
}

// method to display map <int, int> passed in argument
void showMap(map <int, int> revCount) {
	for (map <int, int>::iterator i = revCount.begin(); i != revCount.end(); i++) {
		printf("%d\t:\t%d\n", (*i).first, (*i).second);
	}
	cout << endl;
}

