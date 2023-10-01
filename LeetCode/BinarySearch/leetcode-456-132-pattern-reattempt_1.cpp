// LeetCode-456: https://leetcode.com/problems/132-pattern

#include <iostream>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

class Solution {
private:
    vector<int> buildMinEleOnLeftVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {INT_MAX};
        }

        vector<int> leastEleOnLeftVec(len);
        leastEleOnLeftVec[0] = INT_MAX;
        int minEleOnLeft = INT_MAX;
        for (int i = 0; i < len; i++) {
            leastEleOnLeftVec[i] = minEleOnLeft;
            minEleOnLeft = min(minEleOnLeft, vec[i]);
        }

        return leastEleOnLeftVec;
    }

public:
    friend class SolutionTest;

    bool find132pattern(vector<int>& vec) {
        int len = vec.size();
        if (len < 3) {
            return false;
        }

        vector <int> minEleOnLeftVec = buildMinEleOnLeftVec(vec);
        set <int> mSet = {vec[len - 1]};
        for (int i = len - 1; i > 0; i--) {
            int crrEle = vec[i];

            // least element on (strictly) left of i
            int minEleOnLeft = minEleOnLeftVec[i];

            // smallest element on (strictly) right of i,
            // which is just bigger than 'minEleOnLeft' for ith index
            set <int>::iterator it = mSet.upper_bound(minEleOnLeft);
            if ((it != mSet.end()) && (*it < crrEle)) {
                // if we found such an element, then essentially we've found a 132 pattern
                return true;
            }

            mSet.insert(crrEle);
        }

        return false;
    }
};

class SolutionTest {
public:
    void testBuildMinEleOnLeftVec() {
        Solution soln = Solution();
        vector<int> vec;
        vector<int> minEleOnLeftVecOutExpected, minEleOnLeftVecOutComputed;

        vec = {};
        minEleOnLeftVecOutExpected = {};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);

        vec = {4};
        minEleOnLeftVecOutExpected = {INT_MAX};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);

        vec = {4, 2};
        minEleOnLeftVecOutExpected = {INT_MAX, 4};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);

        vec = {4, 2, 4, 1, 5};
        minEleOnLeftVecOutExpected = {INT_MAX, 4, 2, 2, 1};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);

        vec = {4, 2, 4, 1, 5, 0};
        minEleOnLeftVecOutExpected = {INT_MAX, 4, 2, 2, 1, 1};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);

        vec = {4, 2, 4, 1, 5, 0, 9};
        minEleOnLeftVecOutExpected = {INT_MAX, 4, 2, 2, 1, 1, 0};
        minEleOnLeftVecOutComputed = soln.buildMinEleOnLeftVec(vec);
        assert(minEleOnLeftVecOutExpected == minEleOnLeftVecOutComputed);
    }

    void testFind132Pattern() {
        Solution soln = Solution();
        vector<int> vec;
        bool outExpected, outComputed;

        vec = {};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {1};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {1, 3};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {1, 3, 2};
        outExpected = true;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {1, 2, 3};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {2, 3, 1};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {1,2,3,4};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {3,1,4,2};
        outExpected = true;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {3,1,2,4};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {-1,3,2,0};
        outExpected = true;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {-1,-3,2,0};
        outExpected = true;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);

        vec = {-1,-3,-2,0};
        outExpected = false;
        outComputed = soln.find132pattern(vec);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildMinEleOnLeftVec();
    solnTest.testFind132Pattern();

    return 0;
}
