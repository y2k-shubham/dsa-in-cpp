// https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

int findFloor(vector <int>& vec, int target, int lo, int hi);
int findCeil(vector <int>& vec, int target, int lo, int hi);
vector<int> searchRange(vector<int>& nums, int target);

int main() {
  vector <int> nums;
  vector <int> res;

  // g++ -std=c++11 LeetCode/Arrays-Sorting-Searching/find-first-and-last-position-of-element-in-sorted-array.cpp
  nums = {5,7,7,8,8,10};
  res = {3, 4};
  assert(searchRange(nums, 8) == res);

  nums = {5,7,7,8,8,10};
  res = {-1, -1};
  assert(searchRange(nums, 6) == res);

  nums = {0,0,1,1,1,2,2,3,3,3,4,4,4,4,5,5,6,6,6,8,10,10};
  res = {10, 13};
  assert(searchRange(nums, 4) == res);

  return 0;
}

int findFloor(vector <int>& vec, int target, int lo, int hi) {
  int size = hi - lo + 1;

  if (size <= 0) {
    return -1;
  } else if (size == 1) {
    if (vec[lo] == target) {
      return lo;
    } else {
      return -1;
    }
  } else if (size == 2) {
    if (vec[lo] == target) {
      return lo;
    } else if (vec[hi] == target) {
      return hi;
    } else {
      return -1;
    }
  } else {
    int mid = (lo + hi) / 2;

    if (vec[mid] < target) {
      return findFloor(vec, target, mid + 1, hi);
    } else if (vec[mid] > target) {
      return findFloor(vec, target, lo, mid - 1);
    } else {
      if (vec[mid - 1] == target) {
        return findFloor(vec, target, lo, mid - 1);
      } else {
        return mid;
      }
    }
  }
}

int findCeil(vector <int>& vec, int target, int lo, int hi) {
  int size = hi - lo + 1;

  if (size <= 0) {
    return -1;
  } else if (size == 1) {
    if (vec[lo] == target) {
      return lo;
    } else {
      return -1;
    }
  } else if (size == 2) {
    if (vec[hi] == target) {
      return hi;
    } else if (vec[lo] == target) {
      return lo;
    } else {
      return -1;
    }
  } else {
    int mid = (lo + hi) / 2;

    if (vec[mid] < target) {
      return findCeil(vec, target, mid + 1, hi);
    } else if (vec[mid] > target) {
      return findCeil(vec, target, lo, mid - 1);
    } else {
      if (vec[mid + 1] == target) {
        return findCeil(vec, target, mid + 1, hi);
      } else {
        return mid;
      }
    }
  }
}

vector<int> searchRange(vector<int>& nums, int target) {
  int floorInd = findFloor(nums, target, 0, nums.size() - 1);
  int ceilInd = findCeil(nums, target, 0, nums.size() - 1);
  
  vector <int> vec;
  vec.push_back(floorInd);
  vec.push_back(ceilInd);

  return vec;
}
