// http://www.geeksforgeeks.org/queries-in-a-matrix/

/*
3 3
R 1 2
P 1 1
P 2 1
C 1 2
P 1 1
P 2 1
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 1000

void input(int &, int &);
void fillArr(int [MAX], int);
void query(int [MAX], int, int [MAX], int);
void showArr(int [MAX], int, const char *);
void swapVal(int [MAX], int, int);

int main() {
	int row[MAX], m;
	int col[MAX], n;

	input(m, n);

	fillArr(row, m);
	fillArr(col, n);

	query(row, m, col, n);

	return 0;
}

// input and initialize
void input(int &m, int &n) {
	cout << "Enter no of rows:\t";
	cin >> m;

	cout << "Enter no of columns:\t";
	cin >> n;
}

void fillArr(int arr[MAX], int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = i;
	}
}

// output
void query(int row[MAX], int m, int col[MAX], int n) {
	char type;
	int i1, i2;

	cout << "\nEnter queries:-\n";
	getchar();

	while (true) {
		type = getc(stdin);
		cin >> i1 >> i2;

		switch (type) {
			case 'R':
				swapVal(row, i1 - 1, i2 - 1);
				showArr(row, m, "row[]");
				break;

			case 'C':
				swapVal(col, i1 - 1, i2 - 1);
				showArr(col, n, "col[]");
				break;

			case 'P':
				printf("mat[%d][%d] = %d\n", i1, i2, (row[i1 - 1] * n + col[i2 - 1] + 1));
				break;

			default:
				printf("Invalid Query\n");
				return;
		}
		getc(stdin);
	}
}

void showArr(int arr[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}

// swapVal
void swapVal(int arr[MAX], int p1, int p2) {
	int tmp = arr[p1];
	arr[p1] = arr[p2];
	arr[p2] = tmp;
}

