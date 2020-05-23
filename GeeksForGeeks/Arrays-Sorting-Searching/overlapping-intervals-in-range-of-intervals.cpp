// https://www.geeksforgeeks.org/check-if-any-two-intervals-overlap-among-a-given-set-of-intervals/
/*
Given a set of ranges, output ranges incorporating
the entire interval such that
- Each number in the entire interval is included in only one range
- Against each range, output the intervals in which it occurs
*/

/*
5
2 9
11 14
6 7
9 19
8 17
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

void input(vector <pair <int, int> >&);
void showVec(vector <pair <int, int> >, const char *);

int main() {
  vector <pair <int, int> > inpRanges;

  input(inpRanges);
  sort(inpRanges.begin(), inpRanges.end());
  showVec(inpRanges, "inpRanges");

  return 0;
}

// input-output
void input(vector <pair <int, int> >& inpRanges) {
  int len;

  cout << "Enter number of ranges:\t";
  cin >> len;

  cout << "Enter ranges:-" << endl;
  for (int i = 1; i <= len; i++) {
    int rLo, rHi;
    cin >> rLo >> rHi;

    inpRanges.push_back(make_pair(rLo, rHi));
  }
}

void showVec(vector <pair <int, int> > vec, const char * name) {
  printf("\n%s vector is:-\n", name);
  for (int i = 0; i < vec.size(); i++) {
    printf("[%d]\t(%d,\t%d)\n", i, vec[i].first, vec[i].second);
  }
  cout << endl;
}

// method - 1
// k = upperbound of union of all inpRanges
// Space: O(k)
// Time: O(k)
vector <set <int> > createOverlapRangeSetVec(vector <pair <int, int> > inpRanges) {
  int minValue = findMinValue(inpRanges);
  int maxValue = findMaxValue(inpRanges);
  vector <set <int> > overlapRangeSetVec(maxValue - minValue + 1 + 2);

  // initialize with empty set
  for (int i = 0; i < overlapRangeSetVec.size(); i++) {
    set <int> emptySet;
    overlapRangeSetVec[i] = emptySet;
  }

  // 

  return overlapRangeSetVec;
}

// utility methods
int findMinValue(vector <pair <int, int> > vec) {
  return vec.front().first;
}

int findMaxValue(vector <pair <int, int> > vec) {
  int maxVal = INT_MIN;
  for (int i = 0; i < vec.size(); i++) {
    maxVal = max(maxVal, vec[i].second);
  }

  return maxVal;
}
