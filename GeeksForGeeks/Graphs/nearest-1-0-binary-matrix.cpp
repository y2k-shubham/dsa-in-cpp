// http://www.geeksforgeeks.org/nearest-1-0-binary-matrix/
// Quite Similar: http://www.geeksforgeeks.org/find-shortest-distance-guard-bank/

/*
3 4
0 0 0 1
0 0 1 1
0 1 1 0
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <queue>
#include <utility>

using namespace std;
#define MAX 100

void input(int [MAX][MAX], int &, int &);
void init(int [MAX][MAX], int, int);
void init(int [MAX][MAX], int, int, int [MAX][MAX], queue <pair <int, int> > &);
void showTab(int [MAX][MAX], int, int, const char *);
void bfs(int [MAX][MAX], int, int, queue <pair <int, int> >);

int main() {
	int mat[MAX][MAX], row, col;
	int dist[MAX][MAX];
	queue <pair <int, int> > que;

	input(mat, row, col);
	showTab(mat, row, col, "mat[][]");

	init(dist, row, col);
	init(mat, row, col, dist, que);

	bfs(dist, row, col, que);
	showTab(dist, row, col, "dist[][]");

	return 0;
}

void input(int mat[MAX][MAX], int &row, int &col) {
	cout << "Enter dimensions of matrix:\t";
	cin >> row >> col;

	cout << "Enter the matrix:-\n";
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> mat[i][j];
		}
	}
}

void init(int mat[MAX][MAX], int row, int col, int dist[MAX][MAX], queue <pair <int, int> > &que) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (mat[i][j] == 1) {
				dist[i][j] = 0;
				que.push(make_pair(i, j));
			}
		}
	}
}

void init(int dist[MAX][MAX], int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			dist[i][j] = INT_MAX;
		}
	}
}

void showTab(int tab[MAX][MAX], int row, int col, const char * name) {
	printf("\n%s matrix is:-\n", name);

	cout << "Ind:\t";
	for (int j = 0; j < col; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < col; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

void bfs(int dist[MAX][MAX], int row, int col, queue <pair <int, int> > que) {
	while (!que.empty()) {
		pair <int, int> p = que.front();
		que.pop();

		int r = p.first;
		int c = p.second;

		// above [r][c]
		if (r > 0 && dist[r][c] + 1 < dist[r - 1][c]) {
			dist[r - 1][c] = dist[r][c] + 1;
			que.push({r - 1, c});
		}

		// right of [r][c]
		if (c < col && dist[r][c] + 1 < dist[r][c + 1]) {
			dist[r][c + 1] = dist[r][c] + 1;
			que.push({r, c + 1});
		}

		// below [r][c]
		if (r < row && dist[r][c] + 1 < dist[r + 1][c]) {
			dist[r + 1][c] = dist[r][c] + 1;
			que.push({r + 1, c});
		}

		// left of [r][c]
		if (c > 0 && dist[r][c] + 1 < dist[r][c - 1]) {
			dist[r][c - 1] = dist[r][c] + 1;
			que.push({r, c - 1});
		}
	}
}

