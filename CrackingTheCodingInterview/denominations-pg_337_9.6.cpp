#include <cstdio>
#include <iostream>

using namespace std;

int findDenos(int, int, int *, int);

int main() {
	int n;
	int dList[] = {25, 10, 5, 2, 1};
	int dListLen = 5;

	printf("Enter no of cents:\t");
	scanf("%d", &n);

	printf("No of ways are:\t\t%d\n", findDenos(n, 0, &dList[0], dListLen));

	return 0;
}

int findDenos(int n, int crrDenoInd, int * dList, int dListLen) {
	if (crrDenoInd < dListLen - 1) {
		int crrDeno = * (dList + crrDenoInd);
		int nextDenoInd = crrDenoInd + 1;
		int ways = 0;

		for (int i = 0; i * crrDeno <= n; i++) {
			ways += findDenos(n - i * crrDeno, nextDenoInd, dList, dListLen);
		}

		return ways;
	} else {
		return 1;
	}
}
