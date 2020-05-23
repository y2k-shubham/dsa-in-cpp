#include <stdio.h>
#include <string.h>

#define notdone -1
#define done 0
#define chef 1
#define assistant 2

int main() {
	int T;
	int m;
	int n;
	int index;
	int jobs[1001];
	int turn;
	int chefMax;
	int assistantMax;
	int i;
	int j;

	scanf("%d", &T);

	for (i = 1; i <= T; i++) {
		scanf("%d %d", &n, &m);
		memset(jobs, notdone, (1001 * sizeof(int)));

		for (j = 1; j <= m; j++) {
			scanf("%d", &index);
			jobs[index] = done;
		}

		turn = chef;
		chefMax = 0;
		assistantMax = 0;

		for (j = 1; j <= n; ) {
			// look for a job that is yet to be done (has not been done by cooks)
			while ((j <= n) && (jobs[j] != notdone)) {
				j++;
			}

			if (j <= n) {
				// assign job to chef or assistant, based on whoever's turn it is
				jobs[j++] = turn;

				// change the turn
				if (turn == chef) {
					//printf("job %d -> chef\n", (j - 1));
					chefMax = j;
					turn = assistant;
				} else {
					//printf("job %d -> assistant\n", (j - 1));
					assistantMax = j;
					turn = chef;
				}
			}
		}

		// display jobs to be done by chef
		if (chefMax > 0) {
			// find and display the first job (job with least index) to be done by chef
			for (j = 1; (j <= chefMax) && (jobs[j] != chef); j++) {
			}
			printf("%d", j++);

			// find and display the subsequent jobs to be done by chef
			for (; j < chefMax; j++) {
				if (jobs[j] == chef) {
					printf(" %d", j);
				}
			}

			// display newline
			printf("\n");
		} else {
			printf("\n");
		}

		// display jobs to be done by assistant
		if (assistantMax > 0) {
			// find and display the first job (job with least index) to be done by assistant
			for (j = 1; (j <= assistantMax) && (jobs[j] != assistant); j++) {
			}
			printf("%d", j++);

			// find and display the subsequent jobs to be done by assistant
			for (; j < assistantMax; j++) {
				if (jobs[j] == assistant) {
					printf(" %d", j);
				}
			}

			// display newline
			printf("\n");
		} else {
			printf("\n");
		}
	}
}
