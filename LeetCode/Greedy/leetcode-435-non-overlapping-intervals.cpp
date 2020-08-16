// LeetCode-435: https://leetcode.com/problems/non-overlapping-intervals/
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/551/week-3-august-15th-august-21st/3425/
// https://www.youtube.com/watch?v=2LUQ6tBdGxo
// relatively hard problem; Greedy Soln

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <cmath>

using namespace std;

void showPairSet(set <pair <int, int> > mSet);
void showPairVec(vector<pair<int, int>> vec);
void testConvertToPairs();
vector<pair<int, int>> convertToPairs(vector<vector<int>>);
vector<pair<int, int>> sortVec(vector<pair<int, int>>);
void testSortVec();
bool comparator(pair<int, int> const&, pair<int, int> const&);
int eraseOverlapIntervals(vector<vector<int>>& intervals);
void testEraseOverlapIntervals();


int main() {
    testConvertToPairs();
    testSortVec();
    testEraseOverlapIntervals();


    return 0;
}

void showPairVec(vector<pair<int, int>> vec) {
    int len = vec.size();
    printf("\nvec is:-\n");

    printf("Ind:\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < len; i++) {
        printf("(%d, %d)\t", vec[i].first, vec[i].second);
    }
    cout << endl;
}

void showPairSet(set <pair <int, int> > mSet) {
  printf("\nSet is:-\n");
  for (set <pair <int, int> >::iterator i = mSet.begin(); i != mSet.end(); i++) {
    printf("(%d, %d)\t", (*i).first, (*i).second);
  }
  cout << endl;
}

void testConvertToPairs() {
    vector<vector<int>> vecIn;
    vector<pair<int, int>> vecOutExpected;
    vector<pair<int, int>> vecOutComputed;

    vecIn = {};
    vecOutExpected = {};
    vecOutComputed = convertToPairs(vecIn);
    assert(vecOutExpected == vecOutComputed);

    vecIn = {{1, 2}};
    vecOutExpected = {make_pair(1, 2)};
    vecOutComputed = convertToPairs(vecIn);
    assert(vecOutExpected == vecOutComputed);

    vecIn = {{3, 4}, {5, 6}};
    vecOutExpected = {make_pair(3, 4), make_pair(5, 6)};
    vecOutComputed = convertToPairs(vecIn);
    // showPairVec(vecOutComputed);
    assert(vecOutExpected == vecOutComputed);

    vecIn = {{3, 4}, {5, 6}, {3, 4}, {1, 2}};
    vecOutExpected = {make_pair(3, 4), make_pair(5, 6), make_pair(3, 4), make_pair(1, 2)};
    vecOutComputed = convertToPairs(vecIn);
    assert(vecOutExpected == vecOutComputed);
}

vector<pair<int, int>> convertToPairs(vector<vector<int>> intervals) {
    int len = intervals.size();
    vector<pair<int, int>> ranges(len);

    for (int i = 0; i < len; i++) {
        ranges[i].first = intervals[i][0];
        ranges[i].second = intervals[i][1];
    }

    return ranges;
}

void testSortVec() {
    vector<pair<int, int>> inVec;
    vector<pair<int, int>> outVecExpected;
    vector<pair<int, int>> outVecComputed;

    inVec = {};
    outVecExpected = {};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(1, 2)};
    outVecExpected = {make_pair(1, 2)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(1, 2), make_pair(2, 2)};
    outVecExpected = {make_pair(1, 2), make_pair(2, 2)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(2, 2), make_pair(1, 2)};
    outVecExpected = {make_pair(1, 2), make_pair(2, 2)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(1, 2), make_pair(1, 3)};
    outVecExpected = {make_pair(1, 2), make_pair(1, 3)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(1, 3), make_pair(1, 2)};
    outVecExpected = {make_pair(1, 2), make_pair(1, 3)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);

    inVec = {make_pair(1, 3), make_pair(2, 2), make_pair(1, 2)};
    outVecExpected = {make_pair(1, 2), make_pair(2, 2), make_pair(1, 3)};
    outVecComputed = sortVec(inVec);
    assert(outVecExpected == outVecComputed);
}

bool comparator(pair<int, int> const& p1, pair<int, int> const& p2) {
  // return p1.second < p2.second;
    bool secondEqual = p1.second == p2.second;
    return secondEqual ? (p1.first < p2.first) : (p1.second < p2.second);
}

vector<pair<int, int>> sortVec(vector<pair<int, int>> vec) {
    sort(vec.begin(), vec.end(), &comparator);
    return vec;
}

void testEraseOverlapIntervals() {
  vector <vector <int> > vecIn;

  vecIn = {};
  assert(eraseOverlapIntervals(vecIn) == 0);

  vecIn = {{1, 3}};
  assert(eraseOverlapIntervals(vecIn) == 0);

  vecIn = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
  assert(eraseOverlapIntervals(vecIn) == 1);

  vecIn = {{1, 2}, {1, 2}, {1, 2}};
  assert(eraseOverlapIntervals(vecIn) == 2);

  vecIn = {{1, 2}, {2, 3}};
  assert(eraseOverlapIntervals(vecIn) == 0);

  vecIn = {{1, 1000}, {2, 3}, {4, 5}, {6, 7}};
  assert(eraseOverlapIntervals(vecIn) == 1);
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
  if (intervals.size() < 2) {
    return 0;
  } else {
    vector <pair <int, int> > ranges = convertToPairs(intervals);
    vector <pair <int, int> > sortedRanges = sortVec(ranges);

    vector <pair <int, int> > rangesToRemove;
    int crrEnd = sortedRanges[0].second;
    for (int i = 1; i < sortedRanges.size(); i++) {
      pair <int, int> crrRange = sortedRanges[i];
      if (crrRange.first < crrEnd) {
        rangesToRemove.push_back(crrRange);
      } else {
        crrEnd = crrRange.second;
      }
    }

    // showPairSet(rangesToRemove);


    return rangesToRemove.size();
  }
}
