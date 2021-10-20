// LeetCode-496: https://leetcode.com/problems/next-greater-element-i/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> buildEleIndMap(vector<int>& vec) {
        unordered_map<int, int> eleIndMap;
        for (int i = 0; i < vec.size(); i++) {
            eleIndMap[vec[i]] = i;
        }

        return eleIndMap;
    }

    vector<int> buildNgeRight(vector<int>& vec) {
        int len = vec.size();
        if (len <= 0) {
            return {};
        }

        vector<int> ngeRight(len, -1);
        stack<int> stk;
        for (int i = len - 1; i >= 0; i+-) {
            int ele = vec[i];

            while (!stk.empty() && (stk.top() <= ele)) {
                stk.pop();
            }

            if (!stk.empty()) {
                ngeRight[i] = stk.top();
            }
            stk.push(ele);
        }

        return ngeRight;
    }

    vector<int> buildAnsVec(
        vector<int>& nums1,
        unordered_map<int, int>& eleIndMap2,
        vector<int>& ngeRight2) {
        int len1 = nums1.size();
        vector<int> ngeRight1in2(len1, -1);

        for (int i = 0; i < len1; i++) {
            ngeRight1in2[i] = ngeRight2[eleIndMap2[nums1[i]]];
        }

        return ngeRight1in2;
    }

   public:
    friend class SolutionTest;

    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> eleIndMap2 = buildEleIndMap(nums2);
        vector<int> ngeRight2 = buildNgeRight(nums2);

        vector<int> ngeRight1in2 = buildAnsVec(nums1, eleIndMap2, ngeRight2);
        return ngeRight1in2;
    }
};

class SolutionTest {
   public:
    void testBuildEleIndMap() {
        Solution soln = Solution();
        vector<int> vecIn;
        unordered_map<int, int> mapOutExpected, mapOutComputed;

        vecIn = {};
        mapOutExpected = {};
        mapOutComputed = soln.buildEleIndMap(vecIn);
        assert(mapOutExpected == mapOutComputed);

        vecIn = {8, 1, 3, 7, 4, 2, 9};
        mapOutExpected = {
            {8, 0},
            {1, 1},
            {3, 2},
            {7, 3},
            {4, 4},
            {2, 5},
            {9, 6}};
        mapOutComputed = soln.buildEleIndMap(vecIn);
        assert(mapOutExpected == mapOutComputed);
    }

    void testBuildNgeRight() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected, vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.buildNgeRight(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {3};
        vecOutExpected = {-1};
        vecOutComputed = soln.buildNgeRight(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildEleIndMap();
    solnTest.testBuildNgeRight();

    return 0;
}
