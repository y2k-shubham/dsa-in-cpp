// https://www.codechef.com/MAY17/problems/CHEFSUBA

/*
5 3 4
1 0 0 1 1
?!!?

10 5 9
1 1 0 0 0 1 0 1 1 1
?!?!?!?!?

10 11 5
1 1 0 0 0 1 0 1 1 1
?!?!?!?!?
*/

#include <cstdio>
#include <iostream>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <utility>

using namespace std;
#define MAX 100005

void input(int&, int&, int&, vector <int>&, string&);
void init(int, int, vector <int>, set <pair <int, int> >&, map <int, int>&);
void showVec(vector <int>, int);
void showSet(set <pair <int, int> >, const char *);
void showMap(map <int, int>, const char *);
void doQuery(vector <int>, int, int, int, set <pair <int, int> >, map <int, int>, string);

int main() {
	vector <int> vec(MAX);
	int N, K, P;
	string qStr;
	set <pair <int, int> > winSet;
	map <int, int> winMap;

	input(N, K, P, vec, qStr);
//	showVec(vec, N);
//	cout << "qStr is " << qStr << endl;

	if (K < N) {
		init(N, K, vec, winSet, winMap);
//	showSet(winSet, "after initialization");
//	showMap(winMap, "after initialization");

		doQuery(vec, N, K, P, winSet, winMap, qStr);
	} else {
		// count ones
		int oneCount = 0;
		for (int i = 0; i < N; i++) {
			if (vec[i] == 1) {
				oneCount++;
			}
		}

		for (int i = 0; i < P; i++) {
			if (qStr[i] == '?') {
				printf("%d\n", oneCount);
			}
		}
	}

	return 0;
}

void input(int& N, int& K, int& P, vector <int>& vec, string& qStr) {
	cin >> N >> K >> P;
	for (int i = 0; i < N; i++) {
		scanf("%d", &vec[i]);
	}
	cin >> qStr;
}

void init(int N, int K, vector <int> vec, set <pair <int, int> >& winSet, map <int, int>& winMap) {
	int i = 0;
	int ctr = 0;

	// add entry for first window
	while ((i < N) && (i < K)) {
		ctr += (vec[i] == 1) ? 1 : 0;
		i++;
	}
	winSet.insert(make_pair(-ctr, 0));
	winMap[0] = -ctr;

	// add entries for subsequent windows
	while (i < N) {
		ctr += (vec[i] == 1) ? 1 : 0;
		ctr -= (vec[i - K] == 1) ? 1 : 0;

		winSet.insert(make_pair(-ctr, i - K + 1));
		winMap[i - K + 1] = -ctr;

		i++;
	}
}

void showVec(vector <int> vec, int N) {
	printf("\nvec is:-\n");

	printf("Ind:\t");
	for (int i = 0; i < N; i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	printf("Val:\t");
	for (int i = 0; i < N; i++) {
		printf("%d\t", vec[i]);
	}
	cout << endl;
}

void showSet(set <pair <int, int> > winSet, const char * when) {
	printf("\n%s, winSet is:-\n", when);
	for (set <pair <int, int> >::iterator i = winSet.begin(); i != winSet.end(); i++) {
		printf("(%d, %d)\n", -(i -> first), i -> second);
	}
}

void showMap(map <int, int> winMap, const char * when) {
	printf("\n%s, winMap is:-\n", when);
	for (map <int, int>::iterator i = winMap.begin(); i != winMap.end(); i++) {
		printf("winMap[%d] = %d\n", (i -> first), -(i -> second));
	}
}

void doQuery(vector <int> vec, int N, int K, int P, set <pair <int, int> > winSet, map <int, int> winMap, string qStr) {
	// initialize indexes
	int addWinInd = -1;
	int remWinInd = N - K;
	int addEleInd = N - 1;
	int remEleInd = K - 1;
	int addWinCtr;

//	int shiftCount = 0;
//	printf("\n=============\nafter shift %d\n", shiftCount++);
//	showVec(vec, N);
//	printf("\naddWinInd = %d\tremWinInd = %d\n", addWinInd, remWinInd);
//	printf("addEle = vec[%d] = %d\tremEle = vec[%d] = %d\n", addEleInd, vec[addEleInd], remEleInd, vec[remEleInd]);
//	showSet(winSet, "");
//	showMap(winMap, "");
//	printf("=============\n");

	// iterate over query string
	//	printf("\nResults of queries are:-\n");
	for (int i = 0; i < P; i++) {
		if (qStr[i] == '?') {
			// display current maximum
			pair <int, int> p = *(winSet.begin());
			printf("%d\n", -p.first);
		} else {
			// remove entry of last window
			winSet.erase(make_pair(winMap[remWinInd], remWinInd));
			winMap.erase(remWinInd);

			// calculate entry of new window
			addWinCtr = -winMap[addWinInd + 1];
			addWinCtr += (vec[addEleInd] == 1) ? 1 : 0;
			addWinCtr -= (vec[remEleInd] == 1) ? 1 : 0;

			// add entry of new window
			winSet.insert(make_pair(-addWinCtr, addWinInd));
			winMap[addWinInd] = -addWinCtr;

			// update indexes
			addWinInd--;
			remWinInd--;
			addEleInd = (addEleInd - 1 + N) % N;
			remEleInd = (remEleInd - 1 + N) % N;

//			printf("\n=============\nafter shift %d\n", shiftCount++);
//			showVec(vec, N);
//			printf("\naddWinInd = %d\tremWinInd = %d\n", addWinInd, remWinInd);
//			printf("addEle = vec[%d] = %d\tremEle = vec[%d] = %d\n", addEleInd, vec[addEleInd], remEleInd, vec[remEleInd]);
//			showSet(winSet, "");
//			showMap(winMap, "");
//			printf("=============\n");
		}
	}
}

