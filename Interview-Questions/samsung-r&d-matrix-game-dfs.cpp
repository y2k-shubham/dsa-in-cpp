/*
12 5
0 1 1 0 0
0 -1 0 1 -1
1 0 -1 -1 0
0 0 0 1 1
0 -1 -1 0 1
1 1 1 0 0
1 0 0 1 0
0 0 -1 -1 0
1 -1 1 1 0
0 0 -1 0 0
1 0 -1 -1 0
0 0 0 0 0
12 2

7 5
1 -1 0 0 1
-1 0 0 1 0
0 1 -1 0 1
1 0 0 -1 1
0 -1 1 0 1
0 1 -1 -1 -1
1 0 1 1 0
7 2

5 5
	0	1	2	3	4
0	1	1	0	0	0
1	1	-1	-1	-1	1
2	1	1	-1	-1	1
3	-1	-1	-1	1	-1
4	-1	-1	0	-1	0
5 2

5 5
1	1	0	0	0
1	-1	-1	-1	1
1	1	-1	-1	1
-1	-1	-1	1	-1
-1	-1	0	-1	0
5 2

6 5
-1 -1 -1 -1 -1
0 0 0 0 0
0 0 -1 0 0
-1 0 0 0 -1
0 0 0 0 0
1 -1 -1 -1 1
6 2

10 5
-1 -1 -1 -1 0
1 -1 0 0 -1
0 -1 0 0 0
-1 -1 0 -1 -1
0 -1 -1 -1 0
0 0 0 0 0
1 0 0 0 -1
0 0 0 0 0
-1 -1 0 -1 1
0 -1 -1 -1 0
10 2

12 5
-1 -1 0 -1 -1
0 1 0 -1 1
0 -1 0 1 0
-1 1 -1 1 0
0 -1 -1 1 -1
0 1 -1 -1 -1
0 -1 1 0 -1
-1 0 1 1 -1
-1 1 1 0 1
0 -1 -1 0 0
-1 0 1 -1 -1
-1 -1 1 -1 1
12 2
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <list>
#include <utility>

using namespace std;
#define ROW 13
#define COL 5

void input(int [ROW][COL], int&, int&, int&, int&);
void init(int [ROW][COL], int, int);
void init();
void showMat(int [ROW][COL], int, int, const char *);
void showStats(int);
int dfs(int [ROW][COL], int, int, int, int, bool, int [ROW][COL], int);
list <pair <int, int> > removeEnemies(int [ROW][COL], int, int, int);
void addEnemies(int [ROW][COL], list <pair <int, int> >);

int rowReachCount[ROW];
int recCallCount;
FILE * f;

int main() {
	int grid[ROW][COL];
	int maxGainTillHere[ROW][COL];
	int row, col;
	int sPosX, sPosY;

	input(grid, row, col, sPosX, sPosY);
	init(maxGainTillHere, row, col);
	init();

	showMat(grid, row, col, "grid[][]");
	showMat(maxGainTillHere, row, col, "maxGainTillHere[][]");

	int maxGain = -1;
//	printf("\nFirst call\n");
//	maxGain = max(maxGain, dfs(grid, row, col, sPosX - 1, sPosY - 1, false, maxGainTillHere, 0));
//	printf("\nSecond call\n");
//	maxGain = max(maxGain, dfs(grid, row, col, sPosX - 1, sPosY, false, maxGainTillHere, 0));
//	printf("\nThird call\n");
//	maxGain = max(maxGain, dfs(grid, row, col, sPosX - 1, sPosY + 1, false, maxGainTillHere, 0));

	printf("\nMax possible gain is %d\n", dfs(grid, row, col, sPosX, sPosY, false, maxGainTillHere, 0));
	showStats(row);

	fclose(f);

	return 0;
}

void input(int grid[ROW][COL], int& row, int& col, int& sPosX, int& sPosY) {
	printf("Enter dimensions of grid:\t");
	cin >> row >> col;

	printf("Enter grid:-\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> grid[i][j];
		}
	}
	for (int j = 0; j < col; j++) {
		grid[row][j] = 0;
	}

	printf("Enter starting position:\t");
	cin >> sPosX >> sPosY;
}

void init(int maxGainTillHere[ROW][COL], int row, int col) {
	for (int i = 0; i <= row; i++) {
		for (int j = 0; j < col; j++) {
			maxGainTillHere[i][j] = -1;
		}
	}
}

void init() {
	recCallCount = 0;
	memset(rowReachCount, 0, ROW * sizeof(int));
	f = fopen("matrix-game.txt", "w");
}

void showMat(int mat[ROW][COL], int row, int col, const char * name) {
	printf("\n%s matrix is:-\n", name);

	printf("\t");
	for (int j = 0; j < col; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < col; j++) {
			printf("%d\t", mat[i][j]);
		}
		cout << endl;
	}
}

void showStats(int row) {
	printf("\nTotal Number of recursive calls made is %d\n", recCallCount);
	printf("Row-reach count is:-\n");

	for (int i = 0; i < row; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		printf("%d\t", rowReachCount[i]);
	}
	cout << endl;
}

int dfs(int grid[ROW][COL], int row, int col, int r, int c, bool bombed, int maxGainTillHere[ROW][COL], int crrGain) {
	recCallCount++;

	crrGain += grid[r][c];
//	printf("at grid[%d][%d]\t", r, c);
//	fprintf(f, "at grid[%d][%d]\t", r, c);
	if (bombed == true) {
//		printf("bombed\t");
//		fprintf(f, "bombed\t");
	} else {
//		printf("not-bombed\t");
//		fprintf(f, "not-bombed\t");
	}
//	fprintf(f, "score = %d\t", crrGain);

	if (crrGain < 0) {
//		printf("game over\n");
//		fprintf(f, "game over\n");
		return -1;
	}

	if (r == 0) {
//		printf("Reached row 0\t", r, c);
//		fprintf(f, "Reached row 0\t", r, c);
		rowReachCount[0]++;
		if (bombed == true) {
			maxGainTillHere[r][c] = max(maxGainTillHere[r][c], crrGain);
//			printf("returned %d\n", maxGainTillHere[r][c]);
//			fprintf(f, "returned %d\n", maxGainTillHere[r][c]);
			return maxGainTillHere[r][c];
		} else {
//			printf("returned -1\n");
//			fprintf(f, "returned -1\n");
			return -1;
		}
	} else {
		if (maxGainTillHere[r][c] < crrGain) {
			maxGainTillHere[r][c] = crrGain;
		} else {
//			printf("returned -1\n");
//			fprintf(f, "returned -1\n");
			rowReachCount[r]++;
			return -1;
		}

		int maxGain = -1;

//		printf("making recursive call from grid[%d][%d]\n", r, c);
//		fprintf(f, "making recursive call from grid[%d][%d]\n", r, c);
		maxGain = (c > 0) ? max(maxGain, dfs(grid, row, col, r - 1, c - 1, bombed, maxGainTillHere, crrGain)) : maxGain;
		maxGain = max(maxGain, dfs(grid, row, col, r - 1, c, bombed, maxGainTillHere, crrGain));
		maxGain = (c < col - 1) ? max(maxGain, dfs(grid, row, col, r - 1, c + 1, bombed, maxGainTillHere, crrGain)) : maxGain;

		if (bombed == false) {
			list <pair <int, int> > enemPos = removeEnemies(grid, col, r, c);

//			printf("making recursive call with blast from grid[%d][%d]\n", r, c);
//			fprintf(f, "making recursive call with blast from grid[%d][%d]\n", r, c);
			maxGain = (c > 0) ? max(maxGain, dfs(grid, row, col, r - 1, c - 1, true, maxGainTillHere, crrGain)) : maxGain;
			maxGain = max(maxGain, dfs(grid, row, col, r - 1, c, true, maxGainTillHere, crrGain));
			maxGain = (c < col - 1) ? max(maxGain, dfs(grid, row, col, r - 1, c + 1, true, maxGainTillHere, crrGain)) : maxGain;

			addEnemies(grid, enemPos);
		}

//		printf("returned %d\n", maxGain);
		//		fprintf(f, "returned %d\n", maxGain);
		return maxGain;
	}
}

list <pair <int, int> > removeEnemies(int grid[ROW][COL], int col, int r, int c) {
	list <pair <int, int> > enemPos;
	for (int i = r - 1; i >= 0 && i >= r - 5; i--) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] == -1) {
				enemPos.push_back(make_pair(i, j));
				grid[i][j] = 0;
			}
		}
	}

	return enemPos;
}

void addEnemies(int grid[ROW][COL], list <pair <int, int> > enemPos) {
	if (enemPos.empty() == false) {
		for (list <pair <int, int> >::iterator i = enemPos.begin(); i != enemPos.end(); i++) {
			grid[(*i).first][(*i).second] = -1;
		}
	}
}

