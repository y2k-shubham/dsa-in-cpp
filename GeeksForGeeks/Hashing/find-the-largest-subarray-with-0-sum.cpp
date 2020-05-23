// http://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
// http://www.geeksforgeeks.org/find-if-there-is-a-subarray-with-0-sum/
// EXTENSION:
// http://www.geeksforgeeks.org/print-all-subarrays-with-0-sum/

/*
11
6 3 -1 -3 4 -2 2 4 6 -12 -7

8
15 -2 2 -8 1 7 10 23

3
1 2 3

3
1 0 3

5
4 2 -3 1 6

5
4 2 0 1 6

5
-3 2 3 1 6
*/

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

void inputAndCompute(int *, int, map <int, int>&, int *, int *);
void output(int *, int, int);

int main() {
	int len;
	map <int, int> sumIndexMap;
	int loInd;
	int hiInd;

	printf("Enter length of array:\t");
	scanf("%d", &len);

	int arr[len];

	inputAndCompute(&arr[0], len, sumIndexMap, &loInd, &hiInd);
	output(&arr[0], loInd, hiInd);

	return 0;
}

void inputAndCompute(int * arr, int len, map <int, int>& sumIndexMap, int * loInd, int * hiInd) {
	int i;
	int sum;
	int crrLen;
	int maxLen;

	sum = 0;
	crrLen = 0;
	maxLen = -1;

	printf("Enter %d elements:-\n", len);
	for (i = 0; i < len; i++) {
		scanf("%d", &arr[i]);
		sum += arr[i];

		if (sumIndexMap.find(sum) == sumIndexMap.end()) {
			// insert the sum and index
			sumIndexMap[sum] = i;
		} else {
			crrLen = i - sumIndexMap[sum] + 1;

			if (crrLen > maxLen) {
				* loInd = sumIndexMap[sum];
				* hiInd = i;
			}
		}
	}

	(*loInd)++;
}

void output(int * arr, int lo, int hi) {
	int i;

	printf("\nThe longest subarray with zero sum is:-\n");
	for (i = lo; i <= hi; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\nThe length of longest subarray with zero sum is\t%d\n", (hi - lo + 1));
}
