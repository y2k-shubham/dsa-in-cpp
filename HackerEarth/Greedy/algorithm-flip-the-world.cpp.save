// https://www.hackerearth.com/practice/algorithms/greedy/basics-of-greedy-algorithms/practice-problems/algorithm/flips-the-world/

/*
8 6
1 0 0 1 1 0
1 1 0 1 0 0
0 1 0 1 1 0
1 0 1 0 1 1
0 1 0 1 0 1
0 0 1 1 1 0
1 1 1 0 1 1
1 0 0 0 1 0

4 3
1 0 1
1 1 0
1 0 1
0 0 0

5 5
0 0 0 1 1
0 0 0 1 1
0 0 0 1 1
1 1 1 1 1
1 1 1 1 1

1 1
1

1 1
0

4 4
0 0 0 0
1 1 1 0
0 1 0 1
1 0 1 1

4 4
1 1 1 0
1 0 1 1
0 0 0 1
1 1 0 0

4 4
0000
1110
0101
1011

4 4
1110
1011
0001
1100
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX][MAX], int &, int &);
void inputFile(int [MAX][MAX], int &, int &);
void showMat(int *, int, int, const char *);
void findFlips(int [MAX][MAX], int, int, int [2][MAX]);

int main() {
	int mat[MAX][MAX];
	int N, M;
	int flips[2][MAX];

	input(mat, N, M);
//	showMat(&mat[0][0], N, M, "mat[][]");

	memset(flips, 0, 2 * MAX * sizeof(int));
//	showMat(&flips[0][0], 2, M, "before calc, flips[][]");

	findFlips(mat, N, M, flips);

	return 0;
}

void input(int mat[MAX][MAX], int &N, int &M) {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> mat[i][j];
		}
	}
}

void inputFile(int mat[MAX][MAX], int &N, int &M) {
	FILE * f = fopen("flip_1", "r");

	fscanf(f, "%d", &N);
	fscanf(f, "%d", &M);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			fscanf(f, "%d", &mat[i][j]);
		}
	}

	fclose(f);
}

void showMat(int * tab, int N, int M, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int j = 0; j < M; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < N; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < M; j++) {
			printf("%d\t", * (tab + i * MAX + j));
		}
		cout << endl;
	}
}

void findFlips(int mat[MAX][MAX], int N, int M, int flips[2][MAX]) {
	int count = 0;

	for (int i = N - 1; i >= 0; i--) {
		for (int j = M - 1; j >= 0; j--) {
			int flipCount = flips[1][j] + flips[0][j + 1];
			bool isEven = ((flipCount % 2) == 0);

			if ((mat[i][j] == 0 && isEven) || (mat[i][j] == 1 && !isEven)) {
				count++;
				flips[0][j] = 1;
			}

			flips[0][j] += flips[0][j + 1];
		}

		for (int j = 0; j < M; j++) {
			flips[1][j] +=flips[0][j];
			flips[0][j] = 0;
		}

//		showMat(&flips[0][0], 2, M, "flip[][]");
	}

	printf("%d\n", count);
}

