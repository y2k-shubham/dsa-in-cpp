// http://www.geeksforgeeks.org/minimum-cost-sort-strings-using-reversal-operations-different-costs/

/*
4
aa 1
ba 3
ac 1
ad 10

4
aa 1
ba 3
ac 1
da 10

4
aa 1
ba 3
ac 10
da 1

4
aa 1
ba 10
ac 3
ad 1
*/

#include <string>
#include <cstdio>
#include <iostream>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;
#define MAX 100

void input(pair <string, int> [MAX], pair <string, int> [MAX], int&);
void showArr(pair <string, int> [MAX], int, const char *);
int backtracking(pair <string, int> [MAX], pair <string, int> [MAX], int, string, int);
void dynamicProgramming(pair <string, int> [MAX], pair <string, int> [MAX], int, int [MAX][2]);
int add(int, int);

int main() {
	pair <string, int> org[MAX];
	pair <string, int> rev[MAX];
	int len;
	int dp[MAX][2];

	input(org, rev, len);

	showArr(org, len, "original array");
	showArr(rev, len, "reverse array");

	int minCost = backtracking(org, rev, len, "", 0);
	if (minCost < INT_MAX) {
		printf("\nBy BackTracking,\tMin Cost of sorting is %d\n", minCost);
	} else {
		printf("\nBy BackTracking,\tNot possible\n");
	}

	dynamicProgramming(org, rev, len, dp);
	minCost = min(dp[len - 1][0], dp[len - 1][1]);
	if (minCost < INT_MAX) {
		printf("By Dynamic Programming,\tMin Cost of sorting is %d\n", minCost);
	} else {
		printf("By Dynamic Programming,\tNot possible\n");
	}

	return 0;
}

void input(pair <string, int> org[MAX], pair <string, int> rev[MAX], int& len) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter strings and reversal cost:-\n");
	for (int i = 0; i < len; i++) {
		cin >> org[i].first;
		cin >> rev[i].second;

		org[i].second = 0;
		rev[i].first.assign(org[i].first.rbegin(), org[i].first.rend());
	}
}

void showArr(pair <string, int> arr[MAX], int len, const char * which) {
	printf("\n%s array is:-\n", which);

	printf("Ind:\t");
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Str:\t");
	for (int i = 0; i < len; i++) {
		cout << arr[i].first << "\t";
	}
	cout << endl;

	printf("Cost:\t");
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i].second);
	}
	cout << endl;
}

int backtracking(pair <string, int> org[MAX], pair <string, int> rev[MAX], int len, string prev, int ind) {
//	printf("\nind = %d\n", ind);
//	cout << "prev = " << prev << endl;

	if (ind >= len) {
//		printf("ind = %d exceeds len = %d\treturned 0\n", ind, len);
		return 0;
	} else {
		bool orgValid = (ind == 0) ? true : (prev.compare(org[ind].first) <= 0);
		bool revValid = (ind == 0) ? true : (prev.compare(rev[ind].first) <= 0);

//		cout << "org = " << org[ind].first << "\t";
//		if (orgValid) {
//			printf("orgValid = true\n");
//		} else {
//			printf("orgValid = false\n");
//		}
//
//		cout << "rev = " << rev[ind].first << "\t";
//		if (revValid) {
//			printf("revValid = true\n");
//		} else {
//			printf("revValid = false\n");
//		}

		if (orgValid && revValid) {
			return min(backtracking(org, rev, len, org[ind].first, ind + 1), add(backtracking(org, rev, len, rev[ind].first, ind + 1), rev[ind].second));
		} else if (orgValid) {
			return backtracking(org, rev, len, org[ind].first, ind + 1);
		} else if (revValid) {
			return add(backtracking(org, rev, len, rev[ind].first, ind + 1), rev[ind].second);
		} else {
			return INT_MAX;
		}
	}
}

int add(int a, int b) {
	if (a == INT_MAX || b == INT_MAX) {
		return INT_MAX;
	} else {
		return (a + b);
	}
}

void dynamicProgramming(pair <string, int> org[MAX], pair <string, int> rev[MAX], int len, int dp[MAX][2]) {
	dp[0][0] = org[0].second;
	dp[0][1] = rev[0].second;

	for (int i = 1; i < len; i++) {
		dp[i][0] = INT_MAX;
		if (org[i].first.compare(org[i - 1].first) >= 0) {
			dp[i][0] = min(dp[i][0], dp[i - 1][0]);
		}
		if (org[i].first.compare(rev[i - 1].first) >= 0) {
			dp[i][0] = min(dp[i][0], dp[i - 1][1]);
		}

		dp[i][1] = INT_MAX;
		if (rev[i].first.compare(org[i - 1].first) >= 0) {
			dp[i][1] = min(dp[i][1], add(dp[i - 1][0], rev[i].second));
		}
		if (rev[i].first.compare(rev[i - 1].first) >= 0) {
			dp[i][1] = min(dp[i][1], add(dp[i - 1][1], rev[i].second));
		}
	}
}

