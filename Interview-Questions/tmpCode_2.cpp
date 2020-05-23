/*
6 2
1 3 10 1 7 2

7 2
1 5 8 9 12 14 15

7 3
1 5 8 9 12 14 15
*/

#include <bits/stdc++.h>
using namespace std;

#define MAX 5000

void showArr(int arr[MAX], int N) {
	printf("\narr\n");
	for (int i = 0; i < N; i++) {
		printf("arr[%d] = %d\n", i, arr[i]);
	}
}

void showMap(map <int, int> mp) {
	printf("\nmap\n");
	for (map <int, int>::iterator i = mp.begin(); i != mp.end(); i++) {
		printf("[%d] = %d\n", i -> first, i -> second);
	}
}

int minSum = INT_MAX;

void calc(int diff[MAX], int N, int i, bool canTake, int left, int crrSum) {
	if (left == 0) {
		minSum = min(minSum, crrSum);
	} else if (i > (N -  2 * left + 1)) {
		return;
	} else if (canTake == false) {
		calc(diff, N, i + 1, true, left, crrSum);
	} else {
		calc(diff, N, i + 1, true, left, crrSum);
		calc(diff, N, i + 1, false, left - 1, crrSum + diff[i]);
	}
}

int main() {
	int val[MAX], diff[MAX];
	int N, P;

	cin >> N >> P;
	for(int i = 0; i < N; i++) {
//		cin >> val[i];
		val[i] = rand() % 1000000;
	}
//	showArr(val, N);

	sort(val, val + N);
//	showArr(val, N);

	for (int i = 1; i < N; i++) {
		diff[i - 1] = val[i] - val[i - 1];
	}
//	showArr(diff, N - 1);

	calc(diff, N - 1, 0, true, P, 0);
	cout << endl << minSum << endl;

	return 0;
}


