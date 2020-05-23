// https://www.hackerearth.com/practice/data-structures/arrays/1-d/practice-problems/algorithm/litte-jhool-and-world-tour-1/

/*
2

4 3
0 1
1 2
2 0

5 5
0 0
1 2
2 3
4 4
4 0

------------------

1
701509916
57
8567035 746421180
31111919 863409789
35810171 165803963
55893872 142635047
62196658 94907237
77952935 767957711
106007921 423336802
109008095 535960665
141538388 671613407
142789103 705938504
158646157 675945433
166212043 555665550
191202848 453281087
213179262 973333787
222278242 36691766
228125686 235275392
235078775 328357113
256665953 770495570
282303464 274411285
299124211 257746221
304971255 768875577
310918746 221345656
319735036 877708044
324770654 283458914
336035168 746055531
375420256 813637747
386357727 92377868
399824374 62621004
423563071 494262829
456413969 595277886
503532878 810942516
533767424 111556141
571577161 570213714
597769927 732752410
629411190 530310321
629477423 188698377
666702156 92828706
699704952 702801553
703906530 55456067
710095820 826191342
731764343 166583326
741777816 199246370
748970437 161422276
766006581 593629761
776952027 598623007
790247771 685671380
792124989 486431528
801063217 644004704
801954075 471455766
805738024 838499830
833707711 448848393
836943562 170395090
874789113 478854862
890925868 544798206
905373918 342713543
925464049 905820887
989827033 501317249
*/

#include <cstdio>
#include <iostream>

using namespace std;
#define MAX 100005

struct range {
	int start;
	int end;
	int otherInd;
	bool done;
};

int input(range [MAX], int, int);
void showArr(range [MAX], int);
bool isPossible(range [MAX], int, int);
void quickSort(range [MAX], int, int);
int partition(range [MAX], int, int);
void swap(range [MAX], int, int);

int main() {
	int T;
	range ranges[MAX];
	int N, M;

	scanf("%d", &T);
	while (T-- > 0) {
		scanf("%d%d", &N, &M);
		M = input(ranges, N, M);

		quickSort(ranges, 0, M - 1);
//
//		printf("\nN = %d\nM = %d", N, M);
//		showArr(ranges, M);

		if (isPossible(ranges, N, M)) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}

	return 0;
}

int input(range ranges[MAX], int N, int M) {
	int Xi, Yi;
	int Meff;
	int ind;

	Meff = M;
	ind = 0;
	for (int i = 0; i < M; i++) {
		scanf("%d%d", &Xi, &Yi);

		ranges[ind].done = false;
		if (Xi <= Yi && Xi < N) {
			ranges[ind].start = Xi;
			ranges[ind].end = Yi;
			ranges[ind].otherInd = -1;
			ind++;
		} else {
			ranges[ind].start = 0;
			ranges[ind].end = Yi;
			ranges[ind].otherInd = ind + 1;
			ind++;

			if (Xi < N) {
				ranges[ind].start = Xi;
				ranges[ind].end = N - 1;
				ranges[ind].otherInd = ind - 1;
				ind++;

				Meff++;
			}
//			printf("range (%d, %d) broken into (%d, %d) and (%d, %d)\n", Xi, Yi, ranges[ind - 2].first, ranges[ind - 2].second, ranges[ind - 1].first, ranges[ind - 1].second);
		}
	}

	return Meff;
}

void showArr(range ranges[MAX], int M) {
	printf("\nRanges are:-\n");
	for (int i = 0; i < M; i++) {
		printf("ranges[%d] = (%d %d)\t(%d, ", i, ranges[i].start, ranges[i].end, ranges[i].otherInd);
		if (ranges[i].done) {
			printf("true)\n");
		} else {
			printf("false)\n");
		}
	}
}

bool isPossible(range ranges[MAX], int N, int M) {
	int i;
	int prev;

	prev = -1;
//	cout << endl;

	for (i = 0; i < M; i++) {
		if ((ranges[i].otherInd == -1) || (ranges[ranges[i].otherInd].done == false)) {
			if (prev < ranges[i].start) {
				prev = ranges[i].start;
				ranges[i].done = true;
			} else if (prev < ranges[i].end) {
				prev++;
				ranges[i].done = true;
			} else {
//				printf("at range[%d] = %d %d\tcan't allocate prev = %d\n", i, ranges[i].start, ranges[i].end, prev);
				break;
			}
//			printf("range[%d] = (%d, %d)\tprev became %d\n", i, ranges[i].start, ranges[i].end, prev);

			if (prev >= N) {
//				printf("at range[%d] = %d %d\tprev became %d\n", i, ranges[i].start, ranges[i].end, prev);
				break;
			}
		} else {
//			printf("ranges[%d].otherInd = %d already done\n", i, ranges[i].otherInd);
		}
	}

	return (i == M);
}

void quickSort(range ranges[MAX], int lo, int hi) {
	if (lo < hi) {
		int pInd = partition(ranges, lo, hi);
		quickSort(ranges, lo, pInd - 1);
		quickSort(ranges, pInd + 1, hi);
	}
}

int partition(range ranges[MAX], int lo, int hi) {
	int pValStart, pValEnd;
	int i, j;

	pValStart = ranges[hi].start;
	pValEnd = ranges[hi].end;

	for (i = lo - 1, j = lo; j < hi; j++) {
		if ((ranges[j].start < pValStart) || (ranges[j].start == pValStart && ranges[j].end <= pValEnd)) {
			i++;
			swap(ranges, i, j);
		}
	}

	i++;
	swap(ranges, i, j);

	return i;
}

void swap(range ranges[MAX], int pos_1, int pos_2) {
	range tmp = ranges[pos_1];
	ranges[pos_1] = ranges[pos_2];
	ranges[pos_2] = tmp;

	ranges[ranges[pos_1].otherInd].otherInd = pos_1;
	ranges[ranges[pos_2].otherInd].otherInd = pos_2;
}

