/*
11
8 7 8 9 10 9 8 7 6 5 6

17
9 8 9 8 7 6 7 6 5 4 3 4 5 6 7 8 7
*/

#include <cstdio>
#include <iostream>
#include <list>

using namespace std;
#define MAX 100

void input(int [MAX], int&, int&);
void showArr(int [MAX], int);
list <int> binSearch(int [MAX], int, int, int);
list <int> appendList(list <int>, list <int>, bool);
void showRes(list <int>, int);
list <int> jmpSearch(int [MAX], int, int);
int abs(int);

int main() {
	int a[MAX], len;
	int ele;

	input(a, len, ele);

	showRes(binSearch(a, 0, len - 1, ele), ele);
	showRes(jmpSearch(a, len, ele), ele);

	return 0;
}

void input(int a[MAX], int& len, int& ele) {
	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		cin >> a[i];
	}

	showArr(a, len);

	printf("\nEnter element to be searched:\t");
	cin >> ele;
}

void showArr(int a[MAX], int len) {
	printf("\na[] array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		printf("%d\t", a[i]);
	}
	cout << endl;
}

list <int> binSearch(int a[MAX], int lo, int hi, int ele) {
	if (lo > hi) {
		list <int> empList;
		return empList;
	} else {
		int mid = (lo + hi) / 2;
		list <int> resList;

		if (a[mid] == ele) {
			resList.push_back(mid);
		}

		if ((a[lo] <= ele && ele <= a[mid]) || (a[lo] >= ele && ele >= a[mid]) ||
				(((a[lo] <= ele && ele >= a[mid]) || (a[lo] >= ele && ele <= a[mid]))
				 && (abs(a[lo] - ele) + abs(ele - a[mid]) <= (mid - lo)))) {
			resList = appendList(resList, binSearch(a, lo, mid - 1, ele), true);
		}

		if ((a[mid] <= ele && ele <= a[hi]) || (a[mid] >= ele && ele >= a[hi]) ||
				(((a[mid] <= ele && ele >= a[hi]) || (a[mid] >= ele && ele <= a[hi]))
				 && (abs(a[mid] - ele) + abs(ele - a[hi]) <= (hi - mid)))) {
			resList = appendList(resList, binSearch(a, mid + 1, hi, ele), false);
		}

		return resList;
	}
}

list <int> appendList(list <int> dstList, list <int> srcList, bool inFront) {
	if (srcList.empty() == false) {
		if (inFront == true) {
			dstList.insert(++(dstList.begin()), srcList.begin(), srcList.end());
		} else {
			dstList.insert(dstList.end(), srcList.begin(), srcList.end());
		}
	}

	return dstList;
}

void showRes(list <int> resList, int ele) {
	if (resList.empty()) {
		printf("\nElement %d is not present in the array\n", ele);
	} else {
		printf("\nElement %d is present in the array at positions:-\n", ele);
		for (list <int>::iterator i = resList.begin(); i != resList.end(); i++) {
			printf("%d\t", *i);
		}
		cout << endl;
	}
}

list <int> jmpSearch(int a[MAX], int len, int ele) {
	list <int> resList;
	int i;

	i = 0;
	while (i >= 0 && i < len) {
		if (a[i] == ele) {
//			printf("at a[%d] = %d\telement found\tincrementing i by 1\n", i, a[i]);
			resList.push_back(i);
			i++;
		} else {
//			printf("at a[%d] = %d\tincrementing i by %d\n", i, a[i], abs(a[i] - ele));
			i += abs(a[i] - ele);
		}
	}

	return resList;
}

int abs(int a) {
	if (a >= 0) {
		return a;
	} else {
		return (-a);
	}
}

