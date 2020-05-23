//http://www.geeksforgeeks.org/maximum-subarray-sum-modulo-m/

#include <cstdio>
#include <iostream>
#include <list>

using namespace std;
#define MAX 100

void input(int [MAX], int&, int&);
void showArr(int [MAX], int);

void input(int a[MAX], int& len, int& ele) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("\nEnter Modulus :\t");
	cin >> ele;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		cin >> a[i];
		a[i] = (a[i]%ele);
	}

	showArr(a, len);
}

void showArr(int a[MAX], int len) {
	printf("\na[] array is:-\n");

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

int solve(int a[MAX], int n, int m) {

	int sum = 0, i = 0, j = 0, ans = 0;
	int ii, jj;

	while (j < n) {
		if ((sum + a[j]) >= m) {
			sum -= a[i++];
			continue;
		} else {
			sum = (sum + a[j++])%m;
		}
		sum %= m;
		if (ans < sum) {
			ans = sum;
			ii = i;
			jj = j - 1;
		}

	}

	printf("\na[%d..%d] = %d\n", ii, jj, ans);

	return ans;
}

int main()
{
	int n, m;
	int a[MAX];

	input(a, n, m);
	int res = solve(a, n, m);

	//	cout << " Max sub_array sum with modulo " << res << endl;

	return 0;
}

/*
5 7
3 3 9 9 5

7 7
8 1 3 7 4 2 9
*/
