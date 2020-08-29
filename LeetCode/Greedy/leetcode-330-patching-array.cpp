// LeetCode-330: https://leetcode.com/problems/patching-array/
// impossible to solve (totally unintuitive, i still don't understand)
// solution taken from here http://buttercola.blogspot.com/2016/06/leetcode-330-patching-array.html

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int minPatchesDebug(vector <int>&, int, bool);
int minPatches(vector <int>&, int);
void testMinPatches();

int main() {
  testMinPatches();

  return 0;
}

void testMinPatches() {
  vector <int> vec;

  vec = {1, 3};
  assert(minPatchesDebug(vec, 6, false) == 1);

  vec = {1, 5, 10};
  assert(minPatches(vec, 20) == 2);

  vec = {1, 2, 2};
  assert(minPatches(vec, 5) == 0);

  vec = {1, 2, 5, 6, 20};
  assert(minPatchesDebug(vec, 50, false) == 2);
}

int minPatchesDebug(vector<int>& nums, int n, bool debug) {
  set <int> elesAdded;

  // crrReach has to be made long or else it runs into integer overflow
  long crrReach = 0;
  int i = 0;
  int len = nums.size();
  while (crrReach < n) {
    int desiredNewReach = crrReach + 1;

    if (debug) {
      printf("\n---------\n");
      if (i < len) {
        printf("crrReach = %d, nums[i=%d] = %d\n", crrReach, i, nums[i]);
      } else {
        printf("crrReach = %d, i = %d\n", crrReach, i);
      }
    }

    if (i < len && nums[i] <= desiredNewReach) {
      crrReach = crrReach + nums[i];
      if (debug) {
        printf("since nums[i]=%d <= desiredNewReach=%d, so picked nums[i] and crrReach increased to %d\n", nums[i], desiredNewReach, crrReach);
      }
      i++;
    } else {
      elesAdded.insert(desiredNewReach);
      crrReach = crrReach + desiredNewReach;
      if (debug) {
        printf("since nums[i]=%d > desiredNewReach=%d, so added desiredNewReach in elesAdded set and crrReach increased to %d\n", nums[i], desiredNewReach, crrReach);
      }
    }
  }

  if (debug) {
    if (elesAdded.empty()) {
      printf("\nNo eles had to be added to achieve sum of n=%d\n", n);
    } else {
      printf("\nfollowing eles had to be added to achieve sum of n=%d\n", n);
      for (set <int>::iterator i = elesAdded.begin(); i != elesAdded.end(); i++) {
        printf("%d ", *i);
      }
      cout << endl;
    }
  }

  return elesAdded.size();
}

int minPatches(vector <int>& nums, int n) {
  return minPatchesDebug(nums, n, false);
}
