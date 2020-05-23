// http://practice.geeksforgeeks.org/problems/array-pair-sum-divisibility-problem/0
// Directi

/*
4
9 3 7 5
6

4
66 48 91 74 
10

6
65 48 92 75 45 35
10
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

void input(vector <int>&, int&);
void showVec(vector <int>);
int findMaxMulti(vector <int>, int);
void findMax(vector <int>, int&, int&);
void createIndMap(vector <int>, map <int, queue <int> >&);
void showMap(map <int, queue <int> >);
bool canBePartitioned(vector <int> , int, int, map <int, queue <int> >);
int remEle(map <int, queue <int> >&, int);

int main() {
	int t;

	cin >> t;
	while (t-- > 0) {
		vector <int> vec;
		map <int, queue <int> > indMap;
		int k;
		
		input(vec, k);
		// showVec(vec);

		createIndMap(vec, indMap);
		// showMap(indMap);

		if (canBePartitioned(vec, k, findMaxMulti(vec, k), indMap)) {
			// printf("\ncanBePartitioned\n");
			cout << "True" << endl;
		} else {
			// printf("\ncan'tBePartitioned\n");
			cout << "False" << endl;
		}
	}

	return 0;
}

void input(vector <int>& vec, int& k) {
	int len;

	// printf("Enter length of vector:\t");
	cin >> len;
	vec.reserve(len);

	// printf("Enter elements of vector:-\n");
	for (int i = 0; i < len; i++) {
		int ele;
		cin >> ele;

		vec.push_back(ele);
	}

	// printf("Enter k:\t");
	cin >> k;
}

void showVec(vector <int> vec) {
	printf("\nVec is:-\n");

	cout << "Ind:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("[%d]\t", i);
	}
	cout << endl;

	cout << "Val:\t";
	for (int i = 0; i < vec.size(); i++) {
		printf("%d\t", vec[i]);
	}
	cout << endl;
}

int findMaxMulti(vector <int> vec, int k) {
	int m1Ele, m2Ele;
	int m1Ind, m2Ind;

	findMax(vec, m1Ele, m1Ind);
	vec[m1Ind] = -1;
	findMax(vec, m2Ele, m2Ind);

	int sum = m1Ele + m2Ele;
	int maxMulti = sum - (sum % k);

	return maxMulti;
}

void findMax(vector <int> vec, int& maxEle, int& maxInd) {
	maxEle = -1;
	maxInd = -1;

	for (int i = 0; i < vec.size(); i++) {
		if (vec[i] > maxEle) {
			maxEle = vec[i];
			maxInd = i;
		}
	}
}

void createIndMap(vector <int> vec, map <int, queue <int> >& indMap) {
	for (int i = 0; i < vec.size(); i++) {
		int ele = vec[i];

		if (indMap.find(ele) == indMap.end()) {
			queue <int> q;
			indMap[ele] = q;
		}

		indMap[ele].push(i);
	}
}

void showMap(map <int, queue <int> > indMap) {
	cout << "\nindMap is:-\n";
	for (map <int, queue <int> >::iterator i = indMap.begin(); i != indMap.end(); i++) {
		int ele = i -> first;
		queue <int> q = i -> second;

		printf("%d\t=>\t", ele);
		while (!q.empty()) {
			printf("[%d]\t", q.front());
			q.pop();
		}
		cout << endl;
	}
}

bool canBePartitioned(vector <int> vec, int k, int maxMulti, map <int, queue <int> > indMap) {
	bool canBePartitioned = true;

	for (int i = 0; i < vec.size(); i++) {
		int ele_1 = vec[i];

		if (ele_1 >= 0) {
			int sum;

			for (sum = maxMulti; sum > ele_1; sum -= k) {
				int ele_2 = sum - ele_1;

				if (indMap.find(ele_2) != indMap.end()) {
					if ((ele_1 == ele_2) && indMap[ele_1].size() == 1) {
						continue;
					}

					int ind_1 = remEle(indMap, ele_1); // always gives i
					int ind_2 = remEle(indMap, ele_2);

					vec[ind_1] = -1;
					vec[ind_2] = -1;

					break;
				}
			}

			if (sum <= ele_1) {
				canBePartitioned = false;
				break;
			}

			if (indMap.empty()) {
				break;
			}
		}
	}

	return (canBePartitioned && indMap.empty());
}

int remEle(map <int, queue <int> >& indMap, int ele) {
	int ind = indMap[ele].front();
	indMap[ele].pop();
	
	if (indMap[ele].empty()) {
		indMap.erase(ele);
	}

	return ind;
}


