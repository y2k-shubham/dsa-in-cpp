// http://www.geeksforgeeks.org/count-quadruples-four-arrays-xor-equals-x/
// http://code.geeksforgeeks.org/AksrUX
// Space Complexity: O(n^2)
// Time Complexity: O(n^2log(n^2)) {assuming searching in map of size n takes logn time}

/*
2
1 10
2
1 10
2
10 1
2
1 10
0

2
0 1
2
2 0
2
0 1
2
1 0
3
*/

#include <cstdio>
#include <iostream>
#include <map>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int, const char *);
map <int, int> createMap(int [MAX], int, int [MAX], int);
int getQuadCount(int [MAX], int, int [MAX], int, int, map <int, int>);

int main() {
	int a[MAX], lenA;
	int b[MAX], lenB;
	int c[MAX], lenC;
	int d[MAX], lenD;
	int x;

	input(a, lenA);
	input(b, lenB);
	input(c, lenC);
	input(d, lenD);

	showArray(a, lenA, "a[]");
	showArray(b, lenB, "b[]");
	showArray(c, lenC, "c[]");
	showArray(d, lenD, "d[]");

	printf("\nEnter XOR value:\t");
	scanf("%d", &x);

	map <int, int> freqMap = createMap(a, lenA, b, lenB);
	printf("\nNo of quads having XOR value %d is %d\n", x, getQuadCount(c, lenC, d, lenD, x, freqMap));

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len, const char * name) {
	printf("\n%s array is :-\n", name);

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

map <int, int> createMap(int a[MAX], int lenA, int b[MAX], int lenB) {
	map <int, int> freqMap;

	for (int i = 0; i < lenA; i++) {
		for (int j = 0; j < lenB; j++) {
			freqMap[a[i] ^ b[j]]++;
		}
	}

	return freqMap;
}

int getQuadCount(int c[MAX], int lenC, int d[MAX], int lenD, int x, map <int, int> freqMap) {
	int count = 0;

	for (int i = 0; i < lenC; i++) {
		for (int j = 0; j < lenD; j++) {
			int reqVal = c[i] ^ d[j] ^ x;
			if (freqMap.find(reqVal) != freqMap.end()) {
				count += freqMap[reqVal];
			}
		}
	}

	return count;
}

