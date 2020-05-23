// http://www.geeksforgeeks.org/print-all-subarrays-with-0-sum/
// RELATED:
// http://www.geeksforgeeks.org/find-the-largest-subarray-with-0-sum/
// http://www.geeksforgeeks.org/find-if-there-is-a-subarray-with-0-sum/

/*
11
6 3 -1 -3 4 -2 2 4 6 -12 -7

8
15 -2 2 -8 1 7 10 23

3
1 2 3

3
1 0 3

5
4 2 -3 1 6

5
4 2 0 1 6

5
-3 2 3 1 6
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <list>

using namespace std;
#define MAX 100

void input(int [MAX], int &);
void createMap(int [MAX], int, map <int, list <int> > &);
void output(int [MAX], int, map <int, list <int> >);
void showMap(map <int, list <int> >);
void showArray(int [MAX], int);

int main() {
	int arr[MAX], len;
	map <int, list <int> > sumIndMap;

	input(arr, len);
	createMap(arr, len, sumIndMap);

	showArray(arr, len);
	showMap(sumIndMap);

	output(arr, len, sumIndMap);

	return 0;
}

void input(int arr[MAX], int &len) {
	cout << "Enter length of array:\t";
	cin >> len;

	cout << "Enter elements of array:-\n";
	for (int i = 0; i < len; i++) {
		cin >> arr[i];
	}
}

void createMap(int arr[MAX], int len, map <int, list <int> > &sumIndMap) {
	list <int> tmpList;
	tmpList.push_back(-1);
	sumIndMap[0] = tmpList;

	int sum = 0;
	for (int i = 0; i < len; i++) {
		sum += arr[i];

//		printf("at\tarr[%d] = %d,\tsum = %d\t", i, arr[i], sum);
		if (sumIndMap.find(sum) == sumIndMap.end()) {
//			printf("new entry added to map\n");
			list <int> tmpList;
			tmpList.push_back(i);
			sumIndMap.insert(make_pair(sum, tmpList));
		} else {
//			printf("index %d pushed to map[%d]\n", i, sum);
			sumIndMap[sum].push_back(i);
		}
	}
}

void showMap(map <int, list <int> > sumIndMap) {
	printf("\nMap is:\n");
	for (map <int, list <int> >::iterator i = sumIndMap.begin(); i != sumIndMap.end(); i++) {
		printf("%d\t=\t", (*i).first);
		for (list <int>::iterator j = ((*i).second).begin(); j != ((*i).second).end(); j++) {
			printf("%d ", *j);
		}
		cout << endl;
	}
	cout << endl;
}

void showArray(int arr[MAX], int len) {
	printf("\nThe array is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < len; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < len; i++) {
		cout << arr[i] << "\t";
	}
	cout << endl << endl;
}

void output(int arr[MAX], int len, map <int, list <int> > sumIndMap) {
	cout << "\nRanges of array with 0 sum are:-\n";

	for (map <int, list <int> >::iterator i = sumIndMap.begin(); i != sumIndMap.end(); i++) {

		if (((*i).second).size() > 1) {

			for (list <int>::iterator j = (*i).second.begin(); j != (*i).second.end(); j++) {
				list <int>::iterator k = j;

				for (k++; k != (*i).second.end(); k++) {
					printf("arr[%d .. %d]\n", ((*j) + 1), *k);
				}
			}
		}
	}
}

