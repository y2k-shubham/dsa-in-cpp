// TusharRoy

/*
7
9 1 5
6 3 8
2 5 4
4 3 7
2 2 2
4 1 4
1 11 3

2
1 2 4
3 2 5
*/

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>

using namespace std;

void input(vector <tuple <int, int, int> > &);
void showVec(vector <tuple <int, int, int> >, const char *);
void quickSort(vector <tuple <int, int, int> > &, int, int);
int partition(vector <tuple <int, int, int> > &, int, int);
bool isNotLesser(const tuple <int, int, int> &, const tuple <int, int, int> &);
void swap(int &, int &);
void genPerms(vector <tuple <int, int, int> >, vector <tuple <int, int, int> > &);
void swap(int *, int, int);
int compute(vector <tuple <int, int, int> >, vector <int> &, vector <int> &);
void buildSoln(vector <int>, queue <int> &, int);
void showSoln(vector <tuple <int, int, int> >, queue <int>);
void init(vector <tuple <int, int, int> >, vector <int> &, vector <int> &);

int main() {
	vector <tuple <int, int, int> > boxes;
	vector <tuple <int, int, int> > perms;
	vector <int> maxHeight, parent;
	queue <int> soln;

	input(boxes);
	showVec(boxes, "List of types of boxes");

//	quickSort(boxes, 0, boxes.size() - 1);
//	showVec(boxes, "Sorted list of types of boxes");

	genPerms(boxes, perms);
	quickSort(perms, 0, perms.size() - 1);
	showVec(perms, "Sorted list of rotations of boxes");

	init(perms, maxHeight, parent);
	int maxInd = compute(perms, maxHeight, parent);

	buildSoln(parent, soln, maxInd);
	showSoln(perms, soln);

	return 0;
}

void init(vector <tuple <int, int, int> > perms, vector <int> &maxHeight, vector <int> &parent) {
	for (int i = 0; i < perms.size(); i++) {
		maxHeight.push_back(get <2> (perms[i]));
		parent.push_back(i);
	}
}

void input(vector <tuple <int, int, int> > &boxes) {
	int noTypes;

	printf("Enter no of box types:\t");
	cin >> noTypes;

	printf("Enter dimensions of different types of boxes\n(l, b, h):-\n");
	for (int i = 1; i <= noTypes; i++) {
		int l, b, h;

		cin >> l >> b >> h;
		boxes.push_back(make_tuple(l, b, h));
	}
}

void showVec(vector <tuple <int, int, int> > vec, const char * msg) {
	printf("\n%s is:-\n", msg);
	for (int i = 0; i < vec.size(); i++) {
		printf("vec[%d] = (%d, %d, %d)\n", i, get <0> (vec[i]), get <1> (vec[i]), get <2> (vec[i]));
	}
	cout << endl;
}

void quickSort(vector <tuple <int, int, int> > &vec, int lo, int hi) {
	if (lo < hi) {
		int pInd = partition(vec, lo, hi);
		quickSort(vec, lo, pInd - 1);
		quickSort(vec, pInd + 1, hi);
	}
}

int partition(vector <tuple <int, int, int > > &vec, int lo, int hi) {
	int pInd = hi;
	tuple <int, int, int> pEle = vec[hi];

	int i, j;
	for (i = lo - 1, j = lo; j < pInd; j++) {
		if (isNotLesser(vec[j], pEle)) {
			i++;
			swap(get <0> (vec[i]), get <0> (vec[j]));
			swap(get <1> (vec[i]), get <1> (vec[j]));
			swap(get <2> (vec[i]), get <2> (vec[j]));
		}
	}

	i++;
	swap(get <0> (vec[i]), get <0> (vec[j]));
	swap(get <1> (vec[i]), get <1> (vec[j]));
	swap(get <2> (vec[i]), get <2> (vec[j]));

	return i;
}

bool isNotLesser(const tuple <int, int, int> &t1, const tuple <int, int, int> &t2) {
	int a1 = get <0> (t1) * get <1> (t1);
	int a2 = get <0> (t2) * get <1> (t2);

	if (a1 == a2) {
		return get <2> (t1) < get <2> (t2);
	} else {
		return a1 > a2;
	}
}

bool isLesser(const tuple <int, int, int> &t1, const tuple <int, int, int> &t2) {
	if (get <0> (t1) < get <0> (t2) && get <1> (t1) < get <1> (t2)) {
		return true;
	} else {
		return false;
	}
}

void swap(int &e1, int &e2) {
	int tmp = e1;
	e1 = e2;
	e2 = tmp;
}

void genPerms(vector <tuple <int, int, int> > boxes, vector <tuple <int, int, int> > &perms) {
	const int len = 3;
	int tmp[len];

	for (int i = 0; i < boxes.size(); i++) {
		tie(tmp[0], tmp[1], tmp[2]) = boxes[i];
		sort(tmp, tmp + len, greater <int> ());

		bool wasSame = false;
		for (int j = 0; j < len - 1; j++) {
			for (int k = j + 1; k < len; k++) {
				if (tmp[j] > tmp[k]) {
					wasSame = false;
					swap(tmp, j, 0);
					swap(tmp, k, 1);
					perms.push_back(make_tuple(tmp[0], tmp[1], tmp[2]));
					swap(tmp, j, 0);
					swap(tmp, k, 1);
				} else if (tmp[k] > tmp[j]) {
					wasSame = false;
					swap(tmp, j, 1);
					swap(tmp, k, 0);
					perms.push_back(make_tuple(tmp[0], tmp[1], tmp[2]));
					swap(tmp, j, 1);
					swap(tmp, k, 0);
				} else {
					if (wasSame == false) {
						perms.push_back(make_tuple(tmp[0], tmp[1], tmp[2]));
						wasSame = true;
					}
				}
			}

			while (j + 1 < len && tmp[j] == tmp[j + 1]) {
				++j;
			}
		}
	}
}

void swap(int * arr, int i1, int i2) {
	int tmp = arr[i1];
	arr[i1] = arr[i2];
	arr[i2] = tmp;
}

int compute(vector <tuple <int, int, int> > perms, vector <int> &maxHeight, vector <int> &parent) {
	int maxVal, maxInd;

	maxVal = 0;
	maxInd = -1;
	for (int i = 1; i < maxHeight.size(); i++) {
//		printf("\nat box %d (%d, %d, %d)\n", i, get <0> (perms[i]), get <1> (perms[i]), get <2> (perms[i]));

		if (get <2> (perms[i]) > maxVal) {
//			printf("updated (maxVal, maxInd) from (%d, %d) to (%d, %d)\n", maxVal, maxInd, get <2> (perms[i]), i);

			maxVal = get <2> (perms[i]);
			maxInd = i;
		}

		for (int j = 0; j < i; j++) {
			if (isLesser(perms[i], perms[j]) && maxHeight[i] < maxHeight[j] + get <2> (perms[i])) {
				maxHeight[i] = maxHeight[j] + get <2> (perms[i]);

				if (maxHeight[i] > maxVal) {
//					printf("updated (maxVal, maxInd) from (%d, %d) to (%d, %d)\n", maxVal, maxInd, maxHeight[i], i);

					maxVal = maxHeight[i];
					maxInd = i;
					parent[i] = j;
				}
			}
		}
	}

	return maxInd;
}

void buildSoln(vector <int> parent, queue <int> &soln, int maxInd) {
	soln.push(maxInd);
	while (parent[maxInd] != maxInd) {
		maxInd = parent[maxInd];
		soln.push(maxInd);
	}
}

void showSoln(vector <tuple <int, int, int> > perms, queue <int> soln) {
	int sum = 0;

	printf("\nTallest possible arrangement of boxes is:-\n");
	while (!soln.empty()) {
		int l, b, h;

		tie(l, b, h) = perms[soln.front()];
		soln.pop();
		sum += h;

		printf("(%d, %d, %d)\tArea = %d\n", l, b, h, (l * b));
	}

	printf("Total height of structure is %d\n", sum);
}
