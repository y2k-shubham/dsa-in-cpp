// http://www.geeksforgeeks.org/find-number-subarrays-even-sum/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=948

/*
Input
3

6
1 2 2 3 4 1

7
8 1 3 7 4 2 9

10
8 7 6 5 7 7 6 0 7 2

Output
9
12
25
*/

/*
Explanation
Let array and cumulative sum arrays be:
Ind			[0]	[1]	[2]	[3]	[4]	[5]	[6]	[7]	[8]	[9]
Arr			8	7	6	5	7	7	6	0	7	2
CS		0	8	15	21	26	33	40	46	46	53	55
CS-Typ	E	E	O	O	E	O	E	E	E	O	O

cumulative sum is even at 6 places (including sum = 0 before beginning of array) and odd at 5
places. now if we pick any two places where CS is odd and take the difference, we find the
subarray between these two locations will have even sum. there are 5C2 such subarrays.

similarly, we can pick 6C2 subarrays terminating at points having even cumulative sum which
will have even sum. so in all there are 6C2 + 5C2 = 25 such subarrays
*/

#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cmath>

using namespace std;

int nCr(int n, int r) {
	if (n < r) {
		return 0;
	}

	if (n - r < r) {
		r = n - r;
	}

	int prod = 1;
	for (int div = 1; div <= r; div++) {
		prod *= n;
		prod /= div;

		n--;
	}

	return prod;
}

int main() {
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		int ele;
		int N;
		int sum, eCount, oCount;

		scanf("%d", &N);
		sum = 0;
		eCount = 1; // as initially, sum is 0 (even)
		oCount = 0;

		for (int i = 0; i < N; i++) {
			cin >> ele;
			sum += ele;

			if (sum & 1) {
				oCount++;
			} else {
				eCount++;
			}
		}

		printf("%d\n", (nCr(eCount, 2) + nCr(oCount, 2)));
	}

	return 0;
}
