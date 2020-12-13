// LeetCode-938: https://leetcode.com/problems/minimum-cost-for-tickets/

#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

int incTrailIdxToDiff(vector <int>& vec, int advIdx, int trailIdx, int maxDiff) {
  int len = vec.size();

  if ((len == 0) || (advIdx >= len)) {
    return -1;
  }

  if (advIdx < 0 || trailIdx < 0) {
    return -1;
  }

  if (trailIdx > advIdx) {
    return -1;
  }

  while ((vec[advIdx] - vec[trailIdx]) >= maxDiff) {
    trailIdx++;
  }

  return trailIdx;
}

void testIncTrailIdxToDiff() {
  vector <int> vec;
  int advIdx;
  int trailIdx;
  int maxDiff;
  int idxOutExpected;
  int idxOutComputed;

  vec = {};
  advIdx = -1;
  trailIdx = -1;
  maxDiff = -1;
  idxOutExpected = -1;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {};
  advIdx = 3;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = 0;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 1;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 2;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 0;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 3;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 0;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 4;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 1;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 5;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 2;
  maxDiff = 7;
  idxOutExpected = 5;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 4;
  maxDiff = 7;
  idxOutExpected = 5;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 5;
  maxDiff = 7;
  idxOutExpected = 5;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 1;
  maxDiff = 7;
  idxOutExpected = 2;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 2;
  maxDiff = 7;
  idxOutExpected = 2;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 3;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 8;
  maxDiff = 7;
  idxOutExpected = 10;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 9;
  maxDiff = 7;
  idxOutExpected = 10;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 10;
  maxDiff = 7;
  idxOutExpected = 10;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 11;
  trailIdx = 10;
  maxDiff = 7;
  idxOutExpected = 10;
  idxOutComputed = incTrailIdxToDiff(vec, advIdx, trailIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);
}

int decAdvIdxToDiff(vector <int>& vec, int trailIdx, int advIdx, int maxDiff) {
  int len = vec.size();

  if ((len == 0) || (advIdx >= len)) {
    return -1;
  }

  if (advIdx < 0 || trailIdx < 0) {
    return -1;
  }

  if (trailIdx > advIdx) {
    return -1;
  }

  while ((vec[advIdx] - vec[trailIdx]) >= maxDiff) {
    advIdx--;
  }

  return advIdx;
}

void testDecAdvIdxToDiff() {
  vector <int> vec;
  int advIdx;
  int trailIdx;
  int maxDiff;
  int idxOutExpected;
  int idxOutComputed;

  vec = {};
  advIdx = -1;
  trailIdx = -1;
  maxDiff = -1;
  idxOutExpected = -1;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {};
  advIdx = 3;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = 0;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 1;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 2;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 2;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 3;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 4;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 2;
  maxDiff = 7;
  idxOutExpected = 4;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 4;
  maxDiff = 7;
  idxOutExpected = 4;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 4;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 1;
  maxDiff = 7;
  idxOutExpected = 7;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 6;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 8;
  trailIdx = 3;
  maxDiff = 7;
  idxOutExpected = 8;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 8;
  maxDiff = 7;
  idxOutExpected = 9;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 1;
  maxDiff = 7;
  idxOutExpected = 7;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 10;
  trailIdx = 10;
  maxDiff = 7;
  idxOutExpected = 10;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,2,3,4,5,6,7,8,9,10,30,31};
  advIdx = 11;
  trailIdx = 10;
  maxDiff = 7;
  idxOutExpected = 11;
  idxOutComputed = decAdvIdxToDiff(vec, trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);
}

int incAdvIdxToDiff(vector <int>& vec, int trailIdx, int advIdx, int maxDiff) {
  int len = vec.size();

  if ((len == 0) || (advIdx >= len)) {
    return -1;
  }

  if (advIdx < 0 || trailIdx < 0) {
    return -1;
  }

  if (trailIdx > advIdx) {
    return -1;
  }

  while ((advIdx < len) && ((vec[advIdx] - vec[trailIdx]) <= (maxDiff - 1))) {
    advIdx++;
  }

  if ((advIdx == len) || ((vec[advIdx] - vec[trailIdx]) >= maxDiff)) {
    advIdx--;
  }

  return advIdx;
}

void testIncAdvIdxToDiff() {
  vector <int> vec;
  int advIdx;
  int trailIdx;
  int maxDiff;
  int idxOutExpected;
  int idxOutComputed;

  vec = {};
  advIdx = -1;
  trailIdx = -1;
  maxDiff = -1;
  idxOutExpected = -1;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {};
  advIdx = 3;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = 0;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 0;
  trailIdx = 1;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {2};
  advIdx = 1;
  trailIdx = 0;
  maxDiff = 3;
  idxOutExpected = -1;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 0;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 1;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 2;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 3;
  trailIdx = 0;
  maxDiff = 7;
  idxOutExpected = 3;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 3;
  trailIdx = 3;
  maxDiff = 7;
  idxOutExpected = 4;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 4;
  trailIdx = 3;
  maxDiff = 7;
  idxOutExpected = 4;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 4;
  trailIdx = 4;
  maxDiff = 7;
  idxOutExpected = 4;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);

  vec = {1,4,6,7,8,20};
  advIdx = 5;
  trailIdx = 5;
  maxDiff = 7;
  idxOutExpected = 5;
  idxOutComputed = incAdvIdxToDiff(vec,trailIdx, advIdx, maxDiff);
  assert(idxOutExpected == idxOutComputed);
}



int main() {
  testIncTrailIdxToDiff();
  testDecAdvIdxToDiff();
  testIncAdvIdxToDiff();

  return 0;
}


