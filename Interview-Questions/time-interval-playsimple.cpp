/*
21:15:00
3
21:15:30
10:10:00
10:10:10
*/

#include <cstdio>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int Q;
	int hh1, mm1, ss1, hh2, mm2, ss2;
	int s1, s2;
	const float degPerSecH = (360.0f / (24 * 60 * 60));
	const float degPerSecM = (360.0f / (60 * 60));
	const float degPerSecS = (360.0f / 60);

	printf("Enter initial time:\t");
	scanf("%d:%d:%d", &hh1, &mm1, &ss1);
	s1 = (60 * 60 * hh1) + (60 * mm1) + ss1;
//	printf("initial seconds = %d\n", s1);

	printf("Enter no of queries:\t");
	cin >> Q;

	printf("Enter queries:-\n");
	for (int i = 1; i <= Q; i++) {
		scanf("%d:%d:%d", &hh2, &mm2, &ss2);
		s2 = (60 * 60 * hh2) + (60 * mm2) + ss2;

		int sDiff = (s2 > s1) ? (s2 - s1) : (24 * 60 * 60 - s1 + s2);
//		printf("at i = %d, s1 = %d\ts2 = %d\tsDiff = %d\n", i, s1, s2, sDiff);

		float degH = degPerSecH * sDiff;
		float degM = degPerSecM * sDiff;
		float degS = degPerSecS * sDiff;

		cout << degH << setprecision(6) << "\t";
		cout << degM << setprecision(6) << "\t";
		cout << degS << setprecision(6) << endl << endl;

		hh1 = hh2;
		mm1 = mm2;
		ss1 = ss2;
		s1 = s2;
	}

	return 0;
}

