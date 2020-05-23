// http://www.geeksforgeeks.org/smallest-number-multiply-convert-floating-point-natural/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1534

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

long findFracPart(char *);
long countDigits(long);
long findReqMultiplier(long, long);
long hcf(long, long);

int main() {
	char num[100];
	long fracPart, fracPartDigCount;

	cout << "Enter a fractional number:\t";
	scanf("%s", num);

	fracPart = findFracPart(num);
	fracPartDigCount = countDigits(fracPart);

	if (fracPart > 0) {
		printf("%ld\n", findReqMultiplier(fracPart, fracPartDigCount));
	} else {
		printf("1\n");
	}

	return 0;
}

long findFracPart(char * num) {
	int len = strlen(num);
	char * dotPtr = strchr(num, '.');

	long fracPart = 0;
	for (char * ptr = dotPtr + 1; (*ptr) != '\0'; ptr++) {
		fracPart = (fracPart * 10) + ((*ptr) - '0');
	}

	return fracPart;
}

long countDigits(long n) {
	long count = 0;

	while (n > 0) {
		n /= 10;
		count++;
	}

	return count;
}

long findReqMultiplier(long fracPart, long fracPartDigCount) {
	long powOf10 = (long) pow(10, fracPartDigCount);

	long gcd = hcf(powOf10, fracPart);
	long lcm = fracPart * powOf10 / gcd;

	return (lcm / fracPart);
}

long hcf(long big, long small) {
	long rem = big % small;

	if (rem == 0) {
		return small;
	} else {
		return hcf(small, rem);
	}
}

