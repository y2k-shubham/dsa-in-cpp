// http://www.practice.geeksforgeeks.org/problem-page.php?pid=496

/*
2
5
@ % $ # ^
% @ # $ ^
9
^ & % @ # * $ ~ !
~ # @ % & * $ ^ !
*/

#include <cstdio>
#include <cstring>

using namespace std;
#define LEN 256
#define MAX 9

void showArray(char [LEN], bool [MAX], int);
void output(char [LEN], bool present[MAX], int);

int main() {
	int T;
	char order[] = {'!', '#', '$', '%', '&', '*', '@', '^', '~'};

	scanf("%d", &T);
	while (T-- > 0) {
		bool present[MAX];
		int N;
		int ctr, i;

		scanf("%d", &N);
		memset(present, false, sizeof(present));
		getc(stdin);

		// input nuts
		for (i = 0; i < N; i++) {
			// read character in mark as present
			char ch = getc(stdin);
//			printf("read %c\n", ch);
			present[((int) ch)] = true;
			// consume space or enter
			getc(stdin);
//			printf("11");
		}

		// consume bolts input
		for (i = 0; i < N; i++) {
			getc(stdin);
			getc(stdin);
//			printf("12");
		}

		showArray(order, present, N);
	}

	return 0;
}

void output(char order[LEN], bool present[MAX], int N) {
	int i, ctr;

	printf("N = %d\n", N);
	// show nuts and bolts output
	ctr = 0;
	for (i = 0; ctr < N - 1; i++) {
		if (present[(int) order[i]]) {
			printf("%c ", order[i]);
			++ctr;
			printf("ctr = %d\n", ctr);
		}
//		printf("1");
	}
	for (; ctr < N; i++) {
		if (present[(int) order[i]]) {
			printf("%c\n", order[i]);
			++ctr;
			printf("ctr = %d\n", ctr);
		}
//		printf("2");
	}
}

void showArray(char order[LEN], bool present[MAX], int N) {
	printf("\nThe entered characters are:-\n");
	output(order, present, N);
}

