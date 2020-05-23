// Soroco coding (2nd) round question

/*
7
8 1 3 7 4 2 9
3
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <list>

using namespace std;

void input(vector <int>&, int&);
void showVec(vector <int>);
void initMap(vector <int>, int, map <int, int>&, map <int, list <int> >&, map <int, int>&);
void showRes(vector <int>, int, map <int, int>, map <int, list <int> >, map <int, int>);
pair <int, int> getMax(map <int, int>, map <int, list <int> >, map <int, int>);
pair <int, int> getMin(map <int, int>, map <int, list <int> >, map <int, int>);
void removeEle(map <int, int>&, map <int, list <int> >&, map <int, int>&);
void addEle(map <int, int>&, map <int, list <int> >&, map <int, int>&, int, int);

int main() {
	int k;
	vector <int> vec;
	map <int, int> indMap, freqMap;
	map <int, list <int> > revIndMap;

	input(vec, k);
	showVec(vec);

	initMap(vec, k, indMap, revIndMap, freqMap);
	showRes(vec, k, indMap, revIndMap, freqMap);

	return 0;
}

void input(vector <int>& vec, int& k) {
	int len;

	printf("Enter length of array:\t");
	cin >> len;

	printf("Enter elements of array:-\n");
	for (int i = 0; i < len; i++) {
		int ele;
		cin >> ele;

		vec.push_back(ele);
	}

	printf("Enter window-size:\t");
	cin >> k;
}

void showVec(vector <int> vec) {
	printf("\nElements of array are:-\n");

	printf("Ind:\t");
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 0; i < vec.size(); i++) {
		printf("%d\t", vec[i]);
	}
	cout << endl;
}

void initMap(vector <int> vec, int k, map <int, int>& indMap, map <int, list <int> >& revIndMap, map <int, int>& freqMap) {
	for (int i = 0; i < k; i++) {
		indMap[i] = vec[i];
		freqMap[vec[i]]++;

		if (freqMap[vec[i]] > 1) {
			list <int> tmpList;
			tmpList.push_back(i);
			revIndMap[vec[i]] = tmpList;
		} else {
			revIndMap[vec[i]].push_back(i);
		}
	}
}

void showRes(vector <int> vec, int k, map <int, int> indMap, map <int, list <int> > revIndMap, map <int, int> freqMap) {
	pair <int, int> minPair;
	pair <int, int> maxPair;

	printf("\nMaximum and minimum elements of all %d-sized windows are:-\n", k);
	printf("Range\tMinInd\tMinEle\tMaxInd\tMaxEle\n");

	minPair = getMin(indMap, revIndMap, freqMap);
	maxPair = getMax(indMap, revIndMap, freqMap);
	printf("0..%d\t%d\t%d\t%d\t%d\n", (k - 1), minPair.first, minPair.second, maxPair.first, maxPair.second);

	for (int i = k; i < vec.size(); i++) {
		removeEle(indMap, revIndMap, freqMap);
		addEle(indMap, revIndMap, freqMap, i, vec[i]);

		minPair = getMin(indMap, revIndMap, freqMap);
		maxPair = getMax(indMap, revIndMap, freqMap);
		printf("%d..%d\t%d\t%d\t%d\t%d\n", (i - k + 1), i, minPair.first, minPair.second, maxPair.first, maxPair.second);
	}
}

pair <int, int> getMax(map <int, int> indMap, map <int, list <int> > revIndMap, map <int, int> freqMap) {
	map <int, int>::iterator i = freqMap.end();
	i--;

	int ele = i -> first;
	list <int>::iterator j = revIndMap[ele].begin();

	return make_pair(*j, ele);
}

pair <int, int> getMin(map <int, int> indMap, map <int, list <int> > revIndMap, map <int, int> freqMap) {
	map <int, int>::iterator i = freqMap.begin();

	int ele = i -> first;
	list <int>::iterator j = revIndMap[ele].begin();

	return make_pair(*j, ele);
}

void removeEle(map <int, int>& indMap, map <int, list <int> >& revIndMap, map <int, int>& freqMap) {
	map <int, int>::iterator i = indMap.begin();
	int ind = i -> first;
	int ele = i -> second;

	indMap.erase(ind);
	freqMap[ele]--;

	if (freqMap[ele] == 0) {
		freqMap.erase(ele);
		revIndMap.erase(ele);
	} else {
		revIndMap[ele].pop_front();
	}
}

void addEle(map <int, int>& indMap, map <int, list <int> >& revIndMap, map <int, int>& freqMap, int ind, int ele) {
	indMap[ind] = ele;
	freqMap[ele]++;

	if (freqMap[ele] == 1) {
		list <int> tmpList;
		tmpList.push_back(ind);
		revIndMap[ele] = tmpList;
	} else {
		revIndMap[ele].push_back(ind);
	}
}

