// http://www.geeksforgeeks.org/count-possible-decodings-given-digit-sequence/
/*
Time:	O(n)
Space:	O(n), but actually needs only O(1) just like Fibonacci
*/

/*
3
1 2 1

4
1 2 3 4
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArr(int [MAX], int, int, const char *);
void calc(int [MAX], int, int [MAX]);
int makeNum(int, int);

int main() {
	int arr[MAX], len;
	int count[MAX];

	input(arr, len);
	showArr(arr, len, 1, "original array");

	calc(arr, len, count);
	showArr(count, len, 0, "count array");

	cout << "\nNo of possible decodings are " << count[len] << endl;

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of digit sequence:\t";
	cin >> len;

	cout << "Enter digit sequence:\t";
	for (int i = 1; i <= len; i++) {
		cin >> arr[i];
	}
}

void showArr(int arr[MAX], int len, int begInd, const char * msg) {
	printf("\n%s is:-\n", msg);

	cout << "Ind:\t";
	for (int i = begInd; i <= len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = begInd; i <= len; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

void calc(int arr[MAX], int len, int count[MAX]) {
	count[0] = count[1] = 1;

	for (int i = 2; i <= len; i++) {
		if (makeNum(arr[i - 1], arr[i]) <= 26) {
			count[i] = count[i - 1] + count[i - 2];
		} else {
			count[i] = count[i - 1];
		}
	}
}

int makeNum(int d10, int d1) {
	return ((d10 * 10) + d1);
}

