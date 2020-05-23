// TusharRoy

/*
7
0 1
1 2
3 4
5 6
4 5
2 6
-1 -1
*/

#include <cstdio>
#include <iostream>

struct node {
	int rank;
	int parent;
};

using namespace std;
#define MAX 100

void init(node [MAX], int);
void showArr(node [MAX], int);
int findSet(node [MAX], int);

int main() {
	node arr[MAX];
	int n;

	// input
	cout << "Enter no of nodes:\t";
	cin >> n;

	// initialization
	init(arr, n);
	showArr(arr, n);

	// union queries
	int nod_1, nod_2;

	cout << "Enter edge (n1, n2):\t";
	cin >> nod_1 >> nod_2;
	while (nod_1 >= 0 && nod_1 < n && nod_2 >= 0 && nod_2 < n) {
		int p1 = findSet(arr, nod_1);
		int p2 = findSet(arr, nod_2);

		if (p1 == p2) {
			// do nothing, they are already in same set
		} else if (arr[p1].rank > arr[p2].rank) {
			arr[p2].parent = p1;
			arr[p2].rank = 0;
		} else if (arr[p1].rank < arr[p2].rank) {
			arr[p1].parent = p2;
			arr[p1].rank = 0;
		} else {
			arr[p2].parent = p1;
			arr[p2].rank = 0;
			arr[p1].rank++;
		}
		showArr(arr, n);

		cout << "Enter edge (n1, n2):\t";
		cin >> nod_1 >> nod_2;
	}

	return 0;
}

void init(node arr[MAX], int n) {
	for (int i = 0; i < n; i++) {
		arr[i].rank = 0;
		arr[i].parent = i;
	}
}

void showArr(node arr[MAX], int n) {
	cout << "\nList of nodes is:-\n";

	cout << "Nod:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", i);
	}
	cout << endl;

	cout << "Par:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i].parent);
	}
	cout << endl;

	cout << "Rnk:\t";
	for (int i = 0; i < n; i++) {
		printf("%d\t", arr[i].rank);
	}
	cout << endl << endl;
}

int findSet(node arr[MAX], int i) {
	if (arr[i].parent == i) {
		return i;
	} else {
		return (arr[i].parent = findSet(arr, arr[i].parent));
	}
}
