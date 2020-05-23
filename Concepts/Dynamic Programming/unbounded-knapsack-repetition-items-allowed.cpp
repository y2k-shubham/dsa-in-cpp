// http://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1599

/*
2	100
1 30
1 50

4	8
10 40 50 70
1 3 4 5

2	3
1 1
2 1

4	8
1 4 5 7
1 3 4 5

34 387
78 16 94 36 87 93 50 22 63 28 91 60 64 27 41 27 73 37 12 69 68 30 83 31 63 24 68 36 30 3 23 59 70 68
94 57 12 43 30 74 22 20 85 38 99 25 16 71 14 27 92 81 57 74 63 71 97 82 6 26 85 28 37 6 47 30 14 58

*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 600

void input(int [MAX], int [MAX], int&, int&);
void fillTab(int [MAX], int [MAX], int, int, int [MAX][MAX]);
void showArr(int [MAX], int, const char *);
void showTab(int [MAX], int [MAX], int, int, int [MAX][MAX], const char *);

int main() {
	int cap;
	int wgt[MAX], val[MAX], n;
	int tab[MAX][MAX];

	input(wgt, val, n, cap);

	showArr(wgt, n, "wgt[] array");
	showArr(val, n, "val[] array");

	memset(tab, 0, (n + 1) * MAX * sizeof(int));
	showTab(wgt, val, n, cap, tab, "before filling");

	fillTab(wgt, val, n, cap, tab);
	showTab(wgt, val, n, cap, tab, "after filling");

	return 0;
}

void input(int wgt[MAX], int val[MAX], int& n, int& cap) {
	printf("Enter no of different items:\t");
	cin >> n;

	cout << "Enter capacity of knap-sack:\t";
	cin >> cap;

	printf("Enter values of items:\t");
	for (int i = 1; i <= n; i++) {
		cin >> val[i];
	}

	printf("Enter weights of items:\t");
	for (int i = 1; i <= n; i++) {
		cin >> wgt[i];
	}
}

void fillTab(int wgt[MAX], int val[MAX], int n, int cap, int tab[MAX][MAX]) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= cap; j++) {
			if (wgt[i] > j) {
				tab[i][j] = tab[i - 1][j];
			} else {
				tab[i][j] = max(tab[i - 1][j], tab[i][j - wgt[i]] + val[i]);
			}
		}
	}
}

void showArr(int arr[MAX], int len, const char * msg) {
	printf("\n%s is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 1; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTab(int wgt[MAX], int val[MAX], int n, int cap, int tab[MAX][MAX], const char * when) {
	printf("\n%s, tab[][] is:-\n", when);

	printf("\t");
	for (int j = 1; j <= cap; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 1; i <= n; i++) {
		printf("%d,%d\t", val[i], wgt[i]);
		for (int j = 1; j <= cap; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
}

