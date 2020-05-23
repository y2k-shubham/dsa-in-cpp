// URL: http://www.geeksforgeeks.org/count-distinct-elements-in-every-window-of-size-k/
/*
    Problem: Given an array of length n and an integer k <= n, find the no of distinct numbers in every window of length k within the array
             (Note that there will be (n - k + 1) windows of size k in the array of length n)

    Solution: Count the no of distinct numbers in the first window of size k and store the frequencies in a hashMap. Thereafter, every time the window
              is shifted by 1 place, adjustments in the count have to be made only for one newly added number and one removed number
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <cstdlib>

using namespace std;

int * input(int *, int *, int *);
void showArray(int *, int);
void output(int *, int, int, map <int, int>&);

int main() {
	int n;
	int k;
	int * arr;
	map <int, int> freqCount;

	arr = input(arr, &n, &k);
	//showArray(arr, n);
	output(arr, n, k, freqCount);

	return 0;
}

int * input(int * arr, int * n, int * k) {
	int i;

	printf("Enter length of array:\tn = ");
	scanf("%d", n);

	arr = (int *) calloc(*n, sizeof(int));

	printf("Enter %d elements:-\n", *n);
	for (i = 0; i < * n; i++) {
		scanf("%d", &arr[i]);
	}

	printf("Enter window size:\tk = ");
	scanf("%d", k);

	return arr;
}

void showArray(int * arr, int n) {
	int i;

	printf("\nThe array entered is:-\n");
	for (i = 0; i < n; i++) {
		printf("%d\t", arr[i]);
	}
	printf("\n");
}

void output(int * arr, int n, int k, map <int, int>& freqMap) {
	int i;
	int frontInd;
	int rearInd;
	int uniqCtr;

    uniqCtr = 0;
	for (i = 0; i < k; i++) {
		if (freqMap.find(arr[i]) == freqMap.end()) {
			freqMap[arr[i]] = 1;
			uniqCtr++;
		} else {
			freqMap[arr[i]]++;
		}
	}

    //printf("From index 0 to %d, no of unique elements:\t%d\n", (k - 1), uniqCtr);

	rearInd = 0;
	frontInd = i;
	printf("\nThe no of unique numbers in each window of size %d is:-\n%d\n", k, uniqCtr);

	for (; frontInd < n; frontInd++, rearInd++) {
		if (freqMap.find(arr[frontInd]) == freqMap.end()) {
			freqMap[arr[frontInd]] = 1;
			uniqCtr++;
		} else {
			freqMap[arr[frontInd]]++;
		}

		if (freqMap[arr[rearInd]] == 1) {
			uniqCtr--;
			freqMap.erase(arr[rearInd]);
		} else {
			freqMap[arr[rearInd]]--;
		}

		printf("%d\n", uniqCtr);
	}
}
