// LeetCode BiWeekly-Contest-196: https://leetcode.com/contest/biweekly-contest-196/problems/assign-umbrella-on-rainy-days/
// medium: work out diffs in terms of a, b, c by
// [1] re-arranging / re-assigning such that a <= b <= c
// [2] working out various possible ranges of diffs against various inputs (tree-diagram / fan-out) in terms of variable values
// that kind of simplifies the problem in mathematical relationships, runtime remains O(1)

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector <int> getSorted(int n1, int n2, int n3) {
        vector <int> nums = {n1, n2, n3};
        sort(nums.begin(), nums.end());
        return nums;
    }

    // unused
    bool hasDuplicates(vector <int>& sortedVec) {
        int n1 = sortedVec[0];
        int n2 = sortedVec[1];
        int n3 = sortedVec[2];

        return (n1 == n2) || (n2 == n3);
    }

public:
    int minRange(int a, int b, int c) {
        vector <int> sortedNums = getSorted(a, b, c);

        // this is wrong because not needed
        // if (hasDuplicates(sortedNums)) {
        //     return 0;
        // }

        a = sortedNums[0];
        b = sortedNums[1];
        c = sortedNums[2];

        int r1 = c - a;
        int r2 = b;
        int r3 = c;

        return min(r1, min(r1, r2));
    }
};
