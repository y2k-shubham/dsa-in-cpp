/*
6
7 9 2
5 8 11
6 7 4
4 6 5
2 5 6
1 3 5

6
7 9 5
5 8 11
6 7 4
4 6 5
2 5 6
1 3 5
*/

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100

struct job {
	int start;
	int end;
	int profit;
};

void input(vector <job> &);
bool comparator(const job &, const job &);
void init(vector <job>, int [MAX], int [MAX]);
void showVec(vector <job>);
int calc(vector <job>, int [MAX], int [MAX]);
bool overlaps(job, job);
void output(int [MAX], int);

int main() {
	vector <job> jobVec;
	int maxProf[MAX];
	int par[MAX];

	input(jobVec);
//	showVec(jobVec);
	sort(jobVec.begin(), jobVec.end(), comparator);
	init(jobVec, maxProf, par);
//	showVec(jobVec);

	int lJob = calc(jobVec, maxProf, par);

	printf("Sequence of jobs is:-\n");
	output(par, lJob);
	printf("\n");

	return 0;
}

void input(vector <job> &jobVec) {
	int jobCount;

	printf("Enter no of jobs:\t");
	scanf("%d", &jobCount);
	jobVec.resize(jobCount);

	printf("Enter jobs as (start, end, profit):-\n");
	for (int i = 0; i < jobCount; i++) {
		scanf("%d%d%d", &jobVec[i].start, &jobVec[i].end, &jobVec[i].profit);
	}
}

bool comparator(const job &j1, const job &j2) {
	return j1.end < j2.end;
}

void init(vector <job> jobVec, int maxProfit[MAX], int par[MAX]) {
	for (int i = 0; i < jobVec.size(); i++) {
		maxProfit[i] = jobVec[i].profit;
		par[i] = -1;
	}
}

void showVec(vector <job> jobVec) {
	printf("\nList of jobs is:-");

	int ctr = 0;
	for (vector <job>::iterator it = jobVec.begin(); it != jobVec.end(); it++) {
		printf("\nJob %d\n", ctr++);
		printf("Start = %d\n", (*it).start);
		printf("End = %d\n", (*it).end);
		printf("Profit = %d\n", (*it).profit);
	}
	printf("\n");
}

int calc(vector <job> jobVec, int maxProfit[MAX], int par[MAX]) {
	int mProf, mProfInd;

	mProf = maxProfit[0];
	mProfInd = 0;

	for (int i = 1; i < jobVec.size(); i++) {
		for (int j = 0; j < i; j++) {
			if (!overlaps(jobVec[j], jobVec[i]) && maxProfit[j] + jobVec[i].profit > maxProfit[i]) {
				maxProfit[i] = maxProfit[j] + jobVec[i].profit;
				par[i] = j;
			}

			if (maxProfit[i] > mProf) {
				mProf = maxProfit[i];
				mProfInd = i;
			}
		}
	}

	printf("\nMax Profit is %d\n", mProf);
	return mProfInd;
}

bool overlaps(job j1, job j2) {
	return j1.end > j2.start;
}

void output(int par[MAX], int ind) {
	if (par[ind] == -1) {
		printf("J%d ", ind);
	} else {
		output(par, par[ind]);
		printf("J%d ", ind);
	}
}

