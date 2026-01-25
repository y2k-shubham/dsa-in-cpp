// LeetCode-128: https://leetcode.com/problems/longest-consecutive-sequence/
// NeetCode: https://www.youtube.com/watch?v=P6RZZMu_maU

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    unordered_set<int> convertToSet(vector<int>& vec) {
        unordered_set<int> mSet(vec.begin(), vec.end());
        return mSet;
    }

    inline bool isBeginningOfConsecutiveSequence(unordered_set<int>& mSet, int num) {
        return isPresent(mSet, num) && !hasPreviousConsecutiveValue(mSet, num);
    }

    inline bool hasPreviousConsecutiveValue(unordered_set<int>& mSet, int num) {
        return isPresent(mSet, num) && isPresent(mSet, num - 1);
    }

    inline bool isPresent(unordered_set<int>& mSet, int num) {
        return mSet.find(num) != mSet.end();
    }

    int findLengthOfConsecutiveSequenceStartingAt(unordered_set<int>& mSet, int num) {
        int len = 0;

        while (isPresent(mSet, num)) {
            len++;
            num++;
        }

        return len;
    }

    void showSet(unordered_set<int>& mSet) {
        if (mSet.empty()) {
            printf("mSet = {} (empty)\n");
            return;
        }
        if (mSet.size() == 1) {
            printf("mSet = {%d}\n", *(mSet.begin()));
            return;
        }

        printf("mSet = {");
        int idx = 0;
        for (int elem : mSet) {
            if (idx == 0) {
                printf("%d", elem);
            } else {
                printf(", %d", elem);
            }

            idx++;
        }
        printf("}\n");
    }

public:
    friend class SolutionTest;

    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        unordered_set<int> mSet = convertToSet(nums);

        // {len, startingVal}
        pair<int, int> longestConsecutiveSequence = {0, nums[0]};

        for (int num : mSet) {
            if (!isBeginningOfConsecutiveSequence(mSet, num)) {
                continue;
            }

            pair<int, int> currentConsecutiveSequence = {findLengthOfConsecutiveSequenceStartingAt(mSet, num), num};
            if (currentConsecutiveSequence.first > longestConsecutiveSequence.first) {
                longestConsecutiveSequence = currentConsecutiveSequence;
            }
        }

        return longestConsecutiveSequence.first;
    }
};

class SolutionTest {
public:
    void testIsBeginningOfConsecutiveSequence() {
        unordered_set<int> mSet;
        int num;
        bool outExpected, outComputed;
        Solution soln = Solution();

        mSet = {};
        num = 9;
        outExpected = false;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);

        soln.enableDebug();
        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 8;
        outExpected = false;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);
        soln.disableDebug();

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 2;
        outExpected = false;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 1;
        outExpected = true;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 7;
        outExpected = true;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 6;
        outExpected = false;
        outComputed = soln.isBeginningOfConsecutiveSequence(mSet, num);
        assert(outExpected == outComputed);
    }

    void testHasPreviousConsecutiveValue() {
        unordered_set<int> mSet;
        int num;
        bool outExpected, outComputed;
        Solution soln = Solution();

        mSet = {};
        num = 9;
        outExpected = false;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);

        soln.enableDebug();
        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 8;
        outExpected = true;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);
        soln.disableDebug();

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 2;
        outExpected = true;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 1;
        outExpected = false;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 7;
        outExpected = false;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 6;
        outExpected = false;
        outComputed = soln.hasPreviousConsecutiveValue(mSet, num);
        assert(outExpected == outComputed);
    }

    void testFindLengthOfConsecutiveSequence() {
        unordered_set<int> mSet;
        int num;
        int outExpected, outComputed;
        Solution soln = Solution();

        mSet = {};
        num = 19;
        outExpected = 0;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 19;
        outExpected = 0;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 9;
        outExpected = 1;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 8;
        outExpected = 2;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 7;
        outExpected = 3;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 1;
        outExpected = 4;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);

        mSet = {8, 1, 3, 7, 4, 2, 9};
        num = 2;
        outExpected = 3;
        outComputed = soln.findLengthOfConsecutiveSequenceStartingAt(mSet, num);
        assert(outExpected == outComputed);
    }

    void testLongestConsecutive() {
        vector<int> mVec;
        int outExpected, outComputed;
        Solution soln = Solution();

        mVec = {};
        outExpected = 0;
        outComputed = soln.longestConsecutive(mVec);
        assert(outExpected == outComputed);

        mVec = {8, 1, 3, 7, 4, 2, 9};
        outExpected = 4;
        outComputed = soln.longestConsecutive(mVec);
        assert(outExpected == outComputed);

        mVec = {100, 4, 200, 1, 3, 2};
        outExpected = 4;
        outComputed = soln.longestConsecutive(mVec);
        assert(outExpected == outComputed);

        mVec = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        outExpected = 9;
        outComputed = soln.longestConsecutive(mVec);
        assert(outExpected == outComputed);

        mVec = {1, 0, 1, 2};
        outExpected = 3;
        outComputed = soln.longestConsecutive(mVec);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIsBeginningOfConsecutiveSequence();
    solnTest.testHasPreviousConsecutiveValue();
    solnTest.testFindLengthOfConsecutiveSequence();
    solnTest.testLongestConsecutive();

    return 0;
}
