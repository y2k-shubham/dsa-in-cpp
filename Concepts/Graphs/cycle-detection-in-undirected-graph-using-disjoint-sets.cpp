// http://www.geeksforgeeks.org/union-find/
// https://www.youtube.com/watch?v=n_t0a_8H8VY&spfreload=10

/*
Input:
7
0 1
1 2
3 4
5 6
4 5
2 6
-1 -1

Output: No cycle

Input:
6
0 1
3 5
2 4
2 1
5 4
3 2

Output: Cycle
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void init(int [MAX], int, int);
void input(int [MAX], int [MAX], int);
void output(int [MAX], int);
void makeUnion(int [MAX], int [MAX], int, int);
int findSet(int [MAX], int);

int main() {
	int n;
	int par[MAX];
	int ran[MAX];

	printf("Enter no of nodes:\t");
	scanf("%d", &n);

	init(par, n, -1);
	init(ran, n, 0);

	input(par, ran, n);
	output(par, n);

	return 0;
}

void init(int arr[MAX], int n, int val) {
	for (int i = 0; i < n; i++) {
		if (val < 0) {
			arr[i] = i;
		} else {
			arr[i] = val;
		}
	}
}

void input(int par[MAX], int ran[MAX], int n) {
	int nod_1, nod_2;

	printf("\nEnter edges as (node_1, node_2):-\n(Enter -1 to terminate)\n");
	scanf("%d%d", &nod_1, &nod_2);

	while (nod_1 != -1 && nod_2 != -1) {
		makeUnion(par, ran, nod_1, nod_2);
		//output(par, n);
		scanf("%d%d", &nod_1, &nod_2);
	}
}

void output(int par[MAX], int n) {
	printf("\nThe output graph is:-\n");
	for (int i = 0; i < n; i++) {
		printf("par[%d] = %d\n", i, findSet(par, i));
	}
}

void makeUnion(int par[MAX], int ran[MAX], int nod_1, int nod_2) {
	int par_1 = findSet(par, nod_1);
	int par_2 = findSet(par, nod_2);

	if (par_1 != par_2) {
		if (ran[par_1] == ran[par_2]) {
			ran[par_1]++;
			par[par_2] = par_1;
		} else if (ran[par_1] > ran[par_2]) {
			par[par_2] = par_1;
		} else {
			par[par_1] = par_2;
		}
	} else {
		printf("Cycle found on edge %d-%d\n++++++++", nod_1, nod_2);
	}
}

int findSet(int par[MAX], int nod) {
	if (par[nod] == nod) {
		return nod;
	} else {
		par[nod] = findSet(par, par[nod]);
		return par[nod];
	}
}
