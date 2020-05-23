// http://www.geeksforgeeks.org/find-a-tour-that-visits-all-stations/

/*
Input:
4
4 6
6 5
7 3
4 5
Output:
No solution

Input:
4
6 4
5 6
3 7
5 4
Output:
1
*/

#include <cstdio>
#define MAX 100

struct station {
	int distance;
	int petrol;
};

void input(station [MAX], int &);
int findStart(station [MAX], int);

int main() {
	station arr[MAX];
	int n;

	input(arr, n);
	int start = findStart(arr, n);

	if (start >= 0) {
		printf("\nThe first starting station is %d\n", start);
	} else {
		printf("\nNo solution\n");
	}

	return 0;
}

void input(station arr[MAX], int &n) {
	printf("Enter no of stations:\t");
	scanf("%d", &n);

	printf("Enter distance and petrol storage of each station:-\n");
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &arr[i].distance, &arr[i].petrol);
	}
}

int findStart(station arr[MAX], int n) {
	int start, end, count;
	int netPetrolLeft;

	count = 1;
	start = -1;
	end = -1;

	do {
		start++;
		end++;
		netPetrolLeft = arr[start].petrol - arr[start].distance;

//		printf("\ninitially\n");
//		printf("start:\tarr[%d] = (%d, %d)\tend:\tarr[%d] = (%d, %d)\n", start, arr[start].distance, arr[start].petrol, end, arr[end].distance, arr[end].petrol);
//		printf("count = %d\tnetPetrolLeft = %d\n", count, netPetrolLeft);
	} while (netPetrolLeft < 0);

	while (count < n) {
//		printf("\nincrementing queue\n");
		while (count < n && netPetrolLeft >= 0) {
			end = (end + 1) % n;
			netPetrolLeft += arr[end].petrol - arr[end].distance;
			count++;

//			printf("start:\tarr[%d] = (%d, %d)\tend:\tarr[%d] = (%d, %d)\n", start, arr[start].distance, arr[start].petrol, end, arr[end].distance, arr[end].petrol);
//			printf("count = %d\tnetPetrolLeft = %d\n", count, netPetrolLeft);
		}

		if (count == n && netPetrolLeft >= 0) {
//			printf("as count = %d, and netPetrolLeft = %d\treturning\n", count, netPetrolLeft);
			return start;
		}

//		printf("\ndecrementing queue\n");
		while (netPetrolLeft < 0) {
			netPetrolLeft -= arr[start].petrol - arr[start].distance;
			start = (start + 1) % n;
			count--;

			//			printf("start:\tarr[%d] = (%d, %d)\tend:\tarr[%d] = (%d, %d)\n", start, arr[start].distance, arr[start].petrol, end, arr[end].distance, arr[end].petrol);
//			printf("count = %d\tnetPetrolLeft = %d\n", count, netPetrolLeft);

			if (start == 0) {
				return -1;
			}
		}
	}

	return start;
}
