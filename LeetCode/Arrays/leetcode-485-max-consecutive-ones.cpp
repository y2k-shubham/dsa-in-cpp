// LeetCode-485: https://leetcode.com/problems/max-consecutive-ones/

#include <vector>

using namespace std;

class Solution {
private:
    int swallowSeqOfCurrentDigits(vector<int>& vec, int startIdx) {
        int len = vec.size();
        int startDigit = vec[startIdx];

        int idx = startIdx;
        while ((idx < len) && (vec[idx] == startDigit)) {
            idx++;
        }

        return idx;
    }

    int findNext1sSeqStartIdx(vector<int>& vec, int startIdx) {
        int len = vec.size();
        if (startIdx >= len) {
            return len;
        }

        if (vec[startIdx] == 1) {
            return startIdx;
        }

        return swallowSeqOfCurrentDigits(vec, startIdx);
    }

public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int len = nums.size();
        if (len <= 0) {
            return len;
        }

        int longest1sSeqLen = 0;
        int idx = 0;
        while (idx < len) {
            idx = findNext1sSeqStartIdx(nums, idx);
            if (idx >= len) {
                break;
            }

            int idxNext = swallowSeqOfCurrentDigits(nums, idx);

            int crr1sSeqLen = idxNext - idx;
            longest1sSeqLen = max(longest1sSeqLen, crr1sSeqLen);

            idx = idxNext;
        }

        return longest1sSeqLen;
    }
};
