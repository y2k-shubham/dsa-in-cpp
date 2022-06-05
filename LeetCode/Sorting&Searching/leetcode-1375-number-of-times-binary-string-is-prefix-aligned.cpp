// LeetCode-1375: https://leetcode.com/problems/number-of-times-binary-string-is-prefix-aligned/

// problem based on binary search on sorted set (lower_bound)
// quite unconventional -> very specific ordering of set operations applied

// runtime O(nlogn); yet LC submission just stood at 5 %tile on speed

#include <set>
#include <vector>

using namespace std;

class Solution {
private:

public:
    int numTimesAllBlue(vector<int>& flips) {
        int n = flips.size();

        set<int> unsetBitPosnsSet;
        vector<bool> bitsVec(n + 1, false);

        int prefixAlignedCount = 0;
        for (int i = 1; i <= flips.size(); i++) {
            if (!bitsVec[i]) {
                // insert ith posn as an unset bit initially
                unsetBitPosnsSet.insert(i);
            }

            int flipIdx = flips[i - 1];

            // flip the bit
            bitsVec[flipIdx] = !bitsVec[flipIdx];
            // update set according to flip
            if (bitsVec[flipIdx]) {
                unsetBitPosnsSet.erase(flipIdx);
            } else {
                unsetBitPosnsSet.insert(flipIdx);
            }

            // if there are no unset bits, it is prefix aligned
            if (unsetBitPosnsSet.empty()) {
                ++prefixAlignedCount;
                continue;
            }

            // take lower bound of current index 'i'
            auto it = unsetBitPosnsSet.lower_bound(i);

            if ((it != unsetBitPosnsSet.end()) && (*it == i)) {
                // if lower bound is 'i' (current index itself),
                // then it can't be prefix aligned
                continue;
            }

            if (it == unsetBitPosnsSet.begin()) {
                // if lower-bound is begin posn of set

                if (*it > i) {
                    // and it contains an index greater that 'i'
                    // then it is prefix aligned
                    ++prefixAlignedCount;
                    continue;
                } else {
                    // otherwise it can't be prefix aligned
                    continue;
                }
            } else {
                // if we are NOT at beginning of set, then
                // it can't be prefix-aligned (as there are some unset bits <= 'i')
                continue;
            }
        }

        return prefixAlignedCount;
    }
};
