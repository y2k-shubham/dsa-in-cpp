// LeetCode-532: https://leetcode.com/problems/k-diff-pairs-in-an-array/
// https://www.geeksforgeeks.org/count-pairs-difference-equal-k/
// https://www.hackerrank.com/challenges/pairs/problem

// InterviewBit has 3 variations
// https://www.interviewbit.com/problems/pair-with-given-difference/
// https://www.interviewbit.com/problems/diffk/
// https://www.interviewbit.com/problems/diffk-ii/

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using namespace std;

// InterviewBit-2 https://www.interviewbit.com/problems/diffk/ can be solved with this and doesn't require sorting
int findPairs(vector<int> &nums, int k) {
    int len = nums.size();
    sort(nums.begin(), nums.end());

    set<pair<int, int> > pairs;

    int i = 0;
    int j = 1;
    while (j < len && i < len) {
        if (i == j) {
            j++;
        } else {
            int diff = nums[j] - nums[i];

            if (diff < k) {
                j++;
            } else if (diff == k) {
                pairs.insert({nums[i], nums[j]});
                i++;
                j++;
            } else {
                i++;
            }
        }
    }

    return pairs.size();
}

// InterviewBit-1 https://www.interviewbit.com/problems/pair-with-given-difference/
// InterviewBit-3 https://www.interviewbit.com/problems/diffk-ii/
#include <unordered_set>
int ib1Solve(vector<int> &A, int B) {
    unordered_set<int> eleSet;

    for (int i = 0; i < A.size(); i++) {
        int crrEle = A[i];

        int crrElePlusB = crrEle + B;
        if (eleSet.find(crrElePlusB) != eleSet.end()) {
            return 1;
        }

        int crrEleMinusB = crrEle - B;
        if (eleSet.find(crrEleMinusB) != eleSet.end()) {
            return 1;
        }

        eleSet.insert(crrEle);
    }

    return 0;
}

// InterviewBit-2 https://www.interviewbit.com/problems/diffk/
int ib2diffPossible(vector<int> &nums, int k) {
    int len = nums.size();
    // sort(nums.begin(), nums.end());

    set<pair<int, int> > pairs;

    int i = 0;
    int j = 1;
    while (j < len && i < len) {
        if (i == j) {
            j++;
        } else {
            int diff = nums[j] - nums[i];

            if (diff < k) {
                j++;
            } else if (diff == k) {
                return 1;
                i++;
                j++;
            } else {
                i++;
            }
        }
    }

    return 0;
}

// InterviewBit-3 https://www.interviewbit.com/problems/diffk-ii/ alternate soln
#include <unordered_map>
unordered_map<int, int> createNumMap(const vector<int> &numVec) {
    unordered_map<int, int> numMap;
    for (int i = 0; i < numVec.size(); i++) {
        numMap[numVec[i]] = i;
    }
    return numMap;
}

int ib3diffPossible(const vector<int> &numVec, int k) {
    int len = numVec.size();
    if (len < 2) {
        return 0;
    }

    unordered_map<int, int> numIndMap = createNumMap(numVec);

    for (int i = 0; i < len; i++) {
        int ele = numVec[i];
        if ((numIndMap.find(ele - k) != numIndMap.end()) && (numIndMap[ele] != i)) {
            return 1;
        }
    }

    return 0;
}
