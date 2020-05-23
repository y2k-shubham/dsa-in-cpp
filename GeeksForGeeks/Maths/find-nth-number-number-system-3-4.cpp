// http://www.geeksforgeeks.org/find-nth-number-number-system-3-4/
// time complexity: log2(n)
/*
	explanation (here N denotes index for Nth number in 3-4 base)
	3-4		N		Bin

	3		1		0		range in dec:	2^1 - 1 to 2^2 - 2	no of dig: 1
	4		2		1

	33		3		00
	34		4		01		range in dec:	2^2 - 1 to 2^3 - 2	no of dig:	2
	43		5		10
	44		6		11

	333		7		000
	334		8		001
	343		9		010
	344		10		011		range in dec:	2^3 - 1 to 2^4 - 2	no of dig:	3
	433		11		100
	434		12		101
	443		13		110
	444		14		111

	so to convert N to corresponding Bin value in above table,
	find floor and ceil of log2(n), let these be logF and logC

	if N equals 2^logC - 1, then it is beginning of range (1, 3, 7, 15...)
		so we set no of dig = logC
	else   we set no of dig = logF

	then N can be calculated as N - (2 ^ no of dig) + 1
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

void findNAndDig(int &, int &);
void showIn34Base(int, int);

int main() {
	int n;
	int noOfDig;

	printf("Enter n for displaying nth number in 3-4 base:\t");
	scanf("%d", &n);

	findNAndDig(n, noOfDig);
//	printf("\nReduced n = %d\tnoOfDig = %d\n", n, noOfDig);
	showIn34Base(n, noOfDig);

	return 0;
}

void findNAndDig(int &n, int &noOfDig) {
	if (n == 1) {
		n = 0;
		noOfDig = 1;
	} else {
		float log = (float) log2(n);	// actual base-2 logarithm
		int logF = (int) floor(log);	// floor of base-2 logarithm
		int logC = (int) ceil(log);		// ceil of base-2 logarithm

		if (n == (int) (pow(2, logC)) - 1) {
			noOfDig = logC;
		} else {
			noOfDig = logF;
		}

		n -= (int) (pow(2, noOfDig));
		n++;
	}
}

void showIn34Base(int n, int noOfDig) {
	string str;

	while (n > 0) {
		if (n % 2 == 0) {
			str += '3';
		} else {
			str += "4";
		}

		noOfDig--;
		n /= 2;
	}

	while (noOfDig > 0) {
		str += '3';
		noOfDig--;
	}

	reverse(str.begin(), str.end());
	cout << "\nThe given number in 3-4 base is:\t" << str << endl;
}
