// TusharRoy

/*
4
1
0 3 15	0 1 3	0 2 6
1 2 -2
2 3 2
3 0 1
-1 -1 -1
*/

#include <cstdio>
#include <iostream>
#include <climits>
#include <cstdlib>

using namespace std;
#define MAX 100

void input_STDIN(int [MAX][MAX], int &);
void input_FILE(int [MAX][MAX], int &);
void init(int [MAX][MAX], int);
void init(int [MAX][MAX], int [MAX][MAX], int, int);
void showMat(int [MAX][MAX], int, const char *);
void floyd(int [MAX][MAX], int, int [MAX][MAX], int [MAX][MAX]);
int add(int, int);

int main() {
	int adjMat[MAX][MAX], n;
	int vertDist[MAX][MAX], vertPath[MAX][MAX];

//	input_STDIN(adjMat, n);
	input_FILE(adjMat, n);
	printf("\n================================\n\n");
	showMat(adjMat, n, "adjacency matrix");

	init(vertDist, adjMat, n, INT_MAX);
	init(vertPath, adjMat, n, n);

	printf("================================\n\n");
	showMat(vertDist, n, "distance matrix before running floyd's algorithm");
	showMat(vertPath, n, "path matrix before running floyd's algorithm");

	floyd(adjMat, n, vertDist, vertPath);

	printf("================================\n\n");
	showMat(vertDist, n, "distance matrix after running floyd's algorithm");
	showMat(vertPath, n, "path matrix after running floyd's algorithm");

	return 0;
}

// input and initialization
void input_STDIN(int adjMat[MAX][MAX], int &n) {
	cout << "Enter no of vertices:\t";
	cin >> n;

	init(adjMat, n);
	int src, dst, wgt;
	int type;

	cout << "0\tUndirected Graph\n1\tDirected Graph\nEnter type:\t";
	cin >> type;

	cout << "Enter edges as (src, dst, wgt):-" << endl;
	cin >> src >> dst >> wgt;

	while (src >= 0 && dst >= 0 && src < n && dst < n) {
		adjMat[src][dst] = wgt;
		if (type == 0) {
			adjMat[dst][src] = wgt;
		}

		cin >> src >> dst >> wgt;
	}
}

void input_FILE(int adjMat[MAX][MAX], int &n) {
	FILE * f = fopen("floyd_ip_1.txt", "r");

	if (f == NULL) {
		cout << "Couldn't open file" << endl;
		return;
	}

	cout << "Enter no of vertices:\t";
	fscanf(f, "%d", &n);
	cout << n << endl;

	init(adjMat, n);
	int src, dst, wgt;
	int type;

	cout << "0\tUndirected Graph\n1\tDirected Graph\nEnter type:\t";
	fscanf(f, "%d", &type);
	cout << type << endl;

	cout << "Enter edges as (src, dst, wgt):-" << endl;
	fscanf(f, "%d%d%d", &src, &dst, &wgt);
	cout << src << " " << dst << " " << wgt << endl;

	while (src >= 0 && dst >= 0 && src < n && dst < n) {
		adjMat[src][dst] = wgt;
		if (type == 0) {
			adjMat[dst][src] = wgt;
		}

		fscanf(f, "%d%d%d", &src, &dst, &wgt);
		cout << src << " " << dst << " " << wgt << endl;
	}

	fclose(f);
}

void init(int adjMat[MAX][MAX], int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			adjMat[i][j] = INT_MAX;
		}
	}
}

void init(int mat[MAX][MAX], int adjMat[MAX][MAX], int n, int defVal) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				if (defVal == INT_MAX) {
					mat[i][j] = 0;
				} else {
					mat[i][j] = n;
				}
			} else if (adjMat[i][j] == INT_MAX) {
				mat[i][j] = defVal;
			} else if (defVal == INT_MAX) {
				mat[i][j] = adjMat[i][j];
			} else {
				mat[i][j] = i;
			}
		}
	}
}

// output
void showMat(int mat[MAX][MAX], int n, const char * name) {
	printf("%s is:-\n", name);

	cout << "\t";
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);

		for (int j = 0; j < n; j++) {
			if (mat[i][j] == INT_MAX) {
				printf("INF\t");
			} else {
				printf("%d\t", mat[i][j]);
			}
		}
		cout << endl;
	}
	cout << endl;
}

// floyd's algorithm
void floyd(int adjMat[MAX][MAX], int n, int vertDist[MAX][MAX], int vertPath[MAX][MAX]) {
	for (int k = 0; k < n; k++) {
//		printf("\n================================\n\n");
//		cout << "k = " << k << endl;

		for (int i = 0; i < n; i++) {
//			printf("i = %d\n", i);
//			printf("--------------\n");

			for (int j = 0; j < n; j++) {
//				printf("d[%d][%d] = ", i, j);
//				if (vertDist[i][j] == INT_MAX) {
//					printf("INF\t>\t");
//				} else {
//					printf("%d\t>\t", vertDist[i][j]);
//				}
//
//				printf("d[%d][%d] = ", i, k);
//				if (vertDist[i][k] == INT_MAX) {
//					printf("INF\t+\t");
//				} else {
//					printf("%d\t+\t", vertDist[i][k]);
//				}
//
//				printf("d[%d][%d] = ", k, j);
//				if (vertDist[k][j] == INT_MAX) {
//					printf("INF\t");
//				} else {
//					printf("%d\t", vertDist[k][j]);
//				}

				if (add(vertDist[i][k], vertDist[k][j]) < vertDist[i][j]) {
//					printf("T\n");
					vertDist[i][j] = add(vertDist[i][k], vertDist[k][j]);
					vertPath[i][j] = vertPath[k][j];
				} else {
//					printf("F\n");
				}
			}
//			cout << endl;
//
//			char * str_1 = (char *) malloc(100 * sizeof(char));
//			sprintf(str_1, "distance matrix after k = %d and i = %d", k, i);
//			showMat(vertDist, n, str_1);
//
//			char * str_2 = (char *) malloc(100 * sizeof(char));
//			sprintf(str_2, "path matrix after k = %d and i = %d", k, i);
//			showMat(vertPath, n, str_2);
		}
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return (a + b);
	}
}

