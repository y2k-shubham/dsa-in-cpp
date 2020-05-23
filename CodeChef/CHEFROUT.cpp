// https://www.codechef.com/MAY17/problems/CHEFROUT
// useless straight-forward question

/*
5
CES
CS
CCC
SC
ECCC

1
CESC
*/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
#define MAX 100005

int main() {
	int T;
	string sched;

	scanf("%d", &T);
	sched.reserve(MAX);
	while (T-- > 0) {
		int i = 0;
		cin >> sched;

		// consume all Cs
		while ((i < sched.length()) && (sched[i] == 'C')) {
			i++;
		}

		// consume all Es
		while ((i < sched.length()) && (sched[i] == 'E')) {
			i++;
		}

		if ((i < sched.length()) && (sched[i] == 'C')) {
			printf("no\n");
			continue;
		}

		// consume all Ss
		while ((i < sched.length()) && (sched[i] == 'S')) {
			i++;
		}

		if ((i < sched.length()) && ((sched[i] == 'C') || (sched[i] == 'E'))) {
			printf("no\n");
			continue;
		}

		printf("yes\n");
	}

	return 0;
}
