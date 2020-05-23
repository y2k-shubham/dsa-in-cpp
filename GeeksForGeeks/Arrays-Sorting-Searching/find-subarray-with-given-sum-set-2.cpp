// http://www.geeksforgeeks.org/find-subarray-with-given-sum-in-array-of-integers/
// also considers arrays with negative numbers
// related:	http://www.geeksforgeeks.org/find-if-there-is-a-subarray-with-0-sum/
// related: http://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/

/*
Input
6
1 4 20 3 10 5
33
Output
arr[2 .. 4]

Input
5
10 2 -2 -20 10
-10
Output
arr[0 .. 3]
arr[3 .. 4]

Input
6
-10 0 2 -2 -20 10
20
Output
<nothing>
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>

using namespace std;
#define MAX 100

void input(int [MAX], int &, int &);
void output(int [MAX], int, int);
void showArray(int [MAX], int);

int main() {
	int arr[MAX];
	int len;
	int reqSum;

	input(arr, len, reqSum);
	showArray(arr, len);
	output(arr, len, reqSum);

	return 0;
}

void input(int arr[MAX], int &len, int &reqSum) {
	printf("Enter length of array:\t");
	scanf("%d", &len);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		scanf("%d", &arr[i]);
	}

	printf("Enter required sum:\t");
	scanf("%d", &reqSum);
}

void output(int arr[MAX], int len, int reqSum) {
	map <int, list <int> > sumMap;
	int crrSum;

	crrSum = 0;
	cout << endl;

	for (int i = 0; i < len; i++) {
		crrSum += arr[i];

		if (sumMap.find(crrSum - reqSum) != sumMap.end()) {
			list <int> lo = sumMap[crrSum - reqSum];

			for (list <int>::iterator it = lo.begin(); it != lo.end(); it++) {
				printf("arr[%d .. %d] = %d\n", ((*it) + 1), i, reqSum);
			}
		}

		if (sumMap.find(crrSum) != sumMap.end()) {
			sumMap[crrSum].push_back(i);
		} else {
			list <int> tmp;
			tmp.push_back(i);
			sumMap.insert(make_pair(crrSum, tmp));
		}
	}
}

void showArray(int arr[MAX], int len) {
	cout << "\nArray is:-\n";

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

