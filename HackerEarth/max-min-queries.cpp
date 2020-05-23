// https://www.hackerearth.com/practice/data-structures/trees/heapspriority-queues/practice-problems/algorithm/little-monk-and-williamson/

#include <cstdio>
#include <iostream>
#include <map>
#include <utility>

using namespace std;

int getMaxEle(map <int, int>);
int getMinEle(map <int, int>);
int decFreq(map <int, int>&, int);
void showFreqMap(map <int, int>);

int main() {
	map <int, int> freqMap;
	int choice;
	int ele;
	int minEle, maxEle;

	choice = -1;
	while (choice != 6) {
		printf("\nPick an action:-\n");
		printf("1. Insert an element\n");
		printf("2. Tell difference between maximum and minimum element\n");
		printf("3. Tell frequency of maximum element\n");
		printf("4. Tell frequency of minimum element\n");
		printf("5. Show map\n");
		printf("6. Exit\n");

		printf("\nEnter your choice:\t");
		cin >> choice;

		switch (choice) {
		case 1:
			printf("Enter element to be inserted:\t");
			cin >> ele;
			freqMap[ele]++;
			break;

		case 2:
			if (freqMap.empty()) {
				printf("Map empty\n");
			} else {
				maxEle = getMaxEle(freqMap);
				minEle = getMinEle(freqMap);

				if (maxEle == minEle) {
					decFreq(freqMap, maxEle);
				} else {
					decFreq(freqMap, minEle);
					decFreq(freqMap, maxEle);
				}

				printf("maxEle (%d) - minEle (%d) = %d\n", maxEle, minEle, (maxEle - minEle));
			}
			break;

		case 3:
			if (freqMap.empty()) {
				printf("Map empty\n");
			} else {
				maxEle = getMaxEle(freqMap);
				printf("Freq of maxEle (%d) = %d\n", maxEle, freqMap[maxEle]);
			}
			break;

		case 4:
			if (freqMap.empty()) {
				printf("Map empty\n");
			} else {
				minEle = getMinEle(freqMap);
				printf("Freq of minEle (%d) = %d\n", minEle, freqMap[minEle]);
			}
			break;

		case 5:
			showFreqMap(freqMap);
			break;

		case 6:
			continue;

		default:
			printf("Invalid choice\n");
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

