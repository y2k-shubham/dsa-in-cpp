
/*
6 9
1 1 1 0 0 1 1 1 1
0 1 0 1 1 3 0 1 0
0 0 1 1 0 1 0 0 1
1 0 0 0 0 1 0 1 0
0 1 0 1 0 0 1 0 1
2 1 1 1 1 1 1 1 1

4 5
1 1 1 0 1
0 0 1 3 1
0 1 1 0 0
2 1 1 1 1

9 8
0 1 1 1 1 1 1 0
1 1 0 0 1 1 1 0
0 0 0 0 1 1 0 0
0 0 0 1 1 1 0 0
1 0 0 1 0 3 1 1
0 0 0 1 0 0 0 1
0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 1
2 1 1 1 1 1 1 1
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <utility>
#include <map>
#include <climits>
#include <cstdlib>
#include <ctime>

using namespace std;
#define MAX 55

void input(int [MAX][MAX], int &, int &);
void inputRand(int [MAX][MAX], int &, int &);
void init(priority_queue <pair <int, pair <int, int> >> &, int, int);
void init(int [MAX][MAX], int, int);
void showTab(int [MAX][MAX], int, int, const char *);
void printTab(int [MAX][MAX], int, int, const char *);
void showQue(priority_queue <pair <int, pair <int, int> > >);
void modBFS(int [MAX][MAX], int, int, priority_queue <pair <int, pair <int, int> > > &, int [MAX][MAX]);

int main() {
	int mat[MAX][MAX];
	int row, col;
	priority_queue <pair <int, pair <int, int> >, vector <pair <int, pair <int, int> > >> pQue;
	int minJmp[MAX][MAX];

//	input(mat, row, col);
//	showTab(mat, row, col, "mat[][]");
	srand(time(NULL));
	inputRand(mat, row, col);
	printTab(mat, row, col, "mat[][]");

	init(pQue, row, col);
	showQue(pQue);

	init(minJmp, row, col);
	showTab(minJmp, row, col, "minJmp[][]");

	modBFS(mat, row, col, pQue, minJmp);

	return 0;
}

void input(int mat[MAX][MAX], int &row, int &col) {
	cout << "Enter dimensions:\t";
	cin >> row >> col;

	printf("Enter elements of table:-\n");
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cin >> mat[i][j];
		}
	}
}

void inputRand(int mat[MAX][MAX], int &row, int &col) {
	row = col = 10;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = rand() % 2;
		}
	}

	for (int j = 0; j < col; j++) {
		mat[row - 1][j] = 1;
	}

	int r = 90;
	while (r >= row - 1) {
		r = rand() % row;
	}
	int c = rand() % col;

	mat[r][c] = 3;
	mat[row - 1][0] = 2;
}

void init(priority_queue <pair <int, pair <int, int> > > &pQue, int row, int col) {
	for (int j = 0; j < col; j++) {
		pQue.push(make_pair(-1, make_pair(-(row - 1), -j)));
	}
}

void init(int minJmp[MAX][MAX], int row, int col) {
	for (int i = 0; i < row - 1; i++) {
		for (int j = 0; j < col; j++) {
			minJmp[i][j] = INT_MAX;
		}
	}

	for (int j = 0; j < col; j++) {
		minJmp[row - 1][j] = 1;
	}
}

void showTab(int mat[MAX][MAX], int row, int col, const char * name) {
	printf("\nThe %s table is:-\n", name);

	printf("Ind:\t");
	for (int j = 0; j < col; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < col; j++) {
			if (mat[i][j] == INT_MAX) {
				printf("_\t");
			} else {
				printf("%d\t", mat[i][j]);
			}
		}
		cout << endl;
	}
	cout << endl;
}

void printTab(int mat[MAX][MAX], int row, int col, const char * name) {
	FILE * f = fopen("samsung-r&d.txt", "w");

	fprintf(f, "\nThe %s table is:-\n", name);

	fprintf(f, "Ind:\t");
	for (int j = 0; j < col; j++) {
		fprintf(f, "[%d]\t", j);
	}
	fprintf(f, "\n");

	for (int i = 0; i < row; i++) {
		fprintf(f, "[%d]\t", i);
		for (int j = 0; j < col; j++) {
			if (mat[i][j] == INT_MAX) {
				fprintf(f, "_\t");
			} else {
				fprintf(f, "%d\t", mat[i][j]);
			}
		}
		fprintf(f, "\n");
	}
	fprintf(f, "\n");

	fclose(f);
}

void showQue(priority_queue <pair <int, pair <int, int> > > pQue) {
	printf("\nPriority Que is:-\n");

	while (!pQue.empty()) {
		pair <int, pair <int, int> > p = pQue.top();
		pQue.pop();

		printf("[%d][%d]\t%d\n", -((p.second).first), -((p.second).second), -(p.first));
	}
	cout << endl;
}

void modBFS(int mat[MAX][MAX], int row, int col, priority_queue <pair <int, pair <int, int> > > &pQue, int minJmp[MAX][MAX]) {
	int minPathJmp = INT_MAX;

	while (!pQue.empty()) {
		pair <int, pair <int, int> > p = pQue.top();
		pQue.pop();

		int r = -((p.second).first);
		int c = -((p.second).second);
		int jmp = -(p.first);
//		printf("\npopped [%d][%d] %d\n", r, c, jmp);
		if (mat[r][c] == 3) {
//			printf("skipping as it is destination\n");
			continue;
		}

		// above cells
		for (int i = 0; i < r; i++) {
//			printf("[%d][%d], crrDist = %d\tnewDist = %d\n", i, c, minJmp[i][c], (jmp + r - i));
			if (mat[i][c] > 0 && minJmp[i][c] > max(jmp, (r - i))) {
//				printf("updated dist of [%d][%d] from %d to %d\n", i, c, minJmp[i][c], max(jmp, (r - i)));
				minJmp[i][c] = max(jmp, (r - i));
				pQue.push(make_pair(-minJmp[i][c], make_pair(-i, -c)));

				if (mat[i][c] == 3) {
//					printf("minPathJmp = min(%d, %d)\n", minPathJmp, minJmp[i][c]);
					minPathJmp = min(minPathJmp, minJmp[i][c]);
				}
			}
		}

		// below cells
		for (int i = row - 1; i > r; i--) {
//			printf("[%d][%d], crrDist = %d\tnewDist = %d\n", i, c, minJmp[i][c], (jmp + i - r));
			if (mat[i][c] > 0 && minJmp[i][c] > max(jmp, (i - r))) {
//				printf("updated dist of [%d][%d] from %d to %d\n", i, c, minJmp[i][c], max(jmp, (i - r)));
				minJmp[i][c] = max(jmp, (i - r));
				pQue.push(make_pair(-minJmp[i][c], make_pair(-i, -c)));

				if (mat[i][c] == 3) {
//					printf("minPathJmp = min(%d, %d)\n", minPathJmp, minJmp[i][c]);
					minPathJmp = min(minPathJmp, minJmp[i][c]);
				}
			}
		}

		// left cells
		for (int j = c - 1; c >= 0 && mat[r][j] > 0; j--) {
//			printf("[%d][%d], crrDist = %d\tnewDist = %d\n", r, j, minJmp[r][j], (jmp));
			if (mat[r][c] > 0 && minJmp[r][j] > jmp) {
//				printf("updated dist of [%d][%d] from %d to %d\n", r, j, minJmp[r][j], jmp);
				minJmp[r][j] = jmp;
				pQue.push(make_pair(-minJmp[r][j], make_pair(-r, -j)));

				if (mat[r][j] == 3) {
//					printf("minPathJmp = min(%d, %d)\n", minPathJmp, minJmp[r][j]);
					minPathJmp = min(minPathJmp, minJmp[r][j]);
				}
			}
		}

		// right cells
		for (int j = c + 1; c < col && mat[r][j] > 0; j++) {
//			printf("[%d][%d], crrDist = %d\tnewDist = %d\n", r, j, minJmp[j][j], (jmp));
			if (mat[r][c] > 0 && minJmp[r][j] > jmp) {
//				printf("updated dist of [%d][%d] from %d to %d\n", r, j, minJmp[r][j], jmp);
				minJmp[r][j] = jmp;
				pQue.push(make_pair(-minJmp[r][j], make_pair(-r, -j)));

				if (mat[r][j] == 3) {
//					printf("minPathJmp = min(%d, %d)\n", minPathJmp, minJmp[r][j]);
					minPathJmp = min(minPathJmp, minJmp[r][j]);
				}
			}
		}

		//		showQue(pQue);
	}

	printf("\nMin(MaxJmp) for any path is %d\n", minPathJmp);
}

