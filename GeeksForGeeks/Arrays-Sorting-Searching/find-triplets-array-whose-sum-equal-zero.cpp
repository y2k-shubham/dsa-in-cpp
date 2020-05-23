// http://www.geeksforgeeks.org/find-triplets-array-whose-sum-equal-zero/
// Method 1: O(n^2) time, O(n) space
// Method 2: O(n^2) time, O(1) space

/*
5
0 -1 2 -3 1

5
1 -2 1 0 5
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <utility>
#include <cmath>

using namespace std;

#define MAX 100
#define min(a, b, c) min(min(a, b), c)
#define max(a, b, c) max(max(a, b), c)
#define mid(a, b, c) ((a != min(a, b, c) && a != max(a, b, c)) ? a : ((b != min(a, b, c) && b != max(a, b, c)) ? b : c))

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
void showSet(int [MAX], set <set <int> >);
void method_1(int [MAX], int);
void createMap(int [MAX], int, map <int, int>&);
set <int> createSet(int, int, int);
void method_2(int [MAX], int);

int main() {
	int arr[MAX], len;

	input(arr, len);

	showArray(arr, len, "before sorting");

	method_1(arr, len);
	method_2(arr, len);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len, const char * when) {
	printf("\n%s, array is :-\n", when);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i =  0; i < len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showSet(int arr[MAX], set <set <int> > indSet) {
	printf("\nMethod 1, triplets adding to zero are:-\n");
	for (set <set <int> >::iterator i = indSet.begin(); i != indSet.end(); i++) {
		set <int> tmpSet = *i;

		for (set <int>::iterator j = tmpSet.begin(); j != tmpSet.end(); j++) {
			printf("arr[%d] = %d\t", *j, arr[*j]);
		}
		cout << endl;
	}
}

void method_1(int arr[MAX], int len) {
	map <int, int> eleMap;
	set <set <int> > indSet;

	createMap(arr, len, eleMap);

	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			int reqSum = -(arr[i] + arr[j]);

			if (eleMap.find(reqSum) != eleMap.end()) {
				int ind = eleMap[reqSum];

				if (ind != i && ind != j) {
					indSet.insert(createSet(ind, i, j));
				}
			}
		}
	}

	showSet(arr, indSet);
}

void createMap(int arr[MAX], int len, map <int, int>& eleMap) {
	for (int i = 0; i < len; i++) {
		eleMap.insert(make_pair(arr[i], i));
	}
}

set <int> createSet(int a, int b, int c) {
	set <int> newSet;
	newSet.insert(a);
	newSet.insert(b);
	newSet.insert(c);
	return newSet;
}

void method_2(int arr[MAX], int len) {
	sort(arr, arr + len);
	showArray(arr, len, "after sorting");

	printf("\nMethod 2: triplets adding to zero are:-\n");
	for (int i = 0; i < len - 2; i++) {
		int reqSum = -arr[i];
		int crrSum = 0;

		int j = i + 1;
		int k = len - 1;
		while (j < k) {
			crrSum = arr[j] + arr[k];
			if (crrSum > reqSum) {
				k--;
			} else if (crrSum < reqSum) {
				j++;
			} else {
				printf("arr[%d] = %d\tarr[%d] = %d\tarr[%d] = %d\n", i, arr[i], j, arr[j], k, arr[k]);
				j++;
				k--;
			}
		}
	}
}

