// LeetCode-46: https://leetcode.com/problems/permutations/

#include <vector>

using namespace std;

class Solution {
private:
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

        if (idx == (len - 1)) {
            permutations.push_back(vec);
            return;
        }

        for (int i = idx; i < len; i++) {
            swap(vec, idx, i);
            permuteRec(vec, idx + 1, permutations);

            // IMPORTANT: dont forget to undo
            // (otherwise we'll get duplicates / incomplete answer)
            swap(vec, idx, i);
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
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

