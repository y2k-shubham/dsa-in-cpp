// https://www.geeksforgeeks.org/union-find-algorithm-set-2-union-by-rank/
// Karumanchi Page 217

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
#define violatesBound(mSet, ele) (ele < 0 || mSet.size() <= ele)
#define sameSet(mSet, ele1, ele2) (findSet(mSet, ele1) == findSet(mSet, ele2))
#define separator "------------------------------------------"

void makeSet(vector <int>&);
int findSet(vector <int>, int);
void unionSets(vector <int>&, int, int);
void unionAndLog(vector <int>&, int, int);
void showSet(vector <int>);

int main() {
  vector <int> mSet(20);

  makeSet(mSet);
  showSet(mSet);

  unionAndLog(mSet, 5, 15);
  unionAndLog(mSet, 11, 2);
  unionAndLog(mSet, 15, 2);
  unionAndLog(mSet, 14, 6);
  unionAndLog(mSet, 6, 5);
  unionAndLog(mSet, 19, 2);
  unionAndLog(mSet, 5, 18);
}

void makeSet(vector <int>& mSet) {
  for (int i = 0; i < mSet.size(); i++) {
    mSet[i] = i;
  }
}

int findSet(vector <int> mSet, int ele) {
  if (violatesBound(mSet, ele)) {
    return -1;
  } else if (mSet[ele] == ele) {
    return ele;
  } else {
    mSet[ele] = findSet(mSet, mSet[ele]);
    return mSet[ele];
  }
}

void unionSets(vector <int>& mSet, int ele1, int ele2) {
  if (violatesBound(mSet, ele1) || violatesBound(mSet, ele2) || sameSet(mSet, ele1, ele2)) {
    return;
  } else {
    mSet[findSet(mSet, ele2)] = ele1;
  }
}

void unionAndLog(vector <int>& mSet, int ele1, int ele2) {
  cout << separator << endl;

  printf("Union(%d, %d)\n", ele1, ele2);
  unionSets(mSet, ele1, ele2);
  showSet(mSet);

  cout << separator << endl;
}

void showSet(vector <int> mSet) {
  cout << endl;

  for (int i = 0; i < mSet.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  for (int i = 0; i < mSet.size(); i++) {
    printf("%d\t", mSet[i]);
  }
  cout << endl;
}
