// LeetCode-456: https://leetcode.com/problems/132-pattern/
// NareshGupta: https://www.youtube.com/watch?v=8nx5dxFuvLo

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <set>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildMinElePrefix(vector<int>& vec) {
        int len = vec.size();

        vector<int> minElePrefix(len, INT_MAX);
        minElePrefix[0] = vec[0];
        for (int i = 1; i < len; i++) {
            minElePrefix[i] = min(minElePrefix[i - 1], vec[i]);
        }

        return minElePrefix;
    }

    // O(nlogn): gives wrong answer even though test cases are passing
    bool find132pattern1Wrong(vector<int>& nums) {
        int len = nums.size();
        if (len < 3) {
            return false;
        }

        vector<int> minElePrefix = buildMinElePrefix(nums);
        set<int> elesSuffix;
        elesSuffix.insert(nums[len - 1]);
        for (int i = len - 2; i > 0; i--) {
            int crrEle = nums[i];
            int minLeftEle = minElePrefix[i - 1];

            if (minLeftEle < crrEle) {
                set<int>::iterator lBound = elesSuffix.lower_bound(crrEle);
                while ((lBound != elesSuffix.begin()) && (*lBound >= crrEle)) {
                    lBound--;
                }

                int maxRightEleLessThanCrrEle = *lBound;
                // printf("minLeftEle = %d, at vec[i=%d] = %d, maxRightEle = %d\n", minLeftEle, i, crrEle, maxRightEleLessThanCrrEle);
                if ((maxRightEleLessThanCrrEle < crrEle) && (maxRightEleLessThanCrrEle > minLeftEle)) {
                    return true;
                }
            } else {
                // printf("minLeftEle = %d, at vec[i=%d] = %d, maxRightEle = NA\n", minLeftEle, i, crrEle);
            }

            elesSuffix.insert(crrEle);
        }

        return false;
    }

    // O(n)
    bool find132pattern2Right(vector<int>& vec) {
        int len = vec.size();
        if (len < 3) {
            return false;
        }

        vector<int> minElePrefix = buildMinElePrefix(vec);
        stack<int> stk;
        for (int i = len - 1; i > 0; i--) {
            int crrEle = vec[i];
            int leftMinEle = minElePrefix[i - 1];

            while (!stk.empty() && (stk.top() <= leftMinEle)) {
                stk.pop();
            }

            if (!stk.empty() && (stk.top() < crrEle)) {
                return true;
            }

            stk.push(crrEle);
        }

        return false;
    }

   public:
    friend class SolutionTest;

    bool find132pattern(vector<int>& vec) {
        return find132pattern2Right(vec);
    }
};

class SolutionTest {
   public:
    void testFind132Pattern1Wrong() {
        Solution soln = Solution();
        vector<int> vecIn;
        bool outExpected, outComputed;

        vecIn = {};
        outExpected = false;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3};
        outExpected = false;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {5, 9};
        outExpected = false;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 4};
        outExpected = false;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 3, 2};
        outExpected = true;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 5, 9, 3, 9, 1, 2};
        outExpected = true;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 9, 2};
        outExpected = true;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3, 1, 4, 2};
        outExpected = true;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);

        vecIn = {-1, 3, 2, 0};
        outExpected = true;
        outComputed = soln.find132pattern1Wrong(vecIn);
        assert(outExpected == outComputed);
    }

    void testFind132Pattern2Right() {
        Solution soln = Solution();
        vector<int> vecIn;
        bool outExpected, outComputed;

        vecIn = {};
        outExpected = false;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3};
        outExpected = false;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {5, 9};
        outExpected = false;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 4};
        outExpected = false;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 3, 2};
        outExpected = true;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 5, 9, 3, 9, 1, 2};
        outExpected = true;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 9, 2};
        outExpected = true;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3, 1, 4, 2};
        outExpected = true;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);

        vecIn = {-1, 3, 2, 0};
        outExpected = true;
        outComputed = soln.find132pattern2Right(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest;

    solnTest.testFind132Pattern1Wrong();
    solnTest.testFind132Pattern2Right();

    return 0;
}
