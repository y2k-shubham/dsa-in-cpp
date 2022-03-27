// Weekly Contest 286: https://leetcode.com/contest/weekly-contest-286/problems/minimum-deletions-to-make-array-beautiful/

#include <vector>

using namespace std;

class Solution {
public:
    int minDeletion(vector<int> &nums) {
        int len = nums.size();
        if (len == 1) {
            return 1;
        }

        int numDeletions = 0;

        int prevEle = -1;
        for (int i = 0; i < len; i++) {
            int crrEle = nums[i];

            bool isCrrIdxActualEven = (i % 2) == 0;
            bool isCrrIdxConsideredEven = ((numDeletions % 2) == 0) ? isCrrIdxActualEven : !isCrrIdxActualEven;

            if (!isCrrIdxConsideredEven && (crrEle == prevEle)) {
                numDeletions++;
            }

            prevEle = crrEle;
        }

        bool isLenEven = (len % 2) == 0;
        bool areDeletionsEven = (numDeletions % 2) == 0;
        if ((((int) isLenEven) ^ ((int) areDeletionsEven)) == 1) {
            numDeletions++;
        }

        return numDeletions;
    }
};
