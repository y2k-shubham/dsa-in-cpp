#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 31

void nextLargest(int);

int main() {
	int n;

	printf("Enter n:\t");
	scanf("%d", &n);

	nextLargest(n);

	return 0;
}

void nextLargest(int n) {
	int pos;
	int onesCnt;
	int nLarge;
	int mask;
	int i;
	bool currOne;
	bool prevOne;

	pos = 0;
	onesCnt = 0;
	prevOne = false;

	for (i = 0; i <= MAX; i++) {
		if ((n & (1 << i)) != 0) {
			currOne = true;
		} else {
			currOne = false;
		}

		if (currOne) {
			++onesCnt;
		}

		if (!currOne && prevOne) {
			pos = i;
			break;
		} else {
			prevOne = currOne;
		}
	}

	pos--;
	onesCnt--;
	//printf("pos = %d\tctr = %d\n", pos, onesCnt);
	nLarge = n;

	mask = (1 << (pos + 1));
	nLarge |= mask;
	//printf("After 1st step, n = %d\n", nLarge);

	mask = ~((1 << (pos + 1)) - 1);
	nLarge &= mask;
	//printf("After 2nd step, n = %d\n", nLarge);

	mask = (1 << onesCnt) - 1;
	nLarge |= mask;
	//printf("After 3rd step, n = %d\n", nLarge);

	printf("Next largest no is %d\n", nLarge);
}

void nextSmallest(int n) {

}
