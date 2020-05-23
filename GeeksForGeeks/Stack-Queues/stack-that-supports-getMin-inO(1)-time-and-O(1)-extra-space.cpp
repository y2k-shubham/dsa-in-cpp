#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

#define MAX 100
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

void push(int [MAX], int &, int &, int);
void pop(int [MAX], int &, int &);
void showStack(int [MAX], int);

int main() {
	int stack[MAX];
	int top, minEle;
	int choice, ele;

	top = -1;
	choice = -1;

	while (choice != 5) {
		printf("\n---------------------------\n");
		printf("\n1. Push");
		printf("\n2. Pop");
		printf("\n3. Show");
		printf("\n4. GetMin");
		printf("\n5. Exit");

		printf("\nEnter choice:\t");
		scanf("%d", &choice);

		switch (choice) {
			case 1:
				printf("\nElement to push:\t");
				scanf("%d", &ele);
				push(stack, top, minEle, ele);
				break;

			case 2:
				pop(stack, top, minEle);
				break;

			case 3:
				showStack(stack, top);
				break;

			case 4:
				if (top >= 0) {
					printf("\nMinimum element:\t%d\n", minEle);
				} else {
					printf("\nError! : Stack UnderFlow\n");
				}
				break;

			case 5:
				continue;

			default:
				printf("\nInvalid Input\n");
		}
	}

	return 0;
}

void push(int stack[MAX], int &top, int &minEle, int ele) {
	if (top < MAX - 1) {
		if (top >= 0) {
			if (ele >= minEle) {
				stack[++top] = ele;
			} else {
				stack[++top] = (2 * ele) - minEle;
				minEle = ele;
			}
		} else {
			stack[++top] = ele;
			minEle = ele;
		}
	} else {
		printf("\nError! : Stack OverFlow\n");
	}
}

void pop(int stack[MAX], int &top, int &minEle) {
	if (top >= 0) {
		int ele = stack[top];

		if (stack[top] < minEle) {
			ele = minEle;
			minEle = (2 * minEle) - stack[top];
		}
		top--;

		printf("\nPopped element:\t%d\n", ele);
	} else {
		printf("\nError! : Stack UnderFlow\n");
	}
}

void showStack(int stack[MAX], int top) {
	if (top >= 0) {
		printf("\nThe stack is:-\n");
		for (int i = top; i >= 0; i--) {
			printf("%d\t", stack[i]);
		}
		printf("\n");
	} else {
		printf("\nError! : Stack UnderFlow\n");
	}
}
