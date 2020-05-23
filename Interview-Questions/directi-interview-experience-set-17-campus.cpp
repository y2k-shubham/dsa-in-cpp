// http://www.geeksforgeeks.org/directi-interview-experience-set-17-campus/

/*
Given 2 arrays of integers of size m and n where m>n.You need to maximize the dot product
by inserting zeros in the second array but we cannot disturb the order of original arrays.
*/

/*
12
5 10 0 1 2 8 1 3 7 4 2 9
5
9 5 2 8 2

8
9 0 4 5 1 2 6 3
6
2 1 3 7 4 8

5
1 9 0 4 5
2
2 9
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>

using namespace std;
#define MAX 100

void input(int [MAX], int&, const char *);
void fillTab(int [MAX], int, int [MAX], int, int [MAX][MAX]);
void findSoln(int [MAX], int, int [MAX], int, int [MAX][MAX], stack <int>&);
void showArr(int [MAX], int, const char *);
void showTab(int [MAX], int, int [MAX], int, int [MAX][MAX], const char *);
void showSoln(stack <int>, int);

int main() {
	int arrM[MAX], lenM;
	int arrN[MAX], lenN;
	int tab[MAX][MAX];
	stack <int> solnStk;

	input(arrM, lenM, "first");
	input(arrN, lenN, "second");

	showArr(arrM, lenM, "first");
	showArr(arrN, lenN, "second");

	memset(tab, 0, (lenN + 1) * MAX * sizeof(int));
	showTab(arrM, lenM, arrN, lenN, tab, "before filling");

	fillTab(arrM, lenM, arrN, lenN, tab);
	showTab(arrM, lenM, arrN, lenN, tab, "after filling");

	findSoln(arrM, lenM, arrN, lenN, tab, solnStk);
	showSoln(solnStk, lenM);

	return 0;
}

void input(int arr[MAX], int& len, const char * which) {
	printf("\nFor %s array:-\n", which);

	cout << "Enter length:\t";
	cin >> len;

	cout << "Enter elements:-\n";
	for (int i = 1; i <= len; i++) {
		cin >> arr[i];
	}
}

void fillTab(int arrM[MAX], int lenM, int arrN[MAX], int lenN, int tab[MAX][MAX]) {
	for (int i = 1; i <= lenN; i++) {
		for (int j = i; j <= lenM; j++) {
			tab[i][j] = max(tab[i - 1][j - 1] + arrN[i] * arrM[j], tab[i][j - 1]);
		}
	}
}

void findSoln(int arrM[MAX], int lenM, int arrN[MAX], int lenN, int tab[MAX][MAX], stack <int>& stk) {
	int i = lenN;
	int j = lenM;

	while (j > 0) {
		if (tab[i][j] == tab[i][j - 1]) {
			stk.push(0);
		} else {
			stk.push(arrN[i]);
			i--;
		}
		j--;
	}
}

void showArr(int arr[MAX], int len, const char * which) {
	printf("\n%s array is:-\n", which);

	printf("Ind:\t");
	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 1; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTab(int arrM[MAX], int lenM, int arrN[MAX], int lenN, int tab[MAX][MAX], const char * when) {
	printf("\n%s, tab[][] is:-\n", when);

	printf("\t");
	for (int i = 0; i <= lenM; i++) {
		printf("[%d]=%d\t", i, arrM[i]);
	}
	cout << endl;

	for (int i = 0; i <= lenN; i++) {
		printf("[%d]=%d\t", i, arrN[i]);
		for (int j = 0; j <= lenM; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
}

void showSoln(stack <int> stk, int lenM) {
	printf("\nAfter inserting 0s, arrN[] is:-\n");

	cout << "Ind:\t";
	for (int i = 1; i <= lenM; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 1; i <= lenM; i++) {
		printf("%d\t", stk.top());
		stk.pop();
	}
	cout << endl;
}

