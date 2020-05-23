// http://www.geeksforgeeks.org/find-number-of-islands/

/*
Input
5 5
1 1 0 0 0
0 1 0 0 1
1 0 0 1 1
0 0 0 0 0
1 0 1 0 1
Output
5

Input
5 5
1 1 0 0 0
0 1 0 0 0
1 0 0 1 1
0 0 0 0 0
1 0 1 0 1
Output
5

Input
5 5
1 1 0 0 0
0 1 0 0 1
1 0 0 1 1
0 0 0 0 0
1 0 0 0 1
Output
4

Input
5 5
1 1 0 0 0
0 0 0 0 1
1 0 0 1 1
0 0 0 0 0
1 0 0 0 1
Output
5

Input
5 5
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
Output
0
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <cstring>

using namespace std;
#define MAX 100

void input(bool [MAX][MAX], int &, int &);
int bfsCount(bool [MAX][MAX], int, int);
void bfs(bool [MAX][MAX], int, int, bool [MAX][MAX], queue <pair <int, int> >);
int dfsCount(bool [MAX][MAX], int, int);
void dfs(bool [MAX][MAX], int, int, bool [MAX][MAX], int, int);

int main() {
	int m, n;
	bool mat[MAX][MAX];
	int islCount;

	input(mat, m, n);

	islCount = bfsCount(mat, m, n);
	cout << "\nNo of islands using BFS = " << islCount << endl;

	islCount = dfsCount(mat, m, n);
	cout << "No of islands using DFS = " << islCount << endl;

	return 0;
}

void input(bool mat[MAX][MAX], int &m, int &n) {
	cout << "Enter dimensions of grid:\t";
	cin >> m >> n;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int ele;
			cin >> ele;

			mat[i][j] = (ele == 1);
		}
	}
}

int bfsCount(bool mat[MAX][MAX], int m, int n) {
	bool vis[MAX][MAX];
	int ctr;

	ctr = 0;
	memset(vis, false, m * n * sizeof(bool));

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] == true && vis[i][j] == false) {
				queue <pair <int, int> > que;

				que.push(make_pair(i, j));
				vis[i][j] = true;
				bfs(mat, m, n, vis, que);

				ctr++;
			}
		}
	}

	return ctr;
}

void bfs(bool mat[MAX][MAX], int m, int n, bool vis[MAX][MAX], queue <pair <int, int> > que) {
	while (que.empty() == false) {
		pair <int, int> coord = que.front();
		que.pop();

		int i = coord.first;
		int j = coord.second;

		for (int rD = -1; rD <= 1; rD++) {
			for (int cD = -1; cD <= 1; cD++) {
				int newI = i + rD;
				int newJ = j + cD;

				if (0 <= newI && newI < m && 0 <= newJ && newJ < m) {
					if (mat[newI][newJ] == true && vis[newI][newJ] == false) {
						que.push(make_pair(newI, newJ));
						vis[newI][newJ] = true;
					}
				}
			}
		}
	}
}

int dfsCount(bool mat[MAX][MAX], int m, int n) {
	bool vis[MAX][MAX];
	int ctr;

	memset(vis, false, m * n * sizeof(bool));
	ctr = 0;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (mat[i][j] == true && vis[i][j] == false) {
				dfs(mat, m, n, vis, i, j);
				++ctr;
			}
		}
	}

	return ctr;
}

void dfs(bool mat[MAX][MAX], int m, int n, bool vis[MAX][MAX], int i, int j) {
	if (0 <= i && i < m && 0 <= j && j < n) {
		vis[i][j] = true;

		for (int rD = -1; rD <= 1; rD++) {
			for (int cD = -1; cD <= 1; cD++) {
				int newI = i + rD;
				int newJ = j + cD;

				if (0 <= newI && newI < m && 0 <= newJ && newJ < m) {
					if (mat[newI][newJ] == true && vis[newI][newJ] == false) {
						dfs(mat, m, n, vis, newI, newJ);
					}
				}
			}
		}
	}
}

