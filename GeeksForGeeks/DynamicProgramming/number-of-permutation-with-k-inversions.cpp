// http://www.geeksforgeeks.org/number-of-permutation-with-k-inversions/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void init(int [MAX][MAX], int, int);
void calc(int [MAX][MAX], int, int);
void showTab(int [MAX][MAX], int, int, const char *);

int main() {
	int N, K;
	int tab[MAX][MAX];			// N + 1 = no of columns, K + 1 = no of rows

	cout << "Enter N, K:\t";
	cin >> N >> K;

	init(tab, N, K);
	showTab(tab, N, K, "after initialization");

	calc(tab, N, K);
	showTab(tab, N, K, "after calculation");

	return 0;
}

void init(int tab[MAX][MAX], int N, int K) {
	// for K = 0, inversions = 1 (sorted array)
	for (int j = 0; j <= N; j++) {
		tab[0][j] = 1;
	}

	// for N = 0, inversions = 0 (no permutation possible)
	for (int i = 0; i <= K; i++) {
		tab[i][0] = 0;
	}
}

void calc(int tab[MAX][MAX], int N, int K) {
	for (int j = 1; j <= N; j++) {
		int sum = tab[0][j - 1];
		for (int i = 1; i < j && i <= K; i++) {
			sum += tab[i][j - 1];
			tab[i][j] = sum;
		}
	}
}

void showTab(int tab[MAX][MAX], int N, int K, const char * when) {
	printf("\n%s, tab[][] is:-\n", when);

	cout << "\t";
	for (int j = 0; j <= N; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i <= K; i++) {
		printf("[%d]\t", i);
		for (int j = 0; j <= N; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
	cout << endl;
}

