// https://www.geeksforgeeks.org/merging-intervals/
// https://practice.geeksforgeeks.org/problems/overlapping-intervals/0

// https://www.interviewbit.com/problems/merge-overlapping-intervals/
// https://leetcode.com/problems/merge-intervals/

/*
6 8     1 9     2 4     4 7     -1 -1
Output: (1, 9)

Input: 6 8     1 9     4 5     2 4     4 7     -1 -1
Output: (1, 9)

Input: 15 18   1 3     8 10    2 6    -1 -1
Output: 

GfgInput:
2
4
1 3 2 4 6 8 9 10
4
6 8 1 9 2 4 4 7
GfgOutput:
1 4 6 8 9 10
1 9
*/

#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <algorithm>

using namespace std;

void driver();
void gfgDriver();
vector <pair <int, int> > input();
vector <pair <int, int> > gfgInput();
void showVec(vector <pair <int, int> >, const char *);
map <pair <int, int>, list < pair <int, int> > > findOverlappingRanges(vector <pair <int, int> >);
void output(map <pair <int, int>, list < pair <int, int> > >);
void gfgOutput(map <pair <int, int>, list < pair <int, int> > >);

int main() {
  // driver();
  gfgDriver();

  return 0;
}

void driver() {
  vector <pair <int, int> > vec = input();
  showVec(vec, "before sorting, vec");

  sort(vec.begin(), vec.end());
  showVec(vec, "after  sorting, vec");

  map <pair <int, int>, list <pair <int, int> > > mergedRanges = findOverlappingRanges(vec);
  output(mergedRanges);
}

void gfgDriver() {
  int T;

  cin >> T;
  while (T-- > 0) {
    vector <pair <int, int> > vec = gfgInput();
    sort(vec.begin(), vec.end());
    map <pair <int, int>, list <pair <int, int> > > mergedRanges = findOverlappingRanges(vec);
    gfgOutput(mergedRanges);
  }
}

map <pair <int, int>, list <pair <int, int> > > findOverlappingRanges(vector <pair <int, int> > vec) {
  map <pair <int, int>, list <pair <int, int> > > mergedRanges;

  int crrBegin = vec[0].first;
  int crrEnd = vec[0].second;
  
  list <pair <int, int> > crrOverlappingRanges;
  crrOverlappingRanges.push_back(vec[0]);

  for (int i = 1; i < vec.size(); i++) {
    int thisBegin = vec[i].first;
    int thisEnd = vec[i].second;

    // printf("\n----------------\n");
    // printf("(crrBegin, crrEnd) = (%d, %d)\n", crrBegin, crrEnd);
    // printf("at vec[%d] = (%d, %d)\n", i, thisBegin, thisEnd);

    if (thisBegin <= crrEnd) {
      crrOverlappingRanges.push_back(vec[i]);
      crrEnd = max(crrEnd, thisEnd);

      // printf("\nvec[%d] = (%d, %d) included in   range, crrEnd set to %d\n", i, thisBegin, thisEnd, crrEnd);
    } else {
      // printf("\nexcluded from range, new merged range inialized\n");

      // push data of preceding range (now terminated) into map
      mergedRanges[make_pair(crrBegin, crrEnd)] = crrOverlappingRanges;

      // re-initialize variables
      crrBegin = thisBegin;
      crrEnd = thisEnd;

      crrOverlappingRanges.clear();
      crrOverlappingRanges.push_back(vec[i]);
    }
    // printf("\n----------------\n");
  }

  // push data of ongoing (dangling / uncommitted) range (now terminated) into map
  mergedRanges[make_pair(crrBegin, crrEnd)] = crrOverlappingRanges;

  return mergedRanges;
}

void output(map <pair <int, int>, list <pair <int, int> > > mergedRanges) {
  cout << endl << "overlapping ranges are:-" << endl;

  for (map <pair <int, int>, list <pair <int, int> > >::iterator mIt = mergedRanges.begin(); mIt != mergedRanges.end(); mIt++) {
    pair <int, int> crrMergedRange = (*mIt).first;
    printf("(%d, %d):\t", crrMergedRange.first, crrMergedRange.second);

    list <pair <int, int> > crrOverlappingRanges = (*mIt).second;
    for (list <pair <int, int> >::iterator rIt = crrOverlappingRanges.begin(); rIt != crrOverlappingRanges.end(); rIt++) {
      pair <int, int> crrRange = *rIt;
      printf("(%d, %d)\t", crrRange.first, crrRange.second);
    }
    cout << endl;
  }
}

void gfgOutput(map <pair <int, int>, list <pair <int, int> > > mergedRanges) {
  int i = 1;

  for (map <pair <int, int>, list <pair <int, int> > >::iterator mIt = mergedRanges.begin(); mIt != mergedRanges.end(); mIt++) {
    pair <int, int> crrMergedRange = (*mIt).first;
    if (i == 1) {
      printf("%d %d", crrMergedRange.first, crrMergedRange.second);
    } else {
      printf(" %d %d", crrMergedRange.first, crrMergedRange.second);
    }
    i++;
  }
  cout << endl;
}

vector <pair <int, int> > input() {
  vector <pair <int, int> > vec;
  int p1, p2;

  cout << "Enter pairs of elements:-" << endl << "{(-1, -1) to terminate}" << endl;
  cin >> p1 >> p2;
  while ((p1 != -1) || (p2 != -1)) {
    vec.push_back(make_pair(p1, p2));
    cin >> p1 >> p2;
  }

  return vec;
}

vector <pair <int, int> > gfgInput() {
  int len;
  vector <pair <int, int> > vec;

  cin >> len;
  for (int i = 1; i <= len; i++) {
    int p1, p2;
    cin >> p1 >> p2;

    vec.push_back(make_pair(p1, p2));
  }

  return vec;
}

void showVec(vector <pair <int, int> > vec, const char * name) {
  printf("\n%s vector is:-\n", name);

  cout << "Ind:\t";
  for (int i = 0; i < vec.size(); i++) {
    printf("[%d]\t", i);
  }
  cout << endl;

  cout << "Val:\t";
  for (int i = 0; i < vec.size(); i++) {
    printf("(%d, %d)\t", vec[i].first, vec[i].second);
  }
  cout << endl;
}

