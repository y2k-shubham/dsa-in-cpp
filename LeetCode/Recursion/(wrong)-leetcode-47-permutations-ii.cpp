// LeetCode-47: https://leetcode.com/problems/permutations-ii/
// wrong approach

#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
private:
    bool debug = false;

    string convertToStr(vector<int>& vec) {
        if (vec.empty()) {
            return "";
        }

        ostringstream oss;
        oss << vec[0];
        for (int i = 1; i < vec.size(); i++) {
            oss << ',' << vec[i];
        }

        return oss.str();
    }

    void swap(vector<int>& vec, int idx1, int idx2) {
        int tmp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = tmp;
    }

    void permuteRec(
            vector<int>& vec,
            int idx,
            vector<vector<int> >& permutations
    ) {
        int len = vec.size();
        if (len <= idx) {
            return;
        }

        if (debug) {
            printf("invoked permuteRec(vec=%s, idx=%d, permutations)\n", convertToStr(vec).c_str(), idx);
        }

        if (idx == (len - 1)) {
            permutations.push_back(vec);
            return;
        }

        permuteRec(vec, idx + 1, permutations);

        int crrEle = vec[idx];
        for (int i = idx; i < len; i++) {
            if (crrEle == vec[i]) {
                // skip iterating if both numbers are equal
                continue;
            }

            swap(vec, idx, i);
            permuteRec(vec, idx + 1, permutations);

            // IMPORTANT: dont forget to undo
            // (otherwise we'll get duplicates / incomplete answer)
            swap(vec, idx, i);
        }
    }

public:
    friend class SolutionTest;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return {nums};
        }

        sort(nums.begin(), nums.end());

        vector<vector<int>> permutations;
        permuteRec(nums, 0, permutations);

        return permutations;
    }
};

class SolutionTest {
public:
    void testPermuteUnique() {
        Solution soln = Solution();
        vector<int> vecIn;

        soln.debug = true;
        vecIn = {3, 2, 3};
        soln.permuteUnique(vecIn);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testPermuteUnique();

    return 0;
}
