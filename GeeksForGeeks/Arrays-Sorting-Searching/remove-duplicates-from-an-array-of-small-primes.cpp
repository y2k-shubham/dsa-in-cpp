// http://www.geeksforgeeks.org/remove-duplicates-from-an-array-of-small-primes/

/*
8
3 5 7 2 2 5 7 7

10
3 5 7 3 3 13 5 13 29 13
*/

#include <cstdio>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100

void input(vector <int> &);
vector <int> method_1(vector <int>);
vector <int> method_2(vector <int>);
void output(vector <int>);

int main() {
	vector <int> vec;

	input(vec);

	vector <int> v1 = method_1(vec);
	vector <int> v2 = method_2(vec);

	output(v1);
	output(v2);

	return 0;
}

void input(vector <int> &vec) {
	int n;

	cout << "Enter no of elements:\t";
	cin >> n;

	cout << "Enter elements:-\n";
	for (int i = 1; i <= n; i++) {
		int ele;
		cin >> ele;
		vec.push_back(ele);
	}
}

vector <int> method_1(vector <int> vec) {
	unordered_set <int> uset (vec.begin(), vec.end());
	vec.assign(uset.begin(), uset.end());
	return vec;
}

vector <int> method_2(vector <int> vec) {
	int prod = 1;

	for (vector <int>::iterator it = vec.begin(); it != vec.end(); ) {
		if (prod % (*it) == 0) {
			// duplicate
			it = vec.erase(it);
		} else {
			prod *= *it;
			it++;
		}
	}

	return vec;
}

void output(vector <int> vec) {
	cout << "\nAfter removing duplicates, vector is:-\n";
	for (vector <int>::iterator it = vec.begin(); it != vec.end(); it++) {
		printf("%d ", *it);
	}
	cout << endl;
}

