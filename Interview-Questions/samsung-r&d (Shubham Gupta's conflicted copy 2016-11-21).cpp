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
void inputFile(int [MAX][MAX], int &, int &, const char *);
void inputRand(int [MAX][MAX], int &, int &);
void inputWorst(int [MAX][MAX], int &, int &);
void init(priority_queue <pair <int, pair <int, int> > > &, int, int);
void init(int [MAX][MAX], int, int);
void showTab(int [MAX][MAX], int, int, const char *);
void printTab(int [MAX][MAX], int, int, const char *);
void showQue(priority_queue <pair <int, pair <int, int> > >);
int modBFS(int [MAX][MAX], int, int, priority_queue <pair <int, pair <int, int> > > &, int [MAX][MAX]);
int modDFS_1(int [MAX][MAX], int, int, int [MAX][MAX], int *, int, int, int, int, int);
bool modDFS_2(int [MAX][MAX], int, int, int [MAX][MAX], int *, int, int, int, int, int);

int main() {
	int mat[MAX][MAX];
	int row, col;
	priority_queue <pair <int, pair <int, int> >, vector <pair <int, pair <int, int> > > > pQue;
	int minJmp[MAX][MAX];
	int minPathJmp;

	// Console Input
//	input(mat, row, col);
//	showTab(mat, row, col, "mat[][]");

	// Random inputs
	srand(time(NULL));
	inputRand(mat, row, col);
	printTab(mat, row, col, "mat[][]");
//	showTab(mat, row, col, "mat[][]");

	//Worst input
//	srand(time(NULL));
//	inputWorst(mat, row, col);

	// File input
//	char * fileName = (char *) malloc(100);
//	printf("Enter filename:\t");
//	scanf("%s", fileName);
//	inputFile(mat, row, col, fileName);
//	showTab(mat, row, col, "mat[][]");

	// BFS
	printf("\n===============BFS===============\n");
	init(pQue, row, col);
	showQue(pQue);

	init(minJmp, row, col);
	showTab(minJmp, row, col, "before BFS, minJmp[][]");

	minPathJmp = modBFS(mat, row, col, pQue, minJmp);

	showTab(minJmp, row, col, "after BFS, minJmp[][]");
	printf("\nMin(MaxJmp) for any path using BFS is %d\n", minPathJmp);

	// DFS
	printf("\n===============DFS===============\n");
	init(minJmp, row, col);
	showTab(minJmp, row, col, "before DFS, minJmp[][]");

	minPathJmp = INT_MAX;
	for (int j = 0; j < col; j++) {
//		minPathJmp = min(minPathJmp, modDFS_1(mat, row, col, minJmp, &minPathJmp, 1, -1, -1, row - 1, j));
//		printf("\n");
		modDFS_2(mat, row, col, minJmp, &minPathJmp, 1, -1, -1, row - 1, j);
	}

	showTab(minJmp, row, col, "after DFS, minJmp[][]");
	printf("\nMin(MaxJmp) for any path using DFS is %d\n", minPathJmp);

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

void inputFile(int mat[MAX][MAX], int &row, int &col, const char * fileName) {
	FILE * f = fopen(fileName, "r");

	fscanf(f, "%d", &row);
	fscanf(f, "%d", &col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fscanf(f, "%d", &mat[i][j]);
		}
		cout << endl;
	}

	fclose(f);
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

void inputWorst(int mat[MAX][MAX], int &row, int &col) {
	row = col = 50;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mat[i][j] = 1;
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
	FILE * f = fopen("samsung-r&d-random-input.txt", "w");

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

int modBFS(int mat[MAX][MAX], int row, int col, priority_queue <pair <int, pair <int, int> > > &pQue, int minJmp[MAX][MAX]) {
	int minPathJmp = INT_MAX;

	int iter = 0;
	int ctr = 0;
	while (!pQue.empty()) {
		pair <int, pair <int, int> > p = pQue.top();
		pQue.pop();
		++iter;

		int r = -((p.second).first);
		int c = -((p.second).second);
		int jmp = -(p.first);

//		printf("\npopped [%d][%d] %d\n", r, c, jmp);
		if (mat[r][c] == 3) {
//			printf("skipping as it is destination\n");
			continue;
		} else if (jmp > minJmp[r][c]) {
//			printf("skipping as a smaller path of len %d is already known\n", minJmp[r][c]);
			continue;
		}

		ctr++;
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

		//		showQue(pQue);
	}

	return minPathJmp;
//	printf("\nMin(MaxJmp) for any path using BFS is %d\n", minPathJmp);
//	printf("No of iterations (deque ops from que) is %d\n", iter);
//	printf("No of nodes explored is %d\n", ctr);
}

int modDFS_1(int mat[MAX][MAX], int row, int col, int minJmp[MAX][MAX], int * minJmpG, int cMaxJmp, int cMaxR, int cMaxC, int r, int c) {
	if (r < 0 || r > row || c < 0 || c > col) {
		return INT_MAX;
	} else if (mat[r][c] == 3) {
		minJmp[r][c] = min(minJmp[r][c], cMaxJmp);
		*minJmpG = minJmp[r][c];
//		printf("reached destination [%d][%d], updated minJmp[%d][%d] to %d and returned it\n", r, c, r, c, minJmp[r][c]);
		return minJmp[r][c];
	} else {
		int minJmpValG = INT_MAX;
		minJmp[r][c] = min(minJmp[r][c], cMaxJmp);
//		printf("at [%d][%d], updated minJmp[%d][%d] to %d\n", r, c, r, c, minJmp[r][c]);
//		printf("cMaxJmp = %d made from [%d][%d]\n", cMaxJmp, cMaxR, cMaxC);

		// move above
		for (int i = r - 1; i >= 0; i--) {
//			printf("for [%d][%d], prev cost = %d\tpossible min = %d, so trying DFS\n", i, c, minJmp[i][c], cMaxJmp);
			if (mat[i][c] > 0 && cMaxJmp < minJmp[i][c]) {
				int crrJmp = r - i;
				int minJmpValL;

				if (crrJmp >= *minJmpG) {
					continue;
				}

				if (crrJmp > cMaxJmp) {
					minJmpValL = modDFS_1(mat, row, col, minJmp, minJmpG, crrJmp, r, c, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, exploring another\n", r, c, minJmpValL);
				} else {
					minJmpValL = modDFS_1(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, returning as shorter path not possible\n", r, c, minJmpValL);
					if (minJmpValL != INT_MAX) {
						return minJmpValL;
					}
				}

				minJmpValG = min(minJmpValG, minJmpValL);
			}
		}

		// move below
		for (int i = r + 1; i < row; i++) {
//			printf("for [%d][%d], prev cost = %d\tpossible min = %d, so trying DFS\n", i, c, minJmp[i][c], cMaxJmp);
			if (mat[i][c] > 0 && cMaxJmp < minJmp[i][c]) {
				int crrJmp = i - r;
				int minJmpValL;

				if (crrJmp >= *minJmpG) {
					continue;
				}

				if (crrJmp > cMaxJmp) {
					minJmpValL = modDFS_1(mat, row, col, minJmp, minJmpG, crrJmp, r, c, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, exploring another\n", r, c, minJmpValL);
				} else {
					minJmpValL = modDFS_1(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, returning as shorter path not possible\n", r, c, minJmpValL);
					if (minJmpValL != INT_MAX) {
						return minJmpValL;
					}
				}

				minJmpValG = min(minJmpValG, minJmpValL);
			}
		}

		// move left
		if (c > 0 && mat[r][c - 1] > 0) {
//			printf("for [%d][%d], prev cost = %d\tnew cost = %d, so invoking DFS\n", r, c - 1, minJmp[r][c - 1], cMaxJmp);
			if (minJmp[r][c - 1] > cMaxJmp) {
				minJmpValG = min(minJmpValG, modDFS_1(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, r, c - 1));
			}
		}

		// move right
		if (c < col - 1 && mat[r][c + 1] > 0) {
//			printf("for [%d][%d], prev cost = %d\tnew cost = %d, so invoking DFS\n", r, c + 1, minJmp[r][c + 1], cMaxJmp);
			if (minJmp[r][c + 1] > cMaxJmp) {
				minJmpValG = min(minJmpValG, modDFS_1(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, r, c + 1));
			}
		}

		//		printf("at [%d][%d], returning minJmpVal = %d\n", r, c, minJmpValG);
		return minJmpValG;
	}
}

bool modDFS_2(int mat[MAX][MAX], int row, int col, int minJmp[MAX][MAX], int * minJmpG, int cMaxJmp, int cMaxR, int cMaxC, int r, int c) {
	if (r < 0 || r > row || c < 0 || c > col) {
		return false;
	} else if (mat[r][c] == 3) {
		minJmp[r][c] = min(minJmp[r][c], cMaxJmp);
		*minJmpG = minJmp[r][c];
//		printf("reached destination [%d][%d], updated minJmp[%d][%d] to %d and returned it\n", r, c, r, c, minJmp[r][c]);
		return true;
	} else {
		bool minJmpValG = false;
		minJmp[r][c] = min(minJmp[r][c], cMaxJmp);
//		printf("at [%d][%d], updated minJmp[%d][%d] to %d\n", r, c, r, c, minJmp[r][c]);
//		printf("cMaxJmp = %d made from [%d][%d]\n", cMaxJmp, cMaxR, cMaxC);

		// move above
		for (int i = r - 1; i >= 0; i--) {
//			printf("for [%d][%d], prev cost = %d\tpossible min = %d, so trying DFS\n", i, c, minJmp[i][c], cMaxJmp);
			if (mat[i][c] > 0 && cMaxJmp < minJmp[i][c]) {
				int crrJmp = r - i;
				bool minJmpValL;

				if (crrJmp >= *minJmpG) {
					continue;
				}

				if (crrJmp > cMaxJmp) {
					minJmpValL = modDFS_2(mat, row, col, minJmp, minJmpG, crrJmp, r, c, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, exploring another\n", r, c, minJmpValL);
				} else {
					minJmpValL = modDFS_2(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, returning as shorter path not possible\n", r, c, minJmpValL);
					if (minJmpValL == true) {
						return true;
					}
				}

				minJmpValG |= minJmpValL;
			}
		}

		// move below
		for (int i = r + 1; i < row; i++) {
//			printf("for [%d][%d], prev cost = %d\tpossible min = %d, so trying DFS\n", i, c, minJmp[i][c], cMaxJmp);
			if (mat[i][c] > 0 && cMaxJmp < minJmp[i][c]) {
				int crrJmp = i - r;
				bool minJmpValL;

				if (crrJmp >= *minJmpG) {
					continue;
				}

				if (crrJmp > cMaxJmp) {
					minJmpValL = modDFS_2(mat, row, col, minJmp, minJmpG, crrJmp, r, c, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, exploring another\n", r, c, minJmpValL);
				} else {
					minJmpValL = modDFS_2(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, i, c);
//					printf("at [%d][%d], one path of minJmpVal %d found, returning as shorter path not possible\n", r, c, minJmpValL);
					if (minJmpValL == true) {
						return true;
					}
				}

				minJmpValG |= minJmpValL;
			}
		}

		// move left
		if (c > 0 && mat[r][c - 1] > 0) {
//			printf("for [%d][%d], prev cost = %d\tnew cost = %d, so invoking DFS\n", r, c - 1, minJmp[r][c - 1], cMaxJmp);
			if (minJmp[r][c - 1] > cMaxJmp) {
				minJmpValG |= modDFS_2(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, r, c - 1);
			}
		}

		// move right
		if (c < col - 1 && mat[r][c + 1] > 0) {
//			printf("for [%d][%d], prev cost = %d\tnew cost = %d, so invoking DFS\n", r, c + 1, minJmp[r][c + 1], cMaxJmp);
			if (minJmp[r][c + 1] > cMaxJmp) {
				minJmpValG |= modDFS_2(mat, row, col, minJmp, minJmpG, cMaxJmp, cMaxR, cMaxC, r, c + 1);
			}
		}

		//		printf("at [%d][%d], returning minJmpVal = %d\n", r, c, minJmpValG);
		return minJmpValG;
	}
}

