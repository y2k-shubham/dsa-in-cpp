// LeetCode-442: https://leetcode.com/problems/find-all-duplicates-in-an-array/

#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
   private:
    // indirect / 2-step
    list<int> buildDuplicatesList(vector<int>& vec) {
        list<int> duplicatesList;

        for (int i = 0; i < vec.size(); i++) {
            int val = abs(vec[i]);

            if (vec[val - 1] < 0) {
                // previously negated -> 2nd occurence
                duplicatesList.push_back(val);
            } else {
                // negate to mark 1st occurence
                vec[val - 1] = -1 * vec[val - 1];
            }
        }

        return duplicatesList;
    }

    vector<int> convertToVec(list<int>& mList) {
        if (mList.empty()) {
            return {};
        }

        vector<int> vec(mList.begin(), mList.end());
        return vec;
    }

    // direct / 1-step (almost same runtime & memory)
    vector<int> buildDuplicatesVec(vector<int>& vec) {
        vector<int> duplicatesVec;

        for (int i = 0; i < vec.size(); i++) {
            int val = abs(vec[i]);

            if (vec[val - 1] < 0) {
                // previously negated -> 2nd occurence
                duplicatesVec.push_back(val);
            } else {
                // negate to mark 1st occurence
                vec[val - 1] = -1 * vec[val - 1];
            }
        }

        return duplicatesVec;
    }

   public:
    vector<int> findDuplicates(vector<int>& nums) {
        return buildDuplicatesVec(nums);
        // list <int> duplicatesList = buildDuplicatesList(nums);
        // return convertToVec(duplicatesList);
    }
};
