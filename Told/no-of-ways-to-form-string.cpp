#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void showArr(int [MAX], int, const char *);
void calc(int [MAX], int, int [MAX]);

int main() {
	int arr[MAX], len;
	int tab[MAX];

	input(arr, len);
	showArr(arr, len, "arr[]");

	memset(tab, 0, len * sizeof(int));
	calc(arr, len, tab);

	showArr(tab, len, "tab[]");
	cout << "\nNo of ways = " << (tab[len - 1] + 1) << endl;

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

void showArr(int arr[MAX], int len, const char * msg) {
	printf("\n%s is:-\n", msg);

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl;
}

void calc(int arr[MAX], int len, int tab[MAX]) {
	if ((arr[0] * 10 + arr[1]) <= 26) {
		tab[1] = 1;
	}

	for (int i = 2; i < len; i++) {
		if ((arr[i - 1] * 10 + arr[i]) <= 26) {
			tab[i] += tab[i - 2] + 1;
		}
		tab[i] += tab[i - 1] + 1;

		tab[i]--;
	}
}

