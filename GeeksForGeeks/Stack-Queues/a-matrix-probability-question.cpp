// http://www.geeksforgeeks.org/a-matrix-probability-question/
#include <cstdio>

void input(int &, int &, int &, int &, int &);
float findProbability(int, int, int, int, int);

int main() {
	int m, n;
	int i, j;
	int N;

	input(m, n, i, j, N);
	printf("\nProbability of staying within the grid is:\t%f\n", findProbability(m, n, i, j, N));

	return 0;
}

void input(int &m, int &n, int &i, int &j, int &N) {
	printf("Enter size of matrix mxn:\t");
	scanf("%d%d", &m, &n);

	printf("Enter initial position:\t\t");
	scanf("%d%d", &i, &j);

	printf("Enter no of moves allowed:\t");
	scanf("%d", &N);
}

float findProbability(int m, int n, int i, int j, int movesLeft) {
	if (movesLeft == 0) {
		if ((i < 0 || i == m) || (j < 0 || j == n)) {
			return 0.0f;
		} else {
			return 1.0f;
		}
	} else {
		float prob;

		prob = findProbability(m, n, i - 1, j, movesLeft - 1);
		prob += findProbability(m, n, i + 1, j, movesLeft - 1);

		prob += findProbability(m, n, i, j - 1, movesLeft - 1);
		prob += findProbability(m, n, i, j + 1, movesLeft - 1);

		return prob * 0.25f;
	}
}
