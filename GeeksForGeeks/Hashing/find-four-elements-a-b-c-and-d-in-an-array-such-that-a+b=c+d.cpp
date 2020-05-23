// http://www.geeksforgeeks.org/find-four-elements-a-b-c-and-d-in-an-array-such-that-ab-cd/

/*
7
3 4 7 1 2 9 8

6
3 4 7 1 12 9

7
65 30 7 90 1 9 8
*/

#include <cstdio>
#include <map>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void findElements(int [MAX], int);

int main() {
	int arr[MAX];
	int n;

	input(arr, n);
	findElements(arr, n);

	return 0;
}

void input(int arr[MAX], int &n) {
	printf("Enter no of elements:\t");
	scanf("%d", &n);

	printf("Enter elements of array:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
}

void findElements(int arr[MAX], int n) {
	map <int, pair <int, int> > sumToIndicesMap;
	bool found = false;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			int sum = arr[i] + arr[j];

			if (sumToIndicesMap.find(sum) == sumToIndicesMap.end()) {
				sumToIndicesMap.insert(make_pair(sum, make_pair(i, j)));
			} else {
				pair <int, int> p = sumToIndicesMap[sum];
				printf("\n\nPairs of elements giving same sum are:-\n");
				printf("arr[%d] = %d\t&\tarr[%d] = %d\n", i, arr[i], j, arr[j]);
				printf("arr[%d] = %d\t&\tarr[%d] = %d\n", p.first, arr[p.first], p.second, arr[p.second]);
				printf("sum = %d\n", sum);
				found = true;
			}
		}
	}

	if (!found) {
		printf("\nNo such numbers found such that a+b = c+d\n");
	}
}
