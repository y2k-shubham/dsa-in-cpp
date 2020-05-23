#include <bits/stdc++.h>
using namespace std;
#define N 5

void genMultiples(bool [N][N]);
void showMultiples(bool [N][N]);
int findWays(bool isMultiple[N][N], vector <pair <int, bool> >, int);
void swapPos(vector <pair <int, bool> >&, int, int);

int main() {
	bool isMultiple[N][N];
	vector <pair <int, bool> > vec(N + 1);

	genMultiples(isMultiple);
//	showMultiples(isMultiple);

	for (int i = 1; i <= N; i++) {
		vec[i].first = i;
		vec[i].second = false;
	}
	cout << findWays(isMultiple, vec, 1) << endl;

	return 0;
}

void genMultiples(bool isMultiple[N][N]) {
	memset(isMultiple, false, N * N * sizeof(bool));
	for (int i = 1; i < N; i++) {
		for (int mult = i; mult < N; mult += i) {
			isMultiple[i][mult] = true;
		}
	}
}

void showMultiples(bool isMultiple[N][N]) {
	printf("Multiples set is:-\n");
	for (int i = 1; i < N; i++) {
		printf("%d\t->\t", i);
		for (int j = 0; j < N; j++) {
			if (isMultiple[i][j] == true) {
				printf("%d ", j);
			}
		}
		cout << endl;
	}
}

int findWays(bool isMultiple[N][N], vector <pair <int, bool> > vec, int pos) {
	if (pos >= N) {
		return 1;
	} else if (vec[pos].second == false) {
		int totalWays = findWays(isMultiple, vec, pos + 1);
		int num = vec[pos].first;

		for (int i = pos + 1; i < N; i++) {
			if (vec[i].second == false && (isMultiple[num][i] || isMultiple[i][num]) && (isMultiple[pos][vec[i].first] || isMultiple[vec[i].first][pos])) {
				swapPos(vec, pos, i);
				vec[i].second = true;
				vec[pos].second = true;

				totalWays += findWays(isMultiple, vec, pos + 1);

				swapPos(vec, pos, i);
				vec[i].second = false;
				vec[pos].second = false;
			}
		}

		return totalWays;
	} else {
		return findWays(isMultiple, vec, pos + 1);
	}
}

void swapPos(vector <pair <int, bool> >& vec, int p1, int p2) {
	int tmp = vec[p1].first;
	vec[p1].first = vec[p2].first;
	vec[p2].first = tmp;
}


