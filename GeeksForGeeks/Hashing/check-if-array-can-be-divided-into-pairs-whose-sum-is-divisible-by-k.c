#include <stdio.h>
#include <strings.h>

void input(int *, int, int *, int);
int checkIfPossible(int *, int, int *, int);

// URL: http://www.geeksforgeeks.org/check-if-an-array-can-be-divided-into-pairs-whose-sum-is-divisible-by-k/
/*
    Problem: Check if it's possible to pick pairs of elements from arr, each of who's sum is divisible by k

    Soultion: Clearly, to make this happen, length of array n, should be even
              This is a question of Hashing. Here, we first find frequencies of various remainders obtained by dividing each element of arr
              by k. Next, we iterate through the array once more and check whether for each remainder r, following condition satisfies:
                (i)  If remainder is r = k/2 then freq[r] should be even
                (ii) For any other remainder freq[r] should be equal to freq[k - r]
              If the above two conditions hold for every element of the array, the answer is true, otherwise false
*/

int main() {
	int n;
	int k;
	int result;

	printf("Enter k:\t\t\t");
	scanf("%d", &k);

	printf("Enter length of arr:\t");
	scanf("%d", &n);

	int arr[n];
	int freq[k];

	memset(freq, 0, k * sizeof(int));

	input(&arr[0], n, &freq[0], k);
	result = checkIfPossible(&arr[0], n, &freq[0], k);

	if (result) {
		printf("It's possible to divide this array into pairs, each of who's sum is divisible by %d\n", k);
	} else {
		printf("It's not possible to divide this array into pairs, each of who's sum is divisible by %d\n", k);
	}

	return 0;
}

void input(int * arr, int n, int * freq, int k) {
	int i;

	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		freq[arr[i] % k]++;
	}
}

int checkIfPossible(int * arr, int n, int * freq, int k) {
	int i;
	int rem;

    if (n % 2) {
        return 0;
    }

	for (i = 0; i < n; i++) {
		rem = arr[i] % k;

		if (rem * 2 == k && freq[rem] % 2 == 0) {
			// means that if remainder is (k / 2) than we need even no of occurences of such remainder so that they pair up during summation
			// to for multiple of k
			// do nothing
		} else if (freq[rem] == freq[k - rem]) {
			// do nothing
		} else {
			return 0;
		}
	}

	return 1;
}
