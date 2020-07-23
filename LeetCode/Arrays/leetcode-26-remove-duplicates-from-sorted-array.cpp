// LeetCode 26: https://leetcode.com/problems/remove-duplicates-from-sorted-array/
// https://www.geeksforgeeks.org/remove-duplicates-sorted-array/
// https://www.interviewbit.com/problems/remove-duplicates-from-sorted-array/

#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void testRemoveDuplicates();
bool removeDuplicatesTester(vector <int>, vector <int>);
int removeDuplicates(vector <int>&);
void showVec(vector<int>, int, const char*);

int main() {
  testRemoveDuplicates();

  return 0;
}

void testRemoveDuplicates() {
  vector <int> in;
  int newSize;
  vector <int> outExpected;

  in = {};
  outExpected = {};
  newSize = removeDuplicates(in);
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));

  in = {1};
  outExpected = {1};
  newSize = removeDuplicates(in);
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));

  in = {1, 2};
  outExpected = {1, 2};
  newSize = removeDuplicates(in);
  // showVec(in, newSize, "");
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));

  in = {1, 1, 2};
  outExpected = {1, 2};
  newSize = removeDuplicates(in);
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));

  in = {1, 2, 2, 3, 4, 4, 4, 5};
  outExpected = {1, 2, 3, 4, 5};
  newSize = removeDuplicates(in);
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));

  in = {9, 9, 9};
  outExpected = {9};
  newSize = removeDuplicates(in);
  assert(newSize == outExpected.size());
  assert(removeDuplicatesTester(in, outExpected));
}

bool removeDuplicatesTester(vector <int> unDeduped, vector <int> deduped) {
  for (int i = 0; i < deduped.size(); i++) {
    if (i >= unDeduped.size() || unDeduped[i] != deduped[i]) {
      return false;
    }
  }
  return true;
}

int removeDuplicates(vector <int>& nums) {
  if (nums.empty()) {
    return 0;
  } else if (nums.size() == 1) {
    return 1;
  } else {
    int i, j;

    for (i = 1, j = 1; i < nums.size(); i++) {
      if (nums[i] != nums[i - 1]) {
        nums[j] = nums[i];
        j++;
      }
    }

    return j;
  }
}

void showVec(vector<int> vec, int lim, const char* name) {
    printf("\nVector %s is:-\n", name);

    printf("Ind:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("Val:\t");
    for (int i = 0; i < vec.size(); i++) {
        printf("%d\t", vec[i]);
    }
    cout << endl;

    printf("\t");
    for (int i = 0; i < lim - 1; i++) {
        printf("\t");
    }
    printf("^^ lim=%d", lim);
    cout << endl;
}
