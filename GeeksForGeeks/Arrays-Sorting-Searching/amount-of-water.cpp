// http://www.practice.geeksforgeeks.org/problem-page.php?pid=393
// http://www.practice.geeksforgeeks.org/editorial.php?pid=393

/*
2



24

2
4	1	3	2	5
4	4	6
3	0	1	4	3	2	3	4	7
5	1	3	4	2 	3




17

5
3 1 4
2 1 3 0 1 2 4
3 0 1 0 1 2

1st answer = 41
2nd answer = 25

Suggested n^2 approach in above link: For each tower, amount of water filled over it
equals min(maxHeightTower on left, maxHeightTower on right) - height of tower. Sum all such
amounts of water over all towers. Obviously, if either there isn't a tower of height greater
than tower itself on it's left or right, then no water will be filled on top of it
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 1000

void input(int [MAX], int &, int &, int &);
int getLeftQty(int [MAX], int);
int getRightQty(int [MAX], int, int, int);

int main() {
	int T;
	int N;
	int H[MAX];

	scanf("%d", &T);
	while (T-- > 0) {
		int qty, max, maxFreq;

		input(H, N, max, maxFreq);
		qty = 0;

		qty += getLeftQty(H, N);
		qty += getRightQty(H, N, max, maxFreq);

		//printf("LeftQty = %d\n", getLeftQty(H, N));
		//printf("RightQty = %d\n", getRightQty(H, N));

		//printf("\nThe volume of water that can be stored is:\t%d\n", qty);
		printf("%d\n", qty);
	}

	return 0;
}

void input(int H[MAX], int &N, int &max, int &maxFreq) {
	scanf("%d", &N);

	max = maxFreq = 0;
	for (int i = 0; i < N; i++) {
		scanf("%d", &H[i]);

		if (H[i] > max) {
			max = H[i];
			maxFreq = 1;
		} else if (H[i] == max) {
			maxFreq++;
		}
	}
}

int getLeftQty(int H[MAX], int N) {
	int qty, sum, max, maxInd;

	qty = sum = max = 0;
	maxInd = -1;

	for (int i = 0; i < N; i++) {
		if (H[i] >= max) {
			//printf("\nlSum of H[%d .. %d] = %d\n", maxInd + 1, i - 1, max * (i - maxInd - 1) - sum);
			//printf("max updated to = %d\n", H[i]);
			qty += max * (i - maxInd - 1) - sum;
			sum = 0;
			max = H[i];
			maxInd = i;
		} else {
			sum += H[i];
		}
	}

	return qty;
}

int getRightQty(int H[MAX], int N, int maxNum, int maxFreq) {
	int qty, sum, max, maxInd;

	qty = sum = max = 0;
	maxInd = N;

	for (int i = N - 1; i >= 0; i--) {
		if (H[i] >= max) {
			//printf("\nrSum of H[%d .. %d] = %d\n", i + 1, maxInd - 1, max * (maxInd - i - 1) - sum);
			//printf("max updated to = %d\n", H[i]);
			qty += max * (maxInd - i - 1) - sum;
			sum = 0;
			max = H[i];
			maxInd = i;

			if (H[i] == maxNum && maxFreq > 1) {
				break;
			}
		} else {
			sum += H[i];
		}
	}

	return qty;
}

