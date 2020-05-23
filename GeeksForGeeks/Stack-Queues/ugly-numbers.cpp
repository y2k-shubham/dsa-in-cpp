// http://www.geeksforgeeks.org/ugly-numbers/
#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

#define MAX 100
#define isLeast(a, b, c) (((a < b) && (a < c)) ? true : false)

void showUglyNum(int, int, int, int);

int main() {
	int n;
	int f1 = 2;
	int f2 = 3;
	int f3 = 5;

	printf("Enter n for showing nth ugly number:\t");
	scanf("%d", &n);

	showUglyNum(f1, f2, f3, n);

	return 0;
}

void showUglyNum(int f1, int f2, int f3, int n) {
	queue <int> q1;
	queue <int> q2;
	queue <int> q3;
	int num;
	int ctr;

	num = 1;
	q1.push(num * f1);
	q2.push(num * f2);
	q3.push(num * f3);

	ctr = 1;
	while (ctr < n) {
		if (isLeast(q1.front(), q2.front(), q3.front())) {
			num = q1.front();
			q1.pop();
			q1.push(num * f1);
			q2.push(num * f2);
			q3.push(num * f3);
		} else if (isLeast(q2.front(), q1.front(), q3.front())) {
			num = q2.front();
			q2.pop();
			q2.push(num * f2);
			q3.push(num * f3);
		} else {
			num = q3.front();
			q3.pop();
			q3.push(num * f3);
		}
		++ctr;
	}

	printf("The %dth ugly number is:\t%d\n", n, num);
}
