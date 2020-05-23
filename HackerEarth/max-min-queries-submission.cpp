// https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/little-monk-and-williamson/

/*
10
CountHigh
Push 442
CountHigh
Push 7555
Diff
Push 2799
Diff
Push 8543
Diff
Diff
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <string>

using namespace std;

int getMaxEle(map <int, int>);
int getMinEle(map <int, int>);
int decFreq(map <int, int>&, int);
void showFreqMap(map <int, int>);
void createQTypeMap(map <string, int>&);

int main() {
	map <int, int> freqMap;
	map <string, int> qTypeMap;
	string qTypeStr;
	int qTypeInt;
	int minEle, maxEle;
	int X, Q;

	cin >> Q;
	createQTypeMap(qTypeMap);

	for (int i = 1; i <= Q; i++) {
		cin >> qTypeStr;
		qTypeInt = qTypeMap[qTypeStr];

		switch (qTypeInt) {
		case 1:
			cin >> X;
			freqMap[X]++;
			break;

		case 2:
			if (freqMap.empty()) {
				printf("-1\n");
			} else if (freqMap.size() == 1) {
				printf("0\n");
				minEle = getMinEle(freqMap);
				decFreq(freqMap, minEle);
			} else {
				maxEle = getMaxEle(freqMap);
				minEle = getMinEle(freqMap);
				printf("%d\n", (maxEle - minEle));
				decFreq(freqMap, minEle);
				decFreq(freqMap, maxEle);
			}
			break;

		case 3:
			if (freqMap.empty()) {
				printf("-1\n");
			} else {
				maxEle = getMaxEle(freqMap);
				printf("%d\n", freqMap[maxEle]);
			}
			break;

		case 4:
			if (freqMap.empty()) {
				printf("-1\n");
			} else {
				minEle = getMinEle(freqMap);
				printf("%d\n", freqMap[minEle]);
			}
			break;
		}
	}

	return 0;
}

int getMaxEle(map <int, int> freqMap) {
	map <int, int>::iterator i = freqMap.end();
	i--;
	return (i -> first);
}

int getMinEle(map <int, int> freqMap) {
	map <int, int>::iterator i = freqMap.begin();
	return (i -> first);
}

int decFreq(map <int, int>& freqMap, int ele) {
	freqMap[ele]--;
	if (freqMap[ele] == 0) {
		freqMap.erase(ele);
	}
}

void showFreqMap(map <int, int> freqMap) {
	printf("\nFreqMap is:-\n");
	for (map <int, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++) {
		printf("freqMap[%d] = %d\n", (i -> first), (i -> second));
	}
}

void createQTypeMap(map <string, int>& qTypeMap) {
	qTypeMap["Push"] = 1;
	qTypeMap["Diff"] = 2;
	qTypeMap["CountHigh"] = 3;
	qTypeMap["CountLow"] = 4;
}

