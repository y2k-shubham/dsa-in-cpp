
// arr dynamic programming solution to finding the number
// of subsets having xor of their elements as k

// http://www.geeksforgeeks.org/count-number-of-subsets-having-a-particular-xor-value/

/*
4
6 9 4 2
6

5
1 2 3 4 5
4

10
78 58 62 64 5 45 81 27 61 91
24
*/

#include<bits/stdc++.h>

using namespace std;
#define MAX 100

void showArr(int [MAX], int, const char *);
void showTab(int [MAX][MAX], int [MAX], int, int, const char *);
void showTabF(int [MAX][MAX], int [MAX], int, int, const char *);

// Returns count of subsets of arr[] with XOR value equals
// to k.
int subsetXOR(int arr[], int n, int k) {
	// Find maximum element in arr[]
	int max_ele = arr[0];
	for (int i=1; i<n; i++)
		if (arr[i] > max_ele) {
			max_ele = arr[i];
		}

	// Maximum possible XOR value
	int m = (1 << (int)(log2(max_ele) + 1) ) - 1;

	// The value of dp[i][j] is the number of subsets having
	// XOR of their elements as j from the set arr[0...i-1]
	int dp[MAX][MAX];

	// Initializing all the values of dp[i][j] as 0
	for (int i=0; i<=n; i++)
		for (int j=0; j<=m; j++) {
			dp[i][j] = 0;
		}

	// The xor of empty subset is 0
	dp[0][0] = 1;

	showTabF(dp, arr, n, m, "before filling");

	// Fill the dp table
	for (int i=1; i<=n; i++)
		for (int j=0; j<=m; j++) {
			dp[i][j] = dp[i-1][j] + dp[i-1][j^arr[i-1]];
		}

	showTabF(dp, arr, n, m, "after filling");

	// The answer is the number of subset from set
	// arr[0..n-1] having XOR of elements as k
	return dp[n][k];
}

// Driver program to test above function
int main() {
	int arr[] = {78, 58, 62, 64, 5, 45, 81, 27, 61, 91};
	int k = 24;
	int n = sizeof(arr)/sizeof(arr[0]);

	showArr(arr, n, "arr[]");
	cout << "\nCount of subsets is " << subsetXOR(arr, n, k) << endl;

	return 0;
}

void showArr(int a[MAX], int len, const char * name) {
	printf("\n%s is:-\n", name);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

void showTab(int tab[MAX][MAX], int arr[MAX], int row, int col, const char * msg) {
	printf("\n%s, tab[][] is:-\n", msg);

	cout << "Ind:\t\t";
	for (int j = 0; j <= col; j++) {
		printf("[%d]\t", j);
	}
	cout << endl;

	for (int i = 0; i <= row; i++) {
		if (i > 0) {
			printf("a[%d] = %d\t", (i - 1), arr[i - 1]);
		} else {
			cout << "\t\t";
		}

		for (int j = 0; j <= col; j++) {
			printf("%d\t", tab[i][j]);
		}
		cout << endl;
	}
}

void showTabF(int tab[MAX][MAX], int arr[MAX], int row, int col, const char * msg) {
	char * fName = (char *) malloc(100);
	sprintf(fName, "count-number-of-subsets-having-a-particular-xor-value-%s-GFG.txt", msg);
	FILE * f = fopen(fName, "w");

	fprintf(f, "\n%s, tab[][] is:-\n", msg);

	fprintf(f, "Ind:\t\t");
	for (int j = 0; j <= col; j++) {
		fprintf(f, "[%d]\t", j);
	}
	fprintf(f, "\n");

	for (int i = 0; i <= row; i++) {
		if (i > 0) {
			fprintf(f, "a[%d] = %d\t", (i - 1), arr[i - 1]);
		} else {
			fprintf(f, "\t\t");
		}

		for (int j = 0; j <= col; j++) {
			fprintf(f, "%d\t", tab[i][j]);
		}
		fprintf(f, "\n");
	}

	fclose(f);
}

