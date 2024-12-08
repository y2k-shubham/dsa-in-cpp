// LeetCode-2540: https://leetcode.com/problems/minimum-common-value/

#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_set <int> findIntersection(unordered_set <int> set1, unordered_set <int> set2) {
        unordered_set <int> intersection;

        for (auto it = set1.begin(); it != set1.end(); it++) {
            if (set2.find(*it) != set2.end()) {
                intersection.insert(*it);
            }
        }

        return intersection;
    }

public:
    int getCommon(vector <int>& nums1, vector <int>& nums2) {
        unordered_set <int> set1(nums1.begin(), nums1.end());
        unordered_set <int> set2(nums2.begin(), nums2.end());

        auto intersectionSet = findIntersection(set1, set2);
        if (intersectionSet.empty()) {
            return -1;
        }

        vector <int> intersectionVec(intersectionSet.begin(), intersectionSet.end());
        sort(intersectionVec.begin(), intersectionVec.end());

        return intersectionVec.empty() ? -1 : intersectionVec.front();
    }
};
