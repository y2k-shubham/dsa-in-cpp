// http://www.geeksforgeeks.org/find-jobs-involved-in-weighted-job-scheduling/
// http://www.geeksforgeeks.org/weighted-job-scheduling/

/*
4
1 2 50
3 5 20
6 19 100
2 100 200
*/

#include <cstdio>
#include <iostream>
#include <cmath>
#include <climits>
#include <algorithm>

struct job {
	int start;
	int end;
	int prof;
};

using namespace std;
#define MAX 100

void input(job jobList[MAX], int &);
void init(int [MAX], int);
void init(int [MAX], int, job [MAX]);
bool comparator(const job &, const job &);
bool comparator2(const job &, const job &);
int ceilInd(job [MAX], int, int, int);
void findMaxProf(job [MAX], int, int [MAX], int [MAX]);
void output(job [MAX], int, int [MAX], int [MAX]);
void showJobs(job [MAX], int [MAX], int [MAX], int);
void showArray(job [MAX], int);
void showArray(int [MAX], int, const char *, const char *);

int main() {
	job jobList[MAX];
	int n;
	int prof[MAX], par[MAX];

	input(jobList, n);

//	sort(jobList, jobList + n, comparator);
	sort(jobList, jobList + n, comparator2);
	showArray(jobList, n);

	init(prof, n, jobList);
	init(par, n);

	findMaxProf(jobList, n, prof, par);
	output(jobList, n, prof, par);

	return 0;
}

void input(job jobList[MAX], int &n) {
	cout << "Enter no of jobs:\t";
	cin >> n;

	cout << "Enter jobs as (start, end, profit):-\n";
	for (int i = 0; i < n; i++) {
		cin >> jobList[i].start >> jobList[i].end >> jobList[i].prof;
	}
}

void init(int arr[MAX], int len) {
	for (int i = 0; i < len; i++) {
		arr[i] = i;
	}
}

void init(int arr[MAX], int len, job jobList[MAX]) {
	for (int i = 0; i < len; i++) {
		arr[i] = jobList[i].prof;
	}
}

bool comparator(const job &j1, const job &j2) {
	return j1.start < j2.start;
}

bool comparator2(const job &j1, const job &j2) {
	return j1.end < j2.end;
}

int ceilInd(job jobList[MAX], int lo, int hi, int val) {
	if (lo > hi || val < jobList[lo].end) {
		return -1;
	} else if (jobList[hi].end <= val) {
		return hi;
	} else {
		int mid = (lo + hi) / 2;

		if (jobList[mid].end < val) {
			if (mid + 1 <= hi && jobList[mid + 1].end <= val) {
				return ceilInd(jobList, mid + 1, hi, val);
			} else {
				return mid;
			}
		} else if (jobList[mid].end == val) {
			if (mid + 1 <= hi && jobList[mid + 1].end == val) {
				return ceilInd(jobList, mid + 1, hi, val);
			} else {
				return mid;
			}
		} else {
			if (mid - 1 >= lo && jobList[mid - 1].end > val) {
				return ceilInd(jobList, lo, mid - 1, val);
			} else {
				return mid - 1;
			}
		}
	}
}

void findMaxProf(job jobList[MAX], int n, int prof[MAX], int par[MAX]) {
	prof[0] = jobList[0].prof;
	for (int i = 1; i < n; i++) {
		int ceil = ceilInd(jobList, 0, i - 1, jobList[i].start);

		if (ceil >= 0 && prof[ceil] + jobList[i].prof > prof[i - 1]) {
			prof[i] = prof[ceil] + jobList[i].prof;
			par[i] = ceil;
		} else {
			prof[i] = prof[i - 1];
			par[i] = -1;
		}

//		cout << "\n=========================\n";
//		printf("at job[%d] = ([%d, %d] %d)\n", i, jobList[i].start, jobList[i].end, jobList[i].prof);
//		showArray(prof, n, "prof[]", "profit");
//		showArray(par, n, "par[]", "parent");
	}
}

void output(job jobList[MAX], int n, int prof[MAX], int par[MAX]) {
	cout << "\nMaximum Profit is:\t" << prof[n - 1] << endl;
	cout << "List of jobs is:-\n";
	showJobs(jobList, prof, par, n - 1);
}

void showJobs(job jobList[MAX], int prof[MAX], int par[MAX], int crrInd) {
	if (crrInd >= 0) {
		if (par[crrInd] < 0) {
			showJobs(jobList, prof, par, crrInd - 1);
		} else if (par[crrInd] == crrInd) {
			printf("([%d, %d] %d)\t", jobList[crrInd].start, jobList[crrInd].end, jobList[crrInd].prof);
		} else {
			showJobs(jobList, prof, par, par[crrInd]);
			printf("([%d, %d] %d)\t", jobList[crrInd].start, jobList[crrInd].end, jobList[crrInd].prof);
		}
	}
}

void showArray(job jobList[MAX], int n) {
	cout << "\nList of jobs is:-\n";

	cout << "Ind:\t";
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Start:\t";
	for (int i = 0; i< n; i++) {
		printf("%d\t", jobList[i].start);
	}
	cout << endl;

	cout << "End:\t";
	for (int i = 0; i< n; i++) {
		printf("%d\t", jobList[i].end);
	}
	cout << endl;

	cout << "Profit:\t";
	for (int i = 0; i< n; i++) {
		printf("$%d\t", jobList[i].prof);
	}
	cout << endl;
}

void showArray(int arr[MAX], int n, const char * msg1, const char * msg2) {
	printf("\n%s array is:-\n", msg1);

	cout << "Ind:\t";
	for (int i = 0; i < n; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << msg2 << ":\t";
	for (int i = 0; i< n; i++) {
		printf("%d\t", arr[i]);
	}
	cout << endl;
}

