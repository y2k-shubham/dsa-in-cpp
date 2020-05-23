// http://www.geeksforgeeks.org/print-all-jumping-numbers-smaller-than-or-equal-to-a-given-value/
#include <cstdio>
#include <iostream>

using namespace std;
void showJumpNo(int, int);

int main() {
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		int N;
		scanf("%d", &N);

		printf("0");
		for (int i = 1; i <= 9; i++) {
			showJumpNo(i, N);
		}
		printf("\n");
	}

	return 0;
}

void showJumpNo(int crrNum, int maxNum) {
	if (crrNum <= maxNum) {
		printf(" %d", crrNum);

		int lastDig = crrNum % 10;
		if (lastDig > 0) {
			showJumpNo(crrNum * 10 + (lastDig - 1), maxNum);
		}
		if (lastDig < 9) {
			showJumpNo(crrNum * 10 + (lastDig + 1), maxNum);
		}
	}
}
