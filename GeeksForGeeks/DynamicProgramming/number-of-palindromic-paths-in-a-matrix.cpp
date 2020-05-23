
/*
3 4
a a a b
b a a a
a b b a
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <cmath>

using namespace std;
#define MAX 100

void input(char [MAX][MAX], int&, int&);
void showMat(char [MAX][MAX], int, int);
int countPalinPaths(char [MAX][MAX], int, int, pair <int, int>, pair <int, int>, map <pair <pair <int, int>, pair <int, int> >, int>&);
bool isValid(int, int, pair <int, int>);

int main() {
	char mat[MAX][MAX];
	int rows, cols;
	map <pair <pair <int, int>, pair <int, int> >, int> pathCount;

	input(mat, rows, cols);
	showMat(mat, rows, cols);

	printf("\nNo of palindromic paths is %d\n", countPalinPaths(mat, rows, cols, make_pair(0, 0), make_pair(rows - 1, cols - 1), pathCount));

	return 0;
}

void input(char mat[MAX][MAX], int& rows, int& cols) {
	printf("Enter dimensions of matrix:\t");
	scanf("%d%d", &rows, &cols);
	getc(stdin);

	printf("Enter matrix:-\n");
	for (int i = 0; i < rows; i++) {
		string line;
		getline(cin, line);

		mat[i][0] = line[0];
		for (int j = 2; j <= (2 * cols); j += 2) {
			mat[i][j / 2] = line[j];
		}
	}
}

int countPalinPaths(char mat[MAX][MAX], int rows, int cols, pair <int, int> sPos, pair <int, int> ePos, map <pair <pair <int, int>, pair <int, int> >, int>& pathCount) {
	if (!isValid(rows, cols, sPos) || !isValid(rows, cols, ePos)) {
		return 0;
	} else if (pathCount.find(make_pair(sPos, ePos)) != pathCount.end()) {
		return pathCount[make_pair(sPos, ePos)];
	} else {
		int sR = sPos.first;
		int sC = sPos.second;
		int eR = ePos.first;
		int eC = ePos.second;
		int count = 0;

		if (mat[sR][sC] == mat[eR][eC]) {
			int dist = (int) (abs(sR - eR) + abs(sC - eC));

			if (dist <= 1) {
				count = 1;
			} else {
				count += countPalinPaths(mat, rows, cols, make_pair(sR + 1, sC), make_pair(eR - 1, eC), pathCount);
				count += countPalinPaths(mat, rows, cols, make_pair(sR, sC + 1), make_pair(eR, eC - 1), pathCount);
				count += countPalinPaths(mat, rows, cols, make_pair(sR + 1, sC), make_pair(eR, eC - 1), pathCount);
				count += countPalinPaths(mat, rows, cols, make_pair(sR, sC + 1), make_pair(eR - 1, eC), pathCount);
			}
		}

		pathCount[make_pair(sPos, ePos)] = count;
		return count;
	}
}

void showMat(char mat[MAX][MAX], int rows, int cols) {
	printf("\nThe matrix is:-\n");

	cout << "\t";
	for (int j = 0; j < cols; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i < rows; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j < cols; j++) {
			printf("%c\t", mat[i][j]);
		}
		cout << endl;
	}
}

bool isValid(int rows, int cols, pair <int, int> pos) {
	if (pos.first < 0 || pos.first >= rows || pos.second < 0 || pos.second >= cols) {
		return false;
	} else {
		return true;
	}
}

