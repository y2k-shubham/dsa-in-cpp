// http://www.geeksforgeeks.org/dynamic-programming-set-7-coin-change/
// TusharRoy

/*
4
1 5 6 8
11

3
5 10 25
30

4
1 5 6 9
11

3
1 2 3
4

4
2 3 5 6
10
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void showWays(int [MAX], int, int, int, string);
string numToString(int);

int main() {
	int denom[MAX];
	int denCount, reqAmt;

	input(denom, denCount, reqAmt);

	printf("\nPossible solutions are:-\n");
	showWays(denom, denCount, reqAmt, 1, "");

	return 0;
}

void input(int denom[MAX], int &denCount, int &reqAmt) {
	printf("Enter no of denominations:\t");
	scanf("%d", &denCount);

	printf("Enter denominations-list:-\n");
	for (int i = 1; i <= denCount; i++) {
		cin >> denom[i];
	}

	cout << "Enter required amount:\t";
	cin >> reqAmt;
}

void showWays(int denom[MAX], int denCount, int reqAmt, int denInd, string soln) {
	if (denInd <= denCount) {
		int denI = denom[denInd];
		string denS = numToString(denI);

//		printf("crrDeno = %d\treqAmt = %d\n", denI, reqAmt);

		for (int i = 0; ((i * denI) <= reqAmt); i++) {
			int remAmt = reqAmt - (i * denI);
			if (i > 0) {
				soln = soln + denS + ' ';
			}

			if (remAmt == 0) {
				cout << soln << endl;
			} else {
				showWays(denom, denCount, remAmt, denInd + 1, soln);
			}
		}
	}
}

string numToString(int num) {
	string str = "";

	while (num > 0) {
		char dig = num % 10 + '0';
		num /= 10;
		str = dig + str;
	}

	return str;
}

