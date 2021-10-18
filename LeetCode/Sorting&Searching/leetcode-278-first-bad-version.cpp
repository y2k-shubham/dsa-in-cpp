// LeetCode-278: https://leetcode.com/problems/first-bad-version/
// Elementary binary search; dont even bother looking

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);
bool isBadVersion(int n) {
    // magic method
}

class Solution {
   private:
    int firstBadVersionRec(int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return INT_MAX;
        }

        int diff = hi - lo;
        int mid = lo + (diff / 2);

        if (isBadVersion(mid)) {
            return min(firstBadVersionRec(lo, mid - 1), mid);
        } else {
            return firstBadVersionRec(mid + 1, hi);
        }
    }

   public:
    int firstBadVersion(int n) {
        return firstBadVersionRec(1, n);
    }
};
