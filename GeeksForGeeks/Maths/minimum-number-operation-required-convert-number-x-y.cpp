// http://www.geeksforgeeks.org/minimum-number-operation-required-convert-number-x-y/
// http://code.geeksforgeeks.org/EPmOM6

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;
void findMinOpsIter(int, int);

int main() {
	// for all inputs, it is assumed that 1st arg >= 2nd arg

	findMinOpsIter(15, 15);
	findMinOpsIter(13, 16);
	findMinOpsIter(4, 7);
	findMinOpsIter(2, 5);
	findMinOpsIter(6, 19);
	findMinOpsIter(15, 84);
	findMinOpsIter(5, 57);

	return 0;
}

void findMinOpsIter(int x, int y) {
	stack <int> stk;
	int ops;
	int yOrig;

	// we would work in reverse, converting y to x by following 2 operations
	// either divide y by 2 (reverse of operation of multiplying x by 2)
	// or add 1 to y (reverse of operation of subtracting x by 1)
	// we'll keep pushing values of y on the stack so as to store the sequence of steps taken
	yOrig = y;
	ops = 0;
	stk.push(y);

	while (y > x) {
		if ((y % 2) == 0) {
			// if it's even, it must've been formed by doubling, so to reverse that, divide it by 2
			y /= 2;
		} else {
			// if it's odd, it must've been formed by subtracting 1, so to reverse that, add 1
			y += 1;
		}

		ops++;
		stk.push(y);
	}
	stk.pop();			// item popped to prevent extra copy of y coming into stack

	// after the loop, we could have following situations:
	// either x = y, in that case ops is the answer
	// or x > y, in that case, to convert y to x, we must add 1 to it repeatedly
	// so both the above situations can be handled by adding difference x - y to ops
	ops += x - y;
	while (x >= y) {
		stk.push(y);
		y++;
	}
	stk.pop();			// top item will always be x, so pop it

	// show the steps taken for conversion by printing out the stack
	printf("\nMin ops for conversion %d -> %d is %d\n", x, yOrig, ops);
	printf("Ops are:-\n");

	while (!stk.empty()) {
		int xNew = stk.top();
		stk.pop();

		if (xNew > x) {
			printf("%d * 2 = %d\n", x, xNew);
		} else {
			printf("%d - 1 = %d\n", x, xNew);
		}

		x = xNew;
	}
}


