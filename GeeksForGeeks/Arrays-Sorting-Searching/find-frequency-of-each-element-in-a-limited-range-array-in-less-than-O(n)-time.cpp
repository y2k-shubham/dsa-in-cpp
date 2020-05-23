// http://www.geeksforgeeks.org/find-frequency-of-each-element-in-a-limited-range-array-in-less-than-on-time/

/*
Assumption: range of numbers in array is 0-m where m << n, n = array of array
*/

/*
14

1 1 1
2
3 3
5 5
8 8 8
9 9
10

*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void findFreq(int [MAX], int, int, int [MAX]);
void output(int [MAX]);

int main() {
	int arr[MAX];
	int len;
	int freq[MAX];

	input(arr, len);
	memset(freq, 0, sizeof(freq));

	findFreq(arr, 0, len - 1, freq);
	output(freq);

	return 0;
}

void input(int arr[MAX], int &len) {
	printf("Enter length of array:\t");
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void findFreq(int arr[MAX], int lo, int hi, int freq[MAX]) {
	if (lo <= hi) {
		if (arr[lo] != arr[hi]) {
			int mid = (lo + hi) / 2;
			freq[arr[mid]]++;

			findFreq(arr, lo, mid - 1, freq);
			findFreq(arr, mid + 1, hi, freq);
		} else {
			freq[arr[lo]] += (hi - lo) + 1;
		}
	}
}

void output(int freq[MAX]) {
	printf("\nFrequencies of various elements in array are:-\n");
	for (int i = 0; i < MAX; i++) {
		if (freq[i] > 0) {
			printf("freq[%d] = %d\n", i, freq[i]);
		}
	}
}

