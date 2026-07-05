// LeetCode-760: https://leetcode.com/problems/find-anagram-mappings/

#include <unordered_map>
#include <list>

using namespace std;

class Solution {
private:
    unordered_map<int, list<int>> createEleIndexesMap(vector<int>& vec) {
        unordered_map<int, list<int>> eleIndexesMap;

        for (int i = 0; i < vec.size(); i++) {
            eleIndexesMap[vec[i]].push_back(i);
        }

        return eleIndexesMap;
    }

    int getNextIndex(unordered_map<int, list<int>>& eleIndexesMap, int ele) {
        int index = eleIndexesMap[ele].front();
        eleIndexesMap[ele].pop_front();
        return index;
    }

public:
    vector<int> anagramMappings(vector<int>& nums1, vector<int>& nums2) {
        int len = nums1.size();
        if (len == 0) {
            return {};
        } else if (len == 1) {
            return {0};
        }

        unordered_map<int, list<int>> eleIndexesMap = createEleIndexesMap(nums2);

        vector <int> mapping(len, -1);
        for (int i = 0; i < len; i++) {
            mapping[i] = getNextIndex(eleIndexesMap, nums1[i]);
        }

        return mapping;
    }
};
