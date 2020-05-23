// http://www.practice.geeksforgeeks.org/problem-page.php?pid=347
// http://www.geeksforgeeks.org/count-pairs-difference-equal-k/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define MAX_LEN 100
#define MAX_SIZE 1001

void input(int [MAX_LEN], int &, int &, int [MAX_SIZE]);
int findCount(int [MAX_LEN], int, int, int [MAX_SIZE]);
void showArr(int [MAX_LEN], int);
void showFreq(int [MAX_SIZE]);
void init(int [MAX_SIZE]);

int main() {
	int Arr[MAX_LEN];
	int Freq[MAX_SIZE];
	int K;
	int N;
	int T;

	scanf("%d", &T);
	while (T-- > 0) {
		input(Arr, N, K, Freq);
		//showArr(Arr, N);
		//showFreq(Freq);
		printf("%d\n", findCount(Arr, N, K, Freq));
	}

	return 0;
}

void input(int Arr[MAX_LEN], int &N, int &K, int Freq[MAX_SIZE]) {
	scanf("%d%d", &N, &K);

	memset(Freq, 0, sizeof(Freq));	// not working for some reason so
	init(Freq);						// had to manually initialize to zero

	for (int i = 0; i < N; i++) {
		scanf("%d", &Arr[i]);
		Freq[Arr[i]]++;
	}
}

void init(int Freq[MAX_SIZE]) {
	for (int i = 0; i < MAX_SIZE; i++) {
		Freq[i] = 0;
	}
}

int findCount(int Arr[MAX_LEN], int N, int K, int Freq[MAX_SIZE]) {
	int count, diff, sum;

	count = 0;
	for (int i = 0; i < N; i++) {
		int temp = Arr[i];
		//printf("\nRead %d\n", temp);

		if ((diff = temp - K) >= 0) {
			count += Freq[diff];
			//printf("Added Freq[%d] = %d to count\n", diff, Freq[diff]);
		}

		if ((sum = temp + K) < MAX_SIZE) {
			count += Freq[sum];
			//printf("Added Freq[%d] = %d to count\n", sum, Freq[sum]);
		}
	}

	return count >> 1;
}

void showArr(int Arr[MAX_LEN], int N) {
	printf("\nThe array is:-\n");
	for (int i = 0; i < N; i++) {
		printf("%d\t", Arr[i]);
	}
	printf("\n");
}

void showFreq(int Freq[MAX_SIZE]) {
	printf("\nThe freq is:-\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		if (Freq[i] > 0) {
			printf("F[%d]=%d\t", i, Freq[i]);
		}
	}
	printf("\n");
}
