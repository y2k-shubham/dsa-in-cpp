// LeetCode 41. First Missing Positive
// https://leetcode.com/problems/first-missing-positive/
// https://www.geeksforgeeks.org/find-the-smallest-positive-number-missing-from-an-unsorted-array/
// explanation https://www.youtube.com/watch?v=9SnkdYXNIzM
// HARD problem

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

bool hasOne(vector <int>);
void testHasOne();
vector<int> removeOutOfRange(vector<int> nums);
void testRemoveOutOfRange();
vector<int> negateNums(vector<int>);
void testNegateNums();
int findFirstMissingPositive(vector<int>);
void testFindFirstMissingPositive();
int firstMissingPositive(vector<int>&);
void testFirstMissingPositive();

int main() {
    testHasOne();
    testRemoveOutOfRange();
    testNegateNums();
    testFindFirstMissingPositive();

    testFirstMissingPositive();

    return 0;
}

void testHasOne() {
  assert(hasOne({}) == false);
  assert(hasOne({0}) == false);
  assert(hasOne({1}) == true);
  assert(hasOne({0, 1}) == true);
  assert(hasOne({1, 0, 1}) == true);
}

bool hasOne(vector <int> nums) {
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] == 1) {
      return true;
    }
  }
  return false;
}

void testRemoveOutOfRange() {
    vector<int> nums;
    vector<int> outExpected;

    outExpected = {7, 1, 3, 1, 2, 1, 1};
    assert(removeOutOfRange({7, -2, 3, 1, 2, 20, -5}) == outExpected);

    outExpected = {1, 1, 1, 1, 2};
    assert(removeOutOfRange({-2, -1, 0, 1, 2}) == outExpected);

    outExpected = {1, 1, 1, 1, 1};
    assert(removeOutOfRange({7, 8, 9, 11, 12}) == outExpected);
}

vector<int> removeOutOfRange(vector<int> nums) {
    int len = nums.size();
    for (int i = 0; i < len; i++) {
        if (nums[i] <= 0 || nums[i] > len) {
            nums[i] = 1;
        }
    }
    return nums;
}

void testNegateNums() {
    vector<int> nums;
    vector<int> outExpected;

    outExpected = {-7, -1, -3, 1, 2, 1, -1};
    assert(negateNums({7, 1, 3, 1, 2, 1, 1}) == outExpected);

    outExpected = {-1, -1, 1, 1, 2};
    assert(negateNums({1, 1, 1, 1, 2}) == outExpected);

    outExpected = {-1, -2, -3};
    assert(negateNums({1, 2, 3}) == outExpected);

    outExpected = {-3, -2, -1};
    assert(negateNums({3, 2, 1}) == outExpected);

    outExpected = {-1, 1, 1, 1, 1};
    assert(negateNums({1, 1, 1, 1, 1}) == outExpected);
}

vector<int> negateNums(vector<int> nums) {
    for (int i = 0; i < nums.size(); i++) {
        int val = abs(nums[i]) - 1;
        nums[val] = -abs(nums[val]);
    }
    return nums;
}

void testFindFirstMissingPositive() {
    assert(findFirstMissingPositive({-7, -1, -3, 1, 2, 1, -1}) == 4);
    assert(findFirstMissingPositive({-1, -1, 1, 1, 2}) == 3);
    assert(findFirstMissingPositive({-1, -2, -3}) == 4);
    assert(findFirstMissingPositive({-3, -2, -1}) == 4);
    assert(findFirstMissingPositive({-1, 1, 1, 1, 1}) == 2);
}

int findFirstMissingPositive(vector<int> nums) {
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            return i + 1;
        }
    }
    return (((int)nums.size()) + 1);
}

void testFirstMissingPositive() {
    vector<int> nums;

    nums = {1, 2, 0};
    assert(firstMissingPositive(nums) == 3);

    nums = {3, 4, -1, 1};
    assert(firstMissingPositive(nums) == 2);

    nums = {2, 3, 7, 6, 8, -1, -10, 15};
    assert(firstMissingPositive(nums) == 1);

    nums = { 2, 3, -7, 6, 8, 1, -10, 15 };
    assert(firstMissingPositive(nums) == 4);

    nums = {1, 1, 0, -1, -2};
    assert(firstMissingPositive(nums) == 2);

    nums = {7, 8, 9, 11, 12};
    assert(firstMissingPositive(nums) == 1);

    nums = {7, -2, 3, 1, 2, 20, -5};
    assert(firstMissingPositive(nums) == 4);

    nums = {8, 1, 3, 7, 4, 2, 9};
    assert(firstMissingPositive(nums) == 5);
}

int firstMissingPositive(vector<int>& nums) {
  if (hasOne(nums)) {
    vector <int> cleanedNums = removeOutOfRange(nums);
    vector <int> negatedNums = negateNums(cleanedNums);
    return findFirstMissingPositive(negatedNums);
  } else {
    return 1;
  }
}
