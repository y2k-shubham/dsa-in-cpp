// https://www.codechef.com/MAY17/problems/UNICOURS
// easy solution, but twisted problem statement and approach

/*
2
3
0 1 1
3
0 1 2
*/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
#define MAX 100005

void input(vector <int>&, int&);
int compute(vector <int>, int);

int main() {
	int T;
	int n;
	vector <int> preReqCount(MAX);

	cin >> T;
	while (T-- > 0) {
		input(preReqCount, n);
		cout << compute(preReqCount, n) << endl;
	}

	return 0;
}

void input(vector <int>& preReqCount, int& n) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &preReqCount[i]);
	}
}

int compute(vector <int> preqReqCount, int n) {
	int useCount = 0;
	int remCount = 1;

	for (int i = 1; i < n; i++) {
		if (preqReqCount[i] > useCount) {
			int diff = preqReqCount[i] - useCount;
			useCount += diff;
			remCount -= diff;
		}
		remCount++;
	}

	return remCount;
}

