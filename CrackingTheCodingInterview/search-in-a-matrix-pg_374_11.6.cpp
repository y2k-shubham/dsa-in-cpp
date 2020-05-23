// http://www.practice.geeksforgeeks.org/problem-page.php?pid=820

/*
4 4
15	20	40	85
20	35	80	95
30	55	95	105
40	80	100	120
55

4 4
15	20	40	85
20	35	80	95
30	55	95	105
40	80	100	120
100

4 4
15	20	40	85
20	35	80	95
30	55	95	105
40	80	100	120
121
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX][MAX], int &, int &, int &);
void search(int [MAX][MAX], int, int, int);

int main() {
	int mat[MAX][MAX];
	int m, n;
	int ele;

	input(mat, m, n, ele);
	search(mat, m, n, ele);

	return 0;
}

void input(int mat[MAX][MAX], int &m, int &n, int &ele) {
	cout << "Enter dimensions of matrix:\t";
	cin >> m >> n;

	cout << "Enter elements of matrix:-\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> mat[i][j];
		}
	}

	cout << "Enter element to be searched:\t";
	cin >> ele;
}

void search(int mat[MAX][MAX], int m, int n, int ele) {
	int i, j;

	i = 0;
	j = n - 1;
	while (i < m && j >= 0) {
		if (mat[i][j] < ele) {
			i++;
		} else if (mat[i][j] > ele) {
			j--;
		} else {
			printf("\n%d found at mat[%d][%d]\n", ele, i, j);
			break;
		}
	}
}
