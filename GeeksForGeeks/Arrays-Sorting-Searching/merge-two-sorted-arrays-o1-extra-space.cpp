// http://www.geeksforgeeks.org/merge-two-sorted-arrays-o1-extra-space/

/*
6
1 5 9 10 15 20
4
2 3 8 13

6
1 2 3 5 8 9
4
10 13 15 20
*/

#include <cstdio>
#define MAX 100

void input(int [MAX], int &, const char *);
void showArray(int [MAX], int, const char *);
void merge(int [MAX], int, int [MAX], int);

int main() {
	int n1, n2;
	int a1[MAX];
	int a2[MAX];

	input(a1, n1, "first");
	input(a2, n2, "second");

	merge(a1, n1, a2, n2);

	showArray(a1, n1, "first array after merging");
	showArray(a2, n2, "second array after merging");

	return 0;
}

void input(int a[MAX], int &n, const char * s) {
	printf("Enter size of %s array:\t", s);
	scanf("%d", &n);

	printf("Enter elements of %s array:-\n", s);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
}

void showArray(int a[MAX], int n, const char * msg) {
	printf("\nThe %s is:-\n", msg);

	printf("Ind:\t");
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	printf("\n");

	printf("Ele\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", a[i]);
	}
	printf("\n");
}

void merge(int a1[MAX], int n1, int a2[MAX], int n2) {
	int l1 = n1 - 1;
	for (int i = n2 - 1; i >= 0; i--) {
//		showArray(a1, n1, "first");
//		showArray(a2, n2, "second");

		int tmp = a2[i];
//		printf("\na2[%d] = %d\n", i, a2[i]);

		if (a1[l1] > tmp) {
			int j;

//			printf("a1[%d] = %d written to a2[%d] = %d\n", l1, a1[l1], i, a2[i]);
			a2[i] = a1[l1];

			for (j = l1; j >= 1 && a1[j - 1] > tmp; j--) {
//				printf("a1[%d] = %d copied to a1[%d] = %d\n", (j - 1), a1[j - 1], j, a1[j]);
				a1[j] = a1[j - 1];
			}

//			printf("tmp = %d written to a1[%d] = %d\n", tmp, j, a1[j]);
			a1[j] = tmp;
		}
	}
}

