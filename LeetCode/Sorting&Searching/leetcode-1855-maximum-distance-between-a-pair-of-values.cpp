// LeetCode-1855: https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/
// not super easy to come up with bin-search approach

#include <cmath>
#include <vector>

using namespace std;

class Solution {
   private:
    int findLastReqIdx(vector<int>& vec, int n, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (midEle < n) {
            return findLastReqIdx(vec, n, lo, mid - 1);
        } else {
            return max(mid, findLastReqIdx(vec, n, mid + 1, hi));
        }
    }

   public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();

        int maxDist = 0;
        int prevReqIdx = 0;
        for (int i = 0; i < min(len1, len2); i++) {
            int ele1 = nums1[i];

            int lastReqIdx2 = findLastReqIdx(nums2, ele1, prevReqIdx, len2 - 1);
            if (lastReqIdx2 >= 0) {
                maxDist = max(maxDist, lastReqIdx2 - i);
                prevReqIdx = lastReqIdx2;
            }
        }

        return maxDist;
    }
};
