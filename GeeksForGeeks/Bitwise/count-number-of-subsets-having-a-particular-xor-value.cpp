// http://www.geeksforgeeks.org/count-number-of-subsets-having-a-particular-xor-value/

/*
4
6 9 4 2
6

5
1 2 3 4 5
4

10
78 58 62 64 5 45 81 27 61 91
24
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;
#define MAX 100

// input
void input(int [MAX], int &, int &, int &);
// output
void showArr(int [MAX], int, const char *);
void showTab(int [MAX][MAX], int [MAX], int, int, const char *);
void showTabF(int [MAX][MAX], int [MAX], int, int, const char *);
// dynamic programming
void fillTab(int [MAX], int, int, int [MAX][MAX]);

int main() {
	int arr[MAX], len;
	int K, m;
	int tab[MAX][MAX];

	input(arr, len, m, K);
	showArr(arr, len, "arr[]");

	memset(tab, 0, (m + 1) * (len + 1) * sizeof(int));
	tab[0][0] = 1;
//	showTab(tab, arr, len, m, "before filling");
	showTabF(tab, arr, len, m, "before filling");

	fillTab(arr, len, m, tab);
//	showTab(tab, arr, len, m, "after filling");
	showTabF(tab, arr, len, m, "after filling");

	cout << "\nRequired number of subsets are " << tab[len][K] << endl;

	return 0;
}

// input
void input(int arr[MAX], int &len, int &m, int &K) {
	int maxVal = -1;

	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of (sorted) array:\t";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
		maxVal = max(maxVal, arr[i]);
	}

	cout << "Enter required XOR value K:\t";
	cin >> K;

	m = ((int) pow(2, ceil(log2(maxVal)))) - 1;
}

// output
void showArr(int a[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

void showTab(int tab[MAX][MAX], int arr[MAX], int row, int col, const char * msg) {
	printf("\n%s, tab[][] is:-\n", msg);

	cout << "Ind:\t\t";
	for (int j = 0; j <= col; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i <= row; i++) {
		if (i > 0) {
			printf("a[%d] = %d\t", (i - 1), arr[i - 1]);
		} else {
			cout << "\t\t";
		}

		for (int j = 0; j <= col; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
}

void showTabF(int tab[MAX][MAX], int arr[MAX], int row, int col, const char * msg) {
	char * fName = (char *) malloc(100);
	sprintf(fName, "count-number-of-subsets-having-a-particular-xor-value-%s-ME.txt", msg);
	FILE * f = fopen(fName, "w");

	fprintf(f, "\n%s, tab[][] is:-\n", msg);

	fprintf(f, "Ind:\t\t");
	for (int j = 0; j <= col; j++) {
		fprintf(f, "[%d]\t", j);
	}
	fprintf(f, "\n");

	for (int i = 0; i <= row; i++) {
		if (i > 0) {
			fprintf(f, "a[%d] = %d\t", (i - 1), arr[i - 1]);
		} else {
			fprintf(f, "\t\t");
		}

		for (int j = 0; j <= col; j++) {
			fprintf(f, "%d\t", tab[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}

// calculation through dynamic programming
void fillTab(int arr[MAX], int len, int m, int tab[MAX][MAX]) {
	for (int i = 1; i <= len; i++) {
		for (int j = 0; j <= m; j++) {
			tab[i][j] = tab[i - 1][j] + tab[i - 1][j ^ arr[i - 1]];
		}
	}
}

