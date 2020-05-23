// http://www.geeksforgeeks.org/majority-element/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
int mooreMajVote(int [MAX], int);
bool isMajor(int [MAX], int, int);

int main() {
	int arr[MAX];
	int n;

	input(arr, n);
	int candidate = mooreMajVote(arr, n);

	if (isMajor(arr, n, candidate)) {
		printf("\nMajority element is %d\n", candidate);
	} else {
		printf("\nNo majority element present\n");
	}

	return 0;
}

void input(int arr[MAX], int &n) {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

int mooreMajVote(int arr[MAX], int n) {
	int count;
	int cand;

	cand = arr[0];
	count = 1;
	for (int i = 1; i < n; i++) {
		if (arr[i] == cand) {
			count++;
		} else {
			count--;
			if (count == 0) {
				count = 1;
				cand = arr[i];
			}
		}
	}

	return cand;
}

bool isMajor(int arr[MAX], int n, int cand) {
	float threshFreq = ((float) n) / 2;
	int freq = 0;

	for (int i = 0; i < n; i++) {
		if (arr[i] == cand) {
			freq++;

			if (freq > threshFreq) {
				return true;
			}
		}
	}

	if (freq > threshFreq) {
		return true;
	} else {
		return false;
	}
}

