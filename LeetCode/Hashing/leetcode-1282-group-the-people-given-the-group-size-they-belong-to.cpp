// LeetCode-1282: https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int> &groupSizes) {
        vector<vector<int> > groupsVec;

        unordered_map<int, vector<int> > groupSizePeopleIdxMap;
        for (int i = 0; i < groupSizes.size(); i++) {
            groupSizePeopleIdxMap[groupSizes[i]].push_back(i);
            if (groupSizePeopleIdxMap[groupSizes[i]].size() == groupSizes[i]) {
                groupsVec.push_back(groupSizePeopleIdxMap[groupSizes[i]]);
                groupSizePeopleIdxMap[groupSizes[i]].clear();
            }
        }

        return groupsVec;
    }
};
