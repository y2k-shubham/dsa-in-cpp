#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

int inputAndCompute(map <int, int>&, int *, int);
void output(int *, int);

// URL: http://www.geeksforgeeks.org/given-an-array-of-pairs-find-all-symmetric-pairs-in-it/

int main() {
	map <int, int> pairMap;
	int len;
	int ctr;

	printf("Enter no of pairs:\t");
	scanf("%d", &len);

	int res[(len / 2) + 1][2];

	ctr = inputAndCompute(pairMap, &res[0][0], len);
	output(&res[0][0], ctr);

	return 0;
}

int inputAndCompute(map <int, int>& pairMap, int * res, int len) {
	int i;
	int first;
	int second;
	int ctr;

	printf("Enter %d pairs:-\n", len);
	for (i = 1, ctr = 0; i <= len; i++) {
		scanf("%d%d", &first, &second);
		pairMap[first] = second;

		if (pairMap.find(second) == pairMap.end()) {
			// do nothing
		} else if (pairMap[second] == first) {
			* (res + (ctr * 2) + 0) = second;
			* (res + (ctr * 2) + 1) = first;
			ctr++;
		}
	}

	return ctr;
}

void output(int * res, int ctr) {
	int i;

	printf("The symmetric pairs are:-\n");
	for (i = 0; i < ctr; i++) {
		printf("(%d, %d)\n", *(res + (i * 2) + 0), *(res + (i * 2) + 1));
	}
}
