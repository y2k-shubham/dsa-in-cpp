// http://www.geeksforgeeks.org/partition-number-two-divisble-parts/

/*
123
12 3

1200
4 3

125
12 3
*/

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void findLRemA(string, int, vector <int>&);
void findRRemB(string, int, vector <int>&);
void showVec(string, int, vector <int>, const char *);
void showParts(string, int, vector <int>, int, vector <int>);

int main() {
	string num;
	int a, b;

	cout << "Enter integer to be partitioned:\t";
	cin >> num;

	cout << "Enter divisors a & b:\t";
	cin >> a >> b;

	vector <int> lRemA(num.size());
	vector <int> rRemB(num.size());

	findLRemA(num, a, lRemA);
	findRRemB(num, b, rRemB);

	showVec(num, a, lRemA, "division from left");
	showVec(num, b, rRemB, "division from right");

	showParts(num, a, lRemA, b, rRemB);

	return 0;
}

void findLRemA(string num, int a, vector <int>& lRemA) {
	int rem = 0;

	for (int i = 0; i < num.size(); i++) {
		rem = ((rem * 10) + (num[i] - '0')) % a;
		lRemA[i] = rem;
	}
}

void findRRemB(string num, int b, vector <int>& rRemB) {
	int rem = 0;
	int power10 = 1;

	for (int i = num.size() - 1; i >= 0; i--) {
		rem = (rem + ((num[i] - '0') * power10)) % b;
		rRemB[i] = rem;
		power10 = (power10 * 10) % b;
	}
}

void showVec(string num, int div, vector <int> rem, const char * msg) {
	cout << "\nRemainder of " << num;
	printf(" with %d on %s is:-\n", div, msg);

	printf("Ind:\t");
	for (int i = 0; i < num.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Num:\t");
	for (int i = 0; i < num.size(); i++) {
		printf("%c\t", num[i]);
	}
	cout << endl;

	printf("Rem:\t");
	for (int i = 0; i < num.size(); i++) {
		printf("%d\t", rem[i]);
	}
	cout << endl;
}

void showParts(string num, int a, vector <int> lRemA, int b, vector <int> rRemB) {
	printf("\nPossible partitions are:-\n");
	for (int i = 0; i < num.size() - 1; i++) {
		if (lRemA[i] == 0 && rRemB[i + 1] == 0) {
			string lPart = num.substr(0, i + 1);
			string rPart = num.substr(i + 1, num.size() - i - 1);

			cout << lPart << " and " << rPart << endl;
		}
	}
}

