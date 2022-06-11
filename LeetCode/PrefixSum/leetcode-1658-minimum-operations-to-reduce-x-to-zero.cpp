// LeetCode-1658: https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
// a little trickier than what it seems at first sight

#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i] << "\t";
        }
        cout << endl;
    }

    vector<int> buildPrefSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefSum(len, 0);
        prefSum[0] = vec[0];

        for (int i = 1; i < len; i++) {
            prefSum[i] = prefSum[i - 1] + vec[i];
        }

        return prefSum;
    }

    vector<int> buildSuffSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> suffSum(len, 0);
        suffSum[len - 1] = vec[len - 1];

        for (int i = len - 2; i >= 0; i--) {
            suffSum[i] = suffSum[i + 1] + vec[i];
        }

        return suffSum;
    }

    int binSearch(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (ele < midEle) {
            return binSearch(vec, ele, lo, mid - 1);
        } else if (ele == midEle) {
            return mid;
        } else {
            return binSearch(vec, ele, mid + 1, hi);
        }
    }

    int binSearchDesc(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        if (len <= 0) {
            return -1;
        }

        int mid = (lo + hi) / 2;
        int midEle = vec[mid];

        if (ele > midEle) {
            return binSearchDesc(vec, ele, lo, mid - 1);
        } else if (ele == midEle) {
            return mid;
        } else {
            return binSearchDesc(vec, ele, mid + 1, hi);
        }
    }

    int findMinOpsViaSuffSumVec(int len, vector<int>& prefSumVec, vector<int>& suffSumVec, int x) {
        int minOps = INT_MAX;
        for (int i = len - 1; i > 0; i--) {
            int crrSuffSum = suffSumVec[i];
            int crrOps = len - i;

            int reqPrefSum = x - crrSuffSum;
            if (reqPrefSum > 0) {
                int idx = binSearch(prefSumVec, reqPrefSum, 0, i - 1);
                if (idx >= 0) {
                    crrOps += idx + 1;
                    if (debug) {
                        printf("at suffSumVec[i=%d]=%d, found prefSumVec[idx=%d]=%d, crrOps=%d\n", i, crrSuffSum, idx,
                               reqPrefSum, crrOps);
                    }
                    minOps = min(minOps, crrOps);
                }
            } else if (reqPrefSum == 0) {
                if (debug) {
                    printf("at suffSumVec[i=%d]=%d, it becomes 0, crrOps=%d\n", i, crrSuffSum, crrOps);
                }
                minOps = min(minOps, crrOps);
            } else {
                break;
            }
        }

        return minOps;
    }

    int findMinOpsViaPrefSumVec(int len, vector<int>& prefSumVec, vector<int>& suffSumVec, int x) {
        int minOps = INT_MAX;
        for (int i = 0; i < len - 1; i++) {
            int crrPrefSum = prefSumVec[i];
            int crrOps = i + 1;

            int reqSuffSum = x - crrPrefSum;
            if (reqSuffSum > 0) {
                int idx = binSearchDesc(suffSumVec, reqSuffSum, i + 1, len - 1);
                if (idx >= 0) {
                    crrOps += len - idx;
                    if (debug) {
                        printf("at prefSumVec[i=%d]=%d, found suffSumVec[idx=%d]=%d, crrOps=%d\n", i, crrPrefSum, idx,
                               reqSuffSum, crrOps);
                    }
                    minOps = min(minOps, crrOps);
                }
            } else if (reqSuffSum == 0) {
                if (debug) {
                    printf("at prefSumVec[i=%d]=%d, it becomes 0, crrOps=%d\n", i, crrPrefSum, crrOps);
                }
                minOps = min(minOps, crrOps);
            } else {
                break;
            }
        }

        return minOps;
    }

public:
    friend class SolutionTest;

    int minOperations(vector<int>& nums, int x) {
        int len = nums.size();
        if (len == 1) {
            return (nums[0] == x) ? 1 : -1;
        }

        vector<int> prefSumVec = buildPrefSum(nums);
        vector<int> suffSumVec = buildSuffSum(nums);
        if (debug) {
            showVec(nums, "nums");
            showVec(prefSumVec, "prefSumVec");
            showVec(suffSumVec, "suffSumVec");
        }

        int ops1 = findMinOpsViaSuffSumVec(len, prefSumVec, suffSumVec, x);
        int ops2 = findMinOpsViaPrefSumVec(len, prefSumVec, suffSumVec, x);
        int ops = min(ops1, ops2);

        return (ops == INT_MAX) ? -1 : ops;
    }
};

class SolutionTest {
public:
    void testMinOperations() {
        Solution soln = Solution();
        vector<int> vecIn;
        int xIn;
        int outExpected, outComputed;

        vecIn = {1, 1, 4, 2, 3};
        xIn = 5;
        outExpected = 2;
        outComputed = soln.minOperations(vecIn, xIn);
        assert(outComputed == outExpected);

        vecIn = {5, 6, 7, 8, 9};
        xIn = 4;
        outExpected = -1;
        outComputed = soln.minOperations(vecIn, xIn);
        assert(outComputed == outExpected);

        vecIn = {3, 2, 20, 1, 1, 3};
        xIn = 10;
        outExpected = 5;
        outComputed = soln.minOperations(vecIn, xIn);
        assert(outComputed == outExpected);

        vecIn = {5};
        xIn = 5;
        outExpected = 1;
        outComputed = soln.minOperations(vecIn, xIn);
        assert(outComputed == outExpected);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinOperations();

    return 0;
}
