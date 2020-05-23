// http://www.geeksforgeeks.org/find-minimum-time-to-finish-all-jobs-with-given-constraints/
/*
Input:
3
4 5 10
2
5
Output:
50

Input:
6
10 7 8 12 6 8
4
5
Output:
75

Input:
7
8 1 3 7 4 2 9
3
5
Output:
60
*/
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

#define LEN 100
#define max(a, b) ((a > b) ? a : b)

int input(int [LEN], int &, int &, int &);
bool isPossible(int [LEN], int, int, int, int [LEN]);
void output(int [LEN], int, int, int [LEN]);

int main() {
	int n, k, t;
	int totalTime;
	int jobs[LEN];
	int bestAssignment[LEN];

	totalTime = input(jobs, n, k, t);
	int lo = 0;
	int hi = totalTime;

	int ctr = 1;
	while (lo <= hi) {
		int crrAssignment[LEN];
		int mid = (lo + hi) / 2;

//		printf("\nIter %d begin\tlo = %d\thi = %d\n", ctr, lo, hi);
		if (isPossible(jobs, n, k, mid, crrAssignment)) {
//			printf("mid = %d, assignment possible\n", mid);
			hi = mid - 1;
			memcpy(bestAssignment, crrAssignment, sizeof(int) * n);
		} else {
//			printf("mid = %d, assignment not possible\n", mid);
			lo = mid + 1;
		}

//		printf("Iter %d end  \tlo = %d\thi = %d\n", ctr++, lo, hi);
	}

	output(jobs, n, t, bestAssignment);

	return 0;
}

int input(int jobs[LEN], int &n, int &k, int &t) {
	int i, sum;

	printf("Enter no of jobs:\t");
	scanf("%d", &n);

	printf("Enter size of jobs one-by-one:-\n");
	for (i = 0, sum = 0; i < n; i++) {
		scanf("%d", &jobs[i]);
		sum += jobs[i];
	}

	printf("\nEnter number of workers:\t\t");
	scanf("%d", &k);

	printf("Enter time taken to finsh unit job:\t");
	scanf("%d", &t);

	return sum;
}

bool isPossible(int jobs[LEN], int n, int k, int maxDur, int assignment[LEN]) {
	int crrDur, workerNo;

	memset(assignment, 0, sizeof(assignment));
	crrDur = 0;
	workerNo = 1;

	for (int i = 0; i < n; i++) {
		if ((crrDur + jobs[i]) <= maxDur) {
			// as long as a job can be assigned to current worker keeping finish time
			// within maxDuration, do this assignment
			assignment[i] = workerNo;
			crrDur += jobs[i];

			// otherwise, we have no option but to assign current job a new worker
		} else if (((workerNo + 1) > k) || (jobs[i] > maxDur)) {
			// if no more workers are left, this assignment is not possible
			return false;
		} else {
			// otherwise, assign current job to a new worker
			assignment[i] = ++workerNo;
			crrDur = jobs[i];
		}
//		printf("job %d assigned to worker %d\tcrrDur = %d\n", i, workerNo, crrDur);
	}

	// if loop ran to completion, it means a legal assignment of jobs to workers was made
	return true;
}

void output(int jobs[LEN], int n, int t, int assignment[LEN]) {
	int crrWorker;
	int crrTime, maxTime;

	crrTime = maxTime = 0;
	crrWorker = 1;

	printf("\nA possible optimum assignment is:-\n");
	printf("Job:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", jobs[i]);
	}

	printf("\nWorker:\t");
	for (int i = 0; i < n; i++) {
		printf("%d\t", assignment[i]);
		if (assignment[i] == crrWorker) {
			crrTime += jobs[i];
		} else {
			maxTime = max(maxTime, crrTime);
			crrTime = jobs[i];
			crrWorker = assignment[i];
		}
	}
	maxTime = max(maxTime, crrTime);

	printf("\n\nMinimum no of workers used is %d\n", assignment[n - 1]);
	printf("Minimum completion time is %d units\n", (maxTime * t));
}
