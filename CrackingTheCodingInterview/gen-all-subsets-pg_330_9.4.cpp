#include <cstdio>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

set <int> makeUnion(set <int>, int);
void showSet(set <int>);

int main() {
	vector <int> nums;
	vector <set <int> > powerSet;
	int ele;

	printf("Enter set for finding subsets:-\n(-1 to terminate)\n");
	scanf("%d", &ele);
	while (ele >= 0) {
		nums.push_back(ele);
		scanf("%d", &ele);
	}

	set <int> emptySet;
	powerSet.push_back(emptySet);
	for (int i = 0; i < nums.size(); i++) {
		int powerSetCrrSize = powerSet.size();
		for (int j = 0; j < powerSetCrrSize; j++) {
			powerSet.push_back(makeUnion(powerSet[j], nums[i]));
		}
	}

	printf("\nThe powerSet is:-\n");
	printf("<empty>\n");
	for (int i = 1; i < powerSet.size(); i++) {
		showSet(powerSet[i]);
	}
	printf("\n");

	return 0;
}

set <int> makeUnion(set <int> set_, int ele) {
	set <int> newSet = set_;
	newSet.insert(ele);
	return newSet;
}

void showSet(set <int> set_) {
	set <int>::iterator it;

	it = set_.begin();
	cout << *it;
	for (it++; it != set_.end(); it++) {
		cout << ", " << *it;
	}
	cout << endl;
}

