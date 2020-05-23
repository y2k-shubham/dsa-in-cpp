#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int original;
	int current;
	struct node * next;
};

#define len 10
typedef struct node link;

link * createNode(int);
link * input();
void output(link *);
void nullifyPointers(link * []);
void trimRears(link * []);
link * radixSort(link *, link * [], link * []);

int main() {
	link * front[len];
	link * rear[len];
	link * head;

	head = input();
	//output(head);
	nullifyPointers(front);
	nullifyPointers(rear);
	head = radixSort(head, front, rear);
	output(head);

	return 0;
}

link * createNode(int val) {
	link * newNode;

	newNode = (link *) malloc(sizeof(link));

	newNode -> original = val;
	newNode -> current = val;
	newNode -> next = NULL;

	return newNode;
}

link * input() {
    int i;
    int n;
    link * head;
	link * list;
	link * newNode;
	int number;

	scanf("%d", &n);
	scanf("%d", &number);

	head = createNode(number);
	for (list = head, i = 2; i <= n; i++) {
		scanf("%d", &number);

		newNode = createNode(number);
		list -> next = newNode;
		list = newNode;
	}

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

	for (i = 1; i <= 6; i++) {
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

void output(link * head) {
    link * list;

    //printf("\nThe sorted numbers are:-\n");
    for (list = head; list != NULL; list = list -> next) {
        printf("%d\n", list -> original);
    }
}
