/* Given an set of positive integers, partition it into two subsets such that difference of
   sums of subsets is minimized. (Not sure how to make it work for negative numbers)
   
   Solved using subset-sum problem (dynamic programming)
*/

/*
7
8 1 3 7 4 2 9

12
8 1 0 3 7 4 0 0 2 0 9 0

10
8 1 3 7 4 12 2 9 5 2
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <stack>
#include <utility>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArray(int [MAX], int);
void showTab(bool [MAX][MAX], int [MAX], int, int);
void init(bool [MAX][MAX], int [MAX], int, int);
int findSum(int [MAX], int);
void fillTab(int [MAX], int, bool [MAX][MAX], int, int &, int &, int &);
void findSubsets(int [MAX], int, bool [MAX][MAX], int, int, stack <pair <int, int> > &, stack <pair <int, int> > &);
void showStack(stack <pair <int, int> >, int, const char *);

int main() {
	int arr[MAX], len;
	int sumTotal, sumSmall, sumBig;
	int setIndR, setIndC;
	bool tab[MAX][MAX];
	stack <pair <int, int> > setSmall, setBig;

	input(arr, len);
	showArray(arr, len);

	sumTotal = findSum(arr, len);
	init(tab, arr, len, sumTotal / 2);

	fillTab(arr, len, tab, sumTotal / 2, sumSmall, setIndR, setIndC);
	showTab(tab, arr, len, sumTotal / 2);

	sumBig = sumTotal - sumSmall;
	cout << "\nSum of all elements of array is " << sumTotal << endl;
	printf("Array can be partitioned into subsets having sums %d and %d with difference %d\n", sumSmall, sumBig, ((int) ceil(abs(sumBig - sumSmall))));

	findSubsets(arr, len, tab, setIndR, setIndC, setSmall, setBig);
	showStack(setSmall, sumSmall, "first");
	showStack(setBig, sumBig, "second");

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	for (int i = 1; i <= len; i++) {
		cin >> arr[i];
	}
}

void showArray(int arr[MAX], int len) {
	printf("\nOriginal array is :-\n");

	cout << "Ind:\t";
	for (int i = 1; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Ele:\t";
	for (int i =  1; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void showTab(bool tab[MAX][MAX], int arr[MAX], int len, int k) {
	cout << "\nTable is:-\n";

	cout << "\t";
	for (int j = 0; j <= k; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i <= len; i++) {
		if (i == 0) {
			printf("[%d]\t", i);
		} else {
			printf("[%d]=%d\t", i, arr[i]);
		}

		for (int j = 0; j <= k; j++) {
			if (tab[i][j] == true) {
				printf("T\t");
			} else {
				printf("_\t");
			}
		}
		cout << endl;
	}
	cout << endl;
}

void init(bool tab[MAX][MAX], int arr[MAX], int len, int k) {
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= k; j++) {
			tab[i][j] = false;
		}
	}

	tab[0][0] = 1;
	int ctr = 0;
	for (int i = 1; i <= len; i++) {
		tab[i][0] = tab[i - 1][0];
		if (arr[i] == 0) {
			ctr++;
			tab[i][0] = (int) (ceil(pow(2, ctr)));
		}
	}
}

int findSum(int arr[MAX], int len) {
	int sum = 0;

	for (int i = 1; i <= len; i++) {
		sum += arr[i];
	}

	return sum;
}

void fillTab(int arr[MAX], int len, bool tab[MAX][MAX], int halfSum, int &sumSmall, int &setIndR, int &setIndC) {
	sumSmall = -1;
	for (int i = 1; i <= len; i++) {
		int j = 1;

		while (j <= halfSum && j < arr[i]) {
			tab[i][j] = tab[i - 1][j];
			j++;
		}

		while (j <= halfSum) {
			if (tab[i - 1][j] == true) {
				tab[i][j] = true;
			} else {
				tab[i][j] = tab[i - 1][j - arr[i]];
				if (tab[i][j] == true && j > sumSmall) {
					sumSmall = j;
					setIndR = i;
					setIndC = j;
				}
			}
			j++;
		}
	}
}

void findSubsets(int arr[MAX], int len, bool tab[MAX][MAX], int setIndR, int setIndC, stack <pair <int, int> > &setSmall, stack <pair <int, int> > &setBig) {
	bool taken[MAX];
	int i, j;

	memset(taken, false, sizeof(bool) * MAX);

	// create smaller-sum set
	for (i = setIndR, j = setIndC; j > 0 && i > 0; i--) {
		if (tab[i - 1][j] == false) {
			j -= arr[i];
			taken[i] = true;
			setSmall.push(make_pair(i, arr[i]));
		}
	}

	// create bigger-sum set
	for (int i = len; i > 0; i--) {
		if (taken[i] == false) {
			setBig.push(make_pair(i, arr[i]));
		}
	}
}

void showStack(stack <pair <int, int> > eleStack, int sum, const char * msg) {
	printf("\n%s set with sum %d is:-\n", msg, sum);

	while (!eleStack.empty()) {
		pair <int, int> elePair = eleStack.top();
		eleStack.pop();

		printf("(a[%d] = %d)\t", elePair.first, elePair.second);
	}
	cout << endl;
}
