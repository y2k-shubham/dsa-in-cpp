// http://www.geeksforgeeks.org/count-numbers-first-last-digits/

/*
Inp: 7 68
Ans: 9

Inp: 5 40
Ans: 8
*/

#include <cstdio>
#include <iostream>

using namespace std;

int findFLNumsBelow(int);
int findFirstDig(int);
int findLastDig(int);

int main() {
	int start, end;

	cout << "Enter range (start, end):\t";
	cin >> start >> end;

	int sCount = findFLNumsBelow(start);
	int eCount = findFLNumsBelow(end);

	int ans = (eCount - sCount);
	if (findFirstDig(start) == findLastDig(start)) {
		ans++;
	}
	printf("\nThere are %d nums between %d and %d having same first & last digits\n", ans, start, end);

	return 0;
}

int findFLNumsBelow(int n) {
	if (n < 10) {
		return n;
	} else if (findLastDig(n) < findFirstDig(n)) {
		return (9 + (n / 10) - 1);
	} else {
		return (9 + (n / 10));
	}
}

int findFirstDig(int n) {
	while ((n / 10) > 0) {
		n /= 10;
	}

	return n;
}

int findLastDig(int n) {
	return (n % 10);
}

