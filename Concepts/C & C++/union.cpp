#include <bits/stdc++.h>

using namespace std;

union uni {
	char c1;
	short s;
	char c2;
	int i;
};

void showUni(uni);

int main() {
	uni u;

	u.i = 0;
	showUni(u);

	u.c1 = 'A';
	showUni(u);

	u.c2 = 'B';
	showUni(u);

	u.s = 257;
	showUni(u);

	u.i = INT_MAX;
	showUni(u);

	return 0;
}

void showUni(uni u) {
	printf("\nValues are:-\n");
	printf("c1 = %d\n", (int) u.c1);
	cout << "s  = " << u.s << endl;
	printf("c2 = %d\n", (int) u.c2);
	printf("i  = %d\n", u.i);
}

