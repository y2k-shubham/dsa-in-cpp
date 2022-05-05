// LeetCode-457: https://leetcode.com/problems/circular-array-loop/
// incomplete (wrong answer)

#include <vector>
#include <unordered_set>
#include <cmath>

using namespace std;

class Solution {
private:
    vector<int> filterPositiveEles(vector<int>& vec) {
        vector<int> positiveVec;

        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] >= 0) {
                positiveVec.push_back(vec[i]);
            }
        }

        return positiveVec;
    }

    vector<int> filterNegativeEles(vector<int>& vec) {
        vector<int> negativeVec;

        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] >= 0) {
                negativeVec.push_back(vec[i]);
            }
        }

        return negativeVec;
    }

    bool hasSubsetOfPositiveNumMultiples(vector<int>& vec, int reqSum) {
        unordered_set<int> mSet;
        mSet.insert(0);

        int sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            int crrEle = vec[i];
            sum += crrEle;

            int multiple = 1;
            while ((sum - (reqSum * multiple) >= 0)) {
                if (mSet.find(sum - (reqSum * multiple)) != mSet.end()) {
                    return true;
                }

                ++multiple;
            }

            mSet.insert(sum);
        }

        return false;
    }

    bool hasSubsetOfNegativeNumMultiples(vector<int>& vec, int reqSum) {
        unordered_set<int> mSet;
        mSet.insert(0);

        int sum = 0;
        for (int i = 0; i < vec.size(); i++) {
            int crrEle = vec[i];
            sum += crrEle;

            int multiple = 1;
            while ((sum + (reqSum * multiple) <= 0)) {
                if (mSet.find(sum + (reqSum * multiple)) != mSet.end()) {
                    return true;
                }

                ++multiple;
            }

            mSet.insert(sum);
        }

        return false;
    }

public:
    bool circularArrayLoop(vector<int>& nums) {
        int len = nums.size();

        vector<int> positiveEles = filterPositiveEles(nums);
        if (hasSubsetOfPositiveNumMultiples(nums, len)) {
            return true;
        }

        vector<int> naegaEles = filterNegativeEles(nums);
        if (hasSubsetOfNegativeNumMultiples(nums, len)) {
            return true;
        }

        return false;
    }
};
