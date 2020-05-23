// http://www.geeksforgeeks.org/find-even-occurring-elements-array-limited-range/
// http://www.practice.geeksforgeeks.org/problem-page.php?pid=1003

/*
11
9 12 23 10 12 12 15 23 14 12 15

13
1 4 7 5 9 7 3 4 6 8 3 0 3

10
4 4 10 10 4 4 4 4 10 10
*/

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void findEvenFreqEle(int [MAX], int, int &, long long int &, long long int &);
void showEvenFreqEle(int, long long int, long long int);

int main() {
	int arr[MAX], len;
	int maxEle;
	long long freq, found;

	input(arr, len);
	freq = found = 0L;
	maxEle = -1;

	findEvenFreqEle(arr, len, maxEle, freq, found);
	showEvenFreqEle(maxEle, freq, found);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void findEvenFreqEle(int arr[MAX], int len, int &maxEle, long long int &freq, long long int &found) {
	for (int i = 0; i < len; i++) {
		maxEle = max(maxEle, arr[i]);
		freq ^= (1 << arr[i]);
		found |= (1 << arr[i]);
	}
}

void showEvenFreqEle(int maxEle, long long int freq, long long int found) {
	cout << "\nEven frequency elements are:-\n";
	for (int i = 0; i <= maxEle; i++) {
		if (((found & (1 << i)) > 0) && ((freq & (1 << i)) == 0)) {
			printf("%d\t", i);
		}
	}
	cout << endl;
}

