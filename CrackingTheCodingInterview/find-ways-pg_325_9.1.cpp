#include <cstdio>
#include <iostream>
#include <map>
#include <cstring>

using namespace std;
#define MAX 50

int findWays_1(int, map <int, int>&);
int findWays_2(int, int [MAX]);

int main() {
	int n;
	int memo[MAX];
	map <int, int> ways;

	cout << "Enter n:\t";
	cin >> n;
	memset(memo, 0, sizeof(memo));

	cout << "\nNo of ways are:\t" << findWays_1(n - 1, ways) << endl;
	cout << "No of ways are:\t" << findWays_2(n, memo) << endl;

	return 0;
}

int findWays_1(int n, map <int, int>& ways) {
	if (n < 0) {
		return 0;
	} else if (n == 0) {
		return 1;
	} else if (ways[n] > 0) {
		return ways[n];
	} else {
		ways[n] = findWays_1(n - 1, ways) + findWays_1(n - 2, ways) + findWays_1(n - 3, ways);
		return ways[n];
	}
}

int findWays_2(int n, int memo[MAX]) {
	int i;

	memo[n] = 1;
	memo[n - 1] = 1;
	memo[n - 2] = 2;

	for (i = n - 3; i >= 1; i--) {
		memo[i] = memo[i + 1] + memo[i + 2] + memo[i + 3];
	}

	return memo[1];
}
