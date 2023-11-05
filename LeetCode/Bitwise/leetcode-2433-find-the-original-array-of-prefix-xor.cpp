// LeetCode-2433: https://leetcode.com/problems/find-the-original-array-of-prefix-xor/

#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> findArray(vector<int>& xoredPrefArr) {
        int len = xoredPrefArr.size();
        if (len <= 1) {
            return xoredPrefArr;
        }

        vector<int> originalArr(len);
        originalArr[0] = xoredPrefArr[0];

        int runningXor = xoredPrefArr[0];
        for (int i = 1; i < len; i++) {
            int ithEle = runningXor ^ xoredPrefArr[i];
            originalArr[i] = ithEle;

            runningXor ^= ithEle;
        }

        return originalArr;
    }
};

class SolutionTest {
public:
    void testFindArray() {
        Solution soln = Solution();
        vector<int> xoredPrefArrIn;
        vector<int> originalArrOutExpected, originalArrOutComputed;

        xoredPrefArrIn = {};
        originalArrOutExpected = {};
        originalArrOutComputed = soln.findArray(xoredPrefArrIn);
        assert(originalArrOutExpected == originalArrOutComputed);

        xoredPrefArrIn = {13};
        originalArrOutExpected = {13};
        originalArrOutComputed = soln.findArray(xoredPrefArrIn);
        assert(originalArrOutExpected == originalArrOutComputed);

        xoredPrefArrIn = {5, 2, 0, 3, 1};
        originalArrOutExpected = {5, 7, 2, 3, 2};
        originalArrOutComputed = soln.findArray(xoredPrefArrIn);
        assert(originalArrOutExpected == originalArrOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindArray();

    return 0;
}
