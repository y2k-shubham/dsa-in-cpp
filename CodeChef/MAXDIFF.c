#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct node {
	int original;
	int current;
	struct node * next;
};

#define len 10
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

typedef struct node link;

link * createNode(int);
link * input(int, int *);
void output(link *);
void nullifyPointers(link * []);
void trimRears(link * []);
link * radixSort(link *, link * [], link * []);
void findSumFirstAndLastK(link *, int, int, int *, int *);
void setSumZero(int *, int *, int *);
void showResult(int [], int);

int main() {
	link * front[len];
	link * rear[len];
	link * head;
	int sumTotal;
	int sumFirstK;
	int sumLastK;
	int T;
	int K;
	int N;
	int i;

	scanf("%d", &T);
	int result[T];

	for (i = 0; i < T; i++) {
		scanf("%d%d", &N, &K);

		setSumZero(&sumTotal, &sumFirstK, &sumLastK);
		head = input(N, &sumTotal);
		//output(head);
		nullifyPointers(front);
		nullifyPointers(rear);
		head = radixSort(head, front, rear);
		//printf("\n===");
		//output(head);
		findSumFirstAndLastK(head, N, K, &sumFirstK, &sumLastK);

		/*
		printf("\n\nSum of first %d elements is:\t%d\nAnd sum of last  %d elements is:\t%d\n", K, sumFirstK, K, sumLastK);
		printf("Total sum is:\t\t\t%d\n", sumTotal);
		printf("===\n\n");
		*/

		result[i] = max(abs(sumFirstK - (sumTotal - sumFirstK)), abs(sumLastK - (sumTotal - sumLastK)));
	}
	showResult(result, T);

	return 0;
}

void findSumFirstAndLastK(link * head, int N, int K, int * sumFirstK, int * sumLastK) {
	link * list;
	int sumFirst;
	int sumLast;
	int index;

	sumFirst = 0;
	sumLast = 0;

	for (list = head, index = 1; list != NULL; index++, list = list -> next) {
		if (index <= K) {
			sumFirst += list -> original;
		}

		if (index > (N - K)) {
			sumLast += list -> original;
		}
	}

	* sumFirstK = sumFirst;
	* sumLastK = sumLast;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));

	newNode -> original = val;
	newNode -> current = val;
	newNode -> next = NULL;

	return newNode;
}

void setSumZero(int * a, int * b, int * c) {
	*a = *b = *c = 0;
}

link * input(int N, int * sum) {
	link * head;
	link * list;
	link * newNode;
	int number;
	int i;
	int temp;

	//printf("\nEnter positive integers to be sorted:-\n(Enter -999 to terminate)\n");
	temp = 0;

	scanf("%d", &number);
	temp += number;

	head = createNode(number);
	list = head;

	for (i = 1, list = head; i < N; i++) {
		scanf("%d", &number);
		temp += number;

		newNode = createNode(number);

		list -> next = newNode;
		list = newNode;
	}

	*sum = temp;
	return head;
}

void nullifyPointers(link * arr[]) {
	int i;

	for (i = 0; i < len; i++) {
		arr[i] = NULL;
	}
}

link * radixSort(link * head, link * front[], link * rear[]) {
	int i;
	int j;
	int digit;
	link * list;

	for (i = 1; i <= 10; i++) {
		// printf("\n\n====\n\nIN PASS %d:-\n", i);
		// inserting numbers into buckets 0 - 9
		for (list = head; list != NULL; list = list -> next) {
			digit = (list -> current) % 10;
			list -> current = (list -> current) / 10;

			// printf("\nNumber = %d\nDigit = %d\n", list -> original, digit);

			if (rear[digit] == NULL) {
				// printf("Inserted in front of bucket %d\n", digit);
				front[digit] = list;
				rear[digit] = list;
			} else {
				// printf("Inserted in rear of bucket %d after node %d\n", digit, rear[digit] -> original);
				rear[digit] -> next = list;
				rear[digit] = list;
			}
		}

		trimRears(rear);

		/*
		printf("\nAFTER PASS %d, THE BUCKETS ARE:-\n", i);
		for (j = 0; j < len; j++) {
		    printf("arr[%d] : ", j);
		    output(front[j]);
		    printf("\n");
		}

		printf("\nAND REARS ARE:-\n");
		for (j = 0; j < len; j++) {
		    printf("rear[%d] = ", j);

		    if (rear[j] != NULL) {
		        printf("%d\n", rear[j] -> original);
		    } else {
		        printf("NULL\n");
		    }
		}
		printf("\n\n====\n\n");
		*/

		// combining nodes of all buckets into single list
		// head initialized to front of first non-empty bucket
		for (j = 0; front[j] == NULL; j++) {
		}
		head = front[j];
		// then rear of each non-empty bucket linked to front of next non-empty bucket
		while (true) {
			list = rear[j];
			for (j++; (j < len) && (front[j] == NULL); j++) {
			}

			if (j < len) {
				list -> next = front[j];
			} else {
				list -> next = NULL;
				break;
			}
		}

		// nullifying arrays for re-use
		nullifyPointers(front);
		nullifyPointers(rear);
	}

	return head;
}

void trimRears(link * rear[]) {
	int i;

	for (i = 0; i < len; i++) {
		if (rear[i] != NULL) {
			rear[i] -> next = NULL;
		}
	}
}

void showResult(int result[], int T) {
	int i;

	for (i = 0; i < T; i++) {
		printf("%d\n", result[i]);
	}
}

void output(link * head) {
	link * list;

	printf("\nThe sorted numbers are:-\n");
	for (list = head; list != NULL; list = list -> next) {
		printf("%d\t", list -> original);
	}
}
